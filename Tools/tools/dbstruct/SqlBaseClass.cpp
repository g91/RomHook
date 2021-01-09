#include "SqlBaseClass.h"

#include "malloc/MyAlloc.h"
#include "smallobj/SmallObj.h"

vector< SqlBaseClass* > SqlBaseClass::_AllSqlBase;
vector< int >			SqlBaseClass::_UnUseID;
MutilThread_CritSect    SqlBaseClass::_Thread_CritSect;
PrintClass*				SqlBaseClass::_Print = NULL;
bool	LegalCheckChar( char ch )
{
	if( ch >= 'a' && ch <='z' )
		return true;
	if( ch >= 'A' && ch <='Z' )
		return true;
	if( ch >= '0' && ch <='9' )
		return true;
	if( ch == '_' )
		return true;
	return false;
}
bool	LegalCheckCharW( wchar_t ch )
{
	if( ch >= L'a' && ch <=L'z' )
		return true;
	if( ch >= L'A' && ch <=L'Z' )
		return true;
	if( ch >= L'0' && ch <=L'9' )
		return true;
	if( ch == L'_' )
		return true;
	return false;
}

bool	SqlCmdCheck( const char* sqlcmd )
{
	//sqlcmd »y¥yÀË¬d
	char* disableStr[] = { "insert" , "update" , "delete" , "truncate" , "alter" , "drop" };
	string str = sqlcmd;
	std::transform( str.begin(), str.end(), str.begin(), ::tolower );
	if( str.size() > 6 )
	{
		for( int i = 0 ; i < 6 ; i++ )
		{
			const char* pos = str.c_str() + 5;
			int  cmdlen = strlen( disableStr[i] );
			while( 1 )
			{
				pos = strstr( pos , disableStr[i] );
				if( pos == NULL )
					break;

				if(		LegalCheckChar( *(pos - 1) ) == false 
					&&	LegalCheckChar( *(pos + cmdlen) ) == false )
					return false;

				pos += cmdlen;
			}
		}
	}
	return true;
}

bool	SqlCmdCheckW( const wchar_t* sqlcmd )
{
	//sqlcmd »y¥yÀË¬d
	wchar_t* disableStr[] = { L"insert" , L"update" , L"delete" , L"truncate" , L"alter" , L"drop" };
	wstring str = sqlcmd;
	std::transform( str.begin(), str.end(), str.begin(), ::tolower );
	if( str.size() > 6 )
	{
		for( int i = 0 ; i < 6 ; i++ )
		{
			const wchar_t* pos = str.c_str() + 5;
			int  cmdlen = wcslen( disableStr[i] );
			while( 1 )
			{
				pos = wcsstr( pos , disableStr[i] );
				if( pos == NULL )
					break;

				if(		LegalCheckCharW( *(pos - 1) ) == false 
					&&	LegalCheckCharW( *(pos + cmdlen) ) == false )
					return false;

				pos += cmdlen;
			}
		}
	}
	return true;
}

bool SqlBaseClass::Init( const char* OutputField , const char* OutputFileName )
{
	if( _Print != NULL )
		return false;
	
	char FileName[512];
	sprintf( FileName , "DBErr_%s" , OutputFileName );
	_Print = NEW PrintClass;
	_Print->SetOutputFieldName( OutputField );
	_Print->SetOutputFileName( FileName );

	_Print->OutputToFile( "#Server Start#" );
	return true;
}

bool SqlBaseClass::Release( )
{
	if( _Print != NULL )
	{
		delete _Print;
		_Print = NULL;
	}
	return true;
}

bool Proxy_SQLBindCol(HSTMT stmt, SQLUSMALLINT colNum, int colType, SQLPOINTER targetValue, SQLINTEGER bufferLength, SQLINTEGER *StrLen_or_Ind)
{
	__try
	{
		SQLBindCol(stmt, colNum, colType, targetValue, bufferLength, StrLen_or_Ind);
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		return false;
	}

	return true;
}

SqlBaseClass::SqlBaseClass( )
{
	
	_Thread_CritSect.Enter();
	if( _UnUseID.size() == 0 )
	{
		_id = _AllSqlBase.size();
		_AllSqlBase.push_back( this );
	}
	else
	{
		_id = _UnUseID.back();
		_UnUseID.pop_back();
		_AllSqlBase[ _id ] = this;
	}
	_Thread_CritSect.Leave();

	_retCode 		= 0;     // ODBC return code
	_henv	 		= 0;     // Environment   
	_hdbc	 		= 0;     // Connection handle
	_hstmt	 		= 0;     // Statement handle
	_lastProcTime	= 0;
	_successCount	= 0;
	_lastSqlCmd[0]	= 0;
	_bkSqlCmd[0]	= 0;
	InitializeCriticalSection(&_objCS);
}
bool	SqlBaseClass::ResetStmt()
{
	if( _isReady != false )
		return false;

	SQLFreeStmt(_hstmt,SQL_DROP);
	_retCode = SQLAllocStmt(_hdbc,&_hstmt);

	return true;
}

