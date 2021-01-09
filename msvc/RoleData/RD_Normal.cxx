#include "RoleDataEx.h"
#include  <math.h>
#include "BaseFunction/BaseFunction.h"
#include "smallobj/SmallObj.h"
#include "ObjectStruct.h"

/*
int RoleDataEx::SelfClock( )
{
    return G_Clock - ItemID();
}
*/

void RoleDataEx::IncDMove( )
{
    if( TempData.Move.ProcDelay == 0 )
        return;

	if( IsPlayer() == false )
		return;

    if( TempData.Move.AddeDelay > 0 )
    {
        TempData.Move.AddeDelay --;
        return;
    }

    TempData.Move.ProcDelay-- ;
    
    if( TempData.Move.ProcDelay <= 0 )
    {
        BaseData.Pos.X = TempData.Move.Tx;
        BaseData.Pos.Y = TempData.Move.Ty;
        BaseData.Pos.Z = TempData.Move.Tz;

		TempData.Move.Dx = 0;
		TempData.Move.Dy = 0;
		TempData.Move.Dz = 0;

    }
    else
    {
        BaseData.Pos.X += TempData.Move.Dx;
        BaseData.Pos.Y += TempData.Move.Dy;
        BaseData.Pos.Z += TempData.Move.Dz;
    }    
}
//------------------------------------------------------------------------------------
void    RoleDataEx::DelMagicCost( GameObjDbStructEx* MagicDB , int MagicLv )
{
	if(		MagicDB->MagicCol.IsDisableSpellBuffEffect == false 
		&&	TempData.Attr.Effect.MagicSpell_NoCost )
	{
	}
	else
	{
		for( int i = 0 ; i < 2 ; i++ )
		{
			DelMagicCostBase( MagicDB , MagicLv , MagicDB->MagicCol.Cost[i].Type , MagicDB->MagicCol.Cost[i].Value );
		}
	}

	AddValue( EM_RoleValue_SoulPoint , MagicDB->MagicCol.AddSoulPoint , NULL );
}
void    RoleDataEx::DelMagicCostBase( GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue )
{
//	MagicSpellCostTypeENUM CostType	= MagicDB->MagicCol.Cost.Type ;
//	int CostValue	= MagicDB->MagicCol.Cost.Value ;

	switch( CostType )
	{
	case EM_MagicSpellCostType_None:					//無消耗

		break;
	case EM_MagicSpellCostType_HP:						//消耗 HP
		{
			 AddHP( this , float( CostValue*-1 ) );
		}
		break;
	case EM_MagicSpellCostType_MP:						//消耗 MP
		{
			if( MPCostPowerRate.size() > (unsigned)MagicLv )
				CostValue = int( CostValue * MPCostPowerRate[MagicLv] );
			CostValue =  int( CostValue * ( 100 - TempData.Attr.ManaDecrease() )/100 );   

			AddMP( this , float( CostValue*-1 ) );
		}
		break;
	case EM_MagicSpellCostType_HP_Per:						//消耗 HP
		{
			int	Value = int( TempData.Attr.Fin.MaxHP * CostValue / 100 );
			AddHP( this , float( Value*-1 ) );
		}
		break;
	case EM_MagicSpellCostType_MP_Per:						//消耗 MP
		{
			int	Value = int( TempData.Attr.Fin.MaxMP * CostValue / 100 );
			//QQ 要把mp消耗減少算進去
			Value =  int( Value * ( 100 - TempData.Attr.ManaDecrease() )/100 );   
			AddMP( this , float( Value *-1 ) );
		}
		break;
	case EM_MagicSpellCostType_SP_Warrior:			//消耗 SP 戰士	
		{
			if( CostValue != -1 )
			{
				CostValue =  int( CostValue * ( 100 - TempData.Attr.SPWarriorDecrease() )/100 ); 
			}

			if(		BaseData.Voc == EM_Vocation_Warrior 
				||	BaseData.Voc == EM_Vocation_Psyron	)
			{
				if( CostValue == -1 )
				{
					BaseData.SP = 0;
				}
				else
					AddSP( this , float( CostValue*-1 ) );
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Warrior
					||	BaseData.Voc_Sub == EM_Vocation_Psyron	)
			{
				if( CostValue == -1 )
					BaseData.SP_Sub = 0;
				else
					AddSP_Sub( this , float( CostValue*-1 ) );
			}
		}break;
	case EM_MagicSpellCostType_SP_Ranger:			//消耗 SP 遊俠
		{
			if( CostValue != -1 )
			{
				CostValue =  int( CostValue * ( 100 - TempData.Attr.SPRangerDecrease() )/100 ); 
			}

			if(		BaseData.Voc == EM_Vocation_Ranger 
				||	BaseData.Voc == EM_Vocation_Harpsyn )
			{
				if( CostValue == -1 )
					BaseData.SP = 0;
				else
					AddSP( this , float( CostValue*-1 ));
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Ranger 
					||	BaseData.Voc_Sub == EM_Vocation_Harpsyn )
			{
				if( CostValue == -1 )
					BaseData.SP_Sub = 0;
				else
					AddSP_Sub( this , float( CostValue*-1 ) );
			}
		}break;
	case EM_MagicSpellCostType_SP_Rogue:			//消耗 SP 盜賊	
		{
			if( CostValue != -1 )
			{
				CostValue =  int( CostValue * ( 100 - TempData.Attr.SPRogueDecrease() )/100 ); 
			}

			if(		BaseData.Voc == EM_Vocation_Rogue 
				||	BaseData.Voc == EM_Vocation_Duelist)
			{
				if( CostValue == -1 )
					BaseData.SP = 0;
				else
					AddSP( this , float( CostValue*-1 ) );
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Rogue 
					||	BaseData.Voc_Sub == EM_Vocation_Duelist	)
			{
				if( CostValue == -1 )
					BaseData.SP_Sub = 0;
				else
					AddSP_Sub( this , float( CostValue*-1 ) );
			}
		}break;
	case EM_MagicSpellCostType_StomachPoint:
		{
			AddStomachPoint( CostValue*-1 );

		}break;
	case EM_MagicSpellCostType_Item:					//消耗 物品
		{
			DelBodyItem( CostValue , 1 , EM_ActionType_MagicDestory );
		}
		break;
	case EM_MagicSpellCostType_Ammo_Gun:				//消耗 子彈
	case EM_MagicSpellCostType_Ammo_Bow:				//消耗 弓箭矢
	case EM_MagicSpellCostType_Ammo_CossBow:			//消耗 十字弓箭矢
	case EM_MagicSpellCostType_Ammo_Throw:				//消耗 投擲物
		{
			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );	
			Log_ItemDestroy( EM_ActionType_MagicDestory , *Item , CostValue , "" );	
			Item->Count -= CostValue;
			if( Item->Count <= 0 )
			{
				Item->Init();
				Net_EQBroken( EM_EQWearPos_Ammo );
			}

			Net_FixItemInfo_EQ( EM_EQWearPos_Ammo );
		}
		break;
	case EM_MagicSpellCostType_Ammo_All:
		{
			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );	
			Log_ItemDestroy( EM_ActionType_MagicDestory , *Item , 1 , "" );	
			Item->Count -= CostValue;
			if( Item->Count <= 0 )
			{
				Item->Init();
				Net_EQBroken( EM_EQWearPos_Ammo );
			}

			Net_FixItemInfo_EQ( EM_EQWearPos_Ammo );
		}
		break;
	case EM_MagicSpellCostType_SoulPoint:
		{
			AddValue( EM_RoleValue_SoulPoint , CostValue*-1 , NULL );
		}
		break;
	}

}
//------------------------------------------------------------------------------------
//計算到某一點的直線所需時間
int		RoleDataEx::MoveTime( float X , float Y , float Z )
{
    int Ret = 0;
	if( BaseData.Mode.Gravity != false )
		Ret = int( ( Length( X ,  Y ,  Z ) * 10 )   /  MoveSpeed() + 0.5 )  ;
	else
		Ret = int( ( Length3D( X ,  Y ,  Z ) * 10 )   /  MoveSpeed() + 0.5 )  ;

    if( Ret <= 0 )
        return 1;
    return Ret;
}
//------------------------------------------------------------------------------------
//取得SampleRoleData
void    RoleDataEx::GetSampleRoleData( SampleRoleData* Data )
{
	char Buf[32];
	sprintf_s( Buf , sizeof(Buf) , "%d" , BaseData.ZoneID );

	Data->DBID = DBID();
	Data->ZoneName	= Buf;
	if( BaseData.Voc == -1 || BaseData.Voc >= EM_Max_Vocation )
		BaseData.Voc = EM_Vocation_Warrior;

    Data->Level		= PlayerBaseData->AbilityList[ BaseData.Voc ].Level;
	if( BaseData.Voc_Sub != EM_Vocation_None && BaseData.Voc_Sub < EM_Max_Vocation )
		Data->Level_Sub = PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].Level;
	else
		Data->Level_Sub = 0;

    Data->OrgObjID  = BaseData.ItemInfo.OrgObjID;
    Data->Race      = BaseData.Race;
	Data->Voc       = BaseData.Voc;
	Data->Voc_Sub	= BaseData.Voc_Sub;
	
	memcpy( Data->BoneScale, BaseData.Look.BoneScale, sizeof( Data->BoneScale ) );

	Data->iFaceID		= BaseData.Look.FaceID;
	Data->iHairID		= BaseData.Look.HairID;
	Data->iHairColor	= BaseData.Look.HairColor;
	Data->iBodyColor	= BaseData.Look.BodyColor;

    Data->RoleName  = BaseData.RoleName;
    Data->Sex       = BaseData.Sex;
	Data->EQ		= BaseData.EQ;
	//////////////////////////////////////////////////////////////////////////
	if( (unsigned) PlayerBaseData->CoolSuitID >= _DEF_MAX_COOL_SUIT_COUNT_ )
		PlayerBaseData->CoolSuitID = 0;
	CoolSuitBase& SuitInfo = PlayerBaseData->CoolSuitList[ PlayerBaseData->CoolSuitID ];

	if( SuitInfo.ShowEQ.Head == false )
	{
		Data->EQ.Head.OrgObjID			= 0;
		Data->EQ.Head.ImageObjectID		= 0;
		Data->EQ.Head.MainColor			= 0;
		Data->EQ.Head.OffColor			= 0;
		Data->EQ.Head.Level				= 0;
	}
	else if( SuitInfo.Head.IsEmpty() == false )
	{
		Data->EQ.Head.OrgObjID			= SuitInfo.Head.ImageObjectID;
		Data->EQ.Head.ImageObjectID		= SuitInfo.Head.ImageObjectID;
		Data->EQ.Head.MainColor			= SuitInfo.Head.MainColor;
		Data->EQ.Head.OffColor			= SuitInfo.Head.OffColor;
		Data->EQ.Head.Level				= 0;
	}

	if( SuitInfo.ShowEQ.Gloves == false )
	{
		Data->EQ.Gloves.OrgObjID			= 0;
		Data->EQ.Gloves.ImageObjectID		= 0;
		Data->EQ.Gloves.MainColor			= 0;
		Data->EQ.Gloves.OffColor			= 0;
		Data->EQ.Gloves.Level				= 0;
	}
	else if( SuitInfo.Gloves.IsEmpty() == false )
	{
		Data->EQ.Gloves.OrgObjID		= SuitInfo.Gloves.ImageObjectID;
		Data->EQ.Gloves.ImageObjectID	= SuitInfo.Gloves.ImageObjectID;
		Data->EQ.Gloves.MainColor		= SuitInfo.Gloves.MainColor;
		Data->EQ.Gloves.OffColor		= SuitInfo.Gloves.OffColor;
		Data->EQ.Gloves.Level			= 0;
	}

	if( SuitInfo.ShowEQ.Shoes == false )
	{
		Data->EQ.Shoes.OrgObjID			= 0;
		Data->EQ.Shoes.ImageObjectID		= 0;
		Data->EQ.Shoes.MainColor			= 0;
		Data->EQ.Shoes.OffColor			= 0;
		Data->EQ.Shoes.Level				= 0;
	}
	else if( SuitInfo.Shoes.IsEmpty() == false )
	{
		Data->EQ.Shoes.OrgObjID			= SuitInfo.Shoes.ImageObjectID;
		Data->EQ.Shoes.ImageObjectID	= SuitInfo.Shoes.ImageObjectID;
		Data->EQ.Shoes.MainColor		= SuitInfo.Shoes.MainColor;
		Data->EQ.Shoes.OffColor			= SuitInfo.Shoes.OffColor;
		Data->EQ.Shoes.Level			= 0;
	}

	if( SuitInfo.ShowEQ.Clothes == false )
	{
		Data->EQ.Clothes.OrgObjID			= 0;
		Data->EQ.Clothes.ImageObjectID		= 0;
		Data->EQ.Clothes.MainColor			= 0;
		Data->EQ.Clothes.OffColor			= 0;
		Data->EQ.Clothes.Level				= 0;
	}
	else if( SuitInfo.Clothes.IsEmpty() == false )
	{
		Data->EQ.Clothes.OrgObjID		= SuitInfo.Clothes.ImageObjectID;
		Data->EQ.Clothes.ImageObjectID	= SuitInfo.Clothes.ImageObjectID;
		Data->EQ.Clothes.MainColor		= SuitInfo.Clothes.MainColor;
		Data->EQ.Clothes.OffColor		= SuitInfo.Clothes.OffColor;
		Data->EQ.Clothes.Level			= 0;
	}

	if( SuitInfo.ShowEQ.Pants == false )
	{
		Data->EQ.Pants.OrgObjID			= 0;
		Data->EQ.Pants.ImageObjectID		= 0;
		Data->EQ.Pants.MainColor			= 0;
		Data->EQ.Pants.OffColor			= 0;
		Data->EQ.Pants.Level				= 0;
	}
	else if( SuitInfo.Pants.IsEmpty() == false )
	{
		Data->EQ.Pants.OrgObjID			= SuitInfo.Pants.ImageObjectID;
		Data->EQ.Pants.ImageObjectID	= SuitInfo.Pants.ImageObjectID;
		Data->EQ.Pants.MainColor		= SuitInfo.Pants.MainColor;
		Data->EQ.Pants.OffColor			= SuitInfo.Pants.OffColor;
		Data->EQ.Pants.Level			= 0;
	}

	if( SuitInfo.ShowEQ.Back == false )
	{
		Data->EQ.Back.OrgObjID			= 0;
		Data->EQ.Back.ImageObjectID		= 0;
		Data->EQ.Back.MainColor			= 0;
		Data->EQ.Back.OffColor			= 0;
		Data->EQ.Back.Level				= 0;
	}
	else if( SuitInfo.Back.IsEmpty() == false )
	{
		Data->EQ.Back.OrgObjID			= SuitInfo.Back.ImageObjectID;
		Data->EQ.Back.ImageObjectID		= SuitInfo.Back.ImageObjectID;
		Data->EQ.Back.MainColor			= SuitInfo.Back.MainColor;
		Data->EQ.Back.OffColor			= SuitInfo.Back.OffColor;
		Data->EQ.Back.Level				= 0;
	}

	if( SuitInfo.ShowEQ.Belt == false )
	{
		Data->EQ.Belt.OrgObjID			= 0;
		Data->EQ.Belt.ImageObjectID		= 0;
		Data->EQ.Belt.MainColor			= 0;
		Data->EQ.Belt.OffColor			= 0;
		Data->EQ.Belt.Level				= 0;
	}
	else if( SuitInfo.Belt.IsEmpty() == false )
	{
		Data->EQ.Belt.OrgObjID			= SuitInfo.Belt.ImageObjectID;
		Data->EQ.Belt.ImageObjectID		= SuitInfo.Belt.ImageObjectID;
		Data->EQ.Belt.MainColor			= SuitInfo.Belt.MainColor;
		Data->EQ.Belt.OffColor			= SuitInfo.Belt.OffColor;
		Data->EQ.Belt.Level				= 0;
	}

	if( SuitInfo.ShowEQ.Shoulder == false )
	{
		Data->EQ.Shoulder.OrgObjID			= 0;
		Data->EQ.Shoulder.ImageObjectID		= 0;
		Data->EQ.Shoulder.MainColor			= 0;
		Data->EQ.Shoulder.OffColor			= 0;
		Data->EQ.Shoulder.Level				= 0;
	}
	else if( SuitInfo.Shoulder.IsEmpty() == false )
	{
		Data->EQ.Shoulder.OrgObjID			= SuitInfo.Shoulder.ImageObjectID;
		Data->EQ.Shoulder.ImageObjectID		= SuitInfo.Shoulder.ImageObjectID;
		Data->EQ.Shoulder.MainColor			= SuitInfo.Shoulder.MainColor;
		Data->EQ.Shoulder.OffColor			= SuitInfo.Shoulder.OffColor;
		Data->EQ.Shoulder.Level				= 0;
	}

	if( SuitInfo.ShowEQ.Ornament == false )
	{
		Data->EQ.Ornament.OrgObjID			= 0;
		Data->EQ.Ornament.ImageObjectID		= 0;
		Data->EQ.Ornament.MainColor			= 0;
		Data->EQ.Ornament.OffColor			= 0;
		Data->EQ.Ornament.Level				= 0;
	}
	else if( SuitInfo.Ornament.IsEmpty() == false )
	{
		Data->EQ.Ornament.OrgObjID			= SuitInfo.Ornament.ImageObjectID;
		Data->EQ.Ornament.ImageObjectID		= SuitInfo.Ornament.ImageObjectID;
		Data->EQ.Ornament.MainColor			= SuitInfo.Ornament.MainColor;
		Data->EQ.Ornament.OffColor			= SuitInfo.Ornament.OffColor;
		Data->EQ.Ornament.Level				= 0;
	}
	//////////////////////////////////////////////////////////////////////////
	if( PlayerBaseData->DestroyTime == -1 )
	{
		Data->DestroyTime = 0;
	}
	else
	{
		Data->DestroyTime = PlayerBaseData->DestroyTime - RoleDataEx::G_Now;
	}

	Data->SysFlag = BaseData.SysFlag;
	//Data->ShowEQ._Value = PlayerBaseData->ShowEQ._Value;
	//Data->ShowEQ = SuitInfo.ShowEQ;
	Data->ShowEQ._Value = -1;
}
//------------------------------------------------------------------------------------
//取得NPCData的資料
void    RoleDataEx::GetNPCData( NPCData* Data )
{
    Data->DBID = Base.DBID;

    Data->OrgObjID  = BaseData.ItemInfo.OrgObjID;							        
    Data->CreateTime = Base.CreateTime;
    Data->Mode      = BaseData.Mode;
    Data->RoleName  = BaseData.RoleName;
    Data->ZoneID    = BaseData.ZoneID;	
    Data->Pos       = BaseData.Pos;
    Data->LiveTime  = SelfData.LiveTime;
    Data->OwnerDBID = TempData.Sys.OwnerDBID;
    Data->PID       = SelfData.PID;
    Data->PlotClassName = SelfData.PlotClassName;
    Data->AutoPlot = SelfData.AutoPlot;
	Data->QuestID	= SelfData.NpcQuestID;
    Data->CreateAccount = TempData.CreateAccount;
	Data->vX		= BaseData.vX;
	Data->vY		= BaseData.vY;
	Data->vZ		= BaseData.vZ;
	Data->RoomID	= BaseData.RoomID;
}
//------------------------------------------------------------------------------------
//取各個物件的時脈於數
bool    RoleDataEx::ClockMod( int Mod )
{
    return ( ( G_Clock - TempData.Sys.ItemID ) % Mod == 0 );
}
//-----------------------------------------------------------------------------------------------
//攻擊距離
int	RoleDataEx::MainAttackRange( RoleData* Target )
{
    return int( TempData.BoundRadiusY + Target->TempData.BoundRadiusY + TempData.Attr.MainAttackRange ) + TempData.Attr.Mid.Body[EM_WearEqType_AttackRange];	

}
int	RoleDataEx::SecAttackRange( RoleData* Target )
{
	return int( TempData.BoundRadiusY + Target->TempData.BoundRadiusY + TempData.Attr.SecAttackRange ) + TempData.Attr.Mid.Body[EM_WearEqType_AttackRange];	

}
//-----------------------------------------------------------------------------------------------
//與看的方向所夾的角度
float   RoleDataEx::CalAngle( RoleDataEx* Target )
{
    double Dir; /*
    if( BaseData.Pos.Dir < 180 )
        Dir = BaseData.Pos.Dir / 57.2958;
    else
        Dir = ( 360 -BaseData.Pos.Dir )/57.2958;*/
    Dir = ( 360 -BaseData.Pos.Dir )/57.2958;

    double x = cos( Dir );
    double z = sin( Dir );

    double x1 = Target->BaseData.Pos.X - BaseData.Pos.X;
    double z1 = Target->BaseData.Pos.Z - BaseData.Pos.Z;

    double Len = sqrt( x1*x1 + z1*z1 );

    if( Len < 0.1 )
        return 0;

    x1 /= Len;
    z1 /= Len;

    double RetDir = acos( x*x1 + z*z1 ) * 57.295;

    return (float)RetDir;
	
}
//-----------------------------------------------------------------------------------------------
//計算面對的方向
//與z軸夾的角度
float		RoleDataEx::CalDir( float dx , float dz )
{
	if( FloatEQU( dz , 0 ) && FloatEQU( dx , 0 ) )
		return 0;

//    if( FloatEQU( dz , 0 ) )
//        dz = float( 0.01 );

//    if( FloatEQU( dx , 0 ) )
//        dx = float( 0.01 );

    double	L	= sqrt( dx * dx + dz * dz );
  
    double	Dir = acos( dx / L ) * 57.2958;

    if( Dir < 0.001 )
        Dir = 0.001;

    if( dz > 0 )
        Dir = 360 - Dir;
    
    return (float)Dir;
}
//-----------------------------------------------------------------------------------------------
float	RoleDataEx::CalDir( RoleDataEx* Target )
{
    return CalDir(	float( Target->BaseData.Pos.X - BaseData.Pos.X )  
        ,	float( Target->BaseData.Pos.Z - BaseData.Pos.Z )	);
}
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::CalDir( float Dir , float& dx , float& dz )
{	
	if( Dir < 0 ) Dir += 360.0f;
	if( Dir > 360 ) Dir -= 360.0f;

	float D =   ( 360.0f - Dir ) / 57.2958f;
//	dx = cos( D ) ;
//	dz = sin( D ) ;
	dx = cos( D );// - sin( D );
	dz = sin( D );// + cos( D );	
}
//-----------------------------------------------------------------------------------------------
//攻擊目標
bool	RoleDataEx::AttackTarget( int TargetID )
{
    RoleDataEx*	TargetVal = (RoleDataEx*)St_GetRoleData( TargetID );

    if( TargetVal == NULL )
        return false;

	if( TargetVal->RoomID() != RoomID() )
		return false;

    //如果為玩家
    if( IsPlayer() )
    {
        SetAttack( TargetVal );
        return true;
    }
    else if ( IsNPC() )
    {
        if (CheckStrikback())
        {
            SetAttack( TargetVal );
            //if( SetAttack( TargetVal ) != false )
            //    SetFollow( TargetVal );
        }
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------
//停止攻擊
bool	RoleDataEx::StopAttack( )
{
    return SetAtkFolOff();
}
//------------------------------------------------------------------------------------
//清除使用中的物品( 使用失敗清除 )
bool    RoleDataEx::ClsUseItem( )
{
    int Pos = TempData.Magic.UseItemPos;
    int Type = TempData.Magic.UseItemType;
    //取得欄位資料

    TempData.Magic.ClsUseItem();

    ItemFieldStruct* Item = GetItem( Pos , Type  );
    if( Item == NULL || Item->Pos != EM_USE_ITEM )
        return false;

    Item->Pos = EM_ItemState_NONE;

    //資料修正
    Net_FixItemInfo( Pos , Type );

    return true;
}
//------------------------------------------------------------------------------------
//刪除使用物品
bool    RoleDataEx::DelUseItem( )
{
    if( TempData.Magic.UseItem == 0 )
        return true;

    int Pos = TempData.Magic.UseItemPos;
    int Type = TempData.Magic.UseItemType;

    //取得欄位資料
    ItemFieldStruct* Item = GetItem( Pos , Type );
    if( Item == NULL || Item->Pos != EM_USE_ITEM )
	{
		TempData.Magic.ClsUseItem();
        return false;
	}

    //檢查是否消耗
    GameObjDbStructEx	*OrgDB;
    OrgDB = St_GetObjDB( Item->OrgObjID );

    if( OrgDB == NULL || OrgDB->Classification != EM_ObjectClass_Item)
	{
		TempData.Magic.ClsUseItem();
        return false;
	}


    //清除欄位資料
    if( OrgDB->Mode.Expense != false )
    {
		//檢查物品被鎖定
		if( Item->Mode.ItemLock != false )
			return false;

		Log_ItemDestroy(  EM_ActionType_UseItemDestroy , *Item , 1 , "" );
        if( Item->Count <= 1 )
		{
            Item->Init();
		}
        else
		{
            Item->Count --;
		}

    }
	if( OrgDB->Item.ItemUseOKScript[0] != 0 )
		CallLuaFunc( TempData.Magic.TargetID , OrgDB->Item.ItemUseOKScript );

    Item->Pos = EM_ItemState_NONE;

    //資料修正
    Net_FixItemInfo( Pos , Type );


    TempData.Magic.ClsUseItem();

    return true;
}
//------------------------------------------------------------------------------------
void    RoleDataEx::StopMove( )
{
	if( TempData.Move.Tx != 0 || TempData.Move.Ty != 0 || TempData.Move.Tz != 0 )
	{
		BaseData.Pos.X = TempData.Move.Tx;
		BaseData.Pos.Y = TempData.Move.Ty;
		BaseData.Pos.Z = TempData.Move.Tz;
	}
	TempData.Move.Dx = 0;
	TempData.Move.Dz = 0;
	TempData.Move.Dy = 0;
    TempData.Move.ProcDelay = 0;
    TempData.Move.AddeDelay = 0;
	St_ClearPath( GUID());
}
//------------------------------------------------------------------------------------
void    RoleDataEx::StopMoveNow( )
{
//	if( TempData.Move.Dx == 0 && TempData.Move.Dz == 0 )
//		return;
	
	if( IsPlayer() )
	{
		TempData.Move.Tx = BaseData.Pos.X;
		TempData.Move.Ty = BaseData.Pos.Y;
		TempData.Move.Tz = BaseData.Pos.Z;
	}
	else
	{
		TempData.Move.Tx = BaseData.Pos.X + TempData.Move.Dx*3;
		TempData.Move.Ty = BaseData.Pos.Y;
		TempData.Move.Tz = BaseData.Pos.Z + TempData.Move.Dz*3;
	}
	TempData.Move.ProcDelay = 0;
	TempData.Move.AddeDelay = 0;
	TempData.Move.Dx = 0;
	TempData.Move.Dz = 0;
	TempData.Move.Dy = 0;

	TempData.Move.LockSetPosX = BaseData.Pos.X;
	TempData.Move.LockSetPosZ = BaseData.Pos.Z;
	TempData.Move.IsLockSetPos = true;

	St_ClearPath( GUID());
//	St_SetPos( GUID() );

	Net_SendRangeMove( EM_ClientMoveType_SetPos );
}
//------------------------------------------------------------------------------------
//重設擁有的被動技能
void    RoleDataEx::ReSetPassiveSkill( )
{
    PlayerTempData->PassiveSkill.Clear();
	PlayerTempData->PassiveSkillLv.Clear();

    GameObjDbStructEx	*MagicCol;
//	GameObjDbStructEx	*MagicBase;
	
    for( int i = 0 ; i < _MAX_NormalSkill_COUNT_+ _MAX_NormalSkill_COUNT_+ _MAX_SPSkill_COUNT_; i++ )
    {
        int SkillID = PlayerTempData->Skill.AllSkill[ i ];

        MagicCol = St_GetObjDB( SkillID );
        if( MagicCol->IsMagicCollect() == false )
            continue;

        if( MagicCol->MagicCol.EffectType != EM_Magic_Eq )
            continue;

		for( int x = 0 ; x <  _MAX_MAGICCOLLECT_GROUP_COUNT_ ; x++ )
			for( int y = 0 ; y < _MAX_MAGICCOLLECT_COUNT_ ; y++ )
			{
				//MagicBase = static_cast<GameObjDbStructEx*>( MagicCol->MagicCol.Magic[x][y].MagicBaseDB );
				//GameObjDbStructEx* MagicBase = St_GetObjDB( MagicCol->MagicCol.Magic_List[0].MagicBaseID );
				GameObjDbStructEx* MagicBase = St_GetObjDB( MagicCol->MagicCol.Magic[x][y].MagicBaseID );
				if( MagicBase == NULL || MagicBase->IsMagicBase() == false )
					continue;

				PlayerTempData->PassiveSkill.Push_Back( MagicBase->GUID );			
				PlayerTempData->PassiveSkillLv.Push_Back( GetMagicLv( i ) );
			}
    }


}
//------------------------------------------------------------------------------------
//初始化主副職法術資料
bool    RoleDataEx::InitMagicBook( )
{   
	if( IsPlayer() == false )
		return false;

	map< int , int >	LearnMagic_ID_Lv_Map;
	//map< int , int >	LearnMagic_ID_Pos_Map;
	map< int , int >::iterator Iter;


    GameObjDbStructEx	*MainJobMB;
    GameObjDbStructEx	*SubJobMB;
    GameObjDbStructEx	*MagicCol;
	GameObjDbStructEx	*KeyItemDB;
	MainJobMB = St_GetObjDB( RoleDataEx::GlobalSetting.LearnMagicID + BaseData.Voc );    

	if ( BaseData.Voc_Sub != -1 )
		SubJobMB = St_GetObjDB( RoleDataEx::GlobalSetting.LearnMagicID + BaseData.Voc_Sub );    
	else
		SubJobMB = NULL;

	//////////////////////////////////////////////////////////////////////////

	memset( &PlayerTempData->Skill.JobSkill , 0 , sizeof(PlayerTempData->Skill.JobSkill) );

    if( MainJobMB == NULL )
    {        
        return false;
	}

	for( int LoopX = 0 ; LoopX < 3 ; LoopX++ )
	{
		//主職    
		//設定一般法術
		for( int i = 0 ; i < MainJobMB->LearnMagic.NormalSkillCount ; i++ )
		{
			JobSkillBaseStruct& Skill = MainJobMB->LearnMagic.NormalSkill[ i ];

			MagicCol = St_GetObjDB( Skill.MagicID );
			if( MagicCol == NULL )
				continue;


			int DLV = TempData.Attr.Level - Skill.LearnLV;
			if( DLV < 0 )
				continue;


			KeyItemDB = St_GetObjDB( MainJobMB->LearnMagic.NormalSkill[ i ].KeyItemID );

			if( KeyItemDB->IsKeyItem() != false )
			{
				if( BaseData.KeyItem.GetFlag( RoleDataEx::KeyItemObjToID( KeyItemDB->GUID) ) == false )
					continue;
			}
			bool PreSkillResult = true;
			//前置技能檢查
			for( int j = 0 ; j < 2 ; j++ )
			{
				int NeedMagicID = MainJobMB->LearnMagic.NormalSkill[ i ].NeedMagicID[j];
				int NeedMagicLv = MainJobMB->LearnMagic.NormalSkill[ i ].NeedMagicLv[j];

				if( NeedMagicID == 0 )
					continue;

				Iter = LearnMagic_ID_Lv_Map.find( NeedMagicID );
				if( Iter == LearnMagic_ID_Lv_Map.end() )
				{
					PreSkillResult = false;
					break;
				}
				int SkillLv =Iter->second;

				if( NeedMagicLv > SkillLv )
				{
					PreSkillResult = false;
					break;
				}
			}

			if( PreSkillResult == false )
				continue;		

			//取得技能等級
			{
				int SkillLv = int( PlayerBaseData->AbilityList[ BaseData.Voc ].NormalSkill[ Skill.SaveLvPos ] );
				PlayerTempData->Skill.MainJob[ Skill.SaveLvPos ] = Skill.MagicID;
				LearnMagic_ID_Lv_Map[ Skill.MagicID ] = SkillLv;
			}
		}

		//設定職業法術
		for( int i = 0 ; i < MainJobMB->LearnMagic.SPSkillCount ; i++ )
		{
			JobSkillBaseStruct& Skill = MainJobMB->LearnMagic.SPSkill[ i ];

			MagicCol = St_GetObjDB( Skill.MagicID );
			if( MagicCol == NULL )
				continue;


			int DLV = TempData.Attr.Level - Skill.LearnLV;
			if( DLV < 0 )
				continue;


			KeyItemDB = St_GetObjDB( MainJobMB->LearnMagic.SPSkill[ i ].KeyItemID );

			if( KeyItemDB->IsKeyItem() != false )
			{
				if( BaseData.KeyItem.GetFlag( RoleDataEx::KeyItemObjToID( KeyItemDB->GUID ) ) == false )
					continue;
			}
			bool PreSkillResult = true;
			//前置技能檢查
			for( int j = 0 ; j < 2 ; j++ )
			{
				int NeedMagicID = MainJobMB->LearnMagic.SPSkill[ i ].NeedMagicID[j];
				int NeedMagicLv = MainJobMB->LearnMagic.SPSkill[ i ].NeedMagicLv[j];
				if( NeedMagicID == 0 )
					continue;

				//int SkillLv = LearnMagic_ID_Lv_Map[ NeedMagicID ];
				Iter = LearnMagic_ID_Lv_Map.find( NeedMagicID );
				if( Iter == LearnMagic_ID_Lv_Map.end() )
				{
					PreSkillResult = false;
					break;
				}
				
				int SkillLv =Iter->second;

				if( NeedMagicLv > SkillLv )
				{
					PreSkillResult = false;
					break;
				}
			}

			if( PreSkillResult == false )
				continue;		

			//取得技能等級
			{
				int SkillLv = int( PlayerBaseData->AbilityList[ BaseData.Voc ].SPSkill[ Skill.SaveLvPos ] );
				PlayerTempData->Skill.SP[ Skill.SaveLvPos ] = Skill.MagicID;
				LearnMagic_ID_Lv_Map[ Skill.MagicID ] = SkillLv;
			}
		}
		//設定副職
		if( SubJobMB != NULL )
		{
			for( int i = 0 ; i < SubJobMB->LearnMagic.NormalSkillCount ; i++ )
			{
				JobSkillBaseStruct& Skill = SubJobMB->LearnMagic.NormalSkill[ i ];

				MagicCol = St_GetObjDB( Skill.MagicID );
				if( MagicCol == NULL )
					continue;


				int DLV = TempData.Attr.Level_Sub - Skill.LearnLV;
				if( DLV < 0 )
					continue;


				KeyItemDB = St_GetObjDB( SubJobMB->LearnMagic.NormalSkill[ i ].KeyItemID );

				if( KeyItemDB->IsKeyItem() != false )
				{
					if( BaseData.KeyItem.GetFlag( RoleDataEx::KeyItemObjToID( KeyItemDB->GUID ) ) == false )
						continue;
				}
				bool PreSkillResult = true;
				//前置技能檢查
				for( int j = 0 ; j < 2 ; j++ )
				{
					int NeedMagicID = SubJobMB->LearnMagic.NormalSkill[ i ].NeedMagicID[j];
					int NeedMagicLv = SubJobMB->LearnMagic.NormalSkill[ i ].NeedMagicLv[j];
					if( NeedMagicID == 0 )
						continue;

					//int SkillLv = LearnMagic_ID_Lv_Map[ NeedMagicID ];
					Iter = LearnMagic_ID_Lv_Map.find( NeedMagicID );
					if( Iter == LearnMagic_ID_Lv_Map.end() )
					{
						PreSkillResult = false;
						break;
					}
					int SkillLv =Iter->second;

					if( NeedMagicLv > SkillLv )
					{
						PreSkillResult = false;
						break;
					}
				}

				if( PreSkillResult == false )
					continue;		

				//取得技能等級
				{
					int SkillLv = int( PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].NormalSkill[ Skill.SaveLvPos ] );
					PlayerTempData->Skill.SubJob[ Skill.SaveLvPos ] = Skill.MagicID;
					LearnMagic_ID_Lv_Map[ Skill.MagicID ] = SkillLv;
				}
			}
		}
	}
   
	SetPetSkill( );

    return true;
}
//------------------------------------------------------------------------------------
//檢查是否可以法術配點
bool    RoleDataEx::CheckSetMagicPoint( int MagicPos )
{
//    if( MagicPos >=  _MAX_NormalSkill_COUNT_ )
//        return false;
/*
    //SkillBaseStruct* Skill = PlayerBaseData->Skill.MainJob[ MagicPos ];
    SkillBaseStruct* Skill = PlayerBaseData->Skill.GetSkill_MainJob( MagicPos );
    if( Skill == NULL )
        return false;

    GameObjDbStructEx	*MainJobMB = St_GetObjDB( Def_ObjectClass_LearnMagic + BaseData.Voc );    
    GameObjDbStructEx	*BaseMagic = St_GetObjDB( Skill->SkillID );

    if( BaseMagic == NULL || MainJobMB == NULL )
        return false;

    JobNormalSkillBase&     Book  = MainJobMB->LearnMagic.NormalSkill[ MagicPos ];

    int DLV = Level() - Book.BaseLearnLV;
    int MaxLV;

    //等級不足
    if( DLV < 0 )
        return false;

    if( Book.Learn_DLV == 0 )
    {
        MaxLV = Book.MaxLV;
    }
    else
    {
        MaxLV = DLV / Book.Learn_DLV + 1;
    }

    if( MaxLV > Book.MaxLV )
        MaxLV = Book.MaxLV;

    if( Skill->Point != 0 )
    {
        if( Skill->Point >= MaxLV )
            return false;
    }
    //檢查法術配點是否足夠
    //if( TempData.Attr.Ability->SkillPoint < BaseMagic->AllMagic[ Skill->Point ]->Magic.CostPoint )
	if( TempData.Attr.Ability->SkillPoint < 1 )
        return false;

    //資料有問題
//    if( BaseMagic->AllMagic[ Skill->Point  ]->Magic.CostPoint < 0 )
//        return false;

    //1檢查是否有重要物品
    if( Book.KeyItemID != 0 )
    {
        if( BaseData.KeyItem.GetFlag( Book.KeyItemID - Def_ObjectClass_KeyItem ) == false )
            return false;
    }

    //2檢查需求法術
    for( int i = 0 ; i < 2 ; i++ )
    {
        GameObjDbStructEx	*NeedMagic = St_GetObjDB( Book.RequestMagicID[ i ] );
        int     MagicBase;
        int     MagicLV;
        bool    IsFind;
        if( NeedMagic == NULL )
            continue;

        if( NeedMagic->MagicCol.MagicBase != 0 )
        {
            MagicBase = NeedMagic->MagicCol.MagicBase;
            MagicLV   = NeedMagic->MagicCol.MagicLV;
        }
        else
        {
            MagicBase = NeedMagic->GUID;
            MagicLV   = 1;

        }

        IsFind = false;
        for( int j = 0 ; j < _MAX_NormalSkill_COUNT_ ; j++ )
        {
            if(     PlayerBaseData->Skill.MainJob[ j ].SkillID == MagicBase 
                &&  PlayerBaseData->Skill.MainJob[ j ].Point  >= MagicLV )
            {
                IsFind = true;
                break;
            }
        }

        if( IsFind == false )
            return false;
    }
*/
    return true;
}
//------------------------------------------------------------------------------------
//重設職業資料
void    RoleDataEx::ResetJobSkill( )
{/*
    GameObjDbStructEx	*MainJobMB = St_GetObjDB( Def_ObjectClass_LearnMagic + BaseData.Voc );    
    if( MainJobMB == NULL )
        return;

    for( int i = 0 ; i < _MAX_SPSkill_COUNT_ ; i++ )
    {
        PlayerTempData->Skill.SP[i].Point = 0;

        GameObjDbStructEx	*SkillDB =  St_GetObjDB( PlayerTempData->Skill.SP[i] );    
        if( SkillDB == NULL )
            continue;

//        if( PlayerBaseData->Skill.SP[i].Point != 0 )
//            continue;
        
        //檢查是否有 KeyItem
        int KeyItem = MainJobMB->LearnMagic.SPSkill[i].KeyItemID;
        int LearnLV   = MainJobMB->LearnMagic.SPSkill[i].LearnLV;

        if( LearnLV > Level() )
            continue;

        if( KeyItem != 0 )
        {
            if( BaseData.KeyItem.GetFlag( KeyItem - Def_ObjectClass_KeyItem ) == false )
            {
                continue;
            }
        }
        
        //PlayerTempData->Skill.SP[i].Point = 1;
        //SetValue( (RoleValueName_ENUM)( EM_RoleValue_SPMagic + i )  , 1 );
    
    }
*/
}
//------------------------------------------------------------------------------------
//檢查是否法術與位置資料與角色點術相符合
bool    RoleDataEx::CheckRoleMagic( int MagicID , int MagicPos )
{
	if( (unsigned)MagicPos >= _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_  )
		return false;

	if( PlayerTempData->Skill.AllSkill[ MagicPos ] != MagicID )
		return false;

    return true;
}
//------------------------------------------------------------------------------------
/*
//檢查是否法術與位置資料與角色點術相符合
bool    RoleDataEx::CheckRoleSPMagic( int MagicID , int MagicPos )
{
    if( MagicID != PlayerBaseData->Skill.SP[ MagicPos ].SkillID )
        return false;
    return true;
}
*/

//取得物件源始的主人
RoleDataEx* RoleDataEx::GetOrgOwner( )
{
    RoleDataEx* Owner = this;
    while( 1 )
    {
        if( Owner->OwnerGUID() == -1 )
            break;

        RoleDataEx* Temp = St_GetRoleData( Owner->OwnerGUID() );
        if( Temp == NULL )
            break;
        Owner = Temp;
    }
    return Owner;
}
//------------------------------------------------------------------------------------
//收尋愁恨的角色
RoleDataEx*    RoleDataEx::SearchHate( )
{
	GameObjDbStructEx* OrgDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( OrgDB->IsNPC() )
		return SearchHate( (float)(OrgDB->NPC.FollowRange) );
	return SearchHate( _DEF_NPC_FIGHT_RANGE_ );
}

RoleDataEx*    RoleDataEx::SearchHate( float Range )
{
	if( BaseData.Mode.Strikback == false )
		return NULL;

    RoleDataEx* HateRole;
    RoleDataEx* MaxHateRole = NULL;
    float         MaxHatePoint = 0;
    float         TempHatePoint;
    for( int i = 0 ; i < TempData.NPCHate.Hate.Size() ;  i++ )
    {		
        HateRole = St_GetRoleData( TempData.NPCHate.Hate[ i ].ItemID );
        if( HateRole == NULL || HateRole->IsDead() )
        {
            TempData.NPCHate.Hate.Erase( i );
            i--;
            continue;
        }

//		if( HateRole->GUID() == TargetID() )
//			continue;

		PathProcStruct& Move = TempData.Move;
		if( IsPlayer() == false )
		{
			if(     ( HateRole->X() - Move.RetX  )*( HateRole->X() - Move.RetX  )
				+	( HateRole->Z() - Move.RetZ  )*( HateRole->Z() - Move.RetZ  )        > Range*Range )
				continue;
		}

		if(CheckAttackable( HateRole ) == false /*|| CheckPhyAttack( HateRole) == false*/ )
		{
			continue;
		}

		float Len = Length( HateRole );

		if( Len >= 400 )
			continue;		

		if( Len < 50 + TempData.BoundRadiusY )
			Len = 50 + TempData.BoundRadiusY;

        TempHatePoint = TempData.NPCHate.Hate[ i ].TotalHatePoint() / float( Len ) ;
		if( TempHatePoint < 0.2f )
			TempHatePoint = 0.2f;

//		if( HateRole->TempData.Attr.Effect.Stop != false )
		if( HateRole->TempData.Attr.Effect.AI_LowAttackPriority != false )
		{
			TempHatePoint = TempHatePoint /1000;
			//Len += 1000;
		}

        if( MaxHateRole == NULL || MaxHatePoint < TempHatePoint  )
        {
            MaxHateRole = HateRole;
            MaxHatePoint = TempHatePoint;
        }        
    }
    return MaxHateRole;
}
//------------------------------------------------------------------------------------
//搜尋新的目標 找不到就停止攻擊
/*
bool		RoleDataEx::FindNewHateTarget( )
{
	GameObjDbStructEx* OrgDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( OrgDB->IsNPC() )
		return FindNewHateTarget( (float)(OrgDB->NPC.FollowRange) );
	return FindNewHateTarget( _DEF_NPC_FIGHT_RANGE_ );
}
/*
bool		RoleDataEx::FindNewHateTarget( float Range )
{
	if( !IsNPC() )
		return false;

	if( IsAttack() == false )
		return false;

	RoleDataEx* Target = SearchHate( Range );
	if( Target == NULL )
	{
		PathProcStruct& Move = _Owner->TempData.Move;

		if( Move.RetX != 0 || Move.RetY != 0 || Move.RetZ != 0 )
		{
			_OwnerObj->Path()->Target( Move.RetX , Move.RetY , Move.RetZ );

			_Owner->SetValue( EM_RoleValue_HP , _Owner->TempData.Attr.Fin.MaxHP );
			_Owner->SetValue( EM_RoleValue_MP , _Owner->TempData.Attr.Fin.MaxMP );

			_Owner->ClearAllBuff();		

			_Owner->AssistMagic( _Owner , RoleDataEx::BaseMagicList[ EM_BaseMagic_Unbeatable ] , 0 , 5 );			
		}

		SetAtkFolOff( );
		return false;
	}
	SetAttack( Target );

	return true;
}
*/
//取得ＨＱ品的額外增加機率
int		RoleDataEx::GetHQExtraValue( SkillValueTypeENUM SkillType )
{
	switch( SkillType )
	{
	case EM_SkillValueType_BlackSmith:	
		return int(TempData.Attr.Fin.SkillValue.BlackSmith);
	case EM_SkillValueType_Carpenter:	
		return int(TempData.Attr.Fin.SkillValue.Carpenter);
	case EM_SkillValueType_MakeArmor:
		return int(TempData.Attr.Fin.SkillValue.MakeArmor);
	case EM_SkillValueType_Tailor:
		return int(TempData.Attr.Fin.SkillValue.Tailor);
	case EM_SkillValueType_Cook:
		return int(TempData.Attr.Fin.SkillValue.Cook);
	case EM_SkillValueType_Alchemy:
		return int(TempData.Attr.Fin.SkillValue.Alchemy);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------
//下線有計算的Buff or Coldown處理
void	RoleDataEx::ProcOffLineTime()
{
	//__time32_t格式
	int		OffLineTime = RoleDataEx::G_Now - Base.LogoutTime;
	if( OffLineTime < 0 )
		OffLineTime = 0;

	//StaticVector< RefineBuffStruct , _MAX_REFINE_BUFF_COUNT_ > RefineColdown; //合成Buff

	//法術Coldown處理
	BaseData.Coldown.NeedUpdatePos.Clear();
	for( int i = 0 ; i < DEF_MAX_COLDOWN_COUNT_ALL ; i++ )
	{
		if( BaseData.Coldown.All[i] <= OffLineTime )
		{
			BaseData.Coldown.All[i] = 0;
		}
		else
		{
			BaseData.Coldown.All[i] -= OffLineTime;
			BaseData.Coldown.NeedUpdatePos.Push_Back( i );
		}
	}
	
	//合成Buff
	for( int i = 0 ; i < PlayerBaseData->RefineColdown.Size() ; i++ )
	{
		if( PlayerBaseData->RefineColdown[i].Coldown <= OffLineTime )
		{
			PlayerBaseData->RefineColdown[i].Coldown = 0;
			PlayerBaseData->RefineColdown[i].RecipeID = 0;
			PlayerBaseData->RefineColdown.Erase( i );
			i--;
		}
		else
		{
			PlayerBaseData->RefineColdown[i].Coldown -= OffLineTime;

		}
	}

	//Buff檢查
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		GameObjDbStruct* MagicBaseDB = BaseData.Buff[i].Magic;
		if( MagicBaseDB->MagicBase.Setting.OfflineBuffTime == false )
			continue;
		BaseData.Buff[i].Time -= OffLineTime;
	}

	for( int i = 0 ; i < _MAX_REALTIME_FLAG_ ; i++ )
	{
		PlayerBaseData->RealTimeFlag[i] -= (OffLineTime/60);
		if( PlayerBaseData->RealTimeFlag[i] <= 0 )
			PlayerBaseData->RealTimeFlag[i] = -1;
	}
	for( int i = 0 ; i < _MAX_PLAYTIME_FLAG_ ; i++ )
	{
		if( PlayerBaseData->PlayTimeFlag[i] <= 0 )
			PlayerBaseData->PlayTimeFlag[i] = -1;
	}

	float famouseDesc = St_SysKeyValue()->TitleSys_FamouseDesc_Min * -1 * (OffLineTime/60); 
	AddValue( EM_RoleValue_TitleSys_Famous , famouseDesc );

}

//取得 OnlinePlayerInfoStruct 的資料
void	RoleDataEx::GetOnlinePlayerInfo( OnlinePlayerInfoStruct& Info )
{
	Info.DBID	 = DBID();
	Info.GUID	 = GUID();
	Info.Name	 = RoleName();
	if( TempData.Sys.OnChangeWorld == true )
		Info.ZoneID = -1;
	else
		Info.ZoneID  = ZoneID();
	Info.Account = Base.Account_ID;
	Info.IsShowTitle = BaseData.IsShowTitle;
	Info.TitleStr = PlayerBaseData->TitleStr;
	Info.Race	 = BaseData.Race;
	Info.Voc	 = BaseData.Voc;
	Info.Voc_Sub = BaseData.Voc_Sub;
	Info.Sex	 = BaseData.Sex;
	Info.Look	 = BaseData.Look;
	Info.LV		 = TempData.Attr.Level;
	Info.LV_Sub  = TempData.Attr.Level_Sub;
	Info.ProxyID = TempData.Sys.ProxyID;
	Info.SockID  = TempData.Sys.SockID;
	Info.GuildID = BaseData.GuildID;
	Info.TitleID = BaseData.TitleID;
	Info.State._State = TempData.Attr.AllZoneState._State;
	Info.Note	 = PlayerSelfData->FriendList.Note;
	Info.RoomID  = BaseData.RoomID;
	Info.ParallelID =  PlayerTempData->ParallelZoneID;
}


//魔法盾吸收計算 回傳吸收多少
int RoleDataEx::MagicShieldAbsorbProc( RoleDataEx* AttackRole , GameObjDbStruct* AtkMagic , int &Damage )
{
	if( Damage < 0 )
		return 0;

	if( AttackRole == NULL )
		AttackRole = this;

	int AbsorbDamage = 0;
	int TotalAbsorbDamage = 0;

	if(	TempData.Attr.AssistMagicSetting.MagicShield == false )
		return 0;

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{   
		BuffBaseStruct& Buff = BaseData.Buff[i];
		GameObjDbStruct* MagicBase = Buff.Magic;
		if( MagicBase == NULL )
			continue;

		if( MagicBase->MagicBase.Setting.MagicShield == false )
			continue;

		if(		AtkMagic == NULL 
			||	AtkMagic->MagicBase.EffectType == EM_Magic_Phy )
		{
			if(		MagicBase->MagicBase.MagicShield.Effect != EM_MagicShieldEffec_All 
				&&	MagicBase->MagicBase.MagicShield.Effect != EM_MagicShieldEffec_Phy )
				continue;
		}
		else if( AtkMagic->MagicBase.EffectType == EM_Magic_Magic )
		{
			switch( MagicBase->MagicBase.MagicShield.Effect )
			{
			case EM_MagicShieldEffec_All:			//所有攻擊
				break;
			case EM_MagicShieldEffec_Phy:			//物理攻擊
				continue;
			case EM_MagicShieldEffec_Magic:			//法術攻擊
				break;
			case EM_MagicShieldEffec_Earth:			//地系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Earth )
					continue;
				break;
			case EM_MagicShieldEffec_Water:    		//水系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Water )
					continue;
				break;
			case EM_MagicShieldEffec_Fire:     		//火系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Fire )
					continue;
				break;
			case EM_MagicShieldEffec_Wind:     		//風系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Wind )
					continue;
				break;
			case EM_MagicShieldEffec_Light:    		//光系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Light )
					continue;
				break;
			case EM_MagicShieldEffec_Darkness: 		//暗系法術攻擊
				if( MagicBase->MagicBase.MagicType != EM_MagicResist_Darkness )
					continue;
				break;
			}
		}		
		else
			continue;

		switch( MagicBase->MagicBase.MagicShield.Type )
		{
		case EM_MagicShieldType_MP:			//MP抵消HP
			if( Damage < BaseData.MP )
			{
				AddMP( AttackRole , float( Damage * -1 ) );
				AbsorbDamage = Damage;
				Damage = 0;
			}
			else
			{
				AbsorbDamage = int( BaseData.MP );
				Damage = Damage - int( BaseData.MP );
				AddMP( AttackRole , float( AbsorbDamage * -1 ) );
				Buff.Time = 0;
				Buff.IsErase = true;
			}				
			break;
		case EM_MagicShieldType_Times:		//抵消次數
			{
				if( Buff.Point <= 0 )
				{
					Buff.Time = 0;
					Buff.IsErase = true;
					break;
				}

				Buff.Point--;
				if( Buff.Point == 0 )
				{
					Buff.Time = 0;
					Buff.IsErase = true;
				}

				AbsorbDamage = Damage;
				Damage = 0;				
			}
			break;
		case EM_MagicShieldType_Point:		//抵消法數設定的點數
		case EM_MagicShieldType_Point_ByHealArg:

			if( Damage < Buff.Point )
			{
				Buff.Point -= Damage;
				AbsorbDamage = Damage;
				Damage = 0;
			}
			else
			{
				AbsorbDamage = Buff.Point;
				Damage = Damage - Buff.Point;
				Buff.Time = 0;
				Buff.Point = 0;
				Buff.IsErase = true;
			}	
			break;
		case EM_MagicShieldType_Percent:		//抵消次數
			{
				if( Buff.Point <= 0 )
				{
					Buff.Time = 0;
					Buff.IsErase = true;
					break;
				}

				int MaxDecPower = int( ((float)MaxHP() * Buff.Point) /100 );
				if( MaxDecPower > Damage )
				{
					Buff.Point -= int( Damage * 100.0f / MaxHP() + 0.99f );
					AbsorbDamage = Damage;
					Damage = 0;				
				}
				else
				{

					Buff.Point = 0;
					Buff.Time = 0;
					Buff.IsErase = true;
					AbsorbDamage = MaxDecPower;
					Damage -= MaxDecPower;
				}

			}
			break;

		}
		if( AbsorbDamage != 0 )
		{
			int AtkMagicGUID = 0;
			if( AtkMagic != NULL )
				AtkMagicGUID = AtkMagic->GUID;

			Net_MagicShieldInfoRange( AttackRole->GUID() , GUID() , AtkMagicGUID , Buff.BuffID , AbsorbDamage );
			TotalAbsorbDamage += AbsorbDamage;
		}

		if( Damage == 0 )
			break;
	}
	return  TotalAbsorbDamage;
}

//取得某技能上限物件
int		RoleDataEx::GetLifeSkillMax( SkillValueTypeENUM Type )
{
	if( (unsigned)Type >= EM_SkillValueType_MaxCount )
		return 0;

	int MaxLv = 0;
	GameObjDbStructEx	*Obj;
	for( int i = 0 ; i < (int)LifeSkillLearnKey[Type].size() ; i++ )
	{
		int KeyItemID = LifeSkillLearnKey[Type][i];
		if( CheckKeyItem( KeyItemID ) == false )
			continue;
		Obj = St_GetObjDB( KeyItemID );
		if( Obj == NULL )
			continue;
		if( MaxLv < Obj->KeyItem.LifeSkillMaxLV )
			MaxLv = Obj->KeyItem.LifeSkillMaxLV;
	}
	return MaxLv;
}
//////////////////////////////////////////////////////////////////////////
//清除PK 資料
void	RoleDataEx::SetPKOff(  )
{
	if( TempData.Attr.Action.PK == false )
	{
		PlayerTempData->PKInfo.Init();
		return;
	}

	//清除PK目標的buff
	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		if( BaseData.Buff[i].OwnerID == PlayerTempData->PKInfo.TargetID )
		{
			//Owner->BaseData.Buff.Erase( i );
			ClearBuffByPos( i );
			i--;
		}

	}

	TempData.Attr.Action.PK = false;
	PlayerTempData->PKInfo.Init();
	

}
//-------------------------------------------------------------------------------------------
//以目前的等級資料取得頭銜
void	RoleDataEx::GetTitle( )
{
	GameObjDbStructEx* ObjDB;
	for( int i = Def_ObjectClass_Title ; ; i++ )
	{
		ObjDB = St_GetObjDB( i );
		if( ObjDB->IsTitle() == false )
			break;
		if( ObjDB->Title.Type != EM_TitleNameType_Job )
			continue;

		if( CheckGetJobTitle( ObjDB->GUID ) == false )
			continue;

		/*
		if( ObjDB->Title.MainJob != BaseData.Voc || ObjDB->Title.MainJobLV > Level() )
			continue;

		if( ObjDB->Title.SubJob != EM_Vocation_None 
			&& (ObjDB->Title.SubJob != BaseData.Voc_Sub  || ObjDB->Title.SubJobLV > Level_Sub()) )
			continue;
			*/

		PlayerBaseData->Title.SetFlagOn( i - Def_ObjectClass_Title );
		
	}
}
//-------------------------------------------------------------------------------------------
//取得施法時間
float		RoleDataEx::GetSpellTime( GameObjDbStructEx* MagicDB  )
{
	if( MagicDB->IsMagicCollect() == false )
		return -1;

	if(		MagicDB->MagicCol.IsDisableSpellBuffEffect == false 
		&&	TempData.Attr.Effect.MagicSpell_ZeroTime )
		return 0;

	float SpellTime = MagicDB->MagicCol.SpellTime;

	SpellTime  = SpellTime * ( TempData.Attr.MagicSpellSpeed() );
	if( SpellTime < 0 )
		SpellTime = 0;
	return SpellTime;
}

//-------------------------------------------------------------------------------------------
float RoleDataEx::GetColdownTime( GameObjDbStructEx* MagicDB )
{
	float coldownTime = 0.0f;

	if ( MagicDB )
	{
		
		switch (MagicDB->Classification)
		{
		case EM_ObjectClass_Item:
			if ( MagicDB->Item.IncMagic_Onuse != 0 )		// 檢查物品是否有法術效果
				return GetColdownTime(St_GetObjDB(MagicDB->Item.IncMagic_Onuse));
			/*
			switch (MagicDB->Item.UseType)
			{
			case EM_ItemUseType_Magic:
				if ( MagicDB->Item.IncMagic_Onuse != 0 )		// 檢查物品是否有法術效果
					return GetColdownTime(St_GetObjDB(MagicDB->Item.IncMagic_Onuse));
				break;
			}*/

			break;

		case EM_ObjectClass_MagicCollect:
			coldownTime = float( MagicDB->MagicCol.Coldown.Time );
			if( coldownTime <= 0 )
			{
				if( MagicDB->MagicCol.Flag.ReferenceWeapon_Bow )
					coldownTime += TempData.Attr.Fin.Bow_ATKSpeed / 10.0f;
				else if ( MagicDB->MagicCol.Flag.ReferenceWeapon_Throw )
					coldownTime += TempData.Attr.Fin.Throw_ATKSpeed / 10;
			}
		}
	}

	return coldownTime;
}
//-------------------------------------------------------------------------------------------
//重設裝備的耐久度
void	RoleDataEx::ResetEqDurable()
{
	for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
	{
		if( BaseData.EQ.Item[i].IsEmpty()	)
			continue;

		if( BaseData.EQ.Item[i].Durable == 0)
		{
			BaseData.EQ.Item[i].Init();
			Net_FixItemInfo_EQ( i );
		}
	}
}
//-------------------------------------------------------------------------------------------
//裝備耐久損耗處理
bool		RoleDataEx::EqDurableProcess( EQWearPosENUM Pos , int DecDurable )
{
	if( IsPlayer() == false || TempData.Attr.Effect.EqProtect  )
		return false;

	if(		Pos == EM_EQWearPos_Ammo 
		||	Pos == EM_EQWearPos_Manufactory
		||	Pos == EM_EQWearPos_MagicTool1
		||	Pos == EM_EQWearPos_MagicTool2
		||	Pos == EM_EQWearPos_MagicTool3	)
		return false;

//	if( rand() % 3 == 0 )
//		return false;

	ItemFieldStruct* Item  = GetEqItem( Pos );
	if( Item->IsEmpty() )
		return false;

	if( Item->Durable <= 0 )
		return false;

	Item->Durable -= DecDurable;
	if( Item->Durable <= 0 )
	{
		TempData.UpdateInfo.Recalculate_All = true;
		Item->Durable = 0;
		Net_FixItemInfo_EQ( Pos );
	}
	else if( Item->Durable/100 != (Item->Durable+DecDurable) / 100 )
	{
		Net_FixItemInfo_EQ( Pos );
	}

	return true;
}
//-------------------------------------------------------------------------------------------
//某些事件增加Buf時間
void	RoleDataEx::OnEventAddBuffTime(  )
{
	MagicSpellFlagStruct Setting;
	Setting._Type = 0;

	if( TempData.UpdateInfo.OnAttackPlayer != false )
		Setting.OnPlayerAttackAddTime = true;
	
	if( TempData.UpdateInfo.OnKill != false )
		Setting.OnKillAddTime = true;

	if( Setting._Type == 0 )
		return;

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		BuffBaseStruct& Buff = BaseData.Buff[i];
		GameObjDbStruct* MagicBase = Buff.Magic;
		if( MagicBase == NULL )
			continue;

		if( ( MagicBase->MagicBase.Setting._Type & Setting._Type ) == 0 )
			continue;
		if( MagicBase->MagicBase.AddBuffTime > Buff.Time )
		{
			Buff.Time = MagicBase->MagicBase.AddBuffTime;
			Net_FixAssistMagicTime( Buff.BuffID , Buff.Time , Buff.OwnerID );
		}
	}

}

