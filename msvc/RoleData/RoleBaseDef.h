#ifndef	__ROLEBASEDEF_H_
#define __ROLEBASEDEF_H_
#pragma	warning (disable:4786)
#pragma warning (disable:4949)
//#pragma warning (disable:4807)
#include "RoleBaseInc.h"
#include <time.h>
#include "MyTypeDef.h"
#include "SmallObj/StaticString.h"
#include "SmallObj/StaticFlag.h"
/*
#ifndef _CLIENT
#include "../NetWalker_Member/NetWakerPGEnum.h"
#else
#include "../NetWaker_Member/NetWakerPGEnum.h"
#endif
*/
#pragma unmanaged

#define DF_DAILY_RESET_TIME			6

#define _DEF_BASE_CLOCL_UNIT_		10          //基本處理的時間
#define	_MAX_LOCALOBJECT_COUNT_		6000        //區域最多物件總量
#define	_MAX_EQ_REFINE_LEVE_		10			//精鍊最高等級
#define	DEF_MAX_DESTROY_ITEM_LOG_COUNT 10		

//帳號最大Size
#define _MAX_ACCOUNT_SIZE_			64			//帳號長度
#define _MAX_CREATETIME_SIZE_		28			//時間字串長度
#define _MAX_NAMERECORD_SIZE_		_MAX_OBJ_NAME_STR_SIZE_			//角色名稱長度

#define _MAX_DESTORYOBJ_REASON		128

#define _MAX_ROLE_COUNT_			5			//角色數量
#define _MAX_ZONENAME_SIZE_			32			//角色名稱長度
#define	_MAX_LUA_FUNTIONNAMESIZE_	32			//劇情名稱最大字串
#define	_MAX_LUA_FUN_ARG_SIZE_		64			//劇情名稱帶參數最大字串
#define _MAX_HATELIST_SIZE_			50			//最大可紀錄仇恨名單
#define _MAX_TRADE_ITEM_COUNT_		25
#define _MAX_FRIENDLIST_NOTE_		300			//好友名單註解
#define _MAX_FRIENDLIST_FAMILY_COUNT_		20	//特殊關係的好友
#define _MAX_FRIENDLIST_COUNT_		100			//好友最大量
#define _MAX_FRIENDLIST_ALL_COUNT_  (_MAX_FRIENDLIST_COUNT_+_MAX_BAD_FRIENDLIST_COUNT_ +_MAX_HATE_PLAYER_LIST_COUNT_)
#define _MAX_BAD_FRIENDLIST_COUNT_	50			//好友最大量
#define _MAX_HATE_PLAYER_LIST_COUNT_	20		//愁人榜最大量
#define _MAX_FRIENDLIST_GROUP_COUNT_	10
#define _MAX_FAMOUS_COUNT_			10			//名生種類
#define _MAX_REGISTER_COUNT_		10			//最多劇情暫存值數量
#define _MAX_LOCATION_SAVE_COUNT_	50			//最多玩家可記錄的傳送位置

#define _MAX_REALTIME_FLAG_			100
#define _MAX_PLAYTIME_FLAG_			100
#define _MAX_LUA_VALUES_FLAG_		1000

#define	_MAX_BASE_ARG_COUNT_		30			//最多基本參數各數
#define	_MAX_EFFECTMAGIC_COUNT_		16			//身上最多有多少輔助法術

#define _MAX_MONEY_COUNT_           999999999	//金錢上限
#define _MAX_BONUSMONEY_COUNT_      99999		//金錢上限
#define Def_MONEY_OBJID_            200000      //金錢物件號碼

#define _MAX_Honor_COIN_COUNT_			25000		//榮譽點數
#define _MAX_DuelistReward_COIN_COUNT_	20000		//勇士勳章
#define _MAX_Relics_COIN_COUNT_			10000		//古代遺物
#define _MAX_PhiriusShell_COIN_COUNT_	1000		//必爾汀圓貝
#define _MAX_EnergyJusticeCoin_COUNT_	10000



#define _BASE_ATTACK_SPEED_         40			//基本攻擊速度
#define _BASE_MOVE_SPEED_           50			//基本移動速度

#define _MAX_ROLE_TOUCH_RANGE_		40			// 所有系統觸碰最大範圍
#define _MAX_ROLE_TOUCH_MAXRANGE_	65			// 觸發劇情後, 脫離距離

#define	_TIME_CHECKCASTEVENT_		100			// 檢查點擊處理的時間間隔
#define	_TIME_CLICKTOGETITEM		5000		// 點擊任務物品所需要的時間
#define	_TIME_QUEST_CLICKTOGETITEM	5000		// 點擊任務物品所需要的時間
#define _TIME_DELAYPATROL			30000		// 點擊巡邏 NPC 延遲時間


#define _MAX_PARTY_COUNT_			36			//隊伍人數上限
#define _MAX_PARTY_COUNT_PARTY_		6
#define _MAX_PARTY_COUNT_RAID_		36

#define _MAX_PARTY_SHARE_RANGE_		1000		//隊伍分享範圍

#define _MAX_SHARE_COLDOWN_COUNT_	30			//共用coldonw上限
#define _MAX_SPEAKDETAIL_SIZE_		1024		//對話系統本文最多字數
#define _MAX_SPEAKOPTION_SIZE_		256			//對話系統選項最多字數

#ifdef _LOCAL_SERVER_
	#define _DEF_ATTACK_EVENT_EFFECT_TIME_	4000	//攻擊事件有效時間
#else
	#define _DEF_ATTACK_EVENT_EFFECT_TIME_	3000	//攻擊事件有效時間
#endif

#define _MAX_MOVE_SENDALL_COUNT_	20			//少於多少人全送
#define _DEF_NPC_FIGHT_RANGE_		400
#define _DEF_ZONE_BASE_COUNT_		1000
#define _DEF_MAX_HOUSE_FURNITURE	500


#define _DEF_GUIDHOUSEITEM_MAX_PAGE_		100		//公會倉庫租用頁數
#define _DEF_GUIDHOUSEITEM_MAX_PAGEITEM_	100		//公會倉庫租用頁數
#define _DEF_GUIDHOUSE_MAX_BUILDING_COUNT_	100		//公會建築最多個數

#define _DEF_GUIDHOUSEITEM_MAX_FURNITURE_	500		//公會屋最多有多少裝飾家俱
#define _DEF_MAX_DBID_COUNT_		10000000		//DBID最大個數
#define _MAX_CYCLE_MAGIC_COUNT_		5

#define _MAX_PK_DEAD_SAVE_COUNT_	3

#define _MAX_BuffTimeDesc_COUNT_	20

#define _DEF_MAX_PET_TYPE_			48				//最多寵物有幾個類型
#define _MEMORY_CHECK_VALUE_		1234567890
#define MAX_TALK_CONTENT			512
#define _ACCOUNT_FLAG_COUNT_		1024
#define _MAX_CLIENT_SETTING_SIZE_	20	//特殊關係的好友
#define _MAX_BACKUP_EQ_SET_COUNT_	5

#define _MAX_PET_CARD_COUNT_		256
//-------------------------------------------------------------------------------------
//		 各種裝備欄位的上限數量
//-------------------------------------------------------------------------------------
#define _MAX_BODY_COUNT_			240			//身上物品最多有多少
#define _MAX_BODY_EX_COUNT_			50			//商城包包數量
#define _MAX_BODY_MAGIC_BOX_COUNT_	10			//月光寶盒
#define _MAX_BODY_BEGIN_POS_		(_MAX_BODY_EX_COUNT_+_MAX_BODY_MAGIC_BOX_COUNT_)

#define _MAX_BANK_COUNT_			300			//身上物品最多有多少
#define _MAX_GIVESYSTEM_COUNT_		10			//給予系統最多有多少
#define _MAX_TEMP_COUNT_			20			//暫存區域最多有多少(當系統給予時所儲存的地方)
#define _MAX_BUFF_COUNT_			50			//最多可以上的Buff數量
#define _MAX_REFINE_BUFF_COUNT_		20			//生產Coldown最大值設定		
#define _MAX_RENT_COUNT_			50			//最大租用的種類

#define _MAX_TITLE_FLAG_COUNT_		2048	
#define _MAX_HOUSES_SHOPFUNCTION_COUNT_	256	
#define _MAX_FLAG_COUNT_			16000
#define _MAX_CARD_COUNT_			2048
#define _MAX_CLIENT_FLAG_COUNT_		256
#define _MAX_CLIENT_DATA_SIZE_		256

#define DF_SKILLID_ATTACK				540000		// 攻擊
#define DF_SKILLID_PORTOL				540001		// 回城術
#define DF_SKILLID_DISENCHANT			540002		// 分解
#define DF_SKILLID_PK					540003		// PK
#define DF_SKILLID_BEGINNERPORTOL_BEGIN	540190		// 傳回新手村開始檢查編號
#define DF_SKILLID_BEGINNERPORTOL_END	540199		// 傳回新手村開始檢查編號

#define _DEL_ROLE_RESERVE_TIME_		(24*60*60)	//刪角保留時間

#define	_DEF_ITEM_ABILITY_DELTA_	500000

#define	Def_AccountMoneyLockTime_Max_Count_ 30
#define	_DEF_MAX_COOL_SUIT_COUNT_	10
#define	_DEF_MAX_COOL_CLOTH_COUNT_	500

#define _DEF_MAX_PET_EXBAG_COUNT_	100
#define _DEF_MAX_HORSE_EXBAG_COUNT_	100

#define DEF_MAX_WEEK_INS_TYPE				5
#define DEF_MAX_WEEK_INS_TYPE_DAY_COUNT		3
//-------------------------------------------------------------------------------------
//		 各種裝備欄位的上限數量
//-------------------------------------------------------------------------------------
#define DF_QUESTDAILY_MAXGROUP		20

//-----------------------------------------------------------------------------------------
#define _DEF_MAX_MONEY_VENTOR_COUNT_	50
//#define _DEF_MAX_BOT_COUNT_				20
//-----------------------------------------------------------------------------------------
//檢查是否可以置換此項裝備
//-----------------------------------------------------------------------------------------
enum CheckSetEQResultENUM
{
	EM_CheckSetEQResult_OK		,
	EM_CheckSetEQResult_OKEx	,	//主副手特殊處理
	EM_CheckSetEQResult_Failed	,
	EM_CheckSetEQResult_Failed_ItemUnique	,
};
//-----------------------------------------------------------------------------------------
//數值名稱列舉
//-----------------------------------------------------------------------------------------
enum	RoleValueName_ENUM
{
	EM_RoleValue_HP	= 0		    ,
	EM_RoleValue_MP			    ,
	EM_RoleValue_RACE			,
	EM_RoleValue_VOC  		    ,
	EM_RoleValue_SEX			,
	EM_RoleValue_EXP			,
	EM_RoleValue_LV			    ,

	EM_RoleValue_X			    ,
	EM_RoleValue_Y			    ,
	EM_RoleValue_Z			    ,
	EM_RoleValue_Dir		    ,

    EM_RoleValue_STR            ,
    EM_RoleValue_STA            ,
    EM_RoleValue_INT            ,
    EM_RoleValue_MND            ,
    EM_RoleValue_AGI            ,

    EM_RoleValue_Point          ,
    EM_RoleValue_SkillPoint     ,

    EM_RoleValue_SP			    ,
	EM_RoleValue_SP_Sub		    ,    

    EM_RoleValue_MaxHP		    ,
    EM_RoleValue_MaxMP		    ,
    EM_RoleValue_MaxSP		    ,
	EM_RoleValue_MaxSP_Sub	    ,

    EM_RoleValue_VOC_SUB	    ,
    EM_RoleValue_LV_SUB		    ,

    EM_RoleValue_ThisLVExp	    ,
	EM_RoleValue_LiveTime	    ,

	EM_RoleValue_BodyCount		,		//身體欄位數量
	EM_RoleValue_BankCount		,		//銀行欄位數量
	EM_RoleValue_RoomID			,
	EM_RoleValue_TpExp			,		//技能經驗值點數


	EM_RoleValue_Money			,		// 身上錢數量
	EM_RoleValue_Money_Account	,		// 身上錢數量

	EM_RoleValue_KillRate		,		//打怪速度
	EM_RoleValue_StomachPoint	,		//設定飽食度

	EM_RoleValue_SysFlag		,

	EM_RoleValue_AddExp			,		//額外增加經驗值
	EM_RoleValue_AddTP			,		//額外增加tp
	EM_RoleValue_PlayTimeQuota	,		//防沉迷
	EM_RoleValue_GoodEvil		,		//善惡值
	EM_RoleValue_VocCount		,		//職業數量上限
	EM_RoleValue_BoxEnergy		,		//融合箱能量
	EM_RoleValue_MedalCount		,		//教導點數
	EM_RoleValue_BonusMoney		,		//紅利幣
	EM_RoleValue_MaxLv			,		//等級上限

	EM_RoleValue_DebtExp		,		//經驗值負債
	EM_RoleValue_DebtTP			,		//TP負債

	EM_RoleValue_FinStr			,		//計算後STR
	EM_RoleValue_FinSta			,		//計算後STA
	EM_RoleValue_FinInt			,		//計算後INT
	EM_RoleValue_FinMnd			,		//計算後MND
	EM_RoleValue_FinAgi			,		//計算後AGI

	EM_RoleValue_Honor			,		//榮譽
	EM_RoleValue_MaxPlantCount	,		//最多可種植的數量
	EM_RoleValue_AttackDelay	,		//攻擊延遲
	EM_RoleValue_TotalTpExp		,		//TP上限值

	EM_RoleValue_CliOk_X	    ,		//確認可走的點
	EM_RoleValue_CliOk_Y	    ,		//確認可走的點
	EM_RoleValue_CliOk_Z	    ,		//確認可走的點

	EM_RoleValue_VIP_Type		,		//VIP Type
	EM_RoleValue_VIP_Flag		,
	EM_RoleValue_UnTrust_Flag	,		//玩家信任機制(有值表示不信任)

	EM_RoleValue_Money_AccountLock	,	//鎖定的帳號幣數量
	EM_RoleValue_TitleID			,	//目前頭銜的ID
	EM_RoleValue_TitleSys_Famous	,	//頭銜系統名聲
	EM_RoleValue_TitleSys_Lv	  	,	//頭銜系統等級
	EM_RoleValue_TitleSys_Exp	  	,	//頭銜系統經驗值
	EM_RoleValue_TitleSys_TitleID1	,	//頭銜系統裝備頭銜
	EM_RoleValue_TitleSys_TitleID2	,	//頭銜系統裝備頭銜
	EM_RoleValue_TitleSys_TitleID3	,	//頭銜系統裝備頭銜
	EM_RoleValue_TitleSys_TitleID4	,	//頭銜系統裝備頭銜
	EM_RoleValue_TitleSys_TitleID5	,	//頭銜系統裝備頭銜
	EM_RoleValue_SoulPoint			,	//靈魂值
	EM_RoleValue_MoveDelay			,	//move延遲
	EM_RoleValue_SlotMachineFreeCount,	//角子老虎免費次數
	EM_RoleValue_DuelistReward		,	//勇士勳章
	EM_RoleValue_TrialBadgeCoin		,	//試煉徽章
	EM_RoleValue_RelicsCoin			,	//古代遺物
	EM_RoleValue_DreamlandCoin		,	//夢境先遣印記
	EM_RoleValue_PhiriusShellCoin	,	//必爾汀圓貝
	EM_RoleValue_EnergyJusticeCoin	,	//正義能量
	EM_RoleValue_ProofLegendCoin	,	//傳說之證
	EM_RoleValue_VenderCount		,	//幣商回報權值
	EM_RoleValue_LockHP				,	//lockHP
	EM_RoleValue_WeekResetCount		,
	EM_RoleValue_MirrorCoin			,	//鏡幻徽印

	EM_RoleValue_Famous         = 400,  

	EM_RoleValue_Register       = 450,  

	
    EM_RoleValue_KeyItemOn      = 600,
	EM_RoleValue_KeyItemOff     ,

	//EM_RoleValue_SkillValue		= 700 , 

	EM_RoleValue_Skill_Unarmed			= 700,	// Unarmed空手
	EM_RoleValue_Skill_Blade			,		// 劍
	EM_RoleValue_Skill_Dagger			,		// 匕首
	EM_RoleValue_Skill_Wand				,		// 權杖
	EM_RoleValue_Skill_Axe				,		// 斧
	EM_RoleValue_Skill_Bludgeon			,		// 鎚棍棒
	EM_RoleValue_Skill_Claymore			,		// 雙手劍
	EM_RoleValue_Skill_Staff			,		// 杖
	EM_RoleValue_Skill_2H_Axe			,		// 雙手斧
	EM_RoleValue_Skill_2H_Hammer		,		// 雙手鎚
	EM_RoleValue_Skill_Polearm			,		// 槍(長矛)
	EM_RoleValue_Skill_Bow				,		// 遠程武器 弓
	EM_RoleValue_Skill_CossBow			,		// 遠程武器 十字弓
	EM_RoleValue_Skill_Gun				,		// 遠程武器 槍
	EM_RoleValue_Skill_Define			,		// 防禦

	EM_RoleValue_Skill_BlackSmith		,		// 打鐵
	EM_RoleValue_Skill_Carpenter		,		// 木工
	EM_RoleValue_Skill_MakeArmor		,		// 製甲
	EM_RoleValue_Skill_Tailor			,		// 裁縫
	EM_RoleValue_Skill_Cook				,		// 烹飪
	EM_RoleValue_Skill_Alchemy			,		// 煉金

	EM_RoleValue_Skill_Mining			,		// 挖礦
	EM_RoleValue_Skill_Lumbering		,		// 砍材
	EM_RoleValue_Skill_Herblism			,		// 採藥
	EM_RoleValue_Skill_Fishing			,		// 釣魚
	EM_RoleValue_Skill_Plant			,		// 種植
	EM_RoleValue_Skill_CatchPet			,		// 寵物補捉

	EM_RoleValue_Skill_Fin_Unarmed		= 750,	// Unarmed空手
	EM_RoleValue_Skill_Fin_Blade		,		// 劍
	EM_RoleValue_Skill_Fin_Dagger		,		// 匕首
	EM_RoleValue_Skill_Fin_Wand			,		// 權杖
	EM_RoleValue_Skill_Fin_Axe			,		// 斧
	EM_RoleValue_Skill_Fin_Bludgeon		,		// 鎚棍棒
	EM_RoleValue_Skill_Fin_Claymore		,		// 雙手劍
	EM_RoleValue_Skill_Fin_Staff		,		// 杖
	EM_RoleValue_Skill_Fin_2H_Axe		,		// 雙手斧
	EM_RoleValue_Skill_Fin_2H_Hammer	,		// 雙手鎚
	EM_RoleValue_Skill_Fin_Polearm		,		// 槍(長矛)
	EM_RoleValue_Skill_Fin_Bow			,		// 遠程武器 弓
	EM_RoleValue_Skill_Fin_CossBow		,		// 遠程武器 十字弓
	EM_RoleValue_Skill_Fin_Gun			,		// 遠程武器 槍
	EM_RoleValue_Skill_Fin_Define		,		// 防禦

	EM_RoleValue_Skill_Fin_BlackSmith	,		// 打鐵
	EM_RoleValue_Skill_Fin_Carpenter	,		// 木工
	EM_RoleValue_Skill_Fin_MakeArmor	,		// 製甲
	EM_RoleValue_Skill_Fin_Tailor		,		// 裁縫
	EM_RoleValue_Skill_Fin_Cook			,		// 烹飪
	EM_RoleValue_Skill_Fin_Alchemy		,		// 煉金

	EM_RoleValue_Skill_Fin_Mining		,		// 挖礦
	EM_RoleValue_Skill_Fin_Lumbering	,		// 砍材
	EM_RoleValue_Skill_Fin_Herblism		,		// 採藥
	EM_RoleValue_Skill_Fin_Fishing		,		// 釣魚
	EM_RoleValue_Skill_Fin_Plant		,		// 種植
	EM_RoleValue_Skill_Fin_CatchPet		,		// 寵物補捉

	EM_RoleValue_SkillMax_Unarmed		= 850,		// Unarmed空手
	EM_RoleValue_SkillMax_Blade			,		// 劍
	EM_RoleValue_SkillMax_Dagger		,		// 匕首
	EM_RoleValue_SkillMax_Wand			,		// 權杖
	EM_RoleValue_SkillMax_Axe			,		// 斧
	EM_RoleValue_SkillMax_Bludgeon		,		// 鎚棍棒
	EM_RoleValue_SkillMax_Claymore		,		// 雙手劍
	EM_RoleValue_SkillMax_Staff			,		// 杖
	EM_RoleValue_SkillMax_2H_Axe		,		// 雙手斧
	EM_RoleValue_SkillMax_2H_Hammer		,		// 雙手鎚
	EM_RoleValue_SkillMax_Polearm		,		// 槍(長矛)
	EM_RoleValue_SkillMax_Bow			,		// 遠程武器 弓
	EM_RoleValue_SkillMax_CossBow		,		// 遠程武器 十字弓
	EM_RoleValue_SkillMax_Gun			,		// 遠程武器 槍
	EM_RoleValue_SkillMax_Define		,		// 防禦

	EM_RoleValue_SkillMax_BlackSmith	,		// 打鐵
	EM_RoleValue_SkillMax_Carpenter		,		// 木工
	EM_RoleValue_SkillMax_MakeArmor		,		// 製甲
	EM_RoleValue_SkillMax_Tailor		,		// 裁縫
	EM_RoleValue_SkillMax_Cook			,		// 烹飪
	EM_RoleValue_SkillMax_Alchemy		,		// 煉金

	EM_RoleValue_SkillMax_Mining		,		// 挖礦
	EM_RoleValue_SkillMax_Lumbering		,		// 砍材
	EM_RoleValue_SkillMax_Herblism		,		// 採藥
	EM_RoleValue_SkillMax_Fishing		,		// 釣魚
	EM_RoleValue_SkillMax_Plant			,		// 種植
	EM_RoleValue_SkillMax_CatchPet		,		// 寵物補捉


	EM_RoleValue_VOCLV_GM				= 900,	// 職業等級 ( 依照 Voc_ENUM 900 ( GM ) + 16 ) 
	EM_RoleValue_VOCLV_Warrior		,
	EM_RoleValue_VOCLV_Ranger		,
	EM_RoleValue_VOCLV_Rogue		,
	EM_RoleValue_VOCLV_Wizard		,
	EM_RoleValue_VOCLV_Priest		,
	EM_RoleValue_VOCLV_Knight		,
	EM_RoleValue_VOCLV_RuneDancer	,
	EM_RoleValue_VOCLV_Druid		,

	EM_RoleValue_ClinetSetting		= 950,			//Client 端設定數值資料

	EM_RoleValue_FamilyFriendListLv_Pos		= 1000,	//好友等級( 共 20 個 )

	EM_RoleValue_LuaMagicID					= 1100,	//好友等級( 共 20 個 )

	EM_RoleValue_TimeFlag					= 1200,	//200個時間旗標

	EM_RoleValue_WeekInstnaces				= 1500, //

	EM_RoleValue_MagicPowerLv_SP			= 2000,
	EM_RoleValue_MagicPowerLv_Normal		= 2200,			
	EM_RoleValue_MagicPowerLv_SubJob		= 2250,

	EM_RoleValue_MagicID_SP					= 2300,
	EM_RoleValue_MagicID_Normal				= 2500,		
	EM_RoleValue_MagicID_SubJob				= 2550,

	EM_RoleValue_CultivatePet_Money			= 2998,
	EM_RoleValue_CultivatePet_NextMergeResetTime = 2999,
	//---------------------------------------------------------------------------------------
	//寵物資料( 3000 - 4000 ) 每個寵物資料偏100 號
	EM_RoleValue_CultivatePet_Value			= 3000	,	//	
	EM_RoleValue_LuaValueFlag				= 4000,
    //---------------------------------------------------------------------------------------
	EM_RoleValue_Coldown					= 6000, //冷卻時間 1+200+15+30 = 246個
	//---------------------------------------------------------------------------------------
    //劇情需要的數值        
    //---------------------------------------------------------------------------------------
    EM_RoleValue_IsNPC          = 7000,
    EM_RoleValue_IsPlayer       ,
    EM_RoleValue_OrgID          ,
	EM_RoleValue_AttackTargetID ,
	EM_RoleValue_PID			,
	EM_RoleValue_IsWalk			,
	EM_RoleValue_MaxHit			,		// 目前對本身造成最大傷害的人
	EM_RoleValue_DBID			,			
	EM_RoleValue_IsDead			,
	EM_RoleValue_GroupID		,
	EM_RoleValue_GuildID		,
	EM_RoleValue_ZoneID			,		//所在區域（去分流）
	EM_RoleValue_HouseDBID		,		//房屋號碼
	EM_RoleValue_PetID			,		//寵物號碼
	EM_RoleValue_IsAttackMode	,
	EM_RoleValue_IsUnholster	,		//client 戰鬥狀態
	EM_RoleValue_SpellMagicID	,		//正在施的法術
	EM_RoleValue_CampID			,		//陣營號碼(read only )
	EM_RoleValue_OwnerDBID		,		//主人的DBID

	EM_RoleValue_OwnerGUID				,	//主人的物件
	EM_RoleValue_DodgeState				,	//(最近有)閃避
	EM_RoleValue_MissState				,	//(最近有)Miss
	EM_RoleValue_ParryState				,	//(最近有)Parry
	EM_RoleValue_BeParryState			,	//(最近有)被Parry
	EM_RoleValue_BeDodgeState			,	//(最近有)被閃避
	EM_RoleValue_CritialState			,	//(最近有)物理Critial
	EM_RoleValue_BeCritialState			,	//(最近有)被物理Critial
	EM_RoleValue_MagicCritialState		,	//(最近有)法術Critial
	EM_RoleValue_BeMagicCritialState	,	//(最近有)被法術Critial
	EM_RoleValue_ShieldBlockState		,	//(最近有)盾檔
	EM_RoleValue_BeShieldBlockState		,	//(最近有)被盾檔	

	EM_RoleValue_LastDHp				,	//最後一次HP變化量
	EM_RoleValue_LastDHpTarget			,	//最後一次改變者
	EM_RoleValue_VisitHouseDBID			,	//參觀的DBID

	EM_RoleValue_PetID_Cultivate,		//寵物號碼	

	EM_RoleValue_Fin_Phy_ATK	,		//攻擊力
	EM_RoleValue_Fin_Phy_Dmg	,		//主手傷害
	EM_RoleValue_Fin_Phy_Def	,		//防禦力

	EM_RoleValue_Fin_Mag_ATK	,		//魔攻
	EM_RoleValue_Fin_Mag_Dmg	,		//魔法傷害
	EM_RoleValue_Fin_Mag_Def	,		//魔法防禦

	EM_RoleValue_Fin_Phy_DodgeLv,		//閃避等級
	EM_RoleValue_Fin_Phy_HitLv	,		//物理命中等級
	EM_RoleValue_Fin_Mag_HitLv	,		//魔法命中等級

	EM_RoleValue_Fin_Phy_ParryRate,		//格檔率

	EM_RoleValue_Fin_Phy_CritRate,		//物理致命一擊率
	EM_RoleValue_Fin_Phy_CritResistRate,//抗物理致命一擊率
	EM_RoleValue_Fin_Phy_CritPower,		//物理致命一擊威力

	EM_RoleValue_Fin_Mag_CritRate,		//法術致命一擊率
	EM_RoleValue_Fin_Mag_CritResistRate,//抗法術致命一擊率
	EM_RoleValue_Fin_Mag_CritPower,		//法術致命一擊威力

	EM_RoleValue_CliState		,		//取得目前角色的Cli端狀態

	EM_RoleValue_AroundPlayer	,		//周圍玩家角色數量
	EM_RoleValue_NpcOnMove		,		//npc 是否正在移動

	EM_RoleValue_IncursivePoint	,		//世界副本入侵事件績分
	EM_RoleValue_RecalculateAll	,		//角色資料重新計算

	EM_RoleValue_PassengerAttackable ,	//可攻擊乘客
	EM_RoleValue_AttachObjGUID	,		//載具物件ID
	EM_RoleValue_BeginAtkDBID 	,		//取得第一個殺怪的人
	EM_RoleValue_DualTargetDBID	,		//取得比試的目標
	EM_RoleValue_CastingType	,		//取得是否有Client使用條
	EM_RoleValue_SetNPCAttackRange,		//設定NPC攻擊距離

	EM_RoleValue_LastAttackType			,	//(全域)最後一次 攻擊類型(OnAttackTypeENUM)
	EM_RoleValue_LastAttackOwnerID		,	//(全域)最後一次 被攻擊者
	EM_RoleValue_LastAttackTargetID		,	//(全域)最後一次 攻擊者
	EM_RoleValue_LastAttackMagColID		,	//(全域)最後一次 攻擊法術集合
	EM_RoleValue_LastAttackMagBaseID	,	//(全域)最後一次 攻擊法術基本
	EM_RoleValue_LastAttackDamage		,	//(全域)最後一次 攻擊傷害量
	EM_RoleValue_LastAttackDmgType		,	//(全域)最後一次 攻擊傷害類型(ATTACK_DMGTYPE_ENUM)
	EM_RoleValue_CycleMagicID			,	//目前循環的法術

