#pragma once

//#include "../NetBridge/NetBridge.h"


typedef long (*_FUNC_C_APEXRECV)	(const char* pBuffer,int nLen);
typedef void (*_FUNC_C_SENDTOSRV)	(int iSize, const char* pData );

class CApexClient
{
public:
	CApexClient();

	static void			Init();
	static void			Release();

	static void			SetSendFunc ( _FUNC_C_SENDTOSRV pFunc  );
	static int			StartApex();

	// ����� Apex Server �o�Ӫ��ʥ], �n�൹ APEX
	static	long	OnApexRecvFromSrv	( const char * pBuffer,int nLen );

	// ����� Apex Client �ݭn�D�o�� Server ���ʥ]
	static	long	OnApexSendToSrv		( const char * pBuffer,int nLen );

	//-------------------------------------------------------------
	static CApexClient*		m_pThis;
	_FUNC_C_APEXRECV		m_pfunApexRecv;
	//CNetBridge*				m_pNetBridge;
	_FUNC_C_SENDTOSRV		m_pfunSendToSrv;


	static	bool			m_bInit;
};

//extern CApexClient* g_pApexClient;