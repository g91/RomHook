#include "CutString.h"
#include <algorithm>
#include "basefunction/BaseFunction.h"
#pragma warning (disable:4949)
#pragma warning (disable:4996)
#pragma unmanaged

void CutString::Parse( )
{
    _Value.clear(); 

    if( _Str.length() == 0 )
        return;

    char*   Arg;
    char    Buf[4096];
    MyStrcpy( Buf , _Str.c_str() , sizeof( Buf ) );

    char* token = strtok( Buf , _Seps.c_str() );
    
    if( token == NULL )
        return;

    _Value.push_back( token );


    for( int i = 0 ; ; i++ )
    {
        Arg = strtok( NULL , _Seps.c_str() );
        if( Arg== NULL ) 
            break;

        _Value.push_back( Arg );
    }

    if( _IsLowercase != false )
    {
        _LowerCase();
    }
}

//把資料轉成小寫
void CutString::_LowerCase()
{
    for( unsigned int i = 0 ; i < _Value.size() ; i++ )
    {
        //_strlwr( (char*) _Value[1].c_str() );
		std::transform( _Value[1].begin(), _Value[1].end(), _Value[1].begin(), ::tolower );
    }
}

CutString::CutString( )
{
    _IsLowercase = true;
    _Seps = " ,\t\n";
}

void CutString::Seps( const string Value )
{
    _Seps = Value;
}

void CutString::Str( const string Value)
{
    _Str = Value;
    Parse( );
}

void CutString::IsLowerCase( const bool Flag )
{
    if( Flag == _IsLowercase )
        return;

    _IsLowercase = Flag;

    if( _IsLowercase != false )
        _LowerCase();
    else
        Parse();

}

int   CutString::GetNum( const int ID )
{
    if( (unsigned)ID > _Value.size() )
        return 0;
    return _MAtoi( _Value[ID] );
}

char* CutString::GetStr( const int ID )
{
    if( (unsigned)ID > _Value.size() )
        return NULL;
    return (char*)_Value[ID].c_str();
}

int CutString::_MAtoi( const string Str)
{
    long	Ret;
    char*   Val = (char*)Str.c_str();

    if(atoi( Val ) == 0)
    {
        Ret = strtol(Val,NULL,16);
        return Ret;
    }

    return atoi(Val);
}

#pragma managed