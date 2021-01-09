#pragma	once

#if _DEBUG
#define NET_BIRDGE_IOCP_DEBUG_PRINT 1
#else
#define NET_BIRDGE_IOCP_DEBUG_PRINT 0
#endif

#include "NetBridge_Base.h"

// 09/19/07		拔掉


//test 1

class CNetBridge_IOCP : public CNetBridge_Base
{
public:
	CNetBridge_IOCP(void);
	virtual ~CNetBridge_IOCP(void);

	virtual int			Init				( int iNumThread );
	virtual	int			Host				( DWORD dwIP , WORD wPort, CEventObj* pEventObj,  BOOL bEncryption, BOOL bCompress, BOOL bTelnet, PVOID pContext );


	virtual int			Connect				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext );
	virtual int			Telnet				( DWORD dwIP , WORD wPort, CEventObj* pEventObj, PVOID pContext );

	virtual void		Send				( DWORD dwNetID, DWORD dwSize, PVOID pData );
	virtual void		SendWithBuff		( DWORD dwNetID, DWORD dwSize1, PVOID pData1, DWORD dwSize2, PVOID pData2 );

	virtual void		SendToAll			( DWORD dwSize, PVOID pPacket );
	virtual void		SendToAllWithBuff	( DWORD dwSize1, PVOID pPacket1, DWORD dwSize2, PVOID pPacket2 );
	virtual void		Close				( DWORD dwNetID );

	
	virtual bool		CheckNetID			( DWORD dwNetID );
	virtual DWORD		GetNumOfConnections	();

	virtual PVOID		GetContext			( DWORD dwNetID );

	virtual int			GetSendQueueSize	();

	virtual	DWORD		GetRespondTime		( DWORD dwNetID );

	virtual	void		SetSocketNoDelay	( DWORD dwNetID );

	//static HANDLE		m_CompletionPort;
	//static HANDLE		m_CompThreads[ DF_NB_MAX_COMPLETION_THREAD_COUNT ];
	HANDLE		m_CompletionPort;
	HANDLE		m_CompThreads[ DF_NB_MAX_COMPLETION_THREAD_COUNT ];

	virtual int			ConnectBase			( CNetSocket* pSocket, DWORD dwIP , WORD wPort, CEventObj* pEventObj );
	//======================================================================================================
//private:
	static DWORD WINAPI	Thread_Completion	( PVOID pParam );

	void				ProcessBuffer		( CNetSocket* pSocket, DWORD dwDataSize, BYTE* pData );

	void				Handle_Accept		( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Recv			( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Send			( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Disconnect	( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Compress		( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Connect		( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	void				Handle_Connectfailed( CNetSocket* pSocket, CBuffer* pBuffer, HANDLE CompletionPort, DWORD dwBytesTransfer );
	
	void				Post_Compress		( CNetSocket* pSocket, CBuffer* pBuffer );
	void				Post_Send			( CNetSocket* pSocket );
	void				Post_Recv			( CNetSocket* pSocket );
	void				Post_Accept			( CNetSocket* pSocket, CBuffer* pBuffer );

	void				ProcessCompress		( CNetSocket* pSocket );

	void				SendConnect			( CNetSocket* pSocket );
	void				SystemPacket		( CNetSocket* pSocket, Struct_PacketHeader* pHeader, DWORD dwDataSize, BYTE* pData );

	inline BYTE			Encode				( BYTE* pTarget, BYTE* pSource, int iSize, byte Code );
	inline void			Decode				( BYTE* pTarget, BYTE* pSource, int iSize, byte Code );
	//inline BYTE			GetCheckSum			( BYTE* pSource, int iSize, byte Code, byte CheckSum = 0 );

	inline BYTE			SendID				( CNetSocket* pSocket );
	inline BYTE			RecvID				( CNetSocket* pSocket );

	

	//-------------------------------------------------------------------------------------------------------
	inline BYTE			AddDataToSendFrame	( CNetSocket* pSocket, DWORD dwSize, BYTE* pData, byte Code, bool bAppend = true );		// 在 Send 函式中的子函式, 將資料放進 Frame

	//-------------------------------------------------------------------------------------------------------
	virtual	bool		Shutdown			();

	virtual void		SendAliveAnswer		( CNetSocket* pSocket, DWORD dwSrvTick );
	virtual void		SendAliveRequest	( CNetSocket* pSocket );
	virtual void		SendChecksumError	( CNetSocket* pSocket, WORD wSendIndex, byte headerchecksum, byte checksum );

	virtual void		SetCompressFun		( pfOutputCompressCB pFun ) { m_pFunCompress = pFun; }
	virtual void		SetDecompressFun	( pfOutputDecompressCB pFun ) { m_pFunDecompress = pFun; }

	virtual	void		SetSendLimit		( bool IsEnable, int iLimit );

	virtual	void		SetRecvEvent		( bool bEnable );
	virtual DWORD		GetSendQueueSize	( DWORD dwNetID );


	//priority_queue< DWORD , CNetSocket* >	m_pqClosingSocket;

	//-------------------------------------------------------------------------------------------------------
	pfOutputCompressCB		m_pFunCompress;
	pfOutputDecompressCB	m_pFunDecompress;

};