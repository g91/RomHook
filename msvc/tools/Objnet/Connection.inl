//====================================================================================================

inline SOCKET Connection::GetSocket(void)
{ return m_sock; }

//====================================================================================================
// Send & SendPkt 主要試用來做 mode 檢查
inline void Connection::ShutdownSendPipe(void) {
//	if( IsInvalidSocket( m_sock ) )
//		throw LSockException( 0, "Sock invalid !" );
//	m_WrMutex.Lock();
	m_WrPacketList.Write( INVALID_BUFFERHANDLE );// push_back( PACKET(m_dwPKTIndex,INVALID_BUFFERHANDLE) );
//	m_WrMutex.Unlock();
}

inline void
Connection::SendPkt( int nSize, void* vpData ) {
	//ASSERT( nSize <= CONNECTION_MAX_WRITE_PACKET_SIZE );

	//TRACE0(" SendPkt1 Add Buffer  \n");
	HBUFFER hBuffer = g_BufferMan.AddBuffer( nSize, vpData );

	SendPkt( hBuffer );
//	TRACE2("\nSend = %x connect=%x",*((short*)vpData),this );
}

inline void
Connection::SendPkt( HBUFFER hBuffer ) {

//	if( IsInvalidSocket( m_sock ) )
//		throw LSockException( 0, "Sock invalid !" );

	//try {
//	m_WrMutex.Lock();
	m_WrPacketList.Write( hBuffer );
//	m_WrMutex.Unlock();
	//} catch( LException& e ) {
	//	TRACE1(" Mutex raise exception: %s\n", e.GetMessage() );
	//}
}



#define GET_ADDRESS( func )\
{\
	int size = sizeof(*addr);\
	if( IsSocketError(func(m_sock, addr, &size) ) )\
		throw LSockException(0);\
}\

inline void Connection::GetPeerAddress(sockaddr* addr) //throw SockException
{
	GET_ADDRESS(getpeername);
}
inline void Connection::GetSockAddress(sockaddr* addr) //throw SockException
{
	GET_ADDRESS(getsockname);
}
//====================================================================================================


inline bool Connection::HaveSomethingToWrite(void)
{
	return (!m_WrPacketList.IsEmpty() || m_hWrBuffer != INVALID_BUFFERHANDLE );
}

