#include "RoleDataEx.h"
#include <math.h>
#include <set>

bool    RoleDataEx::IsPlayer( )
{
	return ( Base.Type == EM_ObjectClass_Player );
}

bool    RoleDataEx::IsNPC( )
{
	return ( Base.Type == EM_ObjectClass_NPC || Base.Type == EM_ObjectClass_QuestNPC );
}
bool    RoleDataEx::IsMine( )
{
	return ( Base.Type == EM_ObjectClass_Mine );
}
bool	RoleDataEx::IsQuestNPC()
{
	return ( Base.Type == EM_ObjectClass_QuestNPC );
}

bool    RoleDataEx::IsItem( )
{
	return ( Base.Type == EM_ObjectClass_Item );
}

bool    RoleDataEx::IsFlag( )
{
	return ( Base.Type == EM_ObjectClass_Flag );
}

bool	RoleDataEx::IsMirror()
{
	return ( TempData.Sys.ZoneID != G_ZoneID );
}

bool RoleDataEx::IsBodyEmpty( int Pos )
{
	if( PlayerBaseData->Body.Item[Pos].OrgObjID == 0 )
		return true;

	return false;
}

bool RoleDataEx::IsBankEmpty( int Pos )
{
	if( PlayerBaseData->Bank.Item[Pos].OrgObjID == 0 )
		return true;

	return false;
}

bool    RoleDataEx::IsAttack( )
{
	return TempData.Attr.Action.Attack;
}

void    RoleDataEx::IsAttack( bool Value )
{
	TempData.Attr.Action.Attack = Value;
}
bool    RoleDataEx::IsSit( )
{
	return TempData.Attr.Action.Sit;
}

bool	RoleDataEx::IsDisableClick()
{
	return TempData.Attr.Action.DisableClick;

}


bool	RoleDataEx::IsDisableQuest()
{
	return TempData.Attr.Action.DisableQuest;
}

void    RoleDataEx::IsSit( bool Value )
{
	TempData.Attr.Action.Sit = Value;
}

bool    RoleDataEx::IsAttackMode( )
{
	return TempData.Attr.Action.AttackMode;
}

void    RoleDataEx::IsAttackMode( bool Value )
{
	if( Value == TempData.Attr.Action.AttackMode )
		return;

	TempData.Attr.Action.AttackMode = Value;

	if( Value == false )
	{
		ClearHate( );
		TempData.BackInfo.BuffClearTime.OnStopAttackMode = true;
//		SetValue( EM_RoleValue_SoulPoint , 0 , NULL );
	}
	else
	{
		TempData.Attr.Action.Sit = false;
		//Log記錄
		PlayerTempData->Log.ActionMode.Fight = true;
	}

	Net_SendRangeAttackMode( Value );
}

bool    RoleDataEx::IsMove( )
{

	return RoleDataEx::CheckTime( TempData.Move.LastMoveTime ) == false;
}

bool    RoleDataEx::IsDead( )
{
	return TempData.Attr.Action.Dead;
}

void    RoleDataEx::IsDead( bool Value )
{
	TempData.Attr.Action.Dead = Value;
}

bool    RoleDataEx::IsFollow( )
{
	return TempData.Attr.Action.Follow;
}

void    RoleDataEx::IsFollow( bool Value )
{
	TempData.Attr.Action.Follow = Value;
}

bool    RoleDataEx::IsWalk( )
{
	return TempData.Attr.Action.Walk;
}

void    RoleDataEx::IsWalk( bool Value )
{
	TempData.Attr.Action.Walk= Value;
}

bool    RoleDataEx::IsTrade( )
{
	return TempData.Attr.Action.Trade;
}

void    RoleDataEx::IsTrade( bool Value )
{
	TempData.Attr.Action.Trade = Value;
}

bool    RoleDataEx::IsPet( RoleDataEx* PetOwner )
{
	PetStruct& SummonPet = PetOwner->TempData.SummonPet.Info[ PetOwner->TempData.SummonPet.Type ];

	if( SummonPet.PetID !=  GUID() )
		return false;
	if( OwnerGUID() != PetOwner->GUID() || TempData.Sys.OwnerDBID != PetOwner->DBID() )
		return false;

	return true;
}

bool    RoleDataEx::IsGuard( RoleDataEx* GuardOwner )
{
	PetStruct& SummonPet = GuardOwner->TempData.SummonPet.Info[ GuardOwner->TempData.SummonPet.Type ];

	//檢查是否為寵物
	if( SummonPet.PetID ==  GUID() )
		return false;

	if( OwnerGUID() != GuardOwner->GUID() || TempData.Sys.OwnerDBID != GuardOwner->DBID() )
		return false;

	return true;
}

bool    RoleDataEx::IsSpell()
{
	return ( TempData.Magic.State != EM_MAGIC_PROC_STATE_NORMAL );
}

//************************************************************************************
//攻擊相關資訊
//************************************************************************************
//檢查是否為朋友
bool	RoleDataEx::CheckFriend( RoleDataEx*	Target )
{
	//(暫時)
	if( Target->RoomID() != RoomID() )
		return false;

	RoleDataEx* OTarget = St_GetRoleData( Target->TempData.Sys.OwnerGUID );
	if( OTarget == NULL )
		OTarget = Target;
	RoleDataEx* OThis = St_GetRoleData( TempData.Sys.OwnerGUID );
	if( OThis == NULL )
		OThis = this;

	return Camp.IsFriend( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID );
}
//-----------------------------------------------------------------------------------------------
//檢查是否敵對
bool	RoleDataEx::CheckEnemy( RoleDataEx* Target )
{
	if( Target->RoomID() != RoomID() )
		return false;

	RoleDataEx* OTarget = St_GetRoleData( Target->TempData.Sys.OwnerGUID );
	if( OTarget == NULL )
		OTarget = Target;
	RoleDataEx* OThis = St_GetRoleData( TempData.Sys.OwnerGUID );
	if( OThis == NULL )
		OThis = this;

	if( OTarget == OThis )
		return false;

	if( OTarget->IsPlayer() && OThis->IsPlayer() )
	{
		if( CheckGuildWarDeclare( Target ) != false )
			return true;

		if( OTarget->TempData.Attr.Action.PK != false &&  OThis->TempData.Attr.Action.PK != false  )
		{
			if( OTarget->GUID() == OThis->PlayerTempData->PKInfo.TargetID )
				return true;
		}

//		if(		OTarget->TempData.Attr.Effect.PKFlag_Disabled != false 
//			||  OThis->TempData.Attr.Effect.PKFlag_Disabled != false		)
//			return false;
		
		if( OTarget->PartyID() == OThis->PartyID() && OTarget->PartyID() >= 0 )
			return false;

		if( Camp.IsEnemy( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID ) == true )
			return true;

		if( RoleDataEx::G_IsPvE == false )
		{
			if(		( OTarget->TempData.Attr.Effect.PKFlag != false && OThis->TempData.AI.CampID != EM_CampID_NewHand )
				||	( OThis->TempData.Attr.Effect.PKFlag != false && OTarget->TempData.AI.CampID != EM_CampID_NewHand  )
				||	( OThis->TempData.Attr.Effect.PKFlag != false && OTarget->TempData.Attr.Effect.PKFlag != false )  )
				return true;
		}
		else
		{
			if(	OThis->TempData.Attr.Effect.PKFlag != false && OTarget->TempData.Attr.Effect.PKFlag != false )
				return true;
		}

		switch( OThis->CheckPKType( OTarget ) )
		{
		case 1:
			return true;
		case 2:
			return false;
		}
	}
	else
	{

		if( Camp.IsEnemy( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID ) == true )
			return true;

		if(		OThis->TempData.Attr.Effect.Guilty  
			||	OTarget->TempData.Attr.Effect.Guilty 	)
		{
			if( OThis->GuildID() <= 0 || OThis->GuildID() != OTarget->GuildID() )
			{
				if( OTarget->IsNPC() )
				{
					GameObjDbStructEx* NpcDB = St_GetObjDB( OTarget->BaseData.ItemInfo.OrgObjID );
					if( NpcDB != NULL && NpcDB->NPC.IgnorePvPRule== false )
					{
						if(		OTarget->TempData.AI.CampID == EM_CampID_Good 
							||	OTarget->TempData.AI.CampID == EM_CampID_Evil	)
							return true;
					}
				}

				if( OThis->IsNPC() )
				{
					GameObjDbStructEx* NpcDB = St_GetObjDB( OThis->BaseData.ItemInfo.OrgObjID );
					if( NpcDB != NULL && NpcDB->NPC.IgnorePvPRule== false )
					{
						if(		OThis->TempData.AI.CampID == EM_CampID_Good 
							||	OThis->TempData.AI.CampID == EM_CampID_Evil	)
							return true;
					}
				}
				if( Camp.IsFriend( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID ) == false )
					return true;
			}
		}
	}

	return false;
//	return Camp.IsEnemy( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID );
//	if( Camp.IsEnemy( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID ) == false )
//		return false;

//	if( CheckAttackable_IgnoreDead( Target ) == false )
//		return false;

//	return true;
}
//-----------------------------------------------------------------------------------------------
bool	RoleDataEx::CheckCampHelp( RoleDataEx* Target )
{
	if( Target->RoomID() != RoomID() )
		return false;

	RoleDataEx* OTarget = St_GetRoleData( Target->TempData.Sys.OwnerGUID );
	if( OTarget == NULL )
		OTarget = Target;
	RoleDataEx* OThis = St_GetRoleData( TempData.Sys.OwnerGUID );
	if( OThis == NULL )
		OThis = this;

	return  Camp.IsCanHelp( OThis->TempData.AI.CampID , OTarget->TempData.AI.CampID );
}
//-----------------------------------------------------------------------------------------------
//檢查此物件是否致能
bool	RoleDataEx::CheckEnabled( )
{
	//如果物件死亡或不在分割區則不處理
	if(		TempData.Sys.SecX == -1
		||	TempData.Sys.SecZ == -1				)
		return false;

	return true;
}
//----------------------------------------------------------------------------------------
//檢查是否要收尋敵人
bool	RoleDataEx::CheckSearchEnemy( )
{//(暫時)
	if( ClockMod( 30 ) )
		return false;

	if( !CheckStrikback() )
		return false;

	return BaseData.Mode.Searchenemy;
}
//-----------------------------------------------------------------------------------------------
//pk檢查  回傳 0 未處理 1 成功 2 失敗
int		RoleDataEx::CheckPKType( RoleDataEx* Target )
{
	const int RetNone  = 0;
	const int RetTrue  = 1;
	const int RetFalse = 2;

	if(		IsPlayer() 
		&&	Target->IsPlayer() )
	{
		switch( RoleDataEx::G_PKType )
		{
		case EM_PK_Normal:			//非PK區
			return RetNone;
		case EM_PK_All:				//大亂鬥
			return RetTrue;
		case EM_PK_Party:			//同Party不能互打
			{
				if(		Target->BaseData.PartyID == BaseData.PartyID 
					&&	Target->BaseData.PartyID >= 0 )
					return RetFalse;

				return RetTrue;
			}
		case EM_PK_Party_Guild:		//同Party 同公會 不能互打
			{
				if(		Target->BaseData.PartyID == BaseData.PartyID 
					&&	Target->BaseData.PartyID >= 0 )
					return RetFalse;

				//檢查是否是同公會
				if(		Target->BaseData.GuildID == BaseData.GuildID 
					&&	Target->BaseData.GuildID > 0 )
					return RetFalse;

				return RetTrue;
			}
		}		
	}
	return RetNone;
}

//檢查是否可以攻擊
bool	RoleDataEx::CheckAttackable( RoleDataEx* Target )
{//(暫時)

	if(		Target->TempData.Attr.Action.Dead != false 
		||	TempData.Attr.Action.Dead != false			)
//		||	Target->TempData.Attr.Effect.PlayDead != false )
		return false;

	return CheckAttackable_IgnoreDead( Target );

	/*
	RoleDataEx* Owner       = GetOrgOwner( );
	RoleDataEx* TargetOwner = Target->GetOrgOwner( );

	
	//(暫時)
	//如果在不同的空間中
	if( Target->RoomID() != RoomID() )
		return false;

	if( Target->SecRoomID() == -1 || SecRoomID() == -1 )
		return false;

	//是否同一個主人
	if( TargetOwner->GUID() == Owner->GUID() )
		return false;

	if(		Target->BaseData.Mode.Fight == false )
		return false;

	if(		Target->TempData.Attr.Action.Dead != false 
		||	TempData.Attr.Action.Dead != false			
		||	Target->TempData.Attr.Effect.PlayDead != false )
		return false;

	if( Target->TempData.Attr.Action.PK != false &&  TempData.Attr.Action.PK != false  )
	{
		if( Target->GUID() == PlayerTempData->PKInfo.TargetID )
			return true;
	}

	if( Target->TempData.Attr.Effect.PKFlag != false && TempData.Attr.Effect.PKFlag != false )
		return true;


	switch( Owner->CheckPKType( TargetOwner ) )
	{
	case 1:
		return true;
	case 2:
		return false;
	}
	//--------------------------------------------------------------------
	//檢查公會
	if( Owner->CheckGuildWarDeclare( TargetOwner ) != false )
		return true;


	//陣營檢查
	return  Camp.IsCanAttck( Owner->TempData.AI.CampID , TargetOwner->TempData.AI.CampID );
*/
	
}

