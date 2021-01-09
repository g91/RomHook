#include "RoleDataEx.h"
//-----------------------------------------------------------------------------------------
boost::function< int(int) >             					RoleDataEx::St_GetKeyMagicID        = Empty_GetKeyMagicID;
boost::function< GameObjDbStructEx*(int) >             	RoleDataEx::St_GetObjDB             = Empty_GetObjDB;
boost::function< RoleDataEx*(int) >                    	RoleDataEx::St_GetRoleData          = Empty_GetRoleData;
boost::function< int() >	                            	RoleDataEx::St_GenerateItemVersion  = Empty_GenerateItemVersionFunction;
boost::function< bool(ItemFieldStruct&,int,int) >			RoleDataEx::St_NewItemInit          = Empty_NewitemInit;
boost::function< void(RoleDataEx* , RoleUpdateEvent) > 	RoleDataEx::St_UpDateEvent          = Empty_UpDateEvent;
boost::function< bool(RoleDataEx*, RoleDataEx*) >      	RoleDataEx::St_ProcessDead          = Empty_ProcessDead;
boost::function< bool(RoleDataEx*,MagicProcInfo*,int) >	RoleDataEx::St_SpellMagic           = Empty_SpellMagic;
boost::function< int(int,float,float,float,float,int,int) >RoleDataEx::St_CreateObj			= Empty_CreateObj;
boost::function< bool(int,int) >							RoleDataEx::St_AddToPartition		= Empty_AddToPartition;
boost::function< bool(int) >								RoleDataEx::St_DelFromPartition		= Empty_DelFromPartition;
boost::function< void(int) >				             	RoleDataEx::St_ClearPath			= Empty_ClearPath;
boost::function< void(int) >				             	RoleDataEx::St_SetPos				= Empty_ClearPath;
boost::function< const char*(RoleDataEx*) >			   	RoleDataEx::St_GetRoleName			= Empty_GetRoleName;
boost::function< SysKeyValueStruct*() >	             	RoleDataEx::St_SysKeyValue			= Empty_SysKeyValueStruct;
boost::function< GameObjDbStructEx*(GameObjDbStructEx*,GameObjDbStructEx*) >	RoleDataEx::St_RuneExchange = Empty_RuneExchange;
boost::function< GameObjDbStructEx*(GameObjDbStructEx*) >	RoleDataEx::St_NextRuneLv			= Empty_NextRuneLv;
boost::function< int(const char* ) >		             	RoleDataEx::St_GetSysKeyValue		= Empty_GetSysKeyValue;
boost::function< int(const char*) >						RoleDataEx::St_GetPCenterID			= Empty_GetPCenterID;
//-----------------------------------------------------------------------------------------
#define Def_Disabled_Update_Flag 0x01
#define Def_Disabled_Insert_Flag 0x02
#define Def_Disabled_Select_Flag 0x04
//-----------------------------------------------------------------------------------------
void RoleDataEx::OnTimeProcAll( )
{
    G_SysTime = timeGetTime() - G_SysTime_Base;
    G_Clock++;

}
//----------------------------------------------------------------------------------------------------------------
ReaderClass<PlayerRoleData>* RoleDataEx::ReaderBase_Account( )
{
	static  ReaderClass<PlayerRoleData> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		char    Buf[256];
		
		PlayerRoleData* Pt = NULL;
		Reader.SetData( "AccountMoney"  , &Pt->PlayerBaseData.Body.Money_Account	, ENUM_Type_IntPoint       );
		Reader.SetData( "BonusMoney"	, &Pt->PlayerBaseData.Money_Bonus			, ENUM_Type_IntPoint       );
		Reader.SetData( "ManageLv"		, &Pt->PlayerBaseData.ManageLV				, ENUM_Type_IntPoint      , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "Password"		,  Pt->PlayerBaseData.Password.Begin()		, ENUM_Type_CharString    , sizeof(Pt->PlayerBaseData.Password)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "PlayTimeQuota" , &Pt->PlayerBaseData.PlayTimeQuota			, ENUM_Type_IntPoint       );
		Reader.SetData( "LogoutTime"	, &Pt->Base.LogoutTime						, ENUM_Type_IntPoint      , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );

		Reader.SetData( "LockAccountTime"			, &Pt->PlayerBaseData.LockAccountTime			, ENUM_Type_IntPoint		);
		for( int i = 0; i < Def_AccountMoneyLockTime_Max_Count_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "LockAccountMoney%d" , i+1  );
			Reader.SetData( Buf						, &Pt->PlayerBaseData.LockAccountMoney[i]		, ENUM_Type_IntPoint		);
		}
		Reader.SetData( "LockAccountMoney_Forever"	, &Pt->PlayerBaseData.LockAccountMoney_Forever	, ENUM_Type_IntPoint		);
		Reader.SetData( "AccountFlag"	, &Pt->Base.AccountFlag						, ENUM_Type_BinaryData	, sizeof(Pt->Base.AccountFlag) );

		Reader.SetData( "VipMemberType"		, &Pt->PlayerBaseData.VipMember.Type		, ENUM_Type_IntPoint      , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "VipMemberTerm"		, &Pt->PlayerBaseData.VipMember.Term		, ENUM_Type_SmallDateTime , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "VipMemberFlag"		, &Pt->PlayerBaseData.VipMember._Flag		, ENUM_Type_IntPoint      , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "UntrustFlag"		, &Pt->PlayerBaseData.VipMember.UntrustFlag._Flag		, ENUM_Type_IntPoint      , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
		Reader.SetData( "CoolClothList"		, &Pt->PlayerBaseData.CoolClothList			, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.CoolClothList) );
		IsReady = true;
	}      
	return &Reader;
}

