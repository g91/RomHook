#include "Tracert.h"

TracertResultList MyTracert( const char* IpStr ) 
{

	TracertResultList result;//�s�x��R���G
	//��l��Windows Socket DLL
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout<<"Initialize Windows Socket DLL Error!"<<endl;
		cout<<"Error code: "<<WSAGetLastError()<<endl;
		return result;
	}

	u_long des_ip = inet_addr(IpStr);//�ت��D��ip��}
	if (des_ip == INADDR_NONE)//�p�G��J���O��W
	{
		//�i���W��ip���ഫ
		hostent* host = gethostbyname(IpStr);
		if (host)
		{
			des_ip = (*(in_addr*)host->h_addr).s_addr;
			cout<<"Tracing route to "<<IpStr<<" ["<<inet_ntoa(*(in_addr*)(&des_ip)) <<"] "<<" ";
		}
		else //��R�D���W����
		{
			cout<<"Can not decode the host name."<<endl;
			WSACleanup();
			return result;
		}
	}
	else
		cout<<"Tracing route to "<<IpStr<<" "; 

	cout<<"over a maximum of "<<MAX_HOP<<" hops"<<endl;

	sockaddr_in des_sock_add;//�s�x�ؼЦ�}
	ZeroMemory(&des_sock_add,sizeof(des_sock_add));
	des_sock_add.sin_family = AF_INET;
	des_sock_add.sin_addr.s_addr = des_ip;

	//�إ�socket
	SOCKET my_socket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(my_socket == INVALID_SOCKET)
	{
		cout<<"Set up the socket error!"<<endl;
		cout<<"Error Code�G"<<WSAGetLastError()<<endl;
		return result;
	}

	int time_out = DEF_ICMP_TIMEOUT;//�O�ɮɶ�

	//��socket�]�w�����M�ǰe���̤j�ɶ�
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

	char send_buffer[sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE];//�ǰe��ưO����w�İ�
	char reveive_buffer[MAX_ICMP_PACKET_SIZE];//������ưO����w�İ�
	//��l�ơA�N�O����w�İϥ����m�s
	memset(send_buffer,0,sizeof(send_buffer));
	memset(reveive_buffer,0,sizeof(reveive_buffer));

	ICMP_HEADER* send_icmp_hd = (ICMP_HEADER*)send_buffer;//ICMP�Y
	//��R�U�����
	send_icmp_hd->type = ICMP_REQUEST;
	send_icmp_hd->code = 0;
	send_icmp_hd->id = (USHORT)GetCurrentProcessId();
	memset(send_buffer+sizeof(ICMP_HEADER), 'E', DEF_ICMP_DATA_SIZE);

	bool reach = false;//�X�ЬO�_��F�ت��D��
	USHORT seq_number = 0;//�Ǹ�
	int max_hop = MAX_HOP;//�̤j����
	int ttl = 1;//ttl�A��l��1
	while(!reach&&max_hop--)
	{
		//�]�wttl
		setsockopt(my_socket,IPPROTO_IP,IP_TTL,(char*)&ttl,sizeof(ttl));
		cout<<setw(3)<<ttl<<flush;

		//��R�ǰe��icmp�]����L���
		((ICMP_HEADER*)send_buffer)->cksum = 0;
		((ICMP_HEADER*)send_buffer)->seq = htons(seq_number);
		seq_number++;
		((ICMP_HEADER*)send_buffer)->cksum = chechsum((USHORT*)send_buffer, sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE);

		//��l�Ƥ��R���G�����
		result.Tracert[seq_number-1].seq = ((ICMP_HEADER*)send_buffer)->seq;
		result.Tracert[seq_number-1].round_time = GetTickCount();

		//�o�]
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
			//���]
			read_len = recvfrom(my_socket,reveive_buffer,MAX_ICMP_PACKET_SIZE,0,(sockaddr*)&from,&from_len);
			if(read_len!=SOCKET_ERROR)
			{
				//��R��ƥ]
				if(decode(reveive_buffer, read_len, result.Tracert[seq_number-1]))
				{
					if (result.Tracert[seq_number-1].ip_address.s_addr == des_sock_add.sin_addr.s_addr)//�O�_��F�ؼХD��
					{
						result.count = seq_number;
						reach = TRUE;
					}
					cout<<'\t'<<inet_ntoa(result.Tracert[seq_number-1].ip_address)<<endl;
					break;
				}
			}
			//�����O��
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
		//ttl���W�A�ǰe@�ӥ]
		ttl++;
	}

	cout<<"Trace complete."<<endl;
	closesocket(my_socket);
	WSACleanup();
	return result;
}
/*********************************************************
�\��G�p���ˬd�M
�ѼơGinput_buf:���ˬd������
	  size:�w�İϪ��j�p
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
�\��G�ﱵ���쪺��ƥ]�i����R�A�ñN���G�s�Jresult��
�ѼơGbuffer:��������ƽw�İ�
	  size:�w�İϤj�p
	  result:���R���G
*********************************************************/
bool decode(char* buffer, int size, TraceouteResult& result)
{
	//�ˬd�]�j�p�O�_�X�k
	IP_HEADER* pIpHdr = (IP_HEADER*)buffer;
	int iIpHdrLen = pIpHdr->hdr_len * 4;
	if (size < (int)(iIpHdrLen+sizeof(ICMP_HEADER)))
		return false;
	
	ICMP_HEADER* pIcmpHdr = (ICMP_HEADER*)(buffer+iIpHdrLen);//ICMP�Y
	USHORT id, seq;//�s�x�q��ƥ]��Ū�J���ХܲũM�Ǹ�
	//�p�G�O�^�������h����Ū��
	if (pIcmpHdr->type == ICMP_REPLY)
	{
		id = pIcmpHdr->id;
		seq = pIcmpHdr->seq;
	}
	//�p�G�O�����O�ɡA�h�ݭn�i�@�B���R�᭱����ơA��o�ХܲũM�Ǹ�
	else if(pIcmpHdr->type == ICMP_TIMEOUT)
	{
		char* pInnerIpHdr = buffer+iIpHdrLen+sizeof(ICMP_HEADER);//IP�Y
		int iInnerIPHdrLen = ((IP_HEADER*)pInnerIpHdr)->hdr_len*4;//IP�Y��
		ICMP_HEADER* pInnerIcmpHdr = (ICMP_HEADER*)(pInnerIpHdr+iInnerIPHdrLen);//������ICMP�Y
		id = pInnerIcmpHdr->id;
		seq = pInnerIcmpHdr->seq;
	}
	else
		return false;
	//�P�_�O�_�����󥻵{���ǰe��icmp����
	if (id != (USHORT)GetCurrentProcessId() || seq !=result.seq) 
		return false;
	
	//�B�z���T���쪺ICMP��Ƴ�
	if (pIcmpHdr->type==ICMP_REPLY||pIcmpHdr->type==ICMP_TIMEOUT)
	{
		//�s�x�ѽX���G
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