//檢查是否可以攻擊
bool	RoleDataEx::CheckAttackable_IgnoreDead( RoleDataEx* Target )
{//(暫時)

	RoleDataEx* Owner       = GetOrgOwner( );
	RoleDataEx* TargetOwner = Target->GetOrgOwner( );

	//(暫時)
	//如果在不同的空間中
	if( Target->RoomID() != RoomID() )
		return false;

	if( Target->SecRoomID() == -1 || SecRoomID() == -1 )
		return false;

	//是否同一個主人
	if( TargetOwner->GUID() == Owner->GUID() )
		return false;

	if(		Target->BaseData.Mode.Fight == false )
		return false;

	/*
	if( 	Target->TempData.AttachObjID > 0
		||	TempData.AttachObjID > 0 )
	{

		return false;
	}
*/
	if(	Target->TempData.AttachObjID > 0 )
	{
		RoleDataEx * TWagon = St_GetRoleData( Target->TempData.AttachObjID );
		if(		TWagon != NULL 
			&&	TWagon->IsPlayer() == false
			&&	TWagon->BaseData.SysFlag.PassengerAttackable == false )
			return false;
	}

	if(	TempData.AttachObjID > 0 )
	{
		RoleDataEx * Wagon = St_GetRoleData( TempData.AttachObjID );
		if(		Wagon != NULL 
			&&	Wagon->IsPlayer() == false 
			&&	Wagon->BaseData.SysFlag.PassengerAttackable == false )
			return false;
	}

	
	if( Owner->IsPlayer() && TargetOwner->IsPlayer() )
	{

		if( TargetOwner->TempData.Attr.Action.PK != false &&  Owner->TempData.Attr.Action.PK != false  )
		{
			if( TargetOwner->GUID() == Owner->PlayerTempData->PKInfo.TargetID )
				return true;
		}

		if(		RoleDataEx::IsDisablePVPRule		== false 
			&&	RoleDataEx::IsDisablePVPRule_Temp	== false )
		{
			if( Owner->TempData.Attr.Effect.PKFlag_Disabled != false || TargetOwner->TempData.Attr.Effect.PKFlag_Disabled != false )
				return false;

			if( TargetOwner->PartyID() == Owner->PartyID() && TargetOwner->PartyID() >= 0 )
				return false;

			if( RoleDataEx::G_IsPvE == false )
			{
				
				if( Owner->PartyID() != TargetOwner->PartyID() || Owner->PartyID() <= 0 )
				{	
					bool OPK = Owner->TempData.Attr.Effect.PKFlag | Owner->TempData.Attr.Effect.Guilty;
					bool TPK = TargetOwner->TempData.Attr.Effect.PKFlag | TargetOwner->TempData.Attr.Effect.Guilty;

					
					if( OPK != false && TPK != false ) 
						return true;

					if( TargetOwner->TempData.AI.CampID != EM_CampID_NewHand  )
					{
						if( OPK != false )
							return true;
						
						if( TargetOwner->TempData.Attr.Effect.Guilty != false )
						{
							if( Owner->TempData.AI.CampID != EM_CampID_NewHand  )
								return true;
						}
					}

				}
				else
				{
					if(	Owner->TempData.Attr.Effect.PKFlag != false && TargetOwner->TempData.Attr.Effect.PKFlag != false  )
					{
						if( Owner->PartyID() != TargetOwner->PartyID() || Owner->PartyID() <= 0 )
							return true;
					}
				}
			}
			else
			{
				if(	Owner->TempData.Attr.Effect.PKFlag != false && TargetOwner->TempData.Attr.Effect.PKFlag != false  )
				{
					if( Owner->PartyID() != TargetOwner->PartyID() || Owner->PartyID() <= 0 )
						return true;
				}
				
			}
		}
		//--------------------------------------------------------------------

		switch( Owner->CheckPKType( TargetOwner ) )
		{
		case 1:
			return true;
		case 2:
			return false;
		}

		//檢查公會
		if( Owner->CheckGuildWarDeclare( TargetOwner ) != false )
			return true;
	}
	else
	{
		if( Owner->PartyID() == TargetOwner->PartyID() && Owner->PartyID() != -1 )
			return false;

//		if(		Owner->TempData.Attr.Effect.Guilty != false 
//			||	TargetOwner->TempData.Attr.Effect.Guilty != false )
//			return true;
		if( Owner->TempData.Attr.Effect.Guilty != false )
		{
			GameObjDbStructEx* ObjDB = St_GetObjDB( TargetOwner->BaseData.ItemInfo.OrgObjID );
			if( ObjDB->IsNPC() == false || ObjDB->NPC.IgnorePvPRule == false )
				return true;
		}
		if( TargetOwner->TempData.Attr.Effect.Guilty != false )
		{
			GameObjDbStructEx* ObjDB = St_GetObjDB( Owner->BaseData.ItemInfo.OrgObjID );
			if( ObjDB->IsNPC() == false || ObjDB->NPC.IgnorePvPRule == false )
				return true;
		}
	}
	
	if( Owner->PartyID() == TargetOwner->PartyID() && Owner->PartyID() != -1 )
		return false;

//	if(		Owner->TempData.Attr.Effect.Guilty != false 
//		||	TargetOwner->TempData.Attr.Effect.Guilty != false )
//		return true;

	//陣營檢查
	return  Camp.IsCanAttck( Owner->TempData.AI.CampID , TargetOwner->TempData.AI.CampID );

}

//-----------------------------------------------------------------------------------------------
//檢查兩物件距離是否可以攻擊
bool	RoleDataEx::CheckMainAttackRange( RoleDataEx* Target )
{
	float Dx = Target->BaseData.Pos.X - BaseData.Pos.X;
	float Dz = Target->BaseData.Pos.Z - BaseData.Pos.Z;
	float Dy = Target->BaseData.Pos.Y - BaseData.Pos.Y;

	if( ( Dy >= 50 || Dy <= -50 ) && IsPlayer() )
		return false;

	if( Target->IsMove() )
	{
		if( sqrt( Dx*Dx + Dz*Dz ) < MainAttackRange( Target) + 15 )
			return true;
	}
	else
	{
		if( sqrt( Dx*Dx + Dz*Dz ) < MainAttackRange( Target) )
			return true;

	}
	return false;
}
//-----------------------------------------------------------------------------------------------
//檢查兩物件距離是否可以攻擊
bool	RoleDataEx::CheckSecAttackRange( RoleDataEx* Target )
{
	float Dx = Target->BaseData.Pos.X - BaseData.Pos.X;
	float Dz = Target->BaseData.Pos.Z - BaseData.Pos.Z;
	float Dy = Target->BaseData.Pos.Y - BaseData.Pos.Y;

	if( Dy >= 50 )
		return false;

	if( Target->IsMove() )
	{
		if( sqrt( Dx*Dx + Dz*Dz ) < SecAttackRange( Target) + 15 )
			return true;
	}
	else
	{
		if( sqrt( Dx*Dx + Dz*Dz ) < SecAttackRange( Target) )
			return true;

	}
	return false;
}
//-----------------------------------------------------------------------------------------------
//檢查是否要計算仇恨值
bool	RoleDataEx::CheckCalHate( )
{
	if( IsPlayer() )
		return false;

	return true;
}
//-----------------------------------------------------------------------------------------------
bool	RoleDataEx::CheckInSight( RoleDataEx* Target , float Angle , float Len )
{

	float TargetLen = Length( Target );

	if( TargetLen < 15 )
		return true;

	//距離檢查
	if( Len < TargetLen )
		return false;

	//角度檢查
	float	Dir = CalDir( Target );

	float DirDF = Dir - BaseData.Pos.Dir;

	if( DirDF > 180 )
		DirDF = 360 - DirDF;
	else if ( DirDF < -180 )
		DirDF += 360;
	else if( DirDF < 0 )
		DirDF *= -1;

	//視角檢查
	if( DirDF > Angle/2 )
		return false;


	return true;
}
//-----------------------------------------------------------------------------------------------
//檢查某物件是否在視野內
bool	RoleDataEx::CheckInSight( RoleDataEx* Target , float Angle , GameObjDbStructEx* OwnerOrgDB )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( OrgDB == NULL )
		return false;

	if( Target->BaseData.Mode.EnemyHide != false )
		return false;


	int DLV = Target->Level() - Level();


	float Rate = 1 - DLV * 0.05f;

	switch( OwnerOrgDB->NPC.Brave )
	{
	case 0://極勇敢		20%  - 150%	(- 5%*等級差)	全打
		if( Rate < 0.2f )
			Rate = 0.2f;
		if( Rate > 1.5f )
			Rate = 1.5f;
		break;
	case 1://勇敢:		50%  - 120%	(- 5%*等級差)	+Lv10
		if( DLV > 10 )
			return false;

		if( Rate > 1.2f )
			Rate = 1.2f;

		break;
	case 2://一般:		85%  - 100%	(- 5%*等級差)	+Lv3
		if( DLV > 3 )
			return false;

		if( Rate > 1 )
			Rate = 1;

		break;
	case 3://有些膽小:	100% - 100%	(- 5%*等級差) 	-Lv1
		if( DLV > -1 )
			return false;

		if( Rate > 1 )
			Rate = 1;

		break;
	case 4://非常膽小:	100% - 100% (- 5%*等級差) 	-Lv5
		if( DLV > -5 )
			return false;

		if( Rate > 1 )
			Rate = 1;
		break;
	}

	GameObjDbStructEx* ImageObjDB = St_GetObjDB( OwnerOrgDB->ImageID ); 
	if( ImageObjDB == NULL )
		return false;

	float Len = OwnerOrgDB->NPC.SearchRange * Rate + ImageObjDB->Image.BoundRadiusY;

	//如果目標裝死
	if( Target->TempData.Attr.Effect.PlayDead && TempData.Attr.Effect.DetectPlayDead == false )
	{
		return false;
	}

	//如果目標為隱形 並且目標沒有偵測隱形
	if( TempData.Attr.Effect.DetectCover == false && Target->TempData.Attr.Effect.Cover != false)
	{
		return false;
	}

	//如果目標在潛行狀態(  )
	if( Target->TempData.Attr.Effect.Sneak && TempData.Attr.Effect.DetectSneak == false )
	{
		Len = float( ImageObjDB->Image.BoundRadiusY + 3 );
		if( DLV < 0 )
		{
			Len = Len + DLV*DLV;
			if( Len >= OwnerOrgDB->NPC.SearchRange )
				Len = float( OwnerOrgDB->NPC.SearchRange );
		}
	}
	float TargetLen = Length3D( Target );

	if( TargetLen < ImageObjDB->Image.BoundRadiusY + 5 )
		return true;

	if( Len < TargetLen )
		return false;

	if( OwnerOrgDB->NPC.SearchEnemyAllDir  )
		return true;

	//角度檢查
	float	Dir = CalDir( Target );

	float DirDF = Dir - BaseData.Pos.Dir;

	if( DirDF > 180 )
		DirDF = 360 - DirDF;
	else if ( DirDF < -180 )
		DirDF += 360;
	else if( DirDF < 0 )
		DirDF *= -1;

	//視角檢查
	if( DirDF > Angle/2 )
		return false;


	return true;
}
//-----------------------------------------------------------------------------------------------
//檢查是否可以要請人入隊伍
bool	RoleDataEx::CheckInvitable( RoleDataEx* Target )
{
	return false;
}
//-----------------------------------------------------------------------------------------------
//簡查是否要停止攻擊
//1 視野=200-1000內 四秒 一次 檢查 有 10% 機率會停止攻擊 
//2 視野=1000 以上 停止功擊
bool	RoleDataEx::CheckStopAttack()
{
	/*
	//每四秒處理一次
	if( ClockMod( 40 ) )
	return false;

	RoleDataEx	*Target = (RoleDataEx*)St_GetRoleData( TempData.AtkFol.TargetID );
	if( Target == NULL )
	return false;

	int Len = Length( Target );

	//
	if( Len > 1000 )
	return true;

	if( rand()%10 == 0  && Len > 200 )
	return true;
	*/
	return false;
}
//-----------------------------------------------------------------------------------------------
//檢查是否可以反擊
bool		RoleDataEx::CheckStrikback( )
{
	return BaseData.Mode.Strikback;
}
//-----------------------------------------------------------------------------------------------
//檢查是否可以移動
bool		RoleDataEx::CheckMoveable( )
{

	return BaseData.Mode.Move && !TempData.Attr.Action.Dead;
}
//-----------------------------------------------------------------------------------------------
bool RoleDataEx::CheckAutoPlot()
{
	if( SelfData.AutoPlot.Size() == 0 )
		return false;
	return true;
}


bool RoleDataEx::CheckClientAutoPlot()
{
	if( TempData.C_AutoPlot.Size() == 0 )
		return false;
	return true;
}

bool RoleDataEx::CheckRangePlot()
{
	if( TempData.RangePlot.Size() == 0 )
		return false;
	return true;
}

bool RoleDataEx::CheckTouchPlot()
{
	if( TempData.TouchPlot.Size() == 0 )
		return false;
	return true;
}

bool RoleDataEx::CheckDeadPlot()
{
	if( TempData.DeadPlot.Size() == 0 )
		return false;
	return true;
}

bool RoleDataEx::CheckSayPlot()
{
	if( TempData.SayPlot.Size() == 0 )
		return false;
	return true;
}
bool RoleDataEx::CheckGiveItemPlot()
{
	if( TempData.GiveItemPlot.Size() == 0 )
		return false;
	return true;
}

