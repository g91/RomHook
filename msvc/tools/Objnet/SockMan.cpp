#include "SockMan.h"
#include <iostream>
#pragma optimize("", off) 
#pragma warning( push )
#pragma		warning (disable:4244)
#pragma		warning (disable:4311)
#pragma		warning (disable:4312)
#pragma		warning (disable:4018)
//#include "LMemUtil.h"
//=====================================================================================================================
using namespace std;
//=====================================================================================================================
// SocketManager Member function
//=====================================================================================================================
cSockMan::~cSockMan() throw(){
	this->UnInit();
}

bool LSAPI cSockMan::WaitingConnect( sockaddr_in* pAddr, INetEventListener* pListener ) {

	SOCKET sock ;
	try {
		sock = ::TCPConnect( pAddr );
	} catch(...) {
		return false;
	}	
	pListener->OnConnected( AddSocket( sock, pListener ) );
	return true;
}
int LSAPI cSockMan::Connect( sockaddr_in* pAddr, INetEventListener* listener ) {

	SOCKET sock;
	try {
		sock = ::NonBlock_TCPConnect( pAddr );
	} catch(...) {
		//listener->OnConnectFailed();
		return -1;
	}
	int id = m_WCList_sock.Add( sock );
	m_WCList_pListener.Add( (UINT32) listener );

	TRACE1(" connection connecting sock=%d!!!\n",sock);
	return id;
}
void LSAPI cSockMan::CancelConnect( int connect_number ) {

	SOCKET sock = (SOCKET) m_WCList_sock.ValueAt( connect_number );
	::closesocket(sock);

	m_WCList_sock.Remove( connect_number );
	m_WCList_pListener.Remove( connect_number );
}

void LSAPI cSockMan::AttachClientListener( LNETID id, INetEventListener* pListener ) {
	Connection* pConn = (Connection*) m_Connections.ValueAt( id );
	pConn->AttachListener( pListener );
}


