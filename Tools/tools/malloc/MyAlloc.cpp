#pragma once

#pragma warning (disable:4949)

#ifdef _MY_MEM_NEW_

#include "myalloc.h"
#include <map>
#include <vector>
#include "debuglog/errormessage.h"
#include "Mydebug.h"
#include "SmallObj/SmallObj.h"




using namespace std;

#pragma unmanaged

inline MutilThread_CritSect*  g_CritSect_Malloc( )
{ 
	static MutilThread_CritSect    g_Thread_CritSect; 

	return &g_Thread_CritSect;
}

//=================================================================================================================================
struct MyMemoryInfo
{
    int				ID;
    int				Line;
    const char*		File;
    int     		Size;
	int				IndexOrder;		
    int     		CheckBegin;
    char			Data[0];

    int     CheckEnd( )
    {
        return *(int*)(Data+Size);
    }
    void    CheckEnd( int V )
    {
        *(int*)(Data+Size) = V;
    }
};

bool    _MyAllocFreeReg( MyMemoryInfo* Mem );
//=================================================================================================================================

#define _MyAlloc_NoRegisterID_  -1
#define _MyAlloc_CheckCode_     0x12345678

vector< void*>*  _MyAllocMemoryList     = NULL;
vector< int >*   _MyAllocMemoryUnusedID = NULL;
//MyMemoryInfo*    _LastNewMemory         = NULL;

