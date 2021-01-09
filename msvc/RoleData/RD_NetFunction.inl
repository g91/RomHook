//RoleDataEx 直接使用到 NetWaker的部份
#ifdef _LOCAL_SERVER_

    void    Net_Mir_SetNumber( RoleValueName_ENUM ValueID , float Value );
	void    Msg( const char* Str );
	void    Msg_Utf8( const char* Str );
    void    Msg( const wchar_t* Str );
    void    Tell( const char* name , const char* Str );
    void    Say( const char* Str );
    //--------------------------------------------------------------------------------------------
    //戰鬥資訊處裡
    //--------------------------------------------------------------------------------------------
    void    Net_AddHP( int DHp );
    void    Net_AddMP( int DMp );
    void    Net_AddMagBuf( int MagicID , int Time  );
    
    //--------------------------------------------------------------------------------------------
    //Item
    //--------------------------------------------------------------------------------------------
    void    Net_ItemInBuffer( ItemFieldStruct& Item );
    void    Net_FixMoney( );
    void    Net_FixItemInfo_Body(  int Pos );
    void    Net_FixItemInfo_Bank(  int Pos );
    void    Net_FixItemInfo_EQ  (  int Pos );
    void    Net_FixItemInfo     (  int Pos , int Type );
	void	Net_FixKeyItemFlag	( int KeyItemID , bool Value );
	void	Net_FixTitleFlag	( int TitleObjID , bool Value );
	void	Net_FixCardFlag		( int TitleObjID , bool Value );
    //--------------------------------------------------------------------------------------------
    //RoleValue
    //--------------------------------------------------------------------------------------------
    void    Net_FixRoleValue( RoleValueName_ENUM	ValueName , double Value );

    //--------------------------------------------------------------------------------------------
    //Fix Look Eq
    //--------------------------------------------------------------------------------------------
    void    Net_FixLookEQ( );

    //--------------------------------------------------------------------------------------------
    //魔法
    //--------------------------------------------------------------------------------------------
    void    Net_ClearAssistMagic( int MagicID , int BuffOwnerID );
	void    Net_FixAssistMagicTime( int MagicID , int Time , int BuffOwnerID );
    //--------------------------------------------------------------------------------------------
    //其他Server有的功能
    //--------------------------------------------------------------------------------------------
    void    FixAttackMode( );
	void	Net_SendRangeAttackMode( bool Mode );
    //--------------------------------------------------------------------------------------------
    //其他Server有的功能
    //--------------------------------------------------------------------------------------------
    void    Net_MoveSpeed();

    //--------------------------------------------------------------------------------------------
    //通知週圍升級
    //--------------------------------------------------------------------------------------------
    void    Net_NotifyLvUp();
	//--------------------------------------------------------------------------------------------
	//通知週角色改職業或升級
	//--------------------------------------------------------------------------------------------
    void    Net_ChangeRoleInfo();
    //--------------------------------------------------------------------------------------------
    //通知週圍HPMPSP
    //--------------------------------------------------------------------------------------------
    void    Net_MaxHPMaxMPMaxSP();
    void    Net_HPMPSP();

    //儲存資料
    void    Net_SavePlayer( int Start , int Size , int SaveTime );
	//--------------------------------------------------------------------------------------------
	//通知Chat好有名單改變
	//--------------------------------------------------------------------------------------------
