/*	«Ý°µ

1. ³s½u¤¤Â_½u³B¸m
2. »{ÃÒ¤¤Â_½u³B¸m
3. Â_½uµo¥Í¤¤, Post_Send ¿ù»~¤Î¦p¦ó§Q¥Î¸Ó¶µ¿ù»~ÀË´úÂ_½uµo¥Í.

MapSocket ¥i¥H¦Ò¼{¥Î vector ¨Ó¹ê§@, ¥[±j®Ä¯à, ¦]¬°¨Ï¥Î map ¨Ó¬d¸ß«Ü¨S®Ä²v

*/
#ifndef __NETBRIDGE_BASE_H__
#define __NETBRIDGE_BASE_H__

#if _DEBUG
#define NET_BRIDGE_BASE_BUFFER_CREATE_AND_DESTORY_DEBUG_PRINT 1
#define NET_BRIDGE_BASE_BUFFER_KEEP_POINTER 1
#define NET_BRIDGE_BASE_EVENT_CREATE_AND_DESTORY_DEBUG_PRINT 1
#else
#define NET_BRIDGE_BASE_BUFFER_CREATE_AND_DESTORY_DEBUG_PRINT 0
#define NET_BRIDGE_BASE_BUFFER_KEEP_POINTER 0
#define NET_BRIDGE_BASE_EVENT_CREATE_AND_DESTORY_DEBUG_PRINT 0
#endif

#include <map>
#include <vector>
#include <queue>

using namespace std;


#include "NetBridge_Struct.h"
#include "NetBridge_EventObj.h"
#include "BufferManger.h"

#include "NetBridge.h"

//typedef priority_queue< CNetSocket*, vector< CNetSocket* >, CompareCloseTime > PQCLOSEQUEUE;
//#define DF_DEBUG_RECVMSG
//#define DF_DEBUG_SENDMSG


/*
¦A¨Ï¥ÎCheckSum°Æµ{¦¡ƒyºâICMP®ÕJ©M¡G  
ˆ`¥Î¤èªk¡G  
((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);  
CheckSum¨ç‡Û¡G  
USHORT CheckSum (USHORT *buffer, int size)  
{  
	unsigned long cksum=0;  

	while(size >1)  
	{  
		cksum+=*buffer++;  
		size -=sizeof(USHORT);  
	}  

	if(size ) 
		cksum += *(UCHAR*)buffer;  
	
	cksum = (cksum >> 16) + (cksum & 0xffff);  
	cksum += (cksum >>16);  

	return (USHORT)(~cksum);  

}// CheckSum¨ç‡Û¬O‡á­ãªº®ÕJ©M¨ç‡Û¡A§A¤]¥i¥H¥ÎÉ¬¤Æ†eªº¥ô¦ó®ÕJ©M¨ç‡ÛƒS¥N´À¥¦ 


 */
struct	SockSendRevInfoStruct
{
	LONG	BytesSend;
	LONG	BytesRevc;
	LONG	PecketSend;
	LONG	PecketRevc;
};

//ºô¸ô®Ö¤ß
class CNetBridge_Base : public CNetBridge
{
public:
	CNetBridge_Base(void);
	virtual ~CNetBridge_Base(void);

