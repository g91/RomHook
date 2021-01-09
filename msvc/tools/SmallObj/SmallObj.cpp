#include "SmallObj.h"
#include <time.h>
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <fstream>
//#include "debuglog/errormessage.h"

//  [9/9/2004]
//-------------------------------------------------------------------------------------
//          Time Str
//-------------------------------------------------------------------------------------
namespace  TimeStr
{
    char _ProcessBegin[32];
    char _Now_Date[32];
    char _Now_Time[32];
    char _Now[32];
	

    void  Update()
    {
        static int  NextProc = 0;  
        int Now = clock();
        if( NextProc - Now > 0 )
            return;

        NextProc = Now + 1000;

        time_t NowTime;
        time( &NowTime );
        struct tm *gmt;
        gmt = localtime( &NowTime );

        sprintf( _Now_Date , "%d/%02d/%02d" , 1900+ gmt->tm_year , 1 + gmt->tm_mon , gmt->tm_mday );
        sprintf( _Now_Time , "%02d:%02d:%02d" , gmt->tm_hour , gmt->tm_min, gmt->tm_sec );
        sprintf( _Now , "%s %s" , _Now_Date , _Now_Time );
    }
    char* ProcessBegin()
    {
        static bool IsInit = false;

        if( IsInit == false )
        {
            IsInit = true;
            time_t NowTime;
            time( &NowTime );
            struct tm gmt;
            gmt = *localtime( &NowTime );
            gmt.tm_sec -= clock() / 1000;
            mktime( &gmt);    

            sprintf( _ProcessBegin , "%d/%02d/%02d %02d:%02d:%02d " 
                , 1900+ gmt.tm_year , 1 + gmt.tm_mon , gmt.tm_mday 
                , gmt.tm_hour , gmt.tm_min, gmt.tm_sec);

        }
        return _ProcessBegin;
    }
    char* Now_Date()
    {
        Update();
        return _Now_Date;
    }
    char* Now_Time()
    {
        Update();
        return _Now_Time;
    }
    char* Now()
    {
        Update();
        return _Now;
    }

	unsigned int  Now_Value( )
	{
		__time32_t NowTime;
		_time32( &NowTime );

		return (unsigned int)NowTime;
	}

	unsigned int  Now_Value( int TimeZone )
	{
		__time32_t NowTime;
		_time32( &NowTime );
		return (unsigned int)NowTime + TimeZone * 60*60;
	}

	char* DateTimeStr( int Time )
	{
		static char DataTime[256];
		__time32_t NowTime = Time;

		struct tm *gmt;
		gmt = _localtime32( &NowTime );

		if( gmt == NULL )
			return "time";

		char DStr[256];
		char TStr[256];
		sprintf( DStr , "%d/%02d/%02d" , 1900+ gmt->tm_year , 1 + gmt->tm_mon , gmt->tm_mday );
		sprintf( TStr , "%02d:%02d:%02d" , gmt->tm_hour , gmt->tm_min, gmt->tm_sec );
		sprintf( DataTime , "%s %s" , DStr , TStr );
		return DataTime;
	}

