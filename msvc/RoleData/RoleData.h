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
//只有Server 使用到的資料(各物件共用)
struct SelfRoleData
{
	int					__MoneyCheckPoint;
	//---------------------------------------------------------------------------------
	//重生點
	//---------------------------------------------------------------------------------
	RolePosStruct		RevPos;			//重生點
	int					RevZoneID;

	int					LiveTime;							        //生存時間(-1 為不消失)
	int					PID;								        //由企劃設定的一個ID，用來劇情命令使用
    int                 NpcQuestID;                                 //任務ID
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_>	PlotClassName;          //劇情分類(用來搜尋角色劇情)
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_>	AutoPlot;               //自動
	RolePosStruct		ReturnPos;		//傳送門的點
	int					ReturnZoneID;


	SelfRoleData()	{ Init(); };
	void	Init();
};

struct PlayerSelfRoleData
{
	int __MoneyCheckPoint;
  	//---------------------------------------------------------------------------------
	//		暫時回傳點(玩家小屋)
	//---------------------------------------------------------------------------------

	FriendListStruct		FriendList;		//好友名單

	MonsterHunterStruct		MonsterHunter;	//打怪資料
	DestroyItemLogStruct	DestroyItemLog;	//物品刪除暫時紀錄
	TombStruct				Tomb;			//墓碑資料
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//一般Client 端與Server端 與各個物件需要的資料
struct	BaseRoleData
{
	int					__MoneyCheckPoint;
	ObjectModeStruct	Mode;								//物件基本設定	
	SystemFlagStruct	SysFlag;

	BaseAbilityStruct	Ability;

	StaticString< _MAX_NAMERECORD_SIZE_ >   RoleName;	    //角色名稱
	int					ZoneID;								//目前區域編號
    RolePosStruct       Pos;
	float				vX , vY , vZ;						//角色方向向量(顯示用)
	int					RoomID;								//所在空間
	int					PlayTime;							//遊戲時間 (分鐘)

    LookStruct          Look;
    ItemFieldStruct		ItemInfo;							//顯像物品如果拿起來代表的資料
	//-------------------------------------------------------------------------------
	//		角色數值資料
	//-------------------------------------------------------------------------------
	Race_ENUM			Race;								//種族
	Voc_ENUM		    Voc;								//職業
    Voc_ENUM		    Voc_Sub;							//副職業
	Sex_ENUM			Sex;								//性別
    
    float				HP,MP,SP;							//目前血量與法力
	float				SP_Sub;								//副職的SP
	int					StomachPoint;						//空腹度
//	BaseAbilityStruct	AbilityList[ EM_Max_Vocation ];	    //各職業的個種基本數質(***)	

	EQStruct			EQ;									//裝備資料

    int                 TitleID;
	bool				IsShowTitle;						//顯示頭銜
	
    SkillValueStruct  	SkillValue;		                    //技能資料

    StaticVector< BuffBaseStruct , _MAX_BUFF_COUNT_ >	Buff; //法術Buff
	StaticFlag<_MAX_FLAG_COUNT_>						KeyItem;
	int					PartyID;							//隊伍ID
	int					GuildID;							//公會ID
	float				GuildLeaveTime;						//公會離開時間

	MagicColdownStruct	Coldown;

	//座騎顏色
	int					HorseColor[4];

	//物件顯像id
	int					ImageObjID;

	
	BaseRoleData( )	{ Init(); };
	void	Init();
};


struct PlayerBaseRoleData
{
	int					__MoneyCheckPoint;

	BaseAbilityStruct	AbilityList[ EM_Max_Vocation ];	    //各職業的個種基本數質(***)	
	int					MaxLv;								//最大等級
	int                 Famous[_MAX_FAMOUS_COUNT_]; 
	//身體物品欄位
	BodyItemStruct      Body;
	BankItemStruct      Bank;
	//保箱資料
	EQStruct			EQBackup[_MAX_BACKUP_EQ_SET_COUNT_];					    //裝備資料
//	TreasureBoxStruct	TreasureBox;

	//頭銜資料
	StaticString< _MAX_NAMERECORD_SIZE_ >   TitleStr;	    //自定頭銜
	StaticFlag<_MAX_TITLE_FLAG_COUNT_>		Title;
	StaticFlag<_MAX_CARD_COUNT_>			Card;			//卡片