//設定攻擊延遲
void		RoleDataEx::SetDelayAttack( int Time )
{
	if( RoleDataEx::G_Clock >= TempData.AI.NextMainAtk + Time )
	{
		TempData.AI.NextMainAtk = RoleDataEx::G_Clock + Time;
	}
	if( RoleDataEx::G_Clock >= TempData.AI.NextSecAtk + Time )
	{
		TempData.AI.NextSecAtk = RoleDataEx::G_Clock + Time;
	}
}

//把所有Itme Queue內的東西堆入身上
void		RoleDataEx::ItemQueueToBody()
{
	for( int i = 0 ; i < PlayerBaseData->ItemTemp.Size() ; i++ )
	{
		ItemFieldStruct& TempItem = PlayerBaseData->ItemTemp[i];

		GameObjDbStructEx* TempItemDB = St_GetObjDB( TempItem.OrgObjID );
		if( TempItemDB == NULL )
			continue;

		for( int j = 0 ; j < PlayerBaseData->Body.Count ; j++ )
		{
			ItemFieldStruct& BodyItem = PlayerBaseData->Body.Item[j];

			if( BodyItem.IsEmpty() )
			{
				BodyItem = TempItem;
				break;
			}
			else if( BodyItem.OrgObjID == TempItem.OrgObjID 
				&& TempItemDB->MaxHeap >= TempItem.Count + BodyItem.Count )
			{
				BodyItem.Count += TempItem.Count;
				break;
			}			
		}
	}
}

