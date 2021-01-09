#ifndef __DBSTRUCTTRANSFERCLASS_H__
#define __DBSTRUCTTRANSFERCLASS_H__
#include "dbtransferclass.h"
#include "ReaderClass/ReaderClass.h"
#include "BaseFunction/BaseFunction.h"
#include "recyclebin/recyclebin.h"

using namespace std;

template< class Temp >
bool ReadDBDataByReader( Temp& OutData , HSTMT dbhstmt , ReaderClass< Temp >* Reader )
{
	int		i;	
	map<string,ReadInfoStruct>*             ReadInfo ;
	map<string,ReadInfoStruct>::iterator    Iter;
	ReadInfo = Reader->ReadInfo();

	for(    Iter  = ReadInfo->begin() , i = 1 ; 
		Iter != ReadInfo->end() ; 
		Iter++ , i++ )
	{

		ReadInfoStruct *IDData = &(Iter->second);

		if( IDData->UserData & Def_Disabled_Select_Flag  )            
			continue;


		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			//不處裡直接定址模式
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			bool bindResult = false;
			switch(IDData->Type)
			{
			case ENUM_Type_FloatPoint:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_FLOAT  , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_IntPoint:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_LONG   , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_ShortPoint:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_SHORT  , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_CharString:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_CHAR   , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;

			case ENUM_Type_WCharString:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_WCHAR  , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;

			case ENUM_Type_WCharStringBase:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_WCHAR  , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;

			case  ENUM_Type_BinaryData:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_BINARY , (SQLPOINTER)(IDData->Point + int(&OutData)) , IDData->Size  , NULL );
				break;
			case ENUM_Type_BitPoint:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_BIT    , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;

			case ENUM_Type_SmallDateTime:
				bindResult = Proxy_SQLBindCol( dbhstmt , i , SQL_C_FLOAT  , (SQLPOINTER)(IDData->Point + int(&OutData)) , SQL_C_DEFAULT  , NULL );
				break;
			}

			if(!bindResult)
				return false;
		}   
	}

	return true;
};


template<class Temp>
class DBStructTransferClass  
{
//***************************************************************************
//      資料結構定義
//***************************************************************************
typedef void  ( *DBReadEventCB ) ( vector<Temp>& , void* UserObj , char* WhereCmd , bool Result );
typedef void  ( *DBWriteEventCB )( Temp *Data , void* UserObj , char *WhereCmd , bool ResultOK );


typedef bool  ( *SQLCmdRequestEvent )( vector<Temp>& ,  SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );
typedef void  ( *SQLCmdReusltEventCB )( vector<Temp>& , void* UserObj , ArgTransferStruct& Arg , bool ResultOK );

//typedef void  ( *DBReadIndexEventCB )( int Index , void* UserObj , char *SQLCMD , bool ResultOK );
//typedef char* ( *DBInitStructInfo )( Temp* Obj );

public:
//--------------------------------------------------------------------------------------
struct DBSqlCmdInfoStruct 
{  
    DBStructTransferClass*  This;

	vector<Temp>			Data;
    void*                   UserObj;    
    SQLCmdRequestEvent      RequestFunc;
    SQLCmdReusltEventCB     ResultFunc;
    ArgTransferStruct       Arg;
    bool                    ResultOK;
	bool					IsTransation;
    void Init()
    {
        This        = NULL;
        UserObj     = NULL;
        RequestFunc = NULL;
		ResultFunc	= NULL;

        Arg.Clear();
        Data.clear();
        ResultOK    = false;
		IsTransation= false;
    };
};
//--------------------------------------------------------------------------------------
struct DBReadInfoStruct 
{  
    DBStructTransferClass*  This;

    void*                   UserObj;    
    DBReadEventCB           EventFunc;
    vector< Temp >          Data;
    string                  WhereCmd;
    bool                    ResultOK;

    void Init()
    {
        This        = NULL;
        UserObj     = NULL;
        EventFunc   = NULL;

        Data.clear();
        WhereCmd.clear();
        ResultOK    = false;
    };
};
//--------------------------------------------------------------------------------------
struct DBWriteInfoStruct 
{  
    DBStructTransferClass*  This;

    Temp                    Data;           //並不是除存當時的資料,資料有可能會被玩家改過
    void*                   UserObj;    
    string                  WhereCmd;
    DBWriteEventCB          EventFunc;
    bool                    ResultOK;

