#pragma once

//#define DF_PACKET_LOG
#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include "NetBridge_EventObj.h"
#include <windows.h>

using namespace std;

typedef void (*pfOutPutCB)( int lv, const char* szOut );
typedef void (*pfOutputCompressCB)( int iSrcSize, BYTE* pSrcData, int* piCompressSize, BYTE* pCompressData );
typedef void (*pfOutputDecompressCB)( int iCompressedSzie, BYTE* pCompressData, BYTE* pDecompressData );

enum NB_ENGINE
{
	NB_ENGINE_IOCP	= 0,
	NB_ENGINE_ASIO	= 1
};

class CNetBridge
{
public:
	CNetBridge( void );
	virtual ~CNetBridge( void );

	virtual int			Init				( int iNumThread )=0;

	virtual	int			Host				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, BOOL bEncryption = false , BOOL bCompress = false, BOOL bTelnet = false, PVOID pContext = NULL )=0;
	virtual int			Connect				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext = NULL )=0;
	virtual int			Telnet				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext = NULL )=0;

	virtual void		Send				( DWORD dwNetID, DWORD dwSize, PVOID pData ) = 0;
	virtual void		SendWithBuff		( DWORD dwNetID, DWORD dwSize1, PVOID pData1, DWORD dwSize2, PVOID pData2 ) = 0;

	virtual void		SendToAll			( DWORD dwSize, PVOID pPacket ) = 0;
	virtual void		SendToAllWithBuff	( DWORD dwSize1, PVOID pPacket1, DWORD dwSize2, PVOID pPacket2 ) = 0;
	
	virtual void		Flush				()=0;
	virtual void		SendFlush			() = 0;
	virtual DWORD		Wait				( DWORD dwTime )=0;
	virtual void		Close				( DWORD dwNetID )=0;

	virtual void		GetConnectInfo		( DWORD dwNetID, DWORD* pdwIP, WORD* pwPort ) =0;
	virtual PVOID		GetContext			( DWORD dwNetID ) = 0;

	virtual void		SetOutPutCB			( pfOutPutCB pFun ) =0;
	
	virtual void		SetCompressFun		( pfOutputCompressCB pFun ) {};
	virtual void		SetDecompressFun	( pfOutputDecompressCB pFun ) {};
	
	virtual void		GetStatusInfo		( char* pszOut ) = 0;
	virtual void		GetRespondInfo		( char* pszOut ) = 0;

	virtual	bool		Shutdown			() =0;

	virtual	void		SetSocketNoDelay	( DWORD dwNetID ) = 0;

	

	virtual HANDLE		GetMsgEvent			() = 0;

	virtual LONG		GetBytesSend		( int Second ) = 0;	//Second 程 3600 ==> 
	virtual LONG		GetBytesRecv		( int Second ) = 0;	//Second 程 3600 ==> 
	virtual LONG		GetPacketsSend		( int Second ) = 0;	//Second 程 3600 ==> 
	virtual LONG		GetPacketsRecv		( int Second ) = 0;	//Second 程 3600 ==> 

	virtual	DWORD		GetRespondTime		( DWORD dwNetID ) = 0;

	virtual	void		SetSendLimit		( bool IsEnable, int iLimit ) {};


	

	virtual	DWORD		GetAvgNewEvent		()	= 0;
	virtual DWORD		GetAvgProcEvent		()	= 0;
	virtual DWORD		GetQueueEvent		()	= 0;

	virtual	DWORD		GetMsgCount			() = 0;

	static  DWORD		WaitAll				( DWORD dwTime );

	virtual	void		SetRecvEvent		( bool bEnable )	{}
	virtual DWORD		GetSendQueueSize	( DWORD dwNetID )	{ return 0;}


	
	// Setting option
	//----------------------------------------------------------------------
	virtual void		SetCheckRespond		( bool bEnable )					= 0;
	virtual	DWORD		GetClientRespond	( DWORD dwNetID )					= 0;
	virtual void		SetKeepAlive		( bool bEnable, DWORD dwTime )		= 0;
	virtual void		SetSendBufferLimit	( bool bEnable, DWORD dwLimit )		= 0;
	//----------------------------------------------------------------------




	static	CNetBridge*	m_pNetPoint[ MAXIMUM_WAIT_OBJECTS ];
	static	HANDLE		m_pNetEventHandle[ MAXIMUM_WAIT_OBJECTS ];

	static	DWORD		m_dwNetHandleIndex;

	static	HANDLE		m_pNetMainEvent;
	static	vector< CNetBridge* >*			m_pvecCore;
	static	vector< CNetBridge* >*			m_pvecNewCore;



	/*
	CNetBridge*			m_pNetPoint[ MAXIMUM_WAIT_OBJECTS ];
	HANDLE				m_pNetEventHandle[ MAXIMUM_WAIT_OBJECTS ];

	DWORD				m_dwNetHandleIndex;
	DWORD				m_dwEnterTime;
	*/

	
	DWORD					m_dwEnterTime;
	CNetBridge*				m_pCore;
	NB_ENGINE				m_EngineType;
	static DWORD			m_refCount;
};

CNetBridge*				CreateNetBridge		( bool bManage = true, int iNumThread = 2 );
void					DeleteNetBridge		( CNetBridge* pBridge );

CNetBridge*				CreateAsio			( bool bManage );

DWORD					ConvertIP			( const char* pszIP );
void					ConvertIPtoString	( DWORD dwIP, char* pszIP );

struct Struct_PacketLog
{
	DWORD dwID;
	DWORD dwTime;
	DWORD dwPacketID;
};




//typedef priority_queue< CNetSocket*, vector< CNetSocket* >, CompareCloseTime > PQCLOSEQUEUE;
//#define DF_DEBUG_RECVMSG
//#define DF_DEBUG_SENDMSG


