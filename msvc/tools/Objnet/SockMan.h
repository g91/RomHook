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
// ���� new connection ���y�{
//	�]�@�w�n SocketManager::AttachEventListener �^
//
//	�� �s�� connection �i�Ӯ�:
//		1. SocketManager �|�I�s EventListener::OnNewConnection ���o�s��
//			Connection ��NetEventListener
//		2. �M��� NetEventListener �� OnConnected �|�Q�I�s
//
//	�� connect �X�h:
//		1. ���I�s Connect �A�ǤJ new connection �� listener
//		2. �Y�O�{�ǤW�S���D�A�� NetEventListener �� OnConnected �|�Q�I�s
//	�]�]���O Async ���A�ҥH�ä��O�Ҥ@�w�s�����W�A���u�n�s�����W�A
//    �| call INetEventListener:OnDisconnected �^
//
//=====================================================================================================================
// �ϥΤ�k�G
//		Init( port );
//		AttachHandler( this );
//		�M��u�@�N����� handler �Ӱ��F
//=====================================================================================================================
// �`�N�G �{�b�W���䴩�h���A�N�Ӧ��ɤ]�ݪ`�N�ASetPacketMode()�ɫܮe���X���D

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


	//�ݭnKey���ʥ]�s�X(Client)
	void	LSAPI NeedKey(){_NeedKey = true;};

	//�ݭn�w�ɧ@�s�u�ˬd
	//�p�G���P�B���Y���h�|�Q��X
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

	//�ݤ��ݭn�[�K
	bool	_NeedKey;
	bool	_NeedCheckConnect;
	int		Time;
};

#pragma managed

#endif //_SOCKET_MANAGER_H