//	void	Net_FriendList_ModifyInfo();
	//--------------------------------------------------------------------------------------------
	//通知週圍某角色 魔法盾資訊
	void	Net_MagicShieldInfoRange( int AttackGUID , int UnAttackGUID , int AttackMagicID , int ShieldMagicID , int AbsobDamage );
	//--------------------------------------------------------------------------------------------
	//通知周圍某npc  要攻擊的目標
	void	Net_NpcAttackTarget();
	//--------------------------------------------------------------------------------------------
	//要求NPC移到某一點
	void	Net_MoveObj( );
	void	Net_SendRangeMove( ClientMoveTypeENUM Type  );
	//--------------------------------------------------------------------------------------------
	//送遊戲事件訊息
	void	Net_GameMsgEvent( GameMessageEventENUM Event );
	//送物件刪除的訊息給Client
	void	Net_SC_DelItemMsg( ItemFieldStruct& Item );
	//--------------------------------------------------------------------------------------------
	//Log處理
	void	Log_ItemTrade	( RoleDataEx* FromRole , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note );
	void	Log_ItemTrade	( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note );
	void	Log_ItemDestroy	( ActionTypeENUM Type , ItemFieldStruct& Item , int ItemCount , const char* Note );
	void	Log_Money		( RoleDataEx* FromRole , ActionTypeENUM Type , int Money );
	void	Log_Money_Account( RoleDataEx* FromRole , ActionTypeENUM Type , int Money );
	void	Log_Money		( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , int Money );
	void	Log_Money_Account( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , int Money );
	void	Log_Money_Bonus	(  RoleDataEx* FromRole , ActionTypeENUM Type , int Money );
	void	Log_DepartmentStore( ItemFieldStruct& Item , ActionTypeENUM Type , int Count , int Cost , int Cost_Bonus , int Cost_Free , int PlayerDBID );

	void	Log_PlayerActionLog( );
	void	Log_Level		( );
	void	Log_Dead		( RoleDataEx* Killer );
	void	Log_AddExp		( int Log );
	void	Log_SkillLv		( int SkillType , int SkillValue );
	//--------------------------------------------------------------------------------------------
	//通知角色基本資料有改變
	void	Net_SendChat_ChangeRoleInfo( );

	//--------------------------------------------------------------------------------------------
	//通知gm tools 角色資料有修正
	void	Net_SendGM_ObjInfo( );
	   //NetSrv_GMTools::S_ObjInfo( DF_NO_LOCALID , Owner );

	//角色特效通知
	void	Net_SendRangeSpecialEfficacy( SpecialEfficacyTypeENUM	EffectType );

	//系統訊息通知
//	void	Net_SystemMessage		( int Msg );
//	void	Net_SystemMessageData	( int Msg , int size , const char* Data );

	//通知裝爆
	void	Net_EQBroken			( EQWearPosENUM Pos );

	void	Net_DeltaRoleValue		( RoleValueName_ENUM ValueName , double Value );

	void	Net_AccountMoneyLockInfo();
	//檢查是否為敵對公會
	bool	CheckGuildWarDeclare	( RoleDataEx* Target );

	//--------------------------------------------------------------------------------------------
	//物品生存到期
	void	Net_ItemTimeout			( ItemFieldStruct& Item , ItemTimeoutPosENUM PosType );

	PartyInfoStruct*	GetPartyInfo( );
	void	ResetAttackSchedular( );

	void	CallLuaFunc( int TargetID , char* LuaScript );

	//////////////////////////////////////////////////////////////////////////
	void	GoodEvilAtkInfoProc( RoleDataEx* Target , int DHP );

	void	Print( int LV , const char* Title , const char* format , ... );

	static	bool LuaCheckFunction	( int OwnerID , int TargetID , const char* LuaScript );

	void	AutoUseItem( GameObjDbStructEx* ItemDB );
	//--------------------------------------------------------------------------------------------
	//Billing相關
	void	Net_BillingNotify( const char* Account, int RoleDBID, int Count );
#else

    void    Net_Mir_SetNumber( RoleValueName_ENUM ValueID , float Value ){};
    void    Msg( const char* Str ){};
	void    Msg_Utf8( const char* Str ){};
    void    Tell( int SayID , const char* Str ){};
    void    Say( const char* Str ){};
    void    Net_AddHP( int DHp ){};
    void    Net_AddMP( int DMp ){};
    void    Net_AddMagBuf( int MagicID , int Time  ){};
    void    Net_ItemInBuffer( ItemFieldStruct& Item ){};
    void    Net_FixItemInfo_Body( int Pos ){};
    void    Net_FixItemInfo_Bank( int Pos ){};
    void    Net_FixItemInfo_EQ( int Pos ){};
    void    Net_FixItemInfo     (  int Pos , int Type ){};
	void	Net_FixKeyItemFlag	( int KeyItemID , bool Value ){};
	void	Net_FixTitleFlag	( int KeyItemID , bool Value ){};
	void	Net_FixCardFlag		( int KeyItemID , bool Value ){};

    void    Net_FixMoney( ){};
    void    Net_FixRoleValue( RoleValueName_ENUM	ValueName , double Value ){};
    void    Net_FixLookEQ( ){};
    void    Net_ClearAssistMagic( int MagicID ,int BuffOwnerID){};
    void    FixAttackMode( ){};
	void	Net_SendRangeAttackMode( bool Mode ){};
    void    Net_MoveSpeed(){};
    void    Net_NotifyLvUp(){};
    void    Net_MaxHPMaxMPMaxSP(){};
    void    Net_HPMPSP(){};

    void    Net_SavePlayer( int Start , int Size , int SaveTime ){};
