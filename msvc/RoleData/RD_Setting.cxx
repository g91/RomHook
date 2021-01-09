#include "RoleDataEx.h"
#include <set>
//-----------------------------------------------------------------------------------------
void    RoleDataEx::ChangeZoneInit( )
{
	PlayerBaseData->Bank.Count = _MAX_BANK_COUNT_;
	TempData.Sys.SecRoomID = -1;
	TempData.Sys.SecX = -1;
	TempData.Sys.SecZ = -1;
	TempData.Sys.LoginProtect = 0;
	TempData.Sys.ChangeZoneTime = 0; //4000 + RoleDataEx::G_SysTime;
	TempData.Sys.MirrorCount = 0;
	TempData.LockHP = 0;
	TempData.SoulPoint = 0;
	memset( &TempData.AI , 0 , sizeof(TempData.AI) );
	PlayerTempData->PKInfo.Init();
	TempData.Attr.Action.PK = false;
	//	TempData.Sys.SockID = -1;
	BaseData.Mode.Fight = true;
	BaseData.Mode.Show = true;
	BaseData.Mode.Mark = true;
	BaseData.Mode.Gravity = true;
	BaseData.Mode.ShowRoleHead = true;
	BaseData.Mode.Move = true;
	TempData.Attr.FixArgTableID = 1;
	TempData.DeadZoneCountDown = 0;
	PlayerTempData->PartyLootOrder = clock();
	TempData.Magic.State = EM_MAGIC_PROC_STATE_NORMAL;
	TempData.Move.MoveType = EM_ClientMoveType_Normal;
	PlayerTempData->ChangeZoneCountDown  = 0;
	BaseData.Coldown.AllMagic = 0;

	memset( PlayerTempData->Skill.LuaSkill , 0 , sizeof( PlayerTempData->Skill.LuaSkill ) );


	BaseData.ZoneID = RoleDataEx::G_ZoneID;

	TempData.Attr.Ability = &PlayerBaseData->AbilityList[ BaseData.Voc ];
	TempData.Attr.SkillValue = &TempData.Attr.MaxSkillValue;

	PlayerTempData->Log.Init();
	PlayerTempData->Log.LastMoney = PlayerBaseData->Body.Money;
	PlayerTempData->Log.SavePlayTime =  BaseData.PlayTime;
	PlayerTempData->Log.LastMoney_Account = PlayerBaseData->Body.Money_Account;

	if( TempData.Attr.Action.Login )
		TempData.BackInfo.BuffClearTime.Logout = true;

	if( TempData.Attr.Action.ChangeZone != false  )
		TempData.BackInfo.BuffClearTime.ChangeZone = true;

	ResetLockAccountMoney();

	TempData.Magic.Init();
	memset( &PlayerTempData->BGInfo , 0 , sizeof( PlayerTempData->BGInfo ) );
	memset( PlayerTempData->PacketCheckPoint , 0 , sizeof(PlayerTempData->PacketCheckPoint) );
	memset( TempData.BuffTimeDesc , 0 , sizeof(TempData.BuffTimeDesc) );

	PlayerTempData->SendPGMode.Mode = 0;
	PlayerTempData->ExSkill.Clear(); //劇情設定額外可以使用的法術

	TempData.AI.NextMainAtk = 0;
	TempData.AI.NextSecAtk = 0;
	TempData.AttachObjID = -1;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::LiveTime( int value , const char* cszReason )
{
	if( value != -1 )
	{
		if( value == 0 )
		{
			St_DelFromPartition( GUID() );
		}

		SelfData.LiveTime = G_SysTime + value;

		TempData.Sys.DestroyAccount = cszReason;
	}
	else
	{
		SelfData.LiveTime = -1;
		TempData.Sys.DestroyAccount = "";
	}

}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::LiveTime( )
{
	if( SelfData.LiveTime == -1 )
		return 0xffffff;

	if( DBID() == -2 )
		return __max( 1 , SelfData.LiveTime - G_SysTime );

	return SelfData.LiveTime - G_SysTime;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::WorldGUID( int value )
{
	TempData.Sys.WorldGUID = value;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::WorldGUID( )
{
	return TempData.Sys.WorldGUID;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::OwnerGUID( int ID )
{
	TempData.Sys.OwnerGUID = ID;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::OwnerGUID( )
{
	return TempData.Sys.OwnerGUID;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::OwnerDBID( int ID )
{
	TempData.Sys.OwnerDBID = ID;
}
int     RoleDataEx::OwnerDBID( )
{
	return TempData.Sys.OwnerDBID;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::GUID( int value )
{
	TempData.Sys.GUID = value;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::GUID( )
{
	return TempData.Sys.GUID;
}
//-----------------------------------------------------------------------------------------
int		RoleDataEx::GuildID()
{
	return BaseData.GuildID;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::ItemID( )
{
	return TempData.Sys.ItemID;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::SockID( int value )
{
	TempData.Sys.SockID = value;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::SockID( )
{
	return TempData.Sys.SockID;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::ZoneID( )
{
	return BaseData.ZoneID;
}
void    RoleDataEx::ZoneID( int ZoneID )
{
	BaseData.ZoneID = ZoneID;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::RoomID( )
{
	return BaseData.RoomID;
}
//-----------------------------------------------------------------------------------------
void     RoleDataEx::RoomID( int value )
{
	if( BaseData.RoomID == value )
		return;

	TempData.Attr.Action.SendAllZoneObj = true;
	BaseData.RoomID = value;
}
//-----------------------------------------------------------------------------------------
RolePosStruct*  RoleDataEx::Pos( )
{
	return &BaseData.Pos;
}
//-----------------------------------------------------------------------------------------
float   RoleDataEx::X( )
{
	return BaseData.Pos.X;
}
//-----------------------------------------------------------------------------------------
float   RoleDataEx::Y( )
{
	return BaseData.Pos.Y;
}
//-----------------------------------------------------------------------------------------
float   RoleDataEx::Z( )
{
	return BaseData.Pos.Z;
}
//-----------------------------------------------------------------------------------------
float   RoleDataEx::Dir( )
{
	return BaseData.Pos.Dir;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::Pos( float X , float Y , float Z , float Dir )
{
	BaseData.Pos.X = X;
	BaseData.Pos.Y = Y;
	BaseData.Pos.Z = Z;
	BaseData.Pos.Dir = Dir;

	TempData.Move.Tx = X;
	TempData.Move.Ty = Y;
	TempData.Move.Tz = Z;

	TempData.Move.Dx = 0;
	TempData.Move.Dy = 0;
	TempData.Move.Dz = 0;

	TempData.Move.CliX = X;
	TempData.Move.CliY = Y;
	TempData.Move.CliZ = Z;

	TempData.Move.ProcDelay = 0;
	TempData.Move.AddeDelay = 0;

	TempData.Move.BeginJumpX = X;
	TempData.Move.BeginJumpY = Y;
	TempData.Move.BeginJumpZ = Z;

	TempData.Move.LOK_CliX = X;
	TempData.Move.LOK_CliY = Y;
	TempData.Move.LOK_CliZ = Z;

	TempData.Move.LCheckLineX = X;
	TempData.Move.LCheckLineY = Y;
	TempData.Move.LCheckLineZ = Z;



//	TempData.Move.LCheckDeadZoneX = X;
//	TempData.Move.LCheckDeadZoneY = Y;
//	TempData.Move.LCheckDeadZoneZ = Z;

}
//-----------------------------------------------------------------------------------------
const char*   RoleDataEx::Account_ID( )
{
	return Base.Account_ID.Begin();
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::Account_ID( char* Name )
{
	//    MyStrcpy( Base.Account_ID , Name , sizeof( Base.Account_ID ) );
	Base.Account_ID = Name;
}
//-----------------------------------------------------------------------------------------
//取出險象所需資料
void    RoleDataEx::PlayerGraph( PlayerGraphStruct& GraphObj )
{
	GraphObj.OrgObjID   = BaseData.ItemInfo.OrgObjID;
	//GraphObj.Mode       = BaseData.Mode;
	GraphObj.Mode       = TempData.BackInfo.Mode;

//	if( TempData.TouchPlot.Size() != 0 )
		GraphObj.TouchPlot_Range = TempData.TouchPlot_Range;
//	else
//		GraphObj.TouchPlot_Range = 0;

//	if( TempData.RangePlot.Size() != 0 )
		GraphObj.RangePlot_Range = TempData.RangePlot_Range;
//	else
//		GraphObj.RangePlot_Range = 0;


	if( TempData.CollisionPlot.Size() != 0 )
		GraphObj.Mode.CollisionPlot = true;
	else
		GraphObj.Mode.CollisionPlot = false;

	GraphObj.Name       			= BaseData.RoleName;
	GraphObj.MaxHP      			= int( TempData.Attr.Fin.MaxHP );
	GraphObj.HP         			= int( BaseData.HP );
	GraphObj.MaxMP      			= int( TempData.Attr.Fin.MaxMP );
	GraphObj.MP         			= int( BaseData.MP );
	GraphObj.MaxSP      			= int( TempData.Attr.Fin.MaxSP );		
	GraphObj.SP         			= int( BaseData.SP );
	GraphObj.MaxSP_Sub  			= int( TempData.Attr.Fin.MaxSP_Sub );		
	GraphObj.SP_Sub     			= int( BaseData.SP_Sub );

	GraphObj.MoveSpeed  			= TempData.Attr.Fin.MoveSpeed;
	GraphObj.Level      			= TempData.Attr.Level;
	GraphObj.NpcQuestID 			= SelfData.NpcQuestID;   
//	GraphObj.Action     			= TempData.Attr.Action;
	GraphObj.Action     			= TempData.Attr.LAction;

	GraphObj.Voc					= BaseData.Voc;
	GraphObj.Voc_Sub				= BaseData.Voc_Sub;
	GraphObj.Race					= BaseData.Race;

	GraphObj.Level_Sub				= TempData.Attr.Level_Sub;

	GraphObj.TitleID				= BaseData.TitleID;
	GraphObj.GuildID				= BaseData.GuildID;
	GraphObj.MinimapIcon			= TempData.iMinimapIcon;
	GraphObj.CursorType				= TempData.CursorType;

	GraphObj.vX						= BaseData.vX;	
	GraphObj.vY						= BaseData.vY;
	GraphObj.vZ						= BaseData.vZ;
	GraphObj.IdleMotionID			= TempData.IdleMotionID;
	GraphObj.CliActionID			= TempData.CliActionID;
	GraphObj.AllZoneState			= TempData.Attr.AllZoneState;
	GraphObj.MagicEffect._Value[0]	= TempData.Attr.Effect._Value[0];
	GraphObj.MagicEffect._Value[1]	= TempData.Attr.Effect._Value[1];
	GraphObj.IsShowTitle			= BaseData.IsShowTitle;
	GraphObj.Sex					= BaseData.Sex;
	GraphObj.GoodEvilType			= GetGoodEvilType();
//	GraphObj.Action._Action			= TempData.Attr.Action._Action;
	GraphObj.iDefIdleMotion			= TempData.iDefIdleAction;
	GraphObj.SysFlag				= BaseData.SysFlag;

	if( GraphObj.Mode.NoFix_Y == false )
	{
		if(		TempData.CliState.InWater != false
			||	TempData.Attr.Effect.Fly != false
			||	TempData.Attr.Effect.WaterWalk != false )
		{
			GraphObj.Mode.NoFix_Y = true;
		}
	}
}

//-----------------------------------------------------------------------------------------
float   RoleDataEx::MoveSpeed( )
{
	if( IsWalk() != false )
		return TempData.Attr.Fin.MoveSpeed/3;

	/*	if( TempData.Attr.Fin.MaxHP > BaseData.HP * 2 ) 
	{
	return __max( 5 , TempData.Attr.Fin.MoveSpeed * ( float( BaseData.HP) / (TempData.Attr.Fin.MaxHP) )* 2 );
	}*/

	return TempData.Attr.Fin.MoveSpeed ;

	/*
	if( IsPlayer() )
	return TempData.Attr.Fin.MoveSpeed;
	if( IsAttack() )
	return TempData.Attr.Fin.MoveSpeed;
	if( IsFollow() )
	{
	//檢查與目標的劇離
	if( Length( TargetID() ) < 30 )
	return 16;
	return TempData.Attr.Fin.MoveSpeed;
	}
	*/
}
//-----------------------------------------------------------------------------------------
/*
float   RoleDataEx::ModelSize( )
{
	return TempData.ModelSize;
}
*/
//-----------------------------------------------------------------------------------------
void    RoleDataEx::MoveTarget( float X , float Y , float Z , float Dir )
{
	TempData.Move.Tx = X;
	TempData.Move.Ty = Y;
	TempData.Move.Tz = Z;

	int DTime = MoveTime( X , Y , Z );
	TempData.Move.ProcDelay = DTime;

	TempData.Move.Dx = ( X - BaseData.Pos.X ) / DTime;
	TempData.Move.Dy = ( Y - BaseData.Pos.Y ) / DTime;
	TempData.Move.Dz = ( Z - BaseData.Pos.Z ) / DTime;
	BaseData.Pos.Dir = Dir;
}
//-----------------------------------------------------------------------------------------
PathProcStruct* RoleDataEx::Move( )
{
	return &TempData.Move;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::SecXZ( int X , int Z )
{
	TempData.Sys.SecX = X;
	TempData.Sys.SecZ = Z;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::SecX( )
{
	return TempData.Sys.SecX;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::SecZ( )
{
	return TempData.Sys.SecZ;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::SecRoomID( )
{
	return TempData.Sys.SecRoomID;
}
//-----------------------------------------------------------------------------------------
void     RoleDataEx::SecRoomID( int value )
{
	TempData.Sys.SecRoomID = value;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::Mode( )
{
	return BaseData.Mode._Mode;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::MaxHP( )
{
	return int(TempData.Attr.Fin.MaxHP);
}
//-----------------------------------------------------------------------------------------
float     RoleDataEx::HP( )
{
	return BaseData.HP;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::MaxMP( )
{
	return int(TempData.Attr.Fin.MaxMP);
}
//-----------------------------------------------------------------------------------------
float    RoleDataEx::MP( )
{
	return BaseData.MP;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::MaxSP( )
{
	return int(TempData.Attr.Fin.MaxSP);
}
//-----------------------------------------------------------------------------------------
float   RoleDataEx::SP( )
{
	return BaseData.SP;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::Level( )
{
	/*	if( IsPlayer() )
	//return TempData.Attr.Ability->Level;
	return PlayerBaseData->AbilityList[ BaseData.Voc ].Level;
	else*/
	return TempData.Attr.Level;
}
//-----------------------------------------------------------------------------------------
/*
void    RoleDataEx::PlayerGraph( PlayerGraphStruct& Graph )
{
Graph.OrgObjID  = BaseData.ItemInfo.OrgObjID;
Graph.Mode._Mode= Mode();
Graph.MaxHP     = MaxHP();
Graph.HP        = HP();
Graph.MoveSpeed = MoveSpeed();
Graph.ModelRate = ModelRate();
Graph.Level     = Level();	

//    memcpy( Graph.Name , RoleName() , sizeof(Graph.Name) );
Graph.Name = RoleName();

}
*/
//-----------------------------------------------------------------------------------------
const char*   RoleDataEx::RoleName( )
{
	return BaseData.RoleName.Begin();
}
void    RoleDataEx::RoleName( char* Name )
{	
	BaseData.RoleName = Name;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::DBID( )
{
	return Base.DBID;
}
//-----------------------------------------------------------------------------------------
/*
void    RoleDataEx::SetValue(  RoleValueName_ENUM Type , int Value  , RoleDataEx* WriteRole)
{
SetValue( Type , (float)Value , WriteRole );
}
*/
void    RoleDataEx::SetValue(  RoleValueName_ENUM Type , int Value , RoleDataEx* WriteRole )
{
	SetValue( Type , (double)Value , WriteRole );
}
void    RoleDataEx::SetValue(  RoleValueName_ENUM Type , float Value , RoleDataEx* WriteRole )
{
	SetValue( Type , (double)Value , WriteRole );
}
//設定或修改數值
void	RoleDataEx::SetValue( RoleValueName_ENUM Type , double Value  , RoleDataEx* WriteRole)
{
	unsigned ID = Type - EM_RoleValue_Skill_Unarmed;
	if( ID < _MAX_SKILLVALUE_TYPE )
	{
		if( int(Value) != int(TempData.Attr.SkillValue->Skill[ID]) )
		{
			TempData.UpdateInfo.SkillValueChange = true;
			//TempData.UpdateInfo.Recalculate_All = true;
			Log_SkillLv( ID ,  int( Value ) );
		}

		TempData.Attr.Fin.SkillValue.Skill[ID] += float( Value - TempData.Attr.SkillValue->Skill[ID] );
		TempData.Attr.SkillValue->Skill[ID]  = float(Value);
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_NormalMagic;
	if( ID < _MAX_NormalSkill_COUNT_ + _MAX_SPSkill_COUNT_ )
	{
		TempData.Attr.Ability->AllSkillLv[ID]  = float(Value);
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_VOCLV_GM;
	if( ID < EM_Max_Vocation  )
	{
		PlayerBaseData->AbilityList[ ID ].Level = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}


	ID = Type - EM_RoleValue_Famous;
	if( ID < _MAX_FAMOUS_COUNT_)
	{
		PlayerBaseData->Famous[ID] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_Register;
	if( ID < _MAX_REGISTER_COUNT_  )
	{
		TempData.Register[ID] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_FamilyFriendListLv_Pos;
	if( ID < _MAX_FRIENDLIST_FAMILY_COUNT_  )
	{
		PlayerSelfData->FriendList.FamilyList[ID].Lv = float(Value);
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_ClinetSetting;
	if( ID < _MAX_CLIENT_SETTING_SIZE_  )
	{
		PlayerBaseData->ClinetSetting[ID] = int(Value);
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_LuaMagicID;
	if( ID < _MAX_Lua_Skill_COUNT_  )
	{
		PlayerTempData->Skill.LuaSkill[ ID ] = int( Value );
		//PlayerSelfData->FriendList.FamilyList[ID].Lv = Value;
		Net_FixRoleValue( Type , Value );
		return;
	}
	ID = Type - EM_RoleValue_TimeFlag;
	if( ID <  _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_  )
	{
		PlayerBaseData->TimeFlag[ ID ] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}
	ID = Type - EM_RoleValue_LuaValueFlag;
	if( ID <  _MAX_LUA_VALUES_FLAG_ )
	{
		PlayerBaseData->LuaValueFlag[ ID ] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}
	ID = Type - EM_RoleValue_Coldown;
	if( ID <  DEF_MAX_COLDOWN_COUNT_ALL )
	{
		if( BaseData.Coldown.NeedUpdatePos.Find( ID ) == -1 )
			BaseData.Coldown.NeedUpdatePos.Push_Back( ID );

		BaseData.Coldown.All[ ID ] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}
	ID = Type - EM_RoleValue_WeekInstnaces;
	if( ID < DEF_MAX_WEEK_INS_TYPE  )
	{
		PlayerBaseData->WeekInstance[ID] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_CultivatePet_Value;
	if( ID < 1000  )
	{
		int PetPos	= ID / 100;
		int DataPos = ID % 100;
		if(		PetPos < MAX_CultivatePet_Count 
			&&	DataPos < EM_CultivatePetStructValueType_Max )
		{

			if(		DataPos >= EM_CultivatePetStructValueType_LifeSkill1 
				||	DataPos == EM_CultivatePetStructValueType_Str 
				||	DataPos == EM_CultivatePetStructValueType_Sta
				||	DataPos == EM_CultivatePetStructValueType_Agi
				||	DataPos == EM_CultivatePetStructValueType_Int
				||	DataPos == EM_CultivatePetStructValueType_Mnd
				||	DataPos == EM_CultivatePetStructValueType_Talent )
			{
				if( PlayerBaseData->Pet.Base[PetPos]._FloatValue[DataPos] == float(Value) )
					return;

				PlayerBaseData->Pet.Base[PetPos]._FloatValue[DataPos] = float(Value);
			}
			else
			{
				if( PlayerBaseData->Pet.Base[PetPos]._Value[DataPos] == int(Value) )
					return;

				PlayerBaseData->Pet.Base[PetPos]._Value[DataPos] = int(Value);
			}
			Net_FixRoleValue( Type , Value );
			return;
		}
	}

	ID = Type - EM_RoleValue_SuitSkill_LeanSkillID;
	if( ID <  _MAX_SUIT_SKILL_COUNT_ )
	{
		PlayerBaseData->SuitSkill.LeanSkillList[ ID ].SkillID = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}
	ID = Type - EM_RoleValue_BG_Return_Value;
	if( ID <  MAX_BG_REGISTER_COUNT_ )
	{
		PlayerTempData->BgReturn.Register[ID] = float( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_SuitSkill_EqID;
	if( ID <  _MAX_SUIT_SKILL_EQ_COUNT_ )
	{
		PlayerBaseData->SuitSkill.EQ[ ID ] = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_SuitWardrobe;
	if( ID <  _DEF_MAX_COOL_CLOTH_COUNT_ )
	{
		PlayerBaseData->CoolClothList[ID]  = int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	ID = Type - EM_RoleValue_PetCard;
	if( ID <  _MAX_PET_CARD_COUNT_ )
	{
		if( Value == 0 )
			PlayerBaseData->PetCard.SetFlagOff(ID);
		else
			PlayerBaseData->PetCard.SetFlagOn(ID);
		Net_FixRoleValue( Type , Value );
		return;
	}

	switch( Type )
	{
	case EM_RoleValue_X:
		BaseData.Pos.X = (float)Value;
		break;

	case EM_RoleValue_Y:
		BaseData.Pos.Y = (float)Value;
		break;

	case EM_RoleValue_Z:
		BaseData.Pos.Z = (float)Value;
		break;

	case EM_RoleValue_Dir:
		BaseData.Pos.Dir = (float)Value;
		break;
	case EM_RoleValue_HP:
		if(int(BaseData.HP) == int(Value) )
			return;

		BaseData.HP = float(Value);
		break;
	case EM_RoleValue_SoulPoint:
		if(Value > 6 )
			Value = 6;
		if( Value < 0 )
			Value = 0;

		if(TempData.SoulPoint == int(Value) )
			return;
		TempData.SoulPoint = int(Value);

		break;

	case EM_RoleValue_MP:
		if( int(BaseData.MP) == int(Value) )
			return;

		BaseData.MP = float(Value);
		break;

	case EM_RoleValue_StomachPoint:
		if( BaseData.StomachPoint == (int)Value )
			return;

		BaseData.StomachPoint = (int)Value;
		break;

	case EM_RoleValue_AddExp:
		if( TempData.Attr.Ability->AddExp == (int)Value )
			return;

		TempData.Attr.Ability->AddExp = (int)Value;
		break;
	case EM_RoleValue_AddTP:
		if( TempData.Attr.Ability->AddTp == (int)Value )
			return;

		TempData.Attr.Ability->AddTp = (int)Value;
		break;
	case EM_RoleValue_CultivatePet_Money:
		if( PlayerBaseData->Pet.Money == (int)Value )
			return;
		PlayerBaseData->Pet.Money = (int)Value;
		break;
	case  EM_RoleValue_CultivatePet_NextMergeResetTime:
		if( PlayerBaseData->Pet.NextMergeResetTime == (int)Value )
			return;
		PlayerBaseData->Pet.NextMergeResetTime = (int)Value;
		break;

	case EM_RoleValue_SysFlag:
		if( BaseData.SysFlag._Value  == (int)Value )
			return;

		BaseData.SysFlag._Value  = (int)Value;
		break;


	case EM_RoleValue_SP:
		if( int(BaseData.SP) == int(Value) )
			return;

		BaseData.SP = float(Value);
		break;

	case EM_RoleValue_SP_Sub:
		if( int(BaseData.SP_Sub) == int(Value) )
			return;

		BaseData.SP_Sub = float(Value);
		break;

	case EM_RoleValue_RACE:
		if( BaseData.Race == (Race_ENUM)(int)Value )
			return;

		BaseData.Race = (Race_ENUM)(int)Value;
		TempData.UpdateInfo.ReSetTalbe = true;
		break;
	case EM_RoleValue_VOC:
		if( BaseData.Voc == (Voc_ENUM)(int)Value )
			return;
		BaseData.Voc = (Voc_ENUM)(int)Value;
		TempData.UpdateInfo.ReSetTalbe = true;
		TempData.UpdateInfo.VocChange = true;
		OnTimeProc( true );
		break;

	case EM_RoleValue_VOC_SUB:
		if( BaseData.Voc_Sub == (Voc_ENUM)(int)Value )
			return;

		if( Value > EM_Max_Vocation && Value != EM_Vocation_None )
			return;

		BaseData.Voc_Sub = (Voc_ENUM)(int)Value;

		if( PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].Level == 0 )
			PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].Level = 1;
		TempData.UpdateInfo.ReSetTalbe = true;
		TempData.UpdateInfo.VocChange = true;
		break;

	case EM_RoleValue_LV_SUB:
		if( (unsigned)BaseData.Voc_Sub > EM_Max_Vocation )
			return;

		PlayerBaseData->AbilityList[ BaseData.Voc_Sub ].Level = int(Value);
		TempData.UpdateInfo.ReSetTalbe = true;
		break;
	case EM_RoleValue_SEX:
		if( BaseData.Sex == (Sex_ENUM)(int)Value )
			return;

		BaseData.Sex = (Sex_ENUM)(int)Value;
		TempData.UpdateInfo.ReSetTalbe = true;
		break;
	case EM_RoleValue_EXP:
		if( TempData.Attr.Ability->EXP == (int)Value )
			return;

		if( Value < 0 )
			Value = 0;

		TempData.Attr.Ability->EXP = (int)Value;
		TempData.UpdateInfo.ExpChange = true;
		break;
	case EM_RoleValue_TotalTpExp:
		{
			if( TempData.Attr.Ability->TotalTpExp == (int)Value )
				return;
			TempData.Attr.Ability->TotalTpExp = (int)Value;;
		}
		break;
	case EM_RoleValue_TpExp:
		{
			if( TempData.Attr.Ability->TpExp == (int)Value )
				return;

			int DTpExp = (int)Value - TempData.Attr.Ability->TpExp;

			if( DTpExp > 0 )
			{
				TempData.Attr.Ability->TotalTpExp += DTpExp;
			}

			TempData.Attr.Ability->TpExp = (int)Value;
		}
		break;
	case EM_RoleValue_DebtExp:		//經驗值負債
		{
			if( Value > 0 )
				return;

			if( TempData.Attr.Ability->DebtExp == (int)Value )
				return;

			if( GetLVExp( TempData.Attr.Voc ) < Value*-1 )
				Value = float( GetLVExp( TempData.Attr.Voc ) * -1 );

			TempData.Attr.Ability->DebtExp = (int)Value;


		}
		break;
	case EM_RoleValue_DebtTP:		//TP負債
		{
			if( Value > 0 )
				return;

			if( TempData.Attr.Ability->DebtTP == (int)Value )
				return;

			if( GetLVExp( TempData.Attr.Voc )/10 < Value*-1 )
				Value = float( GetLVExp( TempData.Attr.Voc )/-10 );

			TempData.Attr.Ability->DebtTP = (int)Value;
		}
		break;

	case EM_RoleValue_LV:
		if( TempData.Attr.Ability->Level == (int)Value )
			return;

		TempData.Attr.Ability->Level = (int)Value;
		TempData.Attr.Level = (int)Value;
		TempData.UpdateInfo.LvChange = true;
		break;

	case EM_RoleValue_STR:
		if( TempData.Attr.Ability->STR == (int)Value )
			return;

		TempData.Attr.Ability->STR = (int)Value;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_STA:
		if( TempData.Attr.Ability->STA == (int)Value )
			return;

		TempData.Attr.Ability->STA = (int)Value;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_INT:
		if( TempData.Attr.Ability->INT == (int)Value )
			return;

		TempData.Attr.Ability->INT = (int)Value;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_MND:
		if( TempData.Attr.Ability->MND == (int)Value )
			return;

		TempData.Attr.Ability->MND = (int)Value;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_AGI:
		if( TempData.Attr.Ability->AGI == (int)Value )
			return;

		TempData.Attr.Ability->AGI = (int)Value;
		TempData.UpdateInfo.Recalculate_All = true;
		break;

	case EM_RoleValue_Point:
		if( TempData.Attr.Ability->Point == (int)Value )
			return;

		TempData.Attr.Ability->Point = (int)Value;
		break;
		/*	case EM_RoleValue_SkillPoint:
		if( TempData.Attr.Ability->SkillPoint == (int)Value )
		return;

		TempData.Attr.Ability->SkillPoint = (int)Value;
		*/		break;

	case EM_RoleValue_LiveTime:		
		LiveTime( (int)Value * 1000 , "SYS SetValue" );
		break;

	case EM_RoleValue_ZoneID:
		BaseData.ZoneID = (int)Value;
		break;

	case EM_RoleValue_BodyCount:				  //身體欄位數量
		{
			int Count = (int)Value;
			if( Count < 0 )
				Count = 0;
			if( Count > _MAX_BODY_COUNT_ )
				Count = _MAX_BODY_COUNT_;
			Value = float( Count );
			PlayerBaseData->Body.Count = Count;
			TempData.UpdateInfo.Body = true;

		}
		break;
	case EM_RoleValue_BankCount:				  //銀行欄位數量
		{
			int Count = (int)Value;
			if( Count < 0 )
				Count = 0;
			if( Count > _MAX_BANK_COUNT_ )
				Count = _MAX_BANK_COUNT_;
			Value = float( Count );
			PlayerBaseData->Bank.Count = Count;
			TempData.UpdateInfo.Bank = true;
		}
		break;
		/*	case EM_RoleValue_Famous:
		if( PlayerBaseData->Famous == (int)Value )
		return;

		PlayerBaseData->Famous = (int)Value;
		break;*/
	case EM_RoleValue_KeyItemOn:
		if( BaseData.KeyItem.GetFlag( (int)Value ) != false )
			return;

		BaseData.KeyItem.SetFlagOn( (int)Value );
		break;
	case EM_RoleValue_KeyItemOff:
		if( BaseData.KeyItem.GetFlag( (int)Value ) == false )
			return;

		BaseData.KeyItem.SetFlagOff( (int)Value );
		break;

	case EM_RoleValue_Money:
		{
			int iOffset			= (int)Value - PlayerBaseData->Body.Money;
			AddBodyMoney( iOffset,  WriteRole , EM_ActionType_PlotGive , true );
			return;
		}
		break;
	case EM_RoleValue_Money_Account:
		{
			int iOffset			= (int)Value - PlayerBaseData->Body.Money_Account;
			AddBodyMoney_Account( iOffset,  WriteRole , EM_ActionType_PlotGive , true );
			return;
		}
		break;

	case EM_RoleValue_KillRate:
		{
			//int Value = (int)Value - PlayerBaseData->Body.Money_Account;
			TempData.Sys.KillRate = int( Value );
			return;
		}
		break;
		//---------------------------------------------------------------------------------------
		//劇情需要的數值        
		//---------------------------------------------------------------------------------------
	case EM_RoleValue_IsWalk:
		IsWalk( Value != 0 );
		break;

	case EM_RoleValue_PID:
		SelfData.PID = int(Value);
		break;

	case EM_RoleValue_PlayTimeQuota:
		PlayerBaseData->PlayTimeQuota = int( Value );
		break;
	case  EM_RoleValue_GoodEvil:
		PlayerBaseData->GoodEvil = float(Value);
		break;

	case EM_RoleValue_VocCount:

		if( int( Value ) > RoleDataEx::G_MaxVocCount )
			PlayerBaseData->VocCount = RoleDataEx::G_MaxVocCount;
		else
			PlayerBaseData->VocCount = int( Value );

		break;
	case EM_RoleValue_BoxEnergy:		//融合箱能量
		PlayerBaseData->BoxEnergy = int(Value);
		break;
	case EM_RoleValue_MedalCount:		//教導點數
		if( Value < 0 )
			Value = 0;
		if( Value > _MAX_MONEY_COUNT_)
			Value = _MAX_MONEY_COUNT_;

		PlayerBaseData->MedalCount = int(Value);
		break;
	case EM_RoleValue_BonusMoney:
		{
			int iOffset	= (int)Value - PlayerBaseData->Money_Bonus;
			AddMoney_Bonus( iOffset,  WriteRole , EM_ActionType_PlotGive );
			return;
		}
	case EM_RoleValue_MaxLv:
		{
			PlayerBaseData->MaxLv = int(Value);
		}
		break;
	case EM_RoleValue_Honor:
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_Honor_COIN_COUNT_)
				Value = _MAX_Honor_COIN_COUNT_;
			PlayerBaseData->Honor = float(Value);
		} break;
	case EM_RoleValue_DuelistReward:
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_DuelistReward_COIN_COUNT_)
				Value = _MAX_DuelistReward_COIN_COUNT_;
			PlayerBaseData->DuelistReward = int(Value);
			
		} break;
	case EM_RoleValue_TrialBadgeCoin:		//試煉徽章
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->TrialBadgeCoin = int(Value);

		} break;
	case EM_RoleValue_RelicsCoin:			//古代遺物
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_Relics_COIN_COUNT_)
				Value = _MAX_Relics_COIN_COUNT_;
			PlayerBaseData->RelicsCoin = int(Value);

		} break;
	case EM_RoleValue_DreamlandCoin:		//夢境先遣印記
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->DreamlandCoin = int(Value);

		} break;
	case EM_RoleValue_PhiriusShellCoin:		//必爾汀圓貝
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_PhiriusShell_COIN_COUNT_)
				Value = _MAX_PhiriusShell_COIN_COUNT_;
			PlayerBaseData->PhiriusShellCoin = int(Value);

		} break;
	case EM_RoleValue_EnergyJusticeCoin:	//正義能量
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_EnergyJusticeCoin_COUNT_)
				Value = _MAX_EnergyJusticeCoin_COUNT_;
			PlayerBaseData->EnergyJusticeCoin = int(Value);

		} break;
	case EM_RoleValue_ProofLegendCoin:		//傳說之證
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->ProofLegendCoin = int(Value);

		} break;
	case EM_RoleValue_MirrorCoin:
		{
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->MirrorCoin = int(Value);

		} break;

	case EM_RoleValue_VenderCount:		//傳說之證
		{
			PlayerBaseData->Defendant.MoneyTraderCount = int(Value);
		} break;
	case EM_RoleValue_WeekResetCount:
		{
			PlayerBaseData->WeekResetCount = int(Value);
		}
		break;
	case EM_RoleValue_LockHP:
		{
			TempData.LockHP = int(Value);
		} break;
	case EM_RoleValue_MaxPlantCount:
		{
			PlayerBaseData->MaxPlantCount = int(Value);
		}break;		
	case EM_RoleValue_AttackDelay:
		{
			TempData.AI.AddAtkTime = int(Value);
		}break;
	case EM_RoleValue_MoveDelay:
		{
			TempData.Move.AddeDelay = int(Value);
		}break;
	case EM_RoleValue_SlotMachineFreeCount:
		{
			PlayerBaseData->SlotMachine.FreeCount = int(Value);
		}break;
	case EM_RoleValue_GuildID:
		{
			if( IsPlayer() )
				return;

			BaseData.GuildID = int(Value);

		}break;
	case EM_RoleValue_SuitSkill_MaxEqSkillCount:
		{
			PlayerBaseData->SuitSkill.MaxEqSkillCount = int(Value);
		}
		break;
	case EM_RoleValue_SuitSkill_LeanSkillCount:
		{
			PlayerBaseData->SuitSkill.LeanSkillCount = int(Value);
		}
		break;

	case EM_RoleValue_IncursivePoint:
		{
			PlayerBaseData->IncursivePoint	= int(Value);
		}break;
	case EM_RoleValue_RecalculateAll:
		{
			TempData.UpdateInfo.ReSetTalbe = true;
			TempData.UpdateInfo.Recalculate_All = true;
		}
		break;
	case EM_RoleValue_PassengerAttackable:
		{
			BaseData.SysFlag.PassengerAttackable = (Value != 0);
		}
		break;
	case EM_RoleValue_IsUnholster:
		{
			TempData.Attr.Action.Unholster	= (Value!=0);
			
			RoleSpriteStatus* temp = (RoleSpriteStatus*)&(TempData.CliActionID);
			temp->isUnholster = (Value!=0);
		}
		break;
	case EM_RoleValue_SetNPCAttackRange:
		{
			if( IsPlayer() )
				return;
			TempData.Attr.MainAttackRange = (int)Value;
		}
		break;
	case EM_RoleValue_TitleSys_Famous:		//頭銜系統能量
		{
			if( Value > 100 )
				Value = 100;
			else if( Value < 0 )
				Value = 0;

			if( PlayerBaseData->TitleSys.Famous == (float)Value )
				return;

			PlayerBaseData->TitleSys.Famous = (float)Value;
			TempData.UpdateInfo.Recalculate_All = true;
			break;
		}
		break;
	case EM_RoleValue_TitleSys_Lv:		//頭銜系統能量
		{
			if( PlayerBaseData->TitleSys.Lv == (int)Value )
				return;

			PlayerBaseData->TitleSys.Lv = (int)Value;
			break;
		}
		break;
	case EM_RoleValue_TitleSys_Exp:		//頭銜系統能量
		{
			if( PlayerBaseData->TitleSys.Exp == (int)Value )
				return;

			PlayerBaseData->TitleSys.Exp = (int)Value;
			break;
		}
		break;
	case EM_RoleValue_TitleSys_TitleID1:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID2:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID3:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID4:		//頭銜系統裝備頭銜
		{
			int ID = Type - EM_RoleValue_TitleSys_TitleID1;
			int& TitleID = PlayerBaseData->TitleSys.TitleID[ID];
			if( TitleID == (int)Value )
				return;

			TitleID = (int)Value;
			TempData.UpdateInfo.Recalculate_All = true;
			break;
		}
		break;
	default:

		return;
	}
	Net_FixRoleValue( Type , Value );

}

void    RoleDataEx::AddValue(  RoleValueName_ENUM Type , int  Value , RoleDataEx* WriteRole )
{
	AddValue(  Type , (double)Value , WriteRole );
}
void    RoleDataEx::AddValue(  RoleValueName_ENUM Type , float  Value , RoleDataEx* WriteRole )
{
	AddValue(  Type , (double)Value , WriteRole );
}

void    RoleDataEx::AddValue(  RoleValueName_ENUM Type , double  Value , RoleDataEx* WriteRole )
{
	if( Value == 0 )
		return;

	unsigned ID = Type - EM_RoleValue_Skill_Unarmed;
	if( ID < _MAX_SKILLVALUE_TYPE )
	{
		if( Value > 0 )
		{
			if( int(TempData.Attr.SkillValue->Skill[ID] ) == int( TempData.Attr.MaxSkillValue.Skill[ID] ) )
			{
				return;
			}
		}
		else
		{
			if( TempData.Attr.SkillValue->Skill[ID] == 0 )
			{
				return;
			}
		}

		if( int(TempData.Attr.SkillValue->Skill[ID] + Value ) != int(TempData.Attr.SkillValue->Skill[ID]) )
		{
//			TempData.UpdateInfo.SkillValueChange = true;		
			Log_SkillLv( ID ,  int(TempData.Attr.SkillValue->Skill[ID] + Value ) );
		}

		TempData.Attr.Fin.SkillValue.Skill[ID] += float(Value);
		TempData.Attr.SkillValue->Skill[ID]  += float(Value);

		if( TempData.Attr.SkillValue->Skill[ID] >  TempData.Attr.MaxSkillValue.Skill[ID]  )
		{
			TempData.Attr.SkillValue->Skill[ID] = TempData.Attr.MaxSkillValue.Skill[ID];
			TempData.UpdateInfo.Recalculate_All = true;
		}
		else if( TempData.Attr.SkillValue->Skill[ID] <  0  )
		{
			TempData.Attr.SkillValue->Skill[ID] = 0;
			TempData.UpdateInfo.Recalculate_All = true;
		}

		Net_FixRoleValue( Type , double( TempData.Attr.SkillValue->Skill[ID] ) );
		return;
	}

	ID = Type - EM_RoleValue_NormalMagic;
	if( ID < _MAX_NormalSkill_COUNT_ + _MAX_SPSkill_COUNT_ )
	{
		TempData.Attr.Ability->AllSkillLv[ID]  += float(Value);
		Net_FixRoleValue( Type , double( TempData.Attr.Ability->AllSkillLv[ID] ) );
		return;
	}

	ID = Type - EM_RoleValue_Famous;
	if( ID < _MAX_FAMOUS_COUNT_ && ID >= 0 )
	{
		PlayerBaseData->Famous[ID] +=  int( Value );
		Net_FixRoleValue( Type , double( PlayerBaseData->Famous[ID] ) );
	}

	ID = Type - EM_RoleValue_Register;
	if( ID < _MAX_REGISTER_COUNT_ && ID >= 0 )
	{
		TempData.Register[ID] += int( Value );
		Net_FixRoleValue( Type , double( TempData.Register[ID] ) );
	}

	ID = Type - EM_RoleValue_FamilyFriendListLv_Pos;
	if( ID < _MAX_FRIENDLIST_FAMILY_COUNT_  )
	{
		PlayerSelfData->FriendList.FamilyList[ID].Lv += float(Value);
		Net_FixRoleValue( Type , double( PlayerSelfData->FriendList.FamilyList[ID].Lv ));
		return;
	}

	ID = Type - EM_RoleValue_ClinetSetting;
	if( ID < _MAX_CLIENT_SETTING_SIZE_  )
	{
		PlayerBaseData->ClinetSetting[ID] += (int)Value;
		Net_FixRoleValue( Type , double(PlayerBaseData->ClinetSetting[ID]) );
		return;
	}

	ID = Type - EM_RoleValue_TimeFlag;
	if( ID <  _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_  )
	{
		PlayerBaseData->TimeFlag[ ID ] += int( Value );
		Net_FixRoleValue( Type , double( PlayerBaseData->TimeFlag[ ID ] ) );
		return;
	}

	ID = Type - EM_RoleValue_LuaValueFlag;
	if( ID <  _MAX_LUA_VALUES_FLAG_ )
	{
		PlayerBaseData->LuaValueFlag[ ID ] += int( Value );
		Net_FixRoleValue( Type , double( PlayerBaseData->LuaValueFlag[ ID ] ) );
		return;
	}

	ID = Type - EM_RoleValue_Coldown;
	if( ID <  DEF_MAX_COLDOWN_COUNT_ALL )
	{
		BaseData.Coldown.All[ ID ] += int( Value );
		Net_FixRoleValue( Type , double( BaseData.Coldown.All[ ID ] ) );
		return;
	}

	ID = Type - EM_RoleValue_BG_Return_Value;
	if( ID <  MAX_BG_REGISTER_COUNT_ )
	{
		PlayerTempData->BgReturn.Register[ID] += int( Value );
		Net_FixRoleValue( Type , double( PlayerTempData->BgReturn.Register[ID] ) );
		return;
	}
	ID = Type - EM_RoleValue_SuitWardrobe;
	if( ID <  _DEF_MAX_COOL_CLOTH_COUNT_ )
	{
		return;
	}
	ID = Type - EM_RoleValue_PetCard;
	if( ID <  _MAX_PET_CARD_COUNT_ )
	{
		return;
	}

	ID = Type - EM_RoleValue_WeekInstnaces;
	if( ID < DEF_MAX_WEEK_INS_TYPE  )
	{
		Value = PlayerBaseData->WeekInstance[ID] += int( Value );
		Net_FixRoleValue( Type , Value );
		return;
	}

	/*
	ID = Type - EM_RoleValue_CultivatePet_Value;
	if( ID < 1000  )
	{
	int PetPos	= ID / 100;
	int DataPos = ID % 100;
	if(		PetPos < MAX_CultivatePet_Count 
	&&	DataPos < EM_CultivatePetStructValueType_Max )
	{
	PlayerBaseData->Pet.Base[PetPos]._Value[DataPos] += int(Value);
	Net_FixRoleValue( Type , double(PlayerBaseData->Pet.Base[PetPos]._Value[DataPos]) );
	return;
	}
	}*/
	ID = Type - EM_RoleValue_CultivatePet_Value;
	if( ID < 1000  )
	{
		int PetPos	= ID / 100;
		int DataPos = ID % 100;
		if(		PetPos < MAX_CultivatePet_Count 
			&&	DataPos < EM_CultivatePetStructValueType_Max )
		{

			if(		DataPos >= EM_CultivatePetStructValueType_LifeSkill1 
				||	DataPos == EM_CultivatePetStructValueType_Str 
				||	DataPos == EM_CultivatePetStructValueType_Sta
				||	DataPos == EM_CultivatePetStructValueType_Agi
				||	DataPos == EM_CultivatePetStructValueType_Int
				||	DataPos == EM_CultivatePetStructValueType_Mnd
				||	DataPos == EM_CultivatePetStructValueType_Talent )
			{
				PlayerBaseData->Pet.Base[PetPos]._FloatValue[DataPos] += float(Value);
				Net_FixRoleValue( Type , double(PlayerBaseData->Pet.Base[PetPos]._FloatValue[DataPos]) );
			}
			else
			{
				PlayerBaseData->Pet.Base[PetPos]._Value[DataPos] += int(Value);
				Net_FixRoleValue( Type , double(PlayerBaseData->Pet.Base[PetPos]._Value[DataPos]) );
			}
			return;
		}
	}



	switch( Type )
	{
	case EM_RoleValue_HP:

		Value = BaseData.HP + Value;        
		BaseData.HP = float( Value );
		break;

	case EM_RoleValue_MP:
		Value = BaseData.MP + Value;        
		BaseData.MP = float( Value );
		break;
	case EM_RoleValue_SoulPoint:
		Value = TempData.SoulPoint + Value;
		
		if( Value > 6 )
			Value = 6;
		if( Value < 0 )
			Value = 0;
		if( (int)Value == TempData.SoulPoint )
			return;
		TempData.SoulPoint = ( int )Value;
		break;
	case EM_RoleValue_StomachPoint:
		Value = BaseData.StomachPoint + Value;        
		BaseData.StomachPoint = int( Value );
		break;
	case EM_RoleValue_AddExp:
		Value = TempData.Attr.Ability->AddExp + Value;        
		TempData.Attr.Ability->AddExp = int( Value );
		break;
	case EM_RoleValue_AddTP:
		Value = TempData.Attr.Ability->AddTp + Value;        
		TempData.Attr.Ability->AddTp = int( Value );
		break;
	case EM_RoleValue_CultivatePet_Money:
		Value = PlayerBaseData->Pet.Money + Value;        
		PlayerBaseData->Pet.Money = int( Value );
		break;

	case EM_RoleValue_SP:
		Value = BaseData.SP + Value;        
		BaseData.SP = float( Value );
		break;

	case EM_RoleValue_SP_Sub :
		Value = BaseData.SP_Sub + Value;        
		BaseData.SP_Sub = float( Value );
		break;

	case EM_RoleValue_EXP:
		PlayerTempData->Log.Exp += int(Value);
		Value = TempData.Attr.Ability->EXP + Value;        
		if( Value < 0 )
			Value = 0;
		TempData.Attr.Ability->EXP = int( Value );				
		TempData.UpdateInfo.ExpChange = true;
		break;

	case EM_RoleValue_TpExp:
		PlayerTempData->Log.Exp_TP += int(Value);		
		TempData.Attr.Ability->TotalTpExp += int(Value);
		Value = TempData.Attr.Ability->TpExp + Value;        
		TempData.Attr.Ability->TpExp = int( Value );
		break;
	case EM_RoleValue_DebtExp:		//經驗值負債
		Value = TempData.Attr.Ability->DebtExp + Value;        
		if( Value > 0 )
			Value = 0;

		if( GetLVExp( TempData.Attr.Voc ) < Value*-1 )
			Value = GetLVExp( TempData.Attr.Voc ) * -1;

		TempData.Attr.Ability->DebtExp = int( Value );
		break;
	case EM_RoleValue_DebtTP:		//TP負債
		Value = TempData.Attr.Ability->DebtTP + Value;        
		if( Value > 0 )
			Value = 0;

		if( GetLVExp( TempData.Attr.Voc )/10 < Value*-1 )
			Value = GetLVExp( TempData.Attr.Voc ) /-10;

		TempData.Attr.Ability->DebtTP = int( Value );
		break;
	case EM_RoleValue_LV:

		TempData.Attr.Ability->Level += (int)Value;
		Value = TempData.Attr.Ability->Level;
		TempData.Attr.Level = TempData.Attr.Ability->Level;
		TempData.UpdateInfo.LvChange = true;
		break;

	case EM_RoleValue_STR:
		TempData.Attr.Ability->STR += (int)Value;
		Value = TempData.Attr.Ability->STR;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_STA:
		TempData.Attr.Ability->STA += (int)Value;
		Value = TempData.Attr.Ability->STA;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_INT:
		TempData.Attr.Ability->INT += (int)Value;
		Value = TempData.Attr.Ability->INT;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_MND:
		TempData.Attr.Ability->MND += (int)Value;
		Value = TempData.Attr.Ability->MND;
		TempData.UpdateInfo.Recalculate_All = true;
		break;
	case EM_RoleValue_AGI:
		TempData.Attr.Ability->AGI += (int)Value;
		Value = TempData.Attr.Ability->AGI;
		TempData.UpdateInfo.Recalculate_All = true;
		break;

	case EM_RoleValue_Point:
		TempData.Attr.Ability->Point += (int)Value;
		Value = TempData.Attr.Ability->Point;
		break;

	case EM_RoleValue_BodyCount:				  //身體欄位數量
		{
			Value = Value + PlayerBaseData->Body.Count;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_BODY_COUNT_ )
				Value = _MAX_BODY_COUNT_;
			PlayerBaseData->Body.Count = int( Value );
			TempData.UpdateInfo.Body = true;
		}
		break;
	case EM_RoleValue_BankCount:				  //銀行欄位數量
		{
			Value = Value + PlayerBaseData->Bank.Count;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_BANK_COUNT_ )
				Value = _MAX_BANK_COUNT_;
			PlayerBaseData->Bank.Count = int( Value );
			TempData.UpdateInfo.Bank = true;
		}
		break;

		/*	case EM_RoleValue_Famous:
		PlayerBaseData->Famous += (int)Value;
		Value = float( PlayerBaseData->Famous );
		break;
		*/
	case EM_RoleValue_Money:
		{
			AddBodyMoney( (int)Value,  WriteRole , EM_ActionType_PlotGive , true );
			//Value = float( PlayerBaseData->Body.Money );
			return;
		}break;

	case EM_RoleValue_Money_Account:
		{
			AddBodyMoney_Account( (int)Value, WriteRole , EM_ActionType_PlotGive , true );
			//Value = float( PlayerBaseData->Body.Money_Account );
			return;
		}break;
	case  EM_RoleValue_GoodEvil:
		{
			PlayerBaseData->GoodEvil += float(Value);
			Value = PlayerBaseData->GoodEvil;
		}
		break;
	case EM_RoleValue_VocCount:
		{
			PlayerBaseData->VocCount += int( Value );
			if( PlayerBaseData->VocCount > RoleDataEx::G_MaxVocCount )
				PlayerBaseData->VocCount = RoleDataEx::G_MaxVocCount;
			Value =  PlayerBaseData->VocCount ;
		}
		break;
	case EM_RoleValue_BoxEnergy:		//融合箱能量
		{
			PlayerBaseData->BoxEnergy += int( Value );
			Value = PlayerBaseData->BoxEnergy;
		}
		break;
	case EM_RoleValue_MedalCount:		//教導點數
		{
			Value += PlayerBaseData->MedalCount;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->MedalCount = int( Value );
		}
		break;
	case EM_RoleValue_BonusMoney:
		{
			AddMoney_Bonus( int(Value),  WriteRole , EM_ActionType_PlotGive );
			return;
		}
		break;
	case EM_RoleValue_Honor:
		{
			Value += PlayerBaseData->Honor;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_Honor_COIN_COUNT_)
				Value = _MAX_Honor_COIN_COUNT_;
			PlayerBaseData->Honor = float( Value );
			Value = PlayerBaseData->Honor;
		} break;
	case EM_RoleValue_DuelistReward:
		{
			Value += PlayerBaseData->DuelistReward;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_DuelistReward_COIN_COUNT_)
				Value = _MAX_DuelistReward_COIN_COUNT_;
			PlayerBaseData->DuelistReward = int(Value);

		} break;
	case EM_RoleValue_TrialBadgeCoin:		//試煉徽章
		{
			Value += PlayerBaseData->TrialBadgeCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->TrialBadgeCoin = int(Value);

		} break;
	case EM_RoleValue_RelicsCoin:			//古代遺物
		{
			Value += PlayerBaseData->RelicsCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_Relics_COIN_COUNT_)
				Value = _MAX_Relics_COIN_COUNT_;
			PlayerBaseData->RelicsCoin = int(Value);

		} break;
	case EM_RoleValue_DreamlandCoin:		//夢境先遣印記
		{
			Value += PlayerBaseData->DreamlandCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->DreamlandCoin = int(Value);

		} break;
	case EM_RoleValue_PhiriusShellCoin:		//必爾汀圓貝
		{
			Value += PlayerBaseData->PhiriusShellCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_PhiriusShell_COIN_COUNT_)
				Value = _MAX_PhiriusShell_COIN_COUNT_;
			PlayerBaseData->PhiriusShellCoin = int(Value);

		} break;
	case EM_RoleValue_EnergyJusticeCoin:	//正義能量
		{
			Value += PlayerBaseData->EnergyJusticeCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->EnergyJusticeCoin = int(Value);

		} break;
	case EM_RoleValue_ProofLegendCoin:		//傳說之證
		{
			Value += PlayerBaseData->ProofLegendCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->ProofLegendCoin = int(Value);

		} break;
	case EM_RoleValue_VenderCount:		//傳說之證
		{
			Value = PlayerBaseData->Defendant.MoneyTraderCount += int(Value);
		} break;
	case EM_RoleValue_MirrorCoin:
		{
			Value += PlayerBaseData->MirrorCoin;
			if( Value < 0 )
				Value = 0;
			if( Value > _MAX_MONEY_COUNT_)
				Value = _MAX_MONEY_COUNT_;
			PlayerBaseData->MirrorCoin = int(Value);

		} break;

	case EM_RoleValue_WeekResetCount:
		{
			Value = PlayerBaseData->WeekResetCount += int(Value);
		}
		break;

	case EM_RoleValue_LockHP:
		{
			Value = TempData.LockHP += int(Value);
		} break;
	case EM_RoleValue_MaxPlantCount:
		{
			PlayerBaseData->MaxPlantCount += int( Value );
			Value = PlayerBaseData->MaxPlantCount;
		} break;
	case EM_RoleValue_AttackDelay:
		{
			TempData.AI.AddAtkTime += int(Value);
			Value = TempData.AI.AddAtkTime;
		}break;
	case EM_RoleValue_MoveDelay:
		{
			TempData.Move.AddeDelay += int(Value);
			Value = TempData.Move.AddeDelay;
		}break;
	case EM_RoleValue_SlotMachineFreeCount:
		{
			PlayerBaseData->SlotMachine.FreeCount += int(Value);
			Value = PlayerBaseData->SlotMachine.FreeCount;
		}break;
	case EM_RoleValue_DodgeState:			//(最近有)閃避
		{
			TempData.BackInfo.LastDodgeTime += int( Value );
			Value = TempData.BackInfo.LastDodgeTime;
		}break;
	case EM_RoleValue_MissState:			//(最近有)Miss
		{
			TempData.BackInfo.LastMissTime += int( Value );
			Value = TempData.BackInfo.LastMissTime;
		}break;
	case EM_RoleValue_ParryState:			//(最近有)Parry
		{
			TempData.BackInfo.LastParryTime += int( Value );
			Value = TempData.BackInfo.LastParryTime;
		}break;
	case EM_RoleValue_BeParryState:			//(最近有)被Parry
		{
			TempData.BackInfo.LastBeParryTime += int( Value );
			Value = TempData.BackInfo.LastBeParryTime;
		}break;
	case EM_RoleValue_BeDodgeState:			//(最近有)被閃避
		{
			TempData.BackInfo.LastBeDodgeTime += int( Value );
			Value = TempData.BackInfo.LastBeDodgeTime;
		}break;
	case EM_RoleValue_CritialState:			//(最近有)物理Critial
		{
			TempData.BackInfo.LastCriticalTime += int( Value );
			Value = TempData.BackInfo.LastCriticalTime;
		}break;
	case EM_RoleValue_BeCritialState:		//(最近有)被物理Critial
		{
			TempData.BackInfo.LastBeCriticalTime += int( Value );
			Value = TempData.BackInfo.LastBeCriticalTime;
		}break;
	case EM_RoleValue_MagicCritialState:	//(最近有)法術Critial
		{
			TempData.BackInfo.LastMagicCriticalTime += int( Value );
			Value = TempData.BackInfo.LastMagicCriticalTime;
		}break;
	case EM_RoleValue_BeMagicCritialState:	//(最近有)被法術Critial
		{
			TempData.BackInfo.LastBeMagicCriticalTime += int( Value );
			Value = TempData.BackInfo.LastBeMagicCriticalTime;
		}break;
	case EM_RoleValue_ShieldBlockState:		//(最近有)盾檔
		{
			TempData.BackInfo.LastShieldBlockTime += int( Value );
			Value = TempData.BackInfo.LastShieldBlockTime;
		}break;
	case EM_RoleValue_BeShieldBlockState:	//(最近有)被盾檔	
		{
			TempData.BackInfo.LastBeShieldBlockTime += int( Value );
			Value = TempData.BackInfo.LastBeShieldBlockTime;
		}break;
	case EM_RoleValue_IncursivePoint:
		{
			PlayerBaseData->IncursivePoint += int( Value );
			Value = PlayerBaseData->IncursivePoint;
		}break;
	case EM_RoleValue_TitleSys_Famous:		//頭銜系統能量
		{
			PlayerBaseData->TitleSys.Famous += float( Value );
			if( PlayerBaseData->TitleSys.Famous > 100 )
				PlayerBaseData->TitleSys.Famous = 100;
			else if( PlayerBaseData->TitleSys.Famous < 0 )
				PlayerBaseData->TitleSys.Famous = 0;

			Value = PlayerBaseData->TitleSys.Famous;
			TempData.UpdateInfo.Recalculate_All = true;
			break;
		}
		break;
	case EM_RoleValue_TitleSys_Lv:		//頭銜系統能量
		{
			PlayerBaseData->TitleSys.Lv += int( Value );
			Value = PlayerBaseData->TitleSys.Lv;
		}
		break;
	case EM_RoleValue_TitleSys_Exp:		//頭銜系統能量
		{
			PlayerBaseData->TitleSys.Exp += int( Value );
			Value = PlayerBaseData->TitleSys.Exp;
		}
		break;

	default:
		return;
	}
	Net_FixRoleValue( Type , (float)Value );

}
int	    RoleDataEx::GetValue_Int(  RoleValueName_ENUM Type )
{
	return int( GetValue( Type ) );
}
float	    RoleDataEx::GetValue_Float(  RoleValueName_ENUM Type )
{
	return float( GetValue( Type ) );
}

double    RoleDataEx::GetValue( RoleValueName_ENUM Type  )
{
	unsigned ID = Type - EM_RoleValue_Skill_Unarmed;
	if( ID < _MAX_SKILLVALUE_TYPE )
	{
		return TempData.Attr.SkillValue->Skill[ID];
	}
	ID = Type - EM_RoleValue_Skill_Fin_Unarmed;
	if( ID < _MAX_SKILLVALUE_TYPE )
	{
		return TempData.Attr.Fin.SkillValue.Skill[ID];
	}
	ID = Type - EM_RoleValue_SkillMax_Unarmed;
	if( ID < _MAX_SKILLVALUE_TYPE )
	{
		return TempData.Attr.MaxSkillValue.Skill[ID];
	}

	ID = Type - EM_RoleValue_NormalMagic;
	if( ID < _MAX_NormalSkill_COUNT_ + _MAX_SPSkill_COUNT_ )
	{
		return TempData.Attr.Ability->AllSkillLv[ID];	
	}

	ID = Type - EM_RoleValue_VOCLV_GM;
	if( ID < EM_Max_Vocation && ID >= 0 )
	{
		return PlayerBaseData->AbilityList[ ID ].Level;
	}

	ID = Type - EM_RoleValue_Famous;
	if( ID < 10 && ID >= 0 )
	{
		return PlayerBaseData->Famous[ ID ];
	}

	ID = Type - EM_RoleValue_Register;
	if( ID < _MAX_REGISTER_COUNT_ && ID >= 0 )
	{
		return TempData.Register[ID];
	}

	ID = Type - EM_RoleValue_FamilyFriendListLv_Pos;
	if( ID < _MAX_FRIENDLIST_FAMILY_COUNT_  )
	{
		return PlayerSelfData->FriendList.FamilyList[ID].Lv;
	}

	ID = Type - EM_RoleValue_ClinetSetting;
	if( ID < _MAX_CLIENT_SETTING_SIZE_  )
	{
		return PlayerBaseData->ClinetSetting[ID];
	}

	ID = Type - EM_RoleValue_LuaMagicID;
	if( ID < _MAX_Lua_Skill_COUNT_  )
	{
		return PlayerTempData->Skill.LuaSkill[ ID ];
	}

	ID = Type - EM_RoleValue_TimeFlag;
	if( ID <  _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_  )
	{
		return PlayerBaseData->TimeFlag[ ID ];
	}

	ID = Type - EM_RoleValue_LuaValueFlag;
	if( ID <  _MAX_LUA_VALUES_FLAG_ )
	{
		return PlayerBaseData->LuaValueFlag[ ID ];
	}

	ID = Type - EM_RoleValue_MagicPowerLv_SP;
	if( ID < _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_  )
	{
		return GetMagicLv( ID );
	}

	ID = Type - EM_RoleValue_Coldown;
	if( ID <  DEF_MAX_COLDOWN_COUNT_ALL )
	{
		return BaseData.Coldown.All[ ID ];
	}

	ID = Type - EM_RoleValue_MagicID_SP;
	if( ID < _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_  )
	{
		return PlayerTempData->Skill.AllSkill[ID];
	}

	ID = Type - EM_RoleValue_CultivatePet_Value;
	if( ID < 1000  )
	{
		int PetPos	= ID / 100;
		int DataPos = ID % 100;
		if(		PetPos < MAX_CultivatePet_Count 
			&&	DataPos < EM_CultivatePetStructValueType_Max )
		{
			if(		DataPos >= EM_CultivatePetStructValueType_LifeSkill1 
				||	DataPos == EM_CultivatePetStructValueType_Str 
				||	DataPos == EM_CultivatePetStructValueType_Sta
				||	DataPos == EM_CultivatePetStructValueType_Agi
				||	DataPos == EM_CultivatePetStructValueType_Int
				||	DataPos == EM_CultivatePetStructValueType_Mnd
				||	DataPos == EM_CultivatePetStructValueType_Talent )
				return PlayerBaseData->Pet.Base[PetPos]._FloatValue[DataPos];
			else
				return PlayerBaseData->Pet.Base[PetPos]._Value[DataPos];

		}
	}


	ID = Type - EM_RoleValue_SuitSkill_LeanSkillID;
	if( ID <  _MAX_SUIT_SKILL_COUNT_ )
	{
		return PlayerBaseData->SuitSkill.LeanSkillList[ ID ].SkillID;
	}
	ID = Type - EM_RoleValue_SuitSkill_EqID;
	if( ID <  _MAX_SUIT_SKILL_EQ_COUNT_ )
	{
		return PlayerBaseData->SuitSkill.EQ[ ID ];
	}
	ID = Type - EM_RoleValue_BG_Return_Value;
	if( ID <  MAX_BG_REGISTER_COUNT_ )
	{
		return PlayerTempData->BgReturn.Register[ID];
	}

	ID = Type - EM_RoleValue_SuitWardrobe;
	if( ID <  _DEF_MAX_COOL_CLOTH_COUNT_ )
	{
		return PlayerBaseData->CoolClothList[ID];
	}
	ID = Type - EM_RoleValue_PetCard;
	if( ID <  _MAX_PET_CARD_COUNT_ )
	{
		return 	PlayerBaseData->PetCard.GetFlag(ID);
	}

	ID = Type - EM_RoleValue_WeekInstnaces;
	if( ID < DEF_MAX_WEEK_INS_TYPE  )
	{
		return PlayerBaseData->WeekInstance[ID];
	}

	switch( Type )
	{
	case EM_RoleValue_HP:
		return BaseData.HP;

	case EM_RoleValue_MP:
		return BaseData.MP;

	case EM_RoleValue_SoulPoint:
		return TempData.SoulPoint;

	case EM_RoleValue_SP:
		return BaseData.SP;

	case EM_RoleValue_SP_Sub:
		return BaseData.SP_Sub;

	case EM_RoleValue_StomachPoint:
		return BaseData.StomachPoint;

	case EM_RoleValue_AddExp:
		return TempData.Attr.Ability->AddExp;

	case EM_RoleValue_AddTP:
		return TempData.Attr.Ability->AddTp;

	case EM_RoleValue_CultivatePet_Money:
		return PlayerBaseData->Pet.Money;


	case EM_RoleValue_MaxHP:
		return TempData.Attr.Fin.MaxHP;

	case EM_RoleValue_MaxMP:
		return TempData.Attr.Fin.MaxMP;

	case EM_RoleValue_MaxSP:
		return TempData.Attr.Fin.MaxSP;

	case EM_RoleValue_MaxSP_Sub:
		return TempData.Attr.Fin.MaxSP_Sub;

	case EM_RoleValue_X:
		return BaseData.Pos.X;

	case EM_RoleValue_Y:
		return BaseData.Pos.Y;

	case EM_RoleValue_Z:
		return BaseData.Pos.Z;

	case EM_RoleValue_CliOk_X:		//確認可走的點
		return TempData.Move.CliX;
	case EM_RoleValue_CliOk_Y:		//確認可走的點
		return TempData.Move.CliY;
	case EM_RoleValue_CliOk_Z:		//確認可走的點
		return TempData.Move.CliZ;

	case EM_RoleValue_VIP_Type:
	{
		if( RoleDataEx::G_Now_Float > PlayerBaseData->VipMember.Term )
			return 0;
		return PlayerBaseData->VipMember.Type;
	}

	case EM_RoleValue_VIP_Flag:
	{
		if( RoleDataEx::G_Now_Float > PlayerBaseData->VipMember.Term )
			return 0;
		return PlayerBaseData->VipMember._Flag;
	}

	case EM_RoleValue_UnTrust_Flag:		//玩家信任機制(有值表示不信任)
		{
			return PlayerBaseData->VipMember.UntrustFlag._Flag;
		}

	case EM_RoleValue_Dir:
		return BaseData.Pos.Dir;

	case EM_RoleValue_RoomID:
		return RoomID();

	case EM_RoleValue_RACE:
		return BaseData.Race;

	case EM_RoleValue_VOC:
		return BaseData.Voc;

	case EM_RoleValue_VOC_SUB:
		return BaseData.Voc_Sub;

	case EM_RoleValue_LV_SUB:
		return TempData.Attr.Level_Sub;

	case EM_RoleValue_ThisLVExp:
		return GetLVExp( BaseData.Voc );

	case EM_RoleValue_SEX:
		return BaseData.Sex;

	case EM_RoleValue_EXP:
		return TempData.Attr.Ability->EXP;

	case EM_RoleValue_TpExp:
		return TempData.Attr.Ability->TpExp;

	case EM_RoleValue_DebtExp:
		return TempData.Attr.Ability->DebtExp;

	case EM_RoleValue_DebtTP:
		return TempData.Attr.Ability->DebtTP;


	case EM_RoleValue_LV:
		return TempData.Attr.Ability->Level;

	case EM_RoleValue_STR:
		return TempData.Attr.Ability->STR;

	case EM_RoleValue_STA:
		return TempData.Attr.Ability->STA;

	case EM_RoleValue_INT:
		return TempData.Attr.Ability->INT;

	case EM_RoleValue_MND:
		return TempData.Attr.Ability->MND;

	case EM_RoleValue_AGI:
		return TempData.Attr.Ability->AGI;

	case EM_RoleValue_Point:
		return TempData.Attr.Ability->Point;

	case EM_RoleValue_BodyCount:				  //身體欄位數量
		return PlayerBaseData->Body.Count;

	case EM_RoleValue_BankCount:				  //銀行欄位數量
		return PlayerBaseData->Bank.Count;

	case EM_RoleValue_Money:
		return PlayerBaseData->Body.Money;

	case EM_RoleValue_Money_Account:
		return PlayerBaseData->Body.Money_Account;
	case EM_RoleValue_Money_AccountLock:
		return PlayerTempData->LockAccountMoney;

	case EM_RoleValue_TitleID:
		return BaseData.TitleID;

	case EM_RoleValue_PlayTimeQuota:
		return PlayerBaseData->PlayTimeQuota;

	case EM_RoleValue_FinStr:
		return TempData.Attr.Fin.STR;

	case EM_RoleValue_FinSta:
		return TempData.Attr.Fin.STA;

	case EM_RoleValue_FinInt:
		return TempData.Attr.Fin.INT;

	case EM_RoleValue_FinMnd:
		return TempData.Attr.Fin.MND;

	case EM_RoleValue_FinAgi:
		return TempData.Attr.Fin.AGI;
		//---------------------------------------------------------------------------------------
		//劇情需要的數值        
		//---------------------------------------------------------------------------------------
	case EM_RoleValue_IsNPC:
		if( IsNPC() )
			return 1.0f;
		return 0.0f;
	case EM_RoleValue_IsPlayer:
		if( IsPlayer() )
			return 1.0f;
		return 0.0f;
	case EM_RoleValue_OrgID:
		return OrgObjID();

	case EM_RoleValue_PID:
		return SelfData.PID;

	case EM_RoleValue_IsWalk:
		return IsWalk();

	case EM_RoleValue_AttackTargetID:
		{
			if( IsAttack() == false || AttackTargetID() < 0 )
			{
				return 0;
			}
			else
			{
				return AttackTargetID();
			}
		}
	case EM_RoleValue_IsAttackMode:
		{
			return IsAttackMode();
		}
		break;
	case EM_RoleValue_IsUnholster:
		{
			return TempData.Attr.Action.Unholster;
		}
		break;
	case EM_RoleValue_PassengerAttackable:
		{
			return BaseData.SysFlag.PassengerAttackable;
		}
		break;
	case EM_RoleValue_AttachObjGUID:
		{
			return TempData.AttachObjID;
		}
		break;
	case EM_RoleValue_BeginAtkDBID:
		{
			return TempData.NPCHate.BeginAtkDBID;
		}
		break;
	case EM_RoleValue_DualTargetDBID:
		{
			if( TempData.Attr.Action.PK )
				return PlayerTempData->PKInfo.TargetDBID;
			return 0;
		}
		break;
	case EM_RoleValue_CastingType:
		{
			return PlayerTempData->CastingType;
		}
		break;
	case EM_RoleValue_SetNPCAttackRange:
		{
			return TempData.Attr.MainAttackRange;
		}
		break;
	case EM_RoleValue_MaxHit:
		{
			NPCHateStruct* pHate = TempData.NPCHate.GetMaxHit();
			if( pHate != NULL ) 
				return pHate->ItemID;
			else
				return 0;
			break;
		}
	case EM_RoleValue_DBID:
		return Base.DBID;
		break;
	case EM_RoleValue_IsDead:
		return IsDead();
		break;
	case EM_RoleValue_GroupID:
		{
			GameObjDbStructEx* ObjDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
			if( ObjDB->IsNPC() == false )
				return 0.0f;
			return ObjDB->NPC.RaceGroupType;
		}
		break;
	case EM_RoleValue_GuildID:
		return BaseData.GuildID;
	case EM_RoleValue_ZoneID:
		return G_ZoneID%1000;
	case EM_RoleValue_RealZoneID:
		return G_ZoneID;
	case EM_RoleValue_HidePlotOwnerDBID:		//(DEBIG)隱藏劇情執行者DBID
		return TempData.HideInfo.OwnerDBID;
	case EM_RoleValue_HidePlotOwnerOrgObjID:		//(DEBIG)隱藏劇情執行者OrgObjID
		return TempData.HideInfo.OwnerOrgID;
	case EM_RoleValue_HouseDBID:
		return PlayerBaseData->HouseDBID;
	case EM_RoleValue_VisitHouseDBID:
		return PlayerTempData->VisitHouseDBID;
	case EM_RoleValue_PetID:
		return TempData.SummonPet.Info[EM_SummonPetType_Normal].PetID;
	case EM_RoleValue_PetID_Cultivate:
		return TempData.SummonPet.Info[EM_SummonPetType_CultivatePet].PetID;
	case EM_RoleValue_GoodEvil:
		return PlayerBaseData->GoodEvil;
	case EM_RoleValue_VocCount:
		return PlayerBaseData->VocCount;
	case EM_RoleValue_BoxEnergy:		//融合箱能量
		return PlayerBaseData->BoxEnergy;
	case EM_RoleValue_MedalCount:		//教導點數
		return PlayerBaseData->MedalCount;
	case EM_RoleValue_BonusMoney:
		return PlayerBaseData->Money_Bonus;
	case EM_RoleValue_MaxLv:
		return PlayerBaseData->MaxLv;
	case EM_RoleValue_SpellMagicID:
		if( IsSpell() == false )
			return 0.0f;
		return TempData.Magic.MagicCollectID;
	case EM_RoleValue_CampID:
		return TempData.AI.CampID;
	case EM_RoleValue_Honor:
		return PlayerBaseData->Honor;
	case EM_RoleValue_DuelistReward:
		return	PlayerBaseData->DuelistReward;
	case EM_RoleValue_TrialBadgeCoin:		//試煉徽章		
		return PlayerBaseData->TrialBadgeCoin;
	case EM_RoleValue_RelicsCoin:			//古代遺物
		return PlayerBaseData->RelicsCoin;
	case EM_RoleValue_DreamlandCoin:		//夢境先遣印記
		return PlayerBaseData->DreamlandCoin;
	case EM_RoleValue_PhiriusShellCoin:		//必爾汀圓貝
		return PlayerBaseData->PhiriusShellCoin;
	case EM_RoleValue_EnergyJusticeCoin:	//正義能量
		return PlayerBaseData->EnergyJusticeCoin;
	case EM_RoleValue_ProofLegendCoin:		//傳說之證
		return PlayerBaseData->ProofLegendCoin;
	case EM_RoleValue_VenderCount:		//傳說之證
		return PlayerBaseData->Defendant.MoneyTraderCount;
	case EM_RoleValue_MirrorCoin:
		return	PlayerBaseData->MirrorCoin;

	case EM_RoleValue_WeekResetCount:
		return PlayerBaseData->WeekResetCount;
	case EM_RoleValue_LockHP:
		return TempData.LockHP;
	case EM_RoleValue_MaxPlantCount:
		return PlayerBaseData->MaxPlantCount;
	case EM_RoleValue_AttackDelay:
		return TempData.AI.AddAtkTime;
	case EM_RoleValue_MoveDelay:
		return TempData.Move.AddeDelay;
	case EM_RoleValue_SlotMachineFreeCount:
		return PlayerBaseData->SlotMachine.FreeCount;
	case  EM_RoleValue_OwnerDBID:
		return TempData.Sys.OwnerDBID;

	case EM_RoleValue_OwnerGUID:			//主人的物件
		return OwnerGUID();
	case EM_RoleValue_DodgeState:			//(最近有)閃避
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastDodgeTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_MissState:			//(最近有)Miss
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastMissTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_ParryState:			//(最近有)Parry
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastParryTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_BeParryState:			//(最近有)被Parry
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeParryTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_BeDodgeState:			//(最近有)被閃避
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeDodgeTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_CritialState:			//(最近有)物理Critial
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastCriticalTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_BeCritialState:		//(最近有)被物理Critial
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeCriticalTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_MagicCritialState:	//(最近有)法術Critial
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastMagicCriticalTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_BeMagicCritialState:	//(最近有)被法術Critial
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeMagicCriticalTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_ShieldBlockState:		//(最近有)盾檔
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastShieldBlockTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_BeShieldBlockState:	//(最近有)被盾檔	
		{
			if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeShieldBlockTime )
				return 0;
			return 1;
		}
	case EM_RoleValue_LastDHp:					//最後一次HP變化量
		return TempData.LastDHp;
	case EM_RoleValue_LastDHpTarget:			//最後一次改變者
		return TempData.LastDHpTarget;

	case EM_RoleValue_Fin_Phy_ATK:
		return TempData.Attr.Fin.ATK;
	case EM_RoleValue_Fin_Phy_Dmg:
		return TempData.Attr.Fin.Main_DMG;
	case EM_RoleValue_Fin_Phy_Def:
		return TempData.Attr.Fin.DEF;

	case EM_RoleValue_Fin_Mag_ATK:
		return TempData.Attr.Fin.MATK;
	case EM_RoleValue_Fin_Mag_Dmg:
		return TempData.Attr.Fin.MDMG;
	case EM_RoleValue_Fin_Mag_Def:
		return TempData.Attr.Fin.MDEF;

	case EM_RoleValue_Fin_Phy_DodgeLv:
		//return TempData.Attr.Mid.Body[ EM_WearEqType_PhyDodgeRate ];
		return TempData.Attr.Fin.DodgeRate;
	case EM_RoleValue_Fin_Phy_HitLv:
		//return TempData.Attr.Mid.Body[ EM_WearEqType_PhyHitRate ];
		return TempData.Attr.Fin.HitRate;
	case EM_RoleValue_Fin_Mag_HitLv:
		//return TempData.Attr.Mid.Body[ EM_WearEqType_MagicHitRate ];
		return TempData.Attr.Fin.MagicHitRate;
	case EM_RoleValue_Fin_Phy_ParryRate:
		return TempData.Attr.Fin.ParryRate;

	case EM_RoleValue_Fin_Phy_CritRate:
		return TempData.Attr.Fin.CriticalHit;
	case EM_RoleValue_Fin_Phy_CritResistRate:
		return TempData.Attr.Fin.ResistCriticalHit;
	case EM_RoleValue_Fin_Phy_CritPower:
		return TempData.Attr.Fin.CriticalHitPower;

	case EM_RoleValue_Fin_Mag_CritRate:
		return TempData.Attr.Fin.MagicCriticalHit;
	case EM_RoleValue_Fin_Mag_CritResistRate:
		return TempData.Attr.Fin.ResistMagicCriticalHit;
	case EM_RoleValue_Fin_Mag_CritPower:
		return TempData.Attr.Fin.MagicCriticalHitPower;
	case EM_RoleValue_SuitSkill_MaxEqSkillCount:
		return PlayerBaseData->SuitSkill.MaxEqSkillCount;
	case EM_RoleValue_SuitSkill_LeanSkillCount:
		return PlayerBaseData->SuitSkill.LeanSkillCount;
	case EM_RoleValue_CliState:
		return TempData.CliState._Mode;
	case EM_RoleValue_AroundPlayer:
		return TempData.AroundPlayer;
	case EM_RoleValue_NpcOnMove:
		{
			if( TempData.Move.Dx != 0 || TempData.Move.Dz != 0 )
				return true;
			return false;
		}
	case EM_RoleValue_IncursivePoint :
		return PlayerBaseData->IncursivePoint;
	case EM_RoleValue_TitleSys_Famous:		//頭銜系統能量
		return PlayerBaseData->TitleSys.Famous;
	case EM_RoleValue_TitleSys_Lv:		//頭銜系統能量
		return PlayerBaseData->TitleSys.Lv;
	case EM_RoleValue_TitleSys_Exp:		//頭銜系統能量
		return PlayerBaseData->TitleSys.Exp;
	case EM_RoleValue_TitleSys_TitleID1:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID2:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID3:		//頭銜系統裝備頭銜
	case EM_RoleValue_TitleSys_TitleID4:		//頭銜系統裝備頭銜
		{
			int ID = Type - EM_RoleValue_TitleSys_TitleID1;
			return PlayerBaseData->TitleSys.TitleID[ID];
		}
	case EM_RoleValue_LastAttackType:			//(全域)最後一次 攻擊類型(OnAttackTypeENUM)
		return RoleDataEx::LastAttackInfo.Type;
	case EM_RoleValue_LastAttackOwnerID:		//(全域)最後一次 被攻擊者
		return RoleDataEx::LastAttackInfo.OwnerID;
	case EM_RoleValue_LastAttackTargetID:		//(全域)最後一次 攻擊者
		return RoleDataEx::LastAttackInfo.TargetID;
	case EM_RoleValue_LastAttackMagColID:		//(全域)最後一次 攻擊法術集合
		return RoleDataEx::LastAttackInfo.MagColID;
	case EM_RoleValue_LastAttackMagBaseID:		//(全域)最後一次 攻擊法術基本
		return RoleDataEx::LastAttackInfo.MagBaseID;
	case EM_RoleValue_LastAttackDamage:			//(全域)最後一次 攻擊傷害量
		return RoleDataEx::LastAttackInfo.Damage;
	case EM_RoleValue_LastAttackDmgType:		//(全域)最後一次 攻擊傷害類型(ATTACK_DMGTYPE_ENUM)
		return RoleDataEx::LastAttackInfo.DmgType;
	case EM_RoleValue_CycleMagicID://目前循環的法術
		return TempData.CycleMagic.MagicID;
	
	case EM_RoleValue_BaseEQ_Str:		//str不算Buff的數值
		return TempData.Attr.BaseEQSTR();
	case EM_RoleValue_BaseEQ_Sta:		//sta不算Buff的數值
		return TempData.Attr.BaseEQSTA();
	case EM_RoleValue_BaseEQ_Int:		//int不算Buff的數值
		return TempData.Attr.BaseEQINT();
	case EM_RoleValue_BaseEQ_Mnd:		//mnd不算Buff的數值
		return TempData.Attr.BaseEQMND();
	case EM_RoleValue_BaseEQ_Agi:		//agi不算Buff的數值
		return TempData.Attr.BaseEQAGI();

	default:
		return 0.0f;
	}

}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::ProxyID( int Value )
{
	TempData.Sys.ProxyID = Value;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::ProxyID( )
{
	return TempData.Sys.ProxyID;
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::SetInitNPC( GameObjDbStructEx* TempDB )
{
	BaseData.Mode.Treasure = false;
	BaseData.Voc  = (Voc_ENUM)TempDB->NPC.Vocation;
	BaseData.Race = (Race_ENUM)TempDB->NPC.Race;
	BaseData.Sex  = (Sex_ENUM)TempDB->NPC.Sex;
	BaseData.Voc_Sub = (Voc_ENUM)TempDB->NPC.Vocation_Sub;
	TempData.Attr.FixArgTableID = 0;
	TempData.Attr.Action.NoReturnAttackPoint = TempDB->NPC.NoReturnAttackPoint;

	BaseData.PartyID = -1;
	TempData.AI.KeepDistance = TempDB->NPC.KeepDistance;

	if( (unsigned)BaseData.Voc >= EM_Max_Vocation )
		BaseData.Voc = EM_Vocation_Warrior;

	if( (unsigned)BaseData.Race >= EM_Max_Race )
		BaseData.Race = EM_Race1;

	if( (unsigned)BaseData.Sex >= EM_Sex_Max_Sex )
		BaseData.Sex = EM_Sex_Boy;

	//TempData.Attr.Ability = NULL;//&PlayerBaseData->AbilityList[ BaseData.Voc ];
	TempData.Attr.Ability = &BaseData.Ability;

	TempData.Attr.SkillValue = &BaseData.SkillValue;
	TempData.Attr.Bas.Resist = TempDB->NPC.Resist;
	PlayerTempData->CastingType = EM_CastingType_NULL;

	TempData.Attr.Ability->STR = TempDB->NPC.STR;
	TempData.Attr.Ability->STA = TempDB->NPC.STA;
	TempData.Attr.Ability->MND = TempDB->NPC.MND;
	TempData.Attr.Ability->INT = TempDB->NPC.INT;
	TempData.Attr.Ability->AGI = TempDB->NPC.AGI;


	TempData.Attr.Bas.Effect._Value[0] = TempDB->NPC.Effect._Value[0];
	TempData.Attr.Bas.Effect._Value[1] = TempDB->NPC.Effect._Value[1];
	TempData.Attr.Bas.IsNoMPSP = TempDB->NPC.IsNoMPSP;


	if( TempDB->NPC.LevelRange > 1 )
		TempData.Attr.Ability->Level = TempDB->NPC.Level  + rand() % TempDB->NPC.LevelRange;
	else
		TempData.Attr.Ability->Level = TempDB->NPC.Level ;

	if( TempData.Attr.Ability->Level > 100 )
		TempData.Attr.Ability->Level  = 100;
/*
	if( TempDB->NPC.LevelRange > 1 )
		TempData.Attr.Level = TempDB->NPC.Level  + rand() % TempDB->NPC.LevelRange;
	else
		TempData.Attr.Level = TempDB->NPC.Level ;

	if( TempData.Attr.Level > 200 )
		TempData.Attr.Level  = 200;
*/
	TempData.Attr.Level = TempData.Attr.Ability->Level;
	TempData.Attr.Level_Sub = TempData.Attr.Ability->Level;
	TempData.Attr.Bas.MoveSpeed_Per = float( TempDB->NPC.MoveSpeed );

	TempData.NPCHate.Init( );

	{
		GameObjDbStructEx* OrgDB;
		//裝備設定
		BaseData.EQ.MainHand.Count      = 1;
		BaseData.EQ.MainHand.OrgObjID   = TempDB->NPC.MainHandEQ[ rand() % _MAX_NPC_EQSEL_COUNT_ ];
		BaseData.EQ.MainHand.ImageObjectID  = BaseData.EQ.MainHand.OrgObjID;
		BaseData.EQ.MainHand.Durable		= 10000;
		BaseData.EQ.MainHand.Quality		= 100;
		BaseData.EQ.MainHand.OrgQuality		= 100;
		BaseData.EQ.MainHand.PowerQuality	= 10;
		BaseData.EQ.MainHand.Rare			= 0;

		OrgDB = St_GetObjDB( BaseData.EQ.MainHand.OrgObjID );
		if( OrgDB->IsWeapon() || OrgDB->IsArmor() )
			BaseData.EQ.MainHand.Level = __min( OrgDB->Item.RefineLv , 20 );

		BaseData.EQ.SecondHand.Count    = 1;
		BaseData.EQ.SecondHand.OrgObjID = TempDB->NPC.SecHandEQ[ rand() % _MAX_NPC_EQSEL_COUNT_ ];
		BaseData.EQ.SecondHand.ImageObjectID  = BaseData.EQ.SecondHand.OrgObjID;
		BaseData.EQ.SecondHand.Durable		= 10000;
		BaseData.EQ.SecondHand.Quality		= 100;
		BaseData.EQ.SecondHand.OrgQuality	= 100;
		BaseData.EQ.SecondHand.PowerQuality	= 10;
		BaseData.EQ.SecondHand.Rare			= 0;

		OrgDB = St_GetObjDB( BaseData.EQ.SecondHand.OrgObjID );
			if( OrgDB->IsWeapon() || OrgDB->IsArmor() )
				BaseData.EQ.SecondHand.Level = __min( OrgDB->Item.RefineLv , 20 );

		BaseData.EQ.Bow.Count    = 1;
		BaseData.EQ.Bow.OrgObjID = TempDB->NPC.BowEQ;
		BaseData.EQ.Bow.ImageObjectID	= TempDB->NPC.BowEQ;
		BaseData.EQ.Bow.Durable			= 10000;
		BaseData.EQ.Bow.Quality			= 100;
		BaseData.EQ.Bow.OrgQuality		= 100;
		BaseData.EQ.Bow.PowerQuality	= 10;
		BaseData.EQ.Bow.Rare			= 0;
		OrgDB = St_GetObjDB( BaseData.EQ.Bow.OrgObjID );
			if( OrgDB->IsWeapon() || OrgDB->IsArmor() )
				BaseData.EQ.Bow.Level = __min( OrgDB->Item.RefineLv , 20 );

		BaseData.EQ.Ornament.Count			= 1;
		BaseData.EQ.Ornament.OrgObjID		= TempDB->NPC.OrnamentEQ;
		BaseData.EQ.Ornament.ImageObjectID	= TempDB->NPC.OrnamentEQ;
		BaseData.EQ.Ornament.Durable		= 10000;
		BaseData.EQ.Ornament.Quality		= 100;
		BaseData.EQ.Ornament.OrgQuality		= 100;
		BaseData.EQ.Ornament.PowerQuality	= 10;
		BaseData.EQ.Ornament.Rare			= 0;
		OrgDB = St_GetObjDB( BaseData.EQ.Ornament.OrgObjID );
			if( OrgDB->IsWeapon() || OrgDB->IsArmor() )
				BaseData.EQ.Ornament.Level = __min( OrgDB->Item.RefineLv , 20 );

	}





	//移動資訊初始化
	memset( &TempData.Move , 0 , sizeof(TempData.Move ) );

	//設定可偷竊的物品 
	if( TempDB->NPC.StealMoney_Rand <= 0 )
		PlayerBaseData->Body.Money = TempDB->NPC.StealMoney_Base;
	else
		PlayerBaseData->Body.Money = TempDB->NPC.StealMoney_Base + rand() % TempDB->NPC.StealMoney_Rand;

	/*
	int Index = 0;
	for( int i = 0 ; i < _MAX_NPC_STEAL_ITEM_COUNT_ ; i++ )
	{
	int TObjID;
	int TCount = 0;
	int	Rate   = TempDB->NPC.StealItem[i].Rate;
	int ItemID = TempDB->NPC.StealItem[i].OrgID;
	int	Count  = 1;

	if( Rate < rand() % 10 *10000 + rand() % 10000 )
	continue;

	if( GetTreasure( ItemID , TObjID  , TCount ) != false )
	{
	ItemID = TObjID;
	Count  = TCount;
	}

	GameObjDbStructEx* OrgDB	= St_GetObjDB( ItemID );
	if( OrgDB->IsItem() == false && OrgDB->IsRecipe() )
	continue;

	St_NewItemInit( PlayerBaseData->Body.Item[Index] , ItemID , 0 );
	PlayerBaseData->Body.Item[Index].Count	  = Count;
	Index++;
	}

	PlayerBaseData->Body.Count = Index;
	*/
	IsWalk( true );
}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::SetInitItem( GameObjDbStructEx* TempDB )
{
	BaseData.Voc_Sub = EM_Vocation_None;
	//TempData.Attr.Ability = NULL;//&PlayerBaseData->AbilityList[0];
	TempData.Attr.Ability = &BaseData.Ability;
	TempData.Attr.SkillValue   = &BaseData.SkillValue;
}
//-----------------------------------------------------------------------------------------
int     RoleDataEx::MirrorCount( )
{
	return TempData.Sys.MirrorCount;
}
//-----------------------------------------------------------------------------------------
bool    RoleDataEx::IsDestroy()
{
	if( SelfData.LiveTime == -1 )
		return false;

	return RoleDataEx::CheckTime( SelfData.LiveTime ) != false;

}
//-----------------------------------------------------------------------------------------
void    RoleDataEx::Destroy( char* Account )
{
	TempData.Sys.DestroyAccount = Account;
	SelfData.LiveTime = RoleDataEx::G_SysTime;
}
//-----------------------------------------------------------------------------------------
BaseAbilityStruct*	RoleDataEx::Ability()
{
	return &PlayerBaseData->AbilityList[ BaseData.Voc ];
}
//-----------------------------------------------------------------------------------------
bool	RoleDataEx::SetAttack(  int TargetID )
{
	RoleDataEx* Target = St_GetRoleData( TargetID );
	if( Target == NULL )
		return false;

	return SetAttack( Target );
}
//設定攻擊某人
bool	RoleDataEx::SetAttack( RoleDataEx* Target )
{
	//檢查目標可不可攻擊
	if( !CheckAttackable( Target ) )
		return false;


	if( TempData.AI.TargetID != Target->GUID() )
	{
		TargetID( Target->GUID() );
		TempData.AI.AttackCount = 1;
	}
	else
	{
		//目前不設定因時差的而累積的次數
		TempData.AI.AttackCount ++;

		if( TempData.AI.AttackCount <= 0 )
			TempData.AI.AttackCount = 1;

		if( TempData.AI.AttackCount  > 2 )
			TempData.AI.AttackCount  = 2;

	}

	if(     IsAttack() == false 
		&&  IsNPC() )  
	{
		IsAttack( true );
		CalHate( Target , 0 , 1 );
		StopMoveNow( );

		ResetAttackSchedular( );
		//設定戰鬥開始劇情
		{
			GameObjDbStructEx* ObjDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
			if( ObjDB->IsNPC()  && strlen( ObjDB->NPC.LuaEvent_BeginAttack) != 0)
			{
				LuaCheckFunction( GUID() , Target->GUID() , ObjDB->NPC.LuaEvent_BeginAttack );
			}
		}
	}
	else
	{
		IsAttack( true );
	}

	return true;
}
//-----------------------------------------------------------------------------------------------
//設定跟隨某人
bool	RoleDataEx::SetFollow( RoleDataEx* Target )
{
	if( Target == NULL )
	{
		TargetID( -1 );
		TempData.Attr.Action.Follow	= false;
	}
	else
	{
		if( !CheckMoveable() )
			return false;

		TargetID( Target->GUID() );
		TempData.Attr.Action.Follow	= true;
	}
	//    TempData.AI.MoveAiType = EM_NPC_MOVETYPE_FOLLOW;

	return true;
}
//-----------------------------------------------------------------------------------------------
//設定停止攻擊
bool	RoleDataEx::SetAtkFolOff( )
{
	if( TempData.Attr.Action.Attack == false)
		return false;


	if( IsNPC() )
	{
		ClearHate( );
		GameObjDbStructEx* ObjDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
		if( ObjDB->IsNPC()  && strlen( ObjDB->NPC.LuaEvent_EndAttack) != 0)
		{
			LuaCheckFunction( GUID() , GUID() , ObjDB->NPC.LuaEvent_EndAttack );
		}
	}

	TempData.Attr.Action.Attack = false;
	TempData.Attr.Action.Follow = false;
	TempData.AI.AttackCount = 0;

	TargetID( -1 );

	return true;
}
//-----------------------------------------------------------------------------------------------
void    RoleDataEx::Dead( bool Value )
{
	TempData.Attr.Action.Dead = Value;
	TempData.AI.ActionType	= Value? EM_ActionType_DEAD : EM_ActionType_NORMAL;

	if( Value != false )
	{
		memset( TempData.BuffTimeDesc , 0 , sizeof(TempData.BuffTimeDesc) );
	}
}
//-----------------------------------------------------------------------------------------------
//取得升級需要的 Exp
int    RoleDataEx::GetLVExp( Voc_ENUM Voc )
{
	if( Voc == EM_Vocation_None )
		return 0;

	int	Level = PlayerBaseData->AbilityList[Voc].Level;

	if(		Level > (int)RoleDataEx::JobExpTable.size() 
		||	Level <= 0 )
		return 0;

	return RoleDataEx::JobExpTable[ Level - 1 ];
}
//----------------------------------------------------------------------------------------
int		RoleDataEx::GetExp( Voc_ENUM Voc )
{
	if( Voc == EM_Vocation_None )
		return 0;

	return PlayerBaseData->AbilityList[Voc].EXP;
}

//----------------------------------------------------------------------------------------
void RoleDataEx::InitNPCData( )
{
	//取得物件資料
	GameObjDbStructEx* OrgDB	= St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( OrgDB == NULL )
		return;

	//關閉攻擊狀態
	SetAtkFolOff();

	//設定等級與偏差資料
	SetInitNPC( OrgDB );

	TempData.Attr.Action._Action = 0;
	TempData.Attr.LAction._Action = -1;
	TempData.Attr.Action.NoReturnAttackPoint = OrgDB->NPC.NoReturnAttackPoint;

	PlayerTempData->CastingType = EM_CastingType_NULL;
	//	TempData.Attr.Bas.Resist = OrgDB->NPC.Resist;

	//清除 Buff
	BaseData.Buff.Clear();
	TempData.Attr.ReSetTable();
	//TempData.Attr.Init_MidValue();
	//ReCalculateMagicAndEQ( );
	ReCalculateEQNoBuff();
	ReCalculateBuff();

	TempData.Attr.Calculate();
	//TempData.Attr.

	TempData.AI.TargetID = -1;
	TempData.AI.LTargetID = -1;
	TempData.AI.KeepDistance = OrgDB->NPC.KeepDistance;			//保持距離

	TempData.NPCHate.Init( );

	BaseData.HP = TempData.Attr.Fin.MaxHP;
	BaseData.MP = TempData.Attr.Fin.MaxMP;
	BaseData.SP = 0;
	BaseData.SP_Sub = 0;
	//PlayerBaseData->Body.Money = OrgDB->NPC.DropMoney_Base + rand()% OrgDB->NPC.DropMoney_Rand;
	TempData.SkillComboID = -1;

	TempData.AI.ActionType		= EM_ActionType_NORMAL;

	TempData.RangePlot.Clear();		//範圍劇情
	TempData.TouchPlot.Clear();		//處發劇情
	TempData.DeadPlot.Clear();		//死亡劇情
	TempData.SayPlot.Clear();		//範圍說話劇情
	TempData.GiveItemPlot.Clear();	//給予處發劇情 ( PCall ) bool GiveItemPlot( int Item1 , int Item2 , int Item3 , int Item4 )
	TempData.CollisionPlot.Clear();	//碰撞劇情

}
//-----------------------------------------------------------------------------------------------
//設定Coldown
bool		RoleDataEx::SetMagicColdown( MagicColdownClassENUM	ColdownClass , int ColdownType , int ColdownTime , int ColdownTimeAllMagic )
{

	if( ColdownTimeAllMagic != 0 )
	{
		BaseData.Coldown.AllMagic = ColdownTimeAllMagic;

		if( BaseData.Coldown.NeedUpdatePos.Find( DEF_COLDOWN_ALL_POS ) == -1 )
			BaseData.Coldown.NeedUpdatePos.Push_Back( DEF_COLDOWN_ALL_POS );
	}

	if( ColdownTime == 0 )
		return true;

	int Pos = -1;

	switch( ColdownClass )
	{
	case EM_MagicColdownClass_None	:		//沒有
		return true;
	case EM_MagicColdownClass_Job	:		//職業類型

		Pos = DEF_COLDOWN_JOB_POS + ColdownType;
		break;
	case EM_MagicColdownClass_EQ	:		//裝備類型
		Pos = DEF_COLDOWN_EQ_POS + ColdownType;
		break;
	case EM_MagicColdownClass_Item	:		//物品類型
		Pos = DEF_COLDOWN_ITEM_POS + ColdownType;
		break;
	}

	if( Pos == -1 || Pos >= DEF_MAX_COLDOWN_COUNT_ALL )
		return false;

	BaseData.Coldown.All[ Pos ] = ColdownTime;

	if( BaseData.Coldown.NeedUpdatePos.Find( Pos ) == -1 )
		BaseData.Coldown.NeedUpdatePos.Push_Back( Pos );		

	return true;
}

//檢查Coldwon
bool    RoleDataEx::CheckMagicColdown( MagicColdownClassENUM	ColdownClass , int ColdownType )
{
	if( BaseData.Coldown.AllMagic > 0 )
		return false;


	int Pos = -1;

	switch( ColdownClass )
	{
	case EM_MagicColdownClass_None	:		//沒有
		return true;
	case EM_MagicColdownClass_Job	:		//職業類型

		Pos = DEF_COLDOWN_JOB_POS + ColdownType;
		break;
	case EM_MagicColdownClass_EQ	:		//裝備類型
		Pos = DEF_COLDOWN_EQ_POS + ColdownType;
		break;
	case EM_MagicColdownClass_Item	:		//物品類型
		Pos = DEF_COLDOWN_ITEM_POS + ColdownType;
		break;
	}

	if( Pos == -1 || Pos >= DEF_MAX_COLDOWN_COUNT_ALL )
		return false;

	if( BaseData.Coldown.All[ Pos ] > 0 )
		return false;

	return true;
}
//-----------------------------------------------------------------------------------------------
//定時處理Coldown
void	RoleDataEx::ColdownProc( )
{
	MagicColdownStruct& Coldown = BaseData.Coldown;
	for( int i = 0 ; i < Coldown.NeedUpdatePos.Size() ; i++ )
	{
		int Pos = Coldown.NeedUpdatePos[i];
		Coldown.All[ Pos ] --;
		if( Coldown.All[ Pos ]  <= 0 )
		{
			Coldown.NeedUpdatePos.Erase( i );
			i--;
			//是否要處發事件
			//....
		}
	}
}
//-----------------------------------------------------------------------------------------------
void	RoleDataEx::RefineColdownProc()
{
	//煉製的Coldown
	for( int i = 0 ; i < PlayerBaseData->RefineColdown.Size() ; i++ )
	{
		int& Coldown = PlayerBaseData->RefineColdown[i].Coldown;
		Coldown --;

		if( Coldown <= 0)
		{
			PlayerBaseData->RefineColdown.Erase( i );
			i--;
		}
	}
}
//-----------------------------------------------------------------------------------------------
//設定角色物件模式
void    RoleDataEx::SetMode( int Mode )
{
	BaseData.Mode._Mode = Mode;
}
//-----------------------------------------------------------------------------------------------
int     RoleDataEx::Level_Sub( )
{
	return TempData.Attr.Level_Sub;
}
//-----------------------------------------------------------------------------------------------
int    RoleDataEx::AttackTargetID()
{
	if( IsAttack() == false )
		return -1;

	return TempData.AI.TargetID;
}

void	RoleDataEx::TargetID( int ID )
{
	if( ID == TempData.AI.TargetID )
		return;

	TempData.AI.LTargetID = TempData.AI.TargetID;
	TempData.AI.TargetID = ID;

	//	if( ID == -1 || IsAttack() )
	Net_NpcAttackTarget( );
}

int    RoleDataEx::OrgObjID()
{
	return BaseData.ItemInfo.OrgObjID;
}
int    RoleDataEx::TargetID()
{
	return TempData.AI.TargetID;
}
//-----------------------------------------------------------------------------------------------
float	RoleDataEx::GetSkillValue( SkillValueTypeENUM SkillID )
{
	if( SkillID >= _MAX_SKILL_COUNT_ )
		return 0;

	return TempData.Attr.Fin.SkillValue.Skill[ SkillID ];
}
//取得武器的技能質
float	RoleDataEx::GetWeaponSkillValue( GameObjectWeaponENUM SkillID )
{
	SkillValueTypeENUM SkillType;
	switch( SkillID )
	{
	case EM_Weapon_Unarmed:			// Unarmed空手
		SkillType = EM_SkillValueType_Unarmed;
		break;
	case EM_Weapon_Blade:           // 劍
		SkillType = EM_SkillValueType_Blade;
		break;
	case EM_Weapon_Dagger:          // 匕首
		SkillType = EM_SkillValueType_Dagger;
		break;
	case EM_Weapon_Wand:            // 權杖
		SkillType = EM_SkillValueType_Wand;
		break;
	case EM_Weapon_Axe:             // 斧
		SkillType = EM_SkillValueType_Axe;
		break;
	case EM_Weapon_Bludgeon:        // 鎚棍棒
		SkillType = EM_SkillValueType_Bludgeon;
		break;
	case EM_Weapon_Claymore:        // 雙手劍
		SkillType = EM_SkillValueType_Claymore;
		break;
	case EM_Weapon_Staff:           // 杖
		SkillType = EM_SkillValueType_Staff;
		break;
	case EM_Weapon_2H_Axe:          // 雙手斧
		SkillType = EM_SkillValueType_2H_Axe;
		break;
	case EM_Weapon_2H_Hammer:       // 雙手鎚
		SkillType = EM_SkillValueType_2H_Hammer;
		break;
	case EM_Weapon_Polearm:			// 槍(長矛)
		SkillType = EM_SkillValueType_Polearm;
		break;
	case EM_Weapon_Bow:				// 遠程武器 弓
		SkillType = EM_SkillValueType_Bow;
		break;
	case EM_Weapon_CossBow:			// 遠程武器 十字弓
		SkillType = EM_SkillValueType_CossBow;
		break;
	case EM_Weapon_Gun:				// 遠程武器 槍
		SkillType = EM_SkillValueType_Gun;
		break;
	default:
		return 0;
	}
	return TempData.Attr.Fin.SkillValue.Skill[ SkillType ];
}
//-----------------------------------------------------------------------------------------------

void	RoleDataEx::AddWeaponSkillValue( int TargetLV , GameObjectWeaponENUM SkillID , float Exp )
{
	SkillValueTypeENUM SkillType;
	switch( SkillID )
	{
	case EM_Weapon_Unarmed:			// Unarmed空手
		SkillType = EM_SkillValueType_Unarmed;
		break;
	case EM_Weapon_Blade:           // 劍
		SkillType = EM_SkillValueType_Blade;
		break;
	case EM_Weapon_Dagger:          // 匕首
		SkillType = EM_SkillValueType_Dagger;
		break;
	case EM_Weapon_Wand:            // 權杖
		SkillType = EM_SkillValueType_Wand;
		break;
	case EM_Weapon_Axe:             // 斧
		SkillType = EM_SkillValueType_Axe;
		break;
	case EM_Weapon_Bludgeon:        // 鎚棍棒
		SkillType = EM_SkillValueType_Bludgeon;
		break;
	case EM_Weapon_Claymore:        // 雙手劍
		SkillType = EM_SkillValueType_Claymore;
		break;
	case EM_Weapon_Staff:           // 杖
		SkillType = EM_SkillValueType_Staff;
		break;
	case EM_Weapon_2H_Axe:          // 雙手斧
		SkillType = EM_SkillValueType_2H_Axe;
		break;
	case EM_Weapon_2H_Hammer:       // 雙手鎚
		SkillType = EM_SkillValueType_2H_Hammer;
		break;
	case EM_Weapon_Polearm:			// 槍(長矛)
		SkillType = EM_SkillValueType_Polearm;
		break;
	case EM_Weapon_Bow:				// 遠程武器 弓
		SkillType = EM_SkillValueType_Bow;
		break;
	case EM_Weapon_CossBow:			// 遠程武器 十字弓
		SkillType = EM_SkillValueType_CossBow;
		break;
	case EM_Weapon_Gun:				// 遠程武器 槍
		SkillType = EM_SkillValueType_Gun;
		break;
	default:
		return;
	}
	AddSkillValue( TargetLV , SkillType , Exp );
}

//計算每打擊一次獲得的技能熟練度
void	RoleDataEx::AddSkillValue( int TargetLV , SkillValueTypeENUM SkillID , float Exp )
{
	if( IsNPC() )
		return;
	if( PlayerBaseData->PlayTimeQuota < 0 )
		return;

	if( PlayerBaseData->PlayTimeQuota < 2*60*60 )
		Exp /=2;


	if( (unsigned) SkillID >= _MAX_SKILLVALUE_TYPE )
		return;
	if( Exp < 0 )
		return;


	float& SkillValue = TempData.Attr.SkillValue->Skill[ SkillID ];
	float MaxSkillValue = TempData.Attr.MaxSkillValue.GetSkill(SkillID);
	if( SkillValue >= MaxSkillValue )
		return;

	if( SkillID == EM_SkillValueType_Plant )
	{
		
		int		SkillLV		= int( SkillValue ); 
//		float	SkillExp	= Exp / PlantExpTable[SkillLV];

		int DLV = SkillLV - TargetLV;
		if( TargetLV == -1 )
			DLV = 0;

		float SkillExp = Exp * GetBaseDLvPlantExp( DLV )/ PlantExpTable[SkillLV];

		if( SkillExp == 0 )
			return;

		AddValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+SkillID)  , SkillExp );
		
	}
	else if( SkillID >= EM_SkillValueType_Mining  )
	{
		int		SkillLV		= int( SkillValue ); 
		float	SkillExp	= Exp / GatherExpTable[SkillLV];

		if( SkillExp == 0 )
			return;

		AddValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+SkillID)  , SkillExp );
	}
	else
		if( SkillID >= EM_SkillValueType_BlackSmith )
		{ //生活計能
			int SkillLV = int( SkillValue ); 

			int DLV = SkillLV - TargetLV;
			if( TargetLV == -1 )
				DLV = 0;

			float SkillExp = Exp * GetBaseLifeSkillDLvExp( DLV )/ RefineExpTable[SkillLV];

			if( SkillExp == 0 )
				return;

			//SkillValue += SkillExp;
			//TempData.Attr.Fin.SkillValue.Skill[ SkillID ] += SkillExp;
			AddValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+SkillID)  , SkillExp );
		}
		else
		{
			int SkillLV =  (int)(SkillValue / ( MaxSkillValue / TempData.Attr.Level ));
			int DLV = TargetLV - SkillLV -1;

			if( TargetLV == -1 )
				DLV = 0;

			if( SkillLV >= (int)SkillExpTable.size() )
				return;

			float SkillExp = Exp * GetBaseDLvExp( DLV )/ SkillExpTable[SkillLV];

			if( SkillExp == 0 )
				return;

			//		SkillValue += SkillExp;
			//		TempData.Attr.Fin.SkillValue.Skill[ SkillID ] += SkillExp;
			AddValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+SkillID)  , SkillExp );
		}

		//	if( SkillValue >= MaxSkillValue )
		//		SkillValue  = MaxSkillValue;

		//	Net_FixRoleValue( (RoleValueName_ENUM)(EM_RoleValue_Skill_Unarmed+SkillID) , (float)SkillValue );
}
//-----------------------------------------------------------------------------------------------
float	RoleDataEx::GetBaseDLvPlantExp( int DLv )
{
	const float ExpArr[ 20 ] = { 1.0f , 0.9f , 0.8f , 0.7f , 0.6f , 0.5f , 0.4f , 0.3f , 0.2f , 0.1f 
		, 0 , 0 , 0, 0, 0, 0, 0, 0 , 0 , 0 };

	if( DLv < 0 )
		DLv = 0;

	if( DLv >= 20 )
		return 0;

	return ExpArr[DLv];
}

float		RoleDataEx::GetBaseDLvExp( int DLV )
{
	//	static float ExpArr[21]={ 5, 10, 20,30,40,50,60,70,80,90,100
	//							,125,150,175,200,225,250,275,300,325,350 };
	static float ExpArr[21]={ 0.05f,0.08f,0.10f,0.13f,0.18f,0.24f,0.32f,0.42f,0.56f,0.75f,1.00f
		,1.20f,1.44f,1.73f,2.07f,2.49f,2.99f,3.58f,4.30f,5.16f,6.19f };

	DLV += 10;
	if( DLV < 0)
		return 0;

	if( DLV > 20 )
		DLV = 20;

	return ExpArr[DLV];
}

float	RoleDataEx::GetBaseLifeSkillDLvExp( int DLV )
{
	//	const float LifeSkillDLvRate[ 20 ] = { 1.0f , 0.76f , 0.58f , 0.44f , 0.33f , 0.25f , 0.19f , 0.15f , 0.11f , 0.08f 
	//											, 0 , 0 , 0, 0, 0, 0, 0, 0 , 0 , 0 };
	const float LifeSkillDLvRate[ 20 ] = { 1.0f , 0.9f , 0.8f , 0.7f , 0.6f , 0.5f , 0.4f , 0.3f , 0.2f , 0.1f 
		, 0 , 0 , 0, 0, 0, 0, 0, 0 , 0 , 0 };

	if( DLV < 0 )
		DLV = 0;

	if( DLV >= 20 )
		return 0;

	return LifeSkillDLvRate[DLV];

}

int		RoleDataEx::PartyID()
{
	return BaseData.PartyID;
}

bool	RoleDataEx::SetPetSkill( )
{


	for( int x = 0 ; x < EM_SummonPetType_Max ; x++ )
	{
		PetStruct& SummonPet = TempData.SummonPet.Info[x];

//		set< int > ActiveMagicSet;
//		ActiveMagicSet.clear();

		//取得寵物法術
		GameObjDbStructEx* PlayerMagicCol;
		GameObjDbStructEx* MagicBase = St_GetObjDB( SummonPet.MagicID );
		if( MagicBase == NULL )
			continue;

		StaticVector< PetSkillStruct , _MAX_PET_SKILL_COUNT_ >&	PetSkill = SummonPet.Skill;

/*
		for( int i = 0 ; i < PetSkill.Size() ; i++ )
		{
			if( PetSkill[i].IsActive != false )
			{
				ActiveMagicSet.insert( PetSkill[i].MagicColID );
			}
		}
*/
		PetSkill.Clear();

		int PetSkillType[3] = { MagicBase->MagicBase.SummonCreature.SkillType[0] , 
			MagicBase->MagicBase.SummonCreature.SkillType[1] ,
			MagicBase->MagicBase.SummonCreature.SkillType[2]  };

		PetSkillStruct SkillTemp;
		for( int i = 0 ; i < _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ +  _MAX_EQ_Skill_COUNT_ + _MAX_Lua_Skill_COUNT_ ; i++ )
		{
			PlayerMagicCol = St_GetObjDB( PlayerTempData->Skill.AllSkill[i] );
			if( PlayerMagicCol == NULL || PlayerMagicCol->MagicCol.PetSkillType == -1 )
				continue;

			if(		PlayerMagicCol->MagicCol.PetSkillType != PetSkillType[0] 
			&&  PlayerMagicCol->MagicCol.PetSkillType != PetSkillType[1] 
			&&  PlayerMagicCol->MagicCol.PetSkillType != PetSkillType[2] 	)
				continue;

			SkillTemp.MagicColID = PlayerMagicCol->GUID;
			SkillTemp.MagicLv	 = GetMagicLv( i );

/*			if( ActiveMagicSet.find( SkillTemp.MagicColID ) == ActiveMagicSet.end() )
				SkillTemp.IsActive = false;
			else
				SkillTemp.IsActive = true;
				*/
			PetSkill.Push_Back( SkillTemp );
		}
	}

	return true;
}
/*
int		RoleDataEx::ZoneKey()		//進入區域設定的Key
{
	return PlayerBaseData->ZoneKey;
}
void	RoleDataEx::SetZoneKey()
{
	static int KeyValue = 100;
	PlayerBaseData->ZoneKey = KeyValue++;
}
*/