bool	SqlBaseClass::Connect( string server , string dataBase , string userID , string password )
{
	if( _isReady != false )
		return false;

	_server		= server;
	_dataBase	= dataBase;
	_userID		= userID;
	_password	= password;
	_isReady	= false;


	SQLAllocEnv(&_henv);
	SQLAllocConnect(_henv,&_hdbc);


	char	ConnectStr[256];
	sprintf( ConnectStr , "DRIVER=SQL Server;UID=%s;DATABASE=%s;SERVER=%s;PWD=%s" , _userID.c_str() , _dataBase.c_str() , _server.c_str() , _password.c_str() );

	_retCode=SQLDriverConnect(_hdbc, NULL 
		, (SQLCHAR*)ConnectStr
		, SQL_NTS
		, NULL 
		, 0 
		, NULL
		, SQL_DRIVER_COMPLETE );

	// Deallocate handles, display error message, and exit.
	if (!SQL_SUCCEEDED(_retCode))
	{
		/*
		SQLCHAR		Sqlstate[6] = { 0, 0, 0, 0, 0, 0 };
		SQLINTEGER  NativeError;
		SQLTCHAR	ErrorMsg[512];
		SQLSMALLINT	TextLen;

		SQLGetDiagRec( SQL_HANDLE_DBC  ,  _hdbc, 1, Sqlstate, &NativeError, ErrorMsg, 512, &TextLen ); 
		char	Buf[2048];
		sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n[ErrorCode]%s",_retCode ,Sqlstate , NativeError ,ErrorMsg );
		g_pPrint->OutputToFile( LV5 , "SQLERR" , Buf );
*/
		SQLFreeEnv(_henv);
		SQLFreeConnect(_hdbc);
		
		return false;
	}
	int		timeOut = 60*5;
	SQLSetConnectAttr( _hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)&timeOut, 0);

	_retCode = SQLAllocStmt(_hdbc,&_hstmt);

	_isReady = true;
	return true;
}

bool	SqlBaseClass::Reconnect()
{
	Disconnect(false);
	SQLAllocEnv(&_henv);
	SQLAllocConnect(_henv,&_hdbc);

	char	ConnectStr[256];
	sprintf( ConnectStr , "DRIVER=SQL Server;UID=%s;DATABASE=%s;SERVER=%s;PWD=%s" , _userID.c_str() , _dataBase.c_str() , _server.c_str() , _password.c_str() );

	_retCode=SQLDriverConnect(_hdbc, NULL 
		, (SQLCHAR*)ConnectStr
		, SQL_NTS
		, NULL 
		, 0 
		, NULL
		, SQL_DRIVER_COMPLETE );

	// Deallocate handles, display error message, and exit.
	if (!SQL_SUCCEEDED(_retCode))
	{
		SQLFreeEnv(_henv);
		SQLFreeConnect(_hdbc);
		return false;
	}
	int		timeOut = 60*5;
	SQLSetConnectAttr( _hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)&timeOut, 0);

	_retCode = SQLAllocStmt(_hdbc,&_hstmt);

	_successCount	= 0;
	_isReady = true;
	return true;
}


SqlBaseClass::~SqlBaseClass(void)
{
	Disconnect( );

	DeleteCriticalSection(&_objCS);

	_Thread_CritSect.Enter();
	{
		_UnUseID.push_back( _id );
		_AllSqlBase[ _id ] = NULL;
	}
	_Thread_CritSect.Leave();
}

void SqlBaseClass::ErrorOut( )
{
	unsigned char szSQLSTATE[10];
	SDWORD nErr;
	unsigned char msg[SQL_MAX_MESSAGE_LENGTH+1];
	SWORD cbmsg;

	while( SQL_SUCCEEDED( SQLError(0,0,_hstmt,szSQLSTATE,&nErr,msg,sizeof(msg),&cbmsg) ) )
	{
		printf( "Error: SQLSTATE=%s,Native error=%ld,msg='%s' SuccessCmd=%d",szSQLSTATE,nErr,msg,_successCount );
	}
}

bool	SqlBaseClass::Disconnect(  bool resetCredentials )
{
	if( _isReady == false )
		return false;

	SQLFreeStmt(_hstmt,SQL_DROP);
	SQLDisconnect(_hdbc);
	SQLFreeConnect(_hdbc);
	SQLFreeEnv(_henv);
	_isReady = false;

	_retCode = 0;     // ODBC return code
	_henv	 = 0;     // Environment   
	_hdbc	 = 0;     // Connection handle
	_hstmt	 = 0;     // Statement handle

	if( resetCredentials )
	{
		_server.clear();
		_dataBase.clear();
		_userID.clear();
		_password.clear();
	}

	return true;
}

