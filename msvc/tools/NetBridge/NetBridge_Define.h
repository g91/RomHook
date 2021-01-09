#pragma	once

#include <Windows.h>

typedef void (*PFERRMSG)( DWORD dwLevel, DWORD dwErrID,  char *format,... );

//�w�q Winsock �ҨϥΪ��Ҧ�
enum EM_WINSOCK_IO_MODE
{
	OVERLAPPED_MODE				=0,
	IOCP_MODE					,
	TELNET_MODE					,
};

//�w�q�s�u�ҨϥΪ��Ҧ�	
enum EM_CONNECT_MODE
{
	EM_CONNECT_ONCE				=0,
	EM_CONNECT_KEEPTRY					
};

enum EM_SOCKET_MODE
{
	EM_SOCKET_MODE_NORMAL			,
	EM_SOCKET_MODE_TELNET			,
};

enum EM_SOCKET_STAUTS
{
	EM_SOCKET_UNCONNECT				=0,
	EM_SOCKET_CONNECTED				,
	EM_SOCKET_WAIT_CLOSE			,		// �{���n�D�����s�u, ���ݸ�Ƶo�e����
	EM_SOCKET_CLOSING				,
	EM_SOCKET_WAIT_DELETE			,
};

enum EM_AUTHORIZE_STAUTS
{
	EM_AUTHORIZE_OKAY				=0,
	EM_AUTHORIZE_WAIT_AUTHORIZE		,
	EM_AUTHORIZE_WAIT_PASS			,		// Connect out �謰���ݦ����{�Ҹ��, Connect In �謰���ݳs�J
	EM_AUTHORIZE_CHECK_AUTHORIZE	,		// Connect out �謰���ݦ����{�Ҹ��, Connect In �謰���ݳs�J
};

//#define DF_CONNECT_KEEPTRY_MAXTIME_MS	5000	//������ճs�u���ݳ̪����ɶ�

//�w�q���~�N�X
enum EM_ERROR_CODE
{
	NB_OK							=0,
	NB_ERR							=-1,
	NB_ERR_UNABLE_LOAD_WINSOCK		=-2,
	NB_ERR_UNABLE_CREATE_IOCP		=-3,
	NB_ERR_UNABLE_CREATE_IOCPTHREAD	=-4,
	
	NB_ERR_WRONG_ENCRYPTION			= 1,
};

//�w�q�򥻳]�w
#define		DF_MAX_HOST_SOCKET		64		//�ѷ� MAXIMUM_WAIT_OBJECTS �ҳ]���W��


// ���~�T����X


#define DF_NB_MAX_COMPLETION_THREAD_COUNT 32     // Maximum number of completion threads allowed

#define NBERR					0
#define NBERR_CANTFINDNETID		NBERR + 1



#define DF_NB_PACKETBUFFERSIZE			1008

// DF_NB_PACKETBUFFERSIZE must be 2^n  , so we did 1024 - BUFFERMANAGER_PREFIX_SIZE
//#define DF_NB_FRAMEBUFFERSIZE			1008

#define DF_NB_RECVPACKETBUFFERSIZE		2048
#define DF_NB_OVERLAPPEDCOUNTER			6
#define DF_NB_MAXPACKETSIZE				665535

#define DF_TEST_ACCEPTEX

#define DF_TIME_CLOSINGSOCKET	5000	// ����~�o�ͫ�, �h�֬�t�Υ��B�z�����D�� Socket. �ڭ̦ۤv�N������
#define DF_TIME_RECYCLEDELAY	60000
#define DF_TIME_FORCE_DELETE	600000	// �� 10 �����Y Socket ����������, �h�j������

#define DF_NB_TIME_KEEPALIVE		10000	// �W�L�o�Ӯɶ���, �o�e KeepAlive �T��
#define DF_NB_TIME_KEEPALIVECLOSE	20000	// �W�L�o�Ӯɶ���, �����_�u

#define DF_PTAG_KEEPALIVE_ANSWER	0x10000000
#define DF_PTAG_KEEPALIVE_REQUEST	0x20000000
#define DF_PTAG_COLLECT				0x40000000
#define DF_PTAG_COMORESS			0x80000000
#define DF_PTAG_MASK				0xF0000000
#define DF_PTAG_SIZEMASK			0x0FFFFFFF


#define DF_NB_AVG_EVENT_MS_TIME		200

#define DF_PSYSFLAG_CONNECTKEY		0x01
#define DF_PSYSFLAG_ENCRYPTION		0x02
#define DF_PSYSFLAG_R_ALIVE			0x04		// Request Alive provide	Srv->Cli
#define DF_PSYSFLAG_S_ALIVE			0x08		// Send Alive provide		Cli->Srv
#define DF_PSYSFLAG_S_CHECKSUMERR	0x10
#define DF_PSYSFLAG_COMPRESS		0x12

#define DF_PSYSFLAG_MASK			0xff







/*
#define MSG_PACKET			0
#define	MSG_CONNECTFAILED	1
#define	MSG_CONNECTED		2
#define	MSG_NEWCONNECTION	3
#define MSG_ERROR			4
*/

//�w�q Buffer ���A
enum EM_BUFFER_MODE
{
	EM_NULL					= 0,
	EM_ACCEPT				,
	EM_RECV					,
	EM_SEND					,
	EM_COMPRESS				,
	EM_CONNECT				,
};

enum EM_MSG_TYPE
{
	MSG_NULL			=0,
	MSG_RECV			,
	MSG_CONNECT_FAILED	,
	MSG_CONNECT			,
	MSG_ACCEPT			,
	MSG_SEND			,
	MSG_ERROR			,
	MSG_DISCONNECT		,
	MSG_AUTHORIZE		,
	MSG_SYSTEM			,
};


//extern BYTE g_authorize_key[10];
#define DF_KEYTABLE_LENGTH	10
extern BYTE g_NetBridge_KeyTable[DF_KEYTABLE_LENGTH];


