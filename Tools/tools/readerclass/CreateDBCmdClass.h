#pragma once
#include <string>
#include "ReaderClass/ReaderClass.h"
#include "BaseFunction/BaseFunction.h"
#include "smallobj/SmallObj.h"

#define Def_Disabled_Update_Flag 0x01
#define Def_Disabled_Insert_Flag 0x02

#pragma unmanaged
//-----------------------------------------------------------------------------------------------------------------
// Critical Safe class
//-----------------------------------------------------------------------------------------------------------------
template<class Temp>
class CreateDBCmdClass
{    
    ReaderClass<Temp>*  _Reader;   

    string  				_SQLSelectCmd;
    string  				_SQLInsertCmd;
    string  				_SQLUpDateCmd;

	bool					_NoString;		//把自串抽出

public:
    CreateDBCmdClass( ReaderClass<Temp>* Reader , char* TableName , bool IsNoString = true );
    string GetInsertStr( Temp* Date );
    string GetUpDateStr( Temp* Date , char* WhereCmd );
    string GetSelectStr( char* WhereCmd , int TopCount = 0 );
	//不輸出關於字串的物件 (通常為了把字串輸出到另外的表內)
//	void  NoString( bool Flag ){ _NoString = Flag; }
};
//-----------------------------------------------------------------------------------------------------------------
template<class Temp>
CreateDBCmdClass<Temp>::CreateDBCmdClass( ReaderClass<Temp>* Reader , char* TableName , bool IsNoString )
{ 
    _Reader = Reader; 
	_NoString = IsNoString;
    
    string  Str;
    bool    IsBegin;

    _Reader     = Reader;   

    //----------------SQL 字串產生 ---------------------------
    map<string,ReadInfoStruct>* ReadInfo = Reader->ReadInfo();
    map<string,ReadInfoStruct>::iterator Iter;

    _SQLSelectCmd = "";
    _SQLInsertCmd = "Insert ";
    _SQLInsertCmd = _SQLInsertCmd + TableName + "( ";

    IsBegin = true ;
    Str     = "";
    for( Iter = ReadInfo->begin() ; Iter != ReadInfo->end() ; Iter++ )
    {
		ReadInfoStruct* Info = &(Iter->second);
		if( _NoString != false )
		{
		
			switch( Info->Type )
			{
			case ENUM_Type_CharStringPoint:
			case ENUM_Type_TextDataPoint:
				continue;
			}
		}
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

		if( _NoString != false )
		{
			switch( Info->Type )
			{
			case ENUM_Type_CharStringPoint:
			case ENUM_Type_TextDataPoint:
				continue;
			}
		}

        if( IsBegin == false )
        {
            Str = Str + ",";            
        }
        IsBegin = false ;

        Str = Str + Iter->first;

    }
    _SQLInsertCmd = _SQLInsertCmd + Str + ") values( ";


}
//--------------------------------------------------------------------------------------------------------
template<class Temp>
string CreateDBCmdClass<Temp>::GetInsertStr( Temp* Data )
{
    char    Buf[0x20000];
//	_CritSect.Enter();
    map<string,ReadInfoStruct>*             ReadInfo ;
    map<string,ReadInfoStruct>::iterator    Iter;
    string SQLCmd = _SQLInsertCmd;
    ReadInfo = _Reader->ReadInfo();
    bool        BeginFlag = true;

    for(    Iter  = ReadInfo->begin() ; 
        Iter != ReadInfo->end() ; 
        Iter++  )
    {
        ReadInfoStruct *IDData = &(Iter->second);

        if( IDData->UserData & Def_Disabled_Insert_Flag )
            continue;

		if( _NoString != false )
		{
			switch( IDData->Type )
			{
			case ENUM_Type_CharStringPoint:
			case ENUM_Type_TextDataPoint:
				continue;
			}
		}
		
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
            case ENUM_Type_TimeCharString:
                {
                    char* Str = ((char*)(IDData->Point + int(Data)));
                    replace (  Str, Str+strlen(Str) , '\'' , '\"');
                    sprintf( Buf , "'%s'", Str );

                }                
                break;				
			case ENUM_Type_BinaryData:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " CAST( %s AS binary(%d) ) ", StringToSqlX( Str, IDData->Size , false ).c_str() , IDData->Size );
				}
				break;

			case ENUM_Type_CharString:
			case ENUM_Type_TextData:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " CAST( %s AS varchar(8000) ) ", StringToSqlX( Str , IDData->Size ).c_str() );
				}
				break;
			case ENUM_Type_WCharString:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					wchar_t	wcBuf[2048];					
					int Strlen = MultiByteToWideChar( CP_UTF8 , 0 , Str ,  -1 ,wcBuf , sizeof( wcBuf )  ) * 2;
					sprintf( Buf , " CAST( %s AS nvarchar(4000) ) ", StringToSqlX( (char*)wcBuf , Strlen , false ).c_str() );
				}
				break;
			case ENUM_Type_WCharStringBase:
				{					
					char* Str = ((char*)(IDData->Point + int(Data)));
					/*
					wchar_t	wcBuf[2048];					
					int Strlen = MultiByteToWideChar( CP_UTF8 , 0 , Str ,  -1 ,wcBuf , sizeof( wcBuf )  ) * 2;
					*/
					sprintf( Buf , " CAST( %s AS nvarchar(4000) ) ", StringToSqlX( Str , IDData->Size , false ).c_str() );
				}
				break;

 			case ENUM_Type_CharStringPoint:
				{
					char* Str = *((char**)(IDData->Point + int(Data)));
					sprintf( Buf , " CAST( %s As varchar(8000) ) ", StringToSqlX( Str , IDData->Size ).c_str() );
				}
				break;

			case ENUM_Type_TextDataPoint:
				{
					char* Str = *((char**)(IDData->Point + int(Data)));
					sprintf( Buf , " CAST( %s As Text ) ", StringToSqlX( Str , IDData->Size ).c_str() );
				}
				break;

			case ENUM_Type_BitPoint:
                {
                    bool Value = *((bool*)(IDData->Point + int(Data)));
					sprintf( Buf ,"%d" , Value  );

                }
				break;
			case ENUM_Type_SmallDateTime:
				{
					float Value = *((float*)(IDData->Point + int(Data)));
					sprintf( Buf ,"%f" , Value  );
				}break;   
            default:
                continue;
            }

            if( BeginFlag == false )
                SQLCmd = SQLCmd + ",";
            else 
                BeginFlag = false;

            SQLCmd = SQLCmd + Buf;            
        }                
    }
    SQLCmd = SQLCmd + ")";
