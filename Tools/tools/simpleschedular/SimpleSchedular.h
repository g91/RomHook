#ifndef		__SIMPLESCHEDULAR_H_2004_12_16__
#define		__SIMPLESCHEDULAR_H_2004_12_16__
//--------------------------------------------------------------------------------------------------------
#include <vector>
#include "RecycleBin/recyclebin.h"

using namespace std;
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
#define Def_OneShiftArrayLoop_  100
typedef int HSimpleSchedular;
//--------------------------------------------------------------------------------------------------------

template<class Temp>
class	SimpleSchedularClass
{
    //Return 0      代表資料不再使用
    //       大於 0 代表資料丟入多久以後再使用
    typedef int (*TempFunction)(Temp*);
    
    //define 資料
    struct EventStruct:public BaseLinkList
    {
        bool    IsDestroy;
        //剩下時間
        int     DTime;
        Temp*   Data;        
        TempFunction Func;
        
        EventStruct()
        {
            IsDestroy = false;
            DTime = 0;
            Data = NULL;
            Func = NULL;
        }
    };
    //--------------------------------------------------------------------------------------------------------
protected:
    //Dtime = 0
    vector< EventStruct* >      _EventList[ Def_OneShiftArrayLoop_ ];
    //Dtime != 0
    vector< EventStruct* >      _DEventList[ Def_OneShiftArrayLoop_ ];

    RecycleBin< EventStruct >   _EventBin;

    int                     _ShiftID;
    int                     _LShiftID;

    int                     _NextProcTime;
    int                     _OneProcTime;

    map < Temp* , EventStruct >  _EventMap;      //事件分類，清除事件用

    //偏移一個單位
    void    _Shift( );
    int     _Register( int Time , EventStruct* );
    void    _Delete( EventStruct* Obj );
public:
    SimpleSchedularClass();
//    ~SimpleSchedularClass(){};
    //把資料堆入
    //Return 一個位置 HSimpleSchedular

    HSimpleSchedular     Register( int Time , Temp* , TempFunction Func );

    //消除行程
    bool    Delete( HSimpleSchedular hObj , Temp* CheckData );
    //所有有關此勿件的行程全刪除
    bool    DeleteAll(  Temp* CheckData );


    //取目前的資料
    void    Proc();   

    //如果 Value = 0 or 過小 表示每次呼叫都執行
    //每次執行 不遞回補時間
    void    SetOneProcTime( int Value);
};

//--------------------------------------------------------------------------------------------------------
template<class Temp>
SimpleSchedularClass<Temp>::SimpleSchedularClass( )
{
    _ShiftID = 0;
    _LShiftID = Def_OneShiftArrayLoop_-1;
    _NextProcTime = clock();
    _OneProcTime = 100;
};
//--------------------------------------------------------------------------------------------------------

template<class Temp>
void SimpleSchedularClass<Temp>::Proc( )
{
    int i;
    int NowTime = clock();
    while( _NextProcTime < NowTime )
	{
        //return;
		_NextProcTime += _OneProcTime;

		for( i = 0 ; i < (int)_EventList[_ShiftID].size() ; i++ )
		{
			EventStruct *Event = ( _EventList[_ShiftID][i] );
			if( Event->IsDestroy != false )
			{
				//_EventBin.DeleteObj( Event );
				_Delete( Event );
				continue;
			}

			int Ret = Event->Func( Event->Data );
			if( Ret <= 0 )
			{
				//_EventBin.DeleteObj( Event );
				_Delete( Event );
				continue;
			}  

			_Register( Ret , Event );
		}           
	                
		for( i = 0 ; i < (int)_DEventList[_ShiftID].size() ; i++ )
		{
			EventStruct *Event = ( _DEventList[_ShiftID][i] );
			if( Event->IsDestroy != false )
			{   
				//_EventBin.DeleteObj( Event );
				_Delete( Event );
				continue;
			}

			_Register( Event->DTime , Event );        
		}

		_DEventList[_ShiftID].clear();
		_EventList[_ShiftID].clear();

		_Shift( );
	}	

};

//--------------------------------------------------------------------------------------------------------

template<class Temp>
HSimpleSchedular SimpleSchedularClass<Temp>::Register(  int Time , Temp* Data , TempFunction Func )
{
    EventStruct* Event = _EventBin.NewObj();
    Event->Data = Data;
    Event->Func = Func;
    Event->IsDestroy = false;

    EventStruct* EventFront = &_EventMap[ Data ];

    Event->AddTo( EventFront );

    _Register( Time , Event );

    return (int) Event;
};

template<class Temp>
int SimpleSchedularClass<Temp>::_Register( int Time , EventStruct* Event )
{

    if( Time >= Def_OneShiftArrayLoop_ )    
    {
        Event->DTime = Time - Def_OneShiftArrayLoop_ + 1 ;
        _DEventList[ _LShiftID ].push_back( Event );
    }
    else
    {
        int Pos = ( _ShiftID + Time ) % Def_OneShiftArrayLoop_ ;
        Event->DTime = 0;
        _EventList[ Pos ].push_back( Event );
    }
    return (int)Event;
}

//--------------------------------------------------------------------------------------------------------
template<class Temp>
void SimpleSchedularClass<Temp>::_Shift( )
{
    _LShiftID = _ShiftID;
    _ShiftID ++;
    if( _ShiftID >= Def_OneShiftArrayLoop_ )
        _ShiftID = 0;
};
//--------------------------------------------------------------------------------------------------------
//消除行程
template<class Temp>
bool    SimpleSchedularClass<Temp>::Delete( HSimpleSchedular hObj , Temp* CheckData )
{
    if( hObj == NULL )
        return false;

     EventStruct* Event = (EventStruct*)hObj;
     if(    Event->Data != CheckData )
         return false;
     if( Event->IsDestroy != false )
         return false;
     Event->IsDestroy = true;
     return true;
};

//--------------------------------------------------------------------------------------------------------
template<class Temp>
void    SimpleSchedularClass<Temp>::_Delete( EventStruct* Obj )
{
	//assert( Obj->IsDestroy != false );
    Obj->Del( );
    _EventBin.DeleteObj( Obj );
}
//--------------------------------------------------------------------------------------------------------
//所有有關此勿件的行程全刪除
template<class Temp>
bool    SimpleSchedularClass<Temp>::DeleteAll(  Temp* Data )
{
	map < Temp* , EventStruct >::iterator Iter;

	Iter = _EventMap.find( Data );
	if( Iter == _EventMap.end() )
		return false;

    //EventStruct* List = (EventStruct*)_EventMap[ Data ].Next;
	EventStruct* List = (EventStruct*)Iter->second.Next;

    while( List != NULL )
    {
        List->IsDestroy = true;
        List = (EventStruct*)List->Next;
    }
//	_EventMap[ Data ].Next = NULL;
    return true;
}
//--------------------------------------------------------------------------------------------------------
#endif