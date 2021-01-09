#ifndef __MY_SMALL_OBJ_H__
#define __MY_SMALL_OBJ_H__

#include "MyBaseInc.h"
#include "RecycleBin/recyclebin.h"
#include <deque>
#include <queue>
#include "lzo\lzo1x.h"

#pragma warning (disable:4949)

#pragma unmanaged

using		namespace std;
//---------------------------------------------------------------------------
///修改priority_queue 增加一個Clear的功能
template< class T, class Container = vector<T> , class Compare = less<typename Container::value_type > >
class MyP_Queue : public priority_queue<T,Container,Compare>
{
public:
    void clear(){c.clear();};

};

//---------------------------------------------------------------------------
//字串與ID 一對一的 Map
class Map_StrAndID
{
#define _Max_Number_    0x10000

    vector< string >    _IDToStrList;
    map< string , int > _StrToIDList;
public:

    bool    Add     ( char*  Str , int ID );
    bool    Del     ( char*  Str );
    bool    Del     ( int    ID  );
    int     GetID   ( char*  Str );
    char*   GetStr  ( int    ID  );

};
//---------------------------------------------------------------------------
/*
//要使用的Temp 基本組合
struct MyVector_BaseType
{
int  ID;
virtual void Init();     
};
*/
template < class Temp >
class MyVector
{
    RecycleBin< Temp >      _Bin;
    vector<Temp*>           _List;
    set<Temp*>              _Set;
	typename set<Temp*>::iterator	_Iter_GetData ;
public:

    int     size( );
    int     MaxNum( );
    Temp*   operator [] ( const int ID ) const;
    Temp*   New( unsigned ID );
    bool    Del( unsigned ID );

    int     Push_back( Temp* );
    Temp*   Pop_back( );
    Temp*   Back( );
    Temp*   Begin( );

    //Flag = true 重設循序取資料資訊(使用前一定要重設)
    //Flag = false 循序取資料
    Temp*	GetData( bool ResetFlag = false );    
};
//-------------------------------------------------------------------------------------
template<class Temp>
int     MyVector<Temp>::size( )
{
    return (int)_Set.size();
};
//-------------------------------------------------------------------------------------
template<class Temp>
Temp*    MyVector<Temp>::operator [] ( const int ID ) const
{
    if( _List.size() <= (unsigned) ID )
        return NULL;

    return _List[ ID ];
};
//-------------------------------------------------------------------------------------
template<class Temp>
Temp*    MyVector<Temp>::New( unsigned ID )
{
    if( ID > _Max_Number_ )
        return NULL;

    while( _List.size() <= ID )
    {
        _List.push_back( NULL  );
    }


	if( _List[ ID ] != NULL )
		return NULL;

    Temp* Ret =  _Bin.NewObj( );

    if( Ret == NULL )
        return NULL;

	_List[ ID ] = Ret;

    Ret->Init();
    Ret->ID = ID;

    _Set.insert( Ret );
    return Ret;
};
//-------------------------------------------------------------------------------------
template<class Temp>
bool    MyVector<Temp>::Del( unsigned ID ) 
{
    if( _List.size() <= ID )
        return false;

    Temp* CliInfo = _List[ ID ];
    if( CliInfo == NULL )
        return false;

    _Bin.DeleteObj( CliInfo );
    _Set.erase( CliInfo );
    _List[ ID ] = NULL;
    return true;    
};
//-------------------------------------------------------------------------------------
//循序取資料
template<class Temp>
Temp*	MyVector<Temp>::GetData( bool ResetFlag )
{
    //static set<Temp*>::iterator Iter ;
	if( ResetFlag != false )
    {
        _Iter_GetData = _Set.begin();
        return NULL;
    }

    if( _Iter_GetData == _Set.end() )
        return  NULL;

    Temp* Ret = *_Iter_GetData;
    _Iter_GetData++;
	
    return Ret;

};
//-------------------------------------------------------------------------------------
template<class Temp>
int	MyVector<Temp>::MaxNum( )
{
    return (int)_List.size();
}
//---------------------------------------------------------------------------
class MutilThread_CritSect
{
    CRITICAL_SECTION _CritSect;
public:
    MutilThread_CritSect()
    {
        Init();
    }
    ~MutilThread_CritSect()
    {
        DeleteCriticalSection( &_CritSect );
    };
    void Init()
    {
        InitializeCriticalSection( & _CritSect );
    }
    void Enter()
    {
		if( _CritSect.DebugInfo == NULL )
			return;
        EnterCriticalSection( &_CritSect );
    }
    void Leave()
    {
		if( _CritSect.DebugInfo == NULL )
			return;
        LeaveCriticalSection( &_CritSect );
    }
	
};
//--------------------------------------------------------------------------
inline MutilThread_CritSect*  g_CritSect( )
{ 
    static MutilThread_CritSect    g_Thread_CritSect; 

    return &g_Thread_CritSect;
}

