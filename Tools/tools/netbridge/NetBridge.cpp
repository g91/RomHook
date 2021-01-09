#pragma warning (disable:4949)
#pragma unmanaged

#ifndef _NB_USE_OLD_ENGINE
#include "NetBridge_IOCP.h"
#include "NetBridge_ASIO.h"
#else
#include "NetBridge_OLDENGINE.h"
#endif

HANDLE					CNetBridge::m_pNetEventHandle[ MAXIMUM_WAIT_OBJECTS ];
DWORD					CNetBridge::m_dwNetHandleIndex	= 0;
CNetBridge*				CNetBridge::m_pNetPoint[ MAXIMUM_WAIT_OBJECTS ];
//DWORD					CNetBridge::m_dwEnterTime = 0;
HANDLE					CNetBridge::m_pNetMainEvent	= NULL;
vector< CNetBridge* >*	CNetBridge::m_pvecCore		= NULL;
vector< CNetBridge* >*	CNetBridge::m_pvecNewCore	= NULL;
DWORD					CNetBridge::m_refCount		= 0;

//CCritcalsection			CNetBridge::g_csEngineCore;
CNetBridge*				g_pNetEngineCore			= NULL;
CNetBridge*				g_pNetEngineAsioCore		= NULL;
DWORD					g_dwNetEngineRefCount		= 0;
//vector< CNetBridge* >	g_vecNetBridge;

#ifdef DF_PACKET_LOG
DWORD			CNetBridge::m_dwPacketLog = 0;
#endif




CNetBridge::CNetBridge()
{
	m_dwEnterTime	= GetTickCount();

	if( m_pNetMainEvent == NULL )
		m_pNetMainEvent = CreateEvent( NULL, FALSE, FALSE, NULL );




}

CNetBridge::~CNetBridge()
{
	if( m_pNetMainEvent != NULL )
	{
		CloseHandle( m_pNetMainEvent );
		m_pNetMainEvent = NULL;
	}
}

CNetBridge*		CreateNetBridge		( bool bManage, int iNumThread )
{

	CNetBridge* pBridge												= (CNetBridge*)new CNetBridge_IOCP;	

	//if( bSingleCore == false )
	//{
	//g_vecNetBridge.push_back( pBridge );

	if( CNetBridge::m_pvecCore == NULL )
	{
		CNetBridge::m_pvecCore		= new vector< CNetBridge* >;

	}

	if( CNetBridge::m_pvecNewCore == NULL )
	{
		CNetBridge::m_pvecNewCore		= new vector< CNetBridge* >;

	}

	//if( bManage == true )
	{
		CNetBridge::m_pvecNewCore->push_back( pBridge );
	}

	//CNetBridge::m_pNetEventHandle[ CNetBridge::m_dwNetHandleIndex ] = ((CNetBridge_IOCP*)pBridge)->m_hMsgEvent;
	//CNetBridge::m_pNetPoint[ CNetBridge::m_dwNetHandleIndex ]		= pBridge;	
	//CNetBridge::m_dwNetHandleIndex++;	
	//}

	pBridge->Init( 1 );


	return pBridge;
}
//-------------------------------------------------------------
CNetBridge*	CreateAsio			( bool bManage )
{	



	/*
	CNetBridge* pBridge	= (CNetBridge*)new CNetBridge_ASIO;	

	if( CNetBridge::m_pvecCore == NULL )
	CNetBridge::m_pvecCore		= new vector< CNetBridge* >;

	if( CNetBridge::m_pvecNewCore == NULL )
	CNetBridge::m_pvecNewCore	= new vector< CNetBridge* >;

	if( bManage != false )
	CNetBridge::m_pvecNewCore->push_back( pBridge );

	pBridge->Init( 2 );

	return pBridge;
	*/

//	g_csEngineCore.Enter( "CreateNetBridge" );
	{
		g_dwNetEngineRefCount++;

		if( g_pNetEngineAsioCore == NULL )
		{
			g_pNetEngineAsioCore = (CNetBridge*)new CNetBridge_ASIO;
			g_pNetEngineAsioCore->Init( 2 );
			g_pNetEngineAsioCore->m_refCount++;
		}

		/*
		if( CNetBridge::m_pvecCore == NULL )
		CNetBridge::m_pvecCore		= new vector< CNetBridge* >;

		if( CNetBridge::m_pvecNewCore == NULL )
		CNetBridge::m_pvecNewCore	= new vector< CNetBridge* >;

		CNetBridge::m_pvecNewCore->push_back( pBridge );
		*/

	}
//	g_csEngineCore.Leave( "CreateNetBridge" );

	return g_pNetEngineAsioCore;



}
//-------------------------------------------------------------
void DeleteNetBridge		( CNetBridge* pBridge )
{ 
	if ( pBridge == NULL )
		return;

	CNetBridge::WaitAll( 10 );

	if( CNetBridge::m_pvecCore != NULL )
	{
		for( vector< CNetBridge* >::iterator it = CNetBridge::m_pvecCore->begin(); it != CNetBridge::m_pvecCore->end(); it++ )
		{
			if ( (*it) == pBridge )
			{
				CNetBridge::m_pvecCore->erase( it );

				if( CNetBridge::m_pvecCore->size() == 0 )
				{
					delete CNetBridge::m_pvecCore;
					CNetBridge::m_pvecCore = NULL;				
				}

				break;
			}
		}
	}

	if( CNetBridge::m_pvecNewCore != NULL )
	{
		delete CNetBridge::m_pvecNewCore;
		CNetBridge::m_pvecNewCore = NULL;
	}


	pBridge->Shutdown();
	delete pBridge;
}

