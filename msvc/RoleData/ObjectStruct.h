//----------------------------------------------------------------------------------------
//			�C���Ҧ�����򥻸��
//----------------------------------------------------------------------------------------
#ifndef	__OBJECTSTRUCT_H_2003_09_16__
#define __OBJECTSTRUCT_H_2003_09_16__
#pragma		warning (disable:4819)
#include	<windows.h>

//����
#define		_DEF_VERSION	"v0.20"


#define		_MAX_NPC_QUEST_COUNT_			20			// NPC �̦h�൹������
#define		_MAX_QUEST_COUNT_				30			// ����̦h�i�H���� Quest �ƶq

#define		_MAX_QUEST_FLAG_COUNT_			8192		// ����ثe���� Quest ���ƶq, �ثe�̦h�]�w 2048
#define		_MAX_QUEST_KILLKIND_COUNT_		5			// �C�@�� Quest ���w���˥ؼЪ�����
#define		_MAX_QUEST_CLICKIND_COUNT_		5


//----------------------------------------------------------------------------------------
#define		_MAX_OBJ_NAME_STR_SIZE_		    32			//�W�r�r����שw�q
#define		_MAX_NPC_DROPITEM_COUNT_		5			//�w�q���~�̦h���������ƶq
#define		_MAX_SKILL_COUNT_				30			//�̦h�h�ּƭȧޯ�(���m��)
#define		_MAX_RACE_COUNT_			    32			//32�Ӻرڼƶq
#define		_MAX_VOCATION_COUNT_		    32			//32��¾�~
#define		_MAX_SEX_COUNT_		            5			//�ʧO�ƶq
#define		_MAX_FILENAME_SIZE_		        128			//�ɮצW��
#define     _MAX_LEVEL_                     200         //�̰�����
#define     _MAX_DROPITEM_COUNT_            15          //�̦h�Ǫ��i�����~�ƶq
#define     _MAX_DROP_ABILITY_COUNT_        6           //�������~�̦h�����Ӫ��[�ݩ�
#define     _MAX_NPC_EQSEL_COUNT_           5           //�Ǫ��i�諸�Z���̤j�q
#define     _MAX_SPSkill_COUNT_             200          //�̤j¾�~�M�ݧޯ�
#define     _MAX_NormalSkill_COUNT_         50          //�̤j�@��¾�~�ޯ�

#define     _MAX_EQ_Skill_COUNT_		    20          //�䥦���ޯ�
#define     _MAX_Lua_Skill_COUNT_			20          //�䥦���ޯ�


#define     _MAX_Edit_SPSkill_COUNT_        200         //�̤j¾�~�M�ݧޯ�
#define     _MAX_Edit_NormalSkill_COUNT_    300         //�̤j�@��¾�~�ޯ�


#define     _MAX_PASSIVESKILL_COUNT_        30          //�̦h�P�ɦ��h�֭ӳQ�ʧޯ�
#define     _MAX_SELL_ITEM_SAVE_COUNT_      10          //��檫�~�����̤j�q

#define     _MAX_SKILLVALUE_BASETYPE        20          //�򥻪Z�����m�ת������`�� (s+ s s- ..... )
#define     _MAX_SKILLVALUE_TYPE            30          //�򥻪Z�����m�ת�����

#define		_MAX_QUESTLINK_COUNT			20			// �C�� NPC �̦h�M�h�֭ӥ��Ȧ������s
#define		_MAX_SPEAKOPTION_COUNT_			10
#define		_MAX_SCRIPTBORDER_PAGE_			20			// �۸O�����̦h����
#define		_MAX_PET_SKILL_COUNT_			20			//�d���̦h�|�X�ӧޯ�
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
#define Def_ObjectClass_Player				1000		// ���a����
#define Def_ObjectClass_BodyObj				2000		// ���骫��
#define Def_ObjectClass_NPC					100000		// NPC
#define Def_ObjectClass_QuestNPC			110000		// QuestNPC ( 110000-119999 )
#define Def_ObjectClass_Item				200000		// ���~(200000) �˳� �Z�� ���� 
#define Def_ObjectClass_Weapon				210000		// �Z��
#define Def_ObjectClass_Armor				220000		// ����
#define Def_ObjectClass_Phantom				250000		// ���F
#define Def_ObjectClass_Table				300000		// 
#define Def_ObjectClass_QuestCollect		400000		// ( 20000  ) �൹�� Quest �� NPC �N��
#define Def_ObjectClass_QuestDetail			420000		// ( 200000 ) Quest
#define Def_ObjectClass_MagicCollect		490000		// �k�N���X���
#define Def_ObjectClass_Magic				500000		// �k�N���
#define Def_ObjectClass_Attribute   		510000		// ���[��O
#define Def_ObjectClass_Rune           		520000		// �Ť�
#define Def_ObjectClass_Title          		530000		// �Y��
#define Def_ObjectClass_KeyItem        		540000		// Key Item
#define Def_ObjectClass_KeyItemEx      		640000		// Key Item
#define Def_ObjectClass_Recipe        		550000		// �t���
#define Def_ObjectClass_Mine          		560000		// �q��
#define Def_ObjectClass_Image          		570000		// �ϧ�
//#define Def_ObjectClass_Flag          		580000		// �X�l
#define Def_ObjectClass_LearnMagic          590000		// �k�N�ǲߪ�
#define Def_ObjectClass_Shop                600000		// �ө���T
#define Def_ObjectClass_Suit                610000		// �M�˸�T
#define Def_ObjectClass_MagicEx             620000		// �k�N��� �X�R
#define Def_ObjectClass_LuaScript           700000		// lua�@������
#define Def_ObjectClass_Camp	            710000		// �}���T
#define Def_ObjectClass_Treasure            720000		// �_��������
#define Def_ObjectClass_CliLuaScript        730000		// lua�@������
#define Def_ObjectClass_EqRefineAbility     740000		// �ĵ���O
#define Def_ObjectClass_Zone			    750000		// �ϰ�]�w��T
#define Def_ObjectClass_CreateRole		    760000		// �ب�����
#define Def_ObjectClass_Card				770000		// �d��
#define Def_ObjectClass_Flag          		780000		// �X�l
#define Def_ObjectClass_PE          		790000		// �������� (790000 - 899999) PE : 790000 -791999 PH : 792000 - 809999, OB : 810000 - 854999, VAR : 855000 - 899999
#define Def_ObjectClass_ImageEx        		800000		// �ϧ�
#define Def_ObjectClass_MagicCollectEx		850000		// �k�N���X���
#define Def_ObjectClass_Item_Total			100000
#define Def_ObjectClass_QuestDetail_Total	 70000
#define Def_ObjectClass_QuestNPC_Total		 20000		// QuestNPC
#define Def_ObjectClass_KeyItem_Total		 10000
#define Def_ObjectClass_Recipe_Total		 10000
//----------------------------------------------------------------------------------------
// Quest ����
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
//AC ���~�j�M�����w�N
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
//�S�O�t�ΨϥΪ����~
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
	EM_ACPriceType_GameMoney		,		//�C����
	EM_ACPriceType_AccountMoney		,		//�b����
	EM_ACPriceType_BonusMoney		,		//���Q��
	EM_ACPriceType_Phirius			,		//���դB
	EM_ACPriceType_Honor			,		//�Գ��a�A
	EM_ACPriceType_Arena			,		//�v�޳��I��(Arena)
	EM_ACPriceType_GuildWarEnergy	,		//���|�ԯ�q
	EM_ACPriceType_GuildWarHonor	,		//���|�Ծ��Z
	EM_ACPriceType_TrialBadge 		,		//�շ�����
	EM_ACPriceType_Relics 			,		//�j�N��
	EM_ACPriceType_Dreamland		,		//�ڹҥ����L�O
	EM_ACPriceType_PhiriusShell		,		//�����Ŷꨩ
	EM_ACPriceType_EnergyJustice	,		//���q��q
	EM_ACPriceType_ProofLegend		,		//�ǻ�����
	EM_ACPriceType_DuelistReward	,		//�i�h����
	EM_ACPriceType_MirrorCoin		,		//������L

};
//-----------------------------------------------------------------------------
enum BaseMagicTypeENUM
{
	EM_BaseMagic_Unbeatable			,
	EM_BaseMagic_Slow				,
	EM_BaseMagic_ReviveWeak			,		//���ͰI�z
	EM_BaseMagic_NoSearchEnemy		,		//���ͤ�����
	EM_BaseMagic_PlayerUnbeatable	,		//���a���ͮɵL��
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
	EM_RelationType_None	= -1,	//�L���Y
	EM_RelationType_Stranger	,	//���ͤH
	EM_RelationType_Friend		,	//�n��
	EM_RelationType_Enemy		,	//���H

	EM_RelationType_Student		,	//�ǥ�
	EM_RelationType_Teacher		,	//�Ѯv
	EM_RelationType_Wife		,	//�d�l
	EM_RelationType_Husband		,	//����
	EM_RelationType_Lover		,	//���H
	EM_RelationType_Family		,	//�ˤH
	EM_RelationType_BestFriend	,	//����
	EM_RelationType_BadCompany	,	//�l��

	EM_RelationType_MaxRelation	,
};

//-----------------------------------------------------------------------------
//���⪬�A
//----------------------------------------------------------------------------------------
struct	GameObjDbStruct;
typedef union {
	int value;
	struct {
		bool		isUnholster			:1;		// true ���X�Z��	Script �N�X 1
		bool		isWalk				:1;		// true ����		Script �N�X 2
		bool		isCombat			:1;		// true �԰���		Script �N�X 4
		bool		isDead				:1;		// true ���`��		Script �N�X 8
		bool		isSpell				:1;		// true �I�k��		Script �N�X 16

		bool		isSit				:1;		// true ���U		Script �N�X 32
		bool		isSleep				:1;		// true ��ı
		bool		isCrouch			:1;		// true �ۤU
		bool		isCrafting			:1;		// true �[�u
		bool		isSitChair			:1;		// true ���b�Ȥl�W
	};

}RoleSpriteStatus;
//----------------------------------------------------------------------------------------
//�C�����������C�|
//----------------------------------------------------------------------------------------
enum	GameObjectClassificationENUM
{
	EM_ObjectClass_None   = -1      ,
	EM_ObjectClass_Player = 0		,
	EM_ObjectClass_NPC			    ,		// 1	
	EM_ObjectClass_Item			    ,		//���~	�˳� �Z�� ���� 2
	EM_ObjectClass_MagicBase		,		// 3 
	EM_ObjectClass_BodyObj			,		// 4 
	EM_ObjectClass_Attribute        ,		//�_�[�ݩ�	
	EM_ObjectClass_QuestCollect     ,
	EM_ObjectClass_QuestDetail      ,		
	EM_ObjectClass_Title            ,		//�Y��
	EM_ObjectClass_KeyItem          ,		//���n���~
	EM_ObjectClass_Recipe           ,		//�t���
	EM_ObjectClass_Mine             ,		//�q��
	EM_ObjectClass_Flag             ,		//�X�l���
	EM_ObjectClass_Image            ,		//�϶H���
	EM_ObjectClass_QuestNPC			,		//����
	EM_ObjectClass_LearnMagic       ,		//�k�N�ǲ�
	EM_ObjectClass_Shop             ,		//�ө�
	EM_ObjectClass_Suit             ,		//�M��
	EM_ObjectClass_LuaScript        ,		//�@��
	EM_ObjectClass_Camp		        ,		//�}��
	EM_ObjectClass_Treasure	        ,		//�_�c
	EM_ObjectClass_MagicCollect     ,		//�k�N���X
	EM_ObjectClass_EqRefineAbility  ,		//�˳ƺ�Ҫ�
	EM_ObjectClass_Zone			    ,		//�ϰ�
	EM_ObjectClass_CreateRole		,		//�ب�����
	EM_ObjectClass_PE				,		//PE�˪O
	EM_ObjectClass_Phantom			,		//���F

	EM_ObjectClass_Max				,
	EM_GameObjectClassificationEM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//�رڦC�|
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
//�ʧO�C�|
enum	Sex_ENUM
{
	EM_Sex_Boy			= 0,
	EM_Sex_Girl			   ,
	EM_Sex_BigMonster  	   ,		//��^
	EM_Sex_King		  	   ,		//��
	EM_Sex_WorldKing	   ,		//�@�ɤ�
	EM_Sex_Max_Sex         ,
	EM_Sex_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//¾�~�C�|
enum	Voc_ENUM
{
	EM_Vocation_None	    = -1,       		//�S��¾�~
	EM_Vocation_GameMaster	= 0	,
	EM_Vocation_Warrior			,				// �Ԥh
	EM_Vocation_Ranger			,				// �C�L
	EM_Vocation_Rogue			,				// �v���
	EM_Vocation_Wizard			,				// �k�v
	EM_Vocation_Priest			,				// ���q
	EM_Vocation_Knight			,				// �M�h
	EM_Vocation_RuneDancer		,				// �˪L����
	EM_Vocation_Druid			,				// �۵M���x
	EM_Vocation_Harpsyn			,				// �F���
	EM_Vocation_Psyron			,				// �Ť�u�K
	EM_Vocation_Duelist			,				// ���Ѥh
	EM_Vocation13		,
	EM_Vocation14		,
	EM_Vocation15		,
	EM_Vocation16		,
	EM_Max_Vocation     ,
	EM_Vocation_EM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//�}������
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
//¾�~�X��
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
//�رںX��
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
//�ʧO�X��
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
// �ƽ�p��Ѽ�
//----------------------------------------------------------------------------------------
//�T�w�Ѽ�
struct FixFightArgumentStruct
{
	union
	{
		float Arg[ 100 ];
		struct  
		{
			float DmgAtkArg;			//ATK��DMG���
			float MDmgMAtkArg;			//MATK��MDmg���
			float Crit_DLV;				//�P�R�@���v ���t�v�T 
			float DMG_DLV;				//�ˮ` ���t�v�T 
			float Miss_DLV;				//�R���v ���t�v�T
			float Miss_SecHand;			//�Ƥ�R���v�վ�
			float Dmg_SecHand;			//�Ƥ�����v�վ�
			float BaseCritHit;			//�򥻪�Critial ���v
			float BaseCritPower;		//�򥻪�Critial �¤O
			float BaseMagicCritHit;		//�򥻪��]�k Critial ���v
			float BaseMagicCritPower;	//�򥻪��]�k Critial �¤O
			
			float Dmg_MagArg;			//����ޯ��B�~�W�[( ���Ѽ�*DMG)
			float MDmg_MagArg;			//(�ˮ`)�]��(or�[��)�ޯ��B�~�W�[( ���Ѽ�*MDMG*�I�k���)
			float MDmg_DotArg;			//(�ˮ`)Dot�ޯ��B�~�W�[( ���Ѽ�*MDMG*�I�k���/dot����)

			float Dmg_HealArg;			//(�v��)�[���B�~�W�[( ���Ѽ�*MDMG*�I�k��� )
			float Dmg_HealDotArg;		//(�v��)Dot�ޯ��B�~�W�[( ���Ѽ�*MDMG*�I�k���/dot����)

			float BaseRateArg;			//�𨾤�( �P�R ���� ���� )
			float BaseResistArg;		//�𨾤�( �ܭP�R ����� ����� )
			float DLvRateArg;			//�𨾤񵥯żv�T( �P�R ���� ���� )
			float DLvResistArg;			//�𨾤񵥯żv�T(  �ܭP�R ����� ����� )

			float PhyHit_Base;			//���z�R�� ��
			float PhyHit_Range;			//���z�R�� �ܤƶq
			float PhyHit_AgiArg;		//���z�R�� Agi�v�T
			float PhyAvoid_AgiArg;		//���z�{�� Agi�v�T

			float MagHit_Base;			//�k�N�R�� ��
			float MagHit_Range;			//�k�N�R�� �ܤƶq
			float MagHit_MndArg;		//�k�N�R�� Mnd�v�T
			float MagAvoid_AgiArg;		//�k�N�R�� Agi�v�T
			float MagAvoid_MndArg;		//�k�N�{�� Agi�v�T

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
			float Crit_DLV;     //���Ůt�v�T �P�R�@���v
			float DMG_DLV;      //���Ůt�v�T �ˮ`
			float Miss_DLV;     //���Ůt�v�T �R���v
			float Miss_Skill_DLV;	//�ޯ�t�v�T�@���R�� �P �u��{�� 
			float JobExSkillExp;	//job�g��ȻP Skill���g��Ȫ����
			float Miss_SecHand;		//�Ƥ�R���U��
			float Dmg_SecHand;		//�Ƥ�����U��(%)
			float BaseCritHit;			//�򥻪�Critial ���v
			float BaseCritPower;		//�򥻪�Critial �¤O
			float BaseMagicCritHit;		//�򥻪��]�k Critial ���v
			float BaseMagicCritPower;	//�򥻪��]�k Critial �¤O
			float MagAtkDmgArg;			//�C�@�I��MagAtk����X���ˮ`�O
		};*/
	};

};
//----------------------------------------------------------------------------------------
//�Ѻب�¾�~���ź�X�Ӫ���
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
//�ܩʪ�򥻵��c
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
			int		Power0;			//��100%
			int		Power25;		//��75%
			int		Power50;		//��50%
			int		Power75;		//��25%
			int		Power100;		//�����Ө�
		};
	};
};
//-------------------------------------------------------------------------------------
//���|�귽
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
// �����v���]�w
//----------------------------------------------------------------------------------------
struct SystemFlagStruct
{
	union
	{
		int		_Value;
		struct  
		{
			bool	DisableTrade		: 1;		//����T��( AC Shop Mail Trade House)
			bool	DisableTalk			: 1;		//��͸T��
			bool	ChangeNameEnabled	: 1;		//�i��W
			bool	IsHero				: 1;		//
			bool	IsDemon				: 1;		//
			bool	IsHonorLeader		: 1;		// �a�A�ն����A( �p�G���H��Party ����)
			bool	IsNeedSetPosition	: 1;		//���Ϯɭn���s�]�w��m
			bool	FindParty			: 1;
			bool	IsContorlPet		: 1;		//�i�����d��
			bool	PassengerAttackable	: 1;		//�i��������
			bool	MoneySerialCodeError: 1;		//����SerialCode���~
			bool	EnableGMCmd			: 1;		//�}��GM �R�O
		};
	};
};
//----------------------------------------------------------------------------------------
//�򥻪����ݩʩw�q (���󲣥ͥi�]�w����) �C�Ӫ��󪺦@�γ]�w
//----------------------------------------------------------------------------------------
struct	ObjectModeStruct
{
	union
	{
		int			_Mode;			//�p�G_Mode == -1 ��ܸ�ƨS����
		struct		//npc �ݩ�
		{
			//�㹳����
			bool	Show	    		:1;		    //0x00000001	�q�X(���רq�X������, �аO/�P��)
			bool	Mark	    		:1;		    //0x00000002	�i�аO/�I��(�i�H�����a�I��)
			bool	Obstruct    		:1;		    //0x00000004	�|����(���ר�L������)
			bool	Gravity	    		:1;		    //0x00000008	�����O(�a�ߤޤO, �p�⪫��P�a�����I��, �_�h�̷� Client �e�Ӫ��y��, ���|�̦a�����ק��� y)
			bool	Save	    		:1;		    //0x00000010	������O�_�n�x�s
			bool    Drag            	:1;         //0x00000020    �����O��
			bool    GMHide             	:1;			//0x00000040    ��������
			bool    IsAllZoneVisible  	:1;			//0x00000080    ����i������

			bool	DisableRotate		:1;			//0x00000100	�T�����( ���V���|���� ) 
			bool	GM_NpcHide			:1;			//0x00000200	��GM�R�O���Y��NPC hide
			bool	Remove				:1;			//0x00000400	�i�_����(���|�ؿv)
			bool	RelyOwnerPower		:1;			//0x00000800	�ѦҥD�H���¤O
			bool	IgnoreNpcKill		:1;			//0x00001000	����npc����
			bool	EnemyHide			:1;			//0x00002000	�Ĥ�ݤ��ئ�����
			bool    NotShowHPMP    		:1;         //0x00004000	����ܦ��
			bool	NoFix_Y				:1;			//0x00008000	���ץ���b

			//NPC�欰
			bool	Strikback			:1;			//0x00010000	����
			bool	Move				:1;			//0x00020000	����
			bool	Searchenemy			:1;			//0x00040000	�j�M�ĤH
			bool	Revive				:1;			//0x00080000	�i����(�i�� SERVER, �}�Ҧ��X�Ъ�����ݭn����, ���ͮɶ��d�� Revive)
			bool	Fight				:1;			//0x00100000	�i�������(�}�Ҧ��X�Ъ�����i�H�Q���)
			bool    Escape          	:1;         //0x00200000    �k�]
			bool    SearchenemyIgnore	:1;         //0x00400000    �����󤣷|�Q�j�M��

			//�Ѽ�
			bool	AlignToSurface		:1;			//0x00800000	�K����
			bool	HideName			:1;			//0x01000000	NPC �� �����Y�W���W�٬O�_��� ( �����~���ҥ~ )
			bool	HideMinimap			:1;			//0x02000000	NPC �� ����b�p�a�ϤW���O�_��� ( �����~���ҥ~ )
			bool	ShowRoleHead		:1;			//0x04000000	�I�������,�O�_�n����Y����( true �O show, Hide �O

