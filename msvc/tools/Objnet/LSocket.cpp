// LSocket.cpp : Defines the entry point for the DLL application.
//

//#include "stdafx.h"
#include <map>

#include "LSocket.h"

#include "MyDebug.h"
#include "LSocket.h"
#include <wsipx.h>
struct ErrStruct {
	DWORD dwErr;
	char* szErr;
} s_ErrMsg[] =
{{11001,"WSAHOST_NOT_FOUND: Host not found"}
,{11002,"WSATRY_AGAIN: Non-Authoritative Host not found"}
,{11003,"WSANO_RECOVERY: Non-Recoverable errors: FORMERR, REFUSED, NOTIMP"}
,{11004,"WSANO_DATA: Valid name, no data record of requested type"}
,{10091,"WSASYSNOTREADY: Network SubSystem is unavailable"}
,{10092,"WSAVERNOTSUPPORTED: WINSOCK DLL Version out of range"}
,{10093,"WSANOTINITIALISED: Successful WSASTARTUP not yet performed"}
,{10064,"WSAEHOSTDOWN: Host is down"}
,{10065,"WSAEHOSTUNREACH: No Route to Host"}
,{10066,"WSAENOTEMPTY: Directory not empty"}
,{10067,"WSAEPROCLIM: Too many processes"}
,{10068,"WSAEUSERS: Too many users"}
,{10069,"WSAEDQUOT: Disc Quota Exceeded"}
,{10070,"WSAESTALE: Stale NFS file handle"}
,{10071,"WSAEREMOTE: Too many levels of remote in path"}
,{10048,"WSAEADDRINUSE: Address already in use"}
,{10049,"WSAEADDRNOTAVAIL: Can't assign requested address"}
,{10050,"WSAENETDOWN: Network is down"}
,{10051,"WSAENETUNREACH: Network is unreachable"}
,{10052,"WSAENETRESET: Net dropped connection or reset"}
,{10053,"WSAECONNABORTED: Software caused connection abort"}
,{10054,"WSAECONNRESET: Connection reset by peer"}
,{10055,"WSAENOBUFS: No buffer space available"}
,{10056,"WSAEISCONN: Socket is already connected"}
,{10057,"WSAENOTCONN: Socket is not connected"}
,{10058,"WSAESHUTDOWN: Can't send after socket shutdown"}
,{10059,"WSAETOOMANYREFS: Too many references, can't splice"}
,{10060,"WSAETIMEDOUT: Connection timed out"}
,{10061,"WSAECONNREFUSED: Connection refused"}
,{10062,"WSAELOOP: Too many levels of symbolic links"}
,{10063,"WSAENAMETOOLONG: File name too long"}
,{10035,"WSAEWOULDBLOCK: Operation would block"}
,{10036,"WSAEINPROGRESS: Operation now in progress"}
,{10037,"WSAEALREADY: Operation already in progress"}
,{10038,"WSAENOTSOCK: Socket operation on non-socket"}
,{10039,"WSAEDESTADDRREQ: Destination address required"}
,{10040,"WSAEMSGSIZE: Message too long"}
,{10041,"WSAEPROTOTYPE: Protocol wrong type for socket"}
,{10042,"WSAENOPROTOOPT: Bad protocol option"}
,{10043,"WSAEPROTONOSUPPORT: Protocol not supported"}
,{10044,"WSAESOCKTNOSUPPORT: Socket type not supported"}
,{10045,"WSAEOPNOTSUPP: Operation not supported on socket"}
,{10046,"WSAEPFNNOSUPPORT: Protocol family not supported"}
,{10047,"WSAEAFNNOSUPPORT: Address family not supported by p}rotocol family"}
,{10022,"WSAEINVAL: Invalid argument"}
,{10024,"WSAEMFILE: Too many open files"}
,{10000,"[0] No Error"}
,{10004,"WSAEINTR: Interrupted system call"}
,{10009,"WSAEBADF: Bad file number"}
,{10013,"WSACCESS: Permission denied"}
,{10014,"WSAEFAULT: Bad address"}};

//#include <hash_map>

using std::map;
map< DWORD, char* > s_ErrMap;

