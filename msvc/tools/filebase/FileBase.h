#pragma once
#pragma warning (disable:4996)
#pragma warning (disable:4949)

#include <fstream>
#include <string>
#include <vector>
//-------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------
enum FileBaseSeekENUM
{
    EM_FileSeek_Begin					= 0,
    EM_FileSeek_Current					= 1,
    EM_FileSeek_End						= 2,
};

enum FileBaseTypeENUM
{
    EM_FileBaseType_Read   = 0x0001,
    EM_FileBaseType_Write  = 0x0002,
    EM_FileBaseType_Binary = 0x0004,
};
//-------------------------------------------------------------------------------------------------
//基本 開檔模式
class MyFileBase
{
protected:
    char        _LastErrorStr[256];
    int         _IOType;
    string		_FileName;
public:
    MyFileBase( );
    virtual ~MyFileBase( );

    virtual bool    Open( const char* FileName , int Type = EM_FileBaseType_Read | EM_FileBaseType_Binary );
    virtual bool    IsOpen( );
    virtual bool    IsEOF( );

    virtual void    Close( );

    virtual int     Read( void *DestBuf , int Size );
    virtual bool    Write (void *SrcBuf , int Size );

    virtual void    Seek( int Offset , FileBaseSeekENUM Type );
    virtual int     GetLine( void *DestBuf, int Size );

    virtual int	    Size( );
    virtual int	    Position( );
    
    virtual void    ShowLastErrorStr( );
};
//-------------------------------------------------------------------------------------------------
//一般檔案 讀寫
class MyFile : public MyFileBase
{
    fstream     _File;
public:
    MyFile( );
    virtual ~MyFile( );

    //Type = FileBaseTypeENUM 組合
    virtual bool    Open( const char* FileName , int Type = EM_FileBaseType_Read | EM_FileBaseType_Binary );
    virtual bool    IsOpen( );
    virtual bool    IsEOF( );

    virtual void    Close( );						

    virtual int     Read( void *DestBuf , int Size );
    virtual bool    Write (void *SrcBuf , int Size );

    virtual void    Seek( int Offset , FileBaseSeekENUM Type ); 
    virtual int     GetLine( void *DestBuf, int Size );

    virtual int	    Size( );
    virtual int	    Position( );

};
//-------------------------------------------------------------------------------------------------
//記憶體 模擬檔案 讀寫 (小檔案)(效能不佳)
//-------------------------------------------------------------------------------------------------
class MyMemoryFile : public MyFileBase
{
protected:
    vector<char>    _Mem;
    int             _Position;

    void            _Clear( );						
public:
    MyMemoryFile( );
    virtual ~MyMemoryFile( );

    virtual bool    IsEOF( );

    virtual int     Read( void *DestBuf , int Size );
    virtual bool    Write (void *SrcBuf , int Size );

    virtual void    Seek( int Offset , FileBaseSeekENUM Type ); 
    virtual int     GetLine( void *DestBuf, int Size );

    virtual int	    Size( );
    virtual int	    Position( );    
};
//-------------------------------------------------------------------------------------------------
//LZO 讀寫 (小檔案)(效能不佳)
//-------------------------------------------------------------------------------------------------
class MyLZOFile : public MyMemoryFile
{
    
public:
    MyLZOFile( );
    virtual ~MyLZOFile( );
 
    virtual bool    Open( const char* FileName , int Type = EM_FileBaseType_Read );
    virtual void    Close( );

};