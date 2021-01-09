#ifndef _RECYCLEBIN_
#define _RECYCLEBIN_
#include <vector>
#include <assert.h>
#include "Malloc/MyAlloc.h"
#include "debuglog/errormessage.h"

#pragma warning (disable:4949)

#pragma unmanaged
//---------------------------------------------------------------------------
/**
 * @file recyclebin.h 
 * 處理物件記憶體配置與回收\n
 * 加速固定結構記憶體配置與釋放\n
 * Last update [9/9/2004]
 * @author: hsiangren@runewaker.com.tw
 */
//---------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//資源回收物件
//----------------------------------------------------------------------------------
#define _RecycleBin_MemCheckData	0xccddeeff

using namespace std;

template<class Temp>
class RecycleBin
{
    struct BaseStruct
    {
		int		Block_ID;	//資料區塊
		int		Block_Pos;	//資料位置
		int		CheckOut;
		int		Revive;		//保留
        Temp    Data;
        int     CheckEnd;

        BaseStruct()
        {
            CheckEnd    = _RecycleBin_MemCheckData;
			CheckOut	= 0;
        }
    };
	//初始化最大Size;
//	int				_MaxSize;
	//暫存區(尚可配置區)
	
	map< int , vector <BaseStruct *> > _UnUsed;
	map< int , vector <BaseStruct *> > _AllData;

	vector <BaseStruct *> _AllocList;
	
    int             _MemGrowUPSize;
	//向系統要記憶體
	void _Alloc();

public:
	///建構函式
	///設定資源最多會要幾個
	///@param MaxSize 設定資源最多可配置量
	RecycleBin( int SetMemGrowUpSize = 100 );
	~RecycleBin();

	//void	MaxSize( int Size );

	///把所有的資源釋放掉，成為初始狀態
	void	Clear();

    ///回傳剩下未用到的記憶體大小
	///@return 配置未使用的物件各數
    int     MemSize()const {return (int)_UnUsed.size();};

	///配置新記憶體
	///@return 配置到的物件位址 
	Temp*	NewObj();

	///回收記憶體
	///@param DelObj 要釋放的物件指標 
	void	DeleteObj(Temp *DelObj);

	///檢查所有的記憶體
	//@return ture OK false 記憶體出問題
	bool	CheckAllMem();

    ///設定成長大小
    //void    SetMemGrowUpSize( int Size ){ _MemGrowUPSize = Size; };

