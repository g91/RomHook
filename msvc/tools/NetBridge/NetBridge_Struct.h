#pragma	once

#if _DEBUG
#define NET_BRIDGE_STRUCT_CNETSOCKET_DEBUG_PRINT 1
#define NET_BRIDGE_STRUCT_CBUFFER_DEBUG_PRINT 0
#else
#define NET_BRIDGE_STRUCT_CNETSOCKET_DEBUG_PRINT 0
#define NET_BRIDGE_STRUCT_CBUFFER_DEBUG_PRINT 0
#endif

#include <winsock2.h>
#include <mstcpip.h>
#include <mswsock.h>
#include <Windows.h>


#include <map>
#include <vector>
#include <queue>
#include <list>
#include <string>

#include "NetBridge_Define.h"
#include "NetBridge_EventObj.h"
#include "NetBridge_Collections.h"
//#include "DebugLog/errormessage.h"

using namespace std;

class CNetBridge_Base;
class CNetSocket;
class CEventMsg;
//class CBuffer;
//class CCritcalsection;







typedef DWORD (WINAPI *fpt_SetCriticalSectionSpinCount)(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);


#pragma pack(push,1) 
struct Struct_PacketHeader
{
	DWORD	dwTotalPacketSize;
	BYTE	wSystemFlag;
	BYTE	CheckSum;
	BYTE	HeaderChecksum;
	BYTE	Index;
	WORD	SendIndex;			// this packet send serial, �o�ӫʥ]�N���ǰe�Ǹ�
	WORD	RecvIndex;			// Recived send serial,	�w�g���쪺�ǰe�Ǹ�
};
#pragma pack(pop) 

class CCritcalsection
{
private:
	CRITICAL_SECTION	m_cs;
	HANDLE m_event;
	int count;
	std::string			m_csName;
	std::string			m_lastEnterFunc;
public:
	CCritcalsection()	
	{	
		//m_event = CreateEvent( NULL, false, true, NULL );
		//m_event = CreateSemaphore( NULL, 0, 1, NULL );
		InitializeCriticalSection( &m_cs ); 
		
		HMODULE hMod = ::GetModuleHandle("kernel32.dll");
		if(hMod)
		{
			FARPROC fp = ::GetProcAddress(hMod, "SetCriticalSectionSpinCount");
			if(fp)
			{
				((fpt_SetCriticalSectionSpinCount) fp)(&m_cs, 4000);
			}
		}

//		SetCriticalSectionSpinCount( &m_cs, 4000 );
		count = 0;
	}
	~CCritcalsection()	
	{	
		DeleteCriticalSection( &m_cs );		
		//CloseHandle( m_event );
	}

#if _DEBUG
    inline const char* GetName() { return m_csName.c_str(); }
#endif

	void	SetName( const char* pszName )	{ m_csName = pszName; }
	
	void	Enter( const char* pszFuncName )
	{	
		
		//Print(1, "CriticalSection", "[CSEnter][%s][%s] counter = %d ThreadId = %d", m_csName.c_str(), pszFuncName, count, GetCurrentThreadId());

		if( m_cs.LockCount < -1 )
		{
			//MessageBox( NULL, m_lastEnterFunc.c_str() ,"ERROR",MB_OK);
		}

		EnterCriticalSection( &m_cs );
		m_lastEnterFunc = pszFuncName;
		count++;
		if( count != 1 )
		{
			int a = 3;
			//MessageBox( NULL, "ERROR" ,"ERROR",MB_OK);
		}

		//WaitForSingleObject( m_event, INFINITE );
		//ResetEvent( m_event );
	}
	void	Leave( const char* pszFuncName )		
	{	
		//SetEvent( m_event );
		count--;


		if( m_cs.LockCount < -2 )
		{
			//MessageBox( NULL, m_lastEnterFunc.c_str() ,"ERROR",MB_OK);
		}

		m_lastEnterFunc = "";
		//Print(1, "CriticalSection", "[CSLeave][%s][%s] counter = %d ThreadId = %d", m_csName.c_str(), pszFuncName, count, GetCurrentThreadId());
		LeaveCriticalSection( &m_cs );
		
	}
};

/*
class CPacket
{
public:

DWORD	m_dwPacketSize;
BYTE*	m_pPacket;
};
*/


class CBuffer
{
public:

	CBuffer()
	{
		Init();
	}

	CBuffer( DWORD dwSize )	
	{
		Init();
		m_dwTotalSize	= dwSize;
	}