HSTMT	SqlBaseClass::Gethstmt( )
{
	return _hstmt;
}


bool	SqlBaseClass::TrySQLExecDirect( int Time , const char* sqlcmd , bool ignorecheck )
{
	_lastProcTime = GetTickCount();
	bool Ret = _TrySQLExecDirect( Time , sqlcmd , ignorecheck );
	_lastProcTime = 0;	
	//////////////////////////////////////////////////////////////////////////
	if( _Print != NULL  && Ret == false )
		_Print->OutputToFile( LV5 , "DB Write Error" , sqlcmd );
	//////////////////////////////////////////////////////////////////////////
	return Ret;
}

bool	SqlBaseClass::_TrySQLExecDirect( int Time , const char* sqlcmd , bool ignorecheck )
{
	//////////////////////////////////////////////////////////////////////////	
	if(ignorecheck == false && SqlCmdCheck(sqlcmd) == false)
	{
		Print( LV5 , "_TrySQLExecDirect" , "illegal sql cmd = %s" , sqlcmd );
		return true;
	}	
	//////////////////////////////////////////////////////////////////////////
	Lock();
	memcpy( _bkSqlCmd , _lastSqlCmd , sizeof(_lastSqlCmd) );
	strncpy( _lastSqlCmd , sqlcmd , sizeof(_lastSqlCmd) );
	_lastSqlCmd[ sizeof(_lastSqlCmd) - 1 ] = 0;
	Unlock();
	
	for( int procCount = 0 ; procCount <= Time; procCount++ )
	{
		RETCODE result_code = SQL_ERROR;

		__try
		{
			result_code = SQLExecDirect( Gethstmt() , (SQLCHAR*)sqlcmd	, SQL_NTS );
		}
		__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
		{
			result_code = SQL_INVALID_HANDLE;

			PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		}

		BOOL forceReconnect = FALSE;

		if( SQL_SUCCEEDED( result_code ) )
		{
			break;
		}
		else
		{

			PrintToFile( LV5 , "SQL ERROR", sqlcmd );

			
			if(result_code == SQL_INVALID_HANDLE)
			{
				printf("[SQLBaseClass] INFO: Error is SQL_INVALID_HANDLE, Forcing re-connection.\n");
				forceReconnect = TRUE;
			}
			else
			{
				//--------------------------------------------------------------------------------------
				SQLCHAR		Sqlstate[6] = { 0, 0, 0, 0, 0, 0 };
				SQLINTEGER  NativeError;
				SQLCHAR	ErrorMsg[512];
				SQLSMALLINT	TextLen;

				RETCODE retCode = SQL_ERROR;

				__try
				{
					retCode = SQLGetDiagRec( SQL_HANDLE_STMT ,  Gethstmt(), 1, Sqlstate, &NativeError, ErrorMsg, 512, &TextLen ); 
				}
				__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
				{
					forceReconnect = TRUE;

					PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				}

				if(retCode != SQL_ERROR)
				{
					char*	Buf = NEW char [2048 + strlen(sqlcmd)];
					sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n\t[BkSqlCmd]%s \n\t[SQLCMD]%s \n\t[ErrorCode]%s [SuccessCmd]%d"
									,result_code,Sqlstate , NativeError , _bkSqlCmd ,sqlcmd , ErrorMsg , _successCount );
					PrintToFile( LV5 , "SQLERR" , Buf );


					delete[] Buf;

					if( procCount < Time )
					{
//						char*	Buf = NEW char [2048 + strlen(sqlcmd)];
//						sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n[SQLCMD]%s \n[ErrorCode]%s [SuccessCmd]%d",result_code,Sqlstate , NativeError ,sqlcmd , ErrorMsg , _successCount );
//						g_pPrint->OutputToFile( LV5 , "SQLERR" , Buf );
//						delete[] Buf;
					}
					else
					{
//						char*	Buf = NEW char [2048 + strlen(sqlcmd)];
//						sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n[SQLCMD]%s \n[ErrorCode]%s",result_code,Sqlstate , NativeError ,sqlcmd , ErrorMsg );
//						g_pPrint->OutputToFile( LV5 , "SQLERR" , Buf );
//						delete[] Buf;

						//Unlock();
						return false;
					}

					// Check SQL state against our list of reconnectable SQL states
					const char *reconnectableSQLStates[] = { "08S00", "08S01", "08S02", "08S03", "08003", "HY000", "HYT01", NULL };

					for(int i = 0; reconnectableSQLStates[i] != NULL; ++i)
					{
						if(memcmp(Sqlstate, reconnectableSQLStates, 5) == 0)
						{
							printf("[SQLBaseClass] INFO: Error state is re-connectable, Forcing re-connection.\n");
							forceReconnect = TRUE;
							break;
						}
					}
				}

				// If we still do not force reconnection, do further connection tests
				if(!forceReconnect)
				{
					// Test for connection alive
					SQLUSMALLINT maxDriverConnections;
					RETCODE getInfoRetCode = SQL_ERROR;

					__try
					{
						getInfoRetCode = SQLGetInfo(Gethstmt(), SQL_MAX_DRIVER_CONNECTIONS, (SQLPOINTER) &maxDriverConnections, sizeof(SQLUSMALLINT), NULL);
					}
					__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
					{
						PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
					}

					if(SQL_SUCCEEDED(getInfoRetCode))
					{
						//Unlock();
						return false;
					}

					forceReconnect = TRUE;
				}
			}			
		}

		if(forceReconnect)
		{
			for( int i = 0 ; ; i++ )
			{
				Sleep( 1000 );			
				bool Ret = Reconnect();	
				if( Ret != false )
				{
					PrintToFile( LV5 , "SQLERR" , "\n[SQLBaseClass] INFO: Connection re-established." );
					printf("\n[SQLBaseClass] INFO: Connection re-established.\n\n");
					break;
				}

				if( i > 50 )
				{
					PrintToFile( LV5 , "SQLERR" , "TrySQLExecDirect Reconnect error" );
					MessageBoxA( NULL , "TrySQLExecDirect Reconnect error" , "Reconnect" , MB_OK );
					//Unlock();
					return false;
				}
			}
		}
	}

	//Unlock();
	return true;
}
bool	SqlBaseClass::TrySQLExecDirect( int Time , const wchar_t* sqlcmd )
{
	//Lock();
	if( SqlCmdCheckW( sqlcmd ) == false )
	{
		Print( LV5 , "TrySQLExecDirectW" , "illegal sql cmd=%s" , sqlcmd );
		return true;
	}


	for( int procCount = 0 ; procCount <= Time; procCount++ )
	{
		RETCODE result_code = SQL_ERROR;

		__try
		{
			result_code = SQLExecDirectW( Gethstmt() , (SQLWCHAR*)sqlcmd	, SQL_NTS );
		}
		__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
		{
			result_code = SQL_INVALID_HANDLE;

			PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		}

		BOOL forceReconnect = FALSE;

		if( SQL_SUCCEEDED( result_code ) )
		{
			break;
		}		
		

		if(forceReconnect)
		{
			for( int i = 0 ; ; i++ )
			{
				Sleep( 1000 );			
				bool Ret = Reconnect();	
				if( Ret != false )
				{
					PrintToFile( LV5 , "SQLERR" , "\n[SQLBaseClass] INFO: Connection re-established." );
					printf("\n[SQLBaseClass] INFO: Connection re-established.\n\n");
					break;
				}

				if( i > 50 )
				{
					PrintToFile( LV5 , "SQLERR" , "TrySQLExecDirect Reconnect error" );
					MessageBoxA( NULL , "TrySQLExecDirect Reconnect error" , "Reconnect" , MB_OK );
					//Unlock();
					return false;
				}
			}
		}
	}

	//Unlock();
	return true;
}