	StaticFlag<_MAX_CLIENT_FLAG_COUNT_>		ClientFlag;		//client 端要求存的狀太資料
	unsigned char			ClientData[ _MAX_CLIENT_DATA_SIZE_ ];

	QuestStruct			Quest;
	int					DeadCountDown;				    //死亡復活倒數

	StaticVector< RefineBuffStruct , _MAX_REFINE_BUFF_COUNT_ > RefineColdown; //合成Buff

	bool				IsBillboardAnonymous;				//排行榜匿名

	//時間旗標 一分鐘處理一次
	union
	{
		int		TimeFlag[ _MAX_REALTIME_FLAG_ + _MAX_PLAYTIME_FLAG_ ];
		struct  
		{
			int					RealTimeFlag[_MAX_REALTIME_FLAG_];	//真時時間 旗標 ( 剩下幾分鐘 )
			int					PlayTimeFlag[_MAX_PLAYTIME_FLAG_];	//遊戲時間		( 剩下幾分鐘 )
		};
	};
	int		LuaValueFlag[_MAX_LUA_VALUES_FLAG_ ];

	int					PKScore;							//pk積分
	int					TitleCount;							//頭銜數量
	int					HouseDBID;
	int					DestroyTime;						//刪除的時間	
	StaticString< 33 >  Password;						    //玩家二次密碼

	int					PlayTimeQuota;						//防沉迷剩餘時間

	RentFuncStruct		RentFun;							//租用功能

	ManagementENUM		ManageLV;					       	//權限等級

//	ShowEQStruct		ShowEQ;								//裝備顯示

	LocationSaveStruct	LocationSave[ _MAX_LOCATION_SAVE_COUNT_ ];	//記錄的傳送點
	float				GoodEvil;							//善惡值
	float				GoodEvilBonus;						//可增加的善惡值點數
	int					VocCount;							//最多可以學會幾個職業
	int					BoxEnergy;							//月光寶盒能量

	int					MedalCount;							//教導點數
	int					Money_Bonus;

	//交易暫存欄位(當物品要給予玩家時，先放置於暫存欄位中)
	StaticVector< ItemFieldStruct , _MAX_TEMP_COUNT_ > ItemTemp;	

	//重生相關資訊
	RaiseInfoStruct		RaiseInfo;

	int					LockAccountTime;											//帳號幣鎖定 0 代表的時間(NowTime)
	int					LockAccountMoney[ Def_AccountMoneyLockTime_Max_Count_ ];	//每天鎖定
	int					LockAccountMoney_Forever;									//永久鎖的金錢

	RolePetStruct		Pet;

	float				Honor;
	float				HonorWorth;

	int					LastBeHonorKilledTime;										// 上次被榮譽擊殺的時間
	int					MaxPlantCount;						//最多可種植的數量

	struct  
	{
		float		MoneyTraderCount;
		float		AutoBotCount;
		int			BotReportDBID;			//舉報者
		int			BotReportTime;			//最後一次舉報時間
		int			BotReportProtectTime;	//舉保護時間

	}Defendant;	//被告
	InstanceSettingStruct	InstanceSetting;
	int					RoomKey;
	SuitSkillStruct		SuitSkill;

	int					ClinetSetting[_MAX_CLIENT_SETTING_SIZE_];
	
	VipMemberStruct		VipMember;


	CoolSuitBase		CoolSuitList[ _DEF_MAX_COOL_SUIT_COUNT_ ];
	//StaticVector< int , _DEF_MAX_COOL_CLOTH_COUNT_ > CoolClothList;	
	int					CoolClothList[ _DEF_MAX_COOL_CLOTH_COUNT_ ];
	int					Reserver001;
	int					CoolSuitID;	//目前顯示的套裝資料

	StaticVector< int , _DEF_MAX_PET_EXBAG_COUNT_ > PetExBag;	
	StaticVector< HorseExBagBase , _DEF_MAX_HORSE_EXBAG_COUNT_ > HorseExBag;	

	int					IncursivePoint;
	TitleSysStruct		TitleSys;
//	int					ZoneKey;		//進入區域設定的Key
	SlotMachineInfo		SlotMachine;

