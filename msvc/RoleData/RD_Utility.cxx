#include <string>
#include "RoleDataEx.h"

using namespace std;

//-----------------------------------------------------------------------------
int RoleDataEx::GetAttachRuneCount(ItemFieldStruct* item)
{
	if ( item == NULL )
		return 0;

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		GameObjDbStruct* itemDB = St_GetObjDB(item->Rune(i));
		if ( itemDB && itemDB->Item.Class == EM_Item_Rune )
			count++;
	}
	return count;
}

//-----------------------------------------------------------------------------
int	RoleDataEx::GetRuneTotalVolume(ItemFieldStruct* item)
{	
	if (item == NULL)
		return 0;
	
	int total = item->RuneVolume;
	for(int i = 0; i < 4; i++)
	{
		GameObjDbStruct* itemDB = St_GetObjDB(item->Rune(i));
		if ( itemDB && itemDB->Item.Class == EM_Item_Rune )
			total += itemDB->Item.Volume;
	}
	return total;
}

//-----------------------------------------------------------------------------
bool RoleDataEx::GetItemFieldName(ItemFieldStruct* item, char* outName, int size)
{
	if ( item && outName )
	{
		GameObjDbStructEx* itemDB = St_GetObjDB(item->OrgObjID);
		if ( itemDB )
		{
			string tmp;

			tmp.clear();
			/*
			if ( item->Inherent != 0 && itemDB->Item.IsNoTitle == false )
			{
				GameObjDbStruct* inherit = St_GetObjDB(item->Inherent);
				if ( inherit && inherit->Classification == EM_ObjectClass_Attribute )
				{
					tmp = inherit->Name;
				}
			}
			*/
			tmp += itemDB->GetName();

			strncpy( outName, tmp.c_str(), size - 1 );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
int	RoleDataEx::GetResistanceMaxValue()
{
//	return int( TempData.Attr.ResistArgList.size() - 1);
	return 300;
}

//-----------------------------------------------------------------------------
// outAbility[3] 0°ò¥»­È 1°tÂI­È 2¸Ë³Æ¨ä¥LÀò±o
void RoleDataEx::GetAbilityDetailValues(RoleValueName_ENUM name, int* outAbility)
{
	switch (name)
	{
	case EM_RoleValue_STR:
		{
			outAbility[0] = int( TempData.Attr.Bas.BaseStr + 0.1f);
			outAbility[1] = int( TempData.Attr.Ability->STR + 0.1f);
			outAbility[2] = int( TempData.Attr.Fin.STR - TempData.Attr.Bas.BaseStr - TempData.Attr.Ability->STR + 0.1f );
			break;
		}
	case EM_RoleValue_STA:
		{
			outAbility[0] = int( TempData.Attr.Bas.BaseSta + 0.1f );
			outAbility[1] = int( TempData.Attr.Ability->STA + 0.1f );
			outAbility[2] = int( TempData.Attr.Fin.STA - TempData.Attr.Bas.BaseSta - TempData.Attr.Ability->STA + 0.1f );
			break;
		}
	case EM_RoleValue_INT:
		{
			outAbility[0] = int( TempData.Attr.Bas.BaseInt + 0.1f );
			outAbility[1] = int( TempData.Attr.Ability->INT + 0.1f );
			outAbility[2] = int( TempData.Attr.Fin.INT - TempData.Attr.Bas.BaseInt - TempData.Attr.Ability->INT + 0.1f );
			break;
		}
	case EM_RoleValue_MND:
		{
			outAbility[0] = int( TempData.Attr.Bas.BaseMnd + 0.1f );
			outAbility[1] = int( TempData.Attr.Ability->MND + 0.1f );
			outAbility[2] = int( TempData.Attr.Fin.MND - TempData.Attr.Bas.BaseMnd - TempData.Attr.Ability->MND + 0.1f );
			break;
		}
	case EM_RoleValue_AGI:
		{
			outAbility[0] = int( TempData.Attr.Bas.BaseAgi + 0.1f );
			outAbility[1] = int( TempData.Attr.Ability->AGI + 0.1f );
			outAbility[2] = int( TempData.Attr.Fin.AGI - TempData.Attr.Bas.BaseAgi - TempData.Attr.Ability->AGI + 0.1f );
			break;
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// outDPS[2] 0¥D¤â 1°Æ¤â
void RoleDataEx::GetPlayerDPS(float* outDPS)
{

	float MainDPS = TempData.Attr.Fin.Main_DMG / TempData.Attr.Fin.Main_ATKSpeed * 10;
	float SecDPS = TempData.Attr.Fin.Sec_DMG / TempData.Attr.Fin.Sec_ATKSpeed * 10;

	outDPS[0] = MainDPS;
	outDPS[1] = SecDPS;
	
}

//-----------------------------------------------------------------------------
// ­pºâ­I¥]¦PÃþ«¬ª««~¼Æ¶q
int RoleDataEx::GetBagItemCount(int objectID)
{
	int count = 0;
	GameObjDbStruct* itemDB = St_GetObjDB(objectID);
	if ( itemDB ) {
		// ·j´Mª««~­Ó¼Æ
		for( int i = 0 ; i < _MAX_BODY_COUNT_ ; i++ )
		{
			ItemFieldStruct* Temp = &PlayerBaseData->Body.Item[i];
			if ( Temp->OrgObjID == objectID )
				count += max(Temp->Count, 1);
		}

		// ¤£¯à°ïÅ|ª««~³Ì¤j¼Æ¬°1
		if ( count > 1 && itemDB->MaxHeap <= 1 )
			count = 1;
	}
	return count;
}

//-----------------------------------------------------------------------------
// ¨ú±o§Þ¯à¨Ï¥Î§Nƒj®É¶¡
bool RoleDataEx::GetMagicCooldown(MagicColdownStruct& coldown, int objectID, float* outTime)
{
	GameObjDbStructEx* itemDB;
	if ( outTime == NULL )
		return false;

	if ( (itemDB = St_GetObjDB(objectID)) != NULL )
	{
		float mutual, remaining;
		switch (itemDB->Classification)
		{
		case EM_ObjectClass_KeyItem:
			{
				if ( (objectID >= DF_SKILLID_BEGINNERPORTOL_BEGIN && objectID <= DF_SKILLID_BEGINNERPORTOL_END) || 
					objectID == DF_SKILLID_PORTOL || objectID == DF_SKILLID_DISENCHANT )
				{
					int iMagicID = St_GetKeyMagicID( RoleDataEx::KeyItemObjToID( objectID ) );
					if( iMagicID != 0 )
					{
						return GetMagicCooldown(coldown, iMagicID, outTime);
					}
					return true;
				}
			} break;

		case EM_ObjectClass_Item:
			if ( itemDB->Item.IncMagic_Onuse != 0 )		// ÀË¬dª««~¬O§_¦³ªk³N®ÄªG
				return GetMagicCooldown(coldown, itemDB->Item.IncMagic_Onuse, outTime);
			break;

		case EM_ObjectClass_MagicCollect:
			// ³Q°Ê§Þ¯à
			if ( itemDB->MagicCol.EffectType == EM_Magic_Eq )
			{
				outTime[0] = 0.0f;
				outTime[1] = 0.0f;
			}
			else
			{
				switch ( itemDB->MagicCol.Coldown.Class )
				{
				case EM_MagicColdownClass_Job:			//Â¾·~Ãþ«¬
					remaining = coldown.Job[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				case EM_MagicColdownClass_EQ:			//¸Ë³ÆÃþ«¬
					remaining = coldown.Eq[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				case EM_MagicColdownClass_Item:			//ª««~Ãþ«¬
					remaining = coldown.Item[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				default:
					remaining = 0.0f;
				}
				mutual = coldown.AllMagic * 0.1f;
				if ( mutual > remaining )
				{
					outTime[0] = float( itemDB->MagicCol.Coldown.TimeAllMagic );
					outTime[1] = mutual;
				}
				else
				{
					outTime[0] = float( itemDB->MagicCol.Coldown.Time );
					outTime[1] = remaining;
				}
			}			
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// ¨ú±o§Þ¯à¨Ï¥Î§Nƒj®É¶¡
// objectID ª«¥ó½s¸¹
// outTime[2] ¦^¶Ç§Nƒj®É¶¡ 0Á`§Nƒj®É¶¡ 1³Ñ©ó®É¶¡
bool RoleDataEx::GetObjectCooldown(int objectID, float* outTime)
{
	GameObjDbStructEx* itemDB;
	if ( outTime == NULL )
		return false;
	
	if ( (itemDB = St_GetObjDB(objectID)) != NULL )
	{
		float mutual, remaining;
		switch (itemDB->Classification)
		{
		case EM_ObjectClass_KeyItem:
			{
				if ( (objectID >= DF_SKILLID_BEGINNERPORTOL_BEGIN && objectID <= DF_SKILLID_BEGINNERPORTOL_END) || 
					 objectID == DF_SKILLID_PORTOL || objectID == DF_SKILLID_DISENCHANT )
				{
					int iMagicID = St_GetKeyMagicID( RoleDataEx::KeyItemObjToID( objectID ) );
					if( iMagicID != 0 )
					{
						return GetObjectCooldown( iMagicID, outTime );
					}
					return true;
				}
			} break;

		case EM_ObjectClass_Item:			
			//switch (itemDB->Item.UseType)
			//{
			//case EM_ItemUseType_Magic:
			//	if ( itemDB->Item.IncMagic_Onuse != 0 )		// ÀË¬dª««~¬O§_¦³ªk³N®ÄªG
			//		return GetObjectCooldown(itemDB->Item.IncMagic_Onuse, outTime);
			//	break;
			//}
			if ( itemDB->Item.IncMagic_Onuse != 0 )		// ÀË¬dª««~¬O§_¦³ªk³N®ÄªG
				return GetObjectCooldown(itemDB->Item.IncMagic_Onuse, outTime);
			break;

		case EM_ObjectClass_MagicCollect:
			// ³Q°Ê§Þ¯à
			if ( itemDB->MagicCol.EffectType == EM_Magic_Eq )
			{
				outTime[0] = 0.0f;
				outTime[1] = 0.0f;
			}
			else
			{
				switch ( itemDB->MagicCol.Coldown.Class )
				{
				case EM_MagicColdownClass_Job:			//Â¾·~Ãþ«¬
					remaining = BaseData.Coldown.Job[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				case EM_MagicColdownClass_EQ:			//¸Ë³ÆÃþ«¬
					remaining = BaseData.Coldown.Eq[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				case EM_MagicColdownClass_Item:			//ª««~Ãþ«¬
					remaining = BaseData.Coldown.Item[itemDB->MagicCol.Coldown.Type] * 0.1f;
					break;

				default:
					remaining = 0.0f;
				}
				mutual = BaseData.Coldown.AllMagic * 0.1f;
				if ( mutual > remaining )
				{
					outTime[0] = float( itemDB->MagicCol.Coldown.TimeAllMagic );
					outTime[1] = mutual;
				}
				else
				{
					outTime[0] = GetColdownTime(itemDB);//float( itemDB->MagicCol.Coldown.Time );
					outTime[1] = remaining;
				}
			}			
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
// ÀË¬dª««~­­¨î
bool RoleDataEx::CanWearObject(GameObjDbStruct* itemDB, int slot, bool ignoreLevel , int ImageObjID )
{
	if ( itemDB == NULL )
		return false;

	//////////////////////////////////////////////////////////////////////////
	//©Ê§OÀË¬d
	GameObjDbStructEx* ImageObjDB = St_GetObjDB( ImageObjID );
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
	//////////////////////////////////////////////////////////////////////////

	if ( itemDB->Limit.Voc._Voc != -1 )
	{
		if ( !(itemDB->Limit.Voc._Voc & (0x01 << BaseData.Voc)) )
			return false;
	}

	if ( itemDB->Limit.Sex._Sex != -1 )
	{
		switch(BaseData.Sex)
		{
		case EM_Sex_Boy:
			if ( itemDB->Limit.Sex.Boy == false )
				return false;
			break;

		case EM_Sex_Girl:
			if ( itemDB->Limit.Sex.Girl == false )
				return false;
			break;
		}

		/*
		if ( itemDB->Limit.Sex.Boy && BaseData.Sex != EM_Sex_Boy )
			return false;
		else if ( itemDB->Limit.Sex.Girl && BaseData.Sex != EM_Sex_Girl )
			return false;
		*/
	}

	if( IsPlayer() == false )
		return true;


	if ( ignoreLevel == false && itemDB->Limit.Level > TempData.Attr.Level )
		return false;

	if ( itemDB->Limit.STR > TempData.Attr.Ability->STR )
		return false;

	if ( itemDB->Limit.STA > TempData.Attr.Ability->STA )
		return false;

	if ( itemDB->Limit.INT > TempData.Attr.Ability->INT )
		return false;

	if ( itemDB->Limit.MND > TempData.Attr.Ability->MND )
		return false;

	if ( itemDB->Limit.AGI > TempData.Attr.Ability->AGI )
		return false;

	return CheckEquipmentWearSkill(itemDB, slot);
}

//-----------------------------------------------------------------------------
bool RoleDataEx::IsActiveBagItem(int index)
{
	if ( index >= 0 && index < _MAX_BODY_BEGIN_POS_ + 60 )
		return true;

	if ( index < 0 )
		return false;

	index = (index - _MAX_BODY_BEGIN_POS_) / 30;

	index -= 2;
	if ( index >= 0 && index < 4 )
	{
		return PlayerBaseData->TimeFlag[EM_TimeFlagEffect_BagPage3 + index] > -1;
	}
	return false;
}

//-----------------------------------------------------------------------------
bool RoleDataEx::CheckEquipmentWearSkill(GameObjDbStruct* itemDB, int slot)
{
	if ( itemDB == NULL || itemDB->Classification != EM_ObjectClass_Item )
		return false;

	switch ( itemDB->Item.Class )
	{
	case EM_Item_Weapon:
		// ªZ¾¹Ãþ»ÝÀË¬d°Æ¤â
		if ( slot == EM_EQWearPos_SecondHand && !TempData.Attr.Fin.WearSkill.SecondHand )
			return false;

		switch (itemDB->Item.WeaponType)
		{
		case EM_Weapon_Unarmed:
			if ( !TempData.Attr.Fin.WearSkill.Unarmed )
				return false;
			break;

		case EM_Weapon_Blade:
			if ( !TempData.Attr.Fin.WearSkill.Blade )
				return false;
			break;

		case EM_Weapon_Dagger:
			if ( !TempData.Attr.Fin.WearSkill.Dagger )
				return false;
			break;

		case EM_Weapon_Wand:
			if ( !TempData.Attr.Fin.WearSkill.Wand )
				return false;
			break;

		case EM_Weapon_Axe:
			if ( !TempData.Attr.Fin.WearSkill.Axe )
				return false;
			break;

		case EM_Weapon_Bludgeon:
			if ( !TempData.Attr.Fin.WearSkill.Bludgeon )
				return false;
			break;

		case EM_Weapon_Claymore:
			if ( !TempData.Attr.Fin.WearSkill.Claymore )
				return false;
			break;

		case EM_Weapon_Staff:
			if ( !TempData.Attr.Fin.WearSkill.Staff )
				return false;
			break;

		case EM_Weapon_2H_Axe:
			if ( !TempData.Attr.Fin.WearSkill.Axe_2H )
				return false;
			break;

		case EM_Weapon_2H_Hammer:
			if ( !TempData.Attr.Fin.WearSkill.Hammer_2H )
				return false;
			break;

		case EM_Weapon_Polearm:
			if ( !TempData.Attr.Fin.WearSkill.Polearm )
				return false;
			break;

		case EM_Weapon_Bow:
			if ( !TempData.Attr.Fin.WearSkill.Bow )
				return false;
			break;

		case EM_Weapon_CossBow:
			if ( !TempData.Attr.Fin.WearSkill.CossBow )
				return false;
			break;

		case EM_Weapon_Gun:
			if ( !TempData.Attr.Fin.WearSkill.Gun )
				return false;
			break;

		case EM_Weapon_Throw:
			if ( !TempData.Attr.Fin.WearSkill.Throw )
				return false;
			break;
		}
		break;

	case EM_Item_Armor:

		if(		itemDB->Item.ArmorPos == EM_ArmorPos_Back
			||	itemDB->Item.ArmorPos == EM_ArmorPos_Necklace
			||	itemDB->Item.ArmorPos == EM_ArmorPos_Ring
			||	itemDB->Item.ArmorPos == EM_ArmorPos_Earring
			||	itemDB->Item.ArmorPos == EM_ArmorPos_MagicTool					)
		{
			return true;
		}

		switch ( itemDB->Item.ArmorType )
		{
		case EM_Armor_HeavyArmed:
			if ( !TempData.Attr.Fin.WearSkill.HeavyArmed )
				return false;
			break;

		case EM_Armor_LightArmed:
			if ( !TempData.Attr.Fin.WearSkill.LightArmed )
				return false;
			break;

		case EM_Armor_Leather:
			if ( !TempData.Attr.Fin.WearSkill.Leather )
				return false;
			break;

		case EM_Armor_Clothes:
			if ( !TempData.Attr.Fin.WearSkill.Clothes )
				return false;
			break;

		case EM_Armor_Robe:
			if ( !TempData.Attr.Fin.WearSkill.Robe )
				return false;
			break;

		case EM_Armor_Shield:
			if ( !TempData.Attr.Fin.WearSkill.Shield )
				return false;
			break;

		case EM_Armor_Implement:
			if ( !TempData.Attr.Fin.WearSkill.Implement )
				return false;
			break;
		}
		break;
	}

	return true;
}

//-----------------------------------------------------------------------------
float RoleDataEx::GetSkillPoint(int magicID)
{
	for ( int i = 0; i < _MAX_SPSkill_COUNT_; i++ )
	{
		if ( PlayerTempData->Skill.SP[i] == magicID )
			return __min( float( Level() ) , PlayerBaseData->AbilityList[TempData.Attr.Voc].SPSkill[i] );
	}
	for ( int i = 0; i < _MAX_NormalSkill_COUNT_; i++ )
	{
		if ( PlayerTempData->Skill.MainJob[i] == magicID )
			return __min( float( Level() ) , PlayerBaseData->AbilityList[TempData.Attr.Voc].NormalSkill[i] );
	}
	if(		TempData.Attr.Voc_Sub >= EM_Vocation_GameMaster 
		&&	TempData.Attr.Voc_Sub  < EM_Max_Vocation )
	{
		for ( int i = 0; i < _MAX_NormalSkill_COUNT_; i++ )
		{
			if ( PlayerTempData->Skill.SubJob[i] == magicID )
				return __min( float( Level_Sub() ) , PlayerBaseData->AbilityList[TempData.Attr.Voc_Sub].NormalSkill[i] );
		}
	}
	if ( BaseData.TitleID != 0 )
	{
		GameObjDbStruct* objDB = St_GetObjDB(BaseData.TitleID);
		if ( objDB && objDB->Title.SkillID == magicID )
			return (float)objDB->Title.SkillLv;
	}

	//¤ÛÆF²Õ¦X§Þ¯à
	PhantomStruct& info = PlayerBaseData->Phantom;

	//key = ¤jid + ¤pid * 0x100000000
	INT64 id = 0;
	if ( info.EQ[0] > info.EQ[1] )
	{
		id = info.EQ[0] + info.EQ[1] * 0x100000000;
	}
	else
	{
		id = info.EQ[1] + info.EQ[0] * 0x100000000;
	}

	if ( magicID == RoleDataEx::PhantomSkill[ id ] )
	{
		return (( info.Info[ info.EQ[0]%1000 ].Lv + info.Info[ info.EQ[1]%1000 ].Lv ) / 2);
	}

	return 0;
}

//¨ú±o¬YBuffªºPowerLv
int RoleDataEx::GetBuffPowerLv( int magicID )
{
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		if( BaseData.Buff[i].BuffID == magicID )
			return BaseData.Buff[i].Power ;
	}
	return 0;
}

//¨ú±o¬YÄæ¦ìªº§Þ¯à°tÂIÁ`­È
int	RoleDataEx::GetTolalSkillPoint( int Pos )
{
	if( IsPlayer() == false )
		return 0;

	if( Pos >= _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_ )
		return 0;

	GameObjDbStructEx	*ObjDB;
	ObjDB = St_GetObjDB( PlayerTempData->Skill.AllSkill[Pos] );
	float	SkillLv = TempData.Attr.Ability->AllSkillLv[Pos];

	if( ObjDB->IsMagicCollect() == false )
		return 0;

	int	TotalPoint = 0;
	int i;
	for( i = 0 ; i < SkillLv -1 ; i++ )
	{
		int Lv = i + int( ObjDB->MagicCol.ExpTableRate ) - 1;
		if( Lv <= 0 )
			Lv = 0;

		TotalPoint += int( RoleDataEx::JobSkillExpTable[ Lv ] );
	}
	float	DSkillValue = SkillLv - i;

	int MaxSkillID = i + int( ObjDB->MagicCol.ExpTableRate ) - 1;
	if( MaxSkillID <=0 )
		MaxSkillID = 0;
	TotalPoint += int( RoleDataEx::JobSkillExpTable[ MaxSkillID ] * DSkillValue + 0.9 );

	return TotalPoint;
}

// §PÂ_¬O§_¬°¶Â¦â³æ¨¤¦â
bool RoleDataEx::CheckIgnoreNameList(const char* name)
{
	for ( int i = 0; i < _MAX_BAD_FRIENDLIST_COUNT_; i++ ) {
		if ( strcmp( PlayerSelfData->FriendList.BadFriendList[i] , name ) == 0 )
			return true;
	}
	return false;
}

//­pºâ­×¸Ë°²¿ú
int	RoleDataEx::CalRepairWeapon( ItemFieldStruct* InItem , ItemFieldStruct* OutItem)
{
	ItemFieldStruct Item = *InItem;

	bool	FixResult = true;
	int OrgQuality = Item.Quality;
	int	OrgDurable = (Item.Durable /100 * 100 );
	GameObjDbStructEx* ObjDB = St_GetObjDB( Item.OrgObjID );
	if( ObjDB == NULL )
		return 0;

	if( ObjDB->MaxHeap < 1 )
		return 0;

	if( ObjDB->IsArmor() == false && ObjDB->IsWeapon() == false )
		return 0;

	float	CostRate = 1.0f;
	if( ObjDB->IsArmor() )
	{
		if( ObjDB->Item.ArmorPos == EM_ArmorPos_MagicTool )
			return 0;
		CostRate = RoleDataEx::FixArmorRate[ ObjDB->Item.ArmorType ];
	}

	int	LastMaxDurable = ObjDB->Item.Durable * Item.Quality;

	if( Item.Durable >= LastMaxDurable )
		return 0;


	int QualityDown = 0;
//	int	QualityDown = int( ( LastMaxDurable - Item.Durable ) * ( 10.0f ) / LastMaxDurable * ( Item.Quality ) / 100 ); 
//	if( QualityDown < 0 )
//		QualityDown = 0;

	Item.Quality -= QualityDown;
	Item.Durable = ObjDB->Item.Durable * Item.Quality;

	int Cost = int( (Item.Durable - OrgDurable ) * ObjDB->Cost * CostRate * -0.75 / (ObjDB->Item.Durable*100)  );

	if( Cost >= 0 )
		Cost = -1;

	if( OutItem != NULL )
		*OutItem = Item;

	return Cost;
}

bool RoleDataEx::IsEquipSuitSkill(int skillId)
{
	for ( int i = 0; i < PlayerBaseData->SuitSkill.MaxEqSkillCount; i++ )
	{
		if ( PlayerBaseData->SuitSkill.EQ[i] == skillId )
			return true;
	}
	return false;
}

bool RoleDataEx::CheckEquipmentPos(int pos, ItemFieldStruct* itemField)
{
	if ( itemField == NULL )
		return false;

	// ¨ú±oª««~¸ê®Æ
	GameObjDbStruct* itemDB = St_GetObjDB(itemField->OrgObjID);
	if ( itemDB == NULL )
		return false;

	switch (itemDB->Classification)
	{
	case EM_ObjectClass_Item:
		switch ( itemDB->Item.Class )
		{
		case EM_Item_Weapon:
			switch ( itemDB->Item.WeaponPos )
			{
			case EM_WeaponPos_MainHand:			// ¥D¤â
			case EM_WeaponPos_TwoHand:			// ¨â¤â
				if ( pos == EM_EQWearPos_MainHand )
					return true;
				break;

			case EM_WeaponPos_OneHand:			// Âù¤â³£¥i¥H¸Ë³Æ
				if ( pos == EM_EQWearPos_MainHand || pos == EM_EQWearPos_SecondHand )
					return true;
				break;

			case EM_WeaponPos_SecondHand:		// °Æ¤â
				if ( pos == EM_EQWearPos_SecondHand )
					return true;
				break;

			case EM_WeaponPos_Ammo:				// ¤l¼u
				if ( pos == EM_EQWearPos_Ammo )
					return true;
				break;

			case EM_WeaponPos_Bow:				// ¤}
				if ( pos == EM_EQWearPos_Bow )
					return true;
				break;
			}
			break;

		case EM_Item_Armor:
			switch (itemDB->Item.ArmorPos)
			{
			case EM_ArmorPos_Head:
				if ( pos == EM_EQWearPos_Head )
					return true;
				break;

			case EM_ArmorPos_Gloves:
				if ( pos == EM_EQWearPos_Gloves )
					return true;
				break;

			case EM_ArmorPos_Shoes:
				if ( pos == EM_EQWearPos_Shoes )
					return true;
				break;

			case EM_ArmorPos_Clothes:
				if ( pos == EM_EQWearPos_Clothes )
					return true;
				break;

			case EM_ArmorPos_Pants:
				if ( pos == EM_EQWearPos_Pants )
					return true;
				break;

			case EM_ArmorPos_Back:
				if ( pos == EM_EQWearPos_Back )
					return true;
				break;

			case EM_ArmorPos_Belt:
				if ( pos == EM_EQWearPos_Belt )
					return true;
				break;

			case EM_ArmorPos_Shoulder:
				if ( pos == EM_EQWearPos_Shoulder )
					return true;
				break;

			case EM_ArmorPos_Necklace:
				if ( pos == EM_EQWearPos_Necklace )
					return true;
				break;

			case EM_ArmorPos_Ring:
				if ( pos == EM_EQWearPos_Ring1 || pos == EM_EQWearPos_Ring2 )
					return true;				
				break;

			case EM_ArmorPos_Earring:
				if ( pos == EM_EQWearPos_Earring1 || pos == EM_EQWearPos_Earring2 )
					return true;
				break;

			case EM_ArmorPos_SecondHand:
				if ( pos == EM_EQWearPos_SecondHand )
					return true;
				break;

			case EM_ArmorPos_MagicTool:
				if ( pos == EM_EQWearPos_MagicTool1 || pos == EM_EQWearPos_MagicTool2 || pos == EM_EQWearPos_MagicTool3 )
					return true;
				break;

			case EM_ArmorPos_Ornament:
				if ( pos == EM_EQWearPos_Ornament )
					return true;
				break;
			}				
			break;
		}
	}

	return false;
}