//第一次施法檢察
GameMessageEventENUM	RoleDataEx::CheckCanBeginSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic , int MagicLv )
{
	if(		PlayerTempData->CastingType != EM_CastingType_NULL 
		&&	PlayerTempData->CastingType != EM_CastingType_OKRESULT )
		return EM_GameMessageEvent_MagicError_UseItemtoItem;

/*	if( PlayerTempData->CastData->pCastFunc != NULL )
	{
		((GatherCallBackFunc)pCastingData->pCastFunc)( GUID() , EM_GATHER_FAILED );
	}*/
	
	if( Target->SecRoomID() == -1 || SecRoomID() == -1 )
		return EM_GameMessageEvent_MagicError_Target;

	//檢查移動失法問題
	if( TempData.Move.Dx != 0 || TempData.Move.Dz != 0 )
	{
		if( Magic->MagicCol.Flag.Interrupt_OnMove != false && GetSpellTime( Magic ) != 0 )
		{
			if(		Magic->MagicCol.IsDisableSpellBuffEffect == false 
				&&	TempData.Attr.Effect.MagicSpell_Moveable )
			{

			}
			else
				return EM_GameMessageEvent_MagicError_CanNotMove;
		}
	}

	//不可移動衝封
	if( TempData.Attr.Effect.Stop != false && Magic->MagicCol.Flag.Dash )
	{
		return EM_GameMessageEvent_MagicError_Normal;
	}

	if( Magic->MagicCol.IsWaterDisabled != false && TempData.CliState.InWater != false )
	{
		return EM_GameMessageEvent_MagicError_InWater;
	}
	if( Magic->MagicCol.IsWaterEnabled != false && TempData.CliState.InWater == false )
	{
		return EM_GameMessageEvent_MagicError_NotInWater;
	}

	//消耗物品檢查
	if( CheckSpellMagicCost( Target , Magic , MagicLv ) == false)
	{
		//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Request );
		//Msg( "法術 需求有問題 " );
		return EM_GameMessageEvent_MagicError_Request;
	}

	//檢查Coldown
	if( CheckMagicColdown( Magic->MagicCol.Coldown.Class , Magic->MagicCol.Coldown.Type ) == false )
	{
		//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Coldown );
		//Msg( "法術 冷卻中 " );
		return EM_GameMessageEvent_MagicError_Coldown;
	}

	GameMessageEventENUM Ret = CheckCanSpell( Target , TargetX , TargetY , TargetZ , Magic );
	if( Ret != EM_GameMessageEvent_OK )
		return Ret;

	return EM_GameMessageEvent_OK;
}
//檢查是否可以施法
GameMessageEventENUM RoleDataEx::CheckCanSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic )
{
	if( Target == NULL )
		Target = this;

	if( Magic == NULL )
		return EM_GameMessageEvent_MagicError_TargetTooFar;

	//檢查法術技能狀態
	if( Magic->MagicCol.TargetType == EM_Releation_Self )
		Target = this;

	float	AttackDistance = 0;

	if(		Magic->MagicCol.Flag.ReferenceWeapon_Bow 
		||	Magic->MagicCol.Flag.ReferenceWeapon_Bow_SpellTime )
	{
		AttackDistance = TempData.Attr.Fin.Bow_AttackRange;
	}
	else if(	Magic->MagicCol.Flag.ReferenceWeapon_Throw 
		||		Magic->MagicCol.Flag.ReferenceWeapon_Throw_SpellTime	)
	{
		AttackDistance = TempData.Attr.Fin.Throw_AttackRange;
	}

	AttackDistance = float( Magic->MagicCol.AttackDistance + 1 ) + AttackDistance;

	AttackDistance +=( TempData.BoundRadiusY + Target->TempData.BoundRadiusY );


	if( Magic->MagicCol.TargetType == EM_Releation_Locatoin )
	{
		//簡查距離
		if( Length3D( TargetX , TargetY , TargetZ )  > AttackDistance )
		{
			//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_TargetTooFar );
			//Msg( "法術 距離過遠" );
			return EM_GameMessageEvent_MagicError_TargetTooFar;
		}
	}
	else
	{

		//目標檢查
		if( CheckRelation( Target , Magic->MagicCol.TargetType , Magic->MagicCol.IsIgnoreTargetDead  ) == false )
		{
			//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Target );
			//Msg( "法術 不可對此目標施展" );
			return EM_GameMessageEvent_MagicError_Target;
		}

		//簡查距離		
		if( Length3D( Target ) > AttackDistance )
		{
			//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_TargetTooFar );
			//Msg( "法術 距離過遠" );
			return EM_GameMessageEvent_MagicError_TargetTooFar;
		}
	}


	//面向檢查
	if( Length( Target) > 3 )
	{
		if( Magic->MagicCol.Flag.Spell_Back )
		{
			if( Target->CalAngle( this ) < 90 )
			{
				//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Back );
				//Msg( "法術 要在背後施展" );
				return EM_GameMessageEvent_MagicError_Back;
			}
		}

		if( Magic->MagicCol.Flag.Spell_Front )
		{
			if( Target->CalAngle( this ) > 90 )
			{
				//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Front );
				//Msg( "法術 要在前面施展" );
				return EM_GameMessageEvent_MagicError_Front;
			}
		}
	}

	if( Magic->MagicCol.Flag.Spell_LookAtTarget )
	{	
		if( CalAngle( Target ) > 90 )
		{	
			//Net_GameMsgEvent( EM_GameMessageEvent_MagicError_LookAt );
			//Msg( "法術 要面對敵人才可施展" );
			return EM_GameMessageEvent_MagicError_LookAt;
		}	
	}


	return EM_GameMessageEvent_OK;
}
//-----------------------------------------------------------------------------------------------
//與目標關係檢查
bool	RoleDataEx::CheckRelation( RoleDataEx* Target , GameObjectRelationENUM Relation , bool IgnoreDead )
{
	switch( Relation )
	{
	case EM_Releation_Self:			
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( GUID() == Target->GUID() )
				return true;
		}break;
	case EM_Releation_Member:		
		{
			if(	   ( Target->IsDead() && IgnoreDead == false  )
				|| ( Target->TempData.Attr.Action.PK && Target->GUID() != GUID() ) )
				return false;

			if( GUID() == Target->GUID() )
				return true;

			if(		PartyID() == Target->PartyID() 
				&&	PartyID() != -1 )
				return true;

		}break;
	case EM_Releation_Self_Pet:		
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( Target->OwnerGUID() == GUID() )
				return true;
		}break;
	case EM_Releation_Member_Pet:	
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( GUID() == Target->OwnerGUID() )
				return true;

			RoleDataEx* PetOwner = St_GetRoleData( Target->OwnerGUID() );
			if(		PetOwner != NULL 
				&&	PartyID() == PetOwner->PartyID() 
				&&	PartyID() != -1 )
			{
				return true;
			}

		}break;
	case EM_Releation_Friend:		
		{
			if(		( Target->IsDead() && IgnoreDead == false )
				||  ( Target->TempData.Attr.Action.PK && Target->GUID() != GUID() ) )
				return false;

			//載具不處理
			if( Target->IsWagon() != false )
				return false;

			if( GUID() == Target->GUID() )
				return true;

			if(		PartyID() == Target->PartyID() 
				&&	PartyID() != -1 )
				return true;

			return !CheckEnemy( Target );

		}break;
	case EM_Releation_Friend_NPC:	
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( !Target->IsNPC() )
				return false;

			return !CheckEnemy( Target );
		}break;
	case EM_Releation_Enemy:		
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			return CheckAttackable( Target );
		}break;
	case EM_Releation_Player:		
		{
			if(		( Target->IsDead() && IgnoreDead == false )
				||  ( Target->TempData.Attr.Action.PK && Target->GUID() != GUID() ) )
				return false;

			/*
			if( Target->IsPlayer() )
			{
				if(	RoleDataEx::IsPK != false )
				{
					if(		Target->BaseData.PartyID == BaseData.PartyID 
						&&	BaseData.PartyID >= 0 )
						return false;

					if(		Target->BaseData.GuildID == BaseData.GuildID
						&&	BaseData.GuildID >= 0 )
						return false;
				}
				else
					return true;
			}
			*/
			switch( CheckPKType( Target ) )
			{
			case 1:
				return false;
			case 2:
				return true;
			}

			if( Target->IsPlayer() )
				return true;

		}break;
	case EM_Releation_All:
	case EM_Releation_Plot:
		{
			return true;
		}break;
	case EM_Releation_GuildPlayer:	
		{
			if(		( Target->IsDead() && IgnoreDead == false )
				||  ( Target->TempData.Attr.Action.PK && Target->GUID() != GUID() ) )
				return false;

			if( GUID() == Target->GUID() )
				return true;

			if(		GuildID() == Target->GuildID() 
				&&	GuildID() != -1 )
				return true;
		}break;
	case EM_Releation_NotGuildPlayer:
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( GUID() == Target->GUID() )
				return false;

			if(		GuildID() == Target->GuildID() 
				&&	GuildID() != -1 )
				return false;
			else
				return true;
		}break;
	case EM_Releation_Corpse:			//屍體
		{
			if( Target->IsDead() )
				return true;
		}
		break;
	case EM_Releation_Npc_Corpse:		//NPC屍體
		{
			if( !Target->IsDead() )
				return false;

			if( Target->IsNPC() )
				return true;
		}
		break;
	case EM_Releation_Player_Corpse:	//玩家屍體
		{
			if( !Target->IsDead() )
				return false;

			if( Target->IsPlayer() )
				return true;
		}
		break;
	case EM_Releation_Locatoin:			//指定位置( 範圍法術 )
		{
			return true;
		}
		break;
	case EM_Releation_PetOwner:
		{
			if( Target->GUID() == OwnerGUID() )
				return true;
		}
		break;
	case EM_Releation_Wagon:
		{
			if( Target->IsDead() && IgnoreDead == false )
				return false;

			if( Target->IsWagon() == false )
				return false;

			return !CheckEnemy( Target );
		}
		break;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
//簡查施法必要消費
bool	RoleDataEx::CheckSpellMagicCost( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv )
{
	if(		Magic->MagicCol.IsDisableSpellBuffEffect == false 
		&&	TempData.Attr.Effect.MagicSpell_NoCost )
	{
		return true;
	}

	for( int i = 0 ; i < 2 ; i++ )
	{
		if( CheckSpellMagicCostBase( Target , Magic , MagicLv , Magic->MagicCol.Cost[i].Type , Magic->MagicCol.Cost[i].Value ) == false )
			return false;
	}
	return true;
}