			bool	CollisionPlot		:1;			//0x08000000	�O�_�֦��I���@��
			bool	Treasure			:1;			//0x10000000	�_�c
			bool	IsPet				:1;			//0x20000000	�d��
			bool	DisableAction		:1;			//0x40000000	�Ȯɧ��ܰʧ@
			bool	DisableMovePG		:1;			//0x80000000	�i�����㤣�e���ʫʥ]
		};
		struct  //���~�ݩ�
		{
			bool	DurableStart0		:1;			//0x00000001	�@�[�׭�0�}�l
			bool	PkNoDrop			:1;			//0x00000002	pk�ɤ��|����
			bool	DepartmentStore		:1;			//0x00000004	�ӫ����~
			bool	DepartmentStore_Free:1;			//0x00000008	�����B�ӫ����~
			bool	ItemDrop_AllParty	:1;			//0x00000010	��������
			bool	UseWithoutFail		:1;			//0x00000020	�ϥΤ��|����
			bool    SpecialSuit    		:1;         //0x00000040	�Ÿ�
			bool	ItemDrop_Depart		:1;			//0x00000080	���~�����۰ʤ���
			//���~���
			bool	PickupBound			:1;			//0x00000100	�˨��T��
			bool	Sell				:1;			//0x00000200	�i�R��
			bool	Logoutdel			:1;			//0x00000400	���u����
			bool	Expense				:1;			//0x00000800	����
			bool	Coloring			:1;			//0x00001000	�i�V��
			bool	GuildMark			:1;			//0x00002000	���|��
			bool    EQSoulBound     	:1;         //0x00004000	�˳ƸT��
			bool	HideCount			:1;			//0x00008000	����ܼƶq
			bool	ChangeZoneDel		:1;			//0x00010000	���Ϯ���
			bool	HideRefineLight		:1;			//0x00020000	�ĵ��Z������ܯS��
			bool	Unique				:1;			//0x00040000	�ߤ@���~
			bool	VariableRare		:1;			//0x00080000	(�t��M��)�}���׷|����
			bool	NoNPCAbility		:1;			//0x00100000	���~�������a���~�����ݩ�
			bool	EnableLockedItem	:1;			//0x00200000	�i����w�����~�ϥ�
			bool	AutoUseItem			:1;			//0x00400000	�۰ʨϥΪ��~
			bool	DisableRefine		:1;			//0x00800000	���i���
			bool	DisablePowerQuality	:1;			//0x01000000	���i�ɶ�
			bool	DisableMagicBox		:1;			//0x02000000	���i�ϥ��]���_��
			bool	DisableDigHode		:1;			//0x04000000	�L�k����
			bool	HideMaxHeap			:1;			//0x08000000	����̤ܳj���|�q
		};
		struct //�Y���ݩ�
		{
			bool	PreViewTitle		:1;			//0x00000001	�i�w���Y��
		};
	};

	bool	GetMode( int i )
	{
		int T = 0x1 << i;
		return (_Mode & T) != 0;
	};


};
//----------------------------------------------------------------------------------------
//	�k�N�ݩʼv�T�ĪG
//----------------------------------------------------------------------------------------
struct		MagicEffectStruct
{
	union
	{
		int			_Value[2];
		struct
		{
			//�@��
			bool    UseMagicDisable     :1;     //���i�Ϊk�N����
			bool    UsePhyDisable       :1;     //���i�Ϊ��z����
			bool    BadMagicInvincible  :1;     //�a���k�N�L��(�k�N�ޯ�L��)
			bool    BadPhyInvincible    :1;     //�a�����z�L��(���z�ޯ�P�@������L��)
			bool    UseItemDisable      :1;     //���i�ϥΪ��~
			bool    SearchEmenyDisable  :1;     //���i����
			bool    Stop                :1;     //���i����

			//Client �ݮĪG��
			bool    Cover               :1;     //����
			bool    DetectCover         :1;     //��������
			bool	Sneak				:1;		//���
			bool	DetectSneak			:1;		//�������
			bool    Blind               :1;     //����(�ù�����)
			bool	HitDown				:1;		//�˦a
			bool	Trace				:1;		//�l��			

			//��L
			bool	PlayDead			:1;	    //�˦�
			bool    Insure              :1;     //�O�I(�覺�@��)
			bool    Chaos               :1;     //�V��
			bool    Fear                :1;     //����

			bool	LockTarget			:1;		//�����ؼЯ��w			
			bool	WeaponIgnore		:1;		//�Z���L�Ĥ�
			bool	ArmorIgnore			:1;		//����L�Ĥ�			
			bool	Ride				:1;		//�M��
			bool	Raise				:1;		//����
			bool	ExpProtect			:1;		//���`�g��Ȥ���

			bool	Client_Dizzy		:1;		//�w�t(Client �欰) 
			bool	Client_Sleep		:1;		//�ίv(Client �欰)
			bool	PKFlag				:1;		//PK���A(���}�Ҫ��H�N�i�HPK)
			bool	TeleportDisable		:1;		//�T��ǰe

			bool	GPS					:1;		//��m�w�쾹�P��
			bool	PKFlag_Disabled		:1;		//PK�T��O
			bool	AI_LowAttackPriority:1;		//�Q��ai����-�u������̧C
			bool	StopOntimeCure		:1;		//����HPMPSP�w�ɦ^�_

			//////////////////////////////////////////////////////////////////////////
			bool	Silence				:1;		//�T���(GM)
			bool	CliOutofContorl		:1;		//Client���i����
			bool	Freeze				:1;		//Client���a�B��
			bool    GoodMagicInvincible :1;     //�n���k�N�L��(�k�N�ޯ�L��)
			bool    GoodPhyInvincible   :1;     //�n�����z�L��(���z�ޯ�P�@������L��)
			bool	Guilty				:1;		//���o
			bool	Critial				:1;		//����P�R�@��
			bool	Hunter				:1;		//�y����
			bool	NoEscape			:1;		//���i�k�]
			bool	DisableJobSkill		:1;		//����ϥέ쥻¾�~�ޯ�
			bool	IgnoreDeadGoodEvil	:1;		//���B�z���`���c��
			bool	ExchangeZoneDamageEvent:1;	//���N�ϰ�ˮ`
			bool	Fly					:1;		//����
			bool	WaterWalk			:1;		//���W�樫
			bool	GravityDisable		:1;		//�ȮɵL���O
			bool    DisableStrikeBack	:1;		//�_�h�L��
			bool	DisableWagon		:1;		//����W����
			bool	IgnoreInstancePlayer:1;		//�����ƥ��H�ƭp��
			bool	TitleSysPowerUp		:1;		//�s�Y�Ψt�ί�O�⭿
			bool	MagicSpell_ZeroTime	:1;		//�Ҧ��k�N ���o
			bool	MagicSpell_Moveable	:1;		//�Ҧ��k�N �i���ʬI�k
			bool	MagicSpell_NoCost	:1;		//�Ҧ��k�N �L����
			bool	DetectPlayDead		:1;		//���d�˦�
			bool	ChangeMotion		:1;		//�ק�ʧ@
			bool	RangeAttackInvincible:1;	//�a���d��k�N�L��
			bool	EqProtect			:1;		//�˳ƭ@�[�פ��|�U��(�˳ƫO�@)

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
			//�@��
			bool    ForceAttachkWeapon     :1;     //�j��Z���j�w�b��W
		};
	};
};
//----------------------------------------------------------------------------------------
//���U�k�N�I�ı���
//----------------------------------------------------------------------------------------
struct  MagicClearTimeStruct
{
	union
	{
		int			_Value;
		struct
		{
			bool    Attack      		:1;    	//��������
			bool    UnderAtk    		:1;    	//�Q��������
			bool    Move        		:1;    	//���ʮ���
			bool    Spell       		:1;    	//�I�k/�Ϊ��z��/�ϥΪ��~����
			bool    ChangeZone  		:1;    	//���Ϯ���
			bool    Logout      		:1;    	//���u����
			bool	Random				:1;	   	//�üƮ��� Max/3 ~ Max
			bool    WarriorSP0  		:1;    	//�ԤhSP��0����
			bool    RangerSP0   		:1;    	//�C�LSP��0����
			bool    RogueSP0    		:1;    	//�s��SP��0����
			bool    HP0					:1;    	//HP��0����
			bool    MP0         		:1;    	//MP��0����
			bool	Spell_MagicAttack	:1;		//�I�����k�N����
			bool	Spell_PhyAttack		:1;		//�I�����ޯ����
			bool	Spell_Cure			:1;		//�I��^�_�]�k����
			bool	TargetOnAttack		:1;		//�ؼЬO�����Ҧ�or�ݪ���ؼ� ��������
			bool	OnStopAttackMode	:1;		//�������
			bool	OnWater				:1;		//��������
			bool	OnNoWater			:1;		//���W����
			bool	Spell_Magic			:1;		//�I��k�N�ޯ����
			bool	Spell_Phy			:1;		//�I�񪫲z�ޯ����
			bool	ChangeJob			:1;		//��¾�~����
			bool	ChangeSuitSkill		:1;		//�����M�˧ޯ�ɮ���
			bool	ChangeEQPhantom		:1;		//�]�F�˳Ƨ���
		};
	};
};
//----------------------------------------------------------------------------------------
//	���~�C�|
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
//�Z���`���C�|
//----------------------------------------------------------------------------------------

enum	GameObjectWeaponENUM
{
	EM_Weapon_None                  = -1,
	EM_Weapon_Unarmed			,// Unarmed�Ť�
	EM_Weapon_Blade             ,// �C
	EM_Weapon_Dagger            ,// �P��
	EM_Weapon_Wand              ,// �v��
	EM_Weapon_Axe               ,// ��
	EM_Weapon_Bludgeon          ,// ��Ҵ�
	EM_Weapon_Claymore          ,// ����C
	EM_Weapon_Staff             ,// ��
	EM_Weapon_2H_Axe            ,// �����
	EM_Weapon_2H_Hammer         ,// ������
	EM_Weapon_Polearm			,// �j(����)
	EM_Weapon_Bow				,// ���{�Z�� �}
	EM_Weapon_CossBow			,// ���{�Z�� �Q�r�}
	EM_Weapon_Gun				,// ���{�Z�� �j
	EM_Weapon_Ammo_Bow			,// �l�u �}
	EM_Weapon_Ammo_Gun			,// �l�u �j
	EM_Weapon_Throw				,// ���Y���Z��
	EM_Weapon_Lumbering			,// ����
	EM_Weapon_Herbalism			,// ����
	EM_Weapon_Mining			,// ���q
	EM_Weapon_Fishing			,// ����

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
	
	EM_Armor_Implement			,	// �������
	EM_Armor_Ornament	        ,	// ���~��

	//�n������
	EM_Armor_Wood				,	//���Y
	EM_Armor_Stone				,	//���Y
	EM_Armor_Iron				,	//�K

	EM_Armor_MaxCount			,	

	EM_GameObjectArmorEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
//�˳Ƨޯ���
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
//�˳Ʀ�m
//----------------------------------------------------------------------------------------
enum GameObjectWeaponPosENUM
{
	EM_WeaponPos_MainHand     ,   //�D��
	EM_WeaponPos_SecondHand   ,   //�Ƥ�
	EM_WeaponPos_OneHand      ,   //���ⳣ�i�H�˳�
	EM_WeaponPos_TwoHand      ,   //���
	EM_WeaponPos_Ammo         ,   //�l�u
	EM_WeaponPos_Bow          ,   //�}
	EM_WeaponPos_Manufacture  ,   //�Ͳ��u��

	EM_GameObjectWeaponPosENUM_FORCE_DWORD   = 0x7fffffff, 
};

enum GameObjectArmorPosENUM
{
	EM_ArmorPos_Head        ,   //�Y
	EM_ArmorPos_Gloves	    ,   //��M
	EM_ArmorPos_Shoes	    ,   //�c�l
	EM_ArmorPos_Clothes	    ,   //�W��
	EM_ArmorPos_Pants	    ,   //�Ǥl
	EM_ArmorPos_Back	    ,   //�I��
	EM_ArmorPos_Belt	    ,   //�y�a
	EM_ArmorPos_Shoulder    ,   //�ӥ�
	EM_ArmorPos_Necklace    ,   //���� 
	EM_ArmorPos_Ring        ,   //�٤l
	EM_ArmorPos_Earring     ,   //�չ�
	EM_ArmorPos_SecondHand  ,   //�Ƥ�
	EM_ArmorPos_MagicTool	,	//�k�_
	EM_ArmorPos_Ornament	,	//�˹��~


	EM_ArmorPos_MaxCount	,	
	EM_GameObjectArmorPosENUM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//�ܩʯP�|
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
//�ܩʵ��c
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
//NPC�ܩʸ�ƪ�
//----------------------------------------------------------------------------------------
struct NpcResistBaseInfoStruct
{
	char				Name[ 32 ];
	MagicResistENUM		Type;
	MagicResistStruct	Resist;
};
//-------------------------------------------------------------------------------------
//		�ޯ൲�c
//-------------------------------------------------------------------------------------
enum	SkillValueTypeENUM
{
	EM_SkillValueType_None				= -1,			
	EM_SkillValueType_Unarmed			= 0 ,// Unarmed�Ť�
	EM_SkillValueType_Blade             ,// �C
	EM_SkillValueType_Dagger            ,// �P��
	EM_SkillValueType_Wand              ,// �v��
	EM_SkillValueType_Axe               ,// ��
	EM_SkillValueType_Bludgeon          ,// ��Ҵ�
	EM_SkillValueType_Claymore          ,// ����C
	EM_SkillValueType_Staff             ,// ��
	EM_SkillValueType_2H_Axe            ,// �����
	EM_SkillValueType_2H_Hammer         ,// ������
	EM_SkillValueType_Polearm			,// �j(����)
	EM_SkillValueType_Bow				,// ���{�Z�� �}
	EM_SkillValueType_CossBow			,// ���{�Z�� �Q�r�}
	EM_SkillValueType_Gun				,// ���{�Z�� �j
	EM_SkillValueType_Define			,// ���m

	EM_SkillValueType_BlackSmith		,// ���K
	EM_SkillValueType_Carpenter			,// ��u
	EM_SkillValueType_MakeArmor			,// �s��
	EM_SkillValueType_Tailor			,// ���_
	EM_SkillValueType_Cook				,// �i��
	EM_SkillValueType_Alchemy			,// �Ҫ�

