#include "dbtransferclass.h"
#include "..\controllerclient\ControllerClient.h"

#pragma unmanaged
bool   DBTransferClass::_IsStopAll = false;			//停止所有的資料庫儲存
//--------------------------------------------------------------------------------------
/*
int DBTransferClass::_DB_Error(SqlBaseClass* sqlBase, int severity, int dberr, int oserr, char * dberrstr, char * oserrstr)
{
    if (dberrstr != NULL)
        printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

    if (oserr != DBNOERR)
        printf("Operating-system error:\n\t%s\n", oserrstr);

    if ((dbproc == NULL) ||	(DBDEAD(dbproc)))
        return(INT_EXIT);
    else
        return(INT_CANCEL);
}
//--------------------------------------------------------------------------------------
int DBTransferClass::_DB_Msg(SqlBaseClass* sqlBase, DBINT msgno, int msgstate, int severity, char * msgtext)
{
    printf("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
        msgno, msgstate, severity, msgtext);
    return(0);
}
*/
//--------------------------------------------------------------------------------------
DBTransferClass::DBTransferClass( const char* Server , const char* DB , const char* LoginID , const char* Password , int ThreadCount )
{
    _RunThreadCount     = 0;            //執行中的 Thread 數量
    _TotalRequestCount  = 0;
    _IsDestroy      = false;        //物件是否解構
	_IsConnectError = false;

    _Srv        = Server;
    _DB         = DB;
    _LoginID    = LoginID;
    _Password   = Password;
	_ThreadCount = ThreadCount;

	for( int i = 0 ; i < ThreadCount ; i++ )
	{
		deque< DBRequestEventStruct* > Temp;
		_DBWriteRequest.push_back( Temp );

		_hThread.push_back( 0 );
		_hEvent.push_back( 0 );
		_ThreadID.push_back( 0 );
	}

//    dberrhandle((DBERRHANDLE_PROC)_DB_Error);
//    dbmsghandle((DBMSGHANDLE_PROC)_DB_Msg  );


    for( int i = 0 ; i < ThreadCount ; i++ )
    {
        _hEvent[ i ] = CreateEvent( NULL , FALSE , FALSE , NULL );
        _hThread[ i ] = CreateThread( NULL , 0 , _ThreadFuction , (LPVOID) this , 0 , &_ThreadID[i] );

		//等待建立
		for( int j = 0 ; j < 10000 ; j++ )
		{
			if (_RunThreadCount == i+1 )
			{
				break;
			}
			if( _IsConnectError  )
			{
				if( _RunThreadCount == 0 )
				{
						Print( LV5, "DBTransferClass", "Init Error!! Server=%s DB=%s LoginID=%s" , Server , DB , LoginID );
						PrintToController( true, "DBTransferClass Init Error!! Please check database or ini setting\n(Server=%s DB=%s LoginID=%s)" , Server , DB , LoginID );
						return;
				}

				_IsConnectError = false;
				Print( LV5 , "DBTransferClass" , "retry connection!!" );
				i--;
				break;
			}
			Sleep( 10 );
		}


    }

//    printf( "\n DBTransferClass Init Error!! Server=%s DB=%s LoginID=%s" , Server , DB , LoginID );
	if (_RunThreadCount != ThreadCount )
	{
		Print( LV5, "DBTransferClass", "Init Error!! Server=%s DB=%s LoginID=%s" , Server , DB , LoginID );
		PrintToController( true, "DBTransferClass Init Error!! Please check database or ini setting\n(Server=%s DB=%s LoginID=%s)" , Server , DB , LoginID );
	}
}
//--------------------------------------------------------------------------------------
DBTransferClass::~DBTransferClass( )
{
    _IsDestroy = true;

    //等待執行序結束
    while( _RunThreadCount != 0 )
	{
		for( int i = 0 ; i < _ThreadCount ; i++ )
			SetEvent( _hEvent[ i ] );
        Sleep( 10 );
	}

    //要求處理的資料Queue
    while( _DBReadRequest.size() != 0 )
    {
        delete _DBReadRequest.back();
        _DBReadRequest.pop_back();
    }

    for( int i = 0 ; i < _ThreadCount ; i++ )
    {
        while( _DBWriteRequest[i].size() != 0 )
        {
            delete _DBWriteRequest[i].back();
            _DBWriteRequest[i].pop_back();
        }

        CloseHandle( _hEvent[i]  );
    }
    //------------------------------------------------------------------------------------------------
/*    if( ObjCount() <= 1  )
    {
        dbexit();
    }*/
}
//--------------------------------------------------------------------------------------
/*
void DBTransferClass::Read( DBEventCB EventFunc , void* UserObj , char* SQLCmd )
{
    DBRequestEventStruct* ReadEvent;
    ReadEvent = NEW DBRequestEventStruct;
    ReadEvent->UserObj = UserObj;
    ReadEvent->EventFunc = EventFunc;
    ReadEvent->SQLCmd = SQLCmd;


    {
        _Thread_CritSect.Enter();    
        _DBReadRequest.push_back( ReadEvent );
        _TotalRequestCount++;
        _Thread_CritSect.Leave();
    }
    

}
//--------------------------------------------------------------------------------------
//ID是用來決定使用那一個 Thread 做 Write 的動作，同一個資料由不同 thread 寫出會有問題 
void DBTransferClass::Write( int ThreadID , DBEventCB EventFunc , void* UserObj , char* SQLCmd )
{
    DBRequestEventStruct* UpDateEvent;
    UpDateEvent = NEW DBRequestEventStruct;
    UpDateEvent->UserObj = UserObj;
    UpDateEvent->EventFunc = EventFunc;
    UpDateEvent->SQLCmd = SQLCmd;

    ThreadID = ThreadID % _Def_DB_ThreadCount_ ;
    if( ThreadID < 0 )
        ThreadID = 0 ;

    {        
        _Thread_CritSect.Enter();    
        _DBWriteRequest[ ThreadID ].push_back( UpDateEvent );
        _TotalRequestCount++;
        _Thread_CritSect.Leave();
    }
}
*/
void DBTransferClass::Read( DBEventCB EventFunc , void* UserObj , ... )
{
    DBRequestEventStruct* ReadEvent;
    ReadEvent = NEW( DBRequestEventStruct );
    ReadEvent->UserObj = UserObj;
    ReadEvent->EventFunc = EventFunc;
    
    va_list		    	marker;
    ArgValueTypeENUM    type;
    char*               name;
    char                Buf[512];
    char*               value;

    va_start( marker , UserObj );
    while( 1 )
    {
        name = va_arg( marker , char* );
		if( name == NULL )
			break;

        type = ( ArgValueTypeENUM )va_arg( marker , int );
        switch( type )
        {
        case EM_ValueType_Double:
            sprintf( Buf , "%f" , va_arg( marker , double ) );
            value = Buf;
            break;
        case EM_ValueType_Int:
            sprintf( Buf , "%d" , va_arg( marker , int ) );
            value = Buf;
            break;
        case EM_ValueType_String:
            value = va_arg( marker , char* );
            break;
        }
        ReadEvent->Arg.PushValue( name , value );
    }

    va_end( marker );

    {
        _Thread_CritSect.Enter();    
        _DBReadRequest.push_back( ReadEvent );
        _TotalRequestCount++;
        _Thread_CritSect.Leave();
		SetEvent( _hEvent[ rand() % _ThreadCount ] );
    }


}
//--------------------------------------------------------------------------------------
//ID是用來決定使用那一個 Thread 做 Write 的動作，同一個資料由不同 thread 寫出會有問題 
void DBTransferClass::Write( int ThreadID , DBEventCB EventFunc , void* UserObj , ... )
{
    DBRequestEventStruct* UpDateEvent;
    UpDateEvent = NEW( DBRequestEventStruct );
    UpDateEvent->UserObj = UserObj;
    UpDateEvent->EventFunc = EventFunc;

    va_list		    	marker;
    ArgValueTypeENUM    type;
    char*               name;
    char*               value;
    char                Buf[256];

    va_start( marker , UserObj );
    while( 1 )
    {
        name = va_arg( marker , char* );
		if( name == NULL )
			break;
        type = ( ArgValueTypeENUM )va_arg( marker , int );
        switch( type )
        {
        case EM_ValueType_Double:
            sprintf( Buf , "%f" , va_arg( marker , double ) );
            value = Buf;
            break;
        case EM_ValueType_Int:
            sprintf( Buf , "%d" , va_arg( marker , int ) );
            value = Buf;
            break;
        case EM_ValueType_String:
            value = va_arg( marker , char* );
            break;
        }
        UpDateEvent->Arg.PushValue( name , value );
    }


    ThreadID = ThreadID % _ThreadCount ;
    if( ThreadID < 0 )
        ThreadID = 0 ;

    {        
        _Thread_CritSect.Enter();    
        _DBWriteRequest[ ThreadID ].push_back( UpDateEvent );
        _TotalRequestCount++;
        _Thread_CritSect.Leave();
        SetEvent( _hEvent[ ThreadID ] );
        
    }
}
//--------------------------------------------------------------------------------------
void DBTransferClass::SqlCmd( int ThreadID , DBEventCB EventFunc , void* UserObj )
{
    DBRequestEventStruct* UpDateEvent;
    UpDateEvent = NEW( DBRequestEventStruct );
    UpDateEvent->UserObj = UserObj;
    UpDateEvent->EventFunc = EventFunc;

    if( ThreadID < 0 )
	{
		ThreadID = 0 ;
		int MinCount = (int)_DBWriteRequest[0].size();
		for( int i = 1 ; i < _ThreadCount ; i++ )
		{
			if( MinCount > (int)_DBWriteRequest[i].size() )
			{
				MinCount = (int)_DBWriteRequest[i].size();
				ThreadID = i;
			}
		}     
	}
	else
	{
		ThreadID = ThreadID % _ThreadCount ;
	}

    {        
        _Thread_CritSect.Enter();    
        _DBWriteRequest[ ThreadID ].push_back( UpDateEvent );
        _TotalRequestCount++;
        _Thread_CritSect.Leave();
        SetEvent( _hEvent[ ThreadID ] );
    }
}

