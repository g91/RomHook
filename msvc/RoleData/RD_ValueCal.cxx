#include "RoleDataEx.h"
#include <math.h>
#include <set>
//計算到某目標點的長度
float   RoleDataEx::Length( float X , float Y , float Z )
{
	X -= BaseData.Pos.X;
	Y -= BaseData.Pos.Y;
	Z -= BaseData.Pos.Z;
	Y = 0;
	float Ret = sqrt( X*X + Y*Y + Z*Z);
	return Ret;
}

float   RoleDataEx::Length( RoleDataEx* Target )
{
	return Length( Target->BaseData.Pos.X , Target->BaseData.Pos.Y , Target->BaseData.Pos.Z );
}

float   RoleDataEx::Length(  int TargetID )
{
	RoleDataEx* Target = (RoleDataEx*)St_GetRoleData( TargetID );
	if( Target == NULL )
		return 10000;
	return Length( Target->BaseData.Pos.X , Target->BaseData.Pos.Y , Target->BaseData.Pos.Z );
}
float   RoleDataEx::Length3D( float X , float Y , float Z )
{
	X -= BaseData.Pos.X;
	Y -= BaseData.Pos.Y;
	Z -= BaseData.Pos.Z;
	float Ret = sqrt( X*X + Y*Y + Z*Z);
	return Ret;
}

float   RoleDataEx::Length3D( RoleDataEx* Target )
{
	return Length3D( Target->BaseData.Pos.X , Target->BaseData.Pos.Y , Target->BaseData.Pos.Z );
}

float   RoleDataEx::Length3D(  int TargetID )
{
	RoleDataEx* Target = (RoleDataEx*)St_GetRoleData( TargetID );
	if( Target == NULL )
		return 10000;
	return Length3D( Target->BaseData.Pos.X , Target->BaseData.Pos.Y , Target->BaseData.Pos.Z );
}
//計匴所有角色數值
void	RoleDataEx::Calculate( )
{
	float HPRate = 0; 
	float MPRate = 0; 
	if( TempData.Attr.Fin.MaxHP != 0 )
		HPRate = float( BaseData.HP )/ float( TempData.Attr.Fin.MaxHP );
	if( TempData.Attr.Fin.MaxMP != 0 )
		MPRate = float( BaseData.MP )/ float( TempData.Attr.Fin.MaxMP );
	TempData.Attr.Calculate();

#ifdef _LOCAL_SERVER_
	if( TempData.UpdateInfo.Eq == false )
	{
		if( HPRate != 0 )
			BaseData.HP = TempData.Attr.Fin.MaxHP * HPRate +0.5f;
		if( MPRate != 0 )
			BaseData.MP = TempData.Attr.Fin.MaxMP * MPRate +0.5f;
	}
#endif
}
//-----------------------------------------------------------------------------------------------
// 計算生活技能升級上限
void	RoleDataEx::CalLifeSkillMaxValue()
{
	// 修正生活技能升級上限
	for( int i = EM_SkillValueType_BlackSmith; i <= EM_SkillValueType_CatchPet; i++ )
	{
		TempData.Attr.MaxSkillValue.Skill[i] = float( GetLifeSkillMax( (SkillValueTypeENUM)i ) );

		if( TempData.Attr.MaxSkillValue.Skill[i] != 0 && BaseData.SkillValue.Skill[ i ] == 0 )
		{
			BaseData.SkillValue.Skill[ i ] = 1;
			TempData.Attr.Fin.SkillValue.Skill[i] += 1;
			//TempData.UpdateInfo.Recalculate_All = 1;
		}

		if( BaseData.SkillValue.Skill[ i ] > TempData.Attr.MaxSkillValue.Skill[i] )
		{
			BaseData.SkillValue.Skill[ i ] = TempData.Attr.MaxSkillValue.Skill[i];
			TempData.UpdateInfo.Recalculate_All = 1;
		}
	}
}
//-----------------------------------------------------------------------------------------------
//初始化角色計算數值
void	RoleDataEx::InitCal( )
{
	//----------------------------------------------------------------------
	BaseAbilityStruct*		Ability;

	if( IsNPC() )
		TempData.Attr.SkillValue = &TempData.Attr.MaxSkillValue;
	else
		TempData.Attr.SkillValue = &BaseData.SkillValue;


	if( (unsigned)BaseData.Race >= EM_Max_Race )
		BaseData.Race = EM_Race1;

	if( (unsigned)BaseData.Voc >= EM_Max_Vocation )
		BaseData.Voc = EM_Vocation_Warrior;

	if( (unsigned)BaseData.Sex >= EM_Sex_Max_Sex )
		BaseData.Sex = EM_Sex_Boy;

	if( (unsigned)BaseData.Voc_Sub >= EM_Max_Vocation )
		BaseData.Voc_Sub = EM_Vocation_None;

	if( BaseData.Voc_Sub == BaseData.Voc )
		BaseData.Voc_Sub = EM_Vocation_None;

	if( IsPlayer() )
		Ability = TempData.Attr.Ability = &PlayerBaseData->AbilityList[ BaseData.Voc ];
	else
		Ability = TempData.Attr.Ability = &BaseData.Ability;

	if( (unsigned) Ability->Level > _MAX_LEVEL_ )
		Ability->Level = _MAX_LEVEL_;

	if( Ability->Level == 0 )
		Ability->Level = 1;




	TempData.Attr.Level = Ability->Level;

	//基本數值
	TempData.Attr.Race		= BaseData.Race;
	TempData.Attr.Sex		= BaseData.Sex; 
	TempData.Attr.Voc   	= BaseData.Voc;
	TempData.Attr.Voc_Sub   = BaseData.Voc_Sub;
	TempData.Attr.Level_Sub = 0;

	if( IsPlayer() != false )
	{
		TempData.Attr.FixArgTableID = 1;

		if( EM_Vocation_None != BaseData.Voc_Sub )
		{
			TempData.Attr.Level_Sub = PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].Level;
			TempData.Attr.Level_Sub = __min( TempData.Attr.Level_Sub , ( Ability->Level ) );
		}	

	}
	else
	{
		TempData.Attr.FixArgTableID = 0;

		if( EM_Vocation_None != BaseData.Voc_Sub )
		{
			TempData.Attr.Level_Sub = TempData.Attr.Level;
		}	

	}


	GameObjDbStructEx*		OrgDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( OrgDB == NULL )
		return;


	if( !OrgDB->IsNPC() )
	{
		InitMagicBook();
		//設定備動技能
		ReSetPassiveSkill();
	}

	//記算Table 重設
	TempData.Attr.ReSetTable();

	CalLifeSkillMaxValue();


	if( IsNPC() )
		TempData.Attr.Bas.MoveSpeed_Per = (float)OrgDB->NPC.MoveSpeed ;
	else
		TempData.Attr.Bas.MoveSpeed_Per = 100;


	//ReCalculateMagicAndEQ( );
	ReCalculateEQNoBuff();
	ReCalculateBuff();

	ReCalculatePhantom();

	Calculate();
	//----------------------------------------------------------------------
	//(暫時)
	if( IsPlayer() == false )
	{
		BaseData.HP = TempData.Attr.Fin.MaxHP;
		BaseData.MP = TempData.Attr.Fin.MaxMP;
	}
	//----------------------------------------------------------------------

}
//-----------------------------------------------------------------------------------------------
void    RoleDataEx::CheckItemLiveTime()
{
	GameObjDbStructEx*		OrgDB;
	int		i;

	for( i = 0 ; i < PlayerBaseData->Body.Count ; i++ )    
	{
		ItemFieldStruct& Field = PlayerBaseData->Body.Item[i];

		OrgDB = St_GetObjDB( Field.OrgObjID );
		if( OrgDB == NULL )
			continue;

		if( OrgDB->LiveTimeType == EM_ItemLiveTimeType_None )
			continue;

		if( int( RoleDataEx::G_Now - Field.CreateTime ) > OrgDB->LiveTime )
		{
			Log_ItemDestroy( EM_ActionType_TimeUp , Field ,-1 , "" );
			Net_ItemTimeout( Field , EM_ItemTimeoutPos_Body );
			Field.Init();
			Net_FixItemInfo_Body( i );
			
		}

	}
	for( i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )    
	{
		ItemFieldStruct& Field = PlayerBaseData->Bank.Item[i];
		OrgDB = St_GetObjDB( Field.OrgObjID );
		if( OrgDB == NULL )
			continue;

		if( OrgDB->LiveTimeType == EM_ItemLiveTimeType_None )
			continue;

		if( int( RoleDataEx::G_Now - Field.CreateTime ) > OrgDB->LiveTime )
		{
			Log_ItemDestroy( EM_ActionType_TimeUp , Field , -1 , "" );
			Net_ItemTimeout( Field , EM_ItemTimeoutPos_Bank );
			Field.Init();
			Net_FixItemInfo_Bank( i );
		}
	}
	//裝備(暫時)   
	for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )    
	{
		ItemFieldStruct& Field = BaseData.EQ.Item[i];
		OrgDB = St_GetObjDB( Field.OrgObjID );
		if( OrgDB == NULL )
			continue;

		if( OrgDB->LiveTimeType == EM_ItemLiveTimeType_None )
			continue;

		if( int( RoleDataEx::G_Now - Field.CreateTime ) > OrgDB->LiveTime )
		{
			Log_ItemDestroy( EM_ActionType_TimeUp , Field , -1 , "" );
			Net_ItemTimeout( Field , EM_ItemTimeoutPos_EQ );
			Field.Init();
			Net_FixItemInfo_EQ( i );
			TempData.UpdateInfo.Eq = true;
		}

	}
}

void RoleDataEx::InitChangeZone()
{
	int i;
	GameObjDbStructEx*		OrgDB;//	= St_GetObjDB( Field->OrgObjID );
	//hp mp
	if( BaseData.HP <= 0 )
		BaseData.HP = 1;
	if( BaseData.MP < 0 )
		BaseData.MP = 0;

	//物品
	if( PlayerBaseData->Body.Count < 0 )
		PlayerBaseData->Body.Count = 0;
	if( PlayerBaseData->Body.Count > _MAX_BODY_COUNT_ )
		PlayerBaseData->Body.Count = _MAX_BODY_COUNT_;


	for( i = 0 ; i < PlayerBaseData->Body.Count ; i++ )    
	{
		ItemFieldStruct& Field = PlayerBaseData->Body.Item[i];
		OrgDB = St_GetObjDB( Field.OrgObjID );

		if( OrgDB == NULL )
		{
			Field.Init();
			continue;
		}

		if( Field.Count <= 0 || OrgDB->Mode.Logoutdel)
		{
			Field.Init();
			continue;
		}

		if( OrgDB->MaxHeap < Field.Count )
			Field.Count = OrgDB->MaxHeap;

		if( Field.ImageObjectID == 0 )
			Field.ImageObjectID = Field.OrgObjID;

		if( Field.Serial == 0 )
		{
			Field.CreateTime = RoleDataEx::G_Now;
			Field.Serial	 = St_GenerateItemVersion( );
		}

	}
	//銀行
	if( PlayerBaseData->Bank.Count < 0 )
		PlayerBaseData->Bank.Count = 0;
	if( PlayerBaseData->Bank.Count > _MAX_BANK_COUNT_ )
		PlayerBaseData->Bank.Count = _MAX_BANK_COUNT_;

	for( i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )    
	{
		ItemFieldStruct& Field = PlayerBaseData->Bank.Item[i];
		if( Field.Count <= 0)
		{
			Field.Init();
			continue;
		}

		OrgDB = St_GetObjDB( Field.OrgObjID );
		if( OrgDB == NULL || OrgDB->Mode.Logoutdel )
		{
			Field.Init();
			continue;
		}
		if( OrgDB->MaxHeap < Field.Count )
			Field.Count = OrgDB->MaxHeap;

		if( Field.ImageObjectID == 0 )
			Field.ImageObjectID = Field.OrgObjID;

		if( Field.Serial == 0 )
		{
			Field.CreateTime = RoleDataEx::G_Now;
			Field.Serial		= St_GenerateItemVersion( );
		}

	}
	//裝備(暫時)   
	for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )    
	{
		ItemFieldStruct& Field = BaseData.EQ.Item[i];
		OrgDB = St_GetObjDB( Field.OrgObjID );

		if( OrgDB == NULL )
		{
			Field.Init();
			continue;
		}

		if( Field.Count <= 0 || OrgDB->Mode.Logoutdel)
		{
			Field.Init();
			continue;
		}

		
		if( OrgDB->MaxHeap < Field.Count )
			Field.Count = OrgDB->MaxHeap;

		if( Field.ImageObjectID == 0 )
			Field.ImageObjectID = Field.OrgObjID;

		if( Field.Serial == 0 )
		{
			Field.CreateTime = RoleDataEx::G_Now;
			Field.Serial		= St_GenerateItemVersion( );
		}

	}

	for( int j = 0 ; j < _MAX_BACKUP_EQ_SET_COUNT_ ; j++ )
	{
		for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )    
		{
			ItemFieldStruct& Field = PlayerBaseData->EQBackup[j].Item[i];
			OrgDB = St_GetObjDB( Field.OrgObjID );

			if( OrgDB == NULL )
			{
				Field.Init();
				continue;
			}

			if( Field.Count <= 0 || OrgDB->Mode.Logoutdel)
			{
				Field.Init();
				continue;
			}


			if( OrgDB->MaxHeap < Field.Count )
				Field.Count = OrgDB->MaxHeap;

			if( Field.ImageObjectID == 0 )
				Field.ImageObjectID = Field.OrgObjID;

			if( Field.Serial == 0 )
			{
				Field.CreateTime = RoleDataEx::G_Now;
				Field.Serial		= St_GenerateItemVersion( );
			}
		}
	}

	//檢查堆疊內是否有重複的物品
	for( int i = 0 ; i < PlayerBaseData->ItemTemp.Size() ; i++ )
	{
		ItemFieldStruct& Field = PlayerBaseData->ItemTemp[i];
		OrgDB = St_GetObjDB( Field.OrgObjID );

		if(		OrgDB == NULL 
			||	Field.Count <= 0 
			|| OrgDB->Mode.Logoutdel )
		{
			PlayerBaseData->ItemTemp.Erase( i );
			i--;
			continue;
		}

	}
}


bool	RoleDataEx::CheckAndInitItem( ItemFieldStruct& Field )
{
	if( Field.OrgObjID == 0 )
		return false;

	GameObjDbStructEx* OrgDB = St_GetObjDB( Field.OrgObjID );

	if( OrgDB == NULL )
	{
		Print( 6 , "CheckAndInitItem" , "PlayerDBID=%d Field.OrgObjID=%d" , DBID() , Field.OrgObjID );
		//Field.Init();
		return false;
	}

	if( Field.Count <= 0 )
	{
		Field.Init();
		return true;
	}
	//|| OrgDB->Mode.Logoutdel
	if(		TempData.Attr.Action.ChangeZone 
		&&	OrgDB->Mode.ChangeZoneDel )
	{
		Field.Init();
		return true;
	}

	if(		TempData.Attr.Action.Login 
		&&	OrgDB->Mode.Logoutdel )
	{
		Field.Init();
		return true;
	}


	if( OrgDB->MaxHeap > 1 )
		Field.Mode.Trade = !(OrgDB->Mode.PickupBound);


	if( OrgDB->MaxHeap < Field.Count )
		Field.Count = OrgDB->MaxHeap;

	if( Field.ImageObjectID == 0 )
		Field.ImageObjectID = Field.OrgObjID;

	if( Field.Serial == 0 )
	{
		Field.CreateTime = RoleDataEx::G_Now;
		Field.Serial	 = St_GenerateItemVersion( );
	}
	return false;
}