void LSAPI InitSock(void)
{
#ifdef __BORLANDC__
#pragma warn -8084
#endif
	WORD wVersionRequested = MAKEWORD( 1, 1 );
#ifdef __BORLANDC__
#pragma warn +8084
#endif
	WSADATA wsaData;
	int err = WSAStartup( wVersionRequested, &wsaData );
	SockCheckFail( err != 0, "No useable WINSOCK.DLL" );

	for(int i = 0; i< sizeof(s_ErrMsg)/sizeof(ErrStruct); i ++ ) {
		s_ErrMap[ s_ErrMsg[i].dwErr ] = s_ErrMsg[i].szErr;
	}
	return;
}

void LSAPI UninitSock(void) {
	WSACleanup();
}


const char* LSAPI GetSockErrString(void) {
	char* sz = NULL;

	DWORD WSAErr = WSAGetLastError();
	if (WSAErr == 0)           /* If error passed is 0, use the */
		WSAErr = WSABASEERR;     /*  base resource file number */

	if (WSAErr >= WSABASEERR)  /* Valid Error code? */
		/* get error string from the table in the Resource file */
		sz = s_ErrMap[ WSAErr ];

	return (sz);
}
const char* LSAPI GetSockErrString(SOCKET s) {

	char* sz = NULL;

	int k = sizeof(int);
	int WSAErr = 0;
	getsockopt( s, SOL_SOCKET, SO_ERROR, (char*)&WSAErr, &k );

	if (WSAErr == 0)           /* If error passed is 0, use the */
		WSAErr = WSABASEERR;     /*  base resource file number */

	if (WSAErr >= WSABASEERR)  /* Valid Error code? */
		/* get error string from the table in the Resource file */
		sz = s_ErrMap[ WSAErr ];

	return (sz);
}



bool LSAPI SetSocketNonBlock( SOCKET s, bool b ) { 
	u_long t; 
	t = b?1:0; 
	return !IsSocketError( ioctlsocket( s, FIONBIO, &t )); 
}

inline void LSAPI __TCPConnect__( SOCKET sock, sockaddr_in& sa ) {
	int result = connect( sock, (sockaddr *) &sa, sizeof(sa) );

	if( !IsSocketError( result ) )
		return;

	DWORD err = WSAGetLastError();
	closesocket( sock );
	WSASetLastError( err );
#ifdef __BORLANDC__
#pragma warn -8008
#endif
	SockCheckFail( true, " Non_Block_connect connect " );
#ifdef __BORLANDC__
#pragma warn +8008
#endif
}

#if !defined( WIN32 )
#define  WSAGetLastError() errno
#define  WSASetLastError(x) { errno = x; }
#endif

SOCKET LSAPI TCPConnect( sockaddr_in* sa )
{
	ASSERT( sa->sin_family == AF_INET );
	SOCKET sock;
	
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	SockCheckFail( IsInvalidSocket(sock), " Block_Connect connect ");

	int result = connect( sock, (sockaddr *) sa, sizeof(*sa) );

	if( !IsSocketError( result ) )
		return sock;

	DWORD err = WSAGetLastError();
	closesocket( sock );
	WSASetLastError(err);
#ifdef __BORLANDC__
#pragma warn -8008
#endif
	SockCheckFail( true, " Non_Block_connect connect " );
#ifdef __BORLANDC__
#pragma warn +8008
#endif
}

SOCKET LSAPI NonBlock_TCPConnect( sockaddr_in* sa ) //throw( SockException )
{
	ASSERT( sa->sin_family == AF_INET );
	SOCKET sock;
	
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	SockCheckFail( IsInvalidSocket(sock), " Non_Block_connect socket ");
	SetSocketNonBlock( sock, true );

	int result = connect( sock, (sockaddr *) sa, sizeof(*sa) );

	if( IsSocketError( result ) )
		if( WouldSocketBlocked() )
			return sock;
	if( !IsSocketError( result ) )
		return sock;

	DWORD err = WSAGetLastError();
	closesocket( sock );
	WSASetLastError( err );
#ifdef __BORLANDC__
#pragma warn -8008
#endif
	SockCheckFail( true, " Non_Block_connect connect " );
#ifdef __BORLANDC__
#pragma warn +8008
#endif
}