inline MutilThread_CritSect*  g_CritSectTreadOnly( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect; 

	return &g_Thread_CritSect;
}
//--------------------------------------------------------------------------
//計數物件
//--------------------------------------------------------------------------
template<class Temp>
class ObjectConutClass
{
    static int _ObjCount;
public:
    ObjectConutClass() { _ObjCount++; };
    virtual ~ObjectConutClass(){ _ObjCount--; };
    int ObjCount()     { return _ObjCount; }
};
//--------------------------------------------------------------------------
template<class Temp>
int ObjectConutClass<Temp>::_ObjCount = 0;
//--------------------------------------------------------------------------
//時間字串物件
//--------------------------------------------------------------------------
namespace TimeStr
{
    char* ProcessBegin();
    char* Now_Date();
    char* Now_Time();
    char* Now();  

	unsigned int  Now_Value(  );	
	unsigned int  Now_Value( int TimeZone );	
	char* DateTimeStr( int );
	char* DateTimeStr_UTC( int );
};
//--------------------------------------------------------------------------
//=====================================================================================
//劇情參數型態定義
enum	ArgValueTypeENUM
{
    EM_ValueType_Double	    = 1 ,
    EM_ValueType_Int		= 2 ,
    EM_ValueType_String	    = 3 ,
    EM_ArgValueTypeENUM_FORCE_DWORD   = 0x7fffffff, 
};
//=====================================================================================
//參數傳遞物件
//=====================================================================================
class	ArgTransferStruct
{
protected:
    map<string,string>		_Arg;						            //參數，與值	
public:
    void    Clear() { _Arg.clear(); }
    int		GetNumber	( const string Name );				        //讀取參數(數字)
    char*	GetString	( const string Name );				        //讀取參數(字串)
    void	PushValue	( const string Name , const string Value );	//資料設定
	void	PushValue	( const string Name , int	Value );		//資料設定
};
//--------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//指標物件

template <class T > 
class Pointer
{
    T*  _Iter;
public:
    Pointer( )
    {
        _Iter = NEW( T );
    };
    ~Pointer( )
    {
        delete _Iter;
    };

    T* operator->()
    { return _Iter;};
};
//-------------------------------------------------------------------------------------

/*
//範例  
class CYetAnotherClass
{
private:
    InitSimple<int, 42> m_atltuae;
    ...
private:
    enum States
    {
        START, RUNNING, STOP
    };

    InitSimple<States, START> m_state;
};
*/
template <typename T, T t>
struct InitSimple
{
    InitSimple() : m_t(t) {}

    operator T&() {return m_t;}
    operator T&() const {return m_t;}

    T& AsType() {return m_t;}
    const T& AsType() const {return m_t;}

    T* operator&() {return &m_t;}
    const T* operator&() const {return &m_t;}

    T& operator=(const T& t) {return (m_t = t);}
    InitSimple(const InitSimple& rhs) {m_t = rhs.m_t;}

private:
    T m_t;
};
//--------------------------------------------------------------------------------------------------------------------
//	簡易的排序用物件資料
//--------------------------------------------------------------------------------------------------------------------
struct	BaseSortStruct
{
    int		Value;
	union
	{
		void*	Data;
		int		Data_Int;
	};

    bool operator >  ( const BaseSortStruct& P )    
    {	return P.Value > Value;	}
    bool operator <  ( const BaseSortStruct& P )
    {	return P.Value > Value;	}
    bool operator == ( const BaseSortStruct& P )
    {	return P.Value == Value;	}

};
//----------------------------------------------------------------------------------------------------------
struct	BaseSortStruct_Float
{
	float	Value;
	void*	Data;

