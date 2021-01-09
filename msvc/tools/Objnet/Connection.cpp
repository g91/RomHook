#pragma warning (disable:4949)

#include "Connection.h" 
#include <winsock.h>
#include <windows.h>
#include <stdio.h>
#include <algorithm>
#pragma unmanaged
//====================================================================================================
unsigned char Connection::_KeyTable[16] = {	 0x3f,0x12,0x56,0x44,0x9a,0xbb,0x33,0x44
											,0x3f,0x12,0x56,0x44,0x9a,0xbb,0x33,0x44};
//====================================================================================================
Connection::Connection()
{
	_Key = 0;
	_ClientFlag = false;
	_NeedCheckConnect = false;
	_NextCheckConnect = -1;
	_CheckConnectTimes = 0;
	_DataEncodeFlag = false;   


	m_u16WrPacketIndex = 0;

	m_hWrBuffer = INVALID_BUFFERHANDLE;
	m_hRdBuffer = INVALID_BUFFERHANDLE;

	m_u16ReadSize = m_u16ReadIndex = 0;
	m_status = NOT_CREATED;
}

void Connection::Create( SOCKET sock, LNETID id )
{
	ASSERT( !IsInvalidSocket( sock ) );
//	TRACE1("use socket %d\n", sock);

	m_sock = sock;

	m_u16WrPacketIndex = 0;

	m_hWrBuffer = INVALID_BUFFERHANDLE;
	m_hRdBuffer = INVALID_BUFFERHANDLE;

	m_u16ReadSize = m_u16ReadIndex = 0;
	m_u32TotalRecvSize = 0;
	
	m_status = ESTABLISHED;
	m_id = id;
}


void Connection::CleanUp()
{
	m_status = NOT_CREATED;
	while( !m_WrPacketList.IsEmpty() )
	{
		HBUFFER h;
		m_WrPacketList.Read(h);
		g_BufferMan.Release( h );
		//m_WrPacketList.pop_front();
	}

	if( m_hRdBuffer != INVALID_BUFFERHANDLE )
		g_BufferMan.Release( m_hRdBuffer );

	if( !IsInvalidSocket( m_sock ) )
	{
		TRACE1("close socket %d\n", m_sock);
		closesocket( m_sock );
		m_sock = INVALID_SOCKET;
	}
}
Connection::~Connection() {
	CleanUp();
		
//	if(_Key != 0)
//		_Key = 0xffff;

//	_LastCheckConnect = -1;
	
}

//====================================================================================================
//#include "LMemStream.h"
bool Connection::ProcessDataOut(void)
{
	int nLen;
	int nSize;
	void* vpData;

	// 表示 buffer 裡的資料都已經輸出，現將 PacketList 裡的 packet輸出
	while(true) {
		if( m_hWrBuffer == INVALID_BUFFERHANDLE ) 
		{	// 沒有上次為寫完的資料
			if( m_WrPacketList.IsEmpty() ) // 什麼資料都沒有
				return true;
			m_WrPacketList.Read( m_hWrBuffer );
			if( m_hWrBuffer == INVALID_BUFFERHANDLE ) { // shutdown 中
				shutdown( m_sock, 1 );
				m_status = SHUTDOWN_SEND_PIPE;
				return true;
			}
			//g_BufferMan.GetPureBuffer( m_hWrBuffer, nSize, vpData );
			m_u16WrPacketIndex = 0;
		}
		// 取得上一次沒寫完的 packet
		g_BufferMan.GetPureBuffer( m_hWrBuffer, nSize, vpData );

		ASSERT( nSize > 0 && vpData != NULL );

		//編碼如果Key還未設好則不送資料
		if(!_DataEncodeFlag)
		{
			if(!Encode(nSize,(char*)vpData+sizeof(WORD)))
				return true;
			_DataEncodeFlag = true;
		}


		nLen = send( m_sock, (char *)vpData + m_u16WrPacketIndex , nSize + 2 - m_u16WrPacketIndex, 0 );

		if( nLen < 0 )
			if( WouldSocketBlocked() )
			{
				//Decode(nSize,(char*)vpData+sizeof(WORD));		
				return true;
			}
			else {
				//m_sock = INVALID_SOCKET;
				m_status = SHUTDOWNED;
//				m_pListener->OnDisconnected( m_id );
				return false;
				// 發生錯誤，結束連線
			}

		m_u16WrPacketIndex += nLen;
		if( nLen == 0 )		// buffer 已滿，但此 packet 並無寫入，
		{
			
			return true;	// 因為若對方 close connection 會在 exc 的 sock_set 處理階段就已除去
		}
		else /*nLen > 0 */if( m_u16WrPacketIndex < nSize )
		{

			// 如果系統 buffer不足，保留該 packet	
			return true;
		}
		else {// m_u16WrPacketIndex >= size 傳輸完成
			g_BufferMan.Release( m_hWrBuffer );
			m_hWrBuffer = INVALID_BUFFERHANDLE;	// 表示現在是新的資料
			_DataEncodeFlag = false;
		}
	}
	//m_WrMutex.Unlock();
}
//====================================================================================================

