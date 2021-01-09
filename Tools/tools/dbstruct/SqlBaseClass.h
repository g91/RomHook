#pragma once

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "smallobj/SmallObj.h"
#include "debuglog/errormessage.h"
//#define MYSQLSUCCESS(rc) ((rc==SQL_SUCCESS)||(rc==SQL_SUCCESS_WITH_INFO))

using namespace std;

extern bool Proxy_SQLBindCol(HSTMT stmt, SQLUSMALLINT colNum, int colType, SQLPOINTER targetValue, SQLINTEGER bufferLength, SQLINTEGER *StrLen_or_Ind);

class SqlBaseClass
{
	static vector< SqlBaseClass* >	_AllSqlBase;
	static vector< int >			_UnUseID;
	static MutilThread_CritSect		_Thread_CritSect;
	static PrintClass*				_Print;
public:	
	static bool Init( const char* OutputField , const char* OutputFileName );
	static bool Release();
	static vector< SqlBaseClass* > &AllSqlBase() { return _AllSqlBase;};
	static void	OnTimeProc();
protected:
	int			_id;
	string 		_server;
	string 		_dataBase;
	string 		_userID;
	string 		_password;

	RETCODE 	_retCode;     	// ODBC return code
	HENV		_henv;        	// Environment   
	HDBC		_hdbc;        	// Connection handle
	HSTMT		_hstmt;       	// Statement handle

	bool		_isReady;		//連線成

	CRITICAL_SECTION _objCS;

	char		_lastSqlCmd[128];
	char		_bkSqlCmd[128];
	unsigned	_lastProcTime;	//GetTickCount 

	bool	_TrySQLExecDirect( int Time , const char* sqlcmd , bool ignorecheck = false );

	int			_successCount;	//成命令的次數
public:


	SqlBaseClass( );
	~SqlBaseClass(void);
	bool	Disconnect( bool resetCredentials = true );
	bool	Connect( string server , string dataBase , string userID , string password );
	bool	Reconnect();
	void	ErrorOut( );

	HSTMT	Gethstmt();

	bool	TrySQLExecDirect( int Time , const char* sqlcmd , bool ignorecheck = false );
	bool	TrySQLExecDirect( int Time , const wchar_t* sqlcmd );

	bool	Lock();
	bool	Unlock();

	bool	ResetStmt();

	const char* LastSqlCmd() { return _lastSqlCmd; }
};

