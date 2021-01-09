

#include "filebase.h"
#include <Windows.h>
#include <stdio.h>
#include "lzo/lzo1x.h"
#include "malloc/MyAlloc.h"

#pragma unmanaged

//-----------------------------------------------------------------------------------------------------------------
MyFileBase::MyFileBase( )
{
    _LastErrorStr[0] = 0;
    _IOType = 0;   
}

MyFileBase::~MyFileBase( )
{
}

void MyFileBase::ShowLastErrorStr( )
{
    printf( "\nMyFileBase Error : %s" , _LastErrorStr );
}


bool    MyFileBase::Open( const char* FileName , int Type )
{ 
    sprintf( _LastErrorStr , "未實做" );
    return false;
}
bool    MyFileBase::IsOpen( )
{
    return false;
}
bool    MyFileBase::IsEOF( )
{
    return false;
}
void    MyFileBase::Close( )
{
}						
int     MyFileBase::Read( void *DestBuf , int Size )
{
    sprintf( _LastErrorStr , "未實做" );
    return 0;
}
bool    MyFileBase::Write (void *SrcBuf , int Size )
{
    sprintf( _LastErrorStr , "未實做" );
    return 0;
}
void    MyFileBase::Seek( int Offset , FileBaseSeekENUM Type )
{
}
int     MyFileBase::GetLine( void *DestBuf, int Size )
{
    sprintf( _LastErrorStr , "未實做" );
    return 0;
}
int	    MyFileBase::Size( )
{
    return 0;
}
int	    MyFileBase::Position( )
{
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
MyFile::MyFile( )
{
    _IOType = 0;
}
MyFile::~MyFile( )
{

}

bool MyFile::Open( const char* FileName , int Type )
{
    _IOType = Type;
    _FileName = FileName;

    int IOType = 0;
    if( IOType != 0)
        Close();

    if( Type & EM_FileBaseType_Read )
        IOType |= ios::in;
    if( Type & EM_FileBaseType_Write )
        IOType |= ios::out;
    if( Type & EM_FileBaseType_Binary )
        IOType |= ios::binary;

    _File.open( FileName , IOType );
    
    if(_File.is_open() == false )
    {
        _IOType = 0;
        sprintf( _LastErrorStr , "Open %s Error!! Type = %x" , FileName , Type );
        return false;
    }
    
    return true;
}
bool MyFile::IsOpen( )
{
    return _File.is_open();
}

bool MyFile::IsEOF( )
{
    return _File.eof();
}

void MyFile::Close( )
{
    _IOType = 0;
    _File.close();
}

int MyFile::Read( void *DestBuf , int Size )
{
    if( !( _IOType & EM_FileBaseType_Read) )
    {
        sprintf( _LastErrorStr , "Can't Read ( _IOType & EM_FileBaseType_Read ) == false " );
        return 0;
    }
    _File.read( (char*) DestBuf , Size );

    return _File.gcount();
}

bool MyFile::Write (void *SrcBuf , int Size )
{
    if( !( _IOType & EM_FileBaseType_Write) )
    {
        sprintf( _LastErrorStr , "Can't Write ( _IOType & EM_FileBaseType_Write ) == false " );
        return false;
    }
    _File.write( (char*)SrcBuf , Size );

    return true;
}

void MyFile::Seek( int Offset , FileBaseSeekENUM Type )
{
    switch( Type )
    {
    case EM_FileSeek_Begin:
        _File.seekg( Offset , ios::beg );
        break;
    case EM_FileSeek_Current:
        _File.seekg( Offset );
        break;
    case EM_FileSeek_End:
        _File.seekg( Offset , ios::end );
        break;
    }
}
int MyFile::GetLine( void *DestBuf, int Size )
{
    if( !( _IOType & EM_FileBaseType_Read) )
    {
        sprintf( _LastErrorStr , "Can't Read ( _IOType & EM_FileBaseType_Read ) == false " );
        return 0;
    }
    _File.getline( (char*) DestBuf , Size );
    return _File.gcount();
}

int	 MyFile::Size( )
{
    int Pos = _File.tellg();
    _File.seekg( 0 , ios::end );
    int End = _File.tellg();
    _File.seekg( Pos , ios::beg );
    return End;
}
int	 MyFile::Position( )
{
    return _File.tellg();
}

//-----------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//記憶體檔案 讀寫 (小檔案)
//-------------------------------------------------------------------------------------------------
MyMemoryFile::MyMemoryFile( )
{
    _Position = 0;
}
MyMemoryFile::~MyMemoryFile( )
{
    
}

bool    MyMemoryFile::IsEOF( )
{
    return ( _Position == _Mem.size() );
}

void    MyMemoryFile::_Clear( )
{
    _Mem.clear();
    _Position = 0;
}

int     MyMemoryFile::Read( void *DestBuf , int Size )
{
    int DataSize = (int)_Mem.size() - _Position;
    if( Size > DataSize )
        Size = DataSize;

    std::copy(  _Mem.begin() + _Position , _Mem.begin() + _Position + Size , (char*)DestBuf );
    _Position = Size;
    return Size;
}

bool    MyMemoryFile::Write (void *_SrcBuf , int Size )
{
    char* SrcBuf = (char*)_SrcBuf;

    while( (int)_Mem.size() > _Position )
        _Mem.pop_back();

    for( int i = 0 ; i < Size ; i++ )
    {        
        _Mem.push_back( *SrcBuf);
        SrcBuf++;
    }

    _Position = (int)_Mem.size();
    return true;
}

void    MyMemoryFile::Seek( int Offset , FileBaseSeekENUM Type )
{
    switch( Type )
    {
    case EM_FileSeek_Begin:
        if( Offset > (int)_Mem.size() )
        {
            _Position = (int)_Mem.size();
        }
        else
        {
            _Position = Offset;
        }
        break;
    case EM_FileSeek_Current:
        if( Offset + _Position > (int)_Mem.size() )
        {
            _Position = (int)_Mem.size();
        }
        else
        {
            _Position += Offset;
        }
        break;
    case EM_FileSeek_End:
        if( Offset > (int)_Mem.size() )
        {
            _Position = 0;
        }
        else
        {
            _Position = (int)_Mem.size() - Offset;
        }
        break;
    }    
}
int     MyMemoryFile::GetLine( void *_DestBuf, int Size )
{
    char* DestBuf = (char*)_DestBuf;
    int i;

    if( Size + _Position > (int)_Mem.size() )
        Size = (int)_Mem.size() - _Position;

    for( i = 0 ; i < Size ; i++ , _Position++ )
    {        
        if( _Mem[ _Position ] == 13 )
        {            
            _Position++;
            if( _Mem[ _Position ] == '\n' )
                _Position++;

            break;
        }
        DestBuf[i] = _Mem[_Position];
    }
    DestBuf[i] = 0;
    return 0;
}

int	    MyMemoryFile::Size( )
{
    return (int)_Mem.size();
}

int	    MyMemoryFile::Position( )
{
    return _Position;
}
//-----------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//LZO 讀寫 (小檔案)(效能不佳)
//-------------------------------------------------------------------------------------------------
#define  LZO_SERIAL	((long*)"DBF")		//LZO檢查碼

struct LZOFileHead
{
    long    Serial;			//檢查碼
    long	OriginalSize;	//壓縮前的大小
    long	EncoderSize;	//壓縮後的大小
    long	Version;		//版本
    char    Msg[16];		//資訊
    LZOFileHead()
    {
        Serial = *LZO_SERIAL;
        Version = 1;
        strcpy( Msg , "LZO File" );
        OriginalSize = 0;
        EncoderSize = 0;
    }
};

MyLZOFile::MyLZOFile( )
{

}
MyLZOFile::~MyLZOFile( )
{

}


void    MyLZOFile::Close( )
{
    if( !(_IOType & EM_FileBaseType_Write ) )
        return;

    fstream         File;
    LZOFileHead     FileHead;

    FileHead.OriginalSize = (int)_Mem.size();

    //配置壓縮使用記憶體
    BYTE *wrkMem = NEW BYTE[LZO1X_1_MEM_COMPRESS];
    BYTE *EncodeMem = NEW BYTE[_Mem.size() + (_Mem.size() >> 10)];
    BYTE *SrcMem = (BYTE*)&(_Mem[0]);
    lzo1x_1_compress((lzo_byte*)SrcMem ,
        FileHead.OriginalSize ,
        EncodeMem,
        (lzo_uint*) &FileHead.EncoderSize,
        wrkMem );

    File.open( _FileName.c_str() , ios::out | ios::binary );
    if( File.is_open( ) == false  )
    {
        //開檔失
        return ;
    }


    File.write( (char*)&FileHead , sizeof(LZOFileHead) );
    File.write( (char*)EncodeMem, FileHead.EncoderSize );
    File.close();

    delete EncodeMem;
    delete wrkMem;

    MyMemoryFile::Close();
}

bool    MyLZOFile::Open( const char* FileName , int Type )
{
    _FileName = FileName;
    _IOType = Type;

    if( !(Type & EM_FileBaseType_Read ) )
        return true;

    fstream     _File;
    _File.open( FileName , ios::in | ios::binary );
    if( _File.is_open() == false )
    {
        sprintf( _LastErrorStr , "開檔失" );
        return false;
    }
    LZOFileHead FileHead;
    _File.read( (char*)&FileHead , sizeof( FileHead ));
        
	if(FileHead.Serial != *LZO_SERIAL)
    {
        sprintf( _LastErrorStr , "開檔失 %s 不是 LZO檔案" , FileName );
	    return false;
    }
	



	char* LoadData = NEW char[FileHead.EncoderSize];
	char* Source = NEW char [FileHead.OriginalSize];

	_File.read( LoadData , FileHead.EncoderSize );


	lzo1x_decompress((lzo_byte*)LoadData
					, (lzo_uint)FileHead.EncoderSize
					, (lzo_byte*) Source
					, (lzo_uint *)&FileHead.OriginalSize,NULL);

    _Mem.clear();
    for( int i = 0 ; i < FileHead.OriginalSize ; i++ )
    {
        _Mem.push_back( Source[i] );
    }
	delete LoadData;
    delete Source;

    return true;
}


#pragma managed
