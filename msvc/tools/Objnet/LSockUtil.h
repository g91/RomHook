#ifndef _LSOCKUTIL_H_
#define _LSOCKUTIL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __BORLANDC__
#pragma warn -8071
#endif

#pragma comment(lib, "ws2_32.lib")


inline void MAKE_IP_ADDRESS( sockaddr_in* sa, const char* szAddr, UINT uPort ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= inet_addr( szAddr );
	sa->sin_port 		= htons( uPort );
}

inline void MAKE_IP_ADDRESS( sockaddr_in* sa, unsigned long lAddr, int uPort ) {

    memset( sa, 0, sizeof( *sa ) );
    sa->sin_family		= AF_INET;
    sa->sin_addr.s_addr	= lAddr;
    sa->sin_port 		= htons(uPort);
}

inline void MAKE_IPANY_ADDRESS( sockaddr_in* sa, UINT port ) {

	memset( sa, 0, sizeof( *sa ) );
	sa->sin_family		= AF_INET;
	sa->sin_addr.s_addr	= INADDR_ANY;
	sa->sin_port 		= htons( port );
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



inline bool CheckValidTCPHostAddress( sockaddr_in* a ) {
	return ( a->sin_family == AF_INET && a->sin_addr.s_addr == INADDR_ANY );
}

inline unsigned long GetHostIDByName( const char* szHostName ) {

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





#ifdef __BORLANDC__
#pragma warn +8071
#endif

#endif // _LSOCKUTIL_H_