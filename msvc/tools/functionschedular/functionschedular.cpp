#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include "FunctionSchedular.h"
#pragma warning (disable:4949)
#pragma unmanaged
//***************************************************************************************
//靜態資料定義
//***************************************************************************************
/*
MyP_Queue1	<		SchedularInfo*
,	vector<SchedularInfo*>
,	SICompGreat	>			FunctionSchedularClass::_PQueue;

vector< SchedularInfo* >						FunctionSchedularClass::_FunList;
vector< int >									FunctionSchedularClass::_NousedGUIDList;
*/
//template <> FunctionSchedularClass*  Singleton<FunctionSchedularClass>::_Singleton = 0;
//***************************************************************************************
//	SchedularInfo 的函式實做
//***************************************************************************************
FunctionSchedularClass g_Schedular;
//----------------------------------------------------------------------------------
//建構函式 資料初始化
//----------------------------------------------------------------------------------
SchedularInfo::SchedularInfo( )
{
	_Next		= NULL;							//下個指令
	_Front		= NULL;							//上個指令
	//----------------------------------------------------------------------------------
	//	執行定義
	//----------------------------------------------------------------------------------
	_GUID		= -1;							//物件號碼
	_ProcessTime= 0;					//間隔時間
	_Func		= NULL;
	_Enable		= true;						//此物件是否致能
}
//----------------------------------------------------------------------------------
FunctionSchedularClass::~FunctionSchedularClass( )
{
	Clear();
}
//----------------------------------------------------------------------------------
//處理時間 (何時處理)
//----------------------------------------------------------------------------------
int			SchedularInfo::ProcessTime	( )
{
	return _ProcessTime;
}
//----------------------------------------------------------------------------------
//資料是否有效
//----------------------------------------------------------------------------------
bool		SchedularInfo::Enable( )
{
	return _Enable;
}
//----------------------------------------------------------------------------------
//讀取參數(數字)
//----------------------------------------------------------------------------------
char*		SchedularInfo::GetString( string Name )
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
int			SchedularInfo::GetNumber( string Name )
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
void		SchedularInfo::PushValue( string Name , string Value )
{
	_Arg[ Name ] = Value;
}
//----------------------------------------------------------------------------------
//加入一個CallBack函式
//----------------------------------------------------------------------------------
void		SchedularInfo::Add( SchedularInfo* Next )
{
	SchedularInfo*	Temp;
	for( Temp = this ; Temp->_Next != NULL ; Temp = Temp->_Next );

	Temp->_Next  = Next;
	Next->_Front = Temp->_Next;
}

//***************************************************************************************
//FunctionSchedularClass
//***************************************************************************************
//----------------------------------------------------------------------------------
//所有資料清除
//----------------------------------------------------------------------------------
void	FunctionSchedularClass::Clear( )
{
	int i;
	//清除所配置的記憶體
	for( i = 0 ; i < (int)_FunList.size() ; i++ )
	{
		if( _FunList[ i ] != NULL )
			delete _FunList[ i ];
	}

	_FunList.clear();
	_NousedGUIDList.clear();
	_PQueue.clear();
}
//----------------------------------------------------------------------------------
//配置一個ID
//----------------------------------------------------------------------------------
int		FunctionSchedularClass::_GetGUID( )
{
	int Ret;

	if( _NousedGUIDList.size() != 0 )
	{
		Ret = _NousedGUIDList.back();
		_NousedGUIDList.pop_back();
		return Ret;
	}

	Ret = (int)_FunList.size();
	_FunList.push_back( NULL );
	return Ret;
}
//----------------------------------------------------------------------------------
//釋放配置ID
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::_ReleaseGUID( int id )
{
	if( _FunList.size() <= (unsigned)id )
		return false;

	_FunList[id] = NULL;
	_NousedGUIDList.push_back( id );
	return true;
}
//----------------------------------------------------------------------------------
//取得某一個ID的函式登入資料
//----------------------------------------------------------------------------------
SchedularInfo*	FunctionSchedularClass::_GetSchedularInfo( int guid )
{
	if( (unsigned)guid >= _FunList.size() )
		return NULL;

	return _FunList[ guid ];
}
//----------------------------------------------------------------------------------
//設定某一比guid 的函式登入資料
//----------------------------------------------------------------------------------
bool FunctionSchedularClass::_SetSchedularInfo( int guid , SchedularInfo* Info)
{
	if( (unsigned)guid >= _FunList.size() )
		return false;

	_FunList[ guid ] = Info;
	return true;
}
//----------------------------------------------------------------------------------
//設定多久以後執行某個回呼函式
//回傳登入GUID ， 用來移除排程內的事件用
//最後一個摻數一定要是NULL
//範例:Push( Fun, ProcTime ,InuptClass , name1 , EM_ValueType_float  , 10000.0
//						   , name2 , EM_ValueType_string , "Value2"
//						   , name3 , EM_ValueType_int    ,  100		,NULL )
//Func		= 要回呼叫的函式
//ProcTime	= 多久一後要執行(千分之一秒為單位)
//type		= EM_ValueType_float , EM_ValueType_int , EM_ValueType_string , EM_ValueType_void
//----------------------------------------------------------------------------------
int		FunctionSchedularClass::Push( SchedularFunctionBase Func , int  ProcTime , void* _UserObjPoint , ... )
{


	FuncSchedularValueTypeENUM	type;
	char			Buf[64];

	char*			name;	
	char*			value;
	SchedularInfo*	Info = NEW( SchedularInfo );
	va_list			marker;

	va_start( marker , _UserObjPoint );
	while( 1 )
	{
		name = va_arg( marker , char* );
		if( name == NULL )
			break;
		type = ( FuncSchedularValueTypeENUM )va_arg( marker , int );
		switch( type )
		{
		case EM_ValueType_double:
			sprintf( Buf , "%f" , va_arg( marker , double ) );
			value = Buf;
			break;
		case EM_ValueType_int:
			sprintf( Buf , "%d" , va_arg( marker , int ) );
			value = Buf;
			break;
		case EM_ValueType_string:
			value = va_arg( marker , char* );
			break;
		}
		Info->PushValue( name , value );
	}

	va_end( marker );

	//取一個ID
	Info->_GUID			= _GetGUID( );
	Info->_ProcessTime	= ProcTime + clock();
	Info->_Func			= Func;
	Info->_UserObjPoint = _UserObjPoint;
	//資料登入管理
	_SetSchedularInfo( Info->_GUID , Info );
	//丟到處理排程
	_PQueue.push( Info );

	return Info->_GUID;
}