void LSAPI
cSockMan::
RevFlush(timeval* wait_time)
{
	fd_set	in_set, out_set, exc_set;
	UINT	nMaxHandle = 0;
	//LList<Connection>::iterator pConn = m_Connections.GetIterator();
	//LList<WC>::iterator pWC = m_WCList.GetIterator();
	//deque<SOCKET>::iterator i;

	/*if( m_bHaveShutDownConnection == true )*/ 
	if(Time < clock() || m_bHaveShutDownConnection == true)
	{
		Time = clock()+2*1000;
		UINT32ArrayList_foreach( m_Connections, 
			{
				Connection* pConn = (Connection*) u32Value;
				// 處理 close 的資料
				if( pConn->m_status == Connection::SHUTDOWNED )
				{
					pConn->m_pListener->OnDisconnected( i );
					delete pConn;
					m_Connections.Remove( i );
				}else
				{
					pConn->SendCheckPack();
					if(pConn->m_status == Connection::SHUTDOWNED )
					{
						pConn->m_pListener->OnDisconnected( i );
						delete pConn;
						m_Connections.Remove( i );
					}
				}
			}
		);
		m_bHaveShutDownConnection = false;
	}

	// Intialize select SET
	FD_ZERO( &in_set  );
	FD_ZERO( &out_set );
	FD_ZERO( &exc_set );

	
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		SOCKET sock = u32Value;
		nMaxHandle = max( nMaxHandle, sock+1 );
		FD_SET( sock, &in_set );
		FD_SET( sock , &exc_set );
	}
	);

	// add connecting connection to set
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		nMaxHandle = max( nMaxHandle, sock+1 );
		FD_SET( sock , &exc_set );
		FD_SET( sock , &out_set );
	}
	);

	// add normal connection to set
	UINT32ArrayList_foreach( m_Connections, {
		Connection* p = (Connection*) u32Value;
		SOCKET sock = p->GetSocket();
		if( p->NeedRead() ) {

			nMaxHandle = max( nMaxHandle, sock+1 );
			FD_SET( sock , &in_set );	// 若是需要讀取
			FD_SET( sock , &exc_set );

			if( p->HaveSomethingToWrite() ) // 若是有資料需要輸出，才處理
				FD_SET( sock , &out_set );
		}
	}
	);

	if( nMaxHandle == 0 )
		return;
	// 若 bWait 是 true 的話，就等到有新的資料進來才進行處理
	int n = select( nMaxHandle, &in_set, &out_set, &exc_set, wait_time);//bWait?NULL:&null_time );
	if(n <0 )
		OutputDebugString("\nSelect Error");

	//SockCheckFail( n < 0, "SockMan: Select" );
	if( n == 0 ) return;



	// =============================================================================
	UINT32ArrayList_foreach( m_Connections, {

		Connection* pConn = (Connection*) u32Value;
		// 處理 client 端傳來的資料
		if ( FD_ISSET( pConn->GetSocket(), &in_set ) ) {
			UINT32 u32TotalSize = pConn->m_u32TotalRecvSize;
			pConn->ProcessDataIn();
			m_nNumOfBytesRecv += pConn->m_u32TotalRecvSize - u32TotalSize;
		}
		/*
		// 處理寫出去的資料
		if( pConn->m_status != Connection::SHUTDOWNED )
		{
			if ( FD_ISSET( pConn->GetSocket(), &out_set ) ) {
				pConn->ProcessDataOut();
			}
			// 刪除有問題的連線
			if( FD_ISSET( pConn->GetSocket(), &exc_set ) ) {
				cout << "Exc connection "<< pConn->GetSocket() <<endl;
				//pConn->m_pListener->OnDisconnected( i );
				// 跳到下個 connection
			}
		}
		*/
		// 處理 close 的資料
		if( pConn->m_status == Connection::SHUTDOWNED ) {
			pConn->m_pListener->OnDisconnected( i );
			delete pConn;
			m_Connections.Remove( i );
		}
	} 
	);


	// =============================================================================
	// any connecting connection error ?
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &exc_set ) ) {
			::closesocket(u32Value);
			INetEventListener* pListener = (INetEventListener*) m_WCList_pListener.ValueAt(i);
			pListener->OnConnectFailed( i );
			m_WCList_sock.Remove( i );
			m_WCList_pListener.Remove( i );
			TRACE1("OnConnectFailed(%d)\n", i );
		}
	}
	);
	// any connecting connection connected ?
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &out_set ) ) {
			INetEventListener* pListener = (INetEventListener*) m_WCList_pListener.ValueAt(i);
			m_WCList_sock.Remove(i);
			m_WCList_pListener.Remove( i );
			pListener->OnConnected( AddSocket( sock, pListener ) );
		}
	}
	);

	// =============================================================================
	// New connection?
	// any new connection ?
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &in_set ) ) {
			ProcessNewConnect( sock, (INewConnectionListener*)m_ServerSocketList_pListener.ValueAt(i) );
		}
	}
	);

}


