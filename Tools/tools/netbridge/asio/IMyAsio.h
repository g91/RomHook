#pragma once

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "../NetBridge_EventObj.h"

namespace MyAsio{
#define UInt16 unsigned short
#define UInt32 unsigned

#define OutputCBFun         boost::function<void ( int, const char* ) >


/*
class INetAsioEvent
{
public:
	virtual bool	OnRecv			( UInt32 net_id, UInt32 size , void* data ){ return false; }
	virtual void	OnConnectFailed	( UInt32 net_id, UInt32 err_code ){};
	virtual void	OnConnect		( UInt32 net_id ){}
	virtual	void	OnDisconnect	( UInt32 net_id ){}
};
*/






class INetAsio
{

public:
	virtual bool	Host				( UInt32 ip , UInt16 port, CEventObj* event ) = 0;
	virtual bool	Connect				( UInt32 ip , UInt16 port, CEventObj* event ) = 0;

	virtual void	Send				( UInt32 net_id , UInt32 size, void* data ) = 0;
	virtual void	SendWithBuff		( UInt32 net_id , UInt32 size1 , void* data1 , UInt32 size2 , void* data2 ) = 0;

	virtual void	SendToAll			( UInt32 size , void* data ) = 0;
	virtual void	SendToAllWithBuff	( UInt32 size1 , void* data1 , UInt32 size2 , void* data2 ) = 0;

	virtual void	Flush				( ) = 0;
	virtual void	Close				( UInt32 net_id ) = 0;
	virtual	bool	Shutdown			( ) = 0;
	virtual bool	GetConnectInfo		( UInt32 net_id , UInt32* pout_ip, UInt16 *pout_port ) = 0;

	//用來辨識網路物件的用途
	virtual void*	GetContext			( ) = 0;
	virtual void	SetContext			( void* context ) = 0;
	//設定訊息輸出
	virtual void	SetOutPutCB			( OutputCBFun pFun ) = 0;


};


INetAsio*	CreateMyAsio		( );
void		DeleteNetBridge		( INetAsio* net_asio );
unsigned	ConvertIP			( const char* ipstr );
}// namespace MyAsio
