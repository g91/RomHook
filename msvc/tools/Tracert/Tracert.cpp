#include "Tracert.h"

TracertResultList MyTracert( const char* IpStr ) 
{

	TracertResultList result;//存儲剖析結果
	//初始化Windows Socket DLL
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout<<"Initialize Windows Socket DLL Error!"<<endl;
		cout<<"Error code: "<<WSAGetLastError()<<endl;
		return result;
	}

	u_long des_ip = inet_addr(IpStr);//目的主機ip位址
	if (des_ip == INADDR_NONE)//如果輸入的是域名
	{
		//進行域名到ip的轉換
		hostent* host = gethostbyname(IpStr);
		if (host)
		{
			des_ip = (*(in_addr*)host->h_addr).s_addr;
			cout<<"Tracing route to "<<IpStr<<" ["<<inet_ntoa(*(in_addr*)(&des_ip)) <<"] "<<" ";
		}
		else //剖析主機名失敗
		{
			cout<<"Can not decode the host name."<<endl;
			WSACleanup();
			return result;
		}
	}
	else
		cout<<"Tracing route to "<<IpStr<<" "; 

	cout<<"over a maximum of "<<MAX_HOP<<" hops"<<endl;

	sockaddr_in des_sock_add;//存儲目標位址
	ZeroMemory(&des_sock_add,sizeof(des_sock_add));
	des_sock_add.sin_family = AF_INET;
	des_sock_add.sin_addr.s_addr = des_ip;

	//建立socket
	SOCKET my_socket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(my_socket == INVALID_SOCKET)
	{
		cout<<"Set up the socket error!"<<endl;
		cout<<"Error Code："<<WSAGetLastError()<<endl;
		return result;
	}

	int time_out = DEF_ICMP_TIMEOUT;//逾時時間

	//對socket設定接受和傳送的最大時間
	if(setsockopt(my_socket,SOL_SOCKET,SO_RCVTIMEO,(char*)&time_out,sizeof(time_out))==SOCKET_ERROR)
	{
		cout<<"Set the rectimeout error!"<<endl;
		closesocket(my_socket);
		WSACleanup();
		return result;
	}
	if(setsockopt(my_socket,SOL_SOCKET,SO_SNDTIMEO,(char*)&time_out,sizeof(time_out))==SOCKET_ERROR)
	{
		cout<<"Set the sndtimeout error!"<<endl;
		closesocket(my_socket);
		WSACleanup();
		return result;
	}

	char send_buffer[sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE];//傳送資料記憶體緩衝區
	char reveive_buffer[MAX_ICMP_PACKET_SIZE];//接受資料記憶體緩衝區
	//初始化，將記憶體緩衝區全部置零
	memset(send_buffer,0,sizeof(send_buffer));
	memset(reveive_buffer,0,sizeof(reveive_buffer));

	ICMP_HEADER* send_icmp_hd = (ICMP_HEADER*)send_buffer;//ICMP頭
	//填充各個欄位
	send_icmp_hd->type = ICMP_REQUEST;
	send_icmp_hd->code = 0;
	send_icmp_hd->id = (USHORT)GetCurrentProcessId();
	memset(send_buffer+sizeof(ICMP_HEADER), 'E', DEF_ICMP_DATA_SIZE);

	bool reach = false;//旗標是否到達目的主機
	USHORT seq_number = 0;//序號
	int max_hop = MAX_HOP;//最大跳數
	int ttl = 1;//ttl，初始為1
	while(!reach&&max_hop--)
	{
		//設定ttl
		setsockopt(my_socket,IPPROTO_IP,IP_TTL,(char*)&ttl,sizeof(ttl));
		cout<<setw(3)<<ttl<<flush;

		//填充傳送的icmp包的其他欄位
		((ICMP_HEADER*)send_buffer)->cksum = 0;
		((ICMP_HEADER*)send_buffer)->seq = htons(seq_number);
		seq_number++;
		((ICMP_HEADER*)send_buffer)->cksum = chechsum((USHORT*)send_buffer, sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE);

		//初始化分析結果的欄位
		result.Tracert[seq_number-1].seq = ((ICMP_HEADER*)send_buffer)->seq;
		result.Tracert[seq_number-1].round_time = GetTickCount();

		//發包
		if(sendto(my_socket,send_buffer,sizeof(send_buffer),0,(sockaddr*)&des_sock_add,sizeof(des_sock_add))==SOCKET_ERROR)
		{
			if(WSAGetLastError()==WSAEHOSTUNREACH)
				cout<<"Can not reach the destination!"<<endl;
			closesocket(my_socket);
			WSACleanup();
			return result;
		}

		sockaddr_in from;
		int from_len = sizeof(from);
		int read_len;

		while(true)
		{
			//接包
			read_len = recvfrom(my_socket,reveive_buffer,MAX_ICMP_PACKET_SIZE,0,(sockaddr*)&from,&from_len);
			if(read_len!=SOCKET_ERROR)
			{
				//剖析資料包
				if(decode(reveive_buffer, read_len, result.Tracert[seq_number-1]))
				{
					if (result.Tracert[seq_number-1].ip_address.s_addr == des_sock_add.sin_addr.s_addr)//是否到達目標主機
					{
						result.count = seq_number;
						reach = TRUE;
					}
					cout<<'\t'<<inet_ntoa(result.Tracert[seq_number-1].ip_address)<<endl;
					break;
				}
			}
			//接收逾時
			else if (WSAGetLastError() == WSAETIMEDOUT) 
			{
				cout<<setw(9)<<'*'<<'\t'<<"Request timed out."<<endl;
				break;
			}
			else
			{
				cout<<"Receive data error!"<<endl;
				cout<<"Error Code: "<<WSAGetLastError()<<endl;
				closesocket(my_socket);
				WSACleanup();
				return result;
			}
		}
		//ttl遞增，傳送@個包
		ttl++;
	}

	cout<<"Trace complete."<<endl;
	closesocket(my_socket);
	WSACleanup();
	return result;
}
/*********************************************************
功能：計算檢查和
參數：input_buf:待檢查的部份
	  size:緩衝區的大小
*********************************************************/
USHORT chechsum(USHORT* input_buf, int size) 
{
	unsigned long cksum = 0;
	while (size>1) 
	{
		cksum += *input_buf++;
		size -= sizeof(USHORT);
	}
	if (size) 
		cksum += *(UCHAR*)input_buf;
	
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	
	return (USHORT)(~cksum);
}

