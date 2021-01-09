#pragma once

#include "IMyAsio.h"
#include "MyAsioDef.h"
#include <vector>
#include <deque>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include "MyAsioBuffer.h"
#include <deque>

using boost::asio::ip::tcp;

using namespace std;

namespace MyAsio{


class NetAsioBase;
//////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<tcp::acceptor>	acceptor_pointer;
//////////////////////////////////////////////////////////////////////////
//�B�z�s�u�����c
class MyTcpConnection
	: public boost::enable_shared_from_this<MyTcpConnection>
{
public:
	
	typedef boost::shared_ptr<MyTcpConnection>	pointer;
protected:
	NetAsioSendBuffer		_send_buff;
	NetAsioBase*			_net_asio;
	tcp::socket				_socket;
	int						_net_id;

	NetAsioRevBuffer		_rev_buff;

	static vector< char* >	_unused_send_buff;		//char[1024]
	bool					_on_send_flag_;

	deque< SendBaseBufferStruct > _send_list;

	int		DebugWriteInThreadCount;

	void			Handle_Write	(const boost::system::error_code& error, size_t bytes_transferred , void* buff );
	void			Handle_Read		(const boost::system::error_code& error, size_t bytes_transferred );
	
	//�u���e���
	void			SendBase(  UInt32 size , void* data );
public:
	MyTcpConnection(boost::asio::io_service& io_service , NetAsioBase* net_asio );

	virtual ~MyTcpConnection();


	tcp::socket&	Socket();

	//�s�u����
	void			Start( UInt32 net_id );
	

	void			Send( UInt32 size , void* data );
	void			SendFlush();
	int				NetID();
};

//////////////////////////////////////////////////////////////////////////

class NetAsioBase : public INetAsio
{
	friend MyTcpConnection;
protected:
	static boost::asio::io_service*		_io_service;
	static int							_io_serveice_alloc_count;
	boost::asio::deadline_timer*		_timer;
	acceptor_pointer					_acceptor;
	CEventObj*							_event_listener;
	
	//�Ҧ�Client�s�u
	vector< MyTcpConnection::pointer >	_connects;
	vector< int	>						_nouse_netid;
	set< MyTcpConnection::pointer >		_unsend_set;

	//�ʥ]���e��T( �O�d�@�p�� )
	deque<SockSendRevInfoStruct>		_sock_send_rev_info_list;
	//�ثe�ʥ]���e���p
	SockSendRevInfoStruct				_sock_send_rev_info_now;

	void*								_context;
	OutputCBFun							_outputFunc;

protected:
	void Handle_Accept(MyTcpConnection::pointer new_connection , const boost::system::error_code& error , bool ishost );
	void Start_Accept();

public:
	NetAsioBase();
	~NetAsioBase();


	virtual bool		Host				( UInt32 ip , UInt16 port, CEventObj* event );
	virtual bool		Connect				( UInt32 ip , UInt16 port, CEventObj* event );

	virtual void		Send				( UInt32 net_id , UInt32 size, void* data );
	virtual void		SendWithBuff		( UInt32 net_id , UInt32 size1 , void* data1 , UInt32 size2 , void* data2 );

	virtual void		SendToAll			( UInt32 size , void* data );
	virtual void		SendToAllWithBuff	( UInt32 size1 , void* data1 , UInt32 size2 , void* data2 );

	virtual void		Flush				( );
	virtual void		Close				( UInt32 net_id );
	virtual	bool		Shutdown			( );
	virtual bool		GetConnectInfo		( UInt32 net_id , UInt32* pout_ip, UInt16* pout_port );

	//�Ψӿ��Ѻ������󪺥γ~
	virtual void*		GetContext			( );
	virtual void		SetContext			( void* context );
	//�]�w�T����X
	virtual void		SetOutPutCB			( OutputCBFun pFun );


	static 	unsigned char	GetCheckSum		( UInt32 size, void* pData );
	
	
protected:
	void				_CalSendRecvBytes	( );

	CEventObj*		EventListener		( );

};


}// namespace MyAsio