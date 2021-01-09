#ifndef _OBJ_NET_H_
#define _OBJ_NET_H_

#ifndef _LIB

#ifdef OBJNET_EXPORTS
#define OBJNET_API __declspec(dllexport)
#else
#define OBJNET_API __declspec(dllimport)
#endif

#else
#define OBJNET_API
#endif

//#include <winsock.h>
#include "LNet.h"

#pragma pack( push, _obj_net_h_)
#pragma pack(8)

class IObjNet {

public:
	virtual ~IObjNet ()throw(){};

	virtual SOCKET	LSAPI Host(sockaddr_in* TCPAddr, INewConnectionListener* pListener) = 0;
	virtual void	LSAPI RemoveHost( SOCKET host_sock ) = 0;

 	virtual bool	LSAPI WaitingConnect( sockaddr_in* pAddr, INetEventListener* pListener ) = 0;
	virtual int		LSAPI Connect( sockaddr_in* pAddr, INetEventListener* pListener ) = 0;
	virtual void	LSAPI CancelConnect( int connect_number ) = 0;
	virtual void	LSAPI AttachClientListener( LNETID id, INetEventListener* pListener ) = 0;

	virtual void	LSAPI Flush(timeval* wait_time) = 0;
	// 供使用者可以在 Flush 之前送出資料
	// 要注意的是，此時仍然可能 callback OnDisconnected()
	virtual void	LSAPI SendFlush(timeval* wait_time) = 0;

	virtual void	LSAPI RevFlush(timeval* wait_time) = 0;
	
	virtual void	LSAPI Send(LNETID smid, int nSize, void* vpData, int nPriority ) = 0;
	virtual void	LSAPI SendToAll( int nSize, void* vpData ) = 0;
	virtual void	LSAPI SendToMutiple( int nNum, const LNET_PKT_DESTINATION* dest_array, int nSize, void* vpData) = 0;

	virtual void	LSAPI Close( LNETID smid ) = 0;
	virtual void	LSAPI ShutdownSendPipe( LNETID smid ) = 0;

	virtual UINT32	LSAPI GetContext(LNETID smid) = 0;
	virtual void	LSAPI SetContext(LNETID smid, UINT32 c) = 0;

	virtual UINT32	LSAPI GetNumOfBytesSend(void) = 0;
	virtual UINT32	LSAPI GetNumOfBytesRecv(void) = 0;
	virtual bool	LSAPI IsValidLNETID( LNETID u32ID ) = 0;
	virtual int		LSAPI GetNumOfPlayer(void) = 0;

	virtual void	LSAPI GetPeerAddress( LNETID u32id, sockaddr_in* pAddr ) = 0;

	virtual void	LSAPI EnumLNETID( SM_EnumLNETIDCallBack, void* pContext ) = 0;
	virtual void	LSAPI EnumConnections(LNET_EnumPlayersCallBack callback, void* vpContext) = 0;
	//virtual void	LSAPI AttachListener( SOCKET server_socket, INewConnectionListener* listener) = 0;

	virtual UINT32	LSAPI GetPacketLeftInSendQueue( LNETID u32id ) = 0;
	// below for compress
	virtual void	LSAPI GetCompressSuccessVSFailure( int& nSuccess, int& nFailed ) = 0;
	//virtual UINT32	LSAPI GetNumOf_NotCompressedBytes( void ) = 0;
	//virtual UINT32	LSAPI GetNumOf_CompressedBytes( void ) = 0;

	virtual UINT32	LSAPI GetNumOfConnections( void ) = 0;
	// no more than 32767
	virtual void	LSAPI SetMaxPacketSize( UINT32 u32Size ) = 0;

	//檢查是否還要資料沒有送出
	virtual bool	LSAPI CheckPacketEmpty() = 0;
	//---------------------------------------------------------------
	//**(再尚未連線時要設定)**
	//需要Key做封包編碼
	virtual void	LSAPI NeedKey() = 0;

	//**(再尚未連線時要設定 && Server設定)**
	//需要定時作連線檢查
	//如果不同步太嚴重則會被踢出
	virtual void	LSAPI NeedCheckConnect() = 0;
};




extern "C" {

//OBJNET_API IObjNet* LSAPI  CreateObjNet( bool bIsCompress ) throw();
OBJNET_API IObjNet* LSAPI  CreateObjNet( void ) throw();
OBJNET_API void LSAPI  DestroyObjNet( IObjNet* ) throw();

OBJNET_API 	void	LSAPI ObjNetBufferAddRef( HBUFFER hBuffer );
OBJNET_API 	void	LSAPI ObjNetBufferRelease( HBUFFER hBuffer );
OBJNET_API 	void	LSAPI ObjNetGetBuffer( HBUFFER hBuffer, int& nSize, void*& vpData );
}

#pragma pack( pop, _obj_net_h_ )
#endif //_OBJ_NET_H_