//-------------------------------------------------------------------------------------------
//善惡等級
GoodEvilTypeENUM	RoleDataEx::GetGoodEvilType( )
{
	int Type;// = (PlayerBaseData->GoodEvil + 30)/60;

	if( BaseData.SysFlag.IsDemon )
		Type = -4;
	else if( BaseData.SysFlag.IsHero )
		Type = 4;
	else
	{
		Type = int( (PlayerBaseData->GoodEvil )/30);
		if( Type < 0 )
			Type = (Type -1)/2;
		else
			Type = (Type + 1 )/2;
		if( Type < EM_GoodEvil_Evil3 )
			Type = EM_GoodEvil_Evil3;
		else if( Type > EM_GoodEvil_Good3 )
			Type = EM_GoodEvil_Good3;
	}
	
	return (GoodEvilTypeENUM)Type;
}
//////////////////////////////////////////////////////////////////////////
//裝備符文融鍊系統
//////////////////////////////////////////////////////////////////////////
//裝備容解 ==> 魔石
bool	RoleDataEx::SmeltEqtoMagicStone( ItemFieldStruct* EQ , ItemFieldStruct* Item , ItemFieldStruct* outResultItem )
{
	GameObjDbStructEx* EQDB = St_GetObjDB( EQ->OrgObjID );
	GameObjDbStructEx* ItemDB = St_GetObjDB( Item->OrgObjID );

	if(		ItemDB->IsItem() == false 
		||	(EQDB->IsArmor() == false && EQDB->IsWeapon() == false ) )
		return false;

	if( EQDB->IsWeapon() && EQDB->Item.WeaponType >= EM_Weapon_Ammo_Bow )
		return false;

	if( EQDB->IsArmor() && EQDB->Item.ArmorPos == EM_ArmorPos_MagicTool )
		return false;
		
	if( ItemDB->Item.ItemType != EM_ItemType_SmeltStone )
		return false;

	if( (unsigned)EQDB->Rare >= 10  )
		return false;

	unsigned ResultLv = (EQDB->Limit.Level - 1 +  RoleDataEx::RareAddLv( EQDB->Rare+Item->Rare )*3/2 ) / 20;

	if( ResultLv >= unsigned( St_SysKeyValue()->MagicStoneCount ) )
		return false;

	outResultItem->Init();
	outResultItem->OrgObjID = outResultItem->ImageObjectID = St_SysKeyValue()->MagicStoneStart + ResultLv;
	outResultItem->Count = 1;
	outResultItem->Mode.Trade = true;


	vector<ItemFieldStruct*> AbilityList;
	AbilityList.push_back( EQ );
	AbilityList.push_back( Item );
	SelectAbility( AbilityList , outResultItem );	


	return true;
}
//精煉 魔石(升等)
bool	RoleDataEx::RefineMagicStone( ItemFieldStruct* Item[3] , ItemFieldStruct* outResultItem )
{
	if( Item[0] == NULL )
		return false;

	int Count = 1;

	for( int i = 1 ; i < 3 ; i++ )
	{
		if( Item[i] == NULL )
			break;

		if( Item[0]->OrgObjID != Item[i]->OrgObjID )
			return false;

		Count++;
	}

	unsigned	StoneLv = Item[0]->OrgObjID - St_SysKeyValue()->MagicStoneStart;
	if( StoneLv >= unsigned( St_SysKeyValue()->MagicStoneCount - 1 ) )
		return false;

	if( Count == 3 )
		StoneLv++;

	outResultItem->Init();
	outResultItem->OrgObjID = outResultItem->ImageObjectID = St_SysKeyValue()->MagicStoneStart + StoneLv;
	outResultItem->Count = 1;
	outResultItem->Mode.Trade = true;

	vector<ItemFieldStruct*> AbilityList;
	AbilityList.push_back( Item[0] );
	AbilityList.push_back( Item[1] );
	AbilityList.push_back( Item[2] );
	SelectAbility( AbilityList , outResultItem );	

	return true;
}
//裝備 與魔石熔合
bool	RoleDataEx::CombinEQandMagicStone       (  ItemFieldStruct* EQ , ItemFieldStruct* MagicStone[3] , ItemFieldStruct* outResultItem  )
{
	GameObjDbStructEx* EQDB = St_GetObjDB( EQ->OrgObjID );
	if(	EQDB->IsArmor() == false && EQDB->IsWeapon() == false )
		return false;

	if( EQDB->Mode.DisablePowerQuality )
		return false;

	if( EQDB->IsWeapon() && EQDB->Item.WeaponType >= EM_Weapon_Ammo_Bow )
		return false;

	if( EQDB->IsArmor() && EQDB->Item.ArmorPos == EM_ArmorPos_MagicTool )
		return false;


	//檢查魔法時
	int StornObjID = MagicStone[0]->OrgObjID;
	if( MagicStone[1]->OrgObjID != StornObjID || MagicStone[2]->OrgObjID != StornObjID  )
		return false;

	unsigned	StoneLv = StornObjID - St_SysKeyValue()->MagicStoneStart;

	if( StoneLv >= unsigned( St_SysKeyValue()->MagicStoneCount ) )
		return false;

	int WeaponLv = ( EQDB->Limit.Level -1 ) / 20;

	*outResultItem = *EQ;

	outResultItem->PowerQuality = 10 + StoneLv - WeaponLv;
	if( outResultItem->PowerQuality  < 10 )
		outResultItem->PowerQuality  = 10; 

	vector<ItemFieldStruct*> AbilityList;
	AbilityList.push_back( EQ );
	AbilityList.push_back( MagicStone[0] );
	AbilityList.push_back( MagicStone[1] );
	AbilityList.push_back( MagicStone[2] );
	SelectAbility( AbilityList , outResultItem );	


	return true;
}

