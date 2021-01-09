#pragma	once

#include <Windows.h>

typedef void (*PFERRMSG)( DWORD dwLevel, DWORD dwErrID,  char *format,... );

//定義 Winsock 所使用的模式
enum EM_WINSOCK_IO_MODE
{
	OVERLAPPED_MODE				=0,
	IOCP_MODE					,
	TELNET_MODE					,
};

//定義連線所使用的模式	
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
	EM_SOCKET_WAIT_CLOSE			,		// 程式要求關畢連線, 等待資料發送完畢
	EM_SOCKET_CLOSING				,
	EM_SOCKET_WAIT_DELETE			,
};

enum EM_AUTHORIZE_STAUTS
{
	EM_AUTHORIZE_OKAY				=0,
	EM_AUTHORIZE_WAIT_AUTHORIZE		,
	EM_AUTHORIZE_WAIT_PASS			,		// Connect out 方為等待收取認證資料, Connect In 方為等待連入
	EM_AUTHORIZE_CHECK_AUTHORIZE	,		// Connect out 方為等待收取認證資料, Connect In 方為等待連入
};

//#define DF_CONNECT_KEEPTRY_MAXTIME_MS	5000	//持續嘗試連線等待最長的時間

//定義錯誤代碼
enum EM_ERROR_CODE
{
	NB_OK							=0,
	NB_ERR							=-1,
	NB_ERR_UNABLE_LOAD_WINSOCK		=-2,
	NB_ERR_UNABLE_CREATE_IOCP		=-3,
	NB_ERR_UNABLE_CREATE_IOCPTHREAD	=-4,
	
	NB_ERR_WRONG_ENCRYPTION			= 1,
};

//定義基本設定
#define		DF_MAX_HOST_SOCKET		64		//參照 MAXIMUM_WAIT_OBJECTS 所設的上限


// 錯誤訊息輸出


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

#define DF_TIME_CLOSINGSOCKET	5000	// 當錯誤發生後, 多少秒系統未處理有問題的 Socket. 我們自己將之關畢
#define DF_TIME_RECYCLEDELAY	60000
#define DF_TIME_FORCE_DELETE	600000	// 當 10 分鐘某 Socket 仍未能釋放, 則強制釋放

#define DF_NB_TIME_KEEPALIVE		10000	// 超過這個時間後, 發送 KeepAlive 訊息
#define DF_NB_TIME_KEEPALIVECLOSE	20000	// 超過這個時間後, 執行斷線

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

//定義 Buffer 狀態
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


