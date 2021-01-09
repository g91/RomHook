// OutputMsgClass.h: interface for the OutputMsgClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_)
#define AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_
//===========================================================================================
//	基本Class OutputMsgClass 
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
//===========================================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
#include <stdio.h>
#include "IOutputMsg.h"

class OutputMsgClass: public IOutputMsg
{
	FILE*	_File;
	char    _FileName[512];
	char	_Buf[2048];									//資料暫存區
	int		_OutputLevel;								//輸出等級

	bool _Open		(void);								//開啟要寫出的檔案
	bool _Close		(void);								//關閉檔案

public:
	OutputMsgClass();
	virtual ~OutputMsgClass();

	void  FileName	(char *file);						//設定輸出檔案名稱
	char* FileName	(void);								//讀取輸出檔案名稱

	void  OutputLV	(int LV);							//設定輸出等級(設定多少級以上的才輸出)

	bool Print		(int Lv,const char *format,...);	//顯示在螢幕上
	bool Write		(int Lv,const char *format,...);	//寫檔案
	void Flush		(void);								//強制寫入檔案

};

#endif // !defined(AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_)
