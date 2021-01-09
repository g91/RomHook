////;********************************************************************************************
////;                 
////;  File:		MyMapAreaManage.h MyMapAreaManage.cpp
////;  OverView:	-�H���ϰ�޲z�{��
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
    long     ID;		//�x�s���̪�id
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
//Type  1 ��b�e����Box (���}���H)
//		2 ��b�e����Box (�s�i�J���H)
//		3 ��̳���		(��Ӧb�̭����H)
struct PlayIDInfo
{
   int PosX,PosY;             //��m
   short Count;               //�����֦����ƶq
   short Type;				  //
   PlayID *Begin;             //��󦹦�m��id��Ʀ�C

};
//---------------------------------------------------------------------------
class  MyMapAreaManagement
{
    unsigned short          _Width,_Height;             //���e
    int                     _BufferSize;                //�̦h�i���|�i�J���ƶq
    int                     _Count;                     //�ثe���|�i�J���ƶq

    PlayIDInfo***           _IDInfo;                    //�PPlayIDInfo *_IDInfo[_Width][_Height];
    map< int , PlayID* >    _PID;
    RecycleBin<PlayID>      _PIDRecycleBin;
    
	PlayIDInfo*             Ret[MapMaxSearchRange*MapMaxSearchRange];


public:
    MyMapAreaManagement(int Width,int Height,int BufferSize);       //�]�w��l���A �e �� �γ̦h�v�����
    virtual ~MyMapAreaManagement();

    bool            Add         (int x,int y,unsigned long ID);                             //�[�J�@�����
    bool            Del         (unsigned long ID);											//�R���@�����
    bool            Move        (int DesX,int DesY,unsigned long ID);						//���ʤ@�����
    PlayIDInfo**    Search      (int x,int y,int w,int h );					                //�M���� x,y �P�򪺸��
	PlayIDInfo*     Search      (int x,int y );								                //�M���� x,y �P�򪺸��
    PlayIDInfo**    SearchBox   (int MinX,int MinY,int MaxX ,int MaxY );	
	PlayIDInfo**    CompSearch  (int x,int y,int lx,int ly, int w,int h );
	int             FreeMemorySize(){return _BufferSize - _Count;};			                //�|�i�Ψ쪺�O�Щ��j�p
    int             Count       (){ return _Count;};
	void			CheckPlayIDInfo( PlayIDInfo* IDList );
};
//---------------------------------------------------------------------------


