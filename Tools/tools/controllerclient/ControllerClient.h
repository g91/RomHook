#pragma once

#ifndef	__CONTROLLER_CLIENT_H__
#define __CONTROLLER_CLIENT_H__

#include "NetBridge/NetBridge.h"
#include "PG_Controller.h"
#include <string>
#include <deque>

using namespace std;

// ************************************************************************************************************************************************************
typedef void  (*PFUNC_CTRL_PG_CALLBACK) (unsigned long dwNetID , unsigned long dwSize, void* PG);

// ************************************************************************************************************************************************************
class ControllerClient;
class ControllerClientEvent;

// ************************************************************************************************************************************************************
class ControllerClient
{
protected:
	static CNetBridge*					  m_netBridge;
	static ControllerClientEvent*   	  m_netEvent;
	static void*                    	  m_outputBuf;
	static unsigned long           		  m_outputBufSize;
	static deque<string>           		  m_outputQueue;
	static deque<string>            	  m_cmdQueue;
	static unsigned long				  m_lastProcessTick;
	static unsigned long				  m_lastConnectRetryTick;
	static string						  m_srvRegion;
	static string						  m_srvGroup;
	static string						  m_srvName;
	static string						  m_iniFile;
	static string						  m_hostName;
	static unsigned int					  m_port;
	static int							  m_ConnectRetryCount;
	static bool							  m_started;
	static bool							  m_connecting;
	static bool							  m_connected;
	static DWORD						  m_netID;
	static int							  m_Type;
	static vector<PFUNC_CTRL_PG_CALLBACK> m_PGCallBack;
	static bool							  m_ServerReady;

protected:
	static void OnPG_CONNECTED(unsigned long dwNetID , unsigned long dwSize, void* PG);
	static void OnPG_NOTIFICATION(unsigned long dwNetID , unsigned long dwSize, void* PG);
	static void OnPG_COMMAND(unsigned long dwNetID , unsigned long dwSize, void* PG);
	
protected:
	static void RegisterPGCallback(int iPGNum, PFUNC_CTRL_PG_CALLBACK pCallBack);
	static void SendToController(unsigned long dwNetID , unsigned long dwSize , void* pData );	
	static void	QueueCmd(const char* pszCmd);
	static void	Connect();
	static void	Output(const char* pszStr);
	static void ProcessOutput();	
	static void	Print( int iLV , const char* pszTitle , const char* pszContext);
	static void SendServerReady();

public:
	static bool	Init(const char* pszSrvName, const char* pszIniFile, int iSrvType);
	static bool	Start();
	static bool	Stop();	
	static void	Process();

public:	
	static void	QueueOutput(const char* pszStr);
	static bool	GetCmd(string& cmd);

public:
	static bool	OnRecv(unsigned long dwNetID , unsigned long dwSize , void* PG);
	static void	OnConnected(unsigned long dwNetID);
	static void	OnDisconnected();
	static void	OnConnectFailed();
};
// ************************************************************************************************************************************************************
class ControllerClientEvent : public CEventObj
{
public:
	ControllerClientEvent(){}
	virtual	~ControllerClientEvent(){}

	// CEventObj implementation
	virtual bool		OnRecv(unsigned long dwNetID, unsigned long dwSize, void* PG);
	virtual void		OnConnectFailed( unsigned long dwNetID, unsigned long dwFailedCode);
	virtual void		OnConnect(unsigned long dwNetID);
	virtual void		OnDisconnect(unsigned long dwNetID);
	virtual CEventObj*	OnAccept(unsigned long dwNetID);

};
// ************************************************************************************************************************************************************
void PrintToController( bool showdlg, const char* format, ... );

// ************************************************************************************************************************************************************

#endif