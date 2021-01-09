#pragma once
#include <boost/asio.hpp>

namespace MyAsio{
#define _BASE_PACKET_MAX_SIZE_ 1024

//////////////////////////////////////////////////////////////////////////
//��K�˵����~�T�������c
struct AsioErrorValueStruct
{
	union
	{
		int value;
		boost::asio::error::netdb_errors netdberr;
		boost::asio::error::basic_errors baseerr;
		boost::asio::error::addrinfo_errors addinfoerr;
		boost::asio::error::misc_errors miscerr;
	};
};
//////////////////////////////////////////////////////////////////////////
//�ʥ]���e��T
struct SockSendRevInfoStruct
{
	int send_bytes;
	int rev_bytes;
	int send_packets;
	int rev_packets;
	SockSendRevInfoStruct()
	{
		Init();
	}
	void SendSize( int size )
	{
		send_packets ++;
		send_bytes += size;
	}
	void RevSize( int size )
	{
		rev_packets ++;
		rev_bytes += size;
	}
	void Init()
	{
		send_bytes = 0;
		rev_bytes = 0;
		send_packets = 0;
		rev_packets = 0;
	}
};

struct SendBaseBufferStruct
{
	int				size;
	char*			buff;
};

}// namespace MyAsio
