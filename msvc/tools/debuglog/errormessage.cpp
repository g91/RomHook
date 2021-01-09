#pragma warning (disable:4949)

#include	<string>
#include	<time.h>
#include    <windows.h>
#include	<direct.h>
#include	"errormessage.h"
#include	"Malloc/MyAlloc.h"
#include	"../SmallObj/SmallObj.h"

#ifndef _CLIENT 
	#include	"ControllerClient/ControllerClient.h"
#endif

#pragma unmanaged
//-------------------------------------------------------------------------------------------------
//PrintClass   Print;
PrintClass*	g_pPrint		= NULL;
PrintClass*	g_pNetStatus	= NULL;

inline MutilThread_CritSect*  g_CritSect_Print( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect; 

	return &g_Thread_CritSect;
}

inline MutilThread_CritSect*  g_CritSect_Netstatus( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect; 

	return &g_Thread_CritSect;
}

//-------------------------------------------------------------------------------------------------
void	Print( int LV , const char* Title , const char* format , ... )
{
	try
	{
		if( g_pPrint == NULL )
			return;
		g_CritSect_Print()->Enter();
		{
			va_list Marker =(char*)&format + sizeof(format);
			g_pPrint->Print( LV , Title , format , Marker );
		}
		g_CritSect_Print()->Leave();
	}
	catch(...)
	{
		printf( "\nPrint Crash");
	}
}

void	PrintNetstatus( int LV , const char* Title , const char* format , ... )
{
	try
	{
		if( g_pNetStatus == NULL )
			return;
		g_CritSect_Netstatus()->Enter();
		{
			va_list Marker =(char*)&format + sizeof(format);
			g_pNetStatus->Print( LV , Title , format , Marker );
		}
		g_CritSect_Netstatus()->Leave();
	}
	catch(...)
	{
		printf( "\nPrint Crash");
	}
}

/*
void	PrintToFile( int LV , const char* Title , const char* Content  )
{
	try
	{
		if( g_pPrint == NULL )
			return;

		g_CritSect_Print()->Enter();
		{			
			g_pPrint->OutputToBuff( LV , Title , Content );
		}
		g_CritSect_Print()->Leave();
	}
	catch(...)
	{
		printf( "\nPrint Crash");
	}
}
*/

void	PrintToFile( int LV , const char* Title , const char* format , ... )
{
	try
	{
		if( g_pPrint == NULL )
			return;
		g_CritSect_Print()->Enter();
		{
			va_list Marker =(char*)&format + sizeof(format);
			g_pPrint->OutputToBuff( LV , Title , format , Marker );
		}
		g_CritSect_Print()->Leave();
	}
	catch(...)
	{
		printf( "\nPrint Crash");
	}
}
void	CreatePrint(  )
{
	if( g_pPrint == NULL )	
		g_pPrint = NEW PrintClass;

	if( g_pNetStatus == NULL )
		g_pNetStatus = NEW PrintClass;
}
void	DestroyPrint( )
{
	if( g_pPrint != NULL )
		delete g_pPrint;

	if( g_pNetStatus != NULL )
		delete g_pNetStatus;

	g_pPrint		= NULL;
	g_pNetStatus	= NULL;
}

