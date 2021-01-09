////;********************************************************************************************
////;                 
////;  File:		MyMapAreaManage.h MyMapAreaManage.cpp
////;  OverView:	-人物區域管理程式
////;				-
////;  Revision: 1.0
////;  Last UpDate:2001.5.7
////;  Author: jacklo@softstar.com.tw      JackLo  2001.5.18
////;
////;********************************************************************************************

#pragma once
#include <MyBaseInc.h>
//---------------------------------------------------------------------------
#define	MapMaxSearchRange	100
using namespace std;
//---------------------------------------------------------------------------
struct PlayID
{
    long     ID;		//儲存玩者的id
	int		X;
	int		Y;
    PlayID *Next;
	PlayID *Fornt;

    PlayID()
    {
        ID = -1;
        Next = Fornt = NULL;
    }
};
//---------------------------------------------------------------------------
//Type  1 函在前面的Box (離開的人)
//		2 函在前面的Box (新進入的人)
//		3 兩者都函		(原來在裡面的人)
struct PlayIDInfo
{
   int PosX,PosY;             //位置
   short Count;               //內部擁有的數量
   short Type;				  //
   PlayID *Begin;             //位於此位置之id資料串列

};
//---------------------------------------------------------------------------
class  MyMapAreaManagement
{
    unsigned short          _Width,_Height;             //長寬
    int                     _BufferSize;                //最多可堆疊進入的數量
    int                     _Count;                     //目前堆疊進入的數量

    PlayIDInfo***           _IDInfo;                    //同PlayIDInfo *_IDInfo[_Width][_Height];
    map< int , PlayID* >    _PID;
    RecycleBin<PlayID>      _PIDRecycleBin;
    
	PlayIDInfo*             Ret[MapMaxSearchRange*MapMaxSearchRange];


public:
    MyMapAreaManagement(int Width,int Height,int BufferSize);       //設定初始狀態 寬 高 及最多己筆資料
    virtual ~MyMapAreaManagement();

    bool            Add         (int x,int y,unsigned long ID);                             //加入一筆資料
    bool            Del         (unsigned long ID);											//刪除一筆資料
    bool            Move        (int DesX,int DesY,unsigned long ID);						//移動一筆資料
    PlayIDInfo**    Search      (int x,int y,int w,int h );					                //尋找位於 x,y 周圍的資料
	PlayIDInfo*     Search      (int x,int y );								                //尋找位於 x,y 周圍的資料
    PlayIDInfo**    SearchBox   (int MinX,int MinY,int MaxX ,int MaxY );	
	PlayIDInfo**    CompSearch  (int x,int y,int lx,int ly, int w,int h );
	int             FreeMemorySize(){return _BufferSize - _Count;};			                //尚可用到的記憶底大小
    int             Count       (){ return _Count;};
	void			CheckPlayIDInfo( PlayIDInfo* IDList );
};
//---------------------------------------------------------------------------


