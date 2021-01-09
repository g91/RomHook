#ifndef	__READERCLASS_H___
#define __READERCLASS_H___

#include <algorithm>
#include "malloc/myalloc.h"

#pragma	warning (disable:4311)
#pragma	warning (disable:4312)
#pragma warning (disable:4949)
#pragma warning (disable:4996)
#pragma unmanaged

#define Def_Disabled_Update_Flag 0x01
#define Def_Disabled_Insert_Flag 0x02
#define Def_Disabled_Select_Flag 0x04
//------------------------------------------------------------------------------------
//			�����ƨ��o������
//------------------------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>
//------------------------------------------------------------------------------------
//���ЧΦ�
enum ReadInfoTypeENUM
{
	ENUM_Type_FloatPoint	= 0 ,
	ENUM_Type_IntPoint			,
	ENUM_Type_ShortPoint		,
	ENUM_Type_CharPoint			,
	ENUM_Type_BitPoint			,
	ENUM_Type_SmallDateTime		,


	ENUM_Type_CharString		,
	ENUM_Type_WCharString		,		//WChar �� Utf8
	ENUM_Type_WCharStringBase	,		//WChar�榡
    ENUM_Type_BinaryData		,       //�D�n����Ʈw�Ϊ��n�]�wSize
    ENUM_Type_TextData          ,
    ENUM_Type_TimeCharString    ,

	

	ENUM_Type_FloatPointPoint   ,
	ENUM_Type_IntPointPoint		,
	ENUM_Type_ShortPointPoint	,
	ENUM_Type_CharPointPoint	,
	ENUM_Type_CharStringPoint	,
	ENUM_Type_TextDataPoint		,

    //ENUM_Type_StringPoint	    ,		//std String ����


    ENUM_Type_Float     	    ,
    ENUM_Type_Int			    ,
    ENUM_Type_Short		        ,
    ENUM_Type_Char			    ,

	ENUM_Type_Max				,

	ENUM_Type_FORCE_DWORD   = 0x7fffffff ,
};
//------------------------------------------------------------------------------------
enum ReadInfoAddrTypeENUM
{
	ENUM_Direct_Address		= 0	,				//�����w�}
	ENUM_Indirect_Address		,				//�����w�}

	ENUM_Addr_FORCE_DWORD   = 0x7fffffff ,
};
//------------------------------------------------------------------------------------
using	namespace  std;

//�nŪ����ƭn�]�w����T
struct ReadInfoStruct
{
	int						ID;
	string					ValueName;
	int 					Point;
	ReadInfoTypeENUM		Type;	
	ReadInfoAddrTypeENUM	AddressFlag;
    int                     UserData;
    int                     Size;                   //��Ƥj�p
};
//------------------------------------------------------------------------------------
template<class Temp>
class ReaderClass  
{
	map<string,ReadInfoStruct>					_ReadInfo;
    vector<string>								_ArgList;
	vector< ReadInfoStruct >					_ListByType[ENUM_Type_Max];
public:
	ReaderClass(){};
	~ReaderClass();
	
    map<string,ReadInfoStruct>*  ReadInfo(){ return &_ReadInfo;};
	ReadInfoStruct*	GetColumnInfo( string ValueName );

	//�Ҧ��ˬd
	bool	CheckStringType( string ValueName );


	//�Ʀr�Ҧ�
	int		Read( Temp *Obj ,  string ValueName );
	double	Read_Double( Temp *Obj ,  string ValueName );
//	bool	Write( Temp *Obj ,  string ValueName , float Value );
//	bool	Write( Temp *Obj ,  string ValueName , int Value );
	bool	Write( Temp *Obj ,  string ValueName , double Value );

	//�r��Ҧ�
	char*	ReadStr( Temp *Obj ,  string ValueName );
	bool	WriteStr( Temp *Obj ,  string ValueName , const char*	Str );

	vector< ReadInfoStruct >&	ListByType( ReadInfoTypeENUM Type ){return _ListByType[Type];};

	//��Ƴ]�w �p�G�H����ƫh�^�ǥ���
	//�� SetData ( �s���W�� , ���� , ���Ы��A(int short ...)  , �����ζ����w�}�Ҧ� )
	bool SetData( string ValueName , const void* Point , ReadInfoTypeENUM Type , int Size = 0 , ReadInfoAddrTypeENUM Flag = ENUM_Indirect_Address , int UserData = 0  );

