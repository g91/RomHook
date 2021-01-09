#ifndef	__ROLEATTR_H_2003_09_01__
#define __ROLEATTR_H_2003_09_01__
#include "RoleBaseInc.h"


#define Def_Base_TB_Total_Unit_ 400

struct RoleValueData
{
	//----------------------------------------------------------------------
	//	������
	//----------------------------------------------------------------------
	static bool	InitTable( char* Path );    //���ɮ׸��J�Ѽ�

    static void CalBaseTB( );                //�p��򥻪�TB��
 
	//----------------------------------------------------------------------
//	RoleTableStruct			Table;			//�ثe�����⪺ Table���
	//----------------------------------------------------------------------
	RoleValueData*			Target;			//�B��ؼ� 
	//----------------------------------------------------------------------
	MagicEffectStruct		Effect;			//�k�N�v�T
	MagicSpellFlagStruct	AssistMagicSetting;	//���U�k�N�S������	
	RoleActionStruct		Action;			//�ثe����ʪ��A
    RoleActionStruct		LAction;		//�ثe����ʪ��A
	PlayerStateStruct		AllZoneState;	//���Ϫ��A
	//----------------------------------------------------------------------
	SkillValueStruct*		SkillValue;		//�ޯ���
	BaseAbilityStruct*		Ability;		//�ثe¾�~����O
    SkillValueStruct	    MaxSkillValue;	//�ޯ���
	int						DisableMagicSet;//�L�Ī��k�N
	//----------------------------------------------------------------------
    static FixFightArgumentStruct   FixArgTable[2];     //�T�w�Ѽƪ�
    static FightArgumentStruct      RaceArg[ _MAX_RACE_COUNT_ ];        //�رڰѼƪ�
    static FightArgumentStruct      VocArg [ _MAX_VOCATION_COUNT_ ][2]; //¾�~�Ѽƪ�
    static FightArgumentStruct      SexArg [ _MAX_SEX_COUNT_ ];         //�ʧO�Ѽƪ�

	static EqWearSkillStruct JobWearSkill[ _MAX_VOCATION_COUNT_ ];	//�C��¾���ҷ|���˳Ư�O
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

    static int      SkillValueBase[ _MAX_LEVEL_ ][ _MAX_SKILLVALUE_BASETYPE ];				//���m�ץN���ƭ� S+[0] S[1] S-[2]�̦�����
    static int      JobSkillValue[ _MAX_SKILLVALUE_TYPE ][ _MAX_VOCATION_COUNT_ ];

	static int		WeaponBaseDelayTime[ _MAX_SKILLVALUE_TYPE ];							//�U�تZ�����򥻩���ɶ�
	static float	WeaponBaseDmg[ _MAX_SKILLVALUE_TYPE ];									//�U�تZ�����򥻶ˮ`��( �n���W�ӵ���GM���ˮ` )
	static int		WeaponBaseRand[ _MAX_SKILLVALUE_TYPE ];									//�U�تZ�����򥻶ˮ` �ü�
	static float	WeaponBaseMAtk[ _MAX_SKILLVALUE_TYPE ];									//�U�تZ�������]�k������( �n���W�ӵ���GM���ˮ` )
	static float	WeaponBaseCostRate[ _MAX_SKILLVALUE_TYPE ];

//	static vector<ResistArgumentStruct>		ResistArgList;									//�ܩʼƭȪ�
	
	static GameRoleMPSPUseTypeENUM	JobSpMpType[ _MAX_VOCATION_COUNT_ ];					//�U¾�~�ϥ�MPSP���覡
    //============================================================================
    FightArgumentStruct     Arg;		//�ۤv���Ѽ�
	FightArgumentStruct     Arg_Sub;    //��¾���Ѽ�

	int						FixArgTableID;	//0 NPC 1 ���a
	bool					IsNPC;
	//�򥻼ƭ�
	Race_ENUM				Race;
	Sex_ENUM				Sex;
	Voc_ENUM    			Voc;
    Voc_ENUM    			Voc_Sub;
    int                     Level;
    int                     Level_Sub;          //��¾����()
    GameObjectWeaponENUM    MainWeaponType;     //�D��O�_�i����
    GameObjectWeaponENUM    SecWeaponType;      //�Ƥ�O�_�i����
	GameObjectWeaponENUM    BowWeaponType;      //�Ƥ�O�_�i����

	int						MainWeaponAttackSpeed;
	int						SecWeaponAttackSpeed;
	int						BoweAttackSpeed;
	int						ThrowAttackSpeed;

