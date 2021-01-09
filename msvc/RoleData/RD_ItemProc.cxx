#include "RoleDataEx.h"
#include <algorithm>
#include "basefunction/BaseFunction.h"
#include <set>
//------------------------------------------------------------------------------------------------------------------------------------
// 0 Body 1 Bank 2 EQ
ItemFieldStruct* RoleDataEx::GetItem  ( int Pos , int Type )   
{
    switch( Type )
    {
    case 0:
        return GetBodyItem( Pos );
    case 1:
        return GetBankItem( Pos );
    case 2:
        return GetEqItem( Pos );
    }

    return NULL;
}

int  RoleDataEx::GetBodyItemPos( int OrgID , int Version )
{    
    for( int i = 0 ; i < _MAX_BODY_COUNT_ ; i++ )
    {
        ItemFieldStruct* Temp = &PlayerBaseData->Body.Item[ i ];
        if(     Temp->OrgObjID == OrgID 
            && ( Version == 0 || Temp->Serial == Version ) )
            return i;
    }
    return -1;
}
int RoleDataEx::GetBankItemPos( int OrgID , int Version )
{
    for( int i = 0 ; i < _MAX_BANK_COUNT_ ; i++ )
    {
        ItemFieldStruct* Temp = &PlayerBaseData->Bank.Item[ i ];
        if(     Temp->OrgObjID == OrgID 
            && ( Version == 0 || Temp->Serial == Version ) )
            return i;
    }
    return -1;

}
int RoleDataEx::GetEqItemPos  ( int OrgID , int Version )
{
    for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
    {
        ItemFieldStruct* Temp = &BaseData.EQ.Item[ i ];
        if(     Temp->OrgObjID == OrgID 
            && ( Version == 0 || Temp->Serial == Version ) )
            return i;
    }
    return -1;
}
int RoleDataEx::GetBodyRealPos(int index)
{
	if ( (unsigned int)index > _MAX_CLIENT_DATA_SIZE_ )
		return -1;
	return PlayerBaseData->ClientData[index];
}
int RoleDataEx::GetBodyItemCount()
{
	int count = 30 * 2;
	if ( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage3] != -1 )
		count += 30;
	if ( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage4] != -1 )
		count += 30;
	if ( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage5] != -1 )
		count += 30;
	if ( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage6] != -1 )
		count += 30;
	return count;
}
ItemFieldStruct* RoleDataEx::GetBodyVirtualItem( int Pos )
{
	return GetBodyItem(GetBodyRealPos(Pos));
}
ItemFieldStruct* RoleDataEx::GetBodyItem( int Pos )
{    
    if( (unsigned)Pos > _MAX_BODY_COUNT_ )
        return NULL;
    return &PlayerBaseData->Body.Item[ Pos ];
}
ItemFieldStruct* RoleDataEx::GetBankItem( int Pos )
{
    if( (unsigned)Pos > _MAX_BANK_COUNT_ )
        return NULL;

    return &PlayerBaseData->Bank.Item[ Pos ];
}
ItemFieldStruct* RoleDataEx::GetEqItem  ( int OrgPos )
{
	int Type = OrgPos / _DEF_EQ_BACKUP_BASE_;
	int Pos  = OrgPos % _DEF_EQ_BACKUP_BASE_;

    if( (unsigned)Pos > EM_EQWearPos_MaxCount )
        return NULL;

	switch( Type )
	{
	case 0:
		return &BaseData.EQ.Item[ Pos ];
	case 1:
		return &PlayerBaseData->EQBackup[0].Item[ Pos ];
	case 2:
		return &PlayerBaseData->EQBackup[1].Item[ Pos ];
	case 3:
		return &PlayerBaseData->EQBackup[2].Item[ Pos ];
	case 4:
		return &PlayerBaseData->EQBackup[3].Item[ Pos ];
	case 5:
		return &PlayerBaseData->EQBackup[4].Item[ Pos ];
	};
	return NULL;
}

int RoleDataEx::BodyMoney_Account(  )
{
	return PlayerBaseData->Body.Money_Account;
}
int RoleDataEx::BodyMoney(  )
{
    return PlayerBaseData->Body.Money;
}
int RoleDataEx::BankMoeny( )
{
    return PlayerBaseData->Bank.Money;
}

void RoleDataEx::BodyMoney( int Value )
{
//    TempData.UpdateInfo.Money = true;
    PlayerBaseData->Body.Money = Value;
	Net_FixMoney(  );
}
void RoleDataEx::BankMoeny( int Value )
{
    //TempData.UpdateInfo.Money = true;
    PlayerBaseData->Bank.Money = Value;
	Net_FixMoney(  );
}

SellItemFieldStruct* RoleDataEx::GetSellItem( int Pos )
{
	if ( (unsigned)Pos > _MAX_SELL_ITEM_SAVE_COUNT_ )
		return NULL;

	return &PlayerTempData->SellItemBackup[Pos];
}

int RoleDataEx::GetSellItemCount()
{
	return PlayerTempData->SellItemBackup.Size();
}

//檢查欄位資料是否有問題
bool    RoleDataEx::CheckBodyItem( ItemFieldStruct& Item , int Pos )
{
    if( ( unsigned )Pos >= _MAX_BODY_COUNT_ || Pos >= PlayerBaseData->Body.Count  )
        return false;

    if(		Item == *GetBodyItem( Pos ) )
        return true;
	

    return false; 
}

bool    RoleDataEx::CheckBankItem( ItemFieldStruct& Item , int Pos )
{
    if( ( unsigned )Pos >= _MAX_BANK_COUNT_ || Pos >= PlayerBaseData->Bank.Count  )
        return false;

    if(		Item == *GetBankItem( Pos ) )
        return true;

    return false; 
}
//------------------------------------------------------------------------------------------------------------------------------------
bool    RoleDataEx::CheckEQItem( ItemFieldStruct& Item , int Pos  )
{
    if( ( unsigned )Pos >= EM_EQWearPos_MaxCount   )
        return false;

	if(		Item == *GetEqItem( Pos ) )
		return true;

    return false; 
}

//------------------------------------------------------------------------------------------------------------------------------------
bool	RoleDataEx::CheckPetPosTimeFlag( int Pos )
{
	switch( Pos )
	{
	case 0:
	case 1:
		return true;
	case 2:
		if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_PetPage3] < 0 )
			return false;
		else return true;			
	case 3:
		if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_PetPage4] < 0 )
			return false;
		else return true;
	case 4:
		if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_PetPage5] < 0 )
			return false;
		else return true;
	case 5:
		if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_PetPage6] < 0 )
			return false;
		else return true;

	default:
		return false;
	}
	return false;
}

//Type = 0 Body 1 Bank
bool	RoleDataEx::CheckItemPosTimeFlag( int Type , int Pos , int ItemObjID )
{
	switch( Type )
	{
	case 0://Body
		{
			if( Pos >= _DEF_BAG_PAGE6_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage6] < 0 )
					return false;
			}
			else if( Pos >= _DEF_BAG_PAGE5_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage5] < 0 )
					return false;
			}
			else if( Pos >= _DEF_BAG_PAGE4_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage4] < 0 )
					return false;
			}

			else if( Pos >= _DEF_BAG_PAGE3_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage3] < 0 )
					return false;
			}
			break;
		}
	case 1://bank
		{
			if( unsigned(Pos) > _MAX_BANK_COUNT_  )
				return false;

			if( Pos >= _DEF_BANK_MALL_BEGIN_POS_ )
			{
				GameObjDbStructEx* itemDB = St_GetObjDB( ItemObjID );
				if( itemDB )
				{
					if(		itemDB->Mode.DepartmentStore == false 
						&&	itemDB->Mode.DepartmentStore_Free == false )
						return false;
				}
			}
			else if( Pos >= _DEF_BANK_PAGE5_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BankBag5] < 0 )
					return false;
			}
			else if( Pos >= _DEF_BANK_PAGE4_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BankBag4] < 0 )
					return false;
			}

			else if( Pos >= _DEF_BANK_PAGE3_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BankBag3] < 0 )
					return false;
			}
			else if( Pos >= _DEF_BANK_PAGE2_BEGIN_POS_  )
			{
				if( PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BankBag2] < 0 )
					return false;
			}
			
		}
		break;
	case 2:
		return true;
	default:
		return false;

	}
	return true;
}

//把暫存區的物品取到身上
//Item 為確定的物品資料
RoleDataResultENUM RoleDataEx::GetItemBuftoBody( ItemFieldStruct& Item , int Pos , int Count )
{
	if( PlayerBaseData->ItemTemp.Size() <= 0 )
		return EM_RoleData_BufferEmpty;

	if( PlayerBaseData->ItemTemp.Front().IsEmpty() )
		return EM_RoleData_IsEmpty;

	//檢查要放製的位置是否可以放
	if(	PlayerBaseData->ItemTemp.Front() != Item )
		return EM_RoleData_DataInfoErr;

	Item = PlayerBaseData->ItemTemp.Front();

	if( Count <= 0 )
		return EM_RoleData_CountErr;

    if( Count > Item.Count )
        return EM_RoleData_CountErr;


    //檢查是否超過可放置欄位
    if( ( unsigned int ) Pos >= ( unsigned int )PlayerBaseData->Body.Count )
		return EM_RoleData_PosErr;

	//////////////////////////////////////////////////////////////////////////
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , Pos ) == false )
		return EM_RoleData_PosErr;

	//////////////////////////////////////////////////////////////////////////

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( Item.OrgObjID );
	if( OrgDB == NULL )
		return EM_RoleData_DataInfoErr;

	if( OrgDB->MaxHeap < Count + GetBodyItem( Pos )->Count )
		return  EM_RoleData_PosErr;

	if( OrgDB->MaxHeap < Item.Count )
	{
		PlayerBaseData->ItemTemp.Erase( 0 );
		return EM_RoleData_DataInfoErr;
	}


    if( PlayerBaseData->ItemTemp.Front().Count == Count )
        PlayerBaseData->ItemTemp.Erase( 0 );
    else
        PlayerBaseData->ItemTemp.Front().Count -= Count;


	ItemFieldStruct& BodyItem = *GetBodyItem( Pos );

	if( BodyItem.IsEmpty()  )
	{
		Item.Count = Count;
		BodyItem = Item;		
	}
	else
	{
		if(		BodyItem.OrgObjID != Item.OrgObjID 
			||	OrgDB->MaxHeap < BodyItem.Count + Count 
			||  BodyItem.Mode.HideCount != false )
			return EM_RoleData_DataInfoErr;

		GetBodyItem(Pos)->Count += Count;
		//Item = *(GetBodyItem(Pos));
		Item = BodyItem;

		if( BodyItem.IsEmpty() == false )
			BodyItem.Mode.Trade = !(OrgDB->Mode.PickupBound);
	}





    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;

}
//------------------------------------------------------------------------------------------------------------------------------------
//加一個物品到身上某位置
RoleDataResultENUM RoleDataEx::AddItemtoBody( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if(     ( unsigned int )Pos >= ( unsigned int )PlayerBaseData->Body.Count 
        ||  !IsBodyEmpty( Pos ) )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , Pos ) == false )
		return EM_RoleData_PosErr;


    *GetBodyItem(Pos) = Item;

    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//刪除一個物品到身上某位置
RoleDataResultENUM RoleDataEx::DelItemFromBody( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if( ( unsigned int )Pos >= ( unsigned int )PlayerBaseData->Body.Count )
        return EM_RoleData_PosErr;

    //檢查要放製的位置是否可以放
    if(	*GetBodyItem(Pos) != Item )
        return EM_RoleData_DataInfoErr;

	Log_ItemDestroy( EM_ActionType_DestroyItem , Item , -1 , "" );

    GetBodyItem(Pos)->Init();

    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//加一個物品到銀行某位置
RoleDataResultENUM RoleDataEx::AddItemtoBank( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if(     ( unsigned int )Pos >= ( unsigned int )PlayerBaseData->Bank.Count 
        ||  !IsBankEmpty( Pos ) )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , Pos , Item.OrgObjID ) == false )
		return EM_RoleData_PosErr;


    *GetBankItem(Pos) = Item;

    TempData.UpdateInfo.Bank = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//刪除一個物品到銀行某位置