	//Wchar��utf-8�B�z
	void	TransferWChartoUTF8( Temp *Obj , vector< wchar_t*> Data );
};
//------------------------------------------------------------------------------------
template<class Temp>
ReaderClass<Temp>::~ReaderClass()
{
	/*
	map<string,ReadInfoStruct>::iterator	Iter;
	for( Iter = _ReadInfo.begin() ; Iter != _ReadInfo.end() ; Iter++ )
	{
		if( Iter->second.wcTempBuf != NULL )
			delete Iter->second.wcTempBuf;
	}
	*/
}
//------------------------------------------------------------------------------------
template<class Temp>
bool ReaderClass<Temp>::SetData(string	ValueName,const void* Point, ReadInfoTypeENUM Type , int Size , ReadInfoAddrTypeENUM Flag , int UserData )
{

	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	ReadInfoStruct NewData;
	
	NewData.Point		= (int)Point;
	NewData.Type		= Type;
	NewData.AddressFlag = Flag;
    NewData.UserData    = UserData;
    NewData.Size        = Size;
	NewData.ValueName	= ValueName;
	NewData.ID			= (int)_ReadInfo.size();
/*
	//�p�G��WCHAR���榡�h�ഫ
	if( Type == ENUM_Type_WCharString )
	{
		if( Size == 0 )
			return false;
//		NewData.wcTempBuf = NEW wchar_t[Size*2];
	}
	/*
	else if( Type == ENUM_Type_CharString || Type == ENUM_Type_TextData )
	{
		if( Size == 0 )
			return false;
	}
*/

	_ReadInfo[ ValueName ] = NewData;
    _ArgList.push_back( ValueName );

	_ListByType[ Type ].push_back( _ReadInfo[ ValueName ] );
	return true;
}
//------------------------------------------------------------------------------------

//Ū���
template<class Temp>
int ReaderClass<Temp>::Read( Temp *Obj , string	ValueName )
{

	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;

	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return 0;


	ReadInfoStruct *IDData;
	IDData = &( Iter->second );


	if(IDData->AddressFlag == ENUM_Direct_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			return (int)*((float*)IDData->Point);
			
		case ENUM_Type_IntPoint:
			return (int)*((int*)IDData->Point);

		case ENUM_Type_ShortPoint:
			return (int)*((short*)IDData->Point);

		case ENUM_Type_CharPoint:
			return (int)*((char*)IDData->Point);

		case ENUM_Type_BitPoint:
			return (int)*((bool*)IDData->Point);

		case ENUM_Type_SmallDateTime:
			return (int)*((float*)IDData->Point);

		case ENUM_Type_FloatPointPoint:
			return (int)**((float**)IDData->Point);

		case ENUM_Type_IntPointPoint:
			return (int)**((int**)IDData->Point);

		case ENUM_Type_ShortPointPoint:
			return (int)**((short**)IDData->Point);

		case ENUM_Type_CharPointPoint:
			return (int)**((char**)IDData->Point);

//		case ENUM_Type_CharPointPoint:
//			return **((wchar_t**)IDData->Point);


		}
	}
	else if(IDData->AddressFlag == ENUM_Indirect_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			return (int)*((float*)(IDData->Point + int(Obj)));
			
		case ENUM_Type_IntPoint:
			return (int)*((int*)(IDData->Point + int(Obj)));

		case ENUM_Type_SmallDateTime:
			return (int)*((float*)(IDData->Point + int(Obj)));


		case ENUM_Type_ShortPoint:
			return (int)*((short*)(IDData->Point + int(Obj)));
			
		case ENUM_Type_CharPoint:
			return (int)*((char*)(IDData->Point + int(Obj)));
		case ENUM_Type_BitPoint:
			return (int)*((bool*)(IDData->Point + int(Obj)));

		case ENUM_Type_FloatPointPoint:
			return (int)**((float**)(IDData->Point + int(Obj)));

		case ENUM_Type_IntPointPoint:
			return (int)**((int**)(IDData->Point + int(Obj)));

		case ENUM_Type_ShortPointPoint:
			return (int)**((short**)(IDData->Point + int(Obj)));

		case ENUM_Type_CharPointPoint:
			return (int)**((char**)(IDData->Point + int(Obj)));
		}
	}

	return 0;
}

