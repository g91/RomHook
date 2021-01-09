#ifndef	__ROLEATTR_H_2003_09_01__
#define __ROLEATTR_H_2003_09_01__
#include "RoleBaseInc.h"


#define Def_Base_TB_Total_Unit_ 400

struct RoleValueData
{
	//----------------------------------------------------------------------
	//	全域資料
	//----------------------------------------------------------------------
	static bool	InitTable( char* Path );    //重檔案載入參數

    static void CalBaseTB( );                //計算基本的TB表
 
	//----------------------------------------------------------------------
//	RoleTableStruct			Table;			//目前此角色的 Table資料
	//----------------------------------------------------------------------
	RoleValueData*			Target;			//運算目標 
	//----------------------------------------------------------------------
	MagicEffectStruct		Effect;			//法術影響
	MagicSpellFlagStruct	AssistMagicSetting;	//輔助法術特殊類型	
	RoleActionStruct		Action;			//目前的行動狀態
    RoleActionStruct		LAction;		//目前的行動狀態
	PlayerStateStruct		AllZoneState;	//全區狀態
	//----------------------------------------------------------------------
	SkillValueStruct*		SkillValue;		//技能資料
	BaseAbilityStruct*		Ability;		//目前職業的能力
    SkillValueStruct	    MaxSkillValue;	//技能資料
	int						DisableMagicSet;//無效的法術
	//----------------------------------------------------------------------
    static FixFightArgumentStruct   FixArgTable[2];     //固定參數表
    static FightArgumentStruct      RaceArg[ _MAX_RACE_COUNT_ ];        //種族參數表
    static FightArgumentStruct      VocArg [ _MAX_VOCATION_COUNT_ ][2]; //職業參數表
    static FightArgumentStruct      SexArg [ _MAX_SEX_COUNT_ ];         //性別參數表

	static EqWearSkillStruct JobWearSkill[ _MAX_VOCATION_COUNT_ ];	//每個職頁所會的裝備能力
/*
#ifndef _CLIENT
    static float    BaseStrTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseStaTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseIntTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseMndTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseAgiTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseHPTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
    static float    BaseMPTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
#endif
	*/

    static int      SkillValueBase[ _MAX_LEVEL_ ][ _MAX_SKILLVALUE_BASETYPE ];				//熟練度代表的數值 S+[0] S[1] S-[2]依此類推
    static int      JobSkillValue[ _MAX_SKILLVALUE_TYPE ][ _MAX_VOCATION_COUNT_ ];

