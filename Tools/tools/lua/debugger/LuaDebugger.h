#pragma once

#ifndef __LUA_DEBUDDER_H__
#define __LUA_DEBUDDER_H__
#pragma managed(push, off)

#include <vector>
#include <deque>
#include <map>

extern "C"{
#include "../lua.h"
#include "../lauxlib.h"
#include "../lualib.h"
#include "../llex.h"
#include "../lfunc.h"
#include "../ldo.h"
#include "../lmem.h"
#include "../lobject.h"
#include "../lopcodes.h"
#include "../lstring.h"
#include "../lundump.h"
};

#include "../../netbridge/NetBridge.h"
#include "../../NetBridgeFileTransfer/NetBridgeFileTransfer.h"
#include "PG_LuaDebugger.h"


// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
enum LuaBreakPointStatus
{
	EM_BP_STATUS_DISABLED	,
	EM_BP_STATUS_ENABLED
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
enum LuaDebuggerState
{
	EM_LD_STATE_FREE		  ,
	EM_LD_STATE_BLOCKING	  ,
	EM_LD_STATE_RUN_TO_NEXT_BP,
	EM_LD_STATE_STEP_OVER	  ,
	EM_LD_STATE_STEP_INTO
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct ST_LD_THREAD_STATE
{
	int	StackLevel;

	ST_LD_THREAD_STATE()
	{
		StackLevel = -1;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct ST_LD_BREAK_POINT
{
	int Line;
	int Status;
	int GUID;
	int OrgObjID;

	ST_LD_BREAK_POINT()
	{
		Line = -1;
		Status = EM_BP_STATUS_DISABLED;
		GUID = -1;
		OrgObjID = -1;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct ST_LD_FT_USER_DATA
{
	std::string szWho;

	ST_LD_FT_USER_DATA()
	{
		szWho = "";
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct ST_LD_VALUE
{
	int	DataType;
	union
	{
		int		Boolean;
		double	Number;
		void*	Thread;
		void*	UserData;
		void*	Function;
	};

	std::string				 Name;
	std::string				 String;
	std::vector<ST_LD_VALUE*> Key;
	std::vector<ST_LD_VALUE*> Value;

	ST_LD_VALUE()
	{
		DataType	= EM_LD_TNONE;
		Boolean		= 0;
		Number		= 0;
		Thread		= NULL;
		UserData	= NULL;
		Function	= NULL;
		Name		= "";
		String		= "";
	}

	~ST_LD_VALUE()
	{
		int i = 0;
		for (i = 0; i < (int)Key.size(); ++i)
		{
			if (Key[i] != NULL)
			{
				delete Key[i];
			}
		}

		for (i = 0; i < (int)Value.size(); ++i)
		{
			if (Value[i] != NULL)
			{
				delete Value[i];
			}
		}
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct ST_LD_STACK_INFO
{
	int			iStackLevel;
	int			iLine;
	std::string szNamewhat;
	std::string szWhat;
	std::string szSource;

	ST_LD_STACK_INFO()
	{
		iStackLevel = 0;
		iLine = 0;
		szNamewhat = "";
		szWhat = "";
		szSource = "";
	}
};

// ************************************************************************************************************************************************************
class LuaDebugger;
class LuaDebuggerFile;
class LuaDebuggerFileTransfer;

// ************************************************************************************************************************************************************
typedef void  (LuaDebugger::*PFUNC_LD_NETPG) (unsigned long dwNetID , unsigned long dwSize, void* PG);
typedef int  (*PFUNC_GET_GUID) (lua_State *L);
typedef int  (*PFUNC_GET_ORGOBJID) (int iOwnerID);

// ************************************************************************************************************************************************************
class LuaDebugger : public CEventObj
{
protected:
	static LuaDebugger*						m_This;

protected:
	std::map<lua_State*, ST_LD_THREAD_STATE>m_LuaThreads;
	std::map<std::string, LuaDebuggerFile*>	m_LuaFiles;	
	int										m_ZoneID;
	
	//state control
	lua_State*								m_DebuggingThread;
	std::string								m_Locker;
	int										m_State;
	int										m_StepLevel;  // for step over
	std::string								m_CurrentFile;
	int										m_CurrentLine;

	//net
	CNetBridge*								m_NetBridge;
	std::map<int, PFUNC_LD_NETPG>			m_PGCallBack;
	unsigned long							m_NetID;
	int										m_NetStatus;
	std::string								m_AgentIP;
	int										m_AgentPort;
	bool									m_LoadFdbLuaScript;
	bool									m_LoadTxtLuaScript;
	std::string								m_ResourcePath;
	std::string								m_LuaPath;
	unsigned long							m_LastConnetTick;
	bool									m_SelfFlush;

	void*									m_Buffer;
	unsigned long							m_BufferSize;

	LuaDebuggerFileTransfer*				m_FileTransfer;

	PFUNC_GET_GUID							m_GetGUID;
	PFUNC_GET_ORGOBJID						m_GetOrgObjID;

	std::string								m_TempVariableString;

public:
	LuaDebugger();
	virtual ~LuaDebugger();

public:
	static void Init(int iZoneID, const char* pszAgentIP, int iAgentPort, bool bLoadFdbLuaScript,
		bool bLoadTxtLuaScript, const char* pszResourcePath, const char* pszLuaPath,
		PFUNC_GET_GUID pFuncGUID, PFUNC_GET_ORGOBJID pFuncOrgObjID, bool bSelfFlush = false);
	static void Release();

public:
	static void Process();

public:
	static void HookLuaThread(lua_State *L);
	static void BeginReloadPlot();
	static void EndReloadPlot();

protected:
	static void DebugHook(lua_State *L, lua_Debug *ar);
	static void OnLuaFileTransferCompleted(NetBridgeFileTransfer* pFT);

protected:
	void ZipLuaScript();
	void SendLuaFiles(const char* pszLuaPath);

protected:
	void DebugCall		(lua_State *L, lua_Debug *ar);
	void DebugRet		(lua_State *L, lua_Debug *ar);
	void DebugLine		(lua_State *L, lua_Debug *ar);
	void DebugTailRet	(lua_State *L, lua_Debug *ar);

protected:
	void InitPGCallBack();
	void Net();
	void Connect();
	void Flush();
	void Send(unsigned long dwSize, void* pData);
	void* GetBuffer(unsigned long dwSize);

protected:	
	ST_LD_THREAD_STATE*	GetLuaThreadState(lua_State *L);
	bool				IsBreakPoint(const char* pszSource, int iLine, int iGUID, int iOrgObjID);
	void				ClearAllBreakPoint();
	LuaDebuggerFile*	GetLuaFile(const char* pszName);
	bool				IsLocker(const char* pszWho);
	std::string			GetFileName(const char* pszFilePath);
	void				GetLuaValue(lua_State *L, int iIndex, ST_LD_VALUE* pVal);
	void				GetCallStack(lua_State *L, std::vector<ST_LD_STACK_INFO>& vecOut);
	void				GetLocalValue(lua_State *L, std::vector<ST_LD_VALUE*>& vecOut);
	void				GetUpValue(lua_State *L, std::vector<ST_LD_VALUE*>& vecOut);
	unsigned long		GetPGLuaValueDataSize(ST_LD_VALUE* pVal);
	void*				WirtePGLuaValue(ST_LD_VALUE* pVal, void* pBuffer);

protected:
	void S_PG_LDtoDA_INIT_INFO						(int iZoneID);
	void S_PG_LDtoDA_LOCK_RESULT					(const char* pszWho, const char* pszLocker, int iResult, bool bLoadFdbLuaScript, bool bLoadTxtLuaScript);
	void S_PG_LDtoDA_UNLOCK_RESULT					(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_ADD_BP_RESULT					(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_REMOVE_BP_RESULT				(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_ENABLE_BP_RESULT				(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_DISABLE_BP_RESULT				(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT		(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT	(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_START_DEBUGGING_RESULT			(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_STOP_DEBUGGING_RESULT			(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_RUN_RESULT						(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_SETP_INTO_RESULT				(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_SETP_OVER_RESULT				(const char* pszWho, const char* pszLocker, int iResult);
	void S_PG_LDtoDA_BREAK_AT						(const char* pszWho, const char* pszFileName, int iLine);
	void S_PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE			(const char* pszWho);
	void S_PG_LDtoDA_LOCAL_VALUE					(const char* pszWho, ST_LD_VALUE* pVal);
	void S_PG_LDtoDA_END_SEND_LOCAL_VALUE			(const char* pszWho);
	void S_PG_LDtoDA_BEGIN_SEND_UP_VALUE			(const char* pszWho);
	void S_PG_LDtoDA_UP_VALUE						(const char* pszWho, ST_LD_VALUE* pVal);
	void S_PG_LDtoDA_END_SEND_UP_VALUE				(const char* pszWho);
	void S_PG_LDtoDA_GLOBAL_VALUE					(const char* pszWho, ST_LD_VALUE* pVal);
	void S_PG_LDtoDA_BEGIN_SEND_LUA_FILE			(const char* pszWho);
	void S_PG_LDtoDA_END_SEND_LUA_FILE				(const char* pszWho);
	void S_PG_LDtoDA_BEGIN_RELOAD_PLOT				(const char* pszWho);
	void S_PG_LDtoDA_END_RELOAD_PLOT				(const char* pszWho);
	void S_PG_LDtoDA_BEGIN_SEND_CALL_STACK			(const char* pszWho);
	void S_PG_LDtoDA_CALL_STACK						(const char* pszWho, ST_LD_STACK_INFO* pInfo);
	void S_PG_LDtoDA_END_SEND_CALL_STACK			(const char* pszWho);

protected:
	void On_PG_DAtoLD_LOCK							(const char* pszWho);
	void On_PG_DAtoLD_UNLOCK						(const char* pszWho);
	void On_PG_DAtoLD_ADD_BP						(const char* pszWho, const char* pszFileName, int iLine);
	void On_PG_DAtoLD_REMOVE_BP						(const char* pszWho, const char* pszFileName, int iLine);
	void On_PG_DAtoLD_ENABLE_BP						(const char* pszWho, const char* pszFileName, int iLine);
	void On_PG_DAtoLD_DISABLE_BP					(const char* pszWho, const char* pszFileName, int iLine);
	void On_PG_DAtoLD_SET_BP_FILTER_GUID			(const char* pszWho, const char* pszFileName, int iLine, int iGUID);
	void On_PG_DAtoLD_SET_BP_FILTER_ORGOBJID		(const char* pszWho, const char* pszFileName, int iLine, int iOrgObjID);
	void On_PG_DAtoLD_START							(const char* pszWho);
	void On_PG_DAtoLD_STOP							(const char* pszWho);
	void On_PG_DAtoLD_RUN							(const char* pszWho);
	void On_PG_DAtoLD_SETP_INTO						(const char* pszWho);
	void On_PG_DAtoLD_SETP_OVER						(const char* pszWho);
	void On_PG_DAtoLD_GET_GLOBAL_VALUE				(const char* pszWho, const char* pszValName);
	void On_PG_DAtoLD_REQUEST_LUA_FILE				(unsigned long dwNetID, const char* pszWho, const char* pszLuaPath);
	void On_PG_LD_DC_FILE_TRANSFER					(unsigned long dwNetID, unsigned long dwSize, void* PG);

protected:
	void _PG_DAtoLD_LOCK							(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_UNLOCK							(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_ADD_BP							(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_REMOVE_BP						(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_ENABLE_BP						(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_DISABLE_BP						(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_SET_BP_FILTER_GUID				(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_SET_BP_FILTER_ORGOBJID			(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_START_DEBUGGING					(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_STOP_DEBUGGING					(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_RUN								(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_SETP_INTO						(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_SETP_OVER						(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_GET_GLOBAL_VALUE				(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_DAtoLD_REQUEST_LUA_FILE				(unsigned long dwNetID, unsigned long dwSize, void* PG);
	void _PG_LD_DC_FILE_TRANSFER					(unsigned long dwNetID, unsigned long dwSize, void* PG);

public:
	// CEventObj implementation
	virtual bool		OnRecv			(unsigned long dwNetID, unsigned long dwPackSize, void* PG);
	virtual void		OnConnectFailed	(unsigned long dwNetID, unsigned long dwFailedCode);
	virtual void		OnConnect		(unsigned long dwNetID);
	virtual void		OnDisconnect	(unsigned long dwNetID);
	virtual CEventObj*	OnAccept		(unsigned long dwNetID);

public:
	int		GetState()				{return m_State;}
	void	SetState(int value);

public:
	__declspec(property(get = GetState	,put = SetState	))	int	State;

};

// ************************************************************************************************************************************************************
class LuaDebuggerFile
{
protected:
	std::string	m_Name;
	std::map<int, ST_LD_BREAK_POINT> m_BreakPoints; //Line - ST_LD_BREAK_POINT mapping

public:
	LuaDebuggerFile(const char* pszName);
	virtual ~LuaDebuggerFile();

protected:
	ST_LD_BREAK_POINT*	GetBreakPoint(int iLine);

public:
	void AddBreakPoint(int iLine);
	void RemoveBreakPoint(int iLine);	
	void EnableBreakPoint(int iLine);
	void DisableBreakPoint(int iLine);
	void SetGUID(int iLine, int iGUID);
	void SetOrgObjID(int iLine, int iOrgObjID);
	bool IsBreakPoint(int iLine, int iGUID, int iOrgObjID);
};
// ************************************************************************************************************************************************************
class LuaDebuggerFileTransfer : public NetBridgeFileTransferManager
{
public:
	LuaDebuggerFileTransfer(CNetBridge* pNetBridge, int iPGBaseID);

protected:
	virtual int GetHeaderSize();
	virtual void Send(unsigned long dwNetID, unsigned long dwSize, void* PG);
};
// ************************************************************************************************************************************************************
#pragma managed(pop)

#endif