#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include "ControllerClient.h"
#include "DebugLog/errormessage.h"
#include "SmallObj/SmallObj.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

//*************************************************************************************************************
#define new NEW

#define HOST_CONTROLLER_PORT		36580
#define HOST_TIME_OUT_GAP			30000
#define HOST_RECONNECT_TIME_GAP		60000
#define HOST_CONNECT_TRY_THRESHOLD	6
#define MAX_MSG_QUEUE_SIZE			500
#define INVALID_NET_ID				0xFFFFFFFF

//*************************************************************************************************************
CNetBridge*						ControllerClient::m_netBridge				= NULL;
ControllerClientEvent*			ControllerClient::m_netEvent				= NULL;
void*							ControllerClient::m_outputBuf				= NULL;
unsigned long					ControllerClient::m_outputBufSize			= 0;
deque<string>					ControllerClient::m_outputQueue;
deque<string>					ControllerClient::m_cmdQueue;
int								ControllerClient::m_Type					= EM_GAME_SERVER_TYPE_NONE;
string							ControllerClient::m_srvRegion				= "";
string							ControllerClient::m_srvGroup				= "";
string							ControllerClient::m_srvName					= "";
string							ControllerClient::m_iniFile					= "";
string							ControllerClient::m_hostName				= "localhost";
unsigned int					ControllerClient::m_port					= HOST_CONTROLLER_PORT;
unsigned long					ControllerClient::m_lastProcessTick			= 0;
unsigned long					ControllerClient::m_lastConnectRetryTick	= 0;
int								ControllerClient::m_ConnectRetryCount		= 0;
bool							ControllerClient::m_started					= false;
bool							ControllerClient::m_connecting				= false;
bool							ControllerClient::m_connected				= false;
unsigned long					ControllerClient::m_netID					= INVALID_NET_ID;
vector<PFUNC_CTRL_PG_CALLBACK>	ControllerClient::m_PGCallBack;
bool							ControllerClient::m_ServerReady				= false;