	int					DuelistReward;				//勇士勳章
	StaticFlag<_MAX_PET_CARD_COUNT_>	PetCard;	//卡片

	//新增特殊貨幣
	int					TrialBadgeCoin;			//試煉徽章
	int					RelicsCoin;				//古代遺物
	int					DreamlandCoin;			//夢境先遣印記
	int					PhiriusShellCoin;		//必爾汀圓貝
	int					EnergyJusticeCoin;		//正義能量
	int					ProofLegendCoin;		//傳說之證
	int					MirrorCoin;				//鏡幻徽印
	
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
	RoleValueData			Attr;						//角色數值資料

    SysManageInfoStruct     Sys;                        //系統管理相關資訊
	PathProcStruct			Move;						//移動資訊

	NPC_AI_Struct			AI; 						//AI處理

	NPCHateList				NPCHate;					//怪物被打到的資訊(給怪物AI使用)

	RoleUpdateEvent			UpdateInfo;					//更新資訊

	MagicProcInfo			Magic;						//施法資訊

    NPC_RandomMoveStruct    RandomMove;                 //亂數移動資訊


	float					BoundRadiusX;				//基本模型大小
	float					BoundRadiusY;				//基本模型大小

    //---------------------------------------------------------------------------------------
    int                     AroundPlayer;               //周圍大約玩家數量
	//---------------------------------------------------------------------------------------

	//Server端劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> RangePlot;			//範圍劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> TouchPlot;			//處發劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> DeadPlot;			//死亡劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> SayPlot;			//範圍說話劇情
    StaticString< _MAX_LUA_FUNTIONNAMESIZE_> GiveItemPlot;		//給予處發劇情 ( PCall ) bool GiveItemPlot( int Item1 , int Item2 , int Item3 , int Item4 )
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> CollisionPlot;		//碰撞劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> CheckPetCommand;	//寵物檢察劇情

    int                     TouchPlot_Range;
    int                     RangePlot_Range;
	int						OnDeadMagic;				//死亡觸發的法術
	//---------------------------------------------------------------------------------------
	//Client自動劇情
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> C_AutoPlot;//Client 端的自動劇情
	//---------------------------------------------------------------------------------------
    int                     CliActionID;                //Cli端動態ID 進入試野會送出
    //---------------------------------------------------------------------------------------

    StaticString<_MAX_ACCOUNT_SIZE_>     CreateAccount;  //建立此物件的帳號


    RoleBackupInfo          BackInfo;                   //貝份資訊用來更新Client 或狀態處理

    ShopStateStruct         ShopInfo;                   //商店資訊

//	SummonPetTypeENUM		PetType;					//招喚類型
  //  PetStruct				SummonPet[EM_SummonPetType_Max];	//招出來的寵物
	SummonPetInfoStruct		SummonPet;

	int						iGatherNumber;				// 若是採集物件的話, 能被採集數量	

	unsigned				iDelayPatrol;				// 延遲巡邏劇情

	int						iMinimapIcon;				// 在小地圖上顯像的 ICON 代號
	//---------------------------------------------------------------------------------------
	int						iQuestStatus;				// 目前

	ScriptBorderStruct		ScriptBorder;				// 石碑介面


	int						IdleMotionID;

	ScriptEventFlagStruct	CheckEvent;					// 特殊事件檢查

	//---------------------------------------------------------------------------------------
	//換獨立Zone時所需設定的資料
	//---------------------------------------------------------------------------------------	
	ChangeZoneInfoStruct	ChangeZoneInfo;

	int						SkillComboID;
	int						SkillComboTime;				//成立Combo的時間
	int						SkillComboPower;
	int						CursorType;					// Client 端游標類型

	union
	{
		int						CrystalID;					// NPC 所帶表下標公會戰, 或戰場的 ID
		int						BattleGroundZoneID;			// NPC 代表那個戰場
		int						BattleGroundTeamID;			// PLAYER 所屬的戰場隊伍

	};

	//---------------------------------------------------------------------------------
	bool					IsDisabledChangeZone;
	//---------------------------------------------------------------------------------
	int						Register[_MAX_REGISTER_COUNT_];	//暫存值
	//---------------------------------------------------------------------------------
	int						MagicToolsColdown;			//下次可使用魔法物品時間
	int						PlayerClsHateColdown;		//玩家清除仇恨列表Coldown

