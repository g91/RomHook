#pragma once

#ifndef _NANED_PIPE_H
#define _NANED_PIPE_H

#include <Windows.h>
#include <string>
typedef void (*PFUNC_MSG_OUTPUT_CALLBACK)( TCHAR* szPrintf );


class CIPCCritiaclSection
{

protected:

	CRITICAL_SECTION m_cs;

public:
	CIPCCritiaclSection();
	~CIPCCritiaclSection();

	void Lock();
	void UnLock();

};

class CIPICSHelper
{

protected:
	CIPCCritiaclSection* m_pCs;

public:

	CIPICSHelper( CIPCCritiaclSection* pCs )
	{
		m_pCs = pCs;
		m_pCs->Lock();
	}

	~CIPICSHelper()
	{
		m_pCs->UnLock();
	}

};

struct TNamedPipeInfo
{
	TNamedPipeInfo()
	{
		//memset( this, 0, sizeof( *this ) );
	}
	
	std::string strPipePath;
	DWORD dwDesiredAccess;
	DWORD dwSharedMode;
	LPSECURITY_ATTRIBUTES lpSecurityAttributes;
	DWORD dwFlagsAndAttributes;
};


class CNamedPipeEx
{

protected:
	
	HANDLE m_hPipe;
	PFUNC_MSG_OUTPUT_CALLBACK m_pMsgoutCallBack;

	TNamedPipeInfo m_clientPipeInfo;

	CIPCCritiaclSection m_MsgCs;

	OVERLAPPED*	m_pOverlapped;

	HANDLE      m_handleArray[2];
	HANDLE		m_hStopEvent;
	

protected:

	BOOL	IsClientPipe( BOOL &bClientPipe );
	
	BOOL	IsMessagePipe( BOOL &bMessagePipe );
	DWORD	GetOutBoundBufferSize();
	DWORD	GetInBoundBufferSize();

	BOOL	GetClientUserName( TCHAR* lpszUserName );

	BOOL	_Open( TNamedPipeInfo info );

public:
	CNamedPipeEx(void);
	~CNamedPipeEx(void);

	BOOL IsOpen();

	BOOL Write(LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite, 
		DWORD &dwNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

	BOOL Read( LPVOID lpBuffer , DWORD dwNumberOfBytesToRead , 
		DWORD &dwNumberOfBytesRead , LPOVERLAPPED lpOverlapped );

	BOOL Peek(LPVOID lpBuffer, DWORD dwBufferSize, DWORD& dwBytesRead, 
		DWORD& dwTotalBytesAvail, DWORD& dwBytesLeftThisMessage);

	// Create The Pipe(Server)
	BOOL Create( LPCSTR lpszName , DWORD dwOpenMode , 
		DWORD dwPipeMode , DWORD dwMaxInstances , 
		DWORD dwOutBufferSize , DWORD dwInBufferSize , 
		DWORD dwDefaultTimeOut , LPSECURITY_ATTRIBUTES lpSecurityAttribute );

	// Open Pipe( Client)
	BOOL Open( LPCSTR lpszServerName , LPCSTR lpszPipeName , 
		DWORD dwDesiredAccess , DWORD dwSharedMode , 
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
		DWORD dwFlagsAndAttributes );

	void	SetMsgOutCallBack( PFUNC_MSG_OUTPUT_CALLBACK pFunc ){ m_pMsgoutCallBack = pFunc; };

	void	MsgOut( TCHAR* szFormat , ... );

	BOOL	Close();

	// 重新開啟
	BOOL	ReOpen();

	BOOL	ConnectClient();
	BOOL	DisConnectClient();

	BOOL	IsServerPipe( BOOL &bServerPipe );
	BOOL	IsConnected();	

	// 將LOCK住的函式釋放掉( 如 ConnectClient
	void	UnLock();

	static BOOL	ServerAvailable( LPCSTR lpszPipeName , DWORD dwTimeOut );

};


#endif