	EM_SkillValueType_Mining			,// ���q
	EM_SkillValueType_Lumbering			,// ���
	EM_SkillValueType_Herblism			,// ����
	EM_SkillValueType_Fishing			,// ����
	EM_SkillValueType_Plant				,// �ش�
	EM_SkillValueType_CatchPet			,// �ɮ��d��
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
			// �ͬ���
			float BlackSmith , Carpenter , MakeArmor , Tailor , Cook , Alchemy  ;
			// �Ķ��ͬ��ޯ�
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
//	NPC Title ��ܳ]�w�C�|
//----------------------------------------------------------------------------------------
enum NpcTitleTypeENUM
{
	EM_NpcTitleTypeENUM_Nornal			,		//�@��
	EM_NpcTitleTypeENUM_Invisible		,		//�����
	EM_NpcTitleTypeENUM_QuestNPC		,		//���ȫ�npc
	EM_NpcTitleTypeENUM_Neutral			,		//���ߩ�
};

//----------------------------------------------------------------------------------------
//	�k�N���ӦC�|
//----------------------------------------------------------------------------------------
enum MagicSpellCostTypeENUM
{
	EM_MagicSpellCostType_None			,		//�L����
	EM_MagicSpellCostType_HP			,		//���� HP
	EM_MagicSpellCostType_MP			,		//���� MP
	EM_MagicSpellCostType_HP_Per		,		//���� HP�ʤ���
	EM_MagicSpellCostType_MP_Per		,		//���� MP�ʤ���
	EM_MagicSpellCostType_SP_Warrior	,		//���� SP �Ԥh(-1��ܥ���)
	EM_MagicSpellCostType_SP_Ranger		,		//���� SP �C�L(-1��ܥ���)
	EM_MagicSpellCostType_SP_Rogue		,		//���� SP �s��(-1��ܥ���)
	EM_MagicSpellCostType_StomachPoint	,		//���� ������
	EM_MagicSpellCostType_Item			,		//���� ���~
	EM_MagicSpellCostType_Ammo_Gun		,		//���� �l�u
	EM_MagicSpellCostType_Ammo_Bow		,		//���� �}�b��
	EM_MagicSpellCostType_Ammo_CossBow	,		//���� �Q�r�}�b��
	EM_MagicSpellCostType_Ammo_Throw	,		//���� ���Y��
	EM_MagicSpellCostType_Ammo_All		,		//���� �Ҧ������{�u��
	EM_MagicSpellCostType_SoulPoint		,		//���� �F���
};
//----------------------------------------------------------------------------------------
//	�k�N�ݨD�C�|
//----------------------------------------------------------------------------------------
enum MagicSpellNeedTypeENUM
{
	EM_MagicSpellNeedType_None						,	//�L�ݨD
	EM_MagicSpellNeedType_Weapon					,	//�ݨD �ۤv�� �Z��
	EM_MagicSpellNeedType_EQ						,	//�ݨD �ۤv�� �˳�
	EM_MagicSpellNeedType_Suit						,	//�ݨD �ۤv�� �M��
	EM_MagicSpellNeedType_Buf						,	//�ݨD �ۤv�� �k�NBuf
	EM_MagicSpellNeedType_Buf_Target				,	//�ݨD �ؼЦ� �k�NBuf
	EM_MagicSpellNeedType_NoBuf						,	//�ݨD �ۤv�S�� �k�NBuf
	EM_MagicSpellNeedType_NoBuf_Target				,	//�ݨD �ؼШS�� �k�NBuf
	EM_MagicSpellNeedType_WeaponType_Unarmed		,	//�ݨD �ۤv�� �Z������ �Ť�
	EM_MagicSpellNeedType_WeaponType_Blade      	,	//�ݨD �ۤv�� �Z������ ���C
	EM_MagicSpellNeedType_WeaponType_Dagger     	,	//�ݨD �ۤv�� �Z������ �P��
	EM_MagicSpellNeedType_WeaponType_Wand       	,	//�ݨD �ۤv�� �Z������ �v��
	EM_MagicSpellNeedType_WeaponType_Axe        	,	//�ݨD �ۤv�� �Z������ ����
	EM_MagicSpellNeedType_WeaponType_Bludgeon   	,	//�ݨD �ۤv�� �Z������ ��Ҵ�
	EM_MagicSpellNeedType_WeaponType_Claymore   	,	//�ݨD �ۤv�� �Z������ ����C
	EM_MagicSpellNeedType_WeaponType_Staff      	,	//�ݨD �ۤv�� �Z������ ��
	EM_MagicSpellNeedType_WeaponType_2H_Axe     	,	//�ݨD �ۤv�� �Z������ �����
	EM_MagicSpellNeedType_WeaponType_2H_Hammer  	,	//�ݨD �ۤv�� �Z������ ������
	EM_MagicSpellNeedType_WeaponType_Polearm		,	//�ݨD �ۤv�� �Z������ �j(����)
	EM_MagicSpellNeedType_WeaponType_SwordType  	,	//�ݨD �ۤv�� �Z������ �C��(������)
	EM_MagicSpellNeedType_WeaponType_AxeType    	,	//�ݨD �ۤv�� �Z������ ����(������)
	EM_MagicSpellNeedType_WeaponType_Shield			,	//�ݨD �ۤv�� �Z������ ��
	EM_MagicSpellNeedType_Distance					,	//�ݨD �Z���ؼ�
	EM_MagicSpellNeedType_NotAttak					,	//�ݨD �ۤv�D�԰�
	EM_MagicSpellNeedType_Attack					,	//�ݨD �ۤv�԰�
	EM_MagicSpellNeedType_Critical					,	//�ݨD �ۤv�z��
	EM_MagicSpellNeedType_BeCritical				,	//�ݨD �ۤv�Q�z��
	EM_MagicSpellNeedType_Dodge						,	//�ݨD �ۤv�{��
	EM_MagicSpellNeedType_BeDodge					,	//�ݨD �ۤv�Q�{��
	EM_MagicSpellNeedType_Miss						,	//�ݨD �ۤvMiss
	EM_MagicSpellNeedType_Parry						,	//�ݨD �ۤv���
	EM_MagicSpellNeedType_BeParry					,	//�ݨD �ۤv�Q���
	EM_MagicSpellNeedType_NotAttack_Target			,	//�ݨD �ؼЫD�԰�
	EM_MagicSpellNeedType_Attack_Target				,	//�ݨD �ؼо԰�	
	EM_MagicSpellNeedType_SelfHp_Smaller_Percent	,	//�ݨD HP�ʤ���p��
	EM_MagicSpellNeedType_SelfHp_Greater_Percent	,	//�ݨD HP�ʤ���j��
	EM_MagicSpellNeedType_Self_Job					,	//�ݨD ¾�~
	EM_MagicSpellNeedType_WeaponType_LongDistWeapon	,	//�ݨD �ۤv�� �Z������ ���Z���Z��
	EM_MagicSpellNeedType_WeaponType_2H_Weapon		,	//�ݨD �ۤv�� �Z������ ����Z��
	EM_MagicSpellNeedType_WeaponType_Hammer			,	//�ݨD �ۤv�� �Z������ ����(������)
	EM_MagicSpellNeedType_BuffGroup					,	//�ݨD �ۤv�֦��Y Buff Group
	EM_MagicSpellNeedType_ShieldBlock				,	//�ݨD �ۤv�޾�
	EM_MagicSpellNeedType_BeShieldBlock				,	//�ݨD �ۤv�Q�޾�
	EM_MagicSpellNeedType_WeaponType_1H_Weapon		,	//�ݨD �ۤv�� �Z������ ���Z��
	EM_MagicSpellNeedType_NoBuffGroup				,	//�ݨD �ۤv�S���Y Buff Group
	EM_MagicSpellNeedType_TargetBuffGroup			,	//�ݨD �ؼо֦��Y Buff Group
	EM_MagicSpellNeedType_TargetNoBuffGroup			,	//�ݨD �ؼШS���Y Buff Group
	EM_MagicSpellNeedType_MagicCritical				,	//�ݨD �ۤv�z��
	EM_MagicSpellNeedType_BeMagicCritical			,	//�ݨD �ۤv�Q�z��
	EM_MagicSpellNeedType_Self_MainJob				,	//�ݨD �D¾�~
	EM_MagicSpellNeedType_Self_SoulPoint			,	//�ݨD �F���

};
//----------------------------------------------------------------------------------------
//��L�k�N�]�w
//----------------------------------------------------------------------------------------
struct	MagicSpellFlagStruct
{
	union
	{
		int _Type;
		struct
		{
			bool	GoodMagic					: 1;	//�n���k�N
			bool    ShowBuf			    		: 1;	//���Buf
			bool	ContinueMagic				: 1;	//�s�򲣥ͪk�N
			bool	DotMagic					: 1;	//DOT�k�N
			bool	FaceOffMagic				: 1;	//�ܨ��N 			
			bool	CancelBuff					: 1;	//�i����
			bool	ShowBuffTime				: 1;	//Client�����Buff�ɶ�
			bool	SpecialMagic				: 1;	//���ͯS��k�N
			bool	MagicShield					: 1;	//�]�k��
			bool	DeadNotClear				: 1;	//���`���M��
			bool	OfflineBuffTime				: 1;	//�U�uBuff�ɶ��p��
			bool	OnPlayerAttackAddTime		: 1;	//�������a�W�[buff�ɶ�
			bool	OnKillAddTime				: 1;	//��������W�[buff�ɶ�
			bool	SelfBuff					: 1;	//�p�HBuf,���|�P��L�H��Buf����
			bool	FaceOffMagic_ShowEq			: 1;	//�ܨ�����ܭ쥻�˳ƪZ��
			bool	ShowPowerLv					: 1;	//���PowerLv
			bool	DotMagicNoKill				: 1;	//Dot�k�N�������H
			bool	BuffSkill					: 1;	//Buff�֦��ޯ�
			bool	MaxMagicLvEquRoleLv			: 1;	//Buff�̰����ų̦h�P���a����
			bool	DisableShowMagicInfo		: 1;	//Client �ݤ���ܥ[��媺��V
			bool	FixDotPower					: 1;	//Dot���p��˳Ư�O(����𨾤�)
			bool	RideCanAttack				: 1;	//�������|�U��
			bool	RidePetAttack				: 1;	//�M���d���������ʧ@
			bool	CancelBadMagic				: 1;	//�M���ؼЬO�ۤv���a���k�N
			bool	NpcEndFight_NotClearBuff	: 1;	//�԰��������|������Buff
			bool	Dual_NoClearBuff			: 1;	//��յ������M����buff
			bool	IgnoreSpellCureMagicClear	: 1;	//�����I�i�v������
			bool	IgnoreSpellAttackMagicClear	: 1;	//�����I�i��������
			bool	IgnoreBuffMessage			: 1;	//�����I�i��������(client ���㹳�� )
			bool	OnlyYouCanSee				: 1;	//�u���ۤv�ݪ���S��
			bool	NoEffect					: 1;	//(Client ��ܳB�z��)
			bool	forceDisplayEffect			: 1;	//�j����ܯS��
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
			bool		IgnoreMagicAbsorb		: 1;		//�����]�k�l��
			bool		IsDepartmentStore		: 1;		//�ӫ�buff
		};
	};
};

//----------------------------------------------------------------------------------------
//	�Z������Ϊk�N�|�ק缾�a��O�����c
//----------------------------------------------------------------------------------------
enum WearEqTypeENUM
{
	EM_WearEqType_None          			,   // "�L�ĪG",
	EM_WearEqType_Durable       			,   // "�@�[��",
	EM_WearEqType_STR           			,   // "�ݩ� STR �O�q",
	EM_WearEqType_STA           			,	// "�ݩ� STA �@�O",			
	EM_WearEqType_INT           			,	// "�ݩ� INT ���O",			
	EM_WearEqType_MND           			,	// "�ݩ� MND �F�O",
	EM_WearEqType_AGI           			,	// "�ݩ� AGI �ӱ�",			
	EM_WearEqType_AllState      			,   // "�ݩ� �Ҧ�(�򥻤����ݩ�)",
	EM_WearEqType_MaxHP         			,	// "�W�� HP",
	EM_WearEqType_MaxMP		    			,	// "�W�� MP",
	EM_WearEqType_ReHP		    			,	// "�^�_�v HP",
	EM_WearEqType_ReMP		    			,	// "�^�_�v MP",
	EM_WearEqType_ATK		    			,	// "ATK �����O",
	EM_WearEqType_DEF		    			,	// "DEF ���m�O",
	EM_WearEqType_MDEF   	    			,	// "MDEF �]�k���m",
	EM_WearEqType_MATK	        			,	// "MATK �]�k����",
	EM_WearEqType_HitPoint	    			,	// "�R��",
	EM_WearEqType_DodgePoint	   			,	// "�j��",
	EM_WearEqType_CritRate	    			,   // "��������",
	EM_WearEqType_CritPower	    			,   // "�����¤O�[�j(%)",
	EM_WearEqType_MagicCritRate	    		,   // "�k�N��������",
	EM_WearEqType_MagicCritPower	    	,   // "�k�N�����¤O�[�j(%)",
	EM_WearEqType_ParryRate     			,   // "��׵���",
	EM_WearEqType_AtkSpeed	    			,   // "�����t��(%)",
	EM_WearEqType_MoveSpeed	    			,	// "���ʳt��(%)",
	EM_WearEqType_DMG           			,   // "�Z���¤O �Ҧ���ԩλ��{ ( DMG )",
	EM_WearEqType_AllResist     			,   // "�ܩ� �Ҧ�",
	EM_WearEqType_Resist_Earth  			,   // "�ܩ� �a",
	EM_WearEqType_Resist_Water  			,   // "�ܩ� ��",
	EM_WearEqType_Resist_Fire   			,   // "�ܩ� ��",
	EM_WearEqType_Resist_Wind   			,   // "�ܩ� ��",
	EM_WearEqType_Resist_Light  			,   // "�ܩ� ��",
	EM_WearEqType_Resist_Darkness			,   // "�ܩ� ��",
	EM_WearEqType_ManaDecrease				,	// "MP���Ӵ��(%)",
	EM_WearEqType_Exp						,	// "�g���",
	EM_WearEqType_Treasure					,	// "���_�v",
	EM_WearEqType_SecHand_HitRate			,	// "�Ƥ� �R���v",
	EM_WearEqType_SecHand_DMG_Per			,	// "�Ƥ� �ˮ`�O(DMG%)",
	EM_WearEqType_DEF_HeavyArmed			,	// "���m�[�j �Z��(%)",
	EM_WearEqType_DEF_LightArmed			,	// "���m�[�j ���(%)",
	EM_WearEqType_DEF_Leather				,	// "���m�[�j �֥�(%)",
	EM_WearEqType_DEF_Clothes	    		,	// "���m�[�j ��A(%)",
	EM_WearEqType_DEF_Robe					,	// "���m�[�j ���T(%)",
	EM_WearEqType_DEF_Shield				,	// "���m�[�j ��(%)",
	EM_WearEqType_MagicPow_AllMagic 		, 	// "�]�k�¤O �Ҧ�(%)",
	EM_WearEqType_MagicPow_Earth  			, 	// "�]�k�¤O �a(%)",
	EM_WearEqType_MagicPow_Water  			, 	// "�]�k�¤O ��(%)",
	EM_WearEqType_MagicPow_Fire   			, 	// "�]�k�¤O ��(%)",
	EM_WearEqType_MagicPow_Wind   			, 	// "�]�k�¤O ��(%)",
	EM_WearEqType_MagicPow_Light  			, 	// "�]�k�¤O ��(%)",
	EM_WearEqType_MagicPow_Darkness			,	// "�]�k�¤O ��(%)",
	EM_WearEqType_SpellSpeed_AllMagic		, 	// "�I�k�t�� �Ҧ�(%)",
	EM_WearEqType_DMG_AllRange				,	// "���{�Z���¤O(%) �Ҧ�",
	EM_WearEqType_DMG_Bow					,	// "���{�Z���¤O(%) �}",
	EM_WearEqType_DMG_Cossbow				,	// "���{�Z���¤O(%) �Q�r�}",
	EM_WearEqType_DMG_Gun					,	// "���{�Z���¤O(%) �j",
	EM_WearEqType_DMG_AllWeapon				,	// "��ԪZ���¤O(%) �Ҧ�",
	EM_WearEqType_DMG_Unarmed				,	// "��ԪZ���¤O(%) �Ť�",
	EM_WearEqType_DMG_Blade     			,	// "��ԪZ���¤O(%) �C",
	EM_WearEqType_DMG_Dagger    			,	// "��ԪZ���¤O(%) �P��",
	EM_WearEqType_DMG_Wand      			,	// "��ԪZ���¤O(%) �v��",
	EM_WearEqType_DMG_Axe       			,	// "��ԪZ���¤O(%) ��",
	EM_WearEqType_DMG_Bludgeon  			,	// "��ԪZ���¤O(%) ��Ҵ�",
	EM_WearEqType_DMG_Claymore  			,	// "��ԪZ���¤O(%) ����C",
	EM_WearEqType_DMG_Staff     			,	// "��ԪZ���¤O(%) ��",
	EM_WearEqType_DMG_2H_Axe    			,	// "��ԪZ���¤O(%) �����",
	EM_WearEqType_DMG_2H_Hammer 			,	// "��ԪZ���¤O(%) ������",
	EM_WearEqType_DMG_Polearm				,	// "��ԪZ���¤O(%) �j(����)",
	EM_WearEqType_AttackSpeed_AllRange		,	// "���{�Z���t��(%) �Ҧ�",
	EM_WearEqType_AttackSpeed_Bow			,	// "���{�Z���t��(%) �}",
	EM_WearEqType_AttackSpeed_Cossbow		,	// "���{�Z���t��(%) �Q�r�}",
	EM_WearEqType_AttackSpeed_Gun			,	// "���{�Z���t��(%) �j", 
	EM_WearEqType_AttackSpeed_AllWeapon		,	// "��ԪZ���t��(%) �Ҧ�",
	EM_WearEqType_AttackSpeed_Unarmed		,	// "��ԪZ���t��(%) �Ť�",
	EM_WearEqType_AttackSpeed_Blade     	,	// "��ԪZ���t��(%) �C",
	EM_WearEqType_AttackSpeed_Dagger    	,	// "��ԪZ���t��(%) �P��",
	EM_WearEqType_AttackSpeed_Wand      	,	// "��ԪZ���t��(%) �v��",
	EM_WearEqType_AttackSpeed_Axe       	,	// "��ԪZ���t��(%) ��",
	EM_WearEqType_AttackSpeed_Bludgeon  	,	// "��ԪZ���t��(%) ��Ҵ�",
	EM_WearEqType_AttackSpeed_Claymore  	,	// "��ԪZ���t��(%) ����C",
	EM_WearEqType_AttackSpeed_Staff     	,	// "��ԪZ���t��(%) ��",
	EM_WearEqType_AttackSpeed_2H_Axe    	,	// "��ԪZ���t��(%) �����",
	EM_WearEqType_AttackSpeed_2H_Hammer 	,	// "��ԪZ���t��(%) ������",
	EM_WearEqType_AttackSpeed_Polearm		,	// "��ԪZ���t��(%) �j(����)",
	EM_WearEqType_WearEqAbility_Unarmed 	,	// "�˳Ư�O �Ť�",
	EM_WearEqType_WearEqAbility_Blade   	,	// "�˳Ư�O �C",	  	  	
	EM_WearEqType_WearEqAbility_Dagger  	,	// "�˳Ư�O �P��",
	EM_WearEqType_WearEqAbility_Wand    	,	// "�˳Ư�O �v��",  	
	EM_WearEqType_WearEqAbility_Axe     	,	// "�˳Ư�O ��",	  	
	EM_WearEqType_WearEqAbility_Bludgeon	,	// "�˳Ư�O ��Ҵ�",
	EM_WearEqType_WearEqAbility_Claymore	,	// "�˳Ư�O ����C",
	EM_WearEqType_WearEqAbility_Staff   	,	// "�˳Ư�O ��",
	EM_WearEqType_WearEqAbility_Axe_2H  	,	// "�˳Ư�O �����",
	EM_WearEqType_WearEqAbility_Hammer_2H	,	// "�˳Ư�O ������",
	EM_WearEqType_WearEqAbility_Polearm		,	// "�˳Ư�O �j(����)",
	EM_WearEqType_WearEqAbility_Bow			,	// "�˳Ư�O �}",
	EM_WearEqType_WearEqAbility_CossBow		,	// "�˳Ư�O �Q�r�}",
	EM_WearEqType_WearEqAbility_Gun			,	// "�˳Ư�O �j",
	EM_WearEqType_WearEqAbility_Throw		,	// "�˳Ư�O ���Y",
	EM_WearEqType_WearEqAbility_HeavyArmed	,	// "�˳Ư�O �Z��",
	EM_WearEqType_WearEqAbility_LightArmed	,	// "�˳Ư�O ���",
	EM_WearEqType_WearEqAbility_Leather		,	// "�˳Ư�O �֥�",
	EM_WearEqType_WearEqAbility_Clothes	    ,	// "�˳Ư�O ��A",
	EM_WearEqType_WearEqAbility_Robe		,	// "�˳Ư�O ���T",
	EM_WearEqType_WearEqAbility_Shield		,	// "�˳Ư�O ��",
	EM_WearEqType_WearEqAbility_Implement	,	// "�˳Ư�O ����k��",
	EM_WearEqType_WearEqAbility_SecondHand	,	// "�˳Ư�O �����",
	EM_WearEqType_SkillValue_Unarmed		,	// "�ޯ�W�� Unarmed�Ť�",
	EM_WearEqType_SkillValue_Blade          ,	// "�ޯ�W�� �C",
	EM_WearEqType_SkillValue_Dagger         ,	// "�ޯ�W�� �P��",
	EM_WearEqType_SkillValue_Wand           ,	// "�ޯ�W�� �v��",
	EM_WearEqType_SkillValue_Axe            ,	// "�ޯ�W�� ��",
	EM_WearEqType_SkillValue_Bludgeon       ,	// "�ޯ�W�� ��Ҵ�",
	EM_WearEqType_SkillValue_Claymore       ,	// "�ޯ�W�� ����C",
	EM_WearEqType_SkillValue_Staff          ,	// "�ޯ�W�� ��",
	EM_WearEqType_SkillValue_2H_Axe         ,	// "�ޯ�W�� �����",
	EM_WearEqType_SkillValue_2H_Hammer      ,	// "�ޯ�W�� ������",
	EM_WearEqType_SkillValue_Polearm		,	// "�ޯ�W�� �j(����)",
	EM_WearEqType_SkillValue_Bow			,	// "�ޯ�W�� ���{�Z�� �}",
	EM_WearEqType_SkillValue_CossBow		,	// "�ޯ�W�� ���{�Z�� �Q�r�}",
	EM_WearEqType_SkillValue_Gun			,	// "�ޯ�W�� ���{�Z�� �j",
	EM_WearEqType_SkillValue_Define			,	// "�ޯ�W�� ���m",
	EM_WearEqType_SkillValue_BlackSmith		,	// "�ޯ�W�� ���K",
	EM_WearEqType_SkillValue_Carpenter		,	// "�ޯ�W�� ��u",
	EM_WearEqType_SkillValue_MakeArmor		,	// "�ޯ�W�� �s��",
	EM_WearEqType_SkillValue_Tailor			,	// "�ޯ�W�� ���_",
	EM_WearEqType_SkillValue_Cook			,	// "�ޯ�W�� �i��",
	EM_WearEqType_SkillValue_Alchemy		,	// "�ޯ�W�� �Ҫ�",
	EM_WearEqType_HQ_BlackSmith				,	// "HQ�~���v�W�� ���K(%)",
	EM_WearEqType_HQ_Carpenter				,	// "HQ�~���v�W�ɤW�� ��u(%)",
	EM_WearEqType_HQ_MakeArmor				,	// "HQ�~���v�W�ɤW�� �s��(%)",
	EM_WearEqType_HQ_Tailor					,	// "HQ�~���v�W�ɤW�� ���_(%)",
	EM_WearEqType_HQ_Cook					,	// "HQ�~���v�W�ɤW�� �i��(%)",
	EM_WearEqType_HQ_Alchemy				,	// "HQ�~���v�W�ɤW�� �Ҫ�(%)",	
	EM_WearEqType_ATK_Per	    			,	// "ATK �����O (%)",
	EM_WearEqType_DEF_Per	    			,	// "DEF ���m�O (%)",
	EM_WearEqType_StealRate	    			,	// "���Ѧ��\�v (%)",
	EM_WearEqType_DropMoneyRate	    		,	// "���������v (%)",
	EM_WearEqType_HateRate		    		,	// "����׼W�[ (%)",
	EM_WearEqType_ReSP_Per_Warrior			,	// "�ԤhSP �^�_�[�ʤ���",
	EM_WearEqType_ReSP_Per_Ranger			,	// "�C�LSP �^�_�[�ʤ���",
	EM_WearEqType_ReSP_Per_Rogue			,	// "�s��SP �^�_�[�ʤ���",
	EM_WearEqType_MAbsorbRate    			,	// "�]�k�l���v",
	EM_WearEqType_AbsorbRate    			,	// "���m�l���v",
	EM_WearEqType_HealAbsorbRate	  		,	// "�v���l���v",
	EM_WearEqType_MAbsorb	    			,	// "�]�k�l���I��",
	EM_WearEqType_Absorb	    			,	// "���m�l���I��",
	EM_WearEqType_HealAbsorb				,	// "�v���l���I��",
	EM_WearEqType_MDmgPoint        			,   // "�]�k�ˮ`�[�I",
	EM_WearEqType_HealPowerRate	  			,	// "�v���¤O�W�[�v",
	EM_WearEqType_HealPoint		  			,	// "�v���¤O�W�[�I��",
	EM_WearEqType_RangeAttackRange			,	// "���{�Z�������Z���W�[",

	EM_WearEqType_SkillValue_Lumbering		,	// "�ޯ�W�� ����",
	EM_WearEqType_SkillValue_Herbalism		,	// "�ޯ�W�� ����",
	EM_WearEqType_SkillValue_Mining			,	// "�ޯ�W�� ���q",
	EM_WearEqType_SkillValue_Fishing		,	// "�ޯ�W�� ����",

	EM_WearEqType_HQ_Lumbering				,	// "HQ�~���v�W�� ����",
	EM_WearEqType_HQ_Herbalism				,	// "HQ�~���v�W�� ����",
	EM_WearEqType_HQ_Mining					,	// "HQ�~���v�W�� ���q",
	EM_WearEqType_HQ_Fishing				,	// "HQ�~���v�W�� ����",

	EM_WearEqType_SkillValue_GatherRate		,	// "�Ķ����\�v",

	EM_WearEqType_STR_Rate         			,   // "�ݩ� STR �O�q(%)",
	EM_WearEqType_STA_Rate         			,	// "�ݩ� STA �@�O(%)",			
	EM_WearEqType_INT_Rate           		,	// "�ݩ� INT ���O(%)",			
	EM_WearEqType_MND_Rate           		,	// "�ݩ� MND �F�O(%)",
	EM_WearEqType_AGI_Rate           		,	// "�ݩ� AGI �ӱ�(%)",			
	EM_WearEqType_AllState_Rate      		,   // "�ݩ� �Ҧ�(%)(�򥻤����ݩ�)",
	EM_WearEqType_MaxHP_Rate         		,	// "�W�� HP(%)",
	EM_WearEqType_MaxMP_Rate		    	,	// "�W�� MP(%)",
	EM_WearEqType_RideSpeed			    	,	// "�M���t��(%)",
	EM_WearEqType_MDEF_Rate	    			,	// "MDEF(%) �]�k���m",
	EM_WearEqType_MATK_Rate        			,	// "MATK(%) �]�k����",
	EM_WearEqType_ShieldBlockRate     		,   // "�޾׵���",
	EM_WearEqType_DMG_Per          			,   // "�Z���¤O �Ҧ���ԩλ��{ ( DMG% )",
	EM_WearEqType_Exp_SubJob				,	// "��¾�g���"
	EM_WearEqType_TP_Rate					,	// "TP�g���"

	EM_WearEqType_SkillValue_LumberingRate	,	// "���즨�\�v",
	EM_WearEqType_SkillValue_HerbalismRate	,	// "���Ħ��\�v",
	EM_WearEqType_SkillValue_MiningRate		,	// "���q���\�v",
	EM_WearEqType_SkillValue_FishingRate	,	// "�������\�v",
	EM_WearEqType_Gravity					,	// "���O�ץ�"  ,

	EM_WearEqType_DoubleAttack				,	// "�⦸����" ,

	EM_WearEqType_ResistCritRate	    	,   // "�ܼɵ���",
	EM_WearEqType_ResistMagicCritRate		,   // "�����]�k�P�R�@���v",

	//�T�w�k�N�ĪG
	EM_WearEqType_Magic_EarthPower			,	// "�a�ݩʧ���" ,
	EM_WearEqType_Magic_WaterhPower			,	// "���ݩʧ���" ,
	EM_WearEqType_Magic_FirePower			,	// "���ݩʧ���" ,
	EM_WearEqType_Magic_WindhPower			,	// "���ݩʧ���" ,
	EM_WearEqType_Magic_LightPower			,	// "���ݩʧ���" ,
	EM_WearEqType_Magic_DarkPower			,	// "�t�ݩʧ���" ,

	EM_WearEqType_JumpRate					,	// "���D��v"   ,
	EM_WearEqType_MDMG           			,   // "�]�k�ܮ`�I��"	,
	EM_WearEqType_MDMG_Per           		,   // "�]�k�ܮ`��v"	,

	EM_WearEqType_ResistShieldBlock	    	,   // "������",
	EM_WearEqType_ResistParry				,   // "�����",

	EM_WearEqType_MagicHitPoint				,   // "�]�k�R��",
	EM_WearEqType_MagicDodgePoint			,   // "�]�k�{��",

	EM_WearEqType_PhyHitRate				,   // "���z�R���v",
	EM_WearEqType_PhyDodgeRate				,   // "���z�{�ײv",
	EM_WearEqType_MagicHitRate				,   // "�]�k�R���v",
	EM_WearEqType_MagicDodgeRate			,   // "�]�k�{�ײv",

	EM_WearEqType_GatherGenerateRate		,   // "�Ķ����X�q�W�[�v",
	EM_WearEqType_GatherSpeedRate			,   // "�Ķ��t�׼W�[�v",
	EM_WearEqType_GatherExpRate				,   // "�Ķ��g��ȼW�[�v",

	EM_WearEqType_AttackPlayerPowerRate		,   // "(��)�������a(or���a�d��)�¤O�[��",
	EM_WearEqType_AttackNPCPowerRate		,   // "(��)����NPC�¤O�[��",
	EM_WearEqType_PlayerDefRate				,   // "(�u)�Q���a(or���a�d��)�����¤O�[��",
	EM_WearEqType_NPCDefRate				,   // "(�u)�QNPC�����¤O�[��",
	EM_WearEqType_AEMagicPowerRate			,   // "(��)AE�k�N�����¤O�[��",
	EM_WearEqType_AEMagicDefRate			,   // "(�u)�QAC�k�N�����¤O�[��",