	// ¥~³¡¦æ¬°
	//---------------------------------------------------------------------------------------
	virtual int			Init				( int iNumThread );
	virtual void		Release				();
	//virtual	int			Host					( DWORD dwIP , WORD wPort, CEventObj* pEventObj, BOOL bCompress = false , BOOL bEncryption = false ) =0;
	virtual int			Connect				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext );
	virtual int			Telnet				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext )=0;

	virtual void		Flush				();
	virtual DWORD		Wait				( DWORD dwTime );

	//virtual void		Send					( DWORD dwNetID, DWORD dwSize, PVOID pBuffer, DWORD dwPriority = 0, DWORD dwFlag = 0 ) =0;
	//virtual void		SendToAll				( DWORD dwSize, PVOID pPacket, DWORD dwPriority ) =0;
	//virtual void		Close					( DWORD dwNetID ) =0;

	//virtual bool		CheckNetID				( DWORD dwNetID ) =0;
	//virtual DWORD		GetNumOfConnections		() =0;
	
	//virtual int		GetSendQueueSize		() =0;
	virtual void		GetConnectInfo		( DWORD dwNetID, DWORD* pdwIP, WORD* pwPort );

	virtual void		SetOutPutCB			( pfOutPutCB pFun ) { m_pfOutPut = pFun; }
	virtual void		GetStatusInfo		( char* pszOut );
	virtual void		GetRespondInfo		( char* pszOut );
	virtual	bool		Shutdown			();
	virtual HANDLE		GetMsgEvent			() { return this->m_hMsgEvent; }

	// Setting option
	//----------------------------------------------------------------------
	virtual void		SetCheckRespond		( bool bEnable );
	virtual void		SetKeepAlive		( bool bEnable, DWORD dwTime );
	virtual void		SetSendBufferLimit	( bool bEnable, DWORD dwLimit );
	//----------------------------------------------------------------------


	// ¤º³¡¦æ¬°
	//---------------------------------------------------------------------------------------
	void				MsgOutPut			( int lv, char* format , ... );
	LONG				GetBytesSend		();
	LONG				GetBytesRecv		();
	
	LONG				GetPacketSend		()	{ return m_PacketSend; }
	LONG				GetPacketRecv		()	{ return m_PacketRecv; }

	DWORD				GetTotalSocket		();
	void				ReSetSendCount		();
	void				ReSetRecvCount		();

	DWORD				GetAvgNewEvent		()	{ return m_dwAvgNewEvent; }
	DWORD				GetAvgProcEvent		()	{ return ( ((float)m_dwAvgProcEvent) * ( ((float)1000) / DF_NB_AVG_EVENT_MS_TIME ) ); }
	DWORD				GetQueueEvent		()	{ return m_MsgQueue.Count(); }

	void				ReSetPacketSendCount	() { 	InterlockedExchange( &m_PacketSend, 0 ); }
	void				ReSetPacketRecvCount	() { 	InterlockedExchange( &m_PacketRecv, 0 ); }

	virtual	DWORD		GetMsgCount			() { return (DWORD) m_vecMsg.size(); }
	//////////////////////////////////////////////////////////////////////////////////
	//Hsiang 2007/4/11
	void				CalSendRecvBytes	();
	
	virtual LONG		GetBytesSend		( int Second );	//Second ³Ì¦h 3600 ==> ¤@¤p®É
	virtual LONG		GetBytesRecv		( int Second );	//Second ³Ì¦h 3600 ==> ¤@¤p®É
	virtual LONG		GetPacketsSend		( int Second );	//Second ³Ì¦h 3600 ==> ¤@¤p®É
	virtual LONG		GetPacketsRecv		( int Second );	//Second ³Ì¦h 3600 ==> ¤@¤p®É

	//////////////////////////////////////////////////////////////////////////////////

	virtual	DWORD		GetClientRespond	( DWORD dwNetID );


	//virtual void		CheckAuthorize		( vector< CEventMsg* >* pQueue );
	virtual void		CheckMsg			( vector< CEventMsg* >* pQueue );
	
	virtual void		CheckSocket			();
	virtual void		CheckPacket			();
	virtual void		SendFlush			();

	virtual void		Authorize			( CNetSocket* pSocket, CNetSocket* pAcceptSocket );
	
	virtual	bool		RemoveHost			( DWORD dwNetID ){ return false; }
	virtual CEventObj*	ResetClientEvent	( DWORD dwNetID, CEventObj* pEventObj ){	return 0; }
	
	virtual CBuffer*	CreatePacketBuffer	( DWORD dwSize, PVOID pData, BYTE** pOffset );
	virtual bool		CheckCompress		( CBuffer* pBuffer );

	virtual void		Post_Compress		( CNetSocket* pSocket , CBuffer* pBuffer )=0;
	virtual void		Post_Send			( CNetSocket* pSocket )=0;


	virtual void		SendConnect			( CNetSocket* pSocket ) = 0;

