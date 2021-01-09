#pragma warning (disable:4949)
#include "NetBridge_Base.h"
#include <time.h>

#pragma unmanaged



CNetBridge_Base::CNetBridge_Base(void)
{
	m_hMsgEvent			= CreateEvent( NULL, FALSE, FALSE, NULL ); // auto-reset

	m_dwHost			= 0;
	m_pfError			= NULL;

	m_bytesSend			= 0;
	m_bytesRecv			= 0;


	m_pfOutPut			= NULL;
	m_bShutdown			= false;

	m_bEvent			= false;
	m_bCheckRespondTime	= false;

	m_dwAvgProcEvent	= 100;

	m_LastCalSendRevTime = 0;

	m_dwAvgNewEvent		= 0;

	m_bSendBufferLimit	= false;				// Check transfer limit flag, default is off
	m_dwSendBuffLimit	= 20971520;				// Check transfer limit	default is 204,800(bytes) and respond time bigger than 3000ms 2 * 1024 * 1024

	m_dwKeepAliveTime	= 60000;

	ReSetPacketSendCount();
	ReSetPacketRecvCount();	
	//m_CompletionPort	= NULL;

	// Setup array to hold CNetSocket pointers
	m_vecSocketSize		= 4096;
	m_vecSocket			= new CNetSocket * [m_vecSocketSize];

	m_dwTimeLastGetEvent	= GetTickCount();
	m_dwCheckRespondTime	= GetTickCount() + 10000;				// Check respond time for every 10sec

	memset(m_vecSocket, 0, sizeof(CNetSocket *) * m_vecSocketSize);

	for(int i = 0; i < m_vecSocketSize; ++i)
	{
		m_unusedNetIDs.Queue(i);
	}

	m_minFlushTime			= 0;
	m_maxFlushTime			= 0;

	m_minEvent				= 0;
	m_maxEvent				= 0;

	InterlockedExchange( &m_SendCount, 0 );
	m_minSendCountPerSec	= 0;
	m_maxSendCountPerSec	= 0;

	InterlockedExchange( &m_SendBytes, 0 );
	m_maxSendBytesPerSec	= 0;
	m_maxSendBytesPerSec	= 0;

	InterlockedExchange( &m_RecvCount, 0 );
	m_minRecvCountPerSec	= 0;
	m_maxRecvCountPerSec	= 0;

	InterlockedExchange( &m_RecvBytes, 0 );
	m_maxRecvBytesPerSec	= 0;
	m_maxRecvBytesPerSec	= 0;

	for( int i=0; i<10; i++ )
	{
		InterlockedExchange( &(m_Respond[i]), 0 );
	}

	m_LastFlushTime			= GetTickCount();

	m_CheckRecvEvent		= true;


	//ZeroMemory( m_EventHostArray, sizeof( m_EventHostArray ) );
}

CNetBridge_Base::~CNetBridge_Base(void)
{
    OutputDebugString("CNetBridge_Base::~CNetBridge_Base()\n");

	if( m_hMsgEvent )
	{
		CloseHandle( m_hMsgEvent );
		m_hMsgEvent = NULL;
	}

#if NET_BRIDGE_BASE_BUFFER_KEEP_POINTER

    for (std::vector<CNetSocket*>::iterator iter_net = m_vecNetSocket.begin(); iter_net != m_vecNetSocket.end(); ++iter_net)
    {
        char szDebug[255+1];
        _snprintf(szDebug, 255, "> NetSocket[%u] - Address(0x%p) - Buffer(0x%p)\n", (*iter_net)->m_dwNetID, (*iter_net), (*iter_net)->m_pRecvBuff);
        OutputDebugString(szDebug);
    }
    m_vecNetSocket.clear();

    for (std::vector<std::string>::iterator iter_net_name = m_vecNetSocketName.begin(); iter_net_name != m_vecNetSocketName.end(); ++iter_net_name)
    {
        char szDebug[255+1];
        _snprintf(szDebug, 255, "> %s\n", (*iter_net_name).c_str());
        OutputDebugString(szDebug);
    }
    m_vecNetSocketName.clear();

    for (std::vector<CEventMsg*>::iterator iter_event = m_vecEventMsg.begin(); iter_event != m_vecEventMsg.end(); ++iter_event)
    {
        char szDebug[255+1];
        _snprintf(szDebug, 255, "> EventMsg[%u] - Address(0x%p) - Socket(0x%p)\n", (*iter_event)->dwEventID, (*iter_event), (*iter_event)->pSocket);
        OutputDebugString(szDebug);
    }
    m_vecEventMsg.clear();

    for (std::vector<std::string>::iterator iter_event_name = m_vecEventMsgName.begin(); iter_event_name != m_vecEventMsgName.end(); ++iter_event_name)
    {
        char szDebug[255+1];
        _snprintf(szDebug, 255, "> %s\n", (*iter_event_name).c_str());
        OutputDebugString(szDebug);
    }
    m_vecEventMsgName.clear();

#endif

	//@ Memory leak
	// modified by tianyu for temp fix
	//for ( int i = 0; i < m_vecSocketSize; i++ )
	//{
	//	CNetSocket *pSocket = GetSocket( i );
	//	if ( pSocket )
	//	{
	//		for ( vector< CBuffer* >::iterator it = pSocket->m_vecAccept.begin(); it != pSocket->m_vecAccept.end(); it++ )
	//		{
	//			DeleteBuffer( *it );
	//		}
	//	}
	//	DeleteSocket( i );
	//}
	delete[] m_vecSocket;
	m_vecSocket = NULL;
}

int	CNetBridge_Base::Init ( int iNumThread )
{
	// 初始化  Winsock 2.2
	WSADATA          wsd;

	// Load Winsock
	if ( WSAStartup( MAKEWORD(2,2), &wsd ) != 0 )
	{
		return NB_ERR_UNABLE_LOAD_WINSOCK;
	}

	return NB_OK;
}

void CNetBridge_Base::Release				()
{
	WSACleanup( );
}

byte CNetBridge_Base::GetCheckSum( BYTE* pSource, int iSize, byte Code, byte SourceCheckSum )
{
	BYTE CheckSum = SourceCheckSum;		// default = 0;
	for( int i = 0; i < iSize; i++ )
	{
		CheckSum += pSource[ i ];
	}
	CheckSum += Code;

	return CheckSum;
}


bool CNetBridge_Base::GetPacketInfo	( PVOID pData, DWORD dwDataSize, DWORD *pFlag, DWORD *pSize )
{
	// 檢查是否已滿足檢查封包大小的量 ( 暫時先以 DWORD 4 Bytes 訂, 之後可能是用動態或者是其它方式傳送 )

	DWORD dwBaseSize = 0;
	if( dwDataSize >= sizeof( Struct_PacketHeader ) )
	{
		Struct_PacketHeader*	pHeader		= (Struct_PacketHeader*)pData;
		byte					checksum	= GetCheckSum( (byte*)pHeader, sizeof( Struct_PacketHeader ), 0, 0 ) - pHeader->HeaderChecksum;

		if( pHeader->wSystemFlag != 0x20 )
		{
			if( checksum != pHeader->HeaderChecksum )
			{
				return false;
			}
		}




		// 檢查封裝資料有無壓縮 or 打包

		//dwSize = ( dwSize | 0x80000000 ) ^ 0x80000000;
		//return dwSize;
		/*
		if( pFlag )
		{
		//*pFlag = (*((DWORD*)pData) | (!DF_PTAG_MASK) ) ^ (!DF_PTAG_MASK);
		*pFlag = (*((DWORD*)pData) | (DF_PTAG_SIZEMASK) ) ^ (DF_PTAG_SIZEMASK);
		}


		if( pSize )
		{
		*pSize = ((*((DWORD*)pData) | DF_PTAG_MASK) ^ DF_PTAG_MASK ) + dwBaseSize;

		if( *pSize > 100000 )
		{
		//MessageBox( NULL , "封包Size過大","錯誤", MB_OK );
		}
		}
		*/

		*pSize = pHeader->dwTotalPacketSize;
		//*pFlag = *(((DWORD*)pData)+1);

		return true;
	}
	
	return true;
}