bool Connection::ProcessDataIn(void)
{
while(true){
	int nLen;
	// 表示這是一個新的 packet
//	if( m_vpRdBuffer == NULL )
	if( m_hRdBuffer == INVALID_BUFFERHANDLE )
	{
		// 讀取 packet 長度
		nLen = recv( m_sock, ((char *)&m_u16ReadSize) + m_u16ReadIndex , 2 - m_u16ReadIndex, 0 );
		if( nLen <= 0 )
			if( WouldSocketBlocked() && nLen != 0 )
				return true;//NO_DATA_LEFT;
			else
			{
				m_status = SHUTDOWNED;
//				m_pListener->OnDisconnected( m_id );
				return false;//RECV_ERROR;
			}

		m_u16ReadIndex += nLen;
		// 當 size 已讀入了，起始一個新的 packet
		if( m_u16ReadIndex == 2 )
		{
        /*
			if( m_u16ReadSize > CONNECTION_MAX_READ_PACKET_SIZE )
			{
				m_status = SHUTDOWNED;
				m_pListener->OnDisconnected(m_id);
				return false;//RECV_ERROR;
			}
            */
			m_hRdBuffer = g_BufferMan.CreateBuffer( m_u16ReadSize );
			m_u16ReadIndex = 0;
		} else return true;//NO_DATA_LEFT;
	}
	int nSize;
	void* vpData;
	short * pSize;
	//unsigned short	*KeyInfo;
	g_BufferMan.GetBuffer( m_hRdBuffer, nSize, vpData );
	pSize = (short*)vpData - 1;
	//TRACE3("GetBuffer: %d, %d, %x\n", m_hRdBuffer, nSize, vpData );

	int nDateLeft = m_u16ReadSize - m_u16ReadIndex;
	
	if( nDateLeft == 0 ) {
		m_status = PEER_SHUTDOWN_SEND;
		return true;
	}

	if( nDateLeft < 0 ) {
		m_status = SHUTDOWNED;
//		m_pListener->OnDisconnected( m_id );
		return false; // net data error.
	}

	nLen = recv( m_sock,
				 (char*)vpData + m_u16ReadIndex, //從上次剩下的資料開始讀入
				 nDateLeft,
				 0 );
//	ASSERT( m_u16ReadIndex != 0 );

	if( nLen > 0 ) {
		m_u16ReadIndex += nLen;
		// RECV_COMPLETED
		if( m_u16ReadIndex == m_u16ReadSize )
		{
			m_u32TotalRecvSize += m_u16ReadSize;
			//解碼
			//檢查是否為系統封包
			CheckPacket *PG = (CheckPacket *)vpData;
			
			//if(*(short*)vpData != 0xffff)
			if(PG->Command != 0xffff)
			{
				if( !Decode(nSize,(char*)vpData ) )
				{
					//client 送的資料有問題
					m_status = SHUTDOWNED;
//					m_pListener->OnDisconnected( m_id );
				}
				else
				{
					//if(_Key != 0)
					{
						(*pSize)--; 
						nSize -- ;
					}
					if(nSize > 0)
						this->m_pListener->OnPacket( m_id, m_hRdBuffer );
				}
			}
			else
			{	
//				if(_Key != 0)
					nSize -- ;

				//檢查是否為送Key
				if(_Key == 0xffff)
				{
					if(		PG->Command == 0xffff
						&&	nSize == 4)
					{
						_Key = PG->Type; 
					}
					else
					{
						//client 送的資料有問題
						m_status = SHUTDOWNED;
//						m_pListener->OnDisconnected( m_id );
					}
				}
				else
				{
					switch(PG->Type)
					{
						case _Conn_CheckType_CheckConnect_:
							if(!IS_Client())
								_NextCheckConnect+=5000;							
							break;
						case _Conn_CheckType_NeedCheckConnect_:
							if(IS_Client())
								NeedCheckConnect();
							_NextCheckConnect -= 5000;
							break;
					}
				}
			}

			g_BufferMan.Release( m_hRdBuffer );
			//packet_list.Write( m_hRdBuffer );
//			packet_list.push_back( m_hRdBuffer );
			m_hRdBuffer = INVALID_BUFFERHANDLE;
			m_u16ReadIndex = 0;
			continue;
			//goto BEGIN;
			//return m_status;//NO_DATA_LEFT
		}
	} else {

		if( WouldSocketBlocked() && nLen != 0 )
			return true;//NO_DATA_LEFT
		else
		{	// socket error.
			m_status = SHUTDOWNED;
//			m_pListener->OnDisconnected(m_id);
			return false;//RECV_ERROR or end connection
		}
	}
}
}

