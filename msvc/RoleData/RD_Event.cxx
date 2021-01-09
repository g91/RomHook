#include "RoleDataEx.h"
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnTimeProc( bool IsSpecialCalculate )
{

	if( IsDestroy() )
		return;

    //計算Buff
	if( IsSpecialCalculate == false )
	{
		ClearBuffByEvent( );		

#ifdef _LOCAL_SERVER_
		//冷卻處理
		ColdownProc( );
#endif

		RefineColdownProc();

		BuffProc( );
		//---------------------------------------------------------------------------------------------
		//每分鐘存一次位置
		if( ClockMod( 600 ) )
		{
			BaseData.PlayTime++;
			TempData.Attr.Ability->PlayTime++;
			if( BaseData.PlayTime % 10 == 0 )
				Log_PlayerActionLog();


			for( int i = 0 ; i < _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_ ; i++ )
			{
				if( PlayerBaseData->TimeFlag[i] >= 0 )
				{
					PlayerBaseData->TimeFlag[i]--;
					if( PlayerBaseData->TimeFlag[i] <= 0 )
					{
						Net_FixRoleValue( (RoleValueName_ENUM)(i+EM_RoleValue_TimeFlag) , -1 );
					}
				}
			}

		}
		PlayerBaseData->PlayTimeQuota--;
	}

	// 寵物

    RoleUpdateEvent	Event = TempData.UpdateInfo;
    //---------------------------------------------------------------------------------------------
    // 數值狀態修正
    //---------------------------------------------------------------------------------------------

    if( Event._Event != 0 )
    {
//		if( Event.PhantomChange )
//			PhantomChangeProc();


        if( Event.CheckResetItemInfo() )
        {
            SaveDB_Item( );
        }
    
        if( Event.Eq != false )
        {
            Net_FixLookEQ();
            Event.Recalculate_All = true;
        }

		if( Event.LvChange || Event.VocChange  )
		{
			Event.ReSetTalbe = true;
			Event.FriendListModify = true;
			Event.AllZoneInfoChange = true;
		}

        if( Event.ReSetTalbe || Event.SkillKeyItemChange )
        {
            InitCal();
			
        }
		else if( Event.Recalculate_All != false )
		{
			ReCalculateEQNoBuff();
			ReCalculateBuff();
			Calculate( );
		}
        else if( Event.Recalculate_Buff != false )
        {
            //計算數質
            //ReCalculateMagicAndEQ( );
			ReCalculateBuff();
            Calculate( );
            //Net_MoveSpeed();
        }

		if( Event.LvChange || Event.VocChange  )
		{
			if( Event.VocChange )
			{
				PlayerTempData->Log.ActionMode.ChangeJob = true;
				Net_SendRangeSpecialEfficacy( EM_SpecialEfficacyType_ChangeJob );
			}
			if( Event.LvChange )
			{
				Log_Level();
				GetTitle( );	//以目前的等級資料取得頭銜
			}

			Net_SendGM_ObjInfo();

			if( IsPlayer() )
				Net_ChangeRoleInfo();
		}
		
		if( Event.AllZoneInfoChange )
		{
			Net_SendChat_ChangeRoleInfo();			
		}

		if( Event.AccountMoneyLockInfoChange )
		{
			Net_AccountMoneyLockInfo();
		}

#ifdef _LOCAL_SERVER_
		OnEventAddBuffTime();
#endif

        St_UpDateEvent( this , Event );
        TempData.UpdateInfo._Event = 0;
    }
    //---------------------------------------------------------------------------------------------
	//檢查
	//---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------------------
void RoleDataEx::OnTimeProc_HundredMS()
{	
	//冷卻處理
	ColdownProc( );
}

//-----------------------------------------------------------------------------------------
//定時處理事件
void RoleDataEx::OnTimeProc_NPC( )
{
//    IncDMove( );
}
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnTimeProc_Player( )
{
	IncDMove( );
}
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnCreate( )
{

}
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnDestroy( )
{
	Log_PlayerActionLog();
}
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnAddToPartition( )
{
    TempData.Move.Tx = BaseData.Pos.X;
    TempData.Move.Ty = BaseData.Pos.Y;
    TempData.Move.Tz = BaseData.Pos.Z;
	TempData.Move.Dx = 0;
	TempData.Move.Dy = 0;
	TempData.Move.Dz = 0;

    TempData.Move.AddeDelay = 0;
    TempData.Move.ProcDelay = 0;
}
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnDelFromPartition( )
{

}

void RoleDataEx::OnDead( RoleDataEx* Dead )
{
	// Quest 及 Script 系統用來處理任務死亡計數的事件
	//CNetSrv_Script::OnEvent_ObjDead( this, Dead );
}
//-----------------------------------------------------------------------------------------
//當打到別人( Type = 0 MainHand , 1 OffHand 2 Skill 3 Magic)
void RoleDataEx::OnAttack( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM DmgType , int addHP , int magicColID , int magicID  )
{
	SpecialAttackBuffProc( Target , Type , DmgType , addHP , magicColID , magicID );

	if( addHP >= 0 )
	{
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// SP處理
	/////////////////////////////////////////////////////////////////////////
	switch(Type)
	{
	case 0:
		//if( TempData.Attr.MainWeaponType )
		AddSP	 ( this , TempData.Attr.Arg.ReSPAttack * TempData.Attr.Fin.MainJobSPRate * TempData.Attr.Fin.Main_ATKSpeed * 0.1f );
		AddSP_Sub( this , TempData.Attr.Arg_Sub.ReSPAttack * TempData.Attr.Fin.SubJobSPRate * TempData.Attr.Fin.Main_ATKSpeed * 0.1f );
		break;
	case 1:
		AddSP	 ( this , TempData.Attr.Arg.ReSPAttack * TempData.Attr.Fin.MainJobSPRate * TempData.Attr.Fin.Sec_ATKSpeed * 0.1f  / 3 );
		AddSP_Sub( this , TempData.Attr.Arg_Sub.ReSPAttack * TempData.Attr.Fin.SubJobSPRate * TempData.Attr.Fin.Sec_ATKSpeed * 0.1f  /3  );
		break;
	case 2:
		break;
	}

	Target->AddSP	 ( Target , Target->TempData.Attr.Arg.ReSPUnderAttack * Target->TempData.Attr.Fin.MainJobSPRate );
	Target->AddSP_Sub( Target , Target->TempData.Attr.Arg_Sub.ReSPUnderAttack * Target->TempData.Attr.Fin.SubJobSPRate);
	//////////////////////////////////////////////////////////////////////////

	if(		DmgType == EM_ATTACK_DMGTYPE_HALF 
		|| 	DmgType == EM_ATTACK_DMGTYPE_NORMAL 
		|| 	DmgType == EM_ATTACK_DMGTYPE_DOUBLE 
		|| 	DmgType == EM_ATTACK_DMGTYPE_TRIPLE 
		/*|| 	DmgType == EM_ATTACK_DMGTYPE_ABSORB*/ 	)
	{
		Target->CheckMagicInterrupt_OnAttack();
		//////////////////////////////////////////////////////////////////////////
		//	清除被攻擊消失的Buff
		//////////////////////////////////////////////////////////////////////////
		Target->TempData.BackInfo.BuffClearTime.UnderAtk = true;	
		TempData.BackInfo.BuffClearTime.Attack = true;
	}

}
