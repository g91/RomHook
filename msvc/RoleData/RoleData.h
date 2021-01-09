#ifndef	__ROLEDATA_H_
#define __ROLEDATA_H_
#include "RoleBaseInc.h"
#include "RoleAttr.h"

struct StructArenaMember
{
	int		iDBID;
	int		iWeekWinCount;
	int		iWeekLoseCount;
};


struct StructArenaInfo
{
	int						iWeekJoinCount;
	float					fArenaPoint;
	int						iWeekWinCount;
	int						iWeekLoseCount;
	int						iMonthWinCount;
	int						iMonthLoseCount;
	int						iLifeWinCount;
	int						iLifeLoseCount;

	int						iNumTeamMember;
	StructArenaMember		TeamMember[10];	
};

//////////////////////////////////////////////////////////////////////////
//�u��Server �ϥΨ쪺���(�U����@��)
struct SelfRoleData
{
	int					__MoneyCheckPoint;
	//---------------------------------------------------------------------------------
	//�����I
	//---------------------------------------------------------------------------------
	RolePosStruct		RevPos;			//�����I
	int					RevZoneID;

	int					LiveTime;							        //�ͦs�ɶ�(-1 ��������)
	int					PID;								        //�ѥ����]�w���@��ID�A�ΨӼ@���R�O�ϥ�
    int                 NpcQuestID;                                 //����ID
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_>	PlotClassName;          //�@������(�Ψӷj�M����@��)
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_>	AutoPlot;               //�۰�
	RolePosStruct		ReturnPos;		//�ǰe�����I
	int					ReturnZoneID;


	SelfRoleData()	{ Init(); };
	void	Init();
};

struct PlayerSelfRoleData
{
	int __MoneyCheckPoint;
  	//---------------------------------------------------------------------------------
	//		�Ȯɦ^���I(���a�p��)
	//---------------------------------------------------------------------------------

	FriendListStruct		FriendList;		//�n�ͦW��

	MonsterHunterStruct		MonsterHunter;	//���Ǹ��
	DestroyItemLogStruct	DestroyItemLog;	//���~�R���Ȯɬ���
	TombStruct				Tomb;			//�ӸO���
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//�@��Client �ݻPServer�� �P�U�Ӫ���ݭn�����
struct	BaseRoleData
{
	int					__MoneyCheckPoint;
	ObjectModeStruct	Mode;								//����򥻳]�w	
	SystemFlagStruct	SysFlag;

	BaseAbilityStruct	Ability;

	StaticString< _MAX_NAMERECORD_SIZE_ >   RoleName;	    //����W��
	int					ZoneID;								//�ثe�ϰ�s��
    RolePosStruct       Pos;
	float				vX , vY , vZ;						//�����V�V�q(��ܥ�)
	int					RoomID;								//�Ҧb�Ŷ�
	int					PlayTime;							//�C���ɶ� (����)

    LookStruct          Look;
    ItemFieldStruct		ItemInfo;							//�㹳���~�p�G���_�ӥN�����
	//-------------------------------------------------------------------------------
	//		����ƭȸ��
	//-------------------------------------------------------------------------------
	Race_ENUM			Race;								//�ر�
	Voc_ENUM		    Voc;								//¾�~
    Voc_ENUM		    Voc_Sub;							//��¾�~
	Sex_ENUM			Sex;								//�ʧO
    
    float				HP,MP,SP;							//�ثe��q�P�k�O
	float				SP_Sub;								//��¾��SP
	int					StomachPoint;						//�Ÿ���
//	BaseAbilityStruct	AbilityList[ EM_Max_Vocation ];	    //�U¾�~���Ӻذ򥻼ƽ�(***)	

	EQStruct			EQ;									//�˳Ƹ��

    int                 TitleID;
	bool				IsShowTitle;						//����Y��
	
    SkillValueStruct  	SkillValue;		                    //�ޯ���

    StaticVector< BuffBaseStruct , _MAX_BUFF_COUNT_ >	Buff; //�k�NBuff
	StaticFlag<_MAX_FLAG_COUNT_>						KeyItem;
	int					PartyID;							//����ID
	int					GuildID;							//���|ID
	float				GuildLeaveTime;						//���|���}�ɶ�

	MagicColdownStruct	Coldown;

	//�y�M�C��
	int					HorseColor[4];

	//�����㹳id
	int					ImageObjID;

	
	BaseRoleData( )	{ Init(); };
	void	Init();
};


struct PlayerBaseRoleData
{
	int					__MoneyCheckPoint;

	BaseAbilityStruct	AbilityList[ EM_Max_Vocation ];	    //�U¾�~���Ӻذ򥻼ƽ�(***)	
	int					MaxLv;								//�̤j����
	int                 Famous[_MAX_FAMOUS_COUNT_]; 
	//���骫�~���
	BodyItemStruct      Body;
	BankItemStruct      Bank;
	//�O�c���
	EQStruct			EQBackup[_MAX_BACKUP_EQ_SET_COUNT_];					    //�˳Ƹ��
//	TreasureBoxStruct	TreasureBox;

	//�Y�θ��
	StaticString< _MAX_NAMERECORD_SIZE_ >   TitleStr;	    //�۩w�Y��
	StaticFlag<_MAX_TITLE_FLAG_COUNT_>		Title;
	StaticFlag<_MAX_CARD_COUNT_>			Card;			//�d��

	StaticFlag<_MAX_CLIENT_FLAG_COUNT_>		ClientFlag;		//client �ݭn�D�s�����Ӹ��
	unsigned char			ClientData[ _MAX_CLIENT_DATA_SIZE_ ];

	QuestStruct			Quest;
	int					DeadCountDown;				    //���`�_���˼�

	StaticVector< RefineBuffStruct , _MAX_REFINE_BUFF_COUNT_ > RefineColdown; //�X��Buff

	bool				IsBillboardAnonymous;				//�Ʀ�]�ΦW

	//�ɶ��X�� �@�����B�z�@��
	union
	{
		int		TimeFlag[ _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_ ];
		struct  
		{
			int					RealTimeFlag[_MAX_REALTIME_FLAG_];	//�u�ɮɶ� �X�� ( �ѤU�X���� )
			int					PlayTimeFlag[_MAX_PLAYTIME_FLAG_];	//�C���ɶ�		( �ѤU�X���� )
		};
	};
	int		LuaValueFlag[_MAX_LUA_VALUES_FLAG_ ];

	int					PKScore;							//pk�n��
	int					TitleCount;							//�Y�μƶq
	int					HouseDBID;
	int					DestroyTime;						//�R�����ɶ�	
	StaticString< 33 >  Password;						    //���a�G���K�X

	int					PlayTimeQuota;						//���I�g�Ѿl�ɶ�

	RentFuncStruct		RentFun;							//���Υ\��

	ManagementENUM		ManageLV;					       	//�v������

//	ShowEQStruct		ShowEQ;								//�˳����

	LocationSaveStruct	LocationSave[ _MAX_LOCATION_SAVE_COUNT_ ];	//�O�����ǰe�I
	float				GoodEvil;							//���c��
	float				GoodEvilBonus;						//�i�W�[�����c���I��
	int					VocCount;							//�̦h�i�H�Ƿ|�X��¾�~
	int					BoxEnergy;							//����_����q

	int					MedalCount;							//�о��I��
	int					Money_Bonus;

	//����Ȧs���(���~�n�������a�ɡA����m��Ȧs��줤)
	StaticVector< ItemFieldStruct , _MAX_TEMP_COUNT_ > ItemTemp;	

	//���ͬ�����T
	RaiseInfoStruct		RaiseInfo;

	int					LockAccountTime;											//�b������w 0 �N���ɶ�(NowTime)
	int					LockAccountMoney[ Def_AccountMoneyLockTime_Max_Count_ ];	//�C����w
	int					LockAccountMoney_Forever;									//�ä[�ꪺ����

	RolePetStruct		Pet;

	float				Honor;
	float				HonorWorth;

