
#include "InterProcCommBase.h"
#include <ctime>

CInterProcCommBase::CInterProcCommBase()
{
	m_pNamedPipe = NULL;
	m_uTempDataSize = 5 * 1024 * 1024;
	m_pTempData = NULL;  // alloc 5MB memory space

	m_iIPCStatus = EM_IPC_DISCONNECTED;

	m_uBufSize = 1024;
	m_pBuffer = new byte[m_uBufSize];

	m_waitEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_waitTimeEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	QueryPerformanceFrequency( &m_liFrequency );
}

CInterProcCommBase::~CInterProcCommBase()
{
	if( m_pNamedPipe )
	{
		delete m_pNamedPipe;
		m_pNamedPipe = NULL;
	}

	if( m_pTempData )
	{
		delete [] m_pTempData;
		m_pTempData = NULL;
	}

	if( m_pBuffer )
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}
}

void CInterProcCommBase::SetMsgOutCallback( PFUNC_MSG_OUTPUT_CALLBACK pFunc )
{
	m_pMsgOutCB = pFunc;
}

void CInterProcCommBase::MsgOut( int iLevel, const char* format, ... )
{
	CIPICSHelper csHelper( &m_msgCs );

	char szPrintf[ 2048 ];
	va_list args;
	va_start( args , format );
	vsprintf_s( szPrintf , 2048 , format , args );
	va_end( args );

	if( m_pMsgOutCB )
	{
		m_pMsgOutCB( iLevel, szPrintf );
	}
}

void CInterProcCommBase::SetRecvCallback( PFUNC_RECV_CALLBACK pFunc )
{
	m_pRecvCB = pFunc;
}

// set the callback if connect status
void CInterProcCommBase::SetStatusChangeCallback( PFUNC_CONNECT_STATUS_CALLBACK pFunc )
{
	m_pStatusChageCB = pFunc;
}

void CInterProcCommBase::Send( void* pData, unsigned long uPGSize )
{
	TPipePacket packet;

	packet.pData = new byte[ uPGSize ];
	memcpy( packet.pData, pData, uPGSize );

	packet.uSize = uPGSize;

	// push back to send data queue
	CIPICSHelper csHelper( &m_send_cs );
	m_deqSendData.push_back( packet );
}


void CInterProcCommBase::Flush()
{
	// handle recv data
	if( m_deqRecvData.size() > 0 )
	{
		m_recv_cs.Lock();

		// copy recv data queue
		std::deque< TPipePacket > deqTempRecvData = m_deqRecvData;
		m_deqRecvData.clear();

		m_recv_cs.UnLock();

		while( deqTempRecvData.size() > 0 )
		{
			TPipePacket packet = deqTempRecvData.front();

			static int iReadCount = 0;
			iReadCount++;

			if( m_pRecvCB )
			{
				m_pRecvCB( packet.pData, packet.uSize );
			}
			packet.Destroy();
			deqTempRecvData.pop_front();
		}
	}

}

bool CInterProcCommBase::SendDataProc()
{
	while( true )
	{
		// push back to send data queue
		TPipePacket sendData;

		{
			CIPICSHelper csHelper( &m_send_cs );
			if( m_deqSendData.size() == 0 )
				return true;

			// pop send data
			sendData = m_deqSendData.front();
			m_deqSendData.pop_front();
		}

		{
			DWORD dwWriteByte;
		//	boost::timer::cpu_timer t;

			BOOL bSuccess = m_pNamedPipe->Write( sendData.pData , sendData.uSize , dwWriteByte , NULL );		// Write Send Info

			//double duTime = t.elapsed().wall;
		//	printf( "Write Data cost time: [%f]\n",duTime / 1000 / 1000 );
			if( !bSuccess )
			{
				// 重新連結 
				MsgOut( EM_LOG_LEVEL_CRITICAL, "WriteFile Failed Error Code: %d\n", GetLastError() );
				return false;
			}
			else
				MsgOut( EM_LOG_LEVEL_DEBUG, "WriteByte: %u\n", dwWriteByte );

			sendData.Destroy();
		}
	}
	return true;
}



