#pragma managed(push, off)

#include "LuaDebugger.h"
#include "../../zip/zip.h"
#include "../../smallobj/SmallObj.h"
#include "debuglog/errormessage.h"

// ************************************************************************************************************************************************************
enum NetStatus
{
	EM_NET_DISCONNECTED	,
	EM_NET_CONNECTING	,
	EM_NET_CONNECTED
};
// ************************************************************************************************************************************************************

LuaDebugger* LuaDebugger::m_This = NULL;

// ************************************************************************************************************************************************************
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
LuaDebugger::LuaDebugger()
{
	m_ZoneID			= 0;

	m_DebuggingThread	= NULL;
	m_Locker			= "";
	m_State				= EM_LD_STATE_FREE;
	m_StepLevel			= 0;
	m_CurrentFile		= "";
	m_CurrentLine		= -1;

	m_NetBridge			= CreateNetBridge();
	m_NetID				= 0xFFFFFFFF;
	m_NetStatus			= EM_NET_DISCONNECTED;
	m_AgentIP			= "";
	m_AgentPort			= 0;
	m_LoadFdbLuaScript  = false;
	m_LoadTxtLuaScript  = false;
	m_ResourcePath		= "";
	m_LuaPath			= "";
	m_LastConnetTick	= GetTickCount();
	m_SelfFlush			= false;

	m_Buffer			= NULL;
	m_BufferSize		= 0;

	m_FileTransfer		= new LuaDebuggerFileTransfer(m_NetBridge, EM_LD_PG_LD_DC_FILE_TRANSFER);

	m_TempVariableString = "";

	InitPGCallBack();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
LuaDebugger::~LuaDebugger()
{
	ClearAllBreakPoint();
	DeleteNetBridge(m_NetBridge);

	if (m_Buffer != NULL)
	{
		delete m_Buffer;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Init(int iZoneID, const char* pszAgentIP, int iAgentPort, bool bLoadFdbLuaScript,
					   bool bLoadTxtLuaScript, const char* pszResourcePath, const char* pszLuaPath,
					   PFUNC_GET_GUID pFuncGUID, PFUNC_GET_ORGOBJID pFuncOrgObjID, bool bSelfFlush)
{
	if (m_This == NULL)
	{
		m_This = new LuaDebugger();
		m_This->m_AgentIP			= pszAgentIP;
		m_This->m_AgentPort			= iAgentPort;
		m_This->m_ZoneID			= iZoneID;
		m_This->m_SelfFlush			= bSelfFlush;
		m_This->m_LoadFdbLuaScript	= bLoadFdbLuaScript;
		m_This->m_LoadTxtLuaScript	= bLoadTxtLuaScript;
		m_This->m_ResourcePath		= pszResourcePath;
		m_This->m_LuaPath			= pszLuaPath;
		m_This->m_GetGUID			= pFuncGUID;
		m_This->m_GetOrgObjID		= pFuncOrgObjID;
		m_This->ZipLuaScript();
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Release()
{
	if (m_This != NULL)
	{
		delete m_This;
		m_This = NULL;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Process()
{
	if (m_This == NULL)
		return;

	m_This->Net();

	m_This->m_FileTransfer->Process();

	if (m_This->m_SelfFlush)
	{
		m_This->Flush();
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::HookLuaThread(lua_State *L)
{
	if (m_This != NULL)
	{
		lua_sethook( L, &LuaDebugger::DebugHook, LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE, 0);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::BeginReloadPlot()
{
	if (m_This != NULL)
	{
		m_This->State = EM_LD_STATE_FREE;
		m_This->S_PG_LDtoDA_BEGIN_RELOAD_PLOT(m_This->m_Locker.c_str());
		m_This->Flush();
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::EndReloadPlot()
{
	if (m_This != NULL)
	{
		m_This->ZipLuaScript();
		m_This->S_PG_LDtoDA_END_RELOAD_PLOT(m_This->m_Locker.c_str());
		m_This->State = EM_LD_STATE_RUN_TO_NEXT_BP;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::DebugHook(lua_State *L, lua_Debug *ar)
{
	if (m_This == NULL)
		return;

	switch (ar->event)
	{
	case LUA_HOOKCALL:
		m_This->DebugCall(L, ar);
		break;
	case LUA_HOOKRET:
		m_This->DebugRet(L, ar);
		break;
	case LUA_HOOKLINE:
		m_This->DebugLine(L, ar);
		break;
	case LUA_HOOKCOUNT:
		break;
	case LUA_HOOKTAILRET:
		m_This->DebugTailRet(L, ar);
		break;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::OnLuaFileTransferCompleted(NetBridgeFileTransfer* pFT)
{
	if (pFT != NULL)
	{
		if (pFT->UserData != NULL)
		{
			ST_LD_FT_USER_DATA* pUserData = (ST_LD_FT_USER_DATA*)pFT->UserData;
			if (m_This != NULL)
			{
				m_This->S_PG_LDtoDA_END_SEND_LUA_FILE(pUserData->szWho.c_str());
			}			
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::ZipLuaScript()
{
	HZIP hz = CreateZip(".\\LuaScript.zip", "");

	std::string szLuaPath = m_LuaPath;
	std::string szFullPath = "";

	if(	szLuaPath.c_str()[ szLuaPath.length() - 1 ] != '\\' && szLuaPath.c_str()[ szLuaPath.length() - 1 ] != '/'	)
	{
		szLuaPath += "\\";
	}

	szFullPath = szLuaPath ;
	szFullPath += "*.lua";

	WIN32_FIND_DATAA  file_data;
	HANDLE	hfile = FindFirstFileA(szFullPath.c_str(), &file_data);

	if (hfile != INVALID_HANDLE_VALUE)
	{
		szFullPath = szLuaPath;
		szFullPath += file_data.cFileName;

		ZipAdd(hz, file_data.cFileName, szFullPath.c_str());

		while(FindNextFileA(hfile, &file_data))
		{
			szFullPath = szLuaPath;
			szFullPath += file_data.cFileName;

			ZipAdd(hz, file_data.cFileName, szFullPath.c_str());
		}
	}

	CloseZip(hz);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::SendLuaFiles(const char* pszLuaPath)
{
	std::wstring wszLuaPath				= CharToWchar(pszLuaPath);
	std::wstring wszZipFileName			= wszLuaPath + L"\\LuaScript.zip";
	std::wstring wszLocalFdbFileName	= CharToWchar(m_ResourcePath.c_str()) + L"\\fdb\\LUAScript.fdb";
	std::wstring wszDestFdbFileName		= wszLuaPath + L"\\fdb\\LUAScript.fdb";

	ST_LD_FT_USER_DATA* pUserData = new ST_LD_FT_USER_DATA();
	pUserData->szWho = m_Locker;

	NetBridgeFileSender* pSender = m_FileTransfer->CreateSender();
	pSender->PeerNetID = m_NetID;
	pSender->OnCompleted = &LuaDebugger::OnLuaFileTransferCompleted;
	pSender->UserData = pUserData;
	pSender->UserDataSize = sizeof(ST_LD_FT_USER_DATA);

	if (m_LoadFdbLuaScript)
	{
		pSender->AddFile(wszLocalFdbFileName.c_str(), wszDestFdbFileName.c_str());
	}

	if (m_LoadTxtLuaScript)
	{
		pSender->AddFile(L".\\LuaScript.zip", wszZipFileName.c_str());
	}

	m_FileTransfer->LaunchSender(pSender->GUID);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::DebugCall(lua_State *L, lua_Debug *ar)
{
	ST_LD_THREAD_STATE* pThread = GetLuaThreadState(L);

	if (pThread != NULL)
	{
		pThread->StackLevel++;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::DebugRet(lua_State *L, lua_Debug *ar)
{
	ST_LD_THREAD_STATE* pThread = GetLuaThreadState(L);

	if (pThread != NULL)
	{
		pThread->StackLevel--;

		if ((m_DebuggingThread == L) && (pThread->StackLevel < 0))
		{
			//this lua thread is finished
			State = EM_LD_STATE_RUN_TO_NEXT_BP;
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::DebugLine(lua_State *L, lua_Debug *ar)
{
	ST_LD_THREAD_STATE* pThread = GetLuaThreadState(L);

	if (pThread != NULL)
	{
		lua_getinfo(L,"Slnu", ar);

		switch (State)
		{
		case EM_LD_STATE_RUN_TO_NEXT_BP:
			{
				int iGUID = -1;
				int iOrgObjID = -1;

				if (m_GetGUID != NULL)
				{
					iGUID = m_GetGUID(L);
				}

				if (m_GetOrgObjID != NULL)
				{
					iOrgObjID = m_GetOrgObjID(iGUID);
				}

				if (IsBreakPoint(ar->source, ar->currentline, iGUID, iOrgObjID))
				{
					m_DebuggingThread = L;
					m_CurrentFile = ar->source;
					m_CurrentLine = ar->currentline;
					State = EM_LD_STATE_BLOCKING;
				}
			}
			break;
		case EM_LD_STATE_STEP_OVER:
			{
				if (m_DebuggingThread == L)
				{
					if (pThread->StackLevel <= m_StepLevel)
					{
						m_CurrentFile = ar->source;
						m_CurrentLine = ar->currentline;
						State = EM_LD_STATE_BLOCKING;
					}						
				}
			}
			break;
		case EM_LD_STATE_STEP_INTO:
			{
				if (m_DebuggingThread == L)
				{
					m_CurrentFile = ar->source;
					m_CurrentLine = ar->currentline;
					State = EM_LD_STATE_BLOCKING;
				}
			}
			break;
		}

		//blocking thread
		while (State == EM_LD_STATE_BLOCKING)
		{
			//agent connection
			Net();

			m_FileTransfer->Process();

			//flush NetBridge
			Flush();

			::Sleep(100);
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::DebugTailRet(lua_State *L, lua_Debug *ar)
{
	//this lua thread is finished
	State = EM_LD_STATE_RUN_TO_NEXT_BP;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Net()
{
	//------------------------------------------------
	//Aurora agent connect
	unsigned long dwNowTick = GetTickCount();

	switch (m_NetStatus)
	{
	case EM_NET_DISCONNECTED:
		{
			if (dwNowTick - m_LastConnetTick >= 2000)
			{
				Connect();
			}
			break;
		}
	case EM_NET_CONNECTING:
		{
			if (dwNowTick - m_LastConnetTick >= 2000)
			{
				m_NetStatus = EM_NET_DISCONNECTED;
			}
			break;
		}		
	case EM_NET_CONNECTED:
		break;
	}
	//------------------------------------------------
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::InitPGCallBack()
{
	m_PGCallBack[EM_LD_PG_DAtoLD_LOCK]					= &LuaDebugger::_PG_DAtoLD_LOCK;
	m_PGCallBack[EM_LD_PG_DAtoLD_UNLOCK]				= &LuaDebugger::_PG_DAtoLD_UNLOCK;
	m_PGCallBack[EM_LD_PG_DAtoLD_ADD_BP]				= &LuaDebugger::_PG_DAtoLD_ADD_BP;
	m_PGCallBack[EM_LD_PG_DAtoLD_REMOVE_BP]				= &LuaDebugger::_PG_DAtoLD_REMOVE_BP;
	m_PGCallBack[EM_LD_PG_DAtoLD_ENABLE_BP]				= &LuaDebugger::_PG_DAtoLD_ENABLE_BP;
	m_PGCallBack[EM_LD_PG_DAtoLD_DISABLE_BP]			= &LuaDebugger::_PG_DAtoLD_DISABLE_BP;
	m_PGCallBack[EM_LD_PG_DAtoLD_SET_BP_FILTER_GUID]	= &LuaDebugger::_PG_DAtoLD_SET_BP_FILTER_GUID;
	m_PGCallBack[EM_LD_PG_DAtoLD_SET_BP_FILTER_ORGOBJID]= &LuaDebugger::_PG_DAtoLD_SET_BP_FILTER_ORGOBJID;
	m_PGCallBack[EM_LD_PG_DAtoLD_START_DEBUGGING]		= &LuaDebugger::_PG_DAtoLD_START_DEBUGGING;
	m_PGCallBack[EM_LD_PG_DAtoLD_STOP_DEBUGGING]		= &LuaDebugger::_PG_DAtoLD_STOP_DEBUGGING;
	m_PGCallBack[EM_LD_PG_DAtoLD_RUN]					= &LuaDebugger::_PG_DAtoLD_RUN;
	m_PGCallBack[EM_LD_PG_DAtoLD_SETP_INTO]				= &LuaDebugger::_PG_DAtoLD_SETP_INTO;
	m_PGCallBack[EM_LD_PG_DAtoLD_SETP_OVER]				= &LuaDebugger::_PG_DAtoLD_SETP_OVER;
	m_PGCallBack[EM_LD_PG_DAtoLD_GET_GLOBAL_VALUE]		= &LuaDebugger::_PG_DAtoLD_GET_GLOBAL_VALUE;
	m_PGCallBack[EM_LD_PG_DAtoLD_REQUEST_LUA_FILE]		= &LuaDebugger::_PG_DAtoLD_REQUEST_LUA_FILE;	
	m_PGCallBack[EM_LD_PG_LD_DC_FILE_TRANSFER]			= &LuaDebugger::_PG_LD_DC_FILE_TRANSFER;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Connect()
{
	unsigned long dwIP = ConvertIP(m_AgentIP.c_str());

	m_NetBridge->Connect(dwIP, m_AgentPort, this);
	m_NetStatus = EM_NET_CONNECTING;
	m_LastConnetTick = GetTickCount();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Flush()
{
	if (m_NetBridge != NULL)
	{
		m_NetBridge->Flush();
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::Send(unsigned long dwSize, void* pData)
{
	if ((m_NetBridge != NULL) && (m_NetID != 0xFFFFFFFF))
	{
		m_NetBridge->Send(m_NetID, dwSize, pData);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void* LuaDebugger::GetBuffer(unsigned long dwSize)
{
	dwSize = ((dwSize / 4) + 1) * 4;

	if (dwSize > m_BufferSize)
	{
		if (m_Buffer != NULL)
		{
			delete m_Buffer;
		}

		m_BufferSize = dwSize;
		m_Buffer = new BYTE[m_BufferSize];
	}

	memset(m_Buffer, 0, m_BufferSize);

	return m_Buffer;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
ST_LD_THREAD_STATE* LuaDebugger::GetLuaThreadState(lua_State *L)
{
	ST_LD_THREAD_STATE* Result = NULL;

	std::map<lua_State*, ST_LD_THREAD_STATE>::iterator it = m_LuaThreads.find(L);

	if (it != m_LuaThreads.end())
	{
		Result = &(it->second);
	}
	else
	{
		ST_LD_THREAD_STATE newState;
		m_LuaThreads[L] = newState;
		Result = &(m_LuaThreads[L]);
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
bool LuaDebugger::IsBreakPoint(const char* pszSource, int iLine, int iGUID, int iOrgObjID)
{
	bool Result = false;

	std::string szFileName = GetFileName(pszSource);

	std::map<std::string, LuaDebuggerFile*>::iterator it = m_LuaFiles.find(szFileName.c_str());

	if (it != m_LuaFiles.end())
	{
		LuaDebuggerFile* pFile = it->second;

		if (pFile != NULL)
		{
			Result = pFile->IsBreakPoint(iLine, iGUID, iOrgObjID);
		}
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::ClearAllBreakPoint()
{
	std::map<std::string, LuaDebuggerFile*>::iterator it;

	for (it = m_LuaFiles.begin(); it != m_LuaFiles.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
		}
	}

	m_LuaFiles.clear();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
LuaDebuggerFile* LuaDebugger::GetLuaFile(const char* pszName)
{
	LuaDebuggerFile* Result = NULL;

	std::map<std::string, LuaDebuggerFile*>::iterator it = m_LuaFiles.find(pszName);

	if (it != m_LuaFiles.end())
	{
		Result = it->second;
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
bool LuaDebugger::IsLocker(const char* pszWho)
{
	return (_stricmp(m_Locker.c_str(), pszWho) == 0);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
std::string LuaDebugger::GetFileName(const char* pszFilePath)
{
	std::string Result = pszFilePath;

	int iPos1 = (int)Result.find_last_of('\\');
	int iPos2 = (int)Result.find_last_of('/');

	Result = Result.substr(max(iPos1, iPos2) + 1);

	return Result.c_str();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::GetLuaValue(lua_State *L, int iIndex, ST_LD_VALUE* pVal)
{
	pVal->DataType = lua_type(L, iIndex);

	switch (pVal->DataType)
	{
	case LUA_TNONE:
		{
			pVal->DataType = EM_LD_TNONE;
		}
		break;
	case LUA_TNIL:
		{
			pVal->DataType = EM_LD_TNIL;
		}
		break;
	case LUA_TBOOLEAN:
		{
			pVal->DataType = EM_LD_TBOOLEAN;
			pVal->Boolean = lua_toboolean(L, iIndex);
		}						
		break;
	case LUA_TLIGHTUSERDATA:
		{
			pVal->DataType = EM_LD_TLIGHTUSERDATA;
			pVal->UserData = lua_touserdata(L, iIndex);
		}
		break;
	case LUA_TNUMBER:
		{
			pVal->DataType = EM_LD_TNUMBER;
			pVal->Number = lua_tonumber(L, iIndex);
		}						
		break;
	case LUA_TSTRING:
		{
			pVal->DataType = EM_LD_TSTRING;
			pVal->String = lua_tostring(L, iIndex);
		}						
		break;
	case LUA_TTABLE:
		{
			pVal->DataType = EM_LD_TTABLE;			

			//first key
			lua_pushnil(L);

			//table kv pairs iteration
			while (lua_next(L, iIndex) != 0)
			{
				/* uses 'key' (at index -2) and 'value' (at index -1) */

				//fill value
				ST_LD_VALUE* pValue = new ST_LD_VALUE();				
				GetLuaValue(L, lua_gettop(L), pValue);

				/* removes 'value'; keeps 'key' for next iteration */
				lua_pop(L, 1);

				//fill key
				ST_LD_VALUE* pKey = new ST_LD_VALUE();
				GetLuaValue(L, lua_gettop(L), pKey);

				//add kv pair
				pVal->Key.push_back(pKey);
				pVal->Value.push_back(pValue);
			}
		}
		break;
	case LUA_TFUNCTION:
		{
			pVal->DataType = EM_LD_TFUNCTION;
			pVal->Function = (void*)(lua_tocfunction(L, iIndex));
		}
		break;
	case LUA_TUSERDATA:
		{
			pVal->DataType = EM_LD_TUSERDATA;
			pVal->UserData = lua_touserdata(L, iIndex);
		}
		break;
	case LUA_TTHREAD:
		{
			pVal->DataType = EM_LD_TTHREAD;
			pVal->Thread = (void*)(lua_tothread(L, iIndex));
		}
		break;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::GetCallStack(lua_State *L, std::vector<ST_LD_STACK_INFO>& vecOut)
{
	vecOut.clear();

	lua_Debug ar;
	int iStackLevel = 0; 

	while (lua_getstack(L, iStackLevel, &ar))
	{
		lua_getinfo(L, "Sln", &ar);

		ST_LD_STACK_INFO cs;
		cs.iLine		= ar.currentline;
		cs.szNamewhat	= ar.namewhat;
		cs.szWhat		= ar.what;
		cs.szSource		= ar.source;

		vecOut.push_back(cs);

		iStackLevel++;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::GetLocalValue(lua_State *L, std::vector<ST_LD_VALUE*>& vecOut)
{
	vecOut.clear();

	lua_Debug ar;

	if (lua_getstack(L, 0, &ar))
	{
		lua_getinfo(L, "Sln", &ar);

		const char * pszName = NULL;

		int i = 1;

		while ((pszName = lua_getlocal(L, &ar, i++)) != NULL)
		{
			//can't trace "self" as local
			if ((_stricmp(pszName, "self") != 0) && (_stricmp(pszName, "(*temporary)") != 0))
			{
				ST_LD_VALUE* pValue = new ST_LD_VALUE();

				pValue->Name = pszName;
				GetLuaValue(L, lua_gettop(L), pValue);

				vecOut.push_back(pValue);
			}

			lua_pop(L, 1);  /* remove variable value */
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::GetUpValue(lua_State *L, std::vector<ST_LD_VALUE*>& vecOut)
{
	vecOut.clear();

	lua_Debug ar;

	if (lua_getstack(L, 0, &ar))
	{
		lua_getinfo(L, "f", &ar);  /* retrieves function */

		const char * pszName = NULL;

		int i = 1;

		while ((pszName = lua_getupvalue(L, -1, i++)) != NULL)
		{
			ST_LD_VALUE* pValue = new ST_LD_VALUE();
			
			pValue->Name = pszName;
			GetLuaValue(L, lua_gettop(L), pValue);
			
			vecOut.push_back(pValue);

			lua_pop(L, 1);  /* remove variable value */
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
unsigned long LuaDebugger::GetPGLuaValueDataSize(ST_LD_VALUE* pVal)
{
	unsigned long Result = 0;
	switch (pVal->DataType)
	{
	case EM_LD_TNONE:
	case EM_LD_TNIL:
	case EM_LD_TBOOLEAN:
	case EM_LD_TLIGHTUSERDATA:
	case EM_LD_TNUMBER:
	case EM_LD_TFUNCTION:
	case EM_LD_TUSERDATA:
	case EM_LD_TTHREAD:
		{
			Result = sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TSTRING:
		{
			Result = sizeof(PG_LD_VALUE) + (unsigned long)pVal->String.length();
		}
		break;
	case EM_LD_TTABLE:
		{
			Result = sizeof(PG_LD_VALUE);
			for (int i = 0; i < (int)pVal->Key.size(); ++i)
			{
				Result += GetPGLuaValueDataSize(pVal->Key[i]);
			}

			for (int j = 0; j < (int)pVal->Value.size(); ++j)
			{
				Result += GetPGLuaValueDataSize(pVal->Value[j]);
			}
		}
		break;
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void* LuaDebugger::WirtePGLuaValue(ST_LD_VALUE* pVal, void* pBuffer)
{
	PBYTE pTraveler = (PBYTE)pBuffer;

	PG_LD_VALUE* pPGVal = (PG_LD_VALUE*)pTraveler;
	pPGVal->iType = pVal->DataType;
	safe_strcopy(pPGVal->szName, pVal->Name.c_str());

	switch (pVal->DataType)
	{
	case EM_LD_TNONE:
		{
			pPGVal->dwDataSize = 0;
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TNIL:
		{
			pPGVal->dwDataSize = 0;
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TBOOLEAN:
		{
			pPGVal->Data.Boolean = pVal->Boolean;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.Boolean);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TLIGHTUSERDATA:
		{
			pPGVal->Data.UserData = pVal->UserData;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.UserData);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TNUMBER:
		{
			pPGVal->Data.Number = pVal->Number;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.Number);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TSTRING:
		{
			strncpy(pPGVal->Data.String, pVal->String.c_str(), pVal->String.length());
			pPGVal->dwDataSize = (unsigned long)pVal->String.length();
			pTraveler += sizeof(PG_LD_VALUE);
			pTraveler += pVal->String.length();
		}
		break;
	case EM_LD_TTABLE:
		{
			pPGVal->dwDataSize = GetPGLuaValueDataSize(pVal);
			pPGVal->Data.KVCount = (int)pVal->Key.size();
			pTraveler += sizeof(PG_LD_VALUE);

			for (int i = 0; i < (int)pVal->Key.size(); ++i)
			{
				//fill key
				pTraveler = (PBYTE)WirtePGLuaValue(pVal->Key[i], pTraveler);

				//fill value
				pTraveler = (PBYTE)WirtePGLuaValue(pVal->Value[i], pTraveler);
			}
		}
		break;
	case EM_LD_TFUNCTION:
		{
			pPGVal->Data.Function = (void*)pVal->Function;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.Function);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TUSERDATA:
		{
			pPGVal->Data.UserData = pVal->UserData;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.UserData);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	case EM_LD_TTHREAD:
		{
			pPGVal->Data.Thread = (void*)pVal->Thread;
			pPGVal->dwDataSize = sizeof(pPGVal->Data.Thread);
			pTraveler += sizeof(PG_LD_VALUE);
		}
		break;
	}

	return pTraveler;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_INIT_INFO(int iZoneID)
{
	PG_LDtoDA_INIT_INFO Packet;
	Packet.iZoneID = iZoneID;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_LOCK_RESULT(const char* pszWho, const char* pszLocker, int iResult, bool bLoadFdbLuaScript, bool bLoadTxtLuaScript)
{
	PG_LDtoDA_LOCK_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Packet.bLoadFdbLuaScript = bLoadFdbLuaScript;
	Packet.bLoadTxtLuaScript = bLoadTxtLuaScript;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_UNLOCK_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_UNLOCK_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_ADD_BP_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_ADD_BP_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_REMOVE_BP_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_REMOVE_BP_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_ENABLE_BP_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_ENABLE_BP_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_DISABLE_BP_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_DISABLE_BP_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_SET_BP_FILTER_GUID_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_START_DEBUGGING_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_START_DEBUGGING_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_STOP_DEBUGGING_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_STOP_DEBUGGING_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_RUN_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_RUN_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_SETP_INTO_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_SETP_INTO_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_SETP_OVER_RESULT(const char* pszWho, const char* pszLocker, int iResult)
{
	PG_LDtoDA_SETP_OVER_RESULT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szLocker, pszLocker);
	Packet.iResult = iResult;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BREAK_AT(const char* pszWho, const char* pszFileName, int iLine)
{
	PG_LDtoDA_BREAK_AT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	safe_strcopy(Packet.szFileName, pszFileName);
	Packet.iLine = iLine;
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE(const char* pszWho)
{
	PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_LOCAL_VALUE(const char* pszWho, ST_LD_VALUE* pVal)
{
	unsigned long dwSize = sizeof(PG_LDtoDA_LOCAL_VALUE);
	dwSize += GetPGLuaValueDataSize(pVal);

	void* pData = GetBuffer(dwSize);
	PBYTE pTraveler = (PBYTE)pData;

	PG_LDtoDA_LOCAL_VALUE* pHeader = (PG_LDtoDA_LOCAL_VALUE*)pTraveler;
	pHeader->iType = EM_LD_PG_LDtoDA_LOCAL_VALUE;
	safe_strcopy(pHeader->szWho, pszWho);
	pTraveler += sizeof(PG_LDtoDA_LOCAL_VALUE);

	WirtePGLuaValue(pVal, pTraveler);

	Send(dwSize, pData);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_END_SEND_LOCAL_VALUE(const char* pszWho)
{
	PG_LDtoDA_END_SEND_LOCAL_VALUE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BEGIN_SEND_UP_VALUE(const char* pszWho)
{
	PG_LDtoDA_BEGIN_SEND_UP_VALUE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_UP_VALUE(const char* pszWho, ST_LD_VALUE* pVal)
{
	unsigned long dwSize = sizeof(PG_LDtoDA_UP_VALUE);
	dwSize += GetPGLuaValueDataSize(pVal);

	void* pData = GetBuffer(dwSize);
	PBYTE pTraveler = (PBYTE)pData;

	PG_LDtoDA_UP_VALUE* pHeader = (PG_LDtoDA_UP_VALUE*)pData;
	pHeader->iType = EM_LD_PG_LDtoDA_UP_VALUE;
	safe_strcopy(pHeader->szWho, pszWho);
	pTraveler += sizeof(PG_LDtoDA_UP_VALUE);

	WirtePGLuaValue(pVal, pTraveler);

	Send(dwSize, pData);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_END_SEND_UP_VALUE(const char* pszWho)
{
	PG_LDtoDA_END_SEND_UP_VALUE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_GLOBAL_VALUE(const char* pszWho, ST_LD_VALUE* pVal)
{
	unsigned long dwSize = sizeof(PG_LDtoDA_GLOBAL_VALUE);
	dwSize += GetPGLuaValueDataSize(pVal);

	void* pData = GetBuffer(dwSize);
	PBYTE pTraveler = (PBYTE)pData;

	PG_LDtoDA_GLOBAL_VALUE* pHeader = (PG_LDtoDA_GLOBAL_VALUE*)pData;
	pHeader->iType = EM_LD_PG_LDtoDA_GLOBAL_VALUE;
	safe_strcopy(pHeader->szWho, pszWho);
	pTraveler += sizeof(PG_LDtoDA_GLOBAL_VALUE);

	WirtePGLuaValue(pVal, pTraveler);

	Send(dwSize, pData);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BEGIN_SEND_LUA_FILE(const char* pszWho)
{
	PG_LDtoDA_BEGIN_SEND_LUA_FILE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_END_SEND_LUA_FILE(const char* pszWho)
{
	PG_LDtoDA_END_SEND_LUA_FILE Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BEGIN_RELOAD_PLOT(const char* pszWho)
{
	PG_LDtoDA_BEGIN_RELOAD_PLOT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_END_RELOAD_PLOT(const char* pszWho)
{
	PG_LDtoDA_END_RELOAD_PLOT Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_BEGIN_SEND_CALL_STACK(const char* pszWho)
{
	PG_LDtoDA_BEGIN_SEND_CALL_STACK Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_CALL_STACK(const char* pszWho, ST_LD_STACK_INFO* pInfo)
{
	unsigned long dwSize = sizeof(PG_LDtoDA_CALL_STACK);

	dwSize += (unsigned long)pInfo->szSource.length();

	dwSize = ((dwSize / 4) + 1) * 4;

	void* pData = GetBuffer(dwSize);
	memset(pData, 0, dwSize);

	PG_LDtoDA_CALL_STACK* pHeader = (PG_LDtoDA_CALL_STACK*)pData;
	pHeader->iType = EM_LD_PG_LDtoDA_CALL_STACK;
	safe_strcopy(pHeader->szWho, pszWho);

	pHeader->Info.iStackLevel	= pInfo->iStackLevel;
	pHeader->Info.iLine			= pInfo->iLine;
	safe_strcopy(pHeader->Info.szNamewhat	, pInfo->szNamewhat.c_str());
	safe_strcopy(pHeader->Info.szWhat		, pInfo->szWhat.c_str());
	safe_strcopy(pHeader->Info.szSource		, pInfo->szSource.c_str());

	Send(dwSize, pData);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::S_PG_LDtoDA_END_SEND_CALL_STACK(const char* pszWho)
{
	PG_LDtoDA_END_SEND_CALL_STACK Packet;
	safe_strcopy(Packet.szWho, pszWho);
	Send(sizeof(Packet), &Packet);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_LOCK(const char* pszWho)
{
	if (m_Locker.empty() || IsLocker(pszWho))
	{
		m_Locker = pszWho;

		S_PG_LDtoDA_LOCK_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK, m_LoadFdbLuaScript, m_LoadTxtLuaScript);

		//remove all break point
		ClearAllBreakPoint();

		State = EM_LD_STATE_FREE;
	}
	else
	{
		S_PG_LDtoDA_LOCK_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED, m_LoadFdbLuaScript, m_LoadTxtLuaScript);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_UNLOCK(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		m_Locker = "";

		S_PG_LDtoDA_UNLOCK_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);

		//remove all break point
		ClearAllBreakPoint();

		State = EM_LD_STATE_FREE;
	}
	else
	{
		S_PG_LDtoDA_UNLOCK_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_ADD_BP(const char* pszWho, const char* pszFileName, int iLine)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile ==  NULL)
		{
			pLuaFile = new LuaDebuggerFile(pszFileName);
			m_LuaFiles[pszFileName] = pLuaFile;
		}

		pLuaFile->AddBreakPoint(iLine);

		S_PG_LDtoDA_ADD_BP_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_ADD_BP_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_REMOVE_BP(const char* pszWho, const char* pszFileName, int iLine)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile != NULL)
		{
			pLuaFile->RemoveBreakPoint(iLine);
		}

		S_PG_LDtoDA_REMOVE_BP_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_REMOVE_BP_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_ENABLE_BP(const char* pszWho, const char* pszFileName, int iLine)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile != NULL)
		{
			pLuaFile->EnableBreakPoint(iLine);
		}

		S_PG_LDtoDA_ENABLE_BP_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_ENABLE_BP_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_DISABLE_BP(const char* pszWho, const char* pszFileName, int iLine)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile != NULL)
		{
			pLuaFile->DisableBreakPoint(iLine);
		}

		S_PG_LDtoDA_DISABLE_BP_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_DISABLE_BP_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_SET_BP_FILTER_GUID(const char* pszWho, const char* pszFileName, int iLine, int iGUID)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile != NULL)
		{
			pLuaFile->SetGUID(iLine, iGUID);
		}

		S_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_SET_BP_FILTER_ORGOBJID(const char* pszWho, const char* pszFileName, int iLine, int iOrgObjID)
{
	if (IsLocker(pszWho))
	{
		LuaDebuggerFile* pLuaFile = GetLuaFile(pszFileName);

		if (pLuaFile != NULL)
		{
			pLuaFile->SetOrgObjID(iLine, iOrgObjID);
		}

		S_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_START(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		State = EM_LD_STATE_RUN_TO_NEXT_BP;

		S_PG_LDtoDA_START_DEBUGGING_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_START_DEBUGGING_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_STOP(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		State = EM_LD_STATE_FREE;

		S_PG_LDtoDA_STOP_DEBUGGING_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_STOP_DEBUGGING_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_RUN(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		State = EM_LD_STATE_RUN_TO_NEXT_BP;

		S_PG_LDtoDA_RUN_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
	}
	else
	{
		S_PG_LDtoDA_RUN_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_SETP_INTO(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		if (State == EM_LD_STATE_BLOCKING)
		{
			State = EM_LD_STATE_STEP_INTO;
			S_PG_LDtoDA_SETP_INTO_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
		}
		else
		{
			S_PG_LDtoDA_SETP_INTO_RESULT(pszWho, pszWho, EM_LD_STEP_INTO_RET_NONE_BLOCKED);
		}
	}
	else
	{
		S_PG_LDtoDA_SETP_INTO_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_SETP_OVER(const char* pszWho)
{
	if (IsLocker(pszWho))
	{
		if (State == EM_LD_STATE_BLOCKING)
		{
			State = EM_LD_STATE_STEP_OVER;
			S_PG_LDtoDA_SETP_OVER_RESULT(pszWho, pszWho, EM_LD_COMMON_RET_OK);
		}
		else
		{
			S_PG_LDtoDA_SETP_OVER_RESULT(pszWho, pszWho, EM_LD_STEP_OVER_RET_NONE_BLOCKED);
		}
	}
	else
	{
		S_PG_LDtoDA_SETP_OVER_RESULT(pszWho, m_Locker.c_str(), EM_LD_COMMON_RET_ZONE_LOCKED);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_GET_GLOBAL_VALUE(const char* pszWho, const char* pszValName)
{
	if (IsLocker(pszWho))
	{
		if (m_DebuggingThread != NULL)
		{
			lua_State* L = m_DebuggingThread;

			_strlwr( (char*)pszValName );	

			lua_getglobal(L, pszValName);

			int DataType = lua_type(L, -1);

			ST_LD_VALUE* pValue = new ST_LD_VALUE();
			
			pValue->Name = pszValName;
			GetLuaValue(L, lua_gettop(L), pValue);			

			lua_pop(L, 1);

			S_PG_LDtoDA_GLOBAL_VALUE(pszWho, pValue);

			delete pValue;
		}
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_DAtoLD_REQUEST_LUA_FILE	(unsigned long dwNetID, const char* pszWho, const char* pszLuaPath)
{
	if (IsLocker(pszWho))
	{
		S_PG_LDtoDA_BEGIN_SEND_LUA_FILE(pszWho);
		SendLuaFiles(pszLuaPath);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::On_PG_LD_DC_FILE_TRANSFER(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	if (m_FileTransfer != NULL)
	{
		m_FileTransfer->Recv(dwNetID, dwSize, PG);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_LOCK(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_LOCK* pPkt = (PG_DAtoLD_LOCK*)(PG);
	On_PG_DAtoLD_LOCK(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_UNLOCK(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_UNLOCK* pPkt = (PG_DAtoLD_UNLOCK*)(PG);
	On_PG_DAtoLD_UNLOCK(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_ADD_BP(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_ADD_BP* pPkt = (PG_DAtoLD_ADD_BP*)(PG);
	On_PG_DAtoLD_ADD_BP(pPkt->szWho, pPkt->szFileName, pPkt->iLine);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_REMOVE_BP(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_REMOVE_BP* pPkt = (PG_DAtoLD_REMOVE_BP*)(PG);
	On_PG_DAtoLD_REMOVE_BP(pPkt->szWho, pPkt->szFileName, pPkt->iLine);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_ENABLE_BP(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_ENABLE_BP* pPkt = (PG_DAtoLD_ENABLE_BP*)(PG);
	On_PG_DAtoLD_ENABLE_BP(pPkt->szWho, pPkt->szFileName, pPkt->iLine);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_DISABLE_BP(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_DISABLE_BP* pPkt = (PG_DAtoLD_DISABLE_BP*)(PG);
	On_PG_DAtoLD_DISABLE_BP(pPkt->szWho, pPkt->szFileName, pPkt->iLine);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_SET_BP_FILTER_GUID(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_SET_BP_FILTER_GUID* pPkt = (PG_DAtoLD_SET_BP_FILTER_GUID*)(PG);
	On_PG_DAtoLD_SET_BP_FILTER_GUID(pPkt->szWho, pPkt->szFileName, pPkt->iLine, pPkt->iGUID);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_SET_BP_FILTER_ORGOBJID(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_SET_BP_FILTER_ORGOBJID* pPkt = (PG_DAtoLD_SET_BP_FILTER_ORGOBJID*)(PG);
	On_PG_DAtoLD_SET_BP_FILTER_ORGOBJID(pPkt->szWho, pPkt->szFileName, pPkt->iLine, pPkt->iOrgObjID);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_START_DEBUGGING(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_START_DEBUGGING* pPkt = (PG_DAtoLD_START_DEBUGGING*)(PG);
	On_PG_DAtoLD_START(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_STOP_DEBUGGING(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_STOP_DEBUGGING* pPkt = (PG_DAtoLD_STOP_DEBUGGING*)(PG);
	On_PG_DAtoLD_STOP(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_RUN(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_RUN* pPkt = (PG_DAtoLD_RUN*)(PG);
	On_PG_DAtoLD_RUN(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_SETP_INTO(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_SETP_INTO* pPkt = (PG_DAtoLD_SETP_INTO*)(PG);
	On_PG_DAtoLD_SETP_INTO(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_SETP_OVER(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_SETP_OVER* pPkt = (PG_DAtoLD_SETP_OVER*)(PG);
	On_PG_DAtoLD_SETP_OVER(pPkt->szWho);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_GET_GLOBAL_VALUE(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_GET_GLOBAL_VALUE* pPkt = (PG_DAtoLD_GET_GLOBAL_VALUE*)(PG);
	On_PG_DAtoLD_GET_GLOBAL_VALUE(pPkt->szWho, pPkt->szVarName);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_DAtoLD_REQUEST_LUA_FILE(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_DAtoLD_REQUEST_LUA_FILE* pPkt = (PG_DAtoLD_REQUEST_LUA_FILE*)(PG);
	On_PG_DAtoLD_REQUEST_LUA_FILE(dwNetID, pPkt->szWho, pPkt->szLuaPath);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::_PG_LD_DC_FILE_TRANSFER(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_LD_DC_FILE_TRANSFER* pPkt = (PG_LD_DC_FILE_TRANSFER*)(PG);
	PBYTE pTraveler = (PBYTE)PG;
	pTraveler += sizeof(PG_LD_DC_FILE_TRANSFER);
	On_PG_LD_DC_FILE_TRANSFER(dwNetID, pPkt->dwDataSize, pTraveler);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
bool LuaDebugger::OnRecv(unsigned long dwNetID, unsigned long dwPackSize, void* PG)
{
	bool Result = false;

	if (PG)
	{
		LD_PG_BASE *pPkt = reinterpret_cast<LD_PG_BASE *>(PG);

		PFUNC_LD_NETPG pFunc = m_PGCallBack[pPkt->iType];

		if (pFunc)
		{
			(this->*pFunc)(dwNetID, dwPackSize, PG);
			Result = true;
		}
		else
		{
			Print(LV5, "LuaDebugger::OnRecv", "pFunc NULL, iType = %d", pPkt->iType);
		}
	}
	else
	{
		Print(LV5, "LuaDebugger::OnRecv", "PG NULL");
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::OnConnectFailed(unsigned long dwNetID, unsigned long dwFailedCode)
{
	m_NetID = 0xFFFFFFFF;
	m_NetStatus = EM_NET_DISCONNECTED;
	Print(LV5, "", "LuaDebugger Agent (netID: %d) ConnectFailed, code = %d", dwNetID, dwFailedCode);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::OnConnect(unsigned long dwNetID)
{
	m_NetID = dwNetID;
	m_NetStatus = EM_NET_CONNECTED;
	S_PG_LDtoDA_INIT_INFO(m_ZoneID);
	Print(LV2, "", "LuaDebugger Agent (netID: %d) Connected", dwNetID);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::OnDisconnect(unsigned long dwNetID)
{
	m_NetID = 0xFFFFFFFF;
	m_NetStatus = EM_NET_DISCONNECTED;
	Print(LV2, "", "LuaDebugger Agent (netID: %d) Disconnected", dwNetID);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
CEventObj* LuaDebugger::OnAccept(unsigned long dwNetID)
{
	return this;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebugger::SetState(int value)
{
	if (m_State == value)
		return;

	m_State	= value;

	switch (m_State)
	{
	case EM_LD_STATE_FREE:
		{
			m_DebuggingThread = NULL;
			m_StepLevel = 0;
		}
		break;
	case EM_LD_STATE_BLOCKING:
		{
			if (m_DebuggingThread != NULL)
			{
				lua_State* L = m_DebuggingThread;

				S_PG_LDtoDA_BREAK_AT(m_Locker.c_str(), m_CurrentFile.c_str(), m_CurrentLine);

				std::vector<ST_LD_VALUE*> vecLocal;
				std::vector<ST_LD_VALUE*> vecUpValue;
				std::vector<ST_LD_STACK_INFO> vecCallStack;
				ST_LD_VALUE* pValue = NULL;

				GetLocalValue(L, vecLocal);
				GetUpValue(L, vecUpValue);
				GetCallStack(L, vecCallStack);

				//send local valuable
				S_PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE(m_Locker.c_str());
				for (int i = 0; i < (int)vecLocal.size(); ++i)
				{
					pValue = vecLocal[i];
					S_PG_LDtoDA_LOCAL_VALUE(m_Locker.c_str(), pValue);
					delete pValue;
				}
				S_PG_LDtoDA_END_SEND_LOCAL_VALUE(m_Locker.c_str());

				//send up value
				S_PG_LDtoDA_BEGIN_SEND_UP_VALUE(m_Locker.c_str());
				for (int i = 0; i < (int)vecUpValue.size(); ++i)
				{
					pValue = vecUpValue[i];
					S_PG_LDtoDA_UP_VALUE(m_Locker.c_str(), pValue);
					delete pValue;
				}
				S_PG_LDtoDA_END_SEND_UP_VALUE(m_Locker.c_str());

				//send call stack
				S_PG_LDtoDA_BEGIN_SEND_CALL_STACK(m_Locker.c_str());
				for (int i = 0; i < (int)vecCallStack.size(); ++i)
				{
					S_PG_LDtoDA_CALL_STACK(m_Locker.c_str(), &(vecCallStack[i]));
				}
				S_PG_LDtoDA_END_SEND_CALL_STACK(m_Locker.c_str());
			}
		}
		break;
	case EM_LD_STATE_RUN_TO_NEXT_BP:
		{
			m_DebuggingThread = NULL;
			m_StepLevel = 0;
			m_CurrentFile = "";
			m_CurrentLine = -1;
		}
		break;
	case EM_LD_STATE_STEP_OVER:
		{
			m_StepLevel = 0;

			ST_LD_THREAD_STATE* pThread = GetLuaThreadState(m_DebuggingThread);
			if (pThread)
			{
				m_StepLevel = pThread->StackLevel;
			}
		}
		break;
	case EM_LD_STATE_STEP_INTO:
		break;
	}
}

// ************************************************************************************************************************************************************

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
LuaDebuggerFile::LuaDebuggerFile(const char* pszName)
{
	m_Name = pszName;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
LuaDebuggerFile::~LuaDebuggerFile()
{

}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
ST_LD_BREAK_POINT* LuaDebuggerFile::GetBreakPoint(int iLine)
{
	ST_LD_BREAK_POINT* Result = NULL;

	std::map<int, ST_LD_BREAK_POINT>::iterator it = m_BreakPoints.find(iLine);

	if (it != m_BreakPoints.end())
	{
		Result = &(it->second);
	}

	return Result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::AddBreakPoint(int iLine)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP == NULL)
	{
		ST_LD_BREAK_POINT newBP;
		newBP.Line = iLine;
		newBP.Status = EM_BP_STATUS_ENABLED;

		m_BreakPoints[iLine] = newBP;
	}
}
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::RemoveBreakPoint(int iLine)
{
	std::map<int, ST_LD_BREAK_POINT>::iterator it = m_BreakPoints.find(iLine);

	if (it != m_BreakPoints.end())
	{
		m_BreakPoints.erase(it);
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::EnableBreakPoint(int iLine)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP != NULL)
	{
		pBP->Status = EM_BP_STATUS_ENABLED;
	}
}
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::DisableBreakPoint(int iLine)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP != NULL)
	{
		pBP->Status = EM_BP_STATUS_DISABLED;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::SetGUID(int iLine, int iGUID)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP != NULL)
	{
		pBP->GUID = iGUID;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void LuaDebuggerFile::SetOrgObjID(int iLine, int iOrgObjID)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP != NULL)
	{
		pBP->OrgObjID = iOrgObjID;
	}
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
bool LuaDebuggerFile::IsBreakPoint(int iLine, int iGUID, int iOrgObjID)
{
	ST_LD_BREAK_POINT* pBP = GetBreakPoint(iLine);

	if (pBP != NULL)
	{
		if (pBP->GUID >= 0)
		{
			if (pBP->GUID == iGUID)
			{
				return true;
			}
			else
			{
				return false;
			}			
		}

		if (pBP->OrgObjID >= 0)
		{
			if (pBP->OrgObjID == iOrgObjID)
			{
				return true;
			}
			else
			{
				return false;
			}			
		}

		return true;
	}
	else
	{
		return false;
	}	
}

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
LuaDebuggerFileTransfer::LuaDebuggerFileTransfer(CNetBridge* pNetBridge, int iPGBaseID)
:NetBridgeFileTransferManager(pNetBridge, iPGBaseID)
{

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int LuaDebuggerFileTransfer::GetHeaderSize()
{
	return sizeof(PG_LD_DC_FILE_TRANSFER);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void LuaDebuggerFileTransfer::Send(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	PG_LD_DC_FILE_TRANSFER* pHeader = (PG_LD_DC_FILE_TRANSFER*)PG;
	pHeader->iType = EM_LD_PG_LD_DC_FILE_TRANSFER;
	pHeader->dwDataSize = dwSize - sizeof(PG_LD_DC_FILE_TRANSFER);

	if (m_NetBridge != NULL)
	{
		m_NetBridge->Send(dwNetID, dwSize, PG);
	}
}
// ************************************************************************************************************************************************************
#pragma managed(pop)