//檢查角色資料是否有問題，如果有自動更正
void    RoleDataEx::InitCheckRoleData( )
{
	if(		BaseData.Voc < EM_Vocation_GameMaster 
		||	BaseData.Voc >= EM_Max_Vocation )
		BaseData.Voc = EM_Vocation_Warrior;
	TempData.Attr.Fin.MaxHP = 0;
	TempData.Attr.Fin.MaxMP = 0;

	int i;
//	GameObjDbStructEx*		OrgDB;//	= St_GetObjDB( Field->OrgObjID );
	//hp mp
	if( BaseData.HP <= 0 )
		BaseData.HP = 1;
	if( BaseData.MP < 0 )
		BaseData.MP = 0;

	//物品
	if( PlayerBaseData->Body.Count < 0 )
		PlayerBaseData->Body.Count = 0;
	if( PlayerBaseData->Body.Count > _MAX_BODY_COUNT_ )
		PlayerBaseData->Body.Count = _MAX_BODY_COUNT_;

	for( i = 0 ; i < PlayerBaseData->Body.Count ; i++ )    
	{
		if(		CheckAndInitItem( PlayerBaseData->Body.Item[i] ) != false 
			&&	TempData.Attr.Action.Login == false )
		{
			Net_FixItemInfo_Body( i );
		};
	}

	for( int i = 0 ; i < PlayerBaseData->ItemTemp.Size() ; i ++ )
	{
		CheckAndInitItem( PlayerBaseData->ItemTemp[i] );
	}

	//銀行
	if( PlayerBaseData->Bank.Count < 0 )
		PlayerBaseData->Bank.Count = 0;
	if( PlayerBaseData->Bank.Count > _MAX_BANK_COUNT_ )
		PlayerBaseData->Bank.Count = _MAX_BANK_COUNT_;

	for( i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )    
	{		
		ItemFieldStruct& Field = PlayerBaseData->Bank.Item[i];
		if(		CheckAndInitItem( Field ) != false 
			&&	TempData.Attr.Action.Login == false )
		{
			Net_FixItemInfo_Bank( i );
		}
	}
	//裝備(暫時)   
	for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )    
	{
		ItemFieldStruct& Field = BaseData.EQ.Item[i];
		if(		CheckAndInitItem( Field ) != false 
			&&	TempData.Attr.Action.Login == false )
		{
			Net_FixItemInfo_EQ( i );
		}

	}

	//裝備(暫時)   
	for( int j = 0 ; j < _MAX_BACKUP_EQ_SET_COUNT_ ; j++ )
	{
		for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )    
		{
			ItemFieldStruct& Field = PlayerBaseData->EQBackup[j].Item[i];
			if(		CheckAndInitItem( Field ) != false 
				&&	TempData.Attr.Action.Login == false )
			{
				Net_FixItemInfo_EQ( i + _DEF_EQ_BACKUP_BASE_ * (j+1) );
			}
		//	CheckAndInitItem( Field );

		}
	}
	
	//Buff檢查
	for( int i = 0 ; i < (int)BaseData.Buff.Size() ; i++ )
	{
		GameObjDbStructEx* ObjDB = St_GetObjDB( BaseData.Buff[i].BuffID );
		if( ObjDB == NULL )
		{
			//BaseData.Buff.Clear();
			//break;
			BaseData.Buff.Erase( i );
			i--;
			continue;
		}
		BaseData.Buff[i].Magic = ObjDB;
	}

	for( int i = 0 ; i < DEF_MAX_COLDOWN_COUNT_ALL ; i++ )
	{
		if( BaseData.Coldown.All[i] > 60*60*24 )
			BaseData.Coldown.All[i] = 0;
	}

	//頭銜計數
	PlayerBaseData->TitleCount = 0;
	for( int i = 0 ; i < PlayerBaseData->Title.Size() ; i++ )
	{
		if( PlayerBaseData->Title.GetFlag( i ) != false )
			PlayerBaseData->TitleCount++;
	}

	for( int i = 0 ; i < _MAX_INSTANCE_SETTING_COUNT_ ; i++ )
	{
		/*
		if( PlayerBaseData->InstanceSetting.LiveTime[i] < G_Now )
		{
			PlayerBaseData->InstanceSetting.LiveTime[i] = 0;
			PlayerBaseData->InstanceSetting.KeyID[i] = -1;
			PlayerBaseData->InstanceSetting.ClearTime[i] = 0;
		}
		*/
	}
}
//-----------------------------------------------------------------------------------------------
//設定物品裝備資訊
void    RoleDataEx::ResetItemInfo( )
{

}
//-----------------------------------------------------------------------------------------------
/*
//算不包含Buff的能力 , 算到基本
void	RoleDataEx::ReCalculateBase( )
{
	ItemFieldStruct* Item;
	int		i;

	TempData.Attr.Init_MidValue();

	if( IsNPC() )
	{
		WearObject( BaseData.ItemInfo.OrgObjID );
	}
	else
	{
		TempData.Attr.ExAddHP = PlayerBaseData->TitleCount * 5;
		WearObject( BaseData.TitleID );
		//記算被動技能
		for( i = 0 ; i < PlayerTempData->PassiveSkill.Size() ; i++ )
		{
			WearMagic( PlayerTempData->PassiveSkill[i] , PlayerTempData->PassiveSkillLv[i] );
		}
		//-------------------------------------------------------------------------
		//先計算裝備能力
		TempData.Attr.CalWearSkill( );
		map< int , int > SuitIDList;
		map< int , int >::iterator Iter;
		set< int > EqIDSet;

		//計算套裝資料
		for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
		{
			Item = GetEqItem( i );

			GameObjDbStructEx* OrgDB = St_GetObjDB( Item->OrgObjID );
			ItemStateModeStruct Bk_Mode = Item->Mode;
			if( OrgDB == NULL )
				continue;

			if( EqIDSet.insert(Item->OrgObjID).second == false )
				continue;

			if( Item->Mode.EQSoulBound )
			{
				if( Item->Mode.Trade != false )
				{
					Item->Mode.Trade = false;
				}
			}

			if( Item->Mode._Mode != Bk_Mode._Mode )
			{
				Net_FixItemInfo_EQ( i );
			}

			Item = GetEqItem( i );
			WearEQ( Item , i );



			if( OrgDB->Item.SuitID == 0 )
				continue;		

			SuitIDList[ OrgDB->Item.SuitID ] ++;
		}

		for( Iter = SuitIDList.begin() ; Iter != SuitIDList.end() ; Iter++ )
		{
			if( Iter->second <= 1 )
				continue;

			WearSuit( Iter->first , Iter->second );
		}
	}


	//-------------------------------------------------------------------------

	FixWeaponType();
}
*/
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::ReCalculateEqOnly()
{
	ItemFieldStruct* Item;
	//先計算裝備能力
	TempData.Attr.CalWearSkill( );
	map< int , int > SuitIDList;
	map< int , int >::iterator Iter;
	set< int > EqIDSet;

	//計算套裝資料
	for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
	{
		Item = GetEqItem( i );

		GameObjDbStructEx* OrgDB = St_GetObjDB( Item->OrgObjID );
		ItemStateModeStruct Bk_Mode = Item->Mode;
		if( OrgDB == NULL )
			continue;

		if( i == EM_EQWearPos_SecondHand )
		{
			if(		TempData.Attr.Fin.WearSkill.SecondHand == false
				&& OrgDB->IsWeapon() )
			{
				Item->Mode.EQCannotEquipment = true;
				continue;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		if( CheckEQLimit( OrgDB , Item->Mode.IgnoreLimitLv ) == false )
		{
			Item->Mode.EQCannotEquipment = true;
			continue;
		}
		else
		{
			Item->Mode.EQCannotEquipment = false;
		}


		if( Item->Mode.EQSoulBound )
		{
			if( Item->Mode.Trade != false )
			{
				Item->Mode.Trade = false;
			}
		}

		if( Item->Mode._Mode != Bk_Mode._Mode )
		{
			Net_FixItemInfo_EQ( i );
		}

		Item = GetEqItem( i );
		WearEQ( Item , i );

		if( EqIDSet.insert(Item->OrgObjID).second == false )
			continue;

		if( OrgDB->Item.SuitID == 0 )
			continue;		

		SuitIDList[ OrgDB->Item.SuitID ] ++;
	}

	for( Iter = SuitIDList.begin() ; Iter != SuitIDList.end() ; Iter++ )
	{
		if( Iter->second <= 1 )
			continue;

		WearSuit( Iter->first , Iter->second );
	}
}
//只記算基本能力
void	RoleDataEx::ReCalculateEQNoBuff()
{
//	ItemFieldStruct* Item;
	int		i;
	TempData.Attr.Init_BaseEQValue();
	TempData.Attr.Init_MidValue();

	if( IsNPC() )
	{
		WearObject( BaseData.ItemInfo.OrgObjID );
	}
	else
	{
		TempData.Attr.ExAddHP = PlayerBaseData->TitleCount * 5;
		WearObject( BaseData.TitleID );
		//記算被動技能
		for( i = 0 ; i < PlayerTempData->PassiveSkill.Size() ; i++ )
		{
			WearBuff( PlayerTempData->PassiveSkill[i] , PlayerTempData->PassiveSkillLv[i] );
		}

		//-------------------------------------------------------------------------
		ReCalculateEqOnly();
		/*
		//先計算裝備能力
		TempData.Attr.CalWearSkill( );
		map< int , int > SuitIDList;
		map< int , int >::iterator Iter;
		set< int > EqIDSet;

		//計算套裝資料
		for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
		{
			Item = GetEqItem( i );

			GameObjDbStructEx* OrgDB = St_GetObjDB( Item->OrgObjID );
			ItemStateModeStruct Bk_Mode = Item->Mode;
			if( OrgDB == NULL )
				continue;

			if( i == EM_EQWearPos_SecondHand )
			{
				if(		TempData.Attr.Fin.WearSkill.SecondHand == false
					&& OrgDB->IsWeapon() )
				{
					Item->Mode.EQCannotEquipment = true;
					continue;
				}
			}
			//////////////////////////////////////////////////////////////////////////
			if( CheckEQLimit( OrgDB , Item->Mode.IgnoreLimitLv ) == false )
			{
				Item->Mode.EQCannotEquipment = true;
				continue;
			}
			else
			{
				Item->Mode.EQCannotEquipment = false;
			}


			if( Item->Mode.EQSoulBound )
			{
				if( Item->Mode.Trade != false )
				{
					Item->Mode.Trade = false;
				}
			}

			if( Item->Mode._Mode != Bk_Mode._Mode )
			{
				Net_FixItemInfo_EQ( i );
			}

			Item = GetEqItem( i );
			WearEQ( Item , i );

			if( EqIDSet.insert(Item->OrgObjID).second == false )
				continue;

			if( OrgDB->Item.SuitID == 0 )
				continue;		

			SuitIDList[ OrgDB->Item.SuitID ] ++;
		}

		for( Iter = SuitIDList.begin() ; Iter != SuitIDList.end() ; Iter++ )
		{
			if( Iter->second <= 1 )
				continue;

			WearSuit( Iter->first , Iter->second );
		}
		*/

		//計算卡片副加能力
		for( int i = 0 ; i < _MAX_CARD_COUNT_ ; i++ )
		{
			if( PlayerBaseData->Card.GetFlag( i ) != false )
			{	
				GameObjDbStructEx* CardDB = St_GetObjDB( i + Def_ObjectClass_Card );	
				if( CardDB ==NULL )
					continue;
				WearObject( CardDB->Item.CardAddpower );
			}
		}

	}


	//-------------------------------------------------------------------------

	FixWeaponType();
}
//////////////////////////////////////////////////////////////////////////
void    RoleDataEx::ReCalculatePhantom()
{
	PhantomStruct& info = PlayerBaseData->Phantom;
	for( int i = 0 ; i < 2 ; i++ )
	{
		if( info.EQ[i] == 0 )
			continue;

		GameObjDbStructEx* objDB = St_GetObjDB( info.EQ[i] );
		if( objDB->IsPhantom() == false )
			continue;

		int pos = info.EQ[i] %1000;
		float powerlv  = info.Info[pos].Lv * FixArg().PhantomLvArg * ( 1 + info.Info[pos].Rank * FixArg().PhantomRankArg );
		
		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
		{
			int type	= objDB->Phantom.abi_Phantom.EqType[i];
			float value	= objDB->Phantom.abi_Phantom.EqTypeValue[i];

			if( type <= 0 || type >= EM_WearEqType_MaxCount )
				continue;

			value *= ( powerlv * PhantomAbiArg[type] );
			TempData.Attr.Mid.Body[ type ] += value;
			TempData.Attr.Mid.BodyRate[ type ] = TempData.Attr._CalRate( TempData.Attr.Mid.BodyRate[type ] , value );			
		}
	}
}

//計算Buff改變
void    RoleDataEx::ReCalculateBuff( )
{
	TempData.Attr.Init_MidValue();
	//計算法術Buff
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		WearBuff( BaseData.Buff[i].BuffID , BaseData.Buff[i].Power );
	}

	if( IsPlayer() )
	{
		
		//////////////////////////////////////////////////////////////////////////
		//計算新頭銜系統複加能力
		if( PlayerBaseData->TitleSys.Famous > 0 )
		{
			float power = 1.0f;
			if( TempData.Attr.Effect.TitleSysPowerUp )			
				power = 2.0f;

			for( int i = 0 ; i < _MAX_TITLESYS_TITLE_COUNT_ ; i++ )
			{
				GameObjDbStructEx* titleDB = St_GetObjDB( PlayerBaseData->TitleSys.TitleID[i] );
				if( titleDB->IsTitle() == false )
					continue;
				//TempData.Attr.AddAbility( &titleDB->Title.AbilityEx  , EM_Armor_None , 0 , power );				
				TempData.Attr.AddAbility_Buff( &titleDB->Title.AbilityEx , power );
			}			
		}
		//////////////////////////////////////////////////////////////////////////

		for( int i = 0 ; i < PlayerTempData->PassiveSkill.Size() ; i++ )
		{
			//WearMagic( PlayerTempData->PassiveSkill[i] , PlayerTempData->PassiveSkillLv[i] );
			WearBuff( PlayerTempData->PassiveSkill[i] , PlayerTempData->PassiveSkillLv[i] );
		}

		//寵物輔助能力
		//3.輔助力計算方式改為：[ (成長率*等級*(目前資質+目前忠誠度)/160) + (目前屬性值*(目前資質)/30) ] * [ (目前忠誠度+20)/100 ]

		for( int i = 0 ; i < MAX_CultivatePet_Count ; i++ )
		{
			CultivatePetStruct& PetTemp = PlayerBaseData->Pet.Base[i];
			if( PetTemp.IsEmpty() )
				continue;
			GameObjDbStructEx* ItemEggDB = St_GetObjDB( PetTemp.ItemOrgID );
			if( ItemEggDB == NULL )
				continue;

			if( PetTemp.EventType == EM_CultivatePetCommandType_Summon )
			{
				float HungerEffect = ( (PetTemp.Hunger-1)/20 +1 )*0.2f;

				TempData.Attr.Mid.Body[ EM_WearEqType_STR ] += int(( ( ItemEggDB->Item.Pet.STR *PetTemp.Lv *(PetTemp.Talent + PetTemp.Loyal )/160.0f +  PetTemp.STR * PetTemp.Talent / 30.0f ) *( PetTemp.Loyal+20) / 100.0f )*HungerEffect);
				TempData.Attr.Mid.Body[ EM_WearEqType_STA ] += int(( ( ItemEggDB->Item.Pet.STA *PetTemp.Lv *(PetTemp.Talent + PetTemp.Loyal )/160.0f +  PetTemp.STA * PetTemp.Talent / 30.0f ) *( PetTemp.Loyal+20) / 100.0f )*HungerEffect);
				TempData.Attr.Mid.Body[ EM_WearEqType_INT ] += int(( ( ItemEggDB->Item.Pet.INT *PetTemp.Lv *(PetTemp.Talent + PetTemp.Loyal )/160.0f +  PetTemp.INT * PetTemp.Talent / 30.0f ) *( PetTemp.Loyal+20) / 100.0f )*HungerEffect);
				TempData.Attr.Mid.Body[ EM_WearEqType_MND ] += int(( ( ItemEggDB->Item.Pet.MND *PetTemp.Lv *(PetTemp.Talent + PetTemp.Loyal )/160.0f +  PetTemp.MND * PetTemp.Talent / 30.0f ) *( PetTemp.Loyal+20) / 100.0f )*HungerEffect);
				TempData.Attr.Mid.Body[ EM_WearEqType_AGI ] += int(( ( ItemEggDB->Item.Pet.AGI *PetTemp.Lv *(PetTemp.Talent + PetTemp.Loyal )/160.0f +  PetTemp.AGI * PetTemp.Talent / 30.0f ) *( PetTemp.Loyal+20) / 100.0f )*HungerEffect);

				for( int i = 0 ; i < PetTemp.Magic.Size() ; i++ )
				{
					MagicBaseStruct& MagicTemp = PetTemp.Magic[i];
					//WearMagic( MagicTemp.ID , MagicTemp.Lv );
					GameObjDbStructEx* MagicDB = St_GetObjDB( MagicTemp.ID );
					if( MagicDB->IsMagicCollect() == false )
						continue;

					if( MagicDB->MagicCol.EffectType != EM_Magic_Eq )
						continue;

					for( int x = 0 ; x <  _MAX_MAGICCOLLECT_GROUP_COUNT_ ; x++ )
						for( int y = 0 ; y < _MAX_MAGICCOLLECT_COUNT_ ; y++ )
						{
							//						GameObjDbStructEx* MagicBase = St_GetObjDB( MagicDB->MagicCol.Magic[x][y].MagicBaseID );
							//						if( MagicBase == NULL || MagicBase->IsMagicBase() == false )
							//							continue;
							WearBuff( MagicDB->MagicCol.Magic[x][y].MagicBaseID , MagicTemp.Lv );
						}


				}
				break;
			}
		}

	}

}

//記算法術與裝備
/*
void    RoleDataEx::ReCalculateMagicAndEQ( )
{
	ReCalculateEQNoBuff();


	if( IsPlayer() )
	{
		TempData.Attr.ExAddHP = PlayerBaseData->TitleCount * 5;
		if( BaseData.TitleID > 0 )
		{
			if( CheckWearTitle( BaseData.TitleID ) == false )
			{
				BaseData.TitleID = 0;
			}
			else
			{
				WearObject( BaseData.TitleID );
			}
		}

		//記算被動技能
		for( i = 0 ; i < PlayerTempData->PassiveSkill.Size() ; i++ )
		{
			WearMagic( PlayerTempData->PassiveSkill[i] , PlayerTempData->PassiveSkillLv[i] );
		}
		//-------------------------------------------------------------------------
		//先計算裝備能力
		//計算套裝資料
		for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
		{
			Item = GetEqItem( i );

			GameObjDbStructEx* OrgDB = St_GetObjDB( Item->OrgObjID );
			ItemStateModeStruct Bk_Mode = Item->Mode;
			if( OrgDB == NULL )
				continue;

			if( i == EM_EQWearPos_SecondHand )
			{
				if(		TempData.Attr.Fin.WearSkill.SecondHand == false
					&& OrgDB->IsWeapon() )
				{
					Item->Mode.EQCannotEquipment = true;
					continue;
				}
			}
			//////////////////////////////////////////////////////////////////////////
			if( CheckEQLimit( OrgDB , Item->Mode.IgnoreLimitLv ) == false )
			{
				Item->Mode.EQCannotEquipment = true;
				continue;
			}
			else
			{
				Item->Mode.EQCannotEquipment = false;
			}

			if( Item->Mode.EQSoulBound )
			{
				if( Item->Mode.Trade != false )
				{
					Item->Mode.Trade = false;
				}
			}

			if( Item->Mode._Mode != Bk_Mode._Mode )
			{
				Net_FixItemInfo_EQ( i );
			}

			Item = GetEqItem( i );
			WearEQ( Item , i );

			if( OrgDB->Item.SuitID == 0 )
				continue;		

			if( EqIDSet.insert(Item->OrgObjID).second == false )
				continue;

			SuitIDList[ OrgDB->Item.SuitID ] ++;
		}

		for( Iter = SuitIDList.begin() ; Iter != SuitIDList.end() ; Iter++ )
		{
			if( Iter->second <= 1 )
				continue;

			WearSuit( Iter->first , Iter->second );
		}

		//計算寵物帶來的能力
		for( int i = 0 ; i < MAX_CultivatePet_Count ; i++ )
		{
			CultivatePetStruct& PetInfo = PlayerBaseData->Pet.Base[i];
			if(		PetInfo.EventType != EM_CultivatePetCommandType_Summon 
				||	PetInfo.IsEmpty()	)
				continue;

			for( int j = 0 ; j < EM_CultivatePetLifeSkillType_Max ; j++ )
			{
				GameObjDbStructEx* MagicColOrgDB = St_GetObjDB( PetInfo.Magic[j].ID );
				if( MagicColOrgDB->IsMagicCollect() == false )
					continue;
				if( MagicColOrgDB->MagicCol.EffectType == EM_Magic_PetEq )
					continue;

				WearMagic( MagicColOrgDB->MagicCol.Magic_List[0].MagicBaseID , PetInfo.Magic[j].Lv );
			}

			break;
		}
	}
	
}
*/
//-----------------------------------------------------------------------------------------------
//貝份定時檢查的資料
void    RoleDataEx::InitOnTimeCheck( )
{

}
//-----------------------------------------------------------------------------------------------
bool	RoleDataEx::WearEQ( ItemFieldStruct* Field , int Pos )
{
	if(		Field == NULL 
		||	( Field->Durable <= 0 && Pos != EM_EQWearPos_Ammo) )
		return false;

	GameObjDbStructEx*		OrgDB	= St_GetObjDB( Field->OrgObjID );

	if( OrgDB == NULL )
		return false;



	float	PowerRate_Durable = 1.0f;

	int OrgDurable = ( OrgDB->Item.Durable * Field->Quality ) / 100;

	if( Field->Durable/100 > 100 || Field->Durable/100 > OrgDurable )
		PowerRate_Durable = 1.2f;
	else if( Field->Durable/100 > OrgDurable/2 )
		PowerRate_Durable = 1.0f;
	else if( Field->Durable/100 > OrgDurable/5 )
		PowerRate_Durable = 0.8f;
	else
		PowerRate_Durable = 0.2f;


	//物品能力檢查

	float	Power = float( Field->PowerQuality ) / 10.0f * PowerRate_Durable;


	if( OrgDB->IsWeapon() == false )
	{
		if ( WearObject( OrgDB , -1 , Power , Field->Rare ) == false )
			return false;
	}
	else
	{
		if( TempData.Attr.Effect.WeaponIgnore != false )
			return false;

		if ( WearObject( OrgDB , Pos , Power , Field->Rare ) == false )
			return false;

		if( Pos == EM_EQWearPos_SecondHand )
		{
			TempData.Attr.SecWeaponType = OrgDB->Item.WeaponType;
			TempData.Attr.SecAttackRange = OrgDB->Item.AttackRange;
			TempData.Attr.SecWeaponAttackSpeed = OrgDB->Item.AttackSpeed;

		}
		else if( Pos == EM_EQWearPos_MainHand )
		{
			TempData.Attr.MainWeaponType = OrgDB->Item.WeaponType;
			TempData.Attr.MainAttackRange = OrgDB->Item.AttackRange;
			TempData.Attr.MainWeaponAttackSpeed = OrgDB->Item.AttackSpeed;
		}
		else if( Pos == EM_EQWearPos_Bow )
		{
			TempData.Attr.BowWeaponType = OrgDB->Item.WeaponType;
			TempData.Attr.BaseEQ.Bow_AttackRange = (float)OrgDB->Item.AttackRange; 
			TempData.Attr.BoweAttackSpeed = OrgDB->Item.AttackSpeed;
		}
		else if( Pos == EM_EQWearPos_Ammo )
		{
			TempData.Attr.BaseEQ.Throw_AttackRange = (float)OrgDB->Item.AttackRange; 
			TempData.Attr.ThrowAttackSpeed = OrgDB->Item.AttackSpeed;
		}
	}

	if( Field->Level != 0 )
	{
		//
		GameObjDbStructEx* RefineAbilityDB = GetRefinAblility( OrgDB , Field->Level );
		if( RefineAbilityDB )
		{
			WearObject( RefineAbilityDB , Pos , PowerRate_Durable );

			int ExEqPowerRate = RefineAbilityDB->EqRefineAttribute.ExEqPowerRate;
			if( ExEqPowerRate != 0 )
			{
				float fAddDmg = 0.0f;
				float fAddMDmg = 0.0f;
				float fAddDef = 0.0f;
				float fAddMDef = 0.0f;
				GetRareEffect( OrgDB , Field->Rare , fAddDmg , fAddMDmg , fAddDef , fAddMDef );

				GameObjectWearEqStruct AbilityBK = OrgDB->Item.Ability;

				for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
				{
					if( AbilityBK.EqType[i] == EM_WearEqType_DMG )
					{
						AbilityBK.EqTypeValue[i]+= (int)fAddDmg;
						fAddDmg = 0;
					}
					else if( AbilityBK.EqType[i] == EM_WearEqType_MDMG )
					{
						AbilityBK.EqTypeValue[i]+= (int)fAddMDmg;
						fAddMDmg = 0;
					}
					else if( AbilityBK.EqType[i] == EM_WearEqType_DEF )
					{
						AbilityBK.EqTypeValue[i]+= (int)fAddDef;
						fAddDef = 0;
					}
					else if( AbilityBK.EqType[i] == EM_WearEqType_MDEF )
					{
						AbilityBK.EqTypeValue[i]+= (int)fAddMDef;
						fAddMDef = 0;
					}
					else
					{
						AbilityBK.EqTypeValue[i] = 0;
						continue;
					}

					AbilityBK.EqTypeValue[i] = AbilityBK.EqTypeValue[i] * ExEqPowerRate / 100;

					/*
					if(		AbilityBK.EqType[i] != EM_WearEqType_DMG
						&&	AbilityBK.EqType[i] != EM_WearEqType_MDMG
						&&	AbilityBK.EqType[i] != EM_WearEqType_DEF
						&&	AbilityBK.EqType[i] != EM_WearEqType_MDEF )
					{
						AbilityBK.EqTypeValue[i] = 0;
					}
					else
					{
						AbilityBK.EqTypeValue[i] = AbilityBK.EqTypeValue[i] * ExEqPowerRate / 100;
					}
					*/
				}
				TempData.Attr.AddAbility( &AbilityBK , EM_Armor_None , Pos , PowerRate_Durable );	
			}
		}
	}

	//WearObject( Field->Inherent , Pos );
	for( int i = 0 ; i < 6 ; i++ )
	{
		if( Field->Inherent(i) == 0 )
			break;
		WearObject( Field->Inherent(i), Pos , PowerRate_Durable );
	}

	for( int i = 0 ; i < 4 ; i++ )
	{
		if( Field->Rune(i) == 0 )
			break;
		WearObject( Field->Rune(i) , Pos , PowerRate_Durable );
	}

	//WearObject( Field->Rune[1] , Pos );
	//WearObject( Field->Rune[2] , Pos );
	//WearObject( Field->Rune[3] , Pos ); 

	return true;
}

bool	RoleDataEx::WearSuit( int SuitID , int Count )
{

	GameObjDbStructEx*    OrgDB = St_GetObjDB( SuitID );
	RoleValueData&		  Attr = TempData.Attr;

	if( OrgDB == NULL || OrgDB->IsSuit() == false )
		return false;

	if( Count <= 1 || Count > 10 )
		return false;

	if( OrgDB->Suit.TotalCount < Count )
		Count = OrgDB->Suit.TotalCount;

	TempData.Attr.AddAbility( &OrgDB->Suit.SuitValue[ Count - 2 ].Ability  , EM_Armor_None , EM_EQWearPos_None , 1 );

	/*
	for( int i = 0 ; i < 10 ; i++ )
	{
		WearEqTypeENUM  EqType		= OrgDB->Suit.SuitValue[ Count - 2 ].EqType[ i ] ;
		int             EqTypeValue	= OrgDB->Suit.SuitValue[ Count - 2 ].EqTypeValue[ i ];

		Attr.Mid.Body[ EqType ] += EqTypeValue;
	}
*/
	return true;
}

bool	RoleDataEx::WearObject( int OrgDBID , int Pos , float Power , int AddRare )
{
	if( OrgDBID == 0 )
		return false;

	GameObjDbStructEx*    OrgDB = St_GetObjDB( OrgDBID );
	return WearObject( OrgDB , Pos , Power , AddRare );
}

bool	RoleDataEx::WearMagic( int OrgDBID , int MagicLv )
{
	if( OrgDBID == 0 )
		return false;

	GameObjDbStructEx*    OrgDB = St_GetObjDB( OrgDBID );
	if( OrgDB == NULL )
		return false;

	float Power = ( 1 + MagicLv * OrgDB->MagicBase.Ability_SkillLVArg / 100 );
	return WearObject( OrgDB , -1 , Power );
}
bool	RoleDataEx::WearBuff( int OrgDBID , int MagicLv )
{
	if( OrgDBID == 0 )
		return false;

	GameObjDbStructEx*    OrgDB = St_GetObjDB( OrgDBID );
	if( OrgDB == NULL )
		return false;

	float Power = ( 1 + MagicLv * OrgDB->MagicBase.Ability_SkillLVArg / 100 );
//	return WearObject( OrgDB , -1 , Power );

	RoleValueData& Attr = TempData.Attr;
	GameObjectWearEqStruct* Ability;

	Ability = &OrgDB->MagicBase.Ability;
	Attr.Effect._Value[0] = Attr.Effect._Value[0] | OrgDB->MagicBase.Effect._Value[0];
	Attr.Effect._Value[1] = Attr.Effect._Value[1] | OrgDB->MagicBase.Effect._Value[1];
	Attr.DisableMagicSet = Attr.DisableMagicSet | OrgDB->MagicBase.ClearMagicGroupSet;
	Attr.AssistMagicSetting._Type = Attr.AssistMagicSetting._Type | OrgDB->MagicBase.Setting._Type;
	Attr.AddAbility_Buff( Ability , Power );

    return true; // add by slime 2010/08/03
}

bool	RoleDataEx::WearObject( GameObjDbStructEx* OrgDB , int Pos , float Power , int AddRare )
{
	if( OrgDB->IsEmpty() )
		return  false;

	RoleValueData& Attr = TempData.Attr;
	GameObjectWearEqStruct* Ability;


	switch( OrgDB->Classification )
	{
	case EM_ObjectClass_Item:
		{
//			Ability = &OrgDB->Item.Ability;
			GameObjectWearEqStruct TempAbility = OrgDB->Item.Ability;
			if( OrgDB->IsArmor() )
			{
				if( AddRare != 0 )
				{
					float Dmg,MDmg,Def,MDef;
					GetRareEffect( OrgDB , AddRare , Dmg ,MDmg , Def , MDef );
					TempAbility.EqTypeValue[0] += int(Def);
					TempAbility.EqTypeValue[1] += int(MDef);
				}

				Attr.AddAbility( &TempAbility , OrgDB->Item.ArmorType , Pos , Power );
			}
			else
			{
				if( OrgDB->IsWeapon() && OrgDB->Item.WeaponPos == EM_WeaponPos_Ammo )
				{
					Attr.AddAbility( &TempAbility , EM_Armor_None , Pos , 1 );
				}
				else
				{
					if( AddRare != 0 )
					{
						float Dmg,MDmg,Def,MDef;
						GetRareEffect( OrgDB , AddRare , Dmg ,MDmg , Def , MDef );
						TempAbility.EqTypeValue[0] += int(Dmg);
						TempAbility.EqTypeValue[1] += int(MDmg);
					}

					Attr.AddAbility( &TempAbility , EM_Armor_None , Pos , Power );
				}
			}

		}
		break;
	case EM_ObjectClass_MagicCollect:
		{

			if( OrgDB->MagicCol.EffectType != EM_Magic_Eq )
				break;

			for( int x = 0 ; x <  _MAX_MAGICCOLLECT_GROUP_COUNT_ ; x++ )
				for( int y = 0 ; y < _MAX_MAGICCOLLECT_COUNT_ ; y++ )
				{
					GameObjDbStructEx* MagicBase = St_GetObjDB( OrgDB->MagicCol.Magic[x][y].MagicBaseID );
					if( MagicBase == NULL || MagicBase->IsMagicBase() == false )
						continue;
					Ability = &MagicBase->MagicBase.Ability;
					Attr.DisableMagicSet = Attr.DisableMagicSet | MagicBase->MagicBase.ClearMagicGroupSet;
					Attr.AssistMagicSetting._Type = Attr.AssistMagicSetting._Type | MagicBase->MagicBase.Setting._Type;
					Attr.AddAbility( Ability , EM_Armor_None , Pos , Power );
				}
		}
		break;		
	case EM_ObjectClass_MagicBase:
		{
			Ability = &OrgDB->MagicBase.Ability;
//			Attr.Effect._Value[0] = Attr.Effect._Value[0] | OrgDB->MagicBase.Effect._Value[0];
//			Attr.Effect._Value[1] = Attr.Effect._Value[1] | OrgDB->MagicBase.Effect._Value[1];
			Attr.DisableMagicSet = Attr.DisableMagicSet | OrgDB->MagicBase.ClearMagicGroupSet;
			Attr.AssistMagicSetting._Type = Attr.AssistMagicSetting._Type | OrgDB->MagicBase.Setting._Type;
			Attr.AddAbility( Ability , EM_Armor_None , Pos , Power );
		}
		break;
	case EM_ObjectClass_Attribute:
		Ability = &OrgDB->Attirbute.Ability;
		Attr.AddAbility( Ability , EM_Armor_None , Pos , Power );
		break;
	case EM_ObjectClass_EqRefineAbility:
		Ability = &OrgDB->EqRefineAttribute.Ability;
		Ability->OnAttackMagicID = 0;
		Ability->OnAttackMagicRank = 0;
		Ability->OnAttackMagicRate = 0;
		Attr.AddAbility( Ability , EM_Armor_None , Pos , Power );
		break;
	case EM_ObjectClass_NPC:
	case EM_ObjectClass_QuestNPC:
		Attr.AddAbility( &OrgDB->NPC.Ability , EM_Armor_None , Pos , Power );
		Attr.AddAbility( &OrgDB->NPC.AbilityEx , EM_Armor_None , Pos , Power );
//		Attr.AddAbility( &OrgDB->NPC.Ability[1] , EM_Armor_None , Pos , Power );
		break;
	case EM_ObjectClass_Title:
		Attr.AddAbility( &OrgDB->Title.Ability  , EM_Armor_None , Pos , Power );
		break;
	default:
		return false;
	}


	return true;
}

//-----------------------------------------------------------------------------------------------
//計算兩者關係好壞值(用來決定攻擊與幫助的優先次序)
float	RoleDataEx::CalRelation( RoleDataEx* Target )
{
	//(暫時)
	if( Target->TempData.Sys.GUID == TempData.Sys.GUID )
		return 0;

	int DLv = Level() - Target->Level();
	if( DLv <= -10 )
		DLv = -10;

	int	L = int( Length( Target ) ) + DLv * 5;

	if( L > 1000 )
		return 0;

	return float(L - 1000 );
}
//-----------------------------------------------------------------------------------------------
//基本仇恨值
int		RoleDataEx::BaseHate( RoleData* Target )
{
	int	DLV = Target->TempData.Attr.Level - TempData.Attr.Level;
	DLV = __max( 0  , DLV );
	DLV = __min( 10 , DLV );

	return HateTable[BaseData.Race][Target->BaseData.Race] + DLV * 5;
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//他人影響 加HP 或加MP
void	RoleDataEx::AddHP( RoleDataEx* Target ,  float DHP , float HateRate )
{
	float OrgDHP = DHP;
	if( DHP == 0 )
		return;

	if( IsDead() )
		return;

	if( Target == NULL )
		Target = this;

	TempData.LastDHp = (int)DHP;
	TempData.LastDHpTarget = Target->GUID();

	Target->GoodEvilAtkInfoProc( this , (int)DHP );

	if( DHP < 0 )
	{
		MagicClearTimeStruct& ClearEvent = TempData.BackInfo.BuffClearTime;
		ClearEvent.UnderAtk = true;
	}

	if( BaseData.HP+DHP < 0  )
		DHP = BaseData.HP * -1;  
	else if( BaseData.HP+DHP > TempData.Attr.Fin.MaxHP )
		DHP = TempData.Attr.Fin.MaxHP - BaseData.HP;

	BaseData.HP += DHP;

	if( DHP == 0 )
		return;

	if( OrgDHP > 0 && DHP < 0 )
		return;
	if( OrgDHP <0 && DHP > 0 )
		return;

	if( Target != NULL && Target->IsDead() == false )
	{
		CalHate( Target , int( DHP*-1 ) , int( DHP*-1 *HateRate) );

		if( OrgDHP > 0 )
		{
			Target->PlayerTempData->BGInfo.iHealVal += int( DHP );
		}
		else
		{
			if( Target != this )
			{
				Target->PlayerTempData->BGInfo.iDamageVal -= int( DHP );
				PlayerTempData->BGInfo.iDefVal -= int( DHP );
			}
		}

	}

	if( BaseData.HP < TempData.LockHP )
	{
		BaseData.HP = (float)TempData.LockHP;
		LuaCheckFunction( GUID() , Target->GUID() , TempData.LockHPEvent.Begin() );		
	}

	if( BaseData.HP < 1 )
	{		
		St_ProcessDead( this , Target );
		//清除HP為0的Buff
		TempData.BackInfo.BuffClearTime.HP0 = true;
	}

}
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::AddMP( RoleDataEx* Target ,  float DMP , float HateRate )
{
	float	LMP = BaseData.MP;
	if( DMP == 0 )
		return;
	if( IsDead() )
		return;

	Target->GoodEvilAtkInfoProc( this , (int)DMP );

	BaseData.MP += DMP;

	if( BaseData.MP > TempData.Attr.Fin.MaxMP )
		BaseData.MP = TempData.Attr.Fin.MaxMP ;

	if( BaseData.MP <= 0 )
	{
		BaseData.MP = 0;
		TempData.BackInfo.BuffClearTime.MP0 = true;
	}
	if( Target == NULL )
		return;

	if( LMP ==  BaseData.MP )
		return;

	if( DMP < 0 )
		CalHate( Target , int( DMP*-1 ) , int( DMP*-1*HateRate ) );		

}
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::AddSP( RoleDataEx* Target ,  float DSP , float HateRate )
{
	float	LSP = BaseData.SP;

	if( DSP == 0 )
		return;

	if( IsDead() )
		return;

	GoodEvilAtkInfoProc( Target , (int)DSP );

	BaseData.SP += DSP;

	if( BaseData.SP > TempData.Attr.Fin.MaxSP )
		BaseData.SP = TempData.Attr.Fin.MaxSP;

	if( BaseData.SP <= 0 )
	{
		BaseData.SP = 0;

		switch( BaseData.Voc )
		{
		case EM_Vocation_Warrior:		// 戰士
		case EM_Vocation_Psyron:
			TempData.BackInfo.BuffClearTime.WarriorSP0 = true;
			break;
		case EM_Vocation_Ranger:		// 遊俠
		case EM_Vocation_Harpsyn:
			TempData.BackInfo.BuffClearTime.RangerSP0 = true;
			break;
		case EM_Vocation_Rogue:			// 盜賊
		case EM_Vocation_Duelist:		// 鬥棋士
			TempData.BackInfo.BuffClearTime.RogueSP0 = true;
			break;
		}
	}

	if( Target == NULL )
		return;

	if( LSP ==  BaseData.SP )
		return;

	CalHate( Target , int( DSP*-1 ) , int( DSP*-1 *HateRate) );		

}
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::AddSP_Sub( RoleDataEx* Target ,  float DSP , float HateRate )
{
	float	LSubSP = BaseData.SP_Sub;

	if( DSP == 0 )
		return;

	if( IsDead() )
		return;

	BaseData.SP_Sub += DSP;

	if( BaseData.SP_Sub > TempData.Attr.Fin.MaxSP_Sub )
		BaseData.SP_Sub = TempData.Attr.Fin.MaxSP_Sub;

	if( BaseData.SP_Sub <= 0 )
	{
		BaseData.SP_Sub = 0;

		switch( BaseData.Voc_Sub )
		{
		case EM_Vocation_Warrior:		// 戰士
		case EM_Vocation_Psyron:
			TempData.BackInfo.BuffClearTime.WarriorSP0 = true;
			break;
		case EM_Vocation_Ranger:		// 遊俠
		case EM_Vocation_Harpsyn:
			TempData.BackInfo.BuffClearTime.RangerSP0 = true;
			break;
		case EM_Vocation_Rogue:			// 盜賊
		case EM_Vocation_Duelist:		// 鬥棋士
			TempData.BackInfo.BuffClearTime.RogueSP0 = true;
			break;
		}
	}


	if( Target == NULL )
		return;

	if( LSubSP ==  BaseData.SP_Sub )
		return;


	CalHate( Target , int( DSP*-1 ) , int(DSP*-1 *HateRate) );		

}
void    RoleDataEx::AddStomachPoint( int DPoint )
{
	if( DPoint == 0 )
		return;

	if( IsDead() )
		return;

	int OrgPoint = BaseData.StomachPoint;
	BaseData.StomachPoint += DPoint;
	if( BaseData.StomachPoint > 100 )
		BaseData.StomachPoint = 100;

	if( BaseData.StomachPoint < 0 )
		BaseData.StomachPoint = 0;	

	if( OrgPoint != BaseData.StomachPoint )
		Net_FixRoleValue( EM_RoleValue_StomachPoint , (float)BaseData.StomachPoint );


}
//-----------------------------------------------------------------------------------------------
void    RoleDataEx::OnTimeCalHate( )
{
	if( IsAttack() == false )
		return;

	//5秒處理一次
	if( ClockMod( 50 ) )
		return;

	ReCalhateList( );

	/*
	int		i; 
	for( i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++ )
	{
	TempData.NPCHate.Hate[i].HatePoint /= 2 ;
	}

	TempData.NPCHate.MaxHitPoint/=3;
	*/
}
void RoleDataEx::ClearHate()
{

	RoleDataEx*     Target;
	//    NPCHateStruct*	NPCHate;
	int             TempID;

	for( int i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++ )
	{
		TempID = TempData.NPCHate.Hate[i].ItemID;
		//        if( TempID == -1 )
		//            break;
		TempData.NPCHate.Hate[i].Init();

		Target = (RoleDataEx*)St_GetRoleData( TempID );
		if( Target == NULL || Target->IsNPC() )
			continue;

		Target->FixAttackMode();
	}
	TempData.NPCHate.Hate.Clear();
	//TempData.NPCHate.Init();

}

//-----------------------------------------------------------------------------------------------
//增加某一個人的仇恨值( 此怪物被 npc 或 pc 打)
//並做攻擊目標的轉換
bool	RoleDataEx::CalHate( RoleDataEx* Att , int Damage , int HatePoint )
{
	RoleDataEx* Target = this;

	if( IsDead() || Att->IsDead() )
		return false;

	if( Att->BaseData.Mode.Fight == false )
		return false;

/*	if(		Target->IsPlayer() == false 
		&&	BaseData.Mode.Strikback == false 
		&&	HatePoint > 0 )
		HatePoint = 0;
		*/

	if( SecRoomID() == -1 || Att->SecRoomID() == -1 )
		return false;

	if( HatePoint == 0 && Damage == 0 ) 
		return false;

	if( Att == this && HatePoint > 0 )
		return false;

	if( HatePoint == 1 && ( TempData.Attr.Effect.BadMagicInvincible && TempData.Attr.Effect.BadPhyInvincible ) )
		return false;

	//

	if( TempData.NPCHate.BeginAtkDBID <= 0  )
	{
		RoleDataEx* AttOwner =  Att->GetOrgOwner( );
//		if( AttOwner == NULL )
//			AttOwner = Att;

		if( AttOwner->IsPlayer() )
		{
			TempData.NPCHate.BeginAtkDBID = AttOwner->DBID();
			TempData.NPCHate.BeginAtkPartyID = AttOwner->PartyID();
		}
		//Damage= MaxHP()/2 + Damage*3;
	}

	if( HatePoint < 0 )
	{
		if( IsAttackMode() == false )
			return false;
		HatePoint *= -1;

		int TargetID = -1;
		Target = (RoleDataEx*)St_GetRoleData( TempData.AI.TargetID );
		if( Target != NULL )
		{
			Target->CalHate( Att , 0 , HatePoint /4 );
			TargetID = Target->GUID();
		}

		for( int i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++ )
		{
			NPCHateStruct& Hate = TempData.NPCHate.Hate[ i ];
			if( Hate.ItemID != TargetID )
			{
				RoleDataEx* Other= (RoleDataEx*)St_GetRoleData( Hate.ItemID );
				if( Other == NULL || !Other->IsNPC() )
					continue;
				Other->CalHate( Att , 0 , HatePoint / 4 );
			}
		}
		return true;
	}

	//取得id資訊位置	
	NPCHateStruct*	NPCHate = GetHatePos( Att->GUID() , Att->DBID() ); 

	if(	 Target->CheckStrikback() != false || Target->IsPlayer() )  
	{
		Att->IsAttackMode( true );
		IsAttackMode( true );
	}
	Att->TempData.PlayerClsHateColdown = 10 ;
	Target->TempData.PlayerClsHateColdown = 10 ;

	if( Damage < 0 )
		Damage = 0;

	float hateRate = __max(( Att->TempData.Attr.Mid.Body[EM_WearEqType_HateRate] + 100 ) / 100 , 0.1f );

	NPCHate->HatePoint += ( HatePoint * hateRate );
	NPCHate->HitPoint  += Damage;
	NPCHate->PartyID	= Att->PartyID();

	if( IsNPC() )
	{
		//如果沒有在攻擊狀態 就反擊
		if(  Target->IsAttack() == false && Target->CheckStrikback() )
		{
			Target->AttackTarget( Att->GUID() );
		}

		if( Target->TempData.Attr.Effect.AI_LowAttackPriority == false && HatePoint > 1 )
		{
			int  MaxHitPoint = 0;
			//找出目前攻擊目標
			NPCHateStruct*	NPCAtkTarget = GetHatePos( AttackTargetID() ); 
			RoleDataEx* AttackTarget = St_GetRoleData( AttackTargetID() );
			if( NPCAtkTarget != NULL && AttackTarget != NULL && AttackTarget->TempData.Attr.Effect.AI_LowAttackPriority == false )
			{

				if( Length( Att ) >= 100 )
				{
					MaxHitPoint = NPCAtkTarget->TotalHatePoint() * 13 / 10 ;
				}
				else
				{
					MaxHitPoint = NPCAtkTarget->TotalHatePoint() * 11 / 10 ;
				}
			}

			Target->TempData.NPCHate.MaxHitPoint = MaxHitPoint;

			RoleDataEx* PetOwner = St_GetRoleData( OwnerGUID() );
			if( PetOwner == NULL || IsPet( PetOwner ) == false )
			{
				//攻擊超過一定量轉變目標
				if(		MaxHitPoint < NPCHate->TotalHatePoint() 
					&&	TempData.Attr.Effect.LockTarget == false 
					&&  Target->CheckStrikback() != false		) 
				{
					Target->TempData.NPCHate.MaxHitPoint	= NPCHate->TotalHatePoint();
					Target->TargetID( Att->GUID() );
				}
			}
		}

	}
	else if( Att->IsPlayer() )
	{
		//取得id資訊位置	
		NPCHateStruct*	AttPlayerHate = Att->GetHatePos( GUID() , DBID() ); 
		AttPlayerHate->HatePoint ++;
	}

	RoleDataEx* AttOwner = St_GetRoleData( Att->OwnerGUID() );
	if( AttOwner != NULL )
	{
		Target->CalHate( AttOwner , Damage , HatePoint/4+1 );
	}

	if( Att->BaseData.SysFlag.IsHonorLeader == false ) 
	{
		if( TempData.NPCHate.MaxHitLv < Att->Level() )
			TempData.NPCHate.MaxHitLv = Att->Level();
	}
	else
	{
		if( TempData.NPCHate.MaxHitLv < Level() )
			TempData.NPCHate.MaxHitLv = Level();
	}

	if( Att->IsPlayer() && Target->IsPlayer() )
	{
		Att->TempData.UpdateInfo.OnAttackPlayer = true;

		//處理PK 攻擊與防守的問題
		//Att->GoodEvilAtkInfoProc( Target );
		//Target->GoodEvilAtkInfoProc( Att , EM_GoodEvilAtkInfoType_Def );		
	}

	if( HatePoint > 1 )
	{
		PartyInfoStruct* Party = Att->GetPartyInfo( );

		if( Party != NULL )
		{
			for( unsigned int i = 0 ; i < Party->Member.size() ; i++ )
			{
				if( Party->Member[i].DBID == Att->DBID() )
					continue;

				RoleDataEx* Member = St_GetRoleData( Party->Member[i].GItemID );
				if( Member == NULL )
					continue;

				if( Member->Length( this ) > 600 )
					continue;

				CalHate( Member , 0 , 1 );
			}
		}
	}

	return true;
}

bool	RoleDataEx::CalTempHate( RoleDataEx* Att , int Hate )
{
	RoleDataEx* Target = this;

	if( Att == this )
		return false;

	if( Hate == 0 ) 
		return false;

	//取得id資訊位置	
	NPCHateStruct*	NPCHate = GetHatePos( Att->GUID() , Att->DBID() ); 	

	if( Hate == -1 )
	{
		Hate = TempData.NPCHate.MaxHitPoint - NPCHate->HatePoint + 10;
	}

	NPCHate->TempHatePoint += Hate;

	if( IsNPC() && Hate > 0 )
	{
		Att->IsAttackMode( true );
		IsAttackMode( true );

		//如果沒有在攻擊狀態 就反擊
		if(  Target->IsAttack() == false && Target->CheckStrikback() )
		{
			Target->AttackTarget( Att->GUID() );
		}
		else
		{
			//Target->TempData.AI.TargetID		    = Att->GUID();
			//Target->TargetID( Att->GUID() );
		}

		//攻擊超過一定量轉變目標
//		if( TempData.NPCHate.MaxHitPoint < NPCHate->TotalHatePoint() ) 
		{
			Target->TempData.NPCHate.MaxHitPoint	= NPCHate->TotalHatePoint();
			//Target->TargetID( Att->GUID() );
		}
	}   

	return true;
}
//-----------------------------------------------------------------------------------------------
bool	RoleDataEx::ClearHate_One( int PlayerID )
{
	int PlayerPos = -1;
	int i;

	for( i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++)
	{
		int TempID = TempData.NPCHate.Hate[i].ItemID;

		if( TempID == PlayerID )
		{
			PlayerPos = i;
			break;
		}
	}

	if( PlayerPos != -1 )
	{
		TempData.NPCHate.Hate[PlayerPos] = TempData.NPCHate.Hate.Back();
		TempData.NPCHate.Hate.Pop_Back();
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------
bool	RoleDataEx::CalAttackTypeInfo( RoleDataEx* Target  , AttackHandTypeENUM Type , int& OutHitRate , int& OutDodge , int& OutMissRate )
{
	//////////////////////////////////////////////////////////////////////////
	if( CheckPhyAttack( Target ) == false )
	{
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	RoleValueData&	TAttr = Target->TempData.Attr;
	RoleValueData&	OAttr = TempData.Attr;
	int DLV = Level() - Target->Level();
	if( DLV > 20 )
		DLV = 20;

	if( DLV < -20 )
		DLV = -20;

	float	HitRate		= 0;
	float	DodgeRate	= 0;
	float	MissRate	= 0;
	//////////////////////////////////////////////////////////////////////////
	//計算Miss率
	//////////////////////////////////////////////////////////////////////////
	float WeaponSkill;
	if( IsNPC() )
	{
		WeaponSkill = Level() * 2.3f ;
	}
	else
	{
		switch(Type)
		{
		case EM_AttackHandType_Main:
			WeaponSkill = GetWeaponSkillValue( OAttr.MainWeaponType )+10;
			break;
		case EM_AttackHandType_Second:
			WeaponSkill = GetWeaponSkillValue( OAttr.SecWeaponType )+10;
			break;
		}
	}

	float TargetDefSkill = Target->GetSkillValue( EM_SkillValueType_Define )+10;


	if( WeaponSkill <= 0 )
		WeaponSkill = 1;

	float DSkillRate = ( TargetDefSkill - WeaponSkill ) / __max( WeaponSkill , TargetDefSkill );
	MissRate = DSkillRate*10 ;
	/*
	if( IsPlayer() && Target->IsPlayer() )
	{
		MissRate = 10 +  DSkillRate*30 ;
	}
	else
	{
		MissRate = 10 +  DSkillRate*30  - (DLV * FixArg().Miss_DLV);
	}
*/

	//////////////////////////////////////////////////////////////////////////
	//命中與閃避計算
	//////////////////////////////////////////////////////////////////////////
	switch( Type )
	{
	case EM_AttackHandType_Main:
		if( DLV > 0 )
		{
			HitRate		= OAttr.Fin.Main_HitRate;
			DodgeRate	= TAttr.Fin.DodgeRate;
		}
		else
		{
			HitRate		= OAttr.Fin.Main_HitRate;
			DodgeRate	= TAttr.Fin.DodgeRate;
		}
		break;
	case EM_AttackHandType_Second:
		if( DLV > 0 )
		{
			HitRate		= OAttr.Fin.Sec_HitRate;
			DodgeRate	= TAttr.Fin.DodgeRate;
		}
		else
		{
			HitRate		= OAttr.Fin.Sec_HitRate;
			DodgeRate	= TAttr.Fin.DodgeRate;
		}
		break;

	case EM_AttackHandType_None:
		return false;
	}

	float DHitRate = ( HitRate - DodgeRate ) / __max( HitRate , DodgeRate );
	

	HitRate = ( DHitRate * FixArg().PhyHit_Range + FixArg().PhyHit_Base );


	//絕對閃避值
	float AbsHitRate = OAttr.Mid.Body[ EM_WearEqType_PhyHitRate ] - TAttr.Mid.Body[EM_WearEqType_PhyDodgeRate];
	HitRate = HitRate + AbsHitRate;

//	if( HitRate >= 100 )
//		HitRate = 100;

	if( IsPlayer() && Target->IsPlayer() )
	{
	}
	else
	{
		//MissRate = 10 +  DSkillRate*30  - (DLV * FixArg().Miss_DLV);
		//HitRate += (DLV * FixArg().Miss_DLV);
		HitRate = HitRate * ( 100 + DLV * FixArg().Miss_DLV) / 100;
	}

	DodgeRate = float( 100 - int( HitRate ) );
	if( DodgeRate < 0 )
		DodgeRate = 0;

	OutHitRate = int( HitRate);
	OutDodge = int(DodgeRate);
	OutMissRate = int(MissRate);
	return true;
}
//計算攻擊模式
ATTACK_DMGTYPE_ENUM RoleDataEx::CheckAtkDmgType( RoleDataEx* Target , AttackHandTypeENUM Type )
{
	int		HitRate;
	int		DodgeRate;
	int		MissRate;

	if( CalAttackTypeInfo( Target , Type , HitRate , DodgeRate , MissRate) == false )
		return EM_ATTACK_DMGTYPE_NO_EFFECT;

	//////////////////////////////////////////////////////////////////////////
	RoleValueData&	TAttr = Target->TempData.Attr;
	RoleValueData&	OAttr = TempData.Attr;
	int DLV = Level() - Target->Level();
	if( DLV > 20 )
		DLV = 20;

	if( DLV < -20 )
		DLV = -20;

	if( rand() % 100 < DodgeRate )
	{
		return EM_ATTACK_DMGTYPE_DODGE;
	}

	if( rand() % 100 < MissRate )
	{
		return EM_ATTACK_DMGTYPE_MISS;
	}

/*
	int Total = int( HitRate + DodgeRate + MissRate )+1;
	float	RandValue = float( rand() % Total );

	if( RandValue < DodgeRate )
	{
		return EM_ATTACK_DMGTYPE_DODGE;
	}

	RandValue -= DodgeRate;
	if( RandValue < MissRate )
	{
		return EM_ATTACK_DMGTYPE_MISS;
	}
	*/
	//////////////////////////////////////////////////////////////////////////
	if( TAttr.CalShieldBlockRate( OAttr.Level , OAttr.Fin.ResistBlockRate )*100 > rand() % 100  )
	{
		return EM_ATTACK_DMGTYPE_SHIELD_BLOCK;
	}

	if( TAttr.CalParryRate( OAttr.Level , OAttr.Fin.ResistParryRate )*100 > rand() % 100  )
	{
		return EM_ATTACK_DMGTYPE_HALF;
	}

	/*
	//檢查是否被革擋
	if( TAttr.Fin.ParryRate > rand() % 100 )
	{
	return EM_ATTACK_DMGTYPE_HALF;
	}

	if( TAttr.Fin.ShieldBlockRate > rand() % 100 )
	{
	return EM_ATTACK_DMGTYPE_SHIELD_BLOCK;
	}
	*/

	//////////////////////////////////////////////////////////////////////////
	//　　Critial 
	//////////////////////////////////////////////////////////////////////////

	if( Type == EM_AttackHandType_Main )
	{
		//float  CritRate = OAttr.Fin.Main_CriticalHit + DLV * FixArg().Crit_DLV;
		float  CritRate = OAttr.CalCritialRate( OAttr.Fin.Main_CriticalHit , TAttr.Level , TAttr.Fin.ResistCriticalHit ) * 100 + DLV * FixArg().Crit_DLV;

		if( CritRate >= rand() % 100 )
		{
			//if( rand()%100 >= Target->TempData.Attr.Mid.Body[EM_WearEqType_ResistCritRate] )
			return EM_ATTACK_DMGTYPE_DOUBLE;
		}
	}
	else
	{
		//float  CritRate = OAttr.Fin.Sec_CriticalHit + DLV * FixArg().Crit_DLV;
		float  CritRate = OAttr.CalCritialRate( OAttr.Fin.Sec_CriticalHit , TAttr.Level , TAttr.Fin.ResistCriticalHit ) * 100 + DLV * FixArg().Crit_DLV;

		if( CritRate >= rand() % 100 )
		{
			//if( rand()%100 >= Target->TempData.Attr.Mid.Body[EM_WearEqType_ResistCritRate] )
			return EM_ATTACK_DMGTYPE_DOUBLE;
		}
	}

	return EM_ATTACK_DMGTYPE_NORMAL;
}
//-----------------------------------------------------------------------------------------------
//ExpRate 為百分比
int	RoleDataEx::AddPlotExp	( int PlotLv , int ExpRate )
{
	ExpRate = int( ExpRate + ExpRate * TempData.Attr.Mid.Body[ EM_WearEqType_AddPlotExpRate ] / 100 );
	if( PlotLv > (int)PlotExpTable.size() )
		return 0;

	int Exp			= ( int) ( (float) PlotExpTable[ ( PlotLv - 1 ) ] *  ( ( float ) ExpRate / 100 ) );
	int iSourceExp	= Exp;

	//////////////////////////////////////////////////////////
	//經驗值負債處理
	//////////////////////////////////////////////////////////
	{
		int HelfExp = int( Exp*0.7f );
		if( HelfExp > 0 && TempData.Attr.Ability->DebtExp < 0 )
		{
			if( HelfExp > TempData.Attr.Ability->DebtExp*-1 )
				HelfExp = TempData.Attr.Ability->DebtExp*-1;

			AddValue( EM_RoleValue_DebtExp , (float)HelfExp );
			Net_DeltaRoleValue( EM_RoleValue_DebtExp , (float)HelfExp );
			Exp -= HelfExp;
		}
	}

	Addexp( Exp );
	//	Net_DeltaRoleValue( EM_RoleValue_EXP , (float)Exp );

	return iSourceExp;
}
//ExpRate 為百分比
void	RoleDataEx::AddPlotMoney( int PlotLv , int MoneyRate )
{
	if( PlotLv > (int)PlotMoneyTable.size() )
		return;

	int Money = (int)( (float) PlotMoneyTable[ ( PlotLv - 1)  ] * ( (float) MoneyRate / 100 ) );

	AddBodyMoney( Money , NULL , EM_ActionType_PlotGive , true );	
}
//-----------------------------------------------------------------------------------------------
//增加技能經驗值
void	RoleDataEx::AddSkillExp( SkillValueTypeENUM Type , int Exp )
{
	float& SkillValue = TempData.Attr.Fin.SkillValue.Skill[ Type ];
	switch( Type )
	{
	case EM_SkillValueType_Unarmed:			// Unarmed空手
	case EM_SkillValueType_Blade:           // 劍
	case EM_SkillValueType_Dagger:          // 匕首
	case EM_SkillValueType_Wand:            // 權杖
	case EM_SkillValueType_Axe:             // 斧
	case EM_SkillValueType_Bludgeon:        // 鎚棍棒
	case EM_SkillValueType_Claymore:        // 雙手劍
	case EM_SkillValueType_Staff:           // 杖
	case EM_SkillValueType_2H_Axe:          // 雙手斧
	case EM_SkillValueType_2H_Hammer:       // 雙手鎚
	case EM_SkillValueType_Polearm:			// 槍(長矛)
	case EM_SkillValueType_Bow:				// 遠程武器 弓
	case EM_SkillValueType_CossBow:			// 遠程武器 十字弓
	case EM_SkillValueType_Gun:				// 遠程武器 槍
	case EM_SkillValueType_Define:			// 防禦
		{
			if( SkillValue <= _MAX_SKILL_LEVE_ && RoleDataEx::SkillExpTable.size() > unsigned( SkillValue ) )
			{
				float SkillBaseExp = 1.0f / float( RoleDataEx::SkillExpTable [ int( SkillValue ) ] );

				SkillValue += SkillBaseExp;
				if( SkillValue  > _MAX_SKILL_LEVE_ )
					SkillValue = _MAX_SKILL_LEVE_;

				Net_FixRoleValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+Type) , SkillValue );
			}
		}
		break;
	case EM_SkillValueType_BlackSmith:		// 打鐵
	case EM_SkillValueType_Carpenter:		// 木工
	case EM_SkillValueType_MakeArmor:		// 製甲
	case EM_SkillValueType_Tailor:			// 裁縫
	case EM_SkillValueType_Cook:			// 烹飪
	case EM_SkillValueType_Alchemy:			// 煉金
		{
			if( SkillValue <= _MAX_SKILL_LEVE_ && RoleDataEx::RefineExpTable.size() > unsigned( SkillValue ) )
			{
				float SkillBaseExp = 1.0f / float( RoleDataEx::RefineExpTable [ int( SkillValue ) ] );

				SkillValue += SkillBaseExp;
				if( SkillValue  > _MAX_SKILL_LEVE_ )
					SkillValue = _MAX_SKILL_LEVE_;

				Net_FixRoleValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+Type) , SkillValue );
			}
		}
		break;
	case EM_SkillValueType_Mining:			// 挖礦
	case EM_SkillValueType_Lumbering:		// 砍材
	case EM_SkillValueType_Herblism:		// 採藥
	case EM_SkillValueType_Fishing:			// 釣魚
		{
			if( SkillValue <= _MAX_SKILL_LEVE_ && RoleDataEx::GatherExpTable.size() > unsigned( SkillValue ) )
			{
				float SkillBaseExp = 1.0f / float( RoleDataEx::GatherExpTable [ int( SkillValue ) ] );

				SkillValue += SkillBaseExp;
				if( SkillValue  > _MAX_SKILL_LEVE_ )
					SkillValue = _MAX_SKILL_LEVE_;

				Net_FixRoleValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+Type) , SkillValue );
			}
		}		
		break;
	case EM_SkillValueType_Plant:				// 種植
		{
			if( SkillValue <= _MAX_SKILL_LEVE_ )
			{
				float SkillBaseExp = 1.0f / float( RoleDataEx::PlantExpTable [ int( SkillValue ) ] );

				SkillValue += SkillBaseExp;
				if( SkillValue  > _MAX_SKILL_LEVE_ )
					SkillValue = _MAX_SKILL_LEVE_;

				Net_FixRoleValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+Type) , SkillValue );
			}
		}		
		break;
	case EM_SkillValueType_CatchPet:			// 補捉寵物
		break;

	}
}