RoleDataResultENUM RoleDataEx::DelItemFromBank( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if( (unsigned int) Pos >= ( unsigned int )PlayerBaseData->Bank.Count )
        return EM_RoleData_PosErr;

    //檢查要放製的位置是否可以放
    if(	*GetBankItem( Pos ) != Item )
        return EM_RoleData_DataInfoErr;

	Log_ItemDestroy( EM_ActionType_DestroyItem , Item , -1 , ""  );
    GetBankItem(Pos)->Init();

    TempData.UpdateInfo.Bank = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//刪除一個裝備
RoleDataResultENUM RoleDataEx::DelItemFromEQ( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if( (unsigned int) Pos >= EM_EQWearPos_MaxCount )
        return EM_RoleData_PosErr;

    //檢查要放製的位置是否可以放
    if(	BaseData.EQ.Item[Pos] != Item )
        return EM_RoleData_DataInfoErr;

	Log_ItemDestroy( EM_ActionType_DestroyItem , Item , -1 , ""  );
    BaseData.EQ.Item[Pos].Init();

    TempData.UpdateInfo.Eq = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//身體物品交換
RoleDataResultENUM RoleDataEx::ExchangeBodyItem(	ItemFieldStruct& Item1 , int Pos1  
                                                ,	ItemFieldStruct& Item0 , int Pos0  )
{

    if( Pos0 == Pos1 )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , Pos0 ) == false )
		return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , Pos1 ) == false )
		return EM_RoleData_PosErr;


    if( (unsigned int)Pos0 >= _MAX_BODY_COUNT_ || (unsigned int)Pos1 >= _MAX_BODY_COUNT_ )
        return EM_RoleData_PosErr;

	if(		GetBodyItem( Pos0 )->Pos != EM_ItemState_NONE 
		||	GetBodyItem( Pos1 )->Pos != EM_ItemState_NONE  )
		return EM_RoleData_DataInfoErr;


    if(		CheckBodyItem( Item0 , Pos0 ) == false
        ||	CheckBodyItem( Item1 , Pos1 ) == false )
        return EM_RoleData_DataInfoErr;
    
    
    if(		Item0.OrgObjID != Item1.OrgObjID 
		|| Item0.Mode.HideCount != false 
		|| Item1.Mode.HideCount != false 	 )
    {
        std::swap( *GetBodyItem( Pos0 ) , *GetBodyItem( Pos1) );
        return EM_RoleData_OK;
    }
    
    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( Item0.OrgObjID );

    if( OrgDB == NULL )
    {
        GetBodyItem( Pos0 )->Init();
        GetBodyItem( Pos1 )->Init();
        return EM_RoleData_OrgObjIDErr;
    }

    if( OrgDB->MaxHeap == 1 )
    {
        std::swap( *GetBodyItem( Pos0 ) , *GetBodyItem( Pos1) );
        return EM_RoleData_OK;
    }
    
    if( OrgDB->MaxHeap >= GetBodyItem( Pos0 )->Count + GetBodyItem( Pos1 )->Count )
    {
        GetBodyItem( Pos0 )->Count += GetBodyItem( Pos1 )->Count;
		GetBodyItem( Pos0 )->Mode.Trade = !(OrgDB->Mode.PickupBound);
        GetBodyItem( Pos1 )->Init();
    }
    else
    {
        GetBodyItem( Pos1 )->Count = GetBodyItem( Pos1 )->Count + GetBodyItem( Pos0 )->Count - OrgDB->MaxHeap;
        GetBodyItem( Pos0 )->Count = OrgDB->MaxHeap;
    }
	if( GetBodyItem( Pos0 )->IsEmpty() == false )
		GetBodyItem( Pos0 )->Mode.Trade = !(OrgDB->Mode.PickupBound);
	if( GetBodyItem( Pos1 )->IsEmpty() == false )
		GetBodyItem( Pos1 )->Mode.Trade = !(OrgDB->Mode.PickupBound);
	

    TempData.UpdateInfo.Body= true;

    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//銀行物品交換
RoleDataResultENUM RoleDataEx::ExchangeBankItem(	ItemFieldStruct& Item0 , int Pos0  
                                                ,	ItemFieldStruct& Item1 , int Pos1  )
{
    if( Pos0 == Pos1 )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , Pos0 , Item1.OrgObjID  ) == false )
		return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , Pos1 , Item0.OrgObjID ) == false )
		return EM_RoleData_PosErr;

	if(		GetBankItem( Pos0 )->Pos != EM_ItemState_NONE 
		||	GetBankItem( Pos1 )->Pos != EM_ItemState_NONE  )
		return EM_RoleData_DataInfoErr;


    if( (unsigned int)Pos0 >= _MAX_BANK_COUNT_ || (unsigned int)Pos1 >= _MAX_BANK_COUNT_ )
        return EM_RoleData_PosErr;

    if(		CheckBankItem( Item0 , Pos0 ) == false
        ||	CheckBankItem( Item1 , Pos1 ) == false )
        return EM_RoleData_DataInfoErr;


    if(		Item0.OrgObjID != Item1.OrgObjID 
		||	Item0.Mode.HideCount != false 
		||	Item1.Mode.HideCount != false )
    {
        std::swap( *GetBankItem( Pos0 ) , *GetBankItem( Pos1) );
        return EM_RoleData_OK;
    }

    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( Item0.OrgObjID );

    if( OrgDB == NULL )
    {
        GetBankItem( Pos0 )->Init();
        GetBankItem( Pos1 )->Init();
        return EM_RoleData_OrgObjIDErr;
    }

    if( OrgDB->MaxHeap == 1  )
    {
        std::swap( *GetBankItem( Pos0 ) , *GetBankItem( Pos1) );
        return EM_RoleData_OK;
    }

    if( OrgDB->MaxHeap >= GetBankItem( Pos0 )->Count + GetBankItem( Pos1 )->Count )
    {
        GetBankItem( Pos0 )->Count += GetBankItem( Pos1 )->Count;
        GetBankItem( Pos1 )->Init();
    }
    else
    {
        GetBankItem( Pos1 )->Count = GetBankItem( Pos1 )->Count + GetBankItem( Pos0 )->Count - OrgDB->MaxHeap;
        GetBankItem( Pos0 )->Count = OrgDB->MaxHeap;
    }

	if( GetBankItem( Pos0 )->IsEmpty() == false )
		GetBankItem( Pos0 )->Mode.Trade = !OrgDB->Mode.PickupBound;
	if( GetBankItem( Pos1 )->IsEmpty() == false )
		GetBankItem( Pos1 )->Mode.Trade = !OrgDB->Mode.PickupBound;


    TempData.UpdateInfo.Bank = true;

    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//身體與銀行交換物品
RoleDataResultENUM RoleDataEx::ExchangeBodyBankItem(	ItemFieldStruct& BodyItem , int BodyPos  
                                                    ,	ItemFieldStruct& BankItem , int BankPos  )
{
    if( (unsigned int)BodyPos >= _MAX_BODY_COUNT_ || (unsigned int)BankPos >= _MAX_BANK_COUNT_ )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , BodyPos ) == false )
		return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , BankPos , BodyItem.OrgObjID  ) == false )
		return EM_RoleData_PosErr;


    if(		CheckBodyItem( BodyItem , BodyPos ) == false
        ||	CheckBankItem( BankItem , BankPos ) == false )
        return EM_RoleData_DataInfoErr;

	if(		PlayerBaseData->Body.Item[ BodyPos ].Pos != EM_ItemState_NONE
		||	PlayerBaseData->Bank.Item[ BankPos ].Pos != EM_ItemState_NONE )
		return EM_RoleData_DataInfoErr;


    if(		BodyItem.OrgObjID != BankItem.OrgObjID 
		||	BodyItem.Mode.HideCount != false 
		||	BankItem.Mode.HideCount != false )
    {
        //std::swap( BodyItem( BodyPos ) , BankItem( BankPos) );
        std::swap( PlayerBaseData->Body.Item[ BodyPos ] , PlayerBaseData->Bank.Item[ BankPos ] );
        return EM_RoleData_OK;
    }

    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( BodyItem.OrgObjID );

    if( OrgDB == NULL )
    {
        GetBodyItem( BodyPos )->Init();
        GetBankItem( BankPos )->Init();
        return EM_RoleData_OrgObjIDErr;
    }

    if( OrgDB->MaxHeap == 1 )
    {
        std::swap( *GetBodyItem( BodyPos ) , *GetBankItem( BankPos ) );
        return EM_RoleData_OK;
    }

    if( OrgDB->MaxHeap >= GetBodyItem( BodyPos )->Count + GetBankItem( BankPos )->Count )
    {
        GetBankItem( BankPos )->Count += GetBodyItem( BodyPos )->Count;
        GetBodyItem( BodyPos )->Init();
        //GetBodyItem( BodyPos )->Count += GetBankItem( BankPos )->Count;
        //GetBankItem( BankPos )->Init();
    }
    else
    {
        GetBodyItem( BodyPos )->Count = GetBodyItem( BodyPos )->Count + GetBankItem( BankPos )->Count - OrgDB->MaxHeap;
        GetBankItem( BankPos )->Count = OrgDB->MaxHeap;

//       GetBankItem( BankPos )->Count = GetBankItem( BankPos )->Count + GetBodyItem( BodyPos )->Count - OrgDB->MaxHeap;
 //      GetBodyItem( BodyPos )->Count = OrgDB->MaxHeap;
    }


	if( GetBodyItem( BodyPos )->IsEmpty() == false )
		GetBodyItem( BodyPos )->Mode.Trade = !OrgDB->Mode.PickupBound;
	if( GetBankItem( BankPos )->IsEmpty() == false )
		GetBankItem( BankPos )->Mode.Trade = !OrgDB->Mode.PickupBound;
	
    TempData.UpdateInfo.Bank = true;
    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
bool    RoleDataEx::CheckBaseSetEQ( int EQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID )
{
    if( BodyOrgDB == NULL )
        return true;

	//////////////////////////////////////////////////////////////////////////
	//性別檢查
	GameObjDbStructEx* ImageObjDB = St_GetObjDB( ImageObjectID );
	if( ImageObjDB->IsItem() )
		ImageObjDB = St_GetObjDB( ImageObjDB->ImageID );

	if( ImageObjDB != NULL && ImageObjDB->Image.LimitSex._Sex != 0 )
	{
		switch( BaseData.Sex )
		{
		case EM_Sex_Boy:
			if( ImageObjDB->Image.LimitSex.Boy == false )
				return false;
			break;
		case EM_Sex_Girl:
			if( ImageObjDB->Image.LimitSex.Girl == false )
				return false;
			break;
		}
	}
	if( BodyOrgDB != NULL )
	{
		switch( BaseData.Sex )
		{
		case EM_Sex_Boy:
			if( BodyOrgDB->Limit.Sex.Boy == false )
				return false;
			break;
		case EM_Sex_Girl:
			if( BodyOrgDB->Limit.Sex.Girl == false )
				return false;
			break;
		}
	}
    
    if( BodyOrgDB->IsWeapon() )
    {
        switch( BodyOrgDB->Item.WeaponPos )
        {
        case EM_WeaponPos_MainHand:     
            {
                if( EQPos != EM_EQWearPos_MainHand )
                    return false;
            }
            break;
        case EM_WeaponPos_SecondHand:
            {
                if( EQPos != EM_EQWearPos_SecondHand )
                {
                    return false;
                }
				if( TempData.Attr.Fin.WearSkill.SecondHand == false )
				{
					return false;
				}
            }
            break;
        case EM_WeaponPos_OneHand:      
            {
                if(     EQPos != EM_EQWearPos_MainHand
                    &&  EQPos != EM_EQWearPos_SecondHand)
                    return false;

				if( EQPos == EM_EQWearPos_SecondHand && TempData.Attr.Fin.WearSkill.SecondHand == false )
				{
					return false;
				}
            }
            break;
        case EM_WeaponPos_TwoHand:      
            {
                if( EQPos != EM_EQWearPos_MainHand )
                    return false;

            }
            break;
        case EM_WeaponPos_Ammo:         
            {
                if( EQPos != EM_EQWearPos_Ammo )
                    return false;
            }
            break;
		case EM_WeaponPos_Bow:         
			{
				if( EQPos != EM_EQWearPos_Bow )
					return false;
			}
			break;
		case EM_WeaponPos_Manufacture:         
			{
				if( EQPos != EM_WeaponPos_Manufacture )
					return false;
			}
			break;
        }
    }
    else if( BodyOrgDB->IsArmor() )
    {
        switch( BodyOrgDB->Item.ArmorPos )
        {
        case EM_ArmorPos_Head:     
        case EM_ArmorPos_Gloves:	   
        case EM_ArmorPos_Shoes:	   
        case EM_ArmorPos_Clothes:
        case EM_ArmorPos_Pants:	   
        case EM_ArmorPos_Back:	   
        case EM_ArmorPos_Belt:	   
        case EM_ArmorPos_Shoulder:  
        case EM_ArmorPos_Necklace:  
            {
                if( EQPos != BodyOrgDB->Item.ArmorPos )
                    return false;
            }
            break;

        case EM_ArmorPos_Ring:  
            {
                if(     EQPos != EM_EQWearPos_Ring1 
                    &&  EQPos != EM_EQWearPos_Ring2 )
                    return false;
            }
            break;
        case EM_ArmorPos_Earring:
            {
                if(     EQPos != EM_EQWearPos_Earring1 
                    &&  EQPos != EM_EQWearPos_Earring2 )
                    return false;
            }
            break;
        case EM_ArmorPos_SecondHand:
            {
                if( EQPos != EM_EQWearPos_SecondHand )
                {
                    return false;
                }

				if( TempData.Attr.Fin.WearSkill.Shield == false && BodyOrgDB->Item.ArmorType == EM_Armor_Shield )
				{
					return false;
				}
            }
            break;
		case EM_ArmorPos_MagicTool:
			{
				if(		EQPos != EM_EQWearPos_MagicTool1 
					&&	EQPos != EM_EQWearPos_MagicTool2 
					&&	EQPos != EM_EQWearPos_MagicTool3 )
					return false;
			}
			break;
		case EM_ArmorPos_Ornament:
			{
				if( EQPos != EM_EQWearPos_Ornament )
					return false;
			}
			break;
        }
    }
    else 
    {
        return false;
    }
    
	if( CheckEQLimit( BodyOrgDB , IgnoreLimitLv ) == false )
		return false;

    return true;
}
//------------------------------------------------------------------------------------------------------------------------------------
//檢查裝備限制
bool	RoleDataEx::CheckEQLimit( GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv )
{
	if( BodyOrgDB->CheckItemAndEqSkill( TempData.Attr.Fin.WearSkill) == false )
		return false;

	if( CheckLimit( BodyOrgDB->Limit , IgnoreLimitLv  ) == false )
		return false;

	return true;
}