void _ThreadFuncCloseCursorHelper( SqlBaseClass &SqlBase )
{
	__try
	{
		SQLCloseCursor( SqlBase.Gethstmt() );
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}
}

//--------------------------------------------------------------------------------------
int  DBTransferClass::_ThreadFunc( )
{
	unsigned		ProcCount = 0;				
    int             ThreadID;
	SqlBaseClass	SqlBase;
    //----------------------------------------------------
    //登入 Thread 設定
    //----------------------------------------------------
    //**************************************************
    {//Begin CritSect
        _Thread_CritSect.Enter();
        ThreadID = _RunThreadCount;

		if( SqlBase.Connect( _Srv , _DB , _LoginID , _Password ) == false )
		{
			//printf( "\nDB Connect Error _Srv = %s _DB=%s _LoginID =%s _Password = %s" , _Srv.c_str() , _DB.c_str() , _LoginID.c_str() , _Password.c_str() );
			Print( LV5, "DBTransferClass", "Connect Error _Srv = %s _DB=%s _LoginID =%s" , _Srv.c_str() , _DB.c_str() , _LoginID.c_str() );
			SqlBase.ErrorOut();
			_IsConnectError = true;
			_Thread_CritSect.Leave();
			return 1;
		}
        _RunThreadCount++;
        _Thread_CritSect.Leave();
    }//end CritSect
    //**************************************************
    //----------------------------------------------------
    DBRequestEventStruct  *DBEvent;
    
	int	WriteEventCount = 0;
	int	LWriteEventCount = 0;
	unsigned LEventProcTime = 0;

    while( _IsDestroy == false )
    {
        DBEvent = NULL;

		//////////////////////////////////////////////////////////////////////////
		// 一分鐘內要求處理的數量都超過20個事件應出訊息
		_Thread_CritSect.Enter();
		{
			WriteEventCount = _DBWriteRequest[ ThreadID ].size();

			if( WriteEventCount > 20 )
			{
				if( LWriteEventCount < WriteEventCount )
				{
					unsigned ProcTime = timeGetTime();
					if( ProcTime - LEventProcTime > 60000 )
					{
						int PrintLevel = LV5;
						if( _DBWriteRequest[ ThreadID ].size() > 100 )
							PrintLevel = 6;

						Print( PrintLevel, "DBTransferClass", "Heavy Loading ... ThreadID=%d WriteRequest=%d ReadRequest=%d\n Last Sql Cmd='%s'" 
							, ThreadID , _DBWriteRequest[ ThreadID ].size() , _DBReadRequest.size() 
							, SqlBase.LastSqlCmd() );
						LEventProcTime = ProcTime;
					}
				}
			}
			LWriteEventCount = WriteEventCount;
		}
		_Thread_CritSect.Leave();
		//////////////////////////////////////////////////////////////////////////
        //Sleep( 1 );
        //-------------------------------------------------------------
        {//Begin CritSect
            _Thread_CritSect.Enter();
            if( _DBWriteRequest[ ThreadID ].size() != 0  )        
            {
                DBEvent = _DBWriteRequest[ ThreadID ].front();
                _DBWriteRequest[ ThreadID ].pop_front();
            }
            _Thread_CritSect.Leave();
        }//end CritSect
        //-------------------------------------------------------------

        if( DBEvent == NULL )
        {
            {//Begin CritSect
                _Thread_CritSect.Enter();
                if( _DBReadRequest.size() != 0 )
                {
                    DBEvent = _DBReadRequest.front();
                    _DBReadRequest.pop_front();
                }
                _Thread_CritSect.Leave();
            }//end CritSect
        }

		while( _IsStopAll )
		{
			Sleep( 1000 );
		}

        //  做 SQL CMD 的動做
        if( DBEvent == NULL )
        {
            WaitForSingleObject( _hEvent[ ThreadID ] , INFINITE );			
            continue;
        }

		_ThreadFuncCloseCursorHelper( SqlBase );

		DBEvent->EventFunc( &SqlBase , DBEvent->UserObj , DBEvent->Arg );

        _Thread_CritSect.Enter();
        _TotalRequestCount --;
        _Thread_CritSect.Leave();
        delete DBEvent;
        //-------------------------------------------------------------
		//重新要DB Stmt
		ProcCount++;
		if( ProcCount > 1000 )
		{
			ProcCount = 0;
			for( int i = 0 ; i < 50 ; i++ )
			{
				if( SqlBase.Reconnect() != false )
					break;
				Sleep( 1000 );
			}
		}
		

    } //End While
    //----------------------------------------------------
    {//Begin CritSect
        _Thread_CritSect.Enter();
        _RunThreadCount--;
        _Thread_CritSect.Leave();
    }//Begin CritSect
	//----------------------------------------------------

    return 0;
}
//--------------------------------------------------------------------------------------
//停止所有資料存取
void DBTransferClass::StopAll( )
{
	_IsStopAll = true;
}
//--------------------------------------------------------------------------------------