//符文轉換
bool	RoleDataEx::RuneTransfer( ItemFieldStruct* Rune1 , ItemFieldStruct* Rune2 , ItemFieldStruct* outResultItem )
{
	GameObjDbStructEx* RuneDB1 = St_GetObjDB( Rune1->OrgObjID );	
	GameObjDbStructEx* RuneDB2 = St_GetObjDB( Rune2->OrgObjID );	

	GameObjDbStructEx*	NewRuneDB = St_RuneExchange( RuneDB1 , RuneDB2 ); 
	if( NewRuneDB == NULL || Rune1->Count != Rune2->Count )
		return false;

	outResultItem->Init();
	outResultItem->OrgObjID = outResultItem->ImageObjectID = NewRuneDB->GUID;
	outResultItem->Count = Rune1->Count;
	return true;
}

//符文升等
bool	RoleDataEx::RefineRune( ItemFieldStruct* Rune , ItemFieldStruct* outResultItem  )
{
	if( Rune->Count % 5 != 0 )
		return false;

	GameObjDbStructEx* RuneDB = St_GetObjDB( Rune->OrgObjID );	
	
	GameObjDbStructEx*	NewRuneDB = St_NextRuneLv( RuneDB ); 
	if( NewRuneDB == NULL )
		return false;

	outResultItem->Init();
	outResultItem->OrgObjID = outResultItem->ImageObjectID = NewRuneDB->GUID;
	outResultItem->Count = Rune->Count/5;

	if( outResultItem->Count == 0 )
		return false;

	return true;	
}
//////////////////////////////////////////////////////////////////////////
//物品融合兌換
bool	RoleDataEx::ItemCombine( vector< ItemFieldStruct >& ItemList , ItemFieldStruct* outResultItem )
{
	ItemCombineStruct info;
	info.Init();
	{
		map< int , int > fixInfoMap;
		int i;
		for( i = 0 ; i < ItemList.size() ; i++ )
		{
			fixInfoMap[ ItemList[i].OrgObjID ] += ItemList[i].Count;
		}

		map< int , int >::iterator iter;
		for( i = 0 , iter = fixInfoMap.begin() ; iter != fixInfoMap.end() ; iter++ , i++ )
		{
			info.SourceCount[i] = iter->second;
			info.SourceID[i] = iter->first;
		}
	}
	int hashID = GetHashCode( &info , sizeof( info ) );

	//////////////////////////////////////////////////////////////////////////
	//查後台資料表
	//////////////////////////////////////////////////////////////////////////
	map< int , vector< ItemCombineStruct > >::iterator iter;

	iter = ItemCombineListEx[ ItemCombineListExGroupID ].find( hashID );
	if( iter == ItemCombineListEx[ ItemCombineListExGroupID ].end() )
	{
		iter = ItemCombineList.find( hashID );
		if( iter == ItemCombineList.end() )
			return false;	
	}
	
	vector< ItemCombineStruct >& infoList = iter->second;
	for( unsigned i = 0 ; i < infoList.size() ; i++ )
	{
		bool IsOk = true;
		for( int j = 0 ; j < 5 ; j++ )
		{
			if(		infoList[i].SourceID[j] != info.SourceID[j]
				||	infoList[i].SourceCount[j] != info.SourceCount[j] )
			{
				IsOk = false;
				break;
			}
		}
		if( IsOk == true )
		{
			outResultItem->Init();
			outResultItem->OrgObjID = outResultItem->ImageObjectID = infoList[i].ProductID;
			outResultItem->Count = infoList[i].ProductCount;

			GameObjDbStructEx* ItemDB = St_GetObjDB( outResultItem->OrgObjID );
			if( ItemDB->IsItem() )
			{
				outResultItem->Mode.Trade = !(ItemDB->Mode.PickupBound);
			}

			return true;
		}
	}


	return false;
}
//////////////////////////////////////////////////////////////////////////
//魔法盒煉化
bool	RoleDataEx::MagicBoxSmelt( ItemFieldStruct* outResultItem )
{

	vector< ItemFieldStruct >	RuneItem;
	vector< ItemFieldStruct >	MagicStoneItem;
	vector< ItemFieldStruct >	AllItem;


	ItemFieldStruct	*EQItem = NULL;
	ItemFieldStruct	*SmeltItem = NULL;

	//////////////////////////////////////////////////////////////////////////
	for( int i = 0 ; i < 5 ; i++ )
	{
		if( PlayerBaseData->Body.ItemMagicBox[i].Count == 0 )
			continue;

		GameObjDbStructEx* ItemDB = St_GetObjDB( PlayerBaseData->Body.ItemMagicBox[i].OrgObjID );
		if( ItemDB == NULL  )
			continue;

		if( ItemDB->Mode.DisableMagicBox == true )
			return false;

		if( PlayerBaseData->Body.ItemMagicBox[i].Mode.ItemLock != false )
		{
			Net_GameMsgEvent( EM_GameMessageEvent_Item_ItemLock );
			return false;
		}


		AllItem.push_back( PlayerBaseData->Body.ItemMagicBox[i] );
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//物品融合系統
	//////////////////////////////////////////////////////////////////////////
	if( ItemCombine( AllItem , outResultItem ) == true )
	{
		return true;
	}
	//////////////////////////////////////////////////////////////////////////

	for( int i = 0 ; i < 5 ; i++ )
	{
		if( PlayerBaseData->Body.ItemMagicBox[i].Count == 0 )
			continue;

		GameObjDbStructEx* ItemDB = St_GetObjDB( PlayerBaseData->Body.ItemMagicBox[i].OrgObjID );
		if( ItemDB == NULL  )
			continue;

		if( PlayerBaseData->Body.ItemMagicBox[i].Mode.ItemLock != false )
		{
			Net_GameMsgEvent( EM_GameMessageEvent_Item_ItemLock );
			return false;
		}
		
		if( ItemDB->IsRune() )
		{
			bool IsInsert = true;
			for( unsigned j = 0 ; j < RuneItem.size() ; j++ )
			{
				if( RuneItem[j].OrgObjID == ItemDB->GUID )
				{
					RuneItem[j].Count += PlayerBaseData->Body.ItemMagicBox[i].Count;
					IsInsert = false;

					break;
				}
			}
			if( IsInsert != false )
			{
				RuneItem.push_back( PlayerBaseData->Body.ItemMagicBox[i] );
			}
		}
		else if( ItemDB->IsArmor() || ItemDB->IsWeapon() )
		{
			if( EQItem != NULL )
				return false;
			EQItem = &PlayerBaseData->Body.ItemMagicBox[i];
		}
		else if( ItemDB->Item.ItemType == EM_ItemType_SmeltStone )
		{
			if( SmeltItem != NULL )
				return false;
			SmeltItem = &PlayerBaseData->Body.ItemMagicBox[i];
		}
		else 
		{
			unsigned	StoneLv = ItemDB->GUID - St_SysKeyValue()->MagicStoneStart;

			if( StoneLv >= unsigned( St_SysKeyValue()->MagicStoneCount ) )
				return false;

			MagicStoneItem.push_back( PlayerBaseData->Body.ItemMagicBox[i] );
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool	Result = false;
/*
	if( EQItem != NULL )
	{
		GameObjDbStructEx* EQItemObj = St_GetObjDB( EQItem->OrgObjID );
		if( EQItemObj->IsArmor() && EQItemObj->Item.ArmorPos == EM_ArmorPos_Ornament )
		{
			return false;
		}
	}
*/
	//裝備容解 ==> 魔石
	if( EQItem != NULL && SmeltItem != NULL && RuneItem.size() == 0 && MagicStoneItem.size() == 0 )
	{
		Result = SmeltEqtoMagicStone( EQItem  , SmeltItem , outResultItem );
	}
	//////////////////////////////////////////////////////////////////////////
	//精煉 魔石(升等)
	if( Result == false &&  EQItem == NULL && SmeltItem == NULL && RuneItem.size() == 0 && MagicStoneItem.size() == 3 )
	{
		ItemFieldStruct* Item[3];		
		Item[0] = &MagicStoneItem[0];
		Item[1] = &MagicStoneItem[1];
		Item[2] = &MagicStoneItem[2];
		Result = RefineMagicStone( Item , outResultItem );
	}
	//////////////////////////////////////////////////////////////////////////
	//裝備 與魔石熔合
	if( Result == false &&  EQItem != NULL && SmeltItem == NULL && RuneItem.size() == 0 && MagicStoneItem.size() == 3 )
	{
		ItemFieldStruct* Item[3];		
		Item[0] = &MagicStoneItem[0];
		Item[1] = &MagicStoneItem[1];
		Item[2] = &MagicStoneItem[2];
		Result = CombinEQandMagicStone( EQItem , Item , outResultItem );
	}
	//////////////////////////////////////////////////////////////////////////
	//符文轉換
	if( Result == false &&  EQItem == NULL && SmeltItem == NULL && RuneItem.size() == 2 && MagicStoneItem.size() == 0 )
	{
		Result = RuneTransfer( &RuneItem[0] , &RuneItem[1] , outResultItem );
	}
	//////////////////////////////////////////////////////////////////////////
	//符文升等
	//////////////////////////////////////////////////////////////////////////
	if( Result == false &&  EQItem == NULL && SmeltItem == NULL && RuneItem.size() == 1 && MagicStoneItem.size() == 0 )
	{
		Result = RefineRune( &RuneItem[0] , outResultItem );
	}

	GameObjDbStructEx* ItemDB = St_GetObjDB( outResultItem->OrgObjID );
	if( ItemDB == NULL )
		return false;

	if( outResultItem->Serial == 0 )
	{
		if( ItemDB->IsItem() )
		{
			outResultItem->Mode.Trade = !(ItemDB->Mode.PickupBound);
		}
		if( ItemDB->MaxHeap < outResultItem->Count )
		{
			outResultItem->Init();
			Result = false;
		}
	}
	
	return Result;
}
//////////////////////////////////////////////////////////////////////////
//刪除身上物品
bool	RoleDataEx::DelBodyItem_ByPos( int Pos , int Count , ActionTypeENUM Type )
{
	ItemFieldStruct* Item = GetBodyItem( Pos );

	if( Item == NULL || Item->Count < Count )
		return false;

	Log_ItemDestroy( Type , *Item , Count , "" );

	Item->Count -= Count;
	if( Item->Count <=0 )
		Item->Init();

	Net_FixItemInfo_Body( Pos );

	return true;

}
//////////////////////////////////////////////////////////////////////////
void	RoleDataEx::SelectAbility( vector<ItemFieldStruct*>& AbilityList , ItemFieldStruct* outResultItem )
{
	set<int>					AbilitySet;
	vector< BaseSortStruct >	SortList;
	BaseSortStruct SortTemp;

	GameObjDbStructEx* EQDB = St_GetObjDB( outResultItem->OrgObjID );
	if( EQDB == NULL )
		return;


	for( unsigned i = 0 ; i < AbilityList.size() ; i++ )
	{
		for( unsigned j = 0 ; j < 6 ; j++ )
		{
			GameObjDbStructEx* AbilityDB = St_GetObjDB( AbilityList[i]->Inherent(j) );
			if( AbilityDB->IsAttribute() == false )
				continue;
			if( AbilityDB->Attirbute.InherentValue == -1 && outResultItem->OrgObjID != AbilityList[i]->OrgObjID )
			{
				continue;
			}
			if( EQDB->CheckInherentAbility( AbilityDB->Attirbute.AddPos , false ) == false )
				continue;
			/*
			if( EQDB->CheckInherentAbility( AbilityDB , false ) == false )
			{
				continue;
			}*/

			if( AbilitySet.insert( AbilityDB->GUID).second == false )
				continue;

			SortTemp.Value = AbilityDB->Attirbute.InherentValue;
			SortTemp.Data = AbilityDB;
			SortList.push_back( SortTemp );		
		}
	}

	sort( SortList.begin() , SortList.end() );

	for( unsigned i = 0 ; i < SortList.size() && i < 6 ; i++ )
	{
		GameObjDbStructEx* AbilityDB = (GameObjDbStructEx*)SortList[i].Data;
		outResultItem->Inherent( i , AbilityDB->GUID );
	}
}

//計算有幾個空位
int		RoleDataEx::EmptyPacketCount( )
{
	int RetCount = 0;
	for( int i = _MAX_BODY_BEGIN_POS_ ; i < PlayerBaseData->Body.Count ; i++ )
	{	
		if( CheckItemPosTimeFlag( 0 , i ) == false )
			continue;
		if( PlayerBaseData->Body.Item[i].IsEmpty() )
			RetCount++;
	}

	RetCount = __min( _MAX_TEMP_COUNT_ - PlayerBaseData->ItemTemp.Size() , RetCount );
	return RetCount;
}

int RoleDataEx::MaxJobLv()
{
	int MaxLv = 0;
	for( int i = 0 ; i < EM_Max_Vocation ; i++ )
	{
		if( PlayerBaseData->AbilityList[i].Level > MaxLv )
		{
			MaxLv = PlayerBaseData->AbilityList[i].Level;
		}
	}
	return MaxLv;
}


void	RoleDataEx::ResetLockAccountMoney(  )
{
	int LockAccountTime = ( RoleDataEx::G_Now + RoleDataEx::G_TimeZone * 60 *60 ) /(60*60*24);
	int Day = LockAccountTime - PlayerBaseData->LockAccountTime;

	if( Day >= Def_AccountMoneyLockTime_Max_Count_ )
	{
		memset( PlayerBaseData->LockAccountMoney , 0 , sizeof( PlayerBaseData->LockAccountMoney ) );
		PlayerTempData->LockAccountMoney = 0;
		TempData.UpdateInfo.AccountMoneyLockInfoChange = true;
	}
	else if( Day > 0  )
	{
		
		//for( int i = Def_AccountMoneyLockTime_Max_Count_- Day -1 ; i >= 0 ; i-- )
		for( int i = 0 ; i < Def_AccountMoneyLockTime_Max_Count_- Day ; i++  )
		{
			PlayerBaseData->LockAccountMoney[i] = PlayerBaseData->LockAccountMoney[i+Day];
			//PlayerTempData->LockAccountMoney += PlayerBaseData->LockAccountMoney[i+Day];
		}
		for( int i = Def_AccountMoneyLockTime_Max_Count_- Day ; i < Def_AccountMoneyLockTime_Max_Count_ ; i++ )
			PlayerBaseData->LockAccountMoney[ i ] = 0;

		TempData.UpdateInfo.AccountMoneyLockInfoChange = true;
	}
	
	int AccountMoney = PlayerBaseData->Body.Money_Account;
	AccountMoney -= PlayerBaseData->LockAccountMoney_Forever;
	PlayerTempData->LockAccountMoney = PlayerBaseData->LockAccountMoney_Forever;
	if( AccountMoney < 0 )
	{
		PlayerBaseData->LockAccountMoney_Forever += AccountMoney;
		AccountMoney = 0;
	}

	for( int i = 0 ; i < Def_AccountMoneyLockTime_Max_Count_ ; i++ )
	{
		PlayerTempData->LockAccountMoney += PlayerBaseData->LockAccountMoney[i];
		AccountMoney -= PlayerBaseData->LockAccountMoney[i];
		if( AccountMoney <0 )
		{
			PlayerBaseData->LockAccountMoney[i] += AccountMoney;
			AccountMoney = 0;
		}
	}

	if( PlayerTempData->LockAccountMoney > PlayerBaseData->Body.Money_Account ) 
		PlayerTempData->LockAccountMoney = PlayerBaseData->Body.Money_Account;

	PlayerBaseData->LockAccountTime = LockAccountTime;
	
}

FixFightArgumentStruct&   RoleDataEx::FixArg()     //固定參數表
{
	return TempData.Attr.FixArg();
}

//取得攻防影響等級差
int RoleDataEx::CalAddDotMagicLv( RoleDataEx* Target , GameObjDbStructEx* MagicBaseObjDB , int SpellTime , int OrgMagicLv )
{

	RoleDataEx* Owner = this;

	if( MagicBaseObjDB->MagicBase.Setting.FixDotPower )
		return 0;

	if( Owner->BaseData.Mode.RelyOwnerPower != false )
	{
		RoleDataEx* MasterOwner = St_GetRoleData( Owner->OwnerGUID() );
		if( MasterOwner != NULL )
			Owner = MasterOwner;
	}	

	DotMagicStruct& DotMagic = MagicBaseObjDB->MagicBase.DotMagic;
	if(		MagicBaseObjDB->MagicBase.Setting.DotMagic != true 
		||	(	DotMagic.Type != EM_DotMagicType_HP 
		&&		DotMagic.Type != EM_DotMagicType_MP ) )
		return 0;

	if( DotMagic.DotSkillLVArg == 0 )
		return 0;

	int DotTimes = int( MagicBaseObjDB->MagicBase.EffectTime / DotMagic.Time );
	if( DotTimes <= 1 )
		DotTimes = 1;
	float FinDmg;

	float DotBasePower = DotMagic.Base *( 1.0f + OrgMagicLv * DotMagic.DotSkillLVArg * 0.01f );

	float ExRate = 1;
	if( IsPlayer() )
	{
		ExRate = 0.6f + ( abs( DotBasePower) / 600 );
	}

	//計算攻防比
	if( MagicBaseObjDB->MagicBase.EffectType == EM_Magic_Magic )
	{
		float Power;
		if( DotMagic.Base < 0 )
			Power = DotBasePower- ExRate * Owner->TempData.Attr.Fin.MDMG * SpellTime * FixArg().MDmg_DotArg / DotTimes;
		else
			Power = DotBasePower + ExRate * Owner->TempData.Attr.Fin.MDMG * SpellTime * FixArg().Dmg_HealDotArg / DotTimes;

		float PowerRate = 1;

		float OAtk = ( Owner->TempData.Attr.Fin.MATK + 100 );
		float TDef = Target->TempData.Attr.Fin.MDEF + 200;
		PowerRate = 1 + ( OAtk - TDef )/ __max(OAtk , TDef )/2;

		if( Power < 0 )
		{
			Power = Target->CalResistDMG( MagicBaseObjDB->MagicBase.MagicType , Power *DotTimes ) / DotTimes;
			Power *= PowerRate;
		}
		else
		{
			float MNDPower = Owner->TempData.Attr.Fin.MND * 0.3f *SpellTime / DotTimes;
			if( Power * 5 < MNDPower )
				Power = Power * 6;
			else
				Power = Power +  MNDPower;

//			Power += MNDPower;
			//Owner->TempData.Attr.Mid.BodyRate[EM_WearEqType_HealPowerRate] ) + Owner->TempData.Attr.Mid.Body[EM_WearEqType_HealPoint]
			Power = Power * Owner->TempData.Attr.Mid.BodyRate[EM_WearEqType_HealPowerRate] + Owner->TempData.Attr.Mid.Body[EM_WearEqType_HealPoint]*SpellTime/DotTimes;

			if( MagicBaseObjDB->MagicBase.SettingEx.IgnoreMagicAbsorb == false )
				Power = Power * ( 1 + Target->TempData.Attr.Mid.Body[EM_WearEqType_HealAbsorbRate]/100 ) + Target->TempData.Attr.Mid.Body[EM_WearEqType_HealAbsorb]/DotTimes;

			if( Power < 0 )
				Power = 0;
			
		}
		Power *= Owner->TempData.Attr.MagicPow( MagicBaseObjDB->MagicBase.MagicType );

		FinDmg = Power;
	}
	else 	if( MagicBaseObjDB->MagicBase.EffectType == EM_Magic_Phy )
	{
		float Power;
		if( DotMagic.Base < 0 )
			Power = DotBasePower -  ExRate * 3 * Owner->TempData.Attr.Fin.Main_DMG * SpellTime * FixArg().MDmg_DotArg *10 / Owner->TempData.Attr.Fin.Main_ATKSpeed/ DotTimes;
		else
			Power = DotBasePower + ExRate * Owner->TempData.Attr.Fin.Main_DMG * SpellTime * FixArg().Dmg_HealDotArg * 10 / Owner->TempData.Attr.Fin.Main_ATKSpeed/ DotTimes;

		float PowerRate = 1;

		float OAtk = ( Owner->TempData.Attr.Fin.ATK + 100 );
		float TDef = Target->TempData.Attr.Fin.DEF + 200;
		PowerRate = 1 + ( OAtk - TDef )/ __max(OAtk , TDef )/2;

		if( Power < 0 )
		{
			Power *= PowerRate;
		}

		FinDmg = Power;
	}
	else 
	{
		return 0;
	}

	float DeltaDmg = FinDmg - DotMagic.Base;
	float DSkillLvDmg  = DotMagic.Base * DotMagic.DotSkillLVArg / 100;
	if( DSkillLvDmg == 0 )
		return 0;

	return int( DeltaDmg / DSkillLvDmg - OrgMagicLv );
}

//保險處理
void	RoleDataEx::InsureProc ( )
{
	//if( TempData.Attr.Effect.Insure != false )
	{
		BaseData.HP = TempData.Attr.Fin.MaxHP;
		//Buff清除
		for( int i =  BaseData.Buff.Size() -1  ; i >= 0 ; i-- )
		{
			BuffBaseStruct&		Buff	= BaseData.Buff[i];
			GameObjDbStructEx*  MagBuf	= St_GetObjDB( Buff.BuffID );
			if( MagBuf == NULL )
				continue;
			if( MagBuf->MagicBase.Effect.Insure != false )
			{
				ClearBuffByPos( i );
/*
				if(		MagBuf->MagicBase.OnBuffTimeOutMagicID != 0 
					&&	MagBuf->MagicBase.Setting.SpecialMagic != false )
				{
					MagicProcInfo  MagicInfo;
					MagicInfo.Init();
					MagicInfo.State = EM_MAGIC_PROC_STATE_PERPARE;
					MagicInfo.TargetID			= GUID();							//目標
					MagicInfo.MagicCollectID	= MagBuf->MagicBase.OnBuffTimeOutMagicID;		//法術
					St_SpellMagic( this ,  &MagicInfo , 0 );			
				}
				*/
				break;

			}
		}
	}
}

//刪除一個物品
bool	RoleDataEx::DelOneItem( int ItemPos , ItemFieldStruct& Item , ActionTypeENUM ActionType )
{
	if( Item.IsEmpty() )
		return false;

	Log_ItemDestroy( EM_ActionType_PKItemProtect , Item , 1 , "" );
	if( Item.Count <= 1 )
		Item.Init();
	else
		Item.Count--;

	Net_FixItemInfo_Body( ItemPos );		
	return true;
}

void	RoleDataEx::SwapEQ( int posID )
{
	if( unsigned(posID) >= _MAX_BACKUP_EQ_SET_COUNT_ )
		return;
	swap( BaseData.EQ , PlayerBaseData->EQBackup[posID] );
	swap( BaseData.EQ.Item[EM_EQWearPos_MagicTool1] , PlayerBaseData->EQBackup[posID].Item[EM_EQWearPos_MagicTool1] );
	swap( BaseData.EQ.Item[EM_EQWearPos_MagicTool2] , PlayerBaseData->EQBackup[posID].Item[EM_EQWearPos_MagicTool2] );
	swap( BaseData.EQ.Item[EM_EQWearPos_MagicTool3] , PlayerBaseData->EQBackup[posID].Item[EM_EQWearPos_MagicTool3] );
	TempData.UpdateInfo.Eq = true;
}

int		RoleDataEx::JobCount( )
{
	int RetCount = 0;
	for( int i = 0 ; i < EM_Max_Vocation ; i++ )
	{
		if( PlayerBaseData->AbilityList[i].Level > 0 )
			RetCount++;
	}
	return RetCount;
}

bool	RoleDataEx::OldUnPacket( ItemFieldStruct *SrvItem )
{
	//計算空位是否足夠
	int	ItemCount = 0;

	for( int i = 0 ; i < 4 ; i++ )
	{
		if( SrvItem->ItemIDList[i] == 0 || SrvItem->ItemCountList[i]  == 0 )
		{
			continue;
		}
		GameObjDbStructEx* OrgDB = St_GetObjDB( SrvItem->ItemIDList[i] );
		if( OrgDB == NULL )
			return false;

		ItemCount++;
	}

	if( ItemCount == 0 )
		return false;

	if( EmptyPacketCount() < ItemCount )
	{
		Net_GameMsgEvent( EM_GameMessageEvent_Item_EmptyPacketErr );
		return false;
	}


	for( int i = 0 ; i < 4 ; i++ )
	{
		if( SrvItem->ItemIDList[i] == 0 || SrvItem->ItemCountList[i]  == 0 )
			continue;

		ItemFieldStruct	Item;
		if( St_NewItemInit( Item , SrvItem->ItemIDList[i] , 0 ) == false )
		{
			continue;
		}

		GameObjDbStructEx* OrgDB = St_GetObjDB( Item.OrgObjID );

		if( OrgDB == NULL )
			continue;


		Item.Count		= SrvItem->ItemCountList[i];
		Item.OrgObjID	= SrvItem->ItemIDList[i] ;
		Item.OrgQuality = Item.Quality	= 100;
		Item.Durable	= Item.Quality * OrgDB->Item.Durable;
		Item.RuneVolume = 0;

		if( OrgDB->Mode.DurableStart0 != false )
			Item.Durable	= 0;

		if( OrgDB->IsArmor() || ( OrgDB->IsWeapon() && OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo ) )
		{
			Item.Count	  = 1;
		}

		if( GiveItem( Item , EM_ActionType_OpenPacket , this , "" ) == false )
			continue;

		if( OrgDB->Mode.DepartmentStore != false )
			Log_DepartmentStore	( Item , EM_ActionType_OpenPacket , Item.Count , 0 , 0 , 0 , DBID() );
	}
	return true;
}
bool	RoleDataEx::NewUnPacket( ItemFieldStruct *SrvItem )
{
	int	ItemCount = 0;
	//////////////////////////////////////////////////////////////////////////

	//計算空位是否足夠
	for( int i = 0 ; i < 8 ; i++ )
	{
		int	ItemID = SrvItem->IntAbility[i]/0x100;
		int Count  = SrvItem->IntAbility[i]%0x100;

		if( ItemID == 0 || Count  == 0 )
			continue;

		GameObjDbStructEx* OrgDB = St_GetObjDB( ItemID );
		if( OrgDB == NULL )
			return false;

		ItemCount++;
	}

	if( ItemCount == 0 )
		return false;

	if( EmptyPacketCount() < ItemCount )
	{
		Net_GameMsgEvent( EM_GameMessageEvent_Item_EmptyPacketErr );
		return false;
	}


	for( int i = 0 ; i < 8 ; i++ )
	{
		int	ItemID = SrvItem->IntAbility[i]/0x100;
		int Count  = SrvItem->IntAbility[i]%0x100;

		if( ItemID == 0 || Count == 0 )
			continue;

		ItemFieldStruct	Item;
		if( St_NewItemInit( Item , ItemID , 0 ) == false )
			continue;


		GameObjDbStructEx* OrgDB = St_GetObjDB( Item.OrgObjID );

		if( OrgDB == NULL )
			continue;


		Item.Count		= Count;
		Item.OrgObjID	= ItemID;
		Item.OrgQuality = Item.Quality	= 100;
		Item.Durable	= Item.Quality * OrgDB->Item.Durable;
		Item.RuneVolume = 0;

		if( OrgDB->Mode.DurableStart0 != false )
			Item.Durable	= 0;

		if( OrgDB->IsArmor() || ( OrgDB->IsWeapon() && OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo ) )
		{
			Item.Count	  = 1;
		}

		if( GiveItem( Item , EM_ActionType_OpenPacket , this , "" ) == false )
			continue;

		if( OrgDB->Mode.DepartmentStore != false )
			Log_DepartmentStore	( Item , EM_ActionType_OpenPacket , Item.Count , 0 , 0 , 0 , DBID() );
	}
	return true;
}
bool	RoleDataEx::UnPacket_DropList( ItemFieldStruct *SrvItem )
{
	//計算空位是否足夠
	//int EmptyPacketCount = EmptyPacketCount();
	int	ItemCount = 0;

	GameObjDbStructEx* ItemDB = St_GetObjDB( SrvItem->OrgObjID );
	if( ItemDB == NULL )
		return false;

	GameObjDbStructEx* TreasureDB = St_GetObjDB( ItemDB->Item.DropListPacket );
	if( TreasureDB->IsTreasure() == false )
		return false;
	

	for( int i = 0 ; i < TreasureDB->Treasure.ItemCount ; i++ )
	{
		if( TreasureDB->Treasure.Item[i].OrgID == 0 || TreasureDB->Treasure.Item[i].DropCount  == 0 )
			break;
		ItemCount++;
	}

	if( EmptyPacketCount() < ItemCount )
	{
		Net_GameMsgEvent( EM_GameMessageEvent_Item_EmptyPacketErr );
		return false;
	}


	for( int i = 0 ; i < TreasureDB->Treasure.ItemCount ; i++ )
	{
		if( TreasureDB->Treasure.Item[i].OrgID == 0 || TreasureDB->Treasure.Item[i].DropCount  == 0 )
			break;

		ItemFieldStruct	Item;
		if( St_NewItemInit( Item , TreasureDB->Treasure.Item[i].OrgID , 0 ) == false )
		{
			continue;
		}

		GameObjDbStructEx* OrgDB = St_GetObjDB( TreasureDB->Treasure.Item[i].OrgID  );

		if( OrgDB == NULL )
			continue;


		Item.Count		= TreasureDB->Treasure.Item[i].DropCount;
		Item.OrgObjID	= TreasureDB->Treasure.Item[i].OrgID;
		Item.OrgQuality = Item.Quality	= 100;
		Item.Durable	= Item.Quality * OrgDB->Item.Durable;
		Item.RuneVolume = 0;

		if( OrgDB->Mode.DurableStart0 != false )
			Item.Durable	= 0;

		if( OrgDB->IsArmor() || ( OrgDB->IsWeapon() && OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo ) )
		{
			Item.Count	  = 1;
		}

		if( GiveItem( Item , EM_ActionType_OpenPacket , this , "" ) == false )
			continue;

		if( OrgDB->Mode.DepartmentStore != false )
			Log_DepartmentStore	( Item , EM_ActionType_OpenPacket , Item.Count , 0 , 0 , 0 , DBID() );
		
	}
	return true;
}

void	RoleDataEx::FixItem( ItemFieldStruct *Item )
{
	GameObjDbStructEx* OrgDB = St_GetObjDB( Item->OrgObjID );

	if( OrgDB == NULL )
	{
		Item->Init();
		return;
	}


	Item->OrgQuality = Item->Quality	= 100;
	if( OrgDB->Mode.DurableStart0 == false )
		Item->Durable	= Item->Quality * OrgDB->Item.Durable;
	else
		Item->Durable	= 0;
	
	if( Item->Serial == 0 )
	{
		Item->CreateTime = RoleDataEx::G_Now;
		Item->Serial		= St_GenerateItemVersion( );
	}

	return;
}

int		RoleDataEx::HPMPSPSum()
{
	return int( BaseData.HP )+ int( BaseData.MP ) + int( BaseData.SP ) + int( BaseData.SP_Sub ) + MaxHP() + MaxMP();
}

//取得寵物資料
PetStruct*	RoleDataEx::GetPetInfo( RoleDataEx* Pet )
{
	static PetStruct EmptyPetStruct;
	EmptyPetStruct.Init();

	SummonPetTypeENUM	PetType = Pet->TempData.SummonPet.Type;
	if( (unsigned)PetType >= EM_SummonPetType_Max )
		return &EmptyPetStruct;

	PetStruct* PetInfo = &(TempData.SummonPet.Info[ PetType ]);
	if( PetInfo->PetID != Pet->GUID() )
		return &EmptyPetStruct;

	return PetInfo;
}

//取得到此等級的TP
int		RoleDataEx::GetLvTotalTP( int Lv )
{
	int TpExp = 0;
	//tp計算
	for( int i = 1 ; i < Lv ; i++ )
	{
		TpExp += RoleDataEx::JobExpTable[ i - 1 ]/10;
		TpExp += ( i* 100 + 1000 );
	}

	return TpExp;
}

void	RoleDataEx::GetRareEffect( GameObjDbStructEx* OrgDB , int AddRare , float& Dmg , float& MDmg , float& Def , float& MDef )
{
	Dmg = 0;
	MDmg = 0;
	Def = 0;
	MDef = 0;

	int RareDLv = RoleDataEx::RareAddLv( OrgDB->Rare + AddRare ) - RoleDataEx::RareAddLv( OrgDB->Rare );

	if( OrgDB->IsArmor() )
	{
	
		float BaseDef  = float( OrgDB->Item.Ability.EqTypeValue[0] /*- OrgDB->Item.DDef*/ ); 
		float BaseMDef = float( OrgDB->Item.Ability.EqTypeValue[1] /*- OrgDB->Item.DMDef*/ ); 
		Def = BaseDef;
		MDef = BaseMDef;

		float FixDefRate = 0;
		float FixMDefRate = 0;

		int Type = OrgDB->Item.ArmorType;
		int Pos = OrgDB->Item.ArmorPos;

		switch( Type )
		{
		case EM_Armor_HeavyArmed:
		case EM_Armor_LightArmed:
		case EM_Armor_Leather:
		case EM_Armor_Clothes:
		case EM_Armor_Robe:
			FixDefRate  = RoleDataEx::ArmorArg[0][ Pos ][ Type ];
			FixMDefRate = RoleDataEx::ArmorArg[1][ Pos ][ Type ];
			break;
		case EM_Armor_Shield:
			FixDefRate  = RoleDataEx::ArmorArg[0][ EM_ArmorPos_SecondHand ][ 0 ];
			FixMDefRate = RoleDataEx::ArmorArg[1][ EM_ArmorPos_SecondHand ][ 0 ];
			break;
		case EM_Armor_Implement:
			FixDefRate  = RoleDataEx::ArmorArg[0][ EM_ArmorPos_SecondHand ][ 1 ];
			FixMDefRate = RoleDataEx::ArmorArg[1][ EM_ArmorPos_SecondHand ][ 1 ];
			break;
		}

		for( int i = 0 ; i < RareDLv ; i++ )
		{
			Def = Def * 1.02f + FixDefRate * 0.1f;
			MDef = MDef * 1.02f + FixMDefRate * 0.1f;
		}
		Def -= BaseDef;
		MDef -= BaseMDef;

	}
	else if( OrgDB->IsWeapon() && OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo  )
	{
		float BaseDmg	= float( OrgDB->Item.Ability.EqTypeValue[0] /*- OrgDB->Item.DDmg */);
		float BaseMDmg	= float( OrgDB->Item.Ability.EqTypeValue[1] /*- OrgDB->Item.DMDmg */);
		
		Dmg = BaseDmg;
		MDmg = BaseMDmg;
		
		float FixDmgRate = 0.095838f * RoleValueData::WeaponBaseDmg[ OrgDB->Item.WeaponType ];
		float FixMDmgRate = 10.0f* RoleValueData::WeaponBaseMAtk[ OrgDB->Item.WeaponType ];
		
		for( int i = 0 ; i < RareDLv ; i++ )
		{
			Dmg = Dmg * 1.02f + FixDmgRate * OrgDB->Item.AttackSpeed;
			MDmg = MDmg * 1.02f + FixMDmgRate;
		}
		Dmg -= BaseDmg;
		MDmg -= BaseMDmg;

	}
}

//計算可以載多少人
int		RoleDataEx::CalCarryCount()
{
	if( IsPlayer() )
	{
		if( TempData.Attr.Effect.Ride == false )
			return 0;
		//Buff清除
		for( int i = 0 ; i <  BaseData.Buff.Size() ; i++ )
		{
			BuffBaseStruct&		Buff	= BaseData.Buff[i];
			GameObjDbStructEx*  MagBuf	= St_GetObjDB( Buff.BuffID );
			if( MagBuf == NULL )
				continue;

			if( MagBuf->MagicBase.Effect.Ride != false )
				return MagBuf->MagicBase.CarryCount;
		}
	}
	else
	{
		GameObjDbStructEx	*NpcObjDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
		if( NpcObjDB == NULL )
			return 0;
		return NpcObjDB->NPC.CarryCount;

	}

	return 0;
}
/*
//增加金錢(所有類型)
bool	RoleDataEx::AddMoneyBase( PriceTypeENUM Type , int Money )
{
//	if( CheckMoneyBase(Type , Money ) == false )
//		return false;

	switch( Type )
	{
	case EM_ACPriceType_GameMoney:
		{
			return AddBodyMoney( Money , NULL , EM_ActionType_Buy , true );
		}
		break;
	case EM_ACPriceType_AccountMoney:
		{
			return AddBodyMoney_Account( Money , NULL , EM_ActionType_Buy , true , true );
		}
		break;
	case EM_ACPriceType_BonusMoney:
		{
			return AddMoney_Bonus( Money , NULL , EM_ActionType_Buy );
		}
		break;
	case  EM_ACPriceType_Honor:
		{

			int Honor = int( PlayerBaseData->Honor - Money );
			SetValue( EM_RoleValue_Honor , Honor );
		}
		break;
	default:
		{
			char Buf[256];
			sprintf( Buf , "SYS_PRICETYPE_ICONID_%02d" , Type );
			//取出金錢類型
			int SPMoneyObjID = St_GetSysKeyValue( Buf );

			return DelBodyItem( SPMoneyObjID , Money , EM_ActionType_Buy );
		}
		break;
	}

	return false;
}
//檢查金錢(所有類型)
bool	RoleDataEx::CheckMoneyBase( PriceTypeENUM Type , int Money )
{
	if( Money < 0  )
	{
		//Print( LV5 , "NetSrv_ShopChild::R_BuyItemRequest" , "Buy ItemObjID = %d Money=%d" , OrgObjID , Money );
		return false;
	}

	switch( Type )
	{
	case EM_ACPriceType_GameMoney:
		{
			//計算價錢
			if( PlayerBaseData->Body.Money < Money )
				return false;
		}
		break;
	case EM_ACPriceType_AccountMoney:
		{
			if( PlayerBaseData->Body.Money_Account < Money )
				return false;
		}
		break;
	case EM_ACPriceType_BonusMoney:
		{
			if( PlayerBaseData->Money_Bonus < Money )
				return false;
		}
		break;
	case  EM_ACPriceType_Honor:
		{
			if( PlayerBaseData->Honor < Money )
				return false;
		}
		break;
	default:
		{
			char Buf[256];
			sprintf( Buf , "SYS_PRICETYPE_ICONID_%02d" , Type );
			//取出金錢類型
			int SPMoneyObjID = St_GetSysKeyValue( Buf );

			if( CalBodyItemCount(SPMoneyObjID) < Money  )
				return false;
		}
		break;
	}

	return true;

}
*/

SuitSkllBaseStruct* RoleDataEx::FindSuitSkill( int SkillID )
{
	SuitSkillStruct& SuitSkill = PlayerBaseData->SuitSkill;

	for( int i = 0 ; i < SuitSkill.LeanSkillCount ; i++ )
	{
		if( SuitSkill.LeanSkillList[i].SkillID == SkillID )
		{
			return &SuitSkill.LeanSkillList[i];
		}
	}
	
	return NULL;
}

bool RoleDataEx::FindSuitSkill_EQ( int SkillID )
{
	SuitSkillStruct& SuitSkill = PlayerBaseData->SuitSkill;

	for( int i = 0 ; i < SuitSkill.MaxEqSkillCount ; i++ )
	{
		if( SuitSkill.EQ[i] == SkillID )
		{
			return true;
		}
	}

	return false;
}
/*
void	RoleDataEx::PhantomChangeProc()
{
	PhantomStruct& info = PlayerBaseData->Phantom;
	
	INT64 id = info.EQ[0] + info.EQ[1] * 0x100000000;

	info.SkillID = PhantomSkill[ id ];
	if( info.SkillID )
		info.SkillLv = ( info.Info[ info.EQ[0]%1000 ].Lv + info.Info[ info.EQ[1]%1000 ].Lv ) /2;
	else
		info.SkillLv = 0;

    GameObjDbStructEx orgDB = St_GetObjDB( Item->OrgObjID );
	if( orgDB->IsMagicBase() )
	{
		
	}

}
*/
int RoleDataEx::KeyItemObjToID( int objID )
{
	if( objID >=Def_ObjectClass_KeyItemEx )
		return objID - Def_ObjectClass_KeyItemEx + 10000;
	else if( objID >=Def_ObjectClass_KeyItem  )
		return objID - Def_ObjectClass_KeyItem;
	return objID;
}

int RoleDataEx::IDtoKeyItemObj( int id )
{
	if( id < 10000 )
		return Def_ObjectClass_KeyItem + id;
	else
		return Def_ObjectClass_KeyItemEx + id - 10000;

}