//Ū���
template<class Temp>
double ReaderClass<Temp>::Read_Double( Temp *Obj , string	ValueName )
{

	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;

	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return 0;


	ReadInfoStruct *IDData;
	IDData = &( Iter->second );


	if(IDData->AddressFlag == ENUM_Direct_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			return (double)*((float*)IDData->Point);

		case ENUM_Type_IntPoint:
			return (double)*((int*)IDData->Point);

		case ENUM_Type_ShortPoint:
			return (double)*((short*)IDData->Point);

		case ENUM_Type_CharPoint:
			return (double)*((char*)IDData->Point);

		case ENUM_Type_BitPoint:
			return (double)*((bool*)IDData->Point);

		case ENUM_Type_SmallDateTime:
			return (double)*((float*)IDData->Point);

		case ENUM_Type_FloatPointPoint:
			return (double)**((float**)IDData->Point);

		case ENUM_Type_IntPointPoint:
			return (double)**((int**)IDData->Point);

		case ENUM_Type_ShortPointPoint:
			return (double)**((short**)IDData->Point);

		case ENUM_Type_CharPointPoint:
			return (double)**((char**)IDData->Point);

			//		case ENUM_Type_CharPointPoint:
			//			return **((wchar_t**)IDData->Point);


		}
	}
	else if(IDData->AddressFlag == ENUM_Indirect_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			return (double)*((float*)(IDData->Point + int(Obj)));

		case ENUM_Type_IntPoint:
			return (double)*((int*)(IDData->Point + int(Obj)));

		case ENUM_Type_SmallDateTime:
			return (double)*((float*)(IDData->Point + int(Obj)));


		case ENUM_Type_ShortPoint:
			return (double)*((short*)(IDData->Point + int(Obj)));

		case ENUM_Type_CharPoint:
			return (double)*((char*)(IDData->Point + int(Obj)));
		case ENUM_Type_BitPoint:
			return (double)*((bool*)(IDData->Point + int(Obj)));

		case ENUM_Type_FloatPointPoint:
			return (double)**((float**)(IDData->Point + int(Obj)));

		case ENUM_Type_IntPointPoint:
			return (double)**((int**)(IDData->Point + int(Obj)));

		case ENUM_Type_ShortPointPoint:
			return (double)**((short**)(IDData->Point + int(Obj)));

		case ENUM_Type_CharPointPoint:
			return (double)**((char**)(IDData->Point + int(Obj)));
		}
	}

	return 0;
}
//------------------------------------------------------------------------------------
//Ū���
template<class Temp>
bool ReaderClass<Temp>::Write( Temp *Obj , string ValueName , double Value)
{
	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;

	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return false;

	ReadInfoStruct *IDData;
	IDData = &( Iter->second );

	if(IDData->AddressFlag == ENUM_Direct_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			*((float*)IDData->Point) = Value;
			break;			

		case ENUM_Type_IntPoint:
			*((int*)IDData->Point)   = (int)Value;
			break;

		case ENUM_Type_ShortPoint:
			*((short*)IDData->Point) = (int)Value;
			break;

		case ENUM_Type_CharPoint:
			*((char*)IDData->Point)	 = (int)Value;
			break;

		case ENUM_Type_BitPoint:
			*((bool*)IDData->Point)	 = Value != 0;
			break;

		case ENUM_Type_SmallDateTime:
			*((float*)IDData->Point)   = (float)Value;
			break;

		case ENUM_Type_FloatPointPoint:
			**((float**)IDData->Point) = (float)Value;
			break;

		case ENUM_Type_IntPointPoint:
			**((int**)IDData->Point)   = (int)Value;
			break;

		case ENUM_Type_ShortPointPoint:
			**((short**)IDData->Point) = (int)Value;
			break;

		case ENUM_Type_CharPointPoint:
			**((char**)IDData->Point)	 = (int)Value;
			break;

		default:
			return false;
		}
	}
	else if(IDData->AddressFlag == ENUM_Indirect_Address)
	{
		switch(IDData->Type)
		{
		case ENUM_Type_FloatPoint:
			*((float*)(IDData->Point + int(Obj))) = (float)Value;
			break;

		case ENUM_Type_IntPoint:
			*((int*)(IDData->Point + int(Obj)))   = (int)Value;
			break;

		case ENUM_Type_ShortPoint:
			*((short*)(IDData->Point + int(Obj))) = (int)Value;
			break;
			
		case ENUM_Type_CharPoint:
			*((char*)(IDData->Point + int(Obj)))  = (int)Value;
			break;
		case ENUM_Type_BitPoint:
			*((bool*)(IDData->Point + int(Obj)))  = Value != 0;
			break;
		case ENUM_Type_SmallDateTime:
			*((float*)(IDData->Point + int(Obj)))   = (float)Value;
			break;


		case ENUM_Type_FloatPointPoint:
			**((float**)(IDData->Point + int(Obj))) = (float)Value;
			break;

		case ENUM_Type_IntPointPoint:
			**((int**)(IDData->Point + int(Obj)))   = (int)Value;
			break;

		case ENUM_Type_ShortPointPoint:
			**((short**)(IDData->Point + int(Obj))) = (int)Value;
			break;

		case ENUM_Type_CharPointPoint:
			**((char**)(IDData->Point + int(Obj)))  = (int)Value;
			break;

		default:
			return false;
		}
	}

	return true;
}
/*
template<class Temp>
bool ReaderClass<Temp>::Write( Temp *Obj , string ValueName , int Value)
{
    //_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

    map<string,ReadInfoStruct>::iterator Iter;

    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return false;

    ReadInfoStruct *IDData;
    IDData = &( Iter->second );

    if(IDData->AddressFlag == ENUM_Direct_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            *((float*)IDData->Point) = (float)Value;
            break;			

        case ENUM_Type_IntPoint:
            *((int*)IDData->Point)   = (int)Value;
            break;

        case ENUM_Type_ShortPoint:
            *((short*)IDData->Point) = (int)Value;
            break;

        case ENUM_Type_CharPoint:
            *((char*)IDData->Point)	 = (int)Value;
            break;
		case ENUM_Type_BitPoint:
			*((bool*)IDData->Point)	 = Value != 0;
			break;
		case ENUM_Type_SmallDateTime:
			*((float*)IDData->Point)   = (float)Value;
			break;


        case ENUM_Type_FloatPointPoint:
            **((float**)IDData->Point) = (float)Value;
            break;

        case ENUM_Type_IntPointPoint:
            **((int**)IDData->Point)   = (int)Value;
            break;

        case ENUM_Type_ShortPointPoint:
            **((short**)IDData->Point) = (int)Value;
            break;

        case ENUM_Type_CharPointPoint:
            **((char**)IDData->Point)	 = (int)Value;
            break;

        default:
            return false;
        }
    }
    else if(IDData->AddressFlag == ENUM_Indirect_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            *((float*)(IDData->Point + int(Obj))) = (float)Value;
            break;

        case ENUM_Type_IntPoint:
            *((int*)(IDData->Point + int(Obj)))   = (int)Value;
            break;

        case ENUM_Type_ShortPoint:
            *((short*)(IDData->Point + int(Obj))) = (int)Value;
            break;

        case ENUM_Type_CharPoint:
            *((char*)(IDData->Point + int(Obj)))  = (int)Value;
            break;

		case ENUM_Type_BitPoint:
			*((bool*)(IDData->Point + int(Obj)))  = Value != 0;
			break;

		case ENUM_Type_SmallDateTime:
			*((float*)(IDData->Point + int(Obj)))   = (float)Value;
			break;


        case ENUM_Type_FloatPointPoint:
            **((float**)(IDData->Point + int(Obj))) = (float)Value;
            break;

        case ENUM_Type_IntPointPoint:
            **((int**)(IDData->Point + int(Obj)))   = (int)Value;
            break;

        case ENUM_Type_ShortPointPoint:
            **((short**)(IDData->Point + int(Obj))) = (int)Value;
            break;

        case ENUM_Type_CharPointPoint:
            **((char**)(IDData->Point + int(Obj)))  = (int)Value;
            break;

        default:
            return false;
        }
    }

    return true;
}
*/
//------------------------------------------------------------------------------------
//�r��Ҧ�
template<class Temp>
char* ReaderClass<Temp>::ReadStr( Temp *Obj , string ValueName )
{
	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;

	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return NULL;

	ReadInfoStruct *IDData;
	IDData = &( Iter->second );

	if(     IDData->Type == ENUM_Type_CharString 
		||	IDData->Type == ENUM_Type_WCharString 
//		||	IDData->Type == ENUM_Type_WCharStringBase 
        ||  IDData->Type == ENUM_Type_BinaryData    )
	{	//return NULL;

		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			return ((char*)IDData->Point);
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			return ((char*)(IDData->Point + int(Obj)));
		}
	}
	else if(	IDData->Type == ENUM_Type_CharStringPoint 
			||	IDData->Type == ENUM_Type_TextDataPoint		)
	{
		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			return *((char**)IDData->Point);
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			return *((char**)(IDData->Point + int(Obj)));
		}
	}

	return NULL;
}
//------------------------------------------------------------------------------------