	EM_RoleValue_BaseEQ_Str				,		//str不算Buff的數值
	EM_RoleValue_BaseEQ_Sta				,		//sta不算Buff的數值
	EM_RoleValue_BaseEQ_Int				,		//int不算Buff的數值
	EM_RoleValue_BaseEQ_Mnd				,		//mnd不算Buff的數值
	EM_RoleValue_BaseEQ_Agi				,		//agi不算Buff的數值

	EM_RoleValue_RealZoneID				,		//所在區域（不去分流）
	EM_RoleValue_HidePlotOwnerDBID		,		//(DEBIG)隱藏劇情執行者DBID
	EM_RoleValue_HidePlotOwnerOrgObjID	,		//(DEBIG)隱藏劇情執行者OrgObjID


	EM_RoleValue_SuitSkill_LeanSkillCount = 8000	,	//學習的裝備技能
	EM_RoleValue_SuitSkill_MaxEqSkillCount			,	//最大可裝的到裝技能數

	EM_RoleValue_SuitSkill_EqID			= 8100		,	//目前裝備的技能
	EM_RoleValue_SuitSkill_LeanSkillID	= 8200		,	//目前學會的技能(200個)

	EM_RoleValue_BG_Return_Value		= 8500		,	//特殊戰場回傳值

	EM_RoleValue_SPMagic				= 9000 ,   //法術等級
	EM_RoleValue_NormalMagic			= EM_RoleValue_SPMagic + _MAX_SPSkill_COUNT_ ,   //法術等級

	EM_RoleValue_SuitWardrobe			= 10000 ,	//褲裝衣櫥
	EM_RoleValue_PetCard				= 11000	,	//寵物卡片
    //---------------------------------------------------------------------------------------
    EM_RoleValueName_EM_FORCE_DWORD   = 0x7fffffff, 

	//(...各像技能)
};

//----------------------------------------------------------------------------------
// 角色管理等級
//----------------------------------------------------------------------------------
enum	ManagementENUM
{
	EM_Management_Nornal		= 0,		//一般玩家

	EM_Management_GameVisitor	= 9	 ,		//遊戲參觀者
	EM_Management_GameService	= 10 ,		//遊戲服務者
	EM_Management_GameMaster	= 11 ,		//遊戲管理者
	EM_Management_BigGM			= 12 ,		//大GM
	EM_Management_GameCreator	= 13 ,		//遊戲設計者
};
//----------------------------------------------------------------------------------
// 狀態列舉 (有限狀態機) AI處理列舉
//----------------------------------------------------------------------------------
//例:
// AI1 : Normal -> Spell assist -> Search Enemy -> Attack Enemy  -> Normal
//                                              -> Move          -> Normal
//       under attack -> Attack <-> spell Cure , Atk 
//                    
enum	NPCAIActionTypeENUM
{
    EM_ActionType_NORMAL		= 0	,
    EM_ActionType_MOVE			    ,
    EM_ActionType_SEARCHENEMY       ,
    EM_ActionType_ESCAPE            ,
    EM_ActionType_UNDERATTACK       ,
    EM_ActionType_ATTACK            ,
	EM_ActionType_DEAD              ,

    EM_ActionTypeEM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//善惡等級
enum GoodEvilTypeENUM
{
	EM_GoodEvil_Demon		= -4 ,	
	EM_GoodEvil_Evil3		,	
	EM_GoodEvil_Evil2		,	
	EM_GoodEvil_Evil1		,	
	EM_GoodEvil_Normal		,	
	EM_GoodEvil_Good1		,	
	EM_GoodEvil_Good2		,	
	EM_GoodEvil_Good3		,	
	EM_GoodEvil_Hero		,	
};

//-------------------------------------------------------------------------------------
enum ZoneTypeENUM
{
	EM_ZoneType_NORMAL				= 0,
	EM_ZoneType_DEADZONE			= 1,
	EM_ZoneType_DAMAGEZONE			= 2,
	EM_ZoneType_IMMEDIATEDEATHZONE	= 3,

	EM_ZoneType_FORCE_DWORD			= 0x7FFFFFFF
};
//-------------------------------------------------------------------------------------
//位置資料定義
struct PlayerPosStruct
{
	int	X , Y , Z;
	int Dir;
	int ProcTime;
	PlayerPosStruct()
	{ memset( this , 0 , sizeof(PlayerPosStruct) ); }
};
//-------------------------------------------------------------------------------------
//裝備資料列舉
enum	ItemState_ENUM
{
	EM_ItemState_CliDisabled  = -1          ,
    EM_ItemState_NONE       = 0             ,

    EM_USE_ITEM		        = 0x1000		,	//使用的物品(設定物品使用中)
    EM_USE_SELSELL          = 0x1001		,	//選擇要賣出的
	EM_USE_SELMAIL			= 0x1002		,	//選擇要寄出的(表示已刪除)
	EM_USE_GUILDCONTRIBUTION= 0x1003		,	//選擇要貢獻的物品
	EM_USE_ITEM_GAMBLE		= 0x1004		,	//物品屬性賭博

	EM_RECIPE_RESOURCE	    = 0x1100		,	//配方資源索定

    EM_VENDOR_ONSELL1	    = 0x2000		,	//放至於拍賣欄位
    EM_VENDOR_ONSELL2						,
    EM_VENDOR_ONSELL3						,
    EM_VENDOR_ONSELL4						,
    EM_VENDOR_ONSELL5						,
    EM_VENDOR_ONSELL6						,
    EM_VENDOR_ONSELL7						,
    EM_VENDOR_ONSELL8						,

	EM_TRADE_ITEM1	        = 0x3000		,
	EM_TRADE_ITEM2							,
	EM_TRADE_ITEM3							,
	EM_TRADE_ITEM4							,
	EM_TRADE_ITEM5							,
	EM_TRADE_ITEM6							,
	EM_TRADE_ITEM7							,
	EM_TRADE_ITEM8							,
	EM_TRADE_ITEM9							,
	EM_TRADE_ITEM10							,
	EM_TRADE_ITEM11							,
	EM_TRADE_ITEM12							,
	EM_TRADE_ITEM13							,
	EM_TRADE_ITEM14							,
	EM_TRADE_ITEM15							,
	EM_TRADE_ITEM16							,
	EM_TRADE_ITEM17							,
	EM_TRADE_ITEM18							,
	EM_TRADE_ITEM19							,
	EM_TRADE_ITEM20							,
	EM_TRADE_ITEM21							,
	EM_TRADE_ITEM22							,
	EM_TRADE_ITEM23							,
	EM_TRADE_ITEM24							,			  
	EM_TRADE_ITEM25							,

    EM_ItemState_ENUM_FORCE_DWORD   = 0x7fffffff, 

};
//-------------------------------------------------------------------------------------
enum	ItemStateMode_ENUM
{
	EM_ItemStateMode_PickupSoulBound		,		//撿取綁定
	EM_ItemStateMode_None					,		//一般物品
	EM_ItemStateMode_EQSoulBound			,		//裝備過
	EM_ItemStateMode_SoulBound				,		//裝備後綁定(尚未綁定)
	
};
//-------------------------------------------------------------------------------------
//招喚寵物類型
enum	SummonPetTypeENUM
{
	EM_SummonPetType_Normal			,	//一般寵物
	EM_SummonPetType_CultivatePet	,	//養殖寵物
	EM_SummonPetType_Max			,	//最大寵物數量
};
//-------------------------------------------------------------------------------------
struct	ItemStateModeStruct
{
	union
	{
		int				_Mode;
		struct
		{
			bool	Trade				:1;			//可交易
			bool    EQSoulBound			:1;         //裝備禁制
			bool	ExchangeItemSystem	:1;			//兌換來的物品
			bool	ItemLock			:1;			//玩家用密碼鎖物品
			bool	Protect				:1;			//裝備保護，不會爆
			bool	DepartmentStore		:1;			//有商城物品旗標
			bool	IgnoreLimitLv		:1;			//忽略始用等級
			bool	HideCount			:1;			//影藏數量

			bool	PkProtect			:1;
			bool	ClientCreate		:1;			//客端產生資料
			bool	SuitSkill			:1;			//套裝技能使用狀況
			bool	Reserve11			:1;
			bool	Reserve12			:1;
			bool	Reserve13			:1;
			bool	Reserve14			:1;
			bool	Reserve15			:1;


			//(暫時狀態)
			bool	EQCannotEquipment	:1;			// true 裝備不可穿(不過目前穿在身上) false 一般狀態
			bool	IsHQ				:1;
		};
	};

	ItemStateMode_ENUM Mode()
	{
		return (ItemStateMode_ENUM)(_Mode & 0x11);
	}
};
//-------------------------------------------------------------------------------------
//寵物生活技
enum CultivatePetLifeSkillTypeENUM
{
	EM_CultivatePetLifeSkillType_None	= -1 ,
	EM_CultivatePetLifeSkillType_Mining		,
	EM_CultivatePetLifeSkillType_Lumbering	,
	EM_CultivatePetLifeSkillType_Herblism	,
	EM_CultivatePetLifeSkillType_Skill4		,

	EM_CultivatePetLifeSkillType_Max	,
};
//-------------------------------------------------------------------------------------
//物品欄位定義
// if OrgObjID == 0 代表這個欄位是空的
struct ItemFieldStruct
{
	int				OrgObjID;					//物件樣版的ID
	int				ImageObjectID;
	int             Serial;						//序號 辨識物品是否有拷貝
	int             CreateTime;					//CreateTime;
    
	int				Count;						//數量

	union
	{
		int			ExValue;
		struct  
		{	
			unsigned char	OrgQuality;		//原始的品質
			unsigned char	Quality;		//品質
			unsigned char	PowerQuality:5;	//威力品質( 1 為 10%強度)
			unsigned char	Rare		:3;	//額外增加的稀有度
			unsigned char	Level		:5;	//等級
			unsigned char	RuneVolume	:3;	//符文容量			
		};
	};

	int 			Durable;					//目前耐久度
    ItemState_ENUM  Pos;                        //所在位置狀態

	union
	{
		char		Ability[32];
		int			IntAbility[8];
		//附加能力
		struct  
		{
			short   _Inherent[6];                //天生附加能力( 加50000偏移 )
			short   _Rune[4];                    //符石
			int		MainColor;
			int		OffColor;
		};
		
		//傳點記錄位置
		struct  
		{
			int		ZoneID;						//區域ID
			int		X , Y , Z ;
			int		MapID;						//地圖ID
		};
		//樂透資料
		struct  
		{
			int		Index;						//期數	
			char	Count;
			char	SelectID[20];
		}Lottery;

		//金錢
		struct
		{
			int		Money;
		};

		//座騎顏色
		int		HorseColor[4];					

		//打包商品資訊
		struct  
		{
			unsigned int ItemCount1 : 8;	
			unsigned int ItemID1	: 24;	
			unsigned int ItemCount2 : 8;	
			unsigned int ItemID2	: 24;	
			unsigned int ItemCount3 : 8;	
			unsigned int ItemID3	: 24;	
			unsigned int ItemCount4 : 8;	
			unsigned int ItemID4	: 24;	
			unsigned int ItemCount5 : 8;	
			unsigned int ItemID5	: 24;	
			unsigned int ItemCount6 : 8;	
			unsigned int ItemID6	: 24;	
			unsigned int ItemCount7 : 8;	
			unsigned int ItemID7	: 24;	
			unsigned int ItemCount8 : 8;	
			unsigned int ItemID8	: 24;	
			
		};

		//舊商城物品的規則
		struct
		{
			int  ItemIDList[4];
			int  ItemCountList[4];
		};

		//種植資訊(盆子)
		struct  
		{
			unsigned short	OrgSeedID;			//原本的種子號碼+( Def_ObjectClass_Item )
			unsigned short	SeedID;				// 須加Def_ObjectClass_Item
			int				CreateTime;
			int				LastProcTime;		//最後處理的時間
			short			HealthPoint;		//健康度 (100倍)
			short			RarePoint;			//稀有度 (100倍)
			short			WaterPoint;			//濕度 (100倍)
			short			TopdressPoint;		//養分 (100倍)

			short			DecWaterPoint;		//保水下降量(100倍)	
			short			DecTopdressPoint;	//肥料下降量(100倍)

			short			GrowRate;
			short			FeedPoint;		//飽食度

			bool			IsLock			:1;	//鎖定後變成乾造花不會成長，也無法收成
			bool			IsDead			:1;

		}Plant;

		//寵物資料
		struct
		{
			int CreateTime;
			int PetOrgID;
			int SkillPoint;

			unsigned char PetType;
			char Property;		//屬性(地水火風光暗)
			unsigned char Lv;
			unsigned char TrainCount;

			unsigned short Talent;
			unsigned short STR , STA , INT , MND , AGI;	
			
			//unsigned char LifeSkill[ EM_CultivatePetLifeSkillType_Max ];
			//char PetTypeFlag[ _DEF_MAX_PET_TYPE_ / 8 ];					
		}Pet;
	};


	ItemStateModeStruct	Mode;					//物品狀態

	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}

	bool operator == ( const ItemFieldStruct& P ) const
	{
        //部份檢查
        if(     OrgObjID    == P.OrgObjID 
            &&  Serial      == P.Serial    
            &&  CreateTime  == P.CreateTime 
            &&  Count       == P.Count     
			&&  Mode._Mode	== P.Mode._Mode )
            return true;

        return false;
	};

	bool operator != ( const ItemFieldStruct& P ) const
	{
		//部份檢查
		if(     OrgObjID    == P.OrgObjID 
			&&  Serial      == P.Serial    
			&&  CreateTime  == P.CreateTime 
			&&  Count       == P.Count    
			&&  Mode._Mode	== P.Mode._Mode )
			return false;

		return true;
	};  

	//用來檢是否有重複物品
	bool operator < ( const ItemFieldStruct& P ) const
	{
		if( OrgObjID   <  P.OrgObjID )
			return true;
		else if( OrgObjID   >  P.OrgObjID )
			return false;

		if( Serial   <  P.Serial )
			return true;
		else if( Serial   >  P.Serial )
			return false;

		if( CreateTime   <  P.CreateTime )
			return true;
		else if( CreateTime   >  P.CreateTime )
			return false;

		return false;
	};  

	
	bool IsEmpty()
	{   
        if( this == NULL )
            return true;
		if( Count == 0 && OrgObjID )
			Init();
		return OrgObjID == 0 ;
	}

	int GetCount()
	{
		if ( Mode.HideCount )
			return 1;
		return Count;
	}

	int		Inherent( int i )				
	{ 
		if( _Inherent[i] == 0 )
			return 0;
		return _Inherent[i] + _DEF_ITEM_ABILITY_DELTA_; 
	}
	void	Inherent( int i , int Value )	
	{ 
		if( Value == 0 )
			_Inherent[i] = 0;
		else
			_Inherent[i] = Value - _DEF_ITEM_ABILITY_DELTA_; 
	}
	int		Rune( int i )					
	{ 
		if( _Rune[i] == 0 )
			return 0;
		return _Rune[i] + _DEF_ITEM_ABILITY_DELTA_; 
	}
	void	Rune( int i , int Value )		
	{ 
		if( Value == 0 )
			_Rune[i] = 0;
		else
			_Rune[i] = Value - _DEF_ITEM_ABILITY_DELTA_; 
	}

	bool CheckInherent( int Value )
	{
		for( int i = 0 ; i < 6 ; i++ )
		{
			if( Inherent(i) == Value )
				return true;
		}
		return false;
	}
};
//-------------------------------------------------------------------------------------
struct GambleItemStateStruct
{
	int				BodyItemPos;
	int				ItemVersionID;
	int				GambleTableID;
	int				StatePos;
	int				StateID;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GambleTableID = -1;

	};
};

//-------------------------------------------------------------------------------------
//賣出物品暫存結構
struct SellItemFieldStruct
{
	ItemFieldStruct Item;
	int				Money;			//賣出的錢

	bool operator == ( const SellItemFieldStruct& P ) const
	{
		//部份檢查
		if(     Item    == P.Item 
			&&  Money   == P.Money    )
			return true;

		return false;
	};
};
//-------------------------------------------------------------------------------------
// 對話系統結購

struct SpeakOptionStruct
{
	int		iNPCID;
	int		iIconID;
	//char	szOption[64];
	//char	szLuaFunc[64];
	StaticString< _MAX_SPEAKOPTION_SIZE_ > szOption;
	StaticString< _MAX_SPEAKOPTION_SIZE_ > szLuaFunc;
};

struct SpeakStruct
{
	SpeakStruct() { Reset(); }

	void	Reset()			
	{ 
		iSpeakNPCID = 0;
		iLoadQuest	= 0;
		SpeakDetail.Clear();  
		SpeakOption.Clear();
	}

	int		iSpeakNPCID;
	int		iLoadQuest;

	StaticString< _MAX_SPEAKDETAIL_SIZE_ >								SpeakDetail;
	StaticVector< SpeakOptionStruct, _MAX_SPEAKOPTION_COUNT_ >			SpeakOption;
	//vector< SpeakOptionStruct>											SpeakOption;
};	
//-------------------------------------------------------------------------------------
// 石碑系統資料
//-------------------------------------------------------------------------------------
struct ScriptBorderStruct
{
	ScriptBorderStruct()
	{
		iQuestID = 0;
	}

	void Init()
	{
		iQuestID	= 0;
		iPageCount	= 0;

		//for( int i = 0; i < _MAX_SPEAKOPTION_COUNT_; i++ )
		//	sBorderPage[i]->Clear();
	};

	int												iQuestID;
	int												iPageCount;
	//StaticString<  _MAX_SPEAKDETAIL_SIZE_ >			sBorderPage[ _MAX_SPEAKOPTION_COUNT_ ];
	//string											sBorderPage;
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sTitle;
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sTextureFile;

	//StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sLuaAcceptQuest;
	//StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sLuaAfterRead;
};

//-------------------------------------------------------------------------------------
// 劇情及任務資料
//-------------------------------------------------------------------------------------
enum ENUM_SCRIPTSTATUS
{
	EM_SCRIPT_NONE		= 0,
	EM_SCRIPT_RUNNING	= 1,

};
//-------------------------------------------------------------------------------------
enum ENUM_SCRIPTSTATUS_LOCKTYPE
{
	ENUM_SCRIPTSTATUS_LOCKTYPE_NOLOCK	= 0,
	ENUM_SCRIPTSTATUS_LOCKTYPE_PERSONAL = 1,
	ENUM_SCRIPTSTATUS_LOCKTYPE_PARTY	= 2,
	ENUM_SCRIPTSTATUS_LOCKTYPE_RAID		= 3,	
};
//-------------------------------------------------------------------------------------
struct ScriptStruct 
{
	ENUM_SCRIPTSTATUS				emMode;
	
	ENUM_SCRIPTSTATUS_LOCKTYPE		emLockType;		// 限定特定人物或隊伍才能點選的種類
	int								iLockDBID;		// 限定特定人物或隊伍才能點選的物件代號

};

//-------------------------------------------------------------------------------------
enum	PET_ACTION_ENUM
{
    EM_PET_NONE				,   // 目前沒命令
    EM_PET_STOP				,
    EM_PET_FOLLOW			,
    EM_PET_ATTACK			,
    EM_PET_ATTACKOFF		,
    //EM_PET_PROTECT			,
	EM_PET_STRICKBACK		,
	EM_PET_STRICKBACK_OFF	,
    EM_PET_GUARD			,
	EM_PET_SPELLMAGIC		,


    EM_PET_PROC_STATE_ENUM_FORCE_DWORD   = 0x7fffffff, 
};

struct PetSkillStruct
{
	int		MagicColID;		//技能
	int		MagicLv;		//技能等級
	bool	IsActive;		//自動施展
	PetSkillStruct()
	{
		MagicColID = 0;
		MagicLv = 0;
		IsActive = false;

	}
};

struct PetStruct
{
//	bool				IsPet;			//此NPC為寵物
    PET_ACTION_ENUM		Action;			//目前執行的行為
    int					PetID;			//寵物號碼
    int					TargetID;		//處理的目標
	int					MagicID;		//產生的法術

	StaticVector< PetSkillStruct , _MAX_PET_SKILL_COUNT_ >	Skill;	//寵物技能

    PetStruct()
    {
        Init();
    }

    void Init()
    {
		//ActiveSkill = 0;
        PetID = -1;
        TargetID = -1;
		Action	= EM_PET_FOLLOW;
		Skill.Clear();
    }
};

struct SummonPetInfoStruct
{
	//寵物資料
	SummonPetTypeENUM		Type;						//招喚類型		(寵物紀錄)
	int						MagicBaseID;					
	//主人資料
	PetStruct				Info[EM_SummonPetType_Max];	//招出來的寵物	(主人紀錄)

	void	Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//重生資料
struct RaiseModeStruct
{
	union
	{
		int Mode;
		struct  
		{
			bool	MagicRaiseEnabled : 1;
			bool	ExpProtect		  : 1;
			bool	EqProtect		  : 1;	
		};
	};
};

struct RaiseInfoStruct
{
	RaiseModeStruct	Mode;
	int				ExpRate;		//回復exp的比例
	int				ZoneID;
	float			RevX;
	float			RevY;
	float			RevZ;

	int 			ExpDownRate;
	int 			DebtExpRate;
	int 			DebtTpRate;

	void Init()
	{
		Mode.Mode = 0;
		ExpRate = 0;
		ExpDownRate = 0;
		DebtExpRate = 0;
		DebtTpRate = 0;
	}
};

//-------------------------------------------------------------------------------------
struct		RoleTableStruct
{
    union
    {
        float	Skill[_MAX_SKILL_COUNT_];
        struct
        {
            float		BeatPro;			
            float		BladePro;		
            float		SwordPro;		
            float		AxeHammerPro;
            float		StickPro;		
            float		PikePro;			
            float		RodPro;			
            float		DaggerPro;		
            float		EctPro;			
            float		BowPro;			
            float		RefinePro;		
            float		MeditationPro;	
        };
    };
    int MaxExp;
};
//-------------------------------------------------------------------------------------
enum	MAGIC_PROC_STATE_ENUM
{
	EM_MAGIC_PROC_STATE_NORMAL				    ,	//一般非施法狀態
	EM_MAGIC_PROC_STATE_PERPARE				    ,	//準備施法中
	EM_MAGIC_PROC_STATE_SHOOT					,	//射出
	EM_MAGIC_PROC_STATE_SPELL				    ,	//施法中
	EM_MAGIC_PROC_STATE_INTERRUPT				,	//施法中斷
	EM_MAGIC_PROC_STATE_ENDSPELL				,	//施法剛結束
    EM_MAGIC_PROC_STATE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
/*
enum	MAGIC_VALUE_TYPE_ENUM
{
	EM_MAGIC_VALUE_NONE			,	//不始用
	EM_MAGIC_VALUE_REPLACE		,	//取代
	EM_MAGIC_VALUE_ADD			,	//加上
	EM_MAGIC_VALUE_MUL			,	//乘
};
//-------------------------------------------------------------------------------------
//法術劇情數值設定
struct  MagicScriptValueStruct
{
	float					Value;
	MAGIC_VALUE_TYPE_ENUM	Type;		
};
*/
//-------------------------------------------------------------------------------------
//施法的狀態資訊
struct MagicProcInfo
{
	int						SerialID;			//法術序號

	MAGIC_PROC_STATE_ENUM	State;
	int						TargetID;			//目標
	int						MagicCollectID;		//法術集合ID
	
	int						ProcTime;			//執行時間
	int						TotalSpellTime;		//所需施法時間

	float					BeginX;				//開始施法的位置
	float					BeginY;				//開始施法的位置
	float					BeginZ;				//開始施法的位置
	bool					IsMove;

	float					TargetX;			//目標位置x
	float					TargetY;			//目標位置y
	float					TargetZ;			//目標位置z

    int						UseItem;			//使用的物品
	short					UseItemPos;			//物品的位置
    short                   UseItemType;        // 0 身體 1 銀行 2 EQ
	//-------------------------------------------
	bool					IsSpellCheckOK;		//可以施法 
	bool					IsSuccess;			//施法成功

	int						SpellCount;			//還要施展幾次
	int						NextSpellTime;		//下次施展的時間

	//-------------------------------------------
	//法術主體可設定數值
	bool					MagicEnabled[_MAX_MAGICCOLLECT_GROUP_COUNT_][_MAX_MAGICCOLLECT_COUNT_];	//那些法術為Enabled ( 初始全開 劇情可控制 )
	float					Coldown;
	MagicSpellCostTypeENUM	CostType;
	float					CostValue;
	MagicSpellNeedTypeENUM	NeedType;
	float					NeedValue;
	//法術單體設定數值
	float					SpellTime;			//施法時間
	float					HitRate;			//命中率(Shooting Average)
	int						MagicLv;			//法術等級
	float					EffectTime;			//影響時間
	bool					IsSystemMagic;		//
	bool					IsPayCost;			//已經扣過消耗
	bool					IsCheckUseItem;		
	bool					IsNoRebound;		
	//----------------------------------------------
	//使用的物品內設定的座旗顏色
	int						HorseColor[4];

	int						BaseShootDelayTime;	//最低法術飛行延遲( 千分之一秒 )

	//設定法術序號
	int SetSerialID()
	{
		static int ID = 0;
		SerialID = ID++;
		return SerialID;
	}

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		InitMagicEnabled();
	}

	void InitMagicEnabled()
	{
		for( int i = 0 ; i < _MAX_MAGICCOLLECT_GROUP_COUNT_ ; i ++ )
			for( int j = 0 ; j < _MAX_MAGICCOLLECT_COUNT_ ; j ++ )
				MagicEnabled[i][j] = true;
	}

/*
	bool CheckInterrupt( float x , float z)
	{
		if(		State != EM_MAGIC_PROC_STATE_PERPARE 
			&&	State != EM_MAGIC_PROC_STATE_SHOOT )
			return false;

		//if(		abs( int( x - BeginX ) ) > 10 
	//		||	abs( int( z - BeginZ ) ) > 10 )
		if( IsMove )
		{
			State = EM_MAGIC_PROC_STATE_INTERRUPT;
			return true;
		}

		return false;
	};
*/
	void ClsUseItem()
	{
		UseItem		= 0;
		UseItemPos	= -1;
        UseItemType	= -1;
	};
		
	
};
//-------------------------------------------------------------------------------------
#define _DEF_BAG_PAGE3_BEGIN_POS_	(30*2 + _MAX_BODY_EX_COUNT_ + _MAX_BODY_MAGIC_BOX_COUNT_ )
#define _DEF_BAG_PAGE4_BEGIN_POS_	(30 + _DEF_BAG_PAGE3_BEGIN_POS_ )
#define _DEF_BAG_PAGE5_BEGIN_POS_	(30 + _DEF_BAG_PAGE4_BEGIN_POS_ )
#define _DEF_BAG_PAGE6_BEGIN_POS_	(30 + _DEF_BAG_PAGE5_BEGIN_POS_ )

//身體與銀行資料
struct BodyItemStruct
{
	union
	{
	    ItemFieldStruct     Item[ _MAX_BODY_COUNT_];
		struct
		{
			ItemFieldStruct     ItemEx[ _MAX_BODY_EX_COUNT_ ];						//商城包
			ItemFieldStruct     ItemMagicBox[ _MAX_BODY_MAGIC_BOX_COUNT_ ];			//月光寶盒
			ItemFieldStruct     ItemBase[ _MAX_BODY_COUNT_ - _MAX_BODY_EX_COUNT_ - _MAX_BODY_MAGIC_BOX_COUNT_ ];	//身上包
		};
	};
    int                 Count;
    int                 Money;
	int					Money_Account;

    void Init()
    {
        memset( this , 0 , sizeof(*this) );
    };
};
//-------------------------------------------------------------------------------------
#define _DEF_BANK_PAGE2_BEGIN_POS_	( 40 )
#define _DEF_BANK_PAGE3_BEGIN_POS_	( 40*2 )
#define _DEF_BANK_PAGE4_BEGIN_POS_	( 40*3 )
#define _DEF_BANK_PAGE5_BEGIN_POS_	( 40*4 )
#define _DEF_BANK_MALL_BEGIN_POS_	200
#define _DEF_BANK_MALL_COUNT_		100

//身體與銀行資料
struct BankItemStruct
{
	ItemFieldStruct     Item[ _MAX_BANK_COUNT_];
	int                 Count;
	int                 Money;
	int					Money_Account;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//-------------------------------------------------------------------------------------
//劇情設定可使用法術
//struct Plot
//-------------------------------------------------------------------------------------
struct TreasureBoxStruct
{
	int	Count;
	int					OwnerDBID[_MAX_BODY_COUNT_];
	ItemFieldStruct     Item[ _MAX_BODY_COUNT_ ];
	bool				Lock[ _MAX_BODY_COUNT_ ];
	int	LiveTime;				//能活多久
	int	DeadTime;				//死亡的時間
	int TreasureOwnerDBID;		//擁有者
	int	TreasurePartyID;		//隊伍ID
	int	CheckSerialID;			//玩家掉落屍體檢查用
	bool IsPetLoot;				//	
	