	EM_WearEqType_CraftSpeedRate			,	// "�Ͳ��t�׼W�[�v"
	EM_WearEqType_CraftExpRate				,	// "�Ͳ��g��ȼW�[�v"
	EM_WearEqType_AddPlotExpRate			,	// "�W�[�@���������g��Ȳv"
	EM_WearEqType_AddPlotTPRate				,	// "�W�[�@��������TP�v"

	EM_WearEqType_SP_Warrior_Consume		,	// "�ԷN���Ӵ��(%)"
	EM_WearEqType_SP_Rogue_Consume			,	// "��O���Ӵ��(%)"
	EM_WearEqType_SP_Ranger_Consume			,	// "�M�`���Ӵ��(%)"

	EM_WearEqType_NPC_EXP_Rate				,	// "NPC �g��ȭץ�(%)"
	EM_WearEqType_NPC_TP_Rate				,	// "NPC TP�g��ȭץ�(%)"
	EM_WearEqType_AttackRange				,	// "��{�Z�������Z���W�[",

	EM_WearEqType_AllResist_Per    			,   // "�ܩ� �Ҧ�%",
	EM_WearEqType_Resist_Earth_Per  		,   // "�ܩ� �a%",
	EM_WearEqType_Resist_Water_Per  		,   // "�ܩ� ��%",
	EM_WearEqType_Resist_Fire_Per   		,   // "�ܩ� ��%",
	EM_WearEqType_Resist_Wind_Per   		,   // "�ܩ� ��%",
	EM_WearEqType_Resist_Light_Per			,   // "�ܩ� ��%",
	EM_WearEqType_Resist_Darkness_Per		,   // "�ܩ� ��%",

	EM_WearEqType_ParryRate_Per				,	// "���%"
	EM_WearEqType_Daily_EXP_Rate			,	// "�C����ȸg��ȥ[��"
	EM_WearEqType_Daily_TP_Rate				,	// "�C�����TP�[��"

	EM_WearEqType_MaxCount					,	
};	  

#define Max_WearEqType_Count   10   //�̦h���X���ݩʥi�[
struct  GameObjectWearEqStruct
{
	WearEqTypeENUM  EqType[ Max_WearEqType_Count ];
	int             EqTypeValue[ Max_WearEqType_Count ];

	int				OnAttackMagicRate;		//�o�;��v
	int				OnAttackMagicRank;		//���\����
	int				OnAttackMagicID;		//�k�N���X
};
//----------------------------------------------------------------------------------------
//���~���������c
//----------------------------------------------------------------------------------------
struct ItemDropStruct
{
	int		OrgID;					//���~���X
	int		Rate;					//�������v
};
//----------------------------------------------------------------------------------------
//�ݩ�Player���򥻸��
//----------------------------------------------------------------------------------------
struct GameObjectPlayerStruct
{
	int     None;
};
//----------------------------------------------------------------------------------------
//BodyObj���N�������C�|
//----------------------------------------------------------------------------------------
enum BodyObjectTypeENUM
{
	EM_BodyObjectType_Hair		= 0,
	EM_BodyObjectType_Face		,
};

//----------------------------------------------------------------------------------------
//�ݩ�BodyObj���򥻸��
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
// Quest  �ԲӤ��e�����, �y�z�F Quest �}�Y / �L�{ / ���y
//----------------------------------------------------------------------------------------
struct GameObjectQuestDetail
{
	// �P�_����
	// �Χ@ Client �P�_ User �O�_�i�H�� Quest ( �]�ΰ��b Client�Τp�a�ϤW��� )
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
	
	int		iCheck_RepGroup;	// �i�����Ȫ��n��s��
	int		iCheck_Rep;			// �n��n�D


	int		iCheck_ObjID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iCheck_ObjVal		[ _MAX_SIZE_QUEST_ITEM		];
	int		iCheck_Loop;


	// ���Ȼ���
	//---------------------------------------------------------
	int		iQuestID;
	char*	szQuest_Name;
	char*	szQuest_Desc;

	char*	szQuest_Accept_Detail;
	char*	szQuest_UnComplete_Detail;
	char*	szQuest_Complete_Detail;

	int		iQuest_Catalog;
	int		iQuest_Type;

	// �������ȫ�Ҹm�����A�ε��������~
	//--------------------------------------------------------
	int		iAccept_FlagOn		[ _MAX_SIZE_QUEST_FLAG		];
	int		iAccept_FlagOff		[ _MAX_SIZE_QUEST_FLAG		];
	int		iAccept_ItemID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iAccept_ItemVal		[ _MAX_SIZE_QUEST_ITEM		];

	// �������ȩҶ��n������
	//--------------------------------------------------------
	int		iRequest_ItemID		[ _MAX_SIZE_QUEST_CONDITION ];
	int		iRequest_ItemVal	[ _MAX_SIZE_QUEST_CONDITION	];
	int		iRequest_KillID		[ _MAX_SIZE_QUEST_ITEM		];
	int		iRequest_KillVal	[ _MAX_SIZE_QUEST_ITEM		];
	int		iRequest_Timer;
	int		iRequest_Money;
	int		iRequest_QuestID;