	void Init()
	{
		m_emMode		= EM_NULL;
		m_pNetSocket	= NULL;
		m_dwFlag		= 0;

		//m_pData			= new BYTE[ dwSize ];
		m_pData			= NULL;

		m_dwSize		= 0;
		m_dwTotalSize	= 0;


		m_CheckSum		= 0;


		m_IsCompress	= false;
		m_IsCollect		= false;

		ZeroMemory( &m_overlapped, sizeof( m_overlapped ) );

#if NET_BRIDGE_STRUCT_CBUFFER_DEBUG_PRINT
        char szDebug[255+1];
        _snprintf(szDebug, 255, " CBuffer(%u)\n", m_dwTotalSize);
        OutputDebugString(szDebug);
#endif
	}

	~CBuffer()
    {
#if NET_BRIDGE_STRUCT_CBUFFER_DEBUG_PRINT
        char szDebug[255+1];
        _snprintf(szDebug, 255, "~CBuffer(%u)\n", m_dwTotalSize);
        OutputDebugString(szDebug);
#endif
    };

	DWORD				GetRemain() { return ( m_dwTotalSize - m_dwSize ); }

	//DWORD				m_dwMode;
	WSAOVERLAPPED		m_overlapped;
	EM_BUFFER_MODE		m_emMode;
	CNetSocket*			m_pNetSocket;
	DWORD				m_dwFlag;

	bool				m_IsCompress;
	bool				m_IsCollect;

	BYTE*				m_pData;



	DWORD				m_dwSize;			// �D�n��Ƥj�p
	DWORD				m_dwSystemSize;		// �t�Φb�D�n��ƫ᭱�ҥe�Ϊ��Ŷ�
	DWORD				m_dwTotalSize;		// Buffer ��ڤW�Ҽȥέp����

	DWORD				m_dwPriority;
	DWORD				m_dwNextPriority;

	byte				m_CheckSum;

	map< DWORD, byte >	m_mapCheckSum;

	//CBuffer*			m_pLastBuffer;
	//CBuffer*			m_pNextBuffer;
};

class CFrameBuffer
{
public:
	CFrameBuffer() { Init(); }

	void Init()
	{
		m_pData			= NULL;
		m_dwStoreSize	= 0;
		m_AllocSize		= 0;
	}

	BYTE*				m_pData;
	DWORD				m_dwStoreSize;
	DWORD				m_AllocSize;
};

class CNetSocket
{
public:
	CNetSocket()
	{

		//m_dwTimeToClose				= 0;
		m_dwSendBuf					= 0;
		m_dwNetID					= 0;
		//m_pBuffer					= NULL;
		//m_pBufferIncomplete			= NULL;
		m_emStatus					= EM_SOCKET_UNCONNECT;
		m_pvecMsg					= NULL;
		m_pEvent					= NULL;

		m_dwIP						= 0;
		m_wPort						= 0;
		m_dwTimer					= 0;

		m_MsgRecvCount				= 0;


		m_IsCompress				= false;
		m_IsEncryption				= false;

		m_RecvKeyIndex				= 0;
		m_SendKeyIndex				= 0;

		
		m_dwLastRequestTick			= GetTickCount();
		m_dwRespondTime				= 0;
		m_dwRespondCheck			= 0;
		m_bRespond					= true;

		m_pConnectBuffer			= NULL;

		m_bSending					= false;
		m_iSendQueueBytes			= 0;

		m_pRecvBuff					= NULL;

		m_emMode					= EM_SOCKET_MODE_NORMAL;

		//m_dwBytesBufferNeedProcess	= 0;
		ZeroMemory( &m_overlapped_Recv ,	sizeof( WSAOVERLAPPED )		);
		ZeroMemory( &m_overlapped_Send ,	sizeof( WSAOVERLAPPED )		);
		ZeroMemory( m_arrayTemp,			sizeof( m_arrayTemp )		);

		m_debug						= 0;
		m_DebugIndex				= 0;

		// Recv
		//-------------------------------------------------------
		m_pRecvData					= NULL;
		m_dwSizeRecvData			= 0;
		m_dwCountRecvData			= 0;

		m_pRecvIncomplete			= NULL;
		m_dwSizeRecvIncomplete		= 0;
		m_bConnectOnce				= false;
		
		char szAddress[256];

		sprintf( szAddress, "m_cs_SocketIO[%x]", int(this) );
		m_cs_SocketIO.SetName( szAddress );
#if NET_BRIDGE_STRUCT_CNETSOCKET_DEBUG_PRINT
        OutputDebugString(" CNetSocket() - ");
        OutputDebugString(m_cs_SocketIO.GetName());
        OutputDebugString("\n");
#endif
		m_pContext					= NULL;
		m_SendIndex					= 0;
		m_RecvIndex					= 0;

		m_lastCheckRecvIndex			= GetTickCount();

		m_SendQueueSize					= 0;

	};

#if NET_BRIDGE_STRUCT_CNETSOCKET_DEBUG_PRINT
    ~CNetSocket()
    {
        OutputDebugString("~CNetSocket() - ");
        OutputDebugString(m_cs_SocketIO.GetName());
        OutputDebugString("\n");
    }
#endif