	TreasureBoxStruct( )
	{
		memset( this , 0 , sizeof( *this ) );
	}
};
//-------------------------------------------------------------------------------------
#define _DEF_EQ_BACKUP_BASE_	100
enum    EQWearPosENUM
{
    EM_EQWearPos_None       = -1 , 
    EM_EQWearPos_Head       ,//0
    EM_EQWearPos_Gloves	    ,//1
    EM_EQWearPos_Shoes		,//2
    EM_EQWearPos_Clothes	,//3
    EM_EQWearPos_Pants		,//4
    EM_EQWearPos_Back		,//5
    EM_EQWearPos_Belt		,//6
    EM_EQWearPos_Shoulder	,//7
    EM_EQWearPos_Necklace   ,//8
    EM_EQWearPos_Ammo       ,//9
	EM_EQWearPos_Bow        ,//10
    EM_EQWearPos_Ring1      ,//11
    EM_EQWearPos_Ring2      ,//12
    EM_EQWearPos_Earring1   ,//13
    EM_EQWearPos_Earring2   ,//14
    EM_EQWearPos_MainHand	,//15
    EM_EQWearPos_SecondHand ,//16
	EM_EQWearPos_Manufactory,//17
	EM_EQWearPos_MagicTool1	,//18
	EM_EQWearPos_MagicTool2	,//19
	EM_EQWearPos_MagicTool3	,//20
	EM_EQWearPos_Ornament	,//21
	EM_EQWearPos_MaxCount	,


	EM_EQWearPos_BK_Head       = _DEF_EQ_BACKUP_BASE_,//0
	EM_EQWearPos_BK_Gloves	    ,//1
	EM_EQWearPos_BK_Shoes		,//2
	EM_EQWearPos_BK_Clothes		,//3
	EM_EQWearPos_BK_Pants		,//4
	EM_EQWearPos_BK_Back		,//5
	EM_EQWearPos_BK_Belt		,//6
	EM_EQWearPos_BK_Shoulder	,//7
	EM_EQWearPos_BK_Necklace   	,//8
	EM_EQWearPos_BK_Ammo       	,//9
	EM_EQWearPos_BK_Bow        	,//10
	EM_EQWearPos_BK_Ring1      	,//11
	EM_EQWearPos_BK_Ring2      	,//12
	EM_EQWearPos_BK_Earring1   	,//13
	EM_EQWearPos_BK_Earring2   	,//14
	EM_EQWearPos_BK_MainHand	,//15
	EM_EQWearPos_BK_SecondHand 	,//16
	EM_EQWearPos_BK_Manufactory	,//17
	EM_EQWearPos_BK_MagicTool1	,//18
	EM_EQWearPos_BK_MagicTool2	,//19
	EM_EQWearPos_BK_MagicTool3	,//20
	EM_EQWearPos_BK_Ornament	,//21

    EM_EQWearPosENUM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
struct EQStruct
{
	union
	{
        ItemFieldStruct Item[ EM_EQWearPos_MaxCount ];
        
        
		struct 
		{
			ItemFieldStruct Head			;//頭
			ItemFieldStruct Gloves	    	;//手套
			ItemFieldStruct Shoes			;//鞋子
			ItemFieldStruct Clothes		    ;//上衣
			ItemFieldStruct Pants			;//褲子
			ItemFieldStruct Back			;//背部
			ItemFieldStruct Belt			;//腰帶
            ItemFieldStruct Shoulder		;//肩甲
            ItemFieldStruct Necklace        ;//項鍊
            ItemFieldStruct Ammo            ;//彈藥
            ItemFieldStruct Bow             ;//弓

            ItemFieldStruct Ring1;          ;//戒子
            ItemFieldStruct Ring2;          ;
            ItemFieldStruct Earring1        ;//耳飾	
            ItemFieldStruct Earring2        ;			

            ItemFieldStruct MainHand		;//主手
            ItemFieldStruct SecondHand		;//副手

			ItemFieldStruct Manufacture     ;//生產製造欄位
			ItemFieldStruct MagicTool1		;
			ItemFieldStruct MagicTool2		;
			ItemFieldStruct MagicTool3		;
			ItemFieldStruct Ornament		;
			
		};
	};

	void	Init()
	{
		memset( &Item , 0 , sizeof(Item) );
	};
};
//-------------------------------------------------------------------------------------
struct DestroyItemLogStruct
{
	ItemFieldStruct ItemList[ DEF_MAX_DESTROY_ITEM_LOG_COUNT ];
	void	Push( ItemFieldStruct Item )
	{
		for( int i = DEF_MAX_DESTROY_ITEM_LOG_COUNT-1 ; i > 0 ; i-- )
			ItemList[i] = ItemList[i-1];
		ItemList[0] = Item;
	};
};
//-------------------------------------------------------------------------------------
struct ShowEQStruct
{
	union
	{
		int _Value;
		struct
		{
			bool Head		:1;//頭
			bool Gloves	    :1;//手套
			bool Shoes		:1;//鞋子
			bool Clothes	:1;//上衣
			bool Pants		:1;//褲子
			bool Back		:1;//背部
			bool Belt		:1;//腰帶
			bool Shoulder	:1;//肩甲
			bool Necklace   :1;//項鍊
			bool Ammo       :1;//彈藥
			bool Bow        :1;//弓
			bool Ring1      :1;//戒子
			bool Ring2      :1;
			bool Earring1   :1;//耳飾	
			bool Earring2   :1;			

			bool MainHand	:1;//主手
			bool SecondHand	:1;//副手

			bool Manufacture:1;//生產製造欄位
			bool MagicTool1	:1;
			bool MagicTool2	:1;
			bool MagicTool3	:1;
			bool Ornament	:1;
		};
	};

};
//-------------------------------------------------------------------------------------
#define _DEF_MAX_GOODEVIL_BATTLE_INFO_COUNT_ 30
#define	_DEF_MAX_GOODEVIL_ATK_LIVETIME_		(30*60)
enum GoodEvilAtkInfoTypeENUM
{
	EM_GoodEvilAtkInfoType_Empty	,	//空的資料
	EM_GoodEvilAtkInfoType_Atk		,	//攻擊
	EM_GoodEvilAtkInfoType_Def		,	//防守

};

struct GoodEvilAtkInfoStruct
{
	int		PlayerDBID;
	int		Time;
	GoodEvilAtkInfoTypeENUM Type;
};
//善惡職處理暫存資料
struct GoodEvilTempStruct
{
	StaticVector< GoodEvilAtkInfoStruct , _DEF_MAX_GOODEVIL_BATTLE_INFO_COUNT_ >	BattleInfoList;
//	float	GoodEvilPoint;		//可增加的善惡值點數
};

//-------------------------------------------------------------------------------------
//目前行為模式資料
//-------------------------------------------------------------------------------------
enum	RoleOpenMenuTypeENUM
{
	EM_RoleOpenMenuType_None			,
	EM_RoleOpenMenuType_Shop			,
	EM_RoleOpenMenuType_Bank			,
	EM_RoleOpenMenuType_AC				,
	EM_RoleOpenMenuType_Mail			,
	EM_RoleOpenMenuType_ChangeJob		,
	EM_RoleOpenMenuType_Billboard		,
	EM_RoleOpenMenuType_CreateNewGuild	,
	EM_RoleOpenMenuType_GuildContribution,
//	EM_RoleOpenMenuType_GuildShop		,
	EM_RoleOpenMenuType_ExchangeLottery ,
	EM_RoleOpenMenuType_BuyLottery		,
	EM_RoleOpenMenuType_VisitHouse		,
	EM_RoleOpenMenuType_EQCombin		,
	EM_RoleOpenMenuType_PlotGiveItem	,
	EM_RoleOpenMenuType_AccountBag		,
	EM_RoleOpenMenuType_VisitGuildHouse	,
	EM_RoleOpenMenuType_EqGamble		,
	EM_RoleOpenMenuType_MagicStoneExchange	,
	EM_RoleOpenMenuType_SuitSkill			,
	EM_RoleOpenMenuType_Rare3EqExchangeItem	,
};

struct		RoleActionStruct
{
	union
	{
		unsigned int		_Action;
        struct      
        {
            short   _LowAction;
            short   _HiAction;
        };
		struct
		{
            //前16改變不送資料
			unsigned int	SrvSetPos			:1;		//Server決定的位置
			unsigned int	Reserve2			:1;		
			unsigned int	Reserve_Spell		:1;		//施法
			unsigned int	Follow	        	:1;		//跟隨
            unsigned int	Login	        	:1;		//第一次登入
            unsigned int	SendAllZoneObj  	:1;		//送全域的物件
            unsigned int	ChangeZone      	:1;		//有換區過
            unsigned int	NoReturnAttackPoint :1;

			unsigned int	ChangeParallel		:1;
            unsigned int	Reserve9_15			:7;

			unsigned int	OpenType		:5;		//RoleOpenMenuTypeENUM 開起介面的類型
			unsigned int	Trade			:1;		//交易
			unsigned int	Dead			:1;		//死亡
			unsigned int	Walk			:1;		//跑步or走路

            unsigned int 	AttackMode      :1;     //攻擊中(Cli的攻擊狀態)
			unsigned int	Sit				:1;
			unsigned int	DisableClick	:1;		//執行劇情中, 或不在致能狀態下. 不允許 Client 執行動作
			unsigned int	DisableQuest	:1;		// 關掉任務 NPC 給予任務的狀態 ( 當該 NPC 執行 SCRIPT 中, 由 SCRIPT 關畢及打開 )
			unsigned int	PK				:1;		//pk狀態
			unsigned int	Attack			:1;		//攻擊
			unsigned int	Unholster		:1;		//取出武器
		};
	};
};
//-------------------------------------------------------------------------------------
//全區域定時玩家更新資料
struct PlayerBackupInfoStruct
{
	float	LX , LZ;		//最後更新的座標位置
	int		LHPMPSPSum;		//最後一次 MaxHP , MaxMP HP MP SP 的總和值 , 用來確定是否要更新座標
	int		BuffIDCheckSum;	//BuffID 的加總值
};

//-------------------------------------------------------------------------------------
//全區可查尋的玩家狀態
//-------------------------------------------------------------------------------------
struct PlayerStateStruct
{
	union
	{
		int		_State;
		struct
		{
			bool	FindParty			:1;			//找隊伍
			bool	AFK					:1;			//離開
			bool	Dig					:1;			//挖礦

			bool	HasParty			:1;
			bool	Reserve4			:1;
			bool	Reserve5			:1;
			bool	Reserve6			:1;
			bool	Reserve7			:1;
			bool	Reserve8_15			:8;

			//系統設定
			bool	HonorParty			:1;			//榮譽組隊模式
		};
	};
};
//-------------------------------------------------------------------------------------
//角色顯像資料
//-------------------------------------------------------------------------------------
struct PlayerGraphStruct
{
	int					                    OrgObjID;						//物件原始ID
    StaticString< _MAX_NAMERECORD_SIZE_ >   Name;
	ObjectModeStruct                    	Mode;   
	int		                                MaxHP;
	int		                                MaxMP;
	int		                                MaxSP;
	int		                                MaxSP_Sub;
	int		                                HP;
	int		                                MP;
	int		                                SP;
	int		                                SP_Sub;
	float	                                MoveSpeed;
	int				                    	Level;							//物件等級
    int                                     NpcQuestID;
    short                                   TouchPlot_Range;
    short                                   RangePlot_Range;
    RoleActionStruct		                Action;			                //目前的行動狀態
	Voc_ENUM								Voc;							//主職
	Voc_ENUM								Voc_Sub;						//副職
	Race_ENUM								Race;

	int										Level_Sub;						//副職等級	
	int										TitleID;						//頭銜
	int										GuildID;						//公會ID
	int										MinimapIcon;
	int										CursorType;						// 跟據不同 NPC 類型, 設定該類型特殊的游標
	float									vX , vY , vZ;					//角色方向向量
	int										IdleMotionID;				
	int										CliActionID;					//Client 端的狀態設定資料
	PlayerStateStruct						AllZoneState;					//全區狀態資料
	bool									IsShowTitle;					//是否顯示頭銜
	MagicEffectStruct						MagicEffect;
	Sex_ENUM								Sex;
	GoodEvilTypeENUM						GoodEvilType;
//	int										ImageObjID;						//顯像的物件
	int										iForceFlagID;					//強制背負的旗子
	int										iDefIdleMotion;					//預設的最背景 Idle Motion
	
	SystemFlagStruct						SysFlag;
};
//-----------------------------------------------------------------------------------
// Party 相關資料結構
//-----------------------------------------------------------------------------------
struct PartyMemberModeStruct 
{
	union
	{
		int			_Mode;
		struct  
		{
			bool	IsAssistant		: 1;		//助理		可要請玩家
			bool	IsMainTank		: 1;		//坦克
			bool	IsMainAttack	: 1;		//主攻手
		};
	};
};

struct PartyMemberInfoStruct
{
	int		MemberID;
	int		PartyNo;			//小隊ID
	StaticString <_MAX_NAMERECORD_SIZE_> Name;	
	union
	{
		int		GItemID;	// -1 代表下線狀態
		struct
		{
			short   ItemID;            
			short   ZoneID;
		};
	};
	int DBID;

	int				Voc;								//職業
	int				Voc_Sub;							//副職業
	int				Level;
	int				Level_Sub;
	int				Sex;

	PartyMemberModeStruct Mode;
	PlayerStateStruct	State;		//角色狀態
	int				ParallelID;

	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------
enum GroupObjectTypeEnum
{
	EM_GroupObjectType_SysChannel    = 0  ,	//系統
	EM_GroupObjectType_SysZoneChannel   ,	//每個區域都有的
	EM_GroupObjectType_PlayerChannel    ,	//玩家的
	EM_GroupObjectType_Party            ,	//隊伍
	EM_GroupObjectType_Guild            ,	//工會

	EM_GroupObjectType_Count            ,   //類形種數
	EM_GroupObjectType_MAX        = 0xffffffff    ,
};

enum	PartyItemShareENUM
{
	EM_PartyItemShare_Roll		,
	EM_PartyItemShare_Assign	,
	EM_PartyItemShare_InOrder	,
};

enum	PartyTypeENUM
{
	EM_PartyType_Party		,
	EM_PartyType_Raid		,
};

struct PartyBaseInfoStruct
{
	int				PartyID;
	PartyTypeENUM	Type;								//隊伍類型
	StaticString <_MAX_NAMERECORD_SIZE_> LeaderName;	//隊長
	StaticString <_MAX_NAMERECORD_SIZE_> AttackName;	//攻擊者
	StaticString <_MAX_NAMERECORD_SIZE_> ShareName;		//分配者

	PartyItemShareENUM	ItemShareType;	//分享的模式
	int					RollTypeLV;		//需要擲骰子的等級 or 分配等級
	bool				Roll_CanUse;	//可使用者才可以擲骰子 or 分配等級
	short				InstanceLv;		// 副本難度

	PartyBaseInfoStruct( )
	{
		PartyID = -1;
		ItemShareType = EM_PartyItemShare_InOrder;
		RollTypeLV = 1;
		Roll_CanUse = false;
		Type = EM_PartyType_Party;
		InstanceLv = 0;
	}
};
//Party 資料 
struct PartyInfoStruct
{
	PartyBaseInfoStruct Info;
	vector< PartyMemberInfoStruct > Member;
};
//-------------------------------------------------------------------------------------
//角色位置資料定意
//-------------------------------------------------------------------------------------
struct RolePosStruct
{
    float   X , Y , Z ;
    float   Dir;
};
//-------------------------------------------------------------------------------------
//角色數值資料
//-------------------------------------------------------------------------------------
struct BaseAbilityStruct
{
	int		EXP;
	int		TotalTpExp;			//
	int		TpExp;				//法術技能經驗值點數
	
	int		DebtExp;			//經驗值負債
	int		DebtTP;				//TP負債
	int		AddExp;								//額外增加Exp
	int		AddTp;								//額外增加Tp
	int		Level;

	int		Point;				//可配置點數
	int		PlayTime;			//用此職業遊戲的時間(分鐘)

    int 	STR;			    // 力量
    int 	STA;			    // 耐力
    int 	MND;			    // 智慧
	int     INT;                // 聰明
    int 	AGI;			    // 敏捷


	union
	{
		float	AllSkillLv[ _MAX_SPSkill_COUNT_ + _MAX_NormalSkill_COUNT_ ];
		struct  
		{
			float	SPSkill		[ _MAX_SPSkill_COUNT_ ];			//sp技能等級
			float	NormalSkill	[ _MAX_NormalSkill_COUNT_ ];		//一般法術技能等級
		};
	};


	int		TotalPoint()
	{
		return Point + STR + STA + MND + INT + AGI;
	};
	int		ResetPoint()
	{
		Point = TotalPoint();
		STR = 0;
		STA = 0;
		MND = 0;
		INT = 0;
		AGI = 0;
		return Point;
	};
};
//-------------------------------------------------------------------------------------
// 目前所會法術結構
//-------------------------------------------------------------------------------------

struct SkillStruct
{
    union
    {
        int AllSkill[ _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ +  _MAX_EQ_Skill_COUNT_ + _MAX_Lua_Skill_COUNT_ ];
        struct
        {
			union
			{
				int JobSkill[ _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ ];
				struct
				{
					int SP [ _MAX_SPSkill_COUNT_ ];				//職業專屬技能
					int MainJob[ _MAX_NormalSkill_COUNT_ ] ;	//主職一般技能
					int	SubJob[ _MAX_NormalSkill_COUNT_ ];		//副職一般技能
				};
			};
			union
			{
				int	OtherSkill[ _MAX_EQ_Skill_COUNT_ + _MAX_Lua_Skill_COUNT_];
				struct
				{
					int	EqSkill[ _MAX_EQ_Skill_COUNT_ ];		//因裝備或數值動態來的技能
					int LuaSkill[ _MAX_Lua_Skill_COUNT_ ];		//因 劇情 動態來的技能 (換區消失)
				};
			};

        };
    };   
};
//-------------------------------------------------------------------------------------
//AI 資料結構
struct  NPC_AI_Struct
{
    NPCAIActionTypeENUM		ActionType;		    //行為模式
    NPCAIActionTypeENUM		LActionType;	    //行為模式

	int		TargetID;				//攻擊或跟隨目標
	int		LTargetID;				//最後一次攻擊的目標(用來檢測是否目標有更換)
	unsigned int	NextAtkTime;			//下一次可攻擊時間
    int     AttackCount;            //攻擊累積次數

    //時間以0.1秒為單位
    int     AddAtkTime;
    int     NextMainAtk;            //下一次主手攻擊
    int     NextSecAtk;             //下一次副手攻擊
	int		DoubleAttackCount;

	int		KeepDistance;			//保持距離

	CampID_ENUM		CampID;			//所屬陣營
};
//-------------------------------------------------------------------------------------
//怪物被打到的資訊
//(仇恨資料)
struct  NPCHateStruct
{
	int		DBID;
	int		ItemID;
	float	HitPoint;
	float	HatePoint;
	float	TempHatePoint;
	int		PartyID;

    void Init()
    {
        DBID        = -1;
        ItemID      = -1;
        HitPoint    = 0;
        HatePoint   = 0;
		TempHatePoint = 0;
		PartyID		= -1;
    };

	float TotalHatePoint()
	{
		return HatePoint + TempHatePoint;
	}
};
//-------------------------------------------------------------------------------------
//怪物仇恨資訊 ， 怪物 ai 使用
struct NPCHateList
{
    StaticVector< NPCHateStruct , _MAX_HATELIST_SIZE_ >     Hate;
	int     MaxHitPoint;					//最大攻擊力
	int		MaxHitLv;						//攻擊者最大的等級
	int		BeginAtkPartyID;
	int		BeginAtkDBID;

	void Init( )
	{
		BeginAtkPartyID = -1;
		BeginAtkDBID = -1;
        MaxHitPoint = 0;
		MaxHitLv = 1;
        Hate.Clear();
		//memset( this , -1 , sizeof(*this) );
	}

    NPCHateStruct*     GetMaxHit( )                  //找出打血最多的人
    {
		map< int , int > PartyHitPointMap;

		for( int i = 0 ; i < Hate.Size() ; i++ )
		{
			if( Hate[i].PartyID <=0 )
				continue;
			PartyHitPointMap[ Hate[i].PartyID ] += Hate[i].HitPoint;
		}


        int MaxHit = -1;
        int MaxHitID = -1;
        for( int i = 0 ; i < Hate.Size() ; i++ )
        {
			int HitPoint = Hate[i].HitPoint;
			if( Hate[i].PartyID > 0 )
			{
				HitPoint = PartyHitPointMap[ Hate[i].PartyID ];
			}

            if( HitPoint > MaxHit )
            {
                MaxHit   = Hate[i].HitPoint;
                MaxHitID = i;
            }
        }

        if( MaxHitID == -1 )
            return NULL;

        
        return &Hate[ MaxHitID ];
    
    }

	NPCHateStruct*     GetMaxHate( )                  //找出最恨的人
	{
		int MaxHate = -1;
		int MaxHateID = -1;
		for( int i = 0 ; i < Hate.Size() ; i++ )
		{
			if( Hate[i].TotalHatePoint() > MaxHate )
			{
				MaxHate   = Hate[i].TotalHatePoint();
				MaxHateID = i;
			}
		}

		if( MaxHateID == -1 )
			return NULL;

		return &Hate[ MaxHateID ];

	}
    
};
//-------------------------------------------------------------------------------------
// 需定時處理的事件
//( 某部份資料有變動 )
//-------------------------------------------------------------------------------------
struct		RoleUpdateEvent
{
	union
	{
		unsigned int		_Event;
		struct
		{
			bool	Bank			:1;		
			bool	Body			:1;		
			bool	Eq				:1;
			bool	Recalculate_Buff:1;		//重新計算Buff
			bool	Recalculate_All	:1;		//所有數值重新計算
			bool	ExpChange		:1;
			bool	LvChange		:1;		//Save
			bool	VocChange		:1;		
            bool	ReSetTalbe		:1;
            bool    Trade           :1;
            bool    HPMPSP          :1;
            bool    MoveSpeed       :1;
			bool	AllZoneInfoChange :1;	//全區須要知道的角色資料改變

			//--------------------------
			bool	FriendListModify:1;		//自己的資訊有改變要通知Chat 並轉通知Client
			bool	SkillKeyItemChange:1;	//技能書類型的重要物品改變
			bool	SkillValueChange:1;		//技能書類型的重要物品改變
			bool	OnAttackPlayer  : 1;	//攻擊玩家
			bool	OnKill			: 1;	//殺死物件
			bool	AccountMoneyLockInfoChange:1;//帳號幣鎖定資料改變
			bool	IsDualDead		: 1;	//比試死亡
        };
	};
	bool	CheckResetItemInfo()
	{
		return Bank|Body|Eq;
	}
};

//-------------------------------------------------------------------------------------
//		容貌結構
//-------------------------------------------------------------------------------------
struct LookStruct
{
    int		FaceID;
    int		HairID;
    int		HairColor;
    int		BodyColor;
	//float	BoneScale[10];
	char	BoneScale[15];
	

    LookStruct()
    {
        memset( this , 0 , sizeof(*this) );
    }

    bool IsEmpty()
    {
        return ( FaceID == 0 && HairID == 0 && HairColor ==0 && BodyColor == 0 );
    }
};
//-------------------------------------------------------------------------------------
//兩人交易結構
struct TradeStruct
{
	int	                Money;
	int					Money_Account;
    int					TargetID;	//交易目標
	int					TargetDBID;	//目標資料庫ID
	
	bool	            SelectOK;	//物品選則OK
	bool	            FinalOK;	//交易成立


	TradeStruct()
	{
		Init();
	};

	void Init()
	{
		memset( this, 0 , sizeof(*this));
		TargetDBID = -1;
		TargetID = -1;
	};
};
//-------------------------------------------------------------------------------------
struct ShopStateStruct
{
    int     TargetID;
    int     ShopObjID;          //販賣物品的物件
    int     ItemCount[30];
	int		LastUpdateTime;		//最後更新數量的時間

    StaticString< _MAX_LUA_FUNTIONNAMESIZE_> ShopClosePlot;	    //商店關閉時執行的劇情

    void Init()
    {
        memset( this , 0 , sizeof(*this) );
    }

};
//-------------------------------------------------------------------------------------
//可被偷竊資訊
struct StealStruct
{
	ItemFieldStruct	Item;	//可被偷竊的物品
	int	ItemSuccessRate;	//成功的機率

	int	Money;				//可被偷竊的金錢
	int	MondySuccessRate;	//成功的機率
};
//-------------------------------------------------------------------------------------
//使用中的物品
struct UseItemStruct
{
    short                 Pos;
    short                 Type;

	UseItemStruct()
	{
		Init();
	};

	void Init()
	{
        Pos = -1;
	};
};
//-------------------------------------------------------------------------------------
//攻擊模式列舉
enum	ATTACK_MODE_ENUM
{
	EM_ATTACKMODE_LEFTHAND	= 0	,	
	EM_ATTACKMODE_RIGHTHAND		,	
	EM_ATTACKMODE_BOTHHAND		,	
	EM_ATTACKMODE_NONE			,
    EM_ATTACK_MODE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//攻擊砍殺類型列舉
enum	ATTACK_DMGTYPE_ENUM
{
	EM_ATTACK_DMGTYPE_MISS,			    //MISS
    EM_ATTACK_DMGTYPE_DODGE,		    //DODGE
	EM_ATTACK_DMGTYPE_HALF,			    //被隔檔
	EM_ATTACK_DMGTYPE_NORMAL,			//一般
	EM_ATTACK_DMGTYPE_DOUBLE,			//會心一擊
	EM_ATTACK_DMGTYPE_TRIPLE,			//必殺一擊
	EM_ATTACK_DMGTYPE_HITBACK,          //反擊
	EM_ATTACK_DMGTYPE_NO_EFFECT,		//沒效果
	EM_ATTACK_DMGTYPE_ABSORB,			//吸收
	EM_ATTACK_DMGTYPE_SHIELD_BLOCK,		//盾檔
    EM_ATTACK_DMGTYPE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//攻擊主副手列舉
enum AttackHandTypeENUM
{
	EM_AttackHandType_None		,
	EM_AttackHandType_Main		,
	EM_AttackHandType_Second	,
};
//-------------------------------------------------------------------------------------
//Local Server 的基本資訊
struct	LocalServerBaseDBInfoStruct
{
	int		ItemVersion;				//目前物品的序號(0 - 9999999) 只有不可堆疊的物品有序號
	float	InstanceResetTime;
	float	InstanceNextResetTime;
	int		HouseItemMaxDBID;

	
	LocalServerBaseDBInfoStruct()
	{
		ItemVersion = 0;
		HouseItemMaxDBID = 0;
		InstanceResetTime = 0;
		InstanceNextResetTime = 0;
	}
};
//-------------------------------------------------------------------------------------
enum	SystemVersionENUM
{
	EM_SystemVersion_TW		,
	EM_SystemVersion_CN		,
	EM_SystemVersion_EN		,
	EM_SystemVersion_JP		,
};

//全域設定資料
struct	GlobalServerDBInfoStruct
{
	float	QuestTpRate;
	float	QuestExpRate;
	float	ExpRate;
	float	DropTreasureRate;
	float	TpRate;
	float	MoneyRate;
	float	PK_DotRate;
	float	PK_DamageRate;
	int		LearnMagicID;
	SystemVersionENUM	Version;

	
	struct
	{
		StaticString< 256 >   LuaCheck;
		int		TableID;
	}GlobalDropTable[5];

	float	NPC_DamageRate;
	float	EqRefineRate;

	GlobalServerDBInfoStruct()
	{
		Init();
	}
	void Init()
	{
		QuestTpRate			= 1.0f;
		QuestExpRate		= 1.0f;
		ExpRate				= 1.0f;
		DropTreasureRate	= 1.0f;
		TpRate				= 1.0f;
		MoneyRate			= 1.0f;
		PK_DotRate			= 1.0f;
		PK_DamageRate		= 0.5f;
		LearnMagicID		= Def_ObjectClass_LearnMagic; 
		Version				= EM_SystemVersion_TW;

		NPC_DamageRate		= 1.0f;
		EqRefineRate		= 1.0f;
		GlobalDropTable[0].TableID = 0;
		GlobalDropTable[1].TableID = 0;
		GlobalDropTable[2].TableID = 0;
		GlobalDropTable[3].TableID = 0;
		GlobalDropTable[4].TableID = 0;
	}
};

//-------------------------------------------------------------------------------------
//party 成員結構
/*
struct	PartyMemberStruct
{
	int		DBID;		//資料庫ID
	int		LocalID;	//區域ID
	int		ZoneID;

    StaticString< _MAX_NAMERECORD_SIZE_ > Name;

	bool	IsEmpty()
	{
        if( this == NULL )
            return true;

		return ( DBID == 0 );
	}
};


//Party結構資料
struct	PartyStruct
{
	short Count;				//成員人數
	int	PartyID;			//隊伍ID
	int	LeaderDBID;			//隊長的資料庫ID
	
  	StaticVector< PartyMemberStruct , _MAX_PARTY_COUNT_ > Member;

};
*/
//-------------------------------------------------------------------------------------
struct NPC_RandomMoveStruct
{
	bool				Enable;		//亂數移動致能	
	int					Active;		//亂數移動激活數 (一秒檢查一次 設定執行機率 % )

