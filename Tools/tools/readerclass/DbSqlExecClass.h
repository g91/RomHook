#pragma once
#define	DBNTWIN32		// must identify operating system environment
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <sql.h>
#include <sqlext.h>

#include <vector>
#include "readerclass.h"
#include "DBStruct/SqlBaseClass.h"

#include "../debuglog/errormessage.h"

using namespace std;
//--	------------------------------------------------------------------------------------------------------
//簡化處理 DB存取的物件
class MyDbSqlExecClass
{
	SqlBaseClass*		_sqlBase;

	vector<wchar_t*>	_wcTempBufList;
public:
	MyDbSqlExecClass( SqlBaseClass* sqlBase );
	~MyDbSqlExecClass(void);


	void	SqlBase( SqlBaseClass* sqlBase );

	bool	Close( );
	//sql命令
	bool	SqlCmd( const char* sqlcmd );
	bool	SqlCmd( const wchar_t* sqlcmd );
	//sql命令 只執行一行
	bool	SqlCmd_WriteOneLine( const char* sqlcmd , bool ignorecheck = false );

	//讀取
	bool	Read( );

	//資料連接
	bool	Bind( int column , int vartype , int varlen , void* varaddr );


	//讀取多比
	template< class Temp >
	bool	Bind( Temp& Data , ReaderClass<Temp>* Reader );

	bool	Reconnect();

	void	OutputSqlError( RETCODE rc );

	void	ClearTempBufList();

	vector<wchar_t*>&	wcTempBufList() { return _wcTempBufList; };

	SQLHSTMT GetStatementHandle() {return _sqlBase->Gethstmt();}
};

//--------------------------------------------------------------------------------------------------------
//實做 Template
//--------------------------------------------------------------------------------------------------------
template< class Temp >
bool	MyDbSqlExecClass::Bind( Temp& OutData , ReaderClass<Temp>* Reader )
{
	int		i;	
	map<string,ReadInfoStruct>*             ReadInfo ;
	map<string,ReadInfoStruct>::iterator    Iter;
	ReadInfo = Reader->ReadInfo();

	ClearTempBufList();
	//_wcTempBufList.push_back( NULL );
	while(  _wcTempBufList.size() < ReadInfo->size() )
		_wcTempBufList.push_back( NULL );


	for(    Iter  = ReadInfo->begin() , i = 1 ; 
		Iter != ReadInfo->end() ; 
		Iter++ , i++ )
	{
	//	_wcTempBufList.push_back( NULL );
		ReadInfoStruct *IDData = &(Iter->second);

		if( IDData->UserData & Def_Disabled_Select_Flag  )            
		{
			i--;
			//Print( LV1, "MyDbSqlExecClass::Bind", "MyDbSqlExecClass::Bind skipped because of Def_Disabled_Select_Flag\n" );
			continue;
		}
		
		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			//不處裡直接定址模式
			//Print( LV1, "MyDbSqlExecClass::Bind", "MyDbSqlExecClass::Bind failed because of ENUM_Direct_Address\n" );
			return false;
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			bool bindResult = false;
			switch(IDData->Type)
			{
			case ENUM_Type_FloatPoint:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_FLOAT  , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_IntPoint:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_LONG   , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_ShortPoint:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_SHORT  , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_CharString:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_CHAR   , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;

			case ENUM_Type_WCharString:
				_wcTempBufList[IDData->ID] = NEW wchar_t[ IDData->Size ];
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_WCHAR   , (SQLPOINTER)_wcTempBufList[IDData->ID] , IDData->Size*2  , NULL );
				break;

			case ENUM_Type_WCharStringBase:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_WCHAR   , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;


			case  ENUM_Type_BinaryData:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_BINARY , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;

			case ENUM_Type_BitPoint:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_BIT    , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_SmallDateTime:
				bindResult = Proxy_SQLBindCol( _sqlBase->Gethstmt() , i , SQL_C_FLOAT   , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;
			}   

			if(!bindResult)
			{
				Print( LV2, "MyDbSqlExecClass::Bind", "MyDbSqlExecClass::Bind failed\n" );
				return false;
			}
		}
	}

	return true;
};
