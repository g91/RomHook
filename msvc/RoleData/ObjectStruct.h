//----------------------------------------------------------------------------------------
//			遊戲所有物件基本資料
//----------------------------------------------------------------------------------------
#ifndef	__OBJECTSTRUCT_H_2003_09_16__
#define __OBJECTSTRUCT_H_2003_09_16__
#pragma		warning (disable:4819)
#include	<windows.h>

//版本
#define		_DEF_VERSION	"v0.20"


#define		_MAX_NPC_QUEST_COUNT_			20			// NPC 最多能給的任務
#define		_MAX_QUEST_COUNT_				30			// 角色最多可以接的 Quest 數量

#define		_MAX_QUEST_FLAG_COUNT_			8192		// 角色目前完成 Quest 的數量, 目前最多設定 2048
#define		_MAX_QUEST_KILLKIND_COUNT_		5			// 每一個 Quest 指定打倒目標的種類
#define		_MAX_QUEST_CLICKIND_COUNT_		5


//----------------------------------------------------------------------------------------
#define		_MAX_OBJ_NAME_STR_SIZE_		    32			//名字字串長度定義
#define		_MAX_NPC_DROPITEM_COUNT_		5			//定義物品最多掉落種類數量
#define		_MAX_SKILL_COUNT_				30			//最多多少數值技能(熟練度)
#define		_MAX_RACE_COUNT_			    32			//32個種族數量
#define		_MAX_VOCATION_COUNT_		    32			//32個職業
#define		_MAX_SEX_COUNT_		            5			//性別數量
#define		_MAX_FILENAME_SIZE_		        128			//檔案名稱
#define     _MAX_LEVEL_                     200         //最高等級
#define     _MAX_DROPITEM_COUNT_            15          //最多怪物可掉物品數量
#define     _MAX_DROP_ABILITY_COUNT_        6           //掉落物品最多有給個附加屬性
#define     _MAX_NPC_EQSEL_COUNT_           5           //怪物可選的武器最大量
#define     _MAX_SPSkill_COUNT_             200          //最大職業專屬技能
#define     _MAX_NormalSkill_COUNT_         50          //最大一般職業技能

#define     _MAX_EQ_Skill_COUNT_		    20          //其它的技能
#define     _MAX_Lua_Skill_COUNT_			20          //其它的技能


#define     _MAX_Edit_SPSkill_COUNT_        200         //最大職業專屬技能
#define     _MAX_Edit_NormalSkill_COUNT_    300         //最大一般職業技能


#define     _MAX_PASSIVESKILL_COUNT_        30          //最多同時有多少個被動技能
#define     _MAX_SELL_ITEM_SAVE_COUNT_      10          //拍賣物品貝份最大量

#define     _MAX_SKILLVALUE_BASETYPE        20          //基本武器熟練度的分種總類 (s+ s s- ..... )
#define     _MAX_SKILLVALUE_TYPE            30          //基本武器熟練度的種類

#define		_MAX_QUESTLINK_COUNT			20			// 每個 NPC 最多和多少個任務有所關連
#define		_MAX_SPEAKOPTION_COUNT_			10
#define		_MAX_SCRIPTBORDER_PAGE_			20			// 石碑介面最多頁數
#define		_MAX_PET_SKILL_COUNT_			20			//寵物最多會幾個技能
//----------------------------------------------------------------------------------------
#define		_TABLE_BASE_VOCTABLE_			1000
#define		_TABLE_BASE_SEXTABLE_			2000
#define		_TABLE_BASE_FIXTABLE_			3000
//#define		_TABLE_BASE_VOCTABLE_			4000
#define		_TABLE_BASE_SKILLBASETABLE_		5000
#define		_TABLE_BASE_JOBSKILLTABLE_		6000
#define		_TABLE_BASE_JOBEQSKILLTABLE_	7000
#define		_TABLE_BASE_WEAPONARGTABLE_		8000
#define		_TABLE_BASE_ARMORARGTABLE_		9000
#define		_TABLE_BASE_BASEMAGICTABLE_		10000
//#define		_TABLE_BASE_RESISTARGTABLE_		11000

#define		_TABLE_BASE_EXPTABLE_			13000
//#define		_TABLE_BASE_EQREFINETABLE_		14000
#define		_TABLE_BASE_CREATEROLETABLE_	15000
//#define		_TABLE_BASE_DISSOLUTIONTABLE_	16000
#define		_TABLE_BASE_COMBOTABLETABLE_	17000
#define		_TABLE_BASE_MOTIONTABLE_		18000
#define		_TABLE_BASE_TEACHTABLE_			20000
#define		_TABLE_BASE_COLORINGSHOPTABLE_	21000
#define		_TABLE_BASE_WORLDMAPINFO_		22000
#define		_TABLE_BASE_GUILDLVINFO_		23000
#define		_TABLE_BASE_ACCOUNTSHOPINFO_	24000
//#define		_TABLE_BASE_SYSCOLORDEFINE_		25000
#define		_TABLE_BASE_SYSKEYFUNCTION_		26000
#define		_TABLE_BASE_LOTTERYINFO_		27000
#define		_TABLE_BASE_SYSKEYVALUE_		28000
#define		_TABLE_BASE_INHERENTRATE_		29000
#define		_TABLE_BASE_HOUSESHOPINFO_		30000
#define		_TABLE_BASE_HOUSEENERGRYCOST_	31000
#define		_TABLE_BASE_POWERRATE_			32000
#define		_TABLE_BASE_RENTFUNCTION_		33000
#define		_TABLE_BASE_GUIDFLAGTABLE_		34000
#define		_TABLE_BASE_MAPPOINT_			35000
#define		_TABLE_BASE_RELATIONMAGIC_		36000
#define		_TABLE_BASE_RUNEEXCHANGE_		37000
#define		_TABLE_BASE_GUIDBUILDING_		38000
#define		_TABLE_BASE_GUIDBASEBUILDING_	39000
#define		_TABLE_BASE_GUIDHOUSEITEMPAGE_	40000

#define		_TABLE_BASE_CULTIVATE_PET_BASE_			41000
#define		_TABLE_BASE_CULTIVATE_PET_LEARNMAGIC_	42000
#define		_TABLE_BASE_CULTIVATE_PET_LIFESKILL_	43000
//#define		_TABLE_BASE_CULTIVATE_PET_EVENT_		42000
//#define		_TABLE_BASE_CULTIVATE_PET_GROW_			43000
//#define		_TABLE_BASE_CULTIVATE_PET_TALK_			44000
//#define		_TABLE_BASE_CULTIVATE_PET_VALUE_EFFECT_	45000

#define		_TABLE_BASE_PLANT_GROW_ACTION_			46000
#define		_TABLE_BASE_PLANT_PRODUCT_				47000
#define		_TABLE_BASE_PLANT_GAMBLEITEMSTATE_		48000

#define		_TABLE_BASE_SERVANT_EVENT_				49000
#define		_TABLE_BASE_SERVANT_HIRE_				50000
#define		_TABLE_BASE_SERVANT_STRATVALUE_			51000
#define		_TABLE_BASE_ITEM_COMBINE_				52000
#define		_TABLE_BASE_LIFESKILL_RARE_EX_			53000
#define		_TABLE_BASE_GUILDHOUSE_NPC_REPLACE		54000
#define		_TABLE_BASE_GUILDHOUSE_NPC_REPLACE_COST	55000
#define		_TABLE_BASE_RUNESYSTEM_EVENT_			56000
#define		_TABLE_BASE_PETCOLLECTION_				57000
#define		_TABLE_BASE_ABIPARAMETER_				58000
#define		_TABLE_BASE_PHANTOMRANK_				59000
#define		_TABLE_BASE_PHANTOMLV_					60000
#define		_TABLE_BASE_PHANTOMSKILL_				61000
//----------------------------------------------------------------------------------------
#define Def_ObjectClass_Player				1000		// 玩家物件
#define Def_ObjectClass_BodyObj				2000		// 身體物件
#define Def_ObjectClass_NPC					100000		// NPC
#define Def_ObjectClass_QuestNPC			110000		// QuestNPC ( 110000-119999 )
#define Def_ObjectClass_Item				200000		// 物品(200000) 裝備 武器 金錢 
#define Def_ObjectClass_Weapon				210000		// 武器
#define Def_ObjectClass_Armor				220000		// 防具
#define Def_ObjectClass_Phantom				250000		// 幻靈
#define Def_ObjectClass_Table				300000		// 
#define Def_ObjectClass_QuestCollect		400000		// ( 20000  ) 能給予 Quest 的 NPC 代號
#define Def_ObjectClass_QuestDetail			420000		// ( 200000 ) Quest
#define Def_ObjectClass_MagicCollect		490000		// 法術集合資料
#define Def_ObjectClass_Magic				500000		// 法術資料
#define Def_ObjectClass_Attribute   		510000		// 附加能力
#define Def_ObjectClass_Rune           		520000		// 符文
#define Def_ObjectClass_Title          		530000		// 頭銜
#define Def_ObjectClass_KeyItem        		540000		// Key Item
#define Def_ObjectClass_KeyItemEx      		640000		// Key Item
#define Def_ObjectClass_Recipe        		550000		// 配方表
#define Def_ObjectClass_Mine          		560000		// 礦產
#define Def_ObjectClass_Image          		570000		// 圖形
//#define Def_ObjectClass_Flag          		580000		// 旗子
#define Def_ObjectClass_LearnMagic          590000		// 法術學習表
#define Def_ObjectClass_Shop                600000		// 商店資訊
#define Def_ObjectClass_Suit                610000		// 套裝資訊
#define Def_ObjectClass_MagicEx             620000		// 法術資料 擴充
#define Def_ObjectClass_LuaScript           700000		// lua劇情物件
#define Def_ObjectClass_Camp	            710000		// 陣營資訊
#define Def_ObjectClass_Treasure            720000		// 寶物掉落表
#define Def_ObjectClass_CliLuaScript        730000		// lua劇情物件
#define Def_ObjectClass_EqRefineAbility     740000		// 衝等能力
#define Def_ObjectClass_Zone			    750000		// 區域設定資訊
#define Def_ObjectClass_CreateRole		    760000		// 建角物件
#define Def_ObjectClass_Card				770000		// 卡片
#define Def_ObjectClass_Flag          		780000		// 旗子
#define Def_ObjectClass_PE          		790000		// 公眾任務 (790000 - 899999) PE : 790000 -791999 PH : 792000 - 809999, OB : 810000 - 854999, VAR : 855000 - 899999
#define Def_ObjectClass_ImageEx        		800000		// 圖形
#define Def_ObjectClass_MagicCollectEx		850000		// 法術集合資料
#define Def_ObjectClass_Item_Total			100000
#define Def_ObjectClass_QuestDetail_Total	 70000
#define Def_ObjectClass_QuestNPC_Total		 20000		// QuestNPC
#define Def_ObjectClass_KeyItem_Total		 10000
#define Def_ObjectClass_Recipe_Total		 10000
//----------------------------------------------------------------------------------------
// Quest 相關
//----------------------------------------------------------------------------------------
#define _MAX_SIZE_QUEST_NAME				32
#define _MAX_SIZE_QUEST_DESC				256
#define _MAX_SIZE_QUEST_ACCEPT_DETAIL		1200
#define _MAX_SIZE_QUEST_UNCOMPLETE_DETAIL	400
#define _MAX_SIZE_QUEST_COMPLETE_DETAIL		1200
#define _MAX_SIZE_QUEST_NPC_TEXT			512
#define _MAX_SIZE_QUEST_CATALOG				32
#define _MAX_SIZE_QUEST_TYPE				8
#define _MAX_SIZE_QUEST_FLAG				3
#define _MAX_SIZE_QUEST_ITEM				5
#define _MAX_SIZE_QUEST_CONDITION			10
#define _MAX_SIZE_QUEST_SCRIPT				32
#define _MAX_SIZE64_QUEST_SCRIPT			64
//----------------------------------------------------------------------------------------
//AC 物品搜尋分類定意
//----------------------------------------------------------------------------------------
#define _DEF_ACSEARCHTYPE_EMPTY				-1

#define _DEF_ACSEARCHTYPE_WEAPON			0
#define _DEF_ACSEARCHTYPE_ARMOR				1
#define _DEF_ACSEARCHTYPE_SUPPLIES			2
#define _DEF_ACSEARCHTYPE_STUFF				3
#define _DEF_ACSEARCHTYPE_RECIPE			4
#define _DEF_ACSEARCHTYPE_POWERUP			5
#define _DEF_ACSEARCHTYPE_CARD				6
#define _DEF_ACSEARCHTYPE_RIDE				7
#define _DEF_ACSEARCHTYPE_HOUSE				8
#define _DEF_ACSEARCHTYPE_SPECIAL			9
#define _DEF_ACSEARCHTYPE_COLLECTION		10
#define _DEF_ACSEARCHTYPE_OTHER				11
#define _DEF_ACSEARCHTYPE_MONEY				12

#define _DEF_ACSEARCHTYPE_WEAPON_SWORD		0
#define _DEF_ACSEARCHTYPE_WEAPON_AXE		1
#define _DEF_ACSEARCHTYPE_WEAPON_HAMMER		2
#define _DEF_ACSEARCHTYPE_WEAPON_DAGGER		3
#define _DEF_ACSEARCHTYPE_WEAPON_STAFF		4
#define _DEF_ACSEARCHTYPE_WEAPON_LONGWEAPON	5
#define _DEF_ACSEARCHTYPE_WEAPON_THROW		6
#define _DEF_ACSEARCHTYPE_WEAPON_OTHER		7

#define _DEF_ACSEARCHTYPE_WEAPON_X_ONEHAND	0
#define _DEF_ACSEARCHTYPE_WEAPON_X_TWOEHAND	1

#define _DEF_ACSEARCHTYPE_WEAPON_X_BOW		0
#define _DEF_ACSEARCHTYPE_WEAPON_X_COSSBOW	1
#define _DEF_ACSEARCHTYPE_WEAPON_X_AMMO		2

#define _DEF_ACSEARCHTYPE_ARMOR_HEAVYARMED	0
#define _DEF_ACSEARCHTYPE_ARMOR_LIGHTARMED	1
#define _DEF_ACSEARCHTYPE_ARMOR_LEATHER		2
#define _DEF_ACSEARCHTYPE_ARMOR_CLOTHES		3
#define _DEF_ACSEARCHTYPE_ARMOR_ROBE		3
#define _DEF_ACSEARCHTYPE_ARMOR_DRESS		4
#define _DEF_ACSEARCHTYPE_ARMOR_SECONDHAND	5
#define _DEF_ACSEARCHTYPE_ARMOR_MAGICTOOL	6
#define _DEF_ACSEARCHTYPE_ARMOR_ORNAMENT	7

#define _DEF_ACSEARCHTYPE_ARMOR_X_HEAD		0
#define _DEF_ACSEARCHTYPE_ARMOR_X_CLOTHES	1
#define _DEF_ACSEARCHTYPE_ARMOR_X_BELT		2
#define _DEF_ACSEARCHTYPE_ARMOR_X_PANTS		3
#define _DEF_ACSEARCHTYPE_ARMOR_X_GLOVES	4
#define _DEF_ACSEARCHTYPE_ARMOR_X_SHOES		5
#define _DEF_ACSEARCHTYPE_ARMOR_X_BACK		6
#define _DEF_ACSEARCHTYPE_ARMOR_X_SHOULDER	7

#define _DEF_ACSEARCHTYPE_ARMOR_DRESS_EARRING	0
#define _DEF_ACSEARCHTYPE_ARMOR_DRESS_RING		1
#define _DEF_ACSEARCHTYPE_ARMOR_DRESS_NECKLACE	2

#define _DEF_ACSEARCHTYPE_ARMOR_SECONDHAND_SHIELD		0
#define _DEF_ACSEARCHTYPE_ARMOR_SECONDHAND_IMPLEMENT	1


#define _DEF_ACSEARCHTYPE_STUFF_MINE			0		
#define _DEF_ACSEARCHTYPE_STUFF_WOOD			1
#define _DEF_ACSEARCHTYPE_STUFF_HERB			2
#define _DEF_ACSEARCHTYPE_STUFF_FOOD			3
#define _DEF_ACSEARCHTYPE_STUFF_MANUFACTIRERUNE	4
#define _DEF_ACSEARCHTYPE_STUFF_OTHERSTUFF		5

#define _DEF_ACSEARCHTYPE_SUPPLIES_FOOD			0	
#define _DEF_ACSEARCHTYPE_SUPPLIES_SWEETFOOD	1
#define _DEF_ACSEARCHTYPE_SUPPLIES_MEDICINE		2

#define _DEF_ACSEARCHTYPE_RECIPE_BLACKSMITH		0
#define _DEF_ACSEARCHTYPE_RECIPE_CARPENTER		1
#define _DEF_ACSEARCHTYPE_RECIPE_ARMOR			2
#define _DEF_ACSEARCHTYPE_RECIPE_TAILOR			3
#define _DEF_ACSEARCHTYPE_RECIPE_ALCHEMY		4
#define _DEF_ACSEARCHTYPE_RECIPE_COOK			5

#define _DEF_ACSEARCHTYPE_RUNE_MANUFACTURE	0
#define _DEF_ACSEARCHTYPE_RUNE_WEAPON		1
#define _DEF_ACSEARCHTYPE_RUNE_HEAD			2
#define _DEF_ACSEARCHTYPE_RUNE_BODY			3
#define _DEF_ACSEARCHTYPE_RUNE_PANT			4
#define _DEF_ACSEARCHTYPE_RUNE_SPECIAL		5
#define _DEF_ACSEARCHTYPE_RUNE_ARMOR		6
#define _DEF_ACSEARCHTYPE_RUNE_ORNAMENT		7
#define _DEF_ACSEARCHTYPE_RUNE_SHIELD		8
#define _DEF_ACSEARCHTYPE_RUNE_MAGICTOOLS	9

#define _DEF_ACSEARCHTYPE_POWERUP_REFINE		0	
#define _DEF_ACSEARCHTYPE_POWERUP_RUNE			1	
#define _DEF_ACSEARCHTYPE_POWERUP_SMELTSTONE	2	

#define _DEF_ACSEARCHTYPE_HOUSE_CONTRACT	0
#define _DEF_ACSEARCHTYPE_HOUSE_FURNITURE	1
#define _DEF_ACSEARCHTYPE_HOUSE_STUDY		2

#define _DEF_ACSEARCHTYPE_MONEY_GAMEMONEY		0
#define _DEF_ACSEARCHTYPE_MONEY_ACCOUNTMONEY	1
#define _DEF_ACSEARCHTYPE_MONEY_BONUSMONEY		2
//----------------------------------------------------------------------------------------
//特別系統使用的物品
#define _DEF_ITEMID_MONEY_		200000
#define _DEF_ITEMID_LOTTERY_	200001
//----------------------------------------------------------------------------------------
enum    YesNoENUM
{    
	EM_No       ,
	EM_Yes      ,
	EM_Unknow   ,
};
//-----------------------------------------------------------------------------
enum PriceTypeENUM
{
	EM_ACPriceType_None			= -1,
	EM_ACPriceType_GameMoney		,		//遊戲幣
	EM_ACPriceType_AccountMoney		,		//帳號幣
	EM_ACPriceType_BonusMoney		,		//紅利幣
	EM_ACPriceType_Phirius			,		//必耳丁
	EM_ACPriceType_Honor			,		//戰場榮譽
	EM_ACPriceType_Arena			,		//競技場點數(Arena)
	EM_ACPriceType_GuildWarEnergy	,		//公會戰能量
	EM_ACPriceType_GuildWarHonor	,		//公會戰戰績
	EM_ACPriceType_TrialBadge 		,		//試煉徽章
	EM_ACPriceType_Relics 			,		//古代遺物
	EM_ACPriceType_Dreamland		,		//夢境先遣印記
	EM_ACPriceType_PhiriusShell		,		//必爾汀圓貝
	EM_ACPriceType_EnergyJustice	,		//正義能量
	EM_ACPriceType_ProofLegend		,		//傳說之證
	EM_ACPriceType_DuelistReward	,		//勇士勳章
	EM_ACPriceType_MirrorCoin		,		//鏡幻徽印

};
//-----------------------------------------------------------------------------
enum BaseMagicTypeENUM
{
	EM_BaseMagic_Unbeatable			,
	EM_BaseMagic_Slow				,
	EM_BaseMagic_ReviveWeak			,		//重生衰弱
	EM_BaseMagic_NoSearchEnemy		,		//重生不索敵
	EM_BaseMagic_PlayerUnbeatable	,		//玩家重生時無敵
	EM_BaseMagic_Guilty				,
	EM_BaseMagic_PKDead1			,
	EM_BaseMagic_PKDead2			,
	EM_BaseMagic_PKDead3			,
	EM_BaseMagic_PKHunter			,
	EM_BaseMagic_Reserve5			,
	EM_BaseMagic_Reserve6			,
	EM_BaseMagic_Reserve7			,
	EM_BaseMagic_Reserve8			,
	EM_BaseMagic_Reserve9			,
	EM_BaseMagic_Reserve10			,

	EM_BaseMagic_MaxCount		,
};
//////////////////////////////////////////////////////////////////////////
enum RelationTypeENUM
{
	EM_RelationType_None	= -1,	//無關係
	EM_RelationType_Stranger	,	//莫生人
	EM_RelationType_Friend		,	//好友
	EM_RelationType_Enemy		,	//仇人

	EM_RelationType_Student		,	//學生
	EM_RelationType_Teacher		,	//老師
	EM_RelationType_Wife		,	//妻子
	EM_RelationType_Husband		,	//先生
	EM_RelationType_Lover		,	//情人
	EM_RelationType_Family		,	//親人
	EM_RelationType_BestFriend	,	//摯友
	EM_RelationType_BadCompany	,	//損友

	EM_RelationType_MaxRelation	,
};

//-----------------------------------------------------------------------------
//角色狀態
//----------------------------------------------------------------------------------------
struct	GameObjDbStruct;
typedef union {
	int value;
	struct {
		bool		isUnholster			:1;		// true 取出武器	Script 代碼 1
		bool		isWalk				:1;		// true 走路		Script 代碼 2
		bool		isCombat			:1;		// true 戰鬥中		Script 代碼 4
		bool		isDead				:1;		// true 死亡中		Script 代碼 8
		bool		isSpell				:1;		// true 施法中		Script 代碼 16

		bool		isSit				:1;		// true 坐下		Script 代碼 32
		bool		isSleep				:1;		// true 睡覺
		bool		isCrouch			:1;		// true 蹲下
		bool		isCrafting			:1;		// true 加工
		bool		isSitChair			:1;		// true 坐在椅子上
	};

}RoleSpriteStatus;
//----------------------------------------------------------------------------------------
//遊戲物件類型列舉
//----------------------------------------------------------------------------------------
enum	GameObjectClassificationENUM
{
	EM_ObjectClass_None   = -1      ,
	EM_ObjectClass_Player = 0		,
	EM_ObjectClass_NPC			    ,		// 1	
	EM_ObjectClass_Item			    ,		//物品	裝備 武器 金錢 2
	EM_ObjectClass_MagicBase		,		// 3 
	EM_ObjectClass_BodyObj			,		// 4 
	EM_ObjectClass_Attribute        ,		//復加屬性	
	EM_ObjectClass_QuestCollect     ,
	EM_ObjectClass_QuestDetail      ,		
	EM_ObjectClass_Title            ,		//頭銜
	EM_ObjectClass_KeyItem          ,		//重要物品
	EM_ObjectClass_Recipe           ,		//配方表
	EM_ObjectClass_Mine             ,		//礦產
	EM_ObjectClass_Flag             ,		//旗子資料
	EM_ObjectClass_Image            ,		//圖象資料
	EM_ObjectClass_QuestNPC			,		//任務
	EM_ObjectClass_LearnMagic       ,		//法術學習
	EM_ObjectClass_Shop             ,		//商店
	EM_ObjectClass_Suit             ,		//套裝
	EM_ObjectClass_LuaScript        ,		//劇情
	EM_ObjectClass_Camp		        ,		//陣營
	EM_ObjectClass_Treasure	        ,		//寶箱
	EM_ObjectClass_MagicCollect     ,		//法術集合
	EM_ObjectClass_EqRefineAbility  ,		//裝備精煉表
	EM_ObjectClass_Zone			    ,		//區域
	EM_ObjectClass_CreateRole		,		//建角物件
	EM_ObjectClass_PE				,		//PE樣板
	EM_ObjectClass_Phantom			,		//幻靈

	EM_ObjectClass_Max				,
	EM_GameObjectClassificationEM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//種族列舉
enum	Race_ENUM
{
	EM_Race_None		= -1,
	EM_Race1			= 0,
	EM_Race2			,
	EM_Race3			,
	EM_Race4			,
	EM_Race5			,
	EM_Race_Undead		,
	EM_Race7			,
	EM_Race8			,
	EM_Race9			,
	EM_Race10			,
	EM_Race11			,
	EM_Race12			,
	EM_Race13			,
	EM_Race14			,
	EM_Race15			,
	EM_Race16			,
	EM_Max_Race       ,
	EM_Race_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//性別列舉
enum	Sex_ENUM
{
	EM_Sex_Boy			= 0,
	EM_Sex_Girl			   ,
	EM_Sex_BigMonster  	   ,		//精英
	EM_Sex_King		  	   ,		//王
	EM_Sex_WorldKing	   ,		//世界王
	EM_Sex_Max_Sex         ,
	EM_Sex_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//職業列舉
enum	Voc_ENUM
{
	EM_Vocation_None	    = -1,       		//沒有職業
	EM_Vocation_GameMaster	= 0	,
	EM_Vocation_Warrior			,				// 戰士
	EM_Vocation_Ranger			,				// 遊俠
	EM_Vocation_Rogue			,				// 影行者
	EM_Vocation_Wizard			,				// 法師
	EM_Vocation_Priest			,				// 祭司
	EM_Vocation_Knight			,				// 騎士
	EM_Vocation_RuneDancer		,				// 森林牧者
	EM_Vocation_Druid			,				// 自然神官
	EM_Vocation_Harpsyn			,				// 靈能者
	EM_Vocation_Psyron			,				// 符文工匠
	EM_Vocation_Duelist			,				// 鬥棋士
	EM_Vocation13		,
	EM_Vocation14		,
	EM_Vocation15		,
	EM_Vocation16		,
	EM_Max_Vocation     ,
	EM_Vocation_EM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//陣營類型
//----------------------------------------------------------------------------------------
enum CampID_ENUM
{
	EM_CampID_Unknow	= -1,
	EM_CampID_NewHand		,
	EM_CampID_Good			,
	EM_CampID_Evil			,
	EM_CampID_Monster		,
	EM_CampID_Wagon			,
	EM_CampID_SNPC			,
	EM_CampID_Visitor		,
	EM_CampID_WF_A			,
	EM_CampID_WF_B			,
	EM_CampID_WF_C			,
	EM_CampID_Enemy			,
	EM_CampID_9				,
	EM_CampID_10			,
	EM_CampID_11			,
	EM_CampID_12			,
	EM_CampID_13			,
	EM_CampID_14			,
};
//----------------------------------------------------------------------------------------
//職業旗標
//----------------------------------------------------------------------------------------
struct VocationFlagStruct
{
	union
	{
		int		_Voc;
		struct 
		{
			bool	Voc0		:1;			
			bool	Voc1		:1;
			bool	Voc2		:1;
			bool	Voc3		:1;
			bool	Voc4		:1;
			bool	Voc5		:1;
			bool	Voc6		:1;
			bool	Voc7		:1;
			bool	Voc8		:1;
			bool	Voc9		:1;
			bool	Voc10		:1;
			bool	Voc11		:1;
		};
	};
};
//----------------------------------------------------------------------------------------
//種族旗標
//----------------------------------------------------------------------------------------
struct RaceFlagStruct
{
	union
	{
		int		_Race;
		struct 
		{
			bool	Race0		:1;			
			bool	Race1		:1;
			bool	Race2		:1;
			bool	Race3		:1;
			bool	Race4		:1;
			bool	Race5		:1;
		};
	};
};
//----------------------------------------------------------------------------------------
//性別旗標
struct SexFlagStruct
{
	union
	{
		int		_Sex;
		struct 
		{
			bool	Boy		:1;			
			bool	Girl	:1;
			bool    Unknow  :1;
		};
	};
};
//----------------------------------------------------------------------------------------
// 數質計算參數
//----------------------------------------------------------------------------------------
//固定參數
struct FixFightArgumentStruct
{
	union
	{
		float Arg[ 100 ];
		struct  
		{
			float DmgAtkArg;			//ATK轉DMG比例
			float MDmgMAtkArg;			//MATK轉MDmg比例
			float Crit_DLV;				//致命一擊率 等差影響 
			float DMG_DLV;				//傷害 等差影響 
			float Miss_DLV;				//命中率 等差影響
			float Miss_SecHand;			//副手命中率調整
			float Dmg_SecHand;			//副手攻擊率調整
			float BaseCritHit;			//基本的Critial 機率
			float BaseCritPower;		//基本的Critial 威力
			float BaseMagicCritHit;		//基本的魔法 Critial 機率
			float BaseMagicCritPower;	//基本的魔法 Critial 威力
			