//檢查是否可以置換此項裝備
CheckSetEQResultENUM    RoleDataEx::CheckSetEQ( int OrgEQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID )
{
	//////////////////////////////////////////////////////////////////////////
	//性別檢查
	GameObjDbStructEx* ImageObjDB = St_GetObjDB( ImageObjectID );
	if( ImageObjDB->IsItem() )
		ImageObjDB = St_GetObjDB( ImageObjDB->ImageID );

	if( ImageObjDB != NULL && ImageObjDB->Image.LimitSex._Sex != 0 )
	{
		switch( BaseData.Sex )
		{
		case EM_Sex_Boy:
			if( ImageObjDB->Image.LimitSex.Boy == false )
				return EM_CheckSetEQResult_Failed;
			break;
		case EM_Sex_Girl:
			if( ImageObjDB->Image.LimitSex.Girl == false )
				return EM_CheckSetEQResult_Failed;
			break;
		}
	}
	if( BodyOrgDB != NULL )
	{
		switch( BaseData.Sex )
		{
		case EM_Sex_Boy:
			if( BodyOrgDB->Limit.Sex.Boy == false )
				return EM_CheckSetEQResult_Failed;
			break;
		case EM_Sex_Girl:
			if( BodyOrgDB->Limit.Sex.Girl == false )
				return EM_CheckSetEQResult_Failed;
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	switch( OrgEQPos )
	{
	case EM_EQWearPos_BK_MagicTool1://18
	case EM_EQWearPos_BK_MagicTool2://19
	case EM_EQWearPos_BK_MagicTool3://20
		return EM_CheckSetEQResult_Failed;
	}

	int Type	= OrgEQPos / _DEF_EQ_BACKUP_BASE_;
	int EQPos	= OrgEQPos % _DEF_EQ_BACKUP_BASE_;

    if( BodyOrgDB == NULL )
		return EM_CheckSetEQResult_OK;

	switch( Type )
	{
	case 0:
		{
			if( BodyOrgDB->CheckItemAndEqSkill( TempData.Attr.Fin.WearSkill) == false )
				return EM_CheckSetEQResult_Failed;

			if( CheckEQLimit( BodyOrgDB , IgnoreLimitLv ) == false )
				return EM_CheckSetEQResult_Failed;
			break;
		}
	case 1:
		{
		}
		break;
	case 2:
		return EM_CheckSetEQResult_Failed;
	}

	//裝備唯一檢查
	if( BodyOrgDB->Item.ItemUniqueType != 0 )
	{
		for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
		{
			if( i == EQPos )
				continue;
			GameObjDbStructEx*	TempEQDB = St_GetObjDB(  GetEqItem( i + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
			if( TempEQDB == NULL )
				continue;
			if( TempEQDB->Item.ItemUniqueType == BodyOrgDB->Item.ItemUniqueType )
				return EM_CheckSetEQResult_Failed_ItemUnique;
		}
	}


    if( BodyOrgDB->IsWeapon() )
    {
        switch( BodyOrgDB->Item.WeaponPos )
        {
        case EM_WeaponPos_MainHand:     
            {
                if( EQPos != EM_EQWearPos_MainHand )
                    return EM_CheckSetEQResult_Failed;
            }
            break;
        case EM_WeaponPos_SecondHand:
            {
                if( EQPos != EM_EQWearPos_SecondHand )
                {
                    return EM_CheckSetEQResult_Failed;
                }

				//檢查是否有雙手持的技能
				if( TempData.Attr.Fin.WearSkill.SecondHand == false && Type == 0 )
				{
					return EM_CheckSetEQResult_Failed;
				}

                //檢查主手是否是有裝備
                GameObjDbStructEx*	MainHandDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_MainHand + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
                if( MainHandDB != NULL && MainHandDB->Item.WeaponPos == EM_WeaponPos_TwoHand )
                {
					if( GetEqItem( EM_EQWearPos_SecondHand + _DEF_EQ_BACKUP_BASE_ * Type )->IsEmpty() == false )
						return EM_CheckSetEQResult_Failed;

                    return  EM_CheckSetEQResult_OKEx;
                }
            }
            break;
        case EM_WeaponPos_OneHand:      
            {
                if(     EQPos != EM_EQWearPos_MainHand
                    &&  EQPos != EM_EQWearPos_SecondHand)
                    return EM_CheckSetEQResult_Failed;

                if( EQPos == EM_EQWearPos_SecondHand )
                {

					//檢查是否有雙手持的技能
					if( TempData.Attr.Fin.WearSkill.SecondHand == false && Type == 0 )
					{
						return EM_CheckSetEQResult_Failed;
					}

                    //檢查主手是否是有裝備
                    GameObjDbStructEx*	MainHandDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_MainHand + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
                    if( MainHandDB != NULL && MainHandDB->Item.WeaponPos == EM_WeaponPos_TwoHand )
                    {
						if( GetEqItem( EM_EQWearPos_SecondHand + _DEF_EQ_BACKUP_BASE_ * Type )->IsEmpty() == false )
							return EM_CheckSetEQResult_Failed;

						return  EM_CheckSetEQResult_OKEx;
                    }
                }
            }
            break;
        case EM_WeaponPos_TwoHand:      
            {
                if( EQPos != EM_EQWearPos_MainHand )
                    return EM_CheckSetEQResult_Failed;
                //檢查副手是否是有裝備
                if( GetEqItem( EM_EQWearPos_SecondHand + _DEF_EQ_BACKUP_BASE_ * Type )->IsEmpty() == false )
                {
					if( GetEqItem( EM_EQWearPos_MainHand + _DEF_EQ_BACKUP_BASE_ * Type )->IsEmpty() == false )
						return EM_CheckSetEQResult_Failed;

					return  EM_CheckSetEQResult_OKEx;
                }
            }
            break;
        case EM_WeaponPos_Ammo:         
            {
                if( EQPos != EM_EQWearPos_Ammo )
                    return EM_CheckSetEQResult_Failed;
			
				if( BodyOrgDB->Item.WeaponType !=  EM_Weapon_Throw )
				{
					 //檢查弓的欄位
					GameObjDbStructEx*	BowDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_Bow + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
					if( BowDB != NULL )
					{
						//return EM_CheckSetEQResult_Failed;			
						if( BodyOrgDB->Item.WeaponType == EM_Weapon_Ammo_Bow 
							&& BowDB->Item.WeaponType != EM_Weapon_Bow 
							&& BowDB->Item.WeaponType != EM_Weapon_CossBow )
							return EM_CheckSetEQResult_Failed;
						if( BodyOrgDB->Item.WeaponType == EM_Weapon_Ammo_Gun && BowDB->Item.WeaponType != EM_Weapon_Gun )
							return EM_CheckSetEQResult_Failed;
					}
				}
				else
				{
					GameObjDbStructEx*	BowDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_Bow + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
					if( BowDB != NULL )
						return EM_CheckSetEQResult_Failed;
				}
            }
            break;
		case EM_WeaponPos_Bow:         
			{
				if( EQPos != EM_EQWearPos_Bow )
					return EM_CheckSetEQResult_Failed;

				//檢查彈藥的欄位
                GameObjDbStructEx*	AmmoDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_Ammo + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
                if( AmmoDB != NULL )
				{
					if( BodyOrgDB->Item.WeaponType == EM_Weapon_Bow && AmmoDB->Item.WeaponType != EM_Weapon_Ammo_Bow )
						return EM_CheckSetEQResult_Failed;
					if( BodyOrgDB->Item.WeaponType == EM_Weapon_CossBow && AmmoDB->Item.WeaponType != EM_Weapon_Ammo_Bow )
						return EM_CheckSetEQResult_Failed;
					if( BodyOrgDB->Item.WeaponType == EM_Weapon_Gun && AmmoDB->Item.WeaponType != EM_Weapon_Ammo_Gun )
						return EM_CheckSetEQResult_Failed;
				}
			}
			break;
		case EM_WeaponPos_Manufacture:         
			{
				if( EQPos != EM_EQWearPos_Manufactory )
					return EM_CheckSetEQResult_Failed;
			}
			break;
        }
    }
    else if( BodyOrgDB->IsArmor() )
    {
        switch( BodyOrgDB->Item.ArmorPos )
        {
        case EM_ArmorPos_Shoulder:  
        case EM_ArmorPos_Head:     
        case EM_ArmorPos_Gloves:	   
        case EM_ArmorPos_Shoes:	   
        case EM_ArmorPos_Clothes:
        case EM_ArmorPos_Pants:	   
        case EM_ArmorPos_Back:	   
        case EM_ArmorPos_Belt:	   
        case EM_ArmorPos_Necklace:  
            {
                if( EQPos != BodyOrgDB->Item.ArmorPos )
                    return EM_CheckSetEQResult_Failed;
            }
            break;

        case EM_ArmorPos_Ring:  
            {
                if(     EQPos != EM_EQWearPos_Ring1 
                    &&  EQPos != EM_EQWearPos_Ring2 )
                    return EM_CheckSetEQResult_Failed;
            }
            break;
        case EM_ArmorPos_Earring:
            {
                if(     EQPos != EM_EQWearPos_Earring1 
                    &&  EQPos != EM_EQWearPos_Earring2 )
                    return EM_CheckSetEQResult_Failed;
            }
            break;
        case EM_ArmorPos_SecondHand:
            {
                if( EQPos != EM_EQWearPos_SecondHand )
                {
                    return EM_CheckSetEQResult_Failed;
                }
				//檢查是否有雙手持的技能
				if( TempData.Attr.Fin.WearSkill.Shield == false && BodyOrgDB->Item.ArmorType == EM_Armor_Shield && Type == 0 )
				{
					return EM_CheckSetEQResult_Failed;
				}

                //檢查主手是否是有裝備
                GameObjDbStructEx*	MainHandDB = St_GetObjDB(  GetEqItem( EM_EQWearPos_MainHand + _DEF_EQ_BACKUP_BASE_ * Type )->OrgObjID );
                if( MainHandDB != NULL && MainHandDB->Item.WeaponPos == EM_WeaponPos_TwoHand )
                {
                    return  EM_CheckSetEQResult_OKEx;
                }
				
            }
            break;
		case EM_ArmorPos_MagicTool:
			if(		EQPos != EM_EQWearPos_MagicTool1 
				&&	EQPos != EM_EQWearPos_MagicTool2 
				&&	EQPos != EM_EQWearPos_MagicTool3	)
				return EM_CheckSetEQResult_Failed;
			break;
		case EM_ArmorPos_Ornament:
			if( EQPos != EM_EQWearPos_Ornament )
				return EM_CheckSetEQResult_Failed;
			break;
        }
    }
    else
    {
        return EM_CheckSetEQResult_Failed;
    }

    //if( CheckLimit( BodyOrgDB->Limit ) == false )
        //return false;


    return EM_CheckSetEQResult_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//身體與銀行交換物品
RoleDataResultENUM RoleDataEx::ExchangeBodyEQItem(	ItemFieldStruct& BodyItem , int BodyPos  
                                                  ,	ItemFieldStruct& EQItem   , int EQPos  
												  , bool IsFromEq )
{
    if( (unsigned int)BodyPos >= _MAX_BODY_COUNT_ || (unsigned int)EQPos >= EM_EQWearPos_MaxCount )
        return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , BodyPos ) == false )
		return EM_RoleData_PosErr;


    if(		CheckBodyItem( BodyItem , BodyPos ) == false
        ||	CheckEQItem( EQItem , EQPos ) == false )
        return EM_RoleData_DataInfoErr;

	if(		BodyItem.IsEmpty() != false 
		&&	( EQPos == EM_EQWearPos_MagicTool1 || EQPos == EM_EQWearPos_MagicTool2 || EQPos == EM_EQWearPos_MagicTool3 )  )
		return EM_RoleData_EQWearPosErr;

    GameObjDbStructEx*	BodyOrgDB;
    BodyOrgDB   = St_GetObjDB( BodyItem.OrgObjID );

	EQStruct* EQ;

	if( EQPos < _DEF_EQ_BACKUP_BASE_  )
		EQ = &BaseData.EQ;
	else
	{
		return EM_RoleData_EQWearPosErr;
	}
		//EQ = &PlayerBaseData->EQBackup;


	if(		PlayerBaseData->Body.Item[ BodyPos ].Pos != EM_ItemState_NONE
		||	EQ->Item[ EQPos ].Pos != EM_ItemState_NONE )
		return EM_RoleData_DataInfoErr;

	switch( CheckSetEQ( EQPos , BodyOrgDB , BodyItem.Mode.IgnoreLimitLv , BodyItem.ImageObjectID ) )
	{
	case EM_CheckSetEQResult_OK		:
		{
			////////////////////////////////////////////////////////////////////
			//檢查圖形資料是否符合
			if( BodyOrgDB != NULL )
			{
				GameObjDbStructEx*	BodyImageDB = St_GetObjDB( BodyItem.ImageObjectID );

				if( BodyImageDB != NULL )
				{
					GameObjDbStructEx* ImageObjDB = St_GetObjDB( BodyImageDB->ImageID ); 
					if( ImageObjDB != NULL )
					{
						switch( ImageObjDB->Image.LimitSex._Sex )
						{
						case 1:
							if( BaseData.Sex != EM_Sex_Boy )
								return EM_RoleData_EQWearPosErr;
							break;
						case 2:
							if( BaseData.Sex != EM_Sex_Girl )
								return EM_RoleData_EQWearPosErr;						
							break;
						}

					}
				}
			}
			////////////////////////////////////////////////////////////////////

			if(		EQPos == EM_EQWearPos_MagicTool1
				||	EQPos == EM_EQWearPos_MagicTool2 
				||	EQPos == EM_EQWearPos_MagicTool3 )
			{				
				EQ->Item[ EQPos ].Init();
				std::swap( PlayerBaseData->Body.Item[ BodyPos ] , EQ->Item[ EQPos ] );
			}
			else if( EQPos == EM_EQWearPos_Ammo && EQItem.OrgObjID == BodyItem.OrgObjID )
			{
				if( BodyOrgDB != NULL )
				{
					int AmmoCount = EQItem.Count + BodyItem.Count;
					if( IsFromEq != false )
					{
						if( AmmoCount > BodyOrgDB->MaxHeap )
						{
							PlayerBaseData->Body.Item[ BodyPos ].Count = BodyOrgDB->MaxHeap;
							EQ->Item[EQPos].Count = AmmoCount - BodyOrgDB->MaxHeap;
						}
						else
						{
							PlayerBaseData->Body.Item[ BodyPos ].Count = AmmoCount;
							EQ->Item[EQPos].Init();
						}
					}
					else
					{
						if( AmmoCount > BodyOrgDB->MaxHeap )
						{
							EQ->Item[EQPos].Count = BodyOrgDB->MaxHeap;
							PlayerBaseData->Body.Item[ BodyPos ].Count = AmmoCount - BodyOrgDB->MaxHeap;
						}
						else
						{
							EQ->Item[EQPos].Count = AmmoCount;
							PlayerBaseData->Body.Item[ BodyPos ].Init();
						}
					}
				}
//				BodyItem.Pos = EM_ItemState_NONE;
//				EQItem.Pos = EM_ItemState_NONE;
//				PlayerBaseData->Body.Item[ BodyPos ] = BodyItem;
//				BaseData.EQ->Item[ EQPos ] = EQItem;

			}
			else
			{
				std::swap( PlayerBaseData->Body.Item[ BodyPos ] , EQ->Item[ EQPos ] );
			}
			
			//std::swap( PlayerBaseData->Body.Item[ BodyPos ] , BaseData.EQ->Item[ EQPos ] );
			TempData.UpdateInfo.Eq   = true;
			TempData.UpdateInfo.Body = true;
			return EM_RoleData_OK;
		}
		break;
	case EM_CheckSetEQResult_OKEx	:	//主副手特殊處理
		{
			EQ->Item[ EQPos ] = PlayerBaseData->Body.Item[ BodyPos ];
			if( EQPos == EM_EQWearPos_MainHand )
			{
				PlayerBaseData->Body.Item[ BodyPos ] = EQ->Item[ EM_EQWearPos_SecondHand ];
				EQ->Item[ EM_EQWearPos_SecondHand ].Init();
			}
			else if( EQPos == EM_EQWearPos_SecondHand )
			{
				PlayerBaseData->Body.Item[ BodyPos ] = EQ->Item[ EM_EQWearPos_MainHand ];
				EQ->Item[ EM_EQWearPos_MainHand ].Init();
			}
			TempData.UpdateInfo.Eq   = true;
			TempData.UpdateInfo.Body = true;

			return EM_RoleData_OKEx_SpecialEq;

		}
		break;
	case EM_CheckSetEQResult_Failed	: 
		{
			return EM_RoleData_EQWearPosErr;
		}
		break;
	case EM_CheckSetEQResult_Failed_ItemUnique:
		return EM_RoleData_Err_ItemUnique;
	}
	return EM_RoleData_DataInfoErr;
}

//銀行與裝備交換物品
RoleDataResultENUM RoleDataEx::ExchangeBankEQItem(	ItemFieldStruct& BankItem , int BankPos  
												  ,	ItemFieldStruct& EQItem   , int EQPos   
												  , bool IsFromEq )
{
	if( (unsigned int)BankPos >= _MAX_BANK_COUNT_ || (unsigned int)EQPos >= EM_EQWearPos_MaxCount )
		return EM_RoleData_PosErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , BankPos , EQItem.OrgObjID  ) == false )
		return EM_RoleData_PosErr;

	if(		CheckBankItem( BankItem , BankPos ) == false
		||	CheckEQItem( EQItem , EQPos ) == false )
		return EM_RoleData_DataInfoErr;

	EQStruct* EQ;

	if( EQPos < _DEF_EQ_BACKUP_BASE_  )
		EQ = &BaseData.EQ;
	else
	{
		return EM_RoleData_PosErr;
	}
	//	EQ = &PlayerBaseData->EQBackup;

	if(		PlayerBaseData->Bank.Item[ BankPos ].Pos != EM_ItemState_NONE
		||	EQ->Item[ EQPos ].Pos != EM_ItemState_NONE )
		return EM_RoleData_DataInfoErr;

	GameObjDbStructEx*	BankOrgDB;
	BankOrgDB   = St_GetObjDB( BankItem.OrgObjID );
	switch( CheckSetEQ( EQPos , BankOrgDB , BankItem.Mode.IgnoreLimitLv , BankItem.ImageObjectID ) )
	{
	case EM_CheckSetEQResult_OK		:
		{
			////////////////////////////////////////////////////////////////////
			//檢查圖形資料是否符合
			if( BankOrgDB != NULL )
			{
				GameObjDbStructEx*	BankImageDB = St_GetObjDB( BankItem.ImageObjectID );
				if( BankImageDB != NULL )
				{
					GameObjDbStructEx* ImageObjDB = St_GetObjDB( BankImageDB->ImageID ); 
					if( ImageObjDB != NULL )
					{
						switch( ImageObjDB->Image.LimitSex._Sex )
						{
						case 1:
							if( BaseData.Sex != EM_Sex_Boy )
								return EM_RoleData_EQWearPosErr;
							break;
						case 2:
							if( BaseData.Sex != EM_Sex_Girl )
								return EM_RoleData_EQWearPosErr;						
							break;
						}
					}
				}
			}
			////////////////////////////////////////////////////////////////////
			if(		EQPos == EM_EQWearPos_MagicTool1 
				||	EQPos == EM_EQWearPos_MagicTool2
				||	EQPos == EM_EQWearPos_MagicTool3	)
			{
				EQ->Item[ EQPos ].Init();
				std::swap( PlayerBaseData->Bank.Item[ BankPos ] , EQ->Item[ EQPos ] );
			}
			else if( EQPos == EM_EQWearPos_Ammo && EQItem.OrgObjID == BankItem.OrgObjID )
			{
				if( BankOrgDB != NULL )
				{
					int AmmoCount = EQItem.Count + BankItem.Count;
					if( IsFromEq != false )
					{
						if( AmmoCount > BankOrgDB->MaxHeap )
						{
							PlayerBaseData->Bank.Item[ BankPos ].Count = BankOrgDB->MaxHeap;
							EQ->Item[EQPos].Count = AmmoCount - BankOrgDB->MaxHeap;
						}
						else
						{
							PlayerBaseData->Bank.Item[ BankPos ].Count = AmmoCount;
							EQ->Item[EQPos].Init();
						}
					}
					else
					{
						if( AmmoCount > BankOrgDB->MaxHeap )
						{
							EQ->Item[EQPos].Count = BankOrgDB->MaxHeap;
							PlayerBaseData->Bank.Item[ BankPos ].Count = AmmoCount - BankOrgDB->MaxHeap;
						}
						else
						{
							EQ->Item[EQPos].Count = AmmoCount;
							PlayerBaseData->Bank.Item[ BankPos ].Init();
						}
					}

				}
				//				BodyItem.Pos = EM_ItemState_NONE;
				//				EQItem.Pos = EM_ItemState_NONE;
				//				PlayerBaseData->Body.Item[ BodyPos ] = BodyItem;
				//				BaseData.EQ->Item[ EQPos ] = EQItem;

			}
			else
			{
				std::swap( PlayerBaseData->Bank.Item[ BankPos ] , EQ->Item[ EQPos ] );
			}

			//std::swap( PlayerBaseData->Body.Item[ BodyPos ] , BaseData.EQ->Item[ EQPos ] );
			TempData.UpdateInfo.Eq   = true;
			TempData.UpdateInfo.Bank = true;
			return EM_RoleData_OK;
			/*
			std::swap( PlayerBaseData->Bank.Item[ BankPos ] , BaseData.EQ->Item[ EQPos ] );
			TempData.UpdateInfo.Eq   = true;
			TempData.UpdateInfo.Bank = true;
			return EM_RoleData_OK;
			*/
		}
		break;
	case EM_CheckSetEQResult_OKEx	:	//主副手特殊處理
		{
			EQ->Item[ EQPos ] = PlayerBaseData->Bank.Item[ BankPos ];
			if( EQPos == EM_EQWearPos_MainHand )
			{
				PlayerBaseData->Bank.Item[ BankPos ] = EQ->Item[ EM_EQWearPos_SecondHand ];
				EQ->Item[ EM_EQWearPos_SecondHand ].Init();
			}
			else if( EQPos == EM_EQWearPos_SecondHand )
			{
				PlayerBaseData->Bank.Item[ BankPos ] = EQ->Item[ EM_EQWearPos_MainHand ];
				EQ->Item[ EM_EQWearPos_MainHand ].Init();
			}
			TempData.UpdateInfo.Eq   = true;
			TempData.UpdateInfo.Bank = true;

			return EM_RoleData_OKEx_SpecialEq;

		}
		break;
	case EM_CheckSetEQResult_Failed	: 
		{
			return EM_RoleData_EQWearPosErr;
		}
		break;
	case EM_CheckSetEQResult_Failed_ItemUnique:
		return EM_RoleData_Err_ItemUnique;

	}
	return EM_RoleData_DataInfoErr;
}

/*
//銀行與裝備交換物品
RoleDataResultENUM RoleDataEx::ExchangeBankEQItem(	    ItemFieldStruct& BankItem   , int BankPos 
                                                    ,   ItemFieldStruct& EQItem     , int EQPos  )
{
    if( (unsigned int)BankPos >= _MAX_BODY_COUNT_ || (unsigned int)EQPos >= EM_EQWearPos_MaxCount )
        return EM_RoleData_PosErr;

    if(		CheckBankItem( BankItem , BankPos ) == false
        ||	CheckEQItem( EQItem , EQPos ) == false )
        return EM_RoleData_DataInfoErr;


    GameObjDbStructEx*	OrgDB;
    OrgDB   = St_GetObjDB( BankItem.OrgObjID );
    if( CheckSetEQ( EQPos , OrgDB ) == false )
        return EM_RoleData_EQWearPosErr;

    std::swap( PlayerBaseData->Bank.Item[ BankPos ] , BaseData.EQ.Item[ EQPos ] );
	TempData.UpdateInfo.Eq   = true;
	TempData.UpdateInfo.Bank = true;
    return EM_RoleData_OK;
}
*/
bool    RoleDataEx::CheckEQSwap ( int Pos1, int Pos2 )
{
    GameObjDbStructEx*	OrgDB1;
    GameObjDbStructEx*	OrgDB2;

	if( (unsigned int)Pos1 >= EM_EQWearPos_MaxCount || (unsigned int)Pos1 >= EM_EQWearPos_MaxCount )
		return false;

    OrgDB1   = St_GetObjDB( GetEqItem( Pos1 )->OrgObjID );
    OrgDB2   = St_GetObjDB( GetEqItem( Pos2 )->OrgObjID );

    if( OrgDB1 != NULL )
    {
        if( OrgDB1->Item.Class == EM_Item_Weapon )
        {
            switch( OrgDB1->Item.WeaponPos )
            {
            case EM_WeaponPos_MainHand:     
            case EM_WeaponPos_SecondHand:
            case EM_WeaponPos_TwoHand:      
            case EM_WeaponPos_Ammo:         
            case EM_WeaponPos_Bow:         
			case EM_WeaponPos_Manufacture:

                return false;

            case EM_WeaponPos_OneHand:      
                {
                    if(     Pos2 != EM_EQWearPos_MainHand
                        &&  Pos2 != EM_EQWearPos_SecondHand)
                        return false;

					if( TempData.Attr.Fin.WearSkill.SecondHand == false )
					{
						return false;
//						if( OrgDB2 == NULL || OrgDB2->IsArmor() ) 
//							return false;
					}
                }
                break;
            }
        }
        else
        {
            switch( OrgDB1->Item.ArmorPos )
            {
            case EM_ArmorPos_Head:     
            case EM_ArmorPos_Gloves:	   
            case EM_ArmorPos_Shoes:	   
            case EM_ArmorPos_Clothes:
            case EM_ArmorPos_Pants:	   
            case EM_ArmorPos_Back:	   
            case EM_ArmorPos_Belt:	   
            case EM_ArmorPos_Shoulder:  
            case EM_ArmorPos_Necklace:  
            case EM_ArmorPos_SecondHand:
			case EM_ArmorPos_MagicTool:
			case EM_ArmorPos_Ornament:
                {
                    return false;
                }
                break;

            case EM_ArmorPos_Ring:  
                {
                    if(     Pos2 != EM_EQWearPos_Ring1 
                        &&  Pos2 != EM_EQWearPos_Ring2 )
                        return false;
                }
                break;
            case EM_ArmorPos_Earring:
                {
                    if(     Pos2 != EM_EQWearPos_Earring1 
                        &&  Pos2 != EM_EQWearPos_Earring2 )
                        return false;
                }
                break;
            }
        }
    }

    if( OrgDB2!= NULL )
    {
        if( OrgDB2->Item.Class == EM_Item_Weapon )
        {
            switch( OrgDB2->Item.WeaponPos )
            {
            case EM_WeaponPos_MainHand:     
            case EM_WeaponPos_SecondHand:
            case EM_WeaponPos_TwoHand:      
            case EM_WeaponPos_Ammo:         
			case EM_WeaponPos_Bow:         
			case EM_WeaponPos_Manufacture:
                return false;

            case EM_WeaponPos_OneHand:      
                {
                    if(     Pos1 != EM_EQWearPos_MainHand
                        &&  Pos1 != EM_EQWearPos_SecondHand)
                        return false;
                }
                break;
            }
        }
        else
        {
            switch( OrgDB2->Item.ArmorPos )
            {
            case EM_ArmorPos_Head:     
            case EM_ArmorPos_Gloves:	   
            case EM_ArmorPos_Shoes:	   
            case EM_ArmorPos_Clothes:
            case EM_ArmorPos_Pants:	   
            case EM_ArmorPos_Back:	   
            case EM_ArmorPos_Belt:	   
            case EM_ArmorPos_Shoulder:  
            case EM_ArmorPos_Necklace:  
            case EM_ArmorPos_SecondHand:
			case EM_ArmorPos_MagicTool:
			case EM_ArmorPos_Ornament:
                {
                    return false;
                }
                break;

            case EM_ArmorPos_Ring:  
                {
                    if(     Pos1 != EM_EQWearPos_Ring1 
                        &&  Pos1 != EM_EQWearPos_Ring2 )
                        return false;
                }
                break;
            case EM_ArmorPos_Earring:
                {
                    if(     Pos1 != EM_EQWearPos_Earring1 
                        &&  Pos1 != EM_EQWearPos_Earring2 )
                        return false;
                }
                break;
            }
        }
    }
    return true;
}

//裝備換物品
RoleDataResultENUM RoleDataEx::ExchangeEQItem(     ItemFieldStruct& Item1   , int Pos1  
                                               ,   ItemFieldStruct& Item2   , int Pos2  )
{
    if( Pos1 == Pos2 )
        return EM_RoleData_PosErr;

    if( (unsigned int)Pos1 >= EM_EQWearPos_MaxCount || Pos2 >= (unsigned int)EM_EQWearPos_MaxCount )
        return EM_RoleData_PosErr;

    if(		CheckEQItem( Item1 , Pos1 ) == false
        ||	CheckEQItem( Item2 , Pos2 ) == false )
        return EM_RoleData_DataInfoErr;

/*
    GameObjDbStruct*	OrgDB1;
    GameObjDbStruct*	OrgDB2;
    OrgDB1   = St_GetObjDB( Item1.OrgObjID );
    OrgDB2   = St_GetObjDB( Item2.OrgObjID );
*/
    if( CheckEQSwap( Pos1  , Pos2 ) == false )
        return EM_RoleData_EQWearPosErr;

    std::swap( BaseData.EQ.Item[ Pos1 ] , BaseData.EQ.Item[ Pos2 ] );
	TempData.UpdateInfo.Eq   = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//身體與銀行交換物品
RoleDataResultENUM RoleDataEx::ExchangeBankBodyItem(	ItemFieldStruct& BankItem , int BankPos  
                                                    ,   ItemFieldStruct& BodyItem , int BodyPos  )
{

    if( (unsigned int)BankPos >= _MAX_BANK_COUNT_ || (unsigned int)BodyPos >= _MAX_BODY_COUNT_ )
        return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , BodyPos ) == false )
		return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 1 , BankPos , BodyItem.OrgObjID ) == false )
		return EM_RoleData_PosErr;

    if(		CheckBodyItem( BodyItem , BodyPos ) == false
        ||	CheckBankItem( BankItem , BankPos ) == false )
        return EM_RoleData_DataInfoErr;


    if( BankItem.OrgObjID != BodyItem.OrgObjID 
		||	BankItem.Mode.HideCount != false 
		||	BodyItem.Mode.HideCount != false )
    {
        std::swap( PlayerBaseData->Body.Item[ BodyPos ] , PlayerBaseData->Bank.Item[ BankPos ] );
        return EM_RoleData_OK;
    }

    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( BodyItem.OrgObjID );

    if( OrgDB == NULL )
    {
        GetBodyItem( BodyPos )->Init();
        GetBankItem( BankPos )->Init();
        return EM_RoleData_OrgObjIDErr;
    }

    if( OrgDB->MaxHeap == 1  )
    {
         std::swap( PlayerBaseData->Body.Item[ BodyPos ] , PlayerBaseData->Bank.Item[ BankPos ] );
        return EM_RoleData_OK;
    }

    if( OrgDB->MaxHeap >= GetBodyItem( BodyPos )->Count + GetBankItem( BankPos )->Count )
    {
        GetBodyItem( BodyPos )->Count += GetBankItem( BankPos )->Count;
        GetBankItem( BankPos )->Init();
    }
    else
    {
        GetBankItem( BankPos )->Count = GetBankItem( BankPos )->Count + GetBodyItem( BodyPos )->Count - OrgDB->MaxHeap;
        GetBodyItem( BodyPos )->Count = OrgDB->MaxHeap;
    }

	if( GetBodyItem( BodyPos )->IsEmpty() == false )
		GetBodyItem( BodyPos )->Mode.Trade = !OrgDB->Mode.PickupBound;
	if( GetBankItem( BankPos )->IsEmpty() == false )
		GetBankItem( BankPos )->Mode.Trade = !OrgDB->Mode.PickupBound;

    TempData.UpdateInfo.Bank = true;
    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------------------------------------------------------