template<class Temp>
bool ReaderClass<Temp>::WriteStr( Temp *Obj , string ValueName , const char*	Str )
{
	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;

	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return false;

	ReadInfoStruct *IDData;
	IDData = &( Iter->second );

	if(     IDData->Type == ENUM_Type_CharString 
		||	IDData->Type == ENUM_Type_WCharString 
//		||	IDData->Type == ENUM_Type_WCharStringBase 
        ||  IDData->Type == ENUM_Type_TextData   )
	{

		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			//strncpy( ((char*)IDData->Point) , Str , IDData->Size );
			strcpy( ((char*)IDData->Point) , Str );
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			//strncpy( ((char*)(IDData->Point + int(Obj) )) , Str , IDData->Size );
			strcpy( ((char*)(IDData->Point + int(Obj) )) , Str );
		}
		return true;
	}
	else if(	IDData->Type == ENUM_Type_CharStringPoint
			||	IDData->Type == ENUM_Type_TextDataPoint	)
	{
		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			//strncpy( *((char**)IDData->Point) , Str , IDData->Size );
			strcpy( *((char**)IDData->Point) , Str );
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			//strncpy( *((char**)(IDData->Point + int(Obj) )) , Str , IDData->Size );
			strcpy( *((char**)(IDData->Point + int(Obj) )) , Str );
		}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------------
