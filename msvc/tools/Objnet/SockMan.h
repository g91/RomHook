#ifndef _SOCKET_MANAGER_H
#define _SOCKET_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable:4949)
//=====================================================================================================================
// module: SocketManager
// author: Peacock <peacock@softstar.com.tw>
// create: 04/10/1999
// modify: revise 4/30/1999
//         review N/A
// level : Network Module
// reuse : single or multipile socket management
// file  : SocketManager.h, SocketManager.cpp
// test  : not yet
// ref   : Connection.h, Connection.cpp
//=====================================================================================================================

//=====================================================================================================================
// 產生 new connection 的流程
//	（一定要 SocketManager::AttachEventListener ）
//
//	⊙ 新的 connection 進來時:
//		1. SocketManager 會呼叫 EventListener::OnNewConnection 取得新的
//			Connection 的NetEventListener
//		2. 然後該 NetEventListener 的 OnConnected 會被呼叫
//
//	⊙ connect 出去:
//		1. 先呼叫 Connect ，傳入 new connection 的 listener
//		2. 若是程序上沒問題，該 NetEventListener 的 OnConnected 會被呼叫
//	（因為是 Async 的，所以並不保證一定連接的上，但只要連接不上，
//    會 call INetEventListener:OnDisconnected ）
//
//=====================================================================================================================
// 使用方法：
//		Init( port );
//		AttachHandler( this );
//		然後工作就都交由 handler 來做了
//=====================================================================================================================
// 注意： 現在上不支援多緒，將來有時也需注意，SetPacketMode()時很容易出問題

#include "Connection.h"
#include "LU32Array.h"
#include "LNet.h"
#include "ObjNet.h"
#include "LBuffer.h"

#pragma unmanaged
	
class cSockMan: public IObjNet
{
public:
	~cSockMan() throw();

	void	LSAPI Init(bool bIsCompress);
	void	LSAPI UnInit(void);
	void	LSAPI GetPeerAddress( LNETID smid, sockaddr_in* pAddr );

	void	LSAPI EnumLNETID( SM_EnumLNETIDCallBack, void* pContext );
	void	LSAPI EnumConnections(LNET_EnumPlayersCallBack callback, void* vpContext) throw();
	int		LSAPI GetNumOfPlayer(void);

	//void	Connect( char*  ipaddr, UINT uPort, INetEventListener* listener );
	//void	Connect( u_long  ipaddr, u_short uPort, INetEventListener* listener );
	SOCKET	LSAPI Host(sockaddr_in* TCPAddr, INewConnectionListener* pListener);
	void	LSAPI RemoveHost( SOCKET sock );
	void	LSAPI AttachListener( SOCKET server_socket, INewConnectionListener* listener);

	bool	LSAPI WaitingConnect( sockaddr_in* pAddr, INetEventListener* pListener );
	int		LSAPI Connect( sockaddr_in* pAddr, INetEventListener* pListener );
	void	LSAPI CancelConnect( int connect_number );
	void	LSAPI AttachClientListener( LNETID id, INetEventListener* pListener );
	LNETID	LSAPI AddSocket( SOCKET sock, INetEventListener* pListener );

	void	LSAPI Flush(timeval* wait_time);
	void	LSAPI RevFlush(timeval* wait_time);
	void	LSAPI SendFlush(timeval* wait_time);

	
	void	LSAPI Send(LNETID smid, int nSize, void* vpData, int nPriority );
	void	LSAPI SendToAll( int nSize, void* vpData );
	void	LSAPI SendToMutiple( int nNum, const LNET_PKT_DESTINATION* dest_array, int nSize, void* vpData);

	void	LSAPI Close( LNETID smid );
	void	LSAPI ShutdownSendPipe( LNETID smid );

	UINT32	LSAPI GetContext(LNETID smid);
	void	LSAPI SetContext(LNETID smid, UINT32 c);

	LNETID	LSAPI AddConnection( Connection* pConn );

	UINT32	LSAPI GetNumOfBytesSend(void) throw() {return m_nNumOfBytesSend;};
	UINT32	LSAPI GetNumOfBytesRecv(void) throw() {return m_nNumOfBytesRecv;};
	bool	LSAPI IsValidLNETID( LNETID u32ID ) throw() { return m_Connections.IsValidAt( u32ID ); }

	UINT32	LSAPI GetPacketLeftInSendQueue( LNETID u32id );

	void	LSAPI GetCompressSuccessVSFailure( int& nSuccess, int& nFailed );
	int		LSAPI GetNumOf_NotCompressedBytes( void );
	int		LSAPI GetNumOf_CompressedBytes( void );

	UINT32	LSAPI GetNumOfConnections( void );
	void	LSAPI SetMaxPacketSize( UINT32 u32Size );
	bool	LSAPI CheckPacketEmpty();


	//需要Key做封包編碼(Client)
	void	LSAPI NeedKey(){_NeedKey = true;};

	//需要定時作連線檢查
	//如果不同步太嚴重則會被踢出
	void	LSAPI NeedCheckConnect(){_NeedCheckConnect = true;};
private: // used by Connect() only
	//UINT32	LSAPI ProcessConnect(SOCKET sock );
	void	LSAPI ProcessNewConnect(SOCKET sock,INewConnectionListener* pListener);

private:
	UINT32Array		m_ServerSocketList_sock;		// all server socket
	UINT32Array		m_ServerSocketList_pListener;	// listener of per server
	UINT32Array		m_Connections;					// all connection at working
	UINT32Array		m_WCList_sock;					// socket that wait for connecting connection
	UINT32Array		m_WCList_pListener;				// listener of wait for connecting connection
	//void*						m_pContext;

	//bool	m_bIsCompress;
	//UINT32	m_u32CompressSuccess;
	//UINT32	m_u32CompressFailure;
	//UINT32	m_u32NumOf_NotCompressedBytes;
	//UINT32	m_u32NumOf_CompressedBytes;


	UINT32	m_nNumOfBytesRecv;
	UINT32	m_nNumOfBytesSend;

	INT32	m_u32MaxPacketSize;
	bool	m_bHaveShutDownConnection;

	//需不需要加密
	bool	_NeedKey;
	bool	_NeedCheckConnect;
	int		Time;
};

#pragma managed

#endif //_SOCKET_MANAGER_H