ReaderClass<PlayerRoleData>* RoleDataEx::ReaderBase( )
{
    static  ReaderClass<PlayerRoleData> Reader;
    static  bool    IsReady = false;
    if( IsReady == false )
    {   
        char    Buf[256];
        PlayerRoleData* Pt = NULL;
        Reader.SetData( "CharField"     , &Pt->Base.CharField               , ENUM_Type_IntPoint       );
        Reader.SetData( "DBID"          , &Pt->Base.DBID                    , ENUM_Type_IntPoint       , 0								, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag);
		Reader.SetData( "Account_ID"    ,  Pt->Base.Account_ID.Begin()      , ENUM_Type_CharString     , sizeof(Pt->Base.Account_ID)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "CreateTime"    ,  Pt->Base.CreateTime.Begin()      , ENUM_Type_CharString     , sizeof(Pt->Base.CreateTime)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag);
        Reader.SetData( "LogoutTime"    , &Pt->Base.LogoutTime              , ENUM_Type_IntPoint       );
        Reader.SetData( "Type"          , &Pt->Base.Type                    , ENUM_Type_IntPoint       , 0								, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag);

        Reader.SetData( "Mode"          , &Pt->BaseData.Mode                , ENUM_Type_IntPoint       );
		Reader.SetData( "RoleName"      ,  Pt->BaseData.RoleName.Begin()    , ENUM_Type_WCharString    , sizeof(Pt->BaseData.RoleName)  , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "ZoneID"        , &Pt->BaseData.ZoneID              , ENUM_Type_IntPoint       );
		Reader.SetData( "X"             , &Pt->BaseData.Pos.X               , ENUM_Type_FloatPoint     );
		Reader.SetData( "Y"             , &Pt->BaseData.Pos.Y               , ENUM_Type_FloatPoint     );
        Reader.SetData( "Z"             , &Pt->BaseData.Pos.Z               , ENUM_Type_FloatPoint     );
        Reader.SetData( "Dir"           , &Pt->BaseData.Pos.Dir             , ENUM_Type_FloatPoint     );
        Reader.SetData( "RoomID"        , &Pt->BaseData.RoomID              , ENUM_Type_IntPoint       );
		Reader.SetData( "vX"            , &Pt->BaseData.vX               	, ENUM_Type_FloatPoint     );
		Reader.SetData( "vY"            , &Pt->BaseData.vY               	, ENUM_Type_FloatPoint     );
		Reader.SetData( "vZ"            , &Pt->BaseData.vZ               	, ENUM_Type_FloatPoint     );


		Reader.SetData( "PlayTime"      , &Pt->BaseData.PlayTime            , ENUM_Type_IntPoint		);

		Reader.SetData( "IsShowTitle"	, &Pt->BaseData.IsShowTitle			, ENUM_Type_BitPoint       );
		Reader.SetData( "TitleStr"      ,  Pt->PlayerBaseData.TitleStr.Begin()    , ENUM_Type_WCharString     , sizeof(Pt->PlayerBaseData.TitleStr)  , ENUM_Indirect_Address   );
        Reader.SetData( "TitleID"       , &Pt->BaseData.TitleID             , ENUM_Type_IntPoint       );        
        Reader.SetData( "Race"          , &Pt->BaseData.Race                , ENUM_Type_IntPoint       );        
        Reader.SetData( "Voc"           , &Pt->BaseData.Voc                 , ENUM_Type_IntPoint       );        
        Reader.SetData( "Voc_Sub"       , &Pt->BaseData.Voc_Sub             , ENUM_Type_IntPoint       );        
		Reader.SetData( "LV"            , &Pt->TempData.Attr.Level			, ENUM_Type_IntPoint       );        
		Reader.SetData( "LV_Sub"        , &Pt->TempData.Attr.Level_Sub      , ENUM_Type_IntPoint       );        

        //Reader.SetData( "Famous"        , &Pt->PlayerBaseData.Famous              , ENUM_Type_IntPoint       );        
        Reader.SetData( "Sex"           , &Pt->BaseData.Sex                 , ENUM_Type_IntPoint       );        
        Reader.SetData( "HP"            , &Pt->BaseData.HP                  , ENUM_Type_FloatPoint     );        
        Reader.SetData( "MP"            , &Pt->BaseData.MP                  , ENUM_Type_FloatPoint     );        
		Reader.SetData( "StomachPoint"  , &Pt->BaseData.StomachPoint        , ENUM_Type_IntPoint       );        
//		Reader.SetData( "AddExp"        , &Pt->PlayerBaseData.AddExp              , ENUM_Type_IntPoint       );        
//		Reader.SetData( "AddTp"         , &Pt->PlayerBaseData.AddTp               , ENUM_Type_IntPoint       );        

		Reader.SetData( "MaxLv"         , &Pt->PlayerBaseData.MaxLv         , ENUM_Type_IntPoint       );        
 
		Reader.SetData( "BodyCount"     , &Pt->PlayerBaseData.Body.Count    , ENUM_Type_IntPoint       );        
		Reader.SetData( "BankCount"     , &Pt->PlayerBaseData.Bank.Count	, ENUM_Type_IntPoint       );      
		Reader.SetData( "BodyMoney"     , &Pt->PlayerBaseData.Body.Money    , ENUM_Type_IntPoint       );        
		Reader.SetData( "BankMoney"     , &Pt->PlayerBaseData.Bank.Money	, ENUM_Type_IntPoint       );      

        Reader.SetData( "RevZoneID"     , &Pt->SelfData.RevZoneID     		, ENUM_Type_IntPoint       );
        Reader.SetData( "RevX"          , &Pt->SelfData.RevPos.X      		, ENUM_Type_FloatPoint     );
        Reader.SetData( "RevY"          , &Pt->SelfData.RevPos.Y      		, ENUM_Type_FloatPoint     );
        Reader.SetData( "RevZ"          , &Pt->SelfData.RevPos.Z      		, ENUM_Type_FloatPoint     );
        Reader.SetData( "RevDir"        , &Pt->SelfData.RevPos.Dir    		, ENUM_Type_FloatPoint     );

		Reader.SetData( "ReturnZoneID"  , &Pt->SelfData.ReturnZoneID  		, ENUM_Type_IntPoint       );
		Reader.SetData( "ReturnX"       , &Pt->SelfData.ReturnPos.X   		, ENUM_Type_FloatPoint     );
		Reader.SetData( "ReturnY"       , &Pt->SelfData.ReturnPos.Y   		, ENUM_Type_FloatPoint     );
		Reader.SetData( "ReturnZ"       , &Pt->SelfData.ReturnPos.Z   		, ENUM_Type_FloatPoint     );
		Reader.SetData( "ReturnDir"     , &Pt->SelfData.ReturnPos.Dir 		, ENUM_Type_FloatPoint     );


        Reader.SetData( "KeyItem"		, &Pt->BaseData.KeyItem				, ENUM_Type_BinaryData  , sizeof(Pt->BaseData.KeyItem)  );        
		Reader.SetData( "Card"			, &Pt->PlayerBaseData.Card			, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Card)  );        
        Reader.SetData( "Title"			, &Pt->PlayerBaseData.Title         , ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Title)                 );        
        Reader.SetData( "QuestHistory"	, &Pt->PlayerBaseData.Quest.QuestHistory  , ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Quest.QuestHistory)    );        
		Reader.SetData( "RentFunction"	, &Pt->PlayerBaseData.RentFun		, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.RentFun) );        

		Reader.SetData( "QuestLog"			, &Pt->PlayerBaseData.Quest.QuestLog		, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Quest.QuestLog)    );  

		Reader.SetData( "QuestDaily"		, &Pt->PlayerBaseData.Quest.QuestDaily		, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Quest.QuestDaily)    );        
		Reader.SetData( "QuestGroup"		, &Pt->PlayerBaseData.Quest.iQuestGroup		, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.Quest.iQuestGroup)    );
		Reader.SetData( "LastCompleteTime"	, &Pt->PlayerBaseData.Quest.LastCompleteTime	, ENUM_Type_IntPoint   );


        for( int i = 0 ; i < _MAX_SKILLVALUE_TYPE ; i++ )
        {
            sprintf_s( Buf , sizeof(Buf) , "SkillValue%d" , i + 1 );
            Reader.SetData( Buf        , &Pt->BaseData.SkillValue.Skill[i]  , ENUM_Type_FloatPoint     );
        }

        Reader.SetData( "Buff"          , &Pt->BaseData.Buff                , ENUM_Type_BinaryData  , sizeof(Pt->BaseData.Buff)  );        
        Reader.SetData( "DeadCountDown" , &Pt->PlayerBaseData.DeadCountDown       , ENUM_Type_IntPoint     );
        
        //®e»ª
        Reader.SetData( "FaceID"          , &Pt->BaseData.Look.FaceID       , ENUM_Type_IntPoint       );
        Reader.SetData( "HairID"          , &Pt->BaseData.Look.HairID       , ENUM_Type_IntPoint       );
        Reader.SetData( "HairColor"       , &Pt->BaseData.Look.HairColor    , ENUM_Type_IntPoint       );
        Reader.SetData( "BodyColor"       , &Pt->BaseData.Look.BodyColor    , ENUM_Type_IntPoint       );

		Reader.SetData( "BoneScale"		  , &Pt->BaseData.Look.BoneScale  , ENUM_Type_BinaryData  , sizeof(Pt->BaseData.Look.BoneScale)  );        

        Reader.SetData( "OrgObjID"        , &Pt->BaseData.ItemInfo.OrgObjID , ENUM_Type_IntPoint       );
		Reader.SetData( "PartyID"         , &Pt->BaseData.PartyID			, ENUM_Type_IntPoint       );
		Reader.SetData( "GuildID"         , &Pt->BaseData.GuildID			, ENUM_Type_IntPoint       , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag);
		Reader.SetData( "GuildLeaveTime"  , &Pt->BaseData.GuildLeaveTime	, ENUM_Type_SmallDateTime  , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag);

		Reader.SetData( "FriendNote"		,  Pt->PlayerSelfData.FriendList.Note.Begin()			, ENUM_Type_WCharString , sizeof(Pt->PlayerSelfData.FriendList.Note)   );

        Reader.SetData( "Coldown"          , &Pt->BaseData.Coldown           , ENUM_Type_BinaryData  , sizeof(Pt->BaseData.Coldown)  );
		Reader.SetData( "RefineColdown"    , &Pt->PlayerBaseData.RefineColdown     , ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.RefineColdown)  );

		Reader.SetData( "IsBillboardAnonymous"	, &Pt->PlayerBaseData.IsBillboardAnonymous	, ENUM_Type_BitPoint       );
		Reader.SetData( "PKScore"				, &Pt->PlayerBaseData.PKScore					, ENUM_Type_IntPoint       );	
		Reader.SetData( "TitleCount"			, &Pt->PlayerBaseData.TitleCount				, ENUM_Type_IntPoint       );	
		Reader.SetData( "HouseDBID"				, &Pt->PlayerBaseData.HouseDBID					, ENUM_Type_IntPoint       , 0			, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );	
		Reader.SetData( "ClientFlag"			, &Pt->PlayerBaseData.ClientFlag				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.ClientFlag)  );        
		Reader.SetData( "ClientData"			, &Pt->PlayerBaseData.ClientData				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.ClientData)  );        

		Reader.SetData( "FriendClientData"		, &Pt->PlayerSelfData.FriendList.ClientData		, ENUM_Type_BinaryData  , sizeof(Pt->PlayerSelfData.FriendList.ClientData)  );        
		Reader.SetData( "FriendGroupSortID"		, &Pt->PlayerSelfData.FriendList.GroupSortID	, ENUM_Type_BinaryData  , sizeof(Pt->PlayerSelfData.FriendList.GroupSortID)  );        
		Reader.SetData( "MonsterHunter"			, &Pt->PlayerSelfData.MonsterHunter				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerSelfData.MonsterHunter)  );        

		Reader.SetData( "SysFlag"				, &Pt->BaseData.SysFlag._Value					, ENUM_Type_IntPoint		);        

		for( int i = 0 ; i < _MAX_FAMOUS_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "Famous%d" , i+1  );
			Reader.SetData( Buf					,  &Pt->PlayerBaseData.Famous[i]				, ENUM_Type_IntPoint		);
		}
		Reader.SetData( "DestroyTime"			, &Pt->PlayerBaseData.DestroyTime				, ENUM_Type_IntPoint       , 0								, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag); 
//		Reader.SetData( "ShowEQ"				, &Pt->PlayerBaseData.ShowEQ._Value				, ENUM_Type_IntPoint		);        
        Reader.SetData( "GoodEvil"				, &Pt->PlayerBaseData.GoodEvil       			, ENUM_Type_FloatPoint		);
        Reader.SetData( "GoodEvilBonus"			, &Pt->PlayerBaseData.GoodEvilBonus  			, ENUM_Type_FloatPoint		);
        Reader.SetData( "VocCount"				, &Pt->PlayerBaseData.VocCount       			, ENUM_Type_IntPoint		);
		Reader.SetData( "BoxEnergy"				, &Pt->PlayerBaseData.BoxEnergy       			, ENUM_Type_IntPoint		);

//		Reader.SetData( "BoxEnergy"				, &Pt->PlayerBaseData.BoxEnergy       		, ENUM_Type_IntPoint		);

		Reader.SetData( "RealTimeFlag"			, &Pt->PlayerBaseData.RealTimeFlag				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.RealTimeFlag)  );        
		Reader.SetData( "PlayTimeFlag"			, &Pt->PlayerBaseData.PlayTimeFlag				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.PlayTimeFlag)  );        
		Reader.SetData( "LuaValueFlag"			, &Pt->PlayerBaseData.LuaValueFlag				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.LuaValueFlag)  );        
		Reader.SetData( "MedalCount"			, &Pt->PlayerBaseData.MedalCount       			, ENUM_Type_IntPoint		);
//		Reader.SetData( "Money_Bonus"			, &Pt->PlayerBaseData.Money_Bonus       			, ENUM_Type_IntPoint		);
		Reader.SetData( "LocationSave"			, &Pt->PlayerBaseData.LocationSave				, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.LocationSave)  );        
		Reader.SetData( "HorseColor"			, &Pt->BaseData.HorseColor						, ENUM_Type_BinaryData  , sizeof(Pt->BaseData.HorseColor)  );

		Reader.SetData( "RaiseMode"				, &Pt->PlayerBaseData.RaiseInfo.Mode.Mode		, ENUM_Type_IntPoint		);
		Reader.SetData( "RaiseExpRate"			, &Pt->PlayerBaseData.RaiseInfo.ExpRate  		, ENUM_Type_IntPoint		);
		Reader.SetData( "RaiseZoneID"			, &Pt->PlayerBaseData.RaiseInfo.ZoneID   		, ENUM_Type_IntPoint		);
		Reader.SetData( "RaiseRevX"				, &Pt->PlayerBaseData.RaiseInfo.RevX     		, ENUM_Type_FloatPoint		);
		Reader.SetData( "RaiseRevY"				, &Pt->PlayerBaseData.RaiseInfo.RevY     		, ENUM_Type_FloatPoint		);
		Reader.SetData( "RaiseRevZ"				, &Pt->PlayerBaseData.RaiseInfo.RevZ     		, ENUM_Type_FloatPoint		);