//把身上某欄位物品分出一部份到另外一個欄位
RoleDataResultENUM RoleDataEx::ApartBodyItem(	ItemFieldStruct& Item , int PosSrc 
                                            ,	int CountDes , int PosDes  )
{

    if( CountDes <= 0 )
        return EM_RoleData_ApartSizeErr;

	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , PosSrc ) == false )
		return EM_RoleData_PosErr;
	//租用資訊檢查
	if( CheckItemPosTimeFlag( 0 , PosDes ) == false )
		return EM_RoleData_PosErr;


    if( CheckBodyItem( Item , PosSrc ) == false )
        return EM_RoleData_DataInfoErr;

    //ItemFieldStruct *TempItem  = &( PlayerBaseData->ItemBody[PosSrc] );

    if( GetBodyItem( PosSrc )->Count < CountDes )
        return EM_RoleData_ApartSizeErr;

    int ResultCount = GetBodyItem( PosSrc )->Count - CountDes;
    GetBodyItem( PosSrc )->Count = CountDes;

    AddItemtoBody( *GetBodyItem( PosSrc ) , PosDes );

    GetBodyItem( PosSrc )->Count = ResultCount;

    if( ResultCount == 0 )
    {
        GetBodyItem( PosSrc )->Init();
    }

    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------
