#ifndef _L_SOCKET_H_
#define _L_SOCKET_H_
#pragma warning (disable:4949)

#ifndef _LIB
#ifdef LSOCKET_EXPORTS
#define LSOCKET_API __declspec(dllexport)
#else
#define LSOCKET_API __declspec(dllimport)
#endif

#else
#define LSOCKET_API 
#endif

#include "LBaseType.h"
#include "LException.h"

class LSockException:public LException
{
public:
#define Sock_NotConnected	100
#define Sock_WouldBlocked	101
#define Sock_BufferTooSmall	102
	LSockException(int id)throw():LException(id){};
	LSockException(int id, const char* s):LException(id,s){};
};
#define SockCheckFail( b, str ) \
	if( b ) {\
		TRACE2("%s Sock error occur !!\n%s ", str,GetSockErrString() );\
		throw LSockException( GetLastError(), GetSockErrString() );\
	}
#pragma managed

#if defined( _WIN32 )

	#pragma comment(lib, "ws2_32.lib")
	#undef	FD_SETSIZE
	#define FD_SETSIZE 4096
	//#include <winsock2.h>
	#include <winsock.h>
    #pragma unmanaged

	LSOCKET_API void LSAPI InitSock(void);
	LSOCKET_API void LSAPI UninitSock(void);

	inline bool		IsInvalidSocket( SOCKET  sock ) { return sock == INVALID_SOCKET; }
	inline bool		IsSocketError( int  result ) { return result == SOCKET_ERROR; }
	inline bool		WouldSocketBlocked( void ) { return ( WSAGetLastError() == WSAEWOULDBLOCK ); }
	inline void		usleep( UINT u ) { Sleep(u); }
	inline SOCKET	accept(SOCKET s, sockaddr * addr,UINT* addrlen) { return accept( s, addr, (int*) addrlen ); }
	inline int		recv(SOCKET s, void *buf, int len, unsigned int flags) { return recv( s,(char FAR*) buf, len, (int)flags ); }

    
#else	// not WIN32

	#include <unistd.h>
//	#include <sys/types.h>
//	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netipx/ipx.h>
	#include <arpa/inet.h>
	#include <fcntl.h>
	#include <errno.h>
    #pragma unmanaged
	typedef int SOCKET;
	typedef char BYTE;
	#define UINT unsigned int

	#define INVALID_SOCKET -1

	inline void InitSock(void) {}
	inline void UninitSock(void){}
	inline bool IsInvalidSocket( SOCKET  sock ) { return sock < 0; }
	inline bool IsSocketError( int  result ) { return result < 0; }
	inline bool WouldSocketBlocked( void ) { return ( errno == EWOULDBLOCK ); }
	inline int  closesocket( SOCKET sock ) { return close( sock ); }

	#define SockCheckFail( b, str )\
		if( b ) {\
			perror( str );\
			throw SockException(errno, str);\
		}
#endif	// WIN32



//===================================================================================================
LSOCKET_API SOCKET  LSAPI TCPConnect( sockaddr_in* sa );
LSOCKET_API SOCKET  LSAPI NonBlock_TCPConnect( sockaddr_in* sa );
//===================================================================================================
LSOCKET_API SOCKET  LSAPI CreateServerSocket( sockaddr_in* sa );
LSOCKET_API SOCKET  LSAPI GetNewSocket( SOCKET s, sockaddr_in* addr );
//===================================================================================================
LSOCKET_API bool  LSAPI IsTCP_IPAvailable(void) throw() ;
LSOCKET_API bool  LSAPI IsIPXAvailable(void) throw();
//===================================================================================================
LSOCKET_API unsigned long LSAPI GetHostIDByName( const char* szHostName );
LSOCKET_API u_long LSAPI GetHostID(void) throw();

LSOCKET_API bool	LSAPI SetSocketNonBlock( SOCKET s, bool b );
LSOCKET_API void	LSAPI SockGetLocalAddress( sockaddr& sa );
//===================================================================================================
LSOCKET_API const char*  LSAPI GetSockErrString(void);
LSOCKET_API const char*  LSAPI GetSockErrString(SOCKET);
//===================================================================================================
inline void MAKE_IP_ADDRESS( sockaddr_in* sa, char* szAddr, UINT uPort ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= inet_addr( szAddr );
	sa->sin_port 		= htons( uPort );
}

inline void MAKE_IPANY_ADDRESS( sockaddr_in* sa, UINT port ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= INADDR_ANY;
	sa->sin_port 		= htons( port );
}

inline void MAKE_IP_ADDRESS( sockaddr_in* sa, unsigned long lAddr, int uPort ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= lAddr;
	sa->sin_port 		= htons(uPort);
}

inline void MAKE_IP_ADDRESS_IN_PRIME( sockaddr_in* sa, u_long lAddr, u_short uPort ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= lAddr;
	sa->sin_port 		= uPort;
}

inline bool IsEqualIPAddress(const sockaddr_in* a,const sockaddr_in* b) {
	return ( a->sin_addr.s_addr == b->sin_addr.s_addr &&
		a->sin_port == b->sin_port );
}

inline bool IsPrivateIPAddress( in_addr x ) {

	// Class A 10.0.0.0 ~ 10.255.255.255
	if( (x.S_un.S_addr & 0x000000ff) == 10 )
		return true;
	x.S_un.S_addr &= 0x0000ffff;
	// Class B 172.16.0.0 ~ 172.31.255.255 
	if( x.S_un.S_addr == 0x000010ac )
		return true;
	// Class C 192.168.0.0 ~ 192.168.255.255
	if( x.S_un.S_addr == 0x0000a8c0 )
		return true;
	return false;
}

#pragma managed

#endif // _L_SOCKET_H_