			float Dmg_MagArg;			//物攻技能額外增加( 此參數*DMG)
			float MDmg_MagArg;			//(傷害)魔攻(or加血)技能額外增加( 此參數*MDMG*施法秒數)
			float MDmg_DotArg;			//(傷害)Dot技能額外增加( 此參數*MDMG*施法秒數/dot次數)

			float Dmg_HealArg;			//(治療)加血額外增加( 此參數*MDMG*施法秒數 )
			float Dmg_HealDotArg;		//(治療)Dot技能額外增加( 此參數*MDMG*施法秒數/dot次數)

			float BaseRateArg;			//攻防比底( 致命 格檔 盾檔 )
			float BaseResistArg;		//攻防比底( 抗致命 穿格檔 穿盾檔 )
			float DLvRateArg;			//攻防比等級影響( 致命 格檔 盾檔 )
			float DLvResistArg;			//攻防比等級影響(  抗致命 穿格檔 穿盾檔 )

			float PhyHit_Base;			//物理命中 基底
			float PhyHit_Range;			//物理命中 變化量
			float PhyHit_AgiArg;		//物理命中 Agi影響
			float PhyAvoid_AgiArg;		//物理閃避 Agi影響

			float MagHit_Base;			//法術命中 基底
			float MagHit_Range;			//法術命中 變化量
			float MagHit_MndArg;		//法術命中 Mnd影響
			float MagAvoid_AgiArg;		//法術命中 Agi影響
			float MagAvoid_MndArg;		//法術閃避 Agi影響

			float PhantomRankArg;
			float PhantomLvArg;
		};
		/*
		struct
		{
			float BAbr;
			float AbrArg;
			float DefUnit;
			float MaxAbr;
			float DefDmgRate;
			float HitArg;
			float HitLvArg;
			float BaseHitRate;
			float DogArg;
			float DogLVArg;
			float BaseDogRate;
			float DmgAtkArg;
			float BMagAbr;
			float MagAbrArg;
			float MagUnit;
			float MaxMagAbr;
			float BMagPow;
			float MagPowArg;
			float MagPowUnit;
			float MaxMagPow;
			float Crit_DLV;     //等級差影響 致命一擊率
			float DMG_DLV;      //等級差影響 傷害
			float Miss_DLV;     //等級差影響 命中率
			float Miss_Skill_DLV;	//技能差影響　攻方命中 與 守方閃避 
			float JobExSkillExp;	//job經驗值與 Skill的經驗值的比值
			float Miss_SecHand;		//副手命中下降
			float Dmg_SecHand;		//副手攻擊下降(%)
			float BaseCritHit;			//基本的Critial 機率
			float BaseCritPower;		//基本的Critial 威力
			float BaseMagicCritHit;		//基本的魔法 Critial 機率
			float BaseMagicCritPower;	//基本的魔法 Critial 威力
			float MagAtkDmgArg;			//每一點的MagAtk換算出的傷害力
		};*/
	};

};
//----------------------------------------------------------------------------------------
//由種足職業等級算出來的值
struct FightArgumentStruct
{
	union
	{
		float Arg[ 100 ];
		struct
		{
			float BStrLv1 , BStaLv1 ,BIntLv1    ,BMndLv1 , BAgiLv1 , BHpLv1  ,BMpLv1 ;
			float BStrArg , BStaArg ,BIntArg    ,BMndArg , BAgiArg , BHpArg  ,BMpArg ;
			float StrArg  , StaArg  ,IntArg     ,MndArg;
			float AgiArg        ,HPArg      ,MPArg      ,HpStrArg   ,HpStaArg   ,MPIntArg;
			float MpMndArg      ,AtkStrArg  ,AtkIntArg  ,AtkAgiArg  ,DefArg;
			float BaseReHP      ,BaseReMP   ,ReHpArg    ,ReMpArg    ,MAtkArg;
			float MDefArg ;
			float BaseMoveSpeed;
			float ReSPNormal_Move , ReSPNormal_Stop , ReSPAttack , ReSPUnderAttack;
			float ReSPAttackTime_Move , ReSPAttackTime_Stop ;
			float MaxSP , DmgRate;
		};
	};
};
//----------------------------------------------------------------------------------------
//抗性表基本結構
//----------------------------------------------------------------------------------------
enum	ResistArgType_ENUM
{
	EM_ResistArgType_Power0		,
	EM_ResistArgType_Power25	,
	EM_ResistArgType_Power50	,
	EM_ResistArgType_Power75	,
	EM_ResistArgType_Power100	,

	EM_ResistArgType_Power_MaxCount,
};

struct ResistArgumentStruct
{
	int		Resist;
	union
	{
		int		PowerList[ EM_ResistArgType_Power_MaxCount ];
		struct  
		{
			int		Power0;			//抗100%
			int		Power25;		//抗75%
			int		Power50;		//抗50%
			int		Power75;		//抗25%
			int		Power100;		//完全承受
		};
	};
};
//-------------------------------------------------------------------------------------
//公會資源
struct GuildResourceStruct
{
	union
	{
		int		_Value[7];		
		struct
		{
			int		Gold;
			int		BonusGold;
			int		Mine;
			int		Wood;
			int		Herb;
			int		GuildRune;
			int		GuildStone;
		};
	};

	bool IsEmpty()
	{
		for( int i = 0 ; i < 7 ; i++ )
		{
			if( _Value[i] != 0 )
				return false;
		}
		return true;
	}

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};

//----------------------------------------------------------------------------------------
// 角色權限設定
//----------------------------------------------------------------------------------------
struct SystemFlagStruct
{
	union
	{
		int		_Value;
		struct  
		{
			bool	DisableTrade		: 1;		//交易禁止( AC Shop Mail Trade House)
			bool	DisableTalk			: 1;		//交談禁止
			bool	ChangeNameEnabled	: 1;		//可更名
			bool	IsHero				: 1;		//
			bool	IsDemon				: 1;		//
			bool	IsHonorLeader		: 1;		// 榮譽組隊狀態( 如果此人為Party 隊長)
			bool	IsNeedSetPosition	: 1;		//換區時要重新設定位置
			bool	FindParty			: 1;
			bool	IsContorlPet		: 1;		//可控制寵物
			bool	PassengerAttackable	: 1;		//可攻擊乘客
			bool	MoneySerialCodeError: 1;		//金錢SerialCode錯誤
			bool	EnableGMCmd			: 1;		//開啟GM 命令
		};
	};
};
//----------------------------------------------------------------------------------------
//基本物件屬性定義 (物件產生可設定項目) 每個物件的共用設定
//----------------------------------------------------------------------------------------
struct	ObjectModeStruct
{
	union
	{
		int			_Mode;			//如果_Mode == -1 表示資料沒有用
		struct		//npc 屬性
		{
			//顯像物件
			bool	Show	    		:1;		    //0x00000001	秀出(不論秀出或隱藏, 標記/致能)
			bool	Mark	    		:1;		    //0x00000002	可標記/點選(可以讓玩家點選)
			bool	Obstruct    		:1;		    //0x00000004	會阻擋(阻擋其他的物件)
			bool	Gravity	    		:1;		    //0x00000008	有重力(地心引力, 計算物件與地面的碰撞, 否則依照 Client 送來的座標, 不會依地面高度改變 y)
			bool	Save	    		:1;		    //0x00000010	此物件是否要儲存
			bool    Drag            	:1;         //0x00000020    有阻力的
			bool    GMHide             	:1;			//0x00000040    完全隱行
			bool    IsAllZoneVisible  	:1;			//0x00000080    全域可視物件

			bool	DisableRotate		:1;			//0x00000100	禁止旋轉( 面向不會改變 ) 
			bool	GM_NpcHide			:1;			//0x00000200	用GM命令讓某個NPC hide
			bool	Remove				:1;			//0x00000400	可否移除(公會建築)
			bool	RelyOwnerPower		:1;			//0x00000800	參考主人的威力
			bool	IgnoreNpcKill		:1;			//0x00001000	忽略npc殺死
			bool	EnemyHide			:1;			//0x00002000	敵方看不建此物件
			bool    NotShowHPMP    		:1;         //0x00004000	不顯示血條
			bool	NoFix_Y				:1;			//0x00008000	不修正Ｙ軸

			//NPC行為
			bool	Strikback			:1;			//0x00010000	反擊
			bool	Move				:1;			//0x00020000	移動
			bool	Searchenemy			:1;			//0x00040000	搜尋敵人
			bool	Revive				:1;			//0x00080000	可重生(告知 SERVER, 開啟此旗標的物件需要重生, 重生時間查看 Revive)
			bool	Fight				:1;			//0x00100000	可砍殺攻擊(開啟此旗標的物件可以被砍殺)
			bool    Escape          	:1;         //0x00200000    逃跑
			bool    SearchenemyIgnore	:1;         //0x00400000    此物件不會被搜尋到

			//參數
			bool	AlignToSurface		:1;			//0x00800000	貼齊表面
			bool	HideName			:1;			//0x01000000	NPC 或 物件頭上的名稱是否顯示 ( 類型外的例外 )
			bool	HideMinimap			:1;			//0x02000000	NPC 或 物件在小地圖上面是否顯示 ( 類型外的例外 )
			bool	ShowRoleHead		:1;			//0x04000000	點擊物件後,是否要顯示頭像框( true 是 show, Hide 是

			bool	CollisionPlot		:1;			//0x08000000	是否擁有碰撞劇情
			bool	Treasure			:1;			//0x10000000	寶箱
			bool	IsPet				:1;			//0x20000000	寵物
			bool	DisableAction		:1;			//0x40000000	暫時改變動作
			bool	DisableMovePG		:1;			//0x80000000	可控載具不送移動封包
		};
		struct  //物品屬性
		{
			bool	DurableStart0		:1;			//0x00000001	耐久度重0開始
			bool	PkNoDrop			:1;			//0x00000002	pk時不會掉落
			bool	DepartmentStore		:1;			//0x00000004	商城物品
			bool	DepartmentStore_Free:1;			//0x00000008	必爾丁商城物品
			bool	ItemDrop_AllParty	:1;			//0x00000010	全隊掉落
			bool	UseWithoutFail		:1;			//0x00000020	使用不會失敗
			bool    SpecialSuit    		:1;         //0x00000040	酷裝
			bool	ItemDrop_Depart		:1;			//0x00000080	物品掉落自動分堆
			//物品資料
			bool	PickupBound			:1;			//0x00000100	檢取禁制
			bool	Sell				:1;			//0x00000200	可買賣
			bool	Logoutdel			:1;			//0x00000400	離線消失
			bool	Expense				:1;			//0x00000800	消耗
			bool	Coloring			:1;			//0x00001000	可染色
			bool	GuildMark			:1;			//0x00002000	公會章
			bool    EQSoulBound     	:1;         //0x00004000	裝備禁制
			bool	HideCount			:1;			//0x00008000	不顯示數量
			bool	ChangeZoneDel		:1;			//0x00010000	換區消失
			bool	HideRefineLight		:1;			//0x00020000	衝等武器不顯示特效
			bool	Unique				:1;			//0x00040000	唯一物品
			bool	VariableRare		:1;			//0x00080000	(配方專用)稀有度會改變
			bool	NoNPCAbility		:1;			//0x00100000	物品掉落全靠物品本身屬性
			bool	EnableLockedItem	:1;			//0x00200000	可對鎖定的物品使用
			bool	AutoUseItem			:1;			//0x00400000	自動使用物品
			bool	DisableRefine		:1;			//0x00800000	不可精煉
			bool	DisablePowerQuality	:1;			//0x01000000	不可升階
			bool	DisableMagicBox		:1;			//0x02000000	不可使用魔幻寶盒
			bool	DisableDigHode		:1;			//0x04000000	無法打孔
			bool	HideMaxHeap			:1;			//0x08000000	不顯示最大堆疊量
		};
		struct //頭銜屬性
		{
			bool	PreViewTitle		:1;			//0x00000001	可預覽頭銜
		};
	};

	bool	GetMode( int i )
	{
		int T = 0x1 << i;
		return (_Mode & T) != 0;
	};


};
//----------------------------------------------------------------------------------------
//	法術屬性影響效果
//----------------------------------------------------------------------------------------
struct		MagicEffectStruct
{
	union
	{
		int			_Value[2];
		struct
		{
			//一般
			bool    UseMagicDisable     :1;     //不可用法術攻擊
			bool    UsePhyDisable       :1;     //不可用物理攻擊
			bool    BadMagicInvincible  :1;     //壞的法術無效(法術技能無效)
			bool    BadPhyInvincible    :1;     //壞的物理無效(物理技能與一般攻擊無效)
			bool    UseItemDisable      :1;     //不可使用物品
			bool    SearchEmenyDisable  :1;     //不可索敵
			bool    Stop                :1;     //不可移動

			//Client 端效果型
			bool    Cover               :1;     //隱形
			bool    DetectCover         :1;     //偵測隱形
			bool	Sneak				:1;		//潛行
			bool	DetectSneak			:1;		//偵測潛行
			bool    Blind               :1;     //失明(螢幕全黑)
			bool	HitDown				:1;		//倒地
			bool	Trace				:1;		//追蹤			

			//其他
			bool	PlayDead			:1;	    //裝死
			bool    Insure              :1;     //保險(抵死一次)
			bool    Chaos               :1;     //混亂
			bool    Fear                :1;     //恐懼

			bool	LockTarget			:1;		//攻擊目標索定			
			bool	WeaponIgnore		:1;		//武器無效化
			bool	ArmorIgnore			:1;		//防具無效化			
			bool	Ride				:1;		//騎乘
			bool	Raise				:1;		//重生
			bool	ExpProtect			:1;		//死亡經驗值不扣

			bool	Client_Dizzy		:1;		//暈眩(Client 行為) 
			bool	Client_Sleep		:1;		//睡眠(Client 行為)
			bool	PKFlag				:1;		//PK狀態(有開啟的人就可以PK)
			bool	TeleportDisable		:1;		//禁止傳送

			bool	GPS					:1;		//位置定位器致能
			bool	PKFlag_Disabled		:1;		//PK禁制令
			bool	AI_LowAttackPriority:1;		//被怪ai攻擊-優先降到最低
			bool	StopOntimeCure		:1;		//停止HPMPSP定時回復

			//////////////////////////////////////////////////////////////////////////
			bool	Silence				:1;		//禁止說話(GM)
			bool	CliOutofContorl		:1;		//Client不可控制
			bool	Freeze				:1;		//Client玩家冰凍
			bool    GoodMagicInvincible :1;     //好的法術無效(法術技能無效)
			bool    GoodPhyInvincible   :1;     //好的物理無效(物理技能與一般攻擊無效)
			bool	Guilty				:1;		//有罪
			bool	Critial				:1;		//絕對致命一擊
			bool	Hunter				:1;		//獵殺者
			bool	NoEscape			:1;		//不可逃跑
			bool	DisableJobSkill		:1;		//不能使用原本職業技能
			bool	IgnoreDeadGoodEvil	:1;		//不處理死亡善惡值
			bool	ExchangeZoneDamageEvent:1;	//取代區域傷害
			bool	Fly					:1;		//飛行
			bool	WaterWalk			:1;		//水上行走
			bool	GravityDisable		:1;		//暫時無重力
			bool    DisableStrikeBack	:1;		//震退無效
			bool	DisableWagon		:1;		//不能上載具
			bool	IgnoreInstancePlayer:1;		//忽略副本人數計算
			bool	TitleSysPowerUp		:1;		//新頭銜系統能力兩倍
			bool	MagicSpell_ZeroTime	:1;		//所有法術 瞬發
			bool	MagicSpell_Moveable	:1;		//所有法術 可移動施法
			bool	MagicSpell_NoCost	:1;		//所有法術 無消耗
			bool	DetectPlayDead		:1;		//偵查裝死
			bool	ChangeMotion		:1;		//修改動作
			bool	RangeAttackInvincible:1;	//壞的範圍法術無效
			bool	EqProtect			:1;		//裝備耐久度不會下降(裝備保護)

		};
	};
};
// NPC Other Setting
//----------------------------------------------------------------------------------------
struct		StructNPCOtherFlag
{
	union
	{
		int			Value;
		struct
		{
			//一般
			bool    ForceAttachkWeapon     :1;     //強制武器綁定在手上
		};
	};
};
//----------------------------------------------------------------------------------------
//輔助法術施效條件
//----------------------------------------------------------------------------------------
struct  MagicClearTimeStruct
{
	union
	{
		int			_Value;
		struct
		{
			bool    Attack      		:1;    	//攻擊消失
			bool    UnderAtk    		:1;    	//被攻擊消失
			bool    Move        		:1;    	//移動消失
			bool    Spell       		:1;    	//施法/用物理技/使用物品消失
			bool    ChangeZone  		:1;    	//換區消失
			bool    Logout      		:1;    	//離線消失
			bool	Random				:1;	   	//亂數消失 Max/3 ~ Max
			bool    WarriorSP0  		:1;    	//戰士SP為0消失
			bool    RangerSP0   		:1;    	//遊俠SP為0消失
			bool    RogueSP0    		:1;    	//盜賊SP為0消失
			bool    HP0					:1;    	//HP為0消失
			bool    MP0         		:1;    	//MP為0消失
			bool	Spell_MagicAttack	:1;		//施攻擊法術消失
			bool	Spell_PhyAttack		:1;		//施攻擊技能消失
			bool	Spell_Cure			:1;		//施攻回復魔法消失
			bool	TargetOnAttack		:1;		//目標是攻擊模式or看的到目標 攻擊消失
			bool	OnStopAttackMode	:1;		//停止攻擊
			bool	OnWater				:1;		//水中消失
			bool	OnNoWater			:1;		//路上消失
			bool	Spell_Magic			:1;		//施放法術技能消失
			bool	Spell_Phy			:1;		//施放物理技能消失
			bool	ChangeJob			:1;		//換職業消失
			bool	ChangeSuitSkill		:1;		//切換套裝技能時消失
			bool	ChangeEQPhantom		:1;		//魔靈裝備改變
		};
	};
};
//----------------------------------------------------------------------------------------
//	物品列舉
//----------------------------------------------------------------------------------------
enum	GameObjectItemENUM
{
	EM_Item_Normal	= 0	    ,
	EM_Item_Money			,
	EM_Item_Weapon		    ,
	EM_Item_Armor			,
	EM_Item_Rune			,
	EM_Item_Card			,

	EM_Item_Max				,
	EM_GameObjectItemEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//武器總類列舉
//----------------------------------------------------------------------------------------

enum	GameObjectWeaponENUM
{
	EM_Weapon_None                  = -1,
	EM_Weapon_Unarmed			,// Unarmed空手
	EM_Weapon_Blade             ,// 劍
	EM_Weapon_Dagger            ,// 匕首
	EM_Weapon_Wand              ,// 權杖
	EM_Weapon_Axe               ,// 斧
	EM_Weapon_Bludgeon          ,// 鎚棍棒
	EM_Weapon_Claymore          ,// 雙手劍
	EM_Weapon_Staff             ,// 杖
	EM_Weapon_2H_Axe            ,// 雙手斧
	EM_Weapon_2H_Hammer         ,// 雙手鎚
	EM_Weapon_Polearm			,// 槍(長矛)
	EM_Weapon_Bow				,// 遠程武器 弓
	EM_Weapon_CossBow			,// 遠程武器 十字弓
	EM_Weapon_Gun				,// 遠程武器 槍
	EM_Weapon_Ammo_Bow			,// 子彈 弓
	EM_Weapon_Ammo_Gun			,// 子彈 槍
	EM_Weapon_Throw				,// 投擲類武器
	EM_Weapon_Lumbering			,// 筏木
	EM_Weapon_Herbalism			,// 採藥
	EM_Weapon_Mining			,// 採礦
	EM_Weapon_Fishing			,// 釣魚

	EM_GameObjectWeaponEM_FORCE_DWORD   = 0x7fffffff, 
};

enum	GameObjectArmorENUM
{
	EM_Armor_None			=-1	,
	EM_Armor_HeavyArmed	        ,
	EM_Armor_LightArmed	        ,
	EM_Armor_Leather			,
	EM_Armor_Clothes	        ,
	EM_Armor_Robe		        ,
	EM_Armor_Shield		        ,
	
	EM_Armor_Implement			,	// 手持器具
	EM_Armor_Ornament	        ,	// 飾品類

	//聲音類型
	EM_Armor_Wood				,	//木頭
	EM_Armor_Stone				,	//石頭
	EM_Armor_Iron				,	//鐵

	EM_Armor_MaxCount			,	

	EM_GameObjectArmorEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//裝備技能資料
struct EqWearSkillStruct
{
	union
	{
		int _Skill;
		struct
		{
			bool    Unarmed		  	: 1;		//0x00000001
			bool    Blade           : 1;		//0x00000002
			bool    Dagger          : 1;		//0x00000004
			bool    Wand            : 1;		//0x00000008
			bool    Axe             : 1;		//0x00000010
			bool    Bludgeon        : 1;		//0x00000020
			bool    Claymore        : 1;		//0x00000040
			bool    Staff           : 1;		//0x00000080
			bool    Axe_2H          : 1;		//0x00000100
			bool    Hammer_2H       : 1;		//0x00000200
			bool    Polearm		  	: 1;		//0x00000400
			bool    Bow			  	: 1;		//0x00000800
			bool    CossBow		  	: 1;		//0x00001000
			bool    Gun			  	: 1;		//0x00002000
			bool    Throw			: 1;		//0x00004000
			bool    HeavyArmed	    : 1;		//0x00008000
			bool    LightArmed	    : 1;		//0x00010000
			bool    Leather		    : 1;		//0x00020000
			bool    Clothes	      	: 1;		//0x00040000
			bool    Robe		    : 1;		//0x00080000
			bool	Shield		  	: 1;		//0x00100000
			bool	Implement		: 1;		//0x00200000
			bool	SecondHand		: 1;		//0x00400000
		};
	};
};

//----------------------------------------------------------------------------------------
//裝備位置
//----------------------------------------------------------------------------------------
enum GameObjectWeaponPosENUM
{
	EM_WeaponPos_MainHand     ,   //主手
	EM_WeaponPos_SecondHand   ,   //副手
	EM_WeaponPos_OneHand      ,   //雙手都可以裝備
	EM_WeaponPos_TwoHand      ,   //兩手
	EM_WeaponPos_Ammo         ,   //子彈
	EM_WeaponPos_Bow          ,   //弓
	EM_WeaponPos_Manufacture  ,   //生產工具

	EM_GameObjectWeaponPosENUM_FORCE_DWORD   = 0x7fffffff, 
};

enum GameObjectArmorPosENUM
{
	EM_ArmorPos_Head        ,   //頭
	EM_ArmorPos_Gloves	    ,   //手套
	EM_ArmorPos_Shoes	    ,   //鞋子
	EM_ArmorPos_Clothes	    ,   //上衣
	EM_ArmorPos_Pants	    ,   //褲子
	EM_ArmorPos_Back	    ,   //背部
	EM_ArmorPos_Belt	    ,   //腰帶
	EM_ArmorPos_Shoulder    ,   //肩甲
	EM_ArmorPos_Necklace    ,   //項鍊 
	EM_ArmorPos_Ring        ,   //戒子
	EM_ArmorPos_Earring     ,   //耳飾
	EM_ArmorPos_SecondHand  ,   //副手
	EM_ArmorPos_MagicTool	,	//法寶
	EM_ArmorPos_Ornament	,	//裝飾品


	EM_ArmorPos_MaxCount	,	
	EM_GameObjectArmorPosENUM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//抗性烈舉
enum    MagicResistENUM
{
	EM_MagicResist_None    = -1 ,
	EM_MagicResist_Earth    ,
	EM_MagicResist_Water    ,   
	EM_MagicResist_Fire     ,
	EM_MagicResist_Wind     ,
	EM_MagicResist_Light    ,
	EM_MagicResist_Darkness ,
	EM_MagicResist_MAXCOUNT ,

	EM_MagicResist_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//抗性結構
struct  MagicResistStruct
{
	union
	{
		float     _ArrList[ EM_MagicResist_MAXCOUNT ];
		struct
		{
			float     Earth;
			float     Water;        
			float     Fire;
			float     Wind;
			float     Light;
			float     Darkness;
		};
	};
};
//----------------------------------------------------------------------------------------
//NPC抗性資料表
//----------------------------------------------------------------------------------------
struct NpcResistBaseInfoStruct
{
	char				Name[ 32 ];
	MagicResistENUM		Type;
	MagicResistStruct	Resist;
};
//-------------------------------------------------------------------------------------
//		技能結構
//-------------------------------------------------------------------------------------
enum	SkillValueTypeENUM
{
	EM_SkillValueType_None				= -1,			
	EM_SkillValueType_Unarmed			= 0 ,// Unarmed空手
	EM_SkillValueType_Blade             ,// 劍
	EM_SkillValueType_Dagger            ,// 匕首
	EM_SkillValueType_Wand              ,// 權杖
	EM_SkillValueType_Axe               ,// 斧
	EM_SkillValueType_Bludgeon          ,// 鎚棍棒
	EM_SkillValueType_Claymore          ,// 雙手劍
	EM_SkillValueType_Staff             ,// 杖
	EM_SkillValueType_2H_Axe            ,// 雙手斧
	EM_SkillValueType_2H_Hammer         ,// 雙手鎚
	EM_SkillValueType_Polearm			,// 槍(長矛)
	EM_SkillValueType_Bow				,// 遠程武器 弓
	EM_SkillValueType_CossBow			,// 遠程武器 十字弓
	EM_SkillValueType_Gun				,// 遠程武器 槍
	EM_SkillValueType_Define			,// 防禦

	EM_SkillValueType_BlackSmith		,// 打鐵
	EM_SkillValueType_Carpenter			,// 木工
	EM_SkillValueType_MakeArmor			,// 製甲
	EM_SkillValueType_Tailor			,// 裁縫
	EM_SkillValueType_Cook				,// 烹飪
	EM_SkillValueType_Alchemy			,// 煉金

	EM_SkillValueType_Mining			,// 挖礦
	EM_SkillValueType_Lumbering			,// 砍材
	EM_SkillValueType_Herblism			,// 採藥
	EM_SkillValueType_Fishing			,// 釣魚
	EM_SkillValueType_Plant				,// 種植
	EM_SkillValueType_CatchPet			,// 補捉寵物
	EM_SkillValueType_MaxCount			,
};

struct	SkillValueStruct
{

