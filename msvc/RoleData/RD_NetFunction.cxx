#ifdef _LOCAL_SERVER_
#include "RoleDataEx.h"
#include "../NetWalker_Member/NetWakerGSrvInc.h"
#include "../mainproc/partyinfolist/PartyInfoList.h"
#include "smallobj/SmallObj.h"
#include "debuglog/errormessage.h"
//------------------------------------------------------------------------------------------------------
void RoleDataEx::Net_Mir_SetNumber( RoleValueName_ENUM ValueID , float Value )
{
    if( MirrorCount() == 0 )
        return;
    CNetSrv_PartExchangeData::SettingNumber( TempData.Sys.GUID , ValueID , Value );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_AddHP( int DHp )
{
    if( IsMirror() == false )
        return;
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_AddMP( int DMp )
{
    if( IsMirror() == false )
        return;
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_AddMagBuf( int MagicID , int Time  )
{
    if( IsMirror() == false )
        return;
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Msg( const wchar_t* Str )
{
    NetSrv_Talk::SysMsg( TempData.Sys.GUID , WCharToUtf8( Str ).c_str() );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Msg( const char* Str )
{
	NetSrv_Talk::SysMsg( TempData.Sys.GUID , CharToUtf8( Str ).c_str() );
}
void    RoleDataEx::Msg_Utf8( const char* Str )
{
	NetSrv_Talk::SysMsg( TempData.Sys.GUID , Str );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Tell( const char* Name , const char* Str )
{
    NetSrv_Talk::TalkTo( GUID() , true , Name , RoleName() , Str );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Say( const char* Str )
{
    NetSrv_Talk::Range( GUID() , true , Str, false );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_ItemInBuffer( ItemFieldStruct& Item )
{
    NetSrv_Item::NewItemInBuffer( TempData.Sys.GUID , Item );
}
//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_FixMoney( )
{
    NetSrv_Item::FixMoney( TempData.Sys.GUID , PlayerBaseData->Body.Money , PlayerBaseData->Bank.Money , PlayerBaseData->Body.Money_Account , PlayerBaseData->Money_Bonus );
}
void    RoleDataEx::Net_FixItemInfo_Body( int Pos )
{
    ItemFieldStruct* Item = GetBodyItem( Pos );
    if( Item != NULL )
        NetSrv_Item::FixItemInfo_Body( GUID() , *Item , Pos );
}
void    RoleDataEx::Net_FixItemInfo_Bank( int Pos )
{
    ItemFieldStruct* Item = GetBankItem( Pos );
    if( Item != NULL )
        NetSrv_Item::FixItemInfo_Bank( GUID() , *Item , Pos );
}
void    RoleDataEx::Net_FixItemInfo_EQ( int Pos )
{
    ItemFieldStruct* Item = GetEqItem( Pos );
    if( Item != NULL )
        NetSrv_Item::FixItemInfo_EQ( GUID() , *Item , Pos );
}
void    RoleDataEx::Net_FixItemInfo     (  int Pos , int Type )
{
    ItemFieldStruct* Item = GetItem( Pos , Type );
    if( Item != NULL )
        NetSrv_Item::FixItemInfo( GUID() , *Item , Pos , Type );
}

void	RoleDataEx::Net_FixKeyItemFlag	( int KeyItemID , bool Value )
{
	NetSrv_Item::FixKeyItemFlag( GUID() , KeyItemID , Value );
}

void	RoleDataEx::Net_FixTitleFlag	( int TitleObjID , bool Value )
{
	NetSrv_Item::FixTitleFlag( GUID() , TitleObjID , Value );
}
void	RoleDataEx::Net_FixCardFlag	( int TitleObjID , bool Value )
{
	NetSrv_Item::FixCardFlag( GUID() , TitleObjID , Value );
}

//------------------------------------------------------------------------------------------------------
void    RoleDataEx::Net_FixRoleValue( RoleValueName_ENUM	ValueName , double Value )
{
    NetSrv_RoleValue::S_FixRoleValue(  TempData.Sys.GUID , ValueName , Value );
}
//--------------------------------------------------------------------------------------------
//Fix Look Eq
//--------------------------------------------------------------------------------------------
void    RoleDataEx::Net_FixLookEQ( )
{
    NetSrv_MoveChild::Send_LookEq( this );
}
//--------------------------------------------------------------------------------------------
//其他Server有的功能
//--------------------------------------------------------------------------------------------
void    RoleDataEx::FixAttackMode( )
{
    Global::FixAttackMode( this );
}

void	RoleDataEx::Net_SendRangeAttackMode( bool Mode )
{
	NetSrv_AttackChild::SendRangeAttackMode( this , Mode );
}
//--------------------------------------------------------------------------------------------
//魔法
//--------------------------------------------------------------------------------------------
void    RoleDataEx::Net_ClearAssistMagic( int MagicID , int BuffOwnerID )
{
    NetSrv_MagicChild::S_ClearAssistMagic_Range( GUID() , MagicID , BuffOwnerID );
}

void    RoleDataEx::Net_FixAssistMagicTime( int MagicID , int Time , int BuffOwnerID  )
{
	NetSrv_MagicChild::S_FixAssistMagicTime( GUID() , MagicID , Time , BuffOwnerID );
}
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
void    RoleDataEx::Net_MoveSpeed()
{
    NetSrv_MoveChild::SendRange_MoveSpeed( this );
}
//--------------------------------------------------------------------------------------------
//通知週圍升級
//--------------------------------------------------------------------------------------------

void    RoleDataEx::Net_NotifyLvUp()
{
    NetSrv_RoleValueChild::NotifyLvUp( this );
}

//--------------------------------------------------------------------------------------------
//通知週角色改職業或升級
//--------------------------------------------------------------------------------------------
void    RoleDataEx::Net_ChangeRoleInfo()
{
	NetSrv_RoleValueChild::SendRangeRoleInfo( this );
}
//--------------------------------------------------------------------------------------------
//通知週圍HPMPSP
//--------------------------------------------------------------------------------------------
void    RoleDataEx::Net_MaxHPMaxMPMaxSP()
{
    NetSrv_AttackChild::SendRangeMaxHPMPInfo( this );
}

void    RoleDataEx::Net_HPMPSP()
{
    NetSrv_AttackChild::SendRangeHPInfo( this );
}
//儲存資料
void    RoleDataEx::Net_SavePlayer( int Start , int Size , int SaveTime )
{
    Net_DCBase::SavePlayer( St_GetPCenterID( Account_ID() ) , (PlayerRoleData*)this , Start , Size , SaveTime );
}
//--------------------------------------------------------------------------------------------
//通知Chat好有名單改變
//--------------------------------------------------------------------------------------------
/*
void	RoleDataEx::Net_FriendList_ModifyInfo()
{
	NetSrv_FriendList::SChat_ModifyInfo( this );
}
*/
//通知週圍某角色 魔法盾資訊
void	RoleDataEx::Net_MagicShieldInfoRange( int AttackGUID , int UnAttackGUID , int AttackMagicID , int ShieldMagicID , int AbsobDamage )
{
	NetSrv_MagicChild::MagicShieldInfoRange	( AttackGUID , UnAttackGUID , AttackMagicID , ShieldMagicID , AbsobDamage );
}

void	RoleDataEx::Net_NpcAttackTarget( )
{
	NetSrv_AttackChild::SendRangeNpcAttackTarget( this );
}
//要求NPC移到某一點
void	RoleDataEx::Net_MoveObj( )
{
	NetSrv_MoveChild::MoveObj( this );
}


void	RoleDataEx::Net_SendRangeMove( ClientMoveTypeENUM Type )
{
	NetSrv_MoveChild::SendRangeMove( this , Type );
}

//--------------------------------------------------------------------------------------------
//送遊戲事件訊息
void	RoleDataEx::Net_GameMsgEvent( GameMessageEventENUM Event )
{
	NetSrv_Talk::GameMsgEvent( GUID() , Event );
}
//--------------------------------------------------------------------------------------------
//Log處理
void	RoleDataEx::Log_ItemTrade( RoleDataEx* FromRole , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note )
{
	if( IsPlayer() == false )
		return;

	int		FromPlayerDBID = -1;
	int		FromNpcDBID = -1;

	if( FromRole != NULL )
	{
		if( FromRole->IsPlayer() )
			FromPlayerDBID = FromRole->DBID();
		else
			FromNpcDBID = FromRole->DBID();
	}


	Global::Log_ItemTrade( FromPlayerDBID , FromNpcDBID , DBID() , int( X() ) , int( Z() ) , Type , Item , Note );
}
void	RoleDataEx::Log_ItemTrade	( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note )
{
	if( IsPlayer() == false )
		return;

	Global::Log_ItemTrade( FromRoleDBID , FromNpcDBID , DBID() , int( X() ) , int( Z() ) , Type , Item , Note );
}

void	RoleDataEx::Log_ItemDestroy	( ActionTypeENUM Type , ItemFieldStruct& Item , int ItemCount , const char* Note)
{
	Global::Log_ItemDestroy( this , Type , Item , ItemCount , -1 , Note );
}
void	RoleDataEx::Log_Money( RoleDataEx* FromRole , ActionTypeENUM Type , int Money )
{
	if( IsPlayer() == false )
		return;

	int		FromPlayerDBID = -1;
	int		FromNpcDBID = -1;

	if( FromRole != NULL )
	{
		if( FromRole->IsPlayer() )
			FromPlayerDBID = FromRole->DBID();
		else
			FromNpcDBID = FromRole->DBID();
	}

	if( TempData.Sys.GM_Designed != false )
		return ;

	Global::Log_Money( FromPlayerDBID , FromNpcDBID , this , Type , Money );
}
void	RoleDataEx::Log_Money_Account( RoleDataEx* FromRole , ActionTypeENUM Type , int Money )
{
	if( IsPlayer() == false )
		return;

	int		FromPlayerDBID = -1;
	int		FromNpcDBID = -1;

	if( FromRole != NULL )
	{
		if( FromRole->IsPlayer() )
			FromPlayerDBID = FromRole->DBID();
		else
			FromNpcDBID = FromRole->DBID();
	}

	if( TempData.Sys.GM_Designed != false )
		return ;

	Global::Log_Money_Account( FromPlayerDBID , FromNpcDBID , this , Type , Money );
}
void	RoleDataEx::Log_DepartmentStore( ItemFieldStruct& Item , ActionTypeENUM Type , int Count , int Cost , int Cost_Bonus , int Cost_Free , int PlayerDBID )
{
	Global::Log_DepartmentStore	( Item , Type , Count , Cost , Cost_Bonus , Cost_Free , PlayerDBID	);
}

void	RoleDataEx::Log_Money_Bonus( RoleDataEx* FromRole , ActionTypeENUM Type , int Money )
{
	if( IsPlayer() == false )
		return;

	int		FromPlayerDBID = -1;
	int		FromNpcDBID = -1;

	if( FromRole != NULL )
	{
		if( FromRole->IsPlayer() )
			FromPlayerDBID = FromRole->DBID();
		else
			FromNpcDBID = FromRole->DBID();
	}

	if( TempData.Sys.GM_Designed != false )
		return ;

	Global::Log_Money_Bonus( FromPlayerDBID , FromNpcDBID , this , Type , Money );
}
void	RoleDataEx::Log_Money( int FromPlayerDBID , int FromNpcDBID  , ActionTypeENUM Type , int Money )
{
	if( IsPlayer() == false )
		return;

	if( TempData.Sys.GM_Designed != false )
		return ;

	Global::Log_Money( FromPlayerDBID , FromNpcDBID , this , Type , Money );
}
void	RoleDataEx::Log_Money_Account( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , int Money )
{
	if( IsPlayer() == false )
		return;

	if( TempData.Sys.GM_Designed != false )
		return ;

	Global::Log_Money_Account( FromRoleDBID , FromNpcDBID , this , Type , Money );
}
void	RoleDataEx::Log_PlayerActionLog()
{
	Global::Log_PlayerActionLog( this );
}

void	RoleDataEx::Log_AddExp( int OldExp )
{
	Global::Log_AddExp( this , OldExp );
}

void	RoleDataEx::Log_Level( )
{
	Global::Log_Level( this );
}
void	RoleDataEx::Log_Dead( RoleDataEx* Killer )
{
	Global::Log_Dead( this , Killer );
}
void	RoleDataEx::Log_SkillLv		( int SkillType , int SkillValue )
{
	Global::Log_SkillLv( this , SkillType , SkillValue );
}

void	RoleDataEx::Net_SendChat_ChangeRoleInfo( )
{
	OnlinePlayerInfoStruct Info;
	GetOnlinePlayerInfo( Info );

	NetSrv_ChannelBase::ChangeRoleInfo( Base.Account_ID.Begin() , Info );
}

void	RoleDataEx::Net_SendGM_ObjInfo( )
{
	NetSrv_GMTools::S_ObjInfo( DF_NO_LOCALID , this );
}

//角色特效通知
void	RoleDataEx::Net_SendRangeSpecialEfficacy( SpecialEfficacyTypeENUM	EffectType )
{
	NetSrv_MoveChild::SendRangeSpecialEfficacy( GUID() , EffectType );
}

//系統訊息通知
/*
void	RoleDataEx::Net_SystemMessage		( int Msg )
{
	NetSrv_Other::S_SystemMessage( GUID() , (SystemMessageENUM)Msg );
}
*/
/*
void	RoleDataEx::Net_SystemMessageData	( int Msg , int size , const char* Data )
{
	NetSrv_Other::S_SystemMessageData( GUID() , (SystemMessageDataENUM)Msg , size , Data );
}
*/

//通知裝爆
void	RoleDataEx::Net_EQBroken			( EQWearPosENUM Pos )
{
	NetSrv_EQ::S_EQBroken			( GUID() ,  Pos );
}

void	RoleDataEx::Net_DeltaRoleValue		( RoleValueName_ENUM ValueName , double Value )
{
	if( Value == 0 )
		return;

	NetSrv_RoleValue::S_DeltaRoleValue( GUID() , ValueName , Value );
}

//檢查是否為敵對公會
bool	RoleDataEx::CheckGuildWarDeclare	( RoleDataEx* Target )
{
	return GuildManageClass::This()->IsWarDeclare( BaseData.GuildID , Target->BaseData.GuildID );
}

void	RoleDataEx::Net_ItemTimeout			( ItemFieldStruct& Item , ItemTimeoutPosENUM PosType )
{
	NetSrv_Item::S_ItemTimeout( GUID() , PosType  , Item );
}

PartyInfoStruct*	RoleDataEx::GetPartyInfo( )
{
	return PartyInfoListClass::This()->GetPartyInfo( PartyID() );
}

void	RoleDataEx::ResetAttackSchedular( )
{
	Global::ResetAttackSchedular( this );
}

void	RoleDataEx::CallLuaFunc( int TargetID , char* LuaScript )
{
	BaseItemObject* OwnerObj = Global::GetObj( GUID() );
	if( OwnerObj == NULL )
		return;
	OwnerObj->PlotVM()->CallLuaFunc( LuaScript , TargetID );
}

void	RoleDataEx::Net_AccountMoneyLockInfo( )
{
	NetSrv_Other::SC_AccountMoneyLockInfo( GUID() , this->PlayerBaseData->LockAccountMoney , this->PlayerBaseData->LockAccountMoney_Forever );
}


void	RoleDataEx::GoodEvilAtkInfoProc( RoleDataEx* DefTarget , int DHP )
{
	Global::GoodEvilAtkInfoProc( this , DefTarget , DHP );
}

//送物件刪除的訊息給Client
void	RoleDataEx::Net_SC_DelItemMsg( ItemFieldStruct& Item )
{
	NetSrv_Item::SC_DelItemMsg( GUID() , Item );
}

void	RoleDataEx::Print( int LV , const char* Title , const char* format , ... )
{
	try
	{
		if( g_pPrint == NULL )
			return;
		va_list Marker =(char*)&format + sizeof(format);
		g_pPrint->Print( LV , Title , format , Marker );
	}
	catch(...)
	{
		printf( "\nPrint Crash");
	}
}
bool	RoleDataEx::LuaCheckFunction	( int OwnerID , int TargetID , const char* LuaScript )
{
	return Global::LuaCheckFunction( OwnerID , TargetID , LuaScript );
}
void	RoleDataEx::AutoUseItem( GameObjDbStructEx* ItemDB )
{
	Global::AutoUseItem( this , ItemDB );
}

void RoleDataEx::Net_BillingNotify( const char* Account, int RoleDBID, int Count )
{
	Net_BillingChild::SB_AddAccountMoney(Account, RoleDBID, Count, 0);
}
#endif