	char* DateTimeStr_UTC( int Time )
	{
		static char DataTime[256];
		__time32_t NowTime = Time;

		struct tm *gmt;
		gmt = _gmtime32( &NowTime );

		if( gmt == NULL )
			return "time";

		char DStr[256];
		char TStr[256];
		sprintf( DStr , "%d/%02d/%02d" , 1900+ gmt->tm_year , 1 + gmt->tm_mon , gmt->tm_mday );
		sprintf( TStr , "%02d:%02d:%02d" , gmt->tm_hour , gmt->tm_min, gmt->tm_sec );
		sprintf( DataTime , "%s %s" , DStr , TStr );
		return DataTime;
	}
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
bool    Map_StrAndID::Add( char* Str , int ID )
{
    if( _StrToIDList.find( Str ) != _StrToIDList.end() )
        return false;

    if( _Max_Number_ <= (unsigned)ID )
        return false;

    while( ID >= (int)_IDToStrList.size() )
        _IDToStrList.push_back( "" );

    if( _IDToStrList[ ID ].c_str()[0] != 0 ) 
        return false;

    _StrToIDList[ Str ]  = ID; 
    _IDToStrList[ ID  ]  = Str;

    return true;  
}
bool    Map_StrAndID::Del( char* Str )
{
    int ID = GetID( Str );
    if( ID == -1 )
        return false;

    _IDToStrList[ID] = "";
    if( _StrToIDList.erase( Str ) == 0 )
        return false;


    return true;
}
bool    Map_StrAndID::Del( int ID )
{
    if( (unsigned)ID >= _IDToStrList.size() )
        return false;

    string Str = _IDToStrList[ ID ];

    if( Str.c_str()[0] == 0 )
        return false;

    _IDToStrList[ID] = "";

    if( _StrToIDList.erase( Str ) == 0 )
        return false;

    return true;
}
int     Map_StrAndID::GetID( char* Str )
{
    map< string , int >::iterator Iter;
    Iter = _StrToIDList.find( Str );
    if( Iter == _StrToIDList.end() )
        return -1;
    return Iter->second;
}
char*    Map_StrAndID::GetStr( int ID )
{
    if( (unsigned)ID > _IDToStrList.size() )
        return NULL;

    string Str = _IDToStrList[ ID ];
    return (char*)Str.c_str();
}
//-------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//讀取參數(數字)
//----------------------------------------------------------------------------------
char*		ArgTransferStruct::GetString( string Name )
{
    map<string,string>::iterator Iter;

    Iter = _Arg.find( Name );
    if( Iter == _Arg.end() )
        return NULL;		

    return (char*)Iter->second.c_str();
}
//----------------------------------------------------------------------------------
//讀取參數(字串)
//----------------------------------------------------------------------------------
int			ArgTransferStruct::GetNumber( string Name )
{
    map<string,string>::iterator Iter;

    Iter = _Arg.find( Name );
    if( Iter == _Arg.end() )
        return 0;		

    return atol( Iter->second.c_str() );
}
//----------------------------------------------------------------------------------
//資料設定
//----------------------------------------------------------------------------------
void		ArgTransferStruct::PushValue( string Name , string Value )
{
    _Arg[ Name ] = Value;
}
void		ArgTransferStruct::PushValue( string Name , int Value )
{

	_Arg[ Name ] = IntToStr( Value );
}
//----------------------------------------------------------------------------------
void BaseLinkList::AddTo( BaseLinkList* FrontObj )
{
    assert( FrontObj != this );
    assert( FrontObj->Next != this );

    Front = FrontObj;

    Next = Front->Next;
    Front->Next = this;
    if( Next != NULL )
        Next->Front = this;

    assert( Next != this );
    assert( Front != this );
}

void BaseLinkList::Del( )
{
    assert( Front->Next == this );
   
    Front->Next = Next;

    if( Next )
        Next->Front = Front;

    assert( Next != Front );
}

//----------------------------------------------------------------------------------------------------------
//取得某目錄下所有子目錄
vector<string>*	FilePath::AllPathList( string SrcPath )
{
//	static vector<string> AllPath;
	string Path;
	vector<string> OpenPath;
	struct _finddata_t c_file;
	long	hFile;

	char Findmask[512];
	char Buf[512];

	_RetPathList.clear();
	OpenPath.clear();

	const char *P = SrcPath.c_str();
	if( P[ SrcPath.length() - 1] != '\\' && SrcPath.length() != 0 )
		SrcPath += "\\";


	OpenPath.push_back( "" );


	while( OpenPath.size() )
	{
		Path = OpenPath.back();

		_RetPathList.push_back( Path );

		OpenPath.pop_back();
		sprintf( Findmask , "%s%s*." , SrcPath.c_str() , Path.c_str() );

		if( (hFile = (long)_findfirst( (char*)Findmask , &c_file )) != -1L )
		{

			do
			{
				if( !(c_file.attrib & _A_SUBDIR) )
					continue;

				if( c_file.name[0] == '.' )
					continue;

				//TempPath = Path + c_file.name + "\\";
				sprintf( Buf , "%s%s\\", Path.c_str() , c_file.name );
				OpenPath.push_back( Buf );


			}while( _findnext( hFile, &c_file ) == 0 );


			_findclose( hFile );
		}
	}

	return &_RetPathList;
}
vector<string>*	FilePath::AllPathList_Pure( string Path )
{

	char CurPath[ _MAX_PATH ];

	if( _getcwd( CurPath, _MAX_PATH ) == NULL )
		return NULL;

	_chdir( Path.c_str() );

	AllPathList( "" );

	_chdir( CurPath );

	return &_RetPathList;
}
//取得某目錄下所有子目錄 與檔案
vector<string>*	FilePath::AllFileList( string Path , string Sub )
{

	vector<string>* AllPath = AllPathList( Path );

	if(		Path.c_str()[ Path.length() - 1 ] != '\\' 
		&&	Path.c_str()[ Path.length() - 1 ] != '/'	)
		Path += "\\";

	_RetFileList.clear();
	string Temp;
	for( int i = 0 ; i < (int)AllPath->size() ; i++ )
	{
		Path = (*AllPath)[i] + Sub;

		WIN32_FIND_DATA  file_data;
		HANDLE	hfile = FindFirstFile(Path.c_str(), &file_data);
		if(hfile == INVALID_HANDLE_VALUE)
			continue;
		//return &AllFilePath;
		if( (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			_RetFileList.push_back( (*AllPath)[i] + file_data.cFileName );


		while(FindNextFile(hfile, &file_data))
		{
			if( (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				_RetFileList.push_back( (*AllPath)[i] + file_data.cFileName );
		}

	}

	return &_RetFileList;
}
//取得某目錄下所有子目錄 與檔案(相對目錄)
vector<string>*	FilePath::AllFileList_Sub( string Path , string Sub )
{
	char CurPath[ _MAX_PATH ];

	if( _getcwd( CurPath, _MAX_PATH ) == NULL )
		return NULL;

	_chdir( Path.c_str() );

	AllFileList( "" , Sub );

	_chdir( CurPath );

	return &_RetFileList;
}
//件立以某目錄下所有子目錄
bool	FilePath::CreateAllPath( string Path , vector<string>& PathList )
{
	char CurPath[ _MAX_PATH ];

	if( _getcwd( CurPath, _MAX_PATH ) == NULL )
		return false;

	_mkdir( Path.c_str() );
	_chdir( Path.c_str() );
	for( int i = 0 ; i < (int)PathList.size() ; i++ )
	{
		_mkdir( PathList[i].c_str() );
	}

	_chdir( CurPath );

	return true;
}
//----------------------------------------------------------------------------------------------------------
CharTransferClass*	CharTransferClass::SetString( const char* str )
{
	//if( str == NULL || strlen(str) == 0 )
	if( str == NULL ) //|| strlen(str) == 0 )
	{
		_IsReady = false;
		return this;
	}


	_cStr = str;

	
	//轉換 wchar
	{
		int wcsLen = MultiByteToWideChar(CP_ACP, 0 , str , -1 , NULL , NULL );

		if( wcsLen == 0 )
		{
			_IsReady = false;
			return this;
		}

		wchar_t*	wcsTmp = NEW wchar_t[ wcsLen ];
		MultiByteToWideChar(CP_ACP, 0 , str , -1 , wcsTmp , wcsLen );
		_wcStr =wcsTmp;
		delete wcsTmp;
	}

	//轉換Utf8
	{
		int			utf8Len = WideCharToMultiByte(CP_UTF8 , 0 , _wcStr.c_str() , -1, NULL, NULL, NULL, NULL);
		char*		utf8Tmp = NEW char[ utf8Len + 1 ];
		WideCharToMultiByte(CP_UTF8, 0 , _wcStr.c_str() , -1, utf8Tmp , utf8Len+1 , NULL, NULL);
		_utf8Str =utf8Tmp;
		delete utf8Tmp;
	}
	_IsReady = true;
	return this;
}
CharTransferClass*	CharTransferClass::SetUtf8String( const char* utf8Str )
{

	//if( utf8Str == NULL || strlen(utf8Str) == 0 )
	if( utf8Str == NULL )
	{
		_IsReady = false;
		return this;
	}

	_utf8Str = utf8Str;

	//轉換 wchar
	{
		int wcsLen = MultiByteToWideChar(CP_UTF8, 0 , utf8Str , -1 , NULL , NULL );

		if( wcsLen == 0 )
		{
			_IsReady = false;
			return this;
		}

		wchar_t*	wcsTmp = NEW wchar_t[ wcsLen ];
		MultiByteToWideChar(CP_UTF8, 0 , utf8Str , -1 , wcsTmp , wcsLen );
		_wcStr =wcsTmp;
		delete wcsTmp;
	}

	//轉換 char
	{
		int			cStrLen = WideCharToMultiByte(CP_ACP , 0 , _wcStr.c_str() , -1, NULL, NULL, NULL, NULL);
		char*		cStrTmp = NEW char[ cStrLen ];
		WideCharToMultiByte(CP_ACP, 0 , _wcStr.c_str() , -1, cStrTmp , cStrLen , NULL, NULL);
		_cStr =cStrTmp;
		delete cStrTmp;
	}
	_IsReady = true;
	return this;

}
CharTransferClass*	CharTransferClass::SetWCString( const wchar_t* wcStr )
{
	//if( wcStr == NULL || wcslen(wcStr) == 0 )
	if( wcStr == NULL )
	{
		_IsReady = false;
		return this;
	}
	_wcStr = wcStr;

	//轉換Utf8
	{
		int			utf8Len = WideCharToMultiByte(CP_UTF8 , 0 , _wcStr.c_str() , -1, NULL, NULL, NULL, NULL);
		char*		utf8Tmp = NEW char[ utf8Len ];
		WideCharToMultiByte(CP_UTF8, 0 , _wcStr.c_str() , -1, utf8Tmp , utf8Len , NULL, NULL);
		_utf8Str =utf8Tmp;
		delete utf8Tmp;
	}

	//轉換 char
	{
		int			cStrLen = WideCharToMultiByte(CP_ACP , 0 , _wcStr.c_str() , -1, NULL, NULL, NULL, NULL);
		char*		cStrTmp = NEW char[ cStrLen ];
		WideCharToMultiByte(CP_ACP, 0 , _wcStr.c_str() , -1, cStrTmp , cStrLen , NULL, NULL);
		_cStr =cStrTmp;
		delete cStrTmp;
	}

	_IsReady = true;
	return this;
}

const char* CharTransferClass::GetString( )
{
	if( _IsReady == false )
		return NULL;

	return _cStr.c_str();

}
const char*	CharTransferClass::GetUtf8String( )
{
	if( _IsReady == false )
		return NULL;

	return _utf8Str.c_str();

}
const wchar_t*	CharTransferClass::GetWCString( )
{
	if( _IsReady == false )
		return NULL;

	return _wcStr.c_str();

}

wstring Utf8ToWchar( const char* utf8Str )
{
	if( utf8Str == NULL || strlen( utf8Str ) == 0 )
		return L"";
	CharTransferClass cTran;
	cTran.SetUtf8String( utf8Str );
	return cTran.GetWCString();
}
wstring CharToWchar( const char* cStr )
{
	if( cStr == NULL || strlen( cStr ) == 0 )
		return L"";

	CharTransferClass cTran;
	cTran.SetString( cStr );
	return cTran.GetWCString();
}
string Utf8ToChar( const char* utf8 )
{
	if( utf8 == NULL || strlen( utf8 ) == 0 )
		return "";
	CharTransferClass cTran;
	cTran.SetUtf8String( utf8 );
	return cTran.GetString();
}
string WcharToChar( const wchar_t* wcStr )
{
	if( wcStr == NULL || wcslen( wcStr ) == 0 )
		return "";

	CharTransferClass cTran;
	cTran.SetWCString( wcStr );
	return cTran.GetString();
}
string CharToUtf8( const char* cStr )
{
	if( cStr == NULL || strlen( cStr ) == 0 )
		return "";

	CharTransferClass cTran;
	cTran.SetString( cStr );
	return cTran.GetUtf8String();
}
string WCharToUtf8( const wchar_t* wcStr )
{
	if( wcStr == NULL || wcslen( wcStr ) == 0 )
		return "";

	CharTransferClass cTran;
	cTran.SetWCString( wcStr );
	return cTran.GetUtf8String();
}

//回傳 小於0表示失敗 大於0表示壓縮Size
int MyLzoClass::Encode_Malloc( const char* data , int size , char** encodeMem )
{
	int		EncodeSize;	
	*encodeMem = NEW char[ size + (size>>10) ];
	unsigned char  *EncodeMem = (unsigned char*)*encodeMem;
	
	lzo1x_1_compress((lzo_byte*)data, size,	EncodeMem, (lzo_uint*) &EncodeSize, _wrkMem );
	return EncodeSize;
}
//回傳 小於0表示失敗 大於0表示解壓Size
int MyLzoClass::Decode_Malloc( const char* data , int encodeSize , int OrgSize , char** decodeMem )
{
	int	RetOrgSize;
	*decodeMem = NEW char[ OrgSize ];
	unsigned char* DecodeMem = (unsigned char*)*decodeMem;
	
	
	lzo1x_decompress((lzo_byte*)data
		, (lzo_uint)encodeSize
		, (lzo_byte*) DecodeMem
		, (lzo_uint *)&RetOrgSize,NULL);

	return RetOrgSize;
}

//回傳 小於0表示失敗 大於0表示壓縮Size
int MyLzoClass::Encode( const char* data , int size , char* encodeMem )
{
	int		EncodeSize;	
	lzo1x_1_compress((lzo_byte*)data, size,	(unsigned char*)encodeMem, (lzo_uint*) &EncodeSize, _wrkMem );
	return EncodeSize;
}
//回傳 小於0表示失敗 大於0表示解壓Size
int MyLzoClass::Decode( const char* data , int encodeSize , int OrgSize , char* decodeMem )
{
	int	RetOrgSize;

	lzo1x_decompress((lzo_byte*)data
		, (lzo_uint)encodeSize
		, (lzo_byte*) decodeMem
		, (lzo_uint *)&RetOrgSize,NULL);

	return RetOrgSize;
}

//////////////////////////////////////////////////////////////////////////
ProcTimeLogClass::ProcTimeLogClass()
{
	Clear();
}
void	ProcTimeLogClass::Enter()
{
	_EnterTime = GetTickCount();
}
void	ProcTimeLogClass::Leave()
{
	_LeaveTime = GetTickCount();
	int DTime = _LeaveTime - _EnterTime;

	if( DTime < _Base.MinProcTime )
		_Base.MinProcTime = DTime;

	if( DTime > _Base.MaxProcTime )
		_Base.MaxProcTime = DTime;

	_Base.TotalProcTime += DTime;
	_Base.ProcCount++;
}
void	ProcTimeLogClass::Clear()
{
	_LeaveTime = _ClearTime	= _EnterTime = GetTickCount();
	_Base.Init();
}
//////////////////////////////////////////////////////////////////////////
PacketProcTimeLogClass::PacketProcTimeLogClass( )
{
	_EnterTime = 0;
	_LeaveTime = 0;
	_ClearTime = GetTickCount();
}
void	PacketProcTimeLogClass::Enter( )
{
	_EnterTime = GetTickCount();
}
void	PacketProcTimeLogClass::Leave( int ID )
{
	while( ID >= (int)_PGLog.size() )
	{
		TimeLogBaseStruct Temp;
		_PGLog.push_back( Temp );
	}

	_LeaveTime = GetTickCount();
	int DTime = _LeaveTime - _EnterTime;

	TimeLogBaseStruct& Base = _PGLog[ ID ];

	if( DTime < Base.MinProcTime )
		Base.MinProcTime = DTime;

	if( DTime > Base.MaxProcTime )
		Base.MaxProcTime = DTime;

	Base.TotalProcTime += DTime;
	Base.ProcCount++;

}
void	PacketProcTimeLogClass::Clear( )
{
	for( unsigned i = 0 ; i < _PGLog.size() ; i++ )
		_PGLog.clear();
}
//////////////////////////////////////////////////////////////////////////
// 用Key 存取某塊資料
/*
class KeyDataClass
{
	vector< MemoryBlockStruct > _Data;
	vector< int >				_UnUsedID;
public:
	~KeyDataClass();
	//回傳存此資料的Key
	int PushData( void* Data , int Size );
	int PushData( MemoryBlockStruct DataInfo );
	bool PopData( int Key );
};*/
/*
KeyDataClass::~KeyDataClass()
{
	Clear();
}
*/
int KeyDataClass::PushData(  map< string , vector<char> >& DataInfo )
{
	if( DataInfo.size() == 0 )
		return -1;

	int KeyID = -1;
	if( _UnUsedID.size() != 0)
	{
		KeyID = _UnUsedID.back();
		_UnUsedID.pop_back();
		_Data[ KeyID ] = DataInfo;
	}
	else
	{
		KeyID = _Data.size();
		_Data.push_back( DataInfo );		
	}
	return KeyID;
}

bool KeyDataClass::PopData( int KeyID )
{
	if( unsigned( KeyID ) >= _Data.size() )
		return false;

	_Data[ KeyID ].clear();
	_UnUsedID.push_back( KeyID );

	return true;
}

map< string , vector<char> >* KeyDataClass::GetData( int KeyID )
{
	if( unsigned( KeyID ) >= _Data.size() )
		return NULL;


	return &_Data[ KeyID ];
}

void	KeyDataClass::Clear()
{
//	for( unsigned int i = 0 ; i < _Data.size() ; i++ )
//	{
//		delete _Data[i].Data;
//	}
	_Data.clear();
	_UnUsedID.clear();
	return;
}
//////////////////////////////////////////////////////////////////////////
//封包資料暫存處理
PacketBuffClass::PacketBuffClass()
{
	_pos = 0;
	_packBuffSize = 1024;
	_packBuff = NEW char[1024];
}
PacketBuffClass::~PacketBuffClass()
{
	if( _packBuff != NULL )
		delete _packBuff;
}
int PacketBuffClass::PacketSize()
{
	return int((int*)_packBuff );
}
/*
int PacketBuffClass::Reset( int packetSize )
{
	if(		_packBuffSize < packetSize 
		|| ( _packBuffSize > 0x10000 && packetSize < 0x1000 ) )
	{
		if( _packBuff != NULL )
			delete _packBuff;
		_packBuff = NEW char[packetSize];
		_packBuffSize = packetSize;
	}

	_packsize = packetSize;
}
*/
bool	PacketBuffClass::SetChar( char data )
{
	if( _pos > 4 && _pos >= _packBuffSize )
		return false;

	_packBuff[ _pos ] = data;
	_pos++;

	if( _pos == 4 )
	{
		if(		PacketSize() + 4 > _packBuffSize 
			|| ( PacketSize() > 0x10000 && PacketSize() < 0x1000 ) )
		{
			int  newBuffSize = PacketSize() + sizeof(int);
			if( newBuffSize > 0x100000 )
				return false;
			char* newBuff = NEW char[newBuffSize];
			memcpy( newBuff , _packBuff , 4 );
			delete _packBuff;
			_packBuffSize = newBuffSize;
			_packBuff = newBuff;
		}
	}
	return true;
}
char*	PacketBuffClass::GetData( )
{
	return _packBuff + sizeof(int);
}

void	PacketBuffClass::Clear()
{
	_pos = 0;
}
bool	PacketBuffClass::IsReadOK()
{
	if( _pos < 4 )
		return false;

	if( _pos == PacketSize() + sizeof(int) )
		return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////
unsigned IpTransfer( unsigned IP )
{
	unsigned RetIP;
	char* pIPNum = (char*)&(IP);		
	char* pKey = (char*)&(RetIP);
	pKey[0] = pIPNum[3];
	pKey[1] = pIPNum[2];
	pKey[2] = pIPNum[1];
	pKey[3] = pIPNum[0];

	return RetIP;
}
bool	ApnicFileReaderClass::LoadFile( const char* FileName )
{
	char	Buf[1024];
	_IpList.clear();

	char*	pStr[6];


	fstream fs;

	fs.open( FileName , ios::in );	

	if( fs.is_open() == false )
		return false;

	bool IsGetStrOK;
	while( fs.eof() == false )
	{
		fs.getline( Buf , sizeof( Buf )	);

		pStr[0] = Buf;
		IsGetStrOK = true;
		for( int i = 1 ; i < 6 ; i++ )
		{
			pStr[ i ] = strstr( pStr[ i -1 ] , "|" );			
			if( pStr[ i ] == NULL )
			{
				IsGetStrOK = true;
				break;
			}
			*(pStr[ i ]) = 0;
			pStr[ i ]++;
		}

		if( IsGetStrOK == false )
			continue;

		if(		_stricmp( pStr[0] , "apnic" ) != 0
			||	_stricmp( pStr[2] , "ipv4" ) != 0	)
			continue;

		ApnicCountryInfoStruct Info;
		Info.Country = pStr[1];
		Info.Count = atol( pStr[4] );
		Info.IPNum = inet_addr( pStr[3] );
/*
		char* pIPNum = (char*)&(Info.IPNum);		
		char* pKey = (char*)&(Info.Key);
		pKey[0] = pIPNum[3];
		pKey[1] = pIPNum[2];
		pKey[2] = pIPNum[1];
		pKey[3] = pIPNum[0];
		*/
		Info.Key = IpTransfer( Info.IPNum );

		_IpList[ Info.Key-1 ] = Info;
	}

	fs.close();
	return true;
}

bool	ApnicFileReaderClass::AddIp( const char* BeginIp , const char* EndIp , const char* Courty )
{
	ApnicCountryInfoStruct Info;

	Info.IPNum = inet_addr( BeginIp );

	unsigned MinIp = IpTransfer( inet_addr( BeginIp ) );
	unsigned MaxIp = IpTransfer( inet_addr( EndIp ) );

	if( MinIp > MaxIp )
		return false;


	Info.Country = Courty;
	Info.Count = MaxIp - MinIp + 1;
	Info.IPNum = inet_addr( BeginIp );;
	Info.Key  = MinIp;

	_IpList[ Info.Key-1 ] = Info;
	return true;
}

void	ApnicFileReaderClass::SetCountryFilter		( const char* Courty , bool Flag )
{
	map< unsigned , ApnicCountryInfoStruct , greater<unsigned> >::iterator Iter;

	for( Iter = _IpList.begin() ; Iter != _IpList.end() ; Iter ++ )
	{
		if( _stricmp( Courty , Iter->second.Country.c_str() ) == 0 )
		{
			Iter->second.IsAllowLogin = Flag;
		}
	}
}

void	ApnicFileReaderClass::SetAllCountryFilter		( bool Flag )
{
	map< unsigned , ApnicCountryInfoStruct , greater<unsigned> >::iterator Iter;
	for( Iter = _IpList.begin() ; Iter != _IpList.end() ; Iter ++ )
	{
		Iter->second.IsAllowLogin = Flag;
	}
}

ApnicCountryInfoStruct& ApnicFileReaderClass::FindIP( unsigned IPNum )
{
	static ApnicCountryInfoStruct EmptyResult;
	map< unsigned , ApnicCountryInfoStruct , greater<unsigned> >::iterator Iter;

	char* pIPNum = (char*)&IPNum;
	unsigned Key;
	char* pKey = (char*)&Key;
	pKey[0] = pIPNum[3];
	pKey[1] = pIPNum[2];
	pKey[2] = pIPNum[1];
	pKey[3] = pIPNum[0];


	Iter = _IpList.upper_bound( Key );

	if( Iter == _IpList.end() )
		return EmptyResult;

	if( Key - Iter->second.Key >= Iter->second.Count )
		return EmptyResult;

	return Iter->second;

}
/*
void	EventCountClass::Clear()
{
	_CountMap.clear();
	_NameMap.clear();
}
bool	EventCountClass::SetName( int ID , string Name )
{
	_NameMap[ID] = Name;
	return true;
}
string	EventCountClass::GetInfoString( )
{
	char Buf[2048];
	map< int , int >::iterator Iter;
	for( Iter = _CountMap.begin() ; Iter != _CountMap.end() ; Iter++ )
	{
		sprintf( Buf + strlen(Buf) , "\n EventID[%d]  Count=[%d]" , Iter->first , Iter->second );		
	}
	return Buf;
}

string	EventCountClass::GetInfoString_Name( )
{
	char Buf[2048];
	map< int , string >	::iterator Iter;
	for( Iter = _NameMap.begin() ; Iter != _NameMap.end() ; Iter++ )
	{
		sprintf( Buf + strlen(Buf) , "\n%s = [%d]" , Iter->second.c_str() , _CountMap[ Iter->first ]  );		
	}
	return Buf;
}

bool	EventCountClass::Event( int EventID )
{
	_CountMap[EventID]++;
	return true;
}
*/
//----------------------------------------------------------------------------------------------------------

