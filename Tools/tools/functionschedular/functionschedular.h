//=====================================================================================
/**
 * @file functionschedular.h functionSchedular.cpp 
 * 函式排程系統物件，將不立即處理的函式丟到排程內等到需處理時再呼叫\n
 * Last UpDate:2003.8.29
 * @author jacklo@softstar.com.tw
 */
//=====================================================================================
#pragma once
#pragma warning (disable:4786)
#pragma warning (disable:4949)

#include <map>
#include <queue>
#include <vector>
#include <string>
#include "Singleton/singleton.h"
#include <boost/function.hpp>
#include <functional>
#pragma unmanaged
using namespace	std;

class	SchedularInfo;
class	FunctionSchedularClass;
//=====================================================================================
//函式指標定義
//=====================================================================================
///定義回乎函式的格式 Ret 下一個指令處理的時間  Ret = -1 代表結束
//typedef	int		(*SchedularFunctionBase)(SchedularInfo*	Obj,void*	InputClass);
#define SchedularFunctionBase boost::function<int ( SchedularInfo*	Obj,void*	InputClass ) >
//=====================================================================================
//函式排程內的資料
//=====================================================================================
class	SchedularInfo 
{
	friend class	FunctionSchedularClass;
protected:
	SchedularInfo*			_Next;							//下個指令
	SchedularInfo*			_Front;							//上個指令
	//----------------------------------------------------------------------------------
	//	執行定義
	//----------------------------------------------------------------------------------
	long					_GUID;							//物件號碼
	long					_ProcessTime;					//間隔時間
	SchedularFunctionBase	_Func;
	map<string,string>		_Arg;							//參數，與值	
	bool					_Enable;						//此物件是否致能
	void*					_UserObjPoint;					//玩家設定資料
public:
	SchedularInfo( );
	int			ProcessTime	( );							//處理時間
	bool		Enable		( );							//資料是否有效
	int			GetNumber	( string Name );				//讀取參數(數字)
	char*		GetString	( string Name );				//讀取參數(字串)
	void		PushValue	( string Name , string Value );	//資料設定
	void		Add			( SchedularInfo* Next );		//加入一個CallBack函式
	long		GUID		(){return _GUID;};				//回傳 GUID
};

//=====================================================================================

//=====================================================================================
///給Priority Queue 排序用的比較物件
struct	SICompGreat{
	bool operator() ( SchedularInfo* A , SchedularInfo* B ) 
		{ return A->ProcessTime() > B->ProcessTime(); }
};

//=====================================================================================

//=====================================================================================
//劇情參數型態定義
enum	FuncSchedularValueTypeENUM
{
	EM_ValueType_double	    = 1 ,
	EM_ValueType_int		= 2 ,
	EM_ValueType_string	    = 3 ,
    EM_FuncSchedularValueType_FORCE_DWORD   = 0x7fffffff, 
};
//=====================================================================================

//=====================================================================================
//修改後的priority_queue
template<class T,class Container,class Compare>
class MyP_Queue1 : public priority_queue<T,Container,Compare>
{
public:
    void clear(){c.clear();};

};
//=====================================================================================
//
//=====================================================================================
///處理函式回呼的物件，把函式放到堆疊內經過設定得時間後才執行
class	FunctionSchedularClass //: public Singleton< FunctionSchedularClass >
{
	
protected:
	MyP_Queue1	<		SchedularInfo*
						,	vector<SchedularInfo*>
						,	SICompGreat	>			_PQueue;

	vector< SchedularInfo* >						_FunList;
	vector< int >   								_NousedGUIDList;

	//配置一個ID
	int		_GetGUID( );

	//釋放配置ID
	bool		_ReleaseGUID( int guid );

	//取得某一個ID的資料
	SchedularInfo*	_GetSchedularInfo( int guid );

	//設定某一比guid 的登入資料 
	bool		_SetSchedularInfo( int guid , SchedularInfo* );

	//清除某一個 SchedularInfo 的所有相關資料
	bool		_EraseSchedularInfo( SchedularInfo* );
public:
	~FunctionSchedularClass();

	///所有資料清除
	void	Clear();

	///設定多久以後執行某個回呼函式											\n
	///回傳登入GUID ， 用來移除排程內的事件用								\n
	///最後一個摻數一定要是NULL												\n
	///範例:Push( Fun, ProcTime , NULL										\n
	///	 		    , name1 , EM_ValueType_float  , 10000.0				\n
	///				, name2 , EM_ValueType_string , "Value2"				\n
	///				, name3 , EM_ValueType_int    ,  100		,NULL )		\n
	///@param Func		= 要回呼叫的函式									\n
	///@param ProcTime	= 多久一後要執行(千分之一秒為單位)					\n
	///@param UserObjPoint = 使用者的物件指標								\n
	///@param ... 為 函式名稱 型別  值 .... 最後NULL 
	int		Push( SchedularFunctionBase Func , int  ProcTime , void* UserObjPoint , ... );



	///設定當某GUID的回呼函式做完後，多久以後再執行某個回呼函式				\n
	///回傳登錄成與否														\n
	///最後一個摻數一定要是NULL												\n
	///範例:AddPush( guid , Fun , NULL										\n
	///					 , name1 , EM_ValueType_float  , 10000.0			\n
	///					 , name2 , EM_ValueType_string , "Value2"			\n
	///					 , name3 , EM_ValueType_int    ,  100		,NULL )	\n
	///@param GUID		= 要加入哪個函式後面								\n
	///@param Func		= 要回呼叫的函式(千分之一秒為單位)					\n
	///@param UserObjPoint = 使用者的物件指標								\n
	///@param ... 為 函式名稱 型別  值 .... 最後NULL 						\n
	bool		AddPush( int GUID , SchedularFunctionBase Func , void* UserObjPoint , ... );

	
	///把某已個事件重排程中刪除
	bool		Erase( int GUID );


	///定時函式處理
	void		Process();

};

extern FunctionSchedularClass g_Schedular;
//=====================================================================================
#pragma managed