bool SqlBaseClass::Lock()
{
	/*
	BOOL enterCSResult;
	int i = 0;


	if( TryEnterCriticalSection( &_objCS ) == 0 )
	{
		enterCSResult = false;
		while(!(enterCSResult = TryEnterCriticalSection( &_objCS )))
		{
			if(i > 10)
			{
				break;
			}

			Sleep(100);
			++i;
		}

	}

	return enterCSResult;
*/
	EnterCriticalSection( &_objCS );
	return true;
}

bool SqlBaseClass::Unlock()
{
	LeaveCriticalSection( &_objCS );
	return true;
}


void	SqlBaseClass::OnTimeProc( )
{

	static unsigned LastCheckTime = 0;
	unsigned NowTime = timeGetTime();

	if( NowTime - LastCheckTime < 5000 )
		return;

	LastCheckTime = NowTime;

	for( unsigned i = 0 ; i < _AllSqlBase.size() ; i++ )
	{
		SqlBaseClass* sqlBase = _AllSqlBase[i];		
		if(		sqlBase == NULL 
			||	sqlBase->_lastProcTime == 0 
			||	NowTime - sqlBase->_lastProcTime < 3000 )
			continue;

		int DelayProcTime = NowTime - sqlBase->_lastProcTime;
		if( DelayProcTime > 0 )
		{
			sqlBase->Lock();
			Print( LV5 , "SqlBaseClass::OnTimeProc" , "ProcTime=%d Cmd=%s" , DelayProcTime , sqlBase->_lastSqlCmd );
			sqlBase->Unlock();
		}
		
	}

}