// ¦b¦hºüª¬ªp¤U°õ¦æ

	virtual CBuffer*	On_Compress			( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Uncompress		( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Encrypt			( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Decrypte			( CBuffer* pBuffer ){ return NULL;}

	//¸ê®ÆÀ£ÁY
	// NetID «Ø¥ß/§R°£

	static  DWORD		ConvertIP			( const char* pszIP );
	
	CNetSocket*			CreateSocket		();
	void				DeleteSocket		( DWORD dwNetID		);
	inline CNetSocket*	GetSocket			( DWORD dwNetID		);

	CEventMsg*			CreateMsg			( EM_MSG_TYPE emMsgType, CNetSocket* pSocket );
	void				DeleteMsg			( CEventMsg* pMsg );

	void				MsgAccept			( CNetSocket* pSocket );
	void				MsgConnect			( CNetSocket* pSocket );
	void				MsgDisconnect		( CNetSocket* pSocket );
	void				MsgRecv				( CNetSocket* pSocket, DWORD dwSize, BYTE* pData, BYTE* pPacketData );
	void				MsgError			( CNetSocket* pSocket, DWORD		dwErrorID		);
	void				MsgAuthorize		( CNetSocket* pSocket, CNetSocket* pAcceptSocket	);
	void				MsgConnectFailed	( CNetSocket* pSocket );
	void				MsgSystem			( CNetSocket* pSocket, Struct_PacketHeader*	pHeader, BYTE* pData, DWORD dwDataSize );

	void				PostMsg				( CEventMsg* pMsg );
		
	CBuffer*			CreateBuffer		( DWORD dwSize );
    void				DeleteBuffer		( CBuffer* lpBuffer );

	bool				GetPacketInfo		( PVOID pData, DWORD pDataSize, DWORD *pFlag, DWORD *pSize );
	inline byte			GetCheckSum			( BYTE* pSource, int iSize, byte Code, byte SourceCheckSum );

	virtual void		On_Error			( char *format, ... );

	virtual void		SendAliveAnswer		( CNetSocket* pSocket, DWORD dwSrvTick )	= 0;
	virtual void		SendAliveRequest	( CNetSocket* pSocket )						= 0;

//======================================================================================================

	//EM_WINSOCK_IO_MODE					m_iomode;
	volatile LONG							m_bytesSend;
	volatile LONG							m_bytesRecv;

	volatile LONG							m_PacketSend;
	volatile LONG							m_PacketRecv;

	int										m_vecSocketSize;
	CNetSocket**							m_vecSocket;
	CNetQueue<DWORD>						m_unusedNetIDs;

	bool									m_bShutdown;

	//map< DWORD	, CNetSocket* >				m_mapClosingSocket;
	//priority_queue< CNetSocket*, vector< CNetSocket* >, 
	//PQCLOSEQUEUE							m_pqCloseQueue;

	multimap< DWORD, CNetSocket* >			m_mapClosingSocket;
	
	vector< CNetSocket* >					m_vecWaitCloseSocket;		// µ¥«Ý©Ò¦³«Ý°e°T®§°e¥X«á Close ªº Socket queue
	vector< CNetSocket* >					m_vecWaitDeleteSocket;		// µ¥«Ý©Ò¦³±µ¦¬°T®§³B²z«á Delete ªº Socket queue

	//PVOID									m_pBuffer;
	//DWORD									m_dwBufferIndex;
	//vector< DWORD 
	
	CCritcalsection							m_cs_Socket;		// ·s¼W©Î§R°£ Socket ¥Î
	//CCritcalsection						m_cs_MsgQueue;			// ·s¼W©Î¨ú¥X Msg ¥Î
	//CCritcalsection						m_cs_mapEvent;			// ·s¼W©Î¨ú¥X Event ¥Î
	CCritcalsection							m_cs_MessageAndEvent;	// ·s¼W©Î¨ú¥X Message / Event
	CCritcalsection							m_cs_buffer;
	CCritcalsection							m_cs_vecWaitCloseSocket;
	CCritcalsection							m_cs_EventMsgPool;

	DWORD									m_dwHost;			// ¥Î¨Ó­p¼Æ¦³¦h¤Öªº Socket ¦b Host ª¬ºA, ¤]¬O¥Î¨Ó­p¿ý¦³¦h¤Ö Event Waiting
	//WSAEVENT								m_EventHostArray[ DF_MAX_HOST_SOCKET ];
	HANDLE									m_hMsgEvent;
	bool									m_bEvent;
	
	//vector< CEventMsg* >					m_vecMsg;
	
	CNetQueue< CEventMsg* >					m_vecMsg;
	CNetQueue< CEventMsg* >					m_MsgQueue;




	vector< CEventMsg* >					m_vecAuthorize;

	vector< CEventMsg* >					m_vecHoldMsg;			// ¥Î¨Ó¦s©ñ¼È®É¤£¯à³B²zªº Msg, ¦pÁÙ¨S¦³³] Event ¦ý¤w¦¬¨ì«Ê¥]ªº Msg
	vector< DWORD >							m_vecWaitSendSocket;	// ¥Î¨Ó­p¿ý¨º¨Ç Socket ¦³¸ê®Æ«Ý°e

	CBufferManger							m_bufferManager;

	PFERRMSG								m_pfError;		// ¥Î¨Ó¿é¥X¿ù»~°T®§ªº¨ç¦¡«ü¼Ð
	pfOutPutCB								m_pfOutPut;

	CNetQueue<CEventMsg *>					m_unusedEventMsgs;

	/////////////////////////////////////////////////////////////////////////////
	//¨C¬í¶Ç°e±µ¦¬ªº¸ê°T
	deque< SockSendRevInfoStruct >			m_SockSendRevInfo;
	LONG									m_LastCalSendRevTime;
	/////////////////////////////////////////////////////////////////////////////
	DWORD									m_dwAvgProcEvent;			// ¥­§¡¨C 200ms ³B²zªº¨Æ¥ó¶q
	DWORD									m_dwAvgNewEvent;		// ¨C¬í·s¨Æ¥ó¶q
	DWORD									m_dwTimeLastGetEvent;	


	/////////////////////////////////////////////////////////////////////////////

	// ¶Ç¿é­­¨î¨Ï¥Î
	//------------------------------------------------------------------------------------
	bool									m_bCheckRespondTime;			// ¬O§_¶}±ÒÀË¬d¤ÏÀ³®É¶¡¾÷¨î
	DWORD									m_dwCheckRespondTime;			// ÀË¬d¤ÏÀ³®É¶¡ªº¶¡¹j®É¶¡, Invete for check respond time
	DWORD									m_dwKeepAliveTime;				// ¤ÏÀ³®É¶¡§C©ó¤@©w­È, «KÂ_½u, ­Y³] 0 «hªí¥Ü¤£Â_½u

	bool									m_bSendBufferLimit;				// flag of Check transfer, default is off
	DWORD									m_dwSendBuffLimit;				// number of  transfer limit, default is 4096k and respond time bigger than 3000ms


	

	// Log 
	//------------------------------------------------------------------------------------
	DWORD									m_LastFlushTime;
	DWORD									m_minFlushTime;
	DWORD									m_maxFlushTime;

	DWORD									m_minEvent;
	DWORD									m_maxEvent;

	volatile LONG							m_SendCount;
	DWORD									m_minSendCountPerSec;
	DWORD									m_maxSendCountPerSec;

	volatile LONG							m_SendBytes;
	DWORD									m_minSendBytesPerSec;
	DWORD									m_maxSendBytesPerSec;

	volatile LONG							m_RecvCount;
	DWORD									m_minRecvCountPerSec;
	DWORD									m_maxRecvCountPerSec;

	volatile LONG							m_RecvBytes;
	DWORD									m_minRecvBytesPerSec;
	DWORD									m_maxRecvBytesPerSec;

	volatile LONG							m_Respond[10];				// ¥H 100 Ping ¬°³æ¦ìªº®t§O

	DWORD									m_minSecSendThread;
	DWORD									m_maxSecSendThread;


	bool									m_CheckRecvEvent;

#if NET_BRIDGE_BASE_BUFFER_KEEP_POINTER
    std::vector<CNetSocket*>    m_vecNetSocket;
    std::vector<std::string>    m_vecNetSocketName;
    std::vector<CEventMsg*>     m_vecEventMsg;
    std::vector<std::string>    m_vecEventMsgName;
#endif

};

inline CNetSocket *CNetBridge_Base::GetSocket(DWORD dwNetID)
{
	CNetSocket* pSocket = NULL;

	m_cs_Socket.Enter( "CNetBridge_Base::GetSocket" );
	{
		if(dwNetID < static_cast<DWORD>(m_vecSocketSize))
		{
			pSocket = m_vecSocket[dwNetID];
		}
	}
	m_cs_Socket.Leave( "CNetBridge_Base::GetSocket" );

	return pSocket;
}


#endif //__NETBRIDGE_BASE_H__