//加一個物品到暫存區
bool RoleDataEx::AddItemtoBuf	( ItemFieldStruct& Item )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( Item.OrgObjID );

    if( OrgDB == NULL )
        return false;

    if( OrgDB->IsKeyItem() )
    {
        int ID = RoleDataEx::KeyItemObjToID( OrgDB->GUID );
        if( BaseData.KeyItem.SetFlagOn( ID ) == false )
            return false;
		if( OrgDB->KeyItem.Type == EM_KeyItemType_SkillBook )
			TempData.UpdateInfo.SkillKeyItemChange = 1;

        return true;
    }

	if( OrgDB->Mode.Unique != false && CheckItemInBody( Item.OrgObjID ) )
	{
		Net_GameMsgEvent( EM_GameMessageEvent_Item_ItemUniqueErr );
		return false;
	}

    return PlayerBaseData->ItemTemp.Push_Back( Item );
}
//------------------------------------------------------------------------------------
//刪除暫存區的物件
bool RoleDataEx::DelItemFromBuf	( ItemFieldStruct& Item )
{
    if( PlayerBaseData->ItemTemp.Size() == 0 )
        return false;

    if(	Item != PlayerBaseData->ItemTemp[ 0 ] )
        return false;

    PlayerBaseData->ItemTemp.Pop_Front();

    return true;
}
//------------------------------------------------------------------------------------
RoleDataResultENUM    RoleDataEx::SetItemInfo_Body( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if(  (unsigned)Pos >= (unsigned)PlayerBaseData->Body.Count )
        return EM_RoleData_PosErr;

	/*
	//強制修正被SERVER鎖定物品
	if ( Item.Pos == EM_USE_ITEM )
		Item.Pos = EM_ItemState_NONE;
	*/

    *GetBodyItem(Pos) = Item;

    TempData.UpdateInfo.Body = true;
    return EM_RoleData_OK;

}
RoleDataResultENUM    RoleDataEx::SetItemInfo_Bank( ItemFieldStruct& Item , int Pos )
{
    //檢查是否超過可放置欄位
    if(  (unsigned) Pos >= (unsigned)PlayerBaseData->Bank.Count )
        return EM_RoleData_PosErr;

    *GetBankItem(Pos) = Item;

    TempData.UpdateInfo.Bank = true;
    return EM_RoleData_OK;
}
RoleDataResultENUM    RoleDataEx::SetItemInfo_EQ( ItemFieldStruct& Item , int OrgPos )
{
	switch( OrgPos )
	{
		case EM_EQWearPos_BK_MagicTool1:
		case EM_EQWearPos_BK_MagicTool2:
		case EM_EQWearPos_BK_MagicTool3:
			return EM_RoleData_PosErr;
	}

	int Type = OrgPos / _DEF_EQ_BACKUP_BASE_;
	int Pos = OrgPos % _DEF_EQ_BACKUP_BASE_;

    //檢查是否超過可放置欄位
    if(    (unsigned)Pos >= EM_EQWearPos_MaxCount )
        return EM_RoleData_PosErr;

	switch( Type )
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		break;
	default:
		return EM_RoleData_PosErr;
	}

    *GetEqItem(OrgPos) = Item;

    TempData.UpdateInfo.Eq = true;

    return EM_RoleData_OK;
}
//------------------------------------------------------------------------------------
//給予物品
bool	RoleDataEx::BaseGiveItem( ItemFieldStruct& Item  )
{

    //檢查此簡件是否是物品
    GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( Item.OrgObjID );
	Item.Pos = EM_ItemState_NONE;

    if( OrgDB == NULL )
        return false;

	if( OrgDB->IsNPC() )
	{
		int ItemID = St_CreateObj( Item.OrgObjID , X() , Y() , Z() , Dir() , Item.Count , -1 );
		St_AddToPartition( ItemID , BaseData.RoomID );
		return true;
	}
    if( OrgDB->IsKeyItem() )
    {
		return AddKeyItem( Item.OrgObjID );
    }
	else if( OrgDB->IsTitle() )
	{
		return AddTitle( Item.OrgObjID );
	}
	else if( OrgDB->IsItem() && OrgDB->Mode.AutoUseItem )
	{
		AutoUseItem( OrgDB );
		return true;
	}


	if( OrgDB->IsItem() == false && OrgDB->IsRecipe() == false )
		return false;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

    if( Item.Count > OrgDB->MaxHeap )
        return false;

    if( Item.Count <= 0 )
        return false;

	if( Item.ImageObjectID == 0 )
		Item.ImageObjectID = Item.OrgObjID;

	Item.Pos = EM_ItemState_NONE;

	if( Item.Mode._Mode == -1 )
	{
		Item.Mode._Mode = 0;

		Item.Mode.Trade = !(OrgDB->Mode.PickupBound);
		if( OrgDB->IsArmor() || OrgDB->IsWeapon() )
			Item.Mode.EQSoulBound = OrgDB->Mode.EQSoulBound;
		else
			Item.Mode.EQSoulBound = false;

		Item.Mode.HideCount = OrgDB->Mode.HideCount;
	}

	if( Item.Serial == 0 &&  Item.CreateTime == 0 )
	{
		Item.CreateTime = RoleDataEx::G_Now;
		Item.Serial		= St_GenerateItemVersion( );
		if( Item.Durable == 0)
			Item.Durable = OrgDB->Item.Durable * Item.Quality;

	}

	//////////////////////////////////////////////////////////////////////////
	//檢查身體是不是有重複的物品
	for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
	{
		if( PlayerBaseData->Body.Item[i] == Item )
		{
			return false;
		}
	}
	//檢查堆疊內是否有重複的物品
	for( int i = 0 ; i < PlayerBaseData->ItemTemp.Size() ; i++ )
	{
		if( PlayerBaseData->ItemTemp[i] == Item )
		{
			return false;
		}
	}
	//檢查堆疊內是否有重複的物品
	for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )
	{
		if( PlayerBaseData->Bank.Item[i] == Item )
		{
			return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	if( OrgDB->IsArmor() == false && OrgDB->IsWeapon() == false )
	{
		Item.Durable = 0;
		Item.ExValue = 0;
	}
	
	if(		OrgDB->Item.ItemType == EM_ItemType_Pet 
		&&	Item.Pet.PetOrgID	==	0 )
	{
		Item.Pet.CreateTime	= RoleDataEx::G_SysTime;
		Item.Pet.PetOrgID	= OrgDB->Item.Pet.PetObjID;
		Item.Pet.SkillPoint	= OrgDB->Item.Pet.SkillPoint;
		Item.Pet.PetType	= OrgDB->Item.Pet.PetType;
		Item.Pet.Property	= OrgDB->Item.Pet.Property;		//屬性(地水火風光暗)
		Item.Pet.Lv	= OrgDB->Item.Pet.Lv;
		Item.Pet.Talent	= OrgDB->Item.Pet.Talent;
		Item.Pet.STR	= OrgDB->Item.Pet.STR;
		Item.Pet.STA	= OrgDB->Item.Pet.STA;
		Item.Pet.INT	= OrgDB->Item.Pet.INT;
		Item.Pet.MND	= OrgDB->Item.Pet.MND;
		Item.Pet.AGI	= OrgDB->Item.Pet.AGI;	
		Item.Pet.TrainCount = 0;
	}


    //加一個物品到暫存區
    if(	AddItemtoBuf	( Item ) != true )		
		return false;

    //通知玩家
    Net_ItemInBuffer( Item );

    return true;

}
//----------------------------------------------------------------------------------------
bool	RoleDataEx::GiveItem( int ItemID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note )
{
	if( Count <= 0 )
		return false;
	
	int TObjID , TCount;
	if( GetTreasure( ItemID , TObjID  , TCount ) != false )
	{
		ItemID = TObjID;
		Count = TCount;
	}


    ItemFieldStruct	Item;

    St_NewItemInit( Item , ItemID , 0 );

    Item.Count	  = Count;
	Item.OrgObjID = ItemID;
	Item.RuneVolume = 0;

    return GiveItem( Item , Type , FromRole , Note );
}
//----------------------------------------------------------------------------------------
bool	RoleDataEx::GiveTreasure_Gamble( int OrgObjID , RoleDataEx* FromRole )
{
	GameObjDbStructEx* ObjDB = St_GetObjDB( OrgObjID );
	if( ObjDB->IsTreasure() == false )
		return false;

	int TObjID=0 , TCount=0;
	int TAddPowerID=0 , TAddPowerCount=0;
	if( GetTreasure( OrgObjID  , TObjID  , TCount ) == false )
	{
		TObjID = OrgObjID;
		TCount = 1;
	}
	

	ItemFieldStruct	Item;
	St_NewItemInit( Item , TObjID , 0  );
	Item.Count	  = TCount;

	GameObjDbStructEx* ItemObjDB = St_GetObjDB( TObjID );

	if( ItemObjDB == NULL )
		return false;

	//////////////////////////////////////////////////////////////////////////
	ItemDropStruct* DropItemAbility = ItemObjDB->Item.DropItemAbility;

	set< int >	InherentSet;
	int		Pos =0;

	//////////////////////////////////////////////////////////////////////////
	for( Pos = 0 ; Pos < 6 ; Pos++ )
	{
		if( Item.Inherent(Pos) == 0 )
			break;
	}

	DropItemAbility = ObjDB->Treasure.Gamble.DropItemAbility;
	if( ItemObjDB->IsArmor() || ItemObjDB->IsWeapon() )
	{
		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ && Pos < ItemObjDB->Item.MaxAttrCount  ; i++ )
		{
			int RandValue = Random( 100000 );
			if( RandValue >= DropItemAbility[i].Rate )
				continue;
			//////////////////////////////////////////////////////////////////////////
			//賭博掉落 
			if( RoleDataEx::GetTreasure( DropItemAbility[i].OrgID , TObjID  , TCount ) == false )
			{
				TObjID = DropItemAbility[i].OrgID;
				TCount = 1;
			}

			GameObjDbStructEx* AbilityObjDB = St_GetObjDB( TObjID );
			if( AbilityObjDB->IsAttribute() == false )
				continue;

			if( ItemObjDB->CheckInherentAbility( AbilityObjDB ) == false )
				continue;

			if( InherentSet.insert(TObjID).second == false )
				continue;

			Item.Inherent( Pos , TObjID );
			Pos++;

			//////////////////////////////////////////////////////////////////////////
		}

		{
			Item.RuneVolume = 0;
			for( int i = 0 ; i < ItemObjDB->Item.HoleBase && i < 2  ; i++ )
			{
				if( ItemObjDB->Treasure.Gamble.HoleRate[i] <= 0 )
					break;
				if( rand() % ObjDB->Treasure.Gamble.HoleRate[i] != 0 )
					break;
				Item.RuneVolume++;
			}
			
		}
	}

	char Buf[512];
	sprintf_s( Buf , sizeof(Buf) , "Gameble ObjID = %d" , OrgObjID );

	return GiveItem( Item , EM_ActionType_Gamble , FromRole , Buf );
}
//----------------------------------------------------------------------------------------
bool    RoleDataEx::GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , RoleDataEx* FromRole , const char* Note )
{
	if( BaseGiveItem( Item ) == false )
		return false;

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_ItemTrade(  FromRole , Type , Item , Note );
	return true;
}
bool    RoleDataEx::GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , int FromRoleDBID , int FromNpcDBID , const char* Note )
{
	if( BaseGiveItem( Item ) == false )
		return false;

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_ItemTrade	( FromRoleDBID , FromNpcDBID , Type , Item  , Note );
	return true;
}
//----------------------------------------------------------------------------------------
//加身上的金錢
bool RoleDataEx::AddBodyMoney( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog )
{
	if( Count == 0 )
		return true;
    if( CheckAddBodyMoney( Count ) == false ) 
        return false;

    PlayerBaseData->Body.Money += Count;

	if( SaveZoneLog )
	{
		if( Count > 0 )
			RoleDataEx::MoneyIn += Count;
		else
			RoleDataEx::MoneyOut -= Count;
	}

	Net_FixMoney(  );

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_Money( FromRole , Type , Count );

    return true;
}
//加身上的金錢
bool RoleDataEx::AddBodyMoney( int Count , int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , bool SaveZoneLog )
{
	if( Count == 0 )
		return true;
	if( CheckAddBodyMoney( Count ) == false ) 
		return false;

	PlayerBaseData->Body.Money += Count;

	if( SaveZoneLog )
	{
		if( Count > 0 )
			RoleDataEx::MoneyIn += Count;
		else
			RoleDataEx::MoneyOut -= Count;
	}

	Net_FixMoney(  );

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_Money( FromRoleDBID , FromNpcDBID , Type , Count );

	return true;
}
//----------------------------------------------------------------------------------------
//加身上的金錢
bool RoleDataEx::AddMoney_Bonus( int Count , RoleDataEx* FromRole , ActionTypeENUM Type )
{
	if( Count == 0 )
		return true;

//	if( CheckAddMoney_Bonus( Count ) == false ) 
//		return false;

	PlayerBaseData->Money_Bonus += Count;

	if( PlayerBaseData->Money_Bonus > _MAX_BONUSMONEY_COUNT_ )
		PlayerBaseData->Money_Bonus = _MAX_BONUSMONEY_COUNT_;

	Net_FixMoney(  );

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_Money_Bonus( FromRole , Type , Count );

	return true;
}