	int					LastBeHonorKilledTime;										// �W���Q�a�A�������ɶ�
	int					MaxPlantCount;						//�̦h�i�شӪ��ƶq

	struct  
	{
		float		MoneyTraderCount;
		float		AutoBotCount;
		int			BotReportDBID;			//�|����
		int			BotReportTime;			//�̫�@���|���ɶ�
		int			BotReportProtectTime;	//�|�O�@�ɶ�

	}Defendant;	//�Q�i
	InstanceSettingStruct	InstanceSetting;
	int					RoomKey;
	SuitSkillStruct		SuitSkill;

	int					ClinetSetting[_MAX_CLIENT_SETTING_SIZE_];
	
	VipMemberStruct		VipMember;


	CoolSuitBase		CoolSuitList[ _DEF_MAX_COOL_SUIT_COUNT_ ];
	//StaticVector< int , _DEF_MAX_COOL_CLOTH_COUNT_ > CoolClothList;	
	int					CoolClothList[ _DEF_MAX_COOL_CLOTH_COUNT_ ];
	int					Reserver001;
	int					CoolSuitID;	//�ثe��ܪ��M�˸��

	StaticVector< int , _DEF_MAX_PET_EXBAG_COUNT_ > PetExBag;	
	StaticVector< HorseExBagBase , _DEF_MAX_HORSE_EXBAG_COUNT_ > HorseExBag;	

	int					IncursivePoint;
	TitleSysStruct		TitleSys;
//	int					ZoneKey;		//�i�J�ϰ�]�w��Key
	SlotMachineInfo		SlotMachine;

	int					DuelistReward;				//�i�h����
	StaticFlag<_MAX_PET_CARD_COUNT_>	PetCard;	//�d��

	//�s�W�S��f��
	int					TrialBadgeCoin;			//�շ�����
	int					RelicsCoin;				//�j�N��
	int					DreamlandCoin;			//�ڹҥ����L�O
	int					PhiriusShellCoin;		//�����Ŷꨩ
	int					EnergyJusticeCoin;		//���q��q
	int					ProofLegendCoin;		//�ǻ�����
	int					MirrorCoin;				//������L
	
	int					WeekInstance[ DEF_MAX_WEEK_INS_TYPE ];
	int					WeekInstDay;
	int					WeekResetCount;			//

	PhantomStruct		Phantom;
	

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		for( int i = 0 ; i < _DEF_MAX_COOL_SUIT_COUNT_ ; i++ )
			CoolSuitList[i].ShowEQ._Value = -1;
	}
};
//////////////////////////////////////////////////////////////////////////

struct	TempRoleData
{
	RoleValueData			Attr;						//����ƭȸ��

    SysManageInfoStruct     Sys;                        //�t�κ޲z������T
	PathProcStruct			Move;						//���ʸ�T

	NPC_AI_Struct			AI; 						//AI�B�z

	NPCHateList				NPCHate;					//�Ǫ��Q���쪺��T(���Ǫ�AI�ϥ�)

	RoleUpdateEvent			UpdateInfo;					//��s��T

	MagicProcInfo			Magic;						//�I�k��T

    NPC_RandomMoveStruct    RandomMove;                 //�üƲ��ʸ�T


	float					BoundRadiusX;				//�򥻼ҫ��j�p
	float					BoundRadiusY;				//�򥻼ҫ��j�p

    //---------------------------------------------------------------------------------------
    int                     AroundPlayer;               //�P��j�����a�ƶq
	//---------------------------------------------------------------------------------------

	//Server�ݼ@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> RangePlot;			//�d��@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> TouchPlot;			//�B�o�@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> DeadPlot;			//���`�@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> SayPlot;			//�d�򻡸ܼ@��
    StaticString< _MAX_LUA_FUNTIONNAMESIZE_> GiveItemPlot;		//�����B�o�@�� ( PCall ) bool GiveItemPlot( int Item1 , int Item2 , int Item3 , int Item4 )
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> CollisionPlot;		//�I���@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> CheckPetCommand;	//�d���˹�@��

    int                     TouchPlot_Range;
    int                     RangePlot_Range;
	int						OnDeadMagic;				//���`Ĳ�o���k�N
	//---------------------------------------------------------------------------------------
	//Client�۰ʼ@��
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> C_AutoPlot;//Client �ݪ��۰ʼ@��
	//---------------------------------------------------------------------------------------
    int                     CliActionID;                //Cli�ݰʺAID �i�J�ճ��|�e�X
    //---------------------------------------------------------------------------------------

    StaticString<_MAX_ACCOUNT_SIZE_>     CreateAccount;  //�إߦ����󪺱b��


    RoleBackupInfo          BackInfo;                   //������T�Ψӧ�sClient �Ϊ��A�B�z

    ShopStateStruct         ShopInfo;                   //�ө���T

//	SummonPetTypeENUM		PetType;					//�۳�����
  //  PetStruct				SummonPet[EM_SummonPetType_Max];	//�ۥX�Ӫ��d��
	SummonPetInfoStruct		SummonPet;

	int						iGatherNumber;				// �Y�O�Ķ����󪺸�, ��Q�Ķ��ƶq	

	unsigned				iDelayPatrol;				// �����޼@��

	int						iMinimapIcon;				// �b�p�a�ϤW�㹳�� ICON �N��
	//---------------------------------------------------------------------------------------
	int						iQuestStatus;				// �ثe

	ScriptBorderStruct		ScriptBorder;				// �۸O����


	int						IdleMotionID;

	ScriptEventFlagStruct	CheckEvent;					// �S��ƥ��ˬd

	//---------------------------------------------------------------------------------------
	//���W��Zone�ɩһݳ]�w�����
	//---------------------------------------------------------------------------------------	
	ChangeZoneInfoStruct	ChangeZoneInfo;

	int						SkillComboID;
	int						SkillComboTime;				//����Combo���ɶ�
	int						SkillComboPower;
	int						CursorType;					// Client �ݴ������

	union
	{
		int						CrystalID;					// NPC �ұa��U�Ф��|��, �ξԳ��� ID
		int						BattleGroundZoneID;			// NPC �N���ӾԳ�
		int						BattleGroundTeamID;			// PLAYER ���ݪ��Գ�����

	};

	//---------------------------------------------------------------------------------
	bool					IsDisabledChangeZone;
	//---------------------------------------------------------------------------------
	int						Register[_MAX_REGISTER_COUNT_];	//�Ȧs��
	//---------------------------------------------------------------------------------
	int						MagicToolsColdown;			//�U���i�ϥ��]�k���~�ɶ�
	int						PlayerClsHateColdown;		//���a�M������C��Coldown

	GuildBuildingTypeENUM		GuildBuildingType;
	union
	{
		int						GuildBuildingDBID;		//���|�ؿv��DBID
		int						GuildFurnitureDBID;		//

	};

	int						PingCount;					//�Ψ��˴�Client �O�_���[�t


	

	struct
	{
		int		UseItemTempID;
		int		Type;	
	}EQCombin;

	int						iDefIdleAction;
	int						LookTargetID;
	struct  
	{
		int		MagicID;
		int		MagicPos;
		int		MessageDelayCount;
	}CycleMagic;

	bool		IsPKDead_NotGuilty;					//�c�NPK��


	//�ĥλ���B�z
	struct
	{
		int		Time;
		int		Count;
	}BuffTimeDesc[_MAX_BuffTimeDesc_COUNT_];

	ClientStateStruct		CliState;				//Client �@�Ǫ��A���
	int				DeadZoneCountDown;
	float			ZoneDamgeRate;
	ZoneTypeENUM	ZoneType;

	int			LastDHp;							//�̫�@��HP�ܤ�
	int			LastDHpTarget;						//�̫�@��HP�ܤƪ��ؼ�
	TradeStruct	Trade;

	int				iWorldID;						//�H�����ݪ� WorldID
	int				AttachObjID;					//�s������
	int				AttachPos;						//�s������m
	
	ItemFieldStruct PotInfo;						//�֤l����T

	int				iLockGUID;
	int				iLockTime;
	float			ModelRate;

