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
//		�N �e�X packet size ���j�p�� 4 �令 2 �A�W�[ packet ���ϥβv
//=====================================================================================================================
//=====================================================================================================================
// �w�]�� packet mode
// �򥻤W data ���ޥΦ�ؤ覡�ǿ�A�᳣̫�O stream mode
// �`�N�G TextMode �ɡA�� new CBuf �� Send �ǰe
//		  PacketMode �A�� new CPacket�A�� SendPkt �ǰe
//=====================================================================================================================
// Close Connection ����k�G
//  ��Connection �Y�O�t�X CSocketManager �ϥ�
//		0. ���� delete
//		1. �b OnPacket() callback �ɭY�nclose connection �A�ݥH�Ǧ^ false ���覡 close
//		2. �Y�O�@�뱡�p�A���� �I�s Connection::RemoveFromLink() & delete �N�i�H�F�C
//
//	�� Connection ��W�ϥΡG
//		���� delete �Y�i
// �b OnDisconnected �ɡA�Q�I�s�� object ���o�w�Ѻc
// �N�O�Y�O�� object �H�]�t Connection �覡�A�h�����b ~destructor ��
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
// �ܤ֥����j�� 4 Bytes
//#define CONNECTION_MIN_WRITE_BUFFER_SIZE 512
//#define CONNECTION_MAX_READ_PACKET_SIZE 32767
//#define CONNECTION_MAX_WRITE_PACKET_SIZE 32767

#define CONNECTION_MAX_READ_PACKET_SIZE 65535
#define CONNECTION_MAX_WRITE_PACKET_SIZE 65535

//#include <deque>
//typedef ThreadFreeFIFO< HBUFFER > PACKET_LIST;
//typedef deque< HBUFFER > PACKET_LIST;
//====================================================================================================
// ���G���{���ثe�b little-endian �W�������~��]�]80X86, etc)

//�t�Τ@��ʥ]
//�ˬd�s�u�P�_�u�ʥ]
#define _Conn_CheckType_CheckConnect_		0
//�n�D�e�ˬd�s�u�ʥ]
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

	WORD			m_u16WrPacketIndex;	// �W���S�g���� packet �g���B
	//WORD			m_wdWrPacketSize;	// �W���S�g���� packet ���j�p


	HBUFFER			m_hWrBuffer;

	HBUFFER			m_hRdBuffer;			// ���bŪ���� packet
	WORD			m_u16ReadSize;		// packet mode �� text mode �@��
	WORD			m_u16ReadIndex;		// packet mode �� text mode �@��

	UINT32			m_u32TotalRecvSize;	// Total recvieve bytes size

	UINT32			m_u32Context;
	CN_STATUS		m_status;
	INetEventListener* m_pListener;
	LNETID			m_id;
	unsigned short	_Key;
	//���s���O�_��Client
	bool			_ClientFlag;
	//�ݭn�s�u�ˬd
	bool			_NeedCheckConnect;
	//�W���ʥ]�ˬd���ɶ�
	int				_NextCheckConnect;
	//�s�u�P�B�ˬd(�ʥ]����)
	int				_CheckConnectTimes;
	//KeyTable
	static	unsigned  char	_KeyTable[16];
	//��ƽs�X�L
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
//	void CleanUp(void);		// clean up ���� �N��b create
//	void CloseConnection();
	// GetXXXXAddress �n connect ����~���

	UINT32	GetContext(void) throw() { return m_u32Context; }
	void	SetContext(UINT32 c) throw() { 
		//TRACE1("SetContext %d\n",c); 
		m_u32Context = c; 
	}

	bool ProcessDataOut(void);						// �Ǧ^ false ��ܦ� connection �n����
	bool NeedRead(void) { return !(m_status == SHUTDOWNED || m_status == PEER_SHUTDOWN_SEND || m_status == NOT_CREATED ); }
	bool HaveSomethingToWrite(void);				// �Ǧ^ true ��ܦ� connection ���F���X
	void ShutdownSendPipe(void);

	bool ProcessDataIn(void);						// �Ǧ^ false ��ܦ� connection �n����

	//�s�X key�|���e��h�^�� false
	bool Encode(unsigned short Size,char*);

	//�ѽX �p�G�ѥX�����D�h�^�� false
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