DWORD	CNetBridge_Base::ConvertIP( const char* pszIP )
{
	u_long IP_ADDRESS;

	if( pszIP != NULL )
	{
		if( strlen( pszIP ) != 0 )
		{

			//測試輸入的IP是IP Address 或是 DNS

			//轉換 IP
			IP_ADDRESS = inet_addr( pszIP ); 

			//測試轉出結果, 若傳回 INADDR_NONE 的話, 表該 IP 可能是 DNS
			if ( IP_ADDRESS == INADDR_NONE ) 
			{
				// Host isn't an IP address, try using DNS
				hostent* HE = gethostbyname( pszIP );

				if ( HE == 0 )
				{
					//Error can't check DNS
					return 0;
				}

				IP_ADDRESS = *((u_long*)HE->h_addr_list[0]);
			}
		}
	}

	return IP_ADDRESS;
}


CNetSocket*	CNetBridge_Base::CreateSocket()
{
	DWORD		dwNetID		= 0;
	CNetSocket* pSocket		= NULL;

	pSocket							= new CNetSocket;

	//pSocket->m_pvecMsg				= &m_vecAuthorize;	
	pSocket->m_pvecMsg				= &m_vecMsg;
	pSocket->m_pNetBridge			= this;
	//pSocket->m_pBufferIncomplete	= CreateBuffer( ( DF_NB_PACKETBUFFERSIZE * 2 ) );
	pSocket->m_wsaEvent				= WSACreateEvent();

	m_cs_Socket.Enter( "CNetBridge_Base::CreateSocket" );

	{
		if(m_unusedNetIDs.Count() == 0)
		{
			int newVecSocketSize = m_vecSocketSize * 2;
			CNetSocket **newVecSocket = new CNetSocket * [newVecSocketSize];
			memset(newVecSocket, 0, sizeof(CNetSocket *) * newVecSocketSize);
			memcpy(newVecSocket, m_vecSocket, sizeof(CNetSocket *) * m_vecSocketSize);

			for(int i = m_vecSocketSize; i <  newVecSocketSize; ++i)
			{
				m_unusedNetIDs.Queue(i);
			}

			delete[] m_vecSocket;
			m_vecSocket = newVecSocket;
			m_vecSocketSize = newVecSocketSize;
		}

		dwNetID = m_unusedNetIDs.Dequeue();

		pSocket->m_dwNetID		= dwNetID;
		m_vecSocket[dwNetID]	= pSocket;
	}

#if NET_BRIDGE_BASE_BUFFER_KEEP_POINTER
    char szNetID[16];
    sprintf(szNetID, "%u", dwNetID);
    std::string strDebug;
    strDebug.append("NetID = (");
    strDebug.append(szNetID);
    strDebug.append(")");
    m_vecNetSocket.push_back(pSocket);
    m_vecNetSocketName.push_back(strDebug);
    char szDebug[255+1];
    _snprintf(szDebug, 255, "CNetBridge_Base::CreateSocket(%u) - Address(0x%p)\n", dwNetID, pSocket);
    OutputDebugString(szDebug);
#endif
    
    m_cs_Socket.Leave( "CNetBridge_Base::CreateSocket" );

	return pSocket;
}

void	CNetBridge_Base::DeleteSocket	( DWORD dwNetID )
{
	// DeleteSocket 有義務將所有資料結構中有關該 Socket 的資料刪除

	CNetSocket* pSocket = GetSocket(dwNetID);

#if NET_BRIDGE_BASE_BUFFER_KEEP_POINTER
    char szDebug[255+1];
    _snprintf(szDebug, 255, "CNetBridge_Base::DeleteSocket(%u) - Address(0x%p)\n", dwNetID, pSocket);
    OutputDebugString(szDebug);
#endif

	m_cs_Socket.Enter( "CNetBridge_Base::DeleteSocket" );
	{
		// 檢查有無在等待刪除清單中
		multimap< DWORD, CNetSocket* >::iterator itclose = m_mapClosingSocket.begin();
		if( itclose != m_mapClosingSocket.end() )
		{
			while( 1 )
			{
				if( itclose->second == pSocket )
				{
					itclose = m_mapClosingSocket.erase( itclose );
					break;
				}
				else
					itclose++;

				if( itclose == m_mapClosingSocket.end() )
					break;
			}
		}

		/*
		// 檢查 WaitSendSocket
		vector< DWORD >::iterator itWait = m_vecWaitSendSocket.begin();
		while(1)
		{
			if( *itWait == dwNetID )
			{
				itWait = m_vecWaitSendSocket.erase( dwNetID );
			}
		}
		*/

		if( pSocket != NULL )
		{
			// Free WSA event
			WSACloseEvent( pSocket->m_wsaEvent );

			// Close socket
			if( pSocket->m_tcp_socket != INVALID_SOCKET )
			{
				int Val = closesocket( pSocket->m_tcp_socket );
				pSocket->m_tcp_socket = INVALID_SOCKET;
			}

			// Delete all outstanding packet frames
			while(!pSocket->m_queueSendFrame.IsEmpty())
			{
				CFrameBuffer frame = pSocket->m_queueSendFrame.Dequeue();
				m_bufferManager.Delete(frame.m_pData);
			}


			// 釋放 Incomplete Buffer 
			//DeleteBuffer( pSocket->m_pBufferIncomplete );

			if( pSocket->m_pRecvIncomplete != NULL )
			{
				m_bufferManager.Delete( pSocket->m_pRecvIncomplete );
				pSocket->m_pRecvIncomplete = NULL;
			}

			// 檢查 Accpet Buffer

			// 檢查 Recv Buffer

			// 檢查 Send Buffer

			// Delete socket structure
			delete pSocket;

			// Recycle the deleted socket's NetID
			m_vecSocket[dwNetID] = NULL;
			m_unusedNetIDs.Queue(dwNetID);
		}
	}
	m_cs_Socket.Leave( "CNetBridge_Base::DeleteSocket" );
}

CEventMsg*		CNetBridge_Base::CreateMsg ( EM_MSG_TYPE emMsgType, CNetSocket* pSocket )
{
	CEventMsg *pMsg = NULL;

	m_cs_EventMsgPool.Enter( "CNetBridge_Base::CreateMsg" );
	{
		if(m_unusedEventMsgs.IsEmpty())
		{
			//@ Memory leak
			pMsg			= new CEventMsg;
#if NET_BRIDGE_BASE_EVENT_CREATE_AND_DESTORY_DEBUG_PRINT
            char szNetID[16];
            sprintf(szNetID, "%u", pSocket->m_dwNetID);
            std::string strDebug;
            strDebug.append("NetID = (");
            strDebug.append(szNetID);
            strDebug.append(")");
            m_vecEventMsg.push_back(pMsg);
            m_vecEventMsgName.push_back(strDebug);
            char szDebug[255+1];
            _snprintf(szDebug, 255, "CNetBridge_Base::CreateMsg(%u) - Address(0x%p) - Socket(0x%p)\n", pSocket->m_dwNetID, pMsg, pSocket);
            OutputDebugString(szDebug);
#endif
		}
		else
		{
			pMsg = m_unusedEventMsgs.Dequeue();
		}
	}
	m_cs_EventMsgPool.Leave( "CNetBridge_Base::CreateMsg" );

	// Initialize event message header
	pMsg->emMsg		= emMsgType;
	pMsg->pSocket	= pSocket;
	pMsg->dwNetID	= pSocket->m_dwNetID;

	return pMsg;
}