//		Reader.SetData( "TombItemGUID"			, &Pt->PlayerSelfData.Tomb.ItemGUID			, ENUM_Type_IntPoint		);
		Reader.SetData( "TombCreateTime"		, &Pt->PlayerSelfData.Tomb.CreateTime			, ENUM_Type_IntPoint		);
		Reader.SetData( "TombZoneID"			, &Pt->PlayerSelfData.Tomb.ZoneID				, ENUM_Type_IntPoint		);
		Reader.SetData( "TombX"					, &Pt->PlayerSelfData.Tomb.X					, ENUM_Type_FloatPoint		);
		Reader.SetData( "TombY"					, &Pt->PlayerSelfData.Tomb.Y					, ENUM_Type_FloatPoint		);
		Reader.SetData( "TombZ"					, &Pt->PlayerSelfData.Tomb.Z					, ENUM_Type_FloatPoint		);
		Reader.SetData( "TombDebtExp"			, &Pt->PlayerSelfData.Tomb.DebtExp				, ENUM_Type_IntPoint		);
		Reader.SetData( "TombDebtTp"			, &Pt->PlayerSelfData.Tomb.DebtTp				, ENUM_Type_IntPoint		);
		Reader.SetData( "TombExp"				, &Pt->PlayerSelfData.Tomb.Exp					, ENUM_Type_IntPoint		);

		Reader.SetData( "Honor"					, &Pt->PlayerBaseData.Honor						, ENUM_Type_FloatPoint		);
		Reader.SetData( "HonorWorth"			, &Pt->PlayerBaseData.HonorWorth				, ENUM_Type_FloatPoint		);
		Reader.SetData( "LastBeHonorKilledTime"	, &Pt->PlayerBaseData.LastBeHonorKilledTime		, ENUM_Type_IntPoint		);
		Reader.SetData( "MaxPlantCount"			, &Pt->PlayerBaseData.MaxPlantCount				, ENUM_Type_IntPoint		);

		Reader.SetData( "MoneyTraderCount"		, &Pt->PlayerBaseData.Defendant.MoneyTraderCount, ENUM_Type_FloatPoint		);
		Reader.SetData( "AutoBotCount"			, &Pt->PlayerBaseData.Defendant.AutoBotCount	, ENUM_Type_FloatPoint		);

		Reader.SetData( "BotReportDBID"			, &Pt->PlayerBaseData.Defendant.BotReportDBID	, ENUM_Type_IntPoint		);
		Reader.SetData( "BotReportTime"			, &Pt->PlayerBaseData.Defendant.BotReportTime	, ENUM_Type_IntPoint		);
		Reader.SetData( "BotReportProtectTime"	, &Pt->PlayerBaseData.Defendant.BotReportProtectTime	, ENUM_Type_IntPoint		);

//		Reader.SetData( "InstanceSetting"		, &Pt->PlayerBaseData.InstanceSetting			, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.InstanceSetting) );
		Reader.SetData( "InstanceSetting_KeyID"		, &Pt->PlayerBaseData.InstanceSetting.KeyID		, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.InstanceSetting.KeyID) );
		Reader.SetData( "InstanceSetting_LiveTime"	, &Pt->PlayerBaseData.InstanceSetting.LiveTime	, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.InstanceSetting.LiveTime) );
		Reader.SetData( "InstanceSetting_ExtendTime", &Pt->PlayerBaseData.InstanceSetting.ExtendTime, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.InstanceSetting.ExtendTime) );


		Reader.SetData( "ExpDownRate"			, &Pt->PlayerBaseData.RaiseInfo.ExpDownRate		, ENUM_Type_IntPoint		);
		Reader.SetData( "DebtExpRate"			, &Pt->PlayerBaseData.RaiseInfo.DebtExpRate		, ENUM_Type_IntPoint		);
		Reader.SetData( "DebtTpRate"			, &Pt->PlayerBaseData.RaiseInfo.DebtTpRate		, ENUM_Type_IntPoint		);

		Reader.SetData( "RoomKey"				, &Pt->PlayerBaseData.RoomKey					, ENUM_Type_IntPoint		);

		Reader.SetData( "SuitSkill_LearnCount"	, &Pt->PlayerBaseData.SuitSkill.LeanSkillCount	, ENUM_Type_IntPoint		);
		Reader.SetData( "SuitSkill_MaxEqCount"	, &Pt->PlayerBaseData.SuitSkill.MaxEqSkillCount	, ENUM_Type_IntPoint		);
		Reader.SetData( "SuitSkill_Learn"		, &Pt->PlayerBaseData.SuitSkill.LeanSkillList	, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.SuitSkill.LeanSkillList));
		Reader.SetData( "SuitSkill_EQ"			, &Pt->PlayerBaseData.SuitSkill.EQ				, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.SuitSkill.EQ));

		Reader.SetData( "Pet_NextMergeResetTime", &Pt->PlayerBaseData.Pet.NextMergeResetTime	, ENUM_Type_IntPoint		);
		Reader.SetData( "Pet_Money"				, &Pt->PlayerBaseData.Pet.Money					, ENUM_Type_IntPoint		);

		Reader.SetData( "CoolSuitList"			, &Pt->PlayerBaseData.CoolSuitList				, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.CoolSuitList) );
//		Reader.SetData( "CoolClothList"			, &Pt->PlayerBaseData.CoolClothList				, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.CoolClothList) );
		Reader.SetData( "CoolSuitID"			, &Pt->PlayerBaseData.CoolSuitID				, ENUM_Type_IntPoint		);

		Reader.SetData( "PetExBag"				, &Pt->PlayerBaseData.PetExBag					, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.PetExBag) );
		Reader.SetData( "HorseExBag"			, &Pt->PlayerBaseData.HorseExBag				, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.HorseExBag) );
		Reader.SetData( "IncursivePoint"		, &Pt->PlayerBaseData.IncursivePoint			, ENUM_Type_IntPoint		);
		Reader.SetData( "DuelistReward"			, &Pt->PlayerBaseData.DuelistReward				, ENUM_Type_IntPoint		);
		Reader.SetData( "MirrorCoin"			, &Pt->PlayerBaseData.MirrorCoin				, ENUM_Type_IntPoint		);

		Reader.SetData( "TitleSys_Famous"		, &Pt->PlayerBaseData.TitleSys.Famous			, ENUM_Type_FloatPoint		);
		Reader.SetData( "TitleSys_Lv"			, &Pt->PlayerBaseData.TitleSys.Lv				, ENUM_Type_IntPoint		);
		Reader.SetData( "TitleSys_Exp"			, &Pt->PlayerBaseData.TitleSys.Exp				, ENUM_Type_IntPoint		);
		for( int i = 0 ; i < _MAX_TITLESYS_TITLE_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "TitleSys_TitleID%d" , i+1  );
			Reader.SetData( Buf					,  &Pt->PlayerBaseData.TitleSys.TitleID[i]		, ENUM_Type_IntPoint		);
		}
		Reader.SetData( "SlotMachine_History"	, &Pt->PlayerBaseData.SlotMachine.History		, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.SlotMachine.History) );
		Reader.SetData( "SlotMachine_RandSeed"	, &Pt->PlayerBaseData.SlotMachine.RandSeed		, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.SlotMachine.RandSeed) );
		Reader.SetData( "SlotMachine_FreeCount"	, &Pt->PlayerBaseData.SlotMachine.FreeCount		, ENUM_Type_IntPoint		);
		Reader.SetData( "PetCard"				, &Pt->PlayerBaseData.PetCard					, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.PetCard) );
		Reader.SetData( "DreamlandCoin"			, &Pt->PlayerBaseData.DreamlandCoin				, ENUM_Type_IntPoint		);
		Reader.SetData( "PhiriusShellCoin"		, &Pt->PlayerBaseData.PhiriusShellCoin			, ENUM_Type_IntPoint		);
		Reader.SetData( "EnergyJusticeCoin"		, &Pt->PlayerBaseData.EnergyJusticeCoin			, ENUM_Type_IntPoint		);
		Reader.SetData( "ProofLegendCoin"		, &Pt->PlayerBaseData.ProofLegendCoin			, ENUM_Type_IntPoint		);
		Reader.SetData( "RelicsCoin"			, &Pt->PlayerBaseData.RelicsCoin				, ENUM_Type_IntPoint		);
		Reader.SetData( "TrialBadgeCoin"		, &Pt->PlayerBaseData.TrialBadgeCoin			, ENUM_Type_IntPoint		);

		Reader.SetData( "WeekInstance"			, &Pt->PlayerBaseData.WeekInstance				, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.WeekInstance) );
		Reader.SetData( "WeekInstDay"			, &Pt->PlayerBaseData.WeekInstDay				, ENUM_Type_IntPoint		);
		Reader.SetData( "WeekResetCount"		, &Pt->PlayerBaseData.WeekResetCount				, ENUM_Type_IntPoint		);
		Reader.SetData( "Phantom"				, &Pt->PlayerBaseData.Phantom					, ENUM_Type_BinaryData		, sizeof(Pt->PlayerBaseData.Phantom) );

        IsReady = true;
    }      
    return &Reader;
}

//----------------------------------------------------------------------------------------------------------------
/*
ReaderClass<RoleDataEx>* RoleDataEx::ReaderBaseEx( )
{
	static  ReaderClass<RoleDataEx> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		char    Buf[256];
		RoleData* Pt = NULL;
		Reader.SetData( "DBID"					, &Pt->Base.DBID						, ENUM_Type_IntPoint    , 0								, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag);

		Reader.SetData( "RealTimeFlag"			, &Pt->PlayerBaseData.RealTimeFlag			, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.RealTimeFlag)  );        
		Reader.SetData( "PlayTimeFlag"			, &Pt->PlayerBaseData.PlayTimeFlag			, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.PlayTimeFlag)  );        
		Reader.SetData( "LuaValueFlag"			, &Pt->PlayerBaseData.LuaValueFlag			, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.LuaValueFlag)  );        
		Reader.SetData( "MedalCount"			, &Pt->PlayerBaseData.MedalCount       		, ENUM_Type_IntPoint		);
		Reader.SetData( "Money_Bonus"			, &Pt->PlayerBaseData.Money_Bonus       		, ENUM_Type_IntPoint		);
		Reader.SetData( "LocationSave"			, &Pt->PlayerBaseData.LocationSave			, ENUM_Type_BinaryData  , sizeof(Pt->PlayerBaseData.LocationSave)  );        
		IsReady = true;
	}      
	return &Reader;
}
*/