    int 				CountDown;	//發動倒數 記錄要走到的時間

	float				CenterX;	//移動範圍中心點X
	float				CenterZ;	//移動範圍中心點Z
	float				MaxRange;	//最遠移動範圍
	
	float				Dist;		//移動距離平均值

	NPC_RandomMoveStruct()
	{
		Init();
	};

	void Init()
	{
		Enable		 = false;
		Active		 = 10;
		CenterX      = -1;	    //移動範圍中心點X
		CenterZ      = -1;	    //移動範圍中心點Z
		MaxRange     = 500;	    //最遠移動範圍
	    
		CountDown    = 0;	    //發動倒數

		Dist         = 100;	    //移動距離平均值
		
	};
};
//-------------------------------------------------------------------------------------
enum	NPC_MoveTypeENUM
{
	EM_NPC_MoveType_None		= 0,//不設定用之前的
	EM_NPC_MoveType_Walk		,//走路 
	EM_NPC_MoveType_Run			,//跑部
	EM_NPC_MoveType_Rand		,//走路或跑步
};

enum	NPC_DirModeEnum
{
	EM_NPC_DirMode_None			= 0, // 不改變
	EM_NPC_DirMode_Change		= 1, // 停留或有劇情時改變
};

//NPC定點移動
struct NPC_MoveBaseStruct
{
	NPC_MoveBaseStruct()
	{
		X				= 0;
		Y				= 0;
		Z				= 0;
		Dir				= 0;
		Range			= 0;
		MoveType		= EM_NPC_MoveType_None;
		WaitTime_Base	= 0;
		WaitTime_Rand	= 0;
		DirMode			= EM_NPC_DirMode_None;
		ActionType		= -1;
		IsUsePathFind	= true;
		sLuaFunc.Clear();
	}

	float				X , Y , Z;			// 移動位置	
	float				Dir;				// 面向
	float				Range;				// 移動偏差距離
	NPC_MoveTypeENUM	MoveType;			// 移動方式
	int					WaitTime_Base;		// 基本等待時間(秒)
	int					WaitTime_Rand;		// 亂數等待時間(秒)
											// 等待時間 = Base + Rand( )
	int					ActionType;			// 動作ID ( -1 忽略)
	StaticString< _MAX_LUA_FUN_ARG_SIZE_ >	sLuaFunc;	
	// 到達定點時, 所觸發的劇情;
	NPC_DirModeEnum		DirMode;			//  到定點後, 若有停留時間或劇情, 需不需要改變面向
	bool				IsUsePathFind;
};

struct DB_NPC_MoveBaseStruct
{
	int		ZoneID;		//區域ID
	int		NPCDBID;	//NPCDBID
	int		IndexID;	//位置
	NPC_MoveBaseStruct Base;
};

//-------------------------------------------------------------------------------------
// 系統管理相關資訊
//-------------------------------------------------------------------------------------
struct SysManageInfoStruct
{
    int						SaveSerial;					//儲存順序號碼
    union
    {
        int     GUID;
        struct
        {
            short   ItemID;            
            short   ZoneID;
        };
    };

    union
    {   //擁有者id
        int     OwnerGUID;
        struct
        {
            short   OwnerItemID;            
            short   OwnerZoneID;
        };
    };
	//同個擁有者 每個Group只能有一個物件 主要用在插仗與寵物
	//GroupID = 0 表示不限制  
	int						OwnerGroupID;									
	int						OwnerDBID;
    int                     WorldGUID;                  		//所有代表同一個物件的物件有相同的 ID

    int						SockID;								//封包收送Id
    int                     ProxyID;                    		//處理的Proxy
    int                     SecRoomID;							//所在空間 -1代表沒加入Partition
    int						SecX,SecZ;							//所在分割區的位置
    long					CreateTime;							//物件產生的時間
    int						LoginProtect;						//登入保護，怪物剛產生與角色剛登入時怪物不會主動攻擊
    int                     MirrorCount;                		//此物件是否有Mirror的物件,有多少個(保留 數值不一定正確 )
    int                     LGUID;
    int                     ChangeZoneTime;             		//可換區時間
	int						KillRate;
	
	StaticString< _MAX_DESTORYOBJ_REASON >   DestroyAccount;	//刪除的者
	union
    {
        int                 _Flag;
        struct
        {
            bool	LuaDebugMsg	    	:1;
            bool	GM_Designed	    	:1;
			bool	OnChangeZone		:1;		//正在換區中
			bool	OnChangeWorld		:1;		//換世界中
			bool	WaitLogout			:1;
			bool	WaitChangeParallel	:1;		//換平行空間中
			bool	WaitWebBagInfo		:1;		//要求載入網頁商城資料
			bool	IsPet				:1;
			bool	WaitUnlockPos		:1;		//卡點解除
			bool	PartitionLock		:1;		//不移動分割區
			bool	NeedFixClientPos	:1;		//座標需要更新
        };
    };

    void Init()
    {
        SaveSerial  = 0;
        GUID        = -1;
        SockID      = -1;
        OwnerGUID   = -1;
        SecRoomID   = -1;
        SecX        = -1;
        SecZ        = -1;
        WorldGUID   = -1;
        LGUID       = -1;
        LoginProtect= 15;
        MirrorCount = 0;
        ChangeZoneTime = 0;
        _Flag  = 0;

        _time32( (long *)(&CreateTime) );
        
	}
};
//-------------------------------------------------------------------------------------
// 路徑處理相關資訊
//-------------------------------------------------------------------------------------
enum	ClientMoveTypeENUM
{
	EM_ClientMoveType_Normal	,
	EM_ClientMoveType_Jump		,
	EM_ClientMoveType_SetPos	,		//中途換目標
	EM_ClientMoveType_Mount		,		//在會移動物件上(載具 如電梯)
	EM_ClientMoveType_SetPetPos	,		//在會移動物件上(載具 如電梯),修正寵物坐標
	EM_ClientMoveType_WaterWalk	,		//在水上行走
	EM_ClientMoveType_OntimeSetCliPos,	//every 0.1 second fix client position
};

struct	PathProcStruct
{
    int			AddeDelay;				//因為特殊事件產生的移動暫停
    int			ProcDelay;				//可以處理移動剩下的時間
    float		Dx , Dy , Dz;			//移動向量
    float		Tx , Ty , Tz;			//npc目標

	float			RetX , RetY , RetZ;							//戰鬥後要退回的位置

	float			BeginJumpX , BeginJumpY , BeginJumpZ;		
    unsigned int     BeginJumpTime;								//起跳時間

    unsigned int      LastMoveTime;     //最後移動的時間
	ClientMoveTypeENUM	MoveType;		//記錄玩家移動的方式
	//----------------------------------------------------------
	//(用來檢查是否有加速)
	float		CliX , CliY , CliZ;		//Cli端最後一次送出的位置
	float		LOK_CliX , LOK_CliY , LOK_CliZ;

	float		CalMoveLen;				//移動總計
	unsigned int		CliLastMoveTime;
	int			PacketErrorCount;		//計算移動封包錯誤數量
	int			MoveTotalDistErrCount;	//移動總量錯誤次數
	//----------------------------------------------------------
	bool		IsLockSetPos;
	float		LockSetPosX , LockSetPosZ;
	int			LockTargetPosX , LockTargetPosZ;	//目標位置鎖定 ( PosList Map的位置 用來處理怪物移動不重疊 )
	//----------------------------------------------------------
	int			MoveHeightErrorCount;

	float		LCheckLineX,LCheckLineY,LCheckLineZ;
	float		LCheckDeadZoneX,LCheckDeadZoneY,LCheckDeadZoneZ;
	int			LCheckMovePGDir;

};
//-------------------------------------------------------------------------------------
#define _MAX_RENT_MENBER_RANK_ 20
#define _MAX_RENT_FUNCTION_ ( _MAX_RENT_COUNT_ - _MAX_RENT_MENBER_RANK_ )
struct RentFuncStruct
{
	union
	{
		unsigned RentTime[ _MAX_RENT_COUNT_ ];
		struct  
		{
			unsigned Member[ _MAX_RENT_MENBER_RANK_ ];
			unsigned	Function[ _MAX_RENT_FUNCTION_ ];
		};
	};
};
//-------------------------------------------------------------------------------------
//登入定時處理的事件資訊
//-------------------------------------------------------------------------------------
struct SimpleSchedularInfo
{
    int      SearchEnemyID;
    int      MoveID;
    int      AiID;
    int      AttackID;
    int      SpellMagicID;
};
//-------------------------------------------------------------------------------------
enum SmallGameTypeEnum
{
    EM_SmallGameType_None       = 0 ,
    EM_SmallGameType_WaitJoin      ,
    EM_SmallGameType_Big2           ,
};
struct  SmallGameInfoStruct
{
    SmallGameTypeEnum GameType;              //表示smallgame ok

     
//    int     TradeMoney;         //轉出去的金錢
};
//-------------------------------------------------------------------------------------
enum ItemFieldTypeENUM
{
	EM_ItemFieldType_Body	= 1		,
	EM_ItemFieldType_Bank			,
	EM_ItemFieldType_EQ				,
	EM_ItemFieldType_DestroyItem	,
	EM_ItemFieldType_TempItem		,
	EM_ItemFieldType_EQBackup		,
	EM_ItemFieldType_Pet			,
};
//-------------------------------------------------------------------------------------
//資料庫物品欄位資訊
struct DB_ItemFieldStruct
{
	int	DBID;
	int FieldID;
	int	FieldType;

	ItemFieldStruct Info;
};
//-------------------------------------------------------------------------------------
//角色屬性
struct DB_AbilityStruct
{
	int	DBID;
	int	Job;

	BaseAbilityStruct Info;
};


//-------------------------------------------------------------------------------------
// 任務結構

enum EM_QUESTCHECK_RESULT
{
	EM_QUESTCHECK_RESULT_OK				= 0,
	EM_QUESTCHECK_RESULT_NOTEXIST		,	// NPC 不存在
	EM_QUESTCHECK_RESULT_TOOFAR			,	// 距離 Quest NPC 太遠
	EM_QUESTCHECK_RESULT_FULL			,	// Clinet 所擁有的 Quest 清單已滿
	EM_QUESTCHECK_RESULT_NOTLIST		,	// Clinet 所擁有的 Quest 清單上並沒有該項 Quest
	EM_QUESTCHECK_RESULT_NOTOK			,	// 檢查完成條件時發現尚未完成
	EM_QUESTCHECK_RESULT_RUNNINGSCRIPT	,	// NPC 正在執行劇情中
	EM_QUESTCHECK_RESULT_ALREADYEXIST	,	// USER 已經擁有該任務
	EM_QUESTCHECK_RESULT_ALREADYDONE	,	// USER 已經完成該任務
	EM_QUESTCHECK_RESULT_DAILYDONE		,	// USER 今天已完成過每日任務了
	EM_QUESTCHECK_RESULT_QUESTERR		,	// 任務代號不存在
	EM_QUESTCHECK_RESULT_GROUPFULL		,	// 任務群組已滿
	EM_QUESTCHECK_RESULT_NOQUESTITEM	,	// 任務需求物品不足	( CLIENT 作弊 )
};


struct QuestStruct
{
	struct QuestInfo
	{
		int		iQuestID;
		BYTE	iMode;			// 0 表一般任務, 1 表執行中任務, -1 表任務失敗( 名稱後面加失敗 )
		BYTE	iQuestKillCount[_MAX_QUEST_KILLKIND_COUNT_];

	} QuestLog[ _MAX_QUEST_COUNT_ ];		// Client 身上有的 Quest 清單

	StaticFlag<_MAX_QUEST_FLAG_COUNT_>			QuestHistory;						// 目前最多 2048 個 Quest , 用來紀錄那些 Quest 已完成
	//BYTE 										iQuestKillCount[_MAX_QUEST_COUNT_][_MAX_QUEST_KILLKIND_COUNT_];
																					// 紀錄目前任務, 宰殺紀錄  20 Quest, 3 Kind

	// 每日重置的任務部份
	time_t			LastCompleteTime;								// 上次執行任務的時間, 一但超過每日的 24:00 時, 便將此結構清空
	int				iQuestGroup[DF_QUESTDAILY_MAXGROUP];			// 一共有 10 個組別, 每個組別有各自的計數器, 系統預設 10, 一定完成 10 個之後便不能再解

	StaticFlag<_MAX_QUEST_FLAG_COUNT_>			QuestDaily;			// 目前最多 2048 個 Quest , 用來紀錄那些每日任務已完成, 於每日 24 時重置

	int	HistoryCount()
	{
		int Count = 0;
		for( int i = 0 ; i < _MAX_QUEST_FLAG_COUNT_ ; i++ )
		{
			if( QuestHistory.GetFlag( i ) != false )
				Count++;
		}
		return Count;
	}

};

struct QuestKillStruct
{
	int		iKillObj		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 指定打倒目標的樣版代號
	int		iKillVal		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 指定打倒目標的數量
	float	fDropPercent	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 打倒指定目標掉落機率
	int		iDropItem		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 掉落物品
	int		iDropItemVal	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 掉落物品數量
};

struct QuestClickStruct
{
	int		iClickObj		[ _MAX_QUEST_CLICKIND_COUNT_ ];
	float	fProcPercent	[ _MAX_QUEST_CLICKIND_COUNT_ ];
	int		iDropItem		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 掉落物品
	int		iDropItemVal	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// 掉落物品數量
};



/*
struct QuestTempDataStruct
{
	BYTE				QuestKillCount;
	BYTE				QuestKillIndexTable		[ _MAX_QUEST_COUNT_ ];	// 紀錄是第幾個 QuestField 有打倒計數	
	QuestKillStruct		QuestKill				[ _MAX_QUEST_COUNT_ ];

	BYTE				QuestCollectCount;
	BYTE				QuestCollectIndexTable	[ _MAX_QUEST_COUNT_ ];
	QuestClickStruct	QuestCollect			[ _MAX_QUEST_COUNT_ ];

	int					iQuestResult;
};
*/
enum CastingTypeENUM
{
	EM_CastingType_NULL			=-1		,
	EM_CastingType_NormalUseItem		,
	EM_CastingType_Dissolution			,
	EM_CastingType_SetRune				,
	EM_CastingType_RefineEq				,

	EM_CastingType_OKRESULT		=100	,
//	EM_CastingType_DissolutionOK		,
//	EM_CastingType_SetRuneOK			,
//	EM_CastingType_RefineEqOK			,
};

// 採礦, 取得任務物件時排程給予物品的紀錄
enum ENUM_CASTINGMODE
{
	EM_CASTING_NONE				= 0,
	EM_CASTING_QUESTOBJ			,
	EM_CASTING_MINE				,
	EM_CASTING_HERB			
};

struct CastingData
{
	void Clear()
	{
		//ZeroMemory( this, sizeof(this) );
		iEventHandle		= -1;
		emMode				= EM_CASTING_NONE;
		iGUID				= 0;
		iLockGUID			= 0;
		//iQuestID			= 0;
		//iClickObj			= 0;
		iClickObjID			= 0;
		iLockTime			= 0;
		iEndTime			= 0;
		iContext			= 0;
		pCastFunc			= NULL;
		bBeHit				= false;

		szLuaEvent			= "";

		ZeroMemory( &SourcePos, sizeof( RolePosStruct ) );
	}

	int					iEventHandle;			// 推入 Schedular 所產生的代碼
	ENUM_CASTINGMODE	emMode;
	int					iGUID;
	int					iLockGUID;				// 由那個人物對此物件產生動作
	//int					iQuestID;
	int					iContext;				// 各系統用來暫存的資料
	int					iClickObj;
	int					iClickObjID;
	int					iClickGetObj;
	int					iLockTime;				// 要是有鎖死物件, 故意將時間拉長, 讓同一個玩家能夠確定擁有同一個礦的權力
	int					iEndTime;				// 束的時間

	RolePosStruct		SourcePos;				// 開始施展時, 人物的座標
	PVOID				pCastFunc;				
	bool				bBeHit;					// 施法過程中是否有被攻擊
	StaticString< 64 >	szLuaEvent;

};

// 點擊系統用, 檢測事件, 使用前先清除, 然後檢查下列事件有無變化
struct	ScriptEventFlagStruct
{	
	union
	{
		int _Event;
		struct
		{
			bool    bMove							: 1;	// 從上次設定狀態後移動發生
			bool    bCastSpell						: 1;	// 從上次設定狀態後使用過技能
			bool    bHited			  				: 1;	// 從上次設定狀態後被擊中過
			bool	bUseItem						: 1;	// 從上次設定狀態後有沒有使用過物品
			bool	bSit							: 1;	// 從上次設定狀態後有沒有做下過
			bool	bMotionChange					: 1;	// 從上次設定狀態後有沒有改變動做
		};
	};

	void Clear() { _Event = 0; }
};

//-------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//			公會資料設定
//////////////////////////////////////////////////////////////////////////
//公會功能設定
struct GuildManageSettingStruct
{
	union
	{
		int		Type;
		struct  
		{
			bool	Invite				: 1;	//招收
			bool	AdjustRank			: 1;	//調整階級
			bool	SetGuildNote		: 1;	//設定公告
			bool	Kick				: 1;	//踢除會員
			bool	AdjustGroup			: 1;	//調整群組
			bool	EditMemberNote		: 1;	//設定成員註解
			bool	PostMessage			: 1;	//留言
			bool	ManageMessage		: 1;	//留言板管理
			bool	Building			: 1;	//公會建築
			bool	Furniture			: 1;	//裝潢品擺設
			bool	GuildWarRegister	: 1;	//註冊公會戰
			bool	SetGuildHouseStyle	: 1;	//設定工會屋樣式
		};
	};
};
//-------------------------------------------------------------------------------------
//公會等級
enum  GuildRankENUM
{
	EM_GuildRank_0			,
	EM_GuildRank_1			,
	EM_GuildRank_2			,
	EM_GuildRank_3			,
	EM_GuildRank_4			,
	EM_GuildRank_5			,
	EM_GuildRank_6			,
	EM_GuildRank_7			,
	EM_GuildRank_8			,
	EM_GuildRank_Leader		,

	EM_GuildRank_Count		,

};
//-------------------------------------------------------------------------------------
struct GuildStruct;

//公會成員資料
struct GuildMemberStruct
{
	GuildStruct*			Guild;				//公會資料聯結

	int						GuildID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   MemberName;
	int						MemberDBID;
	GuildRankENUM			Rank;				//角色公會等級
	int						GroupID;			//所在群組
	StaticString< 256 >   	SelfNote;			//自己註解
	StaticString< 256 >   	LeaderNote;			//會長的註解
	int						RankTime;			//就職時間
	bool					IsNeedSave;			//如果資料有更動則會為 true
	bool					IsOnline;

	Voc_ENUM				Voc;
	Voc_ENUM				Voc_Sub;
	Sex_ENUM				Sex;
	int						LV;
	int						LV_Sub;
	int						LogoutTime;

	GuildMemberStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//公會Rank 資料
struct GuildRankBaseInfoStruct
{
	GuildManageSettingStruct				Setting;
	StaticString< _MAX_NAMERECORD_SIZE_ >   RankName;	//名稱
};
//-------------------------------------------------------------------------------------
struct GuildFlagStruct
{
	int InsigniaType;
	int InsigniaMainColor;
	int InsigniaOffColor;
	int BannerType;
	int BannerMainColor;
	int BannerOffColor;
};
//-------------------------------------------------------------------------------------
//簡易的公會資料
struct SimpleGuildInfoStruct
{
	int		GuildID;
	GuildResourceStruct Resource;			//資源
	/*
	int		WarMyScore;						//我方積分
	int		WarMyKillCount;
	int		WarEnemyScore;					//敵方積分
	int		WarEnemyKillCount;
	*/
};
//-------------------------------------------------------------------------------------
struct GuildInfoChangeStruct
{
	union
	{
		int Mode;
		struct
		{
			bool	GuildMessage	: 1;//公會設定修改
		};
	};
};
//-------------------------------------------------------------------------------------
#define		_MAX_GUILD_GROUP_COUNT_	10
#define		_MAX_GUILD_BUYFUNCTION_COUNT_ 256 
//公會結構
struct GuildBaseStruct
{
	int		GuildID;									//公會ID
	StaticString< _MAX_NAMERECORD_SIZE_ >   GuildName;	//公會名稱
	StaticString< _MAX_NAMERECORD_SIZE_ >   LeaderName;	//會長名稱
	int		LeaderDBID;
	union
	{
		int GuildType;
		struct  
		{
			bool	IsRecruit			:1;						//是否招生
			bool	IsReady				:1;						//是否正式成立
			bool	IsEnabledGuildBoard :1;						//開起留言板功能
			bool	IsWar				:1;						//是否有跟別人宣戰
			bool	IsNeedChangeName	:1;						//需要改名
			bool	IsWarPrepare		:1;						//準備開戰
			bool	IsOwnHouse			:1;						//擁有房屋
			bool	IsLockGuildHouse	:1;						//公會屋是否可進入
		};
	};
	bool	IsNeedUpdateSmipleInfo;			//及時更新的資料
	bool	IsNeedSave;						//如果資料有更動則會為 true

	int		Level;							//公會等級
	int		Medal;							//徽章
	int		MaxMemberCount;					//最多可以有多少會員

	GuildResourceStruct Resource;			//資源

	int		WarGuildID;						//敵對公會
	int		WarMyScore;						//我方積分
	int		WarMyKillCount;
	int		WarEnemyScore;					//敵方積分
	int		WarEnemyKillCount;
	int		WarTime;						//戰爭結束時間

	int		WarWinCount;					//勝場
	int		WarEvenCount;					//平手
	int		WarLostCount;					//敗場
	int		WarDeclareTime;					//宣戰時間

	struct
	{
		int		WinCount;					//勝場
		int		EvenCount;					//平手
		int		LostCount;					//敗場
		int		Score;
		int		NextWarTime;				//下一次公會屋戰時間
	}HousesWar;	//公會屋戰
	
	GuildFlagStruct		GuildFlag;			//公會旗資訊

	StaticString< 512 >   Note;				//公告
	StaticString< 512 >   Introduce;		//公會介紹

	int		RankCount;						//公會階層數
	GuildRankBaseInfoStruct	Rank[ EM_GuildRank_Count ];						//每個等級的權限 與名稱
	StaticString< _MAX_NAMERECORD_SIZE_ >   Group[_MAX_GUILD_GROUP_COUNT_];	//群組名稱
	StaticFlag< _MAX_GUILD_BUYFUNCTION_COUNT_ >	Flag;	
	//int		LastCalRentTime;				//最後一次計算維持費的時間

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GuildFlag.BannerMainColor   = 0xffffffff;
		GuildFlag.BannerOffColor    = 0xff000000;
		GuildFlag.InsigniaMainColor = 0xffffffff;
		GuildFlag.InsigniaOffColor  = 0xff000000;
		HousesWar.Score				= 1000;
	}
};
//-------------------------------------------------------------------------------------
//留言版狀態
struct GuildBoardModeStruct
{
	union
	{
		int		_Type;
		struct  
		{
			bool	Top : 1;	//置頂
			bool	Del : 1;	//被刪除
		};
	};

};

//公會留言板
struct GuildBoardStruct
{
	int						GUID;		//序號
	int						GuildID;	//公會ID
	GuildBoardModeStruct	Type;		//狀態
	StaticString< 128 >		Title;		//標題
	StaticString< 512 >		Message;	//訊息
	int						Time;		//發表時間
	StaticString< _MAX_NAMERECORD_SIZE_ >   PlayerName;	    //發表人
};

//////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------
//法術Buff資料 
struct BuffBaseStruct
{
    int     OwnerID;
    int     BuffID;         //魔法ID
    int     Time;           //剩下時間(秒)
	int		Power;			//威力( 魔法累積等級 )
	int		Point;			//點數( 魔法盾可擋點數 or 次數)
	
	union
	{
		int Mode;
		struct
		{
			bool	IsPK	: 1;
			bool	IsErase	: 1;	//因為特別原因清除
		};
	};

	GameObjDbStruct*	Magic;	
};
//-------------------------------------------------------------------------------------
//法術Buff資料
struct RefineBuffStruct
{
	int RecipeID;
	int	Coldown;
};
//-------------------------------------------------------------------------------------
//角色資料貝份,用來更新周圍環境資訊
struct RoleBackupInfo
{
	ObjectModeStruct Mode;
    //數值
    int     MaxHP;
    int     MaxMP;
    int     MaxSP;
    int     MaxSP_Sub;
    int     HP;
    int     MP;
    int     SP;
	int		SP_Sub;
	int		StomachPoint;

	int		GuildID;		
	int		TitleID;
	bool	IsShowTitle;

	int		LastSkillHitPoint;		//最後一次技能傷害
	int		LastPhyHitPoint;		//最後一次一般殤害

	unsigned int	LastCriticalTime;				//最後一次Cirtical 時間
	unsigned int	LastBeCriticalTime;				//最後一次被Cirtical 時間
	unsigned int	LastMagicCriticalTime;			//最後一次Cirtical 時間
	unsigned int	LastBeMagicCriticalTime;		//最後一次被Cirtical 時間

	unsigned int	LastDodgeTime;			//最後一次Dodge 時間
	unsigned int	LastMissTime;			//最後一次Miss 時間
	unsigned int	LastParryTime;			//最後一次Parry 時間
	unsigned int	LastBeParryTime;		//最後一次被Parry 時間
	unsigned int	LastBeDodgeTime;		//最後一次被Dodge 時間
	unsigned int	LastShieldBlockTime;	//最後一次 盾檔 時間
	unsigned int	LastBeShieldBlockTime;	//最後一次被盾檔 時間

	int		MoveSpeed;

	MagicClearTimeStruct	BuffClearTime;	//需要清除的法術Buff
    //跳或掉落起始
    bool    StartJump;
    float   Y;

	int		LZoneID;	//最後移除於分割區的位置
	float	LX , LZ;	//最後移除於分割區的位置

	float	JumpRate;
	float	Gravity;

	int		HEvent_Ai;
	int		HEvent_Move;


	PlayerBackupInfoStruct	ZonePlayerInfo;
};
//-------------------------------------------------------------------------------------
#define DEF_MAX_COLDOWN_COUNT_JOB_	500
#define DEF_MAX_COLDOWN_COUNT_EQ_	15
#define DEF_MAX_COLDOWN_COUNT_ITEM_	80
#define DEF_MAX_COLDOWN_COUNT_ALL	( DEF_MAX_COLDOWN_COUNT_JOB_ + DEF_MAX_COLDOWN_COUNT_EQ_ + DEF_MAX_COLDOWN_COUNT_ITEM_ + 1 )
#define DEF_COLDOWN_ALL_POS			0
#define DEF_COLDOWN_JOB_POS			1
#define DEF_COLDOWN_EQ_POS			( DEF_COLDOWN_JOB_POS + DEF_MAX_COLDOWN_COUNT_JOB_ )
#define DEF_COLDOWN_ITEM_POS		( DEF_COLDOWN_EQ_POS + DEF_MAX_COLDOWN_COUNT_EQ_ )
//所有法術Coldown
struct MagicColdownStruct
{
	union
	{
		int	All[ DEF_MAX_COLDOWN_COUNT_ALL];
		struct  
		{
			int	AllMagic;								//下次可失法的時間 (所有法術)
			int	Job	[ DEF_MAX_COLDOWN_COUNT_JOB_  ];	
			int	Eq	[ DEF_MAX_COLDOWN_COUNT_EQ_   ];	
			int	Item[ DEF_MAX_COLDOWN_COUNT_ITEM_ ];
		};
	};

	//需要更新時間的位置
	StaticVector< short , DEF_MAX_COLDOWN_COUNT_ALL > NeedUpdatePos;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
enum FriendListTypeENUM
{
	EM_FriendListType_Friend	,
	EM_FriendListType_HateFriend,
	EM_FriendListType_FamilyFriend,
};

enum FriendListInsertResultENUM
{
	EM_FriendListInsertResult_OK		,
	EM_FriendListInsertResult_Modify	,
	EM_FriendListInsertResult_Failed	,
};


//好友名單
struct BaseFriendStruct
{
	bool	IsSave;
	RelationTypeENUM	Relation;
	int		DBID;							//角色dbid
	char	Name[_MAX_NAMERECORD_SIZE_];	//角色名稱
	float	Lv;								//關係等級



	union
	{
		char	Note[ 60 ];	    //對朋友的註解
		struct 
		{
			Race_ENUM			Race;								//種族
			Voc_ENUM		    Voc;								//職業
			Voc_ENUM		    Voc_Sub;							//副職業
			Sex_ENUM			Sex;								//性別
			int					JobLv;
			int					JobLv_Sub;
			int					GuildID;
			int					TitleID;
			int					Time;