//*************************************************************************************************************
//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
inline MutilThread_CritSect*  g_CritSect_CmdQueue( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect_CmdQueue;

	return &g_Thread_CritSect_CmdQueue;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
inline MutilThread_CritSect*  g_CritSect_OutputQueue( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect_OutputQueue; 

	return &g_Thread_CritSect_OutputQueue;
}


//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void PrintToController(bool showdlg, const char* format,... )
{
	char Buff[4096];

	SecureZeroMemory(Buff, sizeof(Buff));
	va_list Marker =(char*)&format + sizeof(format);
	vsprintf_s( Buff, sizeof(Buff), format , Marker );

	if (showdlg)
	{
		if (IsWindowVisible(GetConsoleWindow()))
		{
			MessageBox( NULL , Buff , "Error" ,MB_OK );
		}
		else
		{
			printf(Buff);

			string tmp = Buff;

			SecureZeroMemory(Buff, sizeof(Buff));

			sprintf_s(Buff, sizeof(Buff), "Server Error {FE58BC7B-ECE9-4d9a-85D0-ED6433ACAF6D},%s", tmp.c_str());

			ControllerClient::QueueOutput(Buff);
		}
	}
	else
	{
		try
		{
			printf(Buff);

			ControllerClient::QueueOutput(Buff);
		}
		catch(...)
		{
			printf( "\n_Printf Crash");
		}

	}
}

//*************************************************************************************************************
//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
bool ControllerClient::Init(const char* pszSrvName, const char* pszIniFile, int iSrvType)
{
	m_srvName = pszSrvName;
	m_iniFile = pszIniFile;
	m_Type    = iSrvType;

	//設定Controller Client 輸出函式
	if (g_pPrint)
		g_pPrint->SetControllerOutputFunc(&ControllerClient::Print);

	m_netBridge = CreateNetBridge( false, 1 );
	m_netEvent = new ControllerClientEvent;

	RegisterPGCallback(EM_PG_CtoS_CONNECTED			, OnPG_CONNECTED	);
	RegisterPGCallback(EM_PG_CtoS_NOTIFICATION		, OnPG_NOTIFICATION	);
	RegisterPGCallback(EM_PG_CtoS_COMMAND_TO_SERVER	, OnPG_COMMAND		);

	return true;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
bool ControllerClient::Start()
{
	m_started = true;

	return true;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
bool ControllerClient::Stop()
{
	if (m_outputBuf)
	{
		delete m_outputBuf;
		m_outputBuf = NULL;
		m_outputBufSize = 0;
	}

	m_netBridge->Close(m_netID);

	delete m_netEvent;
	m_netEvent = NULL;

	DeleteNetBridge( m_netBridge );
	m_netBridge = NULL;

	m_started = false;

	return true;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnPG_CONNECTED(unsigned long dwNetID , unsigned long dwSize, void* PG)
{
	PG_StoC_REGISTRATION RegSend;
	RegSend.PID = GetCurrentProcessId();
	strncpy_s(RegSend.RegionName , sizeof(RegSend.RegionName) , m_srvRegion.c_str() , m_srvRegion.length());
	strncpy_s(RegSend.GroupName  , sizeof(RegSend.GroupName)  , m_srvGroup.c_str()  , m_srvGroup.length());
	strncpy_s(RegSend.ServerName , sizeof(RegSend.ServerName) , m_srvName.c_str()   , m_srvName.length());
	strncpy_s(RegSend.CmdLine	 , sizeof(RegSend.CmdLine)	  , m_iniFile.c_str()   , m_iniFile.length());

	SendToController(dwNetID, sizeof(RegSend), &RegSend);

	PG_StoC_SERVER_TYPE TypeSend;
	TypeSend.Type = m_Type;

	SendToController(dwNetID, sizeof(TypeSend), &TypeSend);

	SendServerReady();
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnPG_NOTIFICATION(unsigned long dwNetID , unsigned long dwSize, void* PG)
{
	PG_CtoS_NOTIFICATION* pNotify = reinterpret_cast<PG_CtoS_NOTIFICATION *>(PG);

	m_srvRegion = pNotify->RegionName;
	m_srvGroup  = pNotify->GroupName;
	m_srvName   = pNotify->ServerName;

	PG_StoC_NOTIFICATION_OK OK;
	ControllerClient::SendToController(dwNetID, sizeof(OK), &OK);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnPG_COMMAND(unsigned long dwNetID , unsigned long dwSize, void* PG)
{
	PG_CtoS_COMMAND_TO_SERVER* pCmd = reinterpret_cast<PG_CtoS_COMMAND_TO_SERVER *>(PG);
	QueueCmd(pCmd->Cmd);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::RegisterPGCallback(int iPGNum, PFUNC_CTRL_PG_CALLBACK pCallBack)
{
	if (iPGNum >= (int)m_PGCallBack.size())
	{
		int iDiff = (iPGNum - (int)m_PGCallBack.size()) + 1;

		for (int i = 0; i < iDiff; ++i)
		{
			m_PGCallBack.push_back(NULL);
		}
	}

	m_PGCallBack[iPGNum] = pCallBack;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::SendToController(unsigned long dwNetID , unsigned long dwSize , void* pData )
{
	if (m_netBridge)
	{
		m_netBridge->Send(dwNetID, dwSize, pData);
	}
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::QueueOutput(const char* pszStr)
{
	if(strstr(pszStr, "{6EC9D721-D946-4906-AB79-5AF7B35241CB}") != NULL)
	{
		m_ServerReady = true;			
	}

	if (m_outputQueue.size() >= MAX_MSG_QUEUE_SIZE)
	{
		g_CritSect_OutputQueue()->Enter();
		m_outputQueue.pop_front();
		g_CritSect_OutputQueue()->Leave();
	}

	g_CritSect_OutputQueue()->Enter();
	m_outputQueue.push_back(pszStr);
	g_CritSect_OutputQueue()->Leave();
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::QueueCmd(const char* pszCmd)
{
	g_CritSect_CmdQueue()->Enter();
	m_cmdQueue.push_back(pszCmd);
	g_CritSect_CmdQueue()->Leave();
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
bool ControllerClient::GetCmd(string& cmd)
{
	bool Result = false;

	g_CritSect_CmdQueue()->Enter();

	if (!m_cmdQueue.empty())
	{
		cmd = "";
		cmd = m_cmdQueue.front();
		m_cmdQueue.pop_front();
		Result = true;
	}

	g_CritSect_CmdQueue()->Leave();

	return Result;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::Connect()
{
	if(!m_connecting && !m_connected)
	{
		if(GetTickCount() - m_lastConnectRetryTick > HOST_RECONNECT_TIME_GAP)
		{
			unsigned long ip = ConvertIP(m_hostName.c_str());
			m_netBridge->Connect(ip, m_port, m_netEvent);

			m_connecting = true;

			m_lastConnectRetryTick = GetTickCount();
			m_ConnectRetryCount++;
		}
	}
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::Output(const char* pszStr)
{
	unsigned long dwSize = sizeof(PG_StoC_CONSOLE_OUTPUT) + strlen(pszStr);

	//we need a larger buffer
	if (dwSize > m_outputBufSize)
	{
		if (m_outputBuf)
		{
			delete m_outputBuf;
			m_outputBuf = NULL;
		}

		m_outputBufSize = ((dwSize / 4) + 1) * 4 + 32;

		m_outputBuf = new BYTE[m_outputBufSize];
	}

	SecureZeroMemory(m_outputBuf, m_outputBufSize);

	PG_StoC_CONSOLE_OUTPUT *pPacket = reinterpret_cast<PG_StoC_CONSOLE_OUTPUT *>(m_outputBuf);
	pPacket->PGID = EM_PG_StoC_CONSOLE_OUTPUT;
	pPacket->Len  = (int)strlen(pszStr);
	strcpy(pPacket->Output, pszStr);

	SendToController(m_netID, dwSize, m_outputBuf);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::ProcessOutput()
{
	if (m_connected)
	{
		deque<string> tmpQueue;
		tmpQueue.clear();

		g_CritSect_OutputQueue()->Enter();

		tmpQueue = m_outputQueue;
		m_outputQueue.clear();

		g_CritSect_OutputQueue()->Leave();

		while(!tmpQueue.empty())
		{
			Output(tmpQueue[0].c_str());			
			tmpQueue.pop_front();			
		}
	}
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::Print( int iLV , const char* pszTitle , const char* pszContext )
{
	char Buff[4096];

	SecureZeroMemory(Buff, sizeof(Buff));
	sprintf_s( Buff, sizeof(Buff), "(%d)%s\t%s\t%s", iLV , TimeStr::Now_Time() , pszTitle, pszContext);
	ControllerClient::QueueOutput(Buff);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::SendServerReady()
{
	if (m_ServerReady)
	{
		PG_StoC_SERVER_READY Send;
		SendToController(m_netID, sizeof(Send), &Send);
	}
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::Process()
{
	//try to connect to controller if not connected
	Connect();

	if (m_connected)
	{
		ProcessOutput();
	}

	if (m_netBridge)
	{
		CNetBridge::WaitAll( 0 );
	}

}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
bool ControllerClient::OnRecv(unsigned long dwNetID , unsigned long dwSize , void* PG)
{
	bool Result = false;

	if (PG)
	{
		PG_CONTROLLER_BASE *pPkt = reinterpret_cast<PG_CONTROLLER_BASE *>(PG);

		if (pPkt->PGID < (int)m_PGCallBack.size())
		{
			PFUNC_CTRL_PG_CALLBACK pFunc = m_PGCallBack[pPkt->PGID];

			if (pFunc)
			{
				pFunc(dwNetID, dwSize, PG);
				Result = true;
			}
		}
	}

	return Result;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnConnected(unsigned long dwNetID)
{
	m_connecting = false;
	m_connected = true;
	m_netID = dwNetID;

	m_ConnectRetryCount = 0;

	SendServerReady();
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnDisconnected()
{
	m_connecting = false;
	m_connected = false;
	m_netID = INVALID_NET_ID;
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClient::OnConnectFailed()
{
	m_connecting = false;
	m_connected = false;
	m_netID = INVALID_NET_ID;
}

//*************************************************************************************************************

//-----------------------------------------------------------------------------------------------
// CEventObj implementation
//-----------------------------------------------------------------------------------------------
bool ControllerClientEvent::OnRecv(unsigned long dwNetID, unsigned long dwSize, void* PG)
{
	return ControllerClient::OnRecv(dwNetID, dwSize, PG);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClientEvent::OnConnectFailed( unsigned long dwNetID, unsigned long dwFailedCode)
{
	ControllerClient::OnConnectFailed();

	Print(LV2, "ControllerClientEvent::OnConnectFailed", "Code=%d",dwFailedCode);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClientEvent::OnConnect(unsigned long dwNetID)
{
	ControllerClient::OnConnected(dwNetID);
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void ControllerClientEvent::OnDisconnect( unsigned long dwNetID)
{
	ControllerClient::OnDisconnected();
}

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
CEventObj* ControllerClientEvent::OnAccept( unsigned long dwNetID)
{
	return this;
}


//*************************************************************************************************************
