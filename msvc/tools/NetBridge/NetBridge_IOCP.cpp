#pragma warning (disable:4949)
#include "NetBridge_IOCP.h"

#pragma unmanaged

//HANDLE	CNetBridge_IOCP::m_CompletionPort = NULL;
//HANDLE	CNetBridge_IOCP::m_CompThreads[ DF_NB_MAX_COMPLETION_THREAD_COUNT ];


struct Struct_NB_ThreadInfo
{
	Struct_NB_ThreadInfo()
	{
		pBridge		= NULL;
		iThreadID	= 0;
	}

	CNetBridge_IOCP*	pBridge;
	int					iThreadID;
};


//-----------------------------------------------------------------
CNetBridge_IOCP::CNetBridge_IOCP(void)
{
	m_CompletionPort	= NULL;
	ZeroMemory( m_CompThreads, sizeof( m_CompThreads ) );

	m_pFunCompress		= NULL;
	m_pFunDecompress	= NULL;

#if NET_BIRDGE_IOCP_DEBUG_PRINT
    OutputDebugString("CNetBridge_IOCP::CNetBridge_IOCP()\n");
#endif
}
//-----------------------------------------------------------------
CNetBridge_IOCP::~CNetBridge_IOCP(void)
{
    // Post a null buffer to thread, it would cause thread to close

#if NET_BIRDGE_IOCP_DEBUG_PRINT
    OutputDebugString("CNetBridge_IOCP::~CNetBridge_IOCP()\n");
#endif
}
//-----------------------------------------------------------------
int	CNetBridge_IOCP::Init ( int iNumThread )
{
	int iReturn = NB_OK;
	if( ( iReturn = CNetBridge_Base::Init( iNumThread ) ) != NB_OK )
	{
		return iReturn;
	}

	// 嘗試去 Create IOCP Port
	if( m_CompletionPort == NULL )
	{
		m_CompletionPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)NULL, 0 );
		if( m_CompletionPort == NULL )
		{
			return NB_ERR_UNABLE_CREATE_IOCP;
		}

		SYSTEM_INFO      sysinfo;

		// Find out how many processors are on this system
			GetSystemInfo( &sysinfo );

			if (sysinfo.dwNumberOfProcessors > DF_NB_MAX_COMPLETION_THREAD_COUNT)
			{
				sysinfo.dwNumberOfProcessors = DF_NB_MAX_COMPLETION_THREAD_COUNT;
			}

			ZeroMemory( m_CompThreads, sizeof( m_CompThreads ) );


		// Create the worker threads to service the completion notifications
			//for( int i=0; i < (int)sysinfo.dwNumberOfProcessors ; i++ )

			for( int i=0; i < 2; i++ )
			{
				Struct_NB_ThreadInfo *pThreadInfo = new Struct_NB_ThreadInfo;
				
				pThreadInfo->pBridge	= this;
				pThreadInfo->iThreadID	= i;

				//m_CompThreads[i] = CreateThread( NULL, 0, Thread_Completion, (LPVOID)m_CompletionPort, 0, NULL );

				m_CompThreads[i] = CreateThread( NULL, 0, Thread_Completion, (LPVOID)pThreadInfo, 0, NULL );

				if ( m_CompThreads[i] == NULL )
				{
					return NB_ERR_UNABLE_CREATE_IOCPTHREAD;
				}
			}
	}
	return iReturn;
}
//-----------------------------------------------------------------
int	CNetBridge_IOCP::Host ( DWORD dwIP , WORD wPort, CEventObj* pEventObj, BOOL bEncryption, BOOL bCompress, BOOL bTelnet, PVOID pContext  )
{
	// 有 MainThread 呼叫

	if( pEventObj == NULL )
		return NB_ERR;

	int		rc;

	// Create socket
	DWORD		dwNetID;
	//CNetSocket* pSocket = CreateSocket( true, NULL, &dwNetID );
	CNetSocket* pSocket = CreateSocket();

	

	dwNetID					= pSocket->m_dwNetID;
	pSocket->m_IsCompress	= bCompress;
	pSocket->m_IsEncryption	= bEncryption;

	if( bTelnet != false )
	{
		pSocket->m_emMode		= EM_SOCKET_MODE_TELNET;
	}

	pSocket->m_pContext		= pContext;

	// Link the event
	pSocket->m_pEvent = pEventObj;
	//m_mapEvent[ dwNetID ] = pEventObj;

	// Create the tcp socket
	pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

//	printf( "NB: Create Accept TCP ( %d )\n", pSocket->m_tcp_socket );

	HANDLE		hrc			= CreateIoCompletionPort( (HANDLE)pSocket->m_tcp_socket, m_CompletionPort, (ULONG_PTR)pSocket, 0 );

	SetSocketNoDelay( pSocket->m_dwNetID );

	// Bind the socket
	SOCKADDR_IN	sa;
	memset( &sa, 0, sizeof( SOCKADDR_IN ) );
	sa.sin_family		= AF_INET;

	if( dwIP != 0 )
		sa.sin_addr.s_addr	= dwIP;
	else
		sa.sin_addr.s_addr = INADDR_ANY;

	sa.sin_port 		= htons( wPort );

	bind( pSocket->m_tcp_socket, (SOCKADDR *) &sa, sizeof(SOCKADDR));

	// check if now it's iocp mode, then associate it to completion port
	// 並將 pSocket 當成 key 傳入
	// and make pSocket be key to turn in


	DWORD  hID			 = 0;

	// 測試 AcceptEx 的效率

#ifndef DF_TEST_ACCEPTEX

	listen( pSocket->m_tcp_socket , 1 );
	pSocket->m_thread_Accept = CreateThread( NULL, 0, Thread_Accept,	pSocket, 0, &hID );

#else

	//EM_ACCEPT
	GUID        guidAcceptEx				= WSAID_ACCEPTEX;
	GUID		guidGetAcceptExSockaddrs	= WSAID_GETACCEPTEXSOCKADDRS;
	DWORD       dwbytes						= 0;

	// 取出 AccectEx 的函式指標
	// Need to load the Winsock extension functions from each provider
	//    -- e.g. AF_INET and AF_INET6. 
	rc = WSAIoctl	(	
		pSocket->m_tcp_socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidAcceptEx,
		sizeof( guidAcceptEx ),
		&pSocket->m_pfnAcceptEx,
		sizeof( pSocket->m_pfnAcceptEx ),
		&dwbytes,
		NULL,
		NULL
		);

	if (rc == SOCKET_ERROR)
	{
		On_Error( "NB:Host:WSAIoctl: SIO_GET_EXTENSION_FUNCTION_POINTER failed: %d\n", WSAGetLastError() );
		return NB_ERR;
	}

	rc = WSAIoctl	(
		pSocket->m_tcp_socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidGetAcceptExSockaddrs,
		sizeof( guidGetAcceptExSockaddrs ),
		&pSocket->m_pfnGetAcceptExSockaddrs,
		sizeof( pSocket->m_pfnGetAcceptExSockaddrs ),
		&dwbytes,
		NULL,
		NULL
		);

	if (rc == SOCKET_ERROR)
	{
		On_Error( "NB:Host:WSAIoctl: SIO_GET_EXTENSION_FUNCTION_POINTER failed: %d\n", WSAGetLastError() );
		return NB_ERR;
	}

	// 令之成為 listen mode
	listen( pSocket->m_tcp_socket , 1 );

	// Post overlapped accept on a listening socket
	// 根據 DF_NB_OVERLAPPEDCOUNTER 作出多個 Socket 預備成為 Accept 來做為連線使用

	CBuffer* pBuffer = NULL;

	//for( int i = 0; i < DF_NB_OVERLAPPEDCOUNTER; i++ )
	for( int i = 0; i < 12; i++ )
	{
		pBuffer = CreateBuffer( DF_NB_PACKETBUFFERSIZE );
		pSocket->m_vecAccept.push_back( pBuffer );

		Post_Accept( pSocket, pBuffer );
	}

#endif

	return dwNetID;
}

//-----------------------------------------------------------------
// 刪掉 Socket 流程
// 1. Client / Server 斷掉或呼叫 Close. 
// 2. 若呼叫 Close 則會進入 WaitClose 狀態. 給予 5 秒 Send 時間, 把封包發完
// 3. 5 秒到了之後, 切換成 Closing 狀態, 呼叫 closesocket api , 讓系統把 buff 吐回來, 直到 buff 全回來了, 或者是等待時間到了.
// 4. 若時間到 buff 還沒回來, 則將 Socket 推到 Norespond 佇列中延長處理, 並將 Socket 狀太切成 WaitDelete
// 5. 若 buff 全回來了, 則刪掉 Socket, 回收利用, 或者是直接釋放記憶體
//-----------------------------------------------------------------

DWORD WINAPI CNetBridge_IOCP::Thread_Completion	( PVOID pParam )
{
	Struct_NB_ThreadInfo*	pThreadInfo		= NULL;
	HANDLE					CompletionPort;
	OVERLAPPED				*pOverlapped	=NULL;		// Pointer to overlapped structure for completed I/O
	//HANDLE				CompletionPort;				// Completion port handle
	DWORD					dwBytesTransfered = 0;			// Number of bytes transfered
	int						rc;
	CNetSocket*				pSocket			= NULL;
	CBuffer*				pBuffer			= NULL;
	CNetBridge_IOCP*		pNet			= NULL;
	int						iError			= 0;
	CNetBridge_IOCP*		pBridge			= NULL;
	int						iThreadID		= 0;

	//CompletionPort = (HANDLE)pParam;

	pThreadInfo		= (Struct_NB_ThreadInfo*)pParam;
	
	pBridge			= pThreadInfo->pBridge;
	iThreadID		= pThreadInfo->iThreadID;

	CompletionPort	= pBridge->m_CompletionPort;

	delete pThreadInfo;
	




	int CountTimes = 0;

	//try
	{
		while (1)
		{
			//Sleep(1);
			//error = NO_ERROR;
			rc		= GetQueuedCompletionStatus(	CompletionPort,	&dwBytesTransfered, (PULONG_PTR)&pSocket,	&pOverlapped, 1 );

			if( rc != ERROR_SUCCESS )
			{
				if( pOverlapped == NULL )
				{
					// System require to release thread;
						pBridge->m_CompThreads[ iThreadID ] = NULL;
						return 0;
				}
				

				pBuffer	= CONTAINING_RECORD( pOverlapped, CBuffer, m_overlapped );
				pNet	= (CNetBridge_IOCP*)pSocket->m_pNetBridge;

				pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::Thread_Completion" );

				//if( pSocket->m_emStatus != EM_SOCKET_CLOSING && rc != ERROR_SUCCESS && dwBytesTransfered != 0 )
				// 反推回去原本的資料結構....從書上操來的作法, 真是可怕
				pBuffer	= CONTAINING_RECORD( pOverlapped, CBuffer, m_overlapped );
				pNet	= (CNetBridge_IOCP*)pSocket->m_pNetBridge;

				switch( pBuffer->m_emMode )
				{
				case EM_ACCEPT:
					{
						pNet->Handle_Accept	( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					} break;
				case EM_RECV:
					{
						pNet->Handle_Recv	( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					} break;
				case EM_SEND:
					{
						pNet->Handle_Send	( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					} break;
				case EM_COMPRESS:
					{
						pNet->Handle_Compress( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					} break;
				case EM_CONNECT:
					{
						pNet->Handle_Connect( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					} break;
				}

				pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::Thread_Completion" );
			}
			else
			{
				iError = WSAGetLastError();

				if( iError != WAIT_TIMEOUT )				
				{
					// TODO: 如果只有 Buff 的話. Socket 是空的也要回收

					if( pOverlapped == NULL )
					{
						// System require to release thread;
						pBridge->m_CompThreads[ iThreadID ] = NULL;
						return 0;
					}

					pBuffer	= CONTAINING_RECORD( pOverlapped, CBuffer, m_overlapped );

					if( pSocket == NULL || pBuffer == NULL )
						continue;

					//if( WSAWaitForMultipleEvents( 1, &pSocket->m_wsaEvent, false, 0, false ) == WSA_WAIT_EVENT_0 )
					//{
					//pSocket->m_emStatus = EM_SOCKET_CLOSING;

					// 錯誤及斷線處理

					pBuffer	= CONTAINING_RECORD( pOverlapped, CBuffer, m_overlapped );
					pNet	= (CNetBridge_IOCP*)pSocket->m_pNetBridge;

					if( pBuffer->m_emMode == EM_CONNECT )
					{
						// 連線失敗
						pNet->Handle_Connectfailed( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
					}
					else
					{
						// 表該 Socket Handle 關畢 or 錯誤發生
						if( pOverlapped != NULL && dwBytesTransfered == 0 )
						{
							if(pBuffer->m_emMode == EM_ACCEPT)
							{
								// TODO: How often does this happen? Really?
								int a = 825 + 2735;
								pNet->Post_Accept( pSocket, pBuffer );	// I think we do have to post a new guy

								pNet->On_Error("Malformed disconnect on listen socket");
							}
							else
							{
								// 表該 Socket Handle 關畢
								//pNet->On_Error("Close called from Thread_Completion(Socket Closed) [%d] [%u] [%d]", iError, pSocket->m_dwNetID, pBuffer->m_emMode);

#ifdef _DEBUG
								//							printf( "\nNB: Handle_Disconnect invoked due to IOCP socket close indication ( %d ), error code %d ", pSocket->m_dwNetID, iError );
#endif

								pNet->Close( pSocket->m_dwNetID );
								pNet->Handle_Disconnect	( pSocket, pBuffer, CompletionPort, dwBytesTransfered );				
							}
						}
						else
						{
							// 真的發生了錯誤了
							pNet->On_Error( "NB:Thread_Completion: Thread_Completion GetQueuedCompletionStatus failed: %d", iError );

							// 將 Buff 回收後斷線
							// 關掉 Socket 會使 CompletionQueue 將 Buffer 倒回來給系統
							shutdown( pSocket->m_tcp_socket , SD_BOTH );
							//closesocket( pSocket->m_tcp_socket );
							pSocket->m_tcp_socket = INVALID_SOCKET;

							//shutdown( pSocket->m_tcp_socket, SD_SEND );
							pNet->Handle_Disconnect	( pSocket, pBuffer, CompletionPort, dwBytesTransfered );
						}
					}
					//}

				}
			}
		}
	}

	
	//catch(...)
	{
		//MessageBox( NULL, "FUCK", "FUCKME", MB_OK );

	}
	

	return 0;
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Accept ( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{
	CNetSocket* pAcceptSocket	= pBuffer->m_pNetSocket;
	HANDLE		hrc				= CreateIoCompletionPort( (HANDLE)pAcceptSocket->m_tcp_socket, CompletionPort, (ULONG_PTR)pAcceptSocket, 0 );

	SOCKADDR_STORAGE	*LocalSockaddr		= NULL;
	SOCKADDR_STORAGE	*RemoteSockaddr		= NULL;
	int					LocalSockaddrLen,	RemoteSockaddrLen;

	if( hrc == NULL )
	{
		// ERROR
		On_Error( "NB: Thread_Completion: CreateIoCompletionPort failed: %d", GetLastError() );
	}

	//pAcceptSocket->m_cs_SocketIO.Enter();

		// Print the client's addresss
		pSocket->m_pfnGetAcceptExSockaddrs	(
												pBuffer->m_pData,
												//pBuffer->m_dwBufferSize - ((sizeof(SOCKADDR_STORAGE) + 16) * 2),
												0,
												sizeof(SOCKADDR_STORAGE) + 16,
												sizeof(SOCKADDR_STORAGE) + 16,
												(SOCKADDR **)&LocalSockaddr,
												&LocalSockaddrLen,
												(SOCKADDR **)&RemoteSockaddr,
												&RemoteSockaddrLen
											);


		SOCKADDR_IN* pAddr = (SOCKADDR_IN*)RemoteSockaddr;
		
		pAcceptSocket->m_dwIP				= pAddr->sin_addr.s_addr;
		pAcceptSocket->m_wPort				= ntohs( pAddr->sin_port );
		

		pAcceptSocket->m_emStatus			= EM_SOCKET_CONNECTED;
		pAcceptSocket->m_emAuthorize		= EM_AUTHORIZE_CHECK_AUTHORIZE;
		pAcceptSocket->m_dwLastRequestTick	= GetTickCount();
		
		pAcceptSocket->m_bConnectOnce		= true;
		
		// 先將 Host 的 Socket Event 給予 Create 出來的 新 Socket, 等待認證結束後, 才通知 該 Evnet->OnAccept 產生新事件
		pAcceptSocket->m_pEvent			= pSocket->m_pEvent;

		// 將 Socket 推入管理機制中
		//CreateSocket( true, pAcceptSocket );
		//AddSocketToMap( pAcceptSocket );

		// 設定 KeepAlive
		//SetKeepAlive( pAcceptSocket );


		WSAEventSelect( pAcceptSocket->m_tcp_socket, pAcceptSocket->m_wsaEvent, FD_CLOSE );

#ifdef _DEBUG
//		printf( "\nNB: Handle_Accept( %d )", pAcceptSocket->m_dwNetID );
#endif
		// 無論有無加密或壓縮, 則一率傳送 認證封包給連入端, 告知它我方 Socket 目前狀態( 有無加密或壓縮 )
		// 要求對方遵守我方協定, 並要求對方一定要回覆狀態, 若有加密, 則必需是加密過個封包
			
		//Authorize( pSocket, pAcceptSocket );

		// 做出事件通知放入 Queue
		MsgAccept( pAcceptSocket );

		// 做出 Recv Buffer, Post 到 overlapped IO request 上
		Post_Recv( pAcceptSocket );

		// 重新利用 Buffer 去等待連線
		Post_Accept( pSocket, pBuffer );

	//pAcceptSocket->m_cs_SocketIO.Leave();
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Compress		( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{
	// 對封包進行壓縮動作後將資料送出
	WSABUF	wBuf;
	DWORD	dwBytes = 0;
	int		iReturn;

	pBuffer->m_emMode		= EM_SEND;

	wBuf.buf = (char*)pBuffer->m_pData;
	wBuf.len = pBuffer->m_dwTotalSize;

		if( ( iReturn	=	WSASend( pSocket->m_tcp_socket, &wBuf, 1, &dwBytes, 0, &pBuffer->m_overlapped, NULL ) ) == -1 )
		{
			iReturn =	WSAGetLastError();
			On_Error( "Handle_Compress:WSASend: Error %d", iReturn );
		}

	pSocket->m_dwSendBuf++;
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Recv			( CNetSocket* pSocket, CBuffer* pRecvBuffer, HANDLE CompletionPort, DWORD dwBytesRecvied )
{	
/*
#ifdef DF_DEBUG_RECVMSG
	printf( "\n Recv( %d )",dwBytesRecvied );
#endif
*/

	//DWORD dwPacketSize = 0 , dwFlag = 0, dwBufferRemain = 0;

	pRecvBuffer->m_dwSize	= dwBytesRecvied;


	if( dwBytesRecvied == 0 )
	{
		/*
		WSABUF	wbuf;
		DWORD	dwBytes		= 0, dwflag		= 0;


		wbuf.buf				= (char*)pRecvBuffer->m_pData;
		wbuf.len				= pRecvBuffer->m_dwTotalSize;

		int rc	= WSARecv( pSocket->m_tcp_socket, &wbuf, 1, &dwBytes, &dwflag, &pRecvBuffer->m_overlapped, NULL );
		if( ( rc == SOCKET_ERROR ) && ( WSAGetLastError() != WSA_IO_PENDING ) )
		{
			int iErrID = WSAGetLastError();
			if( iErrID != WSA_IO_PENDING )
			{



				// 若這邊有錯, 那代表 Server 已經不穩定了, 應該
				//Close( pSocket->m_dwNetID );
				//Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );

				// 直接斷線處理
			}

			MsgOutPut( "Handle_Recv() WSARecv ErrID = %d", iErrID );
		}
		*/




		
		if( pSocket->m_emStatus != EM_SOCKET_CLOSING )
		{
			//On_Error("Close called from Handle_Recv");
			Close( pSocket->m_dwNetID );
			Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );
		}
		

		return;
	}


	InterlockedExchangeAdd( &m_RecvCount, 1 );
	InterlockedExchangeAdd( &m_RecvBytes, dwBytesRecvied );

	//InterlockedExchangeAdd( &pSocket->m_pNetBridge->m_bytesRecv, dwBytesRecvied );
	//InterlockedExchangeAdd( &pSocket->m_pNetBridge->m_PacketRecv, 1 );

	BYTE*	ptr						= pRecvBuffer->m_pData;
	//BYTE*	pBuffer					= pSocket->m_pBuffer->m_pBuffer;
	//DWORD	dwbytesRemain			= pSocket->m_pBuffer->m_dwBufferSize - pSocket->m_pBuffer->m_dwBytesNeedProcess;
	//DWORD*	pdwBytesNeedProcess		= &pSocket->m_pBuffer->m_dwBytesNeedProcess;
	
	//BYTE*	ptr						= NULL;
	BYTE*	pBuffer					= NULL;
	DWORD	dwBytesNeedProcess		= dwBytesRecvied;
   
	// 上次仍有資料待處理
	//------------------------------------------------------------------------
	// 檢查是否有無法 處理仍無法判斷封包大小的不完整的資料	
		if( pSocket->m_dwSizeRecvIncomplete != 0 )
		{
			if( pSocket->m_dwSizeRecvIncomplete > sizeof( Struct_PacketHeader ) )
			{
				// 理論上不可能會發生這樣的錯誤, 若發生表示收了兩倍 buffer 大小的資料, 確仍不能分析封包大小
				//On_Error( "NB:Handle_Recv: pSocket->m_pBufferIncomplete 滿了卻仍不能處理成訊息資料,需要檢視程式碼或除錯. NetID(%d)", pSocket->m_dwNetID );
				MsgOutPut( 5, "[NetBridge] pSocket->m_dwSizeRecvIncomplete > sizeof( Struct_PacketHeader )"  );
				// 錯誤處理 ? 強制斷線?
				//return;

				//On_Error("Close called from Handle_Recv(over packet buffer size)");
				Close( pSocket->m_dwNetID );
				Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );
				return;
			}

			// 將這次收到的資料併入不完整資料緩衝區中

			//BYTE* ptrIncomplete = pSocket->m_pBufferIncomplete->m_pData + pSocket->m_pBufferIncomplete->m_dwSize;
			BYTE* ptrIncomplete	= pSocket->m_pRecvIncomplete + pSocket->m_dwSizeRecvIncomplete;
			memcpy( ptrIncomplete, ptr, dwBytesRecvied );

			pSocket->m_dwSizeRecvIncomplete			+=	dwBytesRecvied;

			ptr										=	pSocket->m_pRecvIncomplete;
			dwBytesNeedProcess						=	pSocket->m_dwSizeRecvIncomplete;
		}

	// 處理收到資料
	//------------------------------------------------------------------------
		DWORD dwFlag = 0, dwBufferRemain = 0;
		while( dwBytesNeedProcess != 0 )
		{
			DWORD dwPacketSize = 0;

			// 建立 Buffer 讓資料結合
			if( pSocket->m_pRecvData == NULL )
			{
				if( pSocket->m_emMode == EM_SOCKET_MODE_NORMAL )
				{
					bool bResult = GetPacketInfo( ptr, dwBytesNeedProcess, &dwFlag, &dwPacketSize );

					if( bResult == false )
					{
						MsgOutPut( 5, "[NetBridge] Packet header checksum mismatch" );
						Close( pSocket->m_dwNetID );
						Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );					
						return;
					}
					
					if( dwPacketSize > DF_NB_MAXPACKETSIZE )
					{
						//MessageBox( NULL ,"封包 Size 過大!!", "Error" , MB_OK );
						//MsgOutPut( "\nNB_DEBUG: 封包 Size 過大!! KICK()" );
						MsgOutPut( 5, "[NetBridge] Packet size bigger than DF_NB_MAXPACKETSIZE [ %d ]/[ %d ]", dwPacketSize, DF_NB_MAXPACKETSIZE );
						//On_Error("Close called from Handle_Recv(packet too large)");
						Close( pSocket->m_dwNetID );
						Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );					
						return;
					}

					//---------------------------------------------------------
					//MsgOutPut( "\nNB_DEBUG: GetPacketInfo(): dwBytesNeedProcess = %d, dwFlag = %d, dwPacketSize = %d", dwBytesNeedProcess, dwFlag, dwPacketSize );
					if( dwPacketSize != 0 )
					{
						//pSocket->m_pBuffer				= CreateBuffer( dwPacketSize );
						pSocket->m_pRecvData			= m_bufferManager.Apply( dwPacketSize );
						pSocket->m_dwSizeRecvData		= dwPacketSize;
						pSocket->m_dwCountRecvData		= 0;

						//pSocket->m_pBuffer->m_dwFlag	= dwFlag;
						//pBuffer							= pSocket->m_pBuffer->m_pData;
						pBuffer							= pSocket->m_pRecvData;

					}
					else
					{
						break; // 資料量, 不夠可以檢查封包大小的, 跳開, 把資料暫存. 收到之後資料再處理
					}
				}
				else
				if( pSocket->m_emMode == EM_SOCKET_MODE_TELNET )
				{
					dwPacketSize					= dwBytesNeedProcess;
					pSocket->m_pRecvData			= m_bufferManager.Apply( dwPacketSize );
					pSocket->m_dwSizeRecvData		= dwPacketSize;
					pSocket->m_dwCountRecvData		= 0;
					pBuffer							= pSocket->m_pRecvData;
				}
			}
			else
			{
				//pBuffer				= pSocket->m_pBuffer->m_pData + pSocket->m_pBuffer->m_dwSize;
				pBuffer = pSocket->m_pRecvData + pSocket->m_dwCountRecvData;
			}

			//dwBufferRemain = pSocket->m_pBuffer->GetRemain();
			dwBufferRemain	= pSocket->m_dwSizeRecvData - pSocket->m_dwCountRecvData;


			if( dwBufferRemain > dwBytesNeedProcess )
			{
				// 資料量不夠一個完整封包
				memcpy( pBuffer, ptr, dwBytesNeedProcess );


				//pSocket->m_pBuffer->m_dwSize		+= dwBytesNeedProcess;
				pSocket->m_dwCountRecvData			+= dwBytesNeedProcess;
				ptr									+= dwBytesNeedProcess;
				dwBytesNeedProcess					=  0;
			}
			else
			{

				// 剩下的量夠一個完整封包
				memcpy( pBuffer, ptr, dwBufferRemain );

				// 收到一個完整的封包了, 推入訊息佇列
				
				//pSocket->m_pBuffer->m_dwSize		+= dwBufferRemain;

				pSocket->m_dwCountRecvData			+= dwBufferRemain;
				
				// 將資料推入訊習佇列, 等待主 Thread 處理
				ProcessBuffer( pSocket, pSocket->m_dwCountRecvData, pSocket->m_pRecvData );
			
				pSocket->m_pRecvData				= NULL;
				pSocket->m_dwSizeRecvData			= 0;
				pSocket->m_dwCountRecvData			= 0;

				
				// 移動指標
				ptr									+= dwBufferRemain;
				dwBytesNeedProcess					-= dwBufferRemain;
			}
		}


	// 剩餘資料處理
	//-----------------------------------------------------------------------------
	// 檢查是否還有剩餘資料還沒處理
	// 這邊會發生的機會並不大. 會發生的話. 通常是收到一筆資料, 處理後剩下不到 4 個 bytes, 不能知道下一個封包的大小.
	// 就不能建立 RecvData 來存封包. 故建立一個兩倍的緩衝區. 因為我們 Recv Buffer 是 1024 的大小. 故每次處理不會大於 1024
		if( dwBytesNeedProcess != 0 )
		{
			// 還有剩餘資料, 就將剩下的資料搬道 IncompleteBuffer 上
			//BYTE* pIncomplete = pSocket->m_pBufferIncomplete->m_pData + pSocket->m_pBufferIncomplete->m_dwSize;
			
			if( pSocket->m_pRecvIncomplete == NULL )
			{
				pSocket->m_pRecvIncomplete		= m_bufferManager.Apply( ( 16384 ) );
				pSocket->m_dwSizeRecvIncomplete	= 0;
			}

			//MessageBox( NULL, "Error 叫小輝 Handle_Recv()", "Error" , MB_OK );
			//Close( pSocket->m_dwNetID );


			//memmove( pSocket->m_pBufferIncomplete->m_pData, ptr, dwBytesNeedProcess );
			//pSocket->m_pBufferIncomplete->m_dwSize	= dwBytesNeedProcess;

			// 因為有可能 ptr 和 pSocket->m_pRecvIncomplete 是同一個記憶體區段, 避免記憶體問題, 使用 memmove 處理
			memmove( pSocket->m_pRecvIncomplete, ptr, dwBytesNeedProcess );
			pSocket->m_dwSizeRecvIncomplete	= dwBytesNeedProcess;

		}
		else
		{
			if( pSocket->m_pRecvIncomplete != NULL )
			{
				m_bufferManager.Delete( pSocket->m_pRecvIncomplete );
				pSocket->m_pRecvIncomplete		= NULL;		
			}

			pSocket->m_dwSizeRecvIncomplete	= 0;
			//pSocket->m_pBufferIncomplete->m_dwSize = 0;
		}

	// 重置 Recv
	//---------------------------------------------------------------------------------
	// 將 Recv Buffer 再推入 IO Queue, 並將之重新推入 RecvQueue

		pRecvBuffer->m_dwSize	= 0;

	// 將重置好的 Buffer 再次推入 Recv CompleteionQueue 中
		WSABUF	wbuf;
		DWORD	dwBytes		= 0, dwflag		= 0;

		wbuf.buf				= (char*)pRecvBuffer->m_pData;
		wbuf.len				= pRecvBuffer->m_dwTotalSize;

		ZeroMemory( &pRecvBuffer->m_overlapped, sizeof( OVERLAPPED ) );

		int iErrID = 0;
		int rc	= WSARecv( pSocket->m_tcp_socket, &wbuf, 1, &dwBytes, &dwflag, &pRecvBuffer->m_overlapped, NULL );
		if( ( rc == SOCKET_ERROR ) && ( ( iErrID = WSAGetLastError() ) != WSA_IO_PENDING ) ) 
		{
			if( iErrID == WSAENOTSOCK || iErrID == WSAECONNRESET )
			{
				// Socket 已經斷線, 回收 Buff
				Handle_Disconnect( pSocket, pRecvBuffer, CompletionPort, dwBytesRecvied );
				return;
			}

			MsgOutPut( 2, "Handle_Recv() WSARecv ErrID = %d", iErrID );
		}
		

	// 檢查下一個緩衝區是不是已經收到但擱至了, 是的話取出並執行
		
		/*
		CBuffer* pTempBuf = NULL;
		if( ( pTempBuf = pSocket->m_arrayTemp[ pRecvBuffer->m_dwNextPriority ] ) != NULL )
		{
			Handle_Recv( pSocket, pTempBuf, CompletionPort, pTempBuf->m_dwSize );
			pSocket->m_arrayTemp[ pRecvBuffer->m_dwNextPriority ] = NULL;			
		}
		*/
}
//-----------------------------------------------------------------
int CNetBridge_IOCP::Connect( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext )
{
	int iNetID		= 0;
	int iReturn		= 0;

	if( pEventObj == NULL )
		return NB_ERR;

	CNetSocket* pSocket		= CreateSocket();
	//pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, 0 );
	pSocket->m_emAuthorize	= EM_AUTHORIZE_WAIT_AUTHORIZE;
	pSocket->m_emMode		= EM_SOCKET_MODE_NORMAL;
	pSocket->m_pContext		= pContext;

	return ConnectBase( pSocket, dwIP, wPort, pEventObj );
}
//-----------------------------------------------------------------
int	CNetBridge_IOCP::Telnet ( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext )
{
	int iNetID		= 0;
	int iReturn		= 0;

	if( pEventObj == NULL )
		return NB_ERR;


	CNetSocket* pSocket		= CreateSocket();
	//pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	pSocket->m_tcp_socket	= socket( AF_INET, SOCK_STREAM, 0 );
	pSocket->m_emAuthorize	= EM_AUTHORIZE_WAIT_AUTHORIZE;
	pSocket->m_emMode		= EM_SOCKET_MODE_TELNET;
	pSocket->m_pContext		= pContext;

	return ConnectBase( pSocket, dwIP, wPort, pEventObj );
}
//-----------------------------------------------------------------
int CNetBridge_IOCP::ConnectBase ( CNetSocket* pSocket, DWORD dwIP, WORD wPort, CEventObj* pEventObj ) 
{
		int iNetID		= 0;
		int iReturn		= 0;

		if( pEventObj == NULL )
			return NB_ERR;

		// 連結 Socket 與 CompletionPort
			HANDLE hrc			= CreateIoCompletionPort( (HANDLE)pSocket->m_tcp_socket, m_CompletionPort, (ULONG_PTR)pSocket, 0);


		// Bind the socket
			SOCKADDR_IN	sa;
			memset( &sa, 0, sizeof( SOCKADDR_IN ) );
			sa.sin_family		= AF_INET;

			sa.sin_addr.s_addr = INADDR_ANY;

			bind( pSocket->m_tcp_socket, (SOCKADDR *) &sa, sizeof(SOCKADDR));

		// Prepre Socket Address
			//SOCKADDR_IN	sa;
			memset( &sa, 0, sizeof( SOCKADDR_IN ) );
			sa.sin_family		= AF_INET;
			sa.sin_addr.s_addr	= dwIP;
			sa.sin_port 		= htons( (WORD)wPort );




		// 設定 Socket 為 NonBlocking
			//int	iFlag			= 1;
			//iReturn				= ioctlsocket( pSocket->m_tcp_socket, FIONBIO, (u_long FAR*) &iFlag );

		// Tring to connect
			//iReturn			= WSAConnect( pSocket->m_tcp_socket, (SOCKADDR *)&sa, sizeof( SOCKADDR ), NULL, NULL, NULL, NULL );


			//EM_ACCEPT
			GUID        guidConnectEx				= WSAID_CONNECTEX;
			//GUID		guidGetAcceptExSockaddrs	= WSAID_GETACCEPTEXSOCKADDRS;
			DWORD       dwbytes						= 0;

			// 取出 AccectEx 的函式指標
			// Need to load the Winsock extension functions from each provider
			//    -- e.g. AF_INET and AF_INET6. 
			iReturn = WSAIoctl	(	
										pSocket->m_tcp_socket,
										SIO_GET_EXTENSION_FUNCTION_POINTER,
										&guidConnectEx,
										sizeof( guidConnectEx ),
										&pSocket->m_pfnConnectEx,
										sizeof( pSocket->m_pfnConnectEx ),
										&dwbytes,
										NULL,
										NULL
								);

			// Create connection buffer
			if( pSocket->m_pConnectBuffer == NULL )
			{
				pSocket->m_pConnectBuffer	= CreateBuffer( DF_NB_PACKETBUFFERSIZE );		
			}

			// Set buffer mode to EM_CONNECT
			pSocket->m_pConnectBuffer->m_emMode	= EM_CONNECT;


			if(iReturn == 0)
			{
				DWORD	iSend			= 0;
				BOOL bConnect			= pSocket->m_pfnConnectEx( pSocket->m_tcp_socket, (SOCKADDR *)&sa, sizeof( SOCKADDR ), NULL, 0, &iSend, &pSocket->m_pConnectBuffer->m_overlapped );

				if( bConnect == false )
				{
					// 連線失敗
					iReturn = WSAGetLastError();

					if( ( iReturn == WSAEWOULDBLOCK || iReturn == WSA_IO_PENDING ) == false )
					{
						//pEventObj->OnConnectFailed( iReturn );
						//On_Error("DeleteSocket called from Connect(B)");
						//DeleteSocket( pSocket->m_dwNetID );
						Close( pSocket->m_dwNetID );
						return -1;
					}
				}
			}
			else
			{
				// No ConnectEx capability, use a blocking WSAConnect instead
				INT32 wsaConnectErrorCode = WSAConnect(pSocket->m_tcp_socket, (SOCKADDR *) &sa, sizeof( SOCKADDR ), NULL, NULL, NULL, NULL);

				if( wsaConnectErrorCode == SOCKET_ERROR )
				{
					// 連線失敗
					iReturn = WSAGetLastError();

					pEventObj->OnConnectFailed( pSocket->m_dwNetID, iReturn );
					//On_Error("DeleteSocket called from Connect(B)");
					//DeleteSocket( pSocket->m_dwNetID );
					Close( pSocket->m_dwNetID );
					return -1;
				}

				PostQueuedCompletionStatus(m_CompletionPort, 0, (ULONG_PTR) pSocket, (LPOVERLAPPED) pSocket->m_pConnectBuffer);
			}

			// Set Keep alive
			//SetKeepAlive( pSocket );

			WSAEventSelect( pSocket->m_tcp_socket, pSocket->m_wsaEvent, FD_CLOSE );

			// Connected!! Create event and msg
			pSocket->m_emStatus				= EM_SOCKET_CONNECTED;
			pSocket->m_dwLastRequestTick	= GetTickCount();
			pSocket->m_pEvent				= pEventObj;

		// 暫時不發訊息通知 Client, 而等到 Server 發回認證訊息回來後, 才通知 Client 

	//----------------------------------------------------------------------
	//CNetSocket* pSocket = GetSocket( iNetID );


	// 做出 PostRecv Buffer 等待資料
	// Post_Recv( pSocket );
	
	return iNetID;
}

BYTE CNetBridge_IOCP::AddDataToSendFrame ( CNetSocket*	pSocket, DWORD dwSize, BYTE* pData, byte Code, bool bAppend )
{
	BYTE Checksum = 0;

	if( dwSize == 0 )
		return 0;

	// 先建立第一個 Frame, 確定該 Socket 至少有一個 Frame
	CFrameBuffer frame;

	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::AddDataToSendFrame" );
	{
		// If there are no existing send frames in the queue, create a new send frame
		
		if( pSocket->m_queueSendFrame.Count() == 0 || bAppend == false )
		{
			frame.Init();
			frame.m_AllocSize	= DF_NB_PACKETBUFFERSIZE;
			frame.m_pData		= m_bufferManager.Apply( frame.m_AllocSize );
		}
		// Otherwise dequeue the last available send frame
		else
		{
			frame	= pSocket->m_queueSendFrame.DequeueTail();
		}

		// 建立初始資料
		byte*	ptrFrame	= frame.m_pData + frame.m_dwStoreSize;	// 取出儲存空間開始定址
		byte*	ptrData		= pData;
		int		iDataCount	= dwSize;		

		int		iCopyCount	= 0;
		int		iFreeSpace	= 0;

		// 將資料完全複製進 Frame, 若空間不夠, 則建立新的 Frame
		while( iDataCount != 0 )
		{			
			iFreeSpace = frame.m_AllocSize - frame.m_dwStoreSize;
			iCopyCount = min(iDataCount, iFreeSpace);

			if( Code == 0 )
			{
				memcpy( ptrFrame, ptrData, iCopyCount );
			}
			else
			{
				Checksum += Encode( ptrFrame, ptrData, iCopyCount, Code );
			}
			
			ptrFrame			+= iCopyCount;
			ptrData				+= iCopyCount;
			frame.m_dwStoreSize += iCopyCount;

			iDataCount			-= iCopyCount;
			iFreeSpace			-= iCopyCount;

			if( iDataCount > 0 )
			{
				if(iFreeSpace == 0)
				{
					pSocket->m_queueSendFrame.Queue( frame );	// 將資料存入之前的結構

					// 建立新的 Frame
					frame.Init();

					frame.m_AllocSize	= DF_NB_PACKETBUFFERSIZE;
					frame.m_pData		= m_bufferManager.Apply( frame.m_AllocSize );

					ptrFrame			= frame.m_pData;
				}
			}
			else
			{
				pSocket->m_queueSendFrame.Queue( frame );	// 將資料存入之前的結構
				break;
			}
		}

		pSocket->m_SendQueueSize += dwSize;

	}
	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::AddDataToSendFrame" );

	return Checksum;
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::SendWithBuff ( DWORD dwNetID, DWORD dwSize1, PVOID pData1, DWORD dwSize2, PVOID pData2 )
{
	CNetSocket*	pSocket = GetSocket( dwNetID );

	// Make sure the socket exists and is in a valid state
	if( pSocket == NULL || pSocket->m_emStatus != EM_SOCKET_CONNECTED )
		return;

	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::SendWithBuff" );

	if( pSocket->m_emMode == EM_SOCKET_MODE_NORMAL )
	{
		//DWORD dw = dwSize + dwExtraSize;

		byte	Index				= SendID( pSocket );

		Struct_PacketHeader Header;

		Header.dwTotalPacketSize	= dwSize1 + dwSize2 + sizeof( Struct_PacketHeader );
		Header.wSystemFlag			= 0;
		Header.CheckSum				= 0;
		Header.HeaderChecksum		= 0;

		//DWORD						dwBuffSize	= dwSize1 + dwSize2 + sizeof( Struct_PacketHeader );
		//BYTE*						pBuff		= m_bufferManager.Apply( dwBuffSize );


		/*
		DWORD						dwBuffSize	= dwSize1 + dwSize2 + sizeof( Struct_PacketHeader );
		BYTE*						pBuff		= m_bufferManager.Apply( dwBuffSize );
		BYTE*						ptr			= pBuff;
		Struct_PacketHeader*		pHeader		= (Struct_PacketHeader*)pBuff;

		
		memcpy( ptr, &Header, sizeof( Struct_PacketHeader ) );
		ptr += sizeof( Struct_PacketHeader );
		
		memcpy( ptr, (BYTE*)pData1, dwSize1 );
		ptr += dwSize1;
		
		memcpy( ptr, (BYTE*)pData2, dwSize2 );
		ptr += dwSize2;
		*/

		Struct_PacketHeader*		pHeader		= (Struct_PacketHeader*)&Header;

		pSocket->m_SendIndex++;

		if( pSocket->m_IsEncryption != false )
		{
			byte Code = pSocket->m_KeyTable[ Index ];
			

			pHeader->wSystemFlag		= DF_PSYSFLAG_ENCRYPTION;
			pHeader->Index				= Index;

			pHeader->SendIndex			= pSocket->m_SendIndex;
			pHeader->RecvIndex			= pSocket->m_RecvIndex;

			pHeader->CheckSum			= GetCheckSum( (BYTE*)pHeader, sizeof(Struct_PacketHeader), 0, 0 );
			pHeader->CheckSum			= GetCheckSum( (BYTE*)pData1, dwSize1, 0, pHeader->CheckSum );
			pHeader->CheckSum			= GetCheckSum( (BYTE*)pData2, dwSize2, 0, pHeader->CheckSum );
			pHeader->CheckSum			= pHeader->CheckSum + Code;

			pHeader->HeaderChecksum		= GetCheckSum( (BYTE*)pHeader, sizeof(Struct_PacketHeader), 0, 0 );

			//AddDataToSendFrame( pSocket, dwBuffSize, pBuff, 0 );
			AddDataToSendFrame( pSocket, sizeof(Struct_PacketHeader), (BYTE*)pHeader, 0, true );
			AddDataToSendFrame( pSocket, dwSize1, (byte*)pData1, Code, true );
			AddDataToSendFrame( pSocket, dwSize2, (byte*)pData2, Code, true );
			
			/*
			Header.wSystemFlag		= DF_PSYSFLAG_ENCRYPTION;
			Header.Index			= Index;
			Header.CheckSum			= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData1, dwSize1, 0, Header.CheckSum );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData2, dwSize2, 0, Header.CheckSum );
			Header.HeaderChecksum	= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );


			// 將封包頭推進 Frame
			AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );

			// 將資料推進 Frame
			BYTE Check = 0;

			Check += AddDataToSendFrame( pSocket, dwSize1, (BYTE*)pData1, 0 );
			Check += AddDataToSendFrame( pSocket, dwSize2, (BYTE*)pData2, 0 );
			*/

			
		}
		else
		{
			/*
			Header.Index			= Index;

			Header.CheckSum			= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData1, dwSize1, 0, Header.CheckSum );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData2, dwSize2, 0, Header.CheckSum );
			Header.HeaderChecksum	= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );

			// 將封包頭推進 Frame
			AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );

			// 將資料推進 Frame
			AddDataToSendFrame( pSocket, dwSize1, (BYTE*)pData1, 0 );
			AddDataToSendFrame( pSocket, dwSize2, (BYTE*)pData2, 0 );
			*/

			pHeader->Index				= Index;

			pHeader->SendIndex			= pSocket->m_SendIndex;
			pHeader->RecvIndex			= pSocket->m_RecvIndex;

			pHeader->CheckSum			= GetCheckSum( (BYTE*)pHeader, sizeof(Struct_PacketHeader), 0, 0 );
			pHeader->CheckSum			= GetCheckSum( (BYTE*)pData1, dwSize1, 0, pHeader->CheckSum );
			pHeader->CheckSum			= GetCheckSum( (BYTE*)pData2, dwSize2, 0, pHeader->CheckSum );
			pHeader->HeaderChecksum		= GetCheckSum( (BYTE*)pHeader, sizeof(Struct_PacketHeader), 0, 0 );

			//AddDataToSendFrame( pSocket, dwBuffSize, pBuff, 0 );

			AddDataToSendFrame( pSocket, sizeof(Struct_PacketHeader), (BYTE*)pHeader, 0, true );
			AddDataToSendFrame( pSocket, dwSize1, (byte*)pData1, 0, true );
			AddDataToSendFrame( pSocket, dwSize2, (byte*)pData2, 0, true );



		}
	}
	else
	{
		// 將封包頭推進 Frame
		AddDataToSendFrame( pSocket, dwSize1, (BYTE*)pData1, 0 );
		AddDataToSendFrame( pSocket, dwSize2, (BYTE*)pData2, 0 );
	}

	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::SendWithBuff" );

	// 發出事件
	m_bEvent = true;
	SetEvent( m_pNetMainEvent );
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Send ( DWORD dwNetID, DWORD dwSize, PVOID pData )
{
	CNetSocket*	pSocket = GetSocket( dwNetID );

	// Make sure the socket exists and is in a valid state
	if( pSocket == NULL || pSocket->m_emStatus != EM_SOCKET_CONNECTED )
		return;

	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::Send" );

	if( pSocket->m_emMode == EM_SOCKET_MODE_NORMAL )
	{
		//DWORD dw = dwSize + dwExtraSize;
		Struct_PacketHeader Header;
		
		Header.dwTotalPacketSize	= dwSize + sizeof( Struct_PacketHeader );
		Header.wSystemFlag			= 0;
		Header.CheckSum				= 0;
		Header.HeaderChecksum		= 0;
		
		Header.SendIndex			= 0;
		Header.RecvIndex			= 0;
		
		byte	index	= SendID( pSocket );		

		if( pSocket->m_IsEncryption != false )
		{
			pSocket->m_SendIndex++;
			
			byte	Code	= pSocket->m_KeyTable[ index ];

			Header.wSystemFlag		= DF_PSYSFLAG_ENCRYPTION;
			Header.Index			= index;
			
			Header.SendIndex		= pSocket->m_SendIndex;
			Header.RecvIndex		= pSocket->m_RecvIndex;

			Header.CheckSum			= GetCheckSum( (BYTE*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData, dwSize, 0, Header.CheckSum );
			Header.CheckSum			= Header.CheckSum + Code;

			Header.HeaderChecksum	= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
			

			//if( dwSize > 700 )
			if( true )
			{

				// 將封包頭推進 Frame

				BYTE Check = 0;

				//AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );
				//AddDataToSendFrame( pSocket, dwSize, (BYTE*)pData, 0 );

				// Send a copied packet to check packet
				/*
				BYTE*	pBuff		= new BYTE[ ( dwSize + sizeof( Struct_PacketHeader ) ) ];
				BYTE*	pBuff2		= new BYTE[ ( dwSize + sizeof( Struct_PacketHeader ) ) ];
				BYTE*	ptr			= pBuff;
				BYTE	sum			= 0;

				memcpy( ptr, &Header, sizeof( Struct_PacketHeader ) );
				ptr += sizeof( Struct_PacketHeader );

				memcpy( ptr, (BYTE*)pData, dwSize );

				memcpy( pBuff2, pBuff, ( dwSize + sizeof( Struct_PacketHeader ) ) );

				Struct_PacketHeader* pHeader2 = (Struct_PacketHeader*)pBuff2;
				pHeader2->wSystemFlag = 0x20;
				
				AddDataToSendFrame( pSocket, ( dwSize + sizeof( Struct_PacketHeader ) ), (BYTE*)pBuff2, 0, false );
				AddDataToSendFrame( pSocket, ( dwSize + sizeof( Struct_PacketHeader ) ), (BYTE*)pBuff, 0, false );

				delete [] pBuff;
				delete [] pBuff2;
				*/

				



				//BYTE*	pBuff		= new BYTE[ ( dwSize + sizeof( Struct_PacketHeader ) ) ];
				/*
				DWORD	dwBuffSize	= dwSize + sizeof( Struct_PacketHeader );
				BYTE*	pBuff		= m_bufferManager.Apply( dwBuffSize );
				BYTE*	ptr			= pBuff;
				BYTE	sum			= 0;

				memcpy( ptr, &Header, sizeof( Struct_PacketHeader ) );
				ptr += sizeof( Struct_PacketHeader );

				memcpy( ptr, (BYTE*)pData, dwSize );
				*/
				
				//AddDataToSendFrame( pSocket, dwBuffSize, (BYTE*)pBuff, 0, false );

				AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0, true );
				AddDataToSendFrame( pSocket, dwSize, (BYTE*)pData, Code, true );

				//pSocket->m

				//delete [] pBuff;

			}
			else
			{
				// Debug 用
				Struct_PacketHeader PackageHeader;

				PackageHeader.dwTotalPacketSize = ( Header.dwTotalPacketSize + 200 + sizeof( Struct_PacketHeader ) );
				PackageHeader.wSystemFlag		= 0x10;
				PackageHeader.CheckSum			= 0;
				PackageHeader.HeaderChecksum	= 0;
				PackageHeader.Index				= index;
				

				BYTE*	pBuff		= new BYTE[ ( Header.dwTotalPacketSize + 200 + sizeof( Struct_PacketHeader ) ) ];
				BYTE*	ptr			= pBuff;
				BYTE	sum			= 0;
				
				memcpy( ptr, &PackageHeader, sizeof( Struct_PacketHeader ) );
				sum = GetCheckSum( (byte*)&PackageHeader, sizeof( Struct_PacketHeader ), 0, 0 );
				ptr += sizeof( Struct_PacketHeader );

				memcpy( ptr, &Header, sizeof( Struct_PacketHeader ) );
				sum = GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, sum );
				ptr += sizeof( Struct_PacketHeader );

				memcpy( ptr, pData, dwSize );
				sum = GetCheckSum( (byte*)pData, dwSize, 0, sum );
				ptr += dwSize;

				memset( ptr, 1, 200 );
				sum = GetCheckSum( ptr, 200, 0, sum );

				Struct_PacketHeader* pBegin = (Struct_PacketHeader*)pBuff;
				pBegin->CheckSum = sum;

				pBegin->HeaderChecksum		= GetCheckSum( (BYTE*)pBuff, sizeof( Struct_PacketHeader ), 0, 0 );

				AddDataToSendFrame( pSocket, PackageHeader.dwTotalPacketSize, pBuff, 0, false );

				delete[] pBuff;
			}



		
			//BYTE Sum = Check;
			//if( Sum != Header.CheckSum )
			//{
			//	MsgOutPut( "[NET] Send->AddDataToSendFrame Checksum error" );
			//}
			
		}
		else
		{
			pSocket->m_SendIndex++;

			Header.Index			= index;
			Header.SendIndex		= pSocket->m_SendIndex;
			Header.RecvIndex		= pSocket->m_RecvIndex;

			Header.CheckSum			= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
			Header.CheckSum			= GetCheckSum( (BYTE*)pData, dwSize, 0, Header.CheckSum );
			Header.HeaderChecksum	= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );


			// Making buffer
			/*
			DWORD	dwBuffSize		= dwSize + sizeof( Struct_PacketHeader );
			BYTE*	pBuff			= m_bufferManager.Apply( dwBuffSize );
			BYTE*	ptr				= pBuff;			

			memcpy( ptr, &Header, sizeof( Struct_PacketHeader ) );
			ptr += sizeof( Struct_PacketHeader );

			memcpy( ptr, (BYTE*)pData, dwSize );
			*/

			//AddDataToSendFrame( pSocket, dwBuffSize, (BYTE*)pBuff, 0, false );

			AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0, true );
			AddDataToSendFrame( pSocket, dwSize, (BYTE*)pData, 0, true );



			// 將封包頭推進 Frame
			//AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );

			// 將資料推進 Frame
			//AddDataToSendFrame( pSocket, dwSize, (BYTE*)pData, 0 );
		}
	}
	else
	{
		// 將封包頭推進 Frame
		AddDataToSendFrame( pSocket, dwSize, (BYTE*)pData, 0 );
	}

	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::Send" );

	// 發出事件
	m_bEvent = true;
	SetEvent( m_pNetMainEvent );	

}

//下面為舊版 在改成 FrameSend 前使用
/*
void CNetBridge_IOCP::_Send( DWORD dwNetID, DWORD dwSize, PVOID pData, DWORD dwPriority, DWORD dwFlag )
{	

		//下面為舊版

	CNetSocket*	pSocket = GetSocket( dwNetID );
	if( pSocket == NULL || pSocket->m_emStatus != EM_SOCKET_CONNECTED ) return;

	DWORD		dwBytes = 0;
	CBuffer*	pBuffer	= NULL;

	pBuffer		= CreatePacketBuffer( dwSize, pData, NULL );

	if( dwFlag != 0 )
	{
		*((DWORD*)pBuffer->m_pData) |= dwFlag;
	}

	pBuffer->m_emMode		= EM_SEND;

	// 傳送成功, 紀錄傳送中的 Buffer 計數
	pSocket->m_dwSendBuf++;

	m_vecWaitSendSocket.push_back( pSocket->m_dwNetID );
	pSocket->m_vecWaitToSend.push_back( pBuffer );

	// 通知主執行續有事件

	m_bEvent = true;
	//SetEvent( m_hMsgEvent );
	SetEvent( m_pNetMainEvent );
}
*/


//-----------------------------------------------------------------

void CNetBridge_IOCP::Handle_Send ( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{
#ifdef DF_DEBUG_SENDMSG
	printf("\nSend(%d): %d",pSocket->m_dwNetID, dwBytesTransfer );
#endif

	InterlockedExchangeAdd( &m_SendCount, 1 );
	InterlockedExchangeAdd( &m_SendBytes, dwBytesTransfer );

	// 因為 SendBuff 是 Socket 的靜態成員, 故不需解構 pBuffer

	CFrameBuffer frame;

	pSocket->m_cs_SocketIO.Enter( "Handle_Send" );
	{
		// 記錄我們送了多少資料還沒送出去
			pSocket->m_iSendQueueBytes			-= dwBytesTransfer;
		

		m_bufferManager.Delete( pBuffer->m_pData );
		pBuffer->m_pData = NULL;

		if( pSocket->m_queueSendFrame.Count() != 0 )
		{
			frame = pSocket->m_queueSendFrame.Dequeue();		
			pSocket->m_SendQueueSize -= frame.m_dwStoreSize;

			WSABUF		wBuf;
			int			iReturn				= 0;
			DWORD		dwBytes				= 0;

			wBuf.buf						= (char*)frame.m_pData;
			wBuf.len						= frame.m_dwStoreSize;

			pSocket->m_bSending				= true;
			pSocket->m_SendBuffer.m_emMode	= EM_SEND;
			pSocket->m_SendBuffer.m_pData	= frame.m_pData;

			pSocket->m_SendBuffer.m_dwSize		= frame.m_dwStoreSize;


			//pSocket->m_iSendQueueBytes		+=	frame.m_dwStoreSize;

			if( pSocket->m_tcp_socket != INVALID_SOCKET )
			{
				iReturn	= WSASend( pSocket->m_tcp_socket, &wBuf, 1, &dwBytes, 0, &( pSocket->m_SendBuffer.m_overlapped ), NULL );
				if( iReturn == -1 )
				{
					int iErrID = WSAGetLastError();
					if( iErrID != WSA_IO_PENDING )
					{						
						m_bufferManager.Delete( frame.m_pData );
						Close( pSocket->m_dwNetID );
						
						pSocket->m_bSending				= false;
						pSocket->m_SendBuffer.m_pData	= NULL;

						if( iErrID != WSAENOTSOCK || iErrID != WSAECONNRESET )
						{
							MsgOutPut( 2, "Post_Send() WSASend got a WSAERROR [ %d ]", iErrID );
						}						
					}
				}
			}
			else
			{
				m_bufferManager.Delete( frame.m_pData );
				pSocket->m_bSending				= false;
				pSocket->m_SendBuffer.m_pData	= NULL;
			}
		}
		else
		{
			pSocket->m_bSending					= false;	// 沒有資料在佇列了. 設定發送狀態為 false
			pSocket->m_SendBuffer.m_pData		= NULL;
		}
	}
	pSocket->m_cs_SocketIO.Leave( "Handle_Send" );
	//InterlockedExchangeAdd( &pSocket->m_pNetBridge->m_bytesSend, dwBytesTransfer );
	//InterlockedExchangeAdd( &pSocket->m_pNetBridge->m_PacketSend, 1 );
	
		/*
		vector< CBuffer* >::iterator it;
		for( it = pSocket->m_vecSend.begin(); it != pSocket->m_vecSend.end(); it++ )
		{
			if( *it == pBuffer )
			{
			
				pSocket->m_vecSend.erase( it );
				break;
			}
		}
		*/
		//pSocket->m_dwSendBuf--;
		
		
		
		// 收到這表示資料已送完
		//DeleteBuffer( pBuffer );
		//delete pBuffer;	
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Disconnect	( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{
	try
	{
		pSocket->m_cs_SocketIO.Enter( "Handle_Disconnect" );
	}
	catch(...)
	{
		MsgOutPut( 2, "[NetBridge] Handle_Disconnect socket error-A" );
	}

	try
	{
		deque< CBuffer* >::iterator it;
		vector< CBuffer* >::iterator it_vec;
		
		pSocket->m_debug++;

		bool bDeleteSocket = false;		

		// 回收 Buff
		if( pBuffer != NULL )
		{
			switch( pBuffer->m_emMode )
			{
			case EM_ACCEPT:
				{
					for( it_vec = pSocket->m_vecAccept.begin(); it_vec != pSocket->m_vecAccept.end(); it_vec++ )
					{
						if( pBuffer == *it_vec )
						{
							pSocket->m_vecAccept.erase( it_vec );
							break;
						}
					}

					DeleteBuffer( pBuffer );
				} break;

			case EM_RECV:
				{
					if( pSocket->m_pRecvBuff != NULL )
					{
						DeleteBuffer( pBuffer );
						pSocket->m_pRecvBuff = NULL;
					}
											
				} break;
			case EM_SEND:
				{
					m_bufferManager.Delete( pBuffer->m_pData );
					pBuffer->m_pData = NULL;
				} break;
			}

			
		}		


	}
	catch(...)
	{
		MsgOutPut( 2, "[NetBridge] Handle_Disconnect socket error-B" );
	}


	try
	{
		pSocket->m_cs_SocketIO.Leave( "Handle_Disconnect" );
	}
	catch(...)
	{
		MsgOutPut( 2, "[NetBridge] Handle_Disconnect socket error-C" );
	}

			
	
	

	//if( bDeleteSocket
	//DeleteSocket( pSocket->m_dwNetID );
}
//-----------------------------------------------------------------
void	CNetBridge_IOCP::Post_Accept			( CNetSocket* pSocket , CBuffer* pBuffer )
{
	int		rc		= 0;
	DWORD	dwBytes = 0;

	pSocket->m_cs_SocketIO.Enter( "Post_Accept" );
	{
		pBuffer->m_emMode						= EM_ACCEPT;	
		pBuffer->m_pNetSocket					= CreateSocket();
		pBuffer->m_pNetSocket->m_tcp_socket		= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		pBuffer->m_pNetSocket->m_emMode			= pSocket->m_emMode;
		pBuffer->m_pNetSocket->m_pContext		= pSocket->m_pContext;
		
		pBuffer->m_pNetSocket->m_IsEncryption	= pSocket->m_IsEncryption;
		pBuffer->m_pNetSocket->m_IsCompress		= pSocket->m_IsCompress;
//		printf( "NB: Post Accept TCP ( %d )\n", pSocket->m_tcp_socket );

		if( pBuffer->m_pNetSocket->m_tcp_socket	 == INVALID_SOCKET )
		{
			// ERROR?
			On_Error("NB: Error creating TCP socket");
		}

		/*
		rc = pSocket->m_pfnAcceptEx(
		pSocket->m_tcp_socket,
		pBuffer->m_pNetSocket->m_tcp_socket,
		pBuffer->m_pBuffer,
		( pBuffer->m_dwBufferSize - ((sizeof(SOCKADDR_STORAGE) + 16) * 2) ),
		( sizeof(SOCKADDR_STORAGE) + 16 ),
		( sizeof(SOCKADDR_STORAGE) + 16 ),
		&bytes,
		&pBuffer->m_overlapped
		);
		*/

		// 令之成為 Accept 狀態, AcceptEx 可以在一開始的時候接收一個封包, 但暫時用不到,故接收 Buffer 填 0
		rc = pSocket->m_pfnAcceptEx	(
										pSocket->m_tcp_socket,
										pBuffer->m_pNetSocket->m_tcp_socket,
										pBuffer->m_pData,
										0,//((sizeof(SOCKADDR_STORAGE) + 16) * 2),
										( sizeof(SOCKADDR_STORAGE) + 16 ),
										( sizeof(SOCKADDR_STORAGE) + 16 ),
										&dwBytes,
										&pBuffer->m_overlapped
									);

		if( rc == FALSE )
		{
			if( WSAGetLastError() != WSA_IO_PENDING )
			{
				On_Error( "NB:Host:m_pfnAcceptEx: %d", WSAGetLastError() );
			}
		}
	}
	pSocket->m_cs_SocketIO.Leave( "Post_Accept" );
}

//-----------------------------------------------------------------
void	CNetBridge_IOCP::Post_Recv		( CNetSocket* pSocket )
{
	WSABUF		wbuf;
	DWORD		dwBytes		= 0, dwflag		= 0;
	int			rc;

	pSocket->m_cs_SocketIO.Enter( "Post_Recv" );
	{
		// 做出 Recv Buffer, Post 到 overlapped IO request 上
		CBuffer* pRecvBuffer = NULL;

		//pRecvBuffer = CreateBuffer( DF_NB_PACKETBUFFERSIZE );
		pRecvBuffer = CreateBuffer( 8192 );

		pRecvBuffer->m_emMode			= EM_RECV;
		pRecvBuffer->m_dwPriority		= 0;
		pRecvBuffer->m_pNetSocket		= pSocket;
		pRecvBuffer->m_dwNextPriority	= NULL;

		// TODO: Where does this fit into the whole process?
		//pSocket->m_vecRecv.push_back( pRecvBuffer );
		pSocket->m_pRecvBuff	= pRecvBuffer;

		// Setup WSABUF structure for WSAREcv
		wbuf.buf				= (char*)pRecvBuffer->m_pData;
		wbuf.len				= pRecvBuffer->m_dwTotalSize;


		// Post WSARecv call
		rc	= WSARecv( pSocket->m_tcp_socket, &wbuf, 1, &dwBytes, &dwflag, &pRecvBuffer->m_overlapped, NULL );
		if( rc == SOCKET_ERROR )
		{
			int iErrID = WSAGetLastError();
			if( iErrID != WSA_IO_PENDING && iErrID != WSAEWOULDBLOCK )
			{
				// ERROR
				pSocket->m_pNetBridge->On_Error( "NB:Handle_Accept: WSARecv failed: %d", WSAGetLastError() );

				DeleteBuffer( pRecvBuffer );
				pSocket->m_pRecvBuff = NULL;
			}
		}
	}
	pSocket->m_cs_SocketIO.Leave( "Post_Recv" );
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::Post_Compress		( CNetSocket* pSocket , CBuffer* pBuffer )
{
	pBuffer->m_emMode				=  EM_COMPRESS;
	*((DWORD*)pBuffer->m_pData)		|= DF_PTAG_COMORESS;
	

	pSocket->m_cs_SocketIO.Enter( "Post_Compress" );
		BOOL b = PostQueuedCompletionStatus( (HANDLE)m_CompletionPort, pBuffer->m_dwTotalSize, (ULONG_PTR)pSocket, &pBuffer->m_overlapped );
	pSocket->m_cs_SocketIO.Leave( "Post_Compress" );
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::Post_Send			( CNetSocket* pSocket )
{
	WSABUF			wBuf;
	CFrameBuffer	frame;
	DWORD			dwBytes		= 0;
	int				iReturn		= 0;

	pSocket->m_cs_SocketIO.Enter( "Post_Send" );
	{
		// Ensure there is no existing send in-flight, and that there are packet frames waiting
		if( pSocket->m_bSending == false && pSocket->m_queueSendFrame.Count() > 0 )
		{
			// 取出第一個 Frame 發送
			frame = pSocket->m_queueSendFrame.Dequeue();
			pSocket->m_SendQueueSize -= frame.m_dwStoreSize;

			// 貼入 WSASend
			wBuf.buf = (char *) frame.m_pData;
			wBuf.len = frame.m_dwStoreSize;

			pSocket->m_bSending = true;
			
			

			pSocket->m_SendBuffer.Init();
			pSocket->m_SendBuffer.m_emMode		=	EM_SEND;
			pSocket->m_SendBuffer.m_pData		=	frame.m_pData;

			

			//pSocket->m_iSendQueueBytes			+=	frame.m_dwStoreSize;

			pSocket->m_SendBuffer.m_dwSize		= frame.m_dwStoreSize;

			if( pSocket->m_tcp_socket != INVALID_SOCKET )
			{
				iReturn	= WSASend( pSocket->m_tcp_socket, &wBuf, 1, &dwBytes, 0, &( pSocket->m_SendBuffer.m_overlapped ), NULL );
				if( iReturn == -1 )
				{
					iReturn =	WSAGetLastError();
					if( iReturn != WSA_IO_PENDING )
					{
						//On_Error( "Post_Send: Error %d\n", iReturn );

						MsgOutPut( 2, "Post_Send() WSASend got a error [ %d ] on NetID %u (B)\n", iReturn, pSocket->m_dwNetID );

						//shutdown( pSocket->m_tcp_socket , SD_SEND );
						//On_Error("Close called from Post_Send");
						Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
						//pSocket->m_tcp_socket	= INVALID_SOCKET;
						pSocket->m_bSending				= false;
						
						m_bufferManager.Delete( frame.m_pData );

						pSocket->m_SendBuffer.m_pData	= NULL;

						// 釋放記憶體資料
						
					}
				}
			}
			else
			{
				pSocket->m_bSending				= false;		
				m_bufferManager.Delete( frame.m_pData );
				pSocket->m_SendBuffer.m_pData	= NULL;
			}
		}
	}
	pSocket->m_cs_SocketIO.Leave( "Post_Send" );
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::SendToAll ( DWORD dwSize, PVOID pPacket )
{
	CNetSocket*	pSocket = NULL;

		for(int i = 0; i < m_vecSocketSize; ++i)
		{
			m_cs_Socket.Enter( "CNetBridge_IOCP::SendToAll" );
			{
				pSocket = m_vecSocket[i];
			}
			m_cs_Socket.Leave( "CNetBridge_IOCP::SendToAll" );
			if(pSocket)
			{
				if( pSocket->m_emStatus == EM_SOCKET_CONNECTED )
				{
					Send( pSocket->m_dwNetID, dwSize, pPacket );
				}
			}
		}

}
//-----------------------------------------------------------------
void CNetBridge_IOCP::SendToAllWithBuff	( DWORD dwSize1, PVOID pPacket1, DWORD dwSize2, PVOID pPacket2 )
{
	CNetSocket*	pSocket = NULL;

	for(int i = 0; i < m_vecSocketSize; ++i)
	{
		m_cs_Socket.Enter( "CNetBridge_IOCP::SendToAllWithBuff" );
		{
			pSocket = m_vecSocket[i];
		}
		m_cs_Socket.Leave( "CNetBridge_IOCP::SendToAllWithBuff" );
		if(pSocket)
		{
			if( pSocket->m_emStatus == EM_SOCKET_CONNECTED )
			{
				SendWithBuff( pSocket->m_dwNetID, dwSize1, pPacket1, dwSize2, pPacket2 );
			}
		}
	}

}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Close ( DWORD dwNetID )
{
	CNetSocket*	pSocket = GetSocket(dwNetID);
#if NET_BIRDGE_IOCP_DEBUG_PRINT
    char szDebug[255+1];
    _snprintf(szDebug, 255, "> CNetBridge_IOCP::Close(%u) - 0x%p\n", dwNetID, pSocket);
    OutputDebugString(szDebug);
#endif
    if( pSocket == NULL )
		return;

	m_cs_Socket.Enter( "CNetBridge_IOCP::Close" );
	{
		if( pSocket && pSocket->m_tcp_socket != INVALID_SOCKET )
		{
				if( find( m_vecWaitCloseSocket.begin(), m_vecWaitCloseSocket.end(), pSocket ) == m_vecWaitCloseSocket.end() )
				{
					pSocket->m_emStatus		= EM_SOCKET_WAIT_CLOSE;
					pSocket->m_dwTimer		= GetTickCount() + 2000;

					m_vecWaitCloseSocket.push_back( pSocket );
				}		
		}
	}
	m_cs_Socket.Leave( "CNetBridge_IOCP::Close" );
}

//-----------------------------------------------------------------
bool CNetBridge_IOCP::CheckNetID ( DWORD dwNetID )
{
	bool bReturn = false;
	CNetSocket*	pSocket = NULL;
	m_cs_Socket.Enter( "CNetBridge_IOCP::CheckNetID" );

	{
		for(int i = 0; i < m_vecSocketSize; ++i)
		{
			pSocket = m_vecSocket[i];
			if(pSocket)
			{
				if( pSocket->m_emStatus == EM_SOCKET_CONNECTED )
				{
					//Send( pSocket->m_dwNetID, dwSize, pPacket, 0 , 0 );
					if( pSocket->m_dwNetID == dwNetID )
						bReturn = true;
				}
			}
		}
	}
	m_cs_Socket.Leave( "CNetBridge_IOCP::CheckNetID" );

	return bReturn;
}

//-----------------------------------------------------------------
DWORD CNetBridge_IOCP::GetNumOfConnections ()
{
	DWORD dwCount = 0;
	CNetSocket*	pSocket = NULL;
	m_cs_Socket.Enter( "CNetBridge_IOCP::GetNumOfConnections" );
	{
		for(int i = 0; i < m_vecSocketSize; ++i)
		{
			pSocket = m_vecSocket[i];
			if(pSocket)
			{
				if( pSocket->m_emStatus == EM_SOCKET_CONNECTED )
				{
					dwCount++;
				}
			}
		}
	}
	m_cs_Socket.Leave( "CNetBridge_IOCP::GetNumOfConnections" );

	return dwCount;
}

//-----------------------------------------------------------------
int CNetBridge_IOCP::GetSendQueueSize ()
{
	return 0;
}

//-----------------------------------------------------------------
void CNetBridge_IOCP::ProcessBuffer		( CNetSocket* pSocket, DWORD dwPacketSize, BYTE* pPacketData )
{
	if( pSocket->m_emMode == EM_SOCKET_MODE_NORMAL )
	{
		Struct_PacketHeader*	pHeader			= (Struct_PacketHeader*)pPacketData;

		DWORD					dwDataSize		= 0;
		BYTE*					pData			= NULL;

		dwDataSize	= pHeader->dwTotalPacketSize - sizeof( Struct_PacketHeader );
		pData		= pPacketData + sizeof( Struct_PacketHeader );

		if( pSocket->m_IsEncryption != false )
		{
			if( pHeader->wSystemFlag == 0 )
			{
				// Socket 有加密, 但收到封包確沒有加密, 也不是系統封包
				MsgOutPut( 5, "[NET] %d - %s", NB_ERR_WRONG_ENCRYPTION, "RECV A NON-ENCRYPTION PACKET - ProcessBuffer()" );
				Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
				m_bufferManager.Delete( pPacketData );
				return;
			}
		}
		
		if( pHeader->wSystemFlag != 0 )
		{
			// 系統封包, 加密或系統通知
			SystemPacket( pSocket, pHeader, dwDataSize, pData );
			//m_bufferManager.Delete( pPacketData );
		}
		else
		{
			// 一般封包
			MsgRecv( pSocket, dwDataSize, pData, pPacketData  );
		}
	}
	else
	if( pSocket->m_emMode == EM_SOCKET_MODE_TELNET )
	{
		MsgRecv( pSocket, dwPacketSize, pPacketData, pPacketData  );
	}

	//if( bProcessed )
	//	DeleteBuffer( pBuffer );
	//else
	//{
	//	pBuffer->m_dwSize		= pBuffer->m_dwTotalSize;
	//	MsgRecv( pSocket, pBuffer );
	//}
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Connect		( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{
	
	
	DeleteBuffer( pBuffer );
	pSocket->m_pConnectBuffer	= NULL;
	pSocket->m_emAuthorize		= EM_AUTHORIZE_OKAY;
	pSocket->m_bConnectOnce		= true;

	Post_Recv( pSocket );

	if( pSocket->m_emMode == EM_SOCKET_MODE_TELNET )
	{
		MsgConnect( pSocket );
	}
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Handle_Connectfailed( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer )
{		

	DeleteBuffer( pBuffer );
	pSocket->m_pConnectBuffer = NULL;

	MsgConnectFailed( pSocket );

}
//-----------------------------------------------------------------
void CNetBridge_IOCP::SendConnect ( CNetSocket* pSocket )
{
	srand(GetTickCount());

	Struct_PacketHeader		Header;
	//int						iLenKey			= strlen( g_NetBridge_KeyTable ) - 1;
	int						iLenKey			= sizeof( g_NetBridge_KeyTable );
	double					randVal			= rand();
	byte					StartKeyIndex	= (((double) randVal / (double) RAND_MAX ) * iLenKey + 0 );
	
	//byte					KeyTable[DF_KEYTABLE_LENGTH];
	//byte					EncodeKeyTable[DF_KEYTABLE_LENGTH];

	Header.dwTotalPacketSize	= sizeof( pSocket->m_KeyTable ) + sizeof( Struct_PacketHeader );
	Header.wSystemFlag			= DF_PSYSFLAG_CONNECTKEY;
	Header.CheckSum				= 0;
	Header.Index				= 255;
	Header.HeaderChecksum		= 0;
	Header.SendIndex			= 0;
	Header.RecvIndex			= 0;
	
	


	if( pSocket->m_IsEncryption != false )
	{
		byte Code		= g_NetBridge_KeyTable[ pSocket->m_SendKeyIndex ];


		Header.wSystemFlag		|=	 DF_PSYSFLAG_ENCRYPTION;
		Header.CheckSum			=	GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );

		for( int i = 0; i < DF_KEYTABLE_LENGTH; i++ )
		{
			pSocket->m_KeyTable[ i ] = ( rand() % 254 ) + 1;
			//pSocket->m_KeyTable[ i ] = 0;
		}

		
		Header.CheckSum			= GetCheckSum( pSocket->m_KeyTable, sizeof(pSocket->m_KeyTable), Code, Header.CheckSum );
		Header.HeaderChecksum	= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );
		//Encode( EncodeKeyTable, KeyTable, sizeof(EncodeKeyTable), Code );


		// 將封包頭推進 Frame
		AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );

		// 將資料推進 Frame
		AddDataToSendFrame( pSocket, sizeof(pSocket->m_KeyTable) , (BYTE*)pSocket->m_KeyTable, Code );
	}
	else
	{
		Header.CheckSum			= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );
		Header.CheckSum			= GetCheckSum( pSocket->m_KeyTable, sizeof(pSocket->m_KeyTable), 0, Header.CheckSum );
		Header.HeaderChecksum	= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );

		// 將封包頭推進 Frame
		AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );

		// 將資料推進 Frame
		AddDataToSendFrame( pSocket, sizeof(pSocket->m_KeyTable) , (BYTE*)pSocket->m_KeyTable, 0 );
	}
}
//-----------------------------------------------------------------
BYTE CNetBridge_IOCP::Encode(  BYTE* pTarget, BYTE* pSource, int iSize, byte Code )
{
	BYTE Checksum = 0; 
	for( int i = 0; i < iSize; i++ )
	{
		Checksum += pSource[ i ];

		BYTE Val = ( pSource[ i ] ^ Code ) - Code;
		pTarget[ i ] = Val;
	}

	return Checksum;
}
//-----------------------------------------------------------------
void CNetBridge_IOCP::Decode(  BYTE* pTarget, BYTE* pSource, int iSize, byte Code )
{
	for( int i = 0; i < iSize; i++ )
	{
		BYTE Val = ( pSource[ i ] + Code ) ^ Code;
		pTarget[ i ] = Val;
	}
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
void CNetBridge_IOCP::SystemPacket		( CNetSocket* pSocket, Struct_PacketHeader* pHeader, DWORD dwDataSize, BYTE* pData )
{
	if( pHeader->wSystemFlag == DF_PSYSFLAG_ENCRYPTION )
	{
		BYTE CheckSum	= 0;
		BYTE rID		= RecvID( pSocket );
		byte Code		= pSocket->m_KeyTable[ rID ];

		Decode( pData, pData, dwDataSize, Code );

		CheckSum = GetCheckSum( (byte*)pHeader, sizeof( Struct_PacketHeader ) + dwDataSize, Code, 0 ) - pHeader->CheckSum - pHeader->HeaderChecksum;

		if( CheckSum == pHeader->CheckSum )
		{
			MsgRecv( pSocket, dwDataSize, pData, (BYTE*)pHeader  );
			return;
		}
		else
		{
			Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
			m_bufferManager.Delete( (BYTE*)pHeader );
			return;
		}
	}
	else
	if( pHeader->wSystemFlag & DF_PSYSFLAG_CONNECTKEY )
	{
		if( pHeader->wSystemFlag & DF_PSYSFLAG_ENCRYPTION )
		{
			if( dwDataSize == DF_KEYTABLE_LENGTH )
			{
				pSocket->m_IsEncryption = true;

				BYTE KeyTable[DF_KEYTABLE_LENGTH];

				byte Code		= g_NetBridge_KeyTable[ pSocket->m_RecvKeyIndex ];
				byte CheckSum	= 0;

				Decode( pData, pData, dwDataSize, Code );

				//Decode( KeyTable, pData, dwDataSize, Code );
				memcpy( KeyTable, pData, dwDataSize );


				//CheckSum = GetCheckSum( (byte*)pHeader, sizeof( Struct_PacketHeader ) + dwDataSize, Code, 0 ) - pHeader->CheckSum - pHeader->HeaderChecksum;
				CheckSum = GetCheckSum( (byte*)pHeader, sizeof( Struct_PacketHeader ) + dwDataSize, Code, 0 ) - pHeader->CheckSum - pHeader->HeaderChecksum;

				if( CheckSum == pHeader->CheckSum )
				{
					memcpy( pSocket->m_KeyTable, KeyTable, dwDataSize );
					MsgConnect( pSocket );
					m_bufferManager.Delete( (BYTE*)pHeader );
					return;
				}
				//*/
			}
			// 錯誤, 通知錯誤並做出處置			
			MsgOutPut( 5, "[NET] %d - %s", NB_ERR_WRONG_ENCRYPTION, "WRONG_ENCRYPTION SystemPacket()" );
			Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
		}
		else
		{
			MsgConnect( pSocket );
		}
	}
	else
	if(	pHeader->wSystemFlag == DF_PSYSFLAG_R_ALIVE )
	{
		if( dwDataSize == sizeof(DWORD) )
		{
			DWORD dwLastSocketRespondTime = *((DWORD*)pData);
			SendAliveAnswer( pSocket, *((DWORD*)pData) );

			DWORD dwIndex	= ( dwLastSocketRespondTime / 100 );			
			if( dwIndex > 9 )
			{
				dwIndex = 9;
			}

			InterlockedExchangeAdd( &(m_Respond[ dwIndex ]), 1 );
			//MsgSystem( pSocket, pHeader, pData, dwDataSize );
			//return;
		}
		else
		{
			MsgOutPut( 5, "[NET] REQEUEST ALIVE PACKET SIZE WRONG - SystemPacket()" );
			Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
		}
	}
	else
	if( pHeader->wSystemFlag == DF_PSYSFLAG_S_ALIVE )
	{
		if( dwDataSize == sizeof(DWORD) )
		{
			DWORD dwTick					= GetTickCount();
			DWORD dwRespondTime				= (DWORD) abs( ( (int)pSocket->m_dwLastRequestTick - (int)dwTick ) );

			pSocket->m_dwLastRequestTick	= dwTick;
			pSocket->m_dwRespondTime		= dwRespondTime;
			pSocket->m_dwRespondCheck		= 0;	// 有回應, 則將值歸 0
			pSocket->m_bRespond				= true;
		}
	}
	else
	if( pHeader->wSystemFlag == DF_PSYSFLAG_COMPRESS )
	{
		byte*					ptr			= pData;
		DWORD					dwOrgSize	= *((DWORD*)ptr);			ptr += sizeof(DWORD);

		byte*					pOrgData	= m_bufferManager.Apply( dwOrgSize );

		m_pFunDecompress( ( dwDataSize - sizeof(DWORD) ), ptr, pOrgData );

		ptr = pOrgData;

		int iRemain = dwOrgSize;

		while( iRemain > 0 )
		{
			Struct_PacketHeader*	pDataHeader			= (Struct_PacketHeader*)ptr;
			byte*					pBuff				= m_bufferManager.Apply( pDataHeader->dwTotalPacketSize );

			memcpy( pBuff, ptr, pDataHeader->dwTotalPacketSize );
			pDataHeader	= (Struct_PacketHeader*)pBuff;

			DWORD					dwSize				= pDataHeader->dwTotalPacketSize - sizeof( Struct_PacketHeader );
			BYTE*					pContainData		= ptr + sizeof( Struct_PacketHeader );
			
			if( pDataHeader->wSystemFlag != 0 )
			{
				SystemPacket( pSocket, pDataHeader, dwSize, pContainData );
			}
			else
			{
				MsgRecv( pSocket, dwSize, pContainData, (BYTE*)pDataHeader  );
			}

			iRemain -= pDataHeader->dwTotalPacketSize;
		}

		m_bufferManager.Delete( pOrgData );
	}
	else
	{
		MsgOutPut( 5, "[NET] %d - %s", NB_ERR, "UNIDENTIFY PACKET - SystemPacket()" );
		//Close( pSocket->m_dwNetID );		// 關畢 Socket, 有延後的作用. 
	}

	m_bufferManager.Delete( (BYTE*)pHeader );
}

bool CNetBridge_IOCP::Shutdown()
{
	// 立刻, 不加思索的釋放所有記憶體
	//HANDLE	CNetBridge_IOCP::m_CompThreads[ DF_NB_MAX_COMPLETION_THREAD_COUNT ];

	/*
	for( int i = 0; i < DF_NB_MAX_COMPLETION_THREAD_COUNT; i++ )
	{
		if( m_CompThreads[ i ] != NULL )
		{
			CloseHandle( m_CompThreads[ i ] );
			m_CompThreads[ i ]  = NULL;
		}
	}
	*/

	// int iEndTime = GetTickCount() + 300;
	int iStartTime = GetTickCount();

	bool bReleaseThread = false;

	while( 1 )
	{
		bReleaseThread = true;

		for( int i = 0; i < DF_NB_MAX_COMPLETION_THREAD_COUNT; i++ )
		{
			if( m_CompThreads[i] != 0 )
			{
				bReleaseThread = false;
				PostQueuedCompletionStatus( m_CompletionPort, 0, 0, 0 );
			}				
		}

		if( bReleaseThread != false )
		{
			break;
		}
		else
		{
			int iTime	= GetTickCount();
			int iOffset = abs( iTime - iStartTime );

			if( iOffset > 500 )
			{
				break;
			}
		}
	}	
	
	if( bReleaseThread == false )
	{
		for( int i = 0; i < DF_NB_MAX_COMPLETION_THREAD_COUNT; i++ )
		{
			if( m_CompThreads[ i ] != NULL )
			{
				CloseHandle( m_CompThreads[ i ] );
				m_CompThreads[ i ]  = NULL;
			}
		}

		Sleep( 200 );
	}




	// 釋放所有

	return true;

}

BYTE CNetBridge_IOCP::SendID( CNetSocket* pSocket )
{ 
	BYTE Val = pSocket->m_SendKeyIndex;

	pSocket->m_SendKeyIndex++;
	
	if( pSocket->m_SendKeyIndex == DF_KEYTABLE_LENGTH )
	{
		pSocket->m_SendKeyIndex = 0;
	}

	return Val; 
}

BYTE CNetBridge_IOCP::RecvID( CNetSocket* pSocket )
{ 
	BYTE Val = pSocket->m_RecvKeyIndex;

	pSocket->m_RecvKeyIndex++;

	if( pSocket->m_RecvKeyIndex == DF_KEYTABLE_LENGTH )
	{
		pSocket->m_RecvKeyIndex = 0;
	}

	return Val; 
}



//-----------------------------------------------------------------------------------------
void CNetBridge_IOCP::SendAliveRequest ( CNetSocket* pSocket )
{
	Struct_PacketHeader		Header;
	DWORD					dwTick	= pSocket->m_dwRespondTime;

	Header.dwTotalPacketSize	= sizeof( dwTick ) + sizeof( Struct_PacketHeader );
	Header.wSystemFlag			= DF_PSYSFLAG_R_ALIVE;
	Header.CheckSum				= 0;
	Header.HeaderChecksum		= 0;
	Header.Index				= 255;
	Header.SendIndex			= 0;
	Header.RecvIndex			= 0;

	Header.CheckSum				= GetCheckSum( (byte*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
	Header.CheckSum				= GetCheckSum( (byte*)&dwTick, sizeof(dwTick), 0, Header.CheckSum );
	Header.HeaderChecksum		= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );


	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::SendAliveRequest" );
	// 將封包頭推進 Frame
	AddDataToSendFrame( pSocket, sizeof(Struct_PacketHeader), (BYTE*)&Header, 0 );

	// 將資料推進 Frame
	AddDataToSendFrame( pSocket, sizeof(dwTick) , (BYTE*)&dwTick, 0 );

	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::SendAliveRequest" );
}
//-----------------------------------------------------------------------------------------
void CNetBridge_IOCP::SendAliveAnswer ( CNetSocket* pSocket, DWORD dwSrvTick )
{
	Struct_PacketHeader		Header;

	Header.dwTotalPacketSize	= sizeof( dwSrvTick ) + sizeof( Struct_PacketHeader );
	Header.wSystemFlag			= DF_PSYSFLAG_S_ALIVE;
	Header.CheckSum				= 0;
	Header.HeaderChecksum		= 0;
	Header.Index				= 255;
	Header.SendIndex			= 0;
	Header.RecvIndex			= 0;


	Header.CheckSum				= GetCheckSum( (byte*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
	Header.CheckSum				= GetCheckSum( (byte*)&dwSrvTick, sizeof(dwSrvTick), 0, Header.CheckSum );
	Header.HeaderChecksum		= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );


	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::SendAliveAnswer" );

	// 將封包頭推進 Frame
	AddDataToSendFrame( pSocket, sizeof(Struct_PacketHeader), (BYTE*)&Header, 0 );

	// 將資料推進 Frame
	AddDataToSendFrame( pSocket, sizeof(dwSrvTick) , (BYTE*)&dwSrvTick, 0 );

	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::SendAliveAnswer" );
}
//-----------------------------------------------------------------------------------------
void CNetBridge_IOCP::SendChecksumError	( CNetSocket* pSocket, WORD wSendIndex, byte headerchecksum, byte checksum )
{
	Struct_PacketHeader		Header;

	Header.dwTotalPacketSize	= sizeof( wSendIndex ) + sizeof( headerchecksum ) + sizeof( checksum ) + sizeof( Struct_PacketHeader );
	Header.wSystemFlag			= DF_PSYSFLAG_S_CHECKSUMERR;
	Header.CheckSum				= 0;
	Header.HeaderChecksum		= 0;
	Header.Index				= 255;
	Header.SendIndex			= 0;
	Header.RecvIndex			= 0;

	Header.CheckSum				= GetCheckSum( (byte*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
	Header.CheckSum				= GetCheckSum( (byte*)&wSendIndex, sizeof(wSendIndex), 0, Header.CheckSum );
	Header.CheckSum				= GetCheckSum( (byte*)&headerchecksum, sizeof(headerchecksum), 0, Header.CheckSum );
	Header.CheckSum				= GetCheckSum( (byte*)&checksum, sizeof(checksum), 0, Header.CheckSum );
	Header.HeaderChecksum		= GetCheckSum( (byte*)&Header, sizeof( Struct_PacketHeader ), 0, 0 );


	pSocket->m_cs_SocketIO.Enter( "CNetBridge_IOCP::SendChecksumError" );

	// 將封包頭推進 Frame
	AddDataToSendFrame( pSocket, sizeof(Struct_PacketHeader), (BYTE*)&Header, 0 );

	// 將資料推進 Frame
	AddDataToSendFrame( pSocket, sizeof(wSendIndex) , (BYTE*)&wSendIndex, 0 );
	AddDataToSendFrame( pSocket, sizeof(headerchecksum) , (BYTE*)&headerchecksum, 0 );
	AddDataToSendFrame( pSocket, sizeof(checksum) , (BYTE*)&checksum, 0 );

	pSocket->m_cs_SocketIO.Leave( "CNetBridge_IOCP::SendChecksumError" );
}
//-----------------------------------------------------------------------------------------
DWORD CNetBridge_IOCP::GetRespondTime( DWORD dwNetID )
{
	CNetSocket*	pSocket = GetSocket( dwNetID );

	if( pSocket != NULL )
	{
		return pSocket->m_dwRespondTime;
	}

	return 0;
}
//-----------------------------------------------------------------------------------------
void CNetBridge_IOCP::SetSocketNoDelay	( DWORD dwNetID )
{
	int		iVal;
	//int		iResult;

	CNetSocket*	pSocket = GetSocket( dwNetID );

	if( pSocket != NULL )
	{
		iVal = 1;

		if( setsockopt( pSocket->m_tcp_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &iVal, sizeof( iVal) ) == SOCKET_ERROR )
		{
			MsgOutPut( 5, "SetSocketNoDelay() failed" );
			return;
		}
	}

	return;
}
//-----------------------------------------------------------------------------------------
PVOID CNetBridge_IOCP::GetContext( DWORD dwNetID )
{
	CNetSocket*	pSocket = GetSocket( dwNetID );

	if( pSocket != NULL )
	{
		return pSocket->m_pContext;
	}

	return NULL;
}
//-----------------------------------------------------------------------------------------
void CNetBridge_IOCP::ProcessCompress( CNetSocket* pSocket )
{

	if( m_pFunCompress == NULL )
		return;

	CFrameBuffer	frame;

	DWORD			dwSize				= 0;
	DWORD			dwCopySize			= 0;
	DWORD			dwTargetSize		= 0;



	if( pSocket->m_iSendQueueBytes > 4096 )
		dwTargetSize = 4096;
	else
		return;

	byte		szBuff[ 16384 ];
	byte*		ptr				= szBuff;

	CNetQueue< CFrameBuffer >	Queue;


	if( dwTargetSize != 0 )
	{
		while( 1 )
		{
			frame = pSocket->m_queueSendFrame.Dequeue();
			pSocket->m_SendQueueSize -= frame.m_dwStoreSize;

			dwSize += frame.m_dwStoreSize;

			if( dwSize > dwTargetSize && dwSize < 16384 )
			{
				memcpy( ptr, frame.m_pData, frame.m_dwStoreSize );
				ptr += frame.m_dwStoreSize;
				m_bufferManager.Delete( frame.m_pData );
			}
			else
				break;
		}

		Queue.MergeAtEnd( pSocket->m_queueSendFrame );
		pSocket->m_queueSendFrame.clear();

		// Compress
		DWORD	dwCompressedSize	= 0;
		//char*	pCompressData		= new char[dwSize + (dwSize>>1) + 12];
		byte*	pCompressData		= m_bufferManager.Apply( (dwSize + (dwSize>>1) + 12 + sizeof( DWORD )) );
		

		m_pFunCompress( dwSize, szBuff, (int*)&dwCompressedSize, ( pCompressData + sizeof( DWORD) ) );
		memcpy( pCompressData, &dwCompressedSize, sizeof( DWORD ) );
		dwCompressedSize += sizeof( DWORD );
		
		pSocket->m_SendIndex++;

		Struct_PacketHeader Header;

		Header.dwTotalPacketSize	= dwSize + sizeof( Struct_PacketHeader );
		
		Header.wSystemFlag			= DF_PSYSFLAG_COMPRESS;
		Header.SendIndex			= pSocket->m_SendIndex;
		Header.RecvIndex			= pSocket->m_RecvIndex;

		Header.CheckSum				= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );
		Header.CheckSum				= GetCheckSum( (BYTE*)&dwCompressedSize, sizeof(dwCompressedSize), 0, Header.CheckSum );
		Header.CheckSum				= GetCheckSum( (BYTE*)pCompressData, dwCompressedSize, 0, Header.CheckSum );
		Header.HeaderChecksum		= GetCheckSum( (BYTE*)&Header, sizeof(Struct_PacketHeader), 0, 0 );

		AddDataToSendFrame( pSocket, sizeof( Struct_PacketHeader ), (BYTE*)&Header, 0 );
		AddDataToSendFrame( pSocket, dwCompressedSize, (BYTE*)pCompressData, 0 );

		m_bufferManager.Delete( pCompressData );

		pSocket->m_queueSendFrame.MergeAtEnd( Queue );
		Queue.clear();
	}


}

void CNetBridge_IOCP::SetSendLimit( bool IsEnable, int iLimit )
{
	m_bSendBufferLimit	= IsEnable;				// Check transfer limit flag, default is off

	if( iLimit < 1024 * 32 * 2)
	{
		m_dwSendBuffLimit = 1024 * 1024 * 2;
	}
	else
		m_dwSendBuffLimit	= iLimit;				// Check transfer limit	default is 204,800(bytes) and respond time bigger than 3000ms 2 * 1024 * 1024
}

void CNetBridge_IOCP::SetRecvEvent		( bool bEnable )
{
	m_CheckRecvEvent = bEnable;
}

DWORD CNetBridge_IOCP::GetSendQueueSize( DWORD dwNetID )
{
	CNetSocket*	pSocket = GetSocket( dwNetID );

	if( pSocket == NULL )
		return 0;

	return pSocket->m_SendQueueSize;
}


#pragma managed