	// �������ȫ�i����Ȯ�, ��S�w�ؼаʧ@, �Ҳ��ͪ��v�T
	//--------------------------------------------------------
	int		iProcess_ClickToGetItem_ObjID		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_ProcPercent	[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_GetItem		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_ClickToGetItem_GetItemVal	[ _MAX_SIZE_QUEST_CONDITION		];

	int		iProcess_KilltoGetItem_ObjID		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_ProcPercent	[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_GetItem		[ _MAX_SIZE_QUEST_CONDITION		];
	int		iProcess_KilltoGetItem_GetItemVal	[ _MAX_SIZE_QUEST_CONDITION		];

	// �������ȫ�, �ұ���������
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

	// �������ȫ�, �ҳ]�w�����A
	//--------------------------------------------------------
	int		iComplete_ShowQuest;
	int		iComplete_FlagOn	[ _MAX_SIZE_QUEST_FLAG		];
	int		iComplete_FlagOff	[ _MAX_SIZE_QUEST_FLAG		];

	// �������ȫ�, �ҳ]�w�����A
	//--------------------------------------------------------
	char	szScript_OnBegin		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnAccept		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnComplete		[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnClickObjBegin[ _MAX_SIZE64_QUEST_SCRIPT ];
	char	szScript_OnClickObjEnd	[ _MAX_SIZE64_QUEST_SCRIPT ];

	// �C�魭�����
	//--------------------------------------------------------
	int		iQuestGroup;			// ���ȸs�խ��� 0 ��������s�� 1-20 ���s��
	int		iControlType;			// ���Ы����ȧ����ɶ�������	0 ������ 1 ���C�駹���@�� 2 ���C�P�����@��

	int		iRequest_ItemStr		[ _MAX_SIZE_QUEST_CONDITION ];
	int		iRequest_KillStr		[ _MAX_SIZE_QUEST_ITEM		];
	int		iQuestGroupLV;			// �C����ȵ��ŻݨD
	int		iReward_Honor;
	int		iReward_TP;				// ���� TP ����� ( �w�]�O 10% )

	int		iQuestProvider			[5];
	int		iDeleteQuestItem		[5];
	int		iDeleteQuestItemCount	[5];
	int		iRequestCompleteNPCID	[3];		// �ĤG�ի��w���� NPC
	int		iQuestLinkNPC			[5];

	char	szScript_OnDelete		[ _MAX_SIZE64_QUEST_SCRIPT ];	// �����ȩҶ]���@�� ( SERVER SIDE )
	int		iCheck_ObjStatus		[ _MAX_SIZE_QUEST_ITEM		];	// �ˬd������n�D�Ϊ̬O�T��

	bool	bDisableTeam;			// �����ζ��������ȩǳ]�w

	char	szScript_RequestString	[ _MAX_SIZE64_QUEST_SCRIPT ];

	PriceTypeENUM	iReward_CoinType;		//�S���������
	int				iReward_SpecialCoin;	//�S�����

	PriceTypeENUM	iRequest_CoinType;		//�S���������
	int				iRequest_SpecialCoin;	//�S�����

};
//----------------------------------------------------------------------------------------
// ���U�k�N����
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
//NPC�I�k�����c
//----------------------------------------------------------------------------------------
#define	_MAX_NPC_SPELL_MAGIC_COUNT_	8
#define	_MAX_NPC_STEAL_ITEM_COUNT_	3
#define	_MAX_NPC_AVOID_MAGIC_TYPE_COUNT_	5
//�I�k�ɾ�
enum NPCSpellRightTimeENUM
{
	EM_NPCSpellRightTime_None			,//�L
	EM_NPCSpellRightTime_Normal			,//�@�몬�A   (60��)
	EM_NPCSpellRightTime_OnAttack		,//�԰��Ұ�
	EM_NPCSpellRightTime_Attack			,//�԰����A   (1��)
	EM_NPCSpellRightTime_AttackHPHalf	,//�԰�HP1/2  (1��)
	EM_NPCSpellRightTime_AttackHPQuarter,//�԰�HP1/4  (1��)
	EM_NPCSpellRightTime_FriendDead		,//�ͤ覺�`   (1��)
	EM_NPCSpellRightTime_KeepDistance	,//�O���Z��   (1��)

};
//NPC�I�k�ؼ�
enum NPCSpellTargetENUM
{
	EM_NPCSpellTarget_Self				,//�ۤv
	EM_NPCSpellTarget_Target			,//�ؼ�
	EM_NPCSpellTarget_Target_HP_Half	,//�ؼ�(HP 1/2)
	EM_NPCSpellTarget_Target_HP_Quarter	,//�ؼ�(HP 1/4)
	EM_NPCSpellTarget_Target_Distance_30_,//�ؼ�(�Z��30�H�W )
	EM_NPCSpellTarget_Target_Escape		,//�ؼ�(�k�])

	EM_NPCSpellTarget_Friend			,//�ͤ�
	EM_NPCSpellTarget_Friend_HP_Half	,//�ͤ�(HP 1/2)
	EM_NPCSpellTarget_Friend_HP_Quarter	,//�ͤ�(HP 1/4)
	EM_NPCSpellTarget_Enemy				,//�Ĥ�
	EM_NPCSpellTarget_Enemy_HP_Half		,//�Ĥ�(HP 1/2)
	EM_NPCSpellTarget_Enemy_HP_Quarter	,//�Ĥ�(HP 1/4)

	EM_NPCSpellTarget_TargetSpell		,//�ؼЬI�k	  
	EM_NPCSpellTarget_Enemy_RangeEnemySpell,//��������I�k�ؼ� 
	EM_NPCSpellTarget_Enemy_Second		,//����ĤG
	EM_NPCSpellTarget_Enemy_Last		,//����̤p
	EM_NPCSpellTarget_Enemy_Nearest		,//�����̪�
	EM_NPCSpellTarget_Enemy_Farest		,//�����̻���

	EM_NPCSpellTarget_Master			,//�D�H
	EM_NPCSpellTarget_Master_HP_Half	,//�D�H(HP 1/2)
	EM_NPCSpellTarget_Master_HP_Quarter	,//�D�H(HP 1/4)

};

struct  NPCSpellBaseStruct
{
	NPCSpellRightTimeENUM	RigthTime;	//�I�k�ɾ�
	NPCSpellTargetENUM		TargetType;	//�ؼ�����
	int		Rate;						//�o�ʾ��v
	int		MagicID;					//�k�N
	int		MagicLv;					//�k�N����
	char*	SpellString;
};
//----------------------------------------------------------------------------------------
enum	PhyResistTypeENUM
{
	EM_PhyResist_NULL	= -1,	//�L
	EM_PhyResist_Hit	,		//����
	EM_PhyResist_Cut	,		//����
	EM_PhyResist_Puncture,		//���
	EM_PhyResist_MAX	,
};
//----------------------------------------------------------------------------------------
enum SpecialDropItemTypeENUM
{
	EM_SpecialDropItemType_None				,
	EM_SpecialDropItemType_DepartmentStroe	,
	EM_SpecialDropItemType_NoGlobalDrop		,	//�����@�ɱ���
};
//----------------------------------------------------------------------------------------
enum NPCCarryTypeENUM
{
	EM_NPCCarryType_None			,
	EM_NPCCarryType_NoControl		,
	EM_NPCCarryType_Control			,
};
//----------------------------------------------------------------------------------------
//�ݩ�NPC���򥻸��
//----------------------------------------------------------------------------------------
struct GameObjectNpcStruct
{
	int			Race;					//�ر�
	int			Vocation;				//¾�~
	int			Vocation_Sub;			//��¾
	int         Sex;                    //�ʧO
	int 		ExpRate;				//�Ǫ�������i�o�쪺�g��Ȧʤ���
	int			TpRate;
	int			Level;					//�򥻵���
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

	int         MainHandEQ[ _MAX_NPC_EQSEL_COUNT_ ];        //�C�@�� 20 %���|�|�˳�
	int         SecHandEQ[ _MAX_NPC_EQSEL_COUNT_];          //�C�@�� 20 %���|�|�˳�

	int			iQuestMode;

	char*		szQuestNpcText;								// ���� NPC �һ����O��
	char*		szQuestDoingText;
	int			iQuestID[_MAX_NPC_QUEST_COUNT_];			// ���� NPC �ү൹�� Quest

	int         Brave;              //�i����
	int         LinkType;           //�Ǫ��s������
	int			EscapeType;			//�k�]����


	NPCSpellBaseStruct		Spell[_MAX_NPC_SPELL_MAGIC_COUNT_];

	NpcTitleTypeENUM		TitleType;
	//GameObjDbStruct*		pQuestLink[ _MAX_QUESTLINK_COUNT ];
	int						iQuestLinkObj[ _MAX_QUESTLINK_COUNT ];


	int			iQuestNPCRefID;

	int					DB_ResistID;				//��Ʈw����id(�I��)
	MagicResistENUM		ResistType;					//NPC���ݩ�	
	MagicResistStruct	Resist;						//�ܩʭ�

	char		szLuaScript[_MAX_SIZE64_QUEST_SCRIPT];						// ��l�Ƽ@���ι�ܮɩҸ��J�� LUA

	//�i�Q���Ѫ����~
	ItemDropStruct			StealItem[ _MAX_NPC_STEAL_ITEM_COUNT_ ];

	//�i�Q���Ѫ�����
	int         StealMoney_Base;
	int         StealMoney_Rand;

	//�L�Īk�N
	GameObjectMagicTypeENUM	AvoidMagicType[_MAX_NPC_AVOID_MAGIC_TYPE_COUNT_];			

	MagicEffectStruct	Effect;						//���Ī����k�N�ĪG

	int			RaceGroupType;						//�s�����U���s��
	int			iQuestObjType;						//���������I���O�_�|����

	int			KeepDistance;						//�԰��� �O���Z��

	GameObjectWeaponENUM	OrgWeaponType;			//�Z������
	GameObjectArmorENUM     OrgArmorType;			//��������

	int			FollowRange;						//�i�l�v�Z��

	int			RaiseChangeNPCID[2];
	int			RaiseChangeRate[2];					//�Q�U�����@

	bool		IsAbilityStandard;					//�O�_���зǼƭ�
	int			AbilityValue[2];					//�ѦҼ�¾

	GameObjectWearEqStruct	Ability;				//���[��O	

//	bool		IsNoMPSP;							//�S��MPSP

	char*		TitleName;							//npc�Y��

	float		PhyResistRate[ EM_PhyResist_MAX ];	//���z�ܩ�

	int			QuestObjCraftMode;					// ���Ȫ���O�_�O��U��y�u��

	int			ZoneID;								//npc�Ҧb����m
	int			X , Y , Z;

//	bool		IsAllZoneVisible;					//�������
//	bool		IsShowNpcPos;
//	bool		AutoRotate;							//�I�k�۰ʭ��V

	int			ZoneID_Bk;							//���e�]�w���ϰ���
	int			BowEQ;								//�˳Ƥ}���
	CampID_ENUM	CampID;
	int			KillGroupID;						//�����O�� -1 ���B�z	

	char		szLuaInitScript[_MAX_SIZE64_QUEST_SCRIPT];						// �w�]��l�Ƽ@�����
	int			AddPowerLV;							//�������żW�[
	
	char		LuaEvent_OnAttackMagic[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnAssistMagic[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnDead[_MAX_SIZE64_QUEST_SCRIPT];
	char		LuaEvent_OnKill[_MAX_SIZE64_QUEST_SCRIPT];

	StructNPCOtherFlag			OtherFlag;
	//bool		IsShowMaster;						//��ܥD�H��T
	int			DEqTypeValue[10];					//��O�L��
	SpecialDropItemTypeENUM SpecialDropItemType;
	int			MinAbilityLv;
	int			OrnamentEQ;							//�˹��~

	char		szLuaDisplayScript[_MAX_SIZE64_QUEST_SCRIPT];						// �w�]��l�Ƽ@�����

	union
	{
		int		_NpcMode;
		struct	
		{
			bool		IsNoMPSP			:1;			//�S��MPSP
			bool		IsAllZoneVisible	:1;			//�������
			bool		IsShowNpcPos		:1;
			bool		AutoRotate			:1;			//�I�k�۰ʭ��V
			bool		IsShowMaster		:1;			//��ܥD�H��T
			bool		NoRandReborn		:1;			//���üƦ�m����
			bool		ClientDelNoWaitting	:1;			//����R���ɥߧY����
			bool		Prompt				:1;			//����ɴ���
			bool		Treasure			:1;			//�_�c
			bool		SearchEnemyAllDir	:1;			//���ĩ������V
			bool		HideRaceInfo		:1;			//����ܺر�
			bool		IgnoreNpcKill		:1;			//(���_)�����Ǫ�����
			bool		IgnoreQuestObjEffect:1;			//(����)���Ȫ���ɤ��o��
			bool		IsAttackFirst		:1;			//(Client)�����P�_�u��
			bool		Invisible_InWagon	:1;			//(Client)���㤺�ݤ���
			bool		ReCalPath			:1;			//���|�Իݭn������|������
			bool		DisableTreasureDrop	:1;			//���|���_
			bool		IsTrapObj			:1;			//(client)��������
			bool		NoFadein			:1;			//(client)���H�J
			bool		IgnorePvPRule		:1;			//�����{��ǳB�z
			bool		RideAttackable		:1;			//����|�Q����
			bool		ScriptFlag			:1;			//�p�ǲM����,�ݭn�M��
			bool		NoReturnAttackPoint	:1;			//���^��}�l�԰��I
		};
	};

	int					iTagID;							// �������� TAG
	int					CarryCount;
	NPCCarryTypeENUM	CarryType;						//��������
	int					SearchGroupID;
	char				CarryLuaScript[_MAX_SIZE64_QUEST_SCRIPT];	//�W�U����Ĳ�o�@��					
	int					CarryShootRange;
	int					CarryShootAngle;
	GameObjectWearEqStruct	AbilityEx;				//���[��O	

	char				LuaEvent_BeginAttack[_MAX_SIZE64_QUEST_SCRIPT];
	char				LuaEvent_EndAttack[_MAX_SIZE64_QUEST_SCRIPT];
	char				CheckCarryLuaScript[_MAX_SIZE64_QUEST_SCRIPT];	//�W�U����Ĳ�o�@��
	char				CheckCarryLuaPoint[_MAX_FILENAME_SIZE_];		//�Ѧ��I

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
//���[�ݩʪ��򥻸��
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

	AddonPos_WeaponLimitPosENUM  WeaponPosEnum;	// 0 ������ 1 �D�� 2�@����
	int			Level;							// ���~����
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
    AttributeTypeENUM   Type;   //���[��O����

//	int		InheritRate;		//�~�Ӿ��v(�U�����@)
//  int		InheritLV;			//�~�ӵ���
//  int     InheritLV_Range;    //�d��

    int     Inc_Magic;          //���t���k�N
    int     Inc_Magic_ActionRate;//�k�N�o�;��v( ���� �Q���� )

    MagicActionTypeENUM     Inc_MagicType;
    AddonPosTypeStruct      AddPos;             //�i�˳Ƴ���

	GameObjectWearEqStruct	Ability;
	//--------------------------------------------------------------------------------------
	//��O�зǫ�
	bool					IsStandardAbility;
	int						StandardAbility_Lv;
	int						StandardAbility_ArgType[5];
	float					StandardAbility_Arg[5];
	//--------------------------------------------------------------------------------------
	int						StarValue;		//�P����
	bool					IsBirthAbility;
	int						InherentValue;	//�~�ӵ��� -1 ���~��
	int						Rarity;			//�}����(0:�L 1:�� 2:�� 3:��K)
};
//----------------------------------------------------------------------------------------
// ��m��O��
//----------------------------------------------------------------------------------------
enum EqRefineAttributeTypeENUM
{
	EM_EqRefineAttributeType_Weapon		,	//�Z��
	EM_EqRefineAttributeType_Staff		,	//�k����
	EM_EqRefineAttributeType_Bow		,	//���Z���Z��
	EM_EqRefineAttributeType_Head       ,   //�Y
	EM_EqRefineAttributeType_Gloves	    ,   //��M
	EM_EqRefineAttributeType_Shoes	    ,   //�c�l
	EM_EqRefineAttributeType_Clothes	,   //�W��
	EM_EqRefineAttributeType_Pants	    ,   //�Ǥl
	EM_EqRefineAttributeType_Back	    ,   //�I��q
	EM_EqRefineAttributeType_Belt	    ,   //�y�a
	EM_EqRefineAttributeType_Shoulder   ,   //�ӥ�
	EM_EqRefineAttributeType_Necklace   ,   //���� 
	EM_EqRefineAttributeType_Ring       ,   //�٤l
	EM_EqRefineAttributeType_Earring    ,   //�չ�
	EM_EqRefineAttributeType_SecondHand ,   //�Ƥ�
};

struct	GameObjectEqRefineAttributeStruct
{
	EqRefineAttributeTypeENUM	Type;
	int							Level;
	GameObjectWearEqStruct		Ability;
	int							ExEqPowerRate;	//�B�~�W�[�˳ư򥻯�O�ʤ���(DMG MDMG DEF MDEF )
};
//----------------------------------------------------------------------------------------
//�q���]�w
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
    EM_GameObjectCreateType_Always      ,           //�û��s�b
    EM_GameObjectCreateType_EmptyDel    ,           //�����R��
    EM_GameObjectCreateTypeENUM_FORCE_DWORD   = 0x7fffffff, 
};

struct	GameObjectMineStruct
{   
    GameObjectMineType      Type;
    float                   BaseCount;                      // ��l�q
    GameObjectCreateType    CreateType;                     // �O�_����
	int                     LvLimit;                        // ���ŭ���

    int					    GetItem[7];                     // ���o���~ ..(�Ǫ��h�O����)
    int				        GetItemRate[7];                 // ���Ͳv
    int			            GetItemCount[7];                // �ƶq
	int						iFlagID;						// ���ͰѦҺX�l, ( �L�@�� )


	int						iReduceVal;						// ��֪�l�q��������
	int						iGenerateObj[5];				// ���ͫ�, ���ͪ�����
	int						iGenerateObjRate[5];			// ���ͫ�, ���ͪ����󪺾��v

	char					szLuaGetItemScript[_MAX_SIZE64_QUEST_SCRIPT];						// ��l�Ƽ@���ι�ܮɩҸ��J�� LUA
};
//----------------------------------------------------------------------------------------
//���n���~
//----------------------------------------------------------------------------------------
enum	KeyItemTypeENUM
{
	EM_KeyItemType_Invisible		,
	EM_KeyItemType_Normal			,	//�@��
	EM_KeyItemType_Key				,	//�_��
	EM_KeyItemType_Map				,	//�a��
	EM_KeyItemType_SkillBook		,	//�ޯ��
	EM_KeyItemType_Recipe			,	//�t���
	EM_KeyItemType_LifeSkillUnLock	,	//�]�w��
	EM_KeyItemType_DailyFlag		,	//�C�魫��n���~
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
//�t���
//----------------------------------------------------------------------------------------
#define _MAX_RECIPE_SOURCE_COUNT_	8
struct RecipeItemStruct
{
    int     OrgObjID;   //�˪O����
    int     Count;      //�ƶq
    int     Rate;       //���Ͳv(�ʤ����@)
};
struct GameObjectRecipeStruct
{
	
    RecipeItemStruct Source[ _MAX_RECIPE_SOURCE_COUNT_ ];                 //���

	union
	{
		RecipeItemStruct ItemAll[9];              //���ͪ��~�@

		struct 
		{
			union
			{
				RecipeItemStruct Item1[6];              //���ͪ��~�@
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
				RecipeItemStruct ItemOther[3];                  //���ͪ��~2-4
				struct  
				{
					RecipeItemStruct Item2;                     //���ͪ��~2
					RecipeItemStruct Item3;                     //���ͪ��~3
					RecipeItemStruct Item4;                     //���ͪ��~4
				};

			};
		};

	};
	
	//�ݨD
	struct
	{
		SkillValueTypeENUM		Skill;				//�ޯ����
		int						SkillLV;			//�ޯ൥��
		int						KeyItemID;			//���n���~
	}Request;

	int	Coldown;	//�N�o�ɶ�(��)

	int	Type;		//�����]�w������
	int	RequestCraftObjType;

	float						ExpRate;			//�X���ұoexp���v

	int	LearnFee;									// �ǲ߰t���, �һݶO��
	int CraftFee;									// ��y���~��, �һݶO��

};
//----------------------------------------------------------------------------------------
//�Y�θ��
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
    TitleNameTypeENUM     Type;                   //����������(�ȮɵL��)
    //=----------------------------------
    //�ݨD
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
		KillCountTypeENUM		Type;			// 0 �����Ǫ� 1 �Q�Ǫ���
		int						KillGroupID;	//
		int						Count;			//�ƶq

	}KillCount;
	//=----------------------------------
    GameObjectWearEqStruct	Ability;

	//�i�ϥΧޯ�
	int		SkillID;							//�i�ϥΧޯ�
	int		SkillLv;							//�ޯ൥��

	int		Classify[2];

	char	LuaEvent[_MAX_SIZE64_QUEST_SCRIPT];

	GameObjectWearEqStruct	AbilityEx;			//�s�Y�Ψt�μW�[��O
	char*	TitleSysNote;						//�s�Y�Ψt�� ����

    char	TitleSysLuaEvent[_MAX_SIZE64_QUEST_SCRIPT];
};
//----------------------------------------------------------------------------------------
//�ϫ��]�w
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
    EM_Motion_Casting_Delay		,				// "casting_delay" �I�k����
    EM_Motion_Cast_01			,				// "cast01" �X���ۨ�
    EM_Motion_Cast_02			,				// "cast02" �X���ؼ�	
};
*/
//----------------------------------------------------------------------------------------
enum ObjectImageTypeENUM 
{
    EM_ObjectImage_2Foots		,  //�H��
    EM_ObjectImage_4Foots		,  //������
	EM_ObjectImage_4Foots2		,  //����
};
//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
struct MagicPartical
{
    char				Point[_MAX_FILENAME_SIZE_];	// ���I��m
    char				Name[_MAX_FILENAME_SIZE_];	// �S�ĦW��
	bool				IsSoundEnabled;				// �ͭ��}��
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
//�ȫ������
struct	PaperdollStruct
{
	char			Name[ 64 ];		
	ColorStruct		MainColor;					
	ColorStruct		OffColor;
};
//----------------------------------------------------------------------------------------
enum GameObjectImageArmorPosENUM
{
	EM_GameObjectImageArmorPos_Clothes,	//�W��
	EM_GameObjectImageArmorPos_Gloves,	//��M
	EM_GameObjectImageArmorPos_Shoulder,//�ӥ�
	EM_GameObjectImageArmorPos_Back,	//�I��
	EM_GameObjectImageArmorPos_Belt,	//�y�a
	EM_GameObjectImageArmorPos_Shoes,	//�c�l
	EM_GameObjectImageArmorPos_Pants,	//�Ǥl
	EM_GameObjectImageArmorPos_Head,	//�Y
	EM_GameObjectImageArmorPos_Hair,	//�Y�v
	EM_GameObjectImageArmorPos_Face,	//�y
};
/*
enum GameObjectImageArmorPosENUM
{
EM_GameObjectImageArmorPos_Hair,	//�Y�v
EM_GameObjectImageArmorPos_Face,	//�y
EM_GameObjectImageArmorPos_Head,	//�Y
EM_GameObjectImageArmorPos_Gloves,	//��M
EM_GameObjectImageArmorPos_Shoes,	//�c�l
EM_GameObjectImageArmorPos_Clothes,	//�W��
EM_GameObjectImageArmorPos_Pants,	//�Ǥl
EM_GameObjectImageArmorPos_Back,	//�I��
EM_GameObjectImageArmorPos_Belt,	//�y�a
EM_GameObjectImageArmorPos_Shoulder,//�ӥ�

};
*/

enum GameObjectImageIconTypeENUM
{
	EM_GameObjectImageIconType_Money,		// ����
	EM_GameObjectImageIconType_RuneMoney,	// �Ť��
	EM_GameObjectImageIconType_Bonus,		// ���Q��
};

//----------------------------------------------------------------------------------------
enum GameObjectMagicShowTypeENUM
{
	EM_GameObjectMagicShowType_Single,				// ����S�ĥu���@�ؼ�
	EM_GameObjectMagicShowType_Multi,				// ����S�Ĺ�h�ӥؼ�
	EM_GameObjectMagicShowType_PolyLine,			// ��s�S�Ĺ�h�ӥؼ�
	EM_GameObjectMagicShowType_Parabola,			// �ߪ��u(��@�ؼЧ��Y)
	EM_GameObjectMagicShowType_ParabolaMulti,		// �ߪ��u(�h��V�ؼЧ��Y)

	EM_GameObjectMagicShowType_FORCEINT	= 0x7FFFFFFF,
};

enum GameObjectCursorAnchorENUM
{
	EM_GameObjectCursorAnchor_None			,	//�S��
	EM_GameObjectCursorAnchor_Cursor		,	//���
	EM_GameObjectCursorAnchor_RightBottom	,	//�k�U
};

// �M���ɨ���ʧ@
enum GameObjectMountRideMotion
{
	EM_GameObjectMountRideMotion_Ride		,		// ��l�M���ʧ@(���}�i�})
	EM_GameObjectMountRideMotion_Ride1		,		// ��l�M���ʧ@(���}����)
	EM_GameObjectMountRideMotion_Stand		,		// ���ߦb���ʪ���
	EM_GameObjectMountRideMotion_Sit		,		// ���U��������	
	EM_GameObjectMountRideMotion_Ride2		,		// �y�ȧ�������
	EM_GameObjectMountRideMotion_FORCEINT	= 0x7FFFFFFF,
};

//----------------------------------------------------------------------------------------
struct GameObjectImageStruct
{
    GameObjectImageTypENUM          ImageType;                      //��ܼҦ�

    char							ACTField[_MAX_FILENAME_SIZE_];	//���~��쪺 ACT 2D
    char							ACTWorld[_MAX_FILENAME_SIZE_];	//�㹳ACT
    int 							ModelSize;			            //��j���v
    int                             BoundRadiusX;                   //�I���b�|
	int                             BoundRadiusY;                   //�I���b�|
    //-----------------------------------------------------------------------------------------
    //�˳Ƹ��
    //-----------------------------------------------------------------------------------------
    GameObjectImageArmorPosENUM     ArmorPos;
	ColorStruct						ArmorMainColor;					
	ColorStruct						ArmorOffColor;
    //-----------------------------------------------------------------------------------------
    //�k�N�ϫ���T
    //-----------------------------------------------------------------------------------------
    // ��I�k�̦ۨ�
    char							GatherMotion[_MAX_FILENAME_SIZE_];		// ����ʧ@
    MagicPartical					GatherPartical[3];						// ����S��

	// BeginACT �C�����S���ϥΨ�
	char							BeginACT[_MAX_FILENAME_SIZE_];			// �X��S��ACT

	// 
#pragma pack(1)
	union 
	{
		char						BeginPoint[_MAX_OBJ_NAME_STR_SIZE_];	// ��H�Ѧ��I��m
		struct 
		{
			GameObjectMountRideMotion RideMotion;
		};
	};	
#pragma pack()
    // �X��	
    char							ShootMotion[_MAX_FILENAME_SIZE_];		// �X��ʧ@
    int 							ShootMotionScale;						// %
    char							ShootACT[_MAX_FILENAME_SIZE_];			// �X��S��ACT
	char							ShootPoint[_MAX_OBJ_NAME_STR_SIZE_];	// ��H�Ѧ��I��m

    // ����
	char							FlyBeginPoint[_MAX_OBJ_NAME_STR_SIZE_];	// ���w����S�Ķ}�l�Ҧb����Ѧ��I��m
    char							FlyACT[_MAX_FILENAME_SIZE_];			// ����S��ACT

    // �ت�
    char							ExplodeACT[_MAX_FILENAME_SIZE_];		// �ت��z���ĪGACT
	char							TargetPoint[_MAX_OBJ_NAME_STR_SIZE_];	// ��H�Ѧ��I��m

	// �����ت��S��,�D�n�ΥH��ئa�S�ļ����,�{�񪫥�����Ωҭn�����ĪG��{
	// ��p�ت����ͤj�z���S��,�����h���ͿU�N�S��
	char							ExtendACT[_MAX_FILENAME_SIZE_];			// �����ت��S��ACT
	char							ExtenPoint[_MAX_OBJ_NAME_STR_SIZE_];	// ������H�Ѧ��I��m

	// Buff
	char							BuffACT[_MAX_FILENAME_SIZE_];			// Buff�ĪGACT	
	char							BuffPoint[_MAX_OBJ_NAME_STR_SIZE_];		// Buff�ĪG��H�Ѧ��I��m
    //-----------------------------------------------------------------------------------------
    //��������
    //-----------------------------------------------------------------------------------------
    ObjectImageTypeENUM             ObjectType;                             //�O��}�٬O�|���ʪ�
	//-----------------------------------------------------------------------------------------
	char							Sound[_MAX_FILENAME_SIZE_];				//�n��

	//NPC�˳Ƹ��
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
		int			BoneScale[5];			//���[�Y��
		struct 
		{
			int	BoneScaleChest;				//��
			int	BoneScaleButtock;			//�v
			int	BoneScaleHand;				//��
			int	BoneScaleLeg;				//��
			int	BoneScaleBra;				//�ݸn
		};
	};
	int			Alpha;						//�b�z��

	GameObjectCursorAnchorENUM	TipType;	//���Ѥ覡
	bool		IsShowShadow;
	bool		IsThrowType;				//�O�_�X��ʧ@�n�βզX���r��
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
	bool							IsPolyLineEffect;		//�O�_����s�S��
	GameObjectMagicShowTypeENUM		MagicShowType;			//�k�N��ܤ覡
	bool							IsHideWeapon;			// ���êZ��
	GameObjectImageIconTypeENUM		SmallIconType;			//�����p�ϥ�

	char							BuffACTEx[_MAX_FILENAME_SIZE_];			// Buff�ĪGACT
	char							PhantomImg[_MAX_FILENAME_SIZE_];		//���F�j�Y��


};


//----------------------------------------------------------------------------------------
//�ϥέ���c
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
//�������~�W��
//----------------------------------------------------------------------------------------
enum ItemType_ENUM
{
    EM_ItemType_Normal          	, //�@��
    EM_ItemType_Plot            	, //�@�����~
    EM_ItemType_Food            	, //����
    EM_ItemType_SweetFood       	, //����
    EM_ItemType_Water           	, //�Ĥ�
    EM_ItemType_Ore             	, //�q��
    EM_ItemType_Wood            	, //���
    EM_ItemType_Herb            	, //�į�
    EM_ItemType_Hunt            	, //�y��
    EM_ItemType_Seed            	, //�ؤl
    EM_ItemType_Flowerpot       	, //���
    EM_ItemType_Crop            	, //�@��
    EM_ItemType_Fish            	, //��
    EM_ItemType_Tool            	, //�Ķ��u��
    EM_ItemType_Stuff           	, //�s�y����
    EM_ItemType_Recipe_BlackSmith   , //�t�� ���K
	EM_ItemType_Recipe_Carpenter    , //�t�� ��u
	EM_ItemType_Recipe_Armor     	, //�t�� �s��
	EM_ItemType_Recipe_Tailor     	, //�t�� ���_
	EM_ItemType_Recipe_Alchemy     	, //�t�� �Ҫ�
	EM_ItemType_Recipe_Cook     	, //�t�� �i��
    EM_ItemType_Jewel           	, //�ĵ��_��
    EM_ItemType_PowerLight      	, //�ĪG���y
    EM_ItemType_Money           	, //����
	EM_ItemType_Rune	           	, //�Ť�
	EM_ItemType_PosRecord			, //��m�O��
	EM_ItemType_GuildContribution	, //���|�^�m�~
	EM_ItemType_Lottery				, //�ֳz�m��
	EM_ItemType_Furniture			, //�a��
	EM_ItemType_SpecialRune			, //�S��Ť�
	EM_ItemType_SmeltStone			, //���ѥ�
	EM_ItemType_Relation			, //���Y���~
	EM_ItemType_SummonHorse			, //�۴��y�M
	EM_ItemType_Contract			, //�ЫΫ���
	EM_ItemType_Study				, //�׷Ҧʬ�
	EM_ItemType_MagicStone			, //�]��
	EM_ItemType_Collection			, //�e�U����
	EM_ItemType_Packet				, //�]�q���~
	EM_ItemType_Pet					, //�d�����~
	EM_ItemType_Pet_Tools			, //�d���u��
	EM_ItemType_Pet_Furniture		, //�d���í�
	EM_ItemType_Pet_Food			, //�d������
	EM_ItemType_Packet_DropList		, //���]��(������Ҧ��F��)
	EM_ItemType_Egg					, //�ӫ���J
	EM_ItemType_ViewPet				, //�[����d��
	EM_ItemType_TitleItem			, //�Y�Ψt�Ϊ��~
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
	EM_RuneType_Manufacture		,//�Ͳ�
	EM_RuneType_Weapon			,//�Z��
	EM_RuneType_Armor			,//����
	EM_RuneType_Head			,//�Y��
	EM_RuneType_Body			,//�W��
	EM_RuneType_Pant			,//�U��
	EM_RuneType_Special			,//�S��
	EM_RuneType_Ornament		,//���~
	EM_RuneType_Shield			,//��
	EM_RuneType_MagicTools		,//�k��
	EM_RuneType_NewSystem		,//�J��t��
};	

enum ItemUseType_ENUM
{
	EM_ItemUseType_None				,
	EM_ItemUseType_Magic			,
	EM_ItemUseType_SrvScript		,
	EM_ItemUseType_CliScript		,
	EM_ItemUseType_EqRefine			,	//�ĵ�
	EM_ItemUseType_FixEq			,	//�׸�
	EM_ItemUseType_Dissolution		,	//��Ѫ��~
	EM_ItemUseType_Coloring			,	//�V��
	//EM_ItemUseType_ClsEqSoulbound	,	//�M���˳Ƹj�w
	EM_ItemUseType_ClsTrade			,	//�M���˳Ƹj�w
	EM_ItemUseType_ResetAbility		,	//���]�򥻼ƭ�
	EM_ItemUseType_ResetSkillPoint	,	//���]�ޯ��I��
	EM_ItemUseType_EQDigHole		,	//�˳ƫ��}
	EM_ItemUseType_EQClearRune		,	//�M���˳ƲŤ�
	EM_ItemUseType_ItemLock			,	//�˳���
	EM_ItemUseType_ItemUnLock		,	//�Ѱ��˳���
	EM_ItemUseType_EQProtect		,	//�˳ƫO�@
	EM_ItemUseType_EQLimitMax		,	//�˳ƭ@�[�W����Max
	EM_ItemUseType_IgnoreLimitLv	,	//�������ŭ���
	EM_ItemUseType_PK_EQProtect		,	//PK�˳ƫO�@
	EM_ItemUseType_PK_EQProtect_Clear,	//PK�˳ƫO�@�M��
	EM_ItemUseType_UnPacket			,	//���}�]�q���~
	EM_ItemUseType_UnPacket_DropList,	//���]���Ѷ}(������Ҧ��F��)
	EM_ItemUseType_Egg				,	//�ӫ���J
	EM_ItemUseType_ClsEqSoulbound	,	//�M���˳Ƹj�w
	EM_ItemUseType_ClsEqAbility		,	//�M���Ҧ��˳��ݩ�
//	EM_ItemUseType_ClsTrade_All		,	//�M���Ҧ����~�������w
	EM_ItemUseType_ItemtoItemLua	,	//���~�磌�~Ĳ�olua
};

enum EqRefineType_ENUM
{
	EM_EqRefineType_Weapon		,
	EM_EqRefineType_Armor		,
	EM_EqRefineType_Jewels		,
	EM_EqRefineType_Ornament	,
};

//���~�ͦs�ɶ�����
enum ItemLiveTimeTypeENUM
{
	EM_ItemLiveTimeType_None			,	//���|����
	EM_ItemLiveTimeType_RealTime		,	//�u��ɶ�
};

//���~�S�Ĥ���
enum ImageEfficacyTypeENUM
{
	EM_ImageEfficacyType_None			,	//�L
	EM_ImageEfficacyType_Throw_Sword	,	//���Y ���C,���M
	EM_ImageEfficacyType_Throw_Axe		,	//���Y ����
	EM_ImageEfficacyType_Throw_Stone	,	//���Y ���Y
	EM_ImageEfficacyType_Throw_Arrow	,	//���Y �b��
	EM_ImageEfficacyType_Throw_Ammo		,	//���Y �l�u
};


//�í�
enum					EnumItemFurnitureType
{
	EM_FurnitureType_Normal		= 0,	// �@��, ����e�q
	EM_FurnitureType_Storage	= 1,	// ���x�s�Ŷ����í�
	EM_FurnitureType_Coathanger	= 2,	// ��[, �B�i�H�i�ܦ窫, �˳�, ���x�s�Ŷ����í�
	EM_FurnitureType_WeaponSet	= 3,	// �Z���[, �i�H����, ������Z���ά�, ���x�s�Ŷ����í�
	EM_FurnitureType_WeaponAndCloth	= 4,	// �Z����[, �i�H����, �Z���P�˳�
	EM_FurnitureType_Maid		= 5,	// �k��
};

enum					EnumItemFurnitureEffect
{
	EM_FurnitureEffect_None		= 0,	// ���㴣�ɮĪG
	EM_FurnitureEffect_EXP		,		// ���� EXP BOUNS
	EM_FurnitureEffect_TP		,		// ���� TP BOUNS
	EM_FurnitureEffect_HQ		,		// �����U�ب�y�ޯవ�X HQ ���~�����|
};

enum					EnumItemFurniturePos
{
	EM_FurniturePos_NoRule		= 0,	// �����w
	EM_FurniturePos_Ground		,		// �u���b�a�O�W
	EM_FurniturePos_Wall		,		// �u���b��W
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
	EM_AddPowerType_No			,		//���[
	EM_AddPowerType_Standard	,		//�з�
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
	EM_SeedType_None	,	//���O�ؤl
	EM_SeedType_Tree	,	//��
	EM_SeedType_Grass	,	//��
	EM_SeedType_Mine	,	//�q
};

enum ManureTypeENUM
{
	EM_ManureType_None		,	//���O�ή�
	EM_ManureType_Water		,	//��@
	EM_ManureType_Topdress	,	//�I��
	EM_ManureType_MagicWater,	//�]�k��@
};

enum FurnitureTypeENUM
{
	EM_FurnitureType_All		,
	EM_FurnitureType_GuildOnly	,
	EM_FurnitureType_HouseOnly	,
};

enum PetFoodEffectTypeENUM 
{
	EM_PetFoodEffectType_None			,	//�L
	EM_PetFoodEffectType_STR			,	//STR
	EM_PetFoodEffectType_STA			,	//STA
	EM_PetFoodEffectType_INT			,	//INT
	EM_PetFoodEffectType_MND			,	//MND
	EM_PetFoodEffectType_AGI			,	//AGI
	EM_PetFoodEffectType_PetProperty	,	//�����ݩ�
	EM_PetFoodEffectType_PetObjID		,	//���ܥ~�[

};

enum ExBagTypeENUM
{
	EM_ExBagType_None	,
	EM_ExBagType_Pet	,
	EM_ExBagType_Horse	,
};
//----------------------------------------------------------------------------------------
//�ݩ󪫫~���򥻸��
//----------------------------------------------------------------------------------------
struct GameObjectItemStruct
{
	GameObjectItemENUM		Class;

    ItemType_ENUM           ItemType; 

	int						IncMagic_Onuse;		    //���ͪ��k�N�ĪG(�ϥΪ��ĪG)
    int                     IncMagic_OnAttack;      //���ͪ��k�N�ĪG(�\����)
    int                     IncMagic_OnAttackRate;  //�����o�ͪ����v

    int                     DisappearRate;      //�X�����Ѯ����v
	float					DissolutionRate;	//���ѥ[���v
    int                     SrcRecipe;          //�X���t��

    union
    {
	    GameObjectWeaponENUM	WeaponType;			//�Z������
        GameObjectArmorENUM     ArmorType;			//��������
    };
    union
    {
        GameObjectWeaponPosENUM WeaponPos;
        GameObjectArmorPosENUM  ArmorPos;
    };

	GameObjectWearEqStruct	Ability;
	ItemDropStruct DropItemAbility[_MAX_DROP_ABILITY_COUNT_];

	int						AttackDistance;		//�����Z��
    int                     HoleBase;           //�򥻬}��(�Ť�e�q)
    int                     HoleRange;          //�i�ܽd��(�O�d)
//    AddPowerTypeENUM        AddPowerOn;         //���~�����O�_�]�@����[�ݩʳW�h(or�Ť��O) ( 0 ���] 1 �] 2 ���w�� )
	int						MaxAttrCount;		//�̦h�i���[��O�U��


    AddonPosTypeStruct      AddPos;             //(�Ť�)�^�J�˳Ƴ���
    RuneType_ENUM           RuneType;           //�Ť�����(������)
	int						RuneGroup;			//�Ť����
    int                     Durable;
	int						Level;				//�ϥε���
	int						Volume;				//�Ť�e�q
	int						ManuFactureType;	//�s�y����
	int						ManuFactureLV;		//�s�y����

	int						SuitID;				//�M��ID

	int						AttackRange;		//�����d��
	int						AttackSpeed;

	ItemUseType_ENUM		UseType;				//���~�ϥμҦ�
	char					SrvScript[128];			//�ϥΰ��� Server�Y�@�� �����^�� true=1 or false=0 ����ϥ�Sleep
	char					CliScript[128];			//�ϥΰ��� Client�Y�@��
	char					CheckUseScript[128];	//�ϥ��ˬd lua
	//�ײz���
	int						FixQuality;			//���׫~��

	//�ĵ����
	EqRefineType_ENUM		EqRefineType;
	float					EqRefineRate_Base;
	float					EqRefineRate_Fix;
	float					EqRefineRate_Per;

	int						EqRefineEqMinLv;		//�ϥε���
	int						EqRefineEqMaxLv;
	int						EqRefineMinLv;			//��Ƶ���
	int						EqRefineMaxLv;
	float					EqRefineFailed_LevelDownRate_Base;	//���Ѱh�����v
	float					EqRefineFailed_LevelDownRate_Fix;	//���Ѱh�����v
	float					EqRefineFailed_LevelDownRate_Per;	//���Ѱh�����v
	float					EqRefineFailed_ExplodeRate_Base;	//���Ѯ������v
	float					EqRefineFailed_ExplodeRate_Fix;		//���Ѯ������v
	float					EqRefineFailed_ExplodeRate_Per;		//���Ѯ������v
	bool					IsItemToItem;			//�i�磌�~�ϥ�

	bool					IsStandardCost;
	int						ReferenceLv;			//�Ѧһ�����
	int						Coloring_OffColor;
	int						Coloring_MainColor;

	//�d���M�θ��
	int						CardOrgObjID;			//�d�����ު����
	int						CardID;					//�d�������X
	ImageEfficacyTypeENUM	ImageEfficacyType;		//�S�İѼ�

	int						CastingTime;			//�ϥήɶ�
	//--------------------------------------------------------------------------------------
	//��O�зǫ�
	bool					IsStandardAbility;
	int						StandardAbility_Lv;
	int						StandardAbility_ArgType[5];
	float					StandardAbility_Arg[5];
	//--------------------------------------------------------------------------------------
	int						CardPriorityID;			//�d���Ƨ��u���v�@
	int						GuildContributionValue;	//���|�^�m�ҥ[���n��
	//--------------------------------------------------------------------------------------
	int						RefineTableID;			//�ĵ��ѦҸ�Ʀ�m
	//--------------------------------------------------------------------------------------
	char					MagicToolsScript[128];	//�k�_�C�Q��w�ɨϥΪ�Lua

	// �í�
	//--------------------------------------------------------------------------------------
	EnumItemFurnitureType		emFurnitureType;
	EnumItemFurnitureEffect		emFurnitureEffect;
	int							iFurnitureStorageSize;
	EnumItemFurniturePos		emFurniturePos;

	int							iCraftObjType;				// �ണ�Ѩ�U�Ͳ��ޯ�
	int							iFurnitureSuitID;			// �íѮM�ˮĪG

	int							ExpPoint;
	int							TpPoint;
	
	int 						BlackSmithHQPoint;
	int 						CarpenterHQPoint;	
	int 						MakeArmorHQPoint;	
	int 						TailorHQPoint;		
	int 						CookHQPoint;		
	int 						AlchemyHQPoint;

	//--------------------------------------------------------------------------------------
	//�˳ƥ��}
	struct  
	{
		int					MaxHoleCount;	//�̤j�}��
		DigHoleTypeENUM		Type;			//����
		int					Rate;			//���v
	}DigHole;
	//--------------------------------------------------------------------------------------
	//�ϥζ��n2���K�X
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
	int		RuneLimetLv;		//�Ť孭���
	//--------------------------------------------------------------------------------------
	GuildResourceTypeENUM GuildResourceType;
	int	GuildResourceValue;

	int		SelectBaseAttrCount;
	int		BaseAttrCount;
	char	MagicToolsTpExpScript[64];	//���Ǳo��Exp �P Tp
	char	OnDestroyScript[64];	
	int		ItemUniqueType;				//�˳ưߤ@�]�w( 0 ) ��ܨS�]�w
	int		FurnitureNPCObjID;

	char	ItemUseOKScript[64];		//�ϥΪ��~���\���@��
	int		DropListPacket;				//���~�ϥά��������Ҧ��F��
	struct
	{
		struct  
		{	
			SeedTypeENUM	Type;
			float			GrowSpeed;
			int				ModelType;		//�ҫ�����
			int				BestWater;		//�̨Τ���
			int				BestTopdress;	//�̨ξi��
			int				RandSeed;		//�üƺؤl
		}Seed;
		struct  
		{
			union
			{
				int	Mode;
				struct  //�i�ش�����
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
		int	Level;			//�شӵ���
		float			DecWater;		//�����C�p�ɤU��
		float			DecTopdress;	//�i���C�p�ɤU��
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
			int DDmg;			//�Z���L�ո��
			int DMDmg;
		};
		struct
		{	
			int DDef;			//����L�ո��
			int DMDef;
		};
	};

	int		CardAddpower;		//�d���a����O���

	int		FurnitureSoundID;	//�d�n��ID

	ExBagTypeENUM		ExBagType;			//��J�S��]�q�����
	int					ExBagTypeSub;

	int		BodyMaxCount;		//����̦h�X��
	int		DrawOutCost;		//���X����

	struct
	{
		int Famous;
		int	Exp;
	}TitleSys;

	int		RefineLv;				//��l���嵥��
	int		AddPowerQuality;		//�B�~�W�[�¤O
	int		CollectionNPC;			//��Ų�Ѧ�NPC
//	int		ColorType;
//	int		RuneSystemTableID;		//�J��@��� �ѦҪ�ID

};

//----------------------------------------------------------------------------------------
//���F
//----------------------------------------------------------------------------------------
struct AbiParametersTableStruct
{
	int	GUID;				
	float Parameter;		//��O�Ѽ�

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
	int						RankUpMaterial;		//���ɶ��ŧ���
	int						LevelUpType;		//�ɯŧ������O
	GameObjectWearEqStruct	abi_Phantom;		//���F��O	
};
//----------------------------------------------------------------------------------------
//�k�N�����C�|
//----------------------------------------------------------------------------------------
enum	GameObjectMagicENUM
{
	//�ߧY����
	EM_Magic_Attack			    ,	//����
	EM_Magic_Cure				,	//�v��
	EM_Magic_Rebuff			    ,	//�hBuff

	//����ĪG
	EM_Magic_Assist			    ,	//���U�ĪG���k�N
	EM_Magic_Disease			,	//���n�����A
    EM_GameObjectMagicEM_FORCE_DWORD   = 0x7fffffff, 
};

//----------------------------------------------------------------------------------------
//	�k�N�ؼг]�w
//----------------------------------------------------------------------------------------
enum	GameObjectRelationENUM
{
	EM_Releation_Self			,	//�ۤv
	EM_Releation_Member		    ,	//����

	EM_Releation_Self_Pet		,	//�ۤv(pet)
	EM_Releation_Member_Pet	    ,	//����(pet)

	EM_Releation_Friend		    ,	//�ͤ�,(�缾�a �h���Ҧ����a   �藍�ݩ󪱮a��NPC �h�����ݩ󪱮a��NPC)
	EM_Releation_Friend_NPC	    ,	//�ͤ誺�d��(�p�d���A�l��X�Ӫ��A�ݩ���H�ۤv��NPC)

	EM_Releation_Enemy		    ,	//�Ҧ��i������ﶵ
	EM_Releation_Player		    ,	//�Ҧ����a
	EM_Releation_All			,	//�Ҧ�����

	EM_Releation_GuildPlayer	,	//�P���|���a
	EM_Releation_NotGuildPlayer ,	//���P���|���a

    EM_Releation_CountryPlayer	,	//�P��a���a
    EM_Releation_NoCountryPlayer,	//���P��a���a

	EM_Releation_Corpse			,	//����
	EM_Releation_Npc_Corpse		,	//NPC����
	EM_Releation_Player_Corpse	,	//���a����
	EM_Releation_Locatoin		,	//���w��m( �d��k�N )

	EM_Releation_PetOwner		,	//�ۤv���D�H
	EM_Releation_Wagon			,	//����
	EM_Releation_Plot			,	//�@�����

    EM_GameObjectRelationEM_FORCE_DWORD   = 0x7fffffff, 
};

//----------------------------------------------------------------------------------------
//���Ľd��
//----------------------------------------------------------------------------------------
//(�n�����Ľd��)�ۤv ���� �P�u�|
//(�a�����Ľd��)�i�H�����
enum	GameObjectMagicEffectRangeENUM
{
	EM_MagicEffect_Target			,	//�ؼЦ���
	EM_MagicEffect_Good_Range		,	//�n���d��k�N
	EM_MagicEffect_Good_Member	    ,	//�n�������k�N
	EM_MagicEffect_Bad_Range		,	//�a���d��k�N
	EM_MagicEffect_AllObj			,
	EM_MagicEffect_AllPlayer		,
	EM_MagicEffect_AllMonster		,
	EM_MagicEffect_AllPlayer_Enemy	,	//�Ҧ��Ĥ誱�a
	EM_MagicEffect_AllPlayer_Friend	,	//�Ҧ��ڤ誱�a
	EM_MagicEffect_Plot				,	//�@�����
    EM_GameObjectMagicEffectRangeEM_FORCE_DWORD   = 0x7fffffff, 
};
//----------------------------------------------------------------------------------------
enum MagicFuncENUM
{
	EM_MAGICFUN_HPMP		= 0	,
	EM_MAGICFUN_Assist		    ,	//���U
	EM_MAGICFUN_Teleport		,	//�ǰe
	EM_MAGICFUN_SummonCreature  ,	//�۴��ͪ�(�d��)
	EM_MAGICFUN_SummonItem	    ,	//�۴����~
	EM_MAGICFUN_Steal			,	//����
	EM_MAGICFUN_ItemRunPlot	    ,	//���ͪ��~�åB����@��
	EM_MAGICFUN_RunPlot		    ,	//����@��
	EM_MAGICFUN_Raise		   	,	//�_��
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
//�k�N���ӵ��c
//----------------------------------------------------------------------------------------
struct MagicCostStruct
{
	MagicSpellCostTypeENUM	Type;		//��������
	int				Value;				//���Ӽƭ�
};
//----------------------------------------------------------------------------------------
//�k�N�ݨD���c
//----------------------------------------------------------------------------------------
struct MagicNeedStruct
{
	MagicSpellNeedTypeENUM	Type;		//�ݨD����
	int						Value;		//��
};
//-----------------------------------------------------------------------
//�ǰe�]�k
//-----------------------------------------------------------------------
struct	MagicTeleport
{
	int	ZoneID;
	int	X , Y , Z;
	int Dir;
};


//-----------------------------------------------------------------------
//	�����]�k
//-----------------------------------------------------------------------
enum  MagicAttackCalENUM
{
    EM_MagicAttackCal_None      	,
    EM_MagicAttackCal_MPow      	,
    EM_MagicAttackCal_Weapon    	,// (����DMG + �D��DMG)
    EM_MagicAttackCal_Shoot     	,//  �g����( ����DMG + �}DMG + �u��DMG)
    EM_MagicAttackCal_Throw     	,//  ���Y��( ����DMG + �u��DMG)
    EM_MagicAttackCal_INT       	,
    EM_MagicAttackCal_STR       	,
    EM_MagicAttackCal_AGI       	,
    EM_MagicAttackCal_STA       	,
    EM_MagicAttackCal_MND       	,  
	EM_MagicAttackCal_LastSkillDmg 	,  
	EM_MagicAttackCal_LastPhyDmg   	,  
	EM_MagicAttackCal_ShieldDef   	,  
};

//��������
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

    float       Rand;           //�ˮ` �ܤƽd��
	
	int			CritialRate;	//�W�[�P�R�@���v
	float		HateRate;
};
//-----------------------------------------------------------------------
//�_���N
//-----------------------------------------------------------------------
struct MagicRaise
{
	int		ExpPrecnt;
};
//-----------------------------------------------------------------------
//�l��ͪ�
//-----------------------------------------------------------------------
enum MagicSummonCreatureTypeENUM
{
	EM_MagicSummonCreatureType_Pet				,
	EM_MagicSummonCreatureType_Guard			,
	EM_MagicSummonCreatureType_Guard_NoAttack	,
};

enum PetSpellRightTimeENUM
{
	EM_PetSpellRightTime_OwnerStartUsing	,		//�D�H�]�w�ϥ�(�`���ϥ�)
	EM_PetSpellRightTime_Auto				,		//�۰ʨϥ�	
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
	int						Rate;			//�I�k���v
	int						SkillID;		//�k�NID
};
*/

struct MagicSummonCreature
{
	int		ObjID;
	int		Level;
	int		RangeLevel;
	int		LiveTime;				//�ͦs��(-1)�N������
	float	SkillLvArg;
	MagicSummonCreatureTypeENUM Type;
	int		GroupID;				//�P�@�s�եu�঳�@��
	float	OwnerPowerRate;			//�W�[���a�@�w��Ҫ���O���d���W

	//PetSkillStruct	Skill[ _MAX_PET_SKILL_COUNT_ ];
	int		SkillType[3];
	char	InitLua[32];
};
//-----------------------------------------------------------------------
//�l�ꪫ�~
//-----------------------------------------------------------------------
struct MagicSummonItem
{
	int		ObjID;
};
//-----------------------------------------------------------------------
//����
//-----------------------------------------------------------------------
/*
enum	MagicStealClassENUM
{
	EM_MagicSteal_NULL	= 0	,		//�����c��ƵL��
	EM_MagicSteal_Money		,
	EM_MagicSteal_Item		,
};
*/
struct MagicSteal
{
//	MagicStealClassENUM		Class;
	int						SuccessRate;		//���\�v
};
//-----------------------------------------------------------------------
//���ͪ��~����@��
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
	EM_MagicItemRunPlot_Plot	,	//�@����
	EM_MagicItemRunPlot_Mine	,	//�a�p��
	EM_MagicItemRunPlot_Staff	,	//������
};
struct MagicItemRunPlot
{
	MagicItemRunPlotENUM	Type;	//����
	int		ObjID;
	char	PlotName[64];
	int		LiveTime;				//�ͦs��(-1)�N������
	int		UseMagic;				//�ϥΪk�N
	int		OnDeadMagic;			//���`�������ͪ��k�N
	int		GroupID;				//�s��ID	( 0  �N�����s��)
	union
	{
		int		Mode;
		//ObjectModeStruct	Mode;		//���󪺰��ݩ�
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
//����@��
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
    EM_Magic_Good       ,       //�n�k�N
    EM_Magic_Bad        ,       //�a���k�N
};
//----------------------------------------------------------------------------------------
//�k�N �� ���z
//----------------------------------------------------------------------------------------
enum    MagicorPhyENUM
{
    EM_Magic_Magic      ,       //�ݩ��]�k����
    EM_Magic_Phy        ,       //�ݩ󪫲z����
    EM_Magic_Eq         ,       //�˳�( �۰ʬI�i )
	EM_Magic_PetEq      ,       //�˳�( �}�i�d�� )
};

//----------------------------------------------------------------------------------------
//Dot�k�N���c
//----------------------------------------------------------------------------------------
enum	DotMagicTypeENUM
{
	EM_DotMagicType_HP	,			//HP
	EM_DotMagicType_MP	,			//MP
	EM_DotMagicType_WarriorSP	,	//�ԤhSP
	EM_DotMagicType_RangerSP	,	//�C�LSP
	EM_DotMagicType_RogueSP		,	//�s��SP
	EM_DotMagicType_HP_Per		,	//HP�ʤ���
	EM_DotMagicType_MP_Per		,	//MP�ʤ���

};

struct DotMagicStruct
{       
    int					Time;			 //�h�[�@��
    DotMagicTypeENUM    Type;			 //����( 0 HP , 1 MP , 2 SP�Ԥh )
    int					Base;			 //�C���ˮ`
	float				DotSkillLVArg;	 //�ޯ൥�żv�T
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
// �k�O�޳]�w���
//----------------------------------------------------------------------------------------
enum	MagicShieldTypeENUM
{
	EM_MagicShieldType_MP				,		//MP���HP
	EM_MagicShieldType_Times			,		//�������
	EM_MagicShieldType_Point			,		//����k�Ƴ]�w���I��
	EM_MagicShieldType_Percent			,		//��P�ʤ���
	EM_MagicShieldType_Point_ByHealArg	,		//����I��
};

enum	MagicShieldEffecENUM
{
	EM_MagicShieldEffec_All			,	//�Ҧ�����
	EM_MagicShieldEffec_Phy			,	//���z����
	EM_MagicShieldEffec_Magic		,	//�k�N����
	EM_MagicShieldEffec_Earth		,	//�a�t�k�N����
	EM_MagicShieldEffec_Water    	,	//���t�k�N����
	EM_MagicShieldEffec_Fire     	,	//���t�k�N����
	EM_MagicShieldEffec_Wind     	,	//���t�k�N����
	EM_MagicShieldEffec_Light    	,	//���t�k�N����
	EM_MagicShieldEffec_Darkness 	,	//�t�t�k�N����
};

struct MagicShieldStruct
{
	MagicShieldTypeENUM		Type;
	MagicShieldEffecENUM	Effect;
	int						Point;		//�i�l���I��
	float					SkillLvArg;
};

//----------------------------------------------------------------------------------------
// coldown��Ƴ]�w
//----------------------------------------------------------------------------------------
enum	MagicColdownClassENUM
{
	EM_MagicColdownClass_None	,		//�S��
	EM_MagicColdownClass_Job	,		//¾�~����
	EM_MagicColdownClass_EQ		,		//�˳�����
	EM_MagicColdownClass_Item	,		//���~����

};
struct MagicColdownBaseStruct
{
	//�@�몺Coldown
	MagicColdownClassENUM		Class;
	int							Type;
	int							Time;	//(��)
	//�U���i���k���ɶ�
	int							TimeAllMagic;		
};
//----------------------------------------------------------------------------------------
//�S��欰
//----------------------------------------------------------------------------------------
struct MagicAttackSpecialAction
{
	union
	{
		int _Type;
		struct
		{
			bool	None			: 1;	//�O�d
			bool    StrikeBack		: 1;	//�_�h
			bool	SpellInterrupt	: 1;	//�I�k���_
			bool	IgnoreDefine	: 1;	//�L�����mor�ܩ�
			bool	EraseHate		: 1;	//�M������( �|��� �P�[��p�� )
			bool	HateOnePoint	: 1;	//����M����1
			bool	Bomb			: 1;	//����
		};
	};
};
//----------------------------------------------------------------------------------------
//�����k�N�p��覡�C�|
//----------------------------------------------------------------------------------------
enum MagicAttackCalBaseENUM
{
	EM_MagicAttackCalBase_Physics		,//���z�p��
	EM_MagicAttackCalBase_Magic			,//�k�N�p��
	EM_MagicAttackCalBase_Throw			,//���Y�p��
	EM_MagicAttackCalBase_Shoot			,//�g���p��
	EM_MagicAttackCalBase_Fix			,//�w��
	EM_MagicAttackCalBase_HolyHeal		,//���t�v���p��( �t�Ȫ��Miss  )
	EM_MagicAttackCalBase_DarkHeal		,//�����t���p��( �t�Ȫ��Miss  )
	EM_MagicAttackCalBase_SpecialAction	,//�S�����u���S��欰
	EM_MagicAttackCalBase_FixPer		,//�ʤ���
	EM_MagicAttackCalBase_Physics_Point	,//���z�p��
	EM_MagicAttackCalBase_MagicEx		,//�k�ƭp�� ���*MDmg * MDmg_MagArg 

//	EM_MagicAttackCalBase_ShootEx		,//�g���p��(�P���z�p��)
};
//----------------------------------------------------------------------------------------
enum	SpecailMagicEventTypeENUM
{	
	EM_SpecailMagicEventType_None				,	//�L
	EM_SpecailMagicEventType_SelfCritial		,	//�ۤv �����P�R�@��(����)
	EM_SpecailMagicEventType_TargetCritial		,	//�ؼ� �����P�R�@��(����)
	EM_SpecailMagicEventType_SelfDodge			,	//�ۤv �{��
	EM_SpecailMagicEventType_TargetDodge		,	//�ؼ� �{��
	EM_SpecailMagicEventType_SelfMiss			,	//�ۤv Miss
	EM_SpecailMagicEventType_TargetMiss			,	//�ؼ� Miss
	EM_SpecailMagicEventType_ZoneDamage			,	//�ϰ�ˮ`�ƥ�
	EM_SpecailMagicEventType_Phy_SelfCritial	,	//�ۤv �����P�R�@��(���z)
	EM_SpecailMagicEventType_Phy_TargetCritial	,	//�ؼ� �����P�R�@��(���z)
	EM_SpecailMagicEventType_Mag_SelfCritial	,	//�ۤv �����P�R�@��(�k�N)
	EM_SpecailMagicEventType_Mag_TargetCritial	,	//�ؼ� �����P�R�@��(�k�N)
	EM_SpecailMagicEventType_Cure_Self			,	//�ۤv ���v��
	EM_SpecailMagicEventType_Cure_Target		,	//�ؼ� �v���ؼ�
	EM_SpecailMagicEventType_SelfParry			,	//�ۤv ���
	EM_SpecailMagicEventType_TargetParry		,	//�ؼ� ���
	EM_SpecailMagicEventType_SelfSpell			,	//�ۤv�I�k
};
//----------------------------------------------------------------------------------------
//�ݩ�k�N���򥻸��
//----------------------------------------------------------------------------------------
#define _MAX_BUFFSKILL_COUNT_	6
struct GameObjectMagicStruct  
{
	MagicFuncENUM			MagicFunc;				//�k�N����(�n�Ψ��Ӫk�NFunction�h�I�s)
    MagicResistENUM			MagicType;              //�]�k����
	MagicorPhyENUM			EffectType;

	float	    EffectTime;							//���Įɶ�(0.1 �����)
    float       DLV_EffectTime;					    //���Ůt�v�T���Įɶ�(0.1 �����)
	float		EffectTime_SkillLVArg;				//�ޯ൥�żv�T�ɶ��Ѽ�
	int		    HateCost;							//�����(+ �ؼХ[�h�֤����)(- �ؼЪ��������ؼ� ��h�֤����)
	
	int			MaxBuffLv_Base;						//Buf���|�ĪG���̰�����
	float		MaxBuffLv_SkillLVArg;				//�]�ޯ�t�v�Tbuf�̰����Ū��Ѽ�

	int			MagicGroupSet;						//���]�k���ݪ�����
    //-----------------------------------------------------------------------
	MagicSpellFlagStruct			Setting;		//�k�N�]�w�X��
	MagicAttackSpecialAction		SpecialAction;	//�S���欰
	
	//-----------------------------------------------------------------------
	//(����v�T���ƭ�)���U�]�k
	//-----------------------------------------------------------------------
	GameObjectMagicTypeENUM			AssistType;			//�k�N����(�D�n�Ω󻲧U�k�N�����B�z)
    int		                        EffectLV;			//���U�k�N�¤O����
	int								EffectAddonType;	//�P���O�_���\ 0���\    1�����\ 
	MagicEffectStruct				Effect;				//�v�T�ĪG
	

    MagicClearTimeStruct            ClearTime;			//��������
	GameObjectWearEqStruct			Ability;			//�v�T�ݩ�
    float							Ability_SkillLVArg;	//�ޯ൥�żv�T�ĪG

    int                             OnTimeMagic_Magic;  //�w�ɲ��ͪk�N�ĪG(�k�NiD)
    int                             OnTimeMagic_Time;   //�w�ɲ��ͪk�N�ĪG(�h�[�@��)
    int                             FaceOffID;          //�ܨ�ID( 0 �N������ )
	int								RideID;				//�M��ID( 0 �N������ )

	int								OnAttackMagicID;		//��Q�����ɲ��ͪ��k�N
	int								OnBuffTimeOutMagicID;	//�����U�k�N�����ɲ��ͪ��k�N
	int								OnAttackReboundMagicID;	//�Q����ϼu�X�Ӫ��k�N
	int								OnMagicAttackReboundMagicID;	//�Q����ϼu�X�Ӫ��k�N
	int								OnDeadMagicID;			//���`�ɲ��ͪ��k��
	int								TempHateCost;			//�ȮɼW�[�������
    int								ClearMagicGroupSet;		//�Ϩ��������k�N�L��
    DotMagicStruct                  DotMagic;           
	//-----------------------------------------------------------------------
	//�����]�k
	//-----------------------------------------------------------------------
	MagicAttackStruct				Attack;		//�����]�k���
	//-----------------------------------------------------------------------
	//�ǰe�]�k
	//-----------------------------------------------------------------------
	MagicTeleport					Teleport;	
	//-----------------------------------------------------------------------
	//�_���N
	//-----------------------------------------------------------------------
	MagicRaise						Raise;		
	//-----------------------------------------------------------------------
	//�l��ͪ�
	//-----------------------------------------------------------------------
	MagicSummonCreature				SummonCreature;
	//-----------------------------------------------------------------------
	//�l�ꪫ�~
	//-----------------------------------------------------------------------
	MagicSummonItem					SummonItem;
	//-----------------------------------------------------------------------
	//����
	//-----------------------------------------------------------------------
	MagicSteal						Steal;

	//-----------------------------------------------------------------------
	//���ͪ��~����@��
	//-----------------------------------------------------------------------
	MagicItemRunPlot				ItemRunPlot;
	//-----------------------------------------------------------------------
	//����@��
	//-----------------------------------------------------------------------
	MagicRunPlot					RunPlot;
	//-----------------------------------------------------------------------
	//�k�O��
	MagicShieldStruct				MagicShield;

	//�����k�N�p��覡
	MagicAttackCalBaseENUM			AtkCalType;				

	//�k�N�s�դ���
	int								MagicGroupID;

	//Buff�W��ܪ��Ʀr
	int								BuffCount;			

	//���z�ܮ`����
	PhyResistTypeENUM				PhyAttackType;

	//////////////////////////////////////////////////////////////////////////
	//�����B�z
	bool							IsStandard_Attack;
	float							RefPowerLv_Attack;
	float							RefPowerRate_Attack;
	//////////////////////////////////////////////////////////////////////////
	float							ModelSize;			//�ҫ��Y����

	int								Revive_SkillLVArg;	//�����v�T�^�_�g��Ȧʤ���

	int								AddBuffTime;		//�W�[Buff�ɶ�( �� )
	int								OnKillMagicID;		//�����ɲ��ͪ��k��
	char							CheckUseLua[ _MAX_SIZE64_QUEST_SCRIPT ];

	SpecailMagicEventTypeENUM		SpecialMagicEventType;
	int								OnSpecialMagicID;

	int								BuffTimeDesc_Type;
	int								BuffTimeDesc_Time;

	int								BuffSkill[ _MAX_BUFFSKILL_COUNT_ ];

	char							EndUseLua[ _MAX_SIZE64_QUEST_SCRIPT ];
	int								HitBackDist;

	int								CarryCount;			//�i���H��
	int								MusicID;			//BUFFĲ�o�I������
	int								BuffMaxLv;
	int								OnBuffTimeOutMagicIDEx;	//�����U�k�N�����ɲ��ͪ��k�N(�u�����`�ɶ���|Ĳ�o)
	int								MotionChangeType[4];	//�ʧ@��������
	int								MotionChangeID[4];		//�ʧ@����ID
	MagicSpellFlagExStruct			SettingEx;				//�k�N�]�w�X��

};
//----------------------------------------------------------------------------------------
//¾�~�ޯ�
//----------------------------------------------------------------------------------------
//¾�~�M�ݧޯ�]�w
struct  JobSkillBaseStruct
{
    int		MagicID;        //�k�N
    int		LearnLV;        //�۰ʾǷ|����
    int		KeyItemID;      //���n�����n���~
	int		NeedMagicID[2];	//�ݭn�k�N


	char	NeedMagicLv[2];	//�ݭn�k�N����
	char	SaveLvPos;		//�����x�s��m
	char	Reserve;		//(�O�d)
	
};

struct GameObjectLearnMagicStruct
{
	int		SPSkillCount;
    JobSkillBaseStruct  SPSkill[_MAX_Edit_SPSkill_COUNT_ ];            //���Ũ�۰ʾǷ|
	int		NormalSkillCount;
    JobSkillBaseStruct  NormalSkill[_MAX_Edit_NormalSkill_COUNT_ ];        
};

//----------------------------------------------------------------------------------------
//�ө����c
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
	EM_LanguageType_CN		, //²��
	EM_LanguageType_ENUS	,
	EM_LanguageType_DE		, //�w��
	EM_LanguageType_ENEU	, //
	EM_LanguageType_JP		, //���
	EM_LanguageType_KR		, //����
	EM_LanguageType_BR		, //�ڦ�
	EM_LanguageType_TR		, //�g�ը�
	EM_LanguageType_VN		, //�V�n
	EM_LanguageType_RU		, //�Xù��
//	EM_LanguageType_SG		, //�P�[�Y
	EM_LanguageType_TH		, //����
	EM_LanguageType_FR		, //�k��
	EM_LanguageType_ID		, //�L��
	EM_LanguageType_ES		, //��Z��
	EM_LanguageType_PH		, //��߻�
	EM_LanguageType_AE		, //�F�Q�a���ԧB
//	EM_LanguageType_NL		, //����
	//EM_LanguageType_RO		, //ù������
	EM_LanguageType_PL		, //�i��
	EM_LanguageType_PT		, //������y
	EM_LanguageType_SAES	, //���n���w(��Z��)
	EM_LanguageType_ENAR	, //���F�^��
	EM_LanguageType_SAPT	, //���n���w(�����)
	EM_LanguageType_IT		, //�q�j�Q
	

	EM_LanguageType_Count	,
};

enum CountryTypeENUM
{
	EM_CountryType_RW		= -1,
	EM_CountryType_TW		,
	EM_CountryType_CN		, //²��
	EM_CountryType_ENUS		,
	EM_CountryType_DE		, //�w��
	EM_CountryType_ENEU		, //
	EM_CountryType_JP		, //���
	EM_CountryType_KR		, //����
	EM_CountryType_BR		, //�ڦ�
	EM_CountryType_TR		, //�g�ը�
	EM_CountryType_VN		, //�V�n
	EM_CountryType_RU		, //�Xù��
	EM_CountryType_SG		, //�P�[�Y
	EM_CountryType_FR		, //�k��
	EM_CountryType_ID		, //�L��
	EM_CountryType_ES		, //��Z��
	EM_CountryType_NL		, //����
	EM_CountryType_PH		, //��߻�
	EM_CountryType_RO		, //ù������
	EM_CountryType_PT		, //�����
	EM_CountryType_PL		, //�i��
	EM_CountryType_TH		, //����
	EM_CountryType_AE		, //�F�Q�a���ԧB
	EM_CountryType_SA		, //�n��
	EM_CountryType_AUS		, //�D�{
	EM_CountryType_IT		, //�q�j�Q

	EM_CountryType_Count	,
};
//----------------------------------------------------------------------------------------
//�M��
//----------------------------------------------------------------------------------------
struct GameObjectSuitStruct
{
	int TotalCount;		//�M���`��

	struct 
	{
		WearEqTypeENUM  EqType[ 3 ];
		int             EqTypeValue[ 3 ];
	}SuitBase[9];		//�C���ŮM���B�~�a�Ӫ���O


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
	}SuitValue[9];		//�C���ŮM�˱a�Ӫ���O(�֭p��)

	int	SuitList[ 10 ];	//�Ҧ��M��

	//�M�˧ޯ� ��������M�i�諸�ޯ�
	int	SuitSkillID[ 4 ];
	int SuitSkillMoney;
	
};
//----------------------------------------------------------------------------------------
//�}���T
//----------------------------------------------------------------------------------------
#define _MAX_CAMP_COUNT_ 15
enum GameCampTypeENUM
{
	EM_GameCampType_Alliance	=	0	,	//�P�����i���� ( �|����)
	EM_GameCampType_Friend				,	//�͵�( �|���� ) �A �i�j�����
	EM_GameCampType_Neutrality			,	//����
	EM_GameCampType_Enemy				,	//�ĤH
};

struct GameCampStatuteStruct
{
	char	CampName[ _MAX_CAMP_COUNT_ ][ _MAX_OBJ_NAME_STR_SIZE_ ];		//�}��W��
	char	CampInfo[ _MAX_CAMP_COUNT_ ][ _MAX_CAMP_COUNT_+1 ];		//�}�礧�������Y //GameCampTypeENUM
};
//----------------------------------------------------------------------------------------
//�}�_���c
//----------------------------------------------------------------------------------------
#define _MAX_TREASURE_COUNT_	100
struct TreasureBaseInfo
{
	int		OrgID;
	int		Count;		
	int		DropCount;		//�C�������h�֭�
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
	TreasureBaseInfo Item[ _MAX_TREASURE_COUNT_ ];		//���~�`�ƶq�[�_�Ӥ@�w�� 10 �U��
	int		NeedDLv;									//(���߱���)�Ǫ����Ůt
	TreasureGambleInfo Gamble;
	char	LuaCheckScript[_MAX_SIZE64_QUEST_SCRIPT];
};
//----------------------------------------------------------------------------------------
//�k�N���X
//----------------------------------------------------------------------------------------
struct	MagicCollectFlagStruct
{
	union
	{
		int _Type;
		struct
		{
			bool    Interrupt_OnMove				: 1;	//�I�k���_ ����
			bool    Interrupt_OnAttack				: 1;	//�I�k���_ �Q����
			bool    Spell_Back		    			: 1;	//�ĤH�I��~�i�I�i
			bool    Spell_Front		    			: 1;	//�ĤH�����~�i�I�i
			bool    Spell_LookAtTarget				: 1;	//���V�ĤH�~�i�I�i
			bool	ReferenceWeapon_Bow				: 1;	//�ѷӤ} ��t �����Z�� ( �N�o�ɶ��Z��)
			bool	ReferenceWeapon_Throw			: 1;	//�ѷӷt�� ��t �����Z�� ( �N�o�ɶ��Z��)
			bool	Dash							: 1;	//�ļ�
			bool	AllColdown_Reference_Weapon		: 1;	//�@�ΧN�o �ѦҪZ����t
			bool	NoInterrupt						: 1;	//���|�Q�ޯत�_
			bool	HideCastingBar					: 1;	//����ܬI�k��
			bool	Interrupt_SpellOtherMagic		: 1;	//�I�i�䥦���k�N���_
			bool	Ignore_Obstruct					: 1;	//�������ɪ�(�d��k�N)
			bool	ReferenceWeapon_Bow_SpellTime	: 1;	//�ѷӤ} ��t �����Z�� ( �I�k�ɶ��Z��)
			bool	ReferenceWeapon_Throw_SpellTime	: 1;	//�ѷӷt�� ��t �����Z�� ( �I�k�ɶ��Z��)
			bool	IgnoreFightingLog				: 1;	//�����԰��O��
			bool	NoObjectInMagicEffectRange		: 1;	//�d�򤺤��i�H������
			bool	DescDurable						: 1;	//�l�ӭ@�[��
			bool	forceDisplayEffect				: 1;	//�]�w�S�ĥ��ݳQ���
			bool	IgnoreSpellMagicClear			: 1;	//�����I�i����
			bool	SpellStopMove					: 1;	//�I�k�����
		};
	};
};


//----------------------------------------------------------------------------------------
//�k�N���X
//----------------------------------------------------------------------------------------


enum MagicCheckFunctionENUM
{
	EM_MagicCheck_None				,//"�L"											
	EM_MagicCheck_Rand				,//"�ü�"										(r,    ) r�@�ߥN����v
	EM_MagicCheck_Self_Eq			,//"�ۤv�˳�( ���v , �˳Ƹ��X )"				�Y�ۤv�����˳�(r,�s��)
	EM_MagicCheck_Target_Eq			,//"�ؼи˳�( ���v , �˳Ƹ��X )"				�Y�ؼЦ����˳�(r,�s��)
	EM_MagicCheck_Self_EqType		,//"�ۤv�˳�����( ���v , �˳����� )"			�Y�ۤv�������Z��(r,�����s��)
	EM_MagicCheck_Target_EqType		,//"�ؼи˳�����( ���v , �˳����� )"			�Y�ؼЦ������Z��(r,�����s��)
	EM_MagicCheck_Self_Item			,//"�ۤv���~( ���v , ���~ or ���n���~ )"		�Y�ۤv��(r,���~or���n���~)
	EM_MagicCheck_Target_Item		,//"�ؼЪ��~( ���v , ���~ or ���n���~ )"		�Y�ؼЦ�(r,���~or���n���~)
	EM_MagicCheck_Self_Buff			,//"�ۤvBuff( ���v , �֦��YBuff )"				�Y�ۤv�֦��Ybuff(r,�s��)
	EM_MagicCheck_Target_Buff		,//"�ؼ�Buff( ���v , �֦��YBuff )"				�Y�ؼо֦��Ybuff(r,�s��)
	EM_MagicCheck_Self_Position		,//"�ۤv��m( ���v , ��m��O�X )"				�S���@�Τw����
	EM_MagicCheck_Target_Position	,//"�ؼЦ�m( ���v , ��m��O�X )"				�S���@�Τw����
	EM_MagicCheck_Self_Fight		,//"�ۤv�԰�( ���v , 0�D�԰�/1�԰�  )"			�ۤv���A(r,0�D�԰�/1�԰�)
	EM_MagicCheck_Target_Fight		,//"�ؼо԰�( ���v , 0�D�԰�/1�԰�  )"			�ؼЪ��A(r,0�D�԰�/1�԰�)
	EM_MagicCheck_Target_Race		,//"�ؼкر�( ���v , �ر�ID  )"					�ؼЪ��رڬO(r,�رڽs��)
	EM_MagicCheck_Self_HP			,//"�ۤvHP�C��( ���v , HP�ʤ��� )"				�ۤvHP�C��(r, �ʤ���)
	EM_MagicCheck_Time				,//"�ɶ�( ���v , �ɶ� )"						�S���@�Τw����
	EM_MagicCheck_Weather			,//"���( ���v , ��Կ�O�X )"					�S���@�Τw����
	EM_MagicCheck_Self_BuffGroup	,//"�ۤvBuff Group( ���v , �֦��YBuff�s�� )"	�ۤv���Y������buff(r, �����s��)		
	EM_MagicCheck_Target_BuffGroup	,//"�ؼ�Buff Group( ���v , �֦��YBuff�s�� )"	�ۤv���Y������buff(r, �����s��)		
	EM_MagicCheck_Self_Skill		,//"�ۤv�Ƿ|�Y�ޯ�( ���v , �k�NID )"			�ۤv�i�ϥάY�ޯ�(r,�k�N���X)
	EM_MagicCheck_BaseLv			,//"�ݨD����( ���v , LV )"						�Y���ŶW�L(r,����)

	EM_MagicCheck_MaxCount	,
};

//�I�k����
struct MagicCollectCondition
{
	MagicCheckFunctionENUM	FuncType;
	int		MagicBaseID;
	int		Arg[2];

	GameObjDbStruct* MagicBaseDB_Backup;
};


enum HitRateFuncENUM
{
	EM_HitRateFunc_Base ,				//�w��
	EM_HitRateFunc_DLV	,				//���Ůt
	EM_HitRateFunc_DLVxDLV	,			//���Ůt����
	EM_HitRateFunc_DecPerPersion	,	//�̤H�����C
	EM_HitRateFunc_Shoot			,	//�g���p��

};

#define _MAX_MAGICCOLLECT_COUNT_			4
#define _MAX_MAGICCOLLECT_GROUP_COUNT_		3

enum MagicSpellGroupTypeENUM
{
	EM_MagicSpellGroupType_Normal			,	//�����W�߭p��
	EM_MagicSpellGroupType_FirstGroupHit	,	//�Ĥ@�Ӫk�N�R���~�|�B�o�ĤG�P�ĤT�ժk�N
	EM_MagicSpellGroupType_PrvGroupHit		,	//�e�@�ժk�N�R���A�U�@�դ~�|�B�z
	EM_MagicSpellGroupType_Vampire			,	//�Ĥ@�Ӹs�խn�R�� �G�T�s�չ�ۤv�I�k
	EM_MagicSpellGroupType_Vampire1			,	//�Ĥ@�Ӹs�խn�R�� �T�s�չ�ۤv�I�k
};

enum MagicSpellSelectTypeENUM
{
	EM_MagicSpellSelectType_Circle		,//���
	EM_MagicSpellSelectType_Line1		,//���u( �ؼЭ��V  ���ĶZ��)
	EM_MagicSpellSelectType_Line2		,//���u( �I�k�� -> �ؼ� )
	EM_MagicSpellSelectType_Line3		,//���u( �I�k�̦V�ؼ�  ���ĶZ�� )
	EM_MagicSpellSelectType_Fan			,//����
	EM_MagicSpellSelectType_Lighting1	,//�s��q
	EM_MagicSpellSelectType_Lighting2	,//�s��q( �i���п� )
	EM_MagicSpellSelectType_Horizontal	,//��u
	EM_MagicSpellSelectType_Box			,//�諬
};

struct MagicJobInfoStruct
{
	Voc_ENUM	Job;			//�k�N¾�~
	bool		IsJobLimit;		//�O�_¾�~���w
};

enum MagicComboTypeENUM
{
	EM_MagicComboType_Null		= -1,	//�L��
	EM_MagicComboType_Earth		,	//�a
	EM_MagicComboType_Water     ,   //��
	EM_MagicComboType_Fire      ,	//��
	EM_MagicComboType_Wind      ,	//��
	EM_MagicComboType_Light     ,	//��
	EM_MagicComboType_Darkness  ,	//�t
	EM_MagicComboType_Start		,	//�_�ʧ�
};

// CLIENT �I�k�e�P�_����
enum MagicCollisionTypeENUM
{
	EM_MagicCollisionType_None		= 0,				// �L�k
	EM_MagicCollisionType_Line,							// �I�k�̨�ؼЪ��u����
	EM_MagicCollisionType_TargetForward,				// �ؼЪ����V
};

struct GameObjectMagicCollectStruct
{
//	int								MagicBase;      //�Ĥ@�Ūk�N( )
	int								MagicLV;        //�k�N����
	MagicorPhyENUM					EffectType;		//���z�H�� or �k�N�ޯ� or �Q�ʧޯ�

	//-------------------------------------------------------------------------------------
	//�d����
	//-------------------------------------------------------------------------------------
	GameObjectRelationENUM			TargetType;	    //���ĥؼ�
	int								AttackDistance;	//���ĶZ��
	int								EffectRange;    //���Ľd��
	GameObjectMagicEffectRangeENUM	RangeType;	    //��������
	MagicSpellSelectTypeENUM        RangeSelectType;//�d�����覡
	int                             EffectCount;    //���ĤH��
	int								DecreaseArg;	//����Ѽ�( ���d��¤O�B�z��)
	//-------------------------------------------------------------------------------------
	HitRateFuncENUM					HitRateFunc;	//�R���v
	float							HitRateArg[2];	//�R���v�p��Ѽ�
	//-------------------------------------------------------------------------------------
	MagicCostStruct					Cost[2];	    //���Ӫ��~
	MagicNeedStruct					Need[2];		//�ݨD���~
	MagicColdownBaseStruct			Coldown;		//�k�N�N�o
	MagicCollectFlagStruct			Flag;			//
	float							SpellTime;		//�I�k�ɶ�
	float							MagicAttackDelay;//�I�k��������(��)	
	int								SpellCount;		//�I�k����
	float							NextSpellTime;	//�U�����I�k�����j

	char							LUAScript[128];	//���ҳ]�w��Script �]�w �N�T�ɶ� ���� �k�N�P��
	union
	{
		MagicCollectCondition			Magic[_MAX_MAGICCOLLECT_GROUP_COUNT_][ _MAX_MAGICCOLLECT_COUNT_ ];		//���k�N���t�����Ҧ�����k�N
		MagicCollectCondition			Magic_List[_MAX_MAGICCOLLECT_GROUP_COUNT_* _MAX_MAGICCOLLECT_COUNT_ ];		//���k�N���t�����Ҧ�����k�N
	};
	
	MagicSpellGroupTypeENUM			MagicSpellGroupType;
	char							CheckUseScript[128];//�ϥ��ˬd lua

	int								MaxSkillLv;		//�i�׽m����
	float							ExpTableRate;	//�ޯ�ɯŪ��v
	bool							IsMagicAttackDelay_TargetDist;	//�B�~�W�[�ؼжZ������һݮɶ�

	MagicJobInfoStruct				JobInfo;

	MagicComboTypeENUM				ComboType;

	int								NextMagicID;	//�I�k���G��AĲ�o���k�N

	union
	{
		int					_Mode;
		struct  
		{
			bool							IsAutoAttack				: 1;		//�۰ʶi�J�԰�
			bool							IsSwitchType				: 1;		//�ä[����(�}��)
			bool							IsRideEnable				: 1;		//�M���i�ϥ�
			bool							IsShowMagicName				: 1;		//�I�k��ܦW��
			bool							IsStopAttack				: 1;		//�������
			bool							IsLockTarget				: 1;		//���V��w�I�k�ؼ�
			bool							IsPetCycleMagic				: 1;		//�d���i�`���k�N
			bool							IsAutoSpell					: 1;		//�d�����ͦ۰ʬI�i
			bool							IsIgnoreInvincible			: 1;		//�������z�P�k�N�L��(�ؼ�)
			bool							IsIgnoreSilence				: 1;		//�������z�P�k�N�L��(�ۤv)
			bool							IsWaterDisabled				: 1;		//�������i�ϥ�
			bool							IsWaterEnabled				: 1;		//�����ϥ�
			bool							IsRidePetSkill				: 1;		//�M�d���ޯ�(�y�M���I�k)
			bool							IsIgnoreTargetDead			: 1;		//�����ؼЦ��`
			bool							IsDiabledPvPRule			: 1;		//���B�z�{��ǳW�h
			bool							IsIgnoreDmgEffect			: 1;		//�k�N�ˮ`( ���p�� �Z�� )
			bool							IsFixDmgEffect				: 1;		//�k�N�ˮ`( �Z�� ��O�[�� �T�w1�� )
			bool							IsOnWagonEnabled			: 1;		//���y����i�H�ϥ�
			bool							IsDisableSpellBuffEffect	: 1;		//Buff�X�мv�T�I�k�L��( ���o ���ʬI�k �L���� )
			bool							IsShareDamage				: 1;		//��������ˮ`
		};
	};

	int								PetSkillType;			//�d���ޯ����� -1��ܬ����a���ޯ�
	float							MoveDelayTime;			//�I�k�����ʩ���
	MagicCollisionTypeENUM			CliCollisionType;
	int								CliCollisionValue;
	int								LimitLv;				//�����
	char							SelectTargetScript[64];	//�k�N�z���ؼп�ܨ㱡
	char							ShootTargetScript[64];	//�k�N�ؼп��
	int								AddSoulPoint;			//�W�[SoulPoint
	int								SuitPassiveSkill;		//�M�˳Q�ʧޯ� 
};
//----------------------------------------------------------------------------------------
enum PrivateZoneTypeENUM
{
	EM_PrivateZoneType_None				,	//�@��
	EM_PrivateZoneType_Private			,
	EM_PrivateZoneType_Party			,
	EM_PrivateZoneType_Raid				,
	EM_PrivateZoneType_Private_Party	,
};
enum PKZoneTypeENUM
{
	EM_PKZoneType_Normal	,	//�@��DPK��
	EM_PKZoneType_PK		,	//�@��PK��
};

struct MapInfoStruct
{
	int		MapID;
	char	MapName[64];
	bool	IsEnabledSave;		//�O�_�i�H�s�I
};

//----------------------------------------------------------------------------------------
struct GameObjectZoneStruct
{
	char	MapFile[64];					//�a����
	bool	IsEnabledBlockCtrl;				//�ΰ϶��]�w����d��
	int		CtrlMaxZ;
	int		CtrlMaxX;
	int		CtrlMinZ;
	int		CtrlMinX;

	bool	IsPrivateZone;
	int		BaseRoomCount;
	int		PlayRoomCount;
	PrivateZoneTypeENUM	PrivateZoneType;	//�W�߰ϰ�����	
	int		PrivateZoneLiveTime;			//�W�߰ϰ�S�H�i�H�ͦs�h�[ 


	bool	IsEnabledRevPoint;				//�j��ͦ�m
	int		RevX , RevY , RevZ;				//���ͦ�m
	int		RevZoneID;

	int		ViewBlock;						//�����϶��j�p
//	PKZoneTypeENUM	PKType;	
	int		MapID;
	int		CampStatueObjID;				//�}����

	int		MapCount;						//�p�϶��Ӽ�
	MapInfoStruct	MapInfoList[40];		//�ϧָ�T

	char	LuaInitZone[64];
	bool	IsEnabledRide;

	struct  
	{
		char	Key[64];
		char	Value[64];
	}ZoneIni[30];

	int		RoomPlayerCount;				//�ж��̦h���a��

	bool	IsWorldBattleGround;			// �O�_���@�ɾԳ�
	int		iWorldBattleGroundWorldID;		// �@�ɾԳ��A�Ⱦ��N��

	bool	IsCountryBattleGround;			// �O�_����ԾԳ�
	
	bool	IsAllowTeamJoin;				// �O�_���\�ζ��[�J
	bool	IsEnableBattleGroundQueue;		// �O�_�ѥ[�Գ��ƶ��t��

	int		IsLimitJoinLevel;				// �O�_���w�i�J����
	int		iMinJoinLevel;					// �̧C�n�J����
	int		iMaxJoinLevel;					// �̰��n�J����

	bool	IsForceGroup;					// �O�_�j��ն�

	char	LuaPreJoinQueueCheck[64];
	char	LuaAssistWorldGroupID[64];
	int		iCountryWarLinkMap[4];

	bool	IsAutoJoinEventZone;			// �O�_�۰ʥ[�J�ƥ�ƥ�

	int     MirrorInstanceType;				// ��@�ɰƥ��s��
	int     MirrorLimitLv;					// ��@�ɰƥ������
	int     MirrorLimitTime;				// ��@�ɰƥ�����ɶ�
	int		Mirror_X , Mirror_Y , Mirror_Z;	// ��@�ɭ��ͦ�m

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

	//���ͦ�m	
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
//�C���򥻪�����
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


	char*							Name;							//����W��
	char*							Name_Plural;					//�ƼƦW��

    int                             ImageID;                        //�v�����
    GameObjectImageStruct*          ImageObj_Backup;                    
    
	//�㹳���
	int								MaxHeap;			            //�̤j���|�W��
	char*							Note;							//������Ѹ��
	char*							ShortNote;						//������Ѹ��
	ObjectModeStruct				Mode;				            //���󪺰��ݩ�
	PriceTypeENUM					PricesType;						//��������
	int								SellType;						//�ӫ~����
	int								Cost;				            //���󪺻��� ( �H�C�������w�� )
	int								BuyUnit;						//�ʶR���(Client�ө��ʶR�ϥ�)
	int								ReviveTime;			            //���󪺭��ͮɶ�
	int                             Rare;                           //�}����
    float					        GenerateRate;		            //���ͳt��(
    float					        MaxWorldCount;		            //�̤j���ϰ��`�q	

    LimitStruct                     Limit;

	ItemLiveTimeTypeENUM			LiveTimeType;					//���~�ͦs�ɶ�����
	int								LiveTime;						//�����

	int								ACSearchType[3];				//AC ��檺����
	EqWearSkillStruct				ItemEqType;						//AC �j�M������

	int								SpecialMoneyCost;				//�S��f���w��, �H�C�����H�~�����p��
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
		GameCampStatuteStruct			Camp;		//�}���T
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
//��Table ��
//----------------------------------------------------------------------------------------
#define _MAX_SKILL_LEVE_	100		//�ޯ�W������

struct		LvExpRelationTable			//�g��������
{
	int 	LV;				//����
	int 	JobExp;			//¾�~�g���
	int 	SkillExp;		//�ޯ���m�g���
	int 	GatherExp;		//�Ķ��g���
	int 	RefineExp;		//�X���g���
	int 	PlotExp;		//�@���g����w
	int 	PlotMoney;		//�@���������w
	float	JobExp_LvGrowRate;	//�g�禨���v
	int		JobMagicExp;	//¾�~
	int		StandardCost;

	float	BaseMagicPower;
	float	MagicPowerGrowRate;
	int		AbilityPoint;
	int		DefPoint;
	int		HPPoint;
	int		HouseExpArg;	//�Ы�exp ��������
	float	MagicMPGrowRate;

	int		Pet_Exp;
	int		Pet_LifeSkill;
	int		PlantExp;		//�شӸg���
	float	PlantEffectPoint;
};
//////////////////////////////////////////////////////////////////////////
//��Ѫ��~���Table
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
	int	Type[5];	//�s��覡
	int	Bonus;		//�ƥ[���k�N
	int	Final;		//�����ެI�i���k�N
};

//////////////////////////////////////////////////////////////////////////
//��m�Z���[��
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
//�Ш���Ƶ��c
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
//Motion�����
struct MotionTableStruct
{
	int		ID;
	int		MotionID;
	char	IconStr[64];
};
//////////////////////////////////////////////////////////////////////////
//�оǸ��
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
	ColoringShopTypeENUM		Type;	//0 �D�� 1 �Ʀ� 2 ���� 3 �v�� 4�v�� 5�y��
	union
	{
		int Value;
		struct
		{
			unsigned char B,G,R,A;
		};
		
	}Color;
	int		ObjID;				//�ѦҪ���
	int		Cost;
};
//////////////////////////////////////////////////////////////////////////
//�@�ɦa�ϸ��
enum WorldMapITypeENUM
{
	EM_WorldMapIType_None             = 0 , //���ϥ�
	EM_WorldMapIType_World            = 1 , //�j��
	EM_WorldMapIType_Zone             = 2 , //�a��
	EM_WorldMapIType_City             = 3 , //����
	EM_WorldMapIType_Instance         = 4 , //�ƥ�
	EM_WorldMapIType_WorldInstance    = 5 , //�@�ɰƥ�
	EM_WorldMapIType_BusinessInstance = 6 , //���ʰƥ� 
	EM_WorldMapIType_Battleground     = 7 , //�Գ�
	EM_WorldMapIType_Other            = 8 , //��L 


};

struct WorldMapInfoStruct
{
	char    wdbFile[64];	//wdb�ɦW �N��@�Ӯy�Шt��
	char	MapName[64];	//Name
	int		MapID;			//ui ��ܪ��@�ɦa�ϯ���
	int 	WorldID;		//�N���PwdbFile ������P�@�@�ɥ�
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
	int NeedFlagID;		//���n���ӺX�ж}�Ҥ~��
	int	Cost;			//�R���\��n�h�ֿn��
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
	int Type;			//( 0 ��ܬ��íѮ�l 1 ��ܨ䥦�� )
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
	int		Type[4];		//����
	int		ItemObjID;	//���~ID
	int		Count;		//�ƶq
	int		Cost;		//����
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
	int		SelectCount;			//��X�Ӹ��X
	int		CombinationCount;		//�`�@���h�ֲզX
	int		SelectPrize[6][3];		//��N�Ӫ��U������������
};
//////////////////////////////////////////////////////////////////////////
struct SysKeyValueTableStruct 
{
	char  KeyStr[64];
	int	  Value;
};
//////////////////////////////////////////////////////////////////////////
//��q�����O�[����
struct PowerRateTableStruct
{
	int		Power[5];
	float	PowerRate[5];
};
//////////////////////////////////////////////////////////////////////////
//��q�����O�[����
struct RentFunctionTableStruct
{
	int		MemberType;
	int		Cost;
	float	RentDay;
	int		RentFunc[20];
};

//////////////////////////////////////////////////////////////////////////
//��[��O���v
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
//���|�X�]�w���
struct	 GuildFlagTableStruct
{
	int		ID;
	int		Type;
	char	Str[ 50 ];
};
//////////////////////////////////////////////////////////////////////////
//���|�س]
struct GuildBuildingInfoTableStruct
{
	int		ID;
	char	BuildPoint[64];
	char	TypeStr[32];
	int		Lv;
	int		OrgObjID;				//npc �ѦҪ���ID
	int		SrcBuildingID;