//-------------------------------------------------------------------------------------------------
PrintClass::PrintClass()
{
	_LastOutputTime		= TimeStr::Now_Value( )+60;
    _PrintDisplayLV		= 0;
    _OutputFunc			= NULL;
    _OuputLV			= 2;
	_FileOutputLV		= 5;
	_ControllerOuputLV	= 2;
	_OutputField		= "Log";
	_TimeClock			= 0;
	//_OutputFile			;

}
PrintClass::~PrintClass()
{

}
//-------------------------------------------------------------------------------------------------
void PrintClass::Init(  BaseOutputFunction fp  )
{
    _OutputFunc = fp;
}
//-------------------------------------------------------------------------------------------------
void PrintClass::Release( )
{
	OutputBuffToFile( );
}
//-------------------------------------------------------------------------------------------------
void PrintClass::operator() ( int LV , const char* Title ,  const char* Str , ... )
{
    //char	Buf[1024];
    va_list Marker =(char*)&Str + sizeof(Str);
	Print( LV , Title , Str , Marker );
	/*
    vsprintf( Buf , Str , marker );
    if( LV >= _PrintDisplayLV )
    {
        printf( "(%d) " , LV );
        printf( "%s %s\n",Title , Buf );
    }
    if( LV >= _OuputLV && _OutputFunc != NULL )	
    {
        _OutputFunc( LV ,Title , Buf );
    }
	if( LV >= _FileOutputLV )
	{
		OutputToFile( LV , Title, Buf );
		}*/
}
void PrintClass::Print( int LV , const char* Title , const char* Str , va_list Marker )
{
	//////////////////////////////////////////////////////////////////////////
	bool RunningPreCheckOK = false;

	if( LV >= _PrintDisplayLV )
		RunningPreCheckOK = true;
	else if( LV >= _OuputLV && _OutputFunc != NULL )
		RunningPreCheckOK = true;
	else if( LV >= _ControllerOuputLV && _ControllerOutputFunc != NULL )	
		RunningPreCheckOK = true;
	else if( LV >= _FileOutputLV )
		RunningPreCheckOK = true;

	if( RunningPreCheckOK == false )
		return;
	//////////////////////////////////////////////////////////////////////////
	char	Buf[8096];
	int		Zero = 0;
	try
	{

		vsprintf_s( Buf , sizeof(Buf) , Str , Marker );
		if( LV >= _PrintDisplayLV )
		{
			printf( "(%d) " , LV );
			printf( "%s %s\n",Title , Buf );
			fflush(NULL);
		}
		if( LV >= _OuputLV && _OutputFunc != NULL )	
		{
			_OutputFunc( LV ,Title , Buf );
		}
		if( LV >= _ControllerOuputLV && _ControllerOutputFunc != NULL )	
		{
			_ControllerOutputFunc( LV ,Title , Buf );
		}
		if( LV >= _FileOutputLV )
		{
			//OutputToFile( LV , Title, Buf );
			OutputToBuff( LV , Title, Buf );
		}
	}
	catch (...)
	{
		sprintf_s( Buf , sizeof( Buf )  , "(Crash)%s", Title );
		//OutputToFile( LV5 , Buf , Str );
		OutputToBuff( LV5 , Buf , Str );
	}

}
//-------------------------------------------------------------------------------------------------
void PrintClass::_MakePath	(void)
{
//	int TimeClock = 0;

	if( _TimeClock - clock() < 0 )  
	{
		_TimeClock = clock() + 1000 * 60*5;
		char Year[256];
		char TimePath[256];

		time_t Now;
		time( &Now );
		struct tm *gmt;
		gmt = localtime( &Now );

		sprintf(Year,"%s/%04d",_OutputField.c_str() ,gmt->tm_year+1900);

		sprintf( TimePath,"%s/%04d/%02d-%02d"
						,_OutputField.c_str()
						,gmt->tm_year+1900
						,gmt->tm_mon+1
						,gmt->tm_mday);

		_mkdir(_OutputField.c_str() );
		_mkdir(Year);
		_mkdir(TimePath);

		_OutputPath = TimePath;
	}
}
void PrintClass::OutputToFile( int LV , const char* pszTitle, const char* pszMessage )
{
	char szFile[512];
	char szBuff[1024];

	if( _OutputFile.length() == 0 )
		return;

	g_CritSect_Print( )->Enter();
	_MakePath();

	sprintf( szFile, "%s\\%s", _OutputPath.c_str() , _OutputFile.c_str() );
	sprintf( szBuff, "(%d)%s\t%s\t", LV , TimeStr::Now_Time() , pszTitle );

	FILE* file = fopen( szFile , "a+" );
	if( file != NULL )
	{
		fputs(  szBuff , file );
		fputs(  pszMessage , file );
		fputs(  "\n" , file );
		fclose( file );
	}
	g_CritSect_Print( )->Leave();
}
void PrintClass::OutputToFile( const char* pszMessage )
{
	char szFile[512];

	g_CritSect_Print( )->Enter();

	_MakePath();

	sprintf( szFile, "%s\\%s", _OutputPath.c_str() , _OutputFile.c_str() );

	FILE* file = fopen( szFile , "a+" );
	if( file != NULL )
	{
		fputs(  TimeStr::Now_Time() , file );
		fputs(  "\t" , file );
		fputs( pszMessage , file );
		fputs(  "\n" , file );
		fclose( file );
	}

	g_CritSect_Print( )->Leave();
}