//-------------------------------------------------------------

DWORD	CNetBridge::WaitAll				( DWORD dwTime )
{	
	DWORD dwTimeNow	= GetTickCount();

	if( m_pvecNewCore != NULL )
	{
		for( vector< CNetBridge* >::iterator it = CNetBridge::m_pvecNewCore->begin(); it != CNetBridge::m_pvecNewCore->end(); it++ )
		{
			CNetBridge::m_pvecCore->push_back( *it );
		}
		CNetBridge::m_pvecNewCore->clear();
	}

	

	// Check Event, if we got event, we flush
	DWORD dwReturn = WaitForSingleObject( CNetBridge::m_pNetMainEvent, dwTime );

	if( dwReturn != WAIT_TIMEOUT )
	{
		for( vector< CNetBridge* >::iterator it = CNetBridge::m_pvecCore->begin(); it != CNetBridge::m_pvecCore->end(); it++ )
		{
			CNetBridge_IOCP* pNetBridge = (CNetBridge_IOCP*)*it;

			if( pNetBridge->m_bEvent == true )
			{
				pNetBridge->m_bEvent		= false;
				pNetBridge->m_dwEnterTime	= dwTimeNow;
				pNetBridge->Flush();

			}
		}
	}

	// Check time mark, if timenow bigger than netcore's enter time, this is the part that to check disconnect socket and other
	for( vector< CNetBridge* >::iterator it = CNetBridge::m_pvecCore->begin(); it != CNetBridge::m_pvecCore->end(); it++ )
	{
		CNetBridge_IOCP* pNetBridge = (CNetBridge_IOCP*)*it;

		if( (dwTimeNow - pNetBridge->m_dwEnterTime) >= 20)
		{
			pNetBridge->m_dwEnterTime = dwTimeNow;
			pNetBridge->Flush();
		}
	}

	return dwReturn;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
/*
DWORD	CNetBridge::WaitAll				( DWORD dwTime )
{
DWORD dwReturn	= WaitForMultipleObjects( CNetBridge::m_dwNetHandleIndex, CNetBridge::m_pNetEventHandle, false, dwTime );
DWORD dwTimeNow	= GetTickCount();

if( dwReturn != WAIT_TIMEOUT || dwTimeNow > CNetBridge::m_dwEnterTime )
{		
CNetBridge::m_dwEnterTime = GetTickCount() + 100;

//DWORD dwIndex = dwReturn - WAIT_OBJECT_0;	
DWORD dwIndex = 0;
CNetBridge::m_pNetPoint[ dwIndex ]->Flush();

dwIndex++;

while( dwIndex < CNetBridge::m_dwNetHandleIndex )
{
//if( WaitForSingleObject( CNetBridge::m_pNetEventHandle[ dwIndex ], 0 ) != WAIT_TIMEOUT )
//{
CNetBridge::m_pNetPoint[ dwIndex ]->Flush();
//}

dwIndex++;
}
}
return dwReturn;
}
*/
//-------------------------------------------------------------
DWORD	ConvertIP( const char* pszIP )
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

void ConvertIPtoString	( DWORD dwIP, char* pszIP )
{
	BYTE* pIP = (BYTE*)&dwIP;
	if( pszIP != NULL )
	{
		sprintf( pszIP, "%d.%d.%d.%d", *pIP, *(pIP+1), *(pIP+2), *(pIP+3) );
	}
}

/*
void CNetBridge::Send				( DWORD dwNetID, DWORD dwSize, PVOID pBuffer, DWORD dwPriority, DWORD dwFlag )
{
_Send( dwNetID, dwSize, pBuffer, dwPriority, dwFlag );

#ifdef DF_PACKET_LOG
Struct_PacketLog Log;
Log.dwID			= 0x12345678;
Log.dwPacketID		= *(DWORD*)pBuffer;
Log.dwTime			= GetTickCount();
m_dwPacketLog++;

_Send( dwNetID, sizeof( Log ), &Log, 0, 0 );
#endif

}
*/
#pragma managed