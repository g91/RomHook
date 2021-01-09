
#include "InterProcCommHost.h"
#include "NamedPipe.h"



CInterProcCommHost::CInterProcCommHost()
{
	m_uTryConnectTime = 5 * 1000;
	m_bStopProc		= false;
	m_hMainThead = NULL;
}

CInterProcCommHost::~CInterProcCommHost()
{
	//m_bStopProc = true;

	//if( m_hMainThead != INVALID_HANDLE_VALUE )
	//{
	//	CloseHandle( m_hMainThead );
	//	m_hMainThead = INVALID_HANDLE_VALUE;
	//}
	
	Detory();

	//CInterProcCommBase::~CInterProcCommHost();
}

void CInterProcCommHost::Detory()
{
	m_bStopProc = true;

	if( m_pNamedPipe )
	{
		m_pNamedPipe->UnLock();
	}
	
	if( m_hMainThead != INVALID_HANDLE_VALUE )
	{
		ActThread();
		WaitForSingleObject( m_hMainThead, INFINITE );
		CloseHandle( m_hMainThead );
		m_hMainThead = INVALID_HANDLE_VALUE;
	}
}

bool CInterProcCommHost::Init( const char* szPipeName )
{
	Detory();

	m_pNamedPipe = new CNamedPipeEx();

	BOOL bSuccess = m_pNamedPipe->Create( szPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,  PIPE_TYPE_MESSAGE | PIPE_WAIT, 1 , 5 * 1024 * 1024 , 5 * 1024 * 1024, 100 , NULL );
	m_pNamedPipe->DisConnectClient();

	if( bSuccess )
	{
		m_bStopProc = false;
		m_hMainThead = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)RunProc, this, NULL, NULL );
	}

	return bSuccess == TRUE;
}

void CInterProcCommHost::StartProc()
{
	

}

void CInterProcCommHost::Process()
{
	if( HaveHandleData() )
	{
		ActThread();
	}

	Flush();
}

void CInterProcCommHost::RunProc( LPARAM lparam )
{
	CInterProcCommHost* pMain = (CInterProcCommHost*)lparam;

	if( pMain )
		pMain->RSThreadProc();
}


void CInterProcCommHost::RSThreadProc()
{
	while( true )
	{
		if( m_bStopProc )
			return;

		WaitForSingleObject( m_waitEvent, 100 );

		switch( m_iIPCStatus )
		{

		case EM_IPC_CONNECTED:
			{
				// if the client wasnt connected, try to reconnect server
				if( !IsConnected() )
				{
					m_iIPCStatus = EM_IPC_DISCONNECTED;
				}
				else
				{
// 					boost::mutex::scoped_lock lk(m_threadCs);
// 					m_waitEvent.wait( lk );

					// if recv or send data gave error, try to reconnect client
					if( !RecvDataProc() )
						break;

					if( !SendDataProc() )
						break;
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
					m_pNamedPipe->DisConnectClient();

					BOOL bResult = m_pNamedPipe->ConnectClient();

					if( IsConnected() )
					{
						// 設定狀態並且使用CB通知
						ChangeIPCStatus( EM_IPC_CONNECTED );
					}
// 					else if( m_pNamedPipe && m_pNamedPipe->ReOpen() )
// 					{
// 						// 設定狀態並且使用CB通知
// 						ChangeIPCStatus( EM_IPC_CONNECTED );
// 					}

					if( m_iIPCStatus == EM_IPC_CONNECTED )
						MsgOut( EM_LOG_LEVEL_INFO, "Client connected success\n" );
					else
						MsgOut( EM_LOG_LEVEL_WARNNING, "Client connected failed\n" );
				}
				else
				{
					MsgOut( EM_LOG_LEVEL_WARNNING, "Connect the server time out\n" );
					ChangeIPCStatus( EM_IPC_DISCONNECTED );
				}

				break;
			}

		}
	}
}


