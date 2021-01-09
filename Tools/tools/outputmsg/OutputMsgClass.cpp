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
	//��l�Ƴ]�w
	_FileName[0]	= 0;
	_File			= NULL;
	_OutputLevel	= 0;
}
//===========================================================================================
OutputMsgClass::~OutputMsgClass()
{
	
}
//===========================================================================================
//�]�w��X�ɮצW��
void OutputMsgClass::FileName(char *file)
{
	strncpy(_FileName,file,sizeof(_FileName));
}
//===========================================================================================
//Ū����X�ɮצW��
char* OutputMsgClass::FileName()
{
	return _FileName;
}
//===========================================================================================
//��ܦb�ù��W
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
//�]�w��X����(�]�w�h�֯ťH�W���~��X)
void  OutputMsgClass::OutputLV	(int LV)
{
	_OutputLevel = LV;
}
//===========================================================================================
//�}�Ҽg�X���ɮ�
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
//�����ɮ�
bool OutputMsgClass::_Close		(void)
{
	if(_File == NULL)
		return false;

	fclose(_File);

	return true;
}

//===========================================================================================
//�g�ɮ�
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
//�j��g�J�ɮ�
void OutputMsgClass::Flush		(void)
{
	if(_File != NULL)
		fflush(_File);
}
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================