    void Init()
    {
        This        = NULL;
        UserObj     = NULL;
        EventFunc   = NULL;

//        Data        = NULL;
        WhereCmd.clear();
        ResultOK    = false;
    }
};
//--------------------------------------------------------------------------------------

//***************************************************************************

    static void ReadEventCB( SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );
    static void WriteEventCB( SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );
    static void SqlCmdEventCB( SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );
//    static void ReadIndexEventResultCB( HSTMT , void* UserObj ,  RETCODE Result );
    static void NullEventCB( SqlBaseClass* , void* UserObj , ArgTransferStruct& Arg );

    DBTransferClass*                    _DBConnect;
    ReaderClass< Temp >*                _Reader;    
    deque< DBReadInfoStruct* >         _ReadEventResult;
    deque< DBWriteInfoStruct* >        _WriteEventResult;
    deque< DBSqlCmdInfoStruct* >       _DBSqlCmdEventResult;

    RecycleBin< DBReadInfoStruct >      _AllocReadEvent;            //記錄所有配致的DBReadInfoStruct 
    RecycleBin< DBWriteInfoStruct >     _AllocWriteEvent;           
    RecycleBin< DBSqlCmdInfoStruct >    _AllocSqlCmdEvent;          

    MutilThread_CritSect                _Thread_CritSect;

    string  _SQLSelectCmd;
    string  _SQLInsertCmd;
    string  _SQLUpDateCmd;

    
public:
    DBStructTransferClass( DBTransferClass * , ReaderClass< Temp >* , char* TableName );
    ~DBStructTransferClass(void);


    //讀取資料 ，順序有可能錯亂
    void Read( DBReadEventCB CBFunc , void* UserObj , char* WhereCmd  );
    //寫入資訊 ，同一個id順序一定
    void Write( int ID , Temp* Data , DBWriteEventCB CBFunc , void* UserObj , char* WhereCmd = "");

    //直接已 SQL命令寫資料(不定行數的SQL 命令)
    void SqlCmd( int ID , SQLCmdRequestEvent RequestFunc , SQLCmdReusltEventCB ResultFunc , void* UserObj , ... );
	void SqlCmd_Transcation( int ID , SQLCmdRequestEvent RequestFunc , SQLCmdReusltEventCB ResultFunc , void* UserObj , ... );

    //直接已 SQL命令寫資料
    void SQLCMDWrite( int ID , DBWriteEventCB CBFunc , void* UserObj , char* SQL );

    void BeginTransaction( );
    void CommitTransaction( );

    //要求套跳出處理好的CallBack
    void Process( );

	DBTransferClass*        DBConnect()	{ return _DBConnect;};

	RETCODE ReadEventCBDataPush(SqlBaseClass* sqlBase, DBReadInfoStruct* ReadObj, Temp &TempData);
};
//--------------------------------------------------------------------------------------
template<class Temp>
void DBStructTransferClass<Temp>::NullEventCB( SqlBaseClass* sqlBase, void* UserObj , ArgTransferStruct& Arg )
{
 
}

