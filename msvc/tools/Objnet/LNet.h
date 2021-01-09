#ifndef _L_NET_H_
#define _L_NET_H_

#pragma pack( push, _l_net_h_)
#pragma pack(8)

#ifndef LSAPI
#define LSAPI __stdcall
#endif

 /*
#ifndef UINT32
#define UINT32 unsigned int
#endif
*/

#define LNETID	UINT32
#define LNETID_SYSMSG	(0xfffffffe)			
#include <winsock.h>

typedef void (LSAPI *LNET_EnumIDCallBack)(LNETID u32ID , void* vpContext);
typedef void (LSAPI *LNET_EnumPlayersCallBack)(LNETID u32ID, sockaddr_in* pAddr, void* vpContext);

enum LNETSYSMSG {
LNETSYS_NOTHING					=0,
LNETSYS_NEWCONNECTION			=657,
LNETSYS_DESTROYCONNECTION		=843,
LNETSYS_PEERSHUTDOWNCONNECTION	=323
};

struct LNET_PKT_DESTINATION {
	LNETID u32ID;
	int nPriority;
};

struct LNETMSG_GENERAL {
	UINT32	u32Msg;
};
struct LNETMSG_SYSMSG {
	LNETSYSMSG	u32Msg;
	LNETID		u32UserID;
};



/*============================================================================================
	Name
		void LNET_EnumMessage_CallBack(
			UINT32	u32IDOrContext,
			int		nSize,
			LNETMSG_GENERAL* pMsgData,
			void*	pContext 
		)

	Description
		Application-defined callback function The application must implement this function 
		and pass a pointer to it in IJoyXXXX::RegisterEnumMessageCallback()

	Parameters

		u32IDOrContext
				u32LNETID or u32UserContext if you bind(u32LNETID, u32UserContext);
		nSize 
				Size of message.
		pMsgData
				Pointer to the message data.
		pContext
				Application-defined context that specify in RegisterEnumMessageCallback().

	Remark
		When u32IDOrContext == LNETID_SYSMSG ( that's mean you cannot use this value as a 
		context ), the application should cast pMsgData to LNETMSG_SYSMSG and check the u32Msg
		member to see what type of system message it is before processing it. 

============================================================================================*/
typedef  void (LSAPI *LNET_EnumMessage_CallBack)( UINT32 u32IDOrContext, int nSize, LNETMSG_GENERAL* pMsgData, void* pContext ) throw();

typedef void (LSAPI *SM_EnumLNETIDCallBack)(LNETID sm_id , void* pContext);
typedef unsigned int HBUFFER;

class INetEventListener {
public:
	// return false to close connection, bcz this function shouldn't be called.
	// 若你要留下該 packet ，請 AddRef();
	virtual bool LSAPI OnPacket( LNETID id, HBUFFER hIncomingData ) = 0;

	virtual void LSAPI OnConnectFailed( int ConnectID ) = 0;
	virtual void LSAPI OnConnected( LNETID id ) = 0;
	virtual void LSAPI OnPeerShutdown( LNETID id ) = 0;
	virtual void LSAPI OnDisconnected( LNETID id ) = 0;
};

// for incoming connection only, connect others not counted
class INewConnectionListener {
public:
	virtual INetEventListener* LSAPI OnNewConnection( LNETID ) = 0;
};

#pragma pack( pop, _l_net_h_ )
#endif /* _L_NET_H_ */
