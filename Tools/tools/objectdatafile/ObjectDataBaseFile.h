//==================================================================================================
//	簡易物件資料庫快取物件
//
//
//==================================================================================================
#pragma once

#pragma warning (disable:4949)
#pragma	warning (disable:4786)
#pragma unmanaged

#include    <map>
#include    <vector>
#include	<stdio.h>
#include    <algorithm>

#include    "BaseFunction/BaseFunction.h"
#include    "SmallObj/SmallObj.h"
#include    "ReaderClass/ReaderClass.h"
#include    "Malloc/MyAlloc.h"
#include	"recyclebin/recyclebin.h"

#include "filebase/FileBase.h"
//-------------------------------------------------------------------------------
//基本要使用此物件的結構
/*
struct BaseObjStruct
{
    int     GUID;
    int     Class();
};
*/
//////////////////////////////////////////////////////////////////////////
using namespace std;

namespace  NSObjectDataFile
{
	#define		DEF_MAX_NEED_FREE_COUNT	5000
	#define		DEF_ITEMOBJ_FILE_ID     0x6396
	typedef	void		(*pFuncMessageOut)( int, const char*, const char*, ... );
	typedef void		(*pFuncInitObj )( void* , void* );
	//////////////////////////////////////////////////////////////////////////
	struct ObjFileHead
	{   
		char    FileInfoStr[ 128 ];		//檔案資訊
		long    Idenitfy;				//識別字
		long    Count;
		long    Size;

		ObjFileHead( )
		{
			Idenitfy = DEF_ITEMOBJ_FILE_ID;
			strcpy( FileInfoStr , "Item Obj File" );
		};
	};
	//////////////////////////////////////////////////////////////////////////
	struct ObjFileInfo
	{
		MyFileBase*					File;
		ObjFileHead					FileHead;
		ObjFileInfo()
		{
			memset( this , 0 , sizeof(*this) );
		}
		~ObjFileInfo()
		{
			if( File != NULL )
				delete File;
		}
	};
	//////////////////////////////////////////////////////////////////////////
	template < class T >
	struct ObjBaseStruct
	{
		ObjFileInfo*				FileInfo;
		int			 				Seek;
		T*			 				Obj;
		union
		{
			int						Mode;
			struct
			{
				short			AccessCount;		//存取次數
				bool			IsLoad		: 1;	//已載入
				bool			IsInit		: 1;	//已初始化
				bool			IsNeedFree	: 1;	//物件需要釋放
			};
		};

		ObjBaseStruct()
		{
			Init();
		}

		void Init()
		{
			memset( this , 0 , sizeof(*this) );
		}
	};

	//////////////////////////////////////////////////////////////////////////
	enum ObjectDataLoadTypeENUM
	{
		EM_ObjectDataLoadType_None				,
		EM_ObjectDataLoadType_LoadAll			,
		EM_ObjectDataLoadType_LoadAll_NoFree	,
	};
	//////////////////////////////////////////////////////////////////////////

	template <class T , class FileClass = MyFile >
	class	ObjectDataFileClass
	{
	private:
		map < int , ObjBaseStruct<T>* >					_ObjData;
		vector< char* >									_SourceData;	
		vector< ObjFileInfo* >							_FileInfoList;				//所有載入的檔案之檔頭資料
		typename map < int,ObjBaseStruct<T>* >::iterator	_SearchIter;
		pFuncMessageOut									_MsgOutFunc;
		pFuncInitObj									_InitObjFunc;
		int												_NeedFreeCount;				//需要管理釋放的數量
		RecycleBin< ObjBaseStruct<T> >					_ObjBaseRecycleBin;
		void*											_InitUserObj;
		//		int												_MaxNeedFreeCount;			//最多需要管理釋放的數量
	public:
		//-----------------------------------------------------------
		static bool ObjCmp (T* A, T* B) 
		{
			return A->GUID < B->GUID;
		};
		//-----------------------------------------------------------
		ObjectDataFileClass();
		~ObjectDataFileClass();

		void	Release();														//資料釋放
		bool	OpenFile( const char *FileName , ObjectDataLoadTypeENUM LoadType , map<string,ReadInfoStruct>* ReadInfo = NULL );              //讀檔   