void PrintClass::OutputToBuff( int LV , const char* Title , const char* Str , va_list Marker )
{
	//////////////////////////////////////////////////////////////////////////
	if( LV < _FileOutputLV )
		return;

	//////////////////////////////////////////////////////////////////////////
	char	Buf[0xffff];
	try
	{
		int len = _vscprintf( Str , Marker ) + 1;
		if( len >= sizeof(Buf) )
			return;

		vsprintf_s( Buf , sizeof(Buf) , Str , Marker );
		OutputToBuff( LV , Title, Buf );
	}
	catch (...)
	{
		sprintf_s( Buf , sizeof( Buf )  , "(Crash)%s", Title );
		OutputToBuff( LV5 , Buf , Str );
	}
}

void PrintClass::OutputToBuff( int LV , const char* Title, const char* Message )
{
	char	Buf[0xffff];
	sprintf_s( Buf , sizeof(Buf) , "(%d)%s\t%s\t%s\n" , LV , TimeStr::Now_Time() , Title , Message  );
	g_CritSect_Print( )->Enter();
		_OutputMsgList.push_back( Buf );
	g_CritSect_Print( )->Leave();

	if(		TimeStr::Now_Value() - _LastOutputTime > 5 
		||	LV >= 5 )
	{
		OutputBuffToFile( );
	}
}
void PrintClass::OutputToBuff( const char* Message )
{
	char	Buf[0xffff];
	sprintf_s( Buf , sizeof(Buf) , "%s\t%s\n" , TimeStr::Now_Time() , Message  );
	g_CritSect_Print( )->Enter();
		_OutputMsgList.push_back( Buf );
	g_CritSect_Print( )->Leave();

	if( TimeStr::Now_Value() - _LastOutputTime > 5 )
	{
		OutputBuffToFile( );
	}
}
void PrintClass::OutputBuffToFile( )
{
	_LastOutputTime = TimeStr::Now_Value();
	if( _OutputMsgList.size() == 0 )
		return;

	//如果寫檔一直失敗
	if( _OutputMsgList.size() > 100000 )
	{
		//MessageBox( NULL , "OutputBuffToFile Error" ,  "_OutputMsgList.size() > 100000" , MB_OK );
		#ifndef _CLIENT 
			PrintToController(true, "OutputBuffToFile Error _OutputMsgList.size() > 100000");
		#endif
		_OutputMsgList.clear();
	}

	if( _OutputFile.size() == 0 )
		return;

	char szFile[512];

	g_CritSect_Print( )->Enter();

	_MakePath();

	sprintf( szFile, "%s\\%s", _OutputPath.c_str() , _OutputFile.c_str() );

	FILE* file = fopen( szFile , "a+" );
	if( file != NULL )
	{
		for( unsigned i = 0 ; i < _OutputMsgList.size() ; i++ )
		{
			fputs( _OutputMsgList[i].c_str() , file );
		}
		_OutputMsgList.clear();
		fclose( file );
	}
	else
	{
		//MessageBox( NULL , "OutputBuffToFile Error" , szFile , MB_OK );
		#ifndef _CLIENT 
			PrintToController(true, "OutputBuffToFile fopen failed , szFile='%s'" , szFile );
		#endif
		_OutputMsgList.clear();
	}

	g_CritSect_Print( )->Leave();
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
MassageOuputClass::MassageOuputClass(char*	File)
{
    _FileName = File;
}

void	MassageOuputClass::Print(char* format,...)
{
    char	_Buf[512];

    FILE* file = fopen( (char*)_FileName.c_str() , "a+" );	
    va_list marker =(char*)&format + sizeof(format);
    vsprintf( _Buf , format , marker );
    fputs(  _Buf , file );
    OutputDebugString( _Buf );
    fclose( file );

}
#pragma managed