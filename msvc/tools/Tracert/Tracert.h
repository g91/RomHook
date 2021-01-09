#include <iostream>
#include <iomanip>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma pack(1)//�w�q����覡

//IP��Ƴ��Y
typedef struct
{
	unsigned char hdr_len:4;//�Y������ 4��
	unsigned char version:4;//������ 4��
	unsigned char tos;//�A������ 8��
	unsigned short total_len;//�`���� 16��
	unsigned short identifier;//�Хܲ� 16��
	unsigned short frag_flag;//3��X��+13����K�y
	unsigned char ttl;//�ͦs�ɶ� 8��
	unsigned char protocol;//�W�h��ĳ 8��
	unsigned short checksum;//�ˬd�M 16��
	unsigned long source_ip;//��ip��} 32��
	unsigned long des_ip;//�ت�ip��} 32��

} IP_HEADER;

//ICMP��Ƴ��Y
typedef struct
{
	BYTE type;//�������8��
	BYTE code;//�N�X���8��
	USHORT cksum;//�ˬd�M16��
	USHORT id;//�Хܲ�16��
	USHORT seq;//�Ǹ�16��
} ICMP_HEADER;

//�O�����R���G
typedef struct
{
	USHORT seq;			//�Ǹ�
	DWORD round_time;	//����ɶ�
	in_addr ip_address;	//���IP��}

} TraceouteResult;
//�`���G
typedef struct
{
	USHORT count;
	TraceouteResult Tracert[30];
} TracertResultList;
#pragma pack()

const BYTE ICMP_REQUEST	= 8;//ICMP�n�D�^��
const BYTE ICMP_REPLY = 0;//ICMP�^������
const BYTE ICMP_TIMEOUT = 11;//ICMP�O��

const DWORD DEF_ICMP_TIMEOUT	= 3000;	//�w�]�O�ɮɶ��A���ms
const int DEF_ICMP_DATA_SIZE	= 32;	//�w�]ICMP�����쪺����
const int MAX_ICMP_PACKET_SIZE	= 1024;	//�̤jICMP��Ƴ��j�p
const int MAX_HOP = 30;				//�̤j����

using namespace std;

USHORT chechsum(USHORT* input_buf, int Size);
bool decode(char* buffer, int size, TraceouteResult& result);
TracertResultList MyTracert( const char* IpStr);
