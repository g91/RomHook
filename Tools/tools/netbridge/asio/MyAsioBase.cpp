#include "MyAsioBase.h"
#include <boost/bind.hpp>
#include <time.h>

namespace MyAsio{
vector< char* >	MyTcpConnection::_unused_send_buff;
//////////////////////////////////////////////////////////////////////////
// MyTcpConnection 
//////////////////////////////////////////////////////////////////////////
MyTcpConnection::MyTcpConnection(boost::asio::io_service& io_service , NetAsioBase*	net_asio )
		: _socket(io_service)	
{ 
	_net_asio = net_asio;
	_net_id = -1;
	_on_send_flag_ = false;
}

MyTcpConnection::~MyTcpConnection()	
{ 
	if( _net_id == -1 )
		_net_asio->EventListener()->OnDisconnect( _net_id );	
}

tcp::socket& MyTcpConnection::Socket()
{ 
	return _socket; 
}

//連線成立 開始傳送資料
void MyTcpConnection::Start( UInt32 net_id )
{
	_net_id = net_id;
	_net_asio->EventListener()->OnConnect( _net_id );


	boost::asio::async_read( Socket() ,			
		boost::asio::buffer(_rev_buff.GetReadBuff() , _BASE_PACKET_MAX_SIZE_ ),
		boost::asio::transfer_at_least( sizeof(PacketHeader) ),
		boost::bind(&MyTcpConnection::Handle_Read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)); 

}
void MyTcpConnection::SendBase( UInt32 size , void* data )
{

	char* buff;
	if( size > 1024 )
		buff = new char[size];
	else
	{
		if( _unused_send_buff.size() != 0 )
		{
			buff = _unused_send_buff.back();
			_unused_send_buff.pop_back();
		}
		else
		{
			buff = new char[1024];
		}
	}

	memcpy( buff , data , size );

	if( _on_send_flag_ != false )
	{
		SendBaseBufferStruct temp;
		temp.buff = buff;
		temp.size = size;
		_send_list.push_back( temp );
	}
	else
	{
		_on_send_flag_ = true;
		boost::asio::async_write(Socket() , boost::asio::buffer(buff,size),
			boost::bind(&MyTcpConnection::Handle_Write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred,
			buff ));

	}
}


void MyTcpConnection::Handle_Write( const boost::system::error_code& error,	size_t bytes_transferred , void* buff )
{
	if( error.value() != 0 )
	{
		AsioErrorValueStruct errmsg;
		errmsg.value = error.value();
		_net_asio->Close( _net_id );

		OutputDebugStringA( error.message().c_str() );
		_net_asio->_outputFunc( 5, error.message().c_str() );
		return;
	}
	_on_send_flag_ = false;
	if( _send_list.size() != 0 )
	{
		_on_send_flag_ = true;

		SendBaseBufferStruct& temp = _send_list.front();
		boost::asio::async_write(Socket() , boost::asio::buffer(temp.buff ,temp.size),
			boost::bind(&MyTcpConnection::Handle_Write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred,
			temp.buff ));
		_send_list.pop_front();
	}

	if( bytes_transferred > 1024 )
			delete buff;
	else
		_unused_send_buff.push_back( (char*)buff );
}

void MyTcpConnection::Send( UInt32 size , void* data )
{
	//SendBase( size , data );
	if( _send_buff.Add( size , data ) == false )
	{
		SendBase( _send_buff.Size() , _send_buff.Data() );
		_send_buff.Clear();
		if( size < 512 )
		{
			_send_buff.Add( size , data );
		}
		else
			SendBase( size , data );
	}
}
void MyTcpConnection::SendFlush()
{
	if( _send_buff.Size() == 0 )
		return;

	SendBase( _send_buff.Size() , _send_buff.Data() );
	_send_buff.Clear();
}
int MyTcpConnection::NetID()
{
	return _net_id;
}

void MyTcpConnection::Handle_Read	(const boost::system::error_code& error, size_t bytes_transferred )
{
	if( bytes_transferred == 0 && error.value() != 0 )
	{		
		AsioErrorValueStruct errmsg;
		errmsg.value = error.value();
		_net_asio->Close( _net_id );

		OutputDebugStringA( error.message().c_str() );
		_net_asio->_outputFunc( 5, error.message().c_str() );
		return;
	}

	int				packet_size;
	void*			packet_data;
	PacketHeader	packet_header;

	_rev_buff.ReadData( bytes_transferred );

	while( _rev_buff.GetPacket(packet_header,&packet_data) != false )
	{
		_net_asio->_sock_send_rev_info_now.RevSize( packet_header.Size + sizeof(packet_header) );

		if( _net_asio->GetCheckSum( packet_header.Size, packet_data ) != packet_header.CheckSum )
		{
			_net_asio->_outputFunc( 5, "CheckSum Error" );
			_net_asio->Close( _net_id );
		}


		_net_asio->EventListener()->OnRecv( _net_id , packet_header.Size , packet_data );
	}
	//整理讀取的Buff
	_rev_buff.ResetBuff();

	int read_buff_size = 0;
	int read_at_least_size = 0;
	
	_rev_buff.GetReadBuffSize( read_buff_size , read_at_least_size );

	memset( _rev_buff.GetReadBuff() , 1 , read_buff_size );//debug
	boost::asio::async_read( Socket() ,			
		boost::asio::buffer(_rev_buff.GetReadBuff() , read_buff_size  ),
		boost::asio::transfer_at_least(read_at_least_size),
		boost::bind(&MyTcpConnection::Handle_Read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)); 

}
//////////////////////////////////////////////////////////////////////////
// NetAsioBase
//////////////////////////////////////////////////////////////////////////
boost::asio::io_service*		NetAsioBase::_io_service = NULL;
int								NetAsioBase::_io_serveice_alloc_count = 0;

void EmpytOutputFun( int lv, const char* )
{

}

void	NetAsioBase::SetOutPutCB( OutputCBFun pFun )
{
	_outputFunc = pFun;
}
void*	NetAsioBase::GetContext	( )
{
	return _context;
}
void	NetAsioBase::SetContext	( void* context )
{
	_context = context;
}


NetAsioBase::NetAsioBase() //:_timer( _io_service, boost::posix_time::seconds(1) )
{
	_io_serveice_alloc_count++;
	if( _io_service == NULL )
		_io_service = new boost::asio::io_service;

	_timer = new boost::asio::deadline_timer( *_io_service, boost::posix_time::seconds(1) );

	_outputFunc = EmpytOutputFun;
	_context	= NULL;
	_event_listener = NULL;
	_timer->async_wait(boost::bind(&NetAsioBase::_CalSendRecvBytes,this ));
}
NetAsioBase::~NetAsioBase()
{
	_io_serveice_alloc_count --;
	if( _io_serveice_alloc_count == 0 )
	{
		delete _io_service;
		_io_service = NULL;
	}

	delete _timer;
}
bool	NetAsioBase::Host		( UInt32 ip , UInt16 port, CEventObj* event )
{
	if( _acceptor != NULL )
		return false;

	tcp::endpoint end_point( boost::asio::ip::address_v4( ip ), port);
	_acceptor = acceptor_pointer( new tcp::acceptor( *_io_service , end_point ) );
	_event_listener = event;
	Start_Accept();

	return true;
}

void	NetAsioBase::Handle_Accept( MyTcpConnection::pointer new_connection , const boost::system::error_code& error , bool ishost)
{
	if (!error)
	{
		int net_id = 0;
		if( _nouse_netid.size() == 0 )
		{
			net_id = (int)_connects.size();
			_connects.push_back( new_connection );
		}
		else
		{
			int net_id = _nouse_netid.back();
			_nouse_netid.pop_back();
			_connects[ net_id ] = new_connection;
		}
		new_connection->Start( net_id );
		if( ishost )
			Start_Accept();
	}
	else
	{
		EventListener()->OnConnectFailed( -1 , error.value() );
		OutputDebugStringA( error.message().c_str() );
		_outputFunc( 5, error.message().c_str() );
	}
}
void	NetAsioBase::Start_Accept()
{
	MyTcpConnection::pointer new_connection =
		MyTcpConnection::pointer( new MyTcpConnection( *_io_service , this ) );

	_acceptor->async_accept(new_connection->Socket(),
		boost::bind(&NetAsioBase::Handle_Accept, this, new_connection,
		boost::asio::placeholders::error,true));
}

bool	NetAsioBase::Connect	( UInt32 ip , UInt16 port, CEventObj* event )
{
	tcp::endpoint end_point( boost::asio::ip::address_v4( ip ) , port );
	_event_listener = event;

	MyTcpConnection::pointer new_connection =
		MyTcpConnection::pointer( new MyTcpConnection( *_io_service , this ) );


	new_connection->Socket().async_connect( end_point 
		, boost::bind(&NetAsioBase::Handle_Accept, this, new_connection
		, boost::asio::placeholders::error,false) );

	return true;
}
void	NetAsioBase::Send		( UInt32 net_id , UInt32 size , void* data )
{
	if( _connects.size() <= (unsigned)net_id )
		return;
	MyTcpConnection::pointer& connection = _connects[ net_id ];
	if( connection == NULL )
		return;
	_unsend_set.insert( connection );

	/*
	static char Value = 0;
	char* buff = new char[ size +4];
	memcpy( buff , data , size );
	buff[size] = 'c';
	buff[size+1] = 'c';
	buff[size+2] = 'c';
	buff[size+3] = 'c';

	PacketHeader	Header;

	Header.Size			= size + 4;
	Header.SystemID		= Value++;
	Header.CheckSum		= GetCheckSum( size+4, buff );

	connection->Send( sizeof(PacketHeader) ,		&Header );		
	connection->Send( size+4 , buff );
	
	delete buff;
*/

	// Packet Header 4, size, 1, system packetID, 1 checksum
	PacketHeader	Header;

	Header.Size			= size;
	Header.SystemID		= 0;
	Header.CheckSum		= GetCheckSum( size, data );

	connection->Send( sizeof(PacketHeader) ,		&Header );		
	connection->Send( size , data );

	_sock_send_rev_info_now.SendSize( size + sizeof(PacketHeader) );

}
void	NetAsioBase::Flush		( )
{
	_io_service->poll();


	for( set< MyTcpConnection::pointer >::iterator Iter = _unsend_set.begin()
		; Iter != _unsend_set.end() ; Iter++ )
	{
		(*Iter)->SendFlush();
	}
	_unsend_set.clear();

}
void	NetAsioBase::Close		( UInt32 net_id )
{
	if( _connects.size() <= (unsigned)net_id )
		return;
	MyTcpConnection::pointer& connection = _connects[ net_id ];
	if( connection == NULL )
		return;
	connection->Socket().shutdown( boost::asio::socket_base::shutdown_send );
	_connects[ net_id ].reset( );

	EventListener()->OnDisconnect( net_id );
}
bool	NetAsioBase::Shutdown	( )
{
	for( unsigned i = 0 ; i < _connects.size() ; i++ )
	{
		MyTcpConnection::pointer& connection = _connects[ i ];
		if( connection == NULL )
			continue;
		connection->Socket().shutdown( boost::asio::socket_base::shutdown_send );
	}
	_connects.clear();
	return false;
}

CEventObj*	NetAsioBase::EventListener()
{
	return _event_listener;
}

void NetAsioBase::SendWithBuff		( UInt32 net_id , UInt32 size1 , void* data1 , UInt32 size2 , void* data2 )
{
	if( _connects.size() <= (unsigned)net_id )
		return;
	MyTcpConnection::pointer& connection = _connects[ net_id ];
	if( connection == NULL )
		return;

	_unsend_set.insert( connection );
	int size = size1 + size2;

	PacketHeader	Header;

	Header.Size			= size;
	Header.SystemID		= 0;
	Header.CheckSum		= GetCheckSum( size1, data1 ) + GetCheckSum( size2, data2 );


	connection->Send( sizeof(Header) , &Header );
	connection->Send( size1 , data1 );
	connection->Send( size2 , data2 );

	_sock_send_rev_info_now.SendSize( size + sizeof(Header) );
}
void NetAsioBase::SendToAll			( UInt32 size , void* data )
{
	for( unsigned i = 0 ; i < _connects.size() ; i++ )	
	{
		MyTcpConnection::pointer& connection = _connects[ i ];
		if( connection == NULL )
			continue;
		_unsend_set.insert( connection );

		PacketHeader	Header;

		Header.Size			= size;
		Header.SystemID		= 0;
		Header.CheckSum		= GetCheckSum( size, data ) ;

		connection->Send( sizeof(Header) , &Header );
		connection->Send( size , data );
		_sock_send_rev_info_now.SendSize( size + sizeof(Header) );
	}
}
void NetAsioBase::SendToAllWithBuff	( UInt32 size1 , void* data1 , UInt32 size2 , void* data2 )
{

	int size = size1 + size2;
	PacketHeader	Header;

	Header.Size			= size;
	Header.SystemID		= 0;
	Header.CheckSum		= GetCheckSum( size1, data1 ) + GetCheckSum( size2, data2 );


	for( unsigned i = 0 ; i < _connects.size() ; i++ )	
	{
		MyTcpConnection::pointer& connection = _connects[ i ];
		if( connection == NULL )
			continue;
		_unsend_set.insert( connection );

		connection->Send( sizeof(Header) , &Header );
		connection->Send( size1 , data1 );
		connection->Send( size2 , data2 );
		_sock_send_rev_info_now.SendSize( size + sizeof(Header) );
	}
}

bool	NetAsioBase::GetConnectInfo		( UInt32 net_id , UInt32* out_ip, UInt16* out_port )
{
	if( _connects.size() <= (unsigned)net_id )
		return false;
	MyTcpConnection::pointer& connection = _connects[ net_id ];
	if( connection == NULL )
		return false;

	if( out_port != NULL )
		*out_port = connection->Socket().remote_endpoint().port();
	if( out_ip != NULL )
		*out_ip = connection->Socket().remote_endpoint().address().to_v4().to_ulong();

	return true;
}
void	NetAsioBase::_CalSendRecvBytes	( )
{
	/*
	printf( "\nsend=(%d/%d) rev=(%d/%d)" 
				,_sock_send_rev_info_now.send_bytes
				,_sock_send_rev_info_now.send_packets
				,_sock_send_rev_info_now.rev_bytes
				,_sock_send_rev_info_now.rev_packets );
*/

//	_sock_send_rev_info_list.push_front( _sock_send_rev_info_now );
//	if( _sock_send_rev_info_list.size() > 60*60 )
//		_sock_send_rev_info_list.pop_front();
	_sock_send_rev_info_now.Init();

	_timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(1));
	_timer->async_wait(boost::bind(&NetAsioBase::_CalSendRecvBytes,this ));

}



unsigned char NetAsioBase::GetCheckSum ( UInt32 size, void* pData )
{
	char	CheckSum	= 0;
	char*	ptr			= (char*)pData;

	for( int i=0; i<size; i++ )
	{
		CheckSum += ptr[i];
	}

	return CheckSum;
}

}// namespace MyAsio