	WSAOVERLAPPED				m_overlapped_Send;		// as named

	// General
	//--------------------------------------------------------
	DWORD						m_dwNetID;
	SOCKET						m_tcp_socket;

	DWORD						m_dwIP;
	WORD						m_wPort;

	BOOL						m_bConnectOnce;				// �O�_���g�s�u���\�L

	EM_SOCKET_STAUTS			m_emStatus;
	EM_SOCKET_MODE				m_emMode;

	DWORD						m_dwTimer;
	BYTE						m_DebugIndex;				// ������, �����ثe�o�e�ʥ]���Ǹ�

	EM_AUTHORIZE_STAUTS			m_emAuthorize;
	CEventObj*					m_pEvent;
	
	//vector< CEventMsg* >*		m_pvecMsg;					// ���V�ثe Socket �˺A������ queue;
	CNetQueue< CEventMsg* >*	m_pvecMsg;


	//list< CEventMsg* >*			m_plistMsg;
	//DWORD						m_dwTimeToClose;

	CNetBridge_Base*			m_pNetBridge;				// ���V���ݪ����h��

	//CCritcalsection				m_cs_queueSend;
	CCritcalsection				m_cs_SocketIO;				// �Φb Socket IO �ʧ@�ɧ@������w��	

	DWORD						m_dwLastRequestTick;		// The last tick request client respond
	DWORD						m_dwRespondTime;			// �̫᪺�����ɶ� ( PING )
	DWORD						m_dwAvgRespondTime;			// �����������ɶ� ( PING ), �C�� PING �����G�u�� 10% ����ҼW��, �H�קK��M����i
	DWORD						m_dwRespondCheck;			// �C�@�w�ɶ��ˬd����, �Y�L����, �h�N�ӭȥ[�@
	BOOL						m_bRespond;


	//--------------------------------------------------------
	//queue< CBuffer* >			m_queueAccept;				// ��m�������� Buffer ���, �ΨӰO������
	vector< CBuffer* >			m_vecAccept;

	//--------------------------------------------------------
	//queue< CBuffer* >			m_queueRecv;				// ��m�������� Buffer ���, �ΨӰO������
	

	CNetQueue< CFrameBuffer >	m_queueSendFrame;			// �Ψө�m�B�z�L, �ݵo�e�X�h���w�İ�

	int							m_iSendQueueBytes;			// Total bytes in m_queueSendFrame

	bool						m_bSending;					// �O�_���b�o�e�ʥ] (Indicates whether a send packet is posted and in-flight)
	CBuffer						m_SendBuffer;
	//--------------------------------------------------------



	CBuffer*					m_pConnectBuffer;			// �ΨӳB�z�s�u�Ϊ� Buff
	DWORD						m_MsgRecvCount;				// �٦��h�ְT���٥��Q�B�z


	// Recv
	//--------------------------------------------------------
	//CBuffer*					m_pBufferIncomplete;		// ��m�B�z���L�k�P�_�ʥ]�j�p�������㪺���
	//CBuffer*					m_pBuffer;					// ��m�B�z���������㪺���

	//BYTE						m_RecvBuffer[DF_NB_PACKETBUFFERSIZE];		// �w���t�m�n, ����ʥ]�ѪR�e�ϥΪ��Ȧs�Ŷ�

	//deque< CBuffer* >			m_vecRecv;
	CBuffer*					m_pRecvBuff;

	BYTE*						m_pRecvIncomplete;			
	DWORD						m_dwSizeRecvIncomplete;							// �ثe�Ŷ�����ƪ��j�p

	BYTE*						m_pRecvData;				// �Ȧs���쪺���
	DWORD						m_dwSizeRecvData;			// �Ȧs���쪺��ƪ��j�p
	DWORD						m_dwCountRecvData;
	//--------------------------------------------------------