void RoleDataEx::AddLockAccountMoney( int Count, int LockDay)
{
	if( LockDay > 0 )
	{
		if( LockDay > Def_AccountMoneyLockTime_Max_Count_ )
		{
			PlayerBaseData->LockAccountMoney_Forever += Count;
		}
		else
		{
			PlayerBaseData->LockAccountMoney[ LockDay - 1 ] += Count;
		}

		TempData.UpdateInfo.AccountMoneyLockInfoChange = true;
		ResetLockAccountMoney();
	}
}

void RoleDataEx::FixLockMoney( int Count )
{
	int LockMoneySpent = 0;

	if( Count <= 0 )
		return;

	if( PlayerBaseData->LockAccountMoney_Forever > Count )
	{
		LockMoneySpent += Count;
		PlayerBaseData->LockAccountMoney_Forever -= Count;
		Count = 0;
	}
	else
	{
		LockMoneySpent += PlayerBaseData->LockAccountMoney_Forever;
		Count -= PlayerBaseData->LockAccountMoney_Forever;
		PlayerBaseData->LockAccountMoney_Forever = 0;
	}

	for( int i = Def_AccountMoneyLockTime_Max_Count_ -1  ; i >= 0  ; i-- )
	{
		if( PlayerBaseData->LockAccountMoney[i] == 0 )
			continue;

		if( Count > PlayerBaseData->LockAccountMoney[i] )
		{
			LockMoneySpent += PlayerBaseData->LockAccountMoney[i];
			Count -= PlayerBaseData->LockAccountMoney[i];
			PlayerBaseData->LockAccountMoney[i] = 0;
		}
		else
		{
			//Count -= PlayerBaseData->LockAccountMoney[i];
			LockMoneySpent += Count;
			PlayerBaseData->LockAccountMoney[i] -= Count;
			break;
		}
	}

	ResetLockAccountMoney();
	TempData.UpdateInfo.AccountMoneyLockInfoChange = true;

	//紀錄最後哪個Player用掉了多少LockMoney
	RoleDataEx::LastLockMoneySpentPlayerDBID = this->DBID();
	RoleDataEx::LastLockMoneySpent = LockMoneySpent;
}