void	RoleDataEx::AddPlotTP( int TpExp )
{
	TpExp = int( TpExp + TpExp * TempData.Attr.Mid.Body[ EM_WearEqType_AddPlotTPRate ] / 100 );
	//////////////////////////////////////////////////////////
	//TP負債處理
	//////////////////////////////////////////////////////////
	{
		int HelfTP = int( TpExp*0.7f );
		if( HelfTP > 0 && TempData.Attr.Ability->DebtTP < 0 )
		{
			if( HelfTP > TempData.Attr.Ability->DebtTP*-1 )
				HelfTP = TempData.Attr.Ability->DebtTP*-1;

			AddValue( EM_RoleValue_DebtTP , (float)HelfTP );
			Net_DeltaRoleValue( EM_RoleValue_DebtTP , (float)HelfTP );
			TpExp -= HelfTP;
		}

	}

	AddValue( EM_RoleValue_TpExp , TpExp );
	Net_DeltaRoleValue( EM_RoleValue_TpExp , (float)TpExp );
}


void	RoleDataEx::AddTP		( int iTP )
{
	if( iTP > 0 )
	{
		iTP = int( iTP * RoleDataEx::GlobalSetting.TpRate );
	}

	if( iTP == 0 )
		return;

	AddValue( EM_RoleValue_TpExp , iTP );
	Net_DeltaRoleValue( EM_RoleValue_TpExp , (float)iTP );
}