bool CInterProcCommBase::RecvDataProc()
{
	DWORD dwTotalBytesAvail;
	DWORD dwBytesLeftThisMessage;
	
	byte* ptr;

	bool bCreated = false;

	if( m_pTempData == NULL )
	{
		m_pTempData = new byte[ m_uTempDataSize ];  // alloc 5MB memory space
	}

	DWORD	dwCalTotalByte	= 0;
	double	duCalTimeTick	= GetCurTickCount();

//	double uPeekTime = 0;
//	double uReadTime = 0;

	while( true )
	{
		DWORD dwBytesRead = 0;

	//	boost::timer::cpu_timer t;

		// peek whether have any data need to read, if have data that dwBytesLeftThisMessage will be a number of this packet-size  
		if( m_pNamedPipe->Peek( NULL, NULL, dwBytesRead, dwTotalBytesAvail, dwBytesLeftThisMessage ) == FALSE )
			return false;

	//	uPeekTime += t.elapsed().wall;
	//	t.start();

		DWORD dwPGSize = dwBytesLeftThisMessage; 

		if( dwPGSize > 0 )
		{
			TPipePacket packet;
			if( packet.pData == NULL)
			{	
				packet.pData	= new byte[ dwPGSize ];
				packet.uSize	= dwPGSize;

				ptr				= packet.pData;
				dwCalTotalByte	= dwPGSize;
			}

			// real read data
			DWORD dwNumberOfBytesToRead;
			BOOL bResult = m_pNamedPipe->Read( ptr, dwPGSize, dwNumberOfBytesToRead, NULL );

			//double dw = t.elapsed().user;
			//dw = t.elapsed().system;
			//dw = t.elapsed().wall;
		//	uReadTime += t.elapsed().wall;

			if( !bResult )
			{
				delete [] packet.pData;
				MsgOut( EM_LOG_LEVEL_WARNNING, "ReadFile Failed Error Code: %d\n", GetLastError() );
				return false;
			}
			else
			{
				MsgOut( EM_LOG_LEVEL_DEBUG, "Read Bytes: %u\n", dwNumberOfBytesToRead );

// 				// if this message read over, push back to queue, and read next message
// 				if( dwBytesLeftThisMessage == 0 )
// 				{
					CIPICSHelper csHelper( &m_recv_cs );
					m_deqRecvData.push_back( packet );
					
					double duTempTick = GetCurTickCount();

					SetEvent( m_waitTimeEvent );
					MsgOut( EM_LOG_LEVEL_DEBUG, "CInterProcCommBase::RecvDataProc Read %d Bytes, Cost Time: %f ms\n", dwCalTotalByte, duTempTick - duCalTimeTick );

					duCalTimeTick = duTempTick;
					bCreated = false;

				//	if( uPeekTime > 0 && uReadTime > 0 )
					//	printf( "uPeekTime = [%f] ms, uReadTime = [%f] ms\n", uPeekTime / 1000 / 1000 , uReadTime / 1000 / 1000 );
					continue;
				//}
			}
		}
		else
		{
	
			break;
		}
	}
	return true;
}


// get the size of send queue
unsigned long CInterProcCommBase::GetSendQueueSize()
{
	CIPICSHelper csHelper( &m_send_cs );
	return m_deqSendData.size();
}

// get the size of recv queue
unsigned long CInterProcCommBase::GetRecvQeueuSize()
{
	CIPICSHelper csHelper( &m_recv_cs );
	return m_deqRecvData.size();
}

bool CInterProcCommBase::IsConnected()
{
	if( m_pNamedPipe && m_pNamedPipe->IsConnected() )
		return true;

	return false;

}

// get the tick now
double CInterProcCommBase::GetCurTickCount()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter( &counter );
	return double( counter.QuadPart ) / m_liFrequency.QuadPart * 1000; 

}

void CInterProcCommBase::ChangeIPCStatus( int iStatus )
{
	m_iIPCStatus = iStatus;

	if( m_pStatusChageCB )
		m_pStatusChageCB( iStatus );
}

void* CInterProcCommBase::GetBuffer( unsigned long size )
{
	if( size > m_uBufSize )
	{
		if (m_pBuffer != NULL)
		{
			delete [] m_pBuffer;
		}

		m_uBufSize = ((size / 4) + 1) * 4;
		m_pBuffer = new BYTE[m_uBufSize];
	}

	memset( m_pBuffer, 0, m_uBufSize );
	return m_pBuffer;
}

bool CInterProcCommBase::HaveHandleData()
{
	if( m_pNamedPipe != NULL )
	{
		DWORD	dwTotalBytesAvail;
		DWORD	dwBytesLeftThisMessage;
		DWORD	dwBytesRead = 0;

		// peek whether have any data need to read
		if( m_pNamedPipe->Peek( NULL, NULL, dwBytesRead, dwTotalBytesAvail, dwBytesLeftThisMessage ) == TRUE && dwBytesLeftThisMessage > 0 )
			return true;
	}

	CIPICSHelper csHelper( &m_send_cs );
	if( m_deqSendData.size() > 0 )
		return true;

	return false;
}


void CInterProcCommBase::ActThread()
{
	//m_waitEvent.notify_one();
	SetEvent( m_waitEvent );
}

void CInterProcCommBase::GraceSleep()
{
	unsigned long uSleepTime = 10;

	if( m_iIPCStatus == EM_IPC_CONNECTED )
	{
		// 如果有發送的資料 應該趕快發送, 其餘的等待 100ms 或者 等待 Recv Event
		//CIPICSHelper csHelper( &m_send_cs );

		if( HaveHandleData() )
		{
			SetEvent( m_waitEvent );
			uSleepTime = 1;
		}
	}
	MsgOut( EM_LOG_LEVEL_DEBUG, "Sleep Time: %u ms\n", uSleepTime );
	WaitForSingleObject( m_waitTimeEvent, uSleepTime );
}