//-------------------------------------------------------------------------
//							編碼解碼
//-------------------------------------------------------------------------
//#define Def_CheckSum_Value	69
//編碼
bool Connection::Encode(unsigned short Size,char* Data)
{
	int i;
	if(_Key == 0xffff)
		return false;

	if(*(unsigned short*)Data == 0xffff)
		return true;

	if(_Key == 0)
		return true;

	char CheckSum = char(_Key); 
	for( i=Size-2 ; i>=0;i--)
		CheckSum = CheckSum^Data[i];
	Data[Size-1] = CheckSum;

	//---------------------------------------------------------------
	//編碼
	int TablePos = _Key;
	for( i=0 ; i<Size;i++,TablePos++)
		Data[i] = Data[i] ^ _KeyTable[TablePos&0xf];
	
	//交換碼位置
	std::swap(Data[Size-1],Data[_Key%Size]);

	//---------------------------------------------------------------

	return true;
}
//解碼
bool Connection::Decode(unsigned short Size,char* Data)
{
	int i;

	if(Size <= 1)
		return false;

	if(_Key == 0)
		return true;

	//---------------------------------------------------------------
	//解碼
	//交換碼位置
	std::swap(Data[Size-1],Data[_Key%Size]);

	//編碼
	int TablePos = _Key;
	for( i=0 ; i<Size;i++,TablePos++)
		Data[i] = Data[i] ^ _KeyTable[TablePos&0xf];
	
	//---------------------------------------------------------------

	char CheckSum = char(_Key); 
	for( i=Size-2 ; i>=0;i--)
		CheckSum = CheckSum^Data[i];

	if(Data[Size-1] != CheckSum)
		return false;

	return true;
}

void Connection::SendCheckPack()
{
	//如果不用檢查連線
	if(!_NeedCheckConnect)
		return;
	CheckPacket PG; 
	PG.Type = 0;
	if(IS_Client() )
	{
		if( _NextCheckConnect == -1)
			return;

		//檢查是否要送
		for(;_NextCheckConnect < clock();_NextCheckConnect+=10000)
		{
			SendPkt(sizeof(PG),&PG);
			SendPkt(sizeof(PG),&PG);
		}
	}
	else
	{//如果為Server
		if(abs(_NextCheckConnect - clock()) > 60*1000)
		{
			m_status = SHUTDOWNED;
		}
	}

}
//-------------------------------------------------------------------------
#pragma managed