	GuildResourceStruct Resource;
	char	NeedTypeStr1[32];
	char	NeedLv1;
	char	NeedTypeStr2[32];
	char	NeedLv2;
	int		BlockSizeX;
	int		BlockSizeY;
	ObjectModeStruct Mode;
	int		MaintenanceCharge;		//�����O
	int		NeedGuildLv;
	int		BuildSize;
	char	IconPath[64];
	int		SortID;

	void init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

//���|�򥻫ؿv
struct GuildBaseBuildingTableStruct
{
	int		GUID;
	char	BuildPoint[32];
	int		ParentID;
	int		BuildID;
};
//////////////////////////////////////////////////////////////////////////
//���|���~���ʶR����
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
//���Ƴ]�w�a���I
struct MapPointStruct
{	
	char	KeyStr[64];
	char	wdbFile[64];
	float	X;
	float	Y;
	float	Z;
};

//���Y�k�N 
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
//�Ť��ഫ��
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
//�d����ƪ�
//////////////////////////////////////////////////////////////////////////
//��i�d���򥻰Ѽ�
struct CultivatePetBaseValue
{
	float Sweet;		//�˻e��
	float Loyal;		//���۫�
	float Grow;			//������
	float Fitness;		//������
	float Hunger;		//������
	float Tired;		//�h�ҫ�
};
//////////////////////////////////////////////////////////////////////////
//�d���i�ƪ�
struct CultivatePetBaseTableStruct
{
	int PetObjID;				//�d������
	int BasePetObjID;			//��Ӫ��d������
	int	PetType[2];	
	int NewSkill[3];

