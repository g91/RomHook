#pragma once
#pragma warning (disable:4949)
#pragma unmanaged
#include <stdio.h>
//定義DEGUG 用資料
#define _G_(x)		{ \
		sprintf(LogFile_C::Buf,"Function %s line %d, file(%s) \n",x , __LINE__, __FILE__ );\
		LogFile_C::PushPrint();\
	}



#define _LogFile_MaxStrLen_		 50
#define _LogFile_InfoBufferSize_ 200

namespace LogFile_C  
{  
	void Init();
	void PushPrint();
	void Pop();
	void SaveLogFile(char* FileName,char* Note= NULL);
	
};

#pragma managed