//增減 Exp
void    RoleDataEx::Addexp( int Exp )
{
	if( Exp > 0 )
	{
		Exp = int( Exp * RoleDataEx::GlobalSetting.ExpRate );
	}

	if( Exp == 0 )
		return ;
	/*
	//////////////////////////////////////////////////////////
	//經驗值負債處理
	//////////////////////////////////////////////////////////
	int HelfExp = Exp/2;
	if( HelfExp > 0 && TempData.Attr.Ability.DebtExp != 0 )
	{
	if( HelfExp > TempData.Attr.Ability.DebtExp )
	HelfExp = TempData.Attr.Ability.DebtExp;

	AddValue( EM_RoleValue_DebtExp , (float)HelfExp );
	Net_DeltaRoleValue( EM_RoleValue_DebtExp , (float)HelfExp );
	Exp -= HelfExp;
	}
	*/

	//////////////////////////////////////////////////////////

	if(	PlayerBaseData->MaxLv <= TempData.Attr.Ability->Level )
		return;

	int		OldExp = TempData.Attr.Ability->EXP;

	Net_DeltaRoleValue( EM_RoleValue_EXP , (float)Exp );

	TempData.UpdateInfo.ExpChange = true;
	PlayerTempData->Log.Exp += Exp;

	TempData.Attr.Ability->EXP += Exp ;
	if( TempData.Attr.Ability->EXP < 0 )
		TempData.Attr.Ability->EXP = 0;

	while( 1 )
	{
		if(	PlayerBaseData->MaxLv <= TempData.Attr.Ability->Level )
			break;

		int DExp = TempData.Attr.Ability->EXP - GetLVExp( BaseData.Voc );
		//檢查是否升級
		if( DExp < 0 )
			break;
		
		//增加TP			
		AddValue( EM_RoleValue_TpExp , 1000 + TempData.Attr.Ability->Level * 100 );
		Net_DeltaRoleValue( EM_RoleValue_TpExp , float( 1000 + TempData.Attr.Ability->Level * 100 ) );

		AddValue( EM_RoleValue_LV           , 1 );

		//通知週圍升級
		Net_NotifyLvUp();

		TempData.Attr.ReSetTable();
		Calculate();

		BaseData.HP = TempData.Attr.Fin.MaxHP;
		BaseData.MP = TempData.Attr.Fin.MaxMP;
		BaseData.SP = 0;
		BaseData.SP_Sub = 0;
		PlayerBaseData->PKScore += TempData.Attr.Ability->Level *  100;

		Net_MaxHPMaxMPMaxSP();
		Net_HPMPSP();

		TempData.Attr.Ability->EXP	= DExp;
		TempData.UpdateInfo.Recalculate_All = true;
	}

	Net_FixRoleValue( EM_RoleValue_EXP , (float)TempData.Attr.Ability->EXP );

	Log_AddExp( OldExp );
}