template<class Temp>
RETCODE DBStructTransferClass<Temp>::ReadEventCBDataPush(SqlBaseClass* sqlBase, DBReadInfoStruct* ReadObj, Temp &TempData)
{
	RETCODE     result_code = SQL_ERROR;

	__try
	{
		for (result_code=SQLFetch(sqlBase->Gethstmt()); SQL_SUCCEEDED( result_code ); result_code=SQLFetch(sqlBase->Gethstmt()))
		{
			ReadObj->Data.push_back( TempData );
		}
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		ReadObj->ResultOK = false;
		ReadObj->Data.clear();

		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	return result_code;
}

//--------------------------------------------------------------------------------------
//Thread mode
template<class Temp>
void DBStructTransferClass<Temp>::ReadEventCB( SqlBaseClass* sqlBase , void* UserObj , ArgTransferStruct& Arg )
{
	SQLCloseCursor( sqlBase->Gethstmt() );
	//sqlBase->Lock();

	//HSTMT dbhstmt = sqlBase->Gethstmt();
	char*		SQLCMD = ( char * )Arg.GetString( "SqlCmd" );
//	RETCODE     result_code;
	Temp        TempData;

	DBReadInfoStruct*     ReadObj =(DBReadInfoStruct*)UserObj; 
	DBStructTransferClass*  This  = ReadObj->This;

//	map<string,ReadInfoStruct>*             ReadInfo ;
	map<string,ReadInfoStruct>::iterator    Iter;

#ifdef _DEBUG
	PrintToFile( LV5 , "SQLCMD" , SQLCMD );
#endif
	if( sqlBase->TrySQLExecDirect( 5 , SQLCMD ) != false )
		ReadObj->ResultOK = true;
	else
		ReadObj->ResultOK = false;
		
	if( ReadObj->ResultOK )
	{
		This->_Thread_CritSect.Enter();
			ReadDBDataByReader( TempData , sqlBase->Gethstmt() , This->_Reader );
		This->_Thread_CritSect.Leave();

		This->ReadEventCBDataPush(sqlBase, ReadObj, TempData);
/*
		__try
		{
			for (result_code=SQLFetch(sqlBase->Gethstmt()); SQL_SUCCEEDED( result_code ); result_code=SQLFetch(sqlBase->Gethstmt()))
			{
				ReadObj->Data.push_back( TempData );
			}
		}
		__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
		{
			ReadObj->ResultOK = false;
			ReadObj->Data.clear();

			g_pPrint->OutputToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		}
*/
	}


	{
		This->_Thread_CritSect.Enter();
		This->_ReadEventResult.push_back( ReadObj );		
		This->_Thread_CritSect.Leave();
	}
	
	SQLCloseCursor( sqlBase->Gethstmt() );
	//sqlBase->Unlock();
}
//--------------------------------------------------------------------------------------
template<class Temp>
void DBStructTransferClass<Temp>::WriteEventCB( SqlBaseClass* sqlBase , void* UserObj , ArgTransferStruct& Arg )
{
//	sqlBase->close();
	SQLCloseCursor( sqlBase->Gethstmt() );
	//sqlBase->Lock();

	char* SQLCMD = ( char * )Arg.GetString( "SqlCmd" );
#ifdef _DEBUG
	PrintToFile( LV5 , "SQLCMD" , SQLCMD );
#endif

	DBWriteInfoStruct*			WriteObj =(DBWriteInfoStruct*)UserObj; 
	DBStructTransferClass*      This  = WriteObj->This;

	if( sqlBase->TrySQLExecDirect(5 , SQLCMD ) != false )
		WriteObj->ResultOK = true;
	else
		WriteObj->ResultOK = false;

	{
		This->_Thread_CritSect.Enter();
		This->_WriteEventResult.push_back( WriteObj );
		This->_Thread_CritSect.Leave();
	}

	SQLCloseCursor( sqlBase->Gethstmt() );
	//sqlBase->Unlock();
}
//--------------------------------------------------------------------------------------
template<class Temp>
DBStructTransferClass<Temp>::DBStructTransferClass( DBTransferClass *DBConnect , ReaderClass< Temp >* Reader , char* TableName )
{
	/*
    string  Str;
    bool    IsBegin;

    _DBConnect      = DBConnect;
    _Reader         = Reader; 

	//表示不使用內定的Insert Update Del
	if( Reader == NULL )
		return;

    //----------------SQL 字串產生 ---------------------------
    map<string,ReadInfoStruct>* ReadInfo = Reader->ReadInfo();
    map<string,ReadInfoStruct>::iterator Iter;

    _SQLSelectCmd = "Select ";
    _SQLInsertCmd = "Insert ";

    _SQLInsertCmd = _SQLInsertCmd + TableName + "( ";

    Str     = "";
    IsBegin = true ;
    for(  Iter = ReadInfo->begin() ; Iter != ReadInfo->end() ; Iter++ )
    {
		ReadInfoStruct* Info = &(Iter->second);
		if( Info->UserData & Def_Disabled_Select_Flag )
			continue;

        if( IsBegin == false )
        {
            Str = Str + ",";            
        }
        IsBegin = false ;

        Str = Str + Iter->first;
    }

    _SQLSelectCmd = _SQLSelectCmd + Str + " From " + TableName + " ";
 
    _SQLUpDateCmd = "UPDATE "; 
    _SQLUpDateCmd = _SQLUpDateCmd + TableName + " SET ";

    //-----------------------------------------------------------------------------------------------------------------
    Str     = "";
    IsBegin = true ;
    for( Iter = ReadInfo->begin() ; Iter != ReadInfo->end() ; Iter++ )
    {
        ReadInfoStruct* Info = &(Iter->second);
        if( Info->UserData & Def_Disabled_Insert_Flag )
            continue;

        if( IsBegin == false )
        {
            Str = Str + ",";            
        }
        IsBegin = false ;

        Str = Str + Iter->first;

    }
    _SQLInsertCmd = _SQLInsertCmd + Str + ") values( ";
	*/
	
	//_NoString = IsNoString;

	string  Str;
	bool    IsBegin;

	_Reader			= Reader;   
	_DBConnect      = DBConnect;
	if( Reader == NULL )
		return;

	//----------------SQL 字串產生 ---------------------------
	map<string,ReadInfoStruct>* ReadInfo = Reader->ReadInfo();
	map<string,ReadInfoStruct>::iterator Iter;

	_SQLSelectCmd = "Select ";
	_SQLInsertCmd = "Insert ";
	;
	_SQLInsertCmd = _SQLInsertCmd + TableName + "( ";

	IsBegin = true ;
	Str     = "";
	for( Iter = ReadInfo->begin() ; Iter != ReadInfo->end() ; Iter++ )
	{
		ReadInfoStruct* Info = &(Iter->second);

		if( Info->UserData & Def_Disabled_Select_Flag )
			continue;

		if( IsBegin == false )
		{
			Str = Str + ",";            
		}
		IsBegin = false ;

		if( ENUM_Type_SmallDateTime == Info->Type )
		{
			Str = Str + "CAST(";
			Str = Str + Iter->first;
			Str = Str + " AS float )";
		}
		else
			Str = Str + Iter->first;
	}

	_SQLSelectCmd = _SQLSelectCmd + Str + " From " + TableName + " ";
	//-----------------------------------------------------------------------------------------------------------------
	_SQLUpDateCmd = "UPDATE "; 
	_SQLUpDateCmd = _SQLUpDateCmd + TableName + " SET ";

	//-----------------------------------------------------------------------------------------------------------------
	IsBegin = true ;
	Str     = "";
	for( Iter = ReadInfo->begin() ; Iter != ReadInfo->end() ; Iter++ )
	{
		ReadInfoStruct* Info = &(Iter->second);
		if( Info->UserData & Def_Disabled_Insert_Flag )
			continue;

		if( IsBegin == false )
		{
			Str = Str + ",";            
		}
		IsBegin = false ;

		Str = Str + Iter->first;

	}
	_SQLInsertCmd = _SQLInsertCmd + Str + ") values( ";
}
//--------------------------------------------------------------------------------------

template<class Temp>
DBStructTransferClass<Temp>::~DBStructTransferClass( )
{

}

//--------------------------------------------------------------------------------------
template<class Temp>
void DBStructTransferClass<Temp>::Read( DBReadEventCB CBFunc , void* UserObj , char* WhereCmd  )
{
    string  SQLCmd;
    DBReadInfoStruct* ReadInfo = _AllocReadEvent.NewObj();

    ReadInfo->Init();
    ReadInfo->UserObj   = UserObj;
    ReadInfo->EventFunc = CBFunc;
    ReadInfo->WhereCmd  = WhereCmd;
    ReadInfo->This      = this;

    //產生 sql 命令( 利用 Reader產生)
    SQLCmd = _SQLSelectCmd + WhereCmd;

    _DBConnect->Read( ReadEventCB , ReadInfo , "SqlCmd" , EM_ValueType_String , (char*)SQLCmd.c_str() , NULL );
	
}
//--------------------------------------------------------------------------------------
//寫入資訊 ，同一個id順序一定
template<class Temp>
void DBStructTransferClass<Temp>::Write( int ID , Temp* Data ,  DBWriteEventCB CBFunc , void* UserObj , char* WhereCmd )
{
    DBWriteInfoStruct*    WriteInfo = _AllocWriteEvent.NewObj();
    WriteInfo->Init();
    WriteInfo->UserObj      = UserObj;
    WriteInfo->EventFunc    = CBFunc;
    WriteInfo->This         = this;
    WriteInfo->Data         = *Data;
    WriteInfo->WhereCmd     = WhereCmd;

    char    Buf[256];
    string  SQLCmd;
	bool    BeginFlag = true;

    map<string,ReadInfoStruct>*             ReadInfo ;
    map<string,ReadInfoStruct>::iterator    Iter;

    {
        _Thread_CritSect.Enter();
        ReadInfo = _Reader->ReadInfo();
        _Thread_CritSect.Leave();
    }

    if( strlen( WhereCmd ) == 0 )
    {
        SQLCmd = _SQLInsertCmd;
        //map is thread safe for reading
        for(    Iter  = ReadInfo->begin() ; 
                Iter != ReadInfo->end() ; 
                Iter++  )
        {
            ReadInfoStruct *IDData = &(Iter->second);

            if( IDData->UserData & Def_Disabled_Insert_Flag  )            
                continue;

            if(IDData->AddressFlag == ENUM_Indirect_Address )
            {
                switch(IDData->Type)
                {
                case ENUM_Type_FloatPoint:
                    {               
                        float Value = *(float*)(IDData->Point + int(Data));
                        if( CheckFloatAvlid( Value ) == false )
                            Value = 0;
                        sprintf( Buf ,"%e" , Value  );
                    }break;

                case ENUM_Type_IntPoint:
                    {
                        int Value = *((int*)(IDData->Point + int(Data)));
                        sprintf( Buf ,"%d" , Value  );
                    }break;              
                case ENUM_Type_ShortPoint:
                    {                    
                        short Value = *((short*)(IDData->Point + int(Data)));
                        sprintf( Buf ,"%d" , Value  );
                    }                
                    break;
				case ENUM_Type_BitPoint:
					{
						bool	Value = *((bool*)(IDData->Point + int(Data)));
						sprintf( Buf ,"%d" , Value  );
					}
					break;
                case ENUM_Type_CharString:
                    {
                        char* Str = ((char*)(IDData->Point + int(Data)));
                        sprintf( Buf , "'%s'", Str );
                    }                
                    break;
				case ENUM_Type_BinaryData:
					{
						char* Str = ((char*)(IDData->Point + int(Data)));
						sprintf( Buf , " CAST( %s AS binary(%d) ) ", StringToSqlX( Str, IDData->Size , false ).c_str() , IDData->Size );
					}
					break;
				case ENUM_Type_SmallDateTime:
					{
						float Value = *((int*)(IDData->Point + int(Data)));
						sprintf( Buf , "%f", Value );
					}
					break;


                default:
                    continue;
                }

                if( BeginFlag == false )
                {
                    SQLCmd = SQLCmd + ",";
                }
                else
                    BeginFlag = false;

                SQLCmd = SQLCmd + Buf;            
            }                
        }
        SQLCmd = SQLCmd + ")";
    }
    else
    {
        SQLCmd = _SQLUpDateCmd;
        //map is thread safe for reading
        for(    Iter  = ReadInfo->begin() ; 
            Iter != ReadInfo->end() ; 
            Iter++  )
        {
            ReadInfoStruct *IDData = &(Iter->second);

            if( IDData->UserData & Def_Disabled_Update_Flag  )            
                continue;

            if(IDData->AddressFlag == ENUM_Indirect_Address )
            {
                switch(IDData->Type)
                {
                case ENUM_Type_FloatPoint:
                    {               
                        float Value = *(float*)(IDData->Point);
                        if( CheckFloatAvlid( Value ) == false )
                            Value = 0;
                        sprintf( Buf ," %s = %e " , Iter->first.c_str() , Value  );
                    }break;

                case ENUM_Type_IntPoint:
                    {
                        int Value = *((int*)(IDData->Point));
                        sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
                    }break;              
                case ENUM_Type_ShortPoint:
                    {                    
                        short Value = *((short*)(IDData->Point));
                        sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
                    }                
                    break;
				case ENUM_Type_BitPoint:
					{                    
						bool	Value = *((bool*)(IDData->Point));
						sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
					}                
					break;
                case ENUM_Type_CharString:
                    {
                        char* Str = ((char*)(IDData->Point));
                        sprintf( Buf ," %s = '%s' " , Iter->first.c_str() , Str  );
                    }                
                    break;
				case ENUM_Type_BinaryData:
					{
						char* Str = ((char*)(IDData->Point));
						sprintf( Buf , " %s = CAST( %s AS binary(%d) ) ", Iter->first.c_str() , StringToSqlX( Str, IDData->Size , false ).c_str() , IDData->Size );
					}
					break;
				case ENUM_Type_SmallDateTime:
					{
						float Value = *((int*)(IDData->Point + int(Data)));
						sprintf( Buf , "%s = %f ", Iter->first.c_str() , Value );
					}
					break;
                default:
                    continue;
                }
                if( BeginFlag == false )
                {
                    SQLCmd = SQLCmd + ",";
                }
                else
                    BeginFlag = false;

                SQLCmd = SQLCmd + Buf;            
            }                
        }
        SQLCmd = SQLCmd + WhereCmd ;
    }

    _DBConnect->Write( ID , WriteEventCB , WriteInfo , "SqlCmd" , EM_ValueType_String , (char*)SQLCmd.c_str() , NULL );
}
//--------------------------------------------------------------------------------------
//要求套跳出處理好的CallBack
template<class Temp>
void DBStructTransferClass<Temp>::Process( )
{   

    while( 1 )
    {
        DBSqlCmdInfoStruct* DBResult;
        {
            _Thread_CritSect.Enter();
            if( _DBSqlCmdEventResult.size() == 0 )
            {
                _Thread_CritSect.Leave();
                break;
            }

            DBResult = _DBSqlCmdEventResult.front();
            _DBSqlCmdEventResult.pop_front();
            _Thread_CritSect.Leave();
        }
		if( DBResult->ResultFunc )
			DBResult->ResultFunc( DBResult->Data , DBResult->UserObj , DBResult->Arg , DBResult->ResultOK );

        _AllocSqlCmdEvent.DeleteObj( DBResult );
    }

    while ( 1 )    
    {        
        DBReadInfoStruct* DBResult;
        {
            _Thread_CritSect.Enter();
            if( _ReadEventResult.size() == 0 )
            {
                _Thread_CritSect.Leave();
                break;
            }

            DBResult = _ReadEventResult.front();
            _ReadEventResult.pop_front();
            _Thread_CritSect.Leave();
        }
		if( DBResult->EventFunc )
			DBResult->EventFunc( DBResult->Data , DBResult->UserObj , (char*)DBResult->WhereCmd.c_str() , DBResult->ResultOK );

        _AllocReadEvent.DeleteObj( DBResult );
    }

    while ( 1 )    
    {        
        DBWriteInfoStruct* DBResult;
        {
            _Thread_CritSect.Enter();
            if( _WriteEventResult.size() == 0 )
            {
                _Thread_CritSect.Leave();
                break;
            }

            DBResult = _WriteEventResult.front();
            _WriteEventResult.pop_front();
            _Thread_CritSect.Leave();
        }
		if( DBResult->EventFunc )
			DBResult->EventFunc( &(DBResult->Data) , DBResult->UserObj , (char*)DBResult->WhereCmd.c_str() , DBResult->ResultOK );

        _AllocWriteEvent.DeleteObj( DBResult );
    }
}
//--------------------------------------------------------------------------------------
template<class Temp>
void DBStructTransferClass<Temp>::BeginTransaction( )
{
    _DBConnect->Write( 0 , NullEventCB , NULL , "BEGIN TRANSACTION"   );
}
//--------------------------------------------------------------------------------------
template<class Temp>
void DBStructTransferClass<Temp>::CommitTransaction( )
{
    _DBConnect->Write( 0 , NullEventCB , NULL , "COMMIT TRANSACTION"   );
}
//--------------------------------------------------------------------------------------
template<class Temp>
void    DBStructTransferClass<Temp>::SqlCmd_Transcation( int ID , SQLCmdRequestEvent RequestFunc , SQLCmdReusltEventCB ResultFunc , void* UserObj , ... )
{
	DBSqlCmdInfoStruct* CmdInfo = _AllocSqlCmdEvent.NewObj();
	if( CmdInfo == NULL )
	{
		printf( "\n SqlCmd 記憶體要求有問題??????? " );
		return;
	}
	CmdInfo->Init();

	CmdInfo->This       = this;
	CmdInfo->UserObj    = UserObj;    
	CmdInfo->RequestFunc= RequestFunc ;
	CmdInfo->ResultFunc = ResultFunc;
	CmdInfo->IsTransation= true;

	va_list		    	marker;
	ArgValueTypeENUM    type;
	char*               name;
	char                Buf[256];
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
			sprintf( Buf , "%e" , va_arg( marker , double ) );
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
		CmdInfo->Arg.PushValue( name , value );
	}

	_DBConnect->SqlCmd( ID , SqlCmdEventCB , CmdInfo );
}
//--------------------------------------------------------------------------------------
template<class Temp>
void    DBStructTransferClass<Temp>::SqlCmd( int ID , SQLCmdRequestEvent RequestFunc , SQLCmdReusltEventCB ResultFunc , void* UserObj , ... )
{
    DBSqlCmdInfoStruct* CmdInfo = _AllocSqlCmdEvent.NewObj();
    if( CmdInfo == NULL )
    {
        printf( "\n SqlCmd 記憶體要求有問題??????? " );
        return;
    }
	CmdInfo->Init();

    CmdInfo->This       = this;
    CmdInfo->UserObj    = UserObj;    
    CmdInfo->RequestFunc= RequestFunc ;
    CmdInfo->ResultFunc = ResultFunc;

    va_list		    	marker;
    ArgValueTypeENUM    type;
    char*               name;
    char                Buf[256];
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
            sprintf( Buf , "%e" , va_arg( marker , double ) );
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
        CmdInfo->Arg.PushValue( name , value );
    }
    
    _DBConnect->SqlCmd( ID , SqlCmdEventCB , CmdInfo );
}
//--------------------------------------------------------------------------------------
static bool	ST_SqlCmd_WriteOneLine( SqlBaseClass* sqlBase , const char* sqlcmd )
{
	//sqlBase->Lock();

#ifdef _DEBUG
	PrintToFile( LV5 , "SQLCMD" , sqlcmd );
#endif
	if( sqlBase->TrySQLExecDirect(5 , sqlcmd ) == false )
	{
		//sqlBase->Unlock();

		return false;
	}
	
	__try
	{
		SQLCloseCursor( sqlBase->Gethstmt() );
	}
	__except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
	{
		PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!" );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	//sqlBase->Unlock();

	return true;
}

template<class Temp>
void    DBStructTransferClass<Temp>::SqlCmdEventCB( SqlBaseClass* sqlBase , void* UserObj , ArgTransferStruct& Arg )
{
   DBSqlCmdInfoStruct* CmdInfo = (DBSqlCmdInfoStruct*)UserObj;

   //如果是交易模式
   if( CmdInfo->IsTransation != false )
   {
	   g_CritSect()->Enter();
	   ST_SqlCmd_WriteOneLine( sqlBase , "BEGIN TRANSACTION" );
   }

   CmdInfo->ResultOK = CmdInfo->RequestFunc( CmdInfo->Data , sqlBase , CmdInfo->UserObj , CmdInfo->Arg );

   if( CmdInfo->IsTransation != false )
   {
	   ST_SqlCmd_WriteOneLine( sqlBase , "COMMIT TRANSACTION" );
	   g_CritSect()->Leave();
   }

   DBStructTransferClass* This = CmdInfo->This;

   {
       This->_Thread_CritSect.Enter();
       This->_DBSqlCmdEventResult.push_back( CmdInfo );
       This->_Thread_CritSect.Leave();
   }

   __try
   {
	   SQLCloseCursor( sqlBase->Gethstmt() );
   }
   __except ( GetExceptionCode() == STATUS_ACCESS_VIOLATION )
   {
	   PrintToFile( LV5 , "ODBC ERROR", "CRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!-1" );
	   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCRITICAL ODBC DRIVER ERROR! FUCK ME ALREADY! FUCK YOU TOO!-1\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   }

   // Unlock SQL base object
 //  sqlBase->Unlock();
}
//--------------------------------------------------------------------------------------
//直接已 SQL命令寫資料
template<class Temp>
void DBStructTransferClass<Temp>::SQLCMDWrite( int ID , DBWriteEventCB CBFunc , void* UserObj , char* SQL )
{
    DBWriteInfoStruct*    WriteInfo = _AllocWriteEvent.NewObj();
    WriteInfo->Init();
    WriteInfo->UserObj      = UserObj;
    WriteInfo->EventFunc    = CBFunc;
    WriteInfo->This         = this;
    //WriteInfo->Data         = NULL;
    WriteInfo->WhereCmd     = SQL;

    _DBConnect->Write( ID , WriteEventCB , WriteInfo ,  "SqlCmd" , EM_ValueType_String , SQL , NULL   );
}
#endif //__DB_STRUCTTRANSFERCLASS_H__