	int Evolve_RarePoint;		//�i�ƻݨD�����}���I��
	int Evolve_GrowPoint;		//�i�ƻݨD�i�|�I��

	CultivatePetBaseValue Fix;	//�ƭȷL�ռv�T
};
//////////////////////////////////////////////////////////////////////////
//�d���ݩʲ��ͪk�NBuff�� 
struct CultivatePetValueEffectTableStruct
{
	int	MagicBuffID;
	CultivatePetBaseValue LimitLow;
	CultivatePetBaseValue LimitHi;
};
//////////////////////////////////////////////////////////////////////////
//�d���ƥ�p��]�w( ���u , ���A , ���B , �V�m , �ײ� )�P�v�T���ƭ�(table)
struct CultivatePetEventTableStruct
{
	int		ActionType[2];				//���ʤ���
	char	KeyStr[64];					//�ƥ󤺮e
	char	LuaScript[64];				//�ƥ���檺�@��
	struct  
	{
		int		PetType[2];			//�d������
		int		KeyItem;			//���n���~
		int		Character;			//�ө�
		CultivatePetBaseValue Low;
		CultivatePetBaseValue Hi;

	}Limit;
	CultivatePetBaseValue Effect;
	int		Money;						//�ݨD or ��o����
};
//////////////////////////////////////////////////////////////////////////
//�d�����ܪ�
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
//�d��������
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
//�d���򥻪�
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
//�d����Ų
struct PetCollectionTableStruct
{
	int GUID;
	int ObjID;
};
//�d���ޯ�
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
		int Lock;			//�M�ݬYPetType,�����~��
	}Limit;

