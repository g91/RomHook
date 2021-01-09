#pragma warning (disable:4949)
#include "NetBridge_ASIO.h"

#pragma unmanaged

//--------------------------------------------------------------
CNetBridge_ASIO::CNetBridge_ASIO( void )
{
	m_pAsio				= NULL;
	m_EngineType		= NB_ENGINE_ASIO;

#if NET_BIRDGE_ASIO_DEBUG_PRINT
    OutputDebugString("CNetBridge_ASIO::CNetBridge_ASIO()\n");
#endif
}
//--------------------------------------------------------------
CNetBridge_ASIO::~CNetBridge_ASIO( void )
{
#if NET_BIRDGE_ASIO_DEBUG_PRINT
    OutputDebugString("CNetBridge_ASIO::CNetBridge_ASIO()\n");
#endif
}
//--------------------------------------------------------------
int CNetBridge_ASIO::Init( int iNumThread )
{
	if( m_pAsio == NULL )
		m_pAsio = MyAsio::CreateMyAsio();

	return 0;
}
//--------------------------------------------------------------
int CNetBridge_ASIO::Host( DWORD dwIP , WORD wPort, CEventObj* pEventObj, BOOL bEncryption /*= false */, BOOL bCompress /*= false*/, BOOL bTelnet /*= false*/, PVOID pContext /*= NULL */ )
{
	if( m_pAsio == NULL )
		return 0;

	dwIP = CNetBridge_ASIO::Convert( dwIP );
	return m_pAsio->Host( dwIP, wPort, pEventObj );
}
//--------------------------------------------------------------
int CNetBridge_ASIO::Connect( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext /*= NULL */ )
{
	if( m_pAsio == NULL )
		return 0;

	dwIP = CNetBridge_ASIO::Convert( dwIP );
	return m_pAsio->Connect( dwIP, wPort, pEventObj );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::Flush()
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->Flush();
}
//--------------------------------------------------------------
void CNetBridge_ASIO::Close( DWORD dwNetID )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->Close( dwNetID );
}
//--------------------------------------------------------------
bool CNetBridge_ASIO::Shutdown()
{
	if( m_pAsio == NULL )
		return false;

	return m_pAsio->Shutdown();
}
//--------------------------------------------------------------
void CNetBridge_ASIO::GetConnectInfo( DWORD dwNetID, DWORD* pdwIP, WORD* pwPort )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->GetConnectInfo( dwNetID, (unsigned int*)pdwIP, (unsigned short*)pwPort );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::SetOutPutCB( pfOutPutCB pFun )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->SetOutPutCB( pFun );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::Send( DWORD dwNetID, DWORD dwSize, PVOID pData )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->Send( dwNetID, dwSize, pData );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::SendWithBuff( DWORD dwNetID, DWORD dwSize1, PVOID pData1, DWORD dwSize2, PVOID pData2 )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->SendWithBuff( dwNetID, dwSize1, pData1, dwSize2, pData2 );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::SendToAll( DWORD dwSize, PVOID pPacket )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->SendToAll( dwSize, pPacket );
}
//--------------------------------------------------------------
void CNetBridge_ASIO::SendToAllWithBuff( DWORD dwSize1, PVOID pPacket1, DWORD dwSize2, PVOID pPacket2 )
{
	if( m_pAsio == NULL )
		return;

	m_pAsio->SendToAllWithBuff( dwSize1, pPacket1, dwSize2, pPacket2 );
}
//--------------------------------------------------------------
DWORD CNetBridge_ASIO::Convert( DWORD dwIP )
{
	char* IP_Addr_Point = (char*)&dwIP;
	swap( IP_Addr_Point[0] , IP_Addr_Point[3] );
	swap( IP_Addr_Point[1] , IP_Addr_Point[2] );
	return dwIP;
}
//--------------------------------------------------------------

#pragma managed