// MyMapAreaManagement.cpp: implementation of the MyMapAreaManagement class.
//
//////////////////////////////////////////////////////////////////////


#include <memory.h> 
#include "MyMapAreaManagement.h"
#define NULL 0
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyMapAreaManagement::
    MyMapAreaManagement(int W,int H,int BufferSize)
{
    int i,j;
    _Height		=H;
    _Width		=W;
    _BufferSize	=BufferSize;
    _Count		=0;


    _IDInfo=(PlayIDInfo ***)NEW ( char[sizeof(char *) * _Width ]);

    for(i=0;i<(int)_Width;i++)
	{
        _IDInfo[i]=(PlayIDInfo **)NEW ( char[_Height*sizeof(void*)] );
	}

    for(i=0;i<(int)_Width;i++)
       for(j=0;j<(int)_Height;j++)
       {
          _IDInfo[i][j]= NEW PlayIDInfo;

          _IDInfo[i][j]->PosX=i;
          _IDInfo[i][j]->PosY=j;
          _IDInfo[i][j]->Begin=0;
          _IDInfo[i][j]->Count=0;
		  
       }
}
//---------------------------------------------------------------------------
MyMapAreaManagement::
    ~MyMapAreaManagement()
{
    int i,j;

    for(i=0;i<(int)_Width;i++)
       for(j=0;j<(int)_Height;j++)
           if(_IDInfo[i][j]!=0)
               delete(_IDInfo[i][j]);

    for(i=0;i<(int)_Width;i++)
        if(_IDInfo[i]!=0)
            delete(_IDInfo[i]);

    if(_IDInfo!=0)
        delete(_IDInfo);
}
//---------------------------------------------------------------------------
bool MyMapAreaManagement::Add( int x, int y , unsigned long ID )
{

    if( _Count >= _BufferSize )
    {
        g_MyError.SetError( NULL , "EM_MyError_MyMapAreaManagement_Add_OutofMenery");
        return false;
    }
    

    //資料重覆
    if( _PID.find( ID ) != _PID.end() )
    {
        g_MyError.SetError( NULL , "EM_MyError_MyMapAreaManagement_Add_IDIsExist" );
        return false;
    }

	if(_Height <= (unsigned)y || _Width <= (unsigned)x)
    {
        g_MyError.SetError( NULL , "EM_MyError_MyMapAreaManagement_Add_OutofSize" );
        return false;
    }
		

    PlayIDInfo *PBegin=_IDInfo[x][y];
	//PlayID     *P = NEW PlayID
    PlayID     *P = _PIDRecycleBin.NewObj();
    _PID[ID] = P;

    _Count++;
    P->ID=ID;
	P->X = x;
	P->Y = y;
	P->Fornt = NULL;
    P->Next=PBegin->Begin;

    PBegin->Begin = P;
	if(P->Next) 
		P->Next->Fornt = P;

    PBegin->Count++;

    return true;
}
//---------------------------------------------------------------------------
bool MyMapAreaManagement::Del(unsigned long ID)
{
    map< int , PlayID* >::iterator Iter;
    Iter = _PID.find( ID );
    if( Iter == _PID.end() )
    {
        g_MyError.SetError( NULL , "EM_MyError_MyMapAreaManagement_Del_IDNotFind" );
        return false;
    }

    PlayID     *P = (Iter->second);  
	int x = P->X;
	int y = P->Y;

	if(P->Next)
	{
		if(P->Fornt)
		{
			P->Next->Fornt = P->Fornt;
			P->Fornt->Next = P->Next;
		}
		else
		{
			_IDInfo[x][y]->Begin = P->Next;
			P->Next->Fornt = NULL;
		}
	}
	else
	{
		if(P->Fornt)
			P->Fornt->Next = NULL;
		else
			_IDInfo[x][y]->Begin = NULL;
	}

    _IDInfo[x][y]->Count--;
    _Count--;


    _PID.erase( Iter );
    //delete P;
    _PIDRecycleBin.DeleteObj( P );

    return true;
}
//---------------------------------------------------------------------------
bool MyMapAreaManagement::Move(int DesX,int DesY,unsigned long ID )
{
	if(Del(ID))
	{
		Add(DesX,DesY,ID);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
PlayIDInfo** MyMapAreaManagement::CompSearch(int x,int y,int lx,int ly, int w,int h)
{
    int i,j,k;
    x-=w;
    y-=h;
	lx -=w;
	ly -= h;
    w=w*2+1;
    h=h*2+1;
	int PosX,PosY;

	int right	= lx + w;
	int bottom	= ly + h;

    for(i=0,k=0;i<w;i++)
       for(j=0;j<h;j++)
       {
		    PosX = i+x;
			PosY = j+y;
            if((unsigned)PosX>=_Width ||(unsigned)PosY>=_Height)
                continue;
			Ret[k]=_IDInfo[PosX][PosY];
			if(Ret[k]->Begin == NULL)
				continue;

			//檢查是否再另外一個box內
			if(PosX>= lx && PosX<right  && PosY>=ly && PosY < bottom)
				Ret[k]->Type = 3;	//兩個方塊都包含的地方
			else
				Ret[k]->Type = 1;	//只有新的方塊友的地方
			
            k++;
       }

    right	= x + w;
	bottom	= y + h;

    for(i=0;i<w;i++)
       for(j=0;j<h;j++)
       {
		    PosX = i+lx;
			PosY = j+ly;
            if((unsigned)PosX>=_Width || (unsigned)PosY>=_Height)
                continue;
			//檢查是否再另外一個box內
			if(PosX>= x && PosX<right && PosY>=y && PosY < bottom)
				continue;
			Ret[k]=_IDInfo[PosX][PosY];
			if(Ret[k]->Begin == NULL)
				continue;
			Ret[k]->Type = 2;
			
            k++;
       }

    Ret[k]=0;

    return Ret;

	
}
//---------------------------------------------------------------------------
PlayIDInfo** MyMapAreaManagement::Search(int x,int y,int w,int h)
{
    int i,j,k;
    x-=w;
    y-=h;
    w=w*2+1;
    h=h*2+1;
	unsigned PosX,PosY;

	assert( sizeof(void *)*(w*h+1) < sizeof(Ret ) );
	memset(Ret,0,sizeof(void *)*(w*h+1));
    for(i=0,k=0;i<w;i++)
       for(j=0;j<h;j++)
       {
		    PosX = i+x;
			PosY = j+y;
            if(PosX >= _Width || PosY >= _Height)
                continue;

            Ret[k]=_IDInfo[PosX][PosY];
			if(Ret[k]->Begin == NULL)
				continue;
            k++;
       }
    Ret[k]=0;

    return Ret;
}

PlayIDInfo* MyMapAreaManagement::Search(int x,int y)
{

	if(x >= _Width || y >= _Height)
		return NULL;

	PlayIDInfo* Temp = _IDInfo[x][y];
	if( Temp->Begin == NULL)
		return NULL;
	return Temp;
}
//---------------------------------------------------------------------------
PlayIDInfo** MyMapAreaManagement::SearchBox(int MinX,int MinY,int MaxX ,int MaxY )
{
    int x,y,k;
    int w = ( MaxX - MinX ) + 1;
    int h = ( MaxY - MinY ) + 1;

	assert( sizeof(void *)*(w*h+1) < sizeof(Ret ) );

    memset(Ret,0,sizeof(void *)*(w*h+1));
    for( x = MinX , k=0 ; x <= MaxX ; x++ )
        for( y = MinY ; y <= MinY ; y++ )
        {
            if( x >= _Width || y >= _Height)
                continue;

            Ret[k]=_IDInfo[x][y];
            if(Ret[k]->Begin == NULL)
                continue;
            k++;
        }
        Ret[k]=0;

        return Ret;
}
//---------------------------------------------------------------------------

