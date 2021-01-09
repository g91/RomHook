//RoleDataEx �����ϥΨ� NetWaker������
#ifdef _LOCAL_SERVER_

    void    Net_Mir_SetNumber( RoleValueName_ENUM ValueID , float Value );
	void    Msg( const char* Str );
	void    Msg_Utf8( const char* Str );
    void    Msg( const wchar_t* Str );
    void    Tell( const char* name , const char* Str );
    void    Say( const char* Str );
    //--------------------------------------------------------------------------------------------
    //�԰���T�B��
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
    //�]�k
    //--------------------------------------------------------------------------------------------
    void    Net_ClearAssistMagic( int MagicID , int BuffOwnerID );
	void    Net_FixAssistMagicTime( int MagicID , int Time , int BuffOwnerID );
    //--------------------------------------------------------------------------------------------
    //��LServer�����\��
    //--------------------------------------------------------------------------------------------
    void    FixAttackMode( );
	void	Net_SendRangeAttackMode( bool Mode );
    //--------------------------------------------------------------------------------------------
    //��LServer�����\��
    //--------------------------------------------------------------------------------------------
    void    Net_MoveSpeed();

    //--------------------------------------------------------------------------------------------
    //�q���g��ɯ�
    //--------------------------------------------------------------------------------------------
    void    Net_NotifyLvUp();
	//--------------------------------------------------------------------------------------------
	//�q���g�����¾�~�Τɯ�
	//--------------------------------------------------------------------------------------------
    void    Net_ChangeRoleInfo();
    //--------------------------------------------------------------------------------------------
    //�q���g��HPMPSP
    //--------------------------------------------------------------------------------------------
    void    Net_MaxHPMaxMPMaxSP();
    void    Net_HPMPSP();

    //�x�s���
    void    Net_SavePlayer( int Start , int Size , int SaveTime );
	//--------------------------------------------------------------------------------------------
	//�q��Chat�n���W�����
	//--------------------------------------------------------------------------------------------
//	void	Net_FriendList_ModifyInfo();
	//--------------------------------------------------------------------------------------------
	//�q���g��Y���� �]�k�޸�T
	void	Net_MagicShieldInfoRange( int AttackGUID , int UnAttackGUID , int AttackMagicID , int ShieldMagicID , int AbsobDamage );
	//--------------------------------------------------------------------------------------------
	//�q���P��Ynpc  �n�������ؼ�
	void	Net_NpcAttackTarget();
	//--------------------------------------------------------------------------------------------
	//�n�DNPC����Y�@�I
	void	Net_MoveObj( );
	void	Net_SendRangeMove( ClientMoveTypeENUM Type  );
	//--------------------------------------------------------------------------------------------
	//�e�C���ƥ�T��
	void	Net_GameMsgEvent( GameMessageEventENUM Event );
	//�e����R�����T����Client
	void	Net_SC_DelItemMsg( ItemFieldStruct& Item );
	//--------------------------------------------------------------------------------------------
	//Log�B�z
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
	//�q������򥻸�Ʀ�����
	void	Net_SendChat_ChangeRoleInfo( );

	//--------------------------------------------------------------------------------------------
	//�q��gm tools �����Ʀ��ץ�
	void	Net_SendGM_ObjInfo( );
	   //NetSrv_GMTools::S_ObjInfo( DF_NO_LOCALID , Owner );

	//����S�ĳq��
	void	Net_SendRangeSpecialEfficacy( SpecialEfficacyTypeENUM	EffectType );

	//�t�ΰT���q��
//	void	Net_SystemMessage		( int Msg );
//	void	Net_SystemMessageData	( int Msg , int size , const char* Data );

	//�q�����z
	void	Net_EQBroken			( EQWearPosENUM Pos );

	void	Net_DeltaRoleValue		( RoleValueName_ENUM ValueName , double Value );

	void	Net_AccountMoneyLockInfo();
	//�ˬd�O�_���Ĺ綠�|
	bool	CheckGuildWarDeclare	( RoleDataEx* Target );

	//--------------------------------------------------------------------------------------------
	//���~�ͦs���
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
	//Billing����
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
	//�t�ΰT���q��
//	void	Net_SystemMessage		( int Msg ){};
	void	Net_SystemMessageData	( int Msg , int size , const char* Data ){};
	//�q�����z
	void	Net_EQBroken			( EQWearPosENUM Pos ){};
	void	Net_DeltaRoleValue		( RoleValueName_ENUM ValueName , float Value ){};
	void	Log_AddExp				( int Log ){};
	void	Log_SkillLv				( int SkillType , int SkillValue ){};
	bool	CheckGuildWarDeclare	( RoleDataEx* Target ){ return false;};
	void    Net_FixAssistMagicTime( int MagicID , int Time , int BuffOwnerID ){};
	//���~�ͦs���
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