//----------------------------------------------------------------------------------------------------------------
ReaderClass<NPCData>* RoleDataEx::ReaderNPC( )
{
    static  ReaderClass<NPCData> Reader;
    static  bool    IsReady = false;
    if( IsReady == false )
    {   
        NPCData* Pt = NULL;

        Reader.SetData( "DBID"          , &Pt->DBID                 	, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "CreateTime"    ,  Pt->CreateTime.Begin()   	, ENUM_Type_CharString     , sizeof(Pt->CreateTime) , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );
        Reader.SetData( "OrgObjID"      ,  &Pt->OrgObjID            	, ENUM_Type_IntPoint       );
        
        Reader.SetData( "Mode"          , &Pt->Mode                 	, ENUM_Type_IntPoint       );
        Reader.SetData( "RoleName"      ,  Pt->RoleName.Begin()     	, ENUM_Type_WCharString     , sizeof(Pt->RoleName) );
        Reader.SetData( "ZoneID"        , &Pt->ZoneID               	, ENUM_Type_IntPoint       );
		Reader.SetData( "RoomID"        , &Pt->RoomID               	, ENUM_Type_IntPoint       );
        Reader.SetData( "X"             , &Pt->Pos.X                	, ENUM_Type_FloatPoint     );
        Reader.SetData( "Y"             , &Pt->Pos.Y                	, ENUM_Type_FloatPoint     );
        Reader.SetData( "Z"             , &Pt->Pos.Z                	, ENUM_Type_FloatPoint     );
        Reader.SetData( "Dir"           , &Pt->Pos.Dir              	, ENUM_Type_FloatPoint     );

		Reader.SetData( "vX"            , &Pt->vX						, ENUM_Type_FloatPoint     );
		Reader.SetData( "vY"            , &Pt->vY						, ENUM_Type_FloatPoint     );
		Reader.SetData( "vZ"            , &Pt->vZ			            , ENUM_Type_FloatPoint     );


        Reader.SetData( "LiveTime"      , &Pt->LiveTime             	, ENUM_Type_IntPoint       );        
        Reader.SetData( "OwnerDBID"     , &Pt->OwnerDBID            	, ENUM_Type_IntPoint       );        
        Reader.SetData( "PID"           , &Pt->PID                  	, ENUM_Type_IntPoint       );        
        Reader.SetData( "PlotClassName" ,  Pt->PlotClassName.Begin()	, ENUM_Type_CharString     , sizeof(Pt->PlotClassName) );        
        Reader.SetData( "AutoPlot"      ,  Pt->AutoPlot.Begin()     	, ENUM_Type_CharString     , sizeof(Pt->AutoPlot) );        
        Reader.SetData( "QuestID"       , &Pt->QuestID			    	, ENUM_Type_IntPoint	   );        
        Reader.SetData( "CreateAccount" ,  Pt->CreateAccount.Begin()    , ENUM_Type_CharString	   , sizeof(Pt->CreateAccount) );        
        IsReady = true;
    }      
    return &Reader;
}
//----------------------------------------------------------------------------------------------------------------
ReaderClass<DB_ItemFieldStruct>*  RoleDataEx::ReaderRD_Field( )
{
	static  ReaderClass<DB_ItemFieldStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_ItemFieldStruct* Pt = NULL;
        Reader.SetData( "DBID"          , &Pt->DBID                 , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "FieldID"       , &Pt->FieldID              , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "FieldType"     , &Pt->FieldType            , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );

        Reader.SetData( "OrgObjID"      , &Pt->Info.OrgObjID        , ENUM_Type_IntPoint        );
        Reader.SetData( "Serial"        , &Pt->Info.Serial          , ENUM_Type_IntPoint        );
        Reader.SetData( "CreateTime"    , &Pt->Info.CreateTime      , ENUM_Type_IntPoint        );
		Reader.SetData( "ExValue"		, &Pt->Info.ExValue			, ENUM_Type_IntPoint        );
        Reader.SetData( "Count"         , &Pt->Info.Count           , ENUM_Type_IntPoint        );

//		Reader.SetData( "MainColor"		, &Pt->Info.MainColor		, ENUM_Type_IntPoint        );
//		Reader.SetData( "OffColor"      , &Pt->Info.OffColor        , ENUM_Type_IntPoint        );
        Reader.SetData( "Durable"       , &Pt->Info.Durable         , ENUM_Type_IntPoint      );
        Reader.SetData( "ImageObjectID" , &Pt->Info.ImageObjectID   , ENUM_Type_IntPoint      );
        Reader.SetData( "Ability"		, Pt->Info.Ability			, ENUM_Type_BinaryData  , sizeof(Pt->Info.Ability)  );        
		Reader.SetData( "Mode"			, &Pt->Info.Mode			, ENUM_Type_IntPoint      );

		IsReady = true;
	}

	return &Reader;
}
//----------------------------------------------------------------------------------------------------------------
ReaderClass<DB_AbilityStruct>*  RoleDataEx::ReaderRD_Ability( )
{
	static  ReaderClass<DB_AbilityStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		char    Buf[256];
		DB_AbilityStruct* Pt = NULL;
        Reader.SetData( "DBID"          , &Pt->DBID                 , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
        Reader.SetData( "Job"           , &Pt->Job                  , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );

        Reader.SetData( "EXP"           , &Pt->Info.EXP             , ENUM_Type_IntPoint        );
        Reader.SetData( "TotalTpEXP"    , &Pt->Info.TotalTpExp      , ENUM_Type_IntPoint        );
		Reader.SetData( "TpEXP"         , &Pt->Info.TpExp           , ENUM_Type_IntPoint        );
		Reader.SetData( "DebtTP"        , &Pt->Info.DebtTP          , ENUM_Type_IntPoint        );
		Reader.SetData( "DebtExp"       , &Pt->Info.DebtExp         , ENUM_Type_IntPoint        );
		Reader.SetData( "AddTP"         , &Pt->Info.AddTp	        , ENUM_Type_IntPoint        );
		Reader.SetData( "AddExp"        , &Pt->Info.AddExp         , ENUM_Type_IntPoint        );

        Reader.SetData( "Level"         , &Pt->Info.Level           , ENUM_Type_IntPoint        );
        Reader.SetData( "Point"         , &Pt->Info.Point           , ENUM_Type_IntPoint        );
        Reader.SetData( "PlayTime"		, &Pt->Info.PlayTime		, ENUM_Type_IntPoint        );
        Reader.SetData( "STR"           , &Pt->Info.STR             , ENUM_Type_IntPoint        );
        Reader.SetData( "STA"           , &Pt->Info.STA             , ENUM_Type_IntPoint        );
        Reader.SetData( "MND"           , &Pt->Info.MND             , ENUM_Type_IntPoint        );
        Reader.SetData( "INT"           , &Pt->Info.INT             , ENUM_Type_IntPoint        );
        Reader.SetData( "AGI"           , &Pt->Info.AGI             , ENUM_Type_IntPoint        );

        for( int i = 0 ; i < _MAX_NormalSkill_COUNT_ ; i++ )
        {
            sprintf_s( Buf , sizeof(Buf) , "NormalSkill%d" , i+1 );
            Reader.SetData( Buf           , &Pt->Info.NormalSkill[i]             , ENUM_Type_FloatPoint        );
        }
		for( int i = 0 ; i < _MAX_SPSkill_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "SPSkill%d" , i+1 );
			Reader.SetData( Buf           , &Pt->Info.SPSkill[i]             , ENUM_Type_FloatPoint        );
		}

		IsReady = true;
	}      
	return &Reader;
}
//----------------------------------------------------------------------------------------------------------------