void			CNetBridge_Base::DeleteMsg ( CEventMsg* pMsg )
{
#if NET_BRIDGE_BASE_EVENT_CREATE_AND_DESTORY_DEBUG_PRINT
    char szDebug[255+1];
    _snprintf(szDebug, 255, "CNetBridge_Base::DeleteMsg(%u) - Address(0x%p) - Socket(0x%p)\n", pMsg->dwNetID, pMsg, pMsg->pSocket);
    OutputDebugString(szDebug);
#endif

	m_cs_EventMsgPool.Enter( "CNetBridge_Base::DeleteMsg" );
	{
		m_unusedEventMsgs.Queue(pMsg);
	}
	m_cs_EventMsgPool.Leave( "CNetBridge_Base::DeleteMsg" );
}

inline DWORD CNetBridge_Base::Wait					( DWORD dwTime )
{	
	DWORD dwTimeNow	= GetTickCount();
	DWORD dwReturn	= WaitForSingleObject( CNetBridge::m_pNetMainEvent, dwTime );

	if( dwReturn != WAIT_TIMEOUT )
	{
		if( this->m_bEvent != false )
		{
			this->m_bEvent = false;
			this->Flush();
		}
	}

	// 一定時間 Flush 一次
	if( dwReturn != WAIT_TIMEOUT || dwTimeNow > this->m_dwEnterTime )
	{		
		this->m_dwEnterTime = dwTimeNow + 300;
		this->Flush();
	}

	return dwReturn;


	//return WaitForSingleObject( m_hMsgEvent, dwTime );
}

void	CNetBridge_Base::Flush ()
{

	DWORD	dwFlushStart	= GetTickCount();
	DWORD	dwFlushOffset	= abs((long) (GetTickCount() - m_LastFlushTime) );

	if( dwFlushOffset > 1000 )
	{
		// 計算每秒最高及最低的 LOG

		// Send Count
		if( m_minSendCountPerSec > m_SendCount || m_minSendCountPerSec == 0 )
			m_minSendCountPerSec = m_SendCount;

		if( m_maxSendCountPerSec < m_SendCount )
			m_maxSendCountPerSec = m_SendCount;

		m_SendCount = 0;

		// SendBytes
		if( m_minSendBytesPerSec > m_SendBytes || m_minSendBytesPerSec == 0 )
			m_minSendBytesPerSec = m_SendBytes;

		if( m_maxSendBytesPerSec < m_SendBytes )
			m_maxSendBytesPerSec = m_SendBytes;

		m_SendBytes = 0;

		// Recv Count
		if( m_minRecvCountPerSec > m_RecvCount || m_minRecvCountPerSec == 0 )
			m_minRecvCountPerSec = m_RecvCount;

		if( m_maxRecvCountPerSec < m_RecvCount )
			m_maxRecvCountPerSec = m_RecvCount;

		m_RecvCount = 0;

		// RecvBytes
		if( m_minRecvBytesPerSec > m_RecvBytes || m_minRecvBytesPerSec == 0 )
			m_minRecvBytesPerSec = m_RecvBytes;

		if( m_maxRecvBytesPerSec < m_RecvBytes )
			m_maxRecvBytesPerSec = m_RecvBytes;

		m_RecvBytes = 0;



		m_LastFlushTime = dwFlushStart;
	}




	static vector< CEventMsg* >		vecMsg;
	//static vector< CEventMsg* >		vecAuthorize;
	//SleepEx( 0, true );

	// 將所有訊息一口氣取出, 避免多次呼叫浪費系統時間
	m_cs_MessageAndEvent.Enter( "CNetBridge_Base::Flush" );
	{
		// 將 m_vecMsg 的資料併入只有主 Thread 有作用的 m_MsgQueue
		/*
		while( 1 )
		{
			if( m_vecMsg.Count() == 0 )
			{
				break;
			}
			else
			{
				m_MsgQueue.Queue( m_vecMsg.Dequeue() );
			}
		}
		*/

		// 計算每秒新事件量
			/*
			DWORD dwTime			= GetTickCount() - m_dwTimeLastGetEvent;			
			DWORD dwNewEvent		= m_vecMsg.Count();

			m_dwTimeLastGetEvent	= GetTickCount();

			if( dwNewEvent != 0 && dwTime != 0 )
			{
				m_dwAvgNewEvent	= ( m_dwAvgNewEvent + ( ( dwNewEvent * 1000 ) / dwTime ) ) / 2 ;
			}
			*/

		// 將新事件併入主 Thread 用的 Event Queue
			m_MsgQueue.MergeAtEnd( m_vecMsg );
			m_vecMsg.clear();

	}
	m_cs_MessageAndEvent.Leave( "CNetBridge_Base::Flush" );

	// 記錄每次 flush 時最大及最少事件量
	DWORD dwNumEvent	= m_MsgQueue.size();

	if( m_minEvent > dwNumEvent )
		m_minEvent	= dwNumEvent;

	if( m_maxEvent < dwNumEvent )
		m_maxEvent	= dwNumEvent;


	if( m_CheckRecvEvent == true )
	{
		CheckMsg( NULL );
	}

	// 檢查有無 ClosingSocket 到時間了
	CheckSocket();

	// 檢查有無封包待送
	//CheckPacket();	
	SendFlush();

	//計算封包收送資料
	CalSendRecvBytes();

	// Flush the buffer manager
	m_bufferManager.Flush();


	// 記錄每次 flush 時間
	DWORD	dwFlushEnd	= abs( (long) (GetTickCount() - dwFlushStart) );

	if( m_minFlushTime > dwFlushEnd || m_minFlushTime == 0 )
		m_minFlushTime = dwFlushEnd;

	if( m_maxFlushTime < dwFlushEnd )
		m_maxFlushTime = dwFlushEnd;
}