SOCKET LSAPI CreateServerSocket( sockaddr_in* sa ) {

	SOCKET	sock;
	int		x = 1;
	int		result;

	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( IsInvalidSocket( sock ) )
		goto FAILED;

//	result = setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, (char *) &x, sizeof( x ) );
//	if( IsSocketError( result ) )
//		goto FAILED;

//	result = setsockopt( sock, IPPROTO_TCP, TCP_NODELAY, (char *) &x, sizeof( x ) );
//	if( IsSocketError( result ) )
//		goto FAILED;


	result = bind( sock, (struct sockaddr *) sa, sizeof( *sa ) );
	if( IsSocketError( result ) )
		goto FAILED;

	result = listen( sock, 20 );
	if( IsSocketError( result ) )
		goto FAILED;

	return sock;
FAILED:
	closesocket( sock );
	return sock;
}
SOCKET LSAPI GetNewSocket( SOCKET s, sockaddr_in* addr ) {

	SOCKET sock;
	int nAddrLen = sizeof( sockaddr_in );
	sock = accept( s, ( sockaddr *)addr, &nAddrLen );

	int	x = 1;
	int result = setsockopt( sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &x, sizeof( x ) );
//	result = setsockopt( sock, IPPROTO_TCP, TCP_NODELAY, (char *) &x, sizeof( x ) );

	return sock;
}

bool LSAPI IsTCP_IPAvailable(void)throw(){

	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
	closesocket( sock );
	if( IsInvalidSocket( sock ) )
		return false;
	else
		return true;
}

bool LSAPI IsIPXAvailable(void) throw(){

	SOCKET sock = sock = socket ( AF_IPX, SOCK_DGRAM, NSPROTO_IPX );
	closesocket( sock );
	if( IsInvalidSocket( sock ) )
		return false;
	else 
		return true;
}

unsigned long LSAPI GetHostIDByName( const char* szHostName ) {

	static unsigned int nRand;
	hostent* p = gethostbyname( szHostName );
	if( p == NULL )
		return 0;
	
	// search how many address do this server have
	int n=0;
	while( p->h_addr_list[n] != 0 )
		n++;

	n = nRand%n;
	nRand++;
	return *((unsigned long*)p->h_addr_list[n]);
}

#define MAXHOSTNAME 1024
u_long LSAPI GetHostID(void) throw(){

    char szLclHost [MAXHOSTNAME];
    LPHOSTENT lpstHostent;
    SOCKADDR_IN stLclAddr;
    SOCKADDR_IN stRmtAddr;
    int nAddrSize = sizeof(SOCKADDR);
    SOCKET hSock;
    int nRet;
    
    /* Init local address (to zero) */
    stLclAddr.sin_addr.s_addr = INADDR_ANY;
    
    /* Get the local hostname */
    nRet = gethostname(szLclHost, MAXHOSTNAME); 
    if (nRet != SOCKET_ERROR) {
      /* Resolve hostname for local address */
      lpstHostent = gethostbyname((LPSTR)szLclHost);
      if (lpstHostent)
        stLclAddr.sin_addr.s_addr = *((u_long FAR*) (lpstHostent->h_addr));
    } 
    
    /* If still not resolved, then try second strategy */
    if (stLclAddr.sin_addr.s_addr == INADDR_ANY) {
      /* Get a UDP socket */
      hSock = socket(AF_INET, SOCK_DGRAM, 0);
      if (hSock != INVALID_SOCKET)  {
        /* Connect to arbitrary port and address (NOT loopback) */
        stRmtAddr.sin_family = AF_INET;
        stRmtAddr.sin_port   = htons(IPPORT_ECHO);
        stRmtAddr.sin_addr.s_addr = inet_addr("128.127.50.1");
        nRet = connect(hSock,
                       (LPSOCKADDR)&stRmtAddr,
                       sizeof(SOCKADDR));
        if (nRet != SOCKET_ERROR) {
          /* Get local address */
          getsockname(hSock, 
                      (LPSOCKADDR)&stLclAddr, 
                      (int FAR*)&nAddrSize);
        }
        closesocket(hSock);   /* we're done with the socket */
      }
    }
    return (stLclAddr.sin_addr.s_addr);

}

#if defined( _WIN32 )
#else
inline bool SetSocketNonBlock( SOCKET s, bool b ) { 
/*  Technically, fcntl(soc, F_SETFL, O_NONBLOCK) is incorrect since it
clobbers all other file flags. Generally one gets away with it since
the other flags (O_APPEND for example) don't really apply much to
sockets. In a similarly rough vein, you would use fcntl(soc, F_SETFL,
0) to go back to blocking mode.

To do it right, use F_GETFL to get the current flags, set or clear the
O_NONBLOCK flag, then use F_SETFL to set the flags.
*/
	int v = fcntl( s, F_GETFL );

	if( b )
		v |= O_NONBLOCK;
	else 
		v ^= O_NONBLOCK;

	return !IsSocketError( fcntl( s, F_SETFL, v )); 
}
#endif