#include "DbSqlExecClass.h"
#include "debuglog/errormessage.h"

MyDbSqlExecClass::MyDbSqlExecClass( SqlBaseClass* sqlBase )
{
//	_IsOpen = false;
	SqlBase( sqlBase );
	//Close();
	RETCODE  rc = SQLCloseCursor( _sqlBase->Gethstmt() );
/*
	if( SQL_SUCCEEDED( rc )== false )
	{
		Print( LV4 , "MyDbSqlExecClass" , "SQLCloseCursor Return ERROR " );
		OutputSqlError( rc );		
		_sqlBase->Reconnect();
	}
	*/
}

MyDbSqlExecClass::~MyDbSqlExecClass(void)
{
	Close();
}

void	MyDbSqlExecClass::SqlBase( SqlBaseClass* sqlBase )
{
	_sqlBase = sqlBase;
}

bool	MyDbSqlExecClass::Reconnect()
{
	bool Ret = _sqlBase->Reconnect();
	return Ret;
}

//--------------------------------------------------------------------------------------------------------
//清除_wcTempBufList 的資料
void MyDbSqlExecClass::ClearTempBufList()
{
	for( int i = 0 ; i < (int)_wcTempBufList.size() ; i++ )
	{
		if( _wcTempBufList[i] != NULL )
			delete _wcTempBufList[i];
	}
	_wcTempBufList.clear();
}

bool	MyDbSqlExecClass::Close( )
{
	ClearTempBufList();
	__try
	{
		SQLCloseCursor( _sqlBase->Gethstmt() );
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	// Unlock SQL base object
//	_sqlBase->Unlock();

	return true;
}

bool	MyDbSqlExecClass::SqlCmd( const char* sqlcmd )
{
	
#ifdef _DEBUG
	g_pPrint->OutputToFile( LV5 , "SQLCMD" , sqlcmd );
#endif

	// Lock SQL base object
//	_sqlBase->Lock();

	if( _sqlBase->TrySQLExecDirect(5 , sqlcmd ) == false )
		return false;

	return true;
}

bool	MyDbSqlExecClass::SqlCmd( const wchar_t* sqlcmd )
{

	if( _sqlBase->TrySQLExecDirect(5 , sqlcmd ) == false )
		return false;

	return true;
}


//sql命令 只執行一行
bool	MyDbSqlExecClass::SqlCmd_WriteOneLine( const char* sqlcmd , bool ignorecheck )
{

#ifdef _DEBUG
	g_pPrint->OutputToFile( LV5 , "SQLCMD" , sqlcmd );
#endif
	// Lock SQL base object
	//_sqlBase->Lock();

	if( _sqlBase->TrySQLExecDirect(5 , sqlcmd , ignorecheck ) == false )
		return false;

	Close();
	return true;
}

void	MyDbSqlExecClass::OutputSqlError( RETCODE rc )
{
	if(rc == SQL_ERROR || rc == SQL_INVALID_HANDLE)
	{
		SQLCHAR		Sqlstate[6] = { 0, 0, 0, 0, 0, 0 };
		SQLINTEGER  NativeError;
		SQLTCHAR	ErrorMsg[512];
		SQLSMALLINT	TextLen;

		SQLGetDiagRec( SQL_HANDLE_STMT ,  _sqlBase->Gethstmt(), 1, Sqlstate, &NativeError, ErrorMsg, 512, &TextLen ); 

		//char*	Buf = new char [2048];
		char	Buf[2048];
		// 220002 表示select 不到資料
		if( stricmp( (char*)Sqlstate , "22002" ) != 0 )
		{
			sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n[ErrorCode]%s",rc ,Sqlstate , NativeError ,ErrorMsg );
			PrintToFile( LV5 , "SQLERR" , Buf );
		}
	}
}

//讀取
bool	MyDbSqlExecClass::Read( )
{
	RETCODE rc = SQL_ERROR;

	__try
	{
		rc = SQLFetch( _sqlBase->Gethstmt() );
	}	
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	if( SQL_SUCCEEDED( rc )== false )
	{
		/*
		if(rc == SQL_ERROR || rc == SQL_INVALID_HANDLE)
		{
			SQLCHAR		Sqlstate[6] = { 0, 0, 0, 0, 0, 0 };
			SQLINTEGER  NativeError;
			SQLTCHAR	ErrorMsg[512];
			SQLSMALLINT	TextLen;

			SQLGetDiagRec( SQL_HANDLE_STMT ,  _sqlBase->Gethstmt(), 1, Sqlstate, &NativeError, ErrorMsg, 512, &TextLen ); 

			//char*	Buf = new char [2048];
			char	Buf[2048];
			// 220002 表示select 不到資料
			if( stricmp( (char*)Sqlstate , "22002" ) != 0 )
			{
				sprintf( Buf , "[RETCODE]=%d [SqlState]=%s [NativeError]=%d \n[ErrorCode]%s",rc ,Sqlstate , NativeError ,ErrorMsg );
				g_pPrint->OutputToFile( LV5 , "SQLERR" , Buf );
			}
		}

		//g_pPrint->OutputToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		*/
		OutputSqlError( rc );
		return false;
	}

	return true;
}

/*
// 同 dbcoltype 的回傳質
int		MyDbSqlExecClass::ColType( const int column )
{
	return dbcoltype( _dbproc , column );
}

int		MyDbSqlExecClass::ColCount( )
{
	return dbnumcols( _dbproc );
}
*/

bool	MyDbSqlExecClass::Bind( int column , int vartype , int varlen , void* varaddr )
{
	//bool Ret;
	/*
	if( _IsOpen == false )
	{
		Ret = Exec();
		assert( Ret );
	}
	*/

	RETCODE rc = SQL_ERROR;
	
	__try
	{
		rc = SQLBindCol( _sqlBase->Gethstmt() , column , vartype  , (SQLPOINTER)varaddr , varlen  , NULL );
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	//Ret = ( dbbind( _dbproc , column , vartype , varlen , varaddr ) == SUCCEED );
	if( SQL_SUCCEEDED( rc ) == false )
	{
		assert( 0 );
		return false;
	}

	return true;
}
/*
//資料連接
bool	MyDbSqlExecClass::Bind( const char* ColName , int vartype , int varlen , LPBYTE varaddr )
{
	int column = ColOrder( ColName );
	bool Ret = ( dbbind( _dbproc , column , vartype , varlen , varaddr ) == SUCCEED );
	assert( Ret );

	return Ret;
}

/*
//取得攔位名稱
char*	MyDbSqlExecClass::ColName( const int column )
{
	return (char*)dbcolname( _dbproc , column );
}
//用欄位 位置取得欄位名稱
int		MyDbSqlExecClass::ColOrder( const char* name )
{
	for( int i = 0 ; i < ColCount() ; i++ )
	{
		if( _stricmp( name , ColName( i ) ) == 0 )
			return i;
	}
	return -1;
}
*/
//--------------------------------------------------------------------------------------------------------