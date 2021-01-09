/*	�ݰ�

1. �s�u���_�u�B�m
2. �{�Ҥ��_�u�B�m
3. �_�u�o�ͤ�, Post_Send ���~�Φp��Q�θӶ����~�˴��_�u�o��.

MapSocket �i�H�Ҽ{�� vector �ӹ�@, �[�j�į�, �]���ϥ� map �Ӭd�߫ܨS�Ĳv

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
�A�ϥ�CheckSum�Ƶ{���y��ICMP�ՍJ�M�G  
�`�Τ�k�G  
((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);  
CheckSum��ۡG  
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

}// CheckSum��۬O��㪺�ՍJ�M��ۡA�A�]�i�H��ɬ�Ɔe������ՍJ�M��ۃS�N���� 


 */
struct	SockSendRevInfoStruct
{
	LONG	BytesSend;
	LONG	BytesRevc;
	LONG	PecketSend;
	LONG	PecketRevc;
};

//�����֤�
class CNetBridge_Base : public CNetBridge
{
public:
	CNetBridge_Base(void);
	virtual ~CNetBridge_Base(void);

	// �~���欰
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


	// �����欰
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
	
	virtual LONG		GetBytesSend		( int Second );	//Second �̦h 3600 ==> �@�p��
	virtual LONG		GetBytesRecv		( int Second );	//Second �̦h 3600 ==> �@�p��
	virtual LONG		GetPacketsSend		( int Second );	//Second �̦h 3600 ==> �@�p��
	virtual LONG		GetPacketsRecv		( int Second );	//Second �̦h 3600 ==> �@�p��

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

// �b�h�����p�U����

	virtual CBuffer*	On_Compress			( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Uncompress		( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Encrypt			( CBuffer* pBuffer ){ return NULL;}
	virtual CBuffer*	On_Decrypte			( CBuffer* pBuffer ){ return NULL;}

	//������Y
	// NetID �إ�/�R��

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
	
	vector< CNetSocket* >					m_vecWaitCloseSocket;		// ���ݩҦ��ݰe�T���e�X�� Close �� Socket queue
	vector< CNetSocket* >					m_vecWaitDeleteSocket;		// ���ݩҦ������T���B�z�� Delete �� Socket queue

	//PVOID									m_pBuffer;
	//DWORD									m_dwBufferIndex;
	//vector< DWORD 
	
	CCritcalsection							m_cs_Socket;		// �s�W�ΧR�� Socket ��
	//CCritcalsection						m_cs_MsgQueue;			// �s�W�Ψ��X Msg ��
	//CCritcalsection						m_cs_mapEvent;			// �s�W�Ψ��X Event ��
	CCritcalsection							m_cs_MessageAndEvent;	// �s�W�Ψ��X Message / Event
	CCritcalsection							m_cs_buffer;
	CCritcalsection							m_cs_vecWaitCloseSocket;
	CCritcalsection							m_cs_EventMsgPool;

	DWORD									m_dwHost;			// �Ψӭp�Ʀ��h�֪� Socket �b Host ���A, �]�O�Ψӭp�����h�� Event Waiting
	//WSAEVENT								m_EventHostArray[ DF_MAX_HOST_SOCKET ];
	HANDLE									m_hMsgEvent;
	bool									m_bEvent;
	
	//vector< CEventMsg* >					m_vecMsg;
	
	CNetQueue< CEventMsg* >					m_vecMsg;
	CNetQueue< CEventMsg* >					m_MsgQueue;




	vector< CEventMsg* >					m_vecAuthorize;

	vector< CEventMsg* >					m_vecHoldMsg;			// �ΨӦs��Ȯɤ���B�z�� Msg, �p�٨S���] Event ���w����ʥ]�� Msg
	vector< DWORD >							m_vecWaitSendSocket;	// �Ψӭp������ Socket ����ƫݰe

	CBufferManger							m_bufferManager;

	PFERRMSG								m_pfError;		// �Ψӿ�X���~�T�����禡����
	pfOutPutCB								m_pfOutPut;

	CNetQueue<CEventMsg *>					m_unusedEventMsgs;

	/////////////////////////////////////////////////////////////////////////////
	//�C��ǰe��������T
	deque< SockSendRevInfoStruct >			m_SockSendRevInfo;
	LONG									m_LastCalSendRevTime;
	/////////////////////////////////////////////////////////////////////////////
	DWORD									m_dwAvgProcEvent;			// �����C 200ms �B�z���ƥ�q
	DWORD									m_dwAvgNewEvent;		// �C��s�ƥ�q
	DWORD									m_dwTimeLastGetEvent;	


	/////////////////////////////////////////////////////////////////////////////

	// �ǿ魭��ϥ�
	//------------------------------------------------------------------------------------
	bool									m_bCheckRespondTime;			// �O�_�}���ˬd�����ɶ�����
	DWORD									m_dwCheckRespondTime;			// �ˬd�����ɶ������j�ɶ�, Invete for check respond time
	DWORD									m_dwKeepAliveTime;				// �����ɶ��C��@�w��, �K�_�u, �Y�] 0 �h��ܤ��_�u

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

	volatile LONG							m_Respond[10];				// �H 100 Ping ����쪺�t�O

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