void CNetBridge_Base::CheckMsg				( vector< CEventMsg* >* pvecMsg )
{
	CEventMsg*				pMsg	= NULL;
	CEventObj*				pEvent	= NULL;
	DWORD					dwNetID = 0;

	DWORD					dwProcTimes		= 0;
	DWORD					dwSecEvent		= 0;	// 每秒處理事件量

	DWORD					dwStartTime	= GetTickCount();
	DWORD					dwTime		= 0;

	//vector< CEventMsg* >::iterator	it = pvecMsg->begin();

	//while( it != pvecMsg->end() )
	while(1)
	{
		pMsg		= NULL;
		pEvent		= NULL;

		//pMsg = *it;
		//it++;

		if( m_MsgQueue.Count() != 0 )
		{
			//if( dwProcTimes > m_dwAvgProcEvent )
			//if( dwProcTimes > 100 )
			//{
			//	break;
			//}

			pMsg = m_MsgQueue.Dequeue();
		}
		else
		{
			break;
		}

		
		
		// 檢查 Socket 是否仍在
		CNetSocket *pSocket = GetSocket(pMsg->dwNetID);

		// 執行事件
		if( pSocket != NULL )
		{
			switch( pMsg->emMsg )
			{
			case MSG_SYSTEM:
				{
					Struct_PacketHeader* pHeader	= pMsg->MsgSystem.pHeader;

					switch( pHeader->wSystemFlag )					
					{
					case DF_PSYSFLAG_R_ALIVE:
						{
							SendAliveAnswer( pSocket, *((DWORD*)pMsg->MsgSystem.pData) );
						} break;
					}

					m_bufferManager.Delete( (BYTE*)pHeader );

				} break;
			case MSG_RECV:
				{
					// 這裡應該還要做解壓縮 or 其它處理
					//CBuffer*	pRecvBuf	= pMsg->MsgRecv.pBuffer;
					//PVOID		ptr			= pRecvBuf->m_pData + sizeof( DWORD );
					//DWORD		dwBufSize	= pRecvBuf->m_dwSize - sizeof( DWORD );

					PVOID		ptr					= pMsg->MsgRecv.pData;
					DWORD		dwBufSize			= pMsg->MsgRecv.dwDataSize;

					pSocket->m_MsgRecvCount--;

					dwNetID							= pMsg->pSocket->m_dwNetID;

					pSocket->m_lastCheckRecvIndex	= dwStartTime;

					//int iPacketID = *((int*)&(((byte*)ptr)[12]));


					if( pSocket->m_pEvent != NULL && pSocket->m_emStatus == EM_SOCKET_CONNECTED )
						pSocket->m_pEvent->OnRecv( dwNetID, dwBufSize, ptr );

					//DeleteBuffer( pMsg->MsgRecv.pBuffer );
					m_bufferManager.Delete( pMsg->MsgRecv.pPacket );
					//pMsg->MsgRecv.pBuffer = NULL;												
				} break;

					// 因為還沒有做持續連線的動作. 故暫時先不做
					/*
					case MSG_CONNECT_FAILED:
					{
					//((CClientEventObj*)pEvent)->OnConnectFailed( pMsg->m_dwFailID );
					if( GetEvent( dwNetID ) )
					((CClientEventObj*)pEvent)->OnConnectFailed( pMsg->MsgConnectFailed.dwFailID );
					} break;
					*/
			
			case MSG_CONNECT:
				{
					CNetSocket* pSocket		= pMsg->pSocket;
					dwNetID					= pMsg->pSocket->m_dwNetID;

					if( pSocket->m_pEvent )
					{
						pSocket->m_pEvent->OnConnect( pSocket->m_dwNetID );
						SetSocketNoDelay( pSocket->m_dwNetID );
					}

				} break;

			case MSG_CONNECT_FAILED:
				{
					CNetSocket* pSocket		= pMsg->pSocket;
					dwNetID					= pMsg->pSocket->m_dwNetID;

					if( pSocket->m_pEvent )
					{
						pSocket->m_pEvent->OnConnectFailed( dwNetID, -1 );
					}

					//On_Error("DeleteSocket called from CheckMsg(MSG_CONNECT_FAILED)");
					///DeleteSocket( dwNetID );
					Close( dwNetID );

				} break;
		
			case MSG_ACCEPT:
				{
					//CClientEventObj* pClientEvent	= NULL;
					//dwNetID							= pMsg->pSocket->m_dwNetID;
					// 接收使用者定義的新事件
					//CClientEventObj* pNewEvent = ((CHostEventObj*)pEvent)->OnNewConnection( pMsg->m_dwNewConnectionNetID );

					//if( pEvent = GetEvent( dwNetID ) )
					//	pClientEvent	= ((CHostEventObj*)pEvent)->OnAccept( pMsg->MsgAccept.pAcceptSocket->m_dwNetID );

					//m_mapEvent[ pMsg->MsgAccept.pAcceptSocket->m_dwNetID ] = pClientEvent;

					// 發送系統封包, 告知 Client 連線, 並給予認證碼
					// 發送系統封包, 告知 Client 連線, 並給予認證碼
					if( pSocket->m_emMode == EM_SOCKET_MODE_NORMAL )
					{
						SendConnect( pSocket );
						
					}

					// 通知 Server 訊息
						if( pSocket->m_pEvent )
						{
							pSocket->m_pEvent = pSocket->m_pEvent->OnAccept( pSocket->m_dwNetID );
							pSocket->m_pEvent->OnConnect( pSocket->m_dwNetID );
							SetSocketNoDelay( pSocket->m_dwNetID );
						}



				} break;
		
			case MSG_DISCONNECT:
				{
					// 此時並不一定是真的斷現了. 系統有做延遲處理, 會呼叫 Close 後, 等待一段時間後處理

					if( pSocket->m_emStatus != EM_SOCKET_WAIT_DELETE && pSocket->m_pEvent != NULL )
					{
						if( pSocket->m_bConnectOnce != false )
						{
							pSocket->m_pEvent->OnDisconnect( pSocket->m_dwNetID );
						}						
						pSocket->m_pEvent = NULL;
					}

					//On_Error("Close called from CheckMsg(MSG_DISCONNECT)");
					Close( pSocket->m_dwNetID );

				} break;
			}
		}

		// 釋放訊息
		DeleteMsg( pMsg );
		dwProcTimes++;

	}; //dwTickCount != 15 );

	/*
	dwTime			= GetTickCount() - dwStartTime;

	if( dwTime != 0 && dwProcTimes != 0 )
	{
		// 平均每 DF_NB_AVG_EVENT_MS_TIME ms 處理的次數, 加上平均 DF_NB_AVG_EVENT_MS_TIME ms 處理數度取平均
		m_dwAvgProcEvent = ( m_dwAvgProcEvent + ( ( dwProcTimes * DF_NB_AVG_EVENT_MS_TIME ) / dwTime ) ) / 2;

		if( m_dwAvgProcEvent < 100 )
			m_dwAvgProcEvent = 100;
	}
	*/

	//pvecMsg->clear();

	// 處理時間到, 將資源釋放, 讓系統運作順利
	//m_bEvent = true;
	//SetEvent( m_hMsgEvent );
}


void CNetBridge_Base::CheckPacket				()
{
	CNetSocket* pSocket = NULL;
	DWORD		dwNetID = 0;
	CBuffer*	pBuffer	= NULL;

	for(int i = 0; i < m_vecSocketSize; ++i)
	{
		//m_cs_Socket.Enter();
		{
			pSocket = m_vecSocket[i];
		}
		//m_cs_Socket.Leave();

		if(pSocket)
		{
			//if( pSocket->m_listSendFrame.size() != 0 )
			if( pSocket->m_queueSendFrame.Count() != 0 )
			{
				Post_Send( pSocket );
			}
		}
	}

//	while( m_vecWaitSendSocket.empty() != true )
//	{
//		dwNetID = m_vecWaitSendSocket.front();
//		m_vecWaitSendSocket.erase( m_vecWaitSendSocket.begin() );
	for( unsigned int X = 0 ; X < m_vecWaitSendSocket.size() ; X++ )
	{
		dwNetID = m_vecWaitSendSocket[X];

		pSocket = GetSocket( dwNetID );
		if( pSocket == NULL )
			continue;

		DWORD dwTotalSize		= 0;
		DWORD dwBufferCounter	= (DWORD)pSocket->m_vecWaitToSend.size();
	
		vector< CBuffer* >::iterator it;
		/*
		vector< CBuffer* >::iterator it;
		for( it = pSocket->m_vecWaitToSend.begin(); it != pSocket->m_vecWaitToSend.end(); it++ )
		{
			dwTotalSize += ((CBuffer*)*it)->m_dwTotalSize;
		}
		*/

		//if( dwBufferCounter > 2 || dwTotalSize > 128 )
		if( false )
		{
			// 資料量大於 128 bytes 進行壓縮 or 
			BYTE* ptr	= NULL;
			//pBuffer		= CreateBuffer( dwTotalSize );//, NULL, &ptr );
			pBuffer		= CreatePacketBuffer( dwTotalSize , NULL, &ptr );

			// 加註該封包是打包封
			*((DWORD*)pBuffer->m_pData) |= DF_PTAG_COLLECT;

			ptr = pBuffer->m_pData + sizeof( DWORD );

			/*
			// 複製資料進一個 Buffer
			it = pSocket->m_vecWaitToSend.begin();
			
			while( it != pSocket->m_vecWaitToSend.end() )
			{
				memcpy( ptr, ((CBuffer*)*it)->m_pData, ((CBuffer*)*it)->m_dwTotalSize );
				ptr += ((CBuffer*)*it)->m_dwTotalSize;
				DeleteBuffer( *it );
				it = pSocket->m_vecWaitToSend.erase( it );
				
				pSocket->m_dwSendBuf--;
			}
			*/
			for(  it = pSocket->m_vecWaitToSend.begin()
				; it != pSocket->m_vecWaitToSend.end() 
				; it++ )
			{
				memcpy( ptr, ((CBuffer*)*it)->m_pData, ((CBuffer*)*it)->m_dwTotalSize );
                ptr += ((CBuffer*)*it)->m_dwTotalSize;
                DeleteBuffer( *it );				
				
				pSocket->m_dwSendBuf--;
			}
			pSocket->m_vecWaitToSend.clear();

			pSocket->m_dwSendBuf++;


		
			// 資料量大於 128 bytes 進行壓縮
			
			//if( dwTotalSize > 128 )
			if( false )
			{
				// 推入待壓縮佇列後, 再由 Thread 發出封包
				Post_Compress( pSocket, pBuffer );
			}
			else
			{
				// 發出封包
				//Post_Send( pSocket, pBuffer );
			}
		}
		else
		{
			// 小封包, 且數量不大於二
			//ocket->m_vecSend.push_back( pBuffer );
			// 複製資料進一個 Buffer
			/*
			it = pSocket->m_vecWaitToSend.begin();
			while( it != pSocket->m_vecWaitToSend.end() )
			{
				// 發出封包
				//pSocket->m_vecSend.push_back( *it );
				Post_Send( pSocket, *it );
				it = pSocket->m_vecWaitToSend.erase( it );				
			}
			*/
			
			for( it = pSocket->m_vecWaitToSend.begin(); it != pSocket->m_vecWaitToSend.end(); it++ )
			{
				//Post_Send( pSocket, *it );
			}
			pSocket->m_vecWaitToSend.clear();
			
			//SendFlush();
		}

	}
	m_vecWaitSendSocket.clear();
	//m_vecWaitSendSocket.push_back( pSocket->m_dwNetID );

}