float   RoleDataEx::GetValue( MagicAttackCalENUM Type )
{
	switch( Type )
	{
	case EM_MagicAttackCal_None:    
		return 1;
		break;
	case EM_MagicAttackCal_MPow:    
		return TempData.Attr.Fin.MPow;
		break;
	case EM_MagicAttackCal_Weapon:  
		return TempData.Attr.Fin.Main_DMG;
		break;
	case EM_MagicAttackCal_Shoot:
		return TempData.Attr.Fin.Bow_DMG;
		break;
	case EM_MagicAttackCal_Throw:   
		return TempData.Attr.Fin.Throw_DMG;
		break;
	case EM_MagicAttackCal_INT:     
		return TempData.Attr.Fin.INT;
		break;
	case EM_MagicAttackCal_STR:     
		return TempData.Attr.Fin.STR;
		break;
	case EM_MagicAttackCal_AGI:     
		return TempData.Attr.Fin.AGI;
		break;
	case EM_MagicAttackCal_STA:
		return TempData.Attr.Fin.STA;
		break;
	case EM_MagicAttackCal_MND:
		return TempData.Attr.Fin.MND;
		break;
	case EM_MagicAttackCal_LastSkillDmg:
		return float( TempData.BackInfo.LastSkillHitPoint );
		break;
	case EM_MagicAttackCal_LastPhyDmg:
		return float( TempData.BackInfo.LastPhyHitPoint );
		break;

	case EM_MagicAttackCal_ShieldDef:
		{
			return TempData.Attr.BaseEQ.Def[ EM_Armor_Shield ];
			//return TempData.Attr.Mid.ShieldDef;
		}
		break;

	}
	return 1;
}