	int MagicID;
	int	PowerLv;
	int SkillPoint;		//�ݨD�ޯ��I��

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

//�d���ͬ��ޯ�
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
//�ش� �I�θ��
struct PlantGrowActionTableStruct
{
	int ID;
	int	Type;
	int GrowRate;
	int Water;			//0�_ 1 �i 
	int Topdress;
	int MagicWater;
};
*/
//////////////////////////////////////////////////////////////////////////
//�ش� �������
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
//�u�|��npc ���N�B�z
struct GuildHouseNpcReplaceTableStruct
{
	int Type;
	int OrgNpcID;
	int NpcID;
};

//�u�|��npc ���N�B�z����
struct GuildHouseNpcReplaceCostTableStruct
{
	int Type;
	int GuildLv;
	GuildResourceStruct	Cost;
};

//////////////////////////////////////////////////////////////////////////
//�ݩʽ�ժ�
struct GambleItemStateTableStruct
{
	int	GambleObjID;
	int FirstTimeCost;
	int ContinueCost;
	int MaxLv;
	int MinLv;
};
//////////////////////////////////////////////////////////////////////////
// �k���ƥ�
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
	EM_ServantCondition_Master_MasterBoy	,	//�k�D�H
	EM_ServantCondition_Master_MasterGirl	,	//�k�D�H
	EM_ServantCondition_Master_Boy			,	//�k�ȤH
	EM_ServantCondition_Master_Girl			,	//�k�ȤH
	EM_ServantCondition_Master_Master		,	//�D�H
	EM_ServantCondition_Master_Visitor		,	//�ȤH
	EM_ServantCondition_Master_All			,	//����
};


//�k���ƥ��
struct ServantEventTableStruct
{
	int	GUID;					//�ƥ󸹽X
	int	EventType[2];			//�ƥ�����	
	union
	{
		int	Condition[3];			//����
		struct
		{
			ServantCondition_Servant_ENUM	Servant;
			ServantCondition_Master_ENUM	Master;
			int		Character;					//�ө�
		}Check;
	};

	int Rate;					//�o�;��v
	int MinValue[8];			//�̧C�ƭȻݨD
	int	MaxValue[8];			//�̰��ƭȻݨD
	int MotionID;				//�ʧ@
	char TalkStr[128];			//����
	char Voice[128];			//�n����
	char LuaScript[128];		//Server Lua �@��
	char LuaCheckScript[128];	//Server Lua �ˬd �O�_�i�H����
};
//////////////////////////////////////////////////////////////////////////
//���Τk��
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
//�Ҥ� �}���פW�ɧI�����~��
struct LifeSkillRareExStruct
{
	int ItemID;
	int	RareItemID[3];
};
//////////////////////////////////////////////////////////////////////////
//�J��t�Φ@��ճ]�w��
struct RuneSystemStruct
{
	int GUID;
	int MagicCol;		//�@��ĪG
	int MagicColEx;		//�j�Ʀ@��ĪG
	int TriggerCount;
	int RuneColor[6];
};
//////////////////////////////////////////////////////////////////////////
struct LoadTableStruct
{
	int GUID;
	union
	{
		char					Data[1];							//��ƶ}�l��m
		FixFightArgumentStruct  FixTB;								//�T�w�ѳN
		FightArgumentStruct     ArgTB;								//�ر� ¾�~�Ѽƪ�

		int     ExpTB[_MAX_VOCATION_COUNT_];						//¾�~�g��Ȫ�
		int     SkillValueBase[ _MAX_SKILLVALUE_BASETYPE ];			//�ޯ�Ȫ�

		struct
		{
			int     JobSkillValue[ _MAX_VOCATION_COUNT_ ];			//�U¾�~�ޯ઺���m ( �O������ S+ S S- A+ A A- ...)
		};

		EqWearSkillStruct JobWearSkill[ _MAX_VOCATION_COUNT_ ];		//�U¾�~�i�諸����

		struct
		{
			int		WeaponBaseDelayTime[ _MAX_SKILLVALUE_TYPE ];	//�U�تZ�����򥻩���ɶ�
			float	WeaponBaseDmg[ _MAX_SKILLVALUE_TYPE ];			//�U�تZ�����򥻶ˮ`��( �n���W�ӵ���GM���ˮ` )
			int		WeaponBaseRand[ _MAX_SKILLVALUE_TYPE ];
			float	WeaponBaseMAtk[ _MAX_SKILLVALUE_TYPE ];
			float	WeaponBaseCostRate[ _MAX_SKILLVALUE_TYPE ];
			
		};

		int		BaseMagicList[ EM_BaseMagic_MaxCount ];				//�򥻪��į�k�N  ���_�w �L��

		ResistArgumentStruct	ResistArg;							//�ܩʰѼ�

		int		RefineExp[ _MAX_SKILL_LEVE_];						//�һs�g��Ȫ�(�n�ɤU�@�Ū��g���)


		LvExpRelationTable	AllExp;									//�g��������

//		EqRefinePowerStruct	EqRefine;								//��m�Z���[��

		CreateRoleInfoTableStruct CreateRole;

//		LvDissolutionTable	Dissolution;
		ComboTable			Combo;

		MotionTableStruct	Motion;

		TeachTableStruct	Teach;									//�оǸ��

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
