// OutputMsgClass.cpp: implementation of the OutputMsgClass class.
//
//////////////////////////////////////////////////////////////////////

#include "BOutputMsgClass.h"
#include <time.h>
#include <direct.h>
#include <windows.h>

#define		OutputField		"LogFile"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//===========================================================================================
BOutputMsgClass::BOutputMsgClass()
{
	//初始化設定
	_FileName[0]	= 0;
	_File			= NULL;
	_OutputLevel	= 0;
	strcpy(_FieldName,OutputField);
}
//===========================================================================================
BOutputMsgClass::~BOutputMsgClass()
{
	_Close();
}
//===========================================================================================
//設定輸出檔案名稱
void BOutputMsgClass::FileName(char *file)
{
	strncpy(_FileName,file,sizeof(_FileName));
}
//===========================================================================================
//讀取輸出檔案名稱
char* BOutputMsgClass::FileName()
{
	return _FileName;
}
//===========================================================================================
//顯示在螢幕上
bool  BOutputMsgClass::Print(int LV,const char *format,...)
{
	if(LV < _OutputLevel)
		return false;

	try
	{
		va_list marker =(char*)&format + sizeof(format);
		vsprintf(_Buf,format,marker);
		printf("\n");
		puts(_Buf);
	}

	catch(...)
	{
		return false;
	}

	return true;
}
//===========================================================================================
//設定輸出等級(設定多少級以上的才輸出)
void  BOutputMsgClass::OutputLV	(int LV)
{
	_OutputLevel = LV;
}
//===========================================================================================
//開啟寫出的檔案
bool BOutputMsgClass::_Open		(void)								
{
	char FileName[256];

	if(_File != NULL)
		return false;

	MakePath();
	sprintf(FileName,"%s/%s",_TimePath,_FileName);

	_File = fopen( FileName, "a+") ;
	if(_File == NULL)
		return false;

	//五分鐘關閉一次檔案
	_NextClostTime = clock() + 5*60*1000;

	return true;
}
//===========================================================================================
//關閉檔案
bool BOutputMsgClass::_Close		(void)
{
	if(_File == NULL)
		return false;

	fclose(_File);
	_File = NULL;

	return true;
}

//===========================================================================================
//寫檔案
bool BOutputMsgClass::Write		(int Lv,const char *format,...)	
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
		vfprintf(_File,format,marker);
		
		int clocktime = clock();
		if(_NextClostTime < clock())
			_Close();
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
void BOutputMsgClass::Flush		(void)
{
	_Close();
}
//===========================================================================================
//設定目錄
void BOutputMsgClass::MakePath	(void)
{
	char Year[256];

	time_t Now;
    time( &Now );
	struct tm *gmt;
    gmt = localtime( &Now );

	sprintf(Year,"%s/%04d",_FieldName,gmt->tm_year+1900);

	sprintf(_TimePath,"%s/%04d/%02d-%02d"
					,_FieldName
					,gmt->tm_year+1900
					,gmt->tm_mon+1
					,gmt->tm_mday);

	_mkdir(_FieldName);
	_mkdir(Year);
	_mkdir(_TimePath);

}
//===========================================================================================
//設定輸出目錄
void  BOutputMsgClass::FiledName(char* Path)
{
	strncpy(_FieldName,Path,sizeof(_FieldName));
}
//===========================================================================================

//===========================================================================================
//===========================================================================================