bool	RoleDataEx::CheckSpellMagicCostBase( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue )
{
//	MagicSpellCostTypeENUM CostType	= Magic->MagicCol.Cost.Type ;
//	int CostValue	= Magic->MagicCol.Cost.Value;

	if( TempData.Magic.UseItemType >= 0 && TempData.Magic.UseItem != 0 )	
	{
		if( TempData.Magic.IsCheckUseItem != false && TempData.Attr.Effect.UseItemDisable != false )
			return false;
	}
	else if( Magic->MagicCol.EffectType == EM_Magic_Phy && Magic->MagicCol.IsIgnoreSilence == false )
	{
		if( TempData.Attr.Effect.UsePhyDisable  )	
		{
			//Msg( "不可物理攻擊" );
			Net_GameMsgEvent( EM_GameMessageEvent_AttackError_PhyDisable );
			return false;
		}
	}
	else if( Magic->MagicCol.EffectType == EM_Magic_Magic && Magic->MagicCol.IsIgnoreSilence == false )
	{
		if( TempData.Attr.Effect.UseMagicDisable  )	
		{
			//Msg( "不可法術攻擊" );
			Net_GameMsgEvent( EM_GameMessageEvent_AttackError_MagicDisable );
			return false;
		}
	}

	//檢查消費
	switch( CostType )
	{
	case EM_MagicSpellCostType_None:					//無消耗

		break;
	case EM_MagicSpellCostType_HP:						//消耗 HP
		{
			if( BaseData.HP <= CostValue )
			{
				//Msg( "施法 HP不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_HPNotEnough );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_MP:						//消耗 MP
		{
			if( TempData.Attr.Bas.IsNoMPSP != false )
				break;

			if( MPCostPowerRate.size() > (unsigned)MagicLv )
				CostValue = (int)(CostValue * MPCostPowerRate[MagicLv]);
			CostValue =  int( CostValue * ( 100 - TempData.Attr.ManaDecrease() )/100 );   

			if( BaseData.MP < CostValue )
			{		
				//Msg( "施法 MP不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_MPNotEnough );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_HP_Per:						//消耗 HP
		{
			int	Value = (int)( TempData.Attr.Fin.MaxHP * CostValue / 100 );

			if( BaseData.HP <= Value )
			{
				//Msg( "施法 HP不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_HPNotEnough );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_MP_Per:						//消耗 MP
		{
			if( TempData.Attr.Bas.IsNoMPSP != false )
				break;
			int	Value = int( TempData.Attr.Fin.MaxMP * CostValue / 100 );
			//QQ 要把mp消耗減少算進去
			Value =  int( Value * ( 100 - TempData.Attr.ManaDecrease() )/100 );   
			if( BaseData.MP < Value )
			{		
				//Msg( "施法 MP不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_MPNotEnough );
				return false;
			}

		}
		break;
	case EM_MagicSpellCostType_SP_Warrior:		//消耗 SP 戰士	
		{
			if( CostValue == -1 )
				return true;

			if( TempData.Attr.Bas.IsNoMPSP != false )
				break;

			CostValue =  int( CostValue * ( 100 - TempData.Attr.SPWarriorDecrease() )/100 );   

			if(		BaseData.Voc == EM_Vocation_Warrior 
				||	BaseData.Voc == EM_Vocation_Psyron )
			{
				if( BaseData.SP < CostValue )
				{
					//Msg( "戰士 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_WarriorSPNotEnough );
					return false;
				}
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Warrior 
					||	BaseData.Voc_Sub == EM_Vocation_Psyron )
			{
				if( BaseData.SP_Sub < CostValue )
				{
					//Msg( "戰士 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_WarriorSPNotEnough );
					return false;
				}
			}
		}
		break;
	case EM_MagicSpellCostType_SP_Ranger:		//消耗 SP 遊俠
		{
			if( CostValue == -1 )
				return true;

			if( TempData.Attr.Bas.IsNoMPSP != false )
				break;

			CostValue =  int( CostValue * ( 100 - TempData.Attr.SPRangerDecrease() )/100 );   

			if(		BaseData.Voc == EM_Vocation_Ranger 
				||	BaseData.Voc == EM_Vocation_Harpsyn )
			{
				if( BaseData.SP < CostValue )
				{
					//Msg( "遊俠 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_RangerSPNotEnough );
					return false;
				}
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Ranger 
					||	BaseData.Voc_Sub == EM_Vocation_Harpsyn )
			{
				if( BaseData.SP_Sub < CostValue )
				{
					//Msg( "遊俠 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_RangerSPNotEnough );
					return false;
				}
			}
		}
		break;
	case EM_MagicSpellCostType_SP_Rogue:		//消耗 SP 盜賊	
		{
			if( CostValue == -1 )
				return true;

			if( TempData.Attr.Bas.IsNoMPSP != false )
				break;

			CostValue =  int( CostValue * ( 100 - TempData.Attr.SPRogueDecrease() )/100 );   

			if(		BaseData.Voc == EM_Vocation_Rogue 
				||	BaseData.Voc == EM_Vocation_Duelist)
			{
				if( BaseData.SP < CostValue )
				{
					//Msg( "盜賊 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_ThiefSPNotEnough );
					return false;
				}
			}
			else if(	BaseData.Voc_Sub == EM_Vocation_Rogue 
					||	BaseData.Voc_Sub == EM_Vocation_Duelist)
			{
				if( BaseData.SP_Sub < CostValue )
				{
					//Msg( "盜賊 SP不足" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_ThiefSPNotEnough );
					return false;
				}
			}
		}
		break;

	case EM_MagicSpellCostType_StomachPoint:
		{
			if( BaseData.StomachPoint < CostValue )
			{
				//Msg( "吃不下" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_StomachFull );
				return false;
			}
		}break;
	case EM_MagicSpellCostType_Item:					//消耗 物品
		{
			if( CalBodyItemCount( CostValue ) == 0 )
			{
				//Msg( "施法 消耗物品有問題" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_CostItemError );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_Ammo_Gun:				//消耗 子彈
		{
			if( TempData.Attr.BowWeaponType != EM_Weapon_Gun )
			{
				//Msg( "沒有槍" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoGun );
				return false;
			}

			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );
			GameObjDbStructEx*	OrgDB;
			OrgDB = St_GetObjDB( Item->OrgObjID );
			if(		OrgDB->IsWeapon() == false 
				||	OrgDB->Item.WeaponType != EM_Weapon_Ammo_Gun 
				||  OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo 
				||  Item->Mode.EQCannotEquipment != false			)
			{
				//Msg( "施法 沒有子彈" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoGunAmmo );
				return false;
			}

			if( Item->Count < CostValue )
			{
				//Msg( "施法 子彈不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoGunAmmo );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_Ammo_Bow:				//消耗 弓箭矢
		{
			if( TempData.Attr.BowWeaponType != EM_Weapon_Bow )
			{
				//Msg( "沒有弓" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoBow );
				return false;
			}

			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );
			GameObjDbStructEx*	OrgDB;
			OrgDB = St_GetObjDB( Item->OrgObjID );
			if(		OrgDB->IsWeapon() == false 
				||	OrgDB->Item.WeaponType != EM_Weapon_Ammo_Bow
				||  OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo 
				||  Item->Mode.EQCannotEquipment != false		)
			{
				//Msg( "施法 沒有弓箭矢" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoBowAmmo );
				return false;
			}
			if( Item->Count < CostValue )
			{
				//Msg( "施法 弓箭矢不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoBowAmmo );
				return false;
			}

		}
		break;
	case EM_MagicSpellCostType_Ammo_CossBow:			//消耗 十字弓箭矢
		{
			if( TempData.Attr.BowWeaponType != EM_Weapon_Bow )
			{
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoCossBow );
				//Msg( "沒有十字弓" );
				return false;
			}

			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );
			GameObjDbStructEx*	OrgDB;

			OrgDB = St_GetObjDB( Item->OrgObjID );
			if(		OrgDB->IsWeapon() == false 
				||	OrgDB->Item.WeaponType != EM_Weapon_Ammo_Bow 
				||  OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo	
				||  Item->Mode.EQCannotEquipment != false )
			{
				//Msg( "施法 沒有十字弓箭矢" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoCossBowAmmo );
				return false;			
			}
			if( Item->Count < CostValue )
			{
				//Msg( "施法 十字弓箭矢不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoCossBowAmmo );
				return false;
			}

		}
		break;
	case EM_MagicSpellCostType_Ammo_Throw:				//消耗 投擲物
		{

			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );
			GameObjDbStructEx*	OrgDB;
			OrgDB = St_GetObjDB( Item->OrgObjID );
			if(		OrgDB->IsWeapon() == false 
				||	OrgDB->Item.WeaponType != EM_Weapon_Throw 
				||  OrgDB->Item.WeaponPos != EM_WeaponPos_Ammo	
				||  Item->Mode.EQCannotEquipment != false )
			{
				//Msg( "施法 沒有投擲物" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoThrowAmmo );
				return false;	
			}
		}
		break;

	case EM_MagicSpellCostType_Ammo_All:
		{
			if(		TempData.Attr.BowWeaponType != EM_Weapon_CossBow 
				&&	TempData.Attr.BowWeaponType != EM_Weapon_Bow 
				&&	TempData.Attr.BowWeaponType != EM_Weapon_Gun	)
			{
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoAllLongWeapon );
				//Msg( "施法 沒有遠程武器" );
				return false;			
			}


			ItemFieldStruct* Item = GetEqItem( EM_EQWearPos_Ammo );
			GameObjDbStructEx*	OrgDB;
			OrgDB = St_GetObjDB( Item->OrgObjID );

			if(		OrgDB->IsWeapon() == false  
				||  Item->Mode.EQCannotEquipment != false)
			{
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoAmmo );
				//Msg( "施法 沒有彈藥" );
				return false;			
			}

			if(		TempData.Attr.BowWeaponType == EM_Weapon_CossBow
				&&	OrgDB->Item.WeaponType == EM_Weapon_Ammo_Bow 
				&&  OrgDB->Item.WeaponPos == EM_WeaponPos_Ammo	)
			{
				
			}
			else if(		TempData.Attr.BowWeaponType == EM_Weapon_Bow
				&&	OrgDB->Item.WeaponType == EM_Weapon_Ammo_Bow 
				&&  OrgDB->Item.WeaponPos == EM_WeaponPos_Ammo	)
			{
				
			}
			else if(		TempData.Attr.BowWeaponType == EM_Weapon_Gun
				&&	OrgDB->Item.WeaponType == EM_Weapon_Ammo_Gun
				&&  OrgDB->Item.WeaponPos == EM_WeaponPos_Ammo	)
			{
				
			}
			else
			{
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoAmmo );
				return false;
			}


			if( Item->Count < CostValue )
			{
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NoAmmo );
				return false;
			}
		}
		break;
	case EM_MagicSpellCostType_SoulPoint:						//消耗 靈魂值
		{
			if( TempData.SoulPoint < CostValue )
			{
				//Msg( "施法 HP不足" );
				Net_GameMsgEvent( EM_GameMessageEvent_MagicError_SoulPointNotEnough );
				return false;
			}
		}
		break;

	}

	for( int i = 0 ; i < 2 ; i++ )
	{
		//檢查需求
		bool IsFind = false;
		MagicSpellNeedTypeENUM NeedType	= Magic->MagicCol.Need[i].Type ;
		int NeedValue	= Magic->MagicCol.Need[i].Value;

		switch( NeedType )
		{
		case EM_MagicSpellNeedType_None:				//無需求
			break;
		case EM_MagicSpellNeedType_Weapon:				//需求 自己裝 武器
			{
				if(		GetEqItem( EM_EQWearPos_MainHand )->OrgObjID	!= NeedValue 
					&&	GetEqItem( EM_EQWearPos_SecondHand )->OrgObjID	!= NeedValue )
				{
					//Msg( "施法 此武器不可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedWeaponError );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_EQ:					//需求 自己裝 裝備
			{
				for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
				{
					if( BaseData.EQ.Item[i].OrgObjID == NeedValue )
					{
						IsFind = true;
						break;
					}
				}
				if( IsFind == false )
				{
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Suit:				//需求 自己裝 套裝
			{
				int i;
				for( i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
				{
					GameObjDbStructEx*	OrgDB;
					OrgDB = St_GetObjDB( BaseData.EQ.Item[i].OrgObjID  );
					if( OrgDB == NULL )
						continue;
					if( OrgDB->Item.SuitID == NeedValue )
						break;
				}
				if( i == EM_EQWearPos_MaxCount )
					return false;
			}
			break;
		case EM_MagicSpellNeedType_Buf:					//需求 自己有 法術Buf
			{
				for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
				{
					if( BaseData.Buff[i].BuffID == NeedValue )
					{
						IsFind = true;
						break;
					}
				}
				if( IsFind == false )
				{
					//Msg( "施法 缺少前置的法術Buf" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBuffError );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Buf_Target:			//需求 目標有 法術Buf
			{
				for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
				{
					if( Target->BaseData.Buff[i].BuffID == NeedValue )
					{
						IsFind = true;
						break;
					}
				}
				if( IsFind == false )
					return false;				
			}
			break;
		case EM_MagicSpellNeedType_NoBuf:				//需求 自己沒有 法術Buf
			{
				for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
				{
					if( BaseData.Buff[i].BuffID == NeedValue )
					{
						//Msg( "施法 抗Buff還沒有消失" );
						Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedNoBuffError );
						return false;
					}
				}
			}
			break;
		case EM_MagicSpellNeedType_NoBuf_Target:		//需求 目標沒有 法術Buf
			{
				for( int i = 0 ; i < Target->BaseData.Buff.Size() ; i++ )
				{
					if( Target->BaseData.Buff[i].BuffID == NeedValue )
					{
						//Msg( "施法 目標抗Buff還沒有消失" );
						Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedTargetNoBuffError );
						return false;
					}
				}
			}
			break;

		case EM_MagicSpellNeedType_WeaponType_Unarmed:	//需求 自己裝 武器類型 空手
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Unarmed )
				{
					//Msg( "施法 主手要空手" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedUnarmed );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Blade:    //需求 自己裝 武器類型 劍
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Blade )
				{
					//Msg( "施法 主手要拿單手劍" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBlade );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Dagger:   //需求 自己裝 武器類型 匕首
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Dagger )
				{
					//Msg( "施法 主手要拿匕首" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedDagger );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Wand:     //需求 自己裝 武器類型 權杖
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Wand )
				{
					//Msg( "施法 主手要拿權杖" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedWand );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Axe:      //需求 自己裝 武器類型 斧
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Axe )
				{
					//Msg( "施法 主手要拿單手斧" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedAxe );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Bludgeon: //需求 自己裝 武器類型 鎚棍棒
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Bludgeon )
				{
					//Msg( "施法 主手要拿鎚棍棒" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBludgeon );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Claymore: //需求 自己裝 武器類型 雙手劍
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Claymore )
				{
					//Msg( "施法 主手要拿雙手劍" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedClaymore );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Staff:    //需求 自己裝 武器類型 杖
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Staff )
				{
					//Msg( "施法 主手要拿杖" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedStaff );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_2H_Axe:   //需求 自己裝 武器類型 雙手斧
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_2H_Axe )
				{
					//Msg( "施法 主手要拿雙手斧" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Need2HAxe );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_2H_Hammer://需求 自己裝 武器類型 雙手鎚
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_2H_Hammer )
				{
					//Msg( "施法 主手要拿雙手鎚" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Need2HHammer );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Polearm:	//需求 自己裝 武器類型 槍(長矛)
			{
				if( TempData.Attr.MainWeaponType != EM_Weapon_Polearm )
				{
					//Msg( "施法 主手要拿槍(長矛)" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedPolearm );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_SwordType: //需求 自己裝 武器類型 劍類(單雙手)
			{
				if(		TempData.Attr.MainWeaponType != EM_Weapon_Blade 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Claymore )
				{
					//Msg( "施法 主手要拿劍類" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedSwordType );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_AxeType:	//需求 自己裝 武器類型 斧類(單雙手)
			{
				if(		TempData.Attr.MainWeaponType != EM_Weapon_2H_Axe 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Axe )
				{
					//Msg( "施法 主手要拿斧類" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedAxeType );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Shield:	//需求 自己裝 武器類型 斧類(單雙手)
			{
				if( BaseData.EQ.SecondHand.Mode.EQCannotEquipment )
					return false;

				GameObjDbStructEx* OrgObjDB = St_GetObjDB( BaseData.EQ.SecondHand.OrgObjID );
				if( !OrgObjDB->IsArmor() ||  OrgObjDB->Item.ArmorType != EM_Armor_Shield )
				{
					//Msg( "施法 副手要拿盾類" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedShield );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Distance:
			{

				if( Length( Target ) < NeedValue )
				{
					//Msg( "施法 距離太近" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedDistance );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_NotAttak:			//需求 自己非戰鬥
			{
				if( IsAttackMode() != false )
				{
					//Msg( "施法 需要自己非戰鬥" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedNoAttack );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Attack:				//需求 自己戰鬥
			{
				if( IsAttackMode() == false )
				{
					//Msg( "施法 需要自己戰鬥" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedAttack );
					return false;
				}
			}
			break;

		case EM_MagicSpellNeedType_Critical:			//需求 自己爆擊
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastCriticalTime )
				{
					//Msg( "施法 爆擊後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedCritical );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_BeCritical:			//需求 自己被爆擊
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeCriticalTime )
				{
					//Msg( "施法 被爆擊後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBeCritical );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_MagicCritical:			//需求 自己爆擊
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastMagicCriticalTime )
				{
					//Msg( "施法 爆擊後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedMagicCritical );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_BeMagicCritical:			//需求 自己被爆擊
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeMagicCriticalTime )
				{
					//Msg( "施法 被爆擊後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBeMagicCritical );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Dodge:				//需求 自己閃避
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastDodgeTime )
				{
					//Msg( "施法 閃避後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedDodge );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Miss:				//需求 自己Miss
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastMissTime )
				{
					//Msg( "施法 Miss後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedMiss );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Parry:				//需求 自己格擋
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastParryTime)
				{
					//Msg( "施法 格檔後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedParry );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_BeParry:				//需求 自己被格擋
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeParryTime )
				{
					//Msg( "施法 被格檔後才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBeParry );
					return false;
				}
			}
		case EM_MagicSpellNeedType_NotAttack_Target:	//需求 目標非戰鬥		
			{
				if( Target->IsAttackMode() != false )
				{
					//Msg( "施法 目標非戰鬥" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedTargetNoAttack );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Attack_Target:		//需求 目標戰鬥
			{
				if( Target->IsAttackMode() == false )
				{
					//Msg( "施法 目標戰鬥" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedTargetAttack );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_BeDodge:
			{
				if( _DEF_ATTACK_EVENT_EFFECT_TIME_ < G_SysTime - TempData.BackInfo.LastBeDodgeTime )
				{
					//Msg( "施法 被閃避才可使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedBeDodge);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_SelfHp_Smaller_Percent:		//需求 HP百分比小於
			{
				int Rate = int( BaseData.HP * 100 / TempData.Attr.Fin.MaxHP );
				if( NeedValue < Rate )
				{
					//Msg( "施法 HP過多無法使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedHPSmallerPercent);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_SelfHp_Greater_Percent:		//需求 HP百分比大於
			{
				int Rate = int( BaseData.HP * 100 /  TempData.Attr.Fin.MaxHP );
				if( NeedValue > Rate )
				{
					//Msg( "施法 HP過少無法使用" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedHPGreaterPercent);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Self_Job:					//需求 職業
			{
				if(		BaseData.Voc		!= NeedValue 
					&&	BaseData.Voc_Sub	!= NeedValue )
				{
					//Msg( "施法 此職業無法施展" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedJob);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_Self_MainJob:
			{
				if(		BaseData.Voc		!= NeedValue 	)
				{
					//Msg( "施法 此職業無法施展" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedJob);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_LongDistWeapon:	//需求 長距離武器
			{
				if( TempData.Attr.BowWeaponType == EM_Weapon_None )
				{
					//Msg( "施法 長距離武器" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedLongDistWeapon);
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_Hammer:			//需求 自己裝 武器類型 鎚類(單雙手)
			{
				if(		TempData.Attr.MainWeaponType != EM_Weapon_Bludgeon
					&&	TempData.Attr.MainWeaponType != EM_Weapon_2H_Hammer )
				{
					//Msg( "施法 鎚類" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_NeedHammerType );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_2H_Weapon:		//需求 自己裝 武器類型 雙手武器
			{
				if(		TempData.Attr.MainWeaponType != EM_Weapon_Staff
					&&	TempData.Attr.MainWeaponType != EM_Weapon_2H_Hammer 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_2H_Axe 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Claymore 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Polearm	)
				{
					//Msg( "施法 雙手武器" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Need2HWeapon );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_WeaponType_1H_Weapon:		//需求 自己裝 武器類型 雙手武器
			{
				if(		TempData.Attr.MainWeaponType != EM_Weapon_Blade
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Dagger 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Wand 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Axe 
					&&	TempData.Attr.MainWeaponType != EM_Weapon_Bludgeon	)
				{
					//Msg( "施法 雙手武器" );
					Net_GameMsgEvent( EM_GameMessageEvent_MagicError_Need1HWeapon );
					return false;
				}
			}
			break;
		case EM_MagicSpellNeedType_BuffGroup:
			{

				for( int j = 0 ; j < BaseData.Buff.Size() ; j++ )
				{
					BuffBaseStruct& Buf = BaseData.Buff[j];
					if( Buf.Magic->MagicBase.MagicGroupID  != NeedValue )
						continue;
					return true;
				}

				return false;
			}
			break;
		case EM_MagicSpellNeedType_NoBuffGroup:
			{
				for( int j = 0 ; j < BaseData.Buff.Size() ; j++ )
				{
					BuffBaseStruct& Buf = BaseData.Buff[j];
					if( Buf.Magic->MagicBase.MagicGroupID  != NeedValue )
						continue;
					return false;
				}

				return true;
			}
			break;
		case EM_MagicSpellNeedType_TargetBuffGroup:
			{
				for( int j = 0 ; j < Target->BaseData.Buff.Size() ; j++ )
				{
					BuffBaseStruct& Buf = Target->BaseData.Buff[j];
					if( Buf.Magic->MagicBase.MagicGroupID  != NeedValue )
						continue;
					return true;
				}

				return false;
			}
			break;
		case EM_MagicSpellNeedType_TargetNoBuffGroup:
			{
				for( int j = 0 ; j < Target->BaseData.Buff.Size() ; j++ )
				{
					BuffBaseStruct& Buf = Target->BaseData.Buff[j];
					if( Buf.Magic->MagicBase.MagicGroupID  != NeedValue )
						continue;
					return false;
				}

				return true;
			}
			break;
		case EM_MagicSpellNeedType_Self_SoulPoint:	//需求 靈魂值
			{
				if( TempData.SoulPoint < NeedValue )
					return false;
				return true;
			}

		}
	}

 
    return true;
}
//-----------------------------------------------------------------------------------------------
//檢查被攻擊是否施法中斷
bool	RoleDataEx::CheckMagicInterrupt_OnAttack( )
{
	if(		TempData.Magic.State != EM_MAGIC_PROC_STATE_PERPARE 
		&&	TempData.Magic.State != EM_MAGIC_PROC_STATE_SHOOT )
		return false;

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( TempData.Magic.MagicCollectID );
	if( OrgDB == NULL )
		return true;

	if( OrgDB->MagicCol.Flag.Interrupt_OnAttack )
	{
		TempData.Magic.State = EM_MAGIC_PROC_STATE_INTERRUPT;
		return true;
	}

	return false;

}

bool	RoleDataEx::CheckMagicInterrupt( )
{
	if(		TempData.Magic.State != EM_MAGIC_PROC_STATE_PERPARE 
		&&	TempData.Magic.State != EM_MAGIC_PROC_STATE_SHOOT )
		return false;

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( TempData.Magic.MagicCollectID );
	if( OrgDB == NULL )
		return true;
	
	if( OrgDB->MagicCol.Flag.Interrupt_OnMove )
	{
		if(		OrgDB->MagicCol.IsDisableSpellBuffEffect == true 
			||	( TempData.Attr.Effect.MagicSpell_Moveable == false && TempData.Attr.Effect.MagicSpell_ZeroTime == false) )
			return TempData.Magic.IsMove;
	}

	if( TempData.Magic.UseItem == 0 )
	{
		switch( OrgDB->MagicCol.EffectType )
		{
		case EM_Magic_Magic:
			if( TempData.Attr.Effect.UseMagicDisable != false && OrgDB->MagicCol.IsIgnoreSilence == false )
				return true;
			break;
		case EM_Magic_Phy:
			if( TempData.Attr.Effect.UsePhyDisable != false && OrgDB->MagicCol.IsIgnoreSilence == false )
				return true;
			break;
		}

	}
	return false;
}
//-----------------------------------------------------------------------------------------------
//檢查是否可以對目標失法
bool	RoleDataEx::CheckUseItem(  int TargetID , float TargetX , float TargetY , float TargetZ , int Pos , int Type , ItemFieldStruct&  Item )
{
    RoleDataEx*		Target = (RoleDataEx*)St_GetRoleData( TargetID );
    if( Target == NULL )
        Target = this;

    if( Item.Pos != EM_ItemState_NONE )
        return false;

    GameObjDbStructEx*	OrgDB;
    GameObjDbStructEx*	MagicDB;
    OrgDB = St_GetObjDB( Item.OrgObjID );
    if( OrgDB == NULL )
        return false;

	//如果使用物品被封住
	if(		TempData.Attr.Effect.UseItemDisable != false
		&&	OrgDB->Mode.UseWithoutFail == false )
	{
		Net_GameMsgEvent( EM_GameMessageEvent_Item_MagicDisableUseItem );
		return false;
	}


	if( OrgDB->IsRecipe() )
	{
		if( OrgDB->Recipe.Request.Skill != EM_SkillValueType_None )
		{
			//float SkillValue = GetSkillValue( OrgDB->Recipe.Request.Skill );
			//if( SkillValue < OrgDB->Recipe.Request.SkillLV )
			//	return false;
		}

		if( OrgDB->Recipe.Request.KeyItemID == 0 )
			return false;

		if( CheckKeyItem( OrgDB->Recipe.Request.KeyItemID ) != false )
			return false;

		
		return true;
	}

	//如果還有物品使用中則不可使用
	if( TempData.Magic.UseItem != 0 )
		return false;

    MagicDB = St_GetObjDB( OrgDB->Item.IncMagic_Onuse );
    if( MagicDB == NULL )
        return false;

	//MagicProcInfo* MagicProc = &Owner->TempData.Magic;
    //檢查是否可以對目標施法
	GameMessageEventENUM Ret = CheckCanSpell( Target , TargetX , TargetY , TargetZ , MagicDB );
	if(  Ret != EM_GameMessageEvent_OK )
	{
		if( Ret != EM_GameMessageEvent_Failed )
			Net_GameMsgEvent( Ret );
		return false;
	}

//    if( CheckCanSpell( Target , TargetX , TargetY , TargetZ , MagicDB ) == false )
//		return false;


    return true;
}
//-----------------------------------------------------------------------------------------------
//檢查魔法是否命中
bool    RoleDataEx::CheckMagicHit( RoleDataEx* Target , GameObjDbStructEx* OrgDB )
{
	/*
    int DLV = Level() - Target->Level();
    float HitRate =  OrgDB->Magic.HitRate + OrgDB->Magic.DLv_HitRate * DLV   ;
	float Rd = float(rand()%100 ) / 100 ;
    return ( HitRate > Rd );
	*/
	return true;
}

//檢查是否要逃跑
bool    RoleDataEx::CheckEscape( RoleDataEx* Target )
{
	if(		TempData.Attr.Effect.Stop != false 
		||	BaseData.Mode.Move == false )
		return false;

    if( TempData.Attr.Effect.Fear )
        return true;

	if( TempData.Attr.Effect.NoEscape != false )
		return false;

	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );

	if( OrgDB->IsNPC() == false )
		return false;
	
	switch( OrgDB->NPC.EscapeType )
	{
	case 0:
		return false;
		break;
	case 1:
		if( TempData.Attr.Fin.MaxHP > BaseData.HP * 5 && rand() % 20 == 0 )
			return true;
		break;
	case 2:
		if( TempData.Attr.Fin.MaxHP > BaseData.HP * 4 && rand() % 20 == 0 )
			return true;
		break;
	case 3:
		if( TempData.Attr.Fin.MaxHP > BaseData.HP * 3 && rand() % 20 == 0 )
			return true;
		break;
	case 4:
		if( TempData.Attr.Fin.MaxHP > BaseData.HP * 2 && rand() % 20 == 0 )
			return true;
		break;
	case 5:
		if( TempData.Attr.Fin.MaxHP*3 > BaseData.HP * 4 && rand() % 20 == 0 )
			return true;
		break;
	case 6:
		return true;
		
	}
	
    return false;
}
bool    RoleDataEx::IsUnderAttack( )
{
    return TempData.NPCHate.Hate.Size() != 0;
}

//檢查是否可以物理攻擊
bool	RoleDataEx::CheckPhyAttack( RoleDataEx* Target )
{

	if( Target->IsMirror() )
		return false;

	//如果自己  不可用物理攻擊
	if( TempData.Attr.Effect.UsePhyDisable )
		return false;

	//如果目標  物理無效(物理技能與一般攻擊無效)
//	if( Target->TempData.Attr.Effect.PhyInvincible )
//		return false;

	return true;
}
//檢查是否可以法術攻擊
bool	RoleDataEx::CheckMagicAttack( RoleDataEx* Target )
{
	if( Target->IsMirror() )
		return false;

	//如果自己  不可用法術攻擊
	if( TempData.Attr.Effect.UseMagicDisable )
		return false;

	//如果目標  法術無效
//	if( Target->TempData.Attr.Effect.MagicInvincible )
//		return false;

	return true;
}

bool	RoleDataEx::IsRoleDataWriteable( )
{
	if( IsDestroy() )
		return false;

	if( RoleDataEx::G_ZoneID != ZoneID() )
		return false;
	
	if( IsMirror() )
		return false;
	
	return true;
}

//檢查時間
bool	RoleDataEx::CheckTime( int Time )
{
	return int( G_SysTime - Time ) >= 0;
}

//檢查是否已經有某輔助法術
bool	RoleDataEx::CheckHasAssistMagic( GameObjDbStructEx* MagicBaseDB )
{
	if( MagicBaseDB == NULL )
		return false;

	if( BaseData.Buff.Size() >= BaseData.Buff.MaxSize() )
		return false;

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		BuffBaseStruct&  Buf = BaseData.Buff[ i ];

		GameObjDbStructEx*  MagBuf = St_GetObjDB( Buf.BuffID );

		if( MagBuf->GUID == MagicBaseDB->GUID )
		{
			return false;

		}
		else if(     MagBuf->MagicBase.AssistType != EM_Magic_Type_NULL 
			&&  MagBuf->MagicBase.AssistType == MagicBaseDB->MagicBase.AssistType )
		{
			//如果可不可互蓋-
			if(		MagicBaseDB->MagicBase.EffectAddonType == 1  
				&&	MagBuf->MagicBase.EffectLV == MagicBaseDB->MagicBase.EffectLV)
				continue;

			if( MagBuf->MagicBase.EffectLV > MagicBaseDB->MagicBase.EffectLV )
				continue;

			return false;

		}
	}
	return false;

}

bool	RoleDataEx::CheckOpenMenu( RoleOpenMenuTypeENUM OpenType )
{
	if( TempData.Attr.Action.OpenType != OpenType )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > 300 )
	{
		ClsOpenMenu();		
		//TempData.ShopInfo.TargetID = -1;
		//TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}
/*
//檢查AC是否有開啟 , 如果有問題設定成關閉
bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_AC )
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_AC )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > 300 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}

//檢查Mail是否有開啟 , 如果有問題設定成關閉
bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_Mail )
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_Mail )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > _MAX_ROLE_TOUCH_MAXRANGE_* 2 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}
//檢查Shop是否有開啟 , 如果有問題設定成關閉
bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_Shop )
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_Shop )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > _MAX_ROLE_TOUCH_MAXRANGE_* 2 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}

//檢查Bank是否有開啟 , 如果有問題設定成關閉
bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_Bank )
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_Bank )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > _MAX_ROLE_TOUCH_MAXRANGE_* 2 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}


//檢查Bank是否有開啟 , 如果有問題設定成關閉
bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_ChangeJob )
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_ChangeJob )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > _MAX_ROLE_TOUCH_MAXRANGE_* 2 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}

bool	RoleDataEx::CheckOpenMenu( EM_RoleOpenMenuType_Billboard)
{
	if( TempData.Attr.Action.OpenType != EM_RoleOpenMenuType_Billboard )
		return false;

	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > _MAX_ROLE_TOUCH_MAXRANGE_* 2 )
	{
		TempData.ShopInfo.TargetID = -1;
		TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	return true;
}
*/

void	RoleDataEx::ClsOpenMenu( )
{
	TempData.ShopInfo.TargetID = -1;
	TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
}

//檢查是否有開起 AC Mail Shop Bank中任何一個
bool	RoleDataEx::CheckOpenSomething( )
{
	RoleDataEx* TargetNpc = St_GetRoleData( TempData.ShopInfo.TargetID );
	if( TargetNpc == NULL || Length( TargetNpc ) > 300 )
	{
		ClsOpenMenu();		
		//TempData.ShopInfo.TargetID = -1;
		//TempData.Attr.Action.OpenType = EM_RoleOpenMenuType_None;
		return false;
	}

	switch( TempData.Attr.Action.OpenType )
	{
	case EM_RoleOpenMenuType_None:
		return false;
	case EM_RoleOpenMenuType_Shop		:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_ShopOpenYet );
		return true;;
	case EM_RoleOpenMenuType_Bank		:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_BankOpenYet );
		return true;
	case EM_RoleOpenMenuType_AC			:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_ACOpenYet );
		return true;
	case EM_RoleOpenMenuType_Mail		:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_MailOpenYet );
		return true;
	case EM_RoleOpenMenuType_ChangeJob	:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_ChangeJobOpenYet );
		return true;
	case EM_RoleOpenMenuType_Billboard	:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_BillBoardOpenYet );
		return true;
	case EM_RoleOpenMenuType_CreateNewGuild:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_CreateNewGuildOpenYet );
		return true;
	case EM_RoleOpenMenuType_GuildContribution:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_GuildContributionOpenYet );
		return true;
	//case EM_RoleOpenMenuType_GuildShop:
	//	Net_GameMsgEvent( EM_GameMessageEvent_Shop_GuildShopOpenYet );
		return true;
	case EM_RoleOpenMenuType_ExchangeLottery:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_LotteryExchangeShopOpenYet );
		return true;
	case EM_RoleOpenMenuType_BuyLottery:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_LotteryBuyShopOpenYet );
		return true;
	case EM_RoleOpenMenuType_VisitHouse:
		Net_GameMsgEvent( EM_GameMessageEvent_Shop_VisitHousesOpenYet );
		return true;
	case EM_RoleOpenMenuType_EQCombin:
		Net_GameMsgEvent( EM_GameMessageEvent_EQCombin_OpenYet );
		return true;		
	case EM_RoleOpenMenuType_AccountBag:
		Net_GameMsgEvent( EM_GameMessageEvent_AccountBag_OpenYet );
		return true;
	case EM_RoleOpenMenuType_VisitGuildHouse:
		Net_GameMsgEvent( EM_GameMessageEvent_VisitGuildHouse_OpenYet );
		return true;
	case EM_RoleOpenMenuType_EqGamble:

		return true;
	case EM_RoleOpenMenuType_MagicStoneExchange:		
		return true;
	case EM_RoleOpenMenuType_SuitSkill:
		Net_GameMsgEvent( EM_GameMessageEvent_SuitSkill_OpenYet );
		return true;
	}

	return true;
}

//檢查法術是否對目標有效用效用( 用來處理 NPC AI用)
bool RoleDataEx::CheckEffect_SpellMagic( RoleDataEx* Target , GameObjDbStructEx* MagicOrgDB )
{
	if( MagicOrgDB->MagicCol.TargetType == EM_Releation_Self )
	{
		Target = this;
	}

	//取出第一個法術做檢查
	//GameObjDbStructEx* MagicBaseOrgDB = (GameObjDbStructEx*)(MagicOrgDB->MagicCol.Magic_List[0].MagicBaseDB);
	GameObjDbStructEx* MagicBaseOrgDB = St_GetObjDB( MagicOrgDB->MagicCol.Magic_List[0].MagicBaseID );
	if( MagicBaseOrgDB == NULL )
		return false;

	switch( MagicBaseOrgDB->MagicBase.MagicFunc )
	{
	case EM_MAGICFUN_HPMP:
		{
			//如果加血
			if( MagicBaseOrgDB->MagicBase.Attack.DmgPower > 0 )
			{
				if( Target->MaxHP() > Target->HP()*2 )
					return true;
				else
					return false;
			}
		}
		break;
	case EM_MAGICFUN_Assist:			//輔助
		{
			//撿查法術是否可以施展上去 
			BuffBaseStruct* Buf	= GetBuff( MagicBaseOrgDB->MagicBase.AssistType , MagicBaseOrgDB->GUID );
			if( Buf == NULL )
				return false;

			if( Buf->Magic->MagicBase.EffectLV >= MagicBaseOrgDB->MagicBase.EffectLV )
				return false;

			return true;
		}
		break;
	case EM_MAGICFUN_Teleport:			//傳送
		return true;
	case EM_MAGICFUN_SummonCreature:	//招換生物(寵物)
		break;
	case EM_MAGICFUN_SummonItem:		//招換物品
		return false;
	case EM_MAGICFUN_Steal:				//偷竊
		return false;
	case EM_MAGICFUN_ItemRunPlot:		//產生物品並且執行劇情
		return true;
	case EM_MAGICFUN_RunPlot:			//執行劇情
		return true;
	case EM_MAGICFUN_Raise:				//復活
		return false;
	}

	return false;
}

CheckAddRuneResultENUM	RoleDataEx::CheckAddRune	( ItemFieldStruct* UseItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( UseItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( TargetItem->OrgObjID );

	if( TargetItemOrgDB->IsItem() == false )
		return EM_CheckAddRuneResult_TargetItemErr;

	if( UseItemOrgDB->IsRune() == false )
		return EM_CheckAddRuneResult_NotRune;

	if( TargetItemOrgDB->MaxHeap > 1 )
		return EM_CheckAddRuneResult_Unknow;

/*	int RuneLimetLv = TargetItemOrgDB->Item.RuneLimetLv - 1;
	if( TargetItem->PowerQuality > 10 )
		RuneLimetLv = RuneLimetLv + TargetItem->PowerQuality - 10;
	if( RuneLimetLv < UseItemOrgDB->Item.Level )
		return EM_CheckAddRuneResult_LevelError;
		*/

	if( TargetItemOrgDB->IsWeapon() )
	{
		switch( TargetItemOrgDB->Item.WeaponPos )
		{
		case EM_WeaponPos_MainHand:        //主手
			if( UseItemOrgDB->Item.AddPos.WeaponPosEnum == EM_AddonPos_WeaponLimitPos_OffHand )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_WeaponPos_SecondHand:      //副手
			if( UseItemOrgDB->Item.AddPos.WeaponPosEnum == EM_AddonPos_WeaponLimitPos_MainHand )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_WeaponPos_OneHand:         //雙手都可以裝備
			if( UseItemOrgDB->Item.AddPos.WeaponPosEnum == EM_AddonPos_WeaponLimitPos_MainHand )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_WeaponPos_TwoHand:         //兩手			
			break;
		case EM_WeaponPos_Bow:             //弓
			break;
		default:
			return EM_CheckAddRuneResult_WeaponErr;
		}

		switch( TargetItemOrgDB->Item.WeaponType )
		{
		case EM_Weapon_Unarmed:			// Unarmed空手
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Unarmed == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Blade:           // 劍
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Blade == false )				
				return EM_CheckAddRuneResult_WeaponErr;

			break;
		case EM_Weapon_Dagger:          // 匕首
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Dagger == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Wand:            // 權杖
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Wand == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Axe:             // 斧
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Axe == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Bludgeon:        // 鎚棍棒
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Bludgeon == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Claymore:        // 雙手劍
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Claymore == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Staff:           // 杖
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Staff == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_2H_Axe:          // 雙手斧
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Axe_2H == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_2H_Hammer:       // 雙手鎚
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Hammer_2H == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Polearm:			// 槍(長矛)
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Polearm == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Bow:				// 遠程武器 弓
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Bow == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_CossBow:			// 遠程武器 十字弓
			if(		UseItemOrgDB->Item.AddPos.WeaponType.CossBow == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		case EM_Weapon_Gun:				// 遠程武器 槍
			if(		UseItemOrgDB->Item.AddPos.WeaponType.Gun == false )
				return EM_CheckAddRuneResult_WeaponErr;
			break;
		default:
			return EM_CheckAddRuneResult_WeaponErr;
		}
	}
	else if( TargetItemOrgDB->IsArmor() )
	{
		bool	CheckArmorType = true;
		switch( TargetItemOrgDB->Item.ArmorPos )		
		{
		case EM_ArmorPos_Head:			//頭
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Head == false )
				return EM_CheckAddRuneResult_ArmorErr;		
			break;
		case EM_ArmorPos_Gloves:		//手套
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Gloves == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Shoes:			//鞋子
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Shoes == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Clothes:		//上衣
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Clothes == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Pants:			//褲子
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Pants == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Back:			//背部
			if( UseItemOrgDB->Item.AddPos.Other.Back == false )
				return EM_CheckAddRuneResult_ArmorErr;		
			CheckArmorType = false;

			break;
		case EM_ArmorPos_Belt:			//腰帶
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Belt == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Shoulder:		//肩甲
			if( UseItemOrgDB->Item.AddPos.ArmorPos.Shoulder == false )
				return EM_CheckAddRuneResult_ArmorErr;		

			break;
		case EM_ArmorPos_Necklace:		//項鍊 
			if( UseItemOrgDB->Item.AddPos.Other.Necklace == false )
				return EM_CheckAddRuneResult_ArmorErr;		
			CheckArmorType = false;

			break;
		case EM_ArmorPos_Ring:			//戒子
			if( UseItemOrgDB->Item.AddPos.Other.Ring == false )
				return EM_CheckAddRuneResult_ArmorErr;		
			CheckArmorType = false;

			break;
		case EM_ArmorPos_Earring:		//耳飾
			if( UseItemOrgDB->Item.AddPos.Other.Earring == false )
				return EM_CheckAddRuneResult_ArmorErr;	
			CheckArmorType = false;

			break;
		case EM_ArmorPos_SecondHand:	//副手
			if( TargetItemOrgDB->Item.ArmorType == EM_Armor_Shield )
			{
				if( UseItemOrgDB->Item.AddPos.Other.Shield == false )
					return EM_CheckAddRuneResult_ArmorErr;
			}
			else if( TargetItemOrgDB->Item.ArmorType == EM_Armor_Implement )
			{
				if( UseItemOrgDB->Item.AddPos.Other.Implement == false )
					return EM_CheckAddRuneResult_ArmorErr;
			}
			else
			{
				return EM_CheckAddRuneResult_ArmorErr;
			}

			CheckArmorType = false;
			break;
		case EM_ArmorPos_Ornament:
			if( UseItemOrgDB->Item.AddPos.Other.Ornament == false )
				return EM_CheckAddRuneResult_ArmorErr;
			CheckArmorType = false;
			break;
		case EM_ArmorPos_MagicTool:
		default:
			return EM_CheckAddRuneResult_ArmorErr;
		}

	}
	else return EM_CheckAddRuneResult_Unknow;

	if( TargetItem->RuneVolume < UseItemOrgDB->Item.Volume )
		return EM_CheckAddRuneResult_RuneVolumeErr;

	//如果已鑲入相同的符文則失敗
	for( int i = 0 ; i < 4 ; i++ )
	{
		GameObjDbStructEx* ObjDB = St_GetObjDB( TargetItem->Rune(i) );
		if( ObjDB == NULL )
			continue;
		if( ObjDB->Item.RuneGroup == UseItemOrgDB->Item.RuneGroup )
			return EM_CheckAddRuneResult_RuneDuplicate;
/*
		if( TargetItem->Rune(i) == UseItemOrgDB->GUID )
		{
			return EM_CheckAddRuneResult_RuneDuplicate;
		}
		*/
	}


	for( int i = 0 ; ; i++ )
	{
		if( i >= 4 )
		{
			return EM_CheckAddRuneResult_RuneFull;
		}

		if( TargetItem->Rune(i) == 0 )
		{
			break;
		}	
	}

	return EM_CheckAddRuneResult_OK;
}


//檢查是否可以衝等
CheckEqRefineResultENUM	RoleDataEx::CheckEqRefine	( ItemFieldStruct* UseItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( UseItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );

	if( UseItemOrgDB == NULL || TargetItemOrgDB == NULL )
		return EM_CheckEqRefineResult_DataErr;

	if( TargetItemOrgDB->Mode.DisableRefine )
		return EM_CheckEqRefineResult_CantRefine;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckEqRefineResult_DataErr;

	if( UseItemOrgDB->Item.UseType != EM_ItemUseType_EqRefine )
		return EM_CheckEqRefineResult_DataErr;

	if( TargetItem->Level >= 20 )
		return EM_CheckEqRefineResult_MaxLevel;

	switch( UseItemOrgDB->Item.EqRefineType )
	{
	case EM_EqRefineType_Weapon:
		{
			if( TargetItemOrgDB->IsWeapon() == false )
			{
				return EM_CheckEqRefineResult_NotWeapon;
			}
			if(		TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Ammo 
				||	TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Manufacture )
				return EM_CheckEqRefineResult_NotWeapon;

		}
		break;
	case EM_EqRefineType_Armor:
		{
			if( TargetItemOrgDB->IsArmor() == false )
			{
				return EM_CheckEqRefineResult_NotArmor;
			}
			else
			{
				switch( TargetItemOrgDB->Item.ArmorPos )
				{
				case EM_ArmorPos_Head:         //頭
				case EM_ArmorPos_Gloves:	   //手套
				case EM_ArmorPos_Shoes:	       //鞋子
				case EM_ArmorPos_Clothes:	   //上衣
				case EM_ArmorPos_Pants:	       //褲子
				case EM_ArmorPos_Back:	       //背部
				case EM_ArmorPos_Belt:	       //腰帶
				case EM_ArmorPos_Shoulder:     //肩甲
				case EM_ArmorPos_SecondHand:   //副手
					break;
				case EM_ArmorPos_Necklace:     //項鍊 						
				case EM_ArmorPos_Ring:         //戒子
				case EM_ArmorPos_Earring:      //耳飾
					return EM_CheckEqRefineResult_NotArmor;
					break;

				case EM_ArmorPos_MagicTool:
				case EM_ArmorPos_Ornament:
				default:
					return EM_CheckEqRefineResult_NotArmor;
					break;
				}
			}
			break;
		}
	case EM_EqRefineType_Jewels:
		{
			if( TargetItemOrgDB->IsArmor() == false )
			{
				return EM_CheckEqRefineResult_NotJewels;
			}
			else
			{
				switch( TargetItemOrgDB->Item.ArmorPos )
				{
				case EM_ArmorPos_Head:         //頭
				case EM_ArmorPos_Gloves:	   //手套
				case EM_ArmorPos_Shoes:	       //鞋子
				case EM_ArmorPos_Clothes:	   //上衣
				case EM_ArmorPos_Pants:	       //褲子
				case EM_ArmorPos_Back:	       //背部
				case EM_ArmorPos_Belt:	       //腰帶
				case EM_ArmorPos_Shoulder:     //肩甲
				case EM_ArmorPos_SecondHand:   //副手
					return EM_CheckEqRefineResult_NotJewels;
					break;
				case EM_ArmorPos_Necklace:     //項鍊 						
				case EM_ArmorPos_Ring:         //戒子
				case EM_ArmorPos_Earring:      //耳飾									
					break;

				case EM_ArmorPos_MagicTool:
				case EM_ArmorPos_Ornament:
				default:
					return EM_CheckEqRefineResult_NotJewels;
					break;
				}
			}
			break;
		}
	case EM_EqRefineType_Ornament:
		{
			if( TargetItemOrgDB->IsArmor() == false )
			{
				return EM_CheckEqRefineResult_NotOrnament;
			}
			else
			{
				switch( TargetItemOrgDB->Item.ArmorPos )
				{
				case EM_ArmorPos_Head:         //頭
				case EM_ArmorPos_Gloves:	   //手套
				case EM_ArmorPos_Shoes:	       //鞋子
				case EM_ArmorPos_Clothes:	   //上衣
				case EM_ArmorPos_Pants:	       //褲子
				case EM_ArmorPos_Back:	       //背部
				case EM_ArmorPos_Belt:	       //腰帶
				case EM_ArmorPos_Shoulder:     //肩甲
				case EM_ArmorPos_SecondHand:   //副手
				case EM_ArmorPos_Necklace:     //項鍊 						
				case EM_ArmorPos_Ring:         //戒子
				case EM_ArmorPos_Earring:      //耳飾									
				case EM_ArmorPos_MagicTool:
					return EM_CheckEqRefineResult_NotOrnament;

				case EM_ArmorPos_Ornament:
					break; 
				default:
					return EM_CheckEqRefineResult_NotOrnament;
					break;
				}
			}
			break;
		}

	}

	//可精鍊武器等級已達上限
	if ( TargetItemOrgDB->Limit.Level > UseItemOrgDB->Item.EqRefineEqMaxLv || TargetItem->Level > UseItemOrgDB->Item.EqRefineMaxLv )
		return EM_CheckEqRefineResult_ItemLimitMaxLevel;
	//可精鍊武器等級太低問題
	else if ( TargetItemOrgDB->Limit.Level < UseItemOrgDB->Item.EqRefineEqMinLv || TargetItem->Level < UseItemOrgDB->Item.EqRefineMinLv )
		return EM_CheckEqRefineResult_ItemLimitMinLevel;

	return EM_CheckEqRefineResult_OK;
}
//檢查是否可以修裝
ChecFixEqResultENUM	RoleDataEx::CheckFixEq		( ItemFieldStruct* UseItem, ItemFieldStruct* TargetItem, unsigned int playerMoney )
{
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );	

	if( TargetItemOrgDB == NULL  )
		return EM_CheckFixEqResult_DataErr;

	if( UseItem != NULL )
	{
		GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( UseItem->OrgObjID );
		if( UseItemOrgDB == NULL )
			return EM_CheckFixEqResult_DataErr;

		if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
			return EM_CheckFixEqResult_DataErr;
	}

	if( TargetItemOrgDB->IsItem() == false )
		return EM_CheckFixEqResult_DataErr;

	if( TargetItemOrgDB->IsArmor() == false && TargetItemOrgDB->IsWeapon() == false )
		return EM_CheckFixEqResult_NotEQ;

	if( TargetItemOrgDB->IsWeapon() )
	{
		if( TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Ammo )
			return EM_CheckFixEqResult_NotFix;
	}

//	if ( CalRepairWeapon(TargetItem, NULL) == 0 )
//		return EM_CheckFixEqResult_NotFix;

	if( TargetItemOrgDB->IsArmor() )
	{
		if( TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_MagicTool )
			return EM_CheckFixEqResult_NotFix;
	}

	int	LastMaxDurable = 0;
	if( UseItem == NULL )
	{
		LastMaxDurable = TargetItemOrgDB->Item.Durable * TargetItem->Quality;
	}
	else
	{
		GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( UseItem->OrgObjID );

		if( UseItemOrgDB->IsItem() == false )
			return EM_CheckFixEqResult_DataErr;
		LastMaxDurable = TargetItemOrgDB->Item.Durable * TargetItem->Quality * UseItemOrgDB->Item.FixQuality / 100 ;
		//LastMaxDurable = TargetItemOrgDB->Item.Durable * UseItemOrgDB->Item.FixQuality  ;
	}

	if( TargetItem->Durable == LastMaxDurable )
		return EM_CheckFixEqResult_NotFix;

	if( TargetItem->Durable >= LastMaxDurable ) 
	{		
		return EM_CheckFixEqResult_NewOne;
	}

	if ( (unsigned int)(-CalRepairWeapon(TargetItem, NULL)) > playerMoney )
	{
		return EM_CheckFixEqResult_NotEnoughMoney;
	}
	
	return EM_CheckFixEqResult_OK;
}
//檢查是否可以拆解物品
CheckDissolutionResultENUM	RoleDataEx::CheckDissolution( ItemFieldStruct* SrcItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );
//	GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( SrcItem->OrgObjID );
	if( TargetItemOrgDB == NULL )
		return EM_CheckDissolutionResult_Err;

//	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
//		return EM_CheckDissolutionResult_Err;


	if( TargetItemOrgDB->IsWeapon() == false && TargetItemOrgDB->IsArmor() == false )
		return EM_CheckDissolutionResult_Err;

	if( TargetItemOrgDB->MaxHeap != 1 || TargetItem->Mode.ItemLock != false )
		return EM_CheckDissolutionResult_Err;

	if( TargetItemOrgDB->IsWeapon() )
	{
		if( TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Ammo )
		{
			return EM_CheckDissolutionResult_Err;
		}
	}

	return EM_CheckDissolutionResult_OK;
}

CheckColoringResultENUM	RoleDataEx::CheckColoring	( ItemFieldStruct* SrcItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );
	GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( SrcItem->OrgObjID );
	if( TargetItemOrgDB == NULL || UseItemOrgDB == NULL )
		return EM_CheckColoringResult_Err;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckColoringResult_Err;

	if( TargetItemOrgDB->IsItem() == false )
		return EM_CheckColoringResult_Err;

	if(		TargetItemOrgDB->Item.ItemType == EM_ItemType_SummonHorse )
	{
		if(		TargetItem->HorseColor[0] != 0 
			||	TargetItem->HorseColor[1] != 0 
			||	TargetItem->HorseColor[2] != 0 
			||	TargetItem->HorseColor[3] != 0 )
		{
			return EM_CheckColoringResult_OK;
		}
	}
	if( TargetItemOrgDB->Mode.Coloring == false )
		return EM_CheckColoringResult_Err;

	return EM_CheckColoringResult_OK;
}

//檢查是否可以清除Soulbound
CheckClsSoulBoundResultENUM		RoleDataEx::CheckClsSoulBound( ItemFieldStruct* SrcItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );
	GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( SrcItem->OrgObjID );
	if( TargetItemOrgDB == NULL || UseItemOrgDB == NULL )
		return EM_CheckClsSoulBoundResult_Err;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckClsSoulBoundResult_Err;

	if(		TargetItemOrgDB->IsArmor()!= true 
		&&	TargetItemOrgDB->IsWeapon()!= true  ) 
		return EM_CheckClsSoulBoundResult_Err;

	if( TargetItem->Mode.Trade != false  )
		return EM_CheckClsSoulBoundResult_Err_NoSoulBound;

	if( TargetItem->Mode.EQSoulBound == false  )
		return EM_CheckClsSoulBoundResult_Err_NoEqSoulBound;

	return EM_CheckClsSoulBoundResult_OK;
}

//檢查是否可以清除禁止交易
CheckClsSoulBoundResultENUM	RoleDataEx::CheckClsTrade( ItemFieldStruct* SrcItem , ItemFieldStruct* TargetItem )
{
	GameObjDbStructEx* TargetItemOrgDB = St_GetObjDB( TargetItem->OrgObjID );
	GameObjDbStructEx* UseItemOrgDB = St_GetObjDB( SrcItem->OrgObjID );
	if( TargetItemOrgDB == NULL || UseItemOrgDB == NULL )
		return EM_CheckClsSoulBoundResult_Err;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckClsSoulBoundResult_Err;

	if( TargetItem->Mode.Trade != false  )
		return EM_CheckClsSoulBoundResult_Err_NoSoulBound;

	//if( TargetItemOrgDB->Mode.DepartmentStore == false && TargetItemOrgDB->Mode.DepartmentStore_Free == false )
	{
		if(		TargetItemOrgDB->IsArmor()!= true 
			&&	TargetItemOrgDB->IsWeapon()!= true  ) 
			return EM_CheckClsSoulBoundResult_Err;
	}

	//	if( TargetItem->Mode.EQSoulBound == false  )
	//		return EM_CheckClsSoulBoundResult_Err_NoEqSoulBound;

	return EM_CheckClsSoulBoundResult_OK;
}

//檢查是否可以打洞
CheckDigHoleResultENUM		RoleDataEx::CheckDigHole( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( TargetItemOrgDB->IsItem() == false )
		return EM_CheckDigHoleResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckDigHoleResult_SrcErr;


	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_EQDigHole)
		return EM_CheckDigHoleResult_SrcErr;

	if( TargetItemOrgDB->Mode.DisableDigHode == true )
		return EM_CheckDigHoleResult_TargetErr;

	if( TargetItemOrgDB->IsArmor() )
	{
		if(		TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_MagicTool	
			/*||	TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_Ornament */ )
			return EM_CheckDigHoleResult_TargetErr;
	}
	else if( TargetItemOrgDB->IsWeapon() )
	{
		if(		TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Ammo	
			||	TargetItemOrgDB->Item.WeaponPos == EM_WeaponPos_Manufacture )
			return EM_CheckDigHoleResult_TargetErr;
	}
	else
	{
		return EM_CheckDigHoleResult_TargetErr;
	}

	if( TargetItemOrgDB->MaxHeap > 1 )
		return EM_CheckDigHoleResult_TargetErr;


	switch( UseItemOrgDB->Item.DigHole.Type )
	{
	case EM_DigHoleType_All:
		break;
	case EM_DigHoleType_Weapon:
		if(		TargetItemOrgDB->IsWeapon() == false )
			return EM_CheckDigHoleResult_WeaponOnly;
		break;
	case EM_DigHoleType_Armor:
		if(		TargetItemOrgDB->IsArmor() == false 
			||	TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_Necklace 
			||	TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_Ring 
			||	TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_Earring 
			||	TargetItemOrgDB->Item.ArmorPos == EM_ArmorPos_Ornament )
			return EM_CheckDigHoleResult_ArmorOnly;
		break;
	case EM_DigHoleType_Jewels:
		if(		TargetItemOrgDB->IsArmor() == false ) 
			return EM_CheckDigHoleResult_NotJewels;

		if(		TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Necklace 
			&&	TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Ring 
			&&	TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Earring )
			return EM_CheckDigHoleResult_NotJewels;

		break;

	case EM_DigHoleType_Ornament:
		if(		TargetItemOrgDB->IsArmor() == false ) 
			return EM_CheckDigHoleResult_OrnamentOnly;

		if(		TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Ornament )
			return EM_CheckDigHoleResult_OrnamentOnly;

/*
		if(		TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Necklace 
			&&	TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Ring 
			&&	TargetItemOrgDB->Item.ArmorPos != EM_ArmorPos_Earring )
			return EM_CheckDigHoleResult_OrnamentOnly;
*/
		break;
	}

	int RuneVolume = DestItem->RuneVolume;

	for( int i = 0 ; i < 4 ; i++  )
	{
		GameObjDbStructEx* AddPowerDB	= St_GetObjDB( DestItem->Rune(i) );
		if( AddPowerDB->IsRune() == false)
			continue;
		RuneVolume += AddPowerDB->Item.Volume;
	}

	if( UseItemOrgDB->Item.DigHole.MaxHoleCount <= RuneVolume || RuneVolume >= 4 /*|| TargetItemOrgDB->Item.HoleBase <= RuneVolume */)
		return EM_CheckDigHoleResult_HoleErr;


	return EM_CheckDigHoleResult_OK;
}
//檢查是否可以清除所有符文
CheckClsRuneResultENUM		RoleDataEx::CheckClsRune( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if(		TargetItemOrgDB->IsWeapon() == false 
		&&	TargetItemOrgDB->IsArmor() == false 	)
		return EM_CheckClsRuneResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckClsRuneResult_SrcErr;

	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_EQClearRune )
		return EM_CheckClsRuneResult_SrcErr;


	//檢查目標有沒有符文
	//if( DestItem->RuneVolume <= 0 )
//		return EM_CheckClsRuneResult_TargetErr;
	
	if( DestItem->Rune(0) == 0 )
		return EM_CheckClsRuneResult_TargetErr;

	return EM_CheckClsRuneResult_OK;
}

//檢查是否可以鎖定物品
CheckItemLockResultENUM		RoleDataEx::CheckItemLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );
	

	if(		TargetItemOrgDB->IsWeapon() == false 
		&&	TargetItemOrgDB->IsArmor() == false 	)
		return EM_CheckItemLockResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckItemLockResult_TargetErr;

	if( TargetItemOrgDB->MaxHeap > 1 && DestItem->Mode.HideCount == false )
		return EM_CheckItemLockResult_TargetErr;

	if( DestItem->Mode.ItemLock != false )
		return EM_CheckItemLockResult_TargetErr;

	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_ItemLock )
		return EM_CheckItemLockResult_SrcErr;

	return EM_CheckItemLockResult_OK;
}
//檢查是否可以鎖定物品
CheckItemUnLockResultENUM		RoleDataEx::CheckItemUnLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( DestItem->Mode.ItemLock == false )
		return EM_CheckItemUnLockResult_TargetErr;

	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_ItemUnLock )
		return EM_CheckItemUnLockResult_SrcErr;


	return EM_CheckItemUnLockResult_OK;
}

//檢查是否可以鎖定物品
CheckEQProtectResultENUM		RoleDataEx::CheckEQProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if(		DestItem->Mode.Protect != false 
		||	( TargetItemOrgDB->IsArmor() == false && TargetItemOrgDB->IsWeapon() == false ) )
		return EM_CheckEQProtectResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckEQProtectResult_TargetErr;


	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_EQProtect )
		return EM_CheckEQProtectResult_SrcErr;

	return EM_CheckEQProtectResult_OK;
}

//檢查是否可以修裝備上限
CheckEQLimitMaxResultENUM	RoleDataEx::CheckEQLimitMax( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( TargetItemOrgDB->IsArmor() == false && TargetItemOrgDB->IsWeapon() == false  )
		return EM_CheckEQLimitMaxResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckEQLimitMaxResult_TargetErr;

	if( DestItem->Quality >= DestItem->OrgQuality )
		return EM_CheckEQLimitMaxResult_TargetErr;

	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_EQLimitMax )
		return EM_CheckEQLimitMaxResult_SrcErr;

	return EM_CheckEQLimitMaxResult_OK;
}

CheckIgnoreLimitLvMaxResultENUM	RoleDataEx::CheckIgnoreLimitLv( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( TargetItemOrgDB->IsItem() == false )
		return EM_CheckIgnoreLimitLvMaxResult_TargetErr;

	if( UseItemOrgDB->IsItem() == false || UseItemOrgDB->Item.UseType != EM_ItemUseType_IgnoreLimitLv )
		return EM_CheckIgnoreLimitLvMaxResult_SrcErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckIgnoreLimitLvMaxResult_TargetErr;

	if( TargetItemOrgDB->MaxHeap != 1 )
		return EM_CheckIgnoreLimitLvMaxResult_TargetErr;

	return EM_CheckIgnoreLimitLvMaxResult_OK;
}


//檢查是否可以做PK裝備保護
CheckPkEqProtectResultENUM	RoleDataEx::CheckPkEqProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( TargetItemOrgDB->IsWeapon() == false && TargetItemOrgDB->IsArmor() == false )
		return EM_CheckPkEqProtectResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckPkEqProtectResult_TargetErr;

	if( DestItem->Mode.PkProtect != false )
		return EM_CheckPkEqProtectResult_TargetErr;

	if( TargetItemOrgDB->Mode.PkNoDrop != false )
		return EM_CheckPkEqProtectResult_TargetErr;

	return EM_CheckPkEqProtectResult_OK;
}

//檢查是否可以清除PK裝備保護
CheckPkEqProtectcClearResultENUM	RoleDataEx::CheckPkEqProtectClear( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( DestItem->Mode.PkProtect == false )
		return EM_CheckPkEqProtectClearResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckPkEqProtectClearResult_TargetErr;

	DestItem->Mode.PkProtect = false;

	return EM_CheckPkEqProtectClearResult_OK;
}

//建查是否可以清除裝備上的屬性
CheckClsEqAbilityResultENUM	RoleDataEx::CheckClsEqAbility( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem )
{
	GameObjDbStructEx* UseItemOrgDB		= St_GetObjDB( SrcItem->OrgObjID );
	GameObjDbStructEx* TargetItemOrgDB	= St_GetObjDB( DestItem->OrgObjID );

	if( TargetItemOrgDB->IsArmor() == false && TargetItemOrgDB->IsWeapon() == false )
		return EM_CheckClsEqAbilityResult_TargetErr;

	if( TargetItemOrgDB->CheckInherentAbility( UseItemOrgDB->Item.ItemToItemLimit ) == false )
		return EM_CheckClsEqAbilityResult_TargetErr;

	if( DestItem->_Inherent[ 0 ] == 0  )
		return EM_CheckClsEqAbilityResult_TargetErr;

	//memset( DestItem->_Inherent , 0 , sizeof(DestItem->_Inherent) );

	return EM_CheckClsEqAbilityResult_OK;
}


bool	RoleDataEx::CheckGetJobTitle( int TitleID )
{
	GameObjDbStructEx* TitleObjDB = St_GetObjDB( TitleID );
	if( TitleObjDB == NULL )
		return false;

	if(	TitleObjDB->IsTitle() == false 	 )
		return false;

	if( TitleObjDB->Title.Type	!= EM_TitleNameType_Job )
		return true;		

	if( TitleObjDB->Title.MainJobLV > 0 && TitleObjDB->Title.SubJobLV > 0 )
	{
		if( TitleObjDB->Title.MainJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.MainJobLV > TempData.Attr.Level )
				return false;

			if(	TitleObjDB->Title.SubJob != BaseData.Voc_Sub 
				||	TitleObjDB->Title.SubJobLV > TempData.Attr.Level_Sub )
				return false;
		}
		else if( TitleObjDB->Title.SubJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.SubJobLV > TempData.Attr.Level )
				return false;

			if(	TitleObjDB->Title.MainJob != BaseData.Voc_Sub 
				||	TitleObjDB->Title.MainJobLV > TempData.Attr.Level_Sub )
				return false;
		}
		else
		{
			return false;
		}
	}
	else if( TitleObjDB->Title.MainJobLV > 0 )
	{
		if( TitleObjDB->Title.MainJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.MainJobLV > TempData.Attr.Level )
				return false;
		}
		else if( TitleObjDB->Title.SubJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.SubJobLV > TempData.Attr.Level )
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

//檢查是否可裝此頭銜
bool	RoleDataEx::CheckWearTitle( int TitleID )
{
	if( TitleID == -1 )
		return true;

	GameObjDbStructEx* TitleObjDB = St_GetObjDB( TitleID );
	if( TitleObjDB == NULL )
		return false;

	if( PlayerBaseData->Title.GetFlag(TitleID - Def_ObjectClass_Title ) == false )
		return false;

	if(	TitleObjDB->IsTitle() == false 	 )
	{
		return false;
	}

	if( TitleObjDB->Title.Type	!= EM_TitleNameType_Job )
	{
		if( CheckGetJobTitle( TitleID ) == false )
			return false;
	}
	
/*
	if( TitleObjDB->Title.MainJobLV > 0 && TitleObjDB->Title.SubJobLV > 0 )
	{
		if( TitleObjDB->Title.MainJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.MainJobLV > TempData.Attr.Level )
				return false;

			if(	TitleObjDB->Title.SubJob != BaseData.Voc_Sub 
				||	TitleObjDB->Title.SubJobLV > TempData.Attr.Level_Sub )
				return false;
		}
		else if( TitleObjDB->Title.SubJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.SubJob > TempData.Attr.Level )
				return false;

			if(	TitleObjDB->Title.MainJobLV != BaseData.Voc_Sub 
				||	TitleObjDB->Title.MainJobLV > TempData.Attr.Level_Sub )
				return false;
		}
		else
		{
			return false;
		}
	}
	else if( TitleObjDB->Title.MainJobLV > 0 )
	{
		if( TitleObjDB->Title.MainJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.MainJobLV > TempData.Attr.Level )
				return false;
		}
		else if( TitleObjDB->Title.SubJob == BaseData.Voc  )
		{
			if(	TitleObjDB->Title.SubJob > TempData.Attr.Level )
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

/*
	
	if( TitleObjDB->Title.MainJobLV > 0 )
	{
		if(		TitleObjDB->Title.MainJob != BaseData.Voc 
			||	TitleObjDB->Title.MainJobLV > TempData.Attr.Level )
			return false;
	}

	if( TitleObjDB->Title.SubJobLV > 0 )
	{
		if(		TitleObjDB->Title.SubJob != BaseData.Voc_Sub 
			||	TitleObjDB->Title.SubJobLV > TempData.Attr.Level_Sub )
			return false;
	}
*/
	return true;
}
//檢查法術集合內的輔助法術是否
bool	RoleDataEx::CheckMagicBuffExist( int MagicColID )
{
	GameObjDbStructEx* MagicColDB = St_GetObjDB( MagicColID );
	if( MagicColDB->IsMagicCollect() == false )
		return false;

//	for( int i = 0 ; i < )
	return false;
}

//檢查是否有某卡片
bool	RoleDataEx::CheckCardID( int OrgObjID )
{
	GameObjDbStructEx*	OrgDB;
	OrgDB = St_GetObjDB( OrgObjID );

	if( OrgDB->IsCard() == false )
		return false;

	int ID = OrgDB->GUID -  Def_ObjectClass_Card;

	return  PlayerBaseData->Card.GetFlag( ID );
}


//檢查並清除複製品
void 	RoleDataEx::CheckAndClearCopyItem( )
{
	set< ItemFieldStruct > ItemSet;
	pair< set<ItemFieldStruct>::iterator, bool > InsertRet;


	for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
	{
		ItemFieldStruct& Item = PlayerBaseData->Body.Item[i];
		if(	Item.IsEmpty() != false 	)
			continue;

		GameObjDbStructEx* OrgDB = St_GetObjDB( Item.OrgObjID );

		if( OrgDB == NULL || OrgDB->MaxHeap < Item.Count )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_ErrItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_Body( i );
			continue;
		}
		if( OrgDB->MaxHeap > 1 )
		{
			memset( Item.Ability , 0 , sizeof( Item.Ability ) );
			if( Item.Mode.Trade != !(OrgDB->Mode.PickupBound) )
			{
				Item.Mode.Trade = !(OrgDB->Mode.PickupBound);
				Net_FixItemInfo_Body( i );
			}
		}

		if( Item.Serial == 0 )
		{
			Item.CreateTime = RoleDataEx::G_Now;
			Item.Serial		= St_GenerateItemVersion( );
		}
		
		InsertRet = ItemSet.insert( Item );

		if( InsertRet.second == false )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_CloneItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_Body( i );
		}
	}

	for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )
	{
		ItemFieldStruct& Item = PlayerBaseData->Bank.Item[i];
		if(	Item.IsEmpty() != false 	)
			continue;

		GameObjDbStructEx* OrgDB = St_GetObjDB( Item.OrgObjID );

		if( OrgDB == NULL || OrgDB->MaxHeap < Item.Count )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_ErrItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_Bank( i );
			continue;
		}
		if( OrgDB->MaxHeap > 1 )
		{
			memset( Item.Ability , 0 , sizeof( Item.Ability ) );
			if( Item.Mode.Trade != !(OrgDB->Mode.PickupBound) )
			{
				Item.Mode.Trade = !(OrgDB->Mode.PickupBound);
				Net_FixItemInfo_Bank( i );
			}
		}

		if( Item.Serial == 0 )
		{
			Item.CreateTime = RoleDataEx::G_Now;
			Item.Serial		= St_GenerateItemVersion( );
		}

		InsertRet = ItemSet.insert( Item );

		if( InsertRet.second == false )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_CloneItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_Bank( i );
		}
	}

	for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
	{
		ItemFieldStruct& Item =  BaseData.EQ.Item[ i ];
		if(	Item.IsEmpty() != false 	)
			continue;

		GameObjDbStructEx* OrgDB = St_GetObjDB( Item.OrgObjID );

		if( OrgDB == NULL || OrgDB->MaxHeap < Item.Count )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_ErrItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_EQ( i );
			continue;
		}
		if( OrgDB->MaxHeap > 1 )
		{
			memset( Item.Ability , 0 , sizeof( Item.Ability ) );
			if( Item.Mode.Trade != !(OrgDB->Mode.PickupBound) )
			{
				Item.Mode.Trade = !(OrgDB->Mode.PickupBound);
				Net_FixItemInfo_EQ( i );
			}
		}

		if( Item.Serial == 0 )
		{
			Item.CreateTime = RoleDataEx::G_Now;
			Item.Serial		= St_GenerateItemVersion( );
		}

		InsertRet = ItemSet.insert( Item );

		if( InsertRet.second == false )
		{
			Log_ItemDestroy( EM_ActionType_DestroyItem_CloneItem , Item , -1 , "" );
			Item.Init();
			Net_FixItemInfo_EQ( i );
		}
	}
}

//檢查此寶箱是否能刪除
bool	RoleDataEx::CheckTreasureDelete( )
{
	if( BaseData.Mode.Treasure == false )
		return true;

	if( DynamicData.TreasureBox == NULL )
		return true;

	//檢查寶箱是否有人開啟中
	RoleDataEx* Target = St_GetRoleData( TempData.Trade.TargetID );
	if( Target != NULL )
	{
		if( Length( Target ) < 100 )
		{
			return false;
		}
		else
		{
			TempData.Trade.TargetID = -1;
		}
	}

	if(		(unsigned)DynamicData.TreasureBox->LiveTime < RoleDataEx::G_Now 
		||	DynamicData.TreasureBox->Count == 0 )
	{
		delete DynamicData.TreasureBox;
		DynamicData.TreasureBox = NULL;
		BaseData.Mode.Treasure = false;
		TempData.Trade.TargetID = -1;
		return true;
	}

	return false;
}

bool	RoleDataEx::CheckDisplayDotAttack( GameObjDbStruct* AtkMagic )
{
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
		return true;
	}
	return false;
}

//檢查是否可以移動此物品( 如果是 種植物 並且還沒清空 回傳 false  其它 true  )
bool RoleDataEx::CheckMovePlantItem( ItemFieldStruct& houseItem )
{
	if( houseItem.IsEmpty() )
		return true;

	GameObjDbStructEx* ItemDB = St_GetObjDB( houseItem.OrgObjID );
	if( ItemDB->IsItem() == false || ItemDB->Item.Plant.Pot.Mode == 0 )
		return true;

	if( houseItem.Plant.IsLock != false || houseItem.Plant.SeedID == 0 )
		return true;

	return false;
}

bool	RoleDataEx::IsWagon( )
{
	GameObjDbStructEx* ItemDB = St_GetObjDB( BaseData.ItemInfo.OrgObjID );
	if( ItemDB->IsNPC() == false )
		return false;
	if( ItemDB->NPC.CarryType != EM_NPCCarryType_None )
		return true;
	return false;
}
//檢查Buff
bool RoleDataEx::CheckBuff( int buffID )
{

	for( int i = 0 ; i < BaseData.Buff.Size() ; i++ )
	{
		BuffBaseStruct& buff = BaseData.Buff[i];
		if( buff.BuffID == buffID )
			return true;
	}
	return false;
}