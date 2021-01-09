// IOutputMsg.h: interface for the IOutputMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_)
#define AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_

//-----------------------------------------------------------------------------------------
//	基本Log 輸出的Interface 
//*目的 
//		為了之後訊息Log輸出方便，寫一個基本的物件處理 
// 
//*需求 
//  	管理Log輸出檔案，螢幕，與是否輸出 
//
//*重複使用 
//		未來有任何需要Log 輸出的都要使用此物件，或繼承此物件 
//
//*主要能 
//
//輸出形式 (type)<螢幕輸出，檔案輸出，螢幕與檔案輸出，一次固定量寫出> 
//固定量寫出的Buf大小  (Size) 
//開檔 (filename) 
//關檔 () 
//強迫寫檔 () 設定多久強制儲存 
//訊息輸出 (內容)  
//
//-----------------------------------------------------------------------------------------

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IOutputMsg  
{
public:
	virtual ~IOutputMsg(){};

	virtual void  FileName	(char *file) = 0;					//設定輸出檔案名稱
	virtual char* FileName	(void)		 = 0;					//讀取輸出檔案名稱

	virtual void  OutputLV	(int LV) = 0;						//設定輸出等級

	virtual bool  Print		(int,const char *format,...) = 0;	//顯示在螢幕上
	virtual bool  Write		(int,const char *format,...) = 0;	//寫檔案
	virtual void  Flush		(void) = 0;							//強制寫入檔案

};

#endif // !defined(AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_)