		//取得GUID = id 的物件
		ObjBaseStruct<T>*	GetObjBase( int id );
		T*	GetObj( int id );

		//取得目前有幾筆資料
		int		TotalInfoCount( )			{return (int)_ObjData.size();};

		//循序取資料 只取記憶體中的 並且不幫資料初始處理
		//IsResetData = false   取資料
		//IsResetData = true    重設循序取資料資訊(return true;)
		T*		GetDataByOrder( bool IsResetData = false );

		//把某一個資料設定到此物件
		void	SetData( T* );

		void	Process( int MaxObjCount = DEF_MAX_NEED_FREE_COUNT );

		//取得檔頭資訊
		vector< ObjFileInfo* >*	FileInfoList() { return  &_FileInfoList; }				//所有載入的檔案之檔頭資料

		void	SetOutPutFunc( pFuncMessageOut pFunc ) { _MsgOutFunc = pFunc; }
		void	SetInitFunc( pFuncInitObj pFunc , void* UserObj ) { _InitObjFunc = pFunc; _InitUserObj = UserObj; }

	};

	//-------------------------------------------------------------------------------------------------
	//資料釋放
	template <class T , class FileClass >
	void	ObjectDataFileClass<T,FileClass>::Release()
	{
		int i;
		for( i = 0 ; i < (int)_SourceData.size() ; i++ )
		{
			delete _SourceData[i];
		}
		_SourceData.clear();

		{
			vector<  ObjFileInfo* >::iterator Iter;
			for( Iter = _FileInfoList.begin() ; Iter != _FileInfoList.end() ; Iter++ )
			{
				ObjFileInfo* Info = *Iter;
				if(Info->File)
					Info->File->Close();
				delete *Iter;
			}
			_FileInfoList.clear();
		}

		{
			map < int , ObjBaseStruct<T>* >::iterator Iter;
			for( Iter = _ObjData.begin() ; Iter != _ObjData.end() ; Iter++ )
			{
				if( Iter->second->Obj != NULL && Iter->second->IsLoad != false && Iter->second->IsNeedFree != false )
				{
					delete Iter->second->Obj;
				}

				//delete Iter->second;
				_ObjBaseRecycleBin.DeleteObj( Iter->second );
			}
			_ObjData.clear();
		}		
		_NeedFreeCount = 0;
	}
	//-------------------------------------------------------------------------------------------------
	template <class T , class FileClass >
	ObjectDataFileClass<T,FileClass>::ObjectDataFileClass()
		: _ObjBaseRecycleBin( 1000 )
	{
		_InitObjFunc		= NULL;
		_MsgOutFunc			= NULL;
		_NeedFreeCount		= 0;
		//_ObjBaseRecycleBin.MaxSize( 0xfffffff );
		//_ObjBaseRecycleBin.SetMemGrowUpSize( 1000 );
		//_MaxNeedFreeCount	= DEF_MAX_NEED_FREE_COUNT;
	};//ObjectDataFileClass::ObjectDataFileClass
	//-------------------------------------------------------------------------------------------------
	template <class T , class FileClass >
	ObjectDataFileClass<T,FileClass>::~ObjectDataFileClass()
	{
		Release();
	};//ObjectDataFileClass::~ObjectDataFileClass	
	//-------------------------------------------------------------------------------------------------
	//	開啟檔案
	//-------------------------------------------------------------------------------------------------
	template <class T , class FileClass > 
	bool ObjectDataFileClass<T,FileClass>::OpenFile( const char *FileName , ObjectDataLoadTypeENUM LoadType , map<string,ReadInfoStruct>* ReadInfo  )
	{		
		//讀取檔頭資料
		ObjFileInfo* FileInfo = new ObjFileInfo;

		ObjFileHead&				Head = FileInfo->FileHead;
		FileClass*					File = NEW FileClass;
		char*						Data;
		int							i;
		FileInfo->File	= File;

		if( File->Open( FileName ) == false )
		{
			delete FileInfo;
			return false;
		}

		File->Read( &Head , sizeof(Head) );

		//if( Head.Size * Head.Count < 1024*1024*2 )


		if( Head.Idenitfy != DEF_ITEMOBJ_FILE_ID )
		{
			delete FileInfo;
			return false;
		}

		switch( LoadType )
		{
		case EM_ObjectDataLoadType_None:
			{
				for( i = 0 ; i < Head.Count ; i++ )
				{
					T TempObj;
					File->Read( &TempObj , Head.Size );
					//////////////////////////////////////////////////////////////////////////
					ObjBaseStruct<T>* TempObjBase = _ObjBaseRecycleBin.NewObj();//NEW ObjBaseStruct<T>;
					TempObjBase->Init();
					TempObjBase->FileInfo = FileInfo;					
					TempObjBase->Seek	= i * Head.Size + sizeof(Head);
					_ObjData[ TempObj.GUID ] = TempObjBase;
				}
			}
			break;
		case EM_ObjectDataLoadType_LoadAll:
			{
				for( i = 0 ; i < Head.Count ; i++ )
				{
					//////////////////////////////////////////////////////////////////////////
					ObjBaseStruct<T>* TempObjBase = _ObjBaseRecycleBin.NewObj();//NEW ObjBaseStruct<T>;
					TempObjBase->Init();
					TempObjBase->FileInfo	= FileInfo;
					TempObjBase->Seek		= i * Head.Size + sizeof(Head);
					TempObjBase->Obj		= (T*)NEW char[ Head.Size ];
					TempObjBase->IsNeedFree = true;
					TempObjBase->IsLoad		= true;
					File->Read( TempObjBase->Obj , Head.Size );
					_ObjData[TempObjBase->Obj->GUID ] = TempObjBase;
					_NeedFreeCount++;
				}
			}
			break;
		case EM_ObjectDataLoadType_LoadAll_NoFree:
			{
				int DataSizeBase = (Head.Size + sizeof(int) -1 )/sizeof(int)*sizeof(int);

				//為了確定初始化時不會寫記憶體溢位， (例 pNPC	= &pQuestObj->NPC)
				//所以記憶體配置時最後一比大小設為 size(T)
				Data = NEW ( char[ DataSizeBase * Head.Count + sizeof(T) ] );
				_SourceData.push_back( (char*)Data );

				for( i = 0 ; i < Head.Count ; i++ )
				{
					T* D1 = (T*)( Data + i* DataSizeBase );
					File->Read( D1 , Head.Size );

					//////////////////////////////////////////////////////////////////////////
					ObjBaseStruct<T>* TempObjBase = _ObjBaseRecycleBin.NewObj();//NEW ObjBaseStruct<T>;
					TempObjBase->Init();
					TempObjBase->FileInfo = FileInfo;
					TempObjBase->IsLoad	= true;
					TempObjBase->Seek	= i * Head.Size + sizeof(Head);
					TempObjBase->Obj	= D1;

					_ObjData[D1->GUID ] = TempObjBase;
				}

//				delete FileInfo->File;
//				FileInfo->File = NULL;
			}
			break;
		}

		_FileInfoList.push_back( FileInfo );

		if( ReadInfo != NULL )
		{
			map< string , int > NameAddressMap;
			int		StrLen = 0;
			int		Point = 0;
			char	ValueName[512];
			//File->Seek( Head.Size * Head.Count + sizeof( Head ) , EM_FileSeek_Begin );
			while(1)
			{
				if( File->Read( (char*)&( StrLen ) , sizeof(int) ) == 0 )
					break;
				File->Read( (char*)&(Point ) , sizeof(int) );
				File->Read( ValueName , StrLen );
				NameAddressMap[ ValueName ] = Point;
			}
			
			bool	CheckVersionError = false;
			map<string,ReadInfoStruct>::iterator    Iter;
			for( Iter  = ReadInfo->begin() ; 
				Iter != ReadInfo->end() ; 
				Iter++  )
			{
				ReadInfoStruct *IDData = &(Iter->second);
				int FilePoint = NameAddressMap[IDData->ValueName ];
				if( IDData->Point != FilePoint )
				{
					Print( LV5 , "OpenFile" , "FileName=%s , FieldName=%s FilePoint=%d ProgramPont=%d" , FileName , IDData->ValueName.c_str() , FilePoint , IDData->Point );
					CheckVersionError = true;
				}
			}

			if( CheckVersionError != false )
			{
				Print( LV6 , "OpenFile" , "CheckVersionError FileName=%s FileInfoStr=%s" , FileName , Head.FileInfoStr );
			}
		}


		return true;		
	};//OBJECTDATABASEFILE::OpenFile

