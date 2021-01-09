#ifndef __NB_EVENTOBJ_H__
#define __NB_EVENTOBJ_H__

//#include <Windows.h>

class CEventObj
{
public:
	CEventObj(){};
	~CEventObj(){};

	virtual bool		OnRecv			( unsigned long dwNetID, unsigned long dwPackSize, void* pPacketData ) =0;
	//  收到封包
	//		dwID
	//			封包代號
	//		dwPackSize
	//			封包大小
	//		pPacketData
	//			資料, 當放掉此一訊息後, 系統將自己刪除該封包, 絕不可以將此資料指標留下

	virtual void		OnConnectFailed	( unsigned long dwNetID, unsigned long dwFailedCode ) =0;
	//  連線失敗
	//		dwFailedCode
	//			失敗代碼

	virtual void		OnConnect		( unsigned long dwNetID ) =0;
	//  連線成功
	//		dwNetID			
	//			本身為Client, 成功與目標建立連線, 此時 NetID 為當初 Connect 時所傳回的 NetID


	virtual	void		OnDisconnect	( unsigned long dwNetID ) =0;
	// 斷線
	//		dwNetID			斷線對象 NetID

	virtual CEventObj*	OnAccept		( unsigned long dwNetID ) { return 0; };
	// 一個新的連線連入
	//		dwNetID
	//			該連線的 NetID
	//	傳回值
	//			設定該連線新的 Event

};

#endif
