
#include "InterProcCommClient.h"
#include "NamedPipe.h"

CInterProcCommClient::CInterProcCommClient()
{
	m_uTryConnectTime = 30000; // default is 30s
	
	m_hMainThead = INVALID_HANDLE_VALUE;
	m_bStopProc = false;
}

CInterProcCommClient::~CInterProcCommClient()
{
	Destroy();
}

void CInterProcCommClient::Destroy()
{
	if( m_hMainThead != INVALID_HANDLE_VALUE )
	{
		m_bStopProc = true;

		for( size_t i = 0; i < 5; i++ )
		{
			ActThread();
			WaitForSingleObject( m_hMainThead, 1000 );
		}

		CloseHandle( m_hMainThead );
		m_hMainThead = INVALID_HANDLE_VALUE;
	}

	if( m_pNamedPipe )
	{
		delete m_pNamedPipe;
		m_pNamedPipe = NULL;
	}
}

bool CInterProcCommClient::Init( const char* szPipeName )
{
	Destroy();

	m_iIPCStatus	= EM_IPC_INITIALIZE; 
	m_bStopProc		= false;
	m_strPipeName	= szPipeName;
	return true;
}


void CInterProcCommClient::RunProc( LPARAM lparam )
{
	CInterProcCommClient* pMain = (CInterProcCommClient*)lparam;

	if( pMain )
	{
		while( true )
		{
			if( !pMain->RSThreadProc() )
				break;

			//Sleep( 1 );
		}
	}
}

bool CInterProcCommClient::RSThreadProc()
{
// 	boost::mutex::scoped_lock lk(m_threadCs);
// 	m_waitEvent.wait( lk );

	WaitForSingleObject( m_waitEvent, INFINITE );

	if( m_bStopProc )
		return false;

	if( m_iIPCStatus == EM_IPC_CONNECTED )
	{
		RecvDataProc();
		SendDataProc();			
	}	
	return true;
};


bool CInterProcCommClient::IsPipeExist( const char* pszPipe, int iTimeOut )
{
	CNamedPipeEx m_namedPipe;

	if( m_namedPipe.ServerAvailable( pszPipe, iTimeOut ) == FALSE )
		return false;

// 	if( m_namedPipe.Open( ".", pszPipe, GENERIC_WRITE | GENERIC_READ  , FILE_SHARE_READ , NULL , 0 ) == FALSE )
// 		return false;

	return true;
}

bool CInterProcCommClient::InitPipe()
{
	m_pNamedPipe = new CNamedPipeEx();

	if( m_pNamedPipe->ServerAvailable( m_strPipeName.c_str(), 5000 ) == FALSE )
	{
		MsgOut( EM_LOG_LEVEL_CRITICAL, "Pipe: %s not available\n", m_strPipeName.c_str() );

		delete m_pNamedPipe;
		m_pNamedPipe = NULL;
		return false;
	}

	if( m_pNamedPipe->Open( ".", m_strPipeName.c_str(), GENERIC_WRITE | GENERIC_READ  , FILE_SHARE_READ , NULL , 0 ) == FALSE )
	{
		MsgOut( EM_LOG_LEVEL_CRITICAL, "Open Pipe: %s failed\n", m_strPipeName.c_str() );

		delete m_pNamedPipe;
		m_pNamedPipe = NULL;
		return false;
	}	

	m_bStopProc = false;
	m_hMainThead = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)RunProc, this, NULL, NULL );
	return true;
}


void CInterProcCommClient::Process()
{
	switch( m_iIPCStatus )
	{
		case EM_IPC_INITIALIZE:
		{
			if( InitPipe() )
				ChangeIPCStatus( EM_IPC_CONNECTED );
			break;
		}

		case EM_IPC_CONNECTED:
			{
				// if the client wasnt connected, try to reconnect server
				if( !IsConnected() )
				{
					m_iIPCStatus = EM_IPC_DISCONNECTED;
				}
				else
				{
					Flush();

					if( HaveHandleData() )
						ActThread();
				}

				break;
			}

		case EM_IPC_DISCONNECTED:
			{
				m_uTryConnectLastTick = GetTickCount();
				m_iIPCStatus = EM_IPC_CONNECTIING;
				break;
			}

		case EM_IPC_CONNECTIING:
			{
				if( GetTickCount() - m_uTryConnectLastTick < m_uTryConnectTime  )
				{
					if( IsConnected() )
					{
						// 設定狀態並且使用CB通知
						ChangeIPCStatus( EM_IPC_CONNECTED );
					}
					else if( m_pNamedPipe && m_pNamedPipe->ReOpen() )
					{
						// 設定狀態並且使用CB通知
						ChangeIPCStatus( EM_IPC_CONNECTED );
					}

					if( m_iIPCStatus == EM_IPC_CONNECTED )
						MsgOut( EM_LOG_LEVEL_WARNNING, "Try connect the server success\n" );
					else
						MsgOut( EM_LOG_LEVEL_WARNNING, "Try connect the server failed\n" );
				}
				else
				{
					// 設定狀態並且使用CB通知
					MsgOut( EM_LOG_LEVEL_WARNNING, "Connect the server time out\n" );
					ChangeIPCStatus( EM_IPC_DISCONNECTED );
				}

				break;
			}
	}
}


void CInterProcCommClient::SetTryConnectTime( unsigned long dwTime_ms )
{
	m_uTryConnectTime = dwTime_ms;
}