//	_SQLCmd = SQLCmd;
//	_CritSect.Leave();
    return SQLCmd;
}
//--------------------------------------------------------------------------------------------------------
template<class Temp>
string CreateDBCmdClass<Temp>::GetUpDateStr( Temp* Data , char* WhereCmd )
{
//	_CritSect.Enter();
    char    Buf[0x20000];
    bool    Beginflag = true;

    map<string,ReadInfoStruct>*             ReadInfo ;
    map<string,ReadInfoStruct>::iterator    Iter;
    ReadInfo = _Reader->ReadInfo();
    string SQLCmd = _SQLUpDateCmd;

    for(    Iter  = ReadInfo->begin() ; 
        Iter != ReadInfo->end() ; 
        Iter++  )
    {
        ReadInfoStruct *IDData = &(Iter->second);
        
        string TempStr = Iter->first;

		if( IDData->UserData & Def_Disabled_Update_Flag )
			continue;

		if( _NoString != false )
		{
			switch( IDData->Type )
			{
			case ENUM_Type_CharStringPoint:
			case ENUM_Type_TextDataPoint:
				continue;
			}
		}

        if(IDData->AddressFlag == ENUM_Indirect_Address )
        {
            switch(IDData->Type)
            {
            case ENUM_Type_FloatPoint:
                {               
                    float Value = *(float*)(IDData->Point + int(Data));
                    bool Ret = CheckFloatAvlid( Value );
                    if( CheckFloatAvlid( Value ) == false )
                        Value = 0;
                    sprintf( Buf ," %s = %e " , Iter->first.c_str() , Value  );
                }break;

            case ENUM_Type_IntPoint:
                {
                    int Value = *((int*)(IDData->Point + int(Data)));
                    sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
                }break;              
            case ENUM_Type_ShortPoint:
                {                    
                    short Value = *((short*)(IDData->Point + int(Data)));
                    sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
                }                
                break;

            case ENUM_Type_TimeCharString:            
                {
                    char* Str = ((char*)(IDData->Point + int(Data)));
                    replace (  Str, Str+strlen(Str) , '\'' , '\"');
                    sprintf( Buf ," %s = '%s' " , Iter->first.c_str() , Str  );
				}
				break;
			case ENUM_Type_BinaryData:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " %s = CAST( %s AS binary(%d) ) ", Iter->first.c_str() , StringToSqlX( Str, IDData->Size , false ).c_str() , IDData->Size );
				}
                break;
			case ENUM_Type_TextData:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " %s ='%s' ", Iter->first.c_str() , StringToSqlStr( Str , IDData->Size ).c_str()  );
				}
				break;

            case ENUM_Type_CharString:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " %s = CAST( %s AS varchar(8000) ) ", Iter->first.c_str() , StringToSqlX( Str , IDData->Size ).c_str()  );
				}
				break;
			case ENUM_Type_WCharString:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));

					wchar_t	wcBuf[2048];					
					int Strlen = MultiByteToWideChar( CP_UTF8 , 0 , Str ,  -1 ,wcBuf , sizeof( wcBuf )  ) * 2;

					sprintf( Buf , " %s = CAST( %s AS nvarchar(4000) ) ", Iter->first.c_str() , StringToSqlX( (char*)wcBuf , Strlen , false ).c_str()  );
				}
				break;
			case ENUM_Type_WCharStringBase:
				{
					char* Str = ((char*)(IDData->Point + int(Data)));
					sprintf( Buf , " %s = CAST( %s AS nvarchar(4000) ) ", Iter->first.c_str() , StringToSqlX( Str , IDData->Size , false ).c_str()  );
				}
				break;

			case ENUM_Type_CharStringPoint:
				{
					char* Str = *((char**)(IDData->Point + int(Data)));

					sprintf( Buf , " %s = CAST( %s AS varchar(8000) ) ", Iter->first.c_str() , StringToSqlX( Str , IDData->Size ).c_str()  );
				}
				break;
			case ENUM_Type_TextDataPoint:
				{
					char* Str = *((char**)(IDData->Point + int(Data)));

					sprintf( Buf , " %s = CAST( %s AS Text ) ", Iter->first.c_str() , StringToSqlX( Str , IDData->Size ).c_str()  );
				}
				break;
			case ENUM_Type_BitPoint:
                {
					 int Value = *((bool*)(IDData->Point + int(Data)));
		             sprintf( Buf ," %s = %d " , Iter->first.c_str() , Value  );
                }
				break;
			case ENUM_Type_SmallDateTime:
				{
					float Value = *((float*)(IDData->Point + int(Data)));
					sprintf( Buf ," %s = %f " , Iter->first.c_str() , Value  );
				}break;   
            default:
                continue;
            }
            if( !Beginflag  )
            {                
                SQLCmd = SQLCmd + ",";
            }
            else
                Beginflag = false;

            SQLCmd = SQLCmd + Buf;            
        }                
    }

    SQLCmd = SQLCmd + WhereCmd ;
//	_SQLCmd = SQLCmd;
//	_CritSect.Leave();
    return SQLCmd;
}
//--------------------------------------------------------------------------------------------------------
template<class Temp>
string CreateDBCmdClass<Temp>::GetSelectStr( char* WhereCmd , int TopCount )
{
	string SQLCmd;
//	_CritSect.Enter();
    //產生 sql 命令( 利用 Reader產生)
	if( TopCount == 0 )
	{
		SQLCmd = "Select ";
	}
	else
	{
		char	Buf[256];
		sprintf( Buf , "Select Top %d " , TopCount );
		SQLCmd = Buf;
	}

	SQLCmd = SQLCmd+_SQLSelectCmd + WhereCmd;
	//_SQLCmd = SQLCmd;

//	_CritSect.Leave();
    return SQLCmd;
}
//--------------------------------------------------------------------------------------------------------
#pragma managed