template<class Temp>
ReadInfoStruct* ReaderClass<Temp>::GetColumnInfo( string ValueName )
{	
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;
	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return NULL;

	return &(Iter->second);
}

//�Ҧ��ˬd
template<class Temp>
bool ReaderClass<Temp>::CheckStringType( string ValueName )
{
	//_strlwr( (char*)ValueName.c_str() );
	std::transform( ValueName.begin(), ValueName.end(), ValueName.begin(), ::tolower );

	map<string,ReadInfoStruct>::iterator Iter;
	Iter = _ReadInfo.find( ValueName );

	if( Iter == _ReadInfo.end() )
		return false;

	ReadInfoStruct *IDData;
	IDData = &( Iter->second );

	if(		IDData->Type != ENUM_Type_CharString 
//		&&  IDData->Type != ENUM_Type_WCharStringBase
//		&&	IDData->Type == ENUM_Type_WCharString 
//		&&  IDData->Type != ENUM_Type_CharStringPoint
		&&	IDData->Type != ENUM_Type_TextData
		&&	IDData->Type != ENUM_Type_TextDataPoint		)

		return false;

	return true;
}

//Wchar��utf-8�B�z
template<class Temp>
void ReaderClass<Temp>::TransferWChartoUTF8( Temp *Obj , vector<wchar_t*> Data )
{
	vector< ReadInfoStruct >& ReadInfoList = _ListByType[ ENUM_Type_WCharString ];
	char*	utf8Str = NULL;
	for( unsigned int i = 0 ; i < ReadInfoList.size() ; i++ )
	{
		ReadInfoStruct *IDData = &ReadInfoList[i];
		
		if(IDData->AddressFlag == ENUM_Direct_Address)
		{
			utf8Str = ((char*)IDData->Point);
		}
		else if(IDData->AddressFlag == ENUM_Indirect_Address)
		{
			utf8Str = ((char*)(IDData->Point + int(Obj)));
		}
		//WCharToUTF8( IDData->wcTempBuf , utf8Str , IDData->Size );
		WCharToUTF8( Data[IDData->ID] , utf8Str , IDData->Size );
	}

}

