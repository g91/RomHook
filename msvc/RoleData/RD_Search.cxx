#include "RoleDataEx.h"
//------------------------------------------------------------------------------------
//搜尋身體空欄位
//int		RoleDataEx::SearchBodyEmptyPos( )
//{
//    int i;
//    for( i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
//    {
//        if( PlayerBaseData->Body.Item[i].IsEmpty() )
//            return i;
//    }
//
//    return -1;
//}

int		RoleDataEx::SearchBankEmptyPos( )
{
    int i;
	for ( i = 0; i < _MAX_BANK_COUNT_; i++ )
	{		
		if ( i < 40 )
		{
			if( PlayerBaseData->Bank.Item[i].IsEmpty() )
				return i;
		}
		else
		{
			int index = (i - 40) / 40 + EM_TimeFlagEffect_BankBag2;
			if ( PlayerBaseData->TimeFlag[index] != -1 && PlayerBaseData->Bank.Item[i].IsEmpty() )
			{
				return i;
			}
		}
	}
    return -1;
}

//------------------------------------------------------------------------------------
// Item		來源物品資料
// isHeap	是否可以堆疊
// count	來源物品數量
int RoleDataEx::SearchBankEmptyPos( const ItemFieldStruct *Item, bool isHeap, int count )
{
	// 計次物品不能堆疊
	if ( Item && Item->Mode.HideCount )
		isHeap = false;

	// 找尋可以堆疊的位置
	if ( Item && isHeap )
	{
		if ( Item->Count == 0 )
			return -1;

		GameObjDbStructEx*	OrgDB;
		OrgDB = St_GetObjDB( Item->OrgObjID );
		if( OrgDB == NULL )
			return -1;

		for ( int i = 0; i < _MAX_BANK_COUNT_; i++ )
		{
			int index = (i - 40) / 40 + EM_TimeFlagEffect_BankBag2;

			// 租用欄位尚未開?功能
			if ( i >= 40 && PlayerBaseData->TimeFlag[index] == -1 )
				continue;

			if( PlayerBaseData->Bank.Item[i].OrgObjID != OrgDB->GUID || PlayerBaseData->Bank.Item[i].Pos != EM_ItemState_NONE )
				continue;

			if( PlayerBaseData->Bank.Item[i].Count + max(count, 1) <= max(OrgDB->MaxHeap, 1) )
				return i;
		}
	}

	// 找尋空的欄位
	for( int i = 0; i < _MAX_BANK_COUNT_; i++ )
	{
		int index = (i - 40) / 40 + EM_TimeFlagEffect_BankBag2;

		if ( i >= 40 && PlayerBaseData->TimeFlag[index] == -1 )
			continue;
		
		if ( PlayerBaseData->Bank.Item[i].Pos != EM_ItemState_NONE )
			continue;

		if ( PlayerBaseData->Bank.Item[i].IsEmpty() )
			return i;
	}
	
	return -1;
}

//-----------------------------------------------------------------------------------------------
// 判斷是否到達最高
bool CheckBankItemHeap( const ItemFieldStruct *Item, int position );

//-----------------------------------------------------------------------------------------------
//		關於怪物仇恨度處理
//-----------------------------------------------------------------------------------------------
//收尋某物件ID所對應此物件仇恨表的位置
//如果之前沒在裡面 則找一個適合的位置
NPCHateStruct*		RoleDataEx::GetHatePos( int	ID , int DBID )
{
    NPCHateStruct*	NPCHate; 
    int		i;
    int		MinHint = 1000000;
    int		MinID	= 0;
    int		TempID;
    int		TempHint;
    //	int		ID = Att->TempData.ItemID;

    for( i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++)
    {
        TempID = TempData.NPCHate.Hate[i].ItemID;
        if( TempID == -1 || TempID == ID )
            break;

        TempHint = TempData.NPCHate.Hate[i].TotalHatePoint() + TempData.NPCHate.Hate[i].HitPoint;

        if( TempHint < MinHint )
        {
            MinHint = TempHint;
            MinID = i;
        }
    }


    if( i == _MAX_HATELIST_SIZE_ )
    {
        NPCHate = &TempData.NPCHate.Hate[MinID];
        //檢查此人的資料是否有問題
        NPCHate->DBID = DBID;
        NPCHate->HatePoint = 0;
		NPCHate->TempHatePoint = 0;
        NPCHate->HitPoint = 0;
        NPCHate->ItemID = ID;

        return NPCHate;
    }
    else if( i == TempData.NPCHate.Hate.Size() )
    {
        NPCHateStruct TempSt;
        TempSt.Init();
        TempData.NPCHate.Hate.Push_Back( TempSt );
    }
        
    NPCHate = &TempData.NPCHate.Hate[i];
    NPCHate->DBID = DBID;
    NPCHate->ItemID = ID;	

    return NPCHate;
}