	union
	{
		float	Skill[_MAX_SKILL_COUNT_];
		struct
		{
			float Unarmed	, Blade		, Dagger	, Wand		, Axe ;
			float Bludgeon  , Claymore  , Staff		, Axe_2H	, Hammer_2H;
			float Polearm	, Bow		, CossBow	, Gun		;
			float Defense;
			// 生活技
			float BlackSmith , Carpenter , MakeArmor , Tailor , Cook , Alchemy  ;
			// 採集生活技能
			float Mining, Lumbering, Herblism, Fishing,Plant,CatchPet;
		};
	};
	float GetSkill( int ID )
	{
		if( (unsigned)ID < _MAX_SKILL_COUNT_ )
			return Skill[ ID ];
		return 0;
	}
};
//----------------------------------------------------------------------------------------
//	NPC Title 顯示設定列舉
//----------------------------------------------------------------------------------------
enum NpcTitleTypeENUM
{
	EM_NpcTitleTypeENUM_Nornal			,		//一般
	EM_NpcTitleTypeENUM_Invisible		,		//不顯示
	EM_NpcTitleTypeENUM_QuestNPC		,		//任務型npc
	EM_NpcTitleTypeENUM_Neutral			,		//中立怪
};

//----------------------------------------------------------------------------------------
//	法術消耗列舉
//----------------------------------------------------------------------------------------
enum MagicSpellCostTypeENUM
{
	EM_MagicSpellCostType_None			,		//無消耗
	EM_MagicSpellCostType_HP			,		//消耗 HP
	EM_MagicSpellCostType_MP			,		//消耗 MP
	EM_MagicSpellCostType_HP_Per		,		//消耗 HP百分比
	EM_MagicSpellCostType_MP_Per		,		//消耗 MP百分比
	EM_MagicSpellCostType_SP_Warrior	,		//消耗 SP 戰士(-1表示全部)
	EM_MagicSpellCostType_SP_Ranger		,		//消耗 SP 遊俠(-1表示全部)
	EM_MagicSpellCostType_SP_Rogue		,		//消耗 SP 盜賊(-1表示全部)
	EM_MagicSpellCostType_StomachPoint	,		//消耗 飽食度
	EM_MagicSpellCostType_Item			,		//消耗 物品
	EM_MagicSpellCostType_Ammo_Gun		,		//消耗 子彈
	EM_MagicSpellCostType_Ammo_Bow		,		//消耗 弓箭矢
	EM_MagicSpellCostType_Ammo_CossBow	,		//消耗 十字弓箭矢
	EM_MagicSpellCostType_Ammo_Throw	,		//消耗 投擲物
	EM_MagicSpellCostType_Ammo_All		,		//消耗 所有的遠程彈藥
	EM_MagicSpellCostType_SoulPoint		,		//消耗 靈魂值
};
//----------------------------------------------------------------------------------------
//	法術需求列舉
//----------------------------------------------------------------------------------------
enum MagicSpellNeedTypeENUM
{
	EM_MagicSpellNeedType_None						,	//無需求
	EM_MagicSpellNeedType_Weapon					,	//需求 自己裝 武器
	EM_MagicSpellNeedType_EQ						,	//需求 自己裝 裝備
	EM_MagicSpellNeedType_Suit						,	//需求 自己裝 套裝
	EM_MagicSpellNeedType_Buf						,	//需求 自己有 法術Buf
	EM_MagicSpellNeedType_Buf_Target				,	//需求 目標有 法術Buf
	EM_MagicSpellNeedType_NoBuf						,	//需求 自己沒有 法術Buf
	EM_MagicSpellNeedType_NoBuf_Target				,	//需求 目標沒有 法術Buf
	EM_MagicSpellNeedType_WeaponType_Unarmed		,	//需求 自己裝 武器類型 空手
	EM_MagicSpellNeedType_WeaponType_Blade      	,	//需求 自己裝 武器類型 單手劍
	EM_MagicSpellNeedType_WeaponType_Dagger     	,	//需求 自己裝 武器類型 匕首
	EM_MagicSpellNeedType_WeaponType_Wand       	,	//需求 自己裝 武器類型 權杖
	EM_MagicSpellNeedType_WeaponType_Axe        	,	//需求 自己裝 武器類型 單手斧
	EM_MagicSpellNeedType_WeaponType_Bludgeon   	,	//需求 自己裝 武器類型 鎚棍棒
	EM_MagicSpellNeedType_WeaponType_Claymore   	,	//需求 自己裝 武器類型 雙手劍
	EM_MagicSpellNeedType_WeaponType_Staff      	,	//需求 自己裝 武器類型 杖
	EM_MagicSpellNeedType_WeaponType_2H_Axe     	,	//需求 自己裝 武器類型 雙手斧
	EM_MagicSpellNeedType_WeaponType_2H_Hammer  	,	//需求 自己裝 武器類型 雙手鎚
	EM_MagicSpellNeedType_WeaponType_Polearm		,	//需求 自己裝 武器類型 槍(長矛)
	EM_MagicSpellNeedType_WeaponType_SwordType  	,	//需求 自己裝 武器類型 劍類(單雙手)
	EM_MagicSpellNeedType_WeaponType_AxeType    	,	//需求 自己裝 武器類型 斧類(單雙手)
	EM_MagicSpellNeedType_WeaponType_Shield			,	//需求 自己裝 武器類型 盾
	EM_MagicSpellNeedType_Distance					,	//需求 距離目標
	EM_MagicSpellNeedType_NotAttak					,	//需求 自己非戰鬥
	EM_MagicSpellNeedType_Attack					,	//需求 自己戰鬥
	EM_MagicSpellNeedType_Critical					,	//需求 自己爆擊
	EM_MagicSpellNeedType_BeCritical				,	//需求 自己被爆擊
	EM_MagicSpellNeedType_Dodge						,	//需求 自己閃避
	EM_MagicSpellNeedType_BeDodge					,	//需求 自己被閃避
	EM_MagicSpellNeedType_Miss						,	//需求 自己Miss
	EM_MagicSpellNeedType_Parry						,	//需求 自己格擋
	EM_MagicSpellNeedType_BeParry					,	//需求 自己被格擋
	EM_MagicSpellNeedType_NotAttack_Target			,	//需求 目標非戰鬥
	EM_MagicSpellNeedType_Attack_Target				,	//需求 目標戰鬥	
	EM_MagicSpellNeedType_SelfHp_Smaller_Percent	,	//需求 HP百分比小於
	EM_MagicSpellNeedType_SelfHp_Greater_Percent	,	//需求 HP百分比大於
	EM_MagicSpellNeedType_Self_Job					,	//需求 職業
	EM_MagicSpellNeedType_WeaponType_LongDistWeapon	,	//需求 自己裝 武器類型 長距離武器
	EM_MagicSpellNeedType_WeaponType_2H_Weapon		,	//需求 自己裝 武器類型 雙手武器
	EM_MagicSpellNeedType_WeaponType_Hammer			,	//需求 自己裝 武器類型 鎚類(單雙手)
	EM_MagicSpellNeedType_BuffGroup					,	//需求 自己擁有某 Buff Group
	EM_MagicSpellNeedType_ShieldBlock				,	//需求 自己盾擋
	EM_MagicSpellNeedType_BeShieldBlock				,	//需求 自己被盾擋
	EM_MagicSpellNeedType_WeaponType_1H_Weapon		,	//需求 自己裝 武器類型 單手武器
	EM_MagicSpellNeedType_NoBuffGroup				,	//需求 自己沒有某 Buff Group
	EM_MagicSpellNeedType_TargetBuffGroup			,	//需求 目標擁有某 Buff Group
	EM_MagicSpellNeedType_TargetNoBuffGroup			,	//需求 目標沒有某 Buff Group
	EM_MagicSpellNeedType_MagicCritical				,	//需求 自己爆擊
	EM_MagicSpellNeedType_BeMagicCritical			,	//需求 自己被爆擊
	EM_MagicSpellNeedType_Self_MainJob				,	//需求 主職業
	EM_MagicSpellNeedType_Self_SoulPoint			,	//需求 靈魂值

};
//----------------------------------------------------------------------------------------
//其他法術設定
//----------------------------------------------------------------------------------------
struct	MagicSpellFlagStruct
{
	union
	{
		int _Type;
		struct
		{
			bool	GoodMagic					: 1;	//好的法術
			bool    ShowBuf			    		: 1;	//顯示Buf
			bool	ContinueMagic				: 1;	//連續產生法術
			bool	DotMagic					: 1;	//DOT法術
			bool	FaceOffMagic				: 1;	//變身術 			
			bool	CancelBuff					: 1;	//可取消
			bool	ShowBuffTime				: 1;	//Client端顯示Buff時間
			bool	SpecialMagic				: 1;	//產生特殊法術
			bool	MagicShield					: 1;	//魔法盾
			bool	DeadNotClear				: 1;	//死亡不清除
			bool	OfflineBuffTime				: 1;	//下線Buff時間計算
			bool	OnPlayerAttackAddTime		: 1;	//攻擊玩家增加buff時間
			bool	OnKillAddTime				: 1;	//殺死物件增加buff時間
			bool	SelfBuff					: 1;	//私人Buf,不會與其他人的Buf互刺
			bool	FaceOffMagic_ShowEq			: 1;	//變身時顯示原本裝備武器
			bool	ShowPowerLv					: 1;	//顯示PowerLv
			bool	DotMagicNoKill				: 1;	//Dot法術殺不死人
			bool	BuffSkill					: 1;	//Buff擁有技能
			bool	MaxMagicLvEquRoleLv			: 1;	//Buff最高等級最多同玩家等級
			bool	DisableShowMagicInfo		: 1;	//Client 端不顯示加減血的資訓
			bool	FixDotPower					: 1;	//Dot不計算裝備能力(不算攻防比)
			bool	RideCanAttack				: 1;	//攻擊不會下馬
			bool	RidePetAttack				: 1;	//騎乘寵物做攻擊動作
			bool	CancelBadMagic				: 1;	//清除目標是自己的壞的法術
			bool	NpcEndFight_NotClearBuff	: 1;	//戰鬥結束不會消失的Buff
			bool	Dual_NoClearBuff			: 1;	//比試結束不清除的buff
			bool	IgnoreSpellCureMagicClear	: 1;	//忽略施展治療消失
			bool	IgnoreSpellAttackMagicClear	: 1;	//忽略施展攻擊消失
			bool	IgnoreBuffMessage			: 1;	//忽略施展攻擊消失(client 端顯像用 )
			bool	OnlyYouCanSee				: 1;	//只有自己看的到特效
			bool	NoEffect					: 1;	//(Client 顯示處理用)
			bool	forceDisplayEffect			: 1;	//強制顯示特效
		};
	};
};

struct	MagicSpellFlagExStruct
{
	union
	{
		int _Type;
		struct
		{
			bool		IgnoreMagicAbsorb		: 1;		//忽略魔法吸收
			bool		IsDepartmentStore		: 1;		//商城buff
		};
	};
};

//----------------------------------------------------------------------------------------
//	武器防具或法術會修改玩家能力的結構
//----------------------------------------------------------------------------------------
enum WearEqTypeENUM
{
	EM_WearEqType_None          			,   // "無效果",
	EM_WearEqType_Durable       			,   // "耐久度",
	EM_WearEqType_STR           			,   // "屬性 STR 力量",
	EM_WearEqType_STA           			,	// "屬性 STA 耐力",			
	EM_WearEqType_INT           			,	// "屬性 INT 智力",			
	EM_WearEqType_MND           			,	// "屬性 MND 靈力",
	EM_WearEqType_AGI           			,	// "屬性 AGI 敏捷",			
	EM_WearEqType_AllState      			,   // "屬性 所有(基本五個屬性)",
	EM_WearEqType_MaxHP         			,	// "上限 HP",
	EM_WearEqType_MaxMP		    			,	// "上限 MP",
	EM_WearEqType_ReHP		    			,	// "回復率 HP",
	EM_WearEqType_ReMP		    			,	// "回復率 MP",
	EM_WearEqType_ATK		    			,	// "ATK 攻擊力",
	EM_WearEqType_DEF		    			,	// "DEF 防禦力",
	EM_WearEqType_MDEF   	    			,	// "MDEF 魔法防禦",
	EM_WearEqType_MATK	        			,	// "MATK 魔法攻擊",
	EM_WearEqType_HitPoint	    			,	// "命中",
	EM_WearEqType_DodgePoint	   			,	// "迴避",
	EM_WearEqType_CritRate	    			,   // "暴擊等級",
	EM_WearEqType_CritPower	    			,   // "暴擊威力加強(%)",
	EM_WearEqType_MagicCritRate	    		,   // "法術暴擊等級",
	EM_WearEqType_MagicCritPower	    	,   // "法術暴擊威力加強(%)",
	EM_WearEqType_ParryRate     			,   // "格擋等級",
	EM_WearEqType_AtkSpeed	    			,   // "攻擊速度(%)",
	EM_WearEqType_MoveSpeed	    			,	// "移動速度(%)",
	EM_WearEqType_DMG           			,   // "武器威力 所有近戰或遠程 ( DMG )",
	EM_WearEqType_AllResist     			,   // "抗性 所有",
	EM_WearEqType_Resist_Earth  			,   // "抗性 地",
	EM_WearEqType_Resist_Water  			,   // "抗性 水",
	EM_WearEqType_Resist_Fire   			,   // "抗性 火",
	EM_WearEqType_Resist_Wind   			,   // "抗性 風",
	EM_WearEqType_Resist_Light  			,   // "抗性 光",
	EM_WearEqType_Resist_Darkness			,   // "抗性 闇",
	EM_WearEqType_ManaDecrease				,	// "MP消耗減少(%)",
	EM_WearEqType_Exp						,	// "經驗值",
	EM_WearEqType_Treasure					,	// "掉寶率",
	EM_WearEqType_SecHand_HitRate			,	// "副手 命中率",
	EM_WearEqType_SecHand_DMG_Per			,	// "副手 傷害力(DMG%)",
	EM_WearEqType_DEF_HeavyArmed			,	// "防禦加強 鎧甲(%)",
	EM_WearEqType_DEF_LightArmed			,	// "防禦加強 鎖甲(%)",
	EM_WearEqType_DEF_Leather				,	// "防禦加強 皮甲(%)",
	EM_WearEqType_DEF_Clothes	    		,	// "防禦加強 衣服(%)",
	EM_WearEqType_DEF_Robe					,	// "防禦加強 長袍(%)",
	EM_WearEqType_DEF_Shield				,	// "防禦加強 盾(%)",
	EM_WearEqType_MagicPow_AllMagic 		, 	// "魔法威力 所有(%)",
	EM_WearEqType_MagicPow_Earth  			, 	// "魔法威力 地(%)",
	EM_WearEqType_MagicPow_Water  			, 	// "魔法威力 水(%)",
	EM_WearEqType_MagicPow_Fire   			, 	// "魔法威力 火(%)",
	EM_WearEqType_MagicPow_Wind   			, 	// "魔法威力 風(%)",
	EM_WearEqType_MagicPow_Light  			, 	// "魔法威力 光(%)",
	EM_WearEqType_MagicPow_Darkness			,	// "魔法威力 闇(%)",
	EM_WearEqType_SpellSpeed_AllMagic		, 	// "施法速度 所有(%)",
	EM_WearEqType_DMG_AllRange				,	// "遠程武器威力(%) 所有",
	EM_WearEqType_DMG_Bow					,	// "遠程武器威力(%) 弓",
	EM_WearEqType_DMG_Cossbow				,	// "遠程武器威力(%) 十字弓",
	EM_WearEqType_DMG_Gun					,	// "遠程武器威力(%) 槍",
	EM_WearEqType_DMG_AllWeapon				,	// "近戰武器威力(%) 所有",
	EM_WearEqType_DMG_Unarmed				,	// "近戰武器威力(%) 空手",
	EM_WearEqType_DMG_Blade     			,	// "近戰武器威力(%) 劍",
	EM_WearEqType_DMG_Dagger    			,	// "近戰武器威力(%) 匕首",
	EM_WearEqType_DMG_Wand      			,	// "近戰武器威力(%) 權杖",
	EM_WearEqType_DMG_Axe       			,	// "近戰武器威力(%) 斧",
	EM_WearEqType_DMG_Bludgeon  			,	// "近戰武器威力(%) 鎚棍棒",
	EM_WearEqType_DMG_Claymore  			,	// "近戰武器威力(%) 雙手劍",
	EM_WearEqType_DMG_Staff     			,	// "近戰武器威力(%) 杖",
	EM_WearEqType_DMG_2H_Axe    			,	// "近戰武器威力(%) 雙手斧",
	EM_WearEqType_DMG_2H_Hammer 			,	// "近戰武器威力(%) 雙手鎚",
	EM_WearEqType_DMG_Polearm				,	// "近戰武器威力(%) 槍(長矛)",
	EM_WearEqType_AttackSpeed_AllRange		,	// "遠程武器速度(%) 所有",
	EM_WearEqType_AttackSpeed_Bow			,	// "遠程武器速度(%) 弓",
	EM_WearEqType_AttackSpeed_Cossbow		,	// "遠程武器速度(%) 十字弓",
	EM_WearEqType_AttackSpeed_Gun			,	// "遠程武器速度(%) 槍", 
	EM_WearEqType_AttackSpeed_AllWeapon		,	// "近戰武器速度(%) 所有",
	EM_WearEqType_AttackSpeed_Unarmed		,	// "近戰武器速度(%) 空手",
	EM_WearEqType_AttackSpeed_Blade     	,	// "近戰武器速度(%) 劍",
	EM_WearEqType_AttackSpeed_Dagger    	,	// "近戰武器速度(%) 匕首",
	EM_WearEqType_AttackSpeed_Wand      	,	// "近戰武器速度(%) 權杖",
	EM_WearEqType_AttackSpeed_Axe       	,	// "近戰武器速度(%) 斧",
	EM_WearEqType_AttackSpeed_Bludgeon  	,	// "近戰武器速度(%) 鎚棍棒",
	EM_WearEqType_AttackSpeed_Claymore  	,	// "近戰武器速度(%) 雙手劍",
	EM_WearEqType_AttackSpeed_Staff     	,	// "近戰武器速度(%) 杖",
	EM_WearEqType_AttackSpeed_2H_Axe    	,	// "近戰武器速度(%) 雙手斧",
	EM_WearEqType_AttackSpeed_2H_Hammer 	,	// "近戰武器速度(%) 雙手鎚",
	EM_WearEqType_AttackSpeed_Polearm		,	// "近戰武器速度(%) 槍(長矛)",
	EM_WearEqType_WearEqAbility_Unarmed 	,	// "裝備能力 空手",
	EM_WearEqType_WearEqAbility_Blade   	,	// "裝備能力 劍",	  	  	
	EM_WearEqType_WearEqAbility_Dagger  	,	// "裝備能力 匕首",
	EM_WearEqType_WearEqAbility_Wand    	,	// "裝備能力 權杖",  	
	EM_WearEqType_WearEqAbility_Axe     	,	// "裝備能力 斧",	  	
	EM_WearEqType_WearEqAbility_Bludgeon	,	// "裝備能力 鎚棍棒",
	EM_WearEqType_WearEqAbility_Claymore	,	// "裝備能力 雙手劍",
	EM_WearEqType_WearEqAbility_Staff   	,	// "裝備能力 杖",
	EM_WearEqType_WearEqAbility_Axe_2H  	,	// "裝備能力 雙手斧",
	EM_WearEqType_WearEqAbility_Hammer_2H	,	// "裝備能力 雙手鎚",
	EM_WearEqType_WearEqAbility_Polearm		,	// "裝備能力 槍(長矛)",
	EM_WearEqType_WearEqAbility_Bow			,	// "裝備能力 弓",
	EM_WearEqType_WearEqAbility_CossBow		,	// "裝備能力 十字弓",
	EM_WearEqType_WearEqAbility_Gun			,	// "裝備能力 槍",
	EM_WearEqType_WearEqAbility_Throw		,	// "裝備能力 投擲",
	EM_WearEqType_WearEqAbility_HeavyArmed	,	// "裝備能力 鎧甲",
	EM_WearEqType_WearEqAbility_LightArmed	,	// "裝備能力 鎖甲",
	EM_WearEqType_WearEqAbility_Leather		,	// "裝備能力 皮甲",
	EM_WearEqType_WearEqAbility_Clothes	    ,	// "裝備能力 衣服",
	EM_WearEqType_WearEqAbility_Robe		,	// "裝備能力 長袍",
	EM_WearEqType_WearEqAbility_Shield		,	// "裝備能力 盾",
	EM_WearEqType_WearEqAbility_Implement	,	// "裝備能力 手持法器",
	EM_WearEqType_WearEqAbility_SecondHand	,	// "裝備能力 雙手持",
	EM_WearEqType_SkillValue_Unarmed		,	// "技能上升 Unarmed空手",
	EM_WearEqType_SkillValue_Blade          ,	// "技能上升 劍",
	EM_WearEqType_SkillValue_Dagger         ,	// "技能上升 匕首",
	EM_WearEqType_SkillValue_Wand           ,	// "技能上升 權杖",
	EM_WearEqType_SkillValue_Axe            ,	// "技能上升 斧",
	EM_WearEqType_SkillValue_Bludgeon       ,	// "技能上升 鎚棍棒",
	EM_WearEqType_SkillValue_Claymore       ,	// "技能上升 雙手劍",
	EM_WearEqType_SkillValue_Staff          ,	// "技能上升 杖",
	EM_WearEqType_SkillValue_2H_Axe         ,	// "技能上升 雙手斧",
	EM_WearEqType_SkillValue_2H_Hammer      ,	// "技能上升 雙手鎚",
	EM_WearEqType_SkillValue_Polearm		,	// "技能上升 槍(長矛)",
	EM_WearEqType_SkillValue_Bow			,	// "技能上升 遠程武器 弓",
	EM_WearEqType_SkillValue_CossBow		,	// "技能上升 遠程武器 十字弓",
	EM_WearEqType_SkillValue_Gun			,	// "技能上升 遠程武器 槍",
	EM_WearEqType_SkillValue_Define			,	// "技能上升 防禦",
	EM_WearEqType_SkillValue_BlackSmith		,	// "技能上升 打鐵",
	EM_WearEqType_SkillValue_Carpenter		,	// "技能上升 木工",
	EM_WearEqType_SkillValue_MakeArmor		,	// "技能上升 製甲",
	EM_WearEqType_SkillValue_Tailor			,	// "技能上升 裁縫",
	EM_WearEqType_SkillValue_Cook			,	// "技能上升 烹飪",
	EM_WearEqType_SkillValue_Alchemy		,	// "技能上升 煉金",
	EM_WearEqType_HQ_BlackSmith				,	// "HQ品機率上升 打鐵(%)",
	EM_WearEqType_HQ_Carpenter				,	// "HQ品機率上升上升 木工(%)",
	EM_WearEqType_HQ_MakeArmor				,	// "HQ品機率上升上升 製甲(%)",
	EM_WearEqType_HQ_Tailor					,	// "HQ品機率上升上升 裁縫(%)",
	EM_WearEqType_HQ_Cook					,	// "HQ品機率上升上升 烹飪(%)",
	EM_WearEqType_HQ_Alchemy				,	// "HQ品機率上升上升 煉金(%)",	
	EM_WearEqType_ATK_Per	    			,	// "ATK 攻擊力 (%)",
	EM_WearEqType_DEF_Per	    			,	// "DEF 防禦力 (%)",
	EM_WearEqType_StealRate	    			,	// "偷竊成功率 (%)",
	EM_WearEqType_DropMoneyRate	    		,	// "金錢掉落率 (%)",
	EM_WearEqType_HateRate		    		,	// "仇恨度增加 (%)",
	EM_WearEqType_ReSP_Per_Warrior			,	// "戰士SP 回復加百分比",
	EM_WearEqType_ReSP_Per_Ranger			,	// "遊俠SP 回復加百分比",
	EM_WearEqType_ReSP_Per_Rogue			,	// "盜賊SP 回復加百分比",
	EM_WearEqType_MAbsorbRate    			,	// "魔法吸收率",
	EM_WearEqType_AbsorbRate    			,	// "防禦吸收率",
	EM_WearEqType_HealAbsorbRate	  		,	// "治療吸收率",
	EM_WearEqType_MAbsorb	    			,	// "魔法吸收點數",
	EM_WearEqType_Absorb	    			,	// "防禦吸收點數",
	EM_WearEqType_HealAbsorb				,	// "治療吸收點數",
	EM_WearEqType_MDmgPoint        			,   // "魔法傷害加點",
	EM_WearEqType_HealPowerRate	  			,	// "治療威力增加率",
	EM_WearEqType_HealPoint		  			,	// "治療威力增加點數",
	EM_WearEqType_RangeAttackRange			,	// "遠程武器攻擊距離增加",

	EM_WearEqType_SkillValue_Lumbering		,	// "技能上升 筏木",
	EM_WearEqType_SkillValue_Herbalism		,	// "技能上升 採藥",
	EM_WearEqType_SkillValue_Mining			,	// "技能上升 挖礦",
	EM_WearEqType_SkillValue_Fishing		,	// "技能上升 釣魚",

	EM_WearEqType_HQ_Lumbering				,	// "HQ品機率上升 筏木",
	EM_WearEqType_HQ_Herbalism				,	// "HQ品機率上升 採藥",
	EM_WearEqType_HQ_Mining					,	// "HQ品機率上升 挖礦",
	EM_WearEqType_HQ_Fishing				,	// "HQ品機率上升 釣魚",

	EM_WearEqType_SkillValue_GatherRate		,	// "採集成功率",

	EM_WearEqType_STR_Rate         			,   // "屬性 STR 力量(%)",
	EM_WearEqType_STA_Rate         			,	// "屬性 STA 耐力(%)",			
	EM_WearEqType_INT_Rate           		,	// "屬性 INT 智力(%)",			
	EM_WearEqType_MND_Rate           		,	// "屬性 MND 靈力(%)",
	EM_WearEqType_AGI_Rate           		,	// "屬性 AGI 敏捷(%)",			
	EM_WearEqType_AllState_Rate      		,   // "屬性 所有(%)(基本五個屬性)",
	EM_WearEqType_MaxHP_Rate         		,	// "上限 HP(%)",
	EM_WearEqType_MaxMP_Rate		    	,	// "上限 MP(%)",
	EM_WearEqType_RideSpeed			    	,	// "騎乘速度(%)",
	EM_WearEqType_MDEF_Rate	    			,	// "MDEF(%) 魔法防禦",
	EM_WearEqType_MATK_Rate        			,	// "MATK(%) 魔法攻擊",
	EM_WearEqType_ShieldBlockRate     		,   // "盾擋等級",
	EM_WearEqType_DMG_Per          			,   // "武器威力 所有近戰或遠程 ( DMG% )",
	EM_WearEqType_Exp_SubJob				,	// "副職經驗值"
	EM_WearEqType_TP_Rate					,	// "TP經驗值"

	EM_WearEqType_SkillValue_LumberingRate	,	// "筏木成功率",
	EM_WearEqType_SkillValue_HerbalismRate	,	// "採藥成功率",
	EM_WearEqType_SkillValue_MiningRate		,	// "挖礦成功率",
	EM_WearEqType_SkillValue_FishingRate	,	// "釣魚成功率",
	EM_WearEqType_Gravity					,	// "重力修正"  ,

	EM_WearEqType_DoubleAttack				,	// "兩次攻擊" ,

	EM_WearEqType_ResistCritRate	    	,   // "抗暴等擊",
	EM_WearEqType_ResistMagicCritRate		,   // "底抗魔法致命一擊率",

	//固定法術效果
	EM_WearEqType_Magic_EarthPower			,	// "地屬性攻擊" ,
	EM_WearEqType_Magic_WaterhPower			,	// "水屬性攻擊" ,
	EM_WearEqType_Magic_FirePower			,	// "火屬性攻擊" ,
	EM_WearEqType_Magic_WindhPower			,	// "風屬性攻擊" ,
	EM_WearEqType_Magic_LightPower			,	// "光屬性攻擊" ,
	EM_WearEqType_Magic_DarkPower			,	// "暗屬性攻擊" ,

	EM_WearEqType_JumpRate					,	// "跳躍比率"   ,
	EM_WearEqType_MDMG           			,   // "魔法殤害點數"	,
	EM_WearEqType_MDMG_Per           		,   // "魔法殤害比率"	,

	EM_WearEqType_ResistShieldBlock	    	,   // "刺穿盾檔",
	EM_WearEqType_ResistParry				,   // "刺穿格擋",

	EM_WearEqType_MagicHitPoint				,   // "魔法命中",
	EM_WearEqType_MagicDodgePoint			,   // "魔法閃避",

	EM_WearEqType_PhyHitRate				,   // "物理命中率",
	EM_WearEqType_PhyDodgeRate				,   // "物理閃避率",
	EM_WearEqType_MagicHitRate				,   // "魔法命中率",
	EM_WearEqType_MagicDodgeRate			,   // "魔法閃避率",

	EM_WearEqType_GatherGenerateRate		,   // "採集產出量增加率",
	EM_WearEqType_GatherSpeedRate			,   // "採集速度增加率",
	EM_WearEqType_GatherExpRate				,   // "採集經驗值增加率",

	EM_WearEqType_AttackPlayerPowerRate		,   // "(攻)攻擊玩家(or玩家寵物)威力加減",
	EM_WearEqType_AttackNPCPowerRate		,   // "(攻)攻擊NPC威力加減",
	EM_WearEqType_PlayerDefRate				,   // "(守)被玩家(or玩家寵物)攻擊威力加減",
	EM_WearEqType_NPCDefRate				,   // "(守)被NPC攻擊威力加減",
	EM_WearEqType_AEMagicPowerRate			,   // "(攻)AE法術攻擊威力加減",
	EM_WearEqType_AEMagicDefRate			,   // "(守)被AC法術攻擊威力加減",