	bool operator >  ( const BaseSortStruct_Float& P )    
	{	return P.Value > Value;	}
	bool operator <  ( const BaseSortStruct_Float& P )
	{	return P.Value > Value;	}
	bool operator == ( const BaseSortStruct_Float& P )
	{	return P.Value == Value;	}

};
//----------------------------------------------------------------------------------------------------------
//template < typename T >
class BaseLinkList
{
public:
    BaseLinkList()
    {
        Next = Front = NULL;
    }

    BaseLinkList* Next;
    BaseLinkList* Front;

    void AddTo( BaseLinkList* FrontObj );
    void Del( );
};
//////////////////////////////////////////////////////////////////////////
class MyFloat
{
#define _MyFloat_SMATH_EPSILON			1.0e-4f						//1E-6f

    bool _FloatEQU ( float X , float Y )
    {
        return (((X - _MyFloat_SMATH_EPSILON) < Y) && (Y < ( X + _MyFloat_SMATH_EPSILON)));
    }

    float  _Value;
public:
    MyFloat( float V ) { _Value = V; }

    float   operator = ( const float V ) { _Value = V ; return _Value; }
    float   operator = ( const MyFloat& V ) { _Value = V._Value ; return _Value; }
    bool    operator == ( const float V ){ return _FloatEQU ( V , _Value );}
    bool    operator == ( const MyFloat& V ){ return _FloatEQU ( V._Value , _Value ); }
};
//////////////////////////////////////////////////////////////////////////
class FilePath
{
	vector<string> _RetFileList;
	vector<string> _RetPathList;

public:
	//取得某目錄下所有子目錄
	vector<string>*	AllPathList( string Path );
	vector<string>*	AllPathList_Pure( string Path );
	//取得某目錄下所有子目錄 與檔案
	vector<string>*	AllFileList( string Path , string Sub );
	//取得某目錄下所有子目錄 與檔案(相對目錄)
	vector<string>*	AllFileList_Sub( string Path , string Sub );

	vector<string>* PathList(){ return &_RetPathList; }
	vector<string>* FileList(){ return &_RetFileList; }

	//件立以某目錄下所有子目錄
	bool	CreateAllPath( string Path , vector<string>& PathList );
};
//////////////////////////////////////////////////////////////////////////
//字碼轉換的物件
class CharTransferClass
{
	bool		_IsReady;
	string		_cStr;
	string		_utf8Str;
	wstring		_wcStr;

public:
	CharTransferClass()
	{
		_cStr = "";
		_utf8Str = "";
		_wcStr = L"";

		_IsReady = false;
	}
	CharTransferClass*	SetString( const char* Str );
	CharTransferClass*	SetUtf8String( const char* utf8Str );
	CharTransferClass*	SetWCString( const wchar_t* wcStr );

	const char*		GetString( );
	const char*		GetUtf8String( );
	const wchar_t*	GetWCString( );

	int	WCStrLen()	{ return (int)_wcStr.length()+1;}
	int	CStrLen()	{ return (int)_cStr.length() + 1;}
	int	UTF8Strlen(){ return (int)_utf8Str.length() + 1;}
};
//////////////////////////////////////////////////////////////////////////
//自串轉換
wstring Utf8ToWchar( const char* utf8 );
wstring CharToWchar( const char* cStr );
string Utf8ToChar( const char* utf8 );
string WcharToChar( const wchar_t* wcStr );
string CharToUtf8( const char* cStr );
string WCharToUtf8( const wchar_t* wcStr );
//////////////////////////////////////////////////////////////////////////
class MyLzoClass
{
	char	_wrkMem[LZO1X_1_MEM_COMPRESS];

public:
	//回傳 小於0表示失敗 大於0表示壓縮Size
	int Encode( const char* data , int size , char* encodeMem );
	//回傳 小於0表示失敗 大於0表示解壓Size
	int Decode( const char* data , int encodeSize , int OrgSize , char* decodeMem );

	//回傳 小於0表示失敗 大於0表示壓縮Size
	int Encode_Malloc( const char* data , int size , char** encodeMem );
	//回傳 小於0表示失敗 大於0表示解壓Size
	int Decode_Malloc( const char* data , int encodeSize , int OrgSize , char** decodeMem );
};
//////////////////////////////////////////////////////////////////////////
//處理時間Log
//////////////////////////////////////////////////////////////////////////
struct TimeLogBaseStruct
{
	int MaxProcTime;
	int MinProcTime;
	int ProcCount;
	int TotalProcTime;