	int						MainAttackRange;	//�Z�������d��
	int						SecAttackRange;		//�Z�������d��
	float					LastMaxMoveSpeed;

	int						ExAddHP;			//�S��ƥ�W�[HP�W��
	//----------------------------------------------------------------------
	//��l�ƭ�
    //----------------------------------------------------------------------
    struct 
    {
        //�d��o��
        float   BaseStr;
        float   BaseSta;
        float   BaseInt;
        float   BaseMnd;
        float   BaseAgi;
        float   BaseHP;
        float   BaseMP;

        float					MoveSpeed_Per;      //npc�򥻪����ʤO
		MagicResistStruct		Resist;				//npc�ܩ�
		MagicEffectStruct		Effect;				//�ѥͪk�N�į઺�]�w

		float BaseBlackSmithHQRate;					// "HQ�~���v�W�� ���K(%)",
		float BaseCarpenterHQRate;					// "HQ�~���v�W�ɤW�� ��u(%)",
		float BaseMakeArmorHQRate;					// "HQ�~���v�W�ɤW�� �s��(%)",
		float BaseTailorHQRate;						// "HQ�~���v�W�ɤW�� ���_(%)",
		float BaseCookHQRate;						// "HQ�~���v�W�ɤW�� �i��(%)",
		float BaseAlchemyHQRate;					// "HQ�~���v�W�ɤW�� �Ҫ�(%)",
		float HQ_Carpenter;							// "HQ�~���v�W�ɤW�� ��u(%)",

		bool	IsNoMPSP;		//�S��MPSP
    }Bas;
    //============================================================================
	struct 
	{
		float   Main_DMG;           //�D������O
		float   Main_DMG_Per;       //�����O(%)
		float	Main_CriticalHit;
		float	Main_ATKSpeed_Per;
		float	Main_HitRate;
		float   Main_MagicAtk[ EM_MagicResist_MAXCOUNT ];
		int		Main_OnAttackMagicRate;		//����k�N�o�;��v
		int		Main_OnAttackMagicRank;		//����k�N���\����
		int		Main_OnAttackMagicID;		//����k�N�k�N���X


		float   Sec_DMG;			//�Ƥ�����O		
		float   Sec_DMG_Per;        //�����O(%)
		float	Sec_CriticalHit;
		float	Sec_ATKSpeed_Per;
		float	Sec_HitRate;
		float   Sec_MagicAtk[ EM_MagicResist_MAXCOUNT ];
		int		Sec_OnAttackMagicRate;		//����k�N�o�;��v
		int		Sec_OnAttackMagicRank;		//����k�N���\����
		int		Sec_OnAttackMagicID;		//����k�N�k�N���X

		float	Bow_DMG;
		float	Bow_DMG_Per;
		float	Bow_CriticalHit;
		float	Bow_ATKSpeed_Per;
		float	Bow_HitRate;
		float	Bow_AttackRange;

		float	Throw_DMG;			//�u�� �� ���Y���� DMG
		float	Throw_DMG_Per;
		float	Throw_CriticalHit;
		float	Throw_ATKSpeed_Per;
		float	Throw_HitRate;
		float	Throw_AttackRange;

		float	Def[ EM_Armor_MaxCount ];				//�U�����Ҳ��ͪ����m��

		float	Body[ EM_WearEqType_MaxCount ];
		float	BodyRate[ EM_WearEqType_MaxCount ];

	}BaseEQ;

	//�ʺABuff�v�T
	struct 
	{
		int		OnAttackMagicRate;		//����k�N�o�;��v
		int		OnAttackMagicRank;		//����k�N���\����
		int		OnAttackMagicID;		//����k�N�k�N���X

		float	Body[ EM_WearEqType_MaxCount ];
		float	BodyRate[ EM_WearEqType_MaxCount ];
		
	}Mid;
	//----------------------------------------------------------------------
	//�̫��X�����G
    //----------------------------------------------------------------------
    struct  
    {
        float	STR;			// �O�q
        float	STA;			// �@�O
        float	MND;			// ���z
        float   INT;            // �o��
        float	AGI;			// �ӱ�
        float   LUK;

        float	MaxHP;		    // ��O
        float	MaxMP;		    // �]�O
        float   MaxSP;			// �D¾ SP
		float	MaxSP_Sub;		// ��¾ SP

        float	ATK;			// ����
        float	DEF;			// ���m