	//資源回收
	void	GarbageCollectionProc( );
};
//----------------------------------------------------------------------------------
//
//					Source Code
//
//----------------------------------------------------------------------------------
template<class Temp>
Temp* RecycleBin<Temp>::NewObj()
{
	if(_UnUsed.size()==0)
	{
		_Alloc();
        assert( _UnUsed.size()!=0 );
		if(_UnUsed.size()==0)
		{
			Print( LV6 , "RecycleBin<Temp>::NewObj()" , "Out of Memory ,  datasize=%d " ,  sizeof(Temp) );
			return NULL;
		}
	}
	
	map< int , vector <BaseStruct *> >::iterator Iter = _UnUsed.begin();

	vector <BaseStruct *>& UnUseBase = Iter->second;
	
    BaseStruct *Ret=UnUseBase.back();
	UnUseBase.pop_back();
	assert( Ret->CheckOut == 0 );
	Ret->CheckOut = 1;

	if( UnUseBase.size() == 0 )
		_UnUsed.erase( Iter );

	return &Ret->Data;

}
//----------------------------------------------------------------------------------
template<class Temp>
void RecycleBin<Temp>::DeleteObj(Temp *Obj)
{
    BaseStruct*		Data = (BaseStruct*)( ((char*)Obj) - 16 );
    BaseStruct*	    CheckObj = _AllData[ Data->Block_ID ][ Data->Block_Pos ];

    assert( Obj == &CheckObj->Data );
	assert( CheckObj->CheckOut == 1 );

	if( Data->CheckEnd != _RecycleBin_MemCheckData )
		return;
	CheckObj->CheckOut = 0;
	//_UnUsed.push_back(Data);	
	_UnUsed[ Data->Block_ID ].push_back( Data );
}
//----------------------------------------------------------------------------------
template<class Temp>
RecycleBin<Temp>::RecycleBin(int MemGrowUpSize)
{
    _MemGrowUPSize = MemGrowUpSize;
}
//----------------------------------------------------------------------------------
/*
template<class Temp>
void RecycleBin<Temp>::MaxSize( int Size)
{
	_MaxSize = Size;
}*/
//----------------------------------------------------------------------------------
template<class Temp>
RecycleBin<Temp>::~RecycleBin()
{
	Clear();

}
//----------------------------------------------------------------------------------
template<class Temp>
void RecycleBin<Temp>::_Alloc()
{
	int i;
	BaseStruct*		_AllocMemory;
	BaseStruct*		_Addr;

/*	if(_RecycleBin_PackageBlock_ <= _AllocList.size())
    {
	    return;
    }*/
	
    //_AllocMemory = new BaseStruct[ ( sizeof(Temp) + 8 ) * ( _MaxSize/_RecycleBin_PackageBlock_+1 ) ];
    _AllocMemory = NEW (BaseStruct[ _MemGrowUPSize ]);

	if( _AllocMemory == NULL )
	{
		Print( LV6 , "RecycleBin<Temp>::_Alloc()" , "_AllocMemory == NULL ,  datasize=%d AllocCount=%d GrowUp=%d" , sizeof(Temp) , _AllocList.size() , _MemGrowUPSize );
		return;
	}

	//for(i=0;i<=_MaxSize/_RecycleBin_PackageBlock_;i++)
	vector <BaseStruct *>& UnUsedBase	= _UnUsed[ (int)_AllocList.size() ];
	vector <BaseStruct *>& AllDataBase = _AllData[ (int)_AllocList.size() ];

    for(i=0;i<_MemGrowUPSize;i++)
	{
		_Addr = &_AllocMemory[i];
        _Addr->Block_ID = (int)_AllocList.size();
		_Addr->Block_Pos = i;

		UnUsedBase.push_back( _Addr );
		AllDataBase.push_back( _Addr );
	}

	_AllocList.push_back(_AllocMemory);
}
//----------------------------------------------------------------------------------
template<class Temp>
void RecycleBin<Temp>::Clear()
{
	int i;
	for(i=0;i<(int)_AllocList.size();i++)
		delete[] (_AllocList[i]);

	_UnUsed.clear();
	_AllocList.clear();
	_AllData.clear();

}
//----------------------------------------------------------------------------------	
///檢查所有的記憶體
template<class Temp>
bool RecycleBin<Temp>::CheckAllMem()
{
	BaseStruct*		Data;
	map< int , vector <BaseStruct *> >::iterator Iter;

	for( Iter = _AllData.begin() ; Iter != _AllData.end() ; Iter++ )
	{
		vector <BaseStruct *>& DataList = Iter->second;
		for( int i = 0 ; i < (int)DataList.size() ; i++ )
		{
			Data = (BaseStruct*)(DataList[i]);
			if(     Data->Block_Pos != i 
				||  Data->CheckEnd  != _RecycleBin_MemCheckData )
				return false;
		}
	}

	return true;
}
//----------------------------------------------------------------------------------	
//資源回收(只有_MemGrowUPSize=1)
template<class Temp>
void RecycleBin<Temp>::GarbageCollectionProc( )
{
	map< int , vector <BaseStruct *> >::iterator Iter;

	for( Iter = _UnUsed.begin() ; Iter != _UnUsed.end() ;  )
	{
		if( Iter->second.size() != _MemGrowUPSize )
		{
			Iter++;
			continue;
		}
		
		int Block_ID = (*Iter->second.begin())->Block_ID;

		Iter = _UnUsed.erase( Iter );
		_AllData.erase( Block_ID );

		if( _AllocList[Block_ID] != NULL )
				delete[] (_AllocList[Block_ID]);
		_AllocList[Block_ID] = NULL;
	}

	while( _AllocList.size() != 0 )
	{
		if( _AllocList.back() != NULL )
			break;
		_AllocList.pop_back();
	}

	/*
	if( _MemGrowUPSize != 1 || _UnUsed.size() == 0 )
		return;

	_UnUsed.clear();
	_AllocList.clear();

	for( unsigned  i = 0 ; i < _AllData.size() ; i++ )
	{
		BaseStruct *Temp = _AllData[i];
		if( Temp->CheckOut == 1)
		{
			Temp->ID = _AllocList.size();
			_AllocList.push_back( Temp );
		}
		else
			delete Temp;
	}

	_AllData = _AllocList;
	*/
}
//----------------------------------------------------------------------------------	
#pragma managed
#endif