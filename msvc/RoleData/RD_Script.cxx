#include "RoleDataEx.h"



#ifdef _LOCAL_SERVER_
#include "../MainProc/GuildManage/GuildManage.h"
#include "../mainproc/ObjectDataClass.h"
#endif
#ifdef _CLIENT
#include "../Interface/WorldFrames/GuildFrame.h"
#include "../mainproc/ObjectDataClass.h"
#endif

//-------------------------------------------------------------------------------------------------
//給物品到戰利品(Party分響)
bool    RoleDataEx::Sc_GiveItemToParty( int OrgID , int Count )
{
	return false;
}
//給物品到個人 TempBuffer(任物旗標)
bool    RoleDataEx::Sc_GiveItemToBuf( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note )
{
	return GiveItem( OrgID , Count , Type , FromRole , Note );
}
//-------------------------------------------------------------------------------------------------
int RoleDataEx::GetBodyFreeSlot()
{
	int EmptyCount = PlayerBaseData->ItemTemp.Size() * -1;
	for( int i = _MAX_BODY_BEGIN_POS_ ; i < PlayerBaseData->Body.Count ; i++ )
	{
		//租用資訊檢查
		if( CheckItemPosTimeFlag( 0 , i ) == false )
			continue;

		if( PlayerBaseData->Body.Item[i].IsEmpty() )
		{
			EmptyCount++;
			/*
			if( EmptyCount >= 1 )
				break;
			*/
		}
	}

	return EmptyCount;
}
//-------------------------------------------------------------------------------------------------
int RoleDataEx::CountItemFromQueue( int iGUID )
{
	//StaticVector< ItemFieldStruct , _MAX_TEMP_COUNT_ > ItemTemp;

	int iCount	= 0;
	int iSize	= PlayerBaseData->ItemTemp.Size();

	for( int i = 0; i < iSize; i++ )
	{
		if( PlayerBaseData->ItemTemp[ i ].OrgObjID == iGUID )
		{
			iCount++;
		}
	}

	return iCount;
}
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::Sc_GiveItemToBodyFreeSlot( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note )
{
	int EmptyCount = PlayerBaseData->ItemTemp.Size() * -1;
	for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
	{
		if( PlayerBaseData->Body.Item[i].IsEmpty() )
		{
			EmptyCount++;
			if( EmptyCount >= 1 )
				break;
		}
	}
	if( EmptyCount <= 0 )
		return false;

	return GiveItem( OrgID , Count , Type , FromRole , Note );
}
//-------------------------------------------------------------------------------------------------
//刪除物品
bool    RoleDataEx::Sc_DelItemFromBody( int OrgID , int Count , ActionTypeENUM Type )
{
	return DelBodyItem( OrgID , Count , Type );
}

bool    RoleDataEx::Sc_DelItem( int OrgID , int Count , ActionTypeENUM Type )
{
//	DelBodyItem( OrgID , Count , Type );
//	DelBankItem( OrgID , Count , Type );
	ItemFieldStruct DelItemInfo;
	DelItemInfo.Init();
	int			OrgCount = Count;
	//撿查是否為KeyItem
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgID );
	if( OrgDB == NULL )
		return false;

	if( OrgDB->IsKeyItem() != false )
	{
		DelKeyItem( OrgID );
		return true;
	}

	if( CalBodyItemCount( OrgID ) + CalBankItemCount( OrgID ) < (unsigned int)Count )
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

	for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i ++ )
	{
		if( Count == 0 )
			break;

		if(		PlayerBaseData->Bank.Item[i].OrgObjID == OrgID 
			&&  PlayerBaseData->Bank.Item[i].Pos == EM_ItemState_NONE )
		{
			//檢查物品被鎖定
			if( PlayerBaseData->Bank.Item[i].Mode.ItemLock != false )
				continue;

			if( DelItemInfo.IsEmpty() )
				DelItemInfo = PlayerBaseData->Bank.Item[i];

			if( Count >=  PlayerBaseData->Bank.Item[i].Count )
			{
				Log_ItemDestroy( Type , PlayerBaseData->Bank.Item[i]  , -1 , "" );
				Count -= PlayerBaseData->Bank.Item[i].Count;
				PlayerBaseData->Bank.Item[i].Init();
				Net_FixItemInfo_Bank( i );
			}
			else
			{
				Log_ItemDestroy( Type , PlayerBaseData->Bank.Item[i] , Count , "" );
				PlayerBaseData->Bank.Item[i].Count -= Count;
				Net_FixItemInfo_Bank( i );
				break;
			}
		}
	}


	DelItemInfo.Count = OrgCount;
	Net_SC_DelItemMsg( DelItemInfo );
	return true;

}