	// For Send
	//--------------------------------------------------------
	//queue< CBuffer* >			m_queueSend;				// �e�X�����ʥ]
	vector< CBuffer* >			m_vecWaitToSend;			// ���ݥ��]�����Y���ʥ]
	//vector< CBuffer* >			m_vecSend;				// �w�e�X���ʥ],���� IOCP ���u
	DWORD						m_dwSendBuf;				// �ثe�p���餤���h�� Buffer �b�ǰe��
	CBuffer*					m_arrayTemp[ DF_NB_OVERLAPPEDCOUNTER ]; // �S�� Buffer ���Ǩ��o��, �|���ȩ�o��

	//queue< CPacket* >			m_queueSend;
	//queue< CBuffer* >			m_queueBuffer;
	
	// Compress
	//--------------------------------------------------------
	BOOL						m_IsCompress;
	
	// Encryption
	//--------------------------------------------------------
	BOOL						m_IsEncryption;

	BYTE						m_RecvKeyIndex;
	BYTE						m_SendKeyIndex;

	BYTE						m_KeyTable[ DF_KEYTABLE_LENGTH ];
	
	// IOCP
	//--------------------------------------------------------
	LPFN_ACCEPTEX				m_pfnAcceptEx;				// ���V 
	LPFN_GETACCEPTEXSOCKADDRS	m_pfnGetAcceptExSockaddrs;
	LPFN_CONNECTEX				m_pfnConnectEx;				// ���V 

	// OVERLAPPED
	//--------------------------------------------------------
	HANDLE						m_thread_Accept;	// �Y Socket �� listen ���A, �K�|���@ Thread ���䵥�� Accept
	HANDLE						m_thread_Recv;
	HANDLE						m_thread_Send;
	HANDLE						m_event_PreSend;

	WSAOVERLAPPED				m_overlapped_Recv;		// as named
	DWORD						m_debug;
	WSAEVENT					m_wsaEvent;				
	PVOID						m_pContext;
	//	WSAOVERLAPPED				m_overlapped_Send;		// as named

	BYTE						m_lastPacket[2048];
	BYTE						m_lastPacketSize;

	// for checksum error, re-send packet

	int							m_SendQueueSize;	


	// For Accept Socket
	//--------------------------------------------------------
	
	// Checksum error 
	//--------------------------------------------------------
	WORD							m_SendIndex;
	WORD							m_RecvIndex;
	DWORD							m_lastCheckRecvIndex;


	// For Accept Socket
	//--------------------------------------------------------


	//WSAEVENT	m_event;
};


class CEventMsg
{
public:
	CEventMsg()	{ emMsg = MSG_NULL; dwEventID = 0; pSocket = NULL; }

	//DWORD			m_dwMsgID;
	EM_MSG_TYPE		emMsg;
	//DWORD			m_dwNetID;			// �ƥ�����H

	DWORD			dwEventID;		// �q�Ϊ��ƥ�N��

	CNetSocket*		pSocket;
	DWORD			dwNetID;		// �� ID �D��


	union
	{
		struct 
		{
			//DWORD	dwNetID;
			CNetSocket*		pAcceptSocket;
		} MsgAccept;

		struct 
		{
			//CBuffer*	pBuffer;			// �o�̪��o����, �@���ΥΧ��K�|�Q����
			BYTE*		pPacket;
			BYTE*		pData;
			DWORD		dwDataSize;
		} MsgRecv;

		struct 
		{
			DWORD	dwErrorID;
		} MsgError;

		struct 
		{
			DWORD	dwFailID;
		} MsgConnectFailed;

		struct  
		{
			BYTE	AuthorizeIndex;
			BOOL	IsCompress;
			BOOL	IsEncryption;
		} MsgAuthorize;

		struct  
		{
			Struct_PacketHeader*	pHeader;		
			BYTE*					pData;
			DWORD					dwDataSize;
		} MsgSystem;
	};
};

struct Struct_PacketAuthorize
{
	BYTE AuthorizeIndex;
	BOOL IsEncryption;
	BOOL IsCompress;
};

struct Struct_PacketReplyAuthorize
{
	BYTE LastAuthorizeIndex;
};



/*
bool	CompareDeleteTime( const CNetSocket*& pScoket1 , const CNetSocket*& pScoket2 )
{
	return true;
}
*/


/*
struct CompareCloseTime : public binary_function <CNetSocket*, CNetSocket*, bool> 
{
	bool operator()(const CNetSocket*& _Left, 	const CNetSocket*& _Right ) const
	{
		if( _Left->m_dwTimeToClose < _Right->m_dwTimeToClose )
			return true;
		else
			return false;
	}
};
*/