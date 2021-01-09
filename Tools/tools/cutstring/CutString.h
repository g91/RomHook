#pragma once
//======================================================================================
/**
* @file CutString.h CutString.cpp
* ��r�� �@�ӭӪ� �R�O�r��
* "AA BB CC DD" ==>> "AA" "BB" "CC" "DD"
* Data : 2005.3.25
* @author hsiangren@hotmail.com
*/
//======================================================================================

//#include <windows.h>
#include <string>
#include <vector>

using namespace std;

class CutString 
{
    string              _Str;
    vector< string >    _Value;
    string              _Seps;
    bool                _IsLowercase;

    //�����ন�p�g
    void                _LowerCase();
    int                 _MAtoi( const string Str );
public:
    CutString( );

    void                Str( const string );
    void                Seps( const string );
    void                IsLowerCase( const bool Flag );
    void                Parse( );    

    int                 ArgCount(){ return (int)_Value.size();}
    int                 GetNum( const int ID );
    char*               GetStr( const int ID );
};

//======================================================================================