        float	MDEF;		    // ���m
        float	MATK;		    // ����

        float	HitRate;		// �R��
        float	DodgeRate;	    // �{��

		float	MagicHitRate;	// �]�k �R��
		float	MagicDodgeRate;	// �]�k �{��

        float	CriticalHit;
		float	CriticalHitPower;		//Critical�ˮ`���v

		float	MagicCriticalHit;
		float	MagicCriticalHitPower;	//�]�k Critical�ˮ`���v

        float	ParryRate;
		float	ShieldBlockRate;		//���ɲv

		float	ResistParryRate;
		float	ResistBlockRate;
		float	ResistCriticalHit;
		float	ResistMagicCriticalHit;

        float	ReHP;
        float	ReMP;

		float	Main_CriticalHit;
        float 	Main_ATKSpeed;
        float   Main_DMG;           //�D������O
		float	Main_HitRate;
		float   Main_MagicAtk[ EM_MagicResist_MAXCOUNT ];

		float	Sec_CriticalHit;
        float 	Sec_ATKSpeed;
        float   Sec_DMG;			//�Ƥ�����O
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

        float   MPow;           	//�]�k�W�j�v
        float   MAbr;           	//�]�k���m�l���v
        float   Abr;            	//���m�l���v
        float   AB;             	//���m�l���I��

		EqWearSkillStruct	WearSkill;//�˸m��O

        MagicResistStruct   Resist;
		MagicResistStruct   ResistPer;

		SkillValueStruct	SkillValue;	

    }Fin;
    
	//----------------------------------------------------------------------	
	// �@��禡
	//----------------------------------------------------------------------	
	//���]�����⪺ Table ���
	void	ReSetTable();
	//��l�ƩҦ����˳ƩΪk�N���ͪ��ȮɮĪG
	void	Init_MidValue();
	void	Init_BaseEQValue();
    //�������s�p��
    void	Calculate();
    //�����O�ˮ`�p��
    float	MainAtkDamage( ATTACK_DMGTYPE_ENUM DmgType );
    float	SecAtkDamage( ATTACK_DMGTYPE_ENUM DmgType );
	
	//���p��˳Ư�O
	void	CalWearSkill();

	//�p�⪫�z�ˮ`�@�Q���m�ץ�
	float	CalWeaponDMG( float Power );

	//�p��k�N�ˮ`�@�Q�]���ץ�
	float	CalMagicDMG( float Power );

	//�Y�t�]�k�¤O
	float	MagicPow( MagicResistENUM Type );
	//�]�k�I�k�t��
	float	MagicSpellSpeed( );

	//���o�k�N�ܩʭȹ����� �B�z�����O
//	static	ResistArgType_ENUM	GetResistType( int ResistValue );

	//�W�[��O
	void	AddAbility( GameObjectWearEqStruct* Ability , GameObjectArmorENUM ArmorType = EM_Armor_None , int Pos = -1 , float Power = 1 );
	void	AddAbility_Buff( GameObjectWearEqStruct* Ability , float Power );
	//�T�w�Ѽƪ�
	FixFightArgumentStruct&   FixArg();  


	float	CalShieldBlockRate	( int TargetLv , float TargetResistRate );
	float	CalParryRate		( int TargetLv , float TargetResistRate );
	float	CalCritialRate		( float CritialRate , int TargetLv , float TargetResistRate );
	float	CalMagCritialRate	( float MagCritialRate , int TargetLv , float TargetResistRate );

	float	ManaDecrease();	//mp���Ӵ��(%)
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
	//�U���ƭ�²���⦡
	//----------------------------------------------------------------------	
	float	_STR();
	float	_STA();
	float	_INT();
	float	_MND();
	float	_AGI();
	float	_LUK();

    //--------------------------------------    
    float	_MaxHP();	    // ��O
    float	_MaxMP();	    // �]�O
    float   _MaxSP();
	float   _MaxSP_Sub();

    float	_ATK();			// ����
    float	_DEF();			// ���m

    float	_MDEF();	    // ���m
    float	_MATK();	    // ����

	float	_MagHitRate();
	float	_MagDodgeRate();

    float	_HitRate();		// �R��
	float	_Main_HitRate();
	float	_Sec_HitRate();

    float	_DodgeRate();   // �{��

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

    float   _MPow();           //�]�k�W�j�v
    float   _MAbr();           //�]�k���m�l���v
    float   _Abr();            //���m�l���v
    float   _AB();             //���m�l���I��

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