void LSAPI
cSockMan::
Flush(timeval* wait_time)
{
	fd_set	in_set, out_set, exc_set;
	UINT	nMaxHandle = 0;
	//LList<Connection>::iterator pConn = m_Connections.GetIterator();
	//LList<WC>::iterator pWC = m_WCList.GetIterator();
	//deque<SOCKET>::iterator i;

	/*if( m_bHaveShutDownConnection == true )*/ 
	if(Time < clock() || m_bHaveShutDownConnection == true)
	{
		Time = clock()+2*1000;
		UINT32ArrayList_foreach( m_Connections, 
			{
				Connection* pConn = (Connection*) u32Value;
				// 處理 close 的資料
				if( pConn->m_status == Connection::SHUTDOWNED )
				{
					pConn->m_pListener->OnDisconnected( i );
					delete pConn;
					m_Connections.Remove( i );
				}else
				{
					pConn->SendCheckPack();
					if(pConn->m_status == Connection::SHUTDOWNED )
					{
						pConn->m_pListener->OnDisconnected( i );
						delete pConn;
						m_Connections.Remove( i );
					}
				}
			}
		);
		m_bHaveShutDownConnection = false;
	}

	// Intialize select SET
	FD_ZERO( &in_set  );
	FD_ZERO( &out_set );
	FD_ZERO( &exc_set );

	
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		SOCKET sock = u32Value;
		nMaxHandle = max( nMaxHandle, sock+1 );
		FD_SET( sock, &in_set );
		FD_SET( sock , &exc_set );
	}
	);

	// add connecting connection to set
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		nMaxHandle = max( nMaxHandle, sock+1 );
		FD_SET( sock , &exc_set );
		FD_SET( sock , &out_set );
	}
	);

	// add normal connection to set
	UINT32ArrayList_foreach( m_Connections, {
		Connection* p = (Connection*) u32Value;
		SOCKET sock = p->GetSocket();
		if( p->NeedRead() ) {

			nMaxHandle = max( nMaxHandle, sock+1 );
			FD_SET( sock , &in_set );	// 若是需要讀取
			FD_SET( sock , &exc_set );

			if( p->HaveSomethingToWrite() ) // 若是有資料需要輸出，才處理
				FD_SET( sock , &out_set );
		}
	}
	);

	if( nMaxHandle == 0 )
		return;
	// 若 bWait 是 true 的話，就等到有新的資料進來才進行處理
	int n = select( nMaxHandle, &in_set, &out_set, &exc_set, wait_time);//bWait?NULL:&null_time );
	if(n <0 )
		OutputDebugString("\nSelect Error");
	//SockCheckFail( n < 0, "SockMan: Select" );
	if( n == 0 ) return;

	// =============================================================================
	UINT32ArrayList_foreach( m_Connections, {

		Connection* pConn = (Connection*) u32Value;
		// 處理 client 端傳來的資料
		if ( FD_ISSET( pConn->GetSocket(), &in_set ) ) {
			UINT32 u32TotalSize = pConn->m_u32TotalRecvSize;
			pConn->ProcessDataIn();
			m_nNumOfBytesRecv += pConn->m_u32TotalRecvSize - u32TotalSize;
		}
		// 處理寫出去的資料
		if( pConn->m_status != Connection::SHUTDOWNED )
		{
			if ( FD_ISSET( pConn->GetSocket(), &out_set ) ) {

				pConn->ProcessDataOut();
			}
			// 刪除有問題的連線
			if( FD_ISSET( pConn->GetSocket(), &exc_set ) ) {
				cout << "Exc connection "<< pConn->GetSocket() <<endl;
				//pConn->m_pListener->OnDisconnected( i );
				// 跳到下個 connection
			}
		}
		// 處理 close 的資料
		if( pConn->m_status == Connection::SHUTDOWNED ) {
			pConn->m_pListener->OnDisconnected( i );
			delete pConn;
			m_Connections.Remove( i );
		}
	} 
	);


	// =============================================================================
	// any connecting connection error ?
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &exc_set ) ) {
			::closesocket(u32Value);
			INetEventListener* pListener = (INetEventListener*) m_WCList_pListener.ValueAt(i);
			pListener->OnConnectFailed( i );
			m_WCList_sock.Remove( i );
			m_WCList_pListener.Remove( i );
			TRACE1("OnConnectFailed(%d)\n", i );
		}
	}
	);
	// any connecting connection connected ?
	UINT32ArrayList_foreach( m_WCList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &out_set ) ) {
			INetEventListener* pListener = (INetEventListener*) m_WCList_pListener.ValueAt(i);
			m_WCList_sock.Remove(i);
			m_WCList_pListener.Remove( i );
			pListener->OnConnected( AddSocket( sock, pListener ) );
		}
	}
	);

	// =============================================================================
	// New connection?
	// any new connection ?
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		SOCKET sock = u32Value;
		if( FD_ISSET( sock, &in_set ) ) {
			ProcessNewConnect( sock, (INewConnectionListener*)m_ServerSocketList_pListener.ValueAt(i) );
		}
	}
	);

}

