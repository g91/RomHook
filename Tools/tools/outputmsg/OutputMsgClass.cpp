// OutputMsgClass.cpp: implementation of the OutputMsgClass class.
//
//////////////////////////////////////////////////////////////////////

#include "OutputMsgClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//===========================================================================================
OutputMsgClass::OutputMsgClass()
{
	//初始化設定
	_FileName[0]	= 0;
	_File			= NULL;
	_OutputLevel	= 0;
}
//===========================================================================================
OutputMsgClass::~OutputMsgClass()
{
	
}
//===========================================================================================
//設定輸出檔案名稱
void OutputMsgClass::FileName(char *file)
{
	strncpy(_FileName,file,sizeof(_FileName));
}
//===========================================================================================
//讀取輸出檔案名稱
char* OutputMsgClass::FileName()
{
	return _FileName;
}
//===========================================================================================
//顯示在螢幕上
bool  OutputMsgClass::Print(int LV,const char *format,...)
{
	if(LV < _OutputLevel)
		return false;

	try
	{
		va_list marker =(char*)&format + sizeof(format);
		vsprintf(_Buf,format,marker);
		printf("\n");
		printf(_Buf);
	}

	catch(...)
	{
		return false;
	}

	return true;
}
//===========================================================================================
//設定輸出等級(設定多少級以上的才輸出)
void  OutputMsgClass::OutputLV	(int LV)
{
	_OutputLevel = LV;
}
//===========================================================================================
//開啟寫出的檔案
bool OutputMsgClass::_Open		(void)								
{
	if(_File != NULL)
		return false;

	_File = fopen( _FileName, "a+") ;

	if(_File == NULL)
		return false;

	return true;
}
//===========================================================================================
//關閉檔案
bool OutputMsgClass::_Close		(void)
{
	if(_File == NULL)
		return false;

	fclose(_File);

	return true;
}

//===========================================================================================
//寫檔案
bool OutputMsgClass::Write		(int Lv,const char *format,...)	
{
	if(Lv < _OutputLevel)
		return false;

	if(_File == NULL)
	{
		if(_Open() == false )
			return false;
	}

	try
	{
		va_list marker =(char*)&format + sizeof(format);
		vsprintf(_Buf,format,marker);
		fprintf(_File,_Buf);
	}

	catch(...)
	{
		_Close();
		return false;
	}

	return true;
}
//===========================================================================================
//強制寫入檔案
void OutputMsgClass::Flush		(void)
{
	if(_File != NULL)
		fflush(_File);
}
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================