			union
			{
				struct //好友用struct
				{//client 編輯
					int		GroupID : 16;					//資料夾號碼
		//			int		ClientInfo1;
		//			int		ClientInfo2;
				};

				struct //仇人用struct
				{
					int		KillMeCount  : 16; //殺我次數
					int		RevengeCount : 16; //報仇次數
					bool    top          :  1; //置頂
				};
			};

		};
	};


	bool IsEmpty()
	{
		return ( DBID <= 0 );
	}
	void Clear()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

struct FriendListStruct 
{
	StaticString< _MAX_FRIENDLIST_NOTE_ >   Note;	    //自己註解

	union
	{
		BaseFriendStruct	AllFriendList[ _MAX_FRIENDLIST_ALL_COUNT_ ];
		struct
		{
			BaseFriendStruct	FamilyList[ _MAX_FRIENDLIST_FAMILY_COUNT_ ];			//好有名單
			BaseFriendStruct	FriendList[ _MAX_FRIENDLIST_COUNT_ ];			//好有名單
			BaseFriendStruct	HateFriendList[ _MAX_HATE_PLAYER_LIST_COUNT_ ];	//仇恨名單列表
		};
	};
	
	union
	{
		char	ClientData[ _MAX_BAD_FRIENDLIST_COUNT_ + _MAX_FRIENDLIST_GROUP_COUNT_ ][_MAX_NAMERECORD_SIZE_ ];
		struct
		{
			char	BadFriendList[ _MAX_BAD_FRIENDLIST_COUNT_ ][_MAX_NAMERECORD_SIZE_];
			char	GroupName[ _MAX_FRIENDLIST_GROUP_COUNT_ ][_MAX_NAMERECORD_SIZE_];
		};
	};

	void	FixupData()
	{
		int maxCount;
		BaseFriendStruct* pList;
		for( int i = 0 ; i < 3 ; i++ )
		{
			vector< BaseFriendStruct > friendList;
			GetListInfo( (FriendListTypeENUM)i , &pList , maxCount );

			for( int i = 0 ; i < maxCount ; i++ )
			{
				if( pList[i].IsEmpty() )
					continue;
				friendList.push_back( pList[i] );
				memset( &pList[i] , 0 , sizeof(BaseFriendStruct) );
			}
			
			for( unsigned i = 0 ; i < friendList.size() ; i++ )
			{
				pList[i] = friendList[i];
			}
		}

	}

	char	GroupSortID[ _MAX_FRIENDLIST_GROUP_COUNT_  ];

	void	GetListInfo( FriendListTypeENUM Type , BaseFriendStruct** pList , int& MaxCount )
	{
		switch( Type )
		{
		case EM_FriendListType_Friend:
			MaxCount = _MAX_FRIENDLIST_COUNT_;
			*pList = FriendList;
			break;
		case EM_FriendListType_HateFriend:
			MaxCount = _MAX_HATE_PLAYER_LIST_COUNT_;
			*pList = HateFriendList;
			break;
		case EM_FriendListType_FamilyFriend:
			MaxCount = _MAX_FRIENDLIST_FAMILY_COUNT_;
			*pList = FamilyList;
			break;
		default:
			MaxCount = -1;
			*pList = NULL;
			break;
		}
	};
	FriendListInsertResultENUM	Insert( FriendListTypeENUM Type , int Pos , BaseFriendStruct& Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;
		bool				IsEarse;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return EM_FriendListInsertResult_Failed;

		if( Pos >= MaxCount || Pos < 0 )
			return EM_FriendListInsertResult_Failed;

		IsEarse = Erase( Type , Info.DBID );

		for( int i = MaxCount-1 ; i > Pos ; i-- )
		{
			pList[i] = pList[i-1];
		}
		pList[Pos] = Info;
		pList[Pos].IsSave = false;

		if( IsEarse )
			return EM_FriendListInsertResult_Modify;

		return EM_FriendListInsertResult_OK;
	};
	bool	Erase( FriendListTypeENUM Type , int DBID )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		bool IsFind = false;
		for( int i = 0 ; i < MaxCount-1 ; i++ )
		{
			if( IsFind == false && pList[i].DBID != DBID )
				continue;

			IsFind = true;
			pList[i] = pList[i+1];
		}
		pList[MaxCount-1].Clear();

		return IsFind;
	};
	bool	Modify( FriendListTypeENUM Type , BaseFriendStruct& Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].DBID == Info.DBID )
			{
				bool IsSave = pList[i].IsSave;
				pList[i] = Info;
				pList[i].IsSave = IsSave;
				return true;
			}
		}
		return false;
	};

	int	FindFriendInfo( FriendListTypeENUM Type , int DBID , BaseFriendStruct** Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].DBID == DBID )
			{
				*Info = &(pList[i]);
				return i;
			}
		}

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].IsEmpty() )
			{
				*Info = &(pList[i]);
				return i;
			}
		}

		return -1;
	}
	
};


//-------------------------------------------------------------------------------------
//好友名單 (資料庫存取用)
struct DB_BaseFriendStruct
{
	int OwnerDBID;
	int FieldID;
	FriendListTypeENUM	Type;
	BaseFriendStruct Info;
};
//-------------------------------------------------------------------------------------
//所有線上玩家基本資料(送網路封包使用)
struct OnlinePlayerInfoStruct
{
	StaticString< _MAX_ACCOUNT_SIZE_	>   Account;    //帳號
	StaticString< _MAX_NAMERECORD_SIZE_ >   Name;	    //角色名稱	
	int				DBID;
	int				SockID;		//封包收送Id
	int     		ProxyID;    //處理的Proxy
	int				GuildID;	//公會 ID
	int				RoomID;
	bool			IsShowTitle;
	int				TitleID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   TitleStr;	//自定稱號
	StaticString< _MAX_FRIENDLIST_NOTE_ >   Note;	    //自己的註解	

	union
	{
		struct
		{
			short   ItemID;            
			short   ZoneID;
		};
		int				GUID;							// 區域物件ID
	};

	Race_ENUM		Race;
	Voc_ENUM		Voc;
	Voc_ENUM		Voc_Sub;
	Sex_ENUM		Sex;
	LookStruct		Look;
	int				LV;
	int				LV_Sub;
	int				ParallelID;

	PlayerStateStruct	State;	//玩家全區狀態
};
//-------------------------------------------------------------------------------------
//公會屋戰歷史資料
struct GuildHouseWarHistoryStruct
{

	int		GuildID;
	int		TargetGuildID;
	float	EndFightTime;
	int		Result;
	int		GuildScore;
	int		TargetGuildScore;
	StaticString<_MAX_NAMERECORD_SIZE_> TargetGuildName;		
	GuildHouseWarHistoryStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//公會資料結構
struct GuildStruct
{
	GuildBaseStruct						Base;
	vector<GuildMemberStruct*>			Member;

	vector<GuildBoardStruct*>			BoardAll;		//所有的留言
	vector<GuildBoardStruct*>			BoardList;		//最新的60筆資料
	deque<GuildHouseWarHistoryStruct>	GuildWarHistory;


	GuildStruct()
	{
		Base.Init();
	};
	void ClearMemory()
	{
		for( int i = 0 ; i < (int)Member.size() ; i++ )
		{
			delete Member[i];
		}
		Member.clear();

		for( unsigned i = 0 ; i < BoardAll.size() ; i++ )
		{
			delete BoardAll[i];
		}
		BoardAll.clear();
		BoardList.clear();

	};

	//處理置頂
	bool	MessageSetTop( int MessageID , bool Flag )
	{

		if( Flag != false )
		{	//設為Top
			int TopCount = 0;
			for( unsigned i = 0 ; i < BoardList.size() ; i++ )
			{
				GuildBoardStruct* Msg = BoardList[i];
				if( Msg->Type.Top != false )
					TopCount++;

				if( MessageID != Msg->GUID )
					continue;

				if( Msg->Type.Top != false )
					return true;

				Msg->Type.Top = true;
				BoardList.erase( BoardList.begin() + i );
				BoardList.insert( BoardList.begin() + TopCount , Msg );
				return true;
			}

		}
		else
		{
			int TopCount = 0;
			GuildBoardStruct* Msg = NULL;
			int	MsgPos = -1;
			for( unsigned i = 0 ; i < BoardList.size() ; i++ )
			{
				GuildBoardStruct* TempMsg = BoardList[i];

				if( TempMsg->Type.Top == false )
					break;

				TopCount++;
				
				if( MessageID != TempMsg->GUID )
					continue;

				Msg = TempMsg;
				MsgPos = i;
			}

			if( Msg != NULL )
			{
				Msg->Type.Top = false;
				BoardList.erase( BoardList.begin() + MsgPos );
				BoardList.insert( BoardList.begin() + (TopCount - 1) , Msg );
				return true;
			}
		}
		return true;
	}

	
};
//-------------------------------------------------------------------------------------
//信件背景類型
enum	MailBackGroundTypeENUM
{
	EM_MailBackGroundType_Gift		= -2,
	EM_MailBackGroundType_System	= -1,
	EM_MailBackGroundType_Normal	= 0,
	EM_MailBackGroundType_Max		= 5,
};

struct MailBaseInfoStruct
{
	ItemFieldStruct		Item[10];	//資料簡查
	int		Money;
	int		Money_Account;
	int		Money_Bonus;

	bool	IsSendMoney;		//true 寄送金錢 false 獲到付款
	bool	IsSystem;			//是否為系統信件
	bool	IsRead;
	bool	IsSendBack;			//是否為退回信件
	bool	IsGift;				//是送理資料

	int		AcDBID;				//如果不是0 , 則表示是AC發出來的信件

	StaticString <_MAX_NAMERECORD_SIZE_>	OrgSendName;
	StaticString <_MAX_NAMERECORD_SIZE_>	OrgTargetName;

	StaticString <_MAX_NAMERECORD_SIZE_>	Title;
	int		LiveTime;				//生存時間( 單位(分鐘) )
	MailBackGroundTypeENUM PaperType;

	void initItem()
	{
		memset( Item , 0 , sizeof(Item) );
	};

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//-------------------------------------------------------------------------------------
//Mail 資料結構
struct DB_MailStruct
{
	int		GUID;
//	int		ItemGUID;
	int		OwnerDBID;
	int		OrgSendDBID;			//原始送件者
	
	MailBaseInfoStruct	MailBase;
	StaticString<2048>	Content;

	void Init()
	{
		GUID = -1;
//		ItemGUID = -1;
		OwnerDBID = -1;
		OrgSendDBID = -1;			
		Content.Clear();
	};

	DB_MailStruct()
	{
		Init();
	};
};
//--------------------------------------------------------------------------------------------
struct DB_MailItemStruct
{
	int				MailBaseGUID;		//Mail DB 號碼
	ItemFieldStruct Item;
};
//--------------------------------------------------------------------------------------------
enum	ACItemStateENUM
{
	EM_ACItemState_Normal	,
	EM_ACItemState_BuyOut	,
	EM_ACItemState_Cancel	,
};

struct DB_ACItemStruct
{
	int		GUID;					//在AC的資料庫ID
	StaticString <_MAX_NAMERECORD_SIZE_>	SellerName;		//賣方名字
	StaticString <_MAX_NAMERECORD_SIZE_>	BuyerName;		//買方名字

	int		NowPrices;
	int		BuyOutPrices;
	PriceTypeENUM PricesType;
	int		BuyerDBID;
	int		SellerDBID;
	int		LiveTime;				//可生存時間
	int		ItemLevel;				//物品等級

	ItemFieldStruct		Item;		//賣的東西
	StaticString <_MAX_NAMERECORD_SIZE_>	ItemName;		//物品名稱
	int		ItemType[3];			//物品分類
	int		Rare;
	int		RuneVolume;

	SexFlagStruct				SexType;			//性別				
	RaceFlagStruct				RaceType;			//種族			
	VocationFlagStruct			JobType;			//職業
	EqWearSkillStruct			EQType;				//裝備類形
	
	ACItemStateENUM				State;
	int							ImportAcItemGUID;
};
//--------------------------------------------------------------------------------------------
struct  DB_ACItemHistoryStruct
{
	int		GUID;
	StaticString <_MAX_NAMERECORD_SIZE_>	SellerName;		//賣方名字
	StaticString <_MAX_NAMERECORD_SIZE_>	BuyerName;		//買方名字

	int		Date;	//賣出時間
	int		Prices;
	int		BuyerDBID;
	int		SellerDBID;
	PriceTypeENUM PricesType;

	ItemFieldStruct		Item;	//賣的東西
};
//-------------------------------------------------------------------------------------
//Server事件訊息列舉
enum	GameMessageEventENUM
{
	EM_GameMessageEvent_OK								,	//沒有問題
	EM_GameMessageEvent_Failed							,	//一般失敗

	EM_GameMessageEvent_FightNoLogout					,	//戰鬥中不可登出
	EM_GameMessageEvent_ChanageZoneError_PraviteZoneFull,	//獨立區域滿了
	EM_GameMessageEvent_ChanageZoneError_Failed			,	//換區失敗
	EM_GameMessageEvent_MoveSpeedDataError				,	//移動資料有問題
	EM_GameMessageEvent_MoveSpeedToFastError			,	//移動加速??
	EM_GameMessageEvent_TotalMoveSpeedToFastError		,	//移動總量加速??
	EM_GameMessageEvent_MoveVectorError					,	//移動向量過大
	EM_GameMessageEvent_NoMove							,	//目前被施展定身法術，不可移動
	EM_GameMessageEvent_CharacterNotFound				,	//角色不存在
	EM_GameMessageEvent_TalkDisable						,	//禁言中
	EM_GameMessageEvent_ItemLock						,	//物品被密碼鎖住，不能使用
	EM_GameMessageEvent_NeedSysChannelItem				,	//缺少發送系統頻道的物品
	EM_GameMessageEvent_SecondPasswordError				,	//二次密碼輸入錯誤
	EM_GameMessageEvent_ZoneChannelLevelErr				,	//致少要有一個職業等級超過12級，才可使用區頻
	EM_GameMessageEvent_PKItemProtect					,	//PK物品懲罰保護
	EM_GameMessageEvent_VisitGuildHouse_OpenYet			,	//參觀公會屋介面開啟中
	EM_GameMessageEvent_TellCharacterNotFound			,	//角色不在線上，可能會收不到此訊息
	EM_GameMessageEvent_Mail_RoleLvError				,	//角色等級不足，無法寄信
	EM_GameMessageEvent_TargetHasParty					,	//目標已加入隊伍

	EM_GameMessageEvent_Party_AssistPlayerDBID_Error	,	//指定玩家不在線上

	EM_GameMessageEvent_DepartmentBagFull				,	//商城包已滿，物品無法取得
	
	EM_GameMessageEvent_BuffTimeDesc_Time0				,	//此法術暫時再目標上產生免疫效果
	EM_GameMessageEvent_ExchangeItem_DataErr			,	//兌換物品設定的資料有問題，請通知官方
	EM_GameMessageEvent_House_TooManyUnCheckItem		,	//過多物品log 還沒查看
	EM_GameMessageEvent_ClientDataError					,	//客戶端資料異常,回報服務器
	EM_GameMessageEvent_ChanageZoneError_InstanceKeyErr	,	//你和隊伍的副本進度不符合,無法進入副本
	EM_GameMessageEvent_ChanageZoneError_InstanceKey	,	//和隊友的副本進度不同無法進入
	EM_GameMessageEvent_ChanageZoneError_InstanceKeyDuplicate,//已有其他隊伍使用此進度進行遊戲

	EM_GameMessageEvent_SuitSkill_OpenYet				,	//套裝技能淬取介面開啟中


	EM_GameMessageEvent_HonorParty_NumLimit = 40		,	//榮譽組隊上限2人

	//戰鬥
	EM_GameMessageEvent_AttackError_TargetTooFar = 50	,	//攻擊目標過遠
	EM_GameMessageEvent_AttackError_Dir					,	//攻擊面向有問題
	EM_GameMessageEvent_AttackError_TargetDead			,	//目標死亡
	EM_GameMessageEvent_AttackError_Target				,	//目標不可攻擊

	EM_GameMessageEvent_AttackError_PhyDisable			,	//不可物理攻擊
	EM_GameMessageEvent_AttackError_MagicDisable		,	//不可法術攻擊



	//施法
	EM_GameMessageEvent_MagicError_OnSpell		 = 100	,	//已在施法中
	EM_GameMessageEvent_MagicError_TargetTooFar			,	//施法距離過遠
	EM_GameMessageEvent_MagicError_Request				,	//法術需求有問題
	EM_GameMessageEvent_MagicError_Target				,	//法術目標有問題
	EM_GameMessageEvent_MagicError_Back					,	//要在目標背後才可施展
	EM_GameMessageEvent_MagicError_Front				,	//要在目標前面才可施展
	EM_GameMessageEvent_MagicError_LookAt				,	//要看著目標才可施展
	EM_GameMessageEvent_MagicError_Coldown				,	//冷卻中

	EM_GameMessageEvent_MagicError_MagicIDError			,	//MagicID有問題
	EM_GameMessageEvent_MagicError_CreateObjectError	,	//件立物件失敗
	EM_GameMessageEvent_MagicError_HPNotEnough			,	//HP不夠
	EM_GameMessageEvent_MagicError_MPNotEnough			,	//MP不夠
	EM_GameMessageEvent_MagicError_WarriorSPNotEnough	,	//戰士SP不夠
	EM_GameMessageEvent_MagicError_RangerSPNotEnough	,	//遊俠SP不夠
	EM_GameMessageEvent_MagicError_ThiefSPNotEnough		,	//盜賊SP不夠
	EM_GameMessageEvent_MagicError_StomachFull			,	//吃不下
	EM_GameMessageEvent_MagicError_CostItemError		,	//消耗物品有問題
	EM_GameMessageEvent_MagicError_NoGun				,	//沒槍
	EM_GameMessageEvent_MagicError_NoBow				,	//沒弓
	EM_GameMessageEvent_MagicError_NoCossBow			,	//沒十字弓
	EM_GameMessageEvent_MagicError_NoGunAmmo			,	//沒子彈
	EM_GameMessageEvent_MagicError_NoBowAmmo			,	//沒箭
	EM_GameMessageEvent_MagicError_NoCossBowAmmo		,	//沒矢
	EM_GameMessageEvent_MagicError_NoThrowAmmo			,	//沒投擲物
	EM_GameMessageEvent_MagicError_NoAllLongWeapon		,	//沒遠程武器
	EM_GameMessageEvent_MagicError_NoAmmo				,	//沒彈藥
	EM_GameMessageEvent_MagicError_NeedWeaponError		,	//武器無法施展此招式
	EM_GameMessageEvent_MagicError_NeedBuffError		,	//缺少前置的輔助法術
	EM_GameMessageEvent_MagicError_NeedNoBuffError		,	//抗輔助還沒有消失
	EM_GameMessageEvent_MagicError_NeedTargetNoBuffError,	//目標抗輔助還沒有消失
	EM_GameMessageEvent_MagicError_NeedUnarmed			,	//需要空手才可施展
	EM_GameMessageEvent_MagicError_NeedBlade			,	//需要主手拿單手劍才可施展
	EM_GameMessageEvent_MagicError_NeedDagger			,	//需要主手拿匕首才可施展
	EM_GameMessageEvent_MagicError_NeedWand				,	//需要主手拿權杖才可施展
	EM_GameMessageEvent_MagicError_NeedAxe				,	//需要主手拿單手斧才可施展
	EM_GameMessageEvent_MagicError_NeedBludgeon			,	//需要拿棍棒才可施展
	EM_GameMessageEvent_MagicError_NeedClaymore			,	//需要拿雙手劍才可施展
	EM_GameMessageEvent_MagicError_NeedStaff			,	//需要拿雙手杖才可施展
	EM_GameMessageEvent_MagicError_Need2HAxe			,	//需要拿雙手斧才可施展
	EM_GameMessageEvent_MagicError_Need2HHammer			,	//需要拿雙手鎚才可施展
	EM_GameMessageEvent_MagicError_NeedPolearm			,	//需要拿長矛才可施展
	EM_GameMessageEvent_MagicError_NeedSwordType		,	//需要拿劍類才可施展
	EM_GameMessageEvent_MagicError_NeedAxeType			,	//需要拿斧才可施展
	EM_GameMessageEvent_MagicError_NeedShield			,	//需要拿盾才可施展
	EM_GameMessageEvent_MagicError_NeedDistance			,	//需要距離不夠
	EM_GameMessageEvent_MagicError_NeedNoAttack			,	//需要自己非戰鬥
	EM_GameMessageEvent_MagicError_NeedAttack			,	//需要戰鬥才可使用
	EM_GameMessageEvent_MagicError_NeedCritical			,	//爆擊後才可使用
	EM_GameMessageEvent_MagicError_NeedBeCritical		,	//被爆擊後才可使用
	EM_GameMessageEvent_MagicError_NeedDodge			,	//閃避後才可使用
	EM_GameMessageEvent_MagicError_NeedMiss				,	//Miss後才可使用
	EM_GameMessageEvent_MagicError_NeedParry			,	//格檔後才可使用
	EM_GameMessageEvent_MagicError_NeedBeParry			,	//被格檔後才可使用
	EM_GameMessageEvent_MagicError_NeedTargetNoAttack	,	//目標非戰鬥才可使用
	EM_GameMessageEvent_MagicError_NeedTargetAttack		,	//目標戰鬥才可使用
	EM_GameMessageEvent_MagicError_NeedBeDodge			,	//被閃避才可使用
	EM_GameMessageEvent_MagicError_NeedHPSmallerPercent	,	//HP過多無法使用
	EM_GameMessageEvent_MagicError_NeedHPGreaterPercent	,	//HP過少無法使用
	EM_GameMessageEvent_MagicError_NeedJob				,	//此職業無法施展
	EM_GameMessageEvent_MagicError_NeedLongDistWeapon	,	//需要拿長距離武器才可使用
	EM_GameMessageEvent_MagicError_NeedHammerType		,	//需要拿鎚類武器才可使用
	EM_GameMessageEvent_MagicError_Need2HWeapon			,	//需要拿雙手武器才可使用
	EM_GameMessageEvent_MagicError_PetNotFound			,	//找不到寵物

	EM_GameMessageEvent_MagicError_UseItemtoItem		,	//使用物品中
	EM_GameMessageEvent_MagicError_CanNotMove			,	//不可移動施法
	EM_GameMessageEvent_MagicError_IsSit				,	//坐下不可施法

	EM_GameMessageEvent_MagicError_TargetLineNotClear	,	//無法看到目標
	EM_GameMessageEvent_MagicError_Ride					,	//騎乘不能使用
	EM_GameMessageEvent_MagicError_Need1HWeapon			,	//需要拿單手武器才可使用

	EM_GameMessageEvent_MagicError_NeedMagicCritical	,	//法術爆擊後才可使用
	EM_GameMessageEvent_MagicError_NeedBeMagicCritical	,	//被法術爆擊後才可使用
	EM_GameMessageEvent_MagicError_Normal				,	//施法失敗
	EM_GameMessageEvent_MagicError_InWater				,	//水中不可使用
	EM_GameMessageEvent_MagicError_NotInWater			,	//水中才可以使用
	EM_GameMessageEvent_MagicError_SoulPointNotEnough	,	//SoulPoint不夠

	//商店
	EM_GameMessageEvent_Shop_NotCloseYet		= 200	,	//交易狀態沒解除
	EM_GameMessageEvent_Shop_ACOpenYet					,	//交易所正在開啟中
	EM_GameMessageEvent_Shop_MailOpenYet				,	//郵件正在開啟中
	EM_GameMessageEvent_Shop_ShopOpenYet				,	//商店正在開啟中
	EM_GameMessageEvent_Shop_BankOpenYet				,	//銀行正在開啟中
	EM_GameMessageEvent_Shop_ChangeJobOpenYet			,	//換角介面正在開啟中
	EM_GameMessageEvent_Shop_BillBoardOpenYet			,	//排行榜介面正在開啟中

	EM_GameMessageEvent_Shop_ACNoOpen					,	//交易所還沒開啟
	EM_GameMessageEvent_Shop_MailNoOpen					,	//郵件還沒開啟
	EM_GameMessageEvent_Shop_ShopNoOpen					,	//商店還沒開啟
	EM_GameMessageEvent_Shop_BankNoOpen					,	//銀行還沒開啟
	EM_GameMessageEvent_Shop_ChangeJobNoOpen			,	//換角還沒開啟
	EM_GameMessageEvent_Shop_BillBoardNoOpen			,	//排行榜還沒開啟

	EM_GameMessageEvent_Shop_ItemNotSell				,	//沒賣此物品
	EM_GameMessageEvent_Shop_CountTooMany				,	//購買過多	
	EM_GameMessageEvent_Shop_ItemNotExist				,	//此物品不存在
	EM_GameMessageEvent_Shop_CountError					,	//購買數量有問題
	EM_GameMessageEvent_Shop_NoSellAccountItem			,	//不可購買點數商品
	EM_GameMessageEvent_Shop_MomeyNotEnought			,	//金額不足
	EM_GameMessageEvent_Shop_BagFull					,	//包裹滿了
	EM_GameMessageEvent_Shop_SellDataError				,	//物品資料不符
	EM_GameMessageEvent_Shop_SellItemOnUse				,	//物品還在使用中
	EM_GameMessageEvent_Shop_CanNotSell					,	//此物品不可賣
	EM_GameMessageEvent_Shop_PepairDataError			,	//物品資料不符

	EM_GameMessageEvent_Shop_CreateNewGuildOpenYet		,	//建立連署公會開啟中
	EM_GameMessageEvent_Shop_GuildContributionOpenYet	,	//公會貢獻開啟中
	EM_GameMessageEvent_Shop_GuildShopOpenYet			,	//公會商店開啟中

	EM_GameMessageEvent_Shop_LotteryBuyShopOpenYet		,	//彩卷商店開啟中
	EM_GameMessageEvent_Shop_LotteryExchangeShopOpenYet	,	//彩卷兌換開啟中

	EM_GameMessageEvent_Shop_VisitHousesOpenYet			,	//房屋參觀介面開啟中	


	//裝備
	EM_GameMessageEvent_EQError_WearPos_Body	=250	,	//裝備位置有問題
	EM_GameMessageEvent_EQError_DataInfo_Body			,	//裝備資料有問題
	EM_GameMessageEvent_EQError_OrgObjID_Body			,	//裝備物件有問題

	EM_GameMessageEvent_EQError_WearPos_Bank			,	//裝備位置有問題
	EM_GameMessageEvent_EQError_DataInfo_Bank			,	//裝備資料有問題
	EM_GameMessageEvent_EQError_OrgObjID_Bank			,	//裝備物件有問題

	EM_GameMessageEvent_EQError_WearPos_EQ				,	//裝備位置有問題
	EM_GameMessageEvent_EQError_DataInfo_EQ				,	//裝備資料有問題
	EM_GameMessageEvent_EQError_OrgObjID_EQ				,	//裝備物件有問題

	EM_GameMessageEvent_EQError_PKProtectCountError		,	//裝備保護不能穿超過8件
	EM_GameMessageEvent_EQError_WearPos_ItemUnique		,	//同一類型的法寶不可以裝備兩個以上

	//好有名單
	EM_GameMessageEvent_FriendList_DelError		=300	,	//刪除好友有問題

	//公會
	EM_GameMessageEvent_Guild_GuildNoFound		=350	,	//自己沒有公會
	EM_GameMessageEvent_Guild_NoGuild					,	//沒有公會
	EM_GameMessageEvent_Guild_GuildIsReady				,	//已經是正式公會
	EM_GameMessageEvent_Guild_NotLeader					,	//非公會會長
	EM_GameMessageEvent_Guild_TargetNotOnline			,	//此人不在線上
	EM_GameMessageEvent_Guild_LeaderNotOnline			,	//公會會長不在線上
	EM_GameMessageEvent_Guild_GuildIsNotReady			,	//還在連署中
	EM_GameMessageEvent_Guild_NoInviteRight				,	//沒有邀請加入的權限
	EM_GameMessageEvent_Guild_InviterNotOnline			,	//邀請者不在線上
	EM_GameMessageEvent_Guild_MaxMember					,	//公會已到人數上限
	EM_GameMessageEvent_Guild_HasGuild					,	//已擁有公會
	EM_GameMessageEvent_GuildWar_PlayerCountFull		,	//戰場人數已滿
	EM_GameMessageEvent_GuildWar_CantInvite				,	//現在正在進行公會城戰，不能新增成員！