//給名聲( +- )
void    RoleDataEx::Sc_GiveFame( int Value )
{

}
//給Exp ( +- )
void    RoleDataEx::Sc_GiveExp( int Value )
{
	Addexp( Value );
}
//給錢  ( +- )
bool    RoleDataEx::Sc_GiveMoney( int Value )
{
	return AddBodyMoney( Value , NULL , EM_ActionType_PlotGive , true );
}

//-------------------------------------------------------------------------------------------------

//檢查給物品到戰利品(Party分響)
bool    RoleDataEx::Sc_CheckGiveItemToParty( int OrgID , int Count )
{
	return false;
}
//檢查給物品到個人 TempBuffer(任物旗標)
bool    RoleDataEx::Sc_CheckGiveItemToBuf( int OrgID , int Count )
{
	return true;
}
//檢查刪除物品
bool    RoleDataEx::Sc_CheckItemFromBody( int OrgID , int Count )
{
    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( OrgID );

	if( OrgDB == NULL )	return false;

	if( OrgDB->IsKeyItem() )
	{
		int ID = RoleDataEx::KeyItemObjToID( OrgDB->GUID );
		return BaseData.KeyItem.GetFlag( ID );
	}
	return CalBodyItemCount( OrgID ) >= Count;
}

//給錢  ( +- )
bool    RoleDataEx::Sc_CheckGiveMoney( int Value )
{
	return CheckAddBodyMoney( Value );
}
//-------------------------------------------------------------------------------------------------
int	RoleDataEx::Quest_Size ()
{
	int iCount = 0;
	for( int index = 0; index < _MAX_QUEST_COUNT_; index++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ index ].iQuestID != 0 )
		{
			iCount++;
		}
	}

	return iCount;
}
//-------------------------------------------------------------------------------------------------
int	RoleDataEx::Quest_Add ( int iQuestID )
{
	int iQuestIndex = -1;
	for( int index = 0; index < _MAX_QUEST_COUNT_; index++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ index ].iQuestID == 0 )
		{
			iQuestIndex = index;
			PlayerBaseData->Quest.QuestLog[ index ].iQuestID	= iQuestID;
			PlayerBaseData->Quest.QuestLog[ index ].iMode		= 0;

			for( int i = 0; i < _MAX_QUEST_KILLKIND_COUNT_; i++ )
			{
				PlayerBaseData->Quest.QuestLog[ index ].iQuestKillCount[ i ] = 0;
			}


			//Packet.emResult = EM_QUESTACCEPT_RESULT_OK;			
			break;
		}
	}

	return iQuestIndex;
}
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::Quest_Failed						( int iQuestID )
{
	for( int index = 0; index < _MAX_QUEST_COUNT_; index++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ index ].iQuestID == iQuestID )
		{
			//iQuestIndex = index;
			//PlayerBaseData->Quest.QuestLog[ index ].iQuestID	= iQuestID;
			PlayerBaseData->Quest.QuestLog[ index ].iMode	= -1;

			//Packet.emResult = EM_QUESTACCEPT_RESULT_OK;			
			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------------------
void RoleDataEx::Quest_Complete ( int iQuestField, int iQuestID )
{
	for( int i=0; i<_MAX_QUEST_COUNT_; i++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ i ].iQuestID == iQuestID )
		{
			Quest_Delete( iQuestField, iQuestID );
			PlayerBaseData->Quest.QuestHistory.SetFlagOn( iQuestID - Def_ObjectClass_QuestDetail );				
		}
	}
}
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::Quest_Delete ( int iQuestField, int iQuestID )
{

	bool bFound = false;

	for( int i=0; i<_MAX_QUEST_COUNT_; i++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ i ].iQuestID == iQuestID )
		{

			ZeroMemory( &( PlayerBaseData->Quest.QuestLog[ i ] ), sizeof( PlayerBaseData->Quest.QuestLog[ i ] ) );
			bFound = true;
		}
	}

	return bFound;
}
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::CheckQuestHistory_IsComplete		( int iQuestID )
{
	int iID = iQuestID - Def_ObjectClass_QuestDetail;
	if( iID >= 0 && _MAX_QUEST_FLAG_COUNT_ > iID )
	{
		return PlayerBaseData->Quest.QuestHistory.GetFlag( iQuestID - Def_ObjectClass_QuestDetail);
	}
	else
		return false;

}
//-------------------------------------------------------------------------------------------------
int	RoleDataEx::CheckGrayQuest( int iQuestID, GameObjectQuestDetail *pQuest )
{
	int iLowerLV	= 0;
	int iHigherLV	= 0;

	// 檢查所有條件是否成立, 條件不成立的話就傳送失敗回去
		int iResult = CheckQuest_IsAvailable_Base( iQuestID, pQuest );

		if( iResult != 0 )
		{
			return iResult;
		}

	// 檢查是否到達灰色 ! 的條件
		if( pQuest->iCheck_LowerLV == 0 && pQuest->iCheck_HigherLV == 0 )
		{
			int iOffset = int( ( (float) pQuest->iCheck_LV ) * 0.9f );

			iLowerLV = pQuest->iCheck_LV - iOffset;
			if( iLowerLV <= 0 )
			{
				iLowerLV = 1;
			}

			iHigherLV = pQuest->iCheck_LV + iOffset;
		}
		else
		{
			iLowerLV	= pQuest->iCheck_LowerLV;
			iHigherLV	= pQuest->iCheck_HigherLV;
		}

		if( ( ( TempData.Attr.Level + 1 ) < iLowerLV ) || ( TempData.Attr.Level > iHigherLV ) )
		{
			return EM_QUESTCHECK_RESULT_NOTOK;
		}

	return EM_QUESTCHECK_RESULT_OK;
}
//-------------------------------------------------------------------------------------------------
int	RoleDataEx::CheckQuest_IsAvailable ( int iQuestID, GameObjectQuestDetail *pQuest, bool bIgnoreLV )
{

	// 檢查所有條件是否成立, 條件不成立的話就傳送失敗回去
		int iResult = CheckQuest_IsAvailable_Base( iQuestID, pQuest );

		if( iResult != 0 )
		{
			return iResult;
		}

	// 檢查等級
		int iLowerLV	= 0;
		int iHigherLV	= 0;

		if( pQuest->iCheck_LowerLV == 0 && pQuest->iCheck_HigherLV == 0 )
		{
			int iOffset = int( ( (float) pQuest->iCheck_LV ) * 0.9f );

			iLowerLV = pQuest->iCheck_LV - iOffset;
			if( iLowerLV <= 0 )
			{
				iLowerLV = 1;
			}

			iHigherLV = pQuest->iCheck_LV + iOffset;
		}
		else
		{
			iLowerLV	= pQuest->iCheck_LowerLV;
			iHigherLV	= pQuest->iCheck_HigherLV;
		}

		if( TempData.Attr.Level < pQuest->iCheck_LowerLV )
		{
			return EM_QUESTCHECK_RESULT_NOTOK;
		}

		if( TempData.Attr.Level > pQuest->iCheck_HigherLV )
		{
			if( bIgnoreLV == false )
				return EM_QUESTCHECK_RESULT_NOTOK;
		}

	return EM_QUESTCHECK_RESULT_OK;

}
//-------------------------------------------------------------------------------------------------
int	RoleDataEx::CheckQuest_IsComplete ( int iQuestIndex, int iQuestID, GameObjectQuestDetail *pQuest )
{
	// 檢查所有條件是否成立, 條件不成立的話就傳送失敗回去

		// 檢查需求物品
			for( int index = 0; index < _MAX_SIZE_QUEST_CONDITION; index++ )
			{
				if( pQuest->iRequest_ItemID[ index ] != 0 )
				{
					if( Sc_CheckItemFromRole( pQuest->iRequest_ItemID[ index ], pQuest->iRequest_ItemVal[ index ] ) == false )
					{
						return EM_QUESTCHECK_RESULT_NOTOK;
					}
				}
				else
					break;
			}

		// 檢查打倒目標
			for( int index = 0; index < _MAX_SIZE_QUEST_ITEM; index++ )
			{
				if( pQuest->iRequest_KillID[ index ] != 0 )
				{
					//if( PlayerBaseData->Quest.iQuestKillCount[ iQuestIndex ][ index ] != pQuest->iRequest_KillVal[ index ] )
					if( PlayerBaseData->Quest.QuestLog[iQuestIndex].iQuestKillCount[ index ] != pQuest->iRequest_KillVal[ index ] )
					{
						return EM_QUESTCHECK_RESULT_NOTOK;
					}
				}
				else
					break;
			}

		// 檢查金錢
			if( pQuest->iRequest_Money != 0 )
			{
				if( pQuest->iRequest_Money > BodyMoney() )
				{
					return EM_QUESTCHECK_RESULT_NOTOK;
				}
			}

			//檢查金錢(所有類型)
			int Money = pQuest->iRequest_SpecialCoin;

			if( Money != 0  )
			{
				switch( pQuest->iRequest_CoinType )
				{
				case EM_ACPriceType_GameMoney:
					{
						//計算價錢
						if( PlayerBaseData->Body.Money < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_AccountMoney:
					{
						if( PlayerBaseData->Body.Money_Account < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_BonusMoney:
					{
						if( PlayerBaseData->Money_Bonus < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case  EM_ACPriceType_Honor:
					{
						if( PlayerBaseData->Honor < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_GuildWarEnergy:
					{
						return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_DuelistReward:
					{
						if( PlayerBaseData->DuelistReward < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_TrialBadge:		//試煉徽章
					{
						if( PlayerBaseData->TrialBadgeCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_Relics:			//古代遺物
					{
						if( PlayerBaseData->RelicsCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_Dreamland:		//夢境先遣印記
					{
						if( PlayerBaseData->DreamlandCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_PhiriusShell:	//必爾汀圓貝
					{
						if( PlayerBaseData->PhiriusShellCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_EnergyJustice:	//正義能量
					{
						if( PlayerBaseData->EnergyJusticeCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_ProofLegend:	//傳說之證
					{
						if( PlayerBaseData->ProofLegendCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				case EM_ACPriceType_MirrorCoin:
					{
						if( PlayerBaseData->MirrorCoin < Money )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
					break;
				//default:
				//	{
				//		char Buf[256];
				//		sprintf( Buf , "SYS_PRICETYPE_ICONID_%02d" , Type );
				//		//取出金錢類型
				//		int SPMoneyObjID = g_ObjectData->GetSysKeyValue( Buf );

				//		if( Owner->CalBodyItemCount(SPMoneyObjID) < Money  )
				//			return false;
				//	}
				//	break;
				}



			}

	return EM_QUESTCHECK_RESULT_OK;
}
//-------------------------------------------------------------------------------------------------
int RoleDataEx::CheckQuestList_IsGotQuest ( int iQuestID )
{
	for( int index = 0; index < _MAX_QUEST_COUNT_; index++ )
	{
		if( PlayerBaseData->Quest.QuestLog[ index ].iQuestID == iQuestID )
		{
			return index;
		}
	}

	return -1;
}
//-------------------------------------------------------------------------------------------------
/*
int RoleDataEx::CheckQuest_RequestKill_AddCount ( int iDeadObjID )
{
	//RoleDataEx*				pRole		= g_pGameMain->RoleData();
	QuestTempDataStruct*	pQuestTempData	= &( TempData.QuestTempData );

	for( int index = 0; index < pQuestTempData->QuestKillCount; index++ )
	{
		//if( pQuestTempData->iKillObj[ index ] != 0 )
		if( pQuestTempData->QuestKill[ index ].iKillObj[ 0 ] != 0 )
		{
			for( int iKillIndex = 0; iKillIndex < _MAX_QUEST_KILLKIND_COUNT_; iKillIndex++ )
			{
				int	&KillObj	=  pQuestTempData->QuestKill[ index ].iKillObj[ iKillIndex ];

				if( KillObj != 0 )
				{
					if( KillObj == iDeadObjID )
					{
						int		iQuestField = pQuestTempData->QuestKillIndexTable[ index ];

						int		&KillVal	= pQuestTempData->QuestKill[ index].iKillVal[ iKillIndex ];
						BYTE	&KillCount	= PlayerBaseData->Quest.iQuestKillCount[ iQuestField ][ iKillIndex ];

						if( KillVal > KillCount )							
						{
							KillCount++;

							return index;	// 回傳 Temp `資料中的 index
						}
					}
				}
				else
					break;
			}
		}
		else
			break;
	}

	return -1;
}
*/
//-------------------------------------------------------------------------------------------------
/*
int RoleDataEx::CheckQuest_RequestKill_Complete ( int iTempIndex )
{
	
	QuestTempDataStruct*	pQuestTempData	= &( TempData.QuestTempData );
	int						iQuestField		= pQuestTempData->iIndexTable[ iTempIndex ];
	
	if( pQuestTempData->iKillObj[ iTempIndex ] != 0 )
	{
		for( int iKillIndex = 0; iKillIndex < _MAX_QUEST_KILLKIND_COUNT_; iKillIndex++ )
		{				
			if( pQuestTempData->iKillObj[ iTempIndex ][ iKillIndex ] != 0 )
			{
				

				if( pQuestTempData->iKillVal[ iTempIndex ][ iKillIndex ] != PlayerBaseData->Quest.iQuestKillCount[ iQuestField ][ iKillIndex ] )
				{
					return -1;
				}
			}
			else
				break;
		}
		
	}
	else
	{
		return -1;
	}

	return iQuestField;
	

	return -1;

}
*/

//-------------------------------------------------------------------------------------------------
/*
void RoleDataEx::CheckQuest_RequestKill_SetTempData ( int iQuestField, GameObjectQuestDetail *pQuest )
{
	// 更新 TempData
	//--------------------------------------------------------------------
	if( pQuest->iRequest_KillID[ 0 ] != 0 )	// 檢查有無指定打倒的目標
	{
		QuestTempDataStruct	*pQuestTempData = &( TempData.QuestTempData );
		int					index			= pQuestTempData->QuestKillCount;

		pQuestTempData->QuestKillIndexTable[ index ] = iQuestField;

		for( int iKillKind = 0; iKillKind < _MAX_QUEST_KILLKIND_COUNT_; iKillKind++ )
		{
			if( pQuest->iRequest_KillID[ iKillKind ] != 0 )
			{
				pQuestTempData->QuestKill[ index ].iKillObj[ iKillKind ] = pQuest->iRequest_KillID[ iKillKind ];
				pQuestTempData->QuestKill[ index ].iKillVal[ iKillKind ] = pQuest->iRequest_KillVal[ iKillKind ];

				//pQuestTempData->iKillObj[ index ][ iKillKind ]		= pQuest->iRequest_KillID[ iKillKind ];
				//pQuestTempData->iKillVal[ index ][ iKillKind ]		= pQuest->iRequest_KillVal[ iKillKind ];
				//pQuestTempData->fDropPercent[ index ][ iKillKind ]	= pQuest->ip
			}
			else
				break;
		}

		pQuestTempData->QuestKillCount++;
	}
}

//-------------------------------------------------------------------------------------------------
void RoleDataEx::CheckQuest_KillToGetItem_SetTempData ( int iQuestField, GameObjectQuestDetail *pQuest )
{
	// 更新 TempData
	//--------------------------------------------------------------------
	if( pQuest->iProcess_KilltoGetItem_ObjID[ 0 ] != 0 )	// 檢查有無指定打倒的目標
	{
		QuestTempDataStruct	*pQuestTempData = &( TempData.QuestTempData );
		int					index			= pQuestTempData->QuestKillCount;

		pQuestTempData->QuestKillIndexTable[ index ] = iQuestField;

		for( int iKillKind = 0; iKillKind < _MAX_QUEST_KILLKIND_COUNT_; iKillKind++ )
		{
			// 檢
			if( pQuest->iProcess_KilltoGetItem_ObjID[ iKillKind ] != 0 )
			{
				pQuestTempData->QuestKill[ index].iKillObj[ iKillKind ]			= pQuest->iProcess_KilltoGetItem_ObjID[ iKillKind ];			
				pQuestTempData->QuestKill[ index].fDropPercent[ iKillKind ]		= pQuest->iProcess_KilltoGetItem_ProcPercent[ iKillKind ];
				pQuestTempData->QuestKill[ index].iDropItem[ iKillKind ]		= pQuest->iProcess_KilltoGetItem_GetItem[ iKillKind ];
				pQuestTempData->QuestKill[ index].iDropItemVal[ iKillKind ]		= pQuest->iProcess_KilltoGetItem_GetItemVal[ iKillKind ];																	  				
			}
			else
				break;
		}

		pQuestTempData->QuestKillCount++;
	}
}
//-------------------------------------------------------------------------------------------------
void RoleDataEx::CheckQuest_ClickToGetItem_SetTempData ( int iQuestField, GameObjectQuestDetail *pQuest )
{
	// 更新 TempData
	//--------------------------------------------------------------------
	if( pQuest->iProcess_ClickToGetItem_ObjID[ 0 ] != 0 )	// 檢查有無指定打倒的目標
	{
		QuestTempDataStruct	*pQuestTempData = &( TempData.QuestTempData );
		int					iField			= pQuestTempData->QuestCollectCount;

		pQuestTempData->QuestCollectIndexTable[ iField ] = iQuestField;

		for( int index = 0; index < _MAX_QUEST_KILLKIND_COUNT_; index++ )
		{
			if( pQuest->iProcess_ClickToGetItem_ObjID[ index ] != 0 )
			{
				pQuestTempData->QuestCollect[ iField ].iClickObj	[ index ]	= pQuest->iProcess_ClickToGetItem_ObjID			[ index ];			
				pQuestTempData->QuestCollect[ iField ].fProcPercent	[ index ]	= pQuest->iProcess_ClickToGetItem_ProcPercent	[ index ];
				pQuestTempData->QuestCollect[ iField ].iDropItem	[ index ]	= pQuest->iProcess_ClickToGetItem_GetItem		[ index ];
				pQuestTempData->QuestCollect[ iField ].iDropItemVal	[ index ]	= pQuest->iProcess_ClickToGetItem_GetItemVal	[ index ];																	  				
			}
			else
				break;
		}

		pQuestTempData->QuestCollectCount++;
	}
}
*/
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::Sc_CheckItemFromBank ( int OrgID, int Count )
{
    return CalBankItemCount( OrgID ) >= Count;
	//return 0;
}
//-------------------------------------------------------------------------------------------------
bool RoleDataEx::Sc_CheckItemFromRole		( int OrgID, int Count )
{
    GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( OrgID );

	if( OrgDB == NULL )	return false;

	if( OrgDB->IsKeyItem() )
	{
		int ID = RoleDataEx::KeyItemObjToID( OrgDB->GUID );
		return BaseData.KeyItem.GetFlag( ID );
	}
	else
	{
		// Item
		int iCount = Sc_GetItemNumFromRole( OrgID );
		return ( iCount >= Count );
	}
}
//-------------------------------------------------------------------------------------------------
int RoleDataEx::Sc_GetItemNumFromRole		( int OrgID )
{
	GameObjDbStructEx*	OrgDB;
    OrgDB = St_GetObjDB( OrgID );

	if( OrgDB == NULL )	return false;

	if( OrgDB->IsKeyItem() )
	{
		int ID = RoleDataEx::KeyItemObjToID( OrgDB->GUID );
		if( BaseData.KeyItem.GetFlag( ID ) )
			return 1;
		else
			return 0;
	}
	else
	{
		// Item
		int iCount = 0;

		iCount	=	CalBankItemCount( OrgID );
		iCount	+=	CalBodyItemCount( OrgID );

		return iCount;
	}
}
//-------------------------------------------------------------------------------------------------
int RoleDataEx::CheckQuest_IsAvailable_Base( int iQuestID, GameObjectQuestDetail *pQuest )
{
	// 檢查所有條件是否成立, 條件不成立的話就傳送失敗回去

	// 檢查職業 ( 尚未完成 )
	if( pQuest->iCheck_Class_Type != 0 )
	{

	}

	// 檢查性別
	if( pQuest->iCheck_Sex != 0 )
	{
		if( pQuest->iCheck_Sex == 1 ) // 檢查 Sex 為男
		{
			if( BaseData.Sex != EM_Sex_Boy )
				return EM_QUESTCHECK_RESULT_NOTOK;						
		}
		else
		{
			if( BaseData.Sex != EM_Sex_Girl )
				return EM_QUESTCHECK_RESULT_NOTOK;						
		}
	}

	// 檢查稱號
		if( pQuest->iCheck_Title != 0 )
		{

		}

	// 檢查名聲值
		int iRepGroup = pQuest->iCheck_RepGroup;
		if( iRepGroup != 0 ) 
		{
			if( iRepGroup >= 1 && iRepGroup <= _MAX_FAMOUS_COUNT_ )
			{
				int iRep = PlayerBaseData->Famous[ ( iRepGroup-1) ];
				if( iRep < pQuest->iCheck_Rep )
				{
					return EM_QUESTCHECK_RESULT_NOTOK;
				}	
			}
			else
				return EM_QUESTCHECK_RESULT_NOTOK;
		}

	// 檢查每日任務
		if( pQuest->iControlType == 1 )	// 1 為每日
		{
			int iID = iQuestID - Def_ObjectClass_QuestDetail;
			if( iID >= 0 && _MAX_QUEST_FLAG_COUNT_ > iID )
			{
				if( PlayerBaseData->Quest.QuestDaily.GetFlag( iID ) != false )
				{
					return EM_QUESTCHECK_RESULT_NOTOK;
				}
			}
			else
			{
				return EM_QUESTCHECK_RESULT_NOTOK;
			}
		}

	// 檢查群組設定
		if( pQuest->iQuestGroup != 0 )
		{
			int iDailyLimit = 10;

			if( pQuest->iQuestGroup == 1 ) // 公會任務
			{
#ifdef _LOCAL_SERVER_
				GuildStruct* pGuild = GuildManageClass::This()->GetGuildInfo( BaseData.GuildID );

				if( pGuild == NULL  )
					return EM_QUESTCHECK_RESULT_NOTOK;

				if( pQuest->iQuestGroupLV != 0 )
				{
					if( pGuild->Base.Level < pQuest->iQuestGroupLV )
						return EM_QUESTCHECK_RESULT_NOTOK;
				}
				
				int iTotalLV = (int)g_ObjectData->_GuildLvTable.size();
				
				if( pGuild != NULL && ( pGuild->Base.Level >= 1 && pGuild->Base.Level < iTotalLV  ) )
				{
					iDailyLimit = g_ObjectData->_GuildLvTable[ pGuild->Base.Level ].Quest;
				}
				else
				{
					return EM_QUESTCHECK_RESULT_NOTOK;
				}
#endif

#ifdef _CLIENT
				GuildBaseStruct * guidlinfo = g_pGuildFrame->GetGuildBaseInfo();

				if( guidlinfo == NULL )
					return EM_QUESTCHECK_RESULT_NOTOK;

				if( pQuest->iQuestGroupLV != 0 )
				{
					if( guidlinfo->Level < pQuest->iQuestGroupLV )
						return EM_QUESTCHECK_RESULT_NOTOK;
				}


				int iTotalLV = g_ObjectData->_GuildLvTable.size();

				if( guidlinfo != NULL && ( guidlinfo->Level >= 1 && guidlinfo->Level < iTotalLV  ) )
				{
					iDailyLimit = g_ObjectData->_GuildLvTable[ guidlinfo->Level ].Quest;
				}
				else
				{
					return EM_QUESTCHECK_RESULT_NOTOK;
				}
#endif
			}
			

			if( pQuest->iQuestGroup != 3 )	// 公眾任務不扣次數
			{
				int iID = pQuest->iQuestGroup -1;
				if( iID >= 0 && iID < DF_QUESTDAILY_MAXGROUP )
				{
					if( PlayerBaseData->Quest.iQuestGroup[ iID ] >= iDailyLimit )
					{
						return EM_QUESTCHECK_RESULT_NOTOK;
					}
				}
			}
		}

	// 檢查必要 Obj 
		if( pQuest->iCheck_ObjID[0] != 0 )
		{				
			for( int index = 0; index < _MAX_SIZE_QUEST_ITEM; index++ )
			{
				int iObjID = pQuest->iCheck_ObjID[ index ];
				if( iObjID != 0 )
				{
					GameObjDbStructEx* pObjDB = St_GetObjDB( iObjID );

				// 檢查是道具還是完成任務
					//if( ( iObjID >= Def_ObjectClass_Item /*&& iObjID < Def_ObjectClass_Item + Def_ObjectClass_Item_Total*/ ) 
					//|| ( iObjID >= Def_ObjectClass_KeyItem /*&& iObjID < Def_ObjectClass_KeyItem + Def_ObjectClass_KeyItem_Total*/ ) )
					if( pObjDB != NULL && ( pObjDB->IsItem() || pObjDB->IsKeyItem() ) )
					{
						// 道具
						if( Sc_CheckItemFromBody( iObjID, pQuest->iCheck_ObjVal[ index ] ) == false )
						{
							return EM_QUESTCHECK_RESULT_NOTOK;
						}
					}
					else
					//if( iObjID >= Def_ObjectClass_QuestDetail && iObjID < Def_ObjectClass_QuestDetail + Def_ObjectClass_QuestDetail_Total )
					if( pObjDB != NULL && pObjDB->IsQuestDetail() ) 
					{
						// 任務
						if( CheckQuestHistory_IsComplete( iObjID ) == false )
						{
							return EM_QUESTCHECK_RESULT_NOTOK;
						}
					}
					else
					if( pObjDB->IsTitle() != false  )
					{
						int ID = iObjID -  Def_ObjectClass_Title;
						if( PlayerBaseData->Title.GetFlag( ID ) == false )
							return EM_QUESTCHECK_RESULT_NOTOK;
					}
				}
				else
					break;
			}
		}

	return EM_QUESTCHECK_RESULT_OK;
}