ReaderClass<DB_BaseFriendStruct>*  RoleDataEx::ReaderRD_BaseFriendStruct( )
{
	static  ReaderClass<DB_BaseFriendStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   		
		DB_BaseFriendStruct* Pt = NULL;
		Reader.SetData( "OwnerDBID"     , &Pt->OwnerDBID            	, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
		Reader.SetData( "FieldID"       , &Pt->FieldID              	, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
		Reader.SetData( "Type"			, &Pt->Type	                	, ENUM_Type_IntPoint       );

		Reader.SetData( "DBID"			, &Pt->Info.DBID                , ENUM_Type_IntPoint       );
		Reader.SetData( "Name"			,  Pt->Info.Name				, ENUM_Type_WCharString     , sizeof(Pt->Info.Name	));
		Reader.SetData( "Note"			,  Pt->Info.Note				, ENUM_Type_BinaryData		, sizeof(Pt->Info.Note	));
		Reader.SetData( "Relation"		, &Pt->Info.Relation            , ENUM_Type_IntPoint       );
		Reader.SetData( "Lv"			, &Pt->Info.Lv					, ENUM_Type_FloatPoint       );

		IsReady = true;
	}      
	return &Reader;
}

//----------------------------------------------------------------------------------------------------------------
ReaderClass<DB_MailItemStruct>*  RoleDataEx::ReaderRD_MailItem( )
{
	static  ReaderClass<DB_MailItemStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   

		DB_MailItemStruct* Pt = NULL;
		Reader.SetData( "MailBaseGUID"	, &Pt->MailBaseGUID				, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
		Reader.SetData( "OrgObjID"      , &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"		, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    , &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"		, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"		, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"		,  Pt->Item.Ability				, ENUM_Type_BinaryData  , sizeof(Pt->Item.Ability)  );        
		Reader.SetData( "ExValue"		, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"			, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"	, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);

		IsReady = true;
	}      
	return &Reader;
}

ReaderClass<DB_MailStruct>*  RoleDataEx::ReaderRD_MailBase( )
{
	static  ReaderClass<DB_MailStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{    
		DB_MailStruct* Pt = NULL;
		Reader.SetData( "GUID"          , &Pt->GUID								, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
//		Reader.SetData( "ItemGUID"      , &Pt->ItemGUID							, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );

		Reader.SetData( "BKMoney"		, &Pt->MailBase.Money					, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Select_Flag );
		Reader.SetData( "BKMoney_Account", &Pt->MailBase.Money_Account			, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Select_Flag );
		Reader.SetData( "BKMoney_Bonus"	, &Pt->MailBase.Money_Bonus				, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Select_Flag );

		Reader.SetData( "Money"			, &Pt->MailBase.Money					, ENUM_Type_IntPoint       );
		Reader.SetData( "Money_Account"	, &Pt->MailBase.Money_Account			, ENUM_Type_IntPoint       );
		Reader.SetData( "Money_Bonus"	, &Pt->MailBase.Money_Bonus				, ENUM_Type_IntPoint       );

		Reader.SetData( "IsSendMoney"	, &Pt->MailBase.IsSendMoney				, ENUM_Type_BitPoint       );
		Reader.SetData( "IsSystem"		, &Pt->MailBase.IsSystem				, ENUM_Type_BitPoint       );
		Reader.SetData( "IsRead"		, &Pt->MailBase.IsRead					, ENUM_Type_BitPoint       );
		Reader.SetData( "IsGift"		, &Pt->MailBase.IsGift					, ENUM_Type_BitPoint       );

		Reader.SetData( "AcDBID"		, &Pt->MailBase.AcDBID					, ENUM_Type_IntPoint       );
		Reader.SetData( "OwnerDBID"		, &Pt->OwnerDBID						, ENUM_Type_IntPoint       );
		Reader.SetData( "OrgSendDBID"	, &Pt->OrgSendDBID						, ENUM_Type_IntPoint       );
		Reader.SetData( "OrgSendName"	,  Pt->MailBase.OrgSendName.Begin()		, ENUM_Type_WCharString     , sizeof(Pt->MailBase.OrgSendName)	);
		Reader.SetData( "OrgTargetName"	,  Pt->MailBase.OrgTargetName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->MailBase.OrgTargetName) );
		Reader.SetData( "Title"			,  Pt->MailBase.Title.Begin()			, ENUM_Type_WCharString     , sizeof(Pt->MailBase.Title)			);
		Reader.SetData( "LiveTime"		, &Pt->MailBase.LiveTime				, ENUM_Type_IntPoint       );
		Reader.SetData( "Content"		,  Pt->Content.Begin()					, ENUM_Type_WCharString	   , sizeof(Pt->Content)  );
		Reader.SetData( "PaperType"		, &Pt->MailBase.PaperType				, ENUM_Type_IntPoint       );
		IsReady = true;
	}      
	return &Reader;
}
//----------------------------------------------------------------------------------------------------------------
ReaderClass<DB_BillBoardRoleInfoStruct>*	RoleDataEx::ReaderRD_BillBoard( )
{
	static  ReaderClass<DB_BillBoardRoleInfoStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{    
		DB_BillBoardRoleInfoStruct* Pt = NULL;

		Reader.SetData( "RoleName"			,  Pt->RoleName.Begin()					, ENUM_Type_WCharString	   , sizeof(Pt->RoleName)  );		
		Reader.SetData( "Rank_PKScore"		, &Pt->Rank_PKScore						, ENUM_Type_IntPoint       );
		Reader.SetData( "Rank_TitleCount"	, &Pt->Rank_Title						, ENUM_Type_IntPoint       );
		Reader.SetData( "Rank_Money"		, &Pt->Rank_Money						, ENUM_Type_IntPoint       );
		
		for( int i = 0 ; i < 8 ; i++ )
		{
			char Buf[256];
			sprintf_s( Buf , sizeof(Buf) , "Rank_Job%d" ,  i+ 1 );
			Reader.SetData( Buf				, &Pt->Rank_Job[i]						, ENUM_Type_IntPoint       );
		}

		for( int i = 0 ; i < 8 ; i++ )
		{
			char Buf[256];
			sprintf_s( Buf , sizeof(Buf) , "Job%dLv" ,  i+ 1 );
			Reader.SetData( Buf				, &Pt->JobLv[i]						, ENUM_Type_IntPoint       );
		}

		Reader.SetData( "IsAnonymous"		, &Pt->IsAnonymous						, ENUM_Type_BitPoint       );
		Reader.SetData( "DBID"				, &Pt->DBID								, ENUM_Type_IntPoint       );
		Reader.SetData( "Voc"				, &Pt->Voc								, ENUM_Type_IntPoint       );
		Reader.SetData( "Voc_Sub"			, &Pt->Voc_Sub							, ENUM_Type_IntPoint       );
//		Reader.SetData( "Lv"				, &Pt->Lv								, ENUM_Type_IntPoint       );
//		Reader.SetData( "Lv_Sub"			, &Pt->Lv_Sub							, ENUM_Type_IntPoint       );
		Reader.SetData( "Money"				, &Pt->Money							, ENUM_Type_IntPoint       );
		Reader.SetData( "TitleCount"		, &Pt->TitleCount						, ENUM_Type_IntPoint       );
		Reader.SetData( "PKScore"			, &Pt->PKScore							, ENUM_Type_IntPoint       );

		IsReady = true;
	}      
	return &Reader;
}

//----------------------------------------------------------------------------------------------------------------
/*
ReaderClass<DB_ACItemStruct>*  RoleDataEx::ReaderRD_ACItem( )
{
	static  ReaderClass<DB_ACItemStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_ACItemStruct* Pt = NULL;
		Reader.SetData( "GUID"          , &Pt->ACDIBD			, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
		Reader.SetData( "OrgObjID"      , &Pt->Item.OrgObjID	, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"		, &Pt->Item.Serial		, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    , &Pt->Item.CreateTime	, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"		, &Pt->Item.Count		, ENUM_Type_IntPoint       );
		Reader.SetData( "Coldown"		, &Pt->Item.Coldown		, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"		, &Pt->Item.Durable		, ENUM_Type_IntPoint       );
		Reader.SetData( "Inherent"      , &Pt->Item.Inherent	, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune1"			, &Pt->Item.Rune[0]		, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune2"			, &Pt->Item.Rune[1]		, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune3"		    , &Pt->Item.Rune[2]		, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune4"			, &Pt->Item.Rune[3]		, ENUM_Type_IntPoint       );
		Reader.SetData( "RuneVolume"    , &Pt->Item.RuneVolume	, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"			, &Pt->Item.Mode		, ENUM_Type_IntPoint       );
		IsReady = true;
	}      
	return &Reader;
}
*/
ReaderClass<DB_ACItemStruct>*  RoleDataEx::ReaderRD_ACBase( )
{
	static  ReaderClass<DB_ACItemStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_ACItemStruct* Pt = NULL;

		Reader.SetData( "GUID"          , &Pt->GUID					, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );
		Reader.SetData( "LiveTime"      , &Pt->LiveTime				, ENUM_Type_IntPoint       );
		Reader.SetData( "NowPrices"     , &Pt->NowPrices			, ENUM_Type_IntPoint       );
		Reader.SetData( "BuyOutPrices"  , &Pt->BuyOutPrices			, ENUM_Type_IntPoint       );
		Reader.SetData( "PricesType"	, &Pt->PricesType			, ENUM_Type_IntPoint       );
		Reader.SetData( "SellerDBID"	, &Pt->SellerDBID			, ENUM_Type_IntPoint       );
		Reader.SetData( "BuyerDBID"		, &Pt->BuyerDBID			, ENUM_Type_IntPoint       );
		Reader.SetData( "SellerName"	,  Pt->SellerName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->SellerName)	);
		Reader.SetData( "BuyerName"		,  Pt->BuyerName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->BuyerName)	);

		Reader.SetData( "ItemName"		,  Pt->ItemName.Begin()		, ENUM_Type_WCharString     , sizeof(Pt->ItemName)	);
		Reader.SetData( "Type1"     	, &Pt->ItemType[0]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Type2"     	, &Pt->ItemType[1]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Type3"     	, &Pt->ItemType[2]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "ItemLevel"		, &Pt->ItemLevel			, ENUM_Type_IntPoint       	);
		Reader.SetData( "EqWearType"	, &Pt->EQType._Skill		, ENUM_Type_IntPoint		);
		Reader.SetData( "Rare"			, &Pt->Rare					, ENUM_Type_IntPoint		);
		Reader.SetData( "SexType"		, &Pt->SexType._Sex			, ENUM_Type_IntPoint		);
		Reader.SetData( "RaceType"		, &Pt->RaceType._Race		, ENUM_Type_IntPoint		);
		Reader.SetData( "RuneVolume"	, &Pt->RuneVolume			, ENUM_Type_IntPoint		);        

		Reader.SetData( "OrgObjID"      , &Pt->Item.OrgObjID		, ENUM_Type_IntPoint       	);
		Reader.SetData( "Serial"		, &Pt->Item.Serial			, ENUM_Type_IntPoint       	);
		Reader.SetData( "CreateTime"    , &Pt->Item.CreateTime		, ENUM_Type_IntPoint       	);
		Reader.SetData( "[Count]"		, &Pt->Item.Count			, ENUM_Type_IntPoint       	);
//		Reader.SetData( "Coldown"		, &Pt->Item.Coldown			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Durable"		, &Pt->Item.Durable			, ENUM_Type_IntPoint       	);

		Reader.SetData( "Ability"		,  Pt->Item.Ability			, ENUM_Type_BinaryData  , sizeof(Pt->Item.Ability)  );        
		/*
		Reader.SetData( "Inherent"      , &Pt->Item.Inherent		, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune1"			, &Pt->Item.Rune[0]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune2"			, &Pt->Item.Rune[1]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune3"		    , &Pt->Item.Rune[2]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune4"			, &Pt->Item.Rune[3]			, ENUM_Type_IntPoint       	);
		*/
		Reader.SetData( "ExValue"		, &Pt->Item.ExValue			, ENUM_Type_IntPoint       	);
//		Reader.SetData( "MainColor"		, &Pt->Item.MainColor		, ENUM_Type_IntPoint        );
//		Reader.SetData( "OffColor"      , &Pt->Item.OffColor		, ENUM_Type_IntPoint        );
		Reader.SetData( "ImageObjectID"	, &Pt->Item.ImageObjectID	, ENUM_Type_IntPoint		);        

		Reader.SetData( "Mode"			, &Pt->Item.Mode			, ENUM_Type_IntPoint       	);
		Reader.SetData( "ImportAcItemGUID"	, &Pt->ImportAcItemGUID	, ENUM_Type_IntPoint       	);

		IsReady = true;
	}      
	return &Reader;
}

ReaderClass<DB_ACItemHistoryStruct>*	RoleDataEx::ReaderRD_ACHistory( )
{
	static  ReaderClass<DB_ACItemHistoryStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_ACItemHistoryStruct* Pt = NULL;
		Reader.SetData( "GUID"          , &Pt->GUID					, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );		
		Reader.SetData( "SellerName"	,  Pt->SellerName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->SellerName)	);
		Reader.SetData( "BuyerName"		,  Pt->BuyerName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->BuyerName)	);
		Reader.SetData( "DateTime"		, &Pt->Date					, ENUM_Type_IntPoint		);
		Reader.SetData( "Prices"		, &Pt->Prices				, ENUM_Type_IntPoint       	);
		Reader.SetData( "PricesType"	, &Pt->PricesType			, ENUM_Type_IntPoint       	);
		
		Reader.SetData( "OrgObjID"      , &Pt->Item.OrgObjID		, ENUM_Type_IntPoint       	);
		Reader.SetData( "Serial"		, &Pt->Item.Serial			, ENUM_Type_IntPoint       	);
		Reader.SetData( "CreateTime"    , &Pt->Item.CreateTime		, ENUM_Type_IntPoint       	);
		Reader.SetData( "[Count]"		, &Pt->Item.Count			, ENUM_Type_IntPoint       	);