	GuildBuildingTypeENUM		GuildBuildingType;
	union
	{
		int						GuildBuildingDBID;		//公會建築的DBID
		int						GuildFurnitureDBID;		//

	};

	int						PingCount;					//用來檢測Client 是否有加速


	

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

	bool		IsPKDead_NotGuilty;					//惡意PK死


	//效用遞減處理
	struct
	{
		int		Time;
		int		Count;
	}BuffTimeDesc[_MAX_BuffTimeDesc_COUNT_];

	ClientStateStruct		CliState;				//Client 一些狀態資料
	int				DeadZoneCountDown;
	float			ZoneDamgeRate;
	ZoneTypeENUM	ZoneType;

	int			LastDHp;							//最後一次HP變化
	int			LastDHpTarget;						//最後一次HP變化的目標
	TradeStruct	Trade;

	int				iWorldID;						//人物所屬的 WorldID
	int				AttachObjID;					//連結物件
	int				AttachPos;						//連結的位置
	
	ItemFieldStruct PotInfo;						//盆子的資訊

	int				iLockGUID;
	int				iLockTime;
	float			ModelRate;

	//////////////////////////////////////////////////////////////////////////
	int				LockHP;					//鎖定血量點
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> LockHPEvent;	
	//////////////////////////////////////////////////////////////////////////
	int				SoulPoint;				//靈魂值
	//////////////////////////////////////////////////////////////////////////
	LuaHideInfoStruct HideInfo;


	TempRoleData( ) { Init(); };
	void	Init();
};

struct PlayerTempRoleData
{
	PlayerActionLogStruct	Log;						//每10分鐘or 換區時 計錄一次 
	SkillStruct				Skill;                      //技能法術資訊
	CastingData				CastData;
	//拍賣物品貝份
	StaticVector< SellItemFieldStruct , _MAX_SELL_ITEM_SAVE_COUNT_ >	SellItemBackup;

	// 對話選項暫存
	SpeakStruct				SpeakInfo;

	// 劇情執行
	ScriptStruct			ScriptInfo;

	PKInfoStruct			PKInfo;						//pk資訊

	int						DialogSelectID;				//玩家所選的Dialog 的ID( -2 代表等代選則 ， -1 代表取消 )

	CastingTypeENUM			CastingType;				//一般的Casting
	int						CastingTime;				//Casting完成時間
	int						CastingItemID;				//Casting的目標物件

	//被動技能
	StaticVector< int , _MAX_PASSIVESKILL_COUNT_ >						PassiveSkill;
	StaticVector< int , _MAX_PASSIVESKILL_COUNT_ >						PassiveSkillLv;

	//---------------------------------------------------------------------------------
	//		角色回傳位置
	//---------------------------------------------------------------------------------
	int						ParallelZoneID;				//平行空間的ID
	//---------------------------------------------------------------------------------
	//		參關方屋號碼
	//---------------------------------------------------------------------------------
	union
	{
		int						VisitHouseDBID;	
		int						VisitGuildID;	
	};
	BattleGroundInfoStruct	BGInfo;						// 戰場處理資訊

	ChangeWorldStruct		ChangeWorld;

	LuaPlotClockStruct		LuaClock;

	int						LockAccountMoney;

	//各個需檢查的封包權值( 每分扣1點權值 )
	float					PacketCheckPoint[ EM_ClientPacketCheckType_Max ];

	float					TempTpDexp;					//暫存Tp 未配制的點數	

	MineCheckStruct			MineCheck;					//挖礦檢查

	StaticVector< int , _MAX_PK_DEAD_SAVE_COUNT_ > PKDeadTime;

	int                     LoginTempID;                //記錄登入時檢查是否登入的的排程ID

	StructArenaInfo			Arena[3];					// Arena Info

	GambleItemStateStruct	GambleItemState;			//屬性賭博資料

	SendPacketModeStruct	SendPGMode;
	int						LastSendMovePG;
	int						PartyLootOrder;				//Party輪流檢寶序號
	int						ChangeZoneCountDown;		//如果有使用物品 延遲換區
	StaticVector< ExSkillBaseStruct , _MAX_EX_SKILL_COUNT_ >	ExSkill; //劇情設定額外可以使用的法術

