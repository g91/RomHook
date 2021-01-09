#include "MyError.h"
#include <Windows.h>

MyError g_MyError;

void        MyError::SetError( const int ErrorCode , const string ErrorStr )
{
    _LastErrorStr  = ErrorStr;
    _LastErrorCode = ErrorCode;
}

string      MyError::LastErrorStr( )
{
    return _LastErrorStr;
}

int         MyError::LastErrorCode( )
{
    return _LastErrorCode;
}

void        MyError::SetDisplayMode( const int DisplayMode )
{
    _DisplayMode = DisplayMode;
}

void        MyError::Displayer( )
{
    if( _DisplayMode & EM_MyErrorDisplayer_Print )
    {
        printf( "\n%s" , _LastErrorStr.c_str() );
    }
    if( _DisplayMode & EM_MyErrorDisplayer_MessageBox )
    {
        MessageBox( NULL , _LastErrorStr.c_str() , "Error" , MB_OK );
    }
    if( _DisplayMode & EM_MyErrorDisplayer_DebugOutput )
    {
        //OutputDebugStr( _LastErrorStr.c_str() );
    }     
}