//		Reader.SetData( "Coldown"		, &Pt->Item.Coldown			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Durable"		, &Pt->Item.Durable			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Ability"		,  Pt->Item.Ability			, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		/*
		Reader.SetData( "Inherent"      , &Pt->Item.Inherent		, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune1"			, &Pt->Item.Rune[0]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune2"			, &Pt->Item.Rune[1]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune3"		    , &Pt->Item.Rune[2]			, ENUM_Type_IntPoint       	);
		Reader.SetData( "Rune4"			, &Pt->Item.Rune[3]			, ENUM_Type_IntPoint       	);
		*/
		Reader.SetData( "ExValue"		, &Pt->Item.ExValue			, ENUM_Type_IntPoint       	);
//		Reader.SetData( "MainColor"		, &Pt->Item.MainColor		, ENUM_Type_IntPoint        );
//		Reader.SetData( "OffColor"      , &Pt->Item.OffColor		, ENUM_Type_IntPoint        );
		Reader.SetData( "ImageObjectID"	, &Pt->Item.ImageObjectID	, ENUM_Type_IntPoint		);
		Reader.SetData( "Mode"			, &Pt->Item.Mode			, ENUM_Type_IntPoint       	);

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<DB_NPC_MoveBaseStruct>*	RoleDataEx::ReaderRD_NPC_MoveBase( )
{
	static  ReaderClass<DB_NPC_MoveBaseStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_NPC_MoveBaseStruct* Pt = NULL;
		Reader.SetData( "NPCDBID"   		, &Pt->NPCDBID				, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		
		Reader.SetData( "IndexID"   		, &Pt->IndexID				, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		

		Reader.SetData( "ZoneID"			, &Pt->ZoneID				, ENUM_Type_IntPoint       	);
		Reader.SetData( "X"					, &Pt->Base.X				, ENUM_Type_FloatPoint      );
		Reader.SetData( "Y"					, &Pt->Base.Y				, ENUM_Type_FloatPoint      );
		Reader.SetData( "Z"					, &Pt->Base.Z				, ENUM_Type_FloatPoint      );
		Reader.SetData( "Dir"				, &Pt->Base.Dir				, ENUM_Type_FloatPoint      );
		Reader.SetData( "Range"				, &Pt->Base.Range			, ENUM_Type_FloatPoint      );
		Reader.SetData( "MoveType"			, &Pt->Base.MoveType		, ENUM_Type_IntPoint       	);
		Reader.SetData( "WaitTime_Base"		, &Pt->Base.WaitTime_Base	, ENUM_Type_IntPoint       	);
		Reader.SetData( "WaitTime_Rand"		, &Pt->Base.WaitTime_Rand	, ENUM_Type_IntPoint       	);
		Reader.SetData( "ActionType"		, &Pt->Base.ActionType		, ENUM_Type_IntPoint       	);
		Reader.SetData( "DirMode"			, &Pt->Base.DirMode			, ENUM_Type_IntPoint       	);
		Reader.SetData( "LuaFunc"			, Pt->Base.sLuaFunc.Begin()	, ENUM_Type_CharString     , sizeof(Pt->Base.sLuaFunc )	 );		

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildMemberStruct>*	RoleDataEx::ReaderRD_GuildMember( )
{
	static  ReaderClass<GuildMemberStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildMemberStruct* Pt = NULL;
		Reader.SetData( "GuildID"			, &Pt->GuildID				, ENUM_Type_IntPoint       	);
		Reader.SetData( "GuildRank"			, &Pt->Rank					, ENUM_Type_IntPoint       	);
		Reader.SetData( "GuildGroupID"		, &Pt->GroupID				, ENUM_Type_IntPoint       	);
		Reader.SetData( "GuildRankTime"		, &Pt->RankTime				, ENUM_Type_IntPoint       	);
		Reader.SetData( "DBID"   			, &Pt->MemberDBID			, ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );		
		Reader.SetData( "RoleName"			,  Pt->MemberName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->MemberName)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );		

		Reader.SetData( "GuildSelfNote"		,  Pt->SelfNote.Begin()		, ENUM_Type_WCharString     , sizeof(Pt->SelfNote) );		
		Reader.SetData( "GuildLeaderNote"	,  Pt->LeaderNote.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->LeaderNote) );		

		Reader.SetData( "Voc"           	, &Pt->Voc                  , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        
		Reader.SetData( "Voc_Sub"       	, &Pt->Voc_Sub              , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        
		Reader.SetData( "Sex"           	, &Pt->Sex                  , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        
		Reader.SetData( "LV"           		, &Pt->LV                   , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        
		Reader.SetData( "LV_Sub"       		, &Pt->LV_Sub               , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        
		Reader.SetData( "LogoutTime"       	, &Pt->LogoutTime           , ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag | Def_Disabled_Insert_Flag );        

		IsReady = true;
	}
	return &Reader;
}
ReaderClass<GuildBaseStruct>*	RoleDataEx::ReaderRD_GuildBase( )
{
	static  ReaderClass<GuildBaseStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildBaseStruct* Pt = NULL;
		Reader.SetData( "GUID"				, &Pt->GuildID				, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "LeaderDBID"		, &Pt->LeaderDBID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Medal"				, &Pt->Medal				, ENUM_Type_IntPoint       );

		Reader.SetData( "WarGuildID"		, &Pt->WarGuildID			, ENUM_Type_IntPoint       );
		Reader.SetData( "WarMyScore"		, &Pt->WarMyScore			, ENUM_Type_IntPoint       );
		Reader.SetData( "WarEnemyScore"		, &Pt->WarEnemyScore		, ENUM_Type_IntPoint       );
		Reader.SetData( "WarTime"			, &Pt->WarTime				, ENUM_Type_IntPoint       );
		Reader.SetData( "WarEnemyKillCount"	, &Pt->WarEnemyKillCount	, ENUM_Type_IntPoint       );
		Reader.SetData( "WarMyKillCount"	, &Pt->WarMyKillCount		, ENUM_Type_IntPoint       );
		

		Reader.SetData( "WarWinCount"		, &Pt->WarWinCount			, ENUM_Type_IntPoint       );
		Reader.SetData( "WarEvenCount"		, &Pt->WarEvenCount			, ENUM_Type_IntPoint       );
		Reader.SetData( "WarLostCount"		, &Pt->WarLostCount			, ENUM_Type_IntPoint       );
		Reader.SetData( "WarDeclareTime"	, &Pt->WarDeclareTime		, ENUM_Type_IntPoint       );


		Reader.SetData( "GuildType"			, &Pt->GuildType			, ENUM_Type_IntPoint       );
		Reader.SetData( "MaxMemberCount"	, &Pt->MaxMemberCount		, ENUM_Type_IntPoint       );
//		Reader.SetData( "Score"				, &Pt->Score				, ENUM_Type_IntPoint       );

		for( int i = 0 ; i < 7 ; i++ )
		{
			char Buf[256];
			sprintf_s( Buf , sizeof(Buf) ,"GuildResource%d" , i+1 );
			Reader.SetData( Buf				, &Pt->Resource._Value[i]	, ENUM_Type_IntPoint       );
		}

		Reader.SetData( "GuildName"			,  Pt->GuildName.Begin()	, ENUM_Type_WCharString    , sizeof(Pt->GuildName)		);		
		Reader.SetData( "LeaderName"		,  Pt->LeaderName.Begin()	, ENUM_Type_WCharString    , sizeof(Pt->LeaderName)		);		
		Reader.SetData( "Note"				,  Pt->Note.Begin()			, ENUM_Type_WCharString    , sizeof(Pt->Note)			);		
		Reader.SetData( "Introduce"			,  Pt->Introduce.Begin()	, ENUM_Type_WCharString    , sizeof(Pt->Introduce)		);		
		Reader.SetData( "Flag"				, &Pt->Flag					, ENUM_Type_BinaryData	   , sizeof(Pt->Flag)  );        
		Reader.SetData( "GuildFlag"			, &Pt->GuildFlag			, ENUM_Type_BinaryData	   , sizeof(Pt->GuildFlag)  );        
		Reader.SetData( "RankCount"			, &Pt->RankCount			, ENUM_Type_IntPoint       );
		for( int i = 0 ; i < EM_GuildRank_Count ; i++ )
		{
			char Buf[256];
			sprintf_s( Buf , sizeof(Buf) ,"RankAbility%d" , i+1 );
			Reader.SetData( Buf				, &Pt->Rank[i].Setting.Type		, ENUM_Type_IntPoint       );
			sprintf_s( Buf , sizeof(Buf) ,"RankName%d" , i+1 );
			Reader.SetData( Buf				,  Pt->Rank[i].RankName.Begin() , ENUM_Type_WCharString     , sizeof( Pt->Rank[i].RankName )	);		
		}

		for( int i = 0 ; i < _MAX_GUILD_GROUP_COUNT_ ; i++ )
		{
			char Buf[256];
			sprintf_s( Buf , sizeof(Buf) ,"GroupName%d" , i+1 );
			Reader.SetData( Buf		, Pt->Group[i].Begin()			, ENUM_Type_WCharString     , sizeof(  Pt->Group[i] )	);		 
		}

		Reader.SetData( "Lv"				, &Pt->Level				, ENUM_Type_IntPoint       );


		Reader.SetData( "HouesWar_WinCount"		, &Pt->HousesWar.WinCount		, ENUM_Type_IntPoint       );
		Reader.SetData( "HouesWar_EvenCount"	, &Pt->HousesWar.EvenCount		, ENUM_Type_IntPoint       );
		Reader.SetData( "HouesWar_LostCount"	, &Pt->HousesWar.LostCount		, ENUM_Type_IntPoint       );
		Reader.SetData( "HouesWar_Score"		, &Pt->HousesWar.Score			, ENUM_Type_IntPoint       );
		Reader.SetData( "HouesWar_NextWarTime"	, &Pt->HousesWar.NextWarTime	, ENUM_Type_IntPoint       );

		IsReady = true;
	}
	return &Reader;

}

ReaderClass<GuildBoardStruct>*	RoleDataEx::ReaderRD_GuildBoard( )
{
	static  ReaderClass<GuildBoardStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildBoardStruct* Pt = NULL;
		Reader.SetData( "GUID"				, &Pt->GUID					, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "GuildID"			, &Pt->GuildID				, ENUM_Type_IntPoint       );		

		Reader.SetData( "Type"				, &Pt->Type._Type			, ENUM_Type_IntPoint       );
		Reader.SetData( "PostTime"			, &Pt->Time					, ENUM_Type_IntPoint       );

		Reader.SetData( "Title"				,  Pt->Title.Begin()		, ENUM_Type_WCharString      , sizeof(Pt->Title)		);		
		Reader.SetData( "Message"			,  Pt->Message.Begin()		, ENUM_Type_WCharString      , sizeof(Pt->Message)		);		
		Reader.SetData( "PostName"			,  Pt->PlayerName.Begin()	, ENUM_Type_WCharString		, sizeof(Pt->PlayerName)		);		

		IsReady = true;
	}
	return &Reader;
}


ReaderClass<HouseBaseDBStruct>*	RoleDataEx::ReaderRD_HouseBase( )
{
	static  ReaderClass<HouseBaseDBStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		HouseBaseDBStruct* Pt = NULL;

		Reader.SetData( "HouseDBID"				, &Pt->HouseDBID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		

		Reader.SetData( "MaxItemCount"			, &Pt->MaxItemCount			, ENUM_Type_IntPoint       );
		Reader.SetData( "EnergyPoint"			, &Pt->EnergyPoint			, ENUM_Type_IntPoint       );
		Reader.SetData( "HouseType"				, &Pt->HouseType			, ENUM_Type_IntPoint       );
		Reader.SetData( "LastRantelTime"		, &Pt->LastRantelTime		, ENUM_Type_IntPoint       );

		Reader.SetData( "Password"				,  Pt->Password.Begin()		, ENUM_Type_CharString      , sizeof(Pt->Password)		);		
//		Reader.SetData( "Account_ID"			,  Pt->AccountID.Begin()	, ENUM_Type_CharString      , sizeof(Pt->AccountID)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "OwnerDBID"				, &Pt->OwnerDBID			, ENUM_Type_IntPoint       );
		Reader.SetData( "ShopFunction"			, &Pt->ShopFunction			, ENUM_Type_BinaryData		, sizeof(Pt->ShopFunction)  );      
		Reader.SetData( "HouseName"				,  Pt->HouseName.Begin()	, ENUM_Type_WCharString     , sizeof(Pt->HouseName)		);		
		Reader.SetData( "ClientData"			,  Pt->ClientData			, ENUM_Type_BinaryData		, sizeof(Pt->ClientData)	);		
		Reader.SetData( "ItemLog"				,  Pt->ItemLog				, ENUM_Type_BinaryData		, sizeof(Pt->ItemLog)		);		
		Reader.SetData( "UnCheckItemLogCount"	, &Pt->UnCheckItemLogCount	, ENUM_Type_IntPoint		);
		Reader.SetData( "ItemLogPos"			, &Pt->ItemLogPos			, ENUM_Type_IntPoint		);
//		Reader.SetData( "Servant"				, &Pt->Servant				, ENUM_Type_BinaryData		, sizeof( Pt->Servant )		);
		Reader.SetData( "LastServantProcTime"	, &Pt->LastServantProcTime	, ENUM_Type_IntPoint       );

		for( int i = 0 ; i < MAX_SERVANT_COUNT ; i++ )
		{
			char Buf[512];
			sprintf( Buf , "Servant%d" , i+1 );
			Reader.SetData( Buf	, &Pt->Servant[i] , ENUM_Type_BinaryData , sizeof(HouseServantStruct)       );
		}

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<HouseItemDBStruct>*	RoleDataEx::ReaderRD_HouseItem( )
{
	static  ReaderClass<HouseItemDBStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		HouseItemDBStruct* Pt = NULL;

		Reader.SetData( "ItemDBID"			, &Pt->ItemDBID					, ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		
		Reader.SetData( "HouseDBID"			, &Pt->HouseDBID				, ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		
		Reader.SetData( "ParentItemDBID"	, &Pt->ParentItemDBID			, ENUM_Type_IntPoint       );		
		Reader.SetData( "HousePos"			, &Pt->Pos						, ENUM_Type_IntPoint       );		

//		Reader.SetData( "ItemPos"	      	, &Pt->Item.Pos					, ENUM_Type_IntPoint       );
		Reader.SetData( "OrgObjID"      	, &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"			, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    	, &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"			, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"			, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"			,  Pt->Item.Ability				, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		/*
		Reader.SetData( "Inherent"      	, &Pt->Item.Inherent			, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune1"				, &Pt->Item.Rune[0]				, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune2"				, &Pt->Item.Rune[1]				, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune3"		    	, &Pt->Item.Rune[2]				, ENUM_Type_IntPoint       );
		Reader.SetData( "Rune4"				, &Pt->Item.Rune[3]				, ENUM_Type_IntPoint       );
		*/
		Reader.SetData( "ExValue"			, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"				, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
//		Reader.SetData( "MainColor"			, &Pt->Item.MainColor			, ENUM_Type_IntPoint       );
//		Reader.SetData( "OffColor"      	, &Pt->Item.OffColor			, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"		, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);        
		Reader.SetData( "Layout"			, &Pt->Layout					, ENUM_Type_BinaryData  , sizeof(Pt->Layout)  ); 
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<AccountBagItemFieldDBStruct>*	RoleDataEx::ReaderRD_AccountBag( )
{
	static  ReaderClass<AccountBagItemFieldDBStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		AccountBagItemFieldDBStruct* Pt = NULL;

		Reader.SetData( "GUID"				, &Pt->ItemDBID					, ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		
		Reader.SetData( "OrgObjID"      	, &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"			, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    	, &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"			, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"			, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"			,  Pt->Item.Ability				, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		Reader.SetData( "ExValue"			, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"				, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"		, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);        
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<WebShopBagItemFieldDBStruct>*	RoleDataEx::ReaderRD_WebShopBag( )
{
	static  ReaderClass<WebShopBagItemFieldDBStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		WebShopBagItemFieldDBStruct* Pt = NULL;

		Reader.SetData( "GUID"				, &Pt->ItemDBID					, ENUM_Type_IntPoint       , 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag );		
		Reader.SetData( "OrgObjID"      	, &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"			, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    	, &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"			, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"			, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"			,  Pt->Item.Ability				, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		Reader.SetData( "ExValue"			, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"				, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"		, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);        
		Reader.SetData( "Message"			,  Pt->Message					, ENUM_Type_WCharString		, sizeof( Pt->Message )		);        
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<DB_DepartmentStoreBaseInfoStruct>*	RoleDataEx::ReaderRD_DepartmentStoreItem( )
{
	static  ReaderClass<DB_DepartmentStoreBaseInfoStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		char	Buf[256];
		DB_DepartmentStoreBaseInfoStruct* Pt = NULL;

		Reader.SetData( "GUID"					, &Pt->Item.GUID						, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "NeedMemberID"			, &Pt->Item.NeedMemberID				, ENUM_Type_IntPoint    );		
		Reader.SetData( "SortNumber"			, &Pt->Item.SortNumber					, ENUM_Type_IntPoint    );		
		Reader.SetData( "SellType"				, &Pt->Item.SellType[0]					, ENUM_Type_IntPoint    );		
		Reader.SetData( "SellType1"				, &Pt->Item.SellType[1]					, ENUM_Type_IntPoint    );		
		Reader.SetData( "SellType2"				, &Pt->Item.SellType[2]					, ENUM_Type_IntPoint    );		
		Reader.SetData( "Item_DisplayerObjID"	, &Pt->Item.Item.OrgObjID				, ENUM_Type_IntPoint    );		
       Reader.SetData( "Item_Name"				,  Pt->Item.ItemName				    , ENUM_Type_WCharStringBase     , sizeof(Pt->Item.ItemName)	, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag);
		Reader.SetData( "Item_Note"				,  Pt->Item.Note					    , ENUM_Type_WCharStringBase     , sizeof(Pt->Item.Note)		, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag);


		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "Item_OrgObjID%d" , i+1 );
			Reader.SetData( Buf		, &Pt->ItemIDList[i]		, ENUM_Type_IntPoint    );
			sprintf_s( Buf , sizeof(Buf) , "Item_Count%d" , i+1 );
			Reader.SetData( Buf		, &Pt->ItemCountList[i]		, ENUM_Type_IntPoint    );
		}

		Reader.SetData( "Sell_BeginTime"		, &Pt->Item.Sell.BeginTime			, ENUM_Type_SmallDateTime	);
		Reader.SetData( "Sell_EndTime"			, &Pt->Item.Sell.EndTime				, ENUM_Type_SmallDateTime	);
		Reader.SetData( "Sell_Count"			, &Pt->Item.Sell.OrgCount			, ENUM_Type_IntPoint    );
		Reader.SetData( "Sell_MaxCount"			, &Pt->Item.Sell.MaxCount			, ENUM_Type_IntPoint    );
		Reader.SetData( "Sell_Cost"      		, &Pt->Item.Sell.Cost				, ENUM_Type_IntPoint    );
		Reader.SetData( "Sell_Cost_Bonus"  		, &Pt->Item.Sell.Cost_Bonus			, ENUM_Type_IntPoint    );
		Reader.SetData( "Sell_Cost_Free"  		, &Pt->Item.Sell.Cost_Free			, ENUM_Type_IntPoint    );
		Reader.SetData( "Sell_Get_Bonus"  		, &Pt->Item.Sell.Get_Bonus			, ENUM_Type_IntPoint    );
		Reader.SetData( "Icon"  				, &Pt->Item.Sell.Icon				, ENUM_Type_IntPoint    );

		Reader.SetData( "Gamble_Count"  		, &Pt->Item.Gamble.Count			, ENUM_Type_ShortPoint    );

		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "Gamble_Rate%d" , i+1 );
			Reader.SetData( Buf		, &Pt->Item.Gamble.Rate[i]		, ENUM_Type_ShortPoint    );		
		}

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<ImportBoardBaseStruct>*	RoleDataEx::ReaderRD_ImportBoardBase( )
{
	static  ReaderClass<ImportBoardBaseStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		ImportBoardBaseStruct* Pt = NULL;
		Reader.SetData( "UpdateTime"   		, &Pt->UpdateTime			, ENUM_Type_SmallDateTime   );		
		Reader.SetData( "SortNumber"   		, &Pt->SortNumber			, ENUM_Type_IntPoint        );		

		Reader.SetData( "Title"				, &Pt->Title				, ENUM_Type_WCharString		, sizeof(Pt->Title)       	);
		Reader.SetData( "Content"			, &Pt->Content				, ENUM_Type_WCharString		, sizeof(Pt->Content)      	);
		
		Reader.SetData( "IsHot"				, &Pt->IsHot				, ENUM_Type_BitPoint        );
		Reader.SetData( "IsRed"				, &Pt->IsRed				, ENUM_Type_BitPoint        );
		Reader.SetData( "BeginTime"   		, &Pt->BeginTime			, ENUM_Type_SmallDateTime   );		
		Reader.SetData( "EndTime"   		, &Pt->EndTime				, ENUM_Type_SmallDateTime   );		

		for( int i = 0 ; i < 5 ; i++ )
		{
			char Buf[ 256 ];
			sprintf_s( Buf , sizeof(Buf) , "Item%d" , i + 1);
			Reader.SetData( Buf   		, &Pt->Item[i]					, ENUM_Type_IntPoint   );		
			sprintf_s( Buf , sizeof(Buf) , "ItemCount%d" , i + 1);
			Reader.SetData( Buf   		, &Pt->ItemCount[i]				, ENUM_Type_IntPoint   );		
		}
		Reader.SetData( "Money"   			, &Pt->Money				, ENUM_Type_IntPoint        );		
		Reader.SetData( "Money_Account"   	, &Pt->Money_Account		, ENUM_Type_IntPoint        );		
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildHousesInfoStruct>*	RoleDataEx::ReaderRD_GuildHouseInfo( )
{
	static  ReaderClass<GuildHousesInfoStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHousesInfoStruct* Pt = NULL;
		Reader.SetData( "GuildID"			, &Pt->GuildID				, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "ItemMaxPageCount"	, &Pt->ItemMaxPageCount		, ENUM_Type_IntPoint    );
		Reader.SetData( "FurnitureMaxCount"	, &Pt->FurnitureMaxCount	, ENUM_Type_IntPoint    );
		Reader.SetData( "LastCalRentTime"	, &Pt->LastCalRentTime		, ENUM_Type_IntPoint		, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag);
		Reader.SetData( "GuildStyle"		, &Pt->GuildStyle			, ENUM_Type_IntPoint    );
		Reader.SetData( "GuildStyleRight"	, &Pt->GuildStyleRight		, ENUM_Type_IntPoint    );
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildHouseBuildingInfoStruct>*	RoleDataEx::ReaderRD_GuildHouseBuildingInfo( )
{
	static  ReaderClass<GuildHouseBuildingInfoStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHouseBuildingInfoStruct* Pt = NULL;
		Reader.SetData( "GuildID"			, &Pt->GuildID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "BuildingDBID"		, &Pt->BuildingDBID		, ENUM_Type_IntPoint    );
		Reader.SetData( "ParentDBID"		, &Pt->ParentDBID		, ENUM_Type_IntPoint    );
		Reader.SetData( "BuildingID"		, &Pt->BuildingID		, ENUM_Type_IntPoint    );
		Reader.SetData( "Dir"				, &Pt->Dir				, ENUM_Type_FloatPoint    );
		Reader.SetData( "PointStr"			, &Pt->PointStr			, ENUM_Type_CharString		, sizeof(Pt->PointStr)  );      
		Reader.SetData( "Value"				, &Pt->Value			, ENUM_Type_BinaryData		, sizeof(Pt->Value)  );      
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildHouseItemStruct>*	RoleDataEx::ReaderRD_GuildHouseItem( )
{
	static  ReaderClass<GuildHouseItemStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHouseItemStruct* Pt = NULL;
		Reader.SetData( "GuildID"			, &Pt->GuildID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "ItemDBID"			, &Pt->ItemDBID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "PageID"			, &Pt->PageID			, ENUM_Type_IntPoint    );
		Reader.SetData( "PosID"				, &Pt->PosID			, ENUM_Type_IntPoint    );

		Reader.SetData( "OrgObjID"      	, &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"			, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    	, &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"			, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"			, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"			,  Pt->Item.Ability				, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		Reader.SetData( "ExValue"			, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"				, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"		, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);        

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildHouseFurnitureItemStruct>*	RoleDataEx::ReaderRD_GuildHouseFurnitureItem( )
{
	static  ReaderClass<GuildHouseFurnitureItemStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHouseFurnitureItemStruct* Pt = NULL;
		Reader.SetData( "GuildID"			, &Pt->GuildID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "ItemDBID"			, &Pt->ItemDBID			, ENUM_Type_IntPoint       	, 0						, ENUM_Indirect_Address ,  Def_Disabled_Update_Flag  );		
		Reader.SetData( "Pos"				, &Pt->Pos				, ENUM_Type_IntPoint    );

		Reader.SetData( "OrgObjID"      	, &Pt->Item.OrgObjID			, ENUM_Type_IntPoint       );
		Reader.SetData( "Serial"			, &Pt->Item.Serial				, ENUM_Type_IntPoint       );
		Reader.SetData( "CreateTime"    	, &Pt->Item.CreateTime			, ENUM_Type_IntPoint       );
		Reader.SetData( "[Count]"			, &Pt->Item.Count				, ENUM_Type_IntPoint       );
		Reader.SetData( "Durable"			, &Pt->Item.Durable				, ENUM_Type_IntPoint       );
		Reader.SetData( "Ability"			,  Pt->Item.Ability				, ENUM_Type_BinaryData		, sizeof(Pt->Item.Ability)  );        
		Reader.SetData( "ExValue"			, &Pt->Item.ExValue				, ENUM_Type_IntPoint       );
		Reader.SetData( "Mode"				, &Pt->Item.Mode				, ENUM_Type_IntPoint       );
		Reader.SetData( "ImageObjectID"		, &Pt->Item.ImageObjectID		, ENUM_Type_IntPoint		);        
		Reader.SetData( "Layout"			, &Pt->Layout					, ENUM_Type_BinaryData  , sizeof(Pt->Layout)  ); 
		Reader.SetData( "OwnerDBID"      	, &Pt->OwnerDBID				, ENUM_Type_IntPoint       );

		IsReady = true;
	}
	return &Reader;
}

ReaderClass<OfflineMessageDBStruct>*			RoleDataEx::ReaderRD_OfflineMessage()
{
	static  ReaderClass<OfflineMessageDBStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		OfflineMessageDBStruct* Pt = NULL;

		Reader.SetData( "Time"				, &Pt->Time						, ENUM_Type_SmallDateTime    );		
		Reader.SetData( "Type"				, &Pt->Type						, ENUM_Type_IntPoint         );		
		Reader.SetData( "ToPlayerDBID"		, &Pt->ToPlayerDBID				, ENUM_Type_IntPoint         );		
		Reader.SetData( "FromPlayerDBID"	, &Pt->FromPlayerDBID			, ENUM_Type_IntPoint         );		
		Reader.SetData( "ManageLv"			, &Pt->ManageLv					, ENUM_Type_IntPoint	    );		
		
		Reader.SetData( "ToPlayerName"		,  Pt->ToName.Begin()			, ENUM_Type_WCharString      , sizeof(Pt->ToName)		);		
		Reader.SetData( "FromPlayerName"	,  Pt->FromName.Begin()			, ENUM_Type_WCharString      , sizeof(Pt->FromName)		);		
		Reader.SetData( "Message"			,  Pt->Content.Begin()			, ENUM_Type_WCharString      , sizeof(Pt->Content)		);		

		IsReady = true;
	}
	return &Reader;
}


ReaderClass<GuildHouseWarInfoStruct>*			RoleDataEx::ReaderRD_GuildHouseWarInfo()
{
	static  ReaderClass<GuildHouseWarInfoStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHouseWarInfoStruct* Pt = NULL;

//		Reader.SetData( "FightTime"			, &Pt->FightTime			, ENUM_Type_SmallDateTime    );		
		Reader.SetData( "GuildID"			, &Pt->GuildID				, ENUM_Type_IntPoint         );		
		Reader.SetData( "Score"				, &Pt->Score				, ENUM_Type_IntPoint         );		
		Reader.SetData( "EnemyGuildID"		, &Pt->EnemyGuildID			, ENUM_Type_IntPoint         );		
		Reader.SetData( "State"				, &Pt->State				, ENUM_Type_IntPoint		 );				
		Reader.SetData( "GuildName"			,  Pt->GuildName.Begin()	, ENUM_Type_WCharString		 , sizeof( Pt->GuildName ) );		
		Reader.SetData( "ZoneGroupID"		, &Pt->ZoneGroupID			, ENUM_Type_IntPoint		 );		
		IsReady = true;
	}
	return &Reader;
}

ReaderClass<GuildHouseWarHistoryStruct>*			RoleDataEx::ReaderRD_GuildHouseWarHistory()
{
	static  ReaderClass<GuildHouseWarHistoryStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		GuildHouseWarHistoryStruct* Pt = NULL;

		Reader.SetData( "GuildID"			, &Pt->GuildID					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "TargetGuildID"		, &Pt->TargetGuildID			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "EndFightTime"		, &Pt->EndFightTime				, ENUM_Type_SmallDateTime	 );		
		Reader.SetData( "Result"			, &Pt->Result					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "GuildScore"		, &Pt->GuildScore				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "TargetGuildScore"	, &Pt->TargetGuildScore			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "TargetGuildName"	, Pt->TargetGuildName.Begin()	, ENUM_Type_WCharString		 , sizeof( Pt->TargetGuildName )		 );		

		IsReady = true;
	}
	return &Reader;
}

int	RoleDataEx::RareAddLv( int Rare )
{
	if( (unsigned)Rare >= 10 )
		return 0;
	return AddLv_byRare[ Rare ];
}

ReaderClass<ReserverRoleStruct>*			RoleDataEx::ReaderRD_ReserveRole()
{
	static  ReaderClass<ReserverRoleStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		ReserverRoleStruct* Pt = NULL;

		Reader.SetData( "RoleName"			, Pt->RoleName.Begin()		, ENUM_Type_WCharString		, sizeof( Pt->RoleName )		 );		

		Reader.SetData( "IsAutoCreate"		, &Pt->IsAutoCreate			, ENUM_Type_BitPoint		 );		

		Reader.SetData( "Sex"				, &Pt->Sex					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Race"				, &Pt->Race					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Job"				, &Pt->Job					, ENUM_Type_IntPoint		 );		
//		Reader.SetData( "GiftItemID"		, &Pt->GiftItemID			, ENUM_Type_IntPoint		 );		
		
		Reader.SetData( "BoneScale"			, &Pt->Look.BoneScale		, ENUM_Type_BinaryData		, sizeof( Pt->Look.BoneScale )	 );		
		Reader.SetData( "FaceID"			, &Pt->Look.FaceID			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "HairID"			, &Pt->Look.HairID			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "HairColor"			, &Pt->Look.HairColor		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "BodyColor"			, &Pt->Look.BodyColor		, ENUM_Type_IntPoint		 );		

		IsReady = true;
	}
	return &Reader;
}


ReaderClass<DB_CultivatePetStruct>*			RoleDataEx::ReaderRD_CultivatePetStruct()
{
	static  ReaderClass<DB_CultivatePetStruct> Reader;
	static  bool    IsReady = false;
	if( IsReady == false )
	{   
		DB_CultivatePetStruct* Pt = NULL;

		Reader.SetData( "PlayerDBID"		, &Pt->PlayerDBID				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Pos"				, &Pt->Pos						, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Name"				, Pt->Info.Name.Begin()			, ENUM_Type_WCharString		, sizeof( Pt->Info.Name )		 );		
		Reader.SetData( "ItemOrgID"			, &Pt->Info.ItemOrgID			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "CreateTime"		, &Pt->Info.CreateTime			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "PetOrgID"			, &Pt->Info.PetOrgID			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Lv"				, &Pt->Info.Lv					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "PetType"			, &Pt->Info.PetType				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "EventColdown"		, &Pt->Info.EventColdown		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "EventType"			, &Pt->Info.EventType			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "LifeSkillTablePos"	, &Pt->Info.LifeSkillTablePos	, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Exp"				, &Pt->Info.Exp					, ENUM_Type_IntPoint		 );		
		Reader.SetData( "SkillPoint"		, &Pt->Info.SkillPoint			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "TotalSkillPoint"	, &Pt->Info.TotalSkillPoint		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Loyal"				, &Pt->Info.Loyal				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Hunger"			, &Pt->Info.Hunger				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Talent"			, &Pt->Info.Talent				, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "Spirit"			, &Pt->Info.Spirit				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "Mode"				, &Pt->Info.Mode				, ENUM_Type_IntPoint		 );		
		Reader.SetData( "STR"				, &Pt->Info.STR					, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "STA"				, &Pt->Info.STA					, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "AGI"				, &Pt->Info.AGI					, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "INT"				, &Pt->Info.INT					, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "MND"				, &Pt->Info.MND					, ENUM_Type_FloatPoint		 );		
		Reader.SetData( "Property"			, &Pt->Info.Property			, ENUM_Type_IntPoint		 );		
		Reader.SetData( "TrainCount"		, &Pt->Info.TrainCount			, ENUM_Type_IntPoint		 );		

		Reader.SetData( "DayMergeCount"		, &Pt->Info.DayMergeCount		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "LifeSkill1"		, &Pt->Info.LifeSkill[0]		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "LifeSkill2"		, &Pt->Info.LifeSkill[1]		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "LifeSkill3"		, &Pt->Info.LifeSkill[2]		, ENUM_Type_IntPoint		 );		
		Reader.SetData( "LifeSkill4"		, &Pt->Info.LifeSkill[3]		, ENUM_Type_IntPoint		 );		

		Reader.SetData( "Magic"				, &Pt->Info.Magic				, ENUM_Type_BinaryData		, sizeof( Pt->Info.Magic )	 );		
		IsReady = true;
	}
	return &Reader;
}