	TimeLogBaseStruct()
	{
		Init();
	}
	void Init()
	{
		MaxProcTime		= 0;
		MinProcTime		= 0xffffff;
		ProcCount		= 0;
		TotalProcTime	= 0;
	}

	int		AvgProcTime() 
	{ 
		if( ProcCount == 0 )
			return 0;

		return TotalProcTime / ProcCount;
	};
};

class ProcTimeLogClass
{
	int		_EnterTime;
	int		_LeaveTime;
	int		_ClearTime;

	TimeLogBaseStruct	_Base;

public:

	ProcTimeLogClass();

	void	Enter();
	void	Leave();
	void	Clear();
	int		LogTime() { return _LeaveTime - _ClearTime; };

	TimeLogBaseStruct& Base(){ return _Base;}
};
//////////////////////////////////////////////////////////////////////////
//封包Log
//////////////////////////////////////////////////////////////////////////
class PacketProcTimeLogClass
{
	vector< TimeLogBaseStruct > _PGLog;
	int		_EnterTime;
	int		_LeaveTime;
	int		_ClearTime;

public:
	PacketProcTimeLogClass( );

	void	Enter( );
	void	Leave( int ID );
	void	Clear( );
	int		LogTime() { return _LeaveTime - _ClearTime; };
	vector< TimeLogBaseStruct >& PGLog() { return _PGLog;};

};
//////////////////////////////////////////////////////////////////////////
class MemoryAllocStruct
{
	int		_Size;
	char*	_Data;
public:
	int		Size()	{ return _Size;}
	char*	Data()	{ return _Data;}

	MemoryAllocStruct()
	{
		_Size = 0;
		_Data = NULL;
	}

	~MemoryAllocStruct()
	{
		if( _Data != NULL )
			delete _Data;	
	}

	char* Alloc( int S )
	{
		if( _Size == S )
			return _Data;
		if( _Data != NULL )
			delete _Data;
		_Data = NEW char[S];
		_Size = S;
		return _Data;
	}
};
//////////////////////////////////////////////////////////////////////////
/*
struct MemoryBlockStruct
{
	int		Size;
	void*	Data;

	bool IsEmpty()
	{
		return ( Data == NULL );
	}

	MemoryBlockStruct()
	{
		Size = 0;
		Data = NULL;
	}
	void Init()
	{
		if( Data )
			delete Data;

		Size = 0;
		Data = NULL;
	}
};
*/
// 用Key 存取某塊資料
class KeyDataClass
{
	vector< map< string , vector<char> > > _Data;
	vector< int >			_UnUsedID;
public:
	//~KeyDataClass();
	//回傳存此資料的Key
	int		PushData( map< string , vector<char> >& DataInfo );
	bool	PopData( int KeyID );
	map< string , vector<char> >* GetData( int KeyID );
	void	Clear();
};
//////////////////////////////////////////////////////////////////////////
//封包資料暫存處理
class PacketBuffClass
{
	int		_pos;
	int		_packBuffSize;
	char*	_packBuff;
	
public:
	PacketBuffClass();
	~PacketBuffClass();
	int PacketSize();

	bool	SetChar( char data );
	char*	GetData( );
	void	Clear();
	bool	IsReadOK();
};
//////////////////////////////////////////////////////////////////////////
//讀取IP來源的Class
struct ApnicCountryInfoStruct
{
	string		Country;
	unsigned	Count;
	unsigned	IPNum;

	unsigned	Key;

	bool		IsAllowLogin;
	
	ApnicCountryInfoStruct()
	{
		Count = 0;
		IPNum = 0;
		IsAllowLogin = true;
	}
};

class ApnicFileReaderClass
{
	map< unsigned , ApnicCountryInfoStruct , greater<unsigned> > _IpList;
	
public:
	bool	LoadFile				( const char* FileName );
	ApnicCountryInfoStruct& FindIP	( unsigned IPNum );
	bool	AddIp					( const char* BeginIp , const char* EndIp , const char* Courty );
	void	SetCountryFilter		( const char* Courty , bool Flag );
	void	SetAllCountryFilter		( bool Flag );
};
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#pragma managed
#endif //__MY_SMALL_OBJ_H__