void CNetBridge_Base::SendFlush()
{

	CNetSocket* pSocket = NULL;
	DWORD		dwNetID = 0;

	// MYTESTCODE

		for(int i = 0; i < m_vecSocketSize; ++i)
		{
			//m_cs_Socket.Enter();
			{
				pSocket = m_vecSocket[i];
			}
			//m_cs_Socket.Leave();
			if(pSocket)
			{
				if( pSocket->m_queueSendFrame.Count() != 0 )
				{
					Post_Send( pSocket );
				}
			}
		}


	/*

	vector< CBuffer* >::iterator it;
	CNetSocket* pSocket = NULL;
	DWORD		dwNetID = 0;

	for( unsigned int X = 0 ; X < m_vecWaitSendSocket.size() ; X++ )
	{
		dwNetID = m_vecWaitSendSocket[X];

		pSocket = GetSocket( dwNetID );
		if( pSocket == NULL )
			continue;

		for( it = pSocket->m_vecWaitToSend.begin();	it != pSocket->m_vecWaitToSend.end();	it++ )
		{
			Post_Send( pSocket, *it );
		}

		pSocket->m_vecWaitToSend.clear();
	}
	*/
}


void CNetBridge_Base::CheckSocket				()
{
	// 檢查有無 ClosingSocket 到時間了
	DWORD dwTick		= GetTickCount();
	DWORD dwCloseTime	= 0;

	CNetSocket* pSocket = NULL;

	//multimap< DWORD , CNetSocket* >::iterator it;

	
	m_cs_Socket.Enter( "CNetBridge_Base::CheckSocket" );
	{	
		vector< CNetSocket* >::iterator it;
		// Wait Close Socket
		it = m_vecWaitCloseSocket.begin();

		DWORD dwTime = GetTickCount();
		while( it != m_vecWaitCloseSocket.end() ) 
		{
			pSocket = *it;
					
			if( ( pSocket->m_pRecvBuff == NULL && pSocket->m_SendBuffer.m_pData == NULL ) || dwTime > pSocket->m_dwTimer )
			{
				//shutdown( pSocket->m_tcp_socket, SD_SEND );
				if( pSocket->m_tcp_socket != INVALID_SOCKET )
				{
					//On_Error("closesocket called from CheckSocket(Iteration)");
					int result = closesocket( pSocket->m_tcp_socket );
					if( result == WSAEWOULDBLOCK )
					{
						it++;
						continue;
					}
					else
					{
						pSocket->m_tcp_socket = INVALID_SOCKET;
					}
				}

				it = m_vecWaitCloseSocket.erase( it );

				// 推入 Delete Socket 佇列中
				//pSocket->m_emStatus = 
				pSocket->m_dwTimer	= dwTime + 1000;
				
				// 若佇列中沒有該 Socket 才推入
				if( find( m_vecWaitDeleteSocket.begin(), m_vecWaitDeleteSocket.end(), pSocket ) == m_vecWaitDeleteSocket.end() )
				{
					m_vecWaitDeleteSocket.push_back( pSocket );		
				}
				

			}
			else
			{
				it++;
			}
			
		}


		//DWORD dwCount;
		it = m_vecWaitDeleteSocket.begin();
		while( it != m_vecWaitDeleteSocket.end() ) 
		{
			pSocket = *it;
			
			if( m_bShutdown )
			{
				DeleteSocket( pSocket->m_dwNetID );
				it = m_vecWaitDeleteSocket.erase( it );
			}
			else
			{
				if( dwTime > pSocket->m_dwTimer )
				{
					// 檢查是否有發送段現訊息
					if( pSocket->m_emStatus != EM_SOCKET_WAIT_DELETE )
					{
						if( pSocket->m_emStatus != EM_SOCKET_WAIT_DELETE && pSocket->m_pEvent != NULL )
						{
							if( pSocket->m_bConnectOnce != false )
							{
								pSocket->m_pEvent->OnDisconnect( pSocket->m_dwNetID );
							}			
							pSocket->m_emStatus = EM_SOCKET_WAIT_DELETE;
						}					
					}

					if( pSocket->m_vecAccept.empty() && pSocket->m_pRecvBuff == NULL && pSocket->m_SendBuffer.m_pData == NULL )
					{
						DWORD dwDelayTime = abs((long) (dwTime - pSocket->m_dwTimer) );

						if( dwDelayTime > 60000 )
						{
							MsgOutPut( 5, "[NET] Timeout socket be deleted!! NetID[ %d ], Time[ %d ]", pSocket->m_dwNetID, dwDelayTime );
						}

						DeleteSocket( pSocket->m_dwNetID );
						it = m_vecWaitDeleteSocket.erase( it );
						continue;
					}
					else
					{
						DWORD dwDelayTime = abs((long) (dwTime - pSocket->m_dwTimer) );

						if( dwDelayTime > 300000 ) 
						{
							int iAcceptCheck	= 0;
							int	iRecvCheck		= 0;
							int	iSendCheck		= 0;
							
							if( pSocket->m_vecAccept.empty() )	iAcceptCheck = 1;	else iAcceptCheck = 0;
							if( pSocket->m_pRecvBuff == NULL )	iRecvCheck = 1;		else iRecvCheck = 0;
							if( pSocket->m_SendBuffer.m_pData == NULL ) iSendCheck = 1;		else iSendCheck = 0;

							MsgOutPut( 5, "[NET] Delete scoket timeout! reset and wait! NetID[ %d ], Time[ %d ], Accept[%d], Recv[%d], Send[%d]", pSocket->m_dwNetID, dwDelayTime, iAcceptCheck, iRecvCheck, iSendCheck );
							pSocket->m_dwTimer = dwTime + 60000;
						}

					}
				}
				
				it++;		
			}

	//		if( it == m_vecWaitDeleteSocket.end() )
	//			OutputDebugString( "\n[ Leave ] m_vecWaitDeleteSocket Loop" );
		}
	}
	m_cs_Socket.Leave( "CNetBridge_Base::CheckSocket");

		// 檢查 KeepAlive
		// 檢查 Socket respond time
		//----------------------------------------------------------			
			if( dwTick >= m_dwCheckRespondTime )
			{

				DWORD dwAliveCheckCount = ( m_dwKeepAliveTime / 1000 );
				//if( m_bCheckRespondTime != false )	// Check if setting to allow check respond time
				{
					for( int i = 0; i < m_vecSocketSize; ++i )
					{
						CNetSocket*		pSocket		= m_vecSocket[i];
						
						if( pSocket != NULL && pSocket->m_emStatus == EM_SOCKET_CONNECTED && pSocket->m_bConnectOnce != false && pSocket->m_emMode != EM_SOCKET_MODE_TELNET )
						{
							// Get last checktime
								//DWORD dwLastCheckTime	= m_dwCheckRespondTime - 10000;
							// Recaluate respond time, this part is desing for tcp connect broke, but tcp didnt get disconnect

								if( pSocket->m_bRespond == false )
								{
									// Cause last checkPacket didnt come back, so we dont send another. Beasuse tcp packet should be return if everything is okay
									DWORD dwDuring					= (DWORD) abs( ( (int)dwTick - (int)pSocket->m_dwLastRequestTick  ) );
									pSocket->m_dwRespondTime		= ( pSocket->m_dwRespondTime + ( dwDuring / 2 ) );
									pSocket->m_bRespond				= false;
									pSocket->m_dwRespondCheck++;
									SendAliveRequest( pSocket );
								}
								else
								{
									// Normal
									pSocket->m_dwLastRequestTick	= dwTick;
									pSocket->m_bRespond				= false;
									SendAliveRequest( pSocket );
								}


							// Check if we did kick lagger
								//if(  pSocket->m_dwRespondTime > m_dwKeepAliveTime && pSocket != NULL )
								if( pSocket->m_dwRespondCheck > dwAliveCheckCount && pSocket != NULL )
								{

									char szIP[256];
									ConvertIPtoString( pSocket->m_dwIP, szIP );

									if( m_bCheckRespondTime != false )
									{
										MsgOutPut( 5, "[NetBridge] [ %d ] pSocket->m_dwRespondTime is reach limit [ %d ]/[ %d ], IP[ %s ], and it would be closed!", pSocket->m_dwNetID, pSocket->m_dwRespondTime, m_dwKeepAliveTime, szIP );
										Close( pSocket->m_dwNetID );	// Kick lagger
									}
									else
									{
										MsgOutPut( 5, "[NetBridge] [ %d ] pSocket->m_dwRespondTime is reach limit! [ %d ]/[ %d ], IP[ %s ]", pSocket->m_dwNetID, pSocket->m_dwRespondTime, m_dwKeepAliveTime, szIP );
									}									
								}

								
								if( pSocket->m_SendQueueSize > m_dwSendBuffLimit )
								{								
									char szIP[256];
									ConvertIPtoString( pSocket->m_dwIP, szIP );

									if( m_bSendBufferLimit != false )
									{
										MsgOutPut( 5, "[NetBridge] [ %d ] pSocket->m_iSendQueueBytes is reach limit [ %d ]/[ %d ], IP[ %s ], and it would be closed!", pSocket->m_dwNetID, pSocket->m_iSendQueueBytes, m_dwSendBuffLimit, szIP  );
										Close( pSocket->m_dwNetID );	// Buffer reach the queue limit, fast proxy would be 4mb, file transfter server would make it like 20-100mb										
									}
									else
									{
										MsgOutPut( 5, "[NetBridge] [ %d ] pSocket->m_iSendQueueBytes is reach limit [ %d ]/[ %d ], IP[ %s ]", pSocket->m_dwNetID, pSocket->m_iSendQueueBytes, m_dwSendBuffLimit, szIP );
									}
								}

						}
					}
				}

				m_dwCheckRespondTime = dwTick + 10000;

			}
}