int		DBTransferClass::MaxWriteCmdCount()
{
	return (int)_MaxWriteCmdCount;
}
int		DBTransferClass::MinWriteCmdCount()
{
	return (int)_MinWriteCmdCount;
}

int		DBTransferClass::TotalWriteCmdCount()
{
	return (int)_TotalWriteCmdCount;
}
int		DBTransferClass::ThreadCount()
{
	return (int)_DBWriteRequest.size();
}

void		DBTransferClass::ReCalculate()
{
	_MaxWriteCmdCount = -1;
	_MinWriteCmdCount = -1;
	_TotalWriteCmdCount = 0;

	for( unsigned i = 0 ; i < _DBWriteRequest.size() ; i++ )
	{
		if( _MaxWriteCmdCount == -1 || _MaxWriteCmdCount < _DBWriteRequest[i].size() )
			_MaxWriteCmdCount = (int)_DBWriteRequest[i].size();

		if( _MinWriteCmdCount == -1 || _MinWriteCmdCount > _DBWriteRequest[i].size() )
			_MinWriteCmdCount = (int)_DBWriteRequest[i].size();

		_TotalWriteCmdCount += (int)_DBWriteRequest[i].size();
	}
}
int		DBTransferClass::TotalReadCmdCount( )
{
	return (int)_DBReadRequest.size();
}
#pragma managed