void LSAPI cSockMan::SendFlush(timeval* wait_time) {

	fd_set	in_set, out_set, exc_set;
	UINT	nMaxHandle = 0;
	//LList<Connection>::iterator pConn = m_Connections.GetIterator();
	//LList<WC>::iterator pWC = m_WCList.GetIterator();
	//deque<SOCKET>::iterator i;

	// Intialize select SET
	FD_ZERO( &in_set  );
	FD_ZERO( &out_set );
	FD_ZERO( &exc_set );
	
	// add normal connection to set
	UINT32ArrayList_foreach( m_Connections, {
		Connection* p = (Connection*) u32Value;
		SOCKET sock = p->GetSocket();
		nMaxHandle = max( nMaxHandle, sock+1 );

		if( p->NeedRead() )
			FD_SET( sock , &exc_set );
		if( p->NeedRead() && p->HaveSomethingToWrite() ) // 若是有資料需要輸出，才處理
			FD_SET( sock , &out_set );
	}
	);

	if( nMaxHandle == 0 )
		return;
	// 若 bWait 是 true 的話，就等到有新的資料進來才進行處理
	int n = select( nMaxHandle, &in_set, &out_set, &exc_set, wait_time);//bWait?NULL:&null_time );
	if(n <0 )
		OutputDebugString("\nSelect Error");

	//SockCheckFail( n < 0, "SockMan: Select" );
	if( n == 0 ) return;

	// =============================================================================
	UINT32ArrayList_foreach( m_Connections, {
		Connection* pConn = (Connection*) u32Value;
		// 處理寫出去的資料
		if ( FD_ISSET( pConn->GetSocket(), &out_set ) ) {
			pConn->ProcessDataOut();
		}
		// 刪除有問題的連線
		if( FD_ISSET( pConn->GetSocket(), &exc_set ) ) {
			cout << "Exc connection "<< pConn->GetSocket() <<endl;
			//pConn->m_pListener->OnDisconnected( i );
		}
		// 處理 close 的資料
		if( pConn->m_status == Connection::SHUTDOWNED ) {
			pConn->m_pListener->OnDisconnected( i );
			delete pConn;
			m_Connections.Remove( i );
		}
	} 
	);
}

/*HBUFFER
cockMan::
DoCompress( int nSize, void* vpData ) {
	static BYTE cbBuffer[32768];
	
	ASSERT( nSize > (65535/2) );

	HBUFFER h = g_BufferMan.AddBuffer( nSize, vpData );
	int nSrcSize, nNewSize;
	void* vpTmpData;
	g_BufferMan.GetPureBuffer( h, nSrcSize, vpTmpData );

	nNewSize = lzf_compress( vpTmpData, nSrcSize, cbBuffer, nSize );
	// if cannot compress, use old one.
	if( nNewSize == 0 ) {
		return h; // use old handle
	}

	g_BufferMan.Release( h );
	HBUFFER hNew = g_BufferMan.AddBuffer( nNewSize, cbBuffer );
	return hNew;
}
*/
void LSAPI
cSockMan::
Send(UINT32 smid, int nSize, void* vpData, int nPriority ) {

	if(smid == INVALID_UINT32)
			return;

	Connection* pConn = (Connection*) m_Connections.ValueAt( smid );
	if((unsigned int)pConn == INVALID_UINT32)
		return;

//	ASSERT(pConn->m_status==Connection::ESTABLISHED||pConn->m_status==Connection::PEER_SHUTDOWN_SEND);
	if (!(pConn->m_status==Connection::ESTABLISHED||pConn->m_status==Connection::PEER_SHUTDOWN_SEND))
		return;
	ASSERT( nSize <= m_u32MaxPacketSize );

	/*if( m_bIsCompress )
	{ // compress data if needed
	}*/

	//HBUFFER h = g_BufferMan.AddBuffer( nSize, vpData );
	//pConn->SendPkt( h );
	pConn->SendPkt( nSize, vpData );

	m_nNumOfBytesSend += nSize+2;
	//pConn->ProcessDataOut();
	
}

void LSAPI
cSockMan::
SendToAll( int nSize, void* vpData )
{
	ASSERT( nSize <= m_u32MaxPacketSize );

	if( this->m_Connections.Size() == 0 )
		return;

	//TRACE0(" SendPktToAll Add Buffer  \n");
//	HBUFFER h = g_BufferMan.AddBuffer( nSize, vpData );
//	g_BufferMan.AddRef( h, m_Connections.Size() -1 );

	UINT32ArrayList_foreach( m_Connections, {
		Connection* pConn = (Connection*) u32Value;
		if(u32Value == INVALID_UINT32)
			continue;

		if(!(pConn->m_status==Connection::ESTABLISHED||pConn->m_status==Connection::PEER_SHUTDOWN_SEND))
			continue;

		HBUFFER h = g_BufferMan.AddBuffer( nSize, vpData );

		pConn->SendPkt( h );
		m_nNumOfBytesSend += nSize+2;

	}
	);
}

