
#pragma once

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <deque>
#include <Windows.h>
#include "NamedPipe.h"


// #include <boost/thread/mutex.hpp>
// #include <boost/thread.hpp>

//class CNamedPipeEx;

// pipe packet struct
struct TPipePacket
{
	TPipePacket()
	{
		memset( this, 0, sizeof( *this ) );
	}

	byte* pData;
	unsigned long uSize;

	void Destroy()
	{
		delete [] pData;
	}

};

enum IPCStatus
{
	EM_IPC_CONNECTED,
	EM_IPC_DISCONNECTED,
	EM_IPC_CONNECTIING,
	EM_IPC_INITIALIZE,
};


class CInterProcCommBase
{

	typedef boost::function< void( int iLevel, const char* szstr ) > PFUNC_MSG_OUTPUT_CALLBACK;
	typedef boost::function< void( byte* pData, unsigned long uPGSize ) > PFUNC_RECV_CALLBACK;
	typedef boost::function< void( int status ) > PFUNC_CONNECT_STATUS_CALLBACK;

public:

	enum LogSeverity_t
	{
		EM_LOG_LEVEL_DEBUG,
		EM_LOG_LEVEL_INFO,
		EM_LOG_LEVEL_WARNNING,
		EM_LOG_LEVEL_CRITICAL,
		EM_LOG_LEVEL_FATAL,
		EM_LOG_LEVEL_NONE,
	};

protected:

	PFUNC_MSG_OUTPUT_CALLBACK			m_pMsgOutCB;

	PFUNC_RECV_CALLBACK					m_pRecvCB;

	PFUNC_CONNECT_STATUS_CALLBACK		m_pStatusChageCB;

	CIPCCritiaclSection					m_msgCs;

	std::deque< TPipePacket >			m_deqRecvData;
	std::deque< TPipePacket >			m_deqSendData;

	CNamedPipeEx*						m_pNamedPipe;
	byte*								m_pTempData;

	unsigned long						m_uTempDataSize;

	CIPCCritiaclSection					m_send_cs;
	CIPCCritiaclSection					m_recv_cs;
	CIPCCritiaclSection					m_proc_cs;

	LARGE_INTEGER						m_liFrequency;

	int									m_iIPCStatus;

	unsigned long						m_uBufSize;
	byte*								m_pBuffer;

	HANDLE								m_waitEvent;

	HANDLE								m_waitTimeEvent;

// 	boost::mutex						m_threadCs;
// 	boost::condition_variable			m_waitEvent;


protected:

	virtual void						MsgOut( int iLevel, const char* szStr, ... );

	// recv data process
	virtual bool						RecvDataProc();

	// send data process
	virtual bool						SendDataProc();

	// the client was connectd
	bool								IsConnected();

	// get the tick now
	double								GetCurTickCount();

	void								ChangeIPCStatus( int iStatus );

	virtual void						Flush();


public:
	CInterProcCommBase();
	virtual ~CInterProcCommBase();

	virtual bool						Init( const char* szPipeName ) = 0;

	// set message output callback
	void								SetMsgOutCallback( PFUNC_MSG_OUTPUT_CALLBACK pFunc );

	// set recv data callback
	void								SetRecvCallback( PFUNC_RECV_CALLBACK pFunc );

	// set the callback if connect status
	void								SetStatusChangeCallback( PFUNC_CONNECT_STATUS_CALLBACK pFunc );

	// send data
	virtual void						Send( void* pData, unsigned long uPGSize );

	// get the size of send queue
	unsigned long						GetSendQueueSize();

	// get the size of recv queue
	unsigned long						GetRecvQeueuSize();

	// get a temporary buffer
	void*								GetBuffer( unsigned long size );

	void								ActThread();

	// need to notify thread work
	bool								HaveHandleData();

	// sleep
	void								GraceSleep();

};


