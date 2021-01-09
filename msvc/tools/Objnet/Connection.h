#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#pragma once

#pragma warning (disable:4949)

//=====================================================================================================================
// module: SocketManager
// author: Peacock <peacock@softstar.com.tw>
// create: 04/12/1999
// modify: revise 6/22/1999
//         review N/A
// level : Network Module
// reuse : single or multipile socket management
// file  : Connection.h, Connection.cpp
// test  : white box tested
// ref   : Connection.inl
//=====================================================================================================================
// Change:
// 6.22.1999
//		將 送出 packet size 的大小由 4 改成 2 ，增加 packet 的使用率
//=====================================================================================================================
//=====================================================================================================================
// 預設為 packet mode
// 基本上 data 不管用何種方式傳輸，最後都是 stream mode
// 注意： TextMode 時，請 new CBuf 用 Send 傳送
//		  PacketMode ，請 new CPacket，用 SendPkt 傳送
//=====================================================================================================================
// Close Connection 的方法：
//  ⊙Connection 若是配合 CSocketManager 使用
//		0. 不需 delete
//		1. 在 OnPacket() callback 時若要close connection ，需以傳回 false 的方式 close
//		2. 若是一般情況，直接 呼叫 Connection::RemoveFromLink() & delete 就可以了。
//
//	⊙ Connection 單獨使用：
//		直接 delete 即可
// 在 OnDisconnected 時，被呼叫的 object 不得已解構
// 就是若是該 object 以包含 Connection 方式，則必須在 ~destructor 時
// call CleanUp()
//=====================================================================================================================
#include <Time.h>
#include "LSocket.h"
//#include "LSockUtil.h"
//#include "LRefMem.h"
//#include "LList.h"
//#include <deque>
#include "LException.h"
#include "LMutex.h"
#include "LBuffer.h"
#include "LNet.h"
#include "ThreadFreeFIFO.h"
#pragma unmanaged
//#include "ThreadFreeFIFO.h"
// 至少必須大於 4 Bytes
//#define CONNECTION_MIN_WRITE_BUFFER_SIZE 512
//#define CONNECTION_MAX_READ_PACKET_SIZE 32767
//#define CONNECTION_MAX_WRITE_PACKET_SIZE 32767

#define CONNECTION_MAX_READ_PACKET_SIZE 65535
#define CONNECTION_MAX_WRITE_PACKET_SIZE 65535

//#include <deque>
//typedef ThreadFreeFIFO< HBUFFER > PACKET_LIST;
//typedef deque< HBUFFER > PACKET_LIST;
//====================================================================================================
// 註：此程式目前在 little-endian 上的機器才能跑（80X86, etc)

//系統一般封包
//檢查連線與斷線封包
#define _Conn_CheckType_CheckConnect_		0
//要求送檢查連線封包
#define _Conn_CheckType_NeedCheckConnect_	1

struct CheckPacket
{
	unsigned short Command;
	unsigned short Type;
	CheckPacket()
	{
		Command = 0xffff;
	}
};


class Connection
{
public:
	enum CN_STATUS{
		NOT_CREATED,
		CONNECTING,
		ESTABLISHED,
		PEER_SHUTDOWN_SEND,
		SHUTDOWN_SEND_PIPE,
		SHUTDOWNED
	};
protected:
	SOCKET			m_sock;
	LMutex			m_WrMutex;
	ThreadFreeFIFO<HBUFFER>	m_WrPacketList;

	WORD			m_u16WrPacketIndex;	// 上次沒寫完的 packet 寫到何處
	//WORD			m_wdWrPacketSize;	// 上次沒寫完的 packet 的大小


	HBUFFER			m_hWrBuffer;

	HBUFFER			m_hRdBuffer;			// 正在讀取的 packet
	WORD			m_u16ReadSize;		// packet mode 跟 text mode 共用
	WORD			m_u16ReadIndex;		// packet mode 跟 text mode 共用

	UINT32			m_u32TotalRecvSize;	// Total recvieve bytes size

	UINT32			m_u32Context;
	CN_STATUS		m_status;
	INetEventListener* m_pListener;
	LNETID			m_id;
	unsigned short	_Key;
	//此連結是否為Client
	bool			_ClientFlag;
	//需要連線檢查
	bool			_NeedCheckConnect;
	//上次封包檢查的時間
	int				_NextCheckConnect;
	//連線同步檢查(封包次數)
	int				_CheckConnectTimes;
	//KeyTable
	static	unsigned  char	_KeyTable[16];
	//資料編碼過
	bool			_DataEncodeFlag;
public:
	//----------------------------------------------------------------
	void Key(unsigned short V){_Key = V;}
	void NeedCheckConnect(){_NeedCheckConnect = true;_NextCheckConnect= clock()+5000;}
	void SetClient(){_ClientFlag = true;}
	

	bool IS_Client(){return _ClientFlag;};

	void SendCheckPack();
	//----------------------------------------------------------------
	void Create(SOCKET sock, LNETID id);
	void CleanUp(void);
	Connection();
	~Connection();

	void AttachListener( INetEventListener* pListener ) {m_pListener = pListener;}
	void SendPkt( int nSize, void* vpData );
	void SendPkt( HBUFFER );
	//PKT_ID Send( CRefMemList* list );

	inline SOCKET GetSocket(void);
	inline void GetPeerAddress(sockaddr* addr);// throw SockException;
	inline void GetSockAddress(sockaddr* addr);// throw SockException;
	
//	void Connection( SOCKET sock );
//	void CleanUp(void);		// clean up 之後 就能在 create
//	void CloseConnection();
	// GetXXXXAddress 要 connect 之後才能用

	UINT32	GetContext(void) throw() { return m_u32Context; }
	void	SetContext(UINT32 c) throw() { 
		//TRACE1("SetContext %d\n",c); 
		m_u32Context = c; 
	}

	bool ProcessDataOut(void);						// 傳回 false 表示此 connection 要結束
	bool NeedRead(void) { return !(m_status == SHUTDOWNED || m_status == PEER_SHUTDOWN_SEND || m_status == NOT_CREATED ); }
	bool HaveSomethingToWrite(void);				// 傳回 true 表示此 connection 有東西輸出
	void ShutdownSendPipe(void);

	bool ProcessDataIn(void);						// 傳回 false 表示此 connection 要結束

	//編碼 key尚未送到則回傳 false
	bool Encode(unsigned short Size,char*);

	//解碼 如果解出有問題則回傳 false
	bool Decode(unsigned short Size,char*);
	
	friend class cSockMan;
};
//inline CPacket* MAKE_PACKET( UINT size, BYTE* buf);
//========================================================================
// socket address serialize function
//inline IOutputStream& operator<<(IOutputStream& out, sockaddr_in &obj) throw( LIOException );
//inline IInputStream& operator>>(IInputStream& in, sockaddr_in &obj) throw( LIOException );

//====================================================================================================
#include "Connection.inl"
#pragma managed
#endif //_CONNECTION_H_