void LSAPI
cSockMan::
SendToMutiple( int nNum, const LNET_PKT_DESTINATION* dest_array, int nSize, void* vpData) {

	ASSERT( nSize <= m_u32MaxPacketSize );
	HBUFFER h = g_BufferMan.AddBuffer( nSize, vpData );
//	TRACE2(" SendPktToMutiple Add Buffer ref=%d handle=%d \n", h, nNum);
	g_BufferMan.AddRef( h, nNum -1 );
	for( int i=0; i< nNum; i++ ) {
		Connection* pConn = (Connection*) m_Connections.ValueAt( dest_array[i].u32ID );

		if((UINT32)pConn == INVALID_UINT32)
			continue;
		
		ASSERT(pConn->m_status==Connection::ESTABLISHED||pConn->m_status==Connection::PEER_SHUTDOWN_SEND);
		pConn->SendPkt( h );
		m_nNumOfBytesSend += nSize+2;
		//pConn->ProcessDataOut();
	}
}
void LSAPI cSockMan::
Close( LNETID id ) {

	TRACE1( "Close connection %d\n", id );
	// 由於沒有清除 packet queue 裡的資料，所以在 close 之後
	// 仍有可能收到關於這個 connection 的 packet
	Connection* pConn = (Connection*) m_Connections.ValueAt( id );
	if (INVALID_UINT32 == (unsigned int)pConn)
		return;
	pConn->m_status = Connection::SHUTDOWNED;
	m_bHaveShutDownConnection = true;
	//pConn->CleanUp();
}
void LSAPI cSockMan::
ShutdownSendPipe( UINT32 smid ) {

	Connection* pConn = (Connection* )m_Connections.ValueAt( smid );
	pConn->ShutdownSendPipe();
}

SOCKET	LSAPI cSockMan::Host(sockaddr_in* TCPAddr, INewConnectionListener* pListener) {

	TRACE3("SockMan::Host( %s:%d , %d )", inet_ntoa(TCPAddr->sin_addr), ntohs(TCPAddr->sin_port), pListener );
	SOCKET ServerSocket = CreateServerSocket( TCPAddr );
	SetSocketNonBlock( ServerSocket, true );
	m_ServerSocketList_sock.Add( ServerSocket );
	m_ServerSocketList_pListener.Add( (UINT32) pListener);
	return ServerSocket;
}

void LSAPI cSockMan::RemoveHost( SOCKET sock ) {
	
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		if( u32Value == sock ) {
			m_ServerSocketList_sock.Remove(i);
			m_ServerSocketList_pListener.Remove(i);
			closesocket( sock );
		}
	}
	);
}

void LSAPI cSockMan::Init(bool bIsCompress)
{
	m_nNumOfBytesRecv = 0;
	m_nNumOfBytesSend = 0;
	m_u32MaxPacketSize = 65535;
	m_bHaveShutDownConnection = false;
	_NeedKey = false;
	_NeedCheckConnect = false;
	//m_bIsCompress = bIsCompress;

	//m_u32CompressSuccess = 0;
	//m_u32CompressFailure = 0;
	//m_u32NumOf_NotCompressedBytes = 0;
	//m_u32NumOf_CompressedBytes = 0;
	Time = clock();
}
void LSAPI cSockMan::UnInit(void)
{
	// close all server socket
	UINT32ArrayList_foreach( m_ServerSocketList_sock, {
		closesocket( u32Value );
	}
	);

	// delete all connections
	UINT32ArrayList_foreach( m_Connections, {
		Connection* pConn = (Connection*) u32Value;
		pConn->m_pListener->OnDisconnected( i );
		delete pConn;
	}
	);

	m_ServerSocketList_sock.Clear();
	m_ServerSocketList_pListener.Clear();
	m_Connections.Clear();
	m_WCList_sock.Clear();
	m_WCList_pListener.Clear();
}

void LSAPI cSockMan::GetPeerAddress( LNETID smid, sockaddr_in* pAddr ) {

	Connection* pConn = (Connection* )m_Connections.ValueAt( smid );
	pConn->GetPeerAddress( (sockaddr*)pAddr );
}

UINT32 LSAPI/*smid*/	cSockMan::AddSocket( SOCKET sock, INetEventListener* pListener ) {

	TRACE0("Add socket\n");
	Connection* pConn = new Connection;

	// 加入新 connection

	UINT32 u32Actor = m_Connections.Add( (UINT32) pConn );
	pConn->Create( sock ,u32Actor);

	//設定此連線為Client
	pConn->SetClient();
	if(_NeedKey)
		pConn->Key(0xffff);
	else
		pConn->Key(0);

	pConn->SetContext( u32Actor );
	pConn->AttachListener( pListener );
	TRACE1(" add connection %d!!!\n",u32Actor);
	return u32Actor;
}