	//////////////////////////////////////////////////////////////////////////
	int				LockHP;					//��w��q�I
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> LockHPEvent;	
	//////////////////////////////////////////////////////////////////////////
	int				SoulPoint;				//�F���
	//////////////////////////////////////////////////////////////////////////
	LuaHideInfoStruct HideInfo;


	TempRoleData( ) { Init(); };
	void	Init();
};

struct PlayerTempRoleData
{
	PlayerActionLogStruct	Log;						//�C10����or ���Ϯ� �p���@�� 
	SkillStruct				Skill;                      //�ޯ�k�N��T
	CastingData				CastData;
	//��檫�~����
	StaticVector< SellItemFieldStruct , _MAX_SELL_ITEM_SAVE_COUNT_ >	SellItemBackup;

	// ��ܿﶵ�Ȧs
	SpeakStruct				SpeakInfo;

	// �@������
	ScriptStruct			ScriptInfo;

	PKInfoStruct			PKInfo;						//pk��T

	int						DialogSelectID;				//���a�ҿ諸Dialog ��ID( -2 �N���N��h �A -1 �N����� )

	CastingTypeENUM			CastingType;				//�@�몺Casting
	int						CastingTime;				//Casting�����ɶ�
	int						CastingItemID;				//Casting���ؼЪ���

	//�Q�ʧޯ�
	StaticVector< int , _MAX_PASSIVESKILL_COUNT_ >						PassiveSkill;
	StaticVector< int , _MAX_PASSIVESKILL_COUNT_ >						PassiveSkillLv;

	//---------------------------------------------------------------------------------
	//		����^�Ǧ�m
	//---------------------------------------------------------------------------------
	int						ParallelZoneID;				//����Ŷ���ID
	//---------------------------------------------------------------------------------
	//		������θ��X
	//---------------------------------------------------------------------------------
	union
	{
		int						VisitHouseDBID;	
		int						VisitGuildID;	
	};
	BattleGroundInfoStruct	BGInfo;						// �Գ��B�z��T

	ChangeWorldStruct		ChangeWorld;

	LuaPlotClockStruct		LuaClock;

	int						LockAccountMoney;

	//�U�ӻ��ˬd���ʥ]�v��( �C����1�I�v�� )
	float					PacketCheckPoint[ EM_ClientPacketCheckType_Max ];

	float					TempTpDexp;					//�ȦsTp ���t��I��	

	MineCheckStruct			MineCheck;					//���q�ˬd

	StaticVector< int , _MAX_PK_DEAD_SAVE_COUNT_ > PKDeadTime;

	int                     LoginTempID;                //�O���n�J���ˬd�O�_�n�J�����Ƶ{ID

	StructArenaInfo			Arena[3];					// Arena Info

	GambleItemStateStruct	GambleItemState;			//�ݩʽ�ո��

	SendPacketModeStruct	SendPGMode;
	int						LastSendMovePG;
	int						PartyLootOrder;				//Party���y���_�Ǹ�
	int						ChangeZoneCountDown;		//�p�G���ϥΪ��~ ���𴫰�
	StaticVector< ExSkillBaseStruct , _MAX_EX_SKILL_COUNT_ >	ExSkill; //�@���]�w�B�~�i�H�ϥΪ��k�N

	//�I���]�۸��
	MagicStoneExchange		MagicStoneSopeInfo;

	BattleGroundReturnValueStruct	BgReturn;

	int						iForceFlagID;

	void	Init()
	{ 
		memset( this , 0 , sizeof(*this) );
		CastData.Clear(); 
	};
};

//////////////////////////////////////////////////////////////////////////
//���Ϥ��|�s�����
struct DynamicRoleData	
{
	//�_�۸��
	TreasureBoxStruct*	TreasureBox;