int    RoleDataEx::CliAddBuf(  int MagicOwnerID , int MagicID , int MagicLv , bool IsPK , int EffectTime  )
{
	GameObjDbStructEx*  OrgDB = St_GetObjDB( MagicID );
	if( OrgDB == NULL )
		return -1;

	int MaxSkillLv = int( OrgDB->MagicBase.MaxBuffLv_Base + OrgDB->MagicBase.MaxBuffLv_SkillLVArg * MagicLv / 100 );
	if( MaxSkillLv < MagicLv )
		MaxSkillLv = MagicLv;

	int BuffPower = 0;

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		BuffBaseStruct&  Buf = BaseData.Buff[ i ];

		GameObjDbStructEx*  MagBuf = St_GetObjDB( Buf.BuffID );

		if( MagBuf->MagicBase.Setting.SelfBuff && MagicOwnerID != Buf.OwnerID )
			continue;

		if( MagBuf->GUID == OrgDB->GUID )
		{
			if( OrgDB->MagicBase.EffectAddonType == 1  )
				return -1;

			BuffPower = Buf.Power + 1;
			ClearBuffByPos( i );				
			break;
		}
		else if(     MagBuf->MagicBase.AssistType != EM_Magic_Type_NULL 
			&&  MagBuf->MagicBase.AssistType == OrgDB->MagicBase.AssistType )
		{
			if(		OrgDB->MagicBase.EffectAddonType == 1  
				&&	MagBuf->MagicBase.EffectLV == OrgDB->MagicBase.EffectLV )
				return -1;

			if( MagBuf->MagicBase.EffectLV > OrgDB->MagicBase.EffectLV )
				return -1;


			ClearBuffByPos( i );

			break;
		}
	}

	//2 buff是否滿了
	if( BaseData.Buff.Size() >= BaseData.Buff.MaxSize() )
	{
		BuffBaseStruct&  Buf = BaseData.Buff[ 0 ];
		GameObjDbStructEx*  MagBuf = St_GetObjDB( Buf.BuffID );

		ClearBuffByPos( 0 );
	}


	BuffBaseStruct  Buf;
	Buf.BuffID      = OrgDB->GUID;
	Buf.Power		= MagicLv + BuffPower;
	Buf.OwnerID     = MagicOwnerID;
	Buf.Time		= EffectTime;
	Buf.IsPK		= IsPK;

	if( Buf.Power >= MaxSkillLv )
		Buf.Power = MaxSkillLv;

	//如果為 魔法盾
	Buf.Point = int( OrgDB->MagicBase.MagicShield.Point * ( 1 + Buf.Power * OrgDB->MagicBase.MagicShield.SkillLvArg / 100 ) );

	if( OrgDB->MagicBase.MagicShield.Type == EM_MagicShieldType_Point_ByHealArg )
	{
		Buf.Point = ( TempData.Attr.Fin.MDMG * FixArg().Dmg_HealArg + 80 ) * Buf.Point / 100 ;
	}

	Buf.Magic = OrgDB;
	if( Buf.Time != 0 )
	{
		BaseData.Buff.Push_Back( Buf );
	}
	TempData.UpdateInfo.Recalculate_Buff = true;

	CalTempHate( this , OrgDB->MagicBase.TempHateCost );

	return Buf.Time;
}


//加輔助法術
BuffBaseStruct*    RoleDataEx::AssistMagic( RoleDataEx* Target , int MagicID , int MagicLv , bool IsPK , int EffectTime )
{
	GameObjDbStructEx*  OrgDB = St_GetObjDB( MagicID );

	if( OrgDB == NULL )
		return NULL;
	return AssistMagic( Target , OrgDB , MagicLv  , IsPK , EffectTime );
}