//加身上的金錢
bool RoleDataEx::AddBodyMoney_Account( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog  , bool LockMoneyProc )
{
	if( Count == 0 )
		return true;

	if( CheckAddBodyMoney_Account( Count ) == false ) 
		return false;

	RoleDataEx::LastLockMoneySpentPlayerDBID = 0;
	RoleDataEx::LastLockMoneySpent = 0;

	PlayerBaseData->Body.Money_Account += Count;

	if( LockMoneyProc != false )
	{
		FixLockMoney( Count * -1 );
	}

	if( SaveZoneLog )
	{
		if( Count > 0 )
			RoleDataEx::AccountMoneyIn += Count;
		else
			RoleDataEx::AccountMoneyOut -= Count;
	}

	Net_FixMoney(  );

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_Money_Account( FromRole , Type , Count );

	Net_BillingNotify( Account_ID(), DBID(), Count );

	return true;
}

bool RoleDataEx::AddBodyMoney_Account( int Count , int FromRoleDBID , int FromNpcDBID  , ActionTypeENUM Type , bool SaveZoneLog  , bool LockMoneyProc )
{
	if( Count == 0 )
		return true;

	if( LockMoneyProc == false )
	{
		if( Count < 0 && OkAccountMoney() < Count * -1 )
			return false;
	}

	if( CheckAddBodyMoney_Account( Count ) == false ) 
		return false;

	RoleDataEx::LastLockMoneySpentPlayerDBID = 0;
	RoleDataEx::LastLockMoneySpent = 0;

	PlayerBaseData->Body.Money_Account += Count;

	if( LockMoneyProc != false )
	{
		FixLockMoney( Count * -1 );
	}

	if( SaveZoneLog )
	{
		if( Count > 0 )
			RoleDataEx::AccountMoneyIn += Count;
		else
			RoleDataEx::AccountMoneyOut -= Count;
	}

	Net_FixMoney(  );

	if( TempData.Sys.GM_Designed != false )
		return true;

	Log_Money_Account( FromRoleDBID , FromNpcDBID  , Type , Count );

	Net_BillingNotify( Account_ID(), DBID(), Count );

	return true;
}
/*
//加銀行的金錢
bool RoleDataEx::AddBankMoney( int Count )
{
	if( Count == 0 )
		return true;

    if( CheckAddBankMoney( Count ) == false ) 
        return false;

    PlayerBaseData->Bank.Money += Count;
    TempData.UpdateInfo.Money = true;
    return true;
}
*/
//----------------------------------------------------------------------------------------
//檢查加身上的金錢
bool RoleDataEx::CheckAddBodyMoney( int Count )
{
    if(     PlayerBaseData->Body.Money + Count < 0 
        ||  PlayerBaseData->Body.Money + Count > _MAX_MONEY_COUNT_ )    
        return false;
    return true;
}

//檢查加身上的金錢
bool RoleDataEx::CheckAddBodyMoney_Account( int Count )
{
	if(     PlayerBaseData->Body.Money_Account + Count < 0 
		||  PlayerBaseData->Body.Money_Account + Count > _MAX_MONEY_COUNT_ )    
		return false;
	return true;
}

bool RoleDataEx::CheckAddMoney_Bonus( int Count )
{
	if(     PlayerBaseData->Money_Bonus + Count < 0 
		||  PlayerBaseData->Money_Bonus + Count > _MAX_BONUSMONEY_COUNT_ )    
		return false;
	return true;
}
/*
//檢查加銀行的金錢
bool RoleDataEx::CheckAddBankMoney( int Count )
{
    if(     PlayerBaseData->Bank.Money + Count < 0 
        ||  PlayerBaseData->Bank.Money + Count > _MAX_MONEY_COUNT_ )    
        return false;
    return true;
}
*/
//----------------------------------------------------------------------------------------
//計算身體上的交易物品有幾個
int		RoleDataEx::CalBodyTradeItemCount()
{
    int				Count = 0;
    ItemState_ENUM	WearPos;
    int				i;

    for( i = _MAX_BODY_BEGIN_POS_ ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        WearPos = PlayerBaseData->Body.Item[i].Pos;
        if(		WearPos >= EM_TRADE_ITEM1 
            &&  WearPos <= EM_TRADE_ITEM25 )
            Count++;
    }

    return Count;
}

//計算身上有多少個交易物品
int		RoleDataEx::CalTradeItemCount()
{
    int				Count = 0;
    ItemState_ENUM	WearPos;
    int				i;

    for( i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        WearPos = PlayerBaseData->Body.Item[i].Pos;
        if(		WearPos >= EM_TRADE_ITEM1 
            &&  WearPos <= EM_TRADE_ITEM25 )
            Count++;
    }

    return Count;
}
//----------------------------------------------------------------------------------------
//計算有多少個空欄位
/*
int		RoleDataEx::CalEmptyItemCount()
{
	int RetCount = 0;
	for( int i = _MAX_BODY_BEGIN_POS_ ; i < PlayerBaseData->Body.Count ; i++ )
	{	
		if( CheckItemPosTimeFlag( 0 , i ) == false )
			continue;
		if( PlayerBaseData->Body.Item[i].IsEmpty() )
			RetCount++;
	}
	return RetCount;
}
*/
//-----------------------------------------------------------------------------------------------
//清除所有交易中的物品 至 物品欄
void		RoleDataEx::ClsAllTradeItem()
{

    ItemState_ENUM	WearPos;
    int				i;

    for( i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        WearPos = PlayerBaseData->Body.Item[i].Pos;
        if(		WearPos >= EM_TRADE_ITEM1 
            &&  WearPos <= EM_TRADE_ITEM25 )
        {
            PlayerBaseData->Body.Item[i].Pos = EM_ItemState_NONE;
        }
    }

    TempData.UpdateInfo.Body = true;
}
//-----------------------------------------------------------------------------------------------
//清除所有交易中的物品 至 物品欄
void		RoleDataEx::DelAllTradeItem()
{

    ItemState_ENUM	WearPos;
    int				i;

    for( i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        WearPos = PlayerBaseData->Body.Item[i].Pos;
        if(		WearPos >= EM_TRADE_ITEM1 
            &&  WearPos <= EM_TRADE_ITEM25 )
        {
            PlayerBaseData->Body.Item[i].Init();
        }
    }

    TempData.UpdateInfo.Body = true;
}
//----------------------------------------------------------------------------------------
//身上物品數量計算

int     RoleDataEx::CalBodyItemCountNoLock( int OrgID )
{
	GameObjDbStructEx* OrgDB = St_GetObjDB( OrgID );
	if( OrgDB == NULL )
	{
		return 0;
	}
	if( OrgDB->IsTitle() )
	{
		int ID = OrgDB->GUID -  Def_ObjectClass_Title;
		return PlayerBaseData->Title.GetFlag( ID );
	}

	int Count  = 0;
	for( int i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
	{
		if(		PlayerBaseData->Body.Item[i].OrgObjID == OrgID )
			Count += PlayerBaseData->Body.Item[i].Count;
	}
	return Count;
}

int     RoleDataEx::CalBodyItemCount( int OrgID, bool ignoreLocked)
{
	GameObjDbStructEx* OrgDB = St_GetObjDB( OrgID );
	if( OrgDB == NULL )
	{
		return 0;
	}
	if( OrgDB->IsTitle() )
	{
		int ID = OrgDB->GUID -  Def_ObjectClass_Title;
		return PlayerBaseData->Title.GetFlag( ID );
	}

    int Count  = 0;
    for( int i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        if(		PlayerBaseData->Body.Item[i].OrgObjID == OrgID 
			&&  (ignoreLocked || PlayerBaseData->Body.Item[i].Pos <= EM_ItemState_NONE)
			&&	PlayerBaseData->Body.Item[i].Mode.ItemLock == false )
            Count += PlayerBaseData->Body.Item[i].Count;
    }
    return Count;
}
int     RoleDataEx::CalBankItemCount( int OrgID )
{
    int Count  = 0;
    for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i ++ )
    {
        if(		PlayerBaseData->Bank.Item[i].OrgObjID == OrgID 
			&&  PlayerBaseData->Bank.Item[i].Pos <= EM_ItemState_NONE 
			&&	PlayerBaseData->Bank.Item[i].Mode.ItemLock == false	)
            Count += PlayerBaseData->Bank.Item[i].Count;
    }
    return Count;
}
int     RoleDataEx::CalEqItemCount( int OrgID )
{
    int Count  = 0;
    for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i ++ )
    {
        if(		BaseData.EQ.Item[i].OrgObjID == OrgID 
			&&  BaseData.EQ.Item[i].Pos <= EM_ItemState_NONE 
			&&	BaseData.EQ.Item[i].Mode.ItemLock == false	)
            Count += BaseData.EQ.Item[i].Count;
    }
    return Count;
}

bool	RoleDataEx::CheckItemInBody( int OrgID, bool inBank, bool inEQ )
{
	int Count  = 0;

	for( int i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
	{
		if(	PlayerBaseData->Body.Item[i].OrgObjID == OrgID )
			return true;
	}

	if ( inBank )
	{
		for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i ++ )
		{
			if(	PlayerBaseData->Bank.Item[i].OrgObjID == OrgID )
				return true;
		}
	}

	if ( inEQ )
	{
		for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i ++ )
		{
			if(	BaseData.EQ.Item[i].OrgObjID == OrgID )
				return true;
		}


		for( int j = 0 ; j < _MAX_BACKUP_EQ_SET_COUNT_ ; j++ )
		{
			for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i ++ )
			{
				if( PlayerBaseData->EQBackup[j].Item[i].OrgObjID == OrgID )
					return true;
			}
		}
	}
	
	return false;
}