	EM_WearEqType_CraftSpeedRate			,	// "生產速度增加率"
	EM_WearEqType_CraftExpRate				,	// "生產經驗值增加率"
	EM_WearEqType_AddPlotExpRate			,	// "增加劇情給予的經驗值率"
	EM_WearEqType_AddPlotTPRate				,	// "增加劇情給予的TP率"

	EM_WearEqType_SP_Warrior_Consume		,	// "戰意消耗減少(%)"
	EM_WearEqType_SP_Rogue_Consume			,	// "精力消耗減少(%)"
	EM_WearEqType_SP_Ranger_Consume			,	// "專注消耗減少(%)"

	EM_WearEqType_NPC_EXP_Rate				,	// "NPC 經驗值修正(%)"
	EM_WearEqType_NPC_TP_Rate				,	// "NPC TP經驗值修正(%)"
	EM_WearEqType_AttackRange				,	// "近程武器攻擊距離增加",

	EM_WearEqType_AllResist_Per    			,   // "抗性 所有%",
	EM_WearEqType_Resist_Earth_Per  		,   // "抗性 地%",
	EM_WearEqType_Resist_Water_Per  		,   // "抗性 水%",
	EM_WearEqType_Resist_Fire_Per   		,   // "抗性 火%",
	EM_WearEqType_Resist_Wind_Per   		,   // "抗性 風%",
	EM_WearEqType_Resist_Light_Per			,   // "抗性 光%",
	EM_WearEqType_Resist_Darkness_Per		,   // "抗性 闇%",

	EM_WearEqType_ParryRate_Per				,	// "格擋%"
	EM_WearEqType_Daily_EXP_Rate			,	// "每日任務經驗值加乘"
	EM_WearEqType_Daily_TP_Rate				,	// "每日任務TP加乘"

	EM_WearEqType_MaxCount					,	
};	  

#define Max_WearEqType_Count   10   //最多有幾個屬性可加
struct  GameObjectWearEqStruct
{
	WearEqTypeENUM  EqType[ Max_WearEqType_Count ];
	int             EqTypeValue[ Max_WearEqType_Count ];

	int				OnAttackMagicRate;		//發生機率
	int				OnAttackMagicRank;		//互蓋等級
	int				OnAttackMagicID;		//法術號碼
};
//----------------------------------------------------------------------------------------
//物品掉落的結構
//----------------------------------------------------------------------------------------
struct ItemDropStruct
{
	int		OrgID;					//物品號碼
	int		Rate;					//掉落機率
};
//----------------------------------------------------------------------------------------
//屬於Player的基本資料
//----------------------------------------------------------------------------------------
struct GameObjectPlayerStruct
{
	int     None;
};
//----------------------------------------------------------------------------------------
//BodyObj的代表類型列舉
//----------------------------------------------------------------------------------------
enum BodyObjectTypeENUM
{
	EM_BodyObjectType_Hair		= 0,
	EM_BodyObjectType_Face		,
};

//----------------------------------------------------------------------------------------
//屬於BodyObj的基本資料
//----------------------------------------------------------------------------------------
struct GameObjectBodyObjStruct
{
	//int     None;
	BodyObjectTypeENUM Type;

	struct 
	{
		union
		{
			int		Setting;
			struct
			{
				bool	CreateRole		: 1;
				bool	DepartmentStore : 1;
			};
		};
		RaceFlagStruct      Race;
		SexFlagStruct       Sex;

	}Limit;

	int Priority;
};

//----------------------------------------------------------------------------------------
// Quest  詳細內容的資料, 描述了 Quest 開頭 / 過程 / 獎勵
//----------------------------------------------------------------------------------------
struct GameObjectQuestDetail
{
	// 判斷部份
	// 用作 Client 判斷 User 是否可以接 Quest ( 也用做在 Client及小地圖上顯示 )
	//---------------------------------------------------------
	int		iCheck_Class_Type;
	int		iCheck_Class1;
	int		iCheck_Class2;
	int		iCheck_Sex;
	int		iCheck_LV;
	int		iCheck_LowerLV;
	int		iCheck_HigherLV;
	int		iCheck_Title;
	int		iCheck_Group;
	int		iCheck_Flag			[ _MAX_SIZE_QUEST_FLAG		];
	
	int		iCheck_RepGroup;	// 可接任務的聲望群組
	int		iCheck_Rep;			// 聲望要求


	int		iCheck_ObjID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iCheck_ObjVal		[ _MAX_SIZE_QUEST_ITEM		];
	int		iCheck_Loop;


	// 任務說明
	//---------------------------------------------------------
	int		iQuestID;
	char*	szQuest_Name;
	char*	szQuest_Desc;

	char*	szQuest_Accept_Detail;
	char*	szQuest_UnComplete_Detail;
	char*	szQuest_Complete_Detail;

	int		iQuest_Catalog;
	int		iQuest_Type;

	// 接受任務後所置的狀態或給予的物品
	//--------------------------------------------------------
	int		iAccept_FlagOn		[ _MAX_SIZE_QUEST_FLAG		];
	int		iAccept_FlagOff		[ _MAX_SIZE_QUEST_FLAG		];
	int		iAccept_ItemID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iAccept_ItemVal		[ _MAX_SIZE_QUEST_ITEM		];

	// 完成任務所須要的條件
	//--------------------------------------------------------
	int		iRequest_ItemID		[ _MAX_SIZE_QUEST_CONDITION ];
	int		iRequest_ItemVal	[ _MAX_SIZE_QUEST_CONDITION	];
	int		iRequest_KillID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iRequest_KillVal	[ _MAX_SIZE_QUEST_ITEM		];
	int		iRequest_Timer;
	int		iRequest_Money;
	int		iRequest_QuestID;