//	void	Net_FriendList_ModifyInfo(){};
	void	Net_MagicShieldInfoRange( int AttackGUID , int UnAttackGUID , int AttackMagicID , int ShieldMagicID , int AbsobDamage ){};
	void	Net_NpcAttackTarget(){};

	void	Net_MoveObj( ){};
	void	Net_SendRangeMove( ClientMoveTypeENUM Type  ){};

	void	Net_GameMsgEvent( GameMessageEventENUM Event ){};
	void    Net_ChangeRoleInfo(){};

	void	Log_ItemTrade( RoleDataEx* FromRole , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note ){};
	void	Log_ItemTrade	( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , ItemFieldStruct& Item , const char* Note ){};
	void	Log_ItemDestroy	( ActionTypeENUM Type , ItemFieldStruct& Item , int ItemCount , const char* Note ){};
	void	Log_Money		( RoleDataEx* FromRole , ActionTypeENUM Type , int Money ){};
	void	Log_Money_Account( RoleDataEx* FromRole , ActionTypeENUM Type , int Money ){};
	void	Log_Money		( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , int Money ){};
	void	Log_Money_Account( int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , int Money ){};
	void	Log_Money_Bonus	(  RoleDataEx* FromRole , ActionTypeENUM Type , int Money ){};

	void	Log_PlayerActionLog(){};
	void	Log_Level( ){};
	void	Log_Dead( RoleDataEx* Killer ){};
	
	void	Net_SendChat_ChangeRoleInfo( ){};
	void	Net_SendGM_ObjInfo( ){};

	void	Net_SendRangeSpecialEfficacy( SpecialEfficacyTypeENUM	EffectType ){};
	//系統訊息通知
//	void	Net_SystemMessage		( int Msg ){};
	void	Net_SystemMessageData	( int Msg , int size , const char* Data ){};
	//通知裝爆
	void	Net_EQBroken			( EQWearPosENUM Pos ){};
	void	Net_DeltaRoleValue		( RoleValueName_ENUM ValueName , float Value ){};
	void	Log_AddExp				( int Log ){};
	void	Log_SkillLv				( int SkillType , int SkillValue ){};
	bool	CheckGuildWarDeclare	( RoleDataEx* Target ){ return false;};
	void    Net_FixAssistMagicTime( int MagicID , int Time , int BuffOwnerID ){};
	//物品生存到期
	void	Net_ItemTimeout			( ItemFieldStruct& Item , ItemTimeoutPosENUM PosType ){};
	PartyInfoStruct*	GetPartyInfo( ){ return NULL;};
	void	ResetAttackSchedular( ){};
	void	CallLuaFunc( int TargetID , char* LuaScript ){};
	void	Net_AccountMoneyLockInfo(){};
	void	GoodEvilAtkInfoProc( RoleDataEx* DefTarget , int DHP ){};
	void	Log_DepartmentStore( ItemFieldStruct& Item , ActionTypeENUM Type , int Count , int Cost , int Cost_Bonus , int Cost_Free , int PlayerDBID ){};
	void	Net_SC_DelItemMsg( ItemFieldStruct& Item ){};
	void	Print	( int LV , const char* Title , const char* format , ... ){};
	static bool	LuaCheckFunction	( int OwnerID , int TargetID , const char* LuaScript ){ return false;};
	void	AutoUseItem( GameObjDbStructEx* ItemDB ){};
	void	Net_BillingNotify( const char* Account, int RoleDBID, int Count ){};
#endif