CBuffer* CNetBridge_Base::CreateBuffer(DWORD dwSize)
{
	//return m_buffer.Apply( dwSize );
	//return new CBuffer( dwSize );//BYTE[ dwSize ];
	//m_cs_buffer.Enter( "CNetBridge_Base::CreateBuffer" );
		CBuffer* pBuffer = new CBuffer( dwSize );
		pBuffer->m_pData = m_bufferManager.Apply( dwSize );
	//m_cs_buffer.Leave( "CNetBridge_Base::CreateBuffer" );

#if NET_BRIDGE_BASE_BUFFER_CREATE_AND_DESTORY_DEBUG_PRINT
    char szDebug[255+1];
    _snprintf(szDebug, 255, "CNetBridge_Base::CreateBuffer(%u) - 0x%p\n", dwSize, pBuffer);
    OutputDebugString(szDebug);
#endif

	return pBuffer;
}

void			CNetBridge_Base::DeleteBuffer	( CBuffer* pBuffer )
{
#if NET_BRIDGE_BASE_BUFFER_CREATE_AND_DESTORY_DEBUG_PRINT
    if (pBuffer != NULL)
    {
        char szDebug[255+1];
        _snprintf(szDebug, 255, "CNetBridge_Base::DeleteBuffer(0x%p) - Size = %u/%u\n",
            pBuffer, pBuffer->m_dwSize, pBuffer->m_dwTotalSize);
        OutputDebugString(szDebug);
    }
#endif

    if( pBuffer->m_pData != NULL )
    {	
        //m_cs_buffer.Enter( "CNetBridge_Base::DeleteBuffer" );
            m_bufferManager.Delete( pBuffer->m_pData );
        //m_cs_buffer.Leave( "CNetBridge_Base::DeleteBuffer" );
        pBuffer->m_pData = NULL;
    }

    delete pBuffer;

    //delete pBuffer;
}

LONG CNetBridge_Base::GetBytesSend	()
{
	return m_bytesSend;
}

LONG CNetBridge_Base::GetBytesRecv	()
{
	return m_bytesRecv;
}

void CNetBridge_Base::ReSetSendCount	()
{
	InterlockedExchange( &m_bytesSend, 0 );
}

void CNetBridge_Base::ReSetRecvCount	()
{
	InterlockedExchange( &m_bytesRecv, 0 );
}

void CNetBridge_Base::On_Error( char *format, ... )
{
	// NOTHING; FUCK 
	va_list vl;
	char dbgbuf[2048];
	va_start(vl, format);
	wvsprintf(dbgbuf, format, vl);
	va_end(vl);
	char szOutput[2048];
	wsprintf( szOutput, "%s\n" , dbgbuf );

	//OutputDebugString(szOutput);
//	printf(szOutput);
}

void CNetBridge_Base::PostMsg ( CEventMsg* pMsg )
{
	m_cs_MessageAndEvent.Enter( "CNetBridge_Base::PostMsg" );
	{
		//pMsg->pSocket->m_pvecMsg->push_back( pMsg );
		pMsg->pSocket->m_pvecMsg->Queue( pMsg );
		
		m_bEvent = true;
		//SetEvent( m_hMsgEvent );
		SetEvent( m_pNetMainEvent );	
	}
	m_cs_MessageAndEvent.Leave( "CNetBridge_Base::PostMsg" );
}

void CNetBridge_Base::MsgAccept ( CNetSocket* pAcceptSocket )
{
	CEventMsg* pMsg = CreateMsg( MSG_ACCEPT, pAcceptSocket );
	pMsg->MsgAccept.pAcceptSocket	= pAcceptSocket;
	PostMsg( pMsg );
}


void CNetBridge_Base::MsgRecv		( CNetSocket* pSocket, DWORD dwDataSize, BYTE* pData, BYTE* pPacketData )
{
	CEventMsg* pMsg  = CreateMsg( MSG_RECV, pSocket );
	
	//pMsg->MsgRecv.pBuffer		= pBuffer;
	pMsg->MsgRecv.pData			= pData;
	pMsg->MsgRecv.dwDataSize	= dwDataSize;
	pMsg->MsgRecv.pPacket		= pPacketData;				

	PostMsg( pMsg );

}

void CNetBridge_Base::MsgError		( CNetSocket* pSocket, DWORD dwErrorID )
{
	CEventMsg* pMsg = CreateMsg( MSG_ERROR, pSocket );

	pMsg->MsgError.dwErrorID	= dwErrorID;

	PostMsg( pMsg );
}