	//-------------------------------------------------------------------------------------------------
	//把某一個資料設定到此物件
	//-------------------------------------------------------------------------------------------------
	template <class T, class FileClass> 
	void	ObjectDataFileClass<T,FileClass>::SetData( T* Data )
	{
		ObjBaseStruct<T>* TempObjBase = NEW ObjBaseStruct<T>;
		TempObjBase->FileInfo	= NULL;
		TempObjBase->Obj		= NEW ( T );
		TempObjBase->IsLoad		= true;
		_ObjData[D1->GUID ] = TempObjBase;

		T* NewData = TempObjBase->Obj;
		memcpy( NewData , Data , sizeof(T) );

		_SourceData.push_back( (char*)NewData );

	}
	//-------------------------------------------------------------------------------------------------
	template <class T, class FileClass> 
	T*	ObjectDataFileClass<T,FileClass>::GetObj( int id )
	{
		ObjBaseStruct<T>* ObjBase = GetObjBase( id );
		if( ObjBase == NULL )
			return NULL;

		return ObjBase->Obj;
	}
	//取得GUID = id 的物件
	template <class T, class FileClass> 
	ObjBaseStruct<T>*	ObjectDataFileClass<T,FileClass>::GetObjBase( int id )
	{		
		if( id == 0 )
			return NULL;

		map < int , ObjBaseStruct<T>* >::iterator Iter;

		Iter = _ObjData.find( id );
		if( Iter == _ObjData.end() )
			return NULL;


		ObjBaseStruct<T>* ObjInfo = Iter->second;
		//載入資料
		if( ObjInfo->IsLoad == false )
		{			
			_NeedFreeCount++;

			ObjInfo->FileInfo->File->Seek( ObjInfo->Seek , EM_FileSeek_Begin );

			int		ObjSize = ObjInfo->FileInfo->FileHead.Size;
			ObjInfo->Obj = (T*)NEW char[ ObjSize ];
			ObjInfo->FileInfo->File->Read( ObjInfo->Obj , ObjSize );

			ObjInfo->Mode			= 0;
			ObjInfo->IsNeedFree = true;
			ObjInfo->IsLoad			= true;			
			ObjInfo->AccessCount	= 2;
		}
		if( ObjInfo->IsInit == false )
		{
			if( _InitObjFunc )
				_InitObjFunc( _InitUserObj , ObjInfo->Obj );
			ObjInfo->IsInit = true;
		}

		ObjInfo->AccessCount++;

		return ObjInfo;
	}
	//////////////////////////////////////////////////////////////////////////
	template <class T, class FileClass> 
	void	ObjectDataFileClass<T,FileClass>::Process( int MaxObjCount )
	{
		if( MaxObjCount > _NeedFreeCount )
			return;

		map < int , ObjBaseStruct<T>* >::iterator Iter;

		int		MaxDeleteCount = MaxObjCount / 3;
		//把所有只用到一次的物件刪除
		for( Iter = _ObjData.begin() ; Iter != _ObjData.end() ; Iter++ )
		{
			if( MaxDeleteCount <= 0 )
				break;
			
			ObjBaseStruct<T>* ObjBase = Iter->second;

			if(		ObjBase->IsLoad == false 
				||	ObjBase->IsNeedFree == false )
				continue;

			if( ObjBase->AccessCount < 2 )
			{
				delete ObjBase->Obj;
				ObjBase->Obj = NULL;
				ObjBase->Mode = 0;
				MaxDeleteCount--;		
//				Iter = _ObjData.erase( Iter );
				_NeedFreeCount--;
			}
			else
			{
				Iter->second->AccessCount = 0;
			}
		}

	}
	//////////////////////////////////////////////////////////////////////////
	//循序取資料
	template <class T, class FileClass> 
	T* ObjectDataFileClass<T,FileClass>::GetDataByOrder( bool IsResetData )
	{
		if( IsResetData != false )
		{
			_SearchIter = _ObjData.begin();
			return NULL;
		}

		std::map <int,ObjBaseStruct<T>*>::iterator	 TempIter;

		if( _SearchIter == _ObjData.end() )
			return NULL;

		TempIter = _SearchIter ++;

		if( TempIter == _ObjData.end() )
			return NULL;

		if( TempIter->second->IsLoad == false )
			return NULL;

		return TempIter->second->Obj;
	}
}