NPCHateStruct*		RoleDataEx::GetHatePos( int	ItemGUID  )
{
	NPCHateStruct*	NPCHate; 
	int		i;
	int		MinHint = 1000000;
	int		MinID	= 0;
	int		TempID;
	int		TempHint;
	for( i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++)
	{
		TempID = TempData.NPCHate.Hate[i].ItemID;
		if( TempID == -1 || TempID == ItemGUID )
			break;

		TempHint = TempData.NPCHate.Hate[i].TotalHatePoint() + TempData.NPCHate.Hate[i].HitPoint;

		if( TempHint < MinHint )
		{
			MinHint = TempHint;
			MinID = i;
		}
	}


	if( i == TempData.NPCHate.Hate.Size() )
	{
		return NULL;
	}

	NPCHate = &TempData.NPCHate.Hate[i];
	return NPCHate;
}

//找到地一個可堆疊的地方
int  RoleDataEx::SearchBodyFirstFit( const ItemFieldStruct *Item )
{
    if( Item->Count == 0 )
        return -1;

    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( Item->OrgObjID );
    if( OrgDB == NULL )
        return -1;

	for ( int i = 0; i < PlayerBaseData->Body.Count ; i++ )
	{
		if( PlayerBaseData->Body.Item[i].OrgObjID != OrgDB->GUID || PlayerBaseData->Body.Item[i].Pos != EM_ItemState_NONE )
			continue;

		if( PlayerBaseData->Body.Item[i].Count  < OrgDB->MaxHeap )
			return i;
	}
    
    for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
    {
        if( PlayerBaseData->Body.Item[i].IsEmpty() )
            return i;
    }

    return -1;
}

// 找到地一個可堆疊的地方
// 
int	 RoleDataEx::SearchBodyFirstFit( const ItemFieldStruct *Item, bool isHeap, int nowCount )
{
	// 計次物品不能堆疊
	if ( Item && Item->Mode.HideCount )
		isHeap = false;

	int maxCount = _MAX_BODY_COUNT_ - _MAX_BODY_EX_COUNT_ - _MAX_BODY_MAGIC_BOX_COUNT_;
	if ( Item && isHeap )
	{
		if ( Item->Count == 0 )
			return -1;

		GameObjDbStructEx*	OrgDB;
		OrgDB = St_GetObjDB( Item->OrgObjID );
		if( OrgDB == NULL )
			return -1;

		for ( int i = 0; i < maxCount; i++ )
		{			
			int flag	= i / 30;
			if ( flag == 2 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage3] == -1 )
				continue;
			else if ( flag == 3 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage4] == -1 )
				continue;
			else if ( flag == 4 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage5] == -1 )
				continue;
			else if ( flag == 5 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage6] == -1 )
				continue;
			
			int index	= PlayerBaseData->ClientData[i]; 
			if( PlayerBaseData->Body.Item[index].OrgObjID != OrgDB->GUID || PlayerBaseData->Body.Item[index].Pos != EM_ItemState_NONE )
				continue;

			if( PlayerBaseData->Body.Item[index].Count + max(nowCount, 1) <= max(OrgDB->MaxHeap, 1) )
				return index;
		}
	}

	for( int i = 0; i < maxCount; i++ )
	{		
		int flag	= i / 30;
		if ( flag == 2 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage3] == -1 )
			continue;
		else if ( flag == 3 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage4] == -1 )
			continue;
		else if ( flag == 4 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage5] == -1 )
			continue;
		else if ( flag == 5 && PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage6] == -1 )
			continue;
	
		int index	= PlayerBaseData->ClientData[i];
		if ( PlayerBaseData->Body.Item[index].Pos != EM_ItemState_NONE )
			continue;

		if( PlayerBaseData->Body.Item[index].IsEmpty() )
			return index;
	}

	return -1;
}

// 檢查該欄位是否可以使用(租用時間)
bool RoleDataEx::CheckBodyItemEnable( int index )
{
	if ( index < 0 || index >= _MAX_BODY_COUNT_ )
		return false;

	if ( index >= _MAX_BODY_BEGIN_POS_ )
	{
		int flag = (index - _MAX_BODY_BEGIN_POS_) / 30 - 2;
		if ( PlayerBaseData->TimeFlag[flag] == -1 )
			return false;
	}
	return true;
}

// 檢查該欄位是否可以使用(租用時間)
bool RoleDataEx::CheckBankItemEnable( int index )
{
	if ( index < 0 || index >= _MAX_BANK_COUNT_ )
		return false;

	int flag = index / 40 - 1;
	if ( flag >= 0 &&flag<4 && PlayerBaseData->TimeFlag[flag + EM_TimeFlagEffect_BankBag2] == -1 )
		return false;
	return true;
}

//取得身上某一種法術Buf
BuffBaseStruct*		RoleDataEx::GetBuff( GameObjectMagicTypeENUM AssistType , int MagicBaseID )
{
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		if( BaseData.Buff[i].BuffID == MagicBaseID )
			return &BaseData.Buff[i];

		if( AssistType != EM_Magic_Type_NULL && AssistType == BaseData.Buff[i].Magic->MagicBase.AssistType )
			return &BaseData.Buff[i];
	}
	return NULL;
}