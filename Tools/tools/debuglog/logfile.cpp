// LogFile.cpp: implementation of the LogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "LogFile.h"
#include <time.h>
#include <stdio.h>
#include <memory.h>
#include <fstream>

#pragma warning (disable:4949)
#pragma unmanaged

using namespace std;
using namespace LogFile_C;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//開始時間
char _BeginTime[_LogFile_InfoBufferSize_];	

//執行訊息
char _Info[_LogFile_MaxStrLen_][_LogFile_InfoBufferSize_];

//執行位置
int  _Pos;

//共用Buffer
char Buf[_LogFile_InfoBufferSize_];



void Init()
{
	

	time_t Now;
    time( &Now );
	struct tm *gmt;
    gmt = localtime( &Now );
    sprintf(_BeginTime,"Start Time: %s", asctime( gmt ) );

	_Pos = 0;
	memset(&_Info,0,sizeof(_Info));
}

void PushPrint()
{
	if(_Pos >= _LogFile_MaxStrLen_)
		_Pos = 0;

	memcpy(&_Info[_Pos],&Buf,sizeof(Buf));
	_Pos ++;
	
}

void SaveLogFile(char* FileName,char* Note)
{
	ofstream file;
	file.open(FileName,ios::out|ios::ate);

	if(!file.is_open())
		return;
	
	file << "************************************************************\n" ;
	file << _BeginTime ;
	if(Note != NULL)
		file << Note <<'\n' ;
	file << "************************************************************\n";
	for(int i=0;i<_LogFile_MaxStrLen_;i++)
	{
		int Temp = (_Pos+i)%_LogFile_MaxStrLen_;
		if(!_Info[Temp][0])
			continue;
		file << _Info[Temp] ;
	}
	
	file.close();
}

void Pop()
{
	_Info[_Pos][0] = 0;
	_Pos--;
	if(_Pos < 0)
		_Pos = _LogFile_MaxStrLen_ - 1;
}

#pragma managed