	DynamicRoleData()
	{
		memset( this , 0 , sizeof(*this) );
	}
	~DynamicRoleData()
	{
		Init();
	}
	void Init()
	{
		if( TreasureBox != NULL )
		{
			delete TreasureBox;
			TreasureBox = NULL;
		}
	};
};
//////////////////////////////////////////////////////////////////////////
struct SysBaseRoleData
{
	GameObjectClassificationENUM        Type;
	int			                        CharField;          //���b�����ĴX�Ө�����
	int					                DBID;				//��ƮwID
	StaticString<_MAX_ACCOUNT_SIZE_>    Account_ID;	        //�b���W��
	StaticString<_MAX_CREATETIME_SIZE_> CreateTime;	        //�����󲣥ͪ����
	unsigned							LogoutTime;			//�n�X���t�ήɶ�	
	StaticFlag< _ACCOUNT_FLAG_COUNT_ >	AccountFlag;		//�b����ƺX��
};


struct	RoleData
{
	static PlayerSelfRoleData gPlayerSelfData;
	//static PlayerBaseRoleData gPlayerBaseData;
	static PlayerTempRoleData gPlayerTempData;
	static void GlobalInit();

    SysBaseRoleData Base;
	SelfRoleData	SelfData;								//LocalServer �M��
	BaseRoleData	BaseData;								//Client �P Server �|�Ψ�
	TempRoleData	TempData;								//ClientServer �B�z���⪺�Ȧs�K��
	DynamicRoleData	DynamicData;							//�ʺA��ơA���|����
	//////////////////////////////////////////////////////////////////////////
	//�u�����a�|�Ψ쪺���
	//////////////////////////////////////////////////////////////////////////
	PlayerSelfRoleData*		PlayerSelfData;
	PlayerBaseRoleData*	 	PlayerBaseData;
	PlayerTempRoleData*		PlayerTempData;
	//////////////////////////////////////////////////////////////////////////

	RoleData( );
	~RoleData( );
	void	Init( );
	void	Copy( const RoleData* fromRole )
	{
		if( fromRole == this )
			return;

		RoleData* toRole = this;
		toRole->Base = fromRole->Base;

		toRole->SelfData = fromRole->SelfData;			//LocalServer �M��
		toRole->BaseData = fromRole->BaseData;			//Client �P Server �|�Ψ�
		toRole->TempData = fromRole->TempData;			//ClientServer �B�z���⪺�Ȧs�K��
		toRole->DynamicData.Init();						//�ʺA��ơA���|����
		//////////////////////////////////////////////////////////////////////////
		//�u�����a�|�Ψ쪺���
		//////////////////////////////////////////////////////////////////////////
		if(		toRole->PlayerSelfData != &gPlayerSelfData 
			||	toRole->PlayerSelfData != fromRole->PlayerSelfData)
		{
			*(toRole->PlayerSelfData) = *(fromRole->PlayerSelfData);
			*(toRole->PlayerBaseData) = *(fromRole->PlayerBaseData);
			*(toRole->PlayerTempData) = *(fromRole->PlayerTempData);
		}
	}
	void	NpcInitLink()
	{
		PlayerSelfData = &gPlayerSelfData;
		//PlayerBaseData = &gPlayerBaseData;
		PlayerTempData = &gPlayerTempData;
		DynamicData.Init();							//�ʺA��ơA���|����
	}

	const RoleData& operator = ( const RoleData& In )
	{
		Copy( &In );
		return In;
	}
};

struct	PlayerRoleData : public RoleData
{
	//////////////////////////////////////////////////////////////////////////
	//�u�����a�|�Ψ쪺���
	//////////////////////////////////////////////////////////////////////////
	PlayerSelfRoleData		PlayerSelfData;
	PlayerBaseRoleData	 	PlayerBaseData;
	PlayerTempRoleData		PlayerTempData;