//----------------------------------------------------------------------------------
//設定當某GUID的回呼函式做完後，多久以後再執行某個回呼函式
//回傳登錄成功與否
//最後一個摻數一定要是NULL
//範例:AddPush( guid , Fun, ProcTime 
//						   , name1 , EM_ValueType_float  , 10000.0
//						   , name2 , EM_ValueType_string , "Value2"
//						   , name3 , EM_ValueType_int    ,  100		,NULL )
//GUID		= 要加入哪個函式後面
//Func		= 要回呼叫的函式
//ProcTime	= 多久一後要執行
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::AddPush( int GUID , SchedularFunctionBase Func , void* _UserObjPoint , ... )
{

	FuncSchedularValueTypeENUM	type;
	SchedularInfo*	PrvInfo = _GetSchedularInfo( GUID );

	if( PrvInfo == NULL ) 
		return false;

	char*			name;	
	char*			value;
	SchedularInfo*	Info = NEW( SchedularInfo );
	va_list			marker;
	char			Buf[64];

	va_start( marker , _UserObjPoint );

	while( 1 )
	{
		name = va_arg( marker , char* );
		if( name == NULL )
			break;
		type = ( FuncSchedularValueTypeENUM )va_arg( marker , int );
		switch( type )
		{
		case EM_ValueType_double:
			sprintf( Buf , "%f" , va_arg( marker , double ) );
			value = Buf;
			break;
		case EM_ValueType_int:
			sprintf( Buf , "%d" , va_arg( marker , int ) );
			value = Buf;
			break;
		case EM_ValueType_string:
			value = va_arg( marker , char* );
			break;
		}
		Info->PushValue( name , value );
	}

	va_end( marker );

	Info->_UserObjPoint = _UserObjPoint;
	Info->_Func			= Func;
	PrvInfo->Add( Info );

	return true;
}

//----------------------------------------------------------------------------------
//把某已個事件重排程中刪除
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::Erase( int GUID )
{
	SchedularInfo*	PrvInfo = _GetSchedularInfo( GUID );
	if( PrvInfo == NULL )
		return false;

	PrvInfo->_Enable = false;
	return true;
}
//----------------------------------------------------------------------------------
//清除某一個 SchedularInfo 的所有相關資料
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::_EraseSchedularInfo( SchedularInfo* Info )
{

	for( ; Info->_Front != NULL ; Info = Info->_Front );

	_ReleaseGUID( Info->_GUID );

	for( ; Info->_Next != NULL ; Info = Info->_Next )
		delete Info->_Front;


	delete Info;

	return true;
}
//----------------------------------------------------------------------------------
//定時函式處理
//----------------------------------------------------------------------------------
void	FunctionSchedularClass::Process( )
{

	int				IntervalTime;
	SchedularInfo*	Info;
	while(1)
	{
		if( _PQueue.size() == 0 )
			return;

		Info = _PQueue.top();

		//時間還沒到
		if( Info->_ProcessTime - clock() > 0)
			return;

		_PQueue.pop();

		if( !Info->Enable() )
		{
			_EraseSchedularInfo( Info );
			continue;
		}

		if( Info->_Func != NULL)
		{
			IntervalTime = Info->_Func( Info , Info->_UserObjPoint );

			if( IntervalTime == -1 || Info->_Next == NULL )
			{
				_EraseSchedularInfo( Info );
			}
			else 
			{
				Info->_Next->_ProcessTime = clock() + IntervalTime;
				_PQueue.push( Info->_Next );
			}
		}
	}
}
//***************************************************************************************
#pragma managed