/*
//---------------------------------------------------------------------------------------------------------
//��ID��������
//---------------------------------------------------------------------------------------------------------
template<class Temp>
class ReaderClass_Int  
{
    map<int,ReadInfoStruct> _ReadInfo;

public:
    ReaderClass(){};
    ~ReaderClass(){};

    //�Ҧ��ˬd
    bool	CheckStringType( int ValueName );


    //�Ʀr�Ҧ�
    int		Read( Temp *Obj , int ValueName );
    bool	Write( Temp *Obj , int ValueName , int Value );

    //�r��Ҧ�
    char*	ReadStr( Temp *Obj , int ValueName );
    bool	WriteStr( Temp *Obj , int ValueName , char*	Str );


    //��Ƴ]�w �p�G�H����ƫh�^�ǥ���
    //�� SetData ( �s���W�� , ���� , ���Ы��A(int short ...)  , �����ζ����w�}�Ҧ� )
    bool SetData( int ValueName , int Point , ReadInfoTypeENUM Type , ReadInfoAddrTypeENUM Flag );
};

template<class Temp>
bool ReaderClass_Int<Temp>::SetData(string	ValueName,int Point, ReadInfoTypeENUM Type,ReadInfoAddrTypeENUM Flag)
{

    ReadInfoStruct NewData;

    NewData.Point		= Point;
    NewData.Type		= Type;
    NewData.AddressFlag = Flag;

    _ReadInfo[ ValueName ] = NewData;

    return true;
}

//Ū���
template<class Temp>
int ReaderClass_Int<Temp>::Read( Temp *Obj , int	ValueName )
{
    map<int,ReadInfoStruct>::iterator Iter;

    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return 0;


    ReadInfoStruct *IDData;
    IDData = &( Iter->second );


    if(IDData->AddressFlag == ENUM_Direct_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            return *((float*)IDData->Point);

        case ENUM_Type_IntPoint:
            return *((int*)IDData->Point);

        case ENUM_Type_ShortPoint:
            return *((short*)IDData->Point);

        case ENUM_Type_CharPoint:
            return *((char*)IDData->Point);

        case ENUM_Type_FloatPointPoint:
            return **((float**)IDData->Point);

        case ENUM_Type_IntPointPoint:
            return **((int**)IDData->Point);

        case ENUM_Type_ShortPointPoint:
            return **((short**)IDData->Point);

        case ENUM_Type_CharPointPoint:
            return **((char**)IDData->Point);
        }
    }
    else if(IDData->AddressFlag == ENUM_Indirect_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            return *((float*)(IDData->Point + int(Obj)));

        case ENUM_Type_IntPoint:
            return *((int*)(IDData->Point + int(Obj)));

        case ENUM_Type_ShortPoint:
            return *((short*)(IDData->Point + int(Obj)));

        case ENUM_Type_CharPoint:
            return *((char*)(IDData->Point + int(Obj)));

        case ENUM_Type_FloatPointPoint:
            return **((float**)(IDData->Point + int(Obj)));

        case ENUM_Type_IntPointPoint:
            return **((int**)(IDData->Point + int(Obj)));

        case ENUM_Type_ShortPointPoint:
            return **((short**)(IDData->Point + int(Obj)));

        case ENUM_Type_CharPointPoint:
            return **((char**)(IDData->Point + int(Obj)));
        }
    }

    return 0;
}

//Ū���
template<class Temp>
bool ReaderClass_Int<Temp>::Write( Temp *Obj , int ValueName , int Value)
{
    map<int,ReadInfoStruct>::iterator Iter;

    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return false;

    ReadInfoStruct *IDData;
    IDData = &( Iter->second );

    if(IDData->AddressFlag == ENUM_Direct_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            *((float*)IDData->Point) = Value;
            break;			

        case ENUM_Type_IntPoint:
            *((int*)IDData->Point)   = Value;
            break;

        case ENUM_Type_ShortPoint:
            *((short*)IDData->Point) = Value;
            break;

        case ENUM_Type_CharPoint:
            *((char*)IDData->Point)	 = Value;
            break;

        case ENUM_Type_FloatPointPoint:
            **((float**)IDData->Point) = Value;
            break;

        case ENUM_Type_IntPointPoint:
            **((int**)IDData->Point)   = Value;
            break;

        case ENUM_Type_ShortPointPoint:
            **((short**)IDData->Point) = Value;
            break;

        case ENUM_Type_CharPointPoint:
            **((char**)IDData->Point)	 = Value;
            break;

        default:
            return false;
        }
    }
    else if(IDData->AddressFlag == ENUM_Indirect_Address)
    {
        switch(IDData->Type)
        {
        case ENUM_Type_FloatPoint:
            *((float*)(IDData->Point + int(Obj))) = Value;
            break;

        case ENUM_Type_IntPoint:
            *((int*)(IDData->Point + int(Obj)))   = Value;
            break;

        case ENUM_Type_ShortPoint:
            *((short*)(IDData->Point + int(Obj))) = Value;
            break;

        case ENUM_Type_CharPoint:
            *((char*)(IDData->Point + int(Obj)))  = Value;
            break;

        case ENUM_Type_FloatPointPoint:
            **((float**)(IDData->Point + int(Obj))) = Value;
            break;

        case ENUM_Type_IntPointPoint:
            **((int**)(IDData->Point + int(Obj)))   = Value;
            break;

        case ENUM_Type_ShortPointPoint:
            **((short**)(IDData->Point + int(Obj))) = Value;
            break;

        case ENUM_Type_CharPointPoint:
            **((char**)(IDData->Point + int(Obj)))  = Value;
            break;

        default:
            return false;
        }
    }

    return true;
}

//�r��Ҧ�
template<class Temp>
char* ReaderClass_Int<Temp>::ReadStr( Temp *Obj , int ValueName )
{
    map<int,ReadInfoStruct>::iterator Iter;

    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return NULL;

    ReadInfoStruct *IDData;
    IDData = &( Iter->second );

    if( IDData->Type == ENUM_Type_CharString )
    {	//return NULL;

        if(IDData->AddressFlag == ENUM_Direct_Address)
        {
            return ((char*)IDData->Point);
        }
        else if(IDData->AddressFlag == ENUM_Indirect_Address)
        {
            return ((char*)(IDData->Point + int(Obj)));
        }
    }
    else if( IDData->Type == ENUM_Type_CharStringPoint )
    {
        if(IDData->AddressFlag == ENUM_Direct_Address)
        {
            return *((char**)IDData->Point);
        }
        else if(IDData->AddressFlag == ENUM_Indirect_Address)
        {
            return *((char**)(IDData->Point + int(Obj)));
        }
    }

    return NULL;
}


template<class Temp>
bool ReaderClass_Int<Temp>::WriteStr( Temp *Obj , string int , char*	Str )
{
    map<int,ReadInfoStruct>::iterator Iter;

    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return false;

    ReadInfoStruct *IDData;
    IDData = &( Iter->second );

    if( IDData->Type == ENUM_Type_CharString )
    {

        if(IDData->AddressFlag == ENUM_Direct_Address)
        {
            strcpy( ((char*)IDData->Point) , Str );
        }
        else if(IDData->AddressFlag == ENUM_Indirect_Address)
        {
            strcpy( ((char*)(IDData->Point + int(Obj) )) , Str );
        }
        return true;
    }
    else if( IDData->Type == ENUM_Type_CharStringPoint )
    {
        if(IDData->AddressFlag == ENUM_Direct_Address)
        {
            strcpy( *((char**)IDData->Point) , Str );
        }
        else if(IDData->AddressFlag == ENUM_Indirect_Address)
        {
            strcpy( *((char**)(IDData->Point + int(Obj) )) , Str );
        }
        return true;
    }
    return false;
}

//�Ҧ��ˬd
template<class Temp>
bool ReaderClass_Int<Temp>::CheckStringType( int ValueName )
{
    map<int,ReadInfoStruct>::iterator Iter;
    Iter = _ReadInfo.find( ValueName );

    if( Iter == _ReadInfo.end() )
        return false;

    ReadInfoStruct *IDData;
    IDData = &( Iter->second );

    if( IDData->Type != ENUM_Type_CharString &&  IDData->Type != ENUM_Type_CharStringPoint)
        return false;

    return true;
}
*/
//---------------------------------------------------------------------------------------------------------
#pragma managed
#endif 