/*********************************************************
功能：對接受到的資料包進行分析，並將結果存入result中
參數：buffer:接受的資料緩衝區
	  size:緩衝區大小
	  result:分析結果
*********************************************************/
bool decode(char* buffer, int size, TraceouteResult& result)
{
	//檢查包大小是否合法
	IP_HEADER* pIpHdr = (IP_HEADER*)buffer;
	int iIpHdrLen = pIpHdr->hdr_len * 4;
	if (size < (int)(iIpHdrLen+sizeof(ICMP_HEADER)))
		return false;
	
	ICMP_HEADER* pIcmpHdr = (ICMP_HEADER*)(buffer+iIpHdrLen);//ICMP頭
	USHORT id, seq;//存儲從資料包中讀入的標示符和序號
	//如果是回顯應答則直接讀取
	if (pIcmpHdr->type == ICMP_REPLY)
	{
		id = pIcmpHdr->id;
		seq = pIcmpHdr->seq;
	}
	//如果是接受逾時，則需要進一步分析後面的資料，獲得標示符和序號
	else if(pIcmpHdr->type == ICMP_TIMEOUT)
	{
		char* pInnerIpHdr = buffer+iIpHdrLen+sizeof(ICMP_HEADER);//IP頭
		int iInnerIPHdrLen = ((IP_HEADER*)pInnerIpHdr)->hdr_len*4;//IP頭長
		ICMP_HEADER* pInnerIcmpHdr = (ICMP_HEADER*)(pInnerIpHdr+iInnerIPHdrLen);//內部的ICMP頭
		id = pInnerIcmpHdr->id;
		seq = pInnerIcmpHdr->seq;
	}
	else
		return false;
	//判斷是否對應於本程式傳送的icmp應答
	if (id != (USHORT)GetCurrentProcessId() || seq !=result.seq) 
		return false;
	
	//處理正確收到的ICMP資料報
	if (pIcmpHdr->type==ICMP_REPLY||pIcmpHdr->type==ICMP_TIMEOUT)
	{
		//存儲解碼結果
		result.ip_address.s_addr = pIpHdr->source_ip;
		result.round_time = GetTickCount()-result.round_time;

		if (result.round_time)
			cout<<setw(6)<<result.round_time<<" ms"<< flush;
		else
			cout<<setw(6)<<"<1"<<" ms"<<flush;
		return true;
	}
	
	return false;
}