//-----------------------------------------------------------------------------------------------------------------
// 取得身上與銀行內的物品 ObjID
int		RoleDataEx::GetBodyItemIDByName(const char* name)
{
	if ( name && name[0] ) {
		BodyItemStruct &bodyItems = PlayerBaseData->Body;
		for ( int i = 0; i < bodyItems.Count; i++ )
		{
			if ( bodyItems.Item[i].IsEmpty() ) {
				continue;
			} else {
				char itemName[MAX_PATH];
				GetItemFieldName( &bodyItems.Item[i], itemName, MAX_PATH );
				if ( strcmp(itemName, name) == 0 ) {
					return bodyItems.Item[i].OrgObjID;
				}
			}
		}
	}

	return 0;
}

//----------------------------------------------------------------------------------------
int		RoleDataEx::GetBankItemIDByName(const char* name)
{
	if ( name && name[0] ) {
		BankItemStruct &bankItem = PlayerBaseData->Bank;
		for ( int i = 0; i < bankItem.Count; i++ )
		{
			if ( bankItem.Item[i].IsEmpty() ) {
				continue;
			} else {
				char itemName[MAX_PATH];
				GetItemFieldName( &bankItem.Item[i], itemName, MAX_PATH );
				if ( strcmp(itemName, name) == 0 ) {
					return bankItem.Item[i].OrgObjID;
				}
			}
		}
	}

	return 0;
}
//----------------------------------------------------------------------------------------

//刪除身上的某物品
bool     RoleDataEx::DelBodyItem( int OrgID , int Count , ActionTypeENUM Type  )
{
	ItemFieldStruct DelItemInfo;
	DelItemInfo.Init();
	int			OrgCount = Count;
	//撿查是否為KeyItem
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );
	if( OrgDB == NULL )
		return false;
	if( OrgDB->IsKeyItem() )	
	{
		if( Count != 1 )
			return false;

		return DelKeyItem( OrgID );
	}
	if( OrgDB->IsTitle() )
	{
		if( Count != 1 )
			return false;

		return DelTitle( OrgID );
	}

    if( ( ( unsigned int )CalBodyItemCount( OrgID ) + ( unsigned int )CountItemFromQueue( OrgID ) ) < (unsigned int)Count )
        return false;


	for( int i = 0 ; i < PlayerBaseData->ItemTemp.Size() ; i ++ )
	{
		if( Count == 0 )
			break;

		if(	PlayerBaseData->ItemTemp[i].OrgObjID == OrgID )
		{
			if( DelItemInfo.IsEmpty() )
				DelItemInfo = PlayerBaseData->ItemTemp[i];

			if( Count >= PlayerBaseData->ItemTemp[i].Count )
			{
				Log_ItemDestroy( Type , PlayerBaseData->ItemTemp[i] , -1 , "" );
				Count -= PlayerBaseData->ItemTemp[i].Count;
				
				PlayerBaseData->ItemTemp[i].Init();
			}
			else
			{
				Log_ItemDestroy( Type , PlayerBaseData->ItemTemp[i] , Count , "" );
				PlayerBaseData->ItemTemp[i].Count -= Count;
				break;
			}	
		}
		
	}

    
    for( int i = 0 ; i < PlayerBaseData->Body.Count ; i ++ )
    {
        if( Count == 0 )
            break;

        if(		PlayerBaseData->Body.Item[i].OrgObjID == OrgID 
			&&  PlayerBaseData->Body.Item[i].Pos == EM_ItemState_NONE )
        {
			//檢查物品被鎖定
			if( PlayerBaseData->Body.Item[i].Mode.ItemLock != false )
				continue;

			if( DelItemInfo.IsEmpty() )
				DelItemInfo = PlayerBaseData->Body.Item[i];

            if( Count >=  PlayerBaseData->Body.Item[i].Count )
			{
				Log_ItemDestroy( Type , PlayerBaseData->Body.Item[i]  , -1 , "" );
                Count -= PlayerBaseData->Body.Item[i].Count;
				PlayerBaseData->Body.Item[i].Init();
				Net_FixItemInfo_Body( i );
			}
            else
            {
				Log_ItemDestroy( Type , PlayerBaseData->Body.Item[i] , Count , "" );
                PlayerBaseData->Body.Item[i].Count -= Count;
				Net_FixItemInfo_Body( i );
                break;
			}
        }
    }
	DelItemInfo.Count = OrgCount;
	Net_SC_DelItemMsg( DelItemInfo );
    return true;
}
//----------------------------------------------------------------------------------------
//刪除重要物品
bool    RoleDataEx::DelKeyItem( int OrgID )
{	
    int		ID		= RoleDataEx::KeyItemObjToID( OrgID );

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsKeyItem() == false )
		return false;

	bool	bResult = BaseData.KeyItem.SetFlagOff( ID );

	if( OrgDB->KeyItem.Type == EM_KeyItemType_SkillBook )
		TempData.UpdateInfo.SkillKeyItemChange = 1;
	else if( OrgDB->KeyItem.Type == EM_KeyItemType_LifeSkillUnLock ) 
	{
		CalLifeSkillMaxValue();
	}

	Net_FixKeyItemFlag( OrgID , false );
	return bResult;

}
bool	RoleDataEx::AddKeyItem( int OrgID )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsKeyItem() == false )
		return false;

	int ID = RoleDataEx::KeyItemObjToID( OrgDB->GUID );

	if( BaseData.KeyItem.GetFlag( ID ) != false )
		return false;

	if( BaseData.KeyItem.SetFlagOn( ID ) == false )
		return false;

	Net_FixKeyItemFlag( OrgID , true );

	switch( OrgDB->KeyItem.Type )
	{
	case EM_KeyItemType_SkillBook:
		{
			TempData.UpdateInfo.SkillKeyItemChange = 1;
		} break;

	case EM_KeyItemType_LifeSkillUnLock:
		{
			CalLifeSkillMaxValue();
		} break;
	case EM_KeyItemType_DailyFlag:
		{
			//if( PlayerBaseData->TimeFlag[ EM_TimeFlagEffect_DailyFlag ] == -1 )
			{
				__time32_t				NextRestTime;
				__time32_t				NowTime;
				struct	tm*				gmt;


				_time32( &NowTime );
				gmt = _localtime32( &NowTime );

				NowTime = (int)_mktime32( gmt ) + RoleDataEx::G_TimeZone *60*60;

				//計算前天重置時間的秒數 ( 目前預設是早上 06:00 )

				if( gmt->tm_hour < DF_DAILY_RESET_TIME )
				{
					gmt->tm_hour	= DF_DAILY_RESET_TIME;// + RoleDataEx::G_TimeZone;
					gmt->tm_sec		= 0;
					gmt->tm_min		= 0;
					//gmt->tm_mday	= gmt->tm_mday - 1;
					NextRestTime	= (int)_mktime32( gmt ) + RoleDataEx::G_TimeZone *60*60;
				}
				else
				{
					gmt->tm_hour	= DF_DAILY_RESET_TIME;// + RoleDataEx::G_TimeZone;
					gmt->tm_sec		= 0;
					gmt->tm_min		= 0;
					gmt->tm_mday	= gmt->tm_mday + 1;
					NextRestTime	= (int)_mktime32( gmt )  + RoleDataEx::G_TimeZone *60*60;
				}

				int iReminMin =  abs( NextRestTime - NowTime ) / 60;
				PlayerBaseData->TimeFlag[ EM_TimeFlagEffect_DailyFlag ] = iReminMin;
			}

		} break;
	}



	return true;
}

bool    RoleDataEx::DelTitle( int OrgID )
{

	int		ID		= OrgID - Def_ObjectClass_Title;

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsTitle() == false )
		return false;

	if( BaseData.TitleID == OrgID )
		BaseData.TitleID = 0;

	bool	bResult = PlayerBaseData->Title.SetFlagOff( ID );
	if( bResult == false )
		return false;
	
	Net_FixTitleFlag( OrgID , false );
	PlayerBaseData->TitleCount --;
	TempData.UpdateInfo.Recalculate_All = true;
	return true;

}
bool	RoleDataEx::AddTitle( int OrgID )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsTitle() == false )
		return false;

	int ID = OrgDB->GUID -  Def_ObjectClass_Title;

	if( PlayerBaseData->Title.GetFlag( ID ) != false )
		return false;

	if( PlayerBaseData->Title.SetFlagOn( ID ) == false )
		return false;

	Net_FixTitleFlag( OrgID , true );
	
	PlayerBaseData->TitleCount ++;
	TempData.UpdateInfo.Recalculate_All = true;
	return true;
}

bool    RoleDataEx::DelCard( int OrgID )
{

	int		ID		= OrgID - Def_ObjectClass_Card;

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsCard() == false )
		return false;
	
	if( PlayerBaseData->Card.GetFlag( ID ) == false )
		return false;

	PlayerBaseData->Card.SetFlagOff( ID );

	Net_FixCardFlag( OrgID , false );
	TempData.UpdateInfo.Recalculate_All = true;
	return true;

}
bool	RoleDataEx::AddCard( int OrgID )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );

	if( OrgDB->IsCard() == false )
		return false;

	int ID = OrgDB->GUID -  Def_ObjectClass_Card;

	if( PlayerBaseData->Card.GetFlag( ID ) != false )
		return false;

	if( PlayerBaseData->Card.SetFlagOn( ID ) == false )
		return false;

	Net_FixCardFlag( OrgID , true );

	TempData.UpdateInfo.Recalculate_All = true;
	return true;
}
//----------------------------------------------------------------------------------------
bool    RoleDataEx::CheckLimit( LimitStruct& Limit , bool IgnoreLimitLv  )
{
    //
	if( Limit.Voc._Voc != 0 && TestBit( Limit.Voc._Voc , TempData.Attr.Voc ) == false )
		return false;

	if( Limit.Race._Race != 0 && TestBit(Limit.Race._Race , TempData.Attr.Race) == false )
		return false;

	if( Limit.Sex._Sex != 0 && TestBit(Limit.Sex._Sex , TempData.Attr.Sex) == false )
		return false;

	if( IgnoreLimitLv == false )
	{
		if( Level() < Limit.Level )
			return false;
	}

    if( Limit.AGI > (int)TempData.Attr.Fin.AGI )
        return false;

    if( Limit.INT > (int)TempData.Attr.Fin.INT )
        return false;

    if( Limit.MND > (int)TempData.Attr.Fin.MND )
        return false;

    if( Limit.STR > (int)TempData.Attr.Fin.STR )
        return false;

    if( Limit.STA > (int)TempData.Attr.Fin.STA )
        return false;

    return true;
}

//取得寶物 Dlv = 死者 - 攻擊者
bool RoleDataEx::GetTreasure( int TreasureID , int& ObjID  , int& Count , int DLv )
{

	GameObjDbStructEx* OrgDB = St_GetObjDB( TreasureID );

	if( OrgDB == NULL )
		return false;

	if( !OrgDB->IsTreasure() )
	{
		return false;
	}

	if( DLv < OrgDB->Treasure.NeedDLv )
		return false;

	if( LuaCheckFunction(0,0,OrgDB->Treasure.LuaCheckScript) == false )
		return false;
	
	int RValue = Random( 100000 );// % 10000 + ( rand() %10 * 10000 );

	for( int i = 0 ; i < OrgDB->Treasure.ItemCount ; i++ )
	{
		RValue -= OrgDB->Treasure.Item[i].Count;
		if( RValue < 0 )
		{
			ObjID = OrgDB->Treasure.Item[i].OrgID;
			Count = OrgDB->Treasure.Item[i].DropCount;//Random( OrgDB->Treasure.Item[i].DropCount );

			GameObjDbStructEx* ItemDB = St_GetObjDB( ObjID );
			if( ItemDB->IsTreasure() )
			{
				return GetTreasure( ObjID , ObjID , Count , DLv );
			}
			return true;
		}
	}
	
	return false;

}

//檢查是否有某個重要物品
bool	RoleDataEx::CheckKeyItem( int KeyItemID )
{
	bool Ret = BaseData.KeyItem.GetFlag( RoleDataEx::KeyItemObjToID( KeyItemID ) );
		
	return Ret;

}

//////////////////////////////////////////////////////////////////////////
/*
bool	RoleDataEx::AddDropItem( int OwnerDBID , ItemFieldStruct& Item )
{
//	if( PlayerBaseData->Body.Count >= 30 )	
//		return false;

	DynamicData.TreasureBox->Item[ PlayerBaseData->Body.Count ]  = Item;
	DynamicData.TreasureBox->Count++;
	return true;
}
*/