long    RegMemAlloc         = 0;
long    TotalMemoryAlloc    = 0;
int     TotalMemAllocTimes  = 0;
bool	IsInitMyMemoryNewOK	= false;
//--------------------------------------------------------------------------------------------------------------------------
bool    InitMyMemoryNew( )
{
    if(     _MyAllocMemoryList != NULL 
        ||  _MyAllocMemoryUnusedID != NULL )
        return false;
	
	if( IsInitMyMemoryNewOK != false )
		return false;
	IsInitMyMemoryNewOK	= true;

    g_CritSect()->Enter();

        _MyAllocMemoryList = new vector< void* >;
        _MyAllocMemoryUnusedID = new vector< int >;

    g_CritSect()->Leave();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------
bool    _MyAllocMemoryReport( )
{
	int MyM     = 0;

	if( _MyAllocMemoryList == NULL )
		return false;

	g_CritSect()->Enter();
	{
		char Buf[1024];
		map< string , int > MemoryList;

		unsigned            i;
		MyMemoryInfo*       Memory;
		for( i = 0 ; i < _MyAllocMemoryList->size() ; i++ )
		{
			Memory = (MyMemoryInfo*)(*_MyAllocMemoryList)[i];
			if( Memory == NULL )
				continue;

			if( Memory->ID != _MyAlloc_NoRegisterID_ )
			{
				sprintf_s( Buf , sizeof(Buf) , "File=%s Line=%d Size=%d" , Memory->File , Memory->Line , Memory->Size );
				MemoryList[Buf] ++;
				MyM++;
			}
		}
		map< string , int >::iterator Iter;
		for( Iter = MemoryList.begin() ; Iter != MemoryList.end() ; Iter++ )  
		{
			Print( LV5 , "MyAllocMemoryReport" , "%s x (Count=%d)" , Iter->first.c_str() , Iter->second );
		}


		Print( LV5 , "MyAllocMemoryReport" , "----   Size  TotalMemoryAlloc = %0.2f M  RegMemAlloc = %0.2f M" , float(TotalMemoryAlloc)/(1024*1024) , float(RegMemAlloc)/(1024*1024) );
		Print( LV5 , "MyAllocMemoryReport" , "----   Times MyMyMemory = %d , Total = %d not free " , MyM , TotalMemAllocTimes );
	}g_CritSect()->Leave();
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------
bool    _MyAllocMemoryReportAll( )
{
    int MyM     = 0;

	if( _MyAllocMemoryList == NULL )
		return false;

    g_CritSect()->Enter();
    {
        unsigned            i;
        MyMemoryInfo*       Memory;
        for( i = 0 ; i < _MyAllocMemoryList->size() ; i++ )
        {
            Memory = (MyMemoryInfo*)(*_MyAllocMemoryList)[i];
            if( Memory == NULL )
                continue;

            if( Memory->ID != _MyAlloc_NoRegisterID_ )
            {
                Print( LV5 , "MyAllocMemoryReport" , "Memory use 0x%x " , Memory );
                Print( LV5 , "MyAllocMemoryReport" , "File=%s Line=%d Size=%d" , Memory->File , Memory->Line , Memory->Size );
                MyM++;
            }
        }
        Print( LV5 , "MyAllocMemoryReport" , "----   TotalMemoryAlloc = %d RegMemAlloc = %d " , TotalMemoryAlloc , RegMemAlloc );
        Print( LV5 , "MyAllocMemoryReport" , "----   MyMemory = %d , Total = %d not free " , MyM , TotalMemAllocTimes );
    }g_CritSect()->Leave();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------
void    _MyAllocRelease( )
{
    g_CritSect()->Enter();
    {
        if( _MyAllocMemoryList != NULL )
        {
            delete _MyAllocMemoryList;
        }
        if( _MyAllocMemoryUnusedID == NULL )
        {
            delete _MyAllocMemoryUnusedID;
        }
        _MyAllocMemoryList      = NULL;
        _MyAllocMemoryUnusedID  = NULL;
    }g_CritSect()->Leave();
}
//--------------------------------------------------------------------------------------------------------------------------
bool    _MyAllocReg( void* Point , const char* File , int Line )
{
	MyMemoryInfo*   LM = (MyMemoryInfo*)( (char*)Point - sizeof(MyMemoryInfo) );
	if( LM->ID != _MyAlloc_NoRegisterID_ )
	{
		return false;
	}

	if(		_MyAllocMemoryList == NULL 
		||	_MyAllocMemoryUnusedID == NULL )
	{
		if( InitMyMemoryNew() == false )
			return false;

		return _MyAllocReg( Point , File , Line );
	}

	g_CritSect_Malloc()->Enter();
	{
		if( _MyAllocMemoryUnusedID->size() == 0 )
		{
			LM->ID = (int)_MyAllocMemoryList->size();
			_MyAllocMemoryList->push_back( LM );
		}
		else
		{
			LM->ID = _MyAllocMemoryUnusedID->back();
			_MyAllocMemoryUnusedID->pop_back();
			(*_MyAllocMemoryList)[ LM->ID ] = LM;
		}

		LM->File = File;
		LM->Line = Line;
		RegMemAlloc += LM->Size;

	}g_CritSect_Malloc()->Leave();

	return true;    
}
//--------------------------------------------------------------------------------------------------------------------------
void* RealyNew( size_t size  )
{
	static int Order = 0;
	MyMemoryInfo* RBuf = (MyMemoryInfo*)malloc(size +  sizeof(MyMemoryInfo) + 4 );
	RBuf->Size = (int)size;
	RBuf->CheckBegin = _MyAlloc_CheckCode_;
	RBuf->CheckEnd( _MyAlloc_CheckCode_ );
	RBuf->ID = _MyAlloc_NoRegisterID_;
	RBuf->IndexOrder = Order++;

	g_CritSect_Malloc()->Enter();
	TotalMemoryAlloc += long( size );
	TotalMemAllocTimes++;

	g_CritSect_Malloc()->Leave();

	
	return RBuf->Data;
}
//--------------------------------------------------------------------------------------------------------------------------
void RealDel( void* buf )
{
	if( buf == NULL )
		return;

	MyMemoryInfo* Mem = (MyMemoryInfo*)((char*)buf - sizeof(MyMemoryInfo) );

	if( Mem == NULL )
	{
		return;
	}

	if(     Mem->CheckBegin != _MyAlloc_CheckCode_ 
		||  Mem->CheckEnd() != _MyAlloc_CheckCode_ )
	{
		ASSERT( 0 );
		return ;
	}

	g_CritSect_Malloc()->Enter();
	{
		if ( _MyAllocFreeReg( Mem) != true )
		{
			ASSERT( 0 );
		}
		else
		{
			TotalMemoryAlloc -= Mem->Size;
			TotalMemAllocTimes--;
			free( Mem );
		}
	}g_CritSect_Malloc()->Leave();
}

//--------------------------------------------------------------------------------------------------------------------------
bool    _MyAllocFreeReg( MyMemoryInfo* Mem )
{

    if( Mem->ID == _MyAlloc_NoRegisterID_ )
        return true;

    if( _MyAllocMemoryList == NULL )
        return true;

    if( Mem->ID >= (int)_MyAllocMemoryList->size() )
    {
		ASSERT( 0 );
//        TRAC0( "_MyAllocFreeReg Mem ID error .... Serious Error!!" );
        return false;
    }

    if( Mem != (*_MyAllocMemoryList)[ Mem->ID ] )
    {
		ASSERT( 0 );
        //Print( LV5 , "_MyAllocFreeReg" , "Mem != _MyAllocMemoryList[ Mem->ID ] .... Serious Error!!" );
        return false;
    }
    _MyAllocMemoryUnusedID->push_back( Mem->ID );

    RegMemAlloc -= Mem->Size;

    (*_MyAllocMemoryList)[ Mem->ID ] = NULL;
    return true;

}
//--------------------------------------------------------------------------------------------------------------------------
void    _MyAllocMemoryCheck( )
{
    int MyM     = 0;

    if( _MyAllocMemoryList == NULL )
        return ;

    g_CritSect()->Enter();
    {
        Print( LV5 , "_MyAllocMemoryCheck" ,  "----------------MyAllocMemoryCheck----------------" );

        unsigned            i;
        MyMemoryInfo*       Memory;
        for( i = 0 ; i < _MyAllocMemoryList->size() ; i++ )
        {
            Memory = (MyMemoryInfo*)(*_MyAllocMemoryList)[i];
            if( Memory == NULL )
                continue;
            MyM++;
            if(     Memory->CheckBegin != _MyAlloc_CheckCode_ 
                ||  Memory->CheckEnd() != _MyAlloc_CheckCode_ )
            {
                if( Memory->ID != _MyAlloc_NoRegisterID_ )
                {
                    Print( LV5 , "_MyAllocMemoryCheck" , "Mem = 0x%x File=%s Line=%d : " , Memory , Memory->File , Memory->Line );
                }

                Print( LV5 , "_MyAllocMemoryCheck" , "Memory overflow CheckBegin(0x%x) CheckEnd(0x%x) " , Memory->CheckBegin , Memory->CheckEnd() );
            }
        }
        Print( LV5 , "_MyAllocMemoryCheck" , "----   TotalMemoryAlloc = %d RegMemAlloc = %d " , TotalMemoryAlloc , RegMemAlloc );
        Print( LV5 , "_MyAllocMemoryCheck" , "----   MyMemory = %d(block) Total = %d(block) not free " , MyM , TotalMemAllocTimes );

    }g_CritSect()->Leave();

    return ;
}
//--------------------------------------------------------------------------------------------------------------------------
void*   ::operator new( size_t size )
{
	return RealyNew( size );
}
void*   ::operator new( size_t size , const char* File , const int Line )
{
	void *Ret =  RealyNew( size );
	_MyAllocReg( Ret , File , Line );
	return Ret;
}

void ::operator delete(void *buf)
{
	RealDel(buf);
}
void*   ::operator new[]( size_t size )
{
	return RealyNew( size );
}
void*   ::operator new[]( size_t size , const char* File , const int Line )
{
	void *Ret =  RealyNew( size );
	_MyAllocReg( Ret , File , Line );
	return Ret;
}

void ::operator delete[](void *buf)
{
	RealDel(buf);
}

void  ::operator delete( void *buf , const char* File , const int Line )
{
	RealDel(buf);
}
void  ::operator delete[]( void *buf , const char* File , const int Line )
{
	RealDel(buf);
}
//--------------------------------------------------------------------------------------------------------------------------

#endif

#pragma managed