	//物品
	EM_GameMessageEvent_Item_OrgObjIDError		=400	,	//物件資料有問題
	EM_GameMessageEvent_Item_NotItem					,	//非物品
	EM_GameMessageEvent_Item_PosError					,	//要求放的位置有問題
	EM_GameMessageEvent_Item_Queue_PosError				,	//要求放的位置有問題
	EM_GameMessageEvent_Item_Queue_BufferEmpty			,	//物品序列內是空的
	EM_GameMessageEvent_Item_Queue_DataError			,	//物品資料錯誤
	EM_GameMessageEvent_Item_Queue_CountError			,	//物品數量錯誤
	EM_GameMessageEvent_Item_DelError					,	//資料刪除錯誤
	EM_GameMessageEvent_Item_ExchangeError				,	//物品交換有問題
	EM_GameMessageEvent_Item_BankOpenError				,	//銀行開啟狀況有問題
	EM_GameMessageEvent_Item_BankTooFar					,	//銀行距離過遠
	EM_GameMessageEvent_Item_ExchangeMoneyError			,	//金錢交換有問題
	EM_GameMessageEvent_Item_CountError					,	//數量有問題
	EM_GameMessageEvent_Item_DisableTrade				,	//交易功能被禁止
	EM_GameMessageEvent_Item_ColoringFailed				,	//染色失敗
	EM_GameMessageEvent_Item_ResetAbilityFailed			,	//角色能力配點已重設
	EM_GameMessageEvent_Item_ResetSkillPointFailed		,	//角色技能配點已重設
	EM_GameMessageEvent_Item_EmptyPacketErr				,	//包裹空位不夠
	EM_GameMessageEvent_Item_MagicDisableUseItem		,	//物品使用禁制中
	EM_GameMessageEvent_Item_TargetDisableTrade			,	//目標交易功能被禁止
	EM_GameMessageEvent_Item_ItemUniqueErr				,	//刪除重複取得的唯一物品
	EM_GameMessageEvent_Item_ItemLock					,	//物品密碼鎖保護中
	EM_GameMessageEvent_Item_LimitErr					,	//使用條件不符合

	//PK
	EM_GameMessageEvent_PK_PKError				=450	,	//PK處理有問題
	EM_GameMessageEvent_PK_InviteError					,	//已要請其他目標
	EM_GameMessageEvent_PK_Prepar						,	//已在PK準備中
	EM_GameMessageEvent_PK_Begin						,	//已在PK中
	EM_GameMessageEvent_PK_TargetNotExist				,	//目標不存在
	EM_GameMessageEvent_PK_TargetTooFar					,	//目標過遠
	EM_GameMessageEvent_PK_TargetInviteOther			,	//目標要請其他人
	EM_GameMessageEvent_PK_TargetPK						,	//目標PK中
	EM_GameMessageEvent_PK_PKInviteResultError			,	//PK回應資料有問題

	//Trade
	EM_GameMessageEvent_Trade_ItemError			=500	,	//交易物品有問題
	EM_GameMessageEvent_Trade_CanNotTrade				,	//物品不可交易
	EM_GameMessageEvent_Trade_CanNotModify				,	//交易確定後不可修改
	EM_GameMessageEvent_Trade_PosError					,	//放置位置有問題
	EM_GameMessageEvent_Trade_PosOnLock					,	//物品鎖定中
	EM_GameMessageEvent_Trade_MoneyError				,	//金錢為負的
	EM_GameMessageEvent_Trade_AccountError				,	//符文幣為負的
	EM_GameMessageEvent_Trade_MoneyNotEnough			,	//金錢不足
	EM_GameMessageEvent_Trade_AccountNotEnough			,	//點數不足
	EM_GameMessageEvent_Trade_Error						,	//交易失敗
	EM_GameMessageEvent_Trade_RelationItemError			,	//關係物品只能單獨交易
	EM_GameMessageEvent_Trade_RelationErr				,	//關係建立失敗
	EM_GameMessageEvent_Trade_RelationOK				,	//成立新關係


	//兌換訊息
	EM_GameMessageEvent_ItemExchange_IsUse		=550	,	//兌換物品已被使用
	EM_GameMessageEvent_ItemExchange_NotFound			,	//找不到此物品


	//社群
	EM_GameMessageEvent_Socal_AddFriendNoPeople		= 600,	// 新增好友未成功，對方已離線
	EM_GameMessageEvent_Socal_AddFriendNoOwner		,		// 新增好友未成功，邀請人已離線
	EM_GameMessageEvent_Socal_AddFriendRefuse		,		// 對方拒絕你的好友邀請

	//裝備合成
	EM_GameMessageEvent_EQCombin_OpenYet			= 650,	//裝備合成介面開啟中
	EM_GameMessageEvent_AccountBag_OpenYet			,		//帳號背包介面開啟中

	//設定角色權限訊息
	EM_GameMessageEvent_Role_Right_NoSpeak			= 700,	//GM對你 永久禁言
	EM_GameMessageEvent_Role_Right_Speak			,		//GM對你 解除禁言
	EM_GameMessageEvent_Role_Right_NoTrade			,		//GM對你 永久禁止交易
	EM_GameMessageEvent_Role_Right_Trade			,		//GM對你 解除禁止交易
	EM_GameMessageEvent_Role_Untrust				,		//你的帳號目前無法使用此功能

	//Chat訊息		
	EM_GameMessageEvent_Mail_BagFull				= 750,	//背包已滿,無法收取信件

	//公會屋資訊
	EM_GameMessageEvent_GuildHouse_GuildInfoError	= 800 ,	//非自己所屬公會
	EM_GameMessageEvent_GuildHouse_RightError			,	//沒有存取的權限
	EM_GameMessageEvent_GuildHouse_ItemNoTrade			,	//此物品不能放入公會倉庫
	EM_GameMessageEvent_GuildHouse_ItemCountError		,	//存取公會倉庫物品過量
	EM_GameMessageEvent_GuildHouse_FurnitureFull		,	//家俱已滿
	EM_GameMessageEvent_GuildHouse_FurnitureError		,	//此物品不能當公會屋擺設品
	EM_GameMessageEvent_GuildHouse_FurnitureNotYours	,	//此物品不是屬於你的
	EM_GameMessageEvent_GuildHouse_TooNearBuilding		,	//建築時太靠近建物，傳到公會入口處

	//戰場
	EM_GameMessageEvent_BattleGround_RoomAndDataExist		= 850,	//上一場戰場仍未結束, 你必需等待戰場結束方可進入


	EM_GameMessageEvent_Pet_Hunger_Full				= 900	,	//寵物已吃飽
	EM_GameMessageEvent_Pet_Loyal_Full						,	//寵物忠誠度已滿
	EM_GameMessageEvent_Pet_BagFull							,	//背包已滿,無法收成
};

enum	GameMessageEventDataENUM
{	
	//商店
	EM_GameMessageEventData_None						,
	EM_GameMessageEventData_ShopBuy						,	//商店買 [購買 %sx%d 共%d元]
	EM_GameMessageEventData_ShopSell					,	//商店賣 [販賣 %sx%d 獲得%d元]
	EM_GameMessageEventData_ZoneChannelLevelErr			,	//至少要有一個職業等級超過 %d 級，才可使用區域頻道！
	EM_GameMessageEventData_Guild_TargetCanNotInvite	,	//欲邀請的玩家退出前公會時間 %d:%d 。1小時內不得加入公會！

};
//-------------------------------------------------------------------------------------
//定義角色用MP 還是 SP
enum	GameRoleMPSPUseTypeENUM
{
	EM_GameRoleMPSPUseType_None		,	//都沒有
	EM_GameRoleMPSPUseType_MP		,	//有mp
	EM_GameRoleMPSPUseType_SP		,	//有sp

};
//-------------------------------------------------------------------------------------
//玩家行為資料記錄
struct PlayerActionMode
{
	union
	{
		int	_Mode;
		struct  
		{
			bool	Fight		:1;
			bool	Trade		:1;
			bool	Mail		:1;
			bool	AC			:1;
			bool	Shop		:1;
			bool	ChangeJob	:1;
			bool	DailyQuest	:1;
			bool	DailyFlag	:1;
		};
	};
};

struct PlayerActionLogStruct
{
	PlayerActionMode ActionMode;

	int	DeadCount;			//死亡次數
	int	KillCount;			//殺死隻數
	int	Exp;				//這斷時間的經驗值
	int	Exp_TP;
	int	LastMoney;			//最後儲存的金錢
	int	SavePlayTime;		//最後儲存的時間
	int	LastMoney_Account;	//最後儲存的帳號幣r
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};
//--------------------------------------------------------------------------------------------
//排行榜
//--------------------------------------------------------------------------------------------
//單筆排行資料
struct DB_BillBoardRoleInfoStruct
{
	int					Rank_Money;
	int					Rank_Title;				
	int					Rank_PKScore;				

	union
	{
		int				Rank_Job[8];
		struct  
		{
			int					Rank_Job_Warrior;		
			int					Rank_Job_Ranger;			
			int					Rank_Job_Rogue;			
			int					Rank_Job_Wizard;			
			int					Rank_Job_Priest;			
			int					Rank_Job_Knight;			
			int					Rank_Job_RuneDancer;		
			int					Rank_Job_Druid;			
		};
	};

	union
	{
		int				JobLv[8];
		struct  
		{
			int					JobLv_Warrior;		
			int					JobLv_Ranger;			
			int					JobLv_Rogue;			
			int					JobLv_Wizard;			
			int					JobLv_Priest;			
			int					JobLv_Knight;			
			int					JobLv_RuneDancer;		
			int					JobLv_Druid;			
		};
	};

	bool				IsAnonymous;	//匿名

	StaticString< _MAX_NAMERECORD_SIZE_ > RoleName;
	int					DBID;			//資料庫ID

	Voc_ENUM		    Voc;			//職業
	Voc_ENUM		    Voc_Sub;		//副職業
//	int					Lv;				//職業等級
//	int					Lv_Sub;			//副職業等級

	int 				Money;
	int					TitleCount;		//頭銜數量
	int					PKScore;		

	int					GetJobLv( int JobID )
	{
		if( JobID <= 0 || JobID >= 8 )
			return 0;
		return JobLv[ JobID ];
	}
};
//--------------------------------------------------------------------------------------------------------------------
//  AC交易類型
//--------------------------------------------------------------------------------------------------------------------
enum AcActionTypeENUM
{
	EM_AcActionType_Unknow = -1 		,	
	EM_AcActionType_Sell				,	//放入
	EM_AcActionType_Cancel				,	//取消
	EM_AcActionType_Bid					,	//下標
	EM_AcActionType_BuyOut				,	//直購
	EM_AcActionType_DrawBack			,	//(被人競標 or 賣方放棄)
	EM_AcActionType_Deal				,	//成交
	EM_AcActionType_NoDeal				,	//沒成交
	EM_AcActionType_SendMoneytoSeller	,	//成交金錢寄送
};

//--------------------------------------------------------------------------------------------------------------------
//  物品交易類型
//--------------------------------------------------------------------------------------------------------------------
enum ActionTypeENUM
{
	EM_ActionType_Unknow				,
	EM_ActionType_LevelUp				,//升級
	EM_ActionType_EnterWorld			,//入遊戲
	EM_ActionType_LeaveWorld			,//離開遊戲
	EM_ActionType_Buy					,//買
	EM_ActionType_Buy_Record			,//買 過去賣掉的
	EM_ActionType_Sell					,//賣
	EM_ActionType_Tran					,//玩家交易
	EM_ActionType_Get					,//撿取地上
	EM_ActionType_Drop					,//放到地上
	EM_ActionType_GMGive				,//GM給予
	EM_ActionType_PlotGive				,//劇情給予
	EM_ActionType_PlotDestory			,//劇情刪除
	EM_ActionType_KillMonster			,//打怪物
	EM_ActionType_DestroyItem			,//物品消除
	EM_ActionType_ErrorDestory			,//錯誤清除
	EM_ActionType_MagicSummonItem		,//魔法召喚物品
	EM_ActionType_MagicDestory			,//魔法需求藥引	
	EM_ActionType_UseItemGive			,//物品使用給予
	EM_ActionType_UseItemDestroy		,//物品使用消失
	EM_ActionType_OffLienDestory		,//離線消失
	EM_ActionType_ChangeZoneDestory		,//換區消失
	EM_ActionType_GiveSystem			,//用贈與系統給物品
	EM_ActionType_CombineGet			,//煉製得到
	EM_ActionType_CombineDestory		,//煉製消去
	EM_ActionType_Steal					,//偷竊
	EM_ActionType_ToAC					,//放到拍賣所
	EM_ActionType_ToACError				,//放到拍賣所退回(有錯誤)
	EM_ActionType_ToMail				,//放到拍賣所
	EM_ActionType_ToMailError			,//放到拍賣所退回(有錯誤)
	EM_ActionType_FromMail				,//由Mail取得
	EM_ActionType_FromParty				,//由Party分享
	EM_ActionType_Dissolution			,//分解
	EM_ActionType_ACTex					,//使用拍賣所所需
	EM_ActionType_ACBuy					,//拍賣所買東西
	EM_ActionType_Money					,//銀票
	EM_ActionType_Card					,//卡片
	EM_ActionType_Gamble				,//賭博
	EM_ActionType_ItemExchange			,//兌換物品
	EM_ActionType_Buy_Account			,//點數商品購買
	EM_ActionType_Buy_Lottery			,//買彩卷
	EM_ActionType_Gather				,//採集
	EM_ActionType_EqBroken				,//裝備損壞
	EM_ActionType_SysChannel			,//系統頻道消耗物品
	EM_ActionType_ColoringShop_Player	,//染色商店(更換照型)
	EM_ActionType_Lottery_Prize			,//彩金
	EM_ActionType_CreateGuild			,//建立公會
	EM_ActionType_FixEQ					,//修裝備
	EM_ActionType_BuyHouseEnergy		,//買房屋能量
	EM_ActionType_ImportAccountMoney	,//匯入帳號幣		
	EM_ActionType_QuestComplete			,//完成任務
	EM_ActionType_Exp					,//經驗值改變
	EM_ActionType_PlayerDead			,//玩家死亡
	EM_ActionType_MonsterDead			,//怪物死亡
	EM_ActionType_RefineFailedDestroy	,//精鍊升等失敗消失 
	EM_ActionType_EQCombineDestroy		,//裝備合成消失 	
	EM_ActionType_GuildWarDeclare		,//公會宣戰金錢
	EM_ActionType_RefineLvUp			,//精鍊升等
	EM_ActionType_RefineLvDn			,//精鍊降等
	EM_ActionType_RefineNone			,//精鍊沒改變
	EM_ActionType_RefineProtect			,//精鍊保護
	EM_ActionType_Reserve				,//(保留)
	EM_ActionType_PKItemProtect			,//PK物品懲治保護
	EM_ActionType_PKDropItem			,//PK掉落
	EM_ActionType_Loot					,//檢屍
	EM_ActionType_MagicBox				,//寶箱融合
	EM_ActionType_GuildContribution		,//公會貢獻
	EM_ActionType_SellMailGroup			,//群發信件
	EM_ActionType_TimeUp				,//時間到刪除
	EM_ActionType_GuildStoreHouse_Put	,//公會倉庫(放入)
	EM_ActionType_GuildHouse_Funiture_Put,//公會擺設(放入)
	EM_ActionType_OpenPacket			,//打開商城打包
	EM_ActionType_ColoringShop_Horse	,//染色商店(坐騎染色)
	EM_ActionType_Rent_BackPacket		,//租用背包欄位
	EM_ActionType_Rent_BankPacket		,//租用銀行欄位
	EM_ActionType_Rent_Bank				,//租用隨身銀行
	EM_ActionType_Rent_Mail				,//租用隨身信箱
	EM_ActionType_Rent_AC				,//租用隨身交易所
	EM_ActionType_Buy_Account_Gift		,//購買商城禮物
	EM_ActionType_Buy_Account_Bonus		,//商城紅利幣購買
	EM_ActionType_Buy_Account_Free		,//商城必爾丁	購買
	EM_ActionType_Plant_Product			,//種植(產物)
	EM_ActionType_Plant_Destroy			,//種植(刪除)
	EM_ActionType_GuildStoreHouse_Get	,//公會倉庫(拿出)
	EM_ActionType_GuildHouse_Funiture_Get,//公會擺設(拿出)
	EM_ActionType_Card_Destroy			,//卡片放入
	EM_ActionType_MagicBox_Destroy		,//魔幻寶盒刪除
	EM_ActionType_PetRetrain_Destroy	,//寵物重修鍊刪除
	EM_ActionType_Attribute_Gamble		,//物品屬性賭博
	EM_ActionType_GMDestroy				,//GM刪除
	EM_ActionType_BodyShop				,//修改身材
	EM_ActionType_QuestDelete			,//刪除任務
	EM_ActionType_EQCombineResult		,//物品合成結果
	EM_ActionType_MagicBoxResult		,//魔幻寶盒合成結果
	EM_ActionType_ItemtoItemResult		,//物品對物品使用結果
	EM_ActionType_MagicStoneShop		,//魔石兌換商店
	EM_ActionType_ServantHire			,//雇用女僕
	EM_ActionType_SuitSkillCost			,//套裝技能消費金錢
	EM_ActionType_DestroyItem_Buy		,//購買消失
	EM_ActionType_DestroyItem_PetTriMerge		,//寵物融合消耗
	EM_ActionType_DestroyItem_DrawOutRune		,//取出符文
	EM_ActionType_DestroyItem_CoolSuit			,//套裝衣櫃
	EM_ActionType_DestroyItem_CloneItem			,//疑是複製物品刪除
	EM_ActionType_DestroyItem_ErrItem			,//問題物品刪除
	EM_ActionType_Rare3EqExchangeItem			,//稀有度三的物品兌換刪除
	EM_ActionType_DestroyItem_CloneItem_House	,//疑是複製物品刪除(房屋)
	EM_ActionType_PetBag_In						,//放入寵物包
	EM_ActionType_PetBag_Out					,//取出寵物包
	EM_ActionType_HorseBag_In					,//放入坐騎包
	EM_ActionType_HorseBag_Out					,//取出坐騎包
	EM_ActionType_ClsItemAttribute				,//
	EM_ActionType_PutItemToWarDrobe				,//把東西放入衣櫥需求物
	EM_ActionType_BG_IndependenceGame			,//戰場獨立遊戲
	EM_ActionType_SlotMachine					,//角子老虎機

	EM_ActionType_BUY_COOLSUITPAGE				,//買魔法衣櫥
	EM_ActionType_BUY_COOLSUITSET				,//買酷裝設定

	EM_ActionType_Item_ClsAttribute				,//使用屬性清潔石
	EM_ActionType_Item_DrawAttribute			,//使用屬性抽取石
	EM_ActionType_WeekInstReset					,//重置每日副本次數
	EM_ActionType_LuaSetItemInfo				,//Lua修改物品資訊
	EM_ActionType_LoginBonus					,//每日登入禮
};
//-------------------------------------------------------------------------------------
//公會log類型
enum GuildActionTypeENUM
{
	EM_GuildActionType_CreateNewGuild	,//建立新公會
	EM_GuildActionType_JoinNewGuild		,//加入聯屬公會
	EM_GuildActionType_LeaveNewGuild	,//離開聯屬公會
	EM_GuildActionType_DestroyNewGuild	,//刪除聯屬公會
	EM_GuildActionType_RegularGuild		,//成為正式公會
	EM_GuildActionType_Destroy			,//刪除公會
	EM_GuildActionType_Join				,//加入公會
	EM_GuildActionType_Leave			,//離開公會
	EM_GuildActionType_AddScore			,//增加公會積分
	EM_GuildActionType_BuyFuntion		,//買公會功能
	EM_GuildActionType_ChangeLeader		,//更換會長
};
//-------------------------------------------------------------------------------------
//角色特效類型
enum SpecialEfficacyTypeENUM
{
	EM_SpecialEfficacyType_ChangeJob	,	//換職業
	EM_SpecialEfficacyType_Unknow		,
};
//-------------------------------------------------------------------------------------
enum	PKStateENUM
{
	EM_PKState_None				,		//一般狀態
	EM_PKState_Invite			,		//要請
	EM_PKState_Prepare			,		//準備PK
	EM_PKState_Begin			,		//開始PK
	EM_PKState_Begin_OutRange	,		//開始PK 超過範圍
	EM_PKState_End				,		
};
//pk資料
struct PKInfoStruct
{
	int				TargetID;
	int				TargetDBID;
	PKStateENUM		State;
	int				Clock;			//時間
	float			X ,Y, Z;		//要請位置

	void Init()
	{
		memset( this , 0 , sizeof( *this ) );
	}
};
//-------------------------------------------------------------------------------------
struct AttachObjInfoStruct
{
	int		ItemID;		//連結的物件
	int		Type;		//連結類型
	string	ItemPos;	//連結位置
	string	WagonPos;

	void Init()
	{
		ItemID = -1;
		Type = 0;
		ItemPos.clear();
		WagonPos.clear();
	}
	bool IsEmpty()
	{
		return ItemID == -1;
	}
};
//-------------------------------------------------------------------------------------
//換區資訊
struct ChangeZoneInfoStruct
{
	int		CopyRoomID;		//要考貝的房間
};
//-------------------------------------------------------------------------------------
//換區資訊
struct BattleGroundInfoStruct
{
	//int		CopyRoomID;		//要考貝的房間
	int			iKillVal;		// 擊殺敵人次數
	int			iDeadVal;		// 死亡次數
	int			iDamageVal;		// 成功造成傷害的數量
	int			iHealVal;		// 成功治療量	
	