	static int		WeaponBaseDelayTime[ _MAX_SKILLVALUE_TYPE ];							//各種武器的基本延遲時間
	static float	WeaponBaseDmg[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本傷害比( 要乘上該等極GM的傷害 )
	static int		WeaponBaseRand[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本傷害 亂數
	static float	WeaponBaseMAtk[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本魔法攻擊比( 要乘上該等極GM的傷害 )
	static float	WeaponBaseCostRate[ _MAX_SKILLVALUE_TYPE ];

//	static vector<ResistArgumentStruct>		ResistArgList;									//抗性數值表
	
	static GameRoleMPSPUseTypeENUM	JobSpMpType[ _MAX_VOCATION_COUNT_ ];					//各職業使用MPSP的方式
    //============================================================================
    FightArgumentStruct     Arg;		//自己的參數
	FightArgumentStruct     Arg_Sub;    //副職的參數

	int						FixArgTableID;	//0 NPC 1 玩家
	bool					IsNPC;
	//基本數值
	Race_ENUM				Race;
	Sex_ENUM				Sex;
	Voc_ENUM    			Voc;
    Voc_ENUM    			Voc_Sub;
    int                     Level;
    int                     Level_Sub;          //副職等級()
    GameObjectWeaponENUM    MainWeaponType;     //主手是否可攻擊
    GameObjectWeaponENUM    SecWeaponType;      //副手是否可攻擊
	GameObjectWeaponENUM    BowWeaponType;      //副手是否可攻擊

	int						MainWeaponAttackSpeed;
	int						SecWeaponAttackSpeed;
	int						BoweAttackSpeed;
	int						ThrowAttackSpeed;

	int						MainAttackRange;	//武器攻擊範圍
	int						SecAttackRange;		//武器攻擊範圍
	float					LastMaxMoveSpeed;

	int						ExAddHP;			//特殊事件增加HP上限
	//----------------------------------------------------------------------
	//原始數值
    //----------------------------------------------------------------------
    struct 
    {
        //查表得到
        float   BaseStr;
        float   BaseSta;
        float   BaseInt;
        float   BaseMnd;
        float   BaseAgi;
        float   BaseHP;
        float   BaseMP;

        float					MoveSpeed_Per;      //npc基本的移動力
		MagicResistStruct		Resist;				//npc抗性
		MagicEffectStruct		Effect;				//天生法術效能的設定

		float BaseBlackSmithHQRate;					// "HQ品機率上升 打鐵(%)",
		float BaseCarpenterHQRate;					// "HQ品機率上升上升 木工(%)",
		float BaseMakeArmorHQRate;					// "HQ品機率上升上升 製甲(%)",
		float BaseTailorHQRate;						// "HQ品機率上升上升 裁縫(%)",
		float BaseCookHQRate;						// "HQ品機率上升上升 烹飪(%)",
		float BaseAlchemyHQRate;					// "HQ品機率上升上升 煉金(%)",
		float HQ_Carpenter;							// "HQ品機率上升上升 木工(%)",

		bool	IsNoMPSP;		//沒有MPSP
    }Bas;
    //============================================================================
	struct 
	{
		float   Main_DMG;           //主手攻擊力
		float   Main_DMG_Per;       //攻擊力(%)
		float	Main_CriticalHit;
		float	Main_ATKSpeed_Per;
		float	Main_HitRate;
		float   Main_MagicAtk[ EM_MagicResist_MAXCOUNT ];
		int		Main_OnAttackMagicRate;		//普攻法術發生機率
		int		Main_OnAttackMagicRank;		//普攻法術互蓋等級
		int		Main_OnAttackMagicID;		//普攻法術法術號碼


		float   Sec_DMG;			//副手攻擊力		
		float   Sec_DMG_Per;        //攻擊力(%)
		float	Sec_CriticalHit;
		float	Sec_ATKSpeed_Per;
		float	Sec_HitRate;
		float   Sec_MagicAtk[ EM_MagicResist_MAXCOUNT ];
		int		Sec_OnAttackMagicRate;		//普攻法術發生機率
		int		Sec_OnAttackMagicRank;		//普攻法術互蓋等級
		int		Sec_OnAttackMagicID;		//普攻法術法術號碼

		float	Bow_DMG;
		float	Bow_DMG_Per;
		float	Bow_CriticalHit;
		float	Bow_ATKSpeed_Per;
		float	Bow_HitRate;
		float	Bow_AttackRange;

		float	Throw_DMG;			//彈藥 或 投擲物的 DMG
		float	Throw_DMG_Per;
		float	Throw_CriticalHit;
		float	Throw_ATKSpeed_Per;
		float	Throw_HitRate;
		float	Throw_AttackRange;

		float	Def[ EM_Armor_MaxCount ];				//各類型所產生的防禦值

		float	Body[ EM_WearEqType_MaxCount ];
		float	BodyRate[ EM_WearEqType_MaxCount ];

	}BaseEQ;

	//動態Buff影響
	struct 
	{
		int		OnAttackMagicRate;		//普攻法術發生機率
		int		OnAttackMagicRank;		//普攻法術互蓋等級
		int		OnAttackMagicID;		//普攻法術法術號碼

		float	Body[ EM_WearEqType_MaxCount ];
		float	BodyRate[ EM_WearEqType_MaxCount ];
		
	}Mid;
	//----------------------------------------------------------------------
	//最後算出的結果
    //----------------------------------------------------------------------
    struct  
    {
        float	STR;			// 力量
        float	STA;			// 耐力
        float	MND;			// 智慧
        float   INT;            // 聰明
        float	AGI;			// 敏捷
        float   LUK;

        float	MaxHP;		    // 體力
        float	MaxMP;		    // 魔力
        float   MaxSP;			// 主職 SP
		float	MaxSP_Sub;		// 副職 SP

        float	ATK;			// 攻擊
        float	DEF;			// 防禦

        float	MDEF;		    // 防禦
        float	MATK;		    // 攻擊

        float	HitRate;		// 命中
        float	DodgeRate;	    // 閃避

		float	MagicHitRate;	// 魔法 命中
		float	MagicDodgeRate;	// 魔法 閃避

        float	CriticalHit;
		float	CriticalHitPower;		//Critical傷害倍率

		float	MagicCriticalHit;
		float	MagicCriticalHitPower;	//魔法 Critical傷害倍率

        float	ParryRate;
		float	ShieldBlockRate;		//盾檔率

		float	ResistParryRate;
		float	ResistBlockRate;
		float	ResistCriticalHit;
		float	ResistMagicCriticalHit;

        float	ReHP;
        float	ReMP;

		float	Main_CriticalHit;
        float 	Main_ATKSpeed;
        float   Main_DMG;           //主手攻擊力
		float	Main_HitRate;
		float   Main_MagicAtk[ EM_MagicResist_MAXCOUNT ];

		float	Sec_CriticalHit;
        float 	Sec_ATKSpeed;
        float   Sec_DMG;			//副手攻擊力
		float	Sec_HitRate;
		float   Sec_MagicAtk[ EM_MagicResist_MAXCOUNT ];

		float	Bow_CriticalHit;
		float	Bow_ATKSpeed;
		float	Bow_DMG;
		float	Bow_HitRate;
		float	Bow_AttackRange;

		float	Throw_DMG;
		float	Throw_CriticalHit;
		float	Throw_ATKSpeed;
		float	Throw_HitRate;
		float	Throw_AttackRange;

		float   MoveSpeed;
		float   DMG;
		float	MDMG;
		
		float	MainJobSPRate;
		float	SubJobSPRate;

        float   MPow;           	//魔法增強率
        float   MAbr;           	//魔法防禦吸收率
        float   Abr;            	//防禦吸收率
        float   AB;             	//防禦吸收點數

		EqWearSkillStruct	WearSkill;//裝置能力

        MagicResistStruct   Resist;
		MagicResistStruct   ResistPer;

		SkillValueStruct	SkillValue;	

    }Fin;
    
	//----------------------------------------------------------------------	
	// 一般函式
	//----------------------------------------------------------------------	
	//重設此角色的 Table 資料
	void	ReSetTable();
	//初始化所有的裝備或法術產生的暫時效果
	void	Init_MidValue();
	void	Init_BaseEQValue();
    //全部重新計算
    void	Calculate();
    //攻擊力傷害計算
    float	MainAtkDamage( ATTACK_DMGTYPE_ENUM DmgType );
    float	SecAtkDamage( ATTACK_DMGTYPE_ENUM DmgType );
	
	//先計算裝備能力
	void	CalWearSkill();

	//計算物理傷害　被防禦修正
	float	CalWeaponDMG( float Power );

	//計算法術傷害　被魔防修正
	float	CalMagicDMG( float Power );

	//某系魔法威力
	float	MagicPow( MagicResistENUM Type );
	//魔法施法速度
	float	MagicSpellSpeed( );

	//取得法術抗性值對應的 處理的類別
//	static	ResistArgType_ENUM	GetResistType( int ResistValue );

	//增加能力
	void	AddAbility( GameObjectWearEqStruct* Ability , GameObjectArmorENUM ArmorType = EM_Armor_None , int Pos = -1 , float Power = 1 );
	void	AddAbility_Buff( GameObjectWearEqStruct* Ability , float Power );
	//固定參數表
	FixFightArgumentStruct&   FixArg();  


	float	CalShieldBlockRate	( int TargetLv , float TargetResistRate );
	float	CalParryRate		( int TargetLv , float TargetResistRate );
	float	CalCritialRate		( float CritialRate , int TargetLv , float TargetResistRate );
	float	CalMagCritialRate	( float MagCritialRate , int TargetLv , float TargetResistRate );

	float	ManaDecrease();	//mp消耗減少(%)
	float	SPWarriorDecrease();	
	float	SPRogueDecrease();	
	float	SPRangerDecrease();	

	float	BaseEQSTR();
	float	BaseEQSTA();
	float	BaseEQINT();
	float	BaseEQMND();
	float	BaseEQAGI();
	float	BaseEQLUK();

	inline float	_CalRate( float OrgSpeed , float AddSpeed );
protected:
	//----------------------------------------------------------------------	
	//各項數值簡易算式
	//----------------------------------------------------------------------	
	float	_STR();
	float	_STA();
	float	_INT();
	float	_MND();
	float	_AGI();
	float	_LUK();

    //--------------------------------------    
    float	_MaxHP();	    // 體力
    float	_MaxMP();	    // 魔力
    float   _MaxSP();
	float   _MaxSP_Sub();

    float	_ATK();			// 攻擊
    float	_DEF();			// 防禦

    float	_MDEF();	    // 防禦
    float	_MATK();	    // 攻擊

	float	_MagHitRate();
	float	_MagDodgeRate();

    float	_HitRate();		// 命中
	float	_Main_HitRate();
	float	_Sec_HitRate();

    float	_DodgeRate();   // 閃避

    float	_CriticalHit();
	float	_CriticalHitPower();

	float	_MagicCriticalHit();
	float	_MagicCriticalHitPower();


    float	_Main_CriticalHit();
    float	_Sec_CriticalHit();
    float	_ParryRate();
	float	_ShieldBlockRate();

	float	_ResistParryRate();
	float	_ResistBlockRate();
	float	_ResistCriticalHit();
	float	_ResistMagicCriticalHit();

    float	_ReHP();
    float	_ReMP();
    
    float   _Main_ATKSpeed();
    float 	_Sec_ATKSpeed();
    float   _MoveSpeed();
	
    float   _Bow_ATKSpeed();
	float   _Bow_DMG();
	float	_Bow_Critical();
	float	_Bow_HiteRate();
	float	_Bow_AttackRange();

	float	_Throw_DMG();
	float	_Throw_CriticalHit();
	float	_Throw_ATKSpeed();
	float	_Throw_HitRate();
	float	_Throw_AttackRange();
    //--------------------------------------    
    float   _DMG();
    float   _MainDMG();
    float   _SecDMG();
	float	_MDMG();
//	float	_ThrowDMG();

    float   _MPow();           //魔法增強率
    float   _MAbr();           //魔法防禦吸收率
    float   _Abr();            //防禦吸收率
    float   _AB();             //防禦吸收點數

	float	_MainJobSPRate();
	float	_SubJobSPRate();

	EqWearSkillStruct _EqWearSkill();

	void	_SkillValueCal();

	void	_CalElementPower();

	//--------------------------------------    
	float		_CalBaseStr( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseSta( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseInt( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseMnd( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseAgi( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseHP ( int Race , int Voc , int Sex , int Lv );
	float		_CalBaseMP ( int Race , int Voc , int Sex , int Lv );
	float		ToRoundOff( float );
	//--------------------------------------    
};


#endif