BuffBaseStruct*    RoleDataEx::AssistMagic( RoleDataEx* Target , GameObjDbStructEx* OrgDB , int MagicLv , bool IsPK , int EffectTime )
{
	if( OrgDB->IsMagicBase() == false || OrgDB->MagicBase.MagicFunc != EM_MAGICFUN_Assist )
		return NULL;

	BuffBaseStruct* Ret = NULL;
	//buff最高等級
	int MaxSkillLv = int( OrgDB->MagicBase.MaxBuffLv_Base + OrgDB->MagicBase.MaxBuffLv_SkillLVArg * MagicLv / 100 );
	if( MaxSkillLv < MagicLv )
		MaxSkillLv = MagicLv;

	if( OrgDB->MagicBase.Setting.MaxMagicLvEquRoleLv != false )
		MaxSkillLv = Target->Level();

	if( MaxSkillLv > OrgDB->MagicBase.BuffMaxLv )
		MaxSkillLv = OrgDB->MagicBase.BuffMaxLv;

	int BuffPower = 0;

	int DLV = Level() - Target->Level();

	//清除法術
	if( EffectTime == -1 )
	{
		EffectTime = int( OrgDB->MagicBase.EffectTime );

		if( EffectTime >= 0 )
		{
			EffectTime = int( OrgDB->MagicBase.EffectTime * ( 1 + OrgDB->MagicBase.EffectTime_SkillLVArg * MagicLv / 100 ) 
			- DLV * OrgDB->MagicBase.DLV_EffectTime  );
		}
		else
			EffectTime = 100000000;
	}

	//////////////////////////////////////////////////////////////////////////
	/*
	//計算時差
	//RoleDataEx::G_Clock % _DEF_BASE_CLOCL_UNIT_
	{
		int DTime = ( RoleDataEx::G_Clock - ( GUID() & 0xffff ) + 0x10000 ) % _DEF_BASE_CLOCL_UNIT_;
		if( DTime > 5 )
			EffectTime ++;
	}
	*/
	//////////////////////////////////////////////////////////////////////////

	if( EffectTime < 0 )
		EffectTime = 0;

	if( OrgDB->MagicBase.ClearTime.Random )
		EffectTime = ( EffectTime + rand()%( EffectTime * 2) )/3;


	NPCHateStruct* HateInfo;
	if( Target->BaseData.Buff.Size() > Target->BaseData.Buff.MaxSize() )
	{
		Target->BaseData.Buff.Clear();
	}

	int     i;
	//1 簡查是否有互斥的法術
	//  相同ID
	for( i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
	{
		BuffBaseStruct&  Buf = Target->BaseData.Buff[ i ];

		GameObjDbStructEx*  MagBuf = St_GetObjDB( Buf.BuffID );
		if( MagBuf == NULL )
			continue;
		//GameObjDbStructEx*  MagBuf = (GameObjDbStructEx*)Buf.Magic;
	
		if(	( MagBuf->MagicBase.MagicGroupSet & OrgDB->MagicBase.ClearMagicGroupSet ) != 0 )
			Buf.Time = 0;

		if( MagBuf->MagicBase.Setting.SelfBuff && GUID() != Buf.OwnerID )
			continue;


		if( MagBuf->GUID == OrgDB->GUID )
		{
			if( OrgDB->MagicBase.EffectAddonType == 1  )
				return NULL;
			//如果Client不用顯示Buf 的時間
			if(		OrgDB->MagicBase.Setting.ShowBuffTime == false 
				&&	MagicLv == Buf.Power 
				&&  OrgDB->MagicBase.Setting.ShowPowerLv == false )
			{
				Buf.Time = EffectTime;
				Buf.IsPK = IsPK;

				if( OrgDB->MagicBase.ClearTime.Random != false )
					Buf.Time = ( Buf.Time + rand()%( Buf.Time * 2) )/3;

				return &Buf;

			}

			BuffPower = Buf.Power+1;
			Target->ClearBuffByPos( i );
			//如果 Buf 有暫時的仇恨值
			if( MagBuf->MagicBase.TempHateCost != 0 )
			{
				HateInfo = Target->GetHatePos( GUID() );
				if( HateInfo != NULL )
				{
					if( MagBuf->MagicBase.TempHateCost == -1 )
					{
						HateInfo->TempHatePoint = 0;
					}
					else
					{
						HateInfo->TempHatePoint -= MagBuf->MagicBase.TempHateCost;
						if( HateInfo->TempHatePoint <=0 )
							HateInfo->TempHatePoint = 0;
					}
					TempData.NPCHate.MaxHitPoint = HateInfo->TotalHatePoint();
				}
			}			
			break;

		}
		else if(     MagBuf->MagicBase.AssistType != EM_Magic_Type_NULL 
			&&  MagBuf->MagicBase.AssistType == OrgDB->MagicBase.AssistType )
		{
			if(		OrgDB->MagicBase.EffectAddonType == 1  
				&&	MagBuf->MagicBase.EffectLV == OrgDB->MagicBase.EffectLV )
				return NULL;

			if( MagBuf->MagicBase.EffectLV > OrgDB->MagicBase.EffectLV )
				return NULL;


			Target->ClearBuffByPos( i );
			//如果 Buf 有暫時的仇恨值
			if( MagBuf->MagicBase.TempHateCost != 0 )
			{
				HateInfo = Target->GetHatePos( GUID() );
				if( HateInfo != NULL )
				{
					if( MagBuf->MagicBase.TempHateCost == -1 )
					{
						HateInfo->TempHatePoint = 0;
					}
					else
					{
						HateInfo->TempHatePoint -= MagBuf->MagicBase.TempHateCost;
						if( HateInfo->TempHatePoint <=0 )
							HateInfo->TempHatePoint = 0;
					}
					TempData.NPCHate.MaxHitPoint = HateInfo->TotalHatePoint();
				}
			}

			break;
		}
	}

	//2 buff是否滿了
	if( Target->BaseData.Buff.Size() >= Target->BaseData.Buff.MaxSize() )
	{
		BuffBaseStruct*		Buf;//&(Target->BaseData.Buff[ 0 ]);
		GameObjDbStructEx*  MagBuf;// = St_GetObjDB( Buf.BuffID );

		for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
		{
			Buf = &(Target->BaseData.Buff[ i ]);
			MagBuf = St_GetObjDB( Buf->BuffID );
			
			if( MagBuf->MagicBase.SettingEx.IsDepartmentStore == false )
			{
				Target->ClearBuffByPos( i );
				break;
			}
		}


		//如果 Buf 有暫時的仇恨值
		if( MagBuf->IsMagicBase() && MagBuf->MagicBase.TempHateCost != 0 )
		{
			HateInfo = Target->GetHatePos( GUID() );
			if( HateInfo != NULL )
			{
				if( MagBuf->MagicBase.TempHateCost == -1 )
				{
					HateInfo->TempHatePoint = 0;
				}
				else
				{
					HateInfo->TempHatePoint -= MagBuf->MagicBase.TempHateCost;
					if( HateInfo->TempHatePoint <=0 )
						HateInfo->TempHatePoint = 0;
				}
				TempData.NPCHate.MaxHitPoint = HateInfo->TotalHatePoint();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	int BuffTimeDesc_Type = OrgDB->MagicBase.BuffTimeDesc_Type -1;
	float TimeRate = 1;
	if( unsigned(BuffTimeDesc_Type) < _MAX_BuffTimeDesc_COUNT_ )
	{
		float TimeRateList[4] = { 1 , 1, 0.5f , 0.25f };
	
		if( Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Time < (int)RoleDataEx::G_SysTime )
			Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Count = 1;
		else
		{
			if( Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Count >= 3 )
			{//受到多次攻擊產生免疫，法術失效
				Net_GameMsgEvent( EM_GameMessageEvent_BuffTimeDesc_Time0 );
				return NULL;
			}
			Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Count++;
		}
		TimeRate = TimeRateList[ Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Count ];		
		Target->TempData.BuffTimeDesc[BuffTimeDesc_Type].Time = RoleDataEx::G_SysTime + OrgDB->MagicBase.BuffTimeDesc_Time * 1000 + int( EffectTime * TimeRate * 1000) ;
	}
	//////////////////////////////////////////////////////////////////////////

	//3 設定Buff資料
	BuffBaseStruct  Buf;
	Buf.BuffID      = OrgDB->GUID;
	if( BuffPower < 0 )
		BuffPower = 0;
	Buf.Power		= BuffPower + MagicLv ;
	if( Buf.Power >= MaxSkillLv )
		Buf.Power = MaxSkillLv;

	Buf.OwnerID     = GUID();
	Buf.Time		= int( EffectTime * TimeRate );
	Buf.IsPK		= IsPK;

	if( Buf.Time == 0 && EffectTime != 0 )
	{//受到多次攻擊產生免疫，招式失效
		Net_GameMsgEvent( EM_GameMessageEvent_BuffTimeDesc_Time0 );
		return NULL;
	}
	Target->TempData.Attr.Effect._Value[0] |= OrgDB->MagicBase.Effect._Value[0];
	Target->TempData.Attr.Effect._Value[1] |= OrgDB->MagicBase.Effect._Value[1];

	//如果為 魔法盾
	Buf.Point = int( OrgDB->MagicBase.MagicShield.Point * ( 1 + Buf.Power * OrgDB->MagicBase.MagicShield.SkillLvArg / 100 ) );
	
	if( OrgDB->MagicBase.MagicShield.Type == EM_MagicShieldType_Point_ByHealArg )
	{
		Buf.Point = ( TempData.Attr.Fin.MDMG * FixArg().Dmg_HealArg + 80 ) * Buf.Point / 100 ;
	}

	Buf.Magic = OrgDB;
	if( Buf.Time == 0 )
		return NULL;

	Target->BaseData.Buff.Push_Back( Buf );

	Target->TempData.UpdateInfo.Recalculate_Buff = true;

	Target->CalTempHate( this , OrgDB->MagicBase.TempHateCost );


	if(		OrgDB->MagicBase.Effect.LockTarget != false 
		&&  Target->BaseData.Mode.DisableRotate == false )
	{
		if(  Target->IsAttack() == false && Target->CheckStrikback() )
		{
			Target->AttackTarget( GUID() );
		}
		else
		{
			Target->TargetID( GUID() );
		}
	}

	if( OrgDB->MagicBase.Effect.PlayDead != false )
	{
		Target->TempData.BackInfo.BuffClearTime.Attack = false;
		Target->TempData.Attr.Effect.PlayDead = true;
		Target->StopAttack();
	}

	return &(Target->BaseData.Buff.Back());
}

//清除所有Buff
void    RoleDataEx::ClearAllBuff()
{
	/*
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
	Net_ClearAssistMagic( BaseData.Buff[i].BuffID );
	}

	BaseData.Buff.Clear();
	TempData.UpdateInfo.Recalculate = true;
	*/
	for( int i =  BaseData.Buff.Size() -1  ; i >= 0 ; i-- )
	{
		ClearBuffByPos( i );
	}
	return ;
}

void	RoleDataEx::ClearBuffByEvent( MagicClearTimeStruct ClearEvent )
{
	if( ClearEvent._Value == 0 )
		return;

	for( int i =  BaseData.Buff.Size() -1  ; i >= 0 ; i-- )
	{
		BuffBaseStruct&		Buff	= BaseData.Buff[i];
		GameObjDbStructEx*  MagBuf	= St_GetObjDB( Buff.BuffID );
		if( MagBuf->IsMagicBase() == false ||  ( MagBuf->MagicBase.ClearTime._Value & ClearEvent._Value) != 0)
		{
			ClearBuffByPos( i );		
		}
	}

	if( TempData.UpdateInfo.Recalculate_Buff != false )
		OnTimeProc( true );
}

void	RoleDataEx::ClearBuffByEvent(  )
{
	MagicClearTimeStruct& ClearEvent = TempData.BackInfo.BuffClearTime;
	ClearBuffByEvent( TempData.BackInfo.BuffClearTime );
	ClearEvent._Value = 0;
}


//清除Buff
bool    RoleDataEx::ClearBuff( int MagicID , int BuffOwnerID )
{
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		if( MagicID == BaseData.Buff[i].BuffID )
		{
			if( BuffOwnerID != -1 && BaseData.Buff[i].OwnerID != BuffOwnerID )
				continue;
			//Net_ClearAssistMagic( BaseData.Buff[i].BuffID );
			//BaseData.Buff.Erase( i );
			ClearBuffByPos( i );
			//TempData.UpdateInfo.Recalculate = true;
			return true;
		}
	}
	return false;
}

bool    RoleDataEx::ClearBuff_NoEvent( int MagicID , int BuffOwnerID )
{
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		if( MagicID == BaseData.Buff[i].BuffID )
		{
			if( BuffOwnerID != -1 && BaseData.Buff[i].OwnerID != BuffOwnerID )
				continue;
			Net_ClearAssistMagic( BaseData.Buff[i].BuffID , BaseData.Buff[i].OwnerID );
			BaseData.Buff.Erase( i );
			TempData.UpdateInfo.Recalculate_Buff = true;
			return true;
		}
	}
	return false;
}


bool    RoleDataEx::ClearBuffByPos( int Pos )
{
	if( BaseData.Buff.Size() <= Pos )
		return false;

	BuffBaseStruct& Buff = BaseData.Buff[Pos];
	GameObjDbStructEx*  MagBuf	= St_GetObjDB( Buff.BuffID );
	if( MagBuf->IsMagicBase() )
	{
		if( MagBuf->MagicBase.Setting.SpecialMagic  )
		{
			if( MagBuf->MagicBase.OnBuffTimeOutMagicID ) 
			{
				MagicProcInfo  MagicInfo;
				MagicInfo.Init();
				MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
				MagicInfo.TargetID			= GUID();							//目標
				MagicInfo.MagicCollectID	= MagBuf->MagicBase.OnBuffTimeOutMagicID;		//法術
				St_SpellMagic( this ,  &MagicInfo , 0 );
			}
			if(		MagBuf->MagicBase.OnBuffTimeOutMagicIDEx 
				&&	Buff.IsErase == false  
				&&	Buff.Time == 0 ) 
			{
				MagicProcInfo  MagicInfo;
				MagicInfo.Init();
				MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
				MagicInfo.TargetID			= GUID();							//目標
				MagicInfo.MagicCollectID	= MagBuf->MagicBase.OnBuffTimeOutMagicIDEx;		//法術
				St_SpellMagic( this ,  &MagicInfo , 0 );
			}
		}

		if( MagBuf->MagicBase.TempHateCost != 0 )
		{
			NPCHateStruct* HateInfo = GetHatePos( BaseData.Buff[Pos].OwnerID );
			if( HateInfo != NULL )
			{
				if( MagBuf->MagicBase.TempHateCost == -1 )
				{
					HateInfo->TempHatePoint = 0;
				}
				else
				{
					HateInfo->TempHatePoint -= MagBuf->MagicBase.TempHateCost;
					if( HateInfo->TempHatePoint <=0 )
						HateInfo->TempHatePoint = 0;
				}
				TempData.NPCHate.MaxHitPoint = HateInfo->TotalHatePoint();
			}
		}
	}

	Net_ClearAssistMagic( BaseData.Buff[Pos].BuffID , BaseData.Buff[Pos].OwnerID );
	BaseData.Buff.Erase( Pos );

	TempData.UpdateInfo.Recalculate_Buff = true;
	return true;
}

void	RoleDataEx::SpecialAttackBuffProc_SelfSpell( RoleDataEx* Target )
{
	if(	TempData.Attr.AssistMagicSetting.SpecialMagic == false )
		return;

	MagicProcInfo  MagicInfo;
	MagicInfo.Init();

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{        		
		int MagicID = BaseData.Buff[i].Magic->MagicBase.OnSpecialMagicID;
		if(		BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;


		if( BaseData.Buff[i].Magic->MagicBase.SpecialMagicEventType != EM_SpecailMagicEventType_SelfSpell )
			continue;
		
		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
		MagicInfo.IsNoRebound		= true;
		St_SpellMagic( Target ,  &MagicInfo , 10 );		
	}
}

void	RoleDataEx::SpecialAttackBuffProc( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM  DmgType , int addHP , int magicColID , int magicBaseID )
{
	LastAttackInfo.Type = Type;
	LastAttackInfo.OwnerID = GUID();
	LastAttackInfo.TargetID = Target->GUID();
	LastAttackInfo.MagColID	= magicColID;
	LastAttackInfo.MagBaseID = magicBaseID;
	LastAttackInfo.Damage = addHP;	
	LastAttackInfo.DmgType = DmgType;


	if(		Target->TempData.Attr.AssistMagicSetting.SpecialMagic == false 
		&&	TempData.Attr.AssistMagicSetting.SpecialMagic == false )
		return;

	if( Target->TempData.Attr.AssistMagicSetting.SpecialMagic )
	{
		if(		EM_ATTACK_DMGTYPE_NORMAL == DmgType 
			&&	addHP < 0 )
		{
			if( Type == EM_OnAttackType_Magic )
				OnMagicAttackBuffProc( Target );
			else
				OnAttackBuffProc( Target );	
			return;
		}

		if( RoleDataEx::IsDisableMagicRebound == true )
			return;


		MagicProcInfo  MagicInfo;
		MagicInfo.Init();

		for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
		{        		
			int MagicID = Target->BaseData.Buff[i].Magic->MagicBase.OnSpecialMagicID;
			if(		Target->BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
				||	MagicID == 0 )
				continue;

			switch( Target->BaseData.Buff[i].Magic->MagicBase.SpecialMagicEventType )
			{
			case EM_SpecailMagicEventType_TargetCritial:		//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_MainHand && Type != EM_OnAttackType_OffHand)
					continue;
				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;
			case EM_SpecailMagicEventType_Phy_TargetCritial:		//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_Skill )
					continue;
				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;
			case EM_SpecailMagicEventType_Mag_TargetCritial:		//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_Magic )
					continue;
				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;
			case EM_SpecailMagicEventType_SelfDodge:				//目標 閃避
				if( DmgType != EM_ATTACK_DMGTYPE_DODGE )
					continue;
				break;
			case EM_SpecailMagicEventType_TargetMiss:				//目標 Miss
				if( DmgType != EM_ATTACK_DMGTYPE_MISS )
					continue;
				break;
			case EM_SpecailMagicEventType_Cure_Self:
				if( addHP <= 0 )
					continue;
				break;
			case EM_SpecailMagicEventType_SelfParry:				//目標 閃避
				if( DmgType != EM_ATTACK_DMGTYPE_HALF )
					continue;
				break;
			default:
				continue;
				/*
			case EM_SpecailMagicEventType_SelfCritial:			//目標 攻擊致命一擊
			case EM_SpecailMagicEventType_Phy_SelfCritial:			//目標 攻擊致命一擊
			case EM_SpecailMagicEventType_Mag_SelfCritial:			//目標 攻擊致命一擊
			case EM_SpecailMagicEventType_TargetDodge:				//自己 閃避
			case EM_SpecailMagicEventType_SelfMiss:					//自己 Miss		
				continue;
				*/
			}

			MagicProcInfo  MagicInfo;
			MagicInfo.Init();
			MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
			MagicInfo.TargetID			= GUID();			//目標
			MagicInfo.MagicCollectID	= MagicID;				//法術
			MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
			MagicInfo.IsNoRebound		= true;
			St_SpellMagic( Target ,  &MagicInfo , 10 );		
		}
	}
	
	if( TempData.Attr.AssistMagicSetting.SpecialMagic )
	{
		for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
		{        		
			int MagicID = BaseData.Buff[i].Magic->MagicBase.OnSpecialMagicID;
			if(		BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
				||	MagicID == 0 )
				continue;

			switch( BaseData.Buff[i].Magic->MagicBase.SpecialMagicEventType )
			{
			case EM_SpecailMagicEventType_SelfCritial:			//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_MainHand && Type != EM_OnAttackType_OffHand)
					continue;
				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;
			case EM_SpecailMagicEventType_Phy_SelfCritial:		//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_Skill )
					continue;
				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;
			case EM_SpecailMagicEventType_Mag_SelfCritial:		//自己 攻擊致命一擊
				if( Type != EM_OnAttackType_Magic )
					continue;

				if( DmgType != EM_ATTACK_DMGTYPE_DOUBLE )
					continue;
				break;

			case EM_SpecailMagicEventType_TargetDodge:		//目標 閃避
				if( DmgType != EM_ATTACK_DMGTYPE_DODGE )
					continue;
				break;
			case EM_SpecailMagicEventType_SelfMiss:			//自己 Miss
				if( DmgType != EM_ATTACK_DMGTYPE_MISS )
					continue;
				break;
			case EM_SpecailMagicEventType_Cure_Target:
				if( addHP <= 0 )
					continue;
				break;
			case EM_SpecailMagicEventType_TargetParry:		//目標 閃避
				if( DmgType != EM_ATTACK_DMGTYPE_HALF )
					continue;
				break;

			default:
				continue;
				/*
			case EM_SpecailMagicEventType_TargetCritial:	//目標 攻擊致命一擊
			case EM_SpecailMagicEventType_SelfDodge:		//自己 閃避
			case EM_SpecailMagicEventType_TargetMiss:		//目標 Miss	
			case EM_SpecailMagicEventType_SelfParry:
				continue;
				*/
				
			}

			MagicProcInfo  MagicInfo;
			MagicInfo.Init();
			MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
			MagicInfo.TargetID			= Target->GUID();			//目標
			MagicInfo.MagicCollectID	= MagicID;				//法術
			MagicInfo.MagicLv			= BaseData.Buff[i].Power;
			St_SpellMagic( this ,  &MagicInfo , 10 );		
		}
	}

}

//當打別人時 Buff 處理
void	RoleDataEx::OnAttackBuffProc( RoleDataEx* Target )
{
	if( Target->TempData.Attr.AssistMagicSetting.SpecialMagic == false )
		return;

	MagicProcInfo  MagicInfo;
	MagicInfo.Init();

	if( RoleDataEx::IsDisableMagicRebound == true )
		return;

	for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
	{        
		int MagicID = Target->BaseData.Buff[i].Magic->MagicBase.OnAttackReboundMagicID;
		if(		Target->BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;

		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
		MagicInfo.IsNoRebound		= true;
		St_SpellMagic( Target ,  &MagicInfo , 10 );		
	}



	for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
	{        
		int MagicID = Target->BaseData.Buff[i].Magic->MagicBase.OnAttackMagicID;
		if(		Target->BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;

		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
		MagicInfo.IsNoRebound		= true;
		St_SpellMagic( Target ,  &MagicInfo , 10 );		
	}




}
//當打別人時 Buff 處理
void	RoleDataEx::OnMagicAttackBuffProc( RoleDataEx* Target )
{
	if( Target->TempData.Attr.AssistMagicSetting.SpecialMagic == false )
		return;

	if( RoleDataEx::IsDisableMagicRebound == true )
		return;

	MagicProcInfo  MagicInfo;
	MagicInfo.Init();

	for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
	{        
		int MagicID = Target->BaseData.Buff[i].Magic->MagicBase.OnMagicAttackReboundMagicID;
		if(		Target->BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;


		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
		MagicInfo.IsNoRebound		= true;
		St_SpellMagic( Target ,  &MagicInfo , 10 );		
	}

	for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
	{        
		int MagicID = Target->BaseData.Buff[i].Magic->MagicBase.OnAttackMagicID;
		if(		Target->BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;

		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= Target->BaseData.Buff[i].Power;
		MagicInfo.IsNoRebound		= true;
		St_SpellMagic( Target ,  &MagicInfo , 10 );		
	}


}


//當死亡時Buff的處理
void	RoleDataEx::OnDeadBuffProc( RoleDataEx* Killer )
{
	if( TempData.Attr.AssistMagicSetting.SpecialMagic == false )
		return;


	MagicProcInfo  MagicInfo;
	MagicInfo.Init();

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{        
		int MagicID =BaseData.Buff[i].Magic->MagicBase.OnDeadMagicID;
		if(		BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;

		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= Killer->GUID();			//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= BaseData.Buff[i].Power;
		St_SpellMagic( this ,  &MagicInfo , 10 );		
	}

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{        
		int MagicID =BaseData.Buff[i].Magic->MagicBase.OnKillMagicID;
		if(		BaseData.Buff[i].Magic->MagicBase.Setting.SpecialMagic == false
			||	MagicID == 0 )
			continue;

		MagicProcInfo  MagicInfo;
		MagicInfo.Init();
		MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
		MagicInfo.TargetID			= GUID();				//目標
		MagicInfo.MagicCollectID	= MagicID;				//法術
		MagicInfo.MagicLv			= BaseData.Buff[i].Power;
		St_SpellMagic( Killer ,  &MagicInfo , 10 );		
	}
}



//處理Buf的時效
void    RoleDataEx::BuffProc( )
{

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{        
		BaseData.Buff[i].Time --;
#ifdef _LOCAL_SERVER_

		//如果死亡則不處理
		if( IsDead() || IsMirror() )
			break;

		if( BaseData.Buff[i].Magic == NULL )
		{
			BaseData.Buff.Clear();
			break;
		}

		if(		!BaseData.Buff[i].Magic->MagicBase.DotMagic.IsEmpty() 
			&&  BaseData.Buff[i].Time % BaseData.Buff[i].Magic->MagicBase.DotMagic.Time == 0 )
		{         
			RoleDataEx* Target = St_GetRoleData( BaseData.Buff[i].OwnerID );
			int BuffOwnerID = BaseData.Buff[i].OwnerID;
			if( Target == NULL )//|| Target->IsDead() || IsAttackMode() == false )
			{
				//BaseData.Buff[i].OwnerID = GUID();
				BuffOwnerID = GUID();
				Target = this;
			}
			DotMagicStruct&	DotMagic = BaseData.Buff[i].Magic->MagicBase.DotMagic;
			int Damage = int( DotMagic.Base * -1.0  * ( 100 + DotMagic.DotSkillLVArg * BaseData.Buff[i].Power )/ 100 );
			DotMagicTypeENUM DotType = BaseData.Buff[i].Magic->MagicBase.DotMagic.Type;

			//if( Target != NULL && Target->IsPlayer() && IsPlayer() && Damage > 0 )
			if( Damage > 0)
			{
				RoleDataEx::IsDisableMagicRebound = true;
				if( BaseData.Buff[i].Magic->MagicBase.EffectType == EM_Magic_Magic )
					SpecialAttackBuffProc( this , EM_OnAttackType_Magic , EM_ATTACK_DMGTYPE_NORMAL , Damage*-1 , 0 , BaseData.Buff[i].BuffID );
				else
					SpecialAttackBuffProc( this , EM_OnAttackType_Skill , EM_ATTACK_DMGTYPE_NORMAL , Damage*-1 , 0 , BaseData.Buff[i].BuffID );
				RoleDataEx::IsDisableMagicRebound = false;
	
			}
			if( BaseData.Buff[i].IsPK && Damage > 0 )
			{
				Damage = int( Damage*RoleDataEx::GlobalSetting.PK_DotRate);

				if( BaseData.Buff[i].Magic->MagicBase.Setting.GoodMagic != false )
				{
					switch( BaseData.Buff[i].Magic->MagicBase.EffectType )
					{
					case EM_Magic_Magic:
						if( TempData.Attr.Effect.GoodMagicInvincible != false )
							continue;
						break;
					case EM_Magic_Phy:
						if( TempData.Attr.Effect.GoodPhyInvincible != false )
							continue;
						break;
					}
				}
				else
				{
					switch( BaseData.Buff[i].Magic->MagicBase.EffectType )
					{
					case EM_Magic_Magic:
						if( TempData.Attr.Effect.BadMagicInvincible != false )
							continue;
						break;
					case EM_Magic_Phy:
						if( TempData.Attr.Effect.BadPhyInvincible != false )
							continue;
						break;
					}
				}

			}

			switch( DotType )
			{
			case EM_DotMagicType_HP_Per:
				Damage = int( Damage * TempData.Attr.Fin.MaxHP / 100 );
				break;
			case EM_DotMagicType_MP_Per:
				Damage = int( Damage * TempData.Attr.Fin.MaxMP / 100 );
				break;
			}


			if(		DotType == EM_DotMagicType_HP 
				||	DotType == EM_DotMagicType_HP_Per )
				MagicShieldAbsorbProc( Target , BaseData.Buff[i].Magic , Damage );


            switch( BaseData.Buff[i].Magic->MagicBase.DotMagic.Type )
            {
			case EM_DotMagicType_HP:			//HP
			case EM_DotMagicType_HP_Per:		//HP百分比

				if(		BaseData.Buff[i].Magic->MagicBase.Setting.DotMagicNoKill != false
					&&	TempData.Attr.Effect.Insure == false 
					&&	BaseData.HP <= Damage )
				{
					AddHP( Target , BaseData.HP -1 );
					TempData.BackInfo.BuffClearTime.HP0 = true;
				}
				else
				{
					AddHP( Target , float( Damage * -1 ) );
				}
				
				break;
			case EM_DotMagicType_MP:			//MP
				AddMP( Target , float( Damage * -1 ) );
				break;
			case EM_DotMagicType_WarriorSP:		//戰士SP
				if(		BaseData.Voc == EM_Vocation_Warrior 
					||	BaseData.Voc == EM_Vocation_Psyron )
					AddSP(  Target , float( Damage * -1 ) );
				else if(	BaseData.Voc_Sub == EM_Vocation_Warrior 
						||	BaseData.Voc_Sub == EM_Vocation_Psyron	)
					AddSP_Sub(  Target , float( Damage * -1 ) );
				break;
			case EM_DotMagicType_RangerSP:		//遊俠SP
				if(		BaseData.Voc == EM_Vocation_Ranger 
					||	BaseData.Voc == EM_Vocation_Harpsyn )
					AddSP(  Target , float( Damage * -1 ) );
				else if(	BaseData.Voc_Sub == EM_Vocation_Ranger 
						||	BaseData.Voc_Sub == EM_Vocation_Harpsyn )
					AddSP_Sub(  Target , float( Damage * -1 )  );
				break;
			case EM_DotMagicType_RogueSP:		//盜賊SP
				if(		BaseData.Voc == EM_Vocation_Rogue 
					||	BaseData.Voc == EM_Vocation_Duelist)
					AddSP(  Target , float( Damage * -1 ) );
				else if(	BaseData.Voc_Sub == EM_Vocation_Rogue 
						||	BaseData.Voc_Sub == EM_Vocation_Duelist)
					AddSP_Sub(  Target , float( Damage * -1 ) );
				break;
//			case EM_DotMagicType_HP_Per:		//HP百分比
//					AddHP( Target , float( Damage * -1 ) );
				break;
			case EM_DotMagicType_MP_Per:		//MP百分比
					AddMP( Target , float( Damage * -1 ) );
				break;
            }            
        }
		
		vector<int> MagicList;
		vector<int> MagicLvList;
		//MagicList.clear();

		if( BaseData.Buff.Size() <= i || IsDead() )
			break;

		if(     BaseData.Buff[i].Magic->MagicBase.OnTimeMagic_Magic != 0
			&&  BaseData.Buff[i].Magic->MagicBase.OnTimeMagic_Time > 0
			&&  BaseData.Buff[i].Time % BaseData.Buff[i].Magic->MagicBase.OnTimeMagic_Time == 0 )
		{
			MagicList.push_back( BaseData.Buff[i].Magic->MagicBase.OnTimeMagic_Magic );
			MagicLvList.push_back( BaseData.Buff[i].Power );
		}

        if( BaseData.Buff[i].Time <= 0)
        {
			ClearBuffByPos( i );
			i--;
        }
		for( unsigned int i = 0 ; i < MagicList.size() ; i ++ )
		{
			MagicProcInfo  MagicInfo;
			MagicInfo.Init();
			MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
			MagicInfo.TargetID			= GUID();				//目標
			MagicInfo.MagicCollectID	= MagicList[ i ];			//法術		
			MagicInfo.MagicLv			= MagicLvList[ i ];
			St_SpellMagic( this ,  &MagicInfo , 0 );			
		}

#endif
    }

}

//設定武器狀態
void	RoleDataEx::FixWeaponType()
{/*
	GameObjectWeaponENUM& MainWeaponType = TempData.Attr.MainWeaponType;
	GameObjectWeaponENUM& SecWeaponType  = TempData.Attr.SecWeaponType;

	if( MainWeaponType ==  EM_Weapon_Unarmed )
	{
		if( SecWeaponType ==  EM_Weapon_None && BaseData.EQ.SecondHand.IsEmpty() )
		{
			SecWeaponType = EM_Weapon_Unarmed;
		}
	}
	*/
}

//取得對某魔法進行抗性運算結果
float		RoleDataEx::CalResistDMG( MagicResistENUM  MagicType , float Damage )
{
	if( Damage > 0 )
		return Damage;

	switch( MagicType )
	{
	case EM_MagicResist_Earth:   
	case EM_MagicResist_Water:   
	case EM_MagicResist_Fire:    
	case EM_MagicResist_Wind:    
	case EM_MagicResist_Light:   
	case EM_MagicResist_Darkness:
		break;
	default:
		return Damage;
	}
	int ResistValue = int( TempData.Attr.Fin.Resist._ArrList[ MagicType ] );

	float RetDamage;
	
	if( abs( Damage) / 2 <  abs( ResistValue ) )
	{
		if( ResistValue < 0 )
			RetDamage = Damage + Damage / 2;
		else
			RetDamage = Damage - Damage / 2;
	}	
	else
	{
		RetDamage = Damage + ResistValue;
	}

	RetDamage = RetDamage * TempData.Attr.Fin.ResistPer._ArrList[ MagicType ];
	return RetDamage;

/*


	ResistArgType_ENUM	ResistType = TempData.Attr.GetResistType( ResistValue );

	switch( ResistType )
	{
	case EM_ResistArgType_Power0:
		return 0;

	case EM_ResistArgType_Power25:	
		return Damage/4+1;

	case EM_ResistArgType_Power50:	
		return Damage/2+1;

	case EM_ResistArgType_Power75:	
		return Damage*3/4+1;

	case EM_ResistArgType_Power100:	
		return Damage;
	}
*/
	return 0;
}

//重新計算仇恨列表
bool	RoleDataEx::ReCalhateList( )
{
	int MaxHateID;
	TempData.NPCHate.MaxHitPoint = 0;
	for( int i = 0 ; i < TempData.NPCHate.Hate.Size() ; i++ )
	{
		TempData.NPCHate.Hate[i].HatePoint = TempData.NPCHate.Hate[i].HatePoint * 20 / 19;
		int TotalHatePoint = TempData.NPCHate.Hate[i].TotalHatePoint();
		if( TotalHatePoint > TempData.NPCHate.MaxHitPoint  )
		{
			TempData.NPCHate.MaxHitPoint = TotalHatePoint;
			MaxHateID = TempData.NPCHate.Hate[i].ItemID;
		}
	}

	if( MaxHateID != AttackTargetID() && rand()%3 == 0 )
	{
		RoleDataEx* Target = SearchHate();
		if( Target != NULL )
		{
			SetAttack( Target );
		}
	}

	return true;
}

GameObjDbStructEx* RoleDataEx::GetRefinAblility( GameObjDbStructEx* ItemDB , int Level )
{
	if( Level > 20 || Level <= 0 )
		return NULL;

	return St_GetObjDB( ItemDB->Item.RefineTableID + Level -1 );
}

//取得法術等級
int		RoleDataEx::GetMagicLv( int MagicPos )
{
	if( MagicPos < 0 || MagicPos >= _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ )
		return 0;

	if( MagicPos < _MAX_SPSkill_COUNT_ )
		return __min( Level() , int( PlayerBaseData->AbilityList[ BaseData.Voc ].SPSkill[ MagicPos ] ) );

	MagicPos -= _MAX_SPSkill_COUNT_;
	if( MagicPos < _MAX_NormalSkill_COUNT_ )
		return __min( Level() , int( PlayerBaseData->AbilityList[ BaseData.Voc ].NormalSkill[ MagicPos ] ) );

	if( BaseData.Voc_Sub < 0 )
		return 0;

	MagicPos -= _MAX_NormalSkill_COUNT_;
	if( MagicPos < _MAX_NormalSkill_COUNT_ )
		return __min( Level_Sub() , int( PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].NormalSkill[ MagicPos ] ) );

	return 0;
}

//可流通的帳號幣
int RoleDataEx::OkAccountMoney()
{
	int Ret = PlayerBaseData->Body.Money_Account - PlayerTempData->LockAccountMoney;
	if( Ret < 0 )
		return 0;
	return Ret;
}