	int			iForceFlagID;	// 強制背負旗子代號
	int			iCampID;		// 設定陣營的代號
	int			iDefVal;		// 防禦量
	//int			iTemp_3_Val;	// 暫時先保留
};
//-------------------------------------------------------------------------------------
//符文檢查結果
enum CheckAddRuneResultENUM
{
	EM_CheckAddRuneResult_OK				,	//OK
	EM_CheckAddRuneResult_TargetItemErr		,	//目標物品有問題
	EM_CheckAddRuneResult_NotRune			,	//不是符文
	EM_CheckAddRuneResult_RuneVolumeErr		,	//符文容量不足
	EM_CheckAddRuneResult_WeaponErr			,	//鑲嵌武器類型有問題
	EM_CheckAddRuneResult_ArmorErr			,	//鑲嵌防具類型有問題
	EM_CheckAddRuneResult_Unknow			,	//未知錯誤
	EM_CheckAddRuneResult_RuneDuplicate		,	//符文重復
	EM_CheckAddRuneResult_RuneFull			,	//符文滿格
	EM_CheckAddRuneResult_LevelError		,	//使用的等級有問題
};
//-------------------------------------------------------------------------------------
//裝備衝等檢查結果
enum CheckEqRefineResultENUM
{
	EM_CheckEqRefineResult_OK					,	//OK
	EM_CheckEqRefineResult_DataErr				,	//資料有問題
	EM_CheckEqRefineResult_MaxLevel				,	//已到等級上限
	EM_CheckEqRefineResult_NotWeapon			,	//只能精鍊武器類型
	EM_CheckEqRefineResult_NotArmor				,	//只能精鍊防具類型
	EM_CheckEqRefineResult_NotJewels			,	//只能精鍊首飾類型
	EM_CheckEqRefineResult_ItemLimitMinLevel	,	//可精鍊武器等級太低問題
	EM_CheckEqRefineResult_ItemLimitMaxLevel	,	//可精鍊武器等級已達上限
	EM_CheckEqRefineResult_NotOrnament			,	//只能裝飾品類型
	EM_CheckEqRefineResult_CantRefine			,	//不能衝等
};
//-------------------------------------------------------------------------------------
//修裝檢查結果
enum ChecFixEqResultENUM
{
	EM_CheckFixEqResult_OK				,	//OK
	EM_CheckFixEqResult_DataErr			,	//資料有問題
	EM_CheckFixEqResult_NotFix			,	//物品不能修理
	EM_CheckFixEqResult_NotEQ			,	//非裝備
	EM_CheckFixEqResult_NewOne			,	//物品沒損壞
	EM_CheckFixEqResult_NotEnoughMoney	,	//金錢不足
};
//-------------------------------------------------------------------------------------
//拆解物品檢查結果
enum CheckDissolutionResultENUM
{
	EM_CheckDissolutionResult_OK		,	//OK
	EM_CheckDissolutionResult_Err		,	//此物品不可拆解
};
//-------------------------------------------------------------------------------------
//物品染色檢查結果
enum CheckColoringResultENUM
{
	EM_CheckColoringResult_OK		,	//OK
	EM_CheckColoringResult_Err		,	//此物品不可染色
};
//-------------------------------------------------------------------------------------
//物品是否可以清除Soulbond
enum CheckClsSoulBoundResultENUM
{
	EM_CheckClsSoulBoundResult_OK					,	//OK
	EM_CheckClsSoulBoundResult_Err					,	//此物品不可清除Soulbond
	EM_CheckClsSoulBoundResult_Err_NoSoulBound		,	//此物品目前沒Soulbond
	EM_CheckClsSoulBoundResult_Err_NoEqSoulBound	,	//非裝備綁定不能解除
};
//-------------------------------------------------------------------------------------
//是否可以挖洞
enum CheckDigHoleResultENUM
{
	EM_CheckDigHoleResult_OK				,	//OK
	EM_CheckDigHoleResult_TargetErr			,	//不可對此物品挖洞
	EM_CheckDigHoleResult_SrcErr			,	//使用物品有問題
	EM_CheckDigHoleResult_WeaponOnly		,	//只能對武器使用
	EM_CheckDigHoleResult_ArmorOnly			,	//只能對防具使用
	EM_CheckDigHoleResult_OrnamentOnly		,	//只能對飾品使用
	EM_CheckDigHoleResult_HoleErr			,	//洞數過多
	EM_CheckDigHoleResult_NotJewels		,	//只能對飾品使用
};
//-------------------------------------------------------------------------------------
//是否可以清除符文
enum CheckClsRuneResultENUM
{
	EM_CheckClsRuneResult_OK				,	//OK
	EM_CheckClsRuneResult_TargetErr			,	//不可對此物品挖洞
	EM_CheckClsRuneResult_SrcErr			,	//使用物品有問題
};
//-------------------------------------------------------------------------------------
//是否可以物品上鎖
enum CheckItemLockResultENUM
{
	EM_CheckItemLockResult_OK				,	//OK
	EM_CheckItemLockResult_TargetErr		,	//不可對此物品挖洞
	EM_CheckItemLockResult_SrcErr			,	//使用物品有問題
};
//-------------------------------------------------------------------------------------
//是否可以物品解鎖
enum CheckItemUnLockResultENUM
{
	EM_CheckItemUnLockResult_OK				,	//OK
	EM_CheckItemUnLockResult_TargetErr		,	//
	EM_CheckItemUnLockResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//裝備綁定結果
enum CheckEQProtectResultENUM
{
	EM_CheckEQProtectResult_OK				,	//OK
	EM_CheckEQProtectResult_TargetErr		,	//
	EM_CheckEQProtectResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckEQLimitMaxResultENUM
{
	EM_CheckEQLimitMaxResult_OK				,	//OK
	EM_CheckEQLimitMaxResult_TargetErr		,	//
	EM_CheckEQLimitMaxResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckIgnoreLimitLvMaxResultENUM
{
	EM_CheckIgnoreLimitLvMaxResult_OK		,	//OK
	EM_CheckIgnoreLimitLvMaxResult_TargetErr,	//
	EM_CheckIgnoreLimitLvMaxResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckPkEqProtectResultENUM
{
	EM_CheckPkEqProtectResult_OK		,	//OK
	EM_CheckPkEqProtectResult_TargetErr,	//
	EM_CheckPkEqProtectResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckPkEqProtectcClearResultENUM
{
	EM_CheckPkEqProtectClearResult_OK		,	//OK
	EM_CheckPkEqProtectClearResult_TargetErr,	//
	EM_CheckPkEqProtectClearResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckClsEqAbilityResultENUM
{
	EM_CheckClsEqAbilityResult_OK		,	//OK
	EM_CheckClsEqAbilityResult_TargetErr,	//
	EM_CheckClsEqAbilityResult_SrcErr	,	//
};
//-------------------------------------------------------------------------
//物品擺設資料
struct House3DLayoutStruct
{
	union
	{
		int	Mode;
		struct
		{
			bool	IsShow : 1;
			bool	IsFriend_Put  : 1;	//好友可存
			bool	IsFriend_Get  : 1;	//好友可取
			bool	IsFriend_Show : 1;	//好友可看
 			bool	IsSound : 1;	//留聲機
		};
	};

	float X, Y, Z;       //位置
	float UpX, UpY, UpZ; //上方向量
	float Angle;         //選轉角度

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//房屋系統
//////////////////////////////////////////////////////////////////////////
#define MAX_HOUSE_CLIENT_DATA_SIZE_	2048
#define MAX_HOUSE_STRING_SIZE	256

#define MAX_HOUSE_ITEM_LOG_COUNT 100
struct HouseFriendItemLogStruct
{
	int		Time;
	int		FriendDBID;
	int		ItemID;
	int		Count;
};

#define MAX_SERVANT_COUNT	6
#define MAX_SERVANT_FLAG	256

enum HouseServantValueTypeENUM
{
	EM_HouseServantValueType_NPCObjID	,
	EM_HouseServantValueType_Character	,
	EM_HouseServantValueType_Sex		,
	EM_HouseServantValueType_Tired		,	//疲憊度
	EM_HouseServantValueType_Value0		,	// 0-7 基本數值
	EM_HouseServantValueType_Value1		,
	EM_HouseServantValueType_Value2		,
	EM_HouseServantValueType_Value3		,
	EM_HouseServantValueType_Value4		,
	EM_HouseServantValueType_Value5		,
	EM_HouseServantValueType_Value6		,
	EM_HouseServantValueType_Value7		,
	EM_HouseServantValueType_MaxValue0	,	// 0-7 最大基本數值
	EM_HouseServantValueType_MaxValue1	,
	EM_HouseServantValueType_MaxValue2	,
	EM_HouseServantValueType_MaxValue3	,
	EM_HouseServantValueType_MaxValue4	,
	EM_HouseServantValueType_MaxValue5	,
	EM_HouseServantValueType_MaxValue6	,
	EM_HouseServantValueType_MaxValue7	,
	EM_HouseServantValueType_ClothColor0,	// 0-1 衣服顏色
	EM_HouseServantValueType_ClothColor1,
	EM_HouseServantValueType_Flag		= 1000,	// 0-255 女僕專屬旗標	
};

struct HouseServantStruct
{	
//	bool		IsSave;										//資料是否已存在
	union
	{
		int		Mode;
		struct
		{
			bool IsSave : 1;		//是否儲存
			bool IsHire : 1;		//是否被雇用
		};
	};

	StaticString< _MAX_NAMERECORD_SIZE_ >	Name;			//名稱
	int CreateTime;
	int NPCObjID;
	int	MaxValue[8];
	int	Value[8];
	int	ClothColor[2];
	int	Character;											//角色個性
	int	Sex;												//0 男 1 女 2 怪物
	int	Cost;
	int	Tired;												//疲憊度

	StaticFlag<MAX_SERVANT_FLAG>	Flag;		//
	LookStruct Look;
	House3DLayoutStruct	Layout;

	HouseServantStruct()
	{
		Init();
	};
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}

	int		ReadValue( HouseServantValueTypeENUM Type )
	{
		int ID = Type - EM_HouseServantValueType_Flag;

		if( (unsigned)ID < MAX_SERVANT_FLAG )
		{
			return (int)Flag.GetFlag( ID );
		}
		
		switch( Type )
		{
		case EM_HouseServantValueType_NPCObjID:
			return NPCObjID;
		case EM_HouseServantValueType_Character:
			return Character;
		case EM_HouseServantValueType_Sex:
			return Sex;
		case EM_HouseServantValueType_Tired:
			return Tired;
		case EM_HouseServantValueType_Value0:	// 0-7 基本數值
		case EM_HouseServantValueType_Value1:
		case EM_HouseServantValueType_Value2:
		case EM_HouseServantValueType_Value3:
		case EM_HouseServantValueType_Value4:
		case EM_HouseServantValueType_Value5:
		case EM_HouseServantValueType_Value6:
		case EM_HouseServantValueType_Value7:
			return Value[ Type - EM_HouseServantValueType_Value0 ];
		case EM_HouseServantValueType_MaxValue0:	// 0-7 最大基本數值
		case EM_HouseServantValueType_MaxValue1:
		case EM_HouseServantValueType_MaxValue2:
		case EM_HouseServantValueType_MaxValue3:
		case EM_HouseServantValueType_MaxValue4:
		case EM_HouseServantValueType_MaxValue5:
		case EM_HouseServantValueType_MaxValue6:
		case EM_HouseServantValueType_MaxValue7:
			return MaxValue[ Type - EM_HouseServantValueType_MaxValue0 ];
		case EM_HouseServantValueType_ClothColor0:	// 0-1 衣服顏色
			return ClothColor[0];
		case EM_HouseServantValueType_ClothColor1:
			return ClothColor[1];
		}
		return 0;
	}

	bool	WriteValue(	HouseServantValueTypeENUM Type , int V )
	{
		int ID = Type - EM_HouseServantValueType_Flag;

		if( (unsigned)ID < MAX_SERVANT_FLAG )
		{
			if( V == 0 )
				Flag.SetFlagOff( ID );
			else
				Flag.SetFlagOn( ID );
			return true;
		}

		switch( Type )
		{
		case EM_HouseServantValueType_NPCObjID:
//			NPCObjID = V;
			return false;
		case EM_HouseServantValueType_Character:
			Character = V;
			return true;
		case EM_HouseServantValueType_Sex:
			Sex = V;
			return true;
		case EM_HouseServantValueType_Tired:
			Tired = V;
			return true;
		case EM_HouseServantValueType_Value0:	// 0-7 基本數值
		case EM_HouseServantValueType_Value1:
		case EM_HouseServantValueType_Value2:
		case EM_HouseServantValueType_Value3:
		case EM_HouseServantValueType_Value4:
		case EM_HouseServantValueType_Value5:
		case EM_HouseServantValueType_Value6:
		case EM_HouseServantValueType_Value7:
			Value[ Type - EM_HouseServantValueType_Value0 ] = V;
			return true;
		case EM_HouseServantValueType_MaxValue0:	// 0-7 最大基本數值
		case EM_HouseServantValueType_MaxValue1:
		case EM_HouseServantValueType_MaxValue2:
		case EM_HouseServantValueType_MaxValue3:
		case EM_HouseServantValueType_MaxValue4:
		case EM_HouseServantValueType_MaxValue5:
		case EM_HouseServantValueType_MaxValue6:
		case EM_HouseServantValueType_MaxValue7:
			MaxValue[ Type - EM_HouseServantValueType_MaxValue0 ] = V;
			return true;
		case EM_HouseServantValueType_ClothColor0:	// 0-1 衣服顏色
			ClothColor[0] = V;
			return true;
		case EM_HouseServantValueType_ClothColor1:
			ClothColor[1] = V;
			return true;
		}
		return false;
	}
	
};


//房屋資料庫資訊
struct HouseBaseDBStruct
{
	int			HouseDBID;	
	int			MaxItemCount;
	int			EnergyPoint;
	int			HouseType;
	unsigned	LastRantelTime;										//最後一次收取租金的時間
	int			OwnerDBID;
	StaticString< _MAX_NAMERECORD_SIZE_ >		Password;
	StaticFlag<_MAX_HOUSES_SHOPFUNCTION_COUNT_>	ShopFunction;		//使用的功能狀態
	StaticString< _MAX_NAMERECORD_SIZE_ >		HouseName;			//房屋名稱

	union
	{
		char		ClientData[MAX_HOUSE_CLIENT_DATA_SIZE_];
		struct
		{
			char Friend_Enter[MAX_HOUSE_STRING_SIZE]; //好友進入小屋問候語
			char Friend_Leave[MAX_HOUSE_STRING_SIZE]; //好友離開小屋問候語
			char Friend_Use  [MAX_HOUSE_STRING_SIZE]; //好友使用家具問候語
		};
	};

	int			ItemLogPos;
	int			UnCheckItemLogCount;
	HouseFriendItemLogStruct ItemLog[ MAX_HOUSE_ITEM_LOG_COUNT ];

	//////////////////////////////////////////////////////////////////////////
	//女僕資料
	//////////////////////////////////////////////////////////////////////////
	unsigned	LastServantProcTime;
	HouseServantStruct Servant[ MAX_SERVANT_COUNT ];



	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		HouseDBID = -1;		
	}

	void	AddItemLog( HouseFriendItemLogStruct& AddItemLog )
	{
		if( unsigned(ItemLogPos) >= MAX_HOUSE_ITEM_LOG_COUNT )
			ItemLogPos = 0;

		ItemLog[ ItemLogPos ] = AddItemLog;
		ItemLogPos++;
		UnCheckItemLogCount++;
	}
	void ClearItemLog()
	{
		memset( ItemLog , 0 , sizeof(ItemLog) );
		ItemLogPos = 0;
		UnCheckItemLogCount = 0;
	}
};

//-------------------------------------------------------------------------
/*
struct HousePosStruct
{
	union
	{
		unsigned int Value;
		struct  
		{
			char Lv[4];		//-1表示沒有
		};
	};

	int RelativePos( )
	{
		for( int i = 1 ; i < 4 ; i++ )
		{
			if( Lv[i] == -1 )
				return Lv[i-1];				
		}
		return Lv[0];
	}

	int	Level()
	{
		for( int i = 1 ; i < 4 ; i++ )
		{
			if( Lv[i] == -1 )
				return i;
		}
		return 3;
	}
};
*/

//物品的資料庫資訊
struct HouseItemDBStruct
{
	int					HouseDBID;
	int					ItemDBID;
	int					ParentItemDBID;

	int					Pos;
	ItemFieldStruct		Item;
	House3DLayoutStruct	Layout;
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		HouseDBID = -1;
		ItemDBID = -1;
		ParentItemDBID = -1;
	}
};
//-------------------------------------------------------------------------
//商城物品資訊
struct DepartmentStoreBaseInfoStruct
{
	int					GUID;
	int					NeedMemberID;
	int					SellType[3];
	int					SortNumber;
	ItemFieldStruct		Item;
	wchar_t				ItemName[32];
	wchar_t				Note[256];
	struct  
	{
		float				BeginTime;
		float				EndTime;
		int					Count;
		int					OrgCount;		//原始已販賣量
		int					MaxCount;
		int					Cost;			//價錢
		int					Cost_Bonus;		//需要紅利幣
		int					Cost_Free;		//必爾丁幣
		int					Get_Bonus;		//需要紅利幣
		int					Icon;
	}Sell;

	struct
	{
		short	Count;
		short	Rate[8];
	}Gamble;

	DepartmentStoreBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
		GUID = -1;
	}
};

struct DB_DepartmentStoreBaseInfoStruct
{
	int ItemIDList[8];
	int ItemCountList[8];
	DepartmentStoreBaseInfoStruct Item;
};


/*
struct DepartmentStoreBaseInfoStruct
{
	int					GUID;
	int					NeedMemberID;
	int					SellType[3];
	int					SortNumber;
	struct
	{
		int		DisplayObjID;
		char	Name[32]
		int		OrgObjID[5];
		int		Count[5];		
	}Item;

	struct  
	{
		float				BeginTime;
		float				EndTime;
		int					Count;
		int					OrgCount;		//原始已販賣量
		int					MaxCount;
		int					Cost;			//價錢
		int					Cost_Bonus;		//需要紅利幣
		int					Get_Bonus;		//需要紅利幣
		int					Icon;
	}Sell;

	DepartmentStoreBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
		GUID = -1;
	}
	};
*/
//////////////////////////////////////////////////////////////////////////
enum   PKTypeENUM
{
	EM_PK_Normal            ,	//非PK區
	EM_PK_All	            ,	//大亂鬥
	EM_PK_Party	            ,	//同Party不能互打
	EM_PK_Party_Guild		,	//同Party 同公會 不能互打
};
//////////////////////////////////////////////////////////////////////////
struct UntrustFlagStruct
{
	union
	{
		int _Flag;
		struct
		{
			bool DisableMail					: 1;	//無法使用信箱
			bool DisableDepartmentStoreMailGift : 1;	//無法商城送禮
			bool DisableOpenAC					: 1;	//無法使用拍賣場
			bool DisablePlayerTrade				: 1;	//無法與玩家交易
			bool DisablePlayerChannelTalk		: 1;	//無法使用密語
			bool DisableSysChannelTalk			: 1;	//無法使用世界頻道
			bool DisableZoneChannelTalk			: 1;	//無法使用區域頻道
		};
	};
};
//////////////////////////////////////////////////////////////////////////
//帳號基本資料
struct PlayerAccountBaseInfoStruct
{
	int	 AccountMoney;
	int	 BonusMoney;
	int  ManageLv;
	char Password[33];
	int	 PlayTimeQuota;
	int	 LockAccountTime;
	int  LockAccountMoney[ Def_AccountMoneyLockTime_Max_Count_ ];	
	int  LockAccountMoney_Forever;
	StaticFlag< _ACCOUNT_FLAG_COUNT_ >	AccountFlag;		//帳號資料旗標

	int		 VipMemberType;
	float	VipMemberTerm;
	int		VipMemberFlag;	

	UntrustFlagStruct		UntrustFlag;

	int		CoolClothList[ _DEF_MAX_COOL_CLOTH_COUNT_ ];

	int		CheckFailedTimes;
	int		LastCheckTime;

	PlayerAccountBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//公告資訊結購
struct ImportBoardBaseStruct
{
	float	UpdateTime;
	int		SortNumber;
	char	Title[ 256 ];
	char	Content[2048];

	bool	IsHot;
	bool	IsRed;
	float	BeginTime;
	float	EndTime;
	int		Item[5];
	int		ItemCount[5];
	int		Money;
	int		Money_Account;
	ImportBoardBaseStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//Client 端系統資訊
struct ClientComputerInfoStruct
{
	int CPU;
	int RAM_Total;
	int RAM_Free;
	int RAM_Game;
	int Ping;
	int FPS;
	int ZoneID;
	int IPNum;
};
//////////////////////////////////////////////////////////////////////////
//client 要求封包簡查類型
enum ClientPacketCheckTypeENUM
{
	EM_ClientPacketCheckType_HateList	,	
	EM_ClientPacketCheckType_Move		,	
	EM_ClientPacketCheckType_Talk		,
	EM_ClientPacketCheckType_Mail		,
	EM_ClientPacketCheckType_ACSerch	,

	EM_ClientPacketCheckType_Max		=30	,
};

//////////////////////////////////////////////////////////////////////////
//說話 Log 類型
enum TalkLogTypeENUM
{
	EM_TalkLogType_Talk			,//密語
	EM_TalkLogType_Party		,//隊伍頻道
	EM_TalkLogType_Range		,//範圍
	EM_TalkLogType_ZoneChannel	,//區頻道
	EM_TalkLogType_SystemChannel,//系統頻道
	EM_TalkLogType_Guild		,//公會頻道
	EM_TalkLogType_PlayerChannel,//玩家頻道
};
//////////////////////////////////////////////////////////////////////////
struct MineCheckStruct
{
	float X , Y , Z;
	int	  Count;
};
//////////////////////////////////////////////////////////////////////////
struct AccountBagItemFieldDBStruct
{
	int				ItemDBID;
	ItemFieldStruct Item;

	void Init()
	{
		ItemDBID = -1;
		Item.Init();
	}
};

struct WebShopBagItemFieldDBStruct
{
	int				ItemDBID;
	ItemFieldStruct Item;
	char			Message[256];
	void Init()
	{
		ItemDBID = -1;
		Item.Init();
	}

};

//////////////////////////////////////////////////////////////////////////
struct ChangeWorldStruct
{
	int						WorldID;				//登入另外世界的ID	
	int						WorldNetID;			
	RolePosStruct			RetPos;
	int						RetZoneID;
};
//////////////////////////////////////////////////////////////////////////
enum ItemTimeoutPosENUM
{
	EM_ItemTimeoutPos_Body	,
	EM_ItemTimeoutPos_Bank	,
	EM_ItemTimeoutPos_EQ	,
};
//////////////////////////////////////////////////////////////////////////
//記錄的傳送點
struct LocationSaveStruct
{
	int		IconType;		//0 表示沒資料
	char	Note[64];	    //註解
	int		ZoneID;
	float	X , Y , Z;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
/*
//帳號幣匯入時間
struct AccountMoneyLockTimeStruct
{
	int		Time;
	int		AccountMoney;
};
*/
//////////////////////////////////////////////////////////////////////////
//墓碑資訊
struct TombStruct
{
	int	ItemGUID;		//如果生存奇還沒結束，可是找不到物件，就重新產生墓碑
	int	CreateTime;
	int ZoneID;
	float X , Y , Z;
	int	DebtExp;
	int	DebtTp;
	int Exp;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
enum LuaPlotClockTypeENUM
{
	EM_LuaPlotClockType_Close	,
	EM_LuaPlotClockType_Open	,
	EM_LuaPlotClockType_Stop	,

};
//劇情用計時器
struct LuaPlotClockStruct
{
	LuaPlotClockTypeENUM	Type;
	int		CheckValue;		
	int		BeginTime;
	int		EndTime;
	int		NowTime;
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> ChangeZonePlot;
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> TimeUpPlot;

};
//////////////////////////////////////////////////////////////////////////
//Client 狀態資訊
struct ClientStateStruct
{
	union
	{
		int _Mode;
		struct
		{
			bool	InWater	:1;	//在水中
		};
	};
};
//////////////////////////////////////////////////////////////////////////
#define		MAX_CultivatePet_SkillCount		10
#define		MAX_CultivatePet_Count			6
#define		MAX_CultivatePet_Product_Count_	3
//#define MAX_CultivatePet_EQ_Count	7
enum CultivatePetEQTypeENUM
{
	EM_CultivatePetEQType_Tools		,
	EM_CultivatePetEQType_Source	,
	EM_CultivatePetEQType_Product1	,
	EM_CultivatePetEQType_Product2	,
	EM_CultivatePetEQType_Product3	,
	EM_CultivatePetEQType_Other0 	,
	EM_CultivatePetEQType_Other1	,
	EM_CultivatePetEQType_Other2	,
	EM_CultivatePetEQType_Other3	,
	EM_CultivatePetEQType_MAX		,
};


struct CultivatePetMode
{
	union
	{
		int _Mode;
		struct  
		{
			bool IsSummon	:1;
			bool IsTravail	:1;

			//生活技
			bool BlackSmith :1;
			bool Carpenter  :1;
			bool MakeArmor	:1;
			bool Tailor		:1;
			bool Cook		:1;
			bool Alchemy	:1;
			bool Mining		:1;
			bool Lumbering	:1;
			bool Herblism	:1;
			bool Fishing	:1;
		};
	};
};

enum CultivatePetCommandTypeENUM
{
	EM_CultivatePetCommandType_None			,	//沒狀態(停止生活技能)
	EM_CultivatePetCommandType_OnTimeEvent	,	//client 端每10秒通知Server 看那隻寵物(處理說話or特別事件)
	EM_CultivatePetCommandType_Summon		,	//召喚寵物
	EM_CultivatePetCommandType_Feed			,	//餵食
	EM_CultivatePetCommandType_Travel		,	//旅行
	EM_CultivatePetCommandType_Free			,	//放生
	EM_CultivatePetCommandType_Train		,	//特訓
	EM_CultivatePetCommandType_Return		,	//召喚出的寵物回收
	//////////////////////////////////////////////////////////////////////////
	EM_CultivatePetCommandType_LiftSkill		,
	/*
	EM_CultivatePetCommandType_LiftSkill_BlackSmith	=100,	// 打鐵
	EM_CultivatePetCommandType_LiftSkill_Carpenter	,	// 木工
	EM_CultivatePetCommandType_LiftSkill_MakeArmor	,	// 製甲
	EM_CultivatePetCommandType_LiftSkill_Tailor		,	// 裁縫
	EM_CultivatePetCommandType_LiftSkill_Cook		,	// 烹飪
	EM_CultivatePetCommandType_LiftSkill_Alchemy	,	// 煉金
	EM_CultivatePetCommandType_LiftSkill_Mining		,	// 挖礦
	EM_CultivatePetCommandType_LiftSkill_Lumbering	,	// 砍材
	EM_CultivatePetCommandType_LiftSkill_Herblism	,	// 採藥
	EM_CultivatePetCommandType_LiftSkill_Fishing	,	// 釣魚
	EM_CultivatePetCommandType_LiftSkill_Plant		,	// 種植
*/
};

enum CultivatePetStructValueTypeENUM
{
	EM_CultivatePetStructValueType_ItemOrgID	,
	EM_CultivatePetStructValueType_CreateTime	,
	EM_CultivatePetStructValueType_OrgObjID		,	//( + Pos*100 )
	EM_CultivatePetStructValueType_Lv			,
	EM_CultivatePetStructValueType_PetType		,
	EM_CultivatePetStructValueType_EventColdown	,		//事件冷卻
	EM_CultivatePetStructValueType_EventType	,		//事件類型
	EM_CultivatePetStructValueType_LifeSkillTablePos,
	EM_CultivatePetStructValueType_Exp			,
	EM_CultivatePetStructValueType_SKillPoint	,
	EM_CultivatePetStructValueType_TotalSkillPoint,	
	EM_CultivatePetStructValueType_Loyal		,
	EM_CultivatePetStructValueType_Hunger		,
	EM_CultivatePetStructValueType_Talent		,
	EM_CultivatePetStructValueType_Spirit		,
	EM_CultivatePetStructValueType_Mode			,
	EM_CultivatePetStructValueType_Str			,
	EM_CultivatePetStructValueType_Sta			,
	EM_CultivatePetStructValueType_Agi			,
	EM_CultivatePetStructValueType_Int			,
	EM_CultivatePetStructValueType_Mnd			,
	EM_CultivatePetStructValueType_Property		,
	EM_CultivatePetStructValueType_TrainCount	,
	EM_CultivatePetStructValueType_MagicID0		,		
	EM_CultivatePetStructValueType_MagicID1		,
	EM_CultivatePetStructValueType_MagicID2		,
	EM_CultivatePetStructValueType_MagicID3		,
	EM_CultivatePetStructValueType_MagicID4		,
	EM_CultivatePetStructValueType_MagicID5		,
	EM_CultivatePetStructValueType_MagicID6		,
	EM_CultivatePetStructValueType_MagicID7		,
	EM_CultivatePetStructValueType_MagicID8		,
	EM_CultivatePetStructValueType_MagicID9		,
	EM_CultivatePetStructValueType_MagicLv0		,		
	EM_CultivatePetStructValueType_MagicLv1		,
	EM_CultivatePetStructValueType_MagicLv2		,
	EM_CultivatePetStructValueType_MagicLv3		,
	EM_CultivatePetStructValueType_MagicLv4		,
	EM_CultivatePetStructValueType_MagicLv5		,
	EM_CultivatePetStructValueType_MagicLv6		,
	EM_CultivatePetStructValueType_MagicLv7		,
	EM_CultivatePetStructValueType_MagicLv8		,
	EM_CultivatePetStructValueType_MagicLv9		,
	EM_CultivatePetStructValueType_MagicCount	,
	EM_CultivatePetStructValueType_LifeSkill1	,
	EM_CultivatePetStructValueType_LifeSkill2	,
	EM_CultivatePetStructValueType_LifeSkill3	,
	EM_CultivatePetStructValueType_LifeSkill4	,
	EM_CultivatePetStructValueType_MergeCount	,
	EM_CultivatePetStructValueType_Max			,
};

struct MagicBaseStruct
{
	int ID;
	int Lv;
};

#define _MAX_PET_SKILLPOINT_	10000
#define _MAX_PET_UNDERGOPOINT_	10000
#define _MAX_PET_HUNGER_		100
#define _MAX_PET_LOYAL_			100
#define _MAX_PET_TALENT_		100

//養殖寵物
struct CultivatePetStruct
{
	StaticString< _MAX_NAMERECORD_SIZE_ >   Name;
	union
	{
		int			_Value[ EM_CultivatePetStructValueType_Max ];
		float		_FloatValue[ EM_CultivatePetStructValueType_Max ];
		struct  
		{
			int		ItemOrgID;				//寵物蛋物品
			int		CreateTime;				//產生時間
			int		PetOrgID;
			int		Lv;
			int		PetType;

			int								EventColdown;			//事件冷卻
			CultivatePetCommandTypeENUM		EventType;				//事件類型
			int		LifeSkillTablePos;
			int		Exp;
			int		SkillPoint;
			int		TotalSkillPoint;
			int		Loyal;		//親密度
			int		Hunger;		//飽食度
			float	Talent;		//天資
			int		Spirit;		//活力(改為歷練)
			CultivatePetMode	Mode;
			float				STR,STA,AGI,INT,MND;
			MagicResistENUM		Property;
			int		TrainCount;

			StaticVector< MagicBaseStruct , MAX_CultivatePet_SkillCount > Magic;

			float	LifeSkill[ EM_CultivatePetLifeSkillType_Max ];		

			int		DayMergeCount;		//今天融合次數
		};
	};

	union
	{
		ItemFieldStruct		EQ[ EM_CultivatePetEQType_MAX ];
		struct  
		{
			ItemFieldStruct	Tools;			//寵物工具
			ItemFieldStruct Source;			//任何物品
			ItemFieldStruct Product[MAX_CultivatePet_Product_Count_];
			ItemFieldStruct Other[4];		//寵物擺設品		
		};
	};
/*
	bool CheckPetFlag( int ID )
	{
		if( unsigned( ID ) >= _DEF_MAX_PET_TYPE_ )
			return false;

		int Pos1 = ID % 8;
		int Pos2 = ID / 8;

		return ( PetFlagType[ Pos2 ] && ( 1<< Pos1 ) != 0 );		
	};
	void SetPetFlag( int ID , bool Value )
	{
		if( unsigned( ID ) >= _DEF_MAX_PET_TYPE_ )
			return;

		int Pos1 = ID % 8;
		int Pos2 = ID / 8;

		PetFlagType[ Pos2 ] |= ( 1<< Pos1 );
	};
*/
	void init( )
	{
		memset( this , 0 , sizeof(CultivatePetStruct) );
	
		for( int i = 0 ; i < EM_CultivatePetLifeSkillType_Max ;i ++ )
			LifeSkill[i] = 1;
	};
	bool IsEmpty()
	{
		if( PetOrgID == 0 )
			return true;
		return false;
	}

	bool CheckEqEmpty()
	{
		for( int i = 0 ; i < EM_CultivatePetEQType_MAX ; i++ )
		{
			if( EQ[i].IsEmpty() == false )
				return false;
		}
		return true;
	};
/*
	void TranAccept( )
	{
		STR += LastTran.STR; LastTran.STR = 0;
		STA += LastTran.STA; LastTran.STA = 0;
		INT += LastTran.INT; LastTran.INT = 0;
		MND += LastTran.MND; LastTran.MND = 0;
		AGI += LastTran.AGI; LastTran.AGI = 0;
		TrainCheckCount = 0;
	}
	*/

	float AssistPower( int Type );
};

struct DB_CultivatePetStruct
{
	int	PlayerDBID;
	int	Pos;
	CultivatePetStruct Info;
};
//////////////////////////////////////////////////////////////////////////
struct RolePetStruct
{
	CultivatePetStruct	Base[ MAX_CultivatePet_Count ];
	int			Money;				//寵物幣
	int			NextMergeResetTime;	//下一次融合更新
};
//////////////////////////////////////////////////////////////////////////
//公會屋戰狀態
enum GuildHouseWarStateENUM
{
	EM_GuildHouseWarState_None			,	//未知
	EM_GuildHouseWarState_Appointment	,	//預約
	EM_GuildHouseWarState_Prepare		,	//準備
	EM_GuildHouseWarState_Failed		,	//沒有配到隊
	EM_GuildHouseWarState_Fight			,	//戰爭中
	EM_GuildHouseWarState_FightEnd		,	//戰爭結束
	EM_GuildHouseWarState_FightEnd_Even	,	//戰爭平手
	EM_GuildHouseWarState_FightEnd_Win	,	//戰爭勝利
	EM_GuildHouseWarState_FightEnd_Lost	,	//戰爭失敗
};

struct GuildHouseWarInfoStruct
{
	int		ZoneGroupID;
	int		GuildID;			//預約戰的公會
	int		Score;				//積分
	int		EnemyGuildID;		//對戰公會(-1表示沒有)
	int		GuildLv;
	bool	IsAcceptAssignment;	//同意約戰


	GuildHouseWarStateENUM State;
	StaticString< _MAX_NAMERECORD_SIZE_ >   GuildName;

	GuildHouseWarInfoStruct( )
	{
		memset( this , 0 , sizeof(*this) );
		//ZoneGroupID = RoleDataEx::G_ZoneID / 1000;
	}
	
	bool operator <  ( const GuildHouseWarInfoStruct& P ) const
	{	
		/*
		int S = Score;
		int PS = P.Score;
		if( EnemyGuildID )
			S = -1000;
		if( P.EnemyGuildID )
			PS = -1000;

		return PS < S;	
		*/
		if( GuildLv == P.GuildLv)
			return P.Score < Score;
		return P.GuildLv < GuildLv;
	}

};

enum GuildHouseWarResultENUM
{
	EM_GuildHouseWarResultENUM_Win		,	
	EM_GuildHouseWarResultENUM_Lost		,	
	EM_GuildHouseWarResultENUM_Even		,	
};
//////////////////////////////////////////////////////////////////////////
//公會戰 公會基本資訊
struct GuildHouseWarFightBaseStruct
{
	int GuildID;
	int Score;
	int	Energy;
//	map< int , int > ValueMap;
	GuildHouseWarFightBaseStruct()
	{
		Score = 5000;
		GuildID = 0;
		Energy = 0;
	}
};

//公會戰資訊
struct GuildHouseWarFightStruct
{
//	float BeginTime;
//	float EndTime;

	GuildHouseWarFightBaseStruct	Base[2];

	bool IsReady;
	bool IsEndWar;
	bool IsAssignment;		//指定對戰

	GuildHouseWarFightStruct()
	{
		//memset( this , 0 , sizeof(GuildHouseWarFightStruct) );
//		BeginTime = 0;
//		EndTime = 0;
		IsEndWar = false;
//		Base[0].Score = 5000;
//		Base[1].Score = 5000;
	}
	/*
	bool AddWarValue(int GuildID , int Type , int Value )
	{
		map< int , int >* ValueMap ;
		if( GuildID == Base[0].GuildID )
			ValueMap = &Base[0].ValueMap;
		else if( GuildID == Base[1].GuildID )
			ValueMap = &Base[1].ValueMap;
		else return false;

		(*ValueMap)[Type] += Value;
		return true;
	}
	int GetWarValue(int GuildID , int Type )
	{
		map< int , int >* ValueMap ;
		if( GuildID == Base[0].GuildID )
			ValueMap = &Base[0].ValueMap;
		else if( GuildID == Base[1].GuildID )
			ValueMap = &Base[1].ValueMap;
		else return 0;

		return (*ValueMap)[Type];		
	}
	*/
	int	GetScore( int GuildID )
	{
		if( Base[0].GuildID == GuildID )
			return Base[0].Score;
		else if( Base[1].GuildID == GuildID )
			return Base[1].Score;
		return 0;
	}

	bool AddScore( int GuildID , int Value )
	{
		if( Base[0].Score == 0 || Base[1].Score == 0 )
			return false;

		if( Base[0].GuildID == GuildID )
		{
			Base[0].Score += Value;
			Base[1].Score -= Value;

			if(		Base[0].Score < 0 
				||	Base[1].Score > 10000 )
			{
				Base[0].Score = 0;
				Base[1].Score = 10000;
			}
			if(		Base[0].Score > 10000 
				||	Base[1].Score < 0 )
			{
				Base[0].Score = 10000;
				Base[1].Score = 0;
			}
			return true;
		}

		if( Base[1].GuildID == GuildID )
		{
			Base[1].Score += Value;
			Base[0].Score -= Value;

			if(		Base[1].Score < 0 
				||	Base[0].Score > 10000 )
			{
				Base[1].Score = 0;
				Base[0].Score = 10000;
			}
			if(		Base[1].Score > 10000 
				||	Base[0].Score < 0 )
			{
				Base[1].Score = 10000;
				Base[0].Score = 0;
			}
			return true;
		}

		return false;
	}

	bool AddEnergy( int GuildID , int Value )
	{
		GuildHouseWarFightBaseStruct*	BaseInfo = NULL;
		if( Base[0].GuildID == GuildID )
			BaseInfo = &Base[0];
		else if( Base[1].GuildID == GuildID )
			BaseInfo = &Base[1];
		else 
			return false;

		BaseInfo->Energy += Value;
		if( Value < 0 ) 
			Value = 0 ;

		return true;
	}
	int	 GetEnergy( int GuildID )
	{
		GuildHouseWarFightBaseStruct*	BaseInfo = NULL;
		if( Base[0].GuildID == GuildID )
			BaseInfo = &Base[0];
		else if( Base[1].GuildID == GuildID )
			BaseInfo = &Base[1];
		else 
			return 0;

		return BaseInfo->Energy;
	}
};
//////////////////////////////////////////////////////////////////////////
enum	GuildWarPlayerValueENUM
{
	EM_GuildWarPlayerValue_KillPoint	,		//擊破數
	EM_GuildWarPlayerValue_HitPoint		,		//傷害量
	EM_GuildWarPlayerValue_DefPoint		,		//防禦量
	EM_GuildWarPlayerValue_HealPoint	,		//治療量
	EM_GuildWarPlayerValue_WarScore		,		//戰績取得
	EM_GuildWarPlayerValue_EnergyPoint	,		//能源取得
	EM_GuildWarPlayerValue_OccupyPoint	,		//佔領據點
	EM_GuildWarPlayerValue_TotalScore	,		//總分

	EM_GuildWarPlayerValue_Max			,
};


//公會屋戰玩家的戰事資料
struct GuildWarPlayerInfoStruct
{
	int		PlayerDBID;
	int		GuildID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   RoleName;

	union
	{
		int _Score[ EM_GuildWarPlayerValue_Max ];
		struct
		{
			int	KillPoint;			//擊破數
			int	HitPoint;			//傷害量
			int	DefPoint;			//防禦量
			int HealPoint;			//治療量
			int WarScore;			//戰績取得
			int EnergyPoint;		//能源取得
			int OccupyPoint;		//佔領據點
			int TotalScore;			//總分
		};
	};

//	Voc_ENUM		    Voc;								//職業
//	Voc_ENUM		    Voc_Sub;							//副職業
//	int					Level;
//	int					Level_Sub;	

	GuildWarPlayerInfoStruct()
	{
		memset( this , 0 , sizeof(*this));
	}

	bool IsEmpty()
	{
		if( PlayerDBID==0 )
			return true;
		return false;
	}
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_MONSTERHUNT_COUNT_	200
struct MonsterHunterStruct
{
	unsigned short	KillCount[ _MAX_MONSTERHUNT_COUNT_ ];
	unsigned short	DeadCount[ _MAX_MONSTERHUNT_COUNT_ ];
	int		TotalKillCount_Player;
	int		TotalKillCount_NPC;
	int		TotalDeadCount_Player;
	int		TotalDeadCount_NPC;
};
//////////////////////////////////////////////////////////////////////////
struct OfflineMessageDBStruct
{
	float	Time;
	int		Type;
	int		ToPlayerDBID;
	int		FromPlayerDBID;
	int		ManageLv;
	StaticString <32> FromName;
	StaticString <32> ToName;
	StaticString <512>  Content;
};
//////////////////////////////////////////////////////////////////////////
struct CheckKeyAddressStruct
{
	char		Key[64];
	int			Address;
};
//////////////////////////////////////////////////////////////////////////
struct SysKeyValueStruct
{
	vector<int>		GlobalItemDrop;
	vector<int>		GlobalItemDrop_BigMonster;
	vector<int>		GlobalItemDrop_King;
	vector<int>		GlobalItemDrop_WorldKing;
	vector<int>		GlobalItemDrop_DepartmentStore;
	int				Money_GoldObjID;
	int				Money_AccountObjID;	
	int				Money_BonusObjID;
	int				TreasureBaseObjID;
	int				PK_Revive_ZoneID;
	float			PK_Revive_X;
	float			PK_Revive_Y;
	float			PK_Revive_Z;
	int				PK_ProtectEq_ItemID;

	int				MagicStoneCount;			//魔石種類
	int				MagicStoneStart;			//魔石開始位置
	int				Teleport_PointObjID;
	int				MagicBoxOpenKeyItemID;

	int				GoodEvilBuf[9];

	int				GamebleItemState_LockItemID;	//屬性賭博鎖定物品

	struct  
	{
		int	ItemWeapon[10][20];
		int	ItemArmor[10][20];
		int	DLvClothes;
		int	DLvPants;
		int	DLvWeapon_OneHand;
		int	DLvWeapon_TwoHand;
		int	DLvOther;
	}Dissolution;

	int			SysQuestColor_NPC;
	int			SysQuestColor_ITEM;
	int			SysQuestColor_ZONE;

	int			TombObjID;
	int			HouseBuff;
	int			Pet_PopItemID;
	int			Pet_ReTrainItemID;
//	int			KeyItem_EQBackup;

	union
	{
		int		ElementPowerMagicID[EM_MagicResist_MAXCOUNT];
		struct  
		{
			int			EarthPowerMagicID;
			int			WaterPowerMagicID;
			int			FirePowerMagicID;
			int			WindPowerMagicID;
			int			LightPowerMagicID;
			int			DarkPowerMagicID;
		};
	};

	struct
	{
		int FruitsExp;
		int FeedPointDec;
//		int MagicWater;
//		int Topdress;
//		int Water;
	}Plant;

	vector<int>		MagicStoneShopAbilityList;
	PriceTypeENUM	MagicStoneShopCostType[2];


	float	TitleSys_FamouseDesc_Min;

	
	SysKeyValueStruct()
	{
		Init();
	};
	void	Init()
	{
		GlobalItemDrop.clear();
		GlobalItemDrop_BigMonster.clear();
		GlobalItemDrop_King.clear();
		GlobalItemDrop_WorldKing.clear();
		GlobalItemDrop_DepartmentStore.clear();
		Money_GoldObjID = 0;
		Money_AccountObjID = 0;
		Money_BonusObjID = 0;
		TreasureBaseObjID = 0;		
	};
};
//////////////////////////////////////////////////////////////////////////
enum	GuildHouseItemInfoStateENUM
{
	EM_GuildHouseItemInfoState_None		,
	EM_GuildHouseItemInfoState_Insert	,
	EM_GuildHouseItemInfoState_Update	,
};
//----------------------------------------------------------------------------------------------
enum	GuildBuildingTypeENUM
{
	EM_GuildBuildingType_None		,
	EM_GuildBuildingType_Building	,
	EM_GuildBuildingType_Furniture	,
};
//----------------------------------------------------------------------------------------------
//公會屋物品
struct GuildHouseItemStruct
{
	int		GuildID;
	int		ItemDBID;
	int		PageID;
	int		PosID;

	GuildHouseItemInfoStateENUM	State;
	ItemFieldStruct	Item;
};
//----------------------------------------------------------------------------------------------
//物品的資料庫資訊
struct GuildHouseFurnitureItemStruct
{
	int					GuildID;
	int					OwnerDBID;
	int					ItemDBID;
	int					Pos;
	ItemFieldStruct		Item;
	House3DLayoutStruct	Layout;
	GuildHouseItemInfoStateENUM	State;
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GuildID = -1;
		ItemDBID = -1;
	}
};
//----------------------------------------------------------------------------------------------
enum	GuildHouseBuildingInfoStateENUM
{
	EM_GuildHouseBuildingInfoState_None		,
	EM_GuildHouseBuildingInfoState_Insert	,
	EM_GuildHouseBuildingInfoState_Update	,
};
//公會建築資料
struct GuildHouseBuildingInfoStruct
{
	int		GuildID;
	int		BuildingDBID;
	int		ParentDBID;
	int		BuildingID;
	char	PointStr[32];
	float	Dir;
	union
	{
		int		Value[4];
		struct  
		{
			union
			{
				int _Mode;
				struct  
				{
					bool	IsActive : 1;
					bool	Revive1  : 1;
					bool	Revive2  : 1;
					bool	Revive3  : 1;
					bool	Revive4  : 1;
					bool	Revive5  : 1;
					bool	Revive6  : 1;
					bool	Revive7  : 1;
					bool	Revive8  : 1;
				};
			};
			int Value1;
			int Value2;
			int Value3;
		};
	};

	GuildHouseBuildingInfoStateENUM State;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//----------------------------------------------------------------------------------------------
//公會屋資訊
struct GuildHousesInfoStruct
{
	int		GuildID;
	int		ItemMaxPageCount;
	int		FurnitureMaxCount;
	int		LastCalRentTime;		//最後一次計算維持費的時間
	int		GuildStyle;				//工會樣式
	int		GuildStyleRight;		//可以使用的工會樣式
//	int		Money;					//公會金錢
//	int		PageRight_Get[ _DEF_GUIDHOUSEITEM_MAX_PAGE_ ];	
//	int		PageRight_Push[ _DEF_GUIDHOUSEITEM_MAX_PAGE_ ];	
};
//----------------------------------------------------------------------------------------------
//倉庫存取權限設定
struct GuildStorehouseRightStruct
{
	int	GuildID;
	int	PageID;
	struct 
	{
		union
		{
			int	_Right;			//權限
			struct  
			{
				bool	View : 1;
				bool	Put	 : 1;
				bool	Get	 : 1;
			};
		};
		int GetCount;		//領取次數
	}Rank[EM_GuildRank_Count];

	GuildStorehouseRightStruct()
	{
		memset( this , 0 , sizeof(*this) );
		for( int i =0 ; i < EM_GuildRank_Count ; i++ )
		{
			Rank[i].View = true;
		}
	}
};
//-------------------------------------------------------------------------
enum GuildHouseLootTypeENUM
{
	EM_GuildHouseLootType_Put	,		
	EM_GuildHouseLootType_Get	,		
	EM_GuildHouseLootType_Move	,
};

//公會倉庫存取Log
struct GuildItemStoreLogStruct
{
	int GuildID;
	int PageID;
	int	Time;
	GuildHouseLootTypeENUM Type;
	int	PlayerDBID;
	int	ItemOrgID;
	int	ItemCount;
	int	FromPageID;
	int ToPageID;
};


//////////////////////////////////////////////////////////////////////////
//金錢兌換表
struct MoneyExchangeKeyValueStruct
{
	char	KeyStr[32];
	int		Value[4];

	MoneyExchangeKeyValueStruct()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//營運商字串修改表
struct SysKeyStrChangeStruct
{
	StaticString< 32 > KeyStr; 
	StaticString< 256 > Content; 

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//計時旗子 代表功能列舉
enum	TimeFlagEffectENUM
{
	//0-99		真實時間

	EM_TimeFlagEffect_BagPage3			= 0 ,	//--背包3
	EM_TimeFlagEffect_BagPage4				,	//--背包4
	EM_TimeFlagEffect_BagPage5				,	//--背包3
	EM_TimeFlagEffect_BagPage6				,	//--背包4

	EM_TimeFlagEffect_BankBag2			= 10,	//銀行背包 開放
	EM_TimeFlagEffect_BankBag3				,	//銀行背包 開放
	EM_TimeFlagEffect_BankBag4				,	//銀行背包 開放
	EM_TimeFlagEffect_BankBag5				,	//銀行背包 開放

	EM_TimeFlagEffect_HonorParty		= 20,	//榮譽組隊
	EM_TimeFlagEffect_MailPaper				,	//郵件信紙	
	EM_TimeFlagEffect_DailyFlag				,	//每日重要物品清除機制	
	EM_TimeFlagEffect_MailMultiItem			,	//郵件單次傳送多個物品
	EM_TimeFlagEffect_HandyBank				,	//隨身銀行
	EM_TimeFlagEffect_HandyAuction			,	//隨身AC
	EM_TimeFlagEffect_HandyMail				,	//隨身信箱

	EM_TimeFlagEffect_PetPage3			= 30,	//寵物第三頁
	EM_TimeFlagEffect_PetPage4				,	//寵物第三頁
	EM_TimeFlagEffect_PetPage5				,	//寵物第三頁
	EM_TimeFlagEffect_PetPage6				,	//寵物第三頁

	//100-199	遊戲時間
};

//////////////////////////////////////////////////////////////////////////
//送封包給Client 的模式
struct SendPacketModeStruct
{
	union
	{
		int Mode;
		struct  
		{
			bool ReducePlayerMove		: 1;	//玩家移動部分忽略 每秒才會送一次
			bool IgnorePlayerMove		: 1;	//所有移動忽略
			bool IgnoreAllMove			: 1;	//忽略所有移動( 玩家與NPC的移動封包都不送)
		};
	};
};
//////////////////////////////////////////////////////////////////////////
//保留角色資料
struct ReserverRoleStruct
{
	bool		IsAutoCreate;
	StaticString< _MAX_NAMERECORD_SIZE_ > RoleName;
	int			Sex;
	int			Race;
	int			Job;
	LookStruct	Look;
//	int			GiftItemID;
};
//////////////////////////////////////////////////////////////////////////
struct BattleArraryStruct
{
	int		GItemID;
	float	Angle;
	float	Dist;
	bool	UsePathFind;
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_INSTANCE_SETTING_COUNT_	100
struct InstanceSettingStruct
{
/*
	struct
	{
		int		 KeyID;
		unsigned LiveTime;	
	}Setting[ _MAX_INSTANCE_SETTING_COUNT_ ];
*/
	int		 KeyID		[ _MAX_INSTANCE_SETTING_COUNT_ ];
	unsigned LiveTime	[ _MAX_INSTANCE_SETTING_COUNT_ ];	
	unsigned ExtendTime	[ _MAX_INSTANCE_SETTING_COUNT_ ];	//展期時間
	

};
//////////////////////////////////////////////////////////////////////////
#define _MAX_EX_SKILL_COUNT_	10
//劇情設定可使用技能
struct ExSkillBaseStruct
{
	int		SpellerID;		//施法者ID
	int		SkillID;		//法術ID
	int		SkillLv;		//法術等級
	bool operator == ( const ExSkillBaseStruct& P ) const
	{
		return (	P.SpellerID == SpellerID
				&& P.SkillID == SkillID
				&& P.SkillLv == SkillLv	);
	}
};
//////////////////////////////////////////////////////////////////////////
//比賽結果
enum GameResultENUM
{
	EM_GameResult_Win	,
	EM_GameResult_Lost	,
	EM_GameResult_Even	,
};
//////////////////////////////////////////////////////////////////////////
//排行榜 排行類型
enum BillbaordSortTypeENUM
{
	EM_BillboardSortType_Money					,//擁有的金幣    
	EM_BillboardSortType_Money_Account			,//擁有的晶鑽    
	EM_BillboardSortType_Money_Bonus			,//擁有的紅鑽    
	EM_BillboardSortType_STR					,//力量           
	EM_BillboardSortType_AGI					,//敏捷           
	EM_BillboardSortType_STA					,//耐力           
	EM_BillboardSortType_INT					,//智慧           
	EM_BillboardSortType_MND					,//精神           
	EM_BillboardSortType_ATK					,//攻擊強度       
	EM_BillboardSortType_MATK					,//法術強度       
	EM_BillboardSortType_DEF					,//物理防禦       
	EM_BillboardSortType_MDEF					,//法術防禦      
	EM_BillboardSortType_Honor					,//榮譽點數      
	EM_BillboardSortType_TitleCount				,//拿到的稱號數量      
	EM_BillboardSortType_QuestCompleteCount		,//已經完成的任務數量  
};
//////////////////////////////////////////////////////////////////////////
//最後一次處理錯誤訊息
enum RoleErrorMsgENUM
{
	EM_RoleErrorMsg_None	,

	EM_RoleErrorMsg_SpellExSkill_SkillNotFind		,//不會此技能
	EM_RoleErrorMsg_SpellExSkill_SpellerNotExist	,//施法者不存在
	EM_RoleErrorMsg_SpellExSkill_MagicColErr		,//法術資料有問題
	EM_RoleErrorMsg_SpellExSkill_OnSpellErr			,//正在施法中
	EM_RoleErrorMsg_SpellExSkill_TargetLineNotClear	,//有阻擋
	EM_RoleErrorMsg_SpellExSkill_ExplodeTimeErr		,//爆炸時間有問題
};
//////////////////////////////////////////////////////////////////////////
struct MagicStoneExchange
{
	int MagicStoneID;
	int Lv;
	int Money[2];
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_SUIT_SKILL_COUNT_		200
#define	_MAX_SUIT_SKILL_EQ_COUNT_	10
//套裝技能
struct SuitSkllBaseStruct
{
	int			SkillID;
};

struct SuitSkillStruct
{	
	int		LeanSkillCount;
	SuitSkllBaseStruct LeanSkillList[_MAX_SUIT_SKILL_COUNT_];
	int		MaxEqSkillCount;
	int		EQ[_MAX_SUIT_SKILL_EQ_COUNT_];

};
//////////////////////////////////////////////////////////////////////////
struct VipMemberStruct
{
	int		Type;
	float	Term;
	union
	{
		int	_Flag;
		struct  
		{
			bool	Flag_Teleport_Save	: 1;		//傳送之書 免費記點
			bool	Flag_Teleport		: 1;		//傳送之書 免費傳送
			bool	Flag_2		  		: 1;
			bool	Flag_3		  		: 1;
			bool	Flag_4		  		: 1;
			bool	Flag_5		  		: 1;
			bool	Flag_6		  		: 1;
			bool	Flag_7		  		: 1;
		};
	};

	UntrustFlagStruct UntrustFlag;
};	

//////////////////////////////////////////////////////////////////////////
/*
enum BillboardSortTypeENUM
{
	EM_BillboardSortType_STR					,//力量           
	EM_BillboardSortType_AGI					,//敏捷           
	EM_BillboardSortType_STA					,//耐力           
	EM_BillboardSortType_INT					,//智慧           
	EM_BillboardSortType_MND					,//精神           
	EM_BillboardSortType_ATK					,//攻擊強度       
	EM_BillboardSortType_MATK					,//法術強度       
	EM_BillboardSortType_DEF					,//物理防禦       
	EM_BillboardSortType_Phy_ParryRate			,//格檔等級       
	EM_BillboardSortType_Phy_DodgeLv			,//閃躲等級      
	EM_BillboardSortType_MDEF					,//法術防禦      
	EM_BillboardSortType_Honor					,//榮譽點數      
	EM_BillboardSortType_Gold					,//擁有的金幣    
	EM_BillboardSortType_Gold_Account			,//擁有的晶鑽    
	EM_BillboardSortType_Gold_Bonus				,//擁有的紅鑽    
	EM_BillboardSortType_TitleCount				,//拿到的稱號數量      
	EM_BillboardSortType_QuestCompleteCount		,//已經完成的任務數量  
	
};
*/
//////////////////////////////////////////////////////////////////////////
//酷裝資料
struct CoolClothBase
{
	int		ImageObjectID;
	int		MainColor;
	int		OffColor;		

	bool IsEmpty()
	{
		return (ImageObjectID == 0);
	}
};
//酷裝套裝設定資料
struct CoolSuitBase
{
	union
	{
		CoolClothBase	Item[9];
		struct  
		{
			CoolClothBase Head;
			CoolClothBase Gloves;	   
			CoolClothBase Shoes;	
			CoolClothBase Clothes;	   
			CoolClothBase Pants;	
			CoolClothBase Back;		   
			CoolClothBase Belt;		   
			CoolClothBase Shoulder;	   
			CoolClothBase Ornament;
		};
	};

	ShowEQStruct ShowEQ;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		ShowEQ._Value = -1;
	}
};

struct HorseExBagBase
{
	int	ItemID;
	int HorseColor[4];
};

//////////////////////////////////////////////////////////////////////////
//小屋的動作log
enum HouseActionTypeENUM
{
	EM_HouseActionType_Item_BagToFurniture = 0	,//00物品_背包移到傢俱(含傢俱、女僕)
	EM_HouseActionType_Item_FurnitureToBag		,//01物品_傢移到背包(含傢俱、女僕)
	EM_HouseActionType_Item_EqToFurniture		,//02物品_裝備移到傢俱(含傢俱、女僕)
	EM_HouseActionType_Item_FurnitureToEq		,//03物品_傢俱移到裝備(含傢俱、女僕)
	EM_HouseActionType_Item_BagToBank			,//04物品_背包移到銀行
	EM_HouseActionType_Item_BankToBag			,//05物品_銀行移到背包
	EM_HouseActionType_Item_EqToBank			,//06物品_裝備移到銀行
	EM_HouseActionType_Item_BankToEq			,//07物品_銀行移到裝備

	EM_HouseActionType_IntoHouse				,//08進入小屋
	EM_HouseActionType_LeaveHouse				,//09離開小屋
	EM_HouseActionType_ChangeHouseName			,//10修改小屋名稱
	EM_HouseActionType_ChangePassWord			,//11修改小屋密碼
	EM_HouseActionType_ChangeVoc				,//12修改職業
	EM_HouseActionType_EnergyIntro				,//13能量補充
	EM_HouseActionType_SpaceIntro				,//14空間擴充
	EM_HouseActionType_Furniture_Appear			,//15傢俱擺設顯示(含傢俱、女僕)
	EM_HouseActionType_Furniture_Disappear		,//16傢俱擺設隱藏(含傢俱、女僕)
	EM_HouseActionType_ChangeHouseType			,//17格局變更
	EM_HouseActionType_AddFriend				,//18增加房屋好友
	EM_HouseActionType_DeleteFriend				,//19刪除房屋好友
	EM_HouseActionType_HouseGreet				,//20好友問候語

	EM_HouseActionType_Servant_Fire				,//21女僕_開除
	EM_HouseActionType_Servant_Employ			,//21女僕_雇用
	EM_HouseActionType_Servant_Talk				,//22女僕_交談
	EM_HouseActionType_Servant_MagicCourse		,//23女僕_魔法課程
	EM_HouseActionType_Servant_AttackCourse		,//24女僕_攻擊課程
	EM_HouseActionType_Servant_DefendCourse		,//25女僕_守護課程
	EM_HouseActionType_Servant_CookCourse		,//26女僕_烹飪課程
	EM_HouseActionType_Servant_CraftCourse		,//27女僕_工藝課程
};
//////////////////////////////////////////////////////////////////////////
//裝備系統
#define  _MAX_TITLESYS_TITLE_COUNT_	4
struct TitleSysStruct
{
	int			Lv;
	int			Exp;
	float		Famous;
	int			TitleID[_MAX_TITLESYS_TITLE_COUNT_ ];
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
enum OnAttackTypeENUM
{
	EM_OnAttackType_None	= -1 ,
	EM_OnAttackType_MainHand	,
	EM_OnAttackType_OffHand		,
	EM_OnAttackType_Skill		,
	EM_OnAttackType_Magic		,

};
//攻擊觸發資訊
struct OnAttackInfoStruct
{
	OnAttackTypeENUM	Type;
	int					OwnerID;
	int					TargetID;
	int					MagColID;
	int					MagBaseID;
	int					Damage;	
	ATTACK_DMGTYPE_ENUM	DmgType;
	OnAttackInfoStruct()
	{
		Init();
	};
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

#define		MAX_BG_REGISTER_COUNT_	10
enum	BGIndependenceGameProcENUM
{
	EM_BGIndependenceGameProc_None		,	//不帶回去
	EM_BGIndependenceGameProc_Rewrite	,	//複寫
	EM_BGIndependenceGameProc_Merge		,	//合併
};
//戰場回傳資訊
struct BattleGroundReturnValueStruct
{
	bool	IsIndependenceGame;
	BGIndependenceGameProcENUM	MoneyProcType;
	BGIndependenceGameProcENUM	ItemProcType;
	BGIndependenceGameProcENUM	KeyItemProcType;
	BGIndependenceGameProcENUM	TitleProcType;
	BGIndependenceGameProcENUM	CardProcType;

	float	Register[ MAX_BG_REGISTER_COUNT_ ];
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >	RetLua;

	
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

//自動回報有問題角色類型
enum AutoReportPossibleCheaterENUM
{
	EM_AutoReportPossibleCheater_ThroughtWall	,	//穿牆
	EM_AutoReportPossibleCheater_Teleport		,	//傳送
	EM_AutoReportPossibleCheater_Floating		,	//浮空
};

//自動回報有問題角色資訊
struct AutoReportBaseInfoStruct
{
	int		GUID;
	float	X,Y,Z;
};

#define _MAX_SLOT_MACHINE_HISTROY_COUNT_ 10
#define _MAX_SLOT_MACHINE_PRIZES_COUNT_ 10
//餃子老虎機資訊(歷史資訊)
struct SlotMachineHistoryBase
{
	int		Time;	//獎品時間
	int		ItemID;
	int		Count;
};


//餃子老虎機資訊
struct SlotMachineInfo
{
	StaticVector< SlotMachineHistoryBase , _MAX_SLOT_MACHINE_HISTROY_COUNT_ > History;
	short	RandSeed[_MAX_SLOT_MACHINE_PRIZES_COUNT_];	//亂數種子
	int		FreeCount;	//免費次數
	int		ItemID;
	int		ItemCount;
};

struct LuaHideInfoStruct
{
	//劇情隱藏資訊
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_>	PlotStr;	//觸發隱藏的劇情
	int											OwnerDBID;	//執行者
	int											OwnerOrgID;	//執行者物件ID
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};

//公會戰 公會資料
struct GuildWarBaseInfoStruct
{
	int		Guild;
	int		Score;
	StaticString<_MAX_NAMERECORD_SIZE_> GuildName;	
	bool	IsAssignment;
};
/*
//雕文系統角色資訊
struct RuneSystemBaseStruct
{
	int	RuneSetItemID;	//雕文共鳴組物品ID
	int	MagicCol[2];
	int	RuneItem[6];	
};

#define _MAX_RUNESYSTEM_GROUP_COUNT_ 10
struct RuneSystemGroupStruct
{
	int	Count;
	RuneSystemBaseStruct Set[_MAX_RUNESYSTEM_GROUP_COUNT_];
	};
*/
enum PlayerMoveErrTypeENUM
{
	EM_PlayerMoveErrType_VecterErr				,	//移動向量錯誤
	EM_PlayerMoveErrType_MoveDistErr			,	//移動離錯誤
	EM_PlayerMoveErrType_TotalMoveDistErr		,	//移動總距離錯誤
};

struct WeekZoneStruct
{
	int Day;
	int ZoneGroupID;
};

#define MAX_PHANTOM_COUNT	50
struct PhantomBase
{
	int	Lv;			//0 表示沒有資料
	int Rank;
	int	Reserve[4];	//保留資料
};

struct PhantomStruct
{
	PhantomBase	Info[ MAX_PHANTOM_COUNT ];	//儲存位置為 幻影的物件ID%1000
	int	EQ[2];		//幻影的物件ID
	int SkillID;	//可使用技能
	int SkillLv;	//可使用技能等級
};

/*
struct PhantomRankTable
{
	int Rank;
	int	MaxLevel;
	int	NeedFragment;
};
struct PhantomLvTable
{
	int	Lv;
	int Type;
	int Material[4];
};
*/
struct BuffScheduleStruct
{
	int		ZoneID;
	float	EndTime;
	int		BuffID;
	int		BuffLv;
};

#pragma managed


#endif