	// 接受任務後進行任務時, 對特定目標動作, 所產生的影響
	//--------------------------------------------------------
	int		iProcess_ClickToGetItem_ObjID		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_ProcPercent	[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_GetItem		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_GetItemVal	[ _MAX_SIZE_QUEST_CONDITION		];

	int		iProcess_KilltoGetItem_ObjID		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_ProcPercent	[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_GetItem		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_GetItemVal	[ _MAX_SIZE_QUEST_CONDITION		];

	// 完成任務後, 所接收的獎賞
	//--------------------------------------------------------
	int		iReward_ChoiceID	[ _MAX_SIZE_QUEST_ITEM		];
	int		iReward_ChoiceVal	[ _MAX_SIZE_QUEST_ITEM		];
	int		iReward_ItemID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iReward_ItemVal		[ _MAX_SIZE_QUEST_ITEM		];
	int		iReward_Spell		[ _MAX_SIZE_QUEST_ITEM		];
	int		iReward_Money;
	int		iReward_Exp;	
	
	int		iReward_RepGroup	[2];
	int		iReward_Rep			[2];

	// 完成任務後, 所設定的狀態
	//--------------------------------------------------------
	int		iComplete_ShowQuest;
	int		iComplete_FlagOn	[ _MAX_SIZE_QUEST_FLAG		];
	int		iComplete_FlagOff	[ _MAX_SIZE_QUEST_FLAG		];

	// 完成任務後, 所設定的狀態
	//--------------------------------------------------------
	char	szScript_OnBegin		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnAccept		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnComplete		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnClickObjBegin[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnClickObjEnd	[ _MAX_SIZE64_QUEST_SCRIPT ];

	// 每日限制型任務
	//--------------------------------------------------------
	int		iQuestGroup;			// 任務群組限制 0 為不限制群組 1-20 為群組
	int		iControlType;			// 重覆型任務完成時間的限制	0 不限制 1 為每日完成一次 2 為每周完成一次

	int		iRequest_ItemStr		[ _MAX_SIZE_QUEST_CONDITION ];
	int		iRequest_KillStr		[ _MAX_SIZE_QUEST_ITEM		];
	int		iQuestGroupLV;			// 每日任務等級需求
	int		iReward_Honor;
	int		iReward_TP;				// 獎賞 TP 的比例 ( 預設是 10% )

	int		iQuestProvider			[5];
	int		iDeleteQuestItem		[5];
	int		iDeleteQuestItemCount	[5];
	int		iRequestCompleteNPCID	[3];		// 第二組指定完成 NPC
	int		iQuestLinkNPC			[5];

	char	szScript_OnDelete		[ _MAX_SIZE64_QUEST_SCRIPT ];	// 放棄任務所跑的劇情 ( SERVER SIDE )
	int		iCheck_ObjStatus		[ _MAX_SIZE_QUEST_ITEM		];	// 檢查接條件要求或者是禁止

	bool	bDisableTeam;			// 關畢團隊擊殺任務怪設定

	char	szScript_RequestString	[ _MAX_SIZE64_QUEST_SCRIPT ];

	PriceTypeENUM	iReward_CoinType;		//特殊幣值類型
	int				iReward_SpecialCoin;	//特殊幣值

	PriceTypeENUM	iRequest_CoinType;		//特殊幣值類型
	int				iRequest_SpecialCoin;	//特殊幣值

};
//----------------------------------------------------------------------------------------
// 輔助法術類型
//----------------------------------------------------------------------------------------
enum	GameObjectMagicTypeENUM
{
	EM_Magic_Type_NULL	=	-1  ,
	EM_Magic_Type0				,
	EM_Magic_Type1				,
	EM_Magic_Type2				,
	EM_Magic_Type3				,
	EM_Magic_Type4				,
	EM_Magic_Type5				,
	EM_Magic_Type6				,
	EM_Magic_Type7				,
	EM_Magic_Type8				,
	EM_Magic_Type9				,
	EM_Magic_Type10				,
	EM_Magic_Type11				,
	EM_Magic_Type12				,
	EM_Magic_Type13				,
	EM_Magic_Type14				,
	EM_Magic_Type15				,
	EM_GameObjectMagicTypeEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//NPC施法的結構
//----------------------------------------------------------------------------------------
#define	_MAX_NPC_SPELL_MAGIC_COUNT_	8
#define	_MAX_NPC_STEAL_ITEM_COUNT_	3
#define	_MAX_NPC_AVOID_MAGIC_TYPE_COUNT_	5
//施法時機
enum NPCSpellRightTimeENUM
{
	EM_NPCSpellRightTime_None			,//無
	EM_NPCSpellRightTime_Normal			,//一般狀態   (60秒)
	EM_NPCSpellRightTime_OnAttack		,//戰鬥啟動
	EM_NPCSpellRightTime_Attack			,//戰鬥狀態   (1秒)
	EM_NPCSpellRightTime_AttackHPHalf	,//戰鬥HP1/2  (1秒)
	EM_NPCSpellRightTime_AttackHPQuarter,//戰鬥HP1/4  (1秒)
	EM_NPCSpellRightTime_FriendDead		,//友方死亡   (1秒)
	EM_NPCSpellRightTime_KeepDistance	,//保持距離   (1秒)

};
//NPC施法目標
enum NPCSpellTargetENUM
{
	EM_NPCSpellTarget_Self				,//自己
	EM_NPCSpellTarget_Target			,//目標
	EM_NPCSpellTarget_Target_HP_Half	,//目標(HP 1/2)
	EM_NPCSpellTarget_Target_HP_Quarter	,//目標(HP 1/4)
	EM_NPCSpellTarget_Target_Distance_30_,//目標(距離30以上 )
	EM_NPCSpellTarget_Target_Escape		,//目標(逃跑)

	EM_NPCSpellTarget_Friend			,//友方
	EM_NPCSpellTarget_Friend_HP_Half	,//友方(HP 1/2)
	EM_NPCSpellTarget_Friend_HP_Quarter	,//友方(HP 1/4)
	EM_NPCSpellTarget_Enemy				,//敵方
	EM_NPCSpellTarget_Enemy_HP_Half		,//敵方(HP 1/2)
	EM_NPCSpellTarget_Enemy_HP_Quarter	,//敵方(HP 1/4)

	EM_NPCSpellTarget_TargetSpell		,//目標施法	  
	EM_NPCSpellTarget_Enemy_RangeEnemySpell,//仇恨表內的施法目標 
	EM_NPCSpellTarget_Enemy_Second		,//仇恨第二
	EM_NPCSpellTarget_Enemy_Last		,//仇恨最小
	EM_NPCSpellTarget_Enemy_Nearest		,//仇恨表最近的
	EM_NPCSpellTarget_Enemy_Farest		,//仇恨表最遠的

	EM_NPCSpellTarget_Master			,//主人
	EM_NPCSpellTarget_Master_HP_Half	,//主人(HP 1/2)
	EM_NPCSpellTarget_Master_HP_Quarter	,//主人(HP 1/4)

};

struct  NPCSpellBaseStruct
{
	NPCSpellRightTimeENUM	RigthTime;	//施法時機
	NPCSpellTargetENUM		TargetType;	//目標類型
	int		Rate;						//發動機率
	int		MagicID;					//法術
	int		MagicLv;					//法術等級
	char*	SpellString;
};
//----------------------------------------------------------------------------------------
enum	PhyResistTypeENUM
{
	EM_PhyResist_NULL	= -1,	//無
	EM_PhyResist_Hit	,		//打擊
	EM_PhyResist_Cut	,		//砍擊
	EM_PhyResist_Puncture,		//穿刺
	EM_PhyResist_MAX	,
};
//----------------------------------------------------------------------------------------
enum SpecialDropItemTypeENUM
{
	EM_SpecialDropItemType_None				,
	EM_SpecialDropItemType_DepartmentStroe	,
	EM_SpecialDropItemType_NoGlobalDrop		,	//取消世界掉落
};
//----------------------------------------------------------------------------------------
enum NPCCarryTypeENUM
{
	EM_NPCCarryType_None			,
	EM_NPCCarryType_NoControl		,
	EM_NPCCarryType_Control			,
};
//----------------------------------------------------------------------------------------
//屬於NPC的基本資料
//----------------------------------------------------------------------------------------
struct GameObjectNpcStruct
{
	int			Race;					//種族
	int			Vocation;				//職業
	int			Vocation_Sub;			//副職
	int         Sex;                    //性別
	int 		ExpRate;				//怪物打死後可得到的經驗值百分比
	int			TpRate;
	int			Level;					//基本等級
	int         LevelRange;


	int			STR;
	int			STA;
	int			INT;
	int			MND;
	int			AGI;

	int         MoveSpeed;
	int         SearchRange;

	int         DropMoney_Base;
	int         DropMoney_Rand;

	ItemDropStruct DropItem[ _MAX_DROPITEM_COUNT_ ];
	ItemDropStruct DropItemAbility[_MAX_DROP_ABILITY_COUNT_];

	int         MainHandEQ[ _MAX_NPC_EQSEL_COUNT_ ];        //每一個 20 %機會會裝備
	int         SecHandEQ[ _MAX_NPC_EQSEL_COUNT_];          //每一個 20 %機會會裝備

	int			iQuestMode;

	char*		szQuestNpcText;								// 任務 NPC 所說的費話
	char*		szQuestDoingText;
	int			iQuestID[_MAX_NPC_QUEST_COUNT_];			// 任務 NPC 所能給的 Quest

	int         Brave;              //勇敢度
	int         LinkType;           //怪物連鎖類型
	int			EscapeType;			//逃跑類型


	NPCSpellBaseStruct		Spell[_MAX_NPC_SPELL_MAGIC_COUNT_];

	NpcTitleTypeENUM		TitleType;
	//GameObjDbStruct*		pQuestLink[ _MAX_QUESTLINK_COUNT ];
	int						iQuestLinkObj[ _MAX_QUESTLINK_COUNT ];


	int			iQuestNPCRefID;

	int					DB_ResistID;				//資料庫類型id(呼略)
	MagicResistENUM		ResistType;					//NPC的屬性	
	MagicResistStruct	Resist;						//抗性值

	char		szLuaScript[_MAX_SIZE64_QUEST_SCRIPT];						// 初始化劇情或對話時所載入的 LUA

	//可被偷竊的物品
	ItemDropStruct			StealItem[ _MAX_NPC_STEAL_ITEM_COUNT_ ];

	//可被偷竊的金錢
	int         StealMoney_Base;
	int         StealMoney_Rand;

	//無效法術
	GameObjectMagicTypeENUM	AvoidMagicType[_MAX_NPC_AVOID_MAGIC_TYPE_COUNT_];			

	MagicEffectStruct	Effect;						//有效的的法術效果

	int			RaceGroupType;						//連鎖幫助的群組
	int			iQuestObjType;						//任物物件點選後是否會消失

	int			KeepDistance;						//戰鬥時 保持距離

	GameObjectWeaponENUM	OrgWeaponType;			//武器類型
	GameObjectArmorENUM     OrgArmorType;			//防具類型

	int			FollowRange;						//可追逐距離

	int			RaiseChangeNPCID[2];
	int			RaiseChangeRate[2];					//十萬分之一

	bool		IsAbilityStandard;					//是否為標準數值
	int			AbilityValue[2];					//參考數職

	GameObjectWearEqStruct	Ability;				//附加能力	

//	bool		IsNoMPSP;							//沒有MPSP

	char*		TitleName;							//npc頭銜

	float		PhyResistRate[ EM_PhyResist_MAX ];	//物理抗性

	int			QuestObjCraftMode;					// 任務物件是否是協助制造工具

	int			ZoneID;								//npc所在的位置
	int			X , Y , Z;

//	bool		IsAllZoneVisible;					//全區顯示
//	bool		IsShowNpcPos;
//	bool		AutoRotate;							//施法自動面向

	int			ZoneID_Bk;							//企畫設定的區域資料
	int			BowEQ;								//裝備弓欄位
	CampID_ENUM	CampID;
	int			KillGroupID;						//殺死記數 -1 不處理	

	char		szLuaInitScript[_MAX_SIZE64_QUEST_SCRIPT];						// 預設初始化劇情資料
	int			AddPowerLV;							//掉落等級增加
	
	char		LuaEvent_OnAttackMagic[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnAssistMagic[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnDead[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnKill[_MAX_SIZE64_QUEST_SCRIPT];

	StructNPCOtherFlag			OtherFlag;
	//bool		IsShowMaster;						//顯示主人資訊
	int			DEqTypeValue[10];					//能力微調
	SpecialDropItemTypeENUM SpecialDropItemType;
	int			MinAbilityLv;
	int			OrnamentEQ;							//裝飾品

	char		szLuaDisplayScript[_MAX_SIZE64_QUEST_SCRIPT];						// 預設初始化劇情資料

	union
	{
		int		_NpcMode;
		struct	
		{
			bool		IsNoMPSP			:1;			//沒有MPSP
			bool		IsAllZoneVisible	:1;			//全區顯示
			bool		IsShowNpcPos		:1;
			bool		AutoRotate			:1;			//施法自動面向
			bool		IsShowMaster		:1;			//顯示主人資訊
			bool		NoRandReborn		:1;			//不亂數位置重生
			bool		ClientDelNoWaitting	:1;			//物件刪除時立即不見
			bool		Prompt				:1;			//接近時提示
			bool		Treasure			:1;			//寶箱
			bool		SearchEnemyAllDir	:1;			//索敵忽略面向
			bool		HideRaceInfo		:1;			//不顯示種族
			bool		IgnoreNpcKill		:1;			//(掉寶)忽略怪物殺死
			bool		IgnoreQuestObjEffect:1;			//(任務)任務物件時不發光
			bool		IsAttackFirst		:1;			//(Client)攻擊判斷優先
			bool		Invisible_InWagon	:1;			//(Client)載具內看不見
			bool		ReCalPath			:1;			//公會戰需要重算路徑的物件
			bool		DisableTreasureDrop	:1;			//不會掉寶
			bool		IsTrapObj			:1;			//(client)陷阱物件
			bool		NoFadein			:1;			//(client)不淡入
			bool		IgnorePvPRule		:1;			//忽略現行犯處理
			bool		RideAttackable		:1;			//載具會被攻擊
			bool		ScriptFlag			:1;			//小怪清除卷,需要清除
			bool		NoReturnAttackPoint	:1;			//不回到開始戰鬥點
		};
	};

	int					iTagID;							// 版本控制 TAG
	int					CarryCount;
	NPCCarryTypeENUM	CarryType;						//載具類型
	int					SearchGroupID;
	char				CarryLuaScript[_MAX_SIZE64_QUEST_SCRIPT];	//上下載具觸發劇情					
	int					CarryShootRange;
	int					CarryShootAngle;
	GameObjectWearEqStruct	AbilityEx;				//附加能力	

	char				LuaEvent_BeginAttack[_MAX_SIZE64_QUEST_SCRIPT];
	char				LuaEvent_EndAttack[_MAX_SIZE64_QUEST_SCRIPT];
	char				CheckCarryLuaScript[_MAX_SIZE64_QUEST_SCRIPT];	//上下載具觸發劇情
	char				CheckCarryLuaPoint[_MAX_FILENAME_SIZE_];		//參考點

	void		Init()
	{
		char*				_szQuestNpcText		= szQuestNpcText;
		char*				_szQuestDoingText	= szQuestDoingText;
		char				_szLuaScript[ _MAX_SIZE64_QUEST_SCRIPT ];
	
		char*				_szTitleName		= TitleName;


		//GameObjDbStruct*	_pQuestLink[ _MAX_QUESTLINK_COUNT ];
		int					_iQuestLinkObj[ _MAX_QUESTLINK_COUNT ];
		int					_iQuestID[20];

		int					_iQuestMod			= iQuestMode;
		int					_iQuestNPCRefID		= iQuestNPCRefID;
		int					_iQuestObjType		= iQuestObjType;
		int					_QuestObjCraftMode	= QuestObjCraftMode;

		int					_ZoneID				= ZoneID;
		int					_X					= X;
		int					_Y					= Y;
		int					_Z					= Z;
		//bool				_IsAllZoneVisible    = IsAllZoneVisible;
		int					_TempNpcMode		= _NpcMode;

		memcpy( _iQuestLinkObj ,	iQuestLinkObj,		sizeof(iQuestLinkObj) );
		memcpy( _iQuestID ,		iQuestID,		sizeof(_iQuestID) );
		memcpy(	_szLuaScript , szLuaScript ,	sizeof(szLuaScript) );

		//memset( this , 0 , sizeof(*this) );							  

		szQuestNpcText		= _szQuestNpcText;
		szQuestDoingText	= _szQuestDoingText;
		iQuestMode			= _iQuestMod;
		iQuestNPCRefID		= _iQuestNPCRefID;
		iQuestObjType		= _iQuestObjType;
		TitleName			= _szTitleName;
		QuestObjCraftMode	= _QuestObjCraftMode;
//		IsAllZoneVisible    = _IsAllZoneVisible;
		_NpcMode			= _TempNpcMode;

		ZoneID				= _ZoneID;
		X					= _X;
		Y					= _Y;
		Z					= _Z;

		memcpy( _iQuestLinkObj, iQuestLinkObj,	sizeof(iQuestLinkObj) );		
		memcpy( iQuestID,	_iQuestID,		sizeof(_iQuestID) );
		memcpy( szLuaScript,_szLuaScript,	sizeof(_szLuaScript) );
	}

};
//----------------------------------------------------------------------------------------
//附加屬性的基本資料
//----------------------------------------------------------------------------------------
enum  MagicActionTypeENUM
{   
    EM_MagicAction_Attack           ,
    EM_MagicAction_UnderAttack      ,
    EM_MagicAction_EQ               ,
    EM_MagicAction_Used             ,
};

enum    AttributeTypeENUM
{
    EM_AttributeType_AddPower   ,
    EM_AttributeType_Rune       ,
    EM_AttributeType_Title      ,
};

/*
enum AddonPosENUM
{
	EM_AddonPos_None = -1		,
	EM_AddonPos_Head    		,
	EM_AddonPos_Gloves			,
	EM_AddonPos_Shoes			,
	EM_AddonPos_Clothes			,
	EM_AddonPos_Pants			,
	EM_AddonPos_Back			,
	EM_AddonPos_Belt			,
	EM_AddonPos_Shoulder		,
	EM_AddonPos_Necklace		,
	EM_AddonPos_Ring    		,
	EM_AddonPos_Earring 		,
	EM_AddonPos_Shield			,
	EM_AddonPos_Weapon  		,
	EM_AddonPos_Max		  		,
};
/*
struct  AddonPosTypeStruct
{
    union
    {
        int _Type;
        struct
        {
            bool    Head        : 1;
            bool    Gloves	    : 1;
            bool    Shoes	    : 1;
            bool    Clothes	    : 1;
            bool    Pants	    : 1;
            bool    Back	    : 1;
            bool    Belt	    : 1;
            bool    Shoulder    : 1;
            bool    Necklace    : 1;
            bool    Ring        : 1;
            bool    Earring     : 1;
			bool	Shield		: 1;
            bool    Weapon      : 1;
        };
    };
};
*/

enum AddonPos_ArmorPosENUM
{
	EM_AddonPos_ArmorPos_None = -1		,
	EM_AddonPos_ArmorPos_Head			,
	EM_AddonPos_ArmorPos_Gloves			,
	EM_AddonPos_ArmorPos_Shoes			,
	EM_AddonPos_ArmorPos_Clothes		,
	EM_AddonPos_ArmorPos_Pants			,
	EM_AddonPos_ArmorPos_Belt			,
	EM_AddonPos_ArmorPos_Shoulder		,
	EM_AddonPos_ArmorPos_Max			,
};

enum AddonPos_ArmorTypeENUM
{
	EM_AddonPos_ArmorType_None = -1		,
	EM_AddonPos_ArmorType_HeavyArmed	,
	EM_AddonPos_ArmorType_LightArmed	,
	EM_AddonPos_ArmorType_Leather		,
	EM_AddonPos_ArmorType_Clothes		,
	EM_AddonPos_ArmorType_Robe			,
	EM_AddonPos_ArmorType_Max			,
};

enum AddonPos_WeaponLimitPosENUM
{
	EM_AddonPos_WeaponLimitPos_None			,
	EM_AddonPos_WeaponLimitPos_MainHand		,
	EM_AddonPos_WeaponLimitPos_OffHand		,

};

enum AddonPos_WeaponTypeENUM
{
	EM_AddonPos_WeaponType_None = -1	,
	EM_AddonPos_WeaponType_Unarmed	,
	EM_AddonPos_WeaponType_Blade     ,
	EM_AddonPos_WeaponType_Dagger    ,
	EM_AddonPos_WeaponType_Wand      ,
	EM_AddonPos_WeaponType_Axe       ,
	EM_AddonPos_WeaponType_Bludgeon  ,
	EM_AddonPos_WeaponType_Claymore  ,
	EM_AddonPos_WeaponType_Staff     ,
	EM_AddonPos_WeaponType_Axe_2H    ,
	EM_AddonPos_WeaponType_Hammer_2H ,
	EM_AddonPos_WeaponType_Polearm	,
	EM_AddonPos_WeaponType_Bow		,
	EM_AddonPos_WeaponType_CossBow	,
	EM_AddonPos_WeaponType_Gun		,
	EM_AddonPos_WeaponType_Max		,
};

enum AddonPos_OtherENUM
{
	EM_AddonPos_Other_None = -1		,
	EM_AddonPos_Other_Back			,
	EM_AddonPos_Other_Necklace		,
	EM_AddonPos_Other_Ring			,
	EM_AddonPos_Other_Earring		,
	EM_AddonPos_Other_Shield		,
	EM_AddonPos_Other_Implement		,
	EM_AddonPos_Other_Max			,
};


struct AddonPosTypeStruct
{
	union
	{
		int _ArmorPos;
		struct  
		{
			bool	Head		: 1;
			bool    Gloves	    : 1;
			bool    Shoes	    : 1;
			bool    Clothes	    : 1;
			bool    Pants	    : 1;
			bool    Belt	    : 1;
			bool    Shoulder    : 1;
		}ArmorPos;
	};

	union
	{
		int _ArmorType;
		struct  
		{
			bool	HeavyArmed	: 1;
			bool    LightArmed	: 1;
			bool    Leather		: 1;
			bool    Clothes		: 1;
			bool    Robe		: 1;
		}ArmorType;
	};

	union
	{
		int	_WeaponType;
		struct  
		{
			bool	Unarmed		: 1;	
			bool    Blade       : 1;      
			bool    Dagger      : 1;      
			bool    Wand        : 1;      
			bool    Axe         : 1;      
			bool	Bludgeon    : 1;      
			bool    Claymore    : 1;      
			bool    Staff       : 1;      
			bool    Axe_2H      : 1;      
			bool    Hammer_2H   : 1;      
			bool	Polearm		: 1;	
			bool    Bow			: 1;	
			bool    CossBow		: 1;	
			bool    Gun			: 1;	
		}WeaponType;
	};

	AddonPos_WeaponLimitPosENUM  WeaponPosEnum;	// 0 不限制 1 主手 2　附手
	int			Level;							// 物品等級
	union
	{
		int _Other;
		struct  
		{
			bool	Back		: 1;
			bool	Necklace	: 1;
			bool	Ring		: 1;
			bool	Earring		: 1;
			bool	Shield		: 1;
			bool	Implement	: 1;
			bool	Ornament	: 1;
		}Other;
	};

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
//		_WeaponType = -1;
//		_ArmorType	= -1;
//		_ArmorPos	= -1;
//		_Other		= -1;
	}

	
};



struct	GameObjectAttributeStruct
{
    AttributeTypeENUM   Type;   //附加能力類型

//	int		InheritRate;		//繼承機率(萬分之一)
//  int		InheritLV;			//繼承等級
//  int     InheritLV_Range;    //範圍

    int     Inc_Magic;          //內含的法術
    int     Inc_Magic_ActionRate;//法術發生機率( 攻擊 被攻擊 )

    MagicActionTypeENUM     Inc_MagicType;
    AddonPosTypeStruct      AddPos;             //可裝備部位

	GameObjectWearEqStruct	Ability;
	//--------------------------------------------------------------------------------------
	//能力標準型
	bool					IsStandardAbility;
	int						StandardAbility_Lv;
	int						StandardAbility_ArgType[5];
	float					StandardAbility_Arg[5];
	//--------------------------------------------------------------------------------------
	int						StarValue;		//星等值
	bool					IsBirthAbility;
	int						InherentValue;	//繼承等級 -1 不繼承
	int						Rarity;			//稀有度(0:無 1:綠 2:黃 3:橘…)
};
//----------------------------------------------------------------------------------------
// 精練能力表
//----------------------------------------------------------------------------------------
enum EqRefineAttributeTypeENUM
{
	EM_EqRefineAttributeType_Weapon		,	//武器
	EM_EqRefineAttributeType_Staff		,	//法杖類
	EM_EqRefineAttributeType_Bow		,	//遠距離武器
	EM_EqRefineAttributeType_Head       ,   //頭
	EM_EqRefineAttributeType_Gloves	    ,   //手套
	EM_EqRefineAttributeType_Shoes	    ,   //鞋子
	EM_EqRefineAttributeType_Clothes	,   //上衣
	EM_EqRefineAttributeType_Pants	    ,   //褲子
	EM_EqRefineAttributeType_Back	    ,   //背部q
	EM_EqRefineAttributeType_Belt	    ,   //腰帶
	EM_EqRefineAttributeType_Shoulder   ,   //肩甲
	EM_EqRefineAttributeType_Necklace   ,   //項鍊 
	EM_EqRefineAttributeType_Ring       ,   //戒子
	EM_EqRefineAttributeType_Earring    ,   //耳飾
	EM_EqRefineAttributeType_SecondHand ,   //副手
};

struct	GameObjectEqRefineAttributeStruct
{
	EqRefineAttributeTypeENUM	Type;
	int							Level;
	GameObjectWearEqStruct		Ability;
	int							ExEqPowerRate;	//額外增加裝備基本能力百分比(DMG MDMG DEF MDEF )
};
//----------------------------------------------------------------------------------------
//礦產設定
//----------------------------------------------------------------------------------------
enum GameObjectMineType
{
    EM_GameObjectMineType_Mine      ,
    EM_GameObjectMineType_Wood      ,
    EM_GameObjectMineType_Herb      ,
    EM_GameObjectMineType_Fish      ,
    EM_GameObjectMineTypeENUM_FORCE_DWORD   = 0x7fffffff, 
};

enum GameObjectCreateType
{
    EM_GameObjectCreateType_Always      ,           //永遠存在
    EM_GameObjectCreateType_EmptyDel    ,           //取完刪除
    EM_GameObjectCreateTypeENUM_FORCE_DWORD   = 0x7fffffff, 
};

struct	GameObjectMineStruct
{   
    GameObjectMineType      Type;
    float                   BaseCount;                      // 初始量
    GameObjectCreateType    CreateType;                     // 是否消失
	int                     LvLimit;                        // 等級限制

    int					    GetItem[7];                     // 取得物品 ..(怪物則是產生)
    int				        GetItemRate[7];                 // 產生率
    int			            GetItemCount[7];                // 數量
	int						iFlagID;						// 重生參考旗子, ( 無作用 )


	int						iReduceVal;						// 減少初始量的偏移值
	int						iGenerateObj[5];				// 重生後, 產生的物件
	int						iGenerateObjRate[5];			// 重生後, 產生的物件的機率

	char					szLuaGetItemScript[_MAX_SIZE64_QUEST_SCRIPT];						// 初始化劇情或對話時所載入的 LUA
};
//----------------------------------------------------------------------------------------
//重要物品
//----------------------------------------------------------------------------------------
enum	KeyItemTypeENUM
{
	EM_KeyItemType_Invisible		,
	EM_KeyItemType_Normal			,	//一般
	EM_KeyItemType_Key				,	//鑰匙
	EM_KeyItemType_Map				,	//地圖
	EM_KeyItemType_SkillBook		,	//技能書
	EM_KeyItemType_Recipe			,	//配方表
	EM_KeyItemType_LifeSkillUnLock	,	//設定生
	EM_KeyItemType_DailyFlag		,	//每日重制重要物品
};
//----------------------------------------------------------------------------------------
struct	GameObjectKeyItemStruct
{
    KeyItemTypeENUM     Type;
    int					QuestID;

	SkillValueTypeENUM	LifeSkillType;
	int					LifeSkillLearnLV;
	int					LifeSkillMaxLV;
};
//----------------------------------------------------------------------------------------
//配方表
//----------------------------------------------------------------------------------------
#define _MAX_RECIPE_SOURCE_COUNT_	8
struct RecipeItemStruct
{
    int     OrgObjID;   //樣板物件
    int     Count;      //數量
    int     Rate;       //產生率(百分之一)
};
struct GameObjectRecipeStruct
{
	
    RecipeItemStruct Source[ _MAX_RECIPE_SOURCE_COUNT_ ];                 //原料

	union
	{
		RecipeItemStruct ItemAll[9];              //產生物品一

		struct 
		{
			union
			{
				RecipeItemStruct Item1[6];              //產生物品一
				struct
				{
					RecipeItemStruct Item1_Normal;
					RecipeItemStruct Item1_HQ;
					RecipeItemStruct Item1_Slot1;
					RecipeItemStruct Item1_Slot2;
					RecipeItemStruct Item1_Slot3;
					RecipeItemStruct Item1_Slot4;

				};
			};

			union
			{
				RecipeItemStruct ItemOther[3];                  //產生物品2-4
				struct  
				{
					RecipeItemStruct Item2;                     //產生物品2
					RecipeItemStruct Item3;                     //產生物品3
					RecipeItemStruct Item4;                     //產生物品4
				};

			};
		};

	};
	
	//需求
	struct
	{
		SkillValueTypeENUM		Skill;				//技能種類
		int						SkillLV;			//技能等級
		int						KeyItemID;			//重要物品
	}Request;

	int	Coldown;	//冷卻時間(秒)

	int	Type;		//企劃設定的類型
	int	RequestCraftObjType;

	float						ExpRate;			//合成所得exp倍率

	int	LearnFee;									// 學習配方時, 所需費用
	int CraftFee;									// 制造物品時, 所需費用

};
//----------------------------------------------------------------------------------------
//頭銜資料
//----------------------------------------------------------------------------------------
enum TitleClassifyENUM
{
	EM_TitleClassify_Quest			,
	EM_TitleClassify_Challenge		,
	EM_TitleClassify_Item			,
	EM_TitleClassify_Sys			,
	EM_TitleClassify_Activitie		,
};
enum TitleNameTypeENUM
{
	EM_TitleNameType_Famous		,
	EM_TitleNameType_Job		,
	EM_TitleNameType_Plot		,
	EM_TitleNameType_KillCount	,
	
};
enum KillCountTypeENUM
{
	EM_KillCountType_KillCount	,
	EM_KillCountType_DeadCount	,
};
struct  GameObjectTitleStruct
{
    TitleNameTypeENUM     Type;                   //企劃分類用(暫時無用)
    //=----------------------------------
    //需求
    //=----------------------------------
	struct
	{
		int			Famous;                 
		Voc_ENUM    MainJob;
		int			MainJobLV;
		Voc_ENUM    SubJob;
		int			SubJobLV;            
	};

	struct 
	{
		KillCountTypeENUM		Type;			// 0 殺死怪物 1 被怪物殺
		int						KillGroupID;	//
		int						Count;			//數量

	}KillCount;
	//=----------------------------------
    GameObjectWearEqStruct	Ability;

	//可使用技能
	int		SkillID;							//可使用技能
	int		SkillLv;							//技能等級

	int		Classify[2];

	char	LuaEvent[_MAX_SIZE64_QUEST_SCRIPT];

	GameObjectWearEqStruct	AbilityEx;			//新頭銜系統增加能力
	char*	TitleSysNote;						//新頭銜系統 註解

    char	TitleSysLuaEvent[_MAX_SIZE64_QUEST_SCRIPT];
};
//----------------------------------------------------------------------------------------
//圖型設定
//----------------------------------------------------------------------------------------
enum GameObjectImageTypENUM
{
    EM_GameObjectImageType_Normal   ,
    EM_GameObjectImageType_Magic    ,
    EM_GameObjectImageType_Armor    ,
	EM_GameObjectImageType_Weapon   ,
    EM_GameObjectImageType_Flag     ,
	EM_GameObjectImageType_Wing		 ,

    EM_GameObjectImageTypeENUM_FORCE_DWORD   = 0x7fffffff,
};

enum ArgumentPointENUM 
{
    EM_Argument_Null		= 0	,
    EM_Argument_Hit_Point		,
    EM_Argument_Back_Staff		,
    EM_Argument_Back_Shield		,
    EM_Argument_Back_Sworld		,
    EM_Argument_Name_Title		,
    EM_Argument_Hand_Shield		,
    EM_Argument_Left_Hand		,
    EM_Argument_Right_Hand		,
    EM_Argument_Left_Foot		,
    EM_Argument_Right_Foot		,
    EM_Argument_Left_Weapon		,
    EM_Argument_Right_Weapon	,
};

/*
enum MotionENUM 
{
    EM_Motion_Null			= 0	,
    EM_Motion_Casting_Delay		,				// "casting_delay" 施法等待
    EM_Motion_Cast_01			,				// "cast01" 出手對自身
    EM_Motion_Cast_02			,				// "cast02" 出手對目標	
};
*/
//----------------------------------------------------------------------------------------
enum ObjectImageTypeENUM 
{
    EM_ObjectImage_2Foots		,  //人類
    EM_ObjectImage_4Foots		,  //爬蟲類
	EM_ObjectImage_4Foots2		,  //馬類
};
//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
struct MagicPartical
{
    char				Point[_MAX_FILENAME_SIZE_];	// 考點位置
    char				Name[_MAX_FILENAME_SIZE_];	// 特效名稱
	bool				IsSoundEnabled;				// 生音開關
};
//----------------------------------------------------------------------------------------
struct ColorStruct
{
	union
	{
		unsigned int Color;
		struct 
		{
			unsigned char B;
			unsigned char G;
			unsigned char R;
			unsigned char A;
		};
	};
};
//----------------------------------------------------------------------------------------
//紙娃娃資料
struct	PaperdollStruct
{
	char			Name[ 64 ];		
	ColorStruct		MainColor;					
	ColorStruct		OffColor;
};
//----------------------------------------------------------------------------------------
enum GameObjectImageArmorPosENUM
{
	EM_GameObjectImageArmorPos_Clothes,	//上衣
	EM_GameObjectImageArmorPos_Gloves,	//手套
	EM_GameObjectImageArmorPos_Shoulder,//肩甲
	EM_GameObjectImageArmorPos_Back,	//背部
	EM_GameObjectImageArmorPos_Belt,	//腰帶
	EM_GameObjectImageArmorPos_Shoes,	//鞋子
	EM_GameObjectImageArmorPos_Pants,	//褲子
	EM_GameObjectImageArmorPos_Head,	//頭
	EM_GameObjectImageArmorPos_Hair,	//頭髮
	EM_GameObjectImageArmorPos_Face,	//臉
};
/*
enum GameObjectImageArmorPosENUM
{
EM_GameObjectImageArmorPos_Hair,	//頭髮
EM_GameObjectImageArmorPos_Face,	//臉
EM_GameObjectImageArmorPos_Head,	//頭
EM_GameObjectImageArmorPos_Gloves,	//手套
EM_GameObjectImageArmorPos_Shoes,	//鞋子
EM_GameObjectImageArmorPos_Clothes,	//上衣
EM_GameObjectImageArmorPos_Pants,	//褲子
EM_GameObjectImageArmorPos_Back,	//背部
EM_GameObjectImageArmorPos_Belt,	//腰帶
EM_GameObjectImageArmorPos_Shoulder,//肩甲

};
*/

enum GameObjectImageIconTypeENUM
{
	EM_GameObjectImageIconType_Money,		// 金錢
	EM_GameObjectImageIconType_RuneMoney,	// 符文幣
	EM_GameObjectImageIconType_Bonus,		// 紅利幣
};

//----------------------------------------------------------------------------------------
enum GameObjectMagicShowTypeENUM
{
	EM_GameObjectMagicShowType_Single,				// 飛行特效只對單一目標
	EM_GameObjectMagicShowType_Multi,				// 飛行特效對多個目標
	EM_GameObjectMagicShowType_PolyLine,			// 串連特效對多個目標
	EM_GameObjectMagicShowType_Parabola,			// 拋物線(單一目標投擲)
	EM_GameObjectMagicShowType_ParabolaMulti,		// 拋物線(多對向目標投擲)

	EM_GameObjectMagicShowType_FORCEINT	= 0x7FFFFFFF,
};

enum GameObjectCursorAnchorENUM
{
	EM_GameObjectCursorAnchor_None			,	//沒有
	EM_GameObjectCursorAnchor_Cursor		,	//游標
	EM_GameObjectCursorAnchor_RightBottom	,	//右下
};

// 騎乘時角色動作
enum GameObjectMountRideMotion
{
	EM_GameObjectMountRideMotion_Ride		,		// 原始騎乘動作(雙腳張開)
	EM_GameObjectMountRideMotion_Ride1		,		// 原始騎乘動作(雙腳夾緊)
	EM_GameObjectMountRideMotion_Stand		,		// 站立在移動物件
	EM_GameObjectMountRideMotion_Sit		,		// 坐下飛毯類型	
	EM_GameObjectMountRideMotion_Ride2		,		// 座椅坐姿類型
	EM_GameObjectMountRideMotion_FORCEINT	= 0x7FFFFFFF,
};

//----------------------------------------------------------------------------------------
struct GameObjectImageStruct
{
    GameObjectImageTypENUM          ImageType;                      //顯示模式

    char							ACTField[_MAX_FILENAME_SIZE_];	//物品欄位的 ACT 2D
    char							ACTWorld[_MAX_FILENAME_SIZE_];	//顯像ACT
    int 							ModelSize;			            //放大倍率
    int                             BoundRadiusX;                   //碰撞半徑
	int                             BoundRadiusY;                   //碰撞半徑
    //-----------------------------------------------------------------------------------------
    //裝備資料
    //-----------------------------------------------------------------------------------------
    GameObjectImageArmorPosENUM     ArmorPos;
	ColorStruct						ArmorMainColor;					
	ColorStruct						ArmorOffColor;
    //-----------------------------------------------------------------------------------------
    //法術圖型資訊
    //-----------------------------------------------------------------------------------------
    // 對施法者自身
    char							GatherMotion[_MAX_FILENAME_SIZE_];		// 集氣動作
    MagicPartical					GatherPartical[3];						// 集氣特效

	// BeginACT 遊戲內沒有使用到
	char							BeginACT[_MAX_FILENAME_SIZE_];			// 出手特效ACT

	// 
#pragma pack(1)
	union 
	{
		char						BeginPoint[_MAX_OBJ_NAME_STR_SIZE_];	// 對象參考點位置
		struct 
		{
			GameObjectMountRideMotion RideMotion;
		};
	};	
#pragma pack()
    // 出手	
    char							ShootMotion[_MAX_FILENAME_SIZE_];		// 出手動作
    int 							ShootMotionScale;						// %
    char							ShootACT[_MAX_FILENAME_SIZE_];			// 出手特效ACT
	char							ShootPoint[_MAX_OBJ_NAME_STR_SIZE_];	// 對象參考點位置

    // 飛行
	char							FlyBeginPoint[_MAX_OBJ_NAME_STR_SIZE_];	// 指定飛行特效開始所在角色參考點位置
    char							FlyACT[_MAX_FILENAME_SIZE_];			// 飛行特效ACT

    // 目的
    char							ExplodeACT[_MAX_FILENAME_SIZE_];		// 目的爆炸效果ACT
	char							TargetPoint[_MAX_OBJ_NAME_STR_SIZE_];	// 對象參考點位置

	// 延伸目的特效,主要用以當目地特效撥放時,臨近物件受撥及所要做的效果表現
	// 比如目的產生大爆炸特效,延伸則產生燃燒特效
	char							ExtendACT[_MAX_FILENAME_SIZE_];			// 延伸目的特效ACT
	char							ExtenPoint[_MAX_OBJ_NAME_STR_SIZE_];	// 延伸對象參考點位置

	// Buff
	char							BuffACT[_MAX_FILENAME_SIZE_];			// Buff效果ACT	
	char							BuffPoint[_MAX_OBJ_NAME_STR_SIZE_];		// Buff效果對象參考點位置
    //-----------------------------------------------------------------------------------------
    //物件類型
    //-----------------------------------------------------------------------------------------
    ObjectImageTypeENUM             ObjectType;                             //是兩腳還是四角動物
	//-----------------------------------------------------------------------------------------
	char							Sound[_MAX_FILENAME_SIZE_];				//聲音

	//NPC裝備資料
	union
	{
		PaperdollStruct Paperdoll[10];
		struct 
		{
			PaperdollStruct		PaperdollHair;
			PaperdollStruct		PaperdollFace;
			PaperdollStruct		PaperdollHead;
			PaperdollStruct		PaperdollGloves;
			PaperdollStruct		PaperdollShoes;
			PaperdollStruct		PaperdollClothes;
			PaperdollStruct		PaperdollPants;
			PaperdollStruct		PaperdollBack;
			PaperdollStruct		PaperdollBelt;
			PaperdollStruct		PaperdollShouder;
		};
	};
	//-----------------------------------------------------------------------------------------
	union
	{
		ColorStruct ColorArr[2];
		struct 
		{
			ColorStruct SkinColor;
			ColorStruct HairColor;
		};
	};
	union
	{
		int			BoneScale[5];			//骨架縮放
		struct 
		{
			int	BoneScaleChest;				//胸
			int	BoneScaleButtock;			//臀
			int	BoneScaleHand;				//手
			int	BoneScaleLeg;				//角
			int	BoneScaleBra;				//胸罩
		};
	};
	int			Alpha;						//半透明

	GameObjectCursorAnchorENUM	TipType;	//註解方式
	bool		IsShowShadow;
	bool		IsThrowType;				//是否出手動作要用組合的字串
	int			ThrowTypePreviewID;

	struct		
	{
		char	Type[16];
		char	Insignia[16];
		char	Banner[16];
		int		InsigniaColor[2];
		int		BannerColor[2];
	}Flag;

	SexFlagStruct					LimitSex;
	bool							IsPolyLineEffect;		//是否為串連特效
	GameObjectMagicShowTypeENUM		MagicShowType;			//法術顯示方式
	bool							IsHideWeapon;			// 隱藏武器
	GameObjectImageIconTypeENUM		SmallIconType;			//金錢小圖示

	char							BuffACTEx[_MAX_FILENAME_SIZE_];			// Buff效果ACT
	char							PhantomImg[_MAX_FILENAME_SIZE_];		//幻靈大頭圖


};


//----------------------------------------------------------------------------------------
//使用限制結構
//----------------------------------------------------------------------------------------
struct LimitStruct
{
    VocationFlagStruct  Voc;
    RaceFlagStruct      Race;
    SexFlagStruct       Sex;
    int     Level;
    int     STR;
    int     STA;
    int     INT;
    int     MND;
    int     AGI;
};
//----------------------------------------------------------------------------------------
//企劃物品規類
//----------------------------------------------------------------------------------------
enum ItemType_ENUM
{
    EM_ItemType_Normal          	, //一般
    EM_ItemType_Plot            	, //劇情物品
    EM_ItemType_Food            	, //食物
    EM_ItemType_SweetFood       	, //甜食
    EM_ItemType_Water           	, //藥水
    EM_ItemType_Ore             	, //礦石
    EM_ItemType_Wood            	, //木材
    EM_ItemType_Herb            	, //藥草
    EM_ItemType_Hunt            	, //獵物
    EM_ItemType_Seed            	, //種子
    EM_ItemType_Flowerpot       	, //花盆
    EM_ItemType_Crop            	, //作物
    EM_ItemType_Fish            	, //魚
    EM_ItemType_Tool            	, //採集工具
    EM_ItemType_Stuff           	, //製造材料
    EM_ItemType_Recipe_BlackSmith   , //配方 打鐵
	EM_ItemType_Recipe_Carpenter    , //配方 木工
	EM_ItemType_Recipe_Armor     	, //配方 製甲
	EM_ItemType_Recipe_Tailor     	, //配方 裁縫
	EM_ItemType_Recipe_Alchemy     	, //配方 煉金
	EM_ItemType_Recipe_Cook     	, //配方 烹飪
    EM_ItemType_Jewel           	, //衝等寶石
    EM_ItemType_PowerLight      	, //效果光球
    EM_ItemType_Money           	, //金錢
	EM_ItemType_Rune	           	, //符文
	EM_ItemType_PosRecord			, //位置記錄
	EM_ItemType_GuildContribution	, //公會貢獻品
	EM_ItemType_Lottery				, //樂透彩卷
	EM_ItemType_Furniture			, //家俱
	EM_ItemType_SpecialRune			, //特殊符文
	EM_ItemType_SmeltStone			, //熔解石
	EM_ItemType_Relation			, //關係物品
	EM_ItemType_SummonHorse			, //招換座騎
	EM_ItemType_Contract			, //房屋契約
	EM_ItemType_Study				, //修煉百科
	EM_ItemType_MagicStone			, //魔石
	EM_ItemType_Collection			, //委託收集
	EM_ItemType_Packet				, //包裹物品
	EM_ItemType_Pet					, //寵物物品
	EM_ItemType_Pet_Tools			, //寵物工具
	EM_ItemType_Pet_Furniture		, //寵物傢俱
	EM_ItemType_Pet_Food			, //寵物食物
	EM_ItemType_Packet_DropList		, //打包物(掉落表所有東西)
	EM_ItemType_Egg					, //商城轉蛋
	EM_ItemType_ViewPet				, //觀賞用寵物
	EM_ItemType_TitleItem			, //頭銜系統物品
};
enum RareType_ENUM
{
    EM_RareType_Normal      ,
    EM_RareType_Good        ,
    EM_RareType_Magic       ,
    EM_RareType_Legend      ,
    EM_RareType_FORCE_DWORD   = 0x7fffffff, 
};

enum RuneType_ENUM
{
	EM_RuneType_Manufacture		,//生產
	EM_RuneType_Weapon			,//武器
	EM_RuneType_Armor			,//防具
	EM_RuneType_Head			,//頭部
	EM_RuneType_Body			,//上身
	EM_RuneType_Pant			,//下身
	EM_RuneType_Special			,//特殊
	EM_RuneType_Ornament		,//飾品
	EM_RuneType_Shield			,//盾
	EM_RuneType_MagicTools		,//法器
	EM_RuneType_NewSystem		,//雕文系統
};	

enum ItemUseType_ENUM
{
	EM_ItemUseType_None				,
	EM_ItemUseType_Magic			,
	EM_ItemUseType_SrvScript		,
	EM_ItemUseType_CliScript		,
	EM_ItemUseType_EqRefine			,	//衝等
	EM_ItemUseType_FixEq			,	//修裝
	EM_ItemUseType_Dissolution		,	//拆解物品
	EM_ItemUseType_Coloring			,	//染色
	//EM_ItemUseType_ClsEqSoulbound	,	//清除裝備綁定
	EM_ItemUseType_ClsTrade			,	//清除裝備綁定
	EM_ItemUseType_ResetAbility		,	//重設基本數值
	EM_ItemUseType_ResetSkillPoint	,	//重設技能點數
	EM_ItemUseType_EQDigHole		,	//裝備挖洞
	EM_ItemUseType_EQClearRune		,	//清除裝備符文
	EM_ItemUseType_ItemLock			,	//裝備鎖
	EM_ItemUseType_ItemUnLock		,	//解除裝備鎖
	EM_ItemUseType_EQProtect		,	//裝備保護
	EM_ItemUseType_EQLimitMax		,	//裝備耐久上限到Max
	EM_ItemUseType_IgnoreLimitLv	,	//忽略等級限制
	EM_ItemUseType_PK_EQProtect		,	//PK裝備保護
	EM_ItemUseType_PK_EQProtect_Clear,	//PK裝備保護清除
	EM_ItemUseType_UnPacket			,	//打開包裹物品
	EM_ItemUseType_UnPacket_DropList,	//打包物解開(掉落表所有東西)
	EM_ItemUseType_Egg				,	//商城轉蛋
	EM_ItemUseType_ClsEqSoulbound	,	//清除裝備綁定
	EM_ItemUseType_ClsEqAbility		,	//清除所有裝備屬性
//	EM_ItemUseType_ClsTrade_All		,	//清除所有物品的交易鎖定
	EM_ItemUseType_ItemtoItemLua	,	//物品對物品觸發lua
};

enum EqRefineType_ENUM
{
	EM_EqRefineType_Weapon		,
	EM_EqRefineType_Armor		,
	EM_EqRefineType_Jewels		,
	EM_EqRefineType_Ornament	,
};

//物品生存時間類型
enum ItemLiveTimeTypeENUM
{
	EM_ItemLiveTimeType_None			,	//不會消失
	EM_ItemLiveTimeType_RealTime		,	//真實時間
};

//物品特效分類
enum ImageEfficacyTypeENUM
{
	EM_ImageEfficacyType_None			,	//無
	EM_ImageEfficacyType_Throw_Sword	,	//投擲 飛劍,飛刀
	EM_ImageEfficacyType_Throw_Axe		,	//投擲 飛斧
	EM_ImageEfficacyType_Throw_Stone	,	//投擲 石頭
	EM_ImageEfficacyType_Throw_Arrow	,	//投擲 箭矢
	EM_ImageEfficacyType_Throw_Ammo		,	//投擲 子彈
};


//傢俱
enum					EnumItemFurnitureType
{
	EM_FurnitureType_Normal		= 0,	// 一般, 不具容量
	EM_FurnitureType_Storage	= 1,	// 具儲存空間的傢俱
	EM_FurnitureType_Coathanger	= 2,	// 衣架, 且可以展示衣物, 裝備, 具儲存空間的傢俱
	EM_FurnitureType_WeaponSet	= 3,	// 武器架, 可以掛載, 單雙手武器或盾, 具儲存空間的傢俱
	EM_FurnitureType_WeaponAndCloth	= 4,	// 武器衣架, 可以掛載, 武器與裝備
	EM_FurnitureType_Maid		= 5,	// 女僕
};

enum					EnumItemFurnitureEffect
{
	EM_FurnitureEffect_None		= 0,	// 不具提升效果
	EM_FurnitureEffect_EXP		,		// 提高 EXP BOUNS
	EM_FurnitureEffect_TP		,		// 提高 TP BOUNS
	EM_FurnitureEffect_HQ		,		// 提高各種制造技能做出 HQ 物品的機會
};

enum					EnumItemFurniturePos
{
	EM_FurniturePos_NoRule		= 0,	// 不限定
	EM_FurniturePos_Ground		,		// 只能放在地板上
	EM_FurniturePos_Wall		,		// 只能放在牆上
};

enum	DigHoleTypeENUM
{
	EM_DigHoleType_All		,
	EM_DigHoleType_Weapon	,
	EM_DigHoleType_Armor	,
	EM_DigHoleType_Jewels	,
	EM_DigHoleType_Ornament	,
};

/*
enum AddPowerTypeENUM
{
	EM_AddPowerType_No			,		//不加
	EM_AddPowerType_Standard	,		//標準
};
*/
enum	GuildResourceTypeENUM
{
	EM_GuildResourceType_None		= -1,
	EM_GuildResourceType_Gold		,
	EM_GuildResourceType_BonusGold	,
	EM_GuildResourceType_Mine		,
	EM_GuildResourceType_Wood		,
	EM_GuildResourceType_Herb		,
	EM_GuildResourceType_GuildRune	,
	EM_GuildResourceType_GuildStone	,
};

enum SeedTypeENUM
{
	EM_SeedType_None	,	//不是種子
	EM_SeedType_Tree	,	//木
	EM_SeedType_Grass	,	//草
	EM_SeedType_Mine	,	//礦
};

enum ManureTypeENUM
{
	EM_ManureType_None		,	//不是肥料
	EM_ManureType_Water		,	//灌溉
	EM_ManureType_Topdress	,	//施肥
	EM_ManureType_MagicWater,	//魔法灌溉
};

enum FurnitureTypeENUM
{
	EM_FurnitureType_All		,
	EM_FurnitureType_GuildOnly	,
	EM_FurnitureType_HouseOnly	,
};

enum PetFoodEffectTypeENUM 
{
	EM_PetFoodEffectType_None			,	//無
	EM_PetFoodEffectType_STR			,	//STR
	EM_PetFoodEffectType_STA			,	//STA
	EM_PetFoodEffectType_INT			,	//INT
	EM_PetFoodEffectType_MND			,	//MND
	EM_PetFoodEffectType_AGI			,	//AGI
	EM_PetFoodEffectType_PetProperty	,	//改變屬性
	EM_PetFoodEffectType_PetObjID		,	//改變外觀

};

enum ExBagTypeENUM
{
	EM_ExBagType_None	,
	EM_ExBagType_Pet	,
	EM_ExBagType_Horse	,
};
//----------------------------------------------------------------------------------------
//屬於物品的基本資料
//----------------------------------------------------------------------------------------
struct GameObjectItemStruct
{
	GameObjectItemENUM		Class;

    ItemType_ENUM           ItemType; 

	int						IncMagic_Onuse;		    //產生的法術效果(使用的效果)
    int                     IncMagic_OnAttack;      //產生的法術效果(功擊時)
    int                     IncMagic_OnAttackRate;  //攻擊發生的機率

    int                     DisappearRate;      //合成失敗消失率
	float					DissolutionRate;	//分解加成率
    int                     SrcRecipe;          //合成配方

    union
    {
	    GameObjectWeaponENUM	WeaponType;			//武器類型
        GameObjectArmorENUM     ArmorType;			//防具類型
    };
    union
    {
        GameObjectWeaponPosENUM WeaponPos;
        GameObjectArmorPosENUM  ArmorPos;
    };

	GameObjectWearEqStruct	Ability;
	ItemDropStruct DropItemAbility[_MAX_DROP_ABILITY_COUNT_];

	int						AttackDistance;		//攻擊距離
    int                     HoleBase;           //基本洞數(符文容量)
    int                     HoleRange;          //可變範圍(保留)
//    AddPowerTypeENUM        AddPowerOn;         //物品掉落是否跑一般附加屬性規則(or符文能力) ( 0 不跑 1 跑 2 必定有 )
	int						MaxAttrCount;		//最多可附加能力各數


    AddonPosTypeStruct      AddPos;             //(符文)鑲入裝備部位
    RuneType_ENUM           RuneType;           //符文類型(企劃用)
	int						RuneGroup;			//符文分類
    int                     Durable;
	int						Level;				//使用等級
	int						Volume;				//符文容量
	int						ManuFactureType;	//製造類型
	int						ManuFactureLV;		//製造等級

	int						SuitID;				//套裝ID

	int						AttackRange;		//攻擊範圍
	int						AttackSpeed;

	ItemUseType_ENUM		UseType;				//物品使用模式
	char					SrvScript[128];			//使用執行 Server某劇情 必須回傳 true=1 or false=0 不能使用Sleep
	char					CliScript[128];			//使用執行 Client某劇情
	char					CheckUseScript[128];	//使用檢查 lua
	//修理資料
	int						FixQuality;			//維修品質

	//衝等資料
	EqRefineType_ENUM		EqRefineType;
	float					EqRefineRate_Base;
	float					EqRefineRate_Fix;
	float					EqRefineRate_Per;

	int						EqRefineEqMinLv;		//使用等級
	int						EqRefineEqMaxLv;
	int						EqRefineMinLv;			//鍊化等級
	int						EqRefineMaxLv;
	float					EqRefineFailed_LevelDownRate_Base;	//失敗退等機率
	float					EqRefineFailed_LevelDownRate_Fix;	//失敗退等機率
	float					EqRefineFailed_LevelDownRate_Per;	//失敗退等機率
	float					EqRefineFailed_ExplodeRate_Base;	//失敗消失機率
	float					EqRefineFailed_ExplodeRate_Fix;		//失敗消失機率
	float					EqRefineFailed_ExplodeRate_Per;		//失敗消失機率
	bool					IsItemToItem;			//可對物品使用

	bool					IsStandardCost;
	int						ReferenceLv;			//參考價等級
	int						Coloring_OffColor;
	int						Coloring_MainColor;

	//卡片專用資料
	int						CardOrgObjID;			//卡片索引的資料
	int						CardID;					//卡片的號碼
	ImageEfficacyTypeENUM	ImageEfficacyType;		//特效參數

	int						CastingTime;			//使用時間
	//--------------------------------------------------------------------------------------
	//能力標準型
	bool					IsStandardAbility;
	int						StandardAbility_Lv;
	int						StandardAbility_ArgType[5];
	float					StandardAbility_Arg[5];
	//--------------------------------------------------------------------------------------
	int						CardPriorityID;			//卡片排序優先權　
	int						GuildContributionValue;	//公會貢獻所加的積分
	//--------------------------------------------------------------------------------------
	int						RefineTableID;			//衝等參考資料位置
	//--------------------------------------------------------------------------------------
	char					MagicToolsScript[128];	//法寶每十秒定時使用的Lua

	// 傢俱
	//--------------------------------------------------------------------------------------
	EnumItemFurnitureType		emFurnitureType;
	EnumItemFurnitureEffect		emFurnitureEffect;
	int							iFurnitureStorageSize;
	EnumItemFurniturePos		emFurniturePos;

	int							iCraftObjType;				// 能提供協助生產技能
	int							iFurnitureSuitID;			// 傢俱套裝效果

	int							ExpPoint;
	int							TpPoint;
	
	int 						BlackSmithHQPoint;
	int 						CarpenterHQPoint;	
	int 						MakeArmorHQPoint;	
	int 						TailorHQPoint;		
	int 						CookHQPoint;		
	int 						AlchemyHQPoint;

	//--------------------------------------------------------------------------------------
	//裝備打洞
	struct  
	{
		int					MaxHoleCount;	//最大洞數
		DigHoleTypeENUM		Type;			//類型
		int					Rate;			//機率
	}DigHole;
	//--------------------------------------------------------------------------------------
	//使用須要2次密碼
	bool	IsUseNeedPassword;
	bool	IsFixDurable;
	//--------------------------------------------------------------------------------------
	int		MagicToolsTime;
	int		MagicToolsColdown;
	//--------------------------------------------------------------------------------------
	int		AttrValue[8];
	//--------------------------------------------------------------------------------------
	RelationTypeENUM	SenderRelation;
	RelationTypeENUM	TargetRelation;
	//--------------------------------------------------------------------------------------
	int		StarValue;
	int		RuneLimetLv;		//符文限制等級
	//--------------------------------------------------------------------------------------
	GuildResourceTypeENUM GuildResourceType;
	int	GuildResourceValue;

	int		SelectBaseAttrCount;
	int		BaseAttrCount;
	char	MagicToolsTpExpScript[64];	//打怪得到Exp 與 Tp
	char	OnDestroyScript[64];	
	int		ItemUniqueType;				//裝備唯一設定( 0 ) 表示沒設定
	int		FurnitureNPCObjID;

	char	ItemUseOKScript[64];		//使用物品成功的劇情
	int		DropListPacket;				//物品使用為掉落表內所有東西
	struct
	{
		struct  
		{	
			SeedTypeENUM	Type;
			float			GrowSpeed;
			int				ModelType;		//模型類型
			int				BestWater;		//最佳水分
			int				BestTopdress;	//最佳養分
			int				RandSeed;		//亂數種子
		}Seed;
		struct  
		{
			union
			{
				int	Mode;
				struct  //可種植類型
				{
					bool	Tree	:1;
					bool	Grass	:1;
					bool	Mine	:1;
				};
			};

			float	EvnPoint[3][2];
		}Pot;
		struct  
		{
			ManureTypeENUM	Type;
//			float			EvnPoint[2];
			int				AddRare;
			int				AddWater;
			int				AddTopdress;
			int				AddHealth;
			int				AddGrow;
			int				FeedPoint;

		}Manure;
		int	Level;			//種植等級
		float			DecWater;		//水分每小時下降
		float			DecTopdress;	//養分每小時下降
	}Plant;

	FurnitureTypeENUM Furniture_Type;

	struct
	{
		int PetObjID;
		int Lv;
		int SkillPoint;
		int PetType;
		int	Property;
		int	Talent;
		int STR,STA,INT,MND,AGI;
		int Spirit;
		char LuaEvent[64];
	}Pet;

	struct
	{
		int SkillPoint;
		int	Spirit;
		int Loyal;
		int Talent;
		int Hunger;
		int Exp;

		PetFoodEffectTypeENUM EffectType;
		int	EffectValue;
	}PetFood;

	AddonPosTypeStruct ItemToItemLimit;


	union
	{	
		struct
		{	
			int DDmg;			//武器微調資料
			int DMDmg;
		};
		struct
		{	
			int DDef;			//防具微調資料
			int DMDef;
		};
	};

	int		CardAddpower;		//卡片帶的能力資料

	int		FurnitureSoundID;	//留聲機ID

	ExBagTypeENUM		ExBagType;			//放入特殊包裹後分類
	int					ExBagTypeSub;

	int		BodyMaxCount;		//身體最多幾個
	int		DrawOutCost;		//取出價錢

	struct
	{
		int Famous;
		int	Exp;
	}TitleSys;

	int		RefineLv;				//初始精鍊等級
	int		AddPowerQuality;		//額外增加威力
	int		CollectionNPC;			//圖鑑參考NPC
//	int		ColorType;
//	int		RuneSystemTableID;		//雕文共鳴組 參考表ID

};

//----------------------------------------------------------------------------------------
//幻靈
//----------------------------------------------------------------------------------------
struct AbiParametersTableStruct
{
	int	GUID;				
	float Parameter;		//能力參數

};
struct PhantomRankTableStruct
{
	int	Rank;				
	int MaxLevel;				
	int NeedFragment;	

};
struct PhantomLvTableStruct
{
	int	LV;				
	int Type;				
	int Material[4];	

};
struct PhantomSkillTableStruct
{
	int	Phantom[2];				
	int SkillID;	

};

struct GameObjectPhantomStruct
{
	int						RankUpMaterial;		//提升階級材料
	int						LevelUpType;		//升級材料類別
	GameObjectWearEqStruct	abi_Phantom;		//幻靈能力	
};
//----------------------------------------------------------------------------------------
//法術種類列舉
//----------------------------------------------------------------------------------------
enum	GameObjectMagicENUM
{
	//立即反應
	EM_Magic_Attack			    ,	//攻擊
	EM_Magic_Cure				,	//治療
	EM_Magic_Rebuff			    ,	//去Buff

	//持續效果
	EM_Magic_Assist			    ,	//輔助效果的法術
	EM_Magic_Disease			,	//不好的狀態
    EM_GameObjectMagicEM_FORCE_DWORD   = 0x7fffffff, 
};

//----------------------------------------------------------------------------------------
//	法術目標設定
//----------------------------------------------------------------------------------------
enum	GameObjectRelationENUM
{
	EM_Releation_Self			,	//自己
	EM_Releation_Member		    ,	//隊友

	EM_Releation_Self_Pet		,	//自己(pet)
	EM_Releation_Member_Pet	    ,	//隊友(pet)

	EM_Releation_Friend		    ,	//友方,(對玩家 則為所有玩家   對不屬於玩家的NPC 則為不屬於玩家的NPC)
	EM_Releation_Friend_NPC	    ,	//友方的寵物(如寵物，召喚出來的，屬於跟隨自己的NPC)

	EM_Releation_Enemy		    ,	//所有可砍殺的對項
	EM_Releation_Player		    ,	//所有玩家
	EM_Releation_All			,	//所有物件

	EM_Releation_GuildPlayer	,	//同公會玩家
	EM_Releation_NotGuildPlayer ,	//不同公會玩家

    EM_Releation_CountryPlayer	,	//同國家玩家
    EM_Releation_NoCountryPlayer,	//不同國家玩家

	EM_Releation_Corpse			,	//屍體
	EM_Releation_Npc_Corpse		,	//NPC屍體
	EM_Releation_Player_Corpse	,	//玩家屍體
	EM_Releation_Locatoin		,	//指定位置( 範圍法術 )

	EM_Releation_PetOwner		,	//自己的主人
	EM_Releation_Wagon			,	//載具
	EM_Releation_Plot			,	//劇情選取

    EM_GameObjectRelationEM_FORCE_DWORD   = 0x7fffffff, 
};

//----------------------------------------------------------------------------------------
//有效範圍
//----------------------------------------------------------------------------------------
//(好的有效範圍)自己 隊友 同工會
//(壞的有效範圍)可以砍殺者
enum	GameObjectMagicEffectRangeENUM
{
	EM_MagicEffect_Target			,	//目標有效
	EM_MagicEffect_Good_Range		,	//好的範圍法術
	EM_MagicEffect_Good_Member	    ,	//好的成員法術
	EM_MagicEffect_Bad_Range		,	//壞的範圍法術
	EM_MagicEffect_AllObj			,
	EM_MagicEffect_AllPlayer		,
	EM_MagicEffect_AllMonster		,
	EM_MagicEffect_AllPlayer_Enemy	,	//所有敵方玩家
	EM_MagicEffect_AllPlayer_Friend	,	//所有我方玩家
	EM_MagicEffect_Plot				,	//劇情選取
    EM_GameObjectMagicEffectRangeEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
enum MagicFuncENUM
{
	EM_MAGICFUN_HPMP		= 0	,
	EM_MAGICFUN_Assist		    ,	//輔助
	EM_MAGICFUN_Teleport		,	//傳送
	EM_MAGICFUN_SummonCreature  ,	//招換生物(寵物)
	EM_MAGICFUN_SummonItem	    ,	//招換物品
	EM_MAGICFUN_Steal			,	//偷竊
	EM_MAGICFUN_ItemRunPlot	    ,	//產生物品並且執行劇情
	EM_MAGICFUN_RunPlot		    ,	//執行劇情
	EM_MAGICFUN_Raise		   	,	//復活
};
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
enum    ShootItemType
{
	EM_ShootItem_None			,
    EM_ShootItem_Ammunition     ,
    EM_ShootItem_Arrow          ,
    EM_ShootItem_Throw          ,
};
//----------------------------------------------------------------------------------------
//法術消耗結構
//----------------------------------------------------------------------------------------
struct MagicCostStruct
{
	MagicSpellCostTypeENUM	Type;		//消耗類型
	int				Value;				//消耗數值
};
//----------------------------------------------------------------------------------------
//法術需求結構
//----------------------------------------------------------------------------------------
struct MagicNeedStruct
{
	MagicSpellNeedTypeENUM	Type;		//需求類型
	int						Value;		//值
};
//-----------------------------------------------------------------------
//傳送魔法
//-----------------------------------------------------------------------
struct	MagicTeleport
{
	int	ZoneID;
	int	X , Y , Z;
	int Dir;
};


//-----------------------------------------------------------------------
//	攻擊魔法
//-----------------------------------------------------------------------
enum  MagicAttackCalENUM
{
    EM_MagicAttackCal_None      	,
    EM_MagicAttackCal_MPow      	,
    EM_MagicAttackCal_Weapon    	,// (本身DMG + 主手DMG)
    EM_MagicAttackCal_Shoot     	,//  射擊類( 本身DMG + 弓DMG + 彈藥DMG)
    EM_MagicAttackCal_Throw     	,//  投擲類( 本身DMG + 彈藥DMG)
    EM_MagicAttackCal_INT       	,
    EM_MagicAttackCal_STR       	,
    EM_MagicAttackCal_AGI       	,
    EM_MagicAttackCal_STA       	,
    EM_MagicAttackCal_MND       	,  
	EM_MagicAttackCal_LastSkillDmg 	,  
	EM_MagicAttackCal_LastPhyDmg   	,  
	EM_MagicAttackCal_ShieldDef   	,  
};

//攻擊類型
enum	MagicAttackTypeENUM
{
	EM_MagicAttackType_HP			,	
	EM_MagicAttackType_MP			,
	EM_MagicAttackType_SP_Warrior	,
	EM_MagicAttackType_SP_Ranger	,
	EM_MagicAttackType_SP_Rogue		,
	EM_MagicAttackType_StomachPoint	,	
};

struct MagicAttackStruct
{
	MagicAttackTypeENUM	AtkType;

	float		DmgPower;
	float		DmgPower_SkillLVArg;
	
	float				FixValue;
	MagicAttackCalENUM  FixType;
	float		FixDmg_SkillLVArg;						

    float       Rand;           //傷害 變化範圍
	
	int			CritialRate;	//增加致命一擊率
	float		HateRate;
};
//-----------------------------------------------------------------------
//復活術
//-----------------------------------------------------------------------
struct MagicRaise
{
	int		ExpPrecnt;
};
//-----------------------------------------------------------------------
//召喚生物
//-----------------------------------------------------------------------
enum MagicSummonCreatureTypeENUM
{
	EM_MagicSummonCreatureType_Pet				,
	EM_MagicSummonCreatureType_Guard			,
	EM_MagicSummonCreatureType_Guard_NoAttack	,
};

enum PetSpellRightTimeENUM
{
	EM_PetSpellRightTime_OwnerStartUsing	,		//主人設定使用(循環使用)
	EM_PetSpellRightTime_Auto				,		//自動使用	
};

enum PetSpellTargetENUM
{
	EM_PetSpellTarget_Self		,
	EM_PetSpellTarget_Owner		,
	EM_PetSpellTarget_Party		,
	EM_PetSpellTarget_Enemy		,
};
/*
struct PetSkillStruct
{
	int						KeyItemID;
	PetSpellRightTimeENUM	SpellRightTime;
	PetSpellTargetENUM		TargetType;
	int						Rate;			//施法機率
	int						SkillID;		//法術ID
};
*/

struct MagicSummonCreature
{
	int		ObjID;
	int		Level;
	int		RangeLevel;
	int		LiveTime;				//生存期(-1)代表不消失
	float	SkillLvArg;
	MagicSummonCreatureTypeENUM Type;
	int		GroupID;				//同一群組只能有一隻
	float	OwnerPowerRate;			//增加玩家一定比例的能力到寵物上

	//PetSkillStruct	Skill[ _MAX_PET_SKILL_COUNT_ ];
	int		SkillType[3];
	char	InitLua[32];
};
//-----------------------------------------------------------------------
//召喚物品
//-----------------------------------------------------------------------
struct MagicSummonItem
{
	int		ObjID;
};
//-----------------------------------------------------------------------
//偷竊
//-----------------------------------------------------------------------
/*
enum	MagicStealClassENUM
{
	EM_MagicSteal_NULL	= 0	,		//此結構資料無效
	EM_MagicSteal_Money		,
	EM_MagicSteal_Item		,
};
*/
struct MagicSteal
{
//	MagicStealClassENUM		Class;
	int						SuccessRate;		//成功率
};
//-----------------------------------------------------------------------
//產生物品執行劇情
//-----------------------------------------------------------------------
enum	MagicItemRunPlotTargetTypeENUM
{	
	EM_MagicItemRunPlotTargetType_Enemy			,
	EM_MagicItemRunPlotTargetType_Friend		,
	EM_MagicItemRunPlotTargetType_Player		,
	EM_MagicItemRunPlotTargetType_NPC			,
	EM_MagicItemRunPlotTargetType_All			,
	EM_MagicItemRunPlotTargetType_Friend_NoSelf	,
	EM_MagicItemRunPlotTargetType_Player_NoSelf	,
	EM_MagicItemRunPlotTargetType_All_NoSelf	,
};
enum	MagicItemRunPlotENUM
{
	EM_MagicItemRunPlot_Plot	,	//劇情類
	EM_MagicItemRunPlot_Mine	,	//地雷類
	EM_MagicItemRunPlot_Staff	,	//插杖類
};
struct MagicItemRunPlot
{
	MagicItemRunPlotENUM	Type;	//類型
	int		ObjID;
	char	PlotName[64];
	int		LiveTime;				//生存期(-1)代表不消失
	int		UseMagic;				//使用法術
	int		OnDeadMagic;			//死亡順間產生的法術
	int		GroupID;				//群組ID	( 0  代表不分群組)
	union
	{
		int		Mode;
		//ObjectModeStruct	Mode;		//物件的基本屬性
		struct  
		{
			bool	Mark				: 1;
			bool	Fight				: 1;
			bool	NotShowHPMP			: 1;
			bool	EnemyHide			: 1;
			bool	NotRelyOwnerPower	: 1;
		};
	};

	MagicItemRunPlotTargetTypeENUM		TargetType;
//	int		Level;
};
//-----------------------------------------------------------------------
//執行劇情
//-----------------------------------------------------------------------
struct MagicRunPlot
{
	char	PlotName[64];
};

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
enum    MagicGoodorBadENUM
{
    EM_Magic_Good       ,       //好法術
    EM_Magic_Bad        ,       //壞的法術
};
//----------------------------------------------------------------------------------------
//法術 或 物理
//----------------------------------------------------------------------------------------
enum    MagicorPhyENUM
{
    EM_Magic_Magic      ,       //屬於魔法攻擊
    EM_Magic_Phy        ,       //屬於物理攻擊
    EM_Magic_Eq         ,       //裝備( 自動施展 )
	EM_Magic_PetEq      ,       //裝備( 飼養寵物 )
};

//----------------------------------------------------------------------------------------
//Dot法術結構
//----------------------------------------------------------------------------------------
enum	DotMagicTypeENUM
{
	EM_DotMagicType_HP	,			//HP
	EM_DotMagicType_MP	,			//MP
	EM_DotMagicType_WarriorSP	,	//戰士SP
	EM_DotMagicType_RangerSP	,	//遊俠SP
	EM_DotMagicType_RogueSP		,	//盜賊SP
	EM_DotMagicType_HP_Per		,	//HP百分比
	EM_DotMagicType_MP_Per		,	//MP百分比

};

struct DotMagicStruct
{       
    int					Time;			 //多久一次
    DotMagicTypeENUM    Type;			 //類形( 0 HP , 1 MP , 2 SP戰士 )
    int					Base;			 //每次傷害
	float				DotSkillLVArg;	 //技能等級影響
	bool IsEmpty()
    {
        return ( Base == 0 || Time <= 0 );
    }
	void Init()
	{
		memset( this , 0 , sizeof( *this ) );
	}
};
//----------------------------------------------------------------------------------------
// 法力盾設定資料
//----------------------------------------------------------------------------------------
enum	MagicShieldTypeENUM
{
	EM_MagicShieldType_MP				,		//MP抵消HP
	EM_MagicShieldType_Times			,		//抵消次數
	EM_MagicShieldType_Point			,		//抵消法數設定的點數
	EM_MagicShieldType_Percent			,		//抵銷百分比
	EM_MagicShieldType_Point_ByHealArg	,		//抵消點數
};

enum	MagicShieldEffecENUM
{
	EM_MagicShieldEffec_All			,	//所有攻擊
	EM_MagicShieldEffec_Phy			,	//物理攻擊
	EM_MagicShieldEffec_Magic		,	//法術攻擊
	EM_MagicShieldEffec_Earth		,	//地系法術攻擊
	EM_MagicShieldEffec_Water    	,	//水系法術攻擊
	EM_MagicShieldEffec_Fire     	,	//火系法術攻擊
	EM_MagicShieldEffec_Wind     	,	//風系法術攻擊
	EM_MagicShieldEffec_Light    	,	//光系法術攻擊
	EM_MagicShieldEffec_Darkness 	,	//暗系法術攻擊
};

struct MagicShieldStruct
{
	MagicShieldTypeENUM		Type;
	MagicShieldEffecENUM	Effect;
	int						Point;		//可始用點數
	float					SkillLvArg;
};

//----------------------------------------------------------------------------------------
// coldown資料設定
//----------------------------------------------------------------------------------------
enum	MagicColdownClassENUM
{
	EM_MagicColdownClass_None	,		//沒有
	EM_MagicColdownClass_Job	,		//職業類型
	EM_MagicColdownClass_EQ		,		//裝備類型
	EM_MagicColdownClass_Item	,		//物品類型

};
struct MagicColdownBaseStruct
{
	//一般的Coldown
	MagicColdownClassENUM		Class;
	int							Type;
	int							Time;	//(秒)
	//下次可失法的時間
	int							TimeAllMagic;		
};
//----------------------------------------------------------------------------------------
//特殊行為
//----------------------------------------------------------------------------------------
struct MagicAttackSpecialAction
{
	union
	{
		int _Type;
		struct
		{
			bool	None			: 1;	//保留
			bool    StrikeBack		: 1;	//震退
			bool	SpellInterrupt	: 1;	//施法中斷
			bool	IgnoreDefine	: 1;	//無視防禦or抗性
			bool	EraseHate		: 1;	//清除仇恨( 會轉嫁 同加血計算 )
			bool	HateOnePoint	: 1;	//仇恨清除為1
			bool	Bomb			: 1;	//炸飛
		};
	};
};
//----------------------------------------------------------------------------------------
//攻擊法術計算方式列舉
//----------------------------------------------------------------------------------------
enum MagicAttackCalBaseENUM
{
	EM_MagicAttackCalBase_Physics		,//物理計算
	EM_MagicAttackCalBase_Magic			,//法術計算
	EM_MagicAttackCalBase_Throw			,//投擲計算
	EM_MagicAttackCalBase_Shoot			,//射擊計算
	EM_MagicAttackCalBase_Fix			,//定值
	EM_MagicAttackCalBase_HolyHeal		,//神聖治療計算( 負值表示Miss  )
	EM_MagicAttackCalBase_DarkHeal		,//不死系療計算( 負值表示Miss  )
	EM_MagicAttackCalBase_SpecialAction	,//沒攻擊只有特殊行為
	EM_MagicAttackCalBase_FixPer		,//百分比
	EM_MagicAttackCalBase_Physics_Point	,//物理計算
	EM_MagicAttackCalBase_MagicEx		,//法數計算 比例*MDmg * MDmg_MagArg 

//	EM_MagicAttackCalBase_ShootEx		,//射擊計算(同物理計算)
};
//----------------------------------------------------------------------------------------
enum	SpecailMagicEventTypeENUM
{	
	EM_SpecailMagicEventType_None				,	//無
	EM_SpecailMagicEventType_SelfCritial		,	//自己 攻擊致命一擊(普攻)
	EM_SpecailMagicEventType_TargetCritial		,	//目標 攻擊致命一擊(普攻)
	EM_SpecailMagicEventType_SelfDodge			,	//自己 閃避
	EM_SpecailMagicEventType_TargetDodge		,	//目標 閃避
	EM_SpecailMagicEventType_SelfMiss			,	//自己 Miss
	EM_SpecailMagicEventType_TargetMiss			,	//目標 Miss
	EM_SpecailMagicEventType_ZoneDamage			,	//區域傷害事件
	EM_SpecailMagicEventType_Phy_SelfCritial	,	//自己 攻擊致命一擊(物理)
	EM_SpecailMagicEventType_Phy_TargetCritial	,	//目標 攻擊致命一擊(物理)
	EM_SpecailMagicEventType_Mag_SelfCritial	,	//自己 攻擊致命一擊(法術)
	EM_SpecailMagicEventType_Mag_TargetCritial	,	//目標 攻擊致命一擊(法術)
	EM_SpecailMagicEventType_Cure_Self			,	//自己 受治療
	EM_SpecailMagicEventType_Cure_Target		,	//目標 治療目標
	EM_SpecailMagicEventType_SelfParry			,	//自己 格擋
	EM_SpecailMagicEventType_TargetParry		,	//目標 格擋
	EM_SpecailMagicEventType_SelfSpell			,	//自己施法
};
//----------------------------------------------------------------------------------------
//屬於法術的基本資料
//----------------------------------------------------------------------------------------
#define _MAX_BUFFSKILL_COUNT_	6
struct GameObjectMagicStruct  
{
	MagicFuncENUM			MagicFunc;				//法術種類(要用那個法術Function去呼叫)
    MagicResistENUM			MagicType;              //魔法類型
	MagicorPhyENUM			EffectType;

	float	    EffectTime;							//有效時間(0.1 秒為單位)
    float       DLV_EffectTime;					    //等級差影響有效時間(0.1 秒為單位)
	float		EffectTime_SkillLVArg;				//技能等級影響時間參數
	int		    HateCost;							//仇恨值(+ 目標加多少仇恨值)(- 目標的攻擊的目標 減多少仇恨值)
	
	int			MaxBuffLv_Base;						//Buf堆疊效果的最高等級
	float		MaxBuffLv_SkillLVArg;				//因技能差影響buf最高等級的參數

	int			MagicGroupSet;						//此魔法所屬的類型
    //-----------------------------------------------------------------------
	MagicSpellFlagStruct			Setting;		//法術設定旗標
	MagicAttackSpecialAction		SpecialAction;	//特殊的行為
	
	//-----------------------------------------------------------------------
	//(持續影響的數值)輔助魔法
	//-----------------------------------------------------------------------
	GameObjectMagicTypeENUM			AssistType;			//法術類型(主要用於輔助法術互斥處理)
    int		                        EffectLV;			//輔助法術威力等級
	int								EffectAddonType;	//同等是否互蓋 0互蓋    1不互蓋 
	MagicEffectStruct				Effect;				//影響效果
	

    MagicClearTimeStruct            ClearTime;			//消除條件
	GameObjectWearEqStruct			Ability;			//影響屬性
    float							Ability_SkillLVArg;	//技能等級影響效果

    int                             OnTimeMagic_Magic;  //定時產生法術效果(法術iD)
    int                             OnTimeMagic_Time;   //定時產生法術效果(多久一次)
    int                             FaceOffID;          //變身ID( 0 代表不改變 )
	int								RideID;				//騎乘ID( 0 代表不改變 )

	int								OnAttackMagicID;		//當被攻擊時產生的法術
	int								OnBuffTimeOutMagicID;	//當此輔助法術結束時產生的法術
	int								OnAttackReboundMagicID;	//被打到反彈出來的法術
	int								OnMagicAttackReboundMagicID;	//被打到反彈出來的法術
	int								OnDeadMagicID;			//死亡時產生的法數
	int								TempHateCost;			//暫時增加的仇恨質
    int								ClearMagicGroupSet;		//使那些類的法術無效
    DotMagicStruct                  DotMagic;           
	//-----------------------------------------------------------------------
	//攻擊魔法
	//-----------------------------------------------------------------------
	MagicAttackStruct				Attack;		//攻擊魔法資料
	//-----------------------------------------------------------------------
	//傳送魔法
	//-----------------------------------------------------------------------
	MagicTeleport					Teleport;	
	//-----------------------------------------------------------------------
	//復活術
	//-----------------------------------------------------------------------
	MagicRaise						Raise;		
	//-----------------------------------------------------------------------
	//召喚生物
	//-----------------------------------------------------------------------
	MagicSummonCreature				SummonCreature;
	//-----------------------------------------------------------------------
	//召喚物品
	//-----------------------------------------------------------------------
	MagicSummonItem					SummonItem;
	//-----------------------------------------------------------------------
	//偷竊
	//-----------------------------------------------------------------------
	MagicSteal						Steal;

	//-----------------------------------------------------------------------
	//產生物品執行劇情
	//-----------------------------------------------------------------------
	MagicItemRunPlot				ItemRunPlot;
	//-----------------------------------------------------------------------
	//執行劇情
	//-----------------------------------------------------------------------
	MagicRunPlot					RunPlot;
	//-----------------------------------------------------------------------
	//法力盾
	MagicShieldStruct				MagicShield;

	//攻擊法術計算方式
	MagicAttackCalBaseENUM			AtkCalType;				

	//法術群組分類
	int								MagicGroupID;

	//Buff上顯示的數字
	int								BuffCount;			

	//物理殤害類型
	PhyResistTypeENUM				PhyAttackType;

	//////////////////////////////////////////////////////////////////////////
	//介面處理
	bool							IsStandard_Attack;
	float							RefPowerLv_Attack;
	float							RefPowerRate_Attack;
	//////////////////////////////////////////////////////////////////////////
	float							ModelSize;			//模型縮放比例

	int								Revive_SkillLVArg;	//等極影響回復經驗值百分比

	int								AddBuffTime;		//增加Buff時間( 秒 )
	int								OnKillMagicID;		//殺死時產生的法數
	char							CheckUseLua[ _MAX_SIZE64_QUEST_SCRIPT ];

	SpecailMagicEventTypeENUM		SpecialMagicEventType;
	int								OnSpecialMagicID;

	int								BuffTimeDesc_Type;
	int								BuffTimeDesc_Time;

	int								BuffSkill[ _MAX_BUFFSKILL_COUNT_ ];

	char							EndUseLua[ _MAX_SIZE64_QUEST_SCRIPT ];
	int								HitBackDist;

	int								CarryCount;			//可載人數
	int								MusicID;			//BUFF觸發背景音樂
	int								BuffMaxLv;
	int								OnBuffTimeOutMagicIDEx;	//當此輔助法術結束時產生的法術(只有正常時間到會觸發)
	int								MotionChangeType[4];	//動作改變類型
	int								MotionChangeID[4];		//動作改變ID
	MagicSpellFlagExStruct			SettingEx;				//法術設定旗標

};
//----------------------------------------------------------------------------------------
//職業技能
//----------------------------------------------------------------------------------------
//職業專屬技能設定
struct  JobSkillBaseStruct
{
    int		MagicID;        //法術
    int		LearnLV;        //自動學會等級
    int		KeyItemID;      //必要的重要物品
	int		NeedMagicID[2];	//需要法術


	char	NeedMagicLv[2];	//需要法術等級
	char	SaveLvPos;		//等級儲存位置
	char	Reserve;		//(保留)
	
};

struct GameObjectLearnMagicStruct
{
	int		SPSkillCount;
    JobSkillBaseStruct  SPSkill[_MAX_Edit_SPSkill_COUNT_ ];            //等級到自動學會
	int		NormalSkillCount;
    JobSkillBaseStruct  NormalSkill[_MAX_Edit_NormalSkill_COUNT_ ];        
};

//----------------------------------------------------------------------------------------
//商店結構
//----------------------------------------------------------------------------------------
struct GameObjectShopStruct
{
    int         BuyRate;
    int         SellRate;
    YesNoENUM   WeaponRepair;
    int         SellItemID[ 30 ];
    int         SellItemMax[ 30 ];
	int         SellItemPorduce[ 30 ];

	int				SellCost[30][2];
	PriceTypeENUM	CostType[30][2];
};
//////////////////////////////////////////////////////////////////////////
enum LanguageTypeENUM
{
	EM_LanguageType_RW		= -1,
	EM_LanguageType_TW		,
	EM_LanguageType_CN		, //簡體
	EM_LanguageType_ENUS	,
	EM_LanguageType_DE		, //德文
	EM_LanguageType_ENEU	, //
	EM_LanguageType_JP		, //日文
	EM_LanguageType_KR		, //韓文
	EM_LanguageType_BR		, //巴西
	EM_LanguageType_TR		, //土耳其
	EM_LanguageType_VN		, //越南
	EM_LanguageType_RU		, //俄羅斯
//	EM_LanguageType_SG		, //星加坡
	EM_LanguageType_TH		, //泰國
	EM_LanguageType_FR		, //法國
	EM_LanguageType_ID		, //印尼
	EM_LanguageType_ES		, //西班牙
	EM_LanguageType_PH		, //菲律賓
	EM_LanguageType_AE		, //沙烏地阿拉伯
//	EM_LanguageType_NL		, //荷蘭
	//EM_LanguageType_RO		, //羅馬尼亞
	EM_LanguageType_PL		, //波蘭
	EM_LanguageType_PT		, //葡萄牙語
	EM_LanguageType_SAES	, //中南美洲(西班牙)
	EM_LanguageType_ENAR	, //中東英文
	EM_LanguageType_SAPT	, //中南美洲(葡萄牙)
	EM_LanguageType_IT		, //義大利
	

	EM_LanguageType_Count	,
};

enum CountryTypeENUM
{
	EM_CountryType_RW		= -1,
	EM_CountryType_TW		,
	EM_CountryType_CN		, //簡體
	EM_CountryType_ENUS		,
	EM_CountryType_DE		, //德文
	EM_CountryType_ENEU		, //
	EM_CountryType_JP		, //日文
	EM_CountryType_KR		, //韓文
	EM_CountryType_BR		, //巴西
	EM_CountryType_TR		, //土耳其
	EM_CountryType_VN		, //越南
	EM_CountryType_RU		, //俄羅斯
	EM_CountryType_SG		, //星加坡
	EM_CountryType_FR		, //法國
	EM_CountryType_ID		, //印尼
	EM_CountryType_ES		, //西班牙
	EM_CountryType_NL		, //荷蘭
	EM_CountryType_PH		, //菲律賓
	EM_CountryType_RO		, //羅馬尼亞
	EM_CountryType_PT		, //葡萄牙
	EM_CountryType_PL		, //波蘭
	EM_CountryType_TH		, //泰國
	EM_CountryType_AE		, //沙烏地阿拉伯
	EM_CountryType_SA		, //南美
	EM_CountryType_AUS		, //澳州
	EM_CountryType_IT		, //義大利

	EM_CountryType_Count	,
};
//----------------------------------------------------------------------------------------
//套裝
//----------------------------------------------------------------------------------------
struct GameObjectSuitStruct
{
	int TotalCount;		//套裝總數

	struct 
	{
		WearEqTypeENUM  EqType[ 3 ];
		int             EqTypeValue[ 3 ];
	}SuitBase[9];		//每等級套裝額外帶來的能力


	struct 
	{
		union
		{
			GameObjectWearEqStruct	Ability;
			struct  
			{
				WearEqTypeENUM  EqType[ 10 ];
				int             EqTypeValue[ 10 ];
			};
		};
	}SuitValue[9];		//每等級套裝帶來的能力(累計值)

	int	SuitList[ 10 ];	//所有套裝

	//套裝技能 收集完整套可選的技能
	int	SuitSkillID[ 4 ];
	int SuitSkillMoney;
	
};
//----------------------------------------------------------------------------------------
//陣營資訊
//----------------------------------------------------------------------------------------
#define _MAX_CAMP_COUNT_ 15
enum GameCampTypeENUM
{
	EM_GameCampType_Alliance	=	0	,	//同盟不可攻擊 ( 會幫忙)
	EM_GameCampType_Friend				,	//友善( 會幫忙 ) ， 可強制攻擊
	EM_GameCampType_Neutrality			,	//中立
	EM_GameCampType_Enemy				,	//敵人
};

struct GameCampStatuteStruct
{
	char	CampName[ _MAX_CAMP_COUNT_ ][ _MAX_OBJ_NAME_STR_SIZE_ ];		//陣營名稱
	char	CampInfo[ _MAX_CAMP_COUNT_ ][ _MAX_CAMP_COUNT_+1 ];		//陣營之間的關係 //GameCampTypeENUM
};
//----------------------------------------------------------------------------------------
//開寶結構
//----------------------------------------------------------------------------------------
#define _MAX_TREASURE_COUNT_	100
struct TreasureBaseInfo
{
	int		OrgID;
	int		Count;		
	int		DropCount;		//每次掉落多少個
};

struct TreasureGambleInfo
{
	int	Cost;
	int	HoleRate[4];
	//int	AddPower;
	ItemDropStruct DropItemAbility[_MAX_DROP_ABILITY_COUNT_];
};

struct GameTreasureStruct
{
	int		ItemCount;
	TreasureBaseInfo Item[ _MAX_TREASURE_COUNT_ ];		//物品總數量加起來一定為 10 萬個
	int		NeedDLv;									//(成立條件)怪物等級差
	TreasureGambleInfo Gamble;
	char	LuaCheckScript[_MAX_SIZE64_QUEST_SCRIPT];
};
//----------------------------------------------------------------------------------------
//法術集合
//----------------------------------------------------------------------------------------
struct	MagicCollectFlagStruct
{
	union
	{
		int _Type;
		struct
		{
			bool    Interrupt_OnMove				: 1;	//施法中斷 移動
			bool    Interrupt_OnAttack				: 1;	//施法中斷 被攻擊
			bool    Spell_Back		    			: 1;	//敵人背後才可施展
			bool    Spell_Front		    			: 1;	//敵人正面才可施展
			bool    Spell_LookAtTarget				: 1;	//面向敵人才可施展
			bool	ReferenceWeapon_Bow				: 1;	//參照弓 攻速 攻擊距離 ( 冷卻時間距離)
			bool	ReferenceWeapon_Throw			: 1;	//參照暗器 攻速 攻擊距離 ( 冷卻時間距離)
			bool	Dash							: 1;	//衝撞
			bool	AllColdown_Reference_Weapon		: 1;	//共用冷卻 參考武器攻速
			bool	NoInterrupt						: 1;	//不會被技能中斷
			bool	HideCastingBar					: 1;	//不顯示施法條
			bool	Interrupt_SpellOtherMagic		: 1;	//施展其它的法術中斷
			bool	Ignore_Obstruct					: 1;	//忽視阻檔物(範圍法術)
			bool	ReferenceWeapon_Bow_SpellTime	: 1;	//參照弓 攻速 攻擊距離 ( 施法時間距離)
			bool	ReferenceWeapon_Throw_SpellTime	: 1;	//參照暗器 攻速 攻擊距離 ( 施法時間距離)
			bool	IgnoreFightingLog				: 1;	//忽略戰鬥記錄
			bool	NoObjectInMagicEffectRange		: 1;	//範圍內不可以有物件
			bool	DescDurable						: 1;	//損耗耐久度
			bool	forceDisplayEffect				: 1;	//設定特效必需被顯示
			bool	IgnoreSpellMagicClear			: 1;	//忽略施展消失
			bool	SpellStopMove					: 1;	//施法停止移動
		};
	};
};


//----------------------------------------------------------------------------------------
//法術集合
//----------------------------------------------------------------------------------------


enum MagicCheckFunctionENUM
{
	EM_MagicCheck_None				,//"無"											
	EM_MagicCheck_Rand				,//"亂數"										(r,    ) r一律代表機率
	EM_MagicCheck_Self_Eq			,//"自己裝備( 機率 , 裝備號碼 )"				若自己有此裝備(r,編號)
	EM_MagicCheck_Target_Eq			,//"目標裝備( 機率 , 裝備號碼 )"				若目標有此裝備(r,編號)
	EM_MagicCheck_Self_EqType		,//"自己裝備類型( 機率 , 裝備類型 )"			若自己有此類武器(r,類型編號)
	EM_MagicCheck_Target_EqType		,//"目標裝備類型( 機率 , 裝備類型 )"			若目標有此類武器(r,類型編號)
	EM_MagicCheck_Self_Item			,//"自己物品( 機率 , 物品 or 重要物品 )"		若自己有(r,物品or重要物品)
	EM_MagicCheck_Target_Item		,//"目標物品( 機率 , 物品 or 重要物品 )"		若目標有(r,物品or重要物品)
	EM_MagicCheck_Self_Buff			,//"自己Buff( 機率 , 擁有某Buff )"				若自己擁有某buff(r,編號)
	EM_MagicCheck_Target_Buff		,//"目標Buff( 機率 , 擁有某Buff )"				若目標擁有某buff(r,編號)
	EM_MagicCheck_Self_Position		,//"自己位置( 機率 , 位置辨別碼 )"				沒有作用已移除
	EM_MagicCheck_Target_Position	,//"目標位置( 機率 , 位置辨別碼 )"				沒有作用已移除
	EM_MagicCheck_Self_Fight		,//"自己戰鬥( 機率 , 0非戰鬥/1戰鬥  )"			自己狀態(r,0非戰鬥/1戰鬥)
	EM_MagicCheck_Target_Fight		,//"目標戰鬥( 機率 , 0非戰鬥/1戰鬥  )"			目標狀態(r,0非戰鬥/1戰鬥)
	EM_MagicCheck_Target_Race		,//"目標種族( 機率 , 種族ID  )"					目標的種族是(r,種族編號)
	EM_MagicCheck_Self_HP			,//"自己HP低於( 機率 , HP百分比 )"				自己HP低於(r, 百分比)
	EM_MagicCheck_Time				,//"時間( 機率 , 時間 )"						沒有作用已移除
	EM_MagicCheck_Weather			,//"氣候( 機率 , 氣候辨別碼 )"					沒有作用已移除
	EM_MagicCheck_Self_BuffGroup	,//"自己Buff Group( 機率 , 擁有某Buff群組 )"	自己有某類型的buff(r, 類型編號)		
	EM_MagicCheck_Target_BuffGroup	,//"目標Buff Group( 機率 , 擁有某Buff群組 )"	自己有某類型的buff(r, 類型編號)		
	EM_MagicCheck_Self_Skill		,//"自己學會某技能( 機率 , 法術ID )"			自己可使用某技能(r,法術集合)
	EM_MagicCheck_BaseLv			,//"需求等級( 機率 , LV )"						若等級超過(r,等級)

	EM_MagicCheck_MaxCount	,
};

//施法條件
struct MagicCollectCondition
{
	MagicCheckFunctionENUM	FuncType;
	int		MagicBaseID;
	int		Arg[2];

	GameObjDbStruct* MagicBaseDB_Backup;
};


enum HitRateFuncENUM
{
	EM_HitRateFunc_Base ,				//定值
	EM_HitRateFunc_DLV	,				//等級差
	EM_HitRateFunc_DLVxDLV	,			//等級差平方
	EM_HitRateFunc_DecPerPersion	,	//依人次降低
	EM_HitRateFunc_Shoot			,	//射擊計算

};

#define _MAX_MAGICCOLLECT_COUNT_			4
#define _MAX_MAGICCOLLECT_GROUP_COUNT_		3

enum MagicSpellGroupTypeENUM
{
	EM_MagicSpellGroupType_Normal			,	//全部獨立計算
	EM_MagicSpellGroupType_FirstGroupHit	,	//第一個法術命中才會處發第二與第三組法術
	EM_MagicSpellGroupType_PrvGroupHit		,	//前一組法術命中，下一組才會處理
	EM_MagicSpellGroupType_Vampire			,	//第一個群組要命中 二三群組對自己施法
	EM_MagicSpellGroupType_Vampire1			,	//第一個群組要命中 三群組對自己施法
};

enum MagicSpellSelectTypeENUM
{
	EM_MagicSpellSelectType_Circle		,//圓形
	EM_MagicSpellSelectType_Line1		,//直線( 目標面向  有效距離)
	EM_MagicSpellSelectType_Line2		,//直線( 施法者 -> 目標 )
	EM_MagicSpellSelectType_Line3		,//直線( 施法者向目標  有效距離 )
	EM_MagicSpellSelectType_Fan			,//扇形
	EM_MagicSpellSelectType_Lighting1	,//連鎖電
	EM_MagicSpellSelectType_Lighting2	,//連鎖電( 可重覆選 )
	EM_MagicSpellSelectType_Horizontal	,//橫線
	EM_MagicSpellSelectType_Box			,//方型
};

struct MagicJobInfoStruct
{
	Voc_ENUM	Job;			//法術職業
	bool		IsJobLimit;		//是否職業限定
};

enum MagicComboTypeENUM
{
	EM_MagicComboType_Null		= -1,	//無效
	EM_MagicComboType_Earth		,	//地
	EM_MagicComboType_Water     ,   //水
	EM_MagicComboType_Fire      ,	//火
	EM_MagicComboType_Wind      ,	//風
	EM_MagicComboType_Light     ,	//光
	EM_MagicComboType_Darkness  ,	//暗
	EM_MagicComboType_Start		,	//起動技
};

// CLIENT 施法前判斷阻檔
enum MagicCollisionTypeENUM
{
	EM_MagicCollisionType_None		= 0,				// 無法
	EM_MagicCollisionType_Line,							// 施法者到目標直線測試
	EM_MagicCollisionType_TargetForward,				// 目標的面向
};

struct GameObjectMagicCollectStruct
{
//	int								MagicBase;      //第一級法術( )
	int								MagicLV;        //法術等級
	MagicorPhyENUM					EffectType;		//物理寄能 or 法術技能 or 被動技能

	//-------------------------------------------------------------------------------------
	//範圍選取
	//-------------------------------------------------------------------------------------
	GameObjectRelationENUM			TargetType;	    //有效目標
	int								AttackDistance;	//有效距離
	int								EffectRange;    //有效範圍
	GameObjectMagicEffectRangeENUM	RangeType;	    //有效類型
	MagicSpellSelectTypeENUM        RangeSelectType;//範圍選取方式
	int                             EffectCount;    //有效人數
	int								DecreaseArg;	//遞減參數( 給範圍威力處理用)
	//-------------------------------------------------------------------------------------
	HitRateFuncENUM					HitRateFunc;	//命中率
	float							HitRateArg[2];	//命中率計算參數
	//-------------------------------------------------------------------------------------
	MagicCostStruct					Cost[2];	    //消耗物品
	MagicNeedStruct					Need[2];		//需求物品
	MagicColdownBaseStruct			Coldown;		//法術冷卻
	MagicCollectFlagStruct			Flag;			//
	float							SpellTime;		//施法時間
	float							MagicAttackDelay;//施法攻擊延遲(秒)	
	int								SpellCount;		//施法次數
	float							NextSpellTime;	//下次重施法的間隔

	char							LUAScript[128];	//環境設定的Script 設定 冷確時間 消耗 法術致能
	union
	{
		MagicCollectCondition			Magic[_MAX_MAGICCOLLECT_GROUP_COUNT_][ _MAX_MAGICCOLLECT_COUNT_ ];		//此法術內含有的所有元件法術
		MagicCollectCondition			Magic_List[_MAX_MAGICCOLLECT_GROUP_COUNT_* _MAX_MAGICCOLLECT_COUNT_ ];		//此法術內含有的所有元件法術
	};
	
	MagicSpellGroupTypeENUM			MagicSpellGroupType;
	char							CheckUseScript[128];//使用檢查 lua

	int								MaxSkillLv;		//可修練等級
	float							ExpTableRate;	//技能升級表倍率
	bool							IsMagicAttackDelay_TargetDist;	//額外增加目標距離飛行所需時間

	MagicJobInfoStruct				JobInfo;

	MagicComboTypeENUM				ComboType;

	int								NextMagicID;	//施法結果後，觸發的法術

	union
	{
		int					_Mode;
		struct  
		{
			bool							IsAutoAttack				: 1;		//自動進入戰鬥
			bool							IsSwitchType				: 1;		//永久類型(開關)
			bool							IsRideEnable				: 1;		//騎乘可使用
			bool							IsShowMagicName				: 1;		//施法顯示名稱
			bool							IsStopAttack				: 1;		//停止攻擊
			bool							IsLockTarget				: 1;		//面向鎖定施法目標
			bool							IsPetCycleMagic				: 1;		//寵物可循環法術
			bool							IsAutoSpell					: 1;		//寵物產生自動施展
			bool							IsIgnoreInvincible			: 1;		//忽略物理與法術無效(目標)
			bool							IsIgnoreSilence				: 1;		//忽略物理與法術無效(自己)
			bool							IsWaterDisabled				: 1;		//水中不可使用
			bool							IsWaterEnabled				: 1;		//水中使用
			bool							IsRidePetSkill				: 1;		//騎寵的技能(座騎撥施法)
			bool							IsIgnoreTargetDead			: 1;		//忽略目標死亡
			bool							IsDiabledPvPRule			: 1;		//不處理現行犯規則
			bool							IsIgnoreDmgEffect			: 1;		//法術傷害( 不計算 武器 )
			bool							IsFixDmgEffect				: 1;		//法術傷害( 武器 能力加成 固定1秒 )
			bool							IsOnWagonEnabled			: 1;		//乘座載具可以使用
			bool							IsDisableSpellBuffEffect	: 1;		//Buff旗標影響施法無效( 瞬發 移動施法 無消耗 )
			bool							IsShareDamage				: 1;		//平均分擔傷害
		};
	};

	int								PetSkillType;			//寵物技能類型 -1表示為玩家的技能
	float							MoveDelayTime;			//施法完移動延遲
	MagicCollisionTypeENUM			CliCollisionType;
	int								CliCollisionValue;
	int								LimitLv;				//限制等級
	char							SelectTargetScript[64];	//法術爆炸目標選擇具情
	char							ShootTargetScript[64];	//法術目標選擇
	int								AddSoulPoint;			//增加SoulPoint
	int								SuitPassiveSkill;		//套裝被動技能 
};
//----------------------------------------------------------------------------------------
enum PrivateZoneTypeENUM
{
	EM_PrivateZoneType_None				,	//一般
	EM_PrivateZoneType_Private			,
	EM_PrivateZoneType_Party			,
	EM_PrivateZoneType_Raid				,
	EM_PrivateZoneType_Private_Party	,
};
enum PKZoneTypeENUM
{
	EM_PKZoneType_Normal	,	//一般非PK區
	EM_PKZoneType_PK		,	//一般PK區
};

struct MapInfoStruct
{
	int		MapID;
	char	MapName[64];
	bool	IsEnabledSave;		//是否可以存點
};

//----------------------------------------------------------------------------------------
struct GameObjectZoneStruct
{
	char	MapFile[64];					//地圖檔
	bool	IsEnabledBlockCtrl;				//用區塊設定控制範圍
	int		CtrlMaxZ;
	int		CtrlMaxX;
	int		CtrlMinZ;
	int		CtrlMinX;

	bool	IsPrivateZone;
	int		BaseRoomCount;
	int		PlayRoomCount;
	PrivateZoneTypeENUM	PrivateZoneType;	//獨立區域類型	
	int		PrivateZoneLiveTime;			//獨立區域沒人可以生存多久 


	bool	IsEnabledRevPoint;				//強制重生位置
	int		RevX , RevY , RevZ;				//重生位置
	int		RevZoneID;

	int		ViewBlock;						//視野區塊大小
//	PKZoneTypeENUM	PKType;	
	int		MapID;
	int		CampStatueObjID;				//陣營資料

	int		MapCount;						//小區塊個數
	MapInfoStruct	MapInfoList[40];		//區快資訊

	char	LuaInitZone[64];
	bool	IsEnabledRide;

	struct  
	{
		char	Key[64];
		char	Value[64];
	}ZoneIni[30];

	int		RoomPlayerCount;				//房間最多玩家數

	bool	IsWorldBattleGround;			// 是否為世界戰場
	int		iWorldBattleGroundWorldID;		// 世界戰場服務器代號

	bool	IsCountryBattleGround;			// 是否為國戰戰場
	
	bool	IsAllowTeamJoin;				// 是否允許團隊加入
	bool	IsEnableBattleGroundQueue;		// 是否參加戰場排隊系統

	int		IsLimitJoinLevel;				// 是否限定進入等級
	int		iMinJoinLevel;					// 最低登入等級
	int		iMaxJoinLevel;					// 最高登入等級

	bool	IsForceGroup;					// 是否強制組隊

	char	LuaPreJoinQueueCheck[64];
	char	LuaAssistWorldGroupID[64];
	int		iCountryWarLinkMap[4];

	bool	IsAutoJoinEventZone;			// 是否自動加入事件副本

	int     MirrorInstanceType;				// 鏡世界副本群組
	int     MirrorLimitLv;					// 鏡世界副本限制等級
	int     MirrorLimitTime;				// 鏡世界副本限制時間
	int		Mirror_X , Mirror_Y , Mirror_Z;	// 鏡世界重生位置

};
//----------------------------------------------------------------------------------------
struct CreateRoleEQInfoStruct
{
	union
	{
		int ID[ 18 ];
		struct  
		{
			int Head;			
			int Gloves;	    	
			int Shoes;			
			int Clothes;		  
			int Pants;			
			int Back;			
			int Belt;			
			int Shoulder;		
			int Necklace;      
			int Ammo;          
			int Bow;           
			int Ring1;        
			int Ring2;        
			int Earring1;      
			int Earring2;      
			int MainHand;		
			int SecondHand;		
			int Manufacture;   
		};
	};		
};


struct GameObjectCreateRoleStruct
{
	Voc_ENUM Job;

	//重生位置	
	struct 
	{
		int	ZoneID;
		int X , Y , Z , Dir;
	}BornPos;

	CreateRoleEQInfoStruct EQ;

	int ItemID[10];
	int ItemCount[10];

	RaceFlagStruct	RaceLimit;

	CreateRoleEQInfoStruct EQPreview;
};

struct GameObjectPEStruct
{
	int ParentGUID;
	int Type;

	union
	{
		int _FlagData;

		struct
		{
			bool UIVisible			: 1;
			bool ScoreVisible		: 1;
		}PE;

		struct
		{
			bool SLogic	: 1;
			bool FLogic	: 1;
		}PH;

		struct
		{
			bool Visible : 1;
			bool Minor	 : 1;			
		}OB;

	}Flag;

	union
	{
		char _MainData[256];

		struct
		{
			int CoolDown;
			int ZoneID;
			int SubZoneID[10];
		}PE;

		struct
		{
			int PHIndex;
			int NPHTimeGap;
			int Score;
			int BonusScore1;
			int BonusScore2;
		}PH;

		struct
		{
			int OBIndex;
			int OBType;
			int OBCamp;
			int InitValue;
			int Threshold;
			int NPHGUID;
			int NPHTimeGap;
			char VarName[32];
		}OB;

		struct
		{
			char VarName[32];
			char VarNote[128];
		}VAR;

	}Data;

	union
	{
		struct
		{
			char LuaEvent1[64];
			char LuaEvent2[64];
			char LuaEvent3[64];
			char LuaEvent4[64];
			char LuaEvent5[64];
			char LuaEvent6[64];
			char LuaEvent7[64];
			char LuaEvent8[64];
			char LuaEvent9[64];
			char LuaEvent10[64];
		}All;

		struct
		{
			char OnBegin[64];
			char OnSuccess[64];
			char OnFail[64];
			char OnBalance[64];
			char OnPlayerEnter[64];
			char OnPlayerLeave[64];
			char OnPHBegin[64];
			char OnPHSuccess[64];
			char OnPHFail[64];
			char OnOBAchieve[64];
		}PE;

		//struct
		//{
		//}PH;

		//struct
		//{
		//}OB;

	}LuaEvent;
};

//----------------------------------------------------------------------------------------
//遊戲基本物件資料
//----------------------------------------------------------------------------------------
struct	GameObjDbStruct
{
	int								GUID;
	GameObjectClassificationENUM	Classification;

	union
	{
		int		LanguageSet;
		struct
		{
			bool	Language1 : 1;
			bool	Language2 : 1;
			bool	Language3 : 1;
			bool	Language4 : 1;
			bool	Language5 : 1;
			bool	Language6 : 1;
			bool	Language7 : 1;
			bool	Language8 : 1;
		};
	};


	char*							Name;							//物件名稱
	char*							Name_Plural;					//複數名稱

    int                             ImageID;                        //影像資料
    GameObjectImageStruct*          ImageObj_Backup;                    
    
	//顯像資料
	int								MaxHeap;			            //最大堆疊上限
	char*							Note;							//物件註解資料
	char*							ShortNote;						//物件註解資料
	ObjectModeStruct				Mode;				            //物件的基本屬性
	PriceTypeENUM					PricesType;						//價值類型
	int								SellType;						//商品分類
	int								Cost;				            //物件的價值 ( 以遊戲幣為定價 )
	int								BuyUnit;						//購買單位(Client商店購買使用)
	int								ReviveTime;			            //物件的重生時間
	int                             Rare;                           //稀有度
    float					        GenerateRate;		            //產生速度(
    float					        MaxWorldCount;		            //最大的區域總量	

    LimitStruct                     Limit;

	ItemLiveTimeTypeENUM			LiveTimeType;					//物品生存時間類型
	int								LiveTime;						//秒為單位

	int								ACSearchType[3];				//AC 拍賣的分類
	EqWearSkillStruct				ItemEqType;						//AC 搜尋分類用

	int								SpecialMoneyCost;				//特殊貨幣定價, 以遊戲幣以外的單位計價
	int								iTagID;							// TAGID 
	

	union
	{
		GameObjectNpcStruct				NPC;
		GameObjectItemStruct			Item;

        GameObjectMagicStruct			MagicBase;
		GameObjectMagicCollectStruct	MagicCol;

		GameObjectAttributeStruct		Attirbute;
        GameObjectPlayerStruct	    	Player;
        GameObjectBodyObjStruct	    	BodyObj;
		GameObjectQuestDetail			QuestDetail;
        GameObjectMineStruct        	Mine;
        GameObjectKeyItemStruct     	KeyItem;
        GameObjectRecipeStruct      	Recipe;
        GameObjectTitleStruct       	Title;
        GameObjectLearnMagicStruct  	LearnMagic;
        GameObjectShopStruct        	Shop;
        GameObjectImageStruct       	Image;
		GameObjectSuitStruct        	Suit;
		GameCampStatuteStruct			Camp;		//陣營資訊
		GameTreasureStruct				Treasure;
		GameObjectEqRefineAttributeStruct	EqRefineAttribute;
		GameObjectZoneStruct			Zone;
		GameObjectCreateRoleStruct		CreateRole;
		GameObjectPEStruct				PE;
		GameObjectPhantomStruct			Phantom;

		char	Temp[20000];
	};
	
};


//----------------------------------------------------------------------------------------
//載Table 用
//----------------------------------------------------------------------------------------
#define _MAX_SKILL_LEVE_	100		//技能上限等級

struct		LvExpRelationTable			//經驗質相關表
{
	int 	LV;				//等級
	int 	JobExp;			//職業經驗值
	int 	SkillExp;		//技能熟練經驗值
	int 	GatherExp;		//採集經驗值
	int 	RefineExp;		//合成經驗值
	int 	PlotExp;		//劇情經驗報籌
	int 	PlotMoney;		//劇情金錢報籌
	float	JobExp_LvGrowRate;	//經驗成長率
	int		JobMagicExp;	//職業
	int		StandardCost;

	float	BaseMagicPower;
	float	MagicPowerGrowRate;
	int		AbilityPoint;
	int		DefPoint;
	int		HPPoint;
	int		HouseExpArg;	//房屋exp 對應次數
	float	MagicMPGrowRate;

	int		Pet_Exp;
	int		Pet_LifeSkill;
	int		PlantExp;		//種植經驗值
	float	PlantEffectPoint;
};
//////////////////////////////////////////////////////////////////////////
//拆解物品資料Table
struct	LvDissolutionTable
{
	int		Lv;
	int		Weapon_Item;
	float	Weapon_Rate;
	int		Armor_Item;
	float	Armor_Rate;
	int		Ring_Item;
	float	Ring_Rate;
};
//////////////////////////////////////////////////////////////////////////
struct	ComboTable
{
	int	Type[5];	//連攜方式
	int	Bonus;		//副加的法術
	int	Final;		//結束技施展的法術
};

//////////////////////////////////////////////////////////////////////////
//精練武器加乘
struct EqRefinePowerStruct
{
	float	DmgRate;
	float	DefRate;
	float	MagicAtkRate;
	float	MagicDefRate;
	float	AddDmg;
	float	AddDef;
};
//////////////////////////////////////////////////////////////////////////
//創角資料結構
#define DEF_MAX_COUNT_CreateRoleInfo_Body	100
#define DEF_MAX_COUNT_CreateRoleInfo_Color	60
#define DEF_MAX_COUNT_CreateRoleInfo_Job	20
struct CreateRoleInfoTableStruct
{
	int	BodyCount;
	struct 
	{
		bool	Enabled;
		int		OrgID;
		int		Type;
		int		ID;
	} Body[DEF_MAX_COUNT_CreateRoleInfo_Body];

	int	ColorCount;
	struct  
	{
		bool	Enabled;
		int		ID;
		int		Type;
		unsigned char	R,G,B;
		Race_ENUM	Race;
	} Color[DEF_MAX_COUNT_CreateRoleInfo_Color];

	int	JobCount;
	int		JobID[ DEF_MAX_COUNT_CreateRoleInfo_Job ];
	char	JobKeyStr[DEF_MAX_COUNT_CreateRoleInfo_Job][32];
};
//////////////////////////////////////////////////////////////////////////
//Motion的資料
struct MotionTableStruct
{
	int		ID;
	int		MotionID;
	char	IconStr[64];
};
//////////////////////////////////////////////////////////////////////////
//教學資料
struct TeachTableStruct
{
	int		ID;
	int		Height;
	int		Width;
	char	TypeStr[32];
	char	ImageStr[128];
};
//////////////////////////////////////////////////////////////////////////
enum	ColoringShopTypeENUM
{
	EM_ColoringShopType_Main		,
	EM_ColoringShopType_Off			,
	EM_ColoringShopType_Skin		,
	EM_ColoringShopType_Hair		,
	EM_ColoringShopType_HairStyle	,
	EM_ColoringShopType_FaceStyle	,
};
struct ColoringShopStruct
{
	int							ID;
	ColoringShopTypeENUM		Type;	//0 主色 1 副色 2 膚色 3 髮色 4髮型 5臉型
	union
	{
		int Value;
		struct
		{
			unsigned char B,G,R,A;
		};
		
	}Color;
	int		ObjID;				//參考物件
	int		Cost;
};
//////////////////////////////////////////////////////////////////////////
//世界地圖資料
enum WorldMapITypeENUM
{
	EM_WorldMapIType_None             = 0 , //不使用
	EM_WorldMapIType_World            = 1 , //大陸
	EM_WorldMapIType_Zone             = 2 , //地區
	EM_WorldMapIType_City             = 3 , //城市
	EM_WorldMapIType_Instance         = 4 , //副本
	EM_WorldMapIType_WorldInstance    = 5 , //世界副本
	EM_WorldMapIType_BusinessInstance = 6 , //活動副本 
	EM_WorldMapIType_Battleground     = 7 , //戰場
	EM_WorldMapIType_Other            = 8 , //其他 


};

struct WorldMapInfoStruct
{
	char    wdbFile[64];	//wdb檔名 代表一個座標系統
	char	MapName[64];	//Name
	int		MapID;			//ui 顯示的世界地圖索引
	int 	WorldID;		//將不同wdbFile 分類到同一世界用
	int 	Type;			//WorldMapITypeENUM
	int		LX;
	int 	LZ;
	int 	RX;
	int 	RZ;
};
//////////////////////////////////////////////////////////////////////////
/*
struct GuildShopInfoStruct
{
	int FlagID;
	int MemberCount;
	int RankCount;
	int NeedFlagID;		//須要那個旗標開啟才能
	int	Cost;			//買此功能要多少積分
	bool	EnabledGuildBoard;
};
*/
struct GuildLvInfoStruct
{
	int	Lv;
	union
	{
		int _UpgradeValue[7];
		struct
		{
			int	UpgradeGold;
			int	UpgradeBonusGold;
			int	UpgradeMine;
			int	UpgradeWood;
			int	UpgradeHerb;
			int	UpgradeGuildRune;
			int	UpgradeGuildStone;
		};
	};
	int	MemberCount;
	int	DeclareWar;
	int	GuildFlag;
	int	GuildHouse;
	int	GuildWar;
	int	CityWar;
	int	Quest;
	int RankCount;
	int	ChangeGuildStyle;
};
//////////////////////////////////////////////////////////////////////////
struct HouseShopInfoStruct
{
	int FlagID;
	int FunitureCount;
	int	OpenEnergy;
	int	KeppEnergy;
	int Type;			//( 0 表示為傢俱格子 1 表示其它類 )
};
//////////////////////////////////////////////////////////////////////////
struct HouseEnergyCostStruct
{
	int		HouseEnergy;
	int		AccountMoneyCost;
};

//////////////////////////////////////////////////////////////////////////
struct AccountShopInfoStruct
{
	int		Type[4];		//分類
	int		ItemObjID;	//物品ID
	int		Count;		//數量
	int		Cost;		//價錢
	int		MarkType;	// Hot or OnSell or New
};
//////////////////////////////////////////////////////////////////////////
struct SysColorDefineStruct
{
	int Type;
	int ID;
	union
	{
		int Value;
		struct
		{
			unsigned char B,G,R,A;
		};

	}Color;
};
//////////////////////////////////////////////////////////////////////////
struct SysKeyFunctionStruct
{
	int		KeyItemID;
	int		MagicID;
};
//////////////////////////////////////////////////////////////////////////
struct LotteryInfoTableStruct
{
	int		SelectCount;			//選幾個號碼
	int		CombinationCount;		//總共有多少組合
	int		SelectPrize[6][3];		//中N個的各項獎中獎次數
};
//////////////////////////////////////////////////////////////////////////
struct SysKeyValueTableStruct 
{
	char  KeyStr[64];
	int	  Value;
};
//////////////////////////////////////////////////////////////////////////
//能量換算能力加乘表
struct PowerRateTableStruct
{
	int		Power[5];
	float	PowerRate[5];
};
//////////////////////////////////////////////////////////////////////////
//能量換算能力加乘表
struct RentFunctionTableStruct
{
	int		MemberType;
	int		Cost;
	float	RentDay;
	int		RentFunc[20];
};

//////////////////////////////////////////////////////////////////////////
//賦加能力機率
struct InherentRateTableStruct
{
	int	Lv;
	union
	{
		int AllRateLv[ 50 ];
		struct 
		{
			int	ItemRateNone;
			int ItemRateSpacial;
			int	ItemRateLv[33];
		};
	};
};
//////////////////////////////////////////////////////////////////////////
//公會旗設定資料
struct	 GuildFlagTableStruct
{
	int		ID;
	int		Type;
	char	Str[ 50 ];
};
//////////////////////////////////////////////////////////////////////////
//公會建設
struct GuildBuildingInfoTableStruct
{
	int		ID;
	char	BuildPoint[64];
	char	TypeStr[32];
	int		Lv;
	int		OrgObjID;				//npc 參考物件ID
	int		SrcBuildingID;

	GuildResourceStruct Resource;
	char	NeedTypeStr1[32];
	char	NeedLv1;
	char	NeedTypeStr2[32];
	char	NeedLv2;
	int		BlockSizeX;
	int		BlockSizeY;
	ObjectModeStruct Mode;
	int		MaintenanceCharge;		//維持費
	int		NeedGuildLv;
	int		BuildSize;
	char	IconPath[64];
	int		SortID;

	void init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

//公會基本建築
struct GuildBaseBuildingTableStruct
{
	int		GUID;
	char	BuildPoint[32];
	int		ParentID;
	int		BuildID;
};
//////////////////////////////////////////////////////////////////////////
//公會物品頁購買價格
struct	GuildHouseItemPageCostTableStruct 
{
	int		GUID;
	int		ItemPageID;
	GuildResourceStruct Resource;
	
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////////////
//企化設定地圖點
struct MapPointStruct
{	
	char	KeyStr[64];
	char	wdbFile[64];
	float	X;
	float	Y;
	float	Z;
};

//關係法術 
struct RelationMagicStruct
{
	RelationTypeENUM Relation;
	int	Lv;
	int	NormalMagic;
	int Quarter_HP_Magic;	

	void Init()
	{
		Relation = EM_RelationType_None;
		Lv = 0;
		NormalMagic = 0;
		Quarter_HP_Magic = 0;	
	};
	bool IsEmpty()
	{
		if( Relation == EM_RelationType_None )
			return true;
		return false;
	}
};

/*
//符文轉換表
struct RuneExchangeTableStruct
{
	int	ExchangeTable[50];
};
*/
struct RuneExchangeExTableStruct
{
	int	Type1;
	int	Type2;
	int ResultType;
};

/*
//////////////////////////////////////////////////////////////////////////
//寵物資料表
//////////////////////////////////////////////////////////////////////////
//圈養寵物基本參數
struct CultivatePetBaseValue
{
	float Sweet;		//親蜜度
	float Loyal;		//忠誠度
	float Grow;			//成長度
	float Fitness;		//健美度
	float Hunger;		//飽食度
	float Tired;		//疲勞度
};
//////////////////////////////////////////////////////////////////////////
//寵物進化表
struct CultivatePetBaseTableStruct
{
	int PetObjID;				//寵物物件
	int BasePetObjID;			//原來的寵物物件
	int	PetType[2];	
	int NewSkill[3];

	int Evolve_RarePoint;		//進化需求餵食稀有點數
	int Evolve_GrowPoint;		//進化需求養育點數

	CultivatePetBaseValue Fix;	//數值微調影響
};
//////////////////////////////////////////////////////////////////////////
//寵物屬性產生法術Buff表 
struct CultivatePetValueEffectTableStruct
{
	int	MagicBuffID;
	CultivatePetBaseValue LimitLow;
	CultivatePetBaseValue LimitHi;
};
//////////////////////////////////////////////////////////////////////////
//寵物事件如何設定( 打工 , 玩耍 , 散步 , 訓練 , 修習 )與影響的數值(table)
struct CultivatePetEventTableStruct
{
	int		ActionType[2];				//活動分類
	char	KeyStr[64];					//事件內容
	char	LuaScript[64];				//事件執行的劇情
	struct  
	{
		int		PetType[2];			//寵物類型
		int		KeyItem;			//重要物品
		int		Character;			//個性
		CultivatePetBaseValue Low;
		CultivatePetBaseValue Hi;

	}Limit;
	CultivatePetBaseValue Effect;
	int		Money;						//需求 or 獲得金錢
};
//////////////////////////////////////////////////////////////////////////
//寵物說話表
struct CultivatePetTalkTableStruct
{
	char  KeyStr[64];
	struct
	{
		int		KeyItem;
		int		Character;
		int		PetType[2];
		CultivatePetBaseValue Low;
		CultivatePetBaseValue Hi;				
	}Limit;

	int		ActionTimeType;
	int		IntervalTime;
	int		Rate;
};
//////////////////////////////////////////////////////////////////////////
//寵物成長表
struct CultivatePetGrowTableStruct
{
	int Type;
	int Lv;
	int Policy;
	int Str;
	int Sta;
	int Int;
	int Mnd;
	int Agi;
	};
*/
//////////////////////////////////////////////////////////////////////////
/*
//寵物基本表
struct CultivatePetBaseTableStruct
{
	int PetType;
	int	BaseStr;
	int	BaseSta;
	int	BaseInt;
	int	BaseMnd;
	int	BaseAgi;
	int	MinTalent;
	int	MaxTalent;
};
*/
//寵物圖鑑
struct PetCollectionTableStruct
{
	int GUID;
	int ObjID;
};
//寵物技能
struct CultivatePetLearnMagicTableStruct
{
	struct  
	{
		int PetType;
		int PetProperty;
		int Lv;
		int Str;
		int Sta;
		int Int;
		int Mnd;
		int Agi;
		int KeyItem;
		int Lock;			//專屬某PetType,不能繼承
	}Limit;

	int MagicID;
	int	PowerLv;
	int SkillPoint;		//需求技能點數

	bool operator > ( const CultivatePetLearnMagicTableStruct& P ) const
	{
		if( MagicID == P.MagicID )
			return PowerLv > P.PowerLv;
		return MagicID > P.MagicID;
	};

	bool operator < ( const CultivatePetLearnMagicTableStruct& P ) const
	{
		if( MagicID == P.MagicID )
			return PowerLv < P.PowerLv;
		return MagicID < P.MagicID;
	};
};

//寵物生活技能
struct CultivatePetLifeSkillTableStruct
{
	int Lv;
	int SkillType;
	int EventTime;
	struct
	{
		int SkillLv;
		int	ToolID;
		int ItemID;
		int ItemCount;
	}Need;
	struct
	{
		int ItemID;
		//int	ItemCount;
		//int	ItemMaxCount;
	}Product;
};

//////////////////////////////////////////////////////////////////////////
/*
//種植 施肥資料
struct PlantGrowActionTableStruct
{
	int ID;
	int	Type;
	int GrowRate;
	int Water;			//0否 1 可 
	int Topdress;
	int MagicWater;
};
*/
//////////////////////////////////////////////////////////////////////////
//種植 收成資料
struct PlantProductTableStruct
{
	int SeedObjID;
	int Env_RarePoint;
	int Env_GrowPoint;
	int DropID;
	int	DropID_DLv5;
	int DropID_DLv10;
	float	ExpRate;
	char	LuaScript[32];
};
//////////////////////////////////////////////////////////////////////////
//工會物npc 替代處理
struct GuildHouseNpcReplaceTableStruct
{
	int Type;
	int OrgNpcID;
	int NpcID;
};

//工會物npc 替代處理價錢
struct GuildHouseNpcReplaceCostTableStruct
{
	int Type;
	int GuildLv;
	GuildResourceStruct	Cost;
};

//////////////////////////////////////////////////////////////////////////
//屬性賭博表
struct GambleItemStateTableStruct
{
	int	GambleObjID;
	int FirstTimeCost;
	int ContinueCost;
	int MaxLv;
	int MinLv;
};
//////////////////////////////////////////////////////////////////////////
// 女僕事件
//////////////////////////////////////////////////////////////////////////
enum ServantCondition_Servant_ENUM
{
	EM_ServantCondition_Servant_Boy		,
	EM_ServantCondition_Servant_Girl	,
	EM_ServantCondition_Servant_Monster	,
	EM_ServantCondition_Servant_All	,
};


enum ServantCondition_Master_ENUM
{
	EM_ServantCondition_Master_MasterBoy	,	//男主人
	EM_ServantCondition_Master_MasterGirl	,	//女主人
	EM_ServantCondition_Master_Boy			,	//男客人
	EM_ServantCondition_Master_Girl			,	//女客人
	EM_ServantCondition_Master_Master		,	//主人
	EM_ServantCondition_Master_Visitor		,	//客人
	EM_ServantCondition_Master_All			,	//全部
};


//女僕事件表
struct ServantEventTableStruct
{
	int	GUID;					//事件號碼
	int	EventType[2];			//事件類型	
	union
	{
		int	Condition[3];			//條件
		struct
		{
			ServantCondition_Servant_ENUM	Servant;
			ServantCondition_Master_ENUM	Master;
			int		Character;					//個性
		}Check;
	};

	int Rate;					//發生機率
	int MinValue[8];			//最低數值需求
	int	MaxValue[8];			//最高數值需求
	int MotionID;				//動作
	char TalkStr[128];			//說話
	char Voice[128];			//聲音檔
	char LuaScript[128];		//Server Lua 劇情
	char LuaCheckScript[128];	//Server Lua 檢查 是否可以執行
};
//////////////////////////////////////////////////////////////////////////
//雇用女僕
struct ServantHireTableStruct
{
	int NPCObjID;
	int FaceID;
	int HairID;
	int SkinColor;
	int HairColor;
	int	ClothColor1;
	int ClothColor2;
	int Character;
};
//////////////////////////////////////////////////////////////////////////
struct ServantStartValueTableStruct
{
	int NPCObjID;
	int StartValue[8];
	int MaxValue[8];
	int Sex;
	int LookNpcObjID;
	int Cost;
};
//////////////////////////////////////////////////////////////////////////
struct ItemCombineStruct
{
	int ProductID;
	int	ProductCount;
	int SourceID[5];
	int	SourceCount[5];

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//煉化 稀有度上升兌換物品表
struct LifeSkillRareExStruct
{
	int ItemID;
	int	RareItemID[3];
};
//////////////////////////////////////////////////////////////////////////
//雕文系統共鳴組設定表
struct RuneSystemStruct
{
	int GUID;
	int MagicCol;		//共鳴效果
	int MagicColEx;		//強化共鳴效果
	int TriggerCount;
	int RuneColor[6];
};
//////////////////////////////////////////////////////////////////////////
struct LoadTableStruct
{
	int GUID;
	union
	{
		char					Data[1];							//資料開始位置
		FixFightArgumentStruct  FixTB;								//固定參術
		FightArgumentStruct     ArgTB;								//種族 職業參數表

		int     ExpTB[_MAX_VOCATION_COUNT_];						//職業經驗值表
		int     SkillValueBase[ _MAX_SKILLVALUE_BASETYPE ];			//技能值表

		struct
		{
			int     JobSkillValue[ _MAX_VOCATION_COUNT_ ];			//各職業技能的熟練 ( 記錄類似 S+ S S- A+ A A- ...)
		};

		EqWearSkillStruct JobWearSkill[ _MAX_VOCATION_COUNT_ ];		//各職業可穿的類型

		struct
		{
			int		WeaponBaseDelayTime[ _MAX_SKILLVALUE_TYPE ];	//各種武器的基本延遲時間
			float	WeaponBaseDmg[ _MAX_SKILLVALUE_TYPE ];			//各種武器的基本傷害比( 要乘上該等級GM的傷害 )
			int		WeaponBaseRand[ _MAX_SKILLVALUE_TYPE ];
			float	WeaponBaseMAtk[ _MAX_SKILLVALUE_TYPE ];
			float	WeaponBaseCostRate[ _MAX_SKILLVALUE_TYPE ];
			
		};

		int		BaseMagicList[ EM_BaseMagic_MaxCount ];				//基本的效能法術  比方震暈 無敵

		ResistArgumentStruct	ResistArg;							//抗性參數

		int		RefineExp[ _MAX_SKILL_LEVE_];						//煉製經驗值表(要升下一級的經驗值)


		LvExpRelationTable	AllExp;									//經驗質相關表

//		EqRefinePowerStruct	EqRefine;								//精練武器加乘

		CreateRoleInfoTableStruct CreateRole;

//		LvDissolutionTable	Dissolution;
		ComboTable			Combo;

		MotionTableStruct	Motion;

		TeachTableStruct	Teach;									//教學資料

		ColoringShopStruct	ColoringShop;

		WorldMapInfoStruct	WorldMapInfo;

//		GuildShopInfoStruct	GuildShopInfo;
		GuildLvInfoStruct	GuildLvInfo;

		AccountShopInfoStruct	AccountShopInfo;

//		SysColorDefineStruct SysColorDefine;

		SysKeyFunctionStruct SysKeyFunction;

		LotteryInfoTableStruct	LotteryInfoTable;

		SysKeyValueTableStruct SysKeyValue;

		InherentRateTableStruct	InheretRate;

		HouseShopInfoStruct HouseShopInfo;

		HouseEnergyCostStruct HouseEnergyCost;

		PowerRateTableStruct PowerRate;

		RentFunctionTableStruct	RentFunction;

		GuildFlagTableStruct	GuildFlagTable;

		MapPointStruct			MapPoint;

		RelationMagicStruct		RelationMagic;

		RuneExchangeExTableStruct RuneExchangeExTable;

		GuildBuildingInfoTableStruct	GuildBuilding;
		GuildBaseBuildingTableStruct	GuildBaseBuilding;
		GuildHouseItemPageCostTableStruct	GuildHouseItemPageCost;

		CultivatePetLearnMagicTableStruct	CultivatePetLearnMagic;
		CultivatePetLifeSkillTableStruct	CultivatePetLifeSkill;

		PlantProductTableStruct PlantProduct;
		GambleItemStateTableStruct GambleItemState;

		ServantEventTableStruct	ServantEvent;
		ServantHireTableStruct ServantHire;
		ServantStartValueTableStruct ServantStartValue;

		ItemCombineStruct		ItemCombine;
		LifeSkillRareExStruct	LifeSkillRareEx;
		GuildHouseNpcReplaceTableStruct	GuildHouseNpcReplace;
		GuildHouseNpcReplaceCostTableStruct	GuildHouseNpcReplaceCost;
		RuneSystemStruct			RuneSystem;
		PetCollectionTableStruct	PetCard;
		AbiParametersTableStruct	PhantomAbi;
		PhantomRankTableStruct		PhantomRank;
		PhantomLvTableStruct		PhantomLv;
		PhantomSkillTableStruct		PhantomSkill;
	};

};
//----------------------------------------------------------------------------------------
#endif
