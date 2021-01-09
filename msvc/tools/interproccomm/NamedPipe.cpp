#include <windows.h>
#include "NamedPipe.h"
#include "assert.h"
#include <tchar.h>
#include <stdio.h>

CIPCCritiaclSection::CIPCCritiaclSection()
{
	InitializeCriticalSection( &m_cs );
}

CIPCCritiaclSection::~CIPCCritiaclSection()
{
	DeleteCriticalSection( &m_cs );
}

void CIPCCritiaclSection::Lock()
{
	EnterCriticalSection( &m_cs );
}

void CIPCCritiaclSection::UnLock()
{
	LeaveCriticalSection( &m_cs );
}


CNamedPipeEx::CNamedPipeEx(void):
m_pOverlapped(NULL)
{
	m_pMsgoutCallBack = NULL;
	m_hPipe = INVALID_HANDLE_VALUE;

	memset( m_handleArray, 0, sizeof( m_handleArray ));
	m_hStopEvent = NULL;

}

CNamedPipeEx::~CNamedPipeEx(void)
{
	Close();
	//CloseHandle( m_hPipe );
}

// Create The Pipe(Server)
BOOL CNamedPipeEx::Create( LPCSTR lpszName , DWORD dwOpenMode , 
						DWORD dwPipeMode , DWORD dwMaxInstances , 
						DWORD dwOutBufferSize , DWORD dwInBufferSize , 
						DWORD dwDefaultTimeOut , LPSECURITY_ATTRIBUTES lpSecurityAttribute )
{
	char pszPipeName[ MAX_PATH ];
	strcpy_s( pszPipeName ,MAX_PATH , "\\\\.\\PIPE\\" );		// 必須命名格式 "." 可設為區網電腦名稱
	strcat( pszPipeName , lpszName );

	m_hPipe = ::CreateNamedPipeA( pszPipeName , dwOpenMode , dwPipeMode , 
								dwMaxInstances , dwOutBufferSize ,dwInBufferSize , dwDefaultTimeOut ,lpSecurityAttribute );

	if( dwOpenMode & FILE_FLAG_OVERLAPPED )
	{
		m_pOverlapped = new OVERLAPPED;
		memset( m_pOverlapped, 0, sizeof(OVERLAPPED) );
		m_handleArray[0] =  m_pOverlapped->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		m_handleArray[1] =  m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	if( m_hPipe == INVALID_HANDLE_VALUE )
	{
		MsgOut( _T("Create Pipe Failed : GetLastError %d") ,GetLastError() );
	}

	return ( m_hPipe != INVALID_HANDLE_VALUE );
}

// Open Pipe( Client)
BOOL CNamedPipeEx::Open( LPCSTR lpszServerName , LPCSTR lpszPipeName , 
					  DWORD dwDesiredAccess , DWORD dwSharedMode , 
					  LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
					  DWORD dwFlagsAndAttributes )
{
	char pszPipeName[ MAX_PATH ];
	sprintf_s( pszPipeName , MAX_PATH ,"\\\\%s\\PIPE\\%s" , lpszServerName , lpszPipeName );		// 必須命名格式  "."可設為區網電腦名稱

	m_clientPipeInfo.strPipePath = pszPipeName;
	m_clientPipeInfo.dwSharedMode = dwSharedMode;
	m_clientPipeInfo.dwFlagsAndAttributes = dwFlagsAndAttributes;
	m_clientPipeInfo.lpSecurityAttributes = lpSecurityAttributes;
	m_clientPipeInfo.dwDesiredAccess = dwDesiredAccess;

	BOOL bRet = _Open( m_clientPipeInfo );
	return bRet;
}

BOOL CNamedPipeEx::ReOpen()
{
	BOOL bRet = _Open( m_clientPipeInfo );
	return bRet;
}

BOOL CNamedPipeEx::_Open( TNamedPipeInfo info )
{
	Close();

	m_hPipe = CreateFileA( info.strPipePath.c_str(), info.dwDesiredAccess, info.dwSharedMode, info.lpSecurityAttributes, OPEN_EXISTING, info.dwFlagsAndAttributes, NULL );

	if( m_hPipe == INVALID_HANDLE_VALUE )
		MsgOut(_T( "CNamedPipeEx::Open Failed , GetLastError Return %d" ) , GetLastError() );

	return ( m_hPipe != INVALID_HANDLE_VALUE );
}


BOOL CNamedPipeEx::Close()
{
	BOOL bSuccess = TRUE;
	if( IsOpen() )
	{
		// 應該要先釋放 ConnectClient, 在關閉 Pipe
		UnLock();

		bSuccess = CloseHandle( m_hPipe );
		if( !bSuccess )
			MsgOut( _T( "CNamedPipeEx::Close() failed")  );
		else
			m_hPipe = INVALID_HANDLE_VALUE;

		delete m_pOverlapped;
		m_pOverlapped = NULL;
	}

	return bSuccess;
}

BOOL CNamedPipeEx::IsOpen()
{
	return m_hPipe != INVALID_HANDLE_VALUE;
}

BOOL CNamedPipeEx::IsClientPipe( BOOL &bClientPipe )
{
	assert( m_hPipe != NULL );

	DWORD dwFlags;
	BOOL bSuccess = ::GetNamedPipeInfo( m_hPipe , &dwFlags , NULL , NULL , NULL );

	if( !bSuccess )
		MsgOut(  _T("CNamedPipeEx::IsClientPipe() Failed , GetLastError return %d ") , GetLastError() );
	else
		bClientPipe = ( (dwFlags & PIPE_CLIENT_END ) != 0 );

	return bSuccess;
}

BOOL CNamedPipeEx::IsServerPipe( BOOL &bServerPipe )
{
	assert( m_hPipe != NULL );
	
	DWORD dwFlags;
	BOOL bSuccess = ::GetNamedPipeInfo( m_hPipe , &dwFlags , NULL , NULL , NULL );

	if( !bSuccess )
		MsgOut(  _T("CNamedPipeEx::IsServerPipe() Failed , GetLastError return %d ") , GetLastError() );
	else
		bServerPipe = ( (dwFlags & PIPE_SERVER_END ) != 0 );

	return bSuccess;
}

BOOL CNamedPipeEx::IsMessagePipe( BOOL &bMessagePipe )
{
	assert(m_hPipe != NULL); //Pipe must be open

	DWORD dwState;
	BOOL bSuccess = ::GetNamedPipeHandleState(m_hPipe, &dwState, NULL, NULL, NULL, NULL, 0);

	if (!bSuccess)
		MsgOut(  _T("CNamedPipeEx::IsMessagePipe() Failed, GetLastError returned %d\n"), ::GetLastError());
	else
		bMessagePipe = ((dwState & PIPE_READMODE_MESSAGE) != 0);

	return bSuccess;
}

DWORD CNamedPipeEx::GetOutBoundBufferSize()
{
	assert( m_hPipe != NULL );
	DWORD dwOutBufferSize = 0;
	BOOL bSuccess = ::GetNamedPipeInfo( m_hPipe , NULL , &dwOutBufferSize , NULL , NULL );
	
	if( !bSuccess )
		MsgOut(  _T("CNamedPipeEx::GetOutBoundBufferSize faild , GetLastError return %d") , GetLastError() );

	return dwOutBufferSize;
}

DWORD CNamedPipeEx::GetInBoundBufferSize()
{
	assert( m_hPipe != NULL );
	DWORD dwInBufferSuze = 0;
	BOOL bSuccess = ::GetNamedPipeInfo( m_hPipe , NULL , &dwInBufferSuze , NULL , NULL );

	if( !bSuccess )
		MsgOut( _T("CNamedPipeEx::GetInBoundBufferSize faild , GetLastError return %d") , GetLastError() );

	return dwInBufferSuze;
}

BOOL CNamedPipeEx::GetClientUserName( TCHAR* lpszUserName )
{
	BOOL bSuccess = ::GetNamedPipeHandleState( m_hPipe , NULL , NULL , NULL , NULL , lpszUserName , _MAX_PATH );

	if( !bSuccess )
		MsgOut(_T("CNamedPipeEx::GetClientUserName faild , GetLastError return %d ") , GetLastError() );

	return bSuccess;
}

//BOOL CNamedPipeEx::ServerAvailable( LPCTSTR lpszServerName , LPCTSTR lpszPipeName , DWORD dwTimeOut )
//{
//	TCHAR szPipeName[ MAX_PATH ];
//	_stprintf_s( szPipeName , MAX_PATH , _T("\\\\%s\\PIPE\\%s") , lpszServerName , lpszPipeName );
//	
//	BOOL bSuccess = ::WaitNamedPipe( szPipeName , dwTimeOut );
//
//	if( !bSuccess )
//		MsgOut( _T("NamedPipe::ServerAvailable failed , GetLastError  return %d"),GetLastError() );
//
//	return bSuccess;
//}

BOOL CNamedPipeEx::ServerAvailable( LPCSTR lpszPipeName , DWORD dwTimeOut )
{
	char szPipeName[ MAX_PATH ];
	sprintf_s( szPipeName , MAX_PATH , "\\\\.\\PIPE\\%s"  , lpszPipeName );

	BOOL bSuccess = ::WaitNamedPipeA( szPipeName , dwTimeOut );

	//if( !bSuccess )
	//	MsgOut( _T("NamedPipe::ServerAvailable failed , GetLastError  return %d"),GetLastError() );

	return bSuccess;
}


BOOL CNamedPipeEx::Peek(LPVOID lpBuffer, DWORD dwBufferSize, DWORD& dwBytesRead, 
					  DWORD& dwTotalBytesAvail, DWORD& dwBytesLeftThisMessage)
{
	assert( m_hPipe != NULL );
	BOOL bSuccess = ::PeekNamedPipe( m_hPipe , lpBuffer , dwBufferSize , 
									&dwBytesRead , &dwTotalBytesAvail , 
									&dwBytesLeftThisMessage );

	if( !bSuccess )
		MsgOut( _T("CNamedPipeEx::Peek faild , GetLastError :%d "), GetLastError() );

	return bSuccess;
}

BOOL CNamedPipeEx::Read( LPVOID lpBuffer , DWORD dwReadBytes , 
					  DWORD &dwNumberOfBytesRead , LPOVERLAPPED lpOverlapped )
{
	assert( m_hPipe != NULL );
	BOOL bSuccess = ::ReadFile( m_hPipe , lpBuffer , dwReadBytes , 
								&dwNumberOfBytesRead, lpOverlapped );

	if( !bSuccess )
		MsgOut( _T("CNamedPipeEx::Read Faild , GetLastError return %d"),GetLastError() );

	MsgOut( _T("[ MSG ] Pipe Read MaxSize: %d Byte ,Real Read %d Byte"), dwReadBytes, dwNumberOfBytesRead);

	return bSuccess;
}

BOOL CNamedPipeEx::Write(LPCVOID lpBuffer, DWORD dwWriteBytes, 
					   DWORD &dwNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	assert(m_hPipe != NULL); //Pipe must be open

	//char szBuffer[ 1024 ];
	//DWORD dwBytesRead, dwTotalBytesAvail, dwBytesLeftThisMessage;
	//if( Peek( szBuffer, 8192, dwBytesRead ,dwTotalBytesAvail, dwBytesLeftThisMessage ) == false )// Peek 是否有收到訊息
	//{
	//	return FALSE;
	//}

	//if( dwTotalBytesAvail + dwWriteBytes > GetInBoundBufferSize() )
	//{
	//	return FALSE;
	//}

	BOOL bSuccess = ::WriteFile(m_hPipe, lpBuffer, dwWriteBytes, 
		&dwNumberOfBytesWritten, lpOverlapped);

	if (!bSuccess)
		MsgOut( _T("CNamedPipeEx::Write() Failed, GetLastError returned %d\n"), ::GetLastError());

	MsgOut( _T("[ MSG ] Pipe Write Size: %d Byte ,Real Write %d Byte"), dwWriteBytes, dwNumberOfBytesWritten);

	return (bSuccess && dwNumberOfBytesWritten == dwWriteBytes);
}


void CNamedPipeEx::MsgOut( TCHAR* szFormat , ... )
{
	CIPICSHelper csHelper( &m_MsgCs );

	TCHAR szPrintf[ 1024 ];
	va_list args;
	va_start( args , szFormat );
	_vstprintf_s( szPrintf , 1024 , szFormat , args );
	va_end( args );

	if( m_pMsgoutCallBack )
		m_pMsgoutCallBack( szPrintf );

	//OutputDebugString( szPrintf );
	//OutputDebugString( _T("\n") );
}


BOOL CNamedPipeEx::ConnectClient()
{
	assert( m_hPipe != NULL );

 #ifdef _DEBUG
 	BOOL bServerPipe;
 	assert(IsServerPipe( bServerPipe));
 	assert(bServerPipe);     //Must be called from the server side
 #endif

	if( m_hPipe == INVALID_HANDLE_VALUE )
		return FALSE;

	BOOL bSuccess = ConnectNamedPipe( m_hPipe , m_pOverlapped );

	if( !bSuccess )
	{
		MsgOut( _T("CNamedPipeEx::ConnectClient() faild , GetLastError return %d "),GetLastError() );
	}

	// 如果 m_pOverlapped 有實體, 就代表是使用 Overlapped 模式, 就要執行 Overlapped 相關處理
	if( m_pOverlapped )
	{

		// 等待事件 要不就是 Connect 成功, 要不就是手動關閉
		switch (WaitForMultipleObjects( 2, m_handleArray, FALSE, INFINITE ))
		{

		case WAIT_OBJECT_0:
			{
				DWORD dwLastErr = GetLastError();

				switch ( dwLastErr ) { 

				// The overlapped connection in progress. 
				case ERROR_IO_PENDING: 
					bSuccess = true;
					ResetEvent(m_handleArray[0]);
					break; 

				// Client is already connected, so signal an event. 
				case ERROR_PIPE_CONNECTED: 
					bSuccess = false;
					break; 

				// If an error occurs during the connect operation... 
				default: 
					bSuccess = false;
					break;

				}
				break;
			}

		case WAIT_OBJECT_0 + 1:
			return false;
		}
	}



	return bSuccess;
}

BOOL CNamedPipeEx::DisConnectClient()
{
	assert( m_hPipe != NULL );

	BOOL bSuccess = ::DisconnectNamedPipe( m_hPipe );

	if( !bSuccess )
	{
		MsgOut( _T("CNamedPipeEx::DisConnectClient() failed , GetLastError return %d"), GetLastError() );
	}
	return bSuccess;
}

BOOL CNamedPipeEx::IsConnected()
{
	byte testBuf[1];

	DWORD dwBytesRead;
	DWORD dwTotalBytesAvail;
	DWORD dwBytesLeftThisMessage;

	assert( m_hPipe != NULL );

	BOOL bSuccess = ::PeekNamedPipe( m_hPipe , testBuf , 1 , 
		&dwBytesRead , &dwTotalBytesAvail , 
		&dwBytesLeftThisMessage );

	if( !bSuccess )
	{		
		DWORD dwError = GetLastError();

		switch( dwError )
		{
			case ERROR_BROKEN_PIPE:
			case ERROR_PIPE_NOT_CONNECTED:
			case ERROR_INVALID_HANDLE:
			case ERROR_BAD_PIPE:
				return false;
		}
	}
	return true;
}

void CNamedPipeEx::UnLock()
{
	// 應該要先釋放 ConnectClient, 在關閉 Pipe
	SetEvent(m_hStopEvent);
}