	//兌換魔石資料
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
//換區不會存的資料
struct DynamicRoleData	
{
	//寶相資料
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
	int			                        CharField;          //此帳號的第幾個角色資料
	int					                DBID;				//資料庫ID
	StaticString<_MAX_ACCOUNT_SIZE_>    Account_ID;	        //帳號名稱
	StaticString<_MAX_CREATETIME_SIZE_> CreateTime;	        //此物件產生的日期
	unsigned							LogoutTime;			//登出的系統時間	
	StaticFlag< _ACCOUNT_FLAG_COUNT_ >	AccountFlag;		//帳號資料旗標
};


struct	RoleData
{
	static PlayerSelfRoleData gPlayerSelfData;
	//static PlayerBaseRoleData gPlayerBaseData;
	static PlayerTempRoleData gPlayerTempData;
	static void GlobalInit();

    SysBaseRoleData Base;
	SelfRoleData	SelfData;								//LocalServer 專用
	BaseRoleData	BaseData;								//Client 與 Server 會用到
	TempRoleData	TempData;								//ClientServer 處理角色的暫存便數
	DynamicRoleData	DynamicData;							//動態資料，不會換區
	//////////////////////////////////////////////////////////////////////////
	//只有玩家會用到的資料
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

		toRole->SelfData = fromRole->SelfData;			//LocalServer 專用
		toRole->BaseData = fromRole->BaseData;			//Client 與 Server 會用到
		toRole->TempData = fromRole->TempData;			//ClientServer 處理角色的暫存便數
		toRole->DynamicData.Init();						//動態資料，不會換區
		//////////////////////////////////////////////////////////////////////////
		//只有玩家會用到的資料
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
		DynamicData.Init();							//動態資料，不會換區
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
	//只有玩家會用到的資料
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
		SelfData = In.SelfData;			//LocalServer 專用
		BaseData = In.BaseData;			//Client 與 Server 會用到
		TempData = In.TempData;			//ClientServer 處理角色的暫存便數
		DynamicData.Init();				//動態資料，不會換區
		//////////////////////////////////////////////////////////////////////////
		//只有玩家會用到的資料
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
// 選角色資料
//--------------------------------------------------------------------------------------------------------
struct SampleRoleData
{
	int									DBID;
	StaticString<_MAX_NAMERECORD_SIZE_> RoleName;
	StaticString<_MAX_ZONENAME_SIZE_>   ZoneName;		//地圖名稱

	int						OrgObjID;					//物件原始ID
	int						Level;
	int                 	Level_Sub;					//副職等級()

	//顯像資料
	Sex_ENUM				Sex;						//性別
	Race_ENUM				Race;						//種族
    Voc_ENUM            	Voc;
	Voc_ENUM   				Voc_Sub;
	//float					BoneScale[10];
	char					BoneScale[15];

	int						iHairColor;			
	int						iBodyColor;			
	int						iFaceID;			
	int						iHairID;			

	EQStruct				EQ;							//裝備資料
	int						DestroyTime;				//多久後刪除

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
// npc 需要除存的資料
//--------------------------------------------------------------------------------------------------------
struct NPCData
{ 
	int                                     DBID;
	int					                    OrgObjID;		//物品樣板ID(顯像資料)
	StaticString<_MAX_CREATETIME_SIZE_>	    CreateTime;		//此物件產生的日期	
	ObjectModeStruct	                    Mode;			//物件基本設定
	StaticString<_MAX_NAMERECORD_SIZE_>     RoleName;	    //角色名稱
    int					                    ZoneID;			//目前區域編號
    RolePosStruct                           Pos;
    int                                     LiveTime;
    int                                     OwnerDBID;
    int                                     PID;            //企畫設定的ID用來搜尋執行劇情
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_> PlotClassName;	//屬於哪一個劇情使用
	StaticString<_MAX_LUA_FUNTIONNAMESIZE_> AutoPlot;	    //自動   
	int										QuestID;
    StaticString<_MAX_ACCOUNT_SIZE_>		CreateAccount;	//角色名稱
	float									vX , vY , vZ;	//角色面向
	int										RoomID;
};
//--------------------------------------------------------------------------------------------------------
#endif