#include <iostream>
#include <iomanip>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma pack(1)//定義對齊方式

//IP資料報頭
typedef struct
{
	unsigned char hdr_len:4;//頭部長度 4位
	unsigned char version:4;//版本號 4位
	unsigned char tos;//服務類型 8位
	unsigned short total_len;//總長度 16位
	unsigned short identifier;//標示符 16位
	unsigned short frag_flag;//3位旗標+13位片便宜
	unsigned char ttl;//生存時間 8位
	unsigned char protocol;//上層協議 8位
	unsigned short checksum;//檢查和 16位
	unsigned long source_ip;//源ip位址 32位
	unsigned long des_ip;//目的ip位址 32位

} IP_HEADER;

//ICMP資料報頭
typedef struct
{
	BYTE type;//類型欄位8位
	BYTE code;//代碼欄位8位
	USHORT cksum;//檢查和16位
	USHORT id;//標示符16位
	USHORT seq;//序號16位
} ICMP_HEADER;

//記錄分析結果
typedef struct
{
	USHORT seq;			//序號
	DWORD round_time;	//往返時間
	in_addr ip_address;	//對端IP位址

} TraceouteResult;
//總結果
typedef struct
{
	USHORT count;
	TraceouteResult Tracert[30];
} TracertResultList;
#pragma pack()

const BYTE ICMP_REQUEST	= 8;//ICMP要求回顯
const BYTE ICMP_REPLY = 0;//ICMP回顯應答
const BYTE ICMP_TIMEOUT = 11;//ICMP逾時

const DWORD DEF_ICMP_TIMEOUT	= 3000;	//預設逾時時間，單位ms
const int DEF_ICMP_DATA_SIZE	= 32;	//預設ICMP資料欄位的長度
const int MAX_ICMP_PACKET_SIZE	= 1024;	//最大ICMP資料報大小
const int MAX_HOP = 30;				//最大跳數

using namespace std;

USHORT chechsum(USHORT* input_buf, int Size);
bool decode(char* buffer, int size, TraceouteResult& result);
TracertResultList MyTracert( const char* IpStr);
