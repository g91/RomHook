#pragma once
#include    <string>

using namespace std;

#ifdef __MY_ERR_OUTPUT__
    #define SetMyError( code , str )            { g_MyError.SetError( code , str ); }
    #define SetMyErrorDisplayMode( DisplayMode ){ g_MyError.SetDisplayMode( DisplayMode ); }
    #define MyErrorDisplayer( )                 { g_MyError.Displayer( ); }
#else
    #define SetMyError( code , str )            
    #define SetMyErrorDisplayMode( DisplayMode )
    #define MyErrorDisplayer( )                 
#endif



enum MyErrorDisplayerENUM
{
    EM_MyErrorDisplayer_Print       = 1,
    EM_MyErrorDisplayer_MessageBox  = 2 , 
    EM_MyErrorDisplayer_DebugOutput = 4 ,
};

class MyError
{
    string      _LastErrorStr;
    int         _LastErrorCode;

    int         _DisplayMode;
public:

    void        SetError( const int error_code , const string error_str );
    string      LastErrorStr( );
    int         LastErrorCode( );

    void        SetDisplayMode( const int DisplayMode = EM_MyErrorDisplayer_Print );
    void        Displayer();
};

extern MyError g_MyError;