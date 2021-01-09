#include "RaApexClient.h"




//#pragma comment (lib, "SHInterfaceClient")
//#pragma comment (lib, "AHClientInterface")

// WITH APEX SETTING
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#include <windows.h>
#include "ApexClient.h"

CApexClient*		CApexClient::m_pThis = 0;

bool				CApexClient::m_bInit = false;

//----------------------------------------------------------------------------
CApexClient::CApexClient()
{
	m_pfunSendToSrv	= NULL;
	m_pfunApexRecv	= NULL;
	//m_pThis			= this;
}
//----------------------------------------------------------------------------





void CApexClient::Init()
{
	m_pThis						= new CApexClient;
}
//----------------------------------------------------------------------------
int CApexClient::StartApex()
{
#ifdef _APEX
		m_bInit = true;
		return CHCStart( OnApexSendToSrv, m_pThis->m_pfunApexRecv );
#else
		return 0;
#endif
}
//----------------------------------------------------------------------------
long CApexClient::OnApexRecvFromSrv	( const char * pBuffer,int nLen )
{
#ifdef _APEX	
	if( m_pThis->m_pfunApexRecv != NULL )
	{
		m_pThis->m_pfunApexRecv( pBuffer, nLen );
	}
#endif

	return 0;
}
//----------------------------------------------------------------------------
long CApexClient::OnApexSendToSrv		( const char * pBuffer,int nLen )
{
#ifdef _APEX	
	if( m_pThis->m_pfunSendToSrv != NULL )
	{
		m_pThis->m_pfunSendToSrv( nLen, pBuffer );
	}
#endif
	return 0;
}
//----------------------------------------------------------------------------
void CApexClient::Release()
{
#ifdef _APEX	
	if( m_bInit == true )
	{
		CHCEnd();
		delete m_pThis;
		m_bInit = false;
	}
#endif
}
//----------------------------------------------------------------------------
void CApexClient::SetSendFunc ( _FUNC_C_SENDTOSRV pFunc  ) 
{
#ifdef _APEX

	m_pThis->m_pfunSendToSrv = pFunc; 
#endif
}