/*
//-------------------------------------------------------------------------------
#define				DEF_ITEMOBJ_FILE_ID     0x6396

typedef	void		(*pFuncObjectDataFileClassMessageOut)( int, const char*, const char*, ... );

using namespace std;
//-------------------------------------------------------------------------------
struct ObjFileHead
{   
    char    FileInfoStr[ 128 ];  //檔案資訊
    long    Idenitfy;           //識別字
    long    Count;
    long    Size;

    ObjFileHead( )
    {
        Idenitfy = DEF_ITEMOBJ_FILE_ID;
        strcpy( FileInfoStr , "Item Obj File" );
    };
};
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

template <class T , class FileClass = MyFile >
class	ObjectDataFileClass
{
    
private:
	map < int , T* >			_ObjData;
	vector< char* >				_SourceData;
	//char*						_DataBeginAddr;
	map< string , ObjFileHead >	_FileHeadList;			//所有載入的檔案之檔頭資料
	typename map < int,T* >::iterator	_SearchIter;
public:
    //-----------------------------------------------------------
    //
    //-----------------------------------------------------------
    static bool ObjCmp (T* A, T* B) 
    {
        return A->GUID < B->GUID;
    };
    //-----------------------------------------------------------

	ObjectDataFileClass();
	~ObjectDataFileClass();
	
	void	Release();										//資料釋放
	bool	OpenFile( const char *FileName);                //讀檔   
	bool	OpenBuffer( const char *FileName, const char *pBuffer );
    bool	SaveFile( const char *FileName );               //檔案一比結構的大小

    bool	OpenTxtFile(char *FileName , ReaderClass<T> *Reader );    //讀檔
    //bool	SaveTxtFile( char *FileName );					//檔案一比結構的大小


	//取得GUID = id 的物件
	T*		GetObj( int id );

	//取得目前有幾筆資料
	int		TotalInfoCount( )			{return (int)_ObjData.size();};

	//循序取資料
    //IsResetData = false   取資料
    //IsResetData = true    重設循序取資料資訊(return true;)
	T*		GetDataByOrder( bool IsResetData = false );

	//把某一個資料設定到此物件
	void	SetData( T* );

	//取得檔頭資訊
	map< string , ObjFileHead >*	FileHeadList() { return &_FileHeadList; }

	void	SetOutPutFunc( pFuncObjectDataFileClassMessageOut pFunc ) { m_pFunc = pFunc; }

	pFuncObjectDataFileClassMessageOut m_pFunc;
};
//-------------------------------------------------------------------------------------------------
//資料釋放
template <class T, class FileClass>
void	ObjectDataFileClass<T,FileClass>::Release()
{
	int i;
	for( i = 0 ; i < (int)_SourceData.size() ; i++ )
	{
		delete _SourceData[i];
	}

	_SourceData.clear();

}

//-------------------------------------------------------------------------------------------------
template <class T, class FileClass>
ObjectDataFileClass<T,FileClass>::ObjectDataFileClass()
{
	m_pFunc = NULL;
};//ObjectDataFileClass::ObjectDataFileClass
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass>
ObjectDataFileClass<T,FileClass>::~ObjectDataFileClass()
{
	Release();
};//ObjectDataFileClass::~ObjectDataFileClass
//-------------------------------------------------------------------------------------------------
//	開啟檔案
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass> 
bool ObjectDataFileClass<T,FileClass>::OpenFile( const char *FileName)
{
//#ifdef _CLIENT
	ObjFileHead					Head;
	Pointer< FileClass >		File;
	char*						Data;
	int							i;

	if( File->Open( FileName ) == false )
		return false;

	File->Read( &Head , sizeof(Head) );

	if( Head.Idenitfy != DEF_ITEMOBJ_FILE_ID )
		return false;

//	if( (unsigned)Head.Size > sizeof( T ) )
//		return false;

	int DataSizeBase = (Head.Size + sizeof(int) -1 )/sizeof(int)*sizeof(int);

	//為了確定初始化時不會寫記憶體溢位， (例 pNPC	= &pQuestObj->NPC)
	//所以記憶體配置時最後一比大小設為 size(T)
	Data = NEW ( char[ DataSizeBase * Head.Count + sizeof(T) ] );
	_SourceData.push_back( (char*)Data );

	for( i = 0 ; i < Head.Count ; i++ )
	{
		T* D1 = (T*)( Data + i* DataSizeBase );
		File->Read( D1 , Head.Size );
		_ObjData[D1->GUID ] = D1;
	}

	_FileHeadList[ FileName ] = Head ;
	return true;

};//OBJECTDATABASEFILE::OpenFile

template <class T, class FileClass> 
bool ObjectDataFileClass<T,FileClass>::OpenBuffer( const char *FileName, const char *pBuffer )
{
	
	ObjFileHead					Head;
	char*						Data;
	int							i;

	const char*					ptr		= pBuffer;

	if( pBuffer == NULL )
		return false;

	memcpy( &Head, ptr, sizeof(Head) );
	ptr += sizeof(Head);

	if( Head.Idenitfy != DEF_ITEMOBJ_FILE_ID )
		return false;

	int DataSizeBase = (Head.Size + sizeof(int) -1 )/sizeof(int)*sizeof(int);

	//為了確定初始化時不會寫記憶體溢位， (例 pNPC	= &pQuestObj->NPC)
	//所以記憶體配置時最後一比大小設為 size(T)
	Data = NEW ( char[ DataSizeBase * Head.Count + sizeof(T) ] );

	if( m_pFunc != NULL && Data == NULL )
	{
		m_pFunc( LV5, "ObjectDataFileClass", "Data == NULL, Head.Count = %d, Head.Size = %d sizeof(T) = %d", Head.Count, Head.Size, sizeof(T) );
	}


	_SourceData.push_back( (char*)Data );
	
	for( i = 0 ; i < Head.Count ; i++ )
	{
		T* D1 = (T*)( Data + i* DataSizeBase );
		
		//File->Read( D1 , Head.Size );
		memcpy( D1, ptr, Head.Size );
		ptr += Head.Size;

		_ObjData[D1->GUID ] = D1;
	}

	_FileHeadList[ FileName ] = Head ;
	return true;
};

//-------------------------------------------------------------------------------------------------
//	存檔
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass> 
bool ObjectDataFileClass<T,FileClass>::SaveFile( const  char *FileName)
{
    ObjFileHead				Head;
    //Pointer< CRuFileStream>	File;
	Pointer< FileClass >	File;
    T*						Data;
    int						i;


//    if( ruSEC_OK != File->Create( FileName ) )
//        return false;
	if( File->OpenFile( FileName , EM_FileBaseType_Write | EM_FileBaseType_Binary ) == false )
		return false;

    Head.Count = (int)_ObjData.size();
    Head.Size  = sizeof(T);

    File->Write( &Head , sizeof(Head) );

    map <int,T*>::iterator	 Iter;
    vector<T*>               SaveData;

    Iter = _ObjData.begin();
    for( i = 0 ; i < Head.Count ; i++ , Iter++ )
    {
        SaveData.push_back( Iter->second );
    }
    
    sort( SaveData.begin() , SaveData.end() , ObjCmp );

    for( i = 0 ; i < (int)SaveData.size() ; i++ )
    {
        Data = SaveData[ i ];
        File->Write( Data , sizeof( T ) );
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass> 
bool	ObjectDataFileClass<T,FileClass>::OpenTxtFile( char *FileName , ReaderClass<T> *Reader )
{
//    ReaderClass<T> *Reader;
//    Reader = T::GetReader( Type );

    char	seps[] = " \t\n\r";
    vector< string >            _NameList;
    vector< ReadInfoTypeENUM >  _TypeList;
    char    Buf[ 0x10000 ];
    int     ArgCount;
    int     i;
    T       Data;  

    FILE*	file;
    if (NULL == (file = fopen(FileName, "rb")))
        return false;

    //----------------------------------------------------------
    //取得名稱列表
    if( NULL == fgets( Buf , sizeof( Buf ) , file ) )
        return false;
    
    char* token = strtok( Buf , seps );
    for( ArgCount = 0 ; token != NULL ; ArgCount++ )
    {
        _strlwr( token );
        _NameList.push_back( token );
        token = strtok( NULL , seps );
    }
    //----------------------------------------------------------
    //取得Type列表
    if( NULL == fgets( Buf , sizeof( Buf ) , file ) )
        return false;

    token = strtok( Buf , seps );
    for( i = 0 ; i < ArgCount ; i++ )
    {
        if( token == NULL )
        {
            TRACE1( "ObjectDataFileClass<T>::OpenTxtFile Read Type Count Error!! FileName = %s " , FileName );
            return false;
        }

        _strlwr( token );
        if( strcmp( token , "str" ) == 0 )
        {
            _TypeList.push_back( EM_Type_CharString  );
        }
        else if( strcmp( token , "int" ) == 0 )
        {
            _TypeList.push_back( EM_Type_Int );
        }
        else
        {
            TRACE1( "ObjectDataFileClass<T>::OpenTxtFile Read Type Error!! FileName = %s " , FileName );
            return false;
        }
        token = strtok( NULL , seps );
    }
    int Line = 2;
    //----------------------------------------------------------
    while( NULL != fgets( Buf , sizeof( Buf ) , file ) )
    {
        Line ++;
       
        char* token = strtok( Buf , seps );
        for( i = 0 ; i < ArgCount ; i++ )
        {
            if( token == NULL )
            {
                TRACE2( "File Line = %d : Read Value Error!! FileName = %s " , Line , FileName );
                break;
            }
            switch( _TypeList[ i ] )
            {
            case EM_Type_CharString:
                Reader->WriteStr( &Data , _NameList[ i ].c_str() , token  );
                break;
            case EM_Type_Int:
                Reader->Write( &Data , _NameList[ i ].c_str() , atol( token ) );
                break;

            }
            token = strtok( NULL , seps );
        }

        SetData( &Data );
    }
    //----------------------------------------------------------

    return true;
}
//-------------------------------------------------------------------------------------------------
//	取得物件(經由快取)
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass> 
T*	ObjectDataFileClass<T,FileClass>::GetObj(int	id)
{
    if( id == 0 )
        return NULL;

	std::map <int,T*>::iterator Iter;
	Iter = _ObjData.find( id );
	if( Iter == _ObjData.end() )
		return NULL;

	return Iter->second;

};//OBJECTDATABASEFILE::GetObject
//-------------------------------------------------------------------------------------------------
//	版本取得
//-------------------------------------------------------------------------------------------------
//循序取資料
template <class T, class FileClass> 
T* ObjectDataFileClass<T,FileClass>::GetDataByOrder( bool IsResetData )
{
    //static std::map <int,T*>::iterator _SearchIter;

    if( IsResetData != false )
    {
        _SearchIter = _ObjData.begin();
        return NULL;
    }

	std::map <int,T*>::iterator	 TempIter;

	if( _SearchIter == _ObjData.end() )
		return NULL;

	TempIter = _SearchIter ++;

	if( TempIter == _ObjData.end() )
		return NULL;

	return TempIter->second;
}
//-------------------------------------------------------------------------------------------------
//把某一個資料設定到此物件
//-------------------------------------------------------------------------------------------------
template <class T, class FileClass> 
void	ObjectDataFileClass<T,FileClass>::SetData( T* Data )
{
    T* NewData = NEW ( T );
    memcpy( NewData , Data , sizeof(T) );

    _SourceData.push_back( (char*)NewData );
    
	_ObjData[Data->GUID ] = NewData;
}
//-------------------------------------------------------------------------------------------------
*/
#pragma managed