	PlayerRoleData();
	//{
	//	SetLink();
	//	Init();
	//};
	void SetLink()
	{
		((RoleData*)this)->PlayerSelfData = &PlayerSelfData;
		((RoleData*)this)->PlayerBaseData = &PlayerBaseData;
		((RoleData*)this)->PlayerTempData = &PlayerTempData;
	};
	void Init()
	{
		RoleData::Init();
		PlayerSelfData.Init();
		PlayerBaseData.Init();
		PlayerTempData.Init();
		TempData.Attr.Ability			= &PlayerBaseData.AbilityList[0];
		PlayerBaseData.PlayTimeQuota	= 60*60*24*30;
		//PlayerBaseData.SuitSkill.MaxEqSkillCount = 2;

		PlayerSelfData.__MoneyCheckPoint	= _MEMORY_CHECK_VALUE_;
		PlayerBaseData.__MoneyCheckPoint	= _MEMORY_CHECK_VALUE_;
		SelfData.__MoneyCheckPoint			= _MEMORY_CHECK_VALUE_;
		BaseData.__MoneyCheckPoint			= _MEMORY_CHECK_VALUE_;
	};

	const PlayerRoleData& operator = ( const PlayerRoleData& In )
	{
		SetLink();

	
		Base	 = In.Base;
		SelfData = In.SelfData;			//LocalServer �M��
		BaseData = In.BaseData;			//Client �P Server �|�Ψ�
		TempData = In.TempData;			//ClientServer �B�z���⪺�Ȧs�K��
		DynamicData.Init();				//�ʺA��ơA���|����
		//////////////////////////////////////////////////////////////////////////
		//�u�����a�|�Ψ쪺���
		//////////////////////////////////////////////////////////////////////////
		PlayerSelfData = In.PlayerSelfData;
		PlayerBaseData = In.PlayerBaseData;
		PlayerTempData = In.PlayerTempData;
		return In;
	}

	int SerialCode( );
	int SerialCode1( );
	int SerialCode_All();
	int AccountSerialCode( );
};

//--------------------------------------------------------------------------------------------------------
// �﨤����
//--------------------------------------------------------------------------------------------------------
struct SampleRoleData
{
	int									DBID;
	StaticString<_MAX_NAMERECORD_SIZE_> RoleName;
	StaticString<_MAX_ZONENAME_SIZE_>   ZoneName;		//�a�ϦW��

	int						OrgObjID;					//�����lID
	int						Level;
	int                 	Level_Sub;					//��¾����()

	//�㹳���
	Sex_ENUM				Sex;						//�ʧO
	Race_ENUM				Race;						//�ر�
    Voc_ENUM            	Voc;
	Voc_ENUM   				Voc_Sub;
	//float					BoneScale[10];
	char					BoneScale[15];

	int						iHairColor;			
	int						iBodyColor;			
	int						iFaceID;			
	int						iHairID;			

	EQStruct				EQ;							//�˳Ƹ��
	int						DestroyTime;				//�h�[��R��

	SystemFlagStruct		SysFlag;		
	ShowEQStruct			ShowEQ;
	void init()
    {
        memset(this,0,sizeof(SampleRoleData));
		Sex     = EM_Sex_Boy;
		Race    = EM_Race1 ;
        Voc     = EM_Vocation_Warrior;

		for ( int i = 0; i < 15; i++ )
			BoneScale[i] = 100;
	};
};
//--------------------------------------------------------------------------------------------------------
// npc �ݭn���s�����
//--------------------------------------------------------------------------------------------------------
struct NPCData
{ 
	int                                     DBID;
	int					                    OrgObjID;		//���~�˪OID(�㹳���)
	StaticString<_MAX_CREATETIME_SIZE_>	    CreateTime;		//�����󲣥ͪ����	
	ObjectModeStruct	                    Mode;			//����򥻳]�w
	StaticString<_MAX_NAMERECORD_SIZE_>     RoleName;	    //����W��
    int					                    ZoneID;			//�ثe�ϰ�s��
    RolePosStruct                           Pos;
    int                                     LiveTime;
    int                                     OwnerDBID;
    int                                     PID;            //���e�]�w��ID�Ψӷj�M����@��
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_> PlotClassName;	//�ݩ���@�Ӽ@���ϥ�
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_> AutoPlot;	    //�۰�   
	int										QuestID;
    StaticString<_MAX_ACCOUNT_SIZE_>		CreateAccount;	//����W��
	float									vX , vY , vZ;	//���⭱�V
	int										RoomID;
};
//--------------------------------------------------------------------------------------------------------
#endif