void LSAPI cSockMan::ProcessNewConnect(SOCKET server_sock,INewConnectionListener* pServerListener) {

	//unsigned short	Key[2];
	while( true ) {
		sockaddr_in sa;
		SOCKET sock = GetNewSocket( server_sock, &sa );

		if( IsInvalidSocket( sock ) ) {
			//TRACE0( GetSocketErrorMessage() );
			break;
		}

		Connection* pConn = new Connection;

		// 加入新 connection
		UINT32 u32Actor = m_Connections.Add( (UINT32) pConn );
		pConn->Create( sock, u32Actor );
		pConn->SetContext( u32Actor );
		//----------------------------------------------------------------
		//檢查是否需要送Key的資料(是否要加密)
		CheckPacket PG;
		if(_NeedKey)
		{
			//設定與送Key
			//Key[0] = 0xffff;
			//Key[1] = rand()&0xefff;
			PG.Type = rand()&0xefff;
			//送Key
			pConn->SendPkt( sizeof(PG),&PG);
			pConn->Key(PG.Type);
		}
		//檢查是否有要檢查定時檢測連線封包
		if(_NeedCheckConnect)
		{
			pConn->NeedCheckConnect();

			PG.Type = _Conn_CheckType_NeedCheckConnect_;
			pConn->SendPkt( sizeof(PG),&PG);
		}
		//----------------------------------------------------------------
        INetEventListener* pListener = pServerListener->OnNewConnection( u32Actor );
        pListener->OnConnected( u32Actor );
        pConn->AttachListener( pListener );
        TRACE1(" new connection %d!!!\n",u32Actor);

	}
}

void LSAPI cSockMan::EnumLNETID(  SM_EnumLNETIDCallBack callback, void* pContext ) {

	UINT32ArrayList_foreach( m_Connections, {
		callback( i, pContext );
	}
	);
}
int LSAPI cSockMan::GetNumOfPlayer(void) {
	return m_Connections.Size();
}
void LSAPI cSockMan::EnumConnections(LNET_EnumPlayersCallBack callback, void* vpContext) throw() {
	sockaddr_in addr;
	UINT32ArrayList_foreach( m_Connections, {
		GetPeerAddress( i, &addr );
		callback( i, &addr, vpContext );
	}
	);
}



UINT32  LSAPI 	cSockMan::GetContext(UINT32 smid){

	Connection* pConn = (Connection*)m_Connections.ValueAt(smid);
	return pConn->GetContext(); 
}
void   LSAPI	cSockMan::SetContext(UINT32 smid, UINT32 c) {

	Connection* pConn = (Connection*)m_Connections.ValueAt(smid);
	pConn->SetContext( c );
}

LNETID  LSAPI 	cSockMan::AddConnection( Connection* pConn ) {

	UINT32 u32Actor = m_Connections.Add( (UINT32) pConn );
	TRACE0(" add new connection !!!\n");
	return u32Actor;
}


UINT32 LSAPI  cSockMan::GetPacketLeftInSendQueue( LNETID smid ) {

	Connection* pConn = (Connection*)m_Connections.ValueAt(smid);
	if((unsigned int)pConn == INVALID_UINT32)
		return 0;
	return pConn->m_WrPacketList.Size();
}

void LSAPI  cSockMan::GetCompressSuccessVSFailure( int& nSuccess, int& nFailed ) {
}
int	 LSAPI cSockMan::GetNumOf_NotCompressedBytes( void ){
    return 0;
}
int	 LSAPI cSockMan::GetNumOf_CompressedBytes( void ){
    return 0;
}

UINT32  LSAPI 	cSockMan::GetNumOfConnections( void ) {

	return m_Connections.Size();
}
void  LSAPI cSockMan::SetMaxPacketSize( UINT32 u32Size ) {
	ASSERT( u32Size <= 65535 );
	m_u32MaxPacketSize = u32Size;
}

bool	LSAPI cSockMan::CheckPacketEmpty()
{

		UINT32ArrayList_foreach( m_Connections, {
			Connection* pConn = (Connection*) u32Value;
			if(u32Value  == INVALID_UINT32)
				continue;
			
			if(pConn->m_WrPacketList.Size() != 0)
				return false;
		}
		);

	return true;
}
#pragma warning( pop )
#pragma optimize("", on) 