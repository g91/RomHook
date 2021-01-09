#pragma once

#include <windows.h>
#include "SqlBaseClass.h"

#include <deque>
#include <vector>
#include <string>
#include "smallobj/smallobj.h"

using namespace std;


//--------------------------------------------------------------------------
#define _Def_DB_ThreadCount_ 10

class DBTransferClass : public ObjectConutClass< DBTransferClass >
{
//***************************************************************************
//      資料結構定義
//***************************************************************************
 typedef void ( *DBEventCB )( SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );

 struct DBRequestEventStruct 
 {  
    void*               UserObj;
    ArgTransferStruct   Arg;
    DBEventCB           EventFunc;
 };
//***************************************************************************

	static bool   _IsStopAll;			//停止所有的資料庫儲存
    //要求處理的資料Queue
    deque< DBRequestEventStruct* >				_DBReadRequest;  
    //deque< DBRequestEventStruct* >  _DBWriteRequest[_Def_DB_ThreadCount_];  
	vector< deque< DBRequestEventStruct* > >	_DBWriteRequest;  

    MutilThread_CritSect          _Thread_CritSect;

    string _Srv;
    string _DB;
    string _LoginID;
    string _Password;

    int    _RunThreadCount;     //執行中的 Thread 數量
    bool   _IsDestroy;          //物件是否解構
	bool   _IsConnectError;		//連線出問題

    int    _TotalRequestCount;
	int	   _ThreadCount;

    //HANDLE _hThread[ _Def_DB_ThreadCount_ ];
    //HANDLE _hEvent[ _Def_DB_ThreadCount_ ];
    //DWORD  _ThreadID[ _Def_DB_ThreadCount_ ];

	vector< HANDLE > _hThread;
	vector< HANDLE > _hEvent;
	vector< DWORD >  _ThreadID;

    static DWORD WINAPI _ThreadFuction( void* This ){ return ((DBTransferClass*)This)->_ThreadFunc() ; };
    int    _ThreadFunc( );

    // Forward declarations of the error handler and message handler.
//    static int _DB_Error( SqlBaseClass* sqlBase, int severity, int dberr, int oserr, char * dberrstr, char * oserrstr );
//    static int _DB_Msg( SqlBaseClass* sqlBase, DBINT msgno, int msgstate, int severity, char * msgtex );


	unsigned int	_MaxWriteCmdCount;
	unsigned int	_MinWriteCmdCount;
	unsigned int	_TotalWriteCmdCount;


public:
    DBTransferClass( const char* Server , const char* DB , const char* LoginID , const char* Password , int ThreadCount = _Def_DB_ThreadCount_ );
    ~DBTransferClass( );

//    void Read( DBEventCB EventFunc , void* UserObj , char* SQLCmd );
//    void Write( int ID , DBEventCB EventFunc , void* UserObj , char* SQLCmd );
    ///範例:Read( Fun, UserObjPoint
    ///	 		    , name1 , EM_ValueType_Float  , 10000.0				
    ///				, name2 , EM_ValueType_String , "Value2"			
    ///				, name3 , EM_ValueType_Int    ,  100		,NULL )	
    void Read( DBEventCB EventFunc , void* UserObj , ... );
    void Write( int ID , DBEventCB EventFunc , void* UserObj , ... );
    void SqlCmd( int ID , DBEventCB EventFunc , void* UserObj );

    int  TotalRequestCount(){return _TotalRequestCount;};

	//停止所有資料存取
	static void StopAll();	

	void	ReCalculate();
	int		MaxWriteCmdCount();
	int		MinWriteCmdCount();
	int		TotalWriteCmdCount();
	int		ThreadCount();
	int		TotalReadCmdCount();
};


