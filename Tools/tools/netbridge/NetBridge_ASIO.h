#pragma	once

#if _DEBUG
#define NET_BIRDGE_ASIO_DEBUG_PRINT 1
#else
#define NET_BIRDGE_ASIO_DEBUG_PRINT 0
#endif

#include "NetBridge_Base.h"
#include "./asio/IMyAsio.h"

// 09/19/07		©Þ±¼


//test 1

class CNetBridge_ASIO : public CNetBridge_Base
{
public:
	CNetBridge_ASIO( void );
	virtual ~CNetBridge_ASIO( void );

	virtual int			Init				( int iNumThread );

	virtual	int			Host				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, BOOL bEncryption = false , BOOL bCompress = false, BOOL bTelnet = false, PVOID pContext = NULL );
	virtual int			Connect				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext = NULL );
	virtual int			Telnet				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext = NULL ) { return false; };

	virtual void		Send				( DWORD dwNetID, DWORD dwSize, PVOID pData );
	virtual void		SendWithBuff		( DWORD dwNetID, DWORD dwSize1, PVOID pData1, DWORD dwSize2, PVOID pData2 );

	virtual void		SendToAll			( DWORD dwSize, PVOID pPacket );
	virtual void		SendToAllWithBuff	( DWORD dwSize1, PVOID pPacket1, DWORD dwSize2, PVOID pPacket2 );

	virtual void		Flush				();
	virtual void		SendFlush			(){};
	virtual DWORD		Wait				( DWORD dwTime ){ return 0; };
	virtual void		Close				( DWORD dwNetID );

	virtual void		GetConnectInfo		( DWORD dwNetID, DWORD* pdwIP, WORD* pwPort );
	virtual PVOID		GetContext			( DWORD dwNetID ) { return 0; };

	virtual void		SetOutPutCB			( pfOutPutCB pFun );
	virtual void		GetStatusInfo		( char* pszOut ) {};
	virtual void		GetRespondInfo		( char* pszOut ) {};

	virtual	bool		Shutdown			();

	virtual	void		SetSocketNoDelay	( DWORD dwNetID ) {};

	virtual HANDLE		GetMsgEvent			() { return 0; };

	virtual LONG		GetBytesSend		( int Second ) { return 0; };
	virtual LONG		GetBytesRecv		( int Second ) { return 0; };
	virtual LONG		GetPacketsSend		( int Second ) { return 0; };
	virtual LONG		GetPacketsRecv		( int Second ) { return 0; };

	virtual	DWORD		GetRespondTime		( DWORD dwNetID ) { return 0; };




	virtual	DWORD		GetAvgNewEvent		() { return 0; };
	virtual DWORD		GetAvgProcEvent		() { return 0; };
	virtual DWORD		GetQueueEvent		() { return 0; };

	virtual	DWORD		GetMsgCount			() { return 0; };

	static  DWORD		WaitAll				( DWORD dwTime );

	virtual void		Post_Compress		( CNetSocket* pSocket , CBuffer* pBuffer ) {};
	virtual void		Post_Send			( CNetSocket* pSocket ) {};
	virtual void		SendConnect			( CNetSocket* pSocket ) {};

	virtual void		SendAliveAnswer		( CNetSocket* pSocket, DWORD dwSrvTick ) {};
	virtual void		SendAliveRequest	( CNetSocket* pSocket ) {};		

	DWORD				Convert				( DWORD dwIP );

	// Setting option
	//----------------------------------------------------------------------
	virtual void		SetCheckRespond		( bool bEnable )					{};
	virtual	DWORD		GetClientRespond	( DWORD dwNetID )					{ return 0; };
	virtual void		SetKeepAlive		( bool bEnable, DWORD dwTime )		{};
	virtual void		SetSendBufferLimit	( bool bEnable, DWORD dwLimit )		{};
	//----------------------------------------------------------------------
	// Member
	//----------------------------------------------------------------------
	
	MyAsio::INetAsio*						m_pAsio;



};