void CNetBridge_Base::MsgConnect	( CNetSocket* pSocket )
{
	CEventMsg* pMsg = CreateMsg( MSG_CONNECT, pSocket );	
	PostMsg( pMsg );
}

void CNetBridge_Base::MsgConnectFailed	( CNetSocket* pSocket )
{
	CEventMsg* pMsg = CreateMsg( MSG_CONNECT_FAILED, pSocket );
	PostMsg( pMsg );
}

//map< int, int  > mapdebug;

void CNetBridge_Base::MsgDisconnect	( CNetSocket* pSocket )
{
	
/*
	if( mapdebug.find( pSocket->m_dwNetID ) != mapdebug.end() )
	{
		int a = 3;
	}
	else
	{
		mapdebug[ ( pSocket->m_dwNetID ) ] = 0;

	}
*/


	CEventMsg* pMsg = CreateMsg( MSG_DISCONNECT, pSocket );

	PostMsg( pMsg );
}


int	CNetBridge_Base::Connect ( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext )
{
	if( pEventObj == NULL )
		return NB_ERR;

	// Create Socket
		CNetSocket* pSocket		= CreateSocket(); // true, NULL );
		
		pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		pSocket->m_emAuthorize	= EM_AUTHORIZE_WAIT_AUTHORIZE;






	// Prepre Socket Address
		SOCKADDR_IN	sa;
		memset( &sa, 0, sizeof( SOCKADDR_IN ) );
		sa.sin_family		= AF_INET;
		sa.sin_addr.s_addr	= dwIP;
		sa.sin_port 		= htons( (WORD)wPort );

	// Tring to connect
		int iReturn			= WSAConnect( pSocket->m_tcp_socket, (SOCKADDR *)&sa, sizeof( SOCKADDR ), NULL, NULL, NULL, NULL );

		if( iReturn == SOCKET_ERROR )
		{
			// 連線失
			iReturn = WSAGetLastError();
			//pEventObj->OnConnectFailed( iReturn );
			//On_Error("DeleteSocket called from Connect");
			//DeleteSocket( pSocket->m_dwNetID );
			Close( pSocket->m_dwNetID );
			return -1;
		}
		
	// Set Keep alive
		//SetKeepAlive( pSocket );

		pSocket->m_emStatus	= EM_SOCKET_CONNECTED;
	// Connected!! Create event and msg
		pSocket->m_pEvent = pEventObj;

	// 暫時不發訊息通知 Client, 而等到 Server 發回認證訊息回來後, 才通知 Client 
		//MsgConnect( pSocket );

		return pSocket->m_dwNetID;

	// 連線成, 準備收發所須要的事件和執行緒

/* OVERLAPPED 用的
	DWORD hID = 0;

	pSocket->m_overlapped_Recv.hEvent	= WSACreateEvent();	// Create 出來的 Event 是 Non-Signaled 狀態
	pSocket->m_overlapped_Send.hEvent	= WSACreateEvent();	// Create 出來的 Event 是 Non-Signaled 狀態

	pSocket->m_thread_Send				= CreateThread( NULL, 0, Thread_Send,	pSocket, 0, &hID );
	pSocket->m_thread_Recv				= CreateThread( NULL, 0, Thread_Recv,	pSocket, 0, &hID );
*/

}

DWORD	CNetBridge_Base::GetTotalSocket			()
{
	DWORD dwSize = 0;
	m_cs_Socket.Enter( "CNetBridge_Base::GetTotalSocket" );
	{
		dwSize = m_vecSocketSize - m_unusedNetIDs.Count();
	}
	m_cs_Socket.Leave( "CNetBridge_Base::GetTotalSocket" );
	return dwSize;
}

CBuffer*	CNetBridge_Base::CreatePacketBuffer		( DWORD dwSize, PVOID pData, BYTE** pOffset )
{
	DWORD dwPacketSize = dwSize + ( sizeof( DWORD ) );

	CBuffer* pBuffer	= CreateBuffer( dwPacketSize );
	
	BYTE* ptr			= pBuffer->m_pData;

	memcpy( ptr, &dwPacketSize, sizeof( DWORD ) );

	if( pData != NULL )
	{
		ptr += sizeof( DWORD );
		memcpy( ptr, pData, dwSize );
	}

	if( pOffset != NULL )
	{
		*pOffset = ptr;
	}

	return pBuffer;
}

bool CNetBridge_Base::CheckCompress			( CBuffer* pBuffer )
{
	return (( *pBuffer->m_pData & 0x80000000 ) != 0 );
}

void CNetBridge_Base::Authorize				( CNetSocket* pSocket, CNetSocket* pAcceptSocket )
{

	Struct_PacketAuthorize Packet;
	
	Packet.AuthorizeIndex	= 0;
	Packet.IsCompress		= FALSE;
	Packet.IsEncryption		= FALSE;
	
	if( pSocket->m_IsEncryption != false )
	{
		// 根據資料發給 Client 一個 Authorize ID
		// 這裡之後應該要改成用 RANDOM 從 Authorize Key List 中挑一個 index 發給 Client , 但為了測試方便暫不實作
		Packet.AuthorizeIndex	= 0;//g_authorize_key[0];
	}

	Packet.IsEncryption	= pSocket->m_IsEncryption;
	Packet.IsCompress		= pSocket->m_IsCompress;

	CBuffer* pBuffer = CreatePacketBuffer( sizeof( Packet ), &Packet, NULL );
	
	Post_Compress( pAcceptSocket, pBuffer );
}

void CNetBridge_Base::GetConnectInfo		( DWORD dwNetID, DWORD* pdwIP, WORD* pwPort )
{
//	map< DWORD , CNetSocket* > ::iterator it;
	CNetSocket* pSocket = NULL;

//	m_cs_Socket.Enter();		
	{
		pSocket = GetSocket(dwNetID);
		if(pSocket)
		{

				if( pdwIP != NULL )
				{
					*pdwIP = pSocket->m_dwIP;
				}

				if( pwPort != NULL )
				{
					*pwPort = pSocket->m_wPort;
				}
		}
	}
//	m_cs_Socket.Leave();
}
//-----------------------------------------------------------------------
void CNetBridge_Base::SetCheckRespond( bool bEnable )
{
	m_bCheckRespondTime		= bEnable;
}
//-----------------------------------------------------------------------
void CNetBridge_Base::SetKeepAlive( bool bEnable, DWORD dwTime )
{
	m_dwKeepAliveTime	= dwTime;

	if( bEnable == false )
		m_dwKeepAliveTime = 0;
}
//-----------------------------------------------------------------------
void CNetBridge_Base::SetSendBufferLimit	( bool bEnable, DWORD dwLimit )
{
	m_bSendBufferLimit	= bEnable;
	m_dwSendBuffLimit	= dwLimit;
}
//-----------------------------------------------------------------------
void CNetBridge_Base::MsgOutPut			( int lv, char* format , ... )
{

	m_cs_MessageAndEvent.Enter("CNetBridge_Base::MsgOutPut");

	char	_Buf[1024];
	va_list marker =(char*)&format + sizeof(format);
	vsprintf( _Buf , format , marker );
	if( m_pfOutPut )
	{

		m_pfOutPut( lv, _Buf );	
	}

	//OutputDebugStr( _Buf );

	m_cs_MessageAndEvent.Leave("CNetBridge_Base::MsgOutPut");

	#ifdef _NB_DEBUG_FILELOG

		

		


	#endif

}

void CNetBridge_Base::GetRespondInfo		( char* pszOut )
{
	char szPing[4096];	
	float	fRespond[10];
	
	DWORD	dwTotal = 0;

	for( int i = 0; i < 10; i++ )
	{
		dwTotal += m_Respond[i];
	}

	if( dwTotal != 0 )
	{
		for( int i = 0; i < 10; i++ )
		{
			fRespond[i] = (((float)m_Respond[i]) / (float)dwTotal) * (float)100;
		}
	}
	else
	{
		for( int i = 0; i < 10; i++ )
		{
			fRespond[i] = 0;
		}
	}

	sprintf( szPing, "0-100[ %.2f ], 100-200[ %.2f ], 200-300[ %.2f ], 300-400[ %.2f ], 400-500[ %.2f ]\n500-600[ %.2f ], 600-700[ %.2f ], 700-800[ %.2f ], 800-900[ %.2f ], above 900[ %.2f ]",
		fRespond[0], fRespond[1], fRespond[2], fRespond[3], fRespond[4], fRespond[5], fRespond[6], fRespond[7], fRespond[8], fRespond[9] );

	strcpy( pszOut, szPing );

	for( int i=0; i<10; i++ )
	{
		InterlockedExchange( &(m_Respond[i]), 0 );
	}
}


void CNetBridge_Base::GetStatusInfo		( char* pszOut )
{
	char szOut[4096];


//#ifdef DF_PACKET_LOG
//	sprintf( szOut, "Connect( %d )s, Disconnecting( %d )s, WaitEcho( %d )p", m_vecSocketSize - m_unusedNetIDs.Count(), m_mapClosingSocket.size(), m_dwPacketLog );
//#else
//	sprintf( szOut, "Connect( %d )s, Disconnecting( %d )s", m_vecSocketSize - m_unusedNetIDs.Count(), m_mapClosingSocket.size() );
//#endif

	sprintf( szOut, "MinFlushTime[ %d ], MaxFlushTime[ %d ]\nMinEvent[ %d ], MaxEvent[ %d ]\nminSendCountPerSec[ %d ], maxSendCountPerSec[ %d ]\nminSendBytesPerSec[ %.2f ], maxSendBytesPerSec[ %.2f ]\nminRecvCountPerSec[ %d ], maxRecvCountPerSec[ %d ]\nminRecvBytesPerSec[ %.2f ], maxRecvBytesPerSec[ %.2f ]",
		m_minFlushTime, m_maxFlushTime, m_minEvent, m_maxEvent, m_minSendCountPerSec, m_maxSendCountPerSec, ((float)m_minSendBytesPerSec/1024), ((float)m_maxSendBytesPerSec/1024), m_minRecvCountPerSec, m_maxRecvCountPerSec, ((float)m_minRecvBytesPerSec/1024), ((float)m_maxRecvBytesPerSec/1024), m_minSecSendThread, m_maxSecSendThread );
	strcpy( pszOut, szOut );


	// Reset
	m_minFlushTime			= 0;
	m_maxFlushTime			= 0;

	m_minEvent				= 0;
	m_maxEvent				= 0;

	InterlockedExchange( &m_SendCount, 0 );
	m_minSendCountPerSec	= 0;
	m_maxSendCountPerSec	= 0;

	InterlockedExchange( &m_SendBytes, 0 );
	m_maxSendBytesPerSec	= 0;
	m_maxSendBytesPerSec	= 0;

	InterlockedExchange( &m_RecvCount, 0 );
	m_minRecvCountPerSec	= 0;
	m_maxRecvCountPerSec	= 0;

	InterlockedExchange( &m_RecvBytes, 0 );
	m_maxRecvBytesPerSec	= 0;
	m_maxRecvBytesPerSec	= 0;

}

bool CNetBridge_Base::Shutdown ()
{
	bool bReturn = false;
	// 關畢所有連線

		map< DWORD, CNetSocket* >::iterator it;
		CNetSocket*	pSocket = NULL;

		if( m_bShutdown == false )
		{
			m_bShutdown = true;
			// 將所有作用中的 Socket 關畢
			m_cs_Socket.Enter( "CNetBridge_Base::Shutdown" );

			{
				for(int i = 0; i < m_vecSocketSize; ++i)
				{
					pSocket = m_vecSocket[i];
					if(pSocket)
					{
						pSocket->m_cs_SocketIO.Enter( "CNetBridge_Base::Shutdown" );

							pSocket->m_pEvent	= NULL;

							//shutdown( pSocket->m_tcp_socket,  SD_SEND );
							closesocket( pSocket->m_tcp_socket );
						pSocket->m_cs_SocketIO.Leave( "CNetBridge_Base::Shutdown" );
					}
				}
			}

			m_cs_Socket.Leave( "CNetBridge_Base::Shutdown" );
		}

	// 持續 Flush 直到所有連線中斷

			m_cs_Socket.Enter( "CNetBridge_Base::Shutdown" );
			{
				if(m_vecSocketSize == m_unusedNetIDs.Count())
					bReturn = true;
			}
			m_cs_Socket.Leave( "CNetBridge_Base::Shutdown" );

	return bReturn;

}

void	CNetBridge_Base::CalSendRecvBytes	( )
{
	while( 1 )
	{
		int time = clock();
		SockSendRevInfoStruct Info;
		if( time - m_LastCalSendRevTime > 1000 )
		{
			m_LastCalSendRevTime+= 1000;
			Info.BytesSend = GetBytesSend();
			Info.BytesRevc  = GetBytesRecv();
			Info.PecketSend	= GetPacketSend();
			Info.PecketRevc = GetPacketRecv();
			ReSetSendCount();
			ReSetRecvCount();
			ReSetPacketSendCount();
			ReSetPacketRecvCount();

			m_SockSendRevInfo.push_front( Info );
			if( m_SockSendRevInfo.size() > 60*60 )
				m_SockSendRevInfo.pop_front();
		}
		else
		{
			break;
		}
	}
}

LONG	CNetBridge_Base::GetBytesSend		( int Second )
{
	LONG Ret = 0;
	if( m_SockSendRevInfo.size() < (unsigned)Second )
		Second = (int)m_SockSendRevInfo.size();

	for( int i = 0 ; i < Second ; i++ )
	{	
		Ret += m_SockSendRevInfo[i].BytesSend;
	}
	return Ret;
}
LONG	CNetBridge_Base::GetBytesRecv		( int Second )
{
	LONG Ret = 0;
	if( m_SockSendRevInfo.size() < (unsigned)Second )
		Second = (int)m_SockSendRevInfo.size();

	for( int i = 0 ; i < Second ; i++ )
	{	
		Ret += m_SockSendRevInfo[i].BytesRevc;
	}
	return Ret;
}
LONG	CNetBridge_Base::GetPacketsSend		( int Second )
{
	LONG Ret = 0;
	if( m_SockSendRevInfo.size() < (unsigned)Second )
		Second = (int)m_SockSendRevInfo.size();

	for( int i = 0 ; i < Second ; i++ )
	{	
		Ret += m_SockSendRevInfo[i].PecketSend;
	}
	return Ret;
}
LONG	CNetBridge_Base::GetPacketsRecv		( int Second )
{
	LONG Ret = 0;
	if( m_SockSendRevInfo.size() < (unsigned)Second )
		Second = (int)m_SockSendRevInfo.size();

	for( int i = 0 ; i < Second ; i++ )
	{	
		Ret += m_SockSendRevInfo[i].PecketRevc;
	}
	return Ret;
}

void CNetBridge_Base::MsgSystem( CNetSocket* pSocket, Struct_PacketHeader* pHeader, BYTE* pData, DWORD dwDataSize )
{
	CEventMsg* pMsg  = CreateMsg( MSG_SYSTEM, pSocket );

	//pMsg->MsgRecv.pBuffer		= pBuffer;
	pMsg->MsgSystem.pHeader		= pHeader;
	pMsg->MsgSystem.pData		= pData;
	pMsg->MsgSystem.dwDataSize	= dwDataSize;

	PostMsg( pMsg );

}

DWORD CNetBridge_Base::GetClientRespond	( DWORD dwNetID )
{
	CNetSocket* pSocket = GetSocket(dwNetID);

	if( pSocket )
		return pSocket->m_dwRespondTime;
	else
		return 10000;
}

#pragma managed