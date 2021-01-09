
#pragma		warning (disable:4244)
#pragma		warning (disable:4786)

#include "RoleAttr.h"




FixFightArgumentStruct   RoleValueData::FixArgTable[2];                         //固定參數表
FightArgumentStruct      RoleValueData::RaceArg[_MAX_RACE_COUNT_];      //種族參數表
FightArgumentStruct      RoleValueData::VocArg[_MAX_VOCATION_COUNT_][2];   //職業參數表
FightArgumentStruct      RoleValueData::SexArg[_MAX_SEX_COUNT_];        //性別參數表

EqWearSkillStruct RoleValueData::JobWearSkill[ _MAX_VOCATION_COUNT_ ];		//每個職頁所會的裝備能力
/*
#ifndef _CLIENT
float    RoleValueData::BaseStrTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseStaTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseIntTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseMndTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseAgiTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseHPTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
float    RoleValueData::BaseMPTB[_MAX_RACE_COUNT_][_MAX_VOCATION_COUNT_][_MAX_SEX_COUNT_][ _MAX_LEVEL_+1 ][2];
#endif
*/

int      RoleValueData::SkillValueBase[ _MAX_LEVEL_][ _MAX_SKILLVALUE_BASETYPE];
int      RoleValueData::JobSkillValue[ _MAX_SKILLVALUE_TYPE ][ _MAX_VOCATION_COUNT_ ];

int		 RoleValueData::WeaponBaseDelayTime[ _MAX_SKILLVALUE_TYPE ];							//各種武器的基本延遲時間
float	 RoleValueData::WeaponBaseDmg[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本傷害比( 要乘上該等極GM的傷害 )
int		 RoleValueData::WeaponBaseRand[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本傷害 亂數
float	 RoleValueData::WeaponBaseMAtk[ _MAX_SKILLVALUE_TYPE ];									//各種武器的基本傷害比( 要乘上該等極GM的傷害 )
float	 RoleValueData::WeaponBaseCostRate[ _MAX_SKILLVALUE_TYPE ];

//vector<ResistArgumentStruct>		RoleValueData::ResistArgList;									//抗性數值表

GameRoleMPSPUseTypeENUM	RoleValueData::JobSpMpType[ _MAX_VOCATION_COUNT_ ] = 
{
	EM_GameRoleMPSPUseType_MP ,//GM
	EM_GameRoleMPSPUseType_SP ,//戰士
	EM_GameRoleMPSPUseType_SP ,//遊俠
	EM_GameRoleMPSPUseType_SP ,//盜賊
	EM_GameRoleMPSPUseType_MP ,//法師
	EM_GameRoleMPSPUseType_MP ,//僧侶
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
	EM_GameRoleMPSPUseType_MP ,
};					//各職業使用MPSP的方式
//----------------------------------------------------------------------	
// 一般函式
//----------------------------------------------------------------------	
//重設此角色的 Table 資料
void	RoleValueData::ReSetTable( )
{
	int i; 
	for( i = 0 ; i < 100 ; i ++ )
	{
		Arg.Arg[i]		= RaceArg[ Race ].Arg[i] + VocArg[ Voc ][FixArgTableID].Arg[i] + SexArg[ Sex].Arg[i];

		if( Voc_Sub != EM_Vocation_None )
			Arg_Sub.Arg[i]	= RaceArg[ Race ].Arg[i] + VocArg[ Voc_Sub ][FixArgTableID].Arg[i] + SexArg[ Sex].Arg[i];
		else
			Arg_Sub.Arg[i]	= 0;
	}

	Arg.DmgRate = RaceArg[ Race ].DmgRate * VocArg[ Voc][FixArgTableID].DmgRate * SexArg[ Sex].DmgRate;
/*
#ifndef _CLIENT
	if( Voc_Sub == EM_Vocation_None )
	{
		Bas.BaseStr = BaseStrTB[Race][Voc][Sex][Level][FixArgTableID];
		Bas.BaseSta = BaseStaTB[Race][Voc][Sex][Level][FixArgTableID];
		Bas.BaseInt = BaseIntTB[Race][Voc][Sex][Level][FixArgTableID];
		Bas.BaseMnd = BaseMndTB[Race][Voc][Sex][Level][FixArgTableID];
		Bas.BaseAgi = BaseAgiTB[Race][Voc][Sex][Level][FixArgTableID];
		Bas.BaseHP  = BaseHPTB[Race][Voc][Sex] [Level][FixArgTableID];
		Bas.BaseMP  = BaseMPTB[Race][Voc][Sex] [Level][FixArgTableID];
	}
	else
	{
		Bas.BaseStr = BaseStrTB[Race][Voc][Sex][Level][FixArgTableID] + BaseStrTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
		Bas.BaseSta = BaseStaTB[Race][Voc][Sex][Level][FixArgTableID] + BaseStaTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10;
		Bas.BaseInt = BaseIntTB[Race][Voc][Sex][Level][FixArgTableID] + BaseIntTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
		Bas.BaseMnd = BaseMndTB[Race][Voc][Sex][Level][FixArgTableID] + BaseMndTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
		Bas.BaseAgi = BaseAgiTB[Race][Voc][Sex][Level][FixArgTableID] + BaseAgiTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
		Bas.BaseHP  = BaseHPTB[Race][Voc][Sex] [Level][FixArgTableID] + BaseHPTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
		Bas.BaseMP  = BaseMPTB[Race][Voc][Sex] [Level][FixArgTableID] + BaseMPTB[Race][Voc_Sub][Sex][ Level_Sub ][FixArgTableID] / 10 ;
	}
#else
*/
	if( Voc_Sub == EM_Vocation_None )
	{
		Bas.BaseStr = _CalBaseStr( Race , Voc , Sex , Level );
		Bas.BaseSta = _CalBaseSta( Race , Voc , Sex , Level );
		Bas.BaseInt = _CalBaseInt( Race , Voc , Sex , Level );
		Bas.BaseMnd = _CalBaseMnd( Race , Voc , Sex , Level );
		Bas.BaseAgi = _CalBaseAgi( Race , Voc , Sex , Level );
		Bas.BaseHP  = _CalBaseHP ( Race , Voc , Sex , Level );
		Bas.BaseMP  = _CalBaseMP ( Race , Voc , Sex , Level );
	}
	else
	{
		Bas.BaseStr = _CalBaseStr( Race , Voc , Sex , Level ) + _CalBaseStr( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseSta = _CalBaseSta( Race , Voc , Sex , Level ) + _CalBaseSta( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseInt = _CalBaseInt( Race , Voc , Sex , Level ) + _CalBaseInt( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseMnd = _CalBaseMnd( Race , Voc , Sex , Level ) + _CalBaseMnd( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseAgi = _CalBaseAgi( Race , Voc , Sex , Level ) + _CalBaseAgi( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseHP  = _CalBaseHP ( Race , Voc , Sex , Level ) + _CalBaseHP ( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
		Bas.BaseMP  = _CalBaseMP ( Race , Voc , Sex , Level ) + _CalBaseMP ( Race , Voc_Sub , Sex , Level_Sub ) / 10 ;
	}
//#endif

	for( i = 0 ; i < _MAX_SKILL_COUNT_ ; i++ )
	{

		int SkillType = JobSkillValue[i][Voc];

		MaxSkillValue.Skill[i] = SkillValueBase[ Level-1 ][ SkillType ];
	}

	// 修正生活技能升級上限
	for( i = EM_SkillValueType_BlackSmith; i <= EM_SkillValueType_CatchPet; i++ )
	{
		MaxSkillValue.Skill[i] = 100;
	}


}
//先計算裝備能力
void	RoleValueData::CalWearSkill()
{
	Fin.WearSkill	= _EqWearSkill();
}

//初始化所有的裝備或法術產生的暫時效果
void	RoleValueData::Init_MidValue( )
{
	Mid.OnAttackMagicRank = 0;
	Mid.OnAttackMagicRate = 0;
	Mid.OnAttackMagicID   = 0;

//	BaseEQ.Main_OnAttackMagicRank = 0;
//	BaseEQ.Main_OnAttackMagicRate = 0;
//	BaseEQ.Main_OnAttackMagicID   = 0;

	DisableMagicSet = 0;
	AssistMagicSetting._Type = 0;

	Effect._Value[0] = 0;
	Effect._Value[1] = 0;
	memcpy( &Mid.Body		, BaseEQ.Body		, sizeof(Mid.Body) );
	memcpy( &Mid.BodyRate	, BaseEQ.BodyRate	, sizeof(Mid.BodyRate) );
	/*
	memset( &Mid , 0 , sizeof( Mid ) );

	for( int i = 0 ; i < EM_WearEqType_MaxCount ; i++ )
	{
		Mid.BodyRate[ i ]	= 1;
	}
	*/
}

void	RoleValueData::Init_BaseEQValue()
{
	memset( &BaseEQ , 0 , sizeof( BaseEQ ) );
	MainWeaponType = EM_Weapon_Unarmed;
	SecWeaponType = EM_Weapon_None;
	BowWeaponType = EM_Weapon_None;
	MainWeaponAttackSpeed = 30;
	SecWeaponAttackSpeed = 30;
	BoweAttackSpeed = _BASE_ATTACK_SPEED_;
	ThrowAttackSpeed = _BASE_ATTACK_SPEED_;
	Effect._Value[0] = 0;
	Effect._Value[1] = 0;
	DisableMagicSet = 0;
	AssistMagicSetting._Type = 0;
	MainAttackRange = 20;
	SecAttackRange  = 20;

	//速度型數值初始化
	BaseEQ.Main_ATKSpeed_Per	= 1;
	BaseEQ.Sec_ATKSpeed_Per		= 1;
	BaseEQ.Bow_ATKSpeed_Per		= 1;
	BaseEQ.Throw_ATKSpeed_Per	= 1;

	BaseEQ.Main_DMG_Per		= 1;       //攻擊力(%)
	BaseEQ.Sec_DMG_Per		= 1;        //攻擊力(%)
	BaseEQ.Bow_DMG_Per		= 1;
	BaseEQ.Throw_DMG_Per	= 1;


	for( int i = 0 ; i < EM_WearEqType_MaxCount ; i++ )
	{
		BaseEQ.BodyRate[ i ]		= 1;		
	}
}

//全部重新計算
void    RoleValueData::Calculate( )
{
	//清除法術效果
	//Effect._Value	= 0;

	Fin.STR         = _STR();
	Fin.STA         = _STA();
	Fin.INT         = _INT();
	Fin.MND         = _MND();
	Fin.AGI         = _AGI();
	Fin.LUK         = _LUK();

	Fin.MaxHP       = _MaxHP();	        // 體力

	if( Bas.IsNoMPSP == false )
	{
		if(		JobSpMpType[ Voc ] ==  EM_GameRoleMPSPUseType_MP 
			||	(Voc_Sub != EM_Vocation_None && JobSpMpType[ Voc_Sub ] ==  EM_GameRoleMPSPUseType_MP  ) )
		{
			Fin.MaxMP   = _MaxMP();	        // 魔力
		}
		else
		{
			Fin.MaxMP   = 0;
		}

		Fin.MaxSP       = _MaxSP();	        // 
		Fin.MaxSP_Sub   = _MaxSP_Sub();	    // 
	}
	else
	{
		Fin.MaxMP		= 0;
		Fin.MaxSP       = 0;
		Fin.MaxSP_Sub   = 0;
	}


    Fin.ATK         = _ATK();			// 攻擊
    Fin.DEF         = _DEF();			// 防禦

    Fin.MDEF        = _MDEF();	        // 防禦
    Fin.MATK        = _MATK();	        // 攻擊

    Fin.HitRate     = _HitRate();		// 命中
    Fin.DodgeRate   = _DodgeRate();     // 閃避

	Fin.MagicHitRate     = _MagHitRate();		// 命中
	Fin.MagicDodgeRate   = _MagDodgeRate();     // 閃避


    Fin.CriticalHit = _CriticalHit();
	Fin.CriticalHitPower = _CriticalHitPower();

	Fin.MagicCriticalHit = _MagicCriticalHit();
	Fin.MagicCriticalHitPower = _MagicCriticalHitPower();

    Fin.Main_CriticalHit	= _Main_CriticalHit();
    Fin.Sec_CriticalHit		= _Sec_CriticalHit();
    Fin.ParryRate			= _ParryRate();
	Fin.ShieldBlockRate		= _ShieldBlockRate();
	Fin.ResistParryRate			= _ResistParryRate();
	Fin.ResistBlockRate			= _ResistBlockRate();
	Fin.ResistCriticalHit		= _ResistCriticalHit();
	Fin.ResistMagicCriticalHit	= _ResistMagicCriticalHit();

    Fin.ReHP        = _ReHP();
    Fin.ReMP        = _ReMP();


    Fin.Main_ATKSpeed = _Main_ATKSpeed();
    Fin.Sec_ATKSpeed  = _Sec_ATKSpeed();

	Fin.MoveSpeed   = _MoveSpeed();

    Fin.DMG         = _DMG();
	Fin.MDMG		= _MDMG();

    Fin.MPow         = _MPow();           //魔法增強率
    Fin.MAbr         = _MAbr();           //魔法防禦吸收率
    Fin.Abr          = _Abr();            //防禦吸收率
    Fin.AB           = _AB();             //防禦吸收點數
//	Fin.ManaDecrease = _ManaDecrease();

    Fin.Main_DMG    = _MainDMG();
    Fin.Sec_DMG		= _SecDMG();
	Fin.Main_HitRate= _Main_HitRate();		// 命中
	Fin.Sec_HitRate = _Sec_HitRate();		// 命中
	Fin.WearSkill	= _EqWearSkill();

	Fin.MainJobSPRate	= _MainJobSPRate();
	Fin.SubJobSPRate	= _SubJobSPRate();


	Fin.Bow_ATKSpeed	= _Bow_ATKSpeed();
	Fin.Bow_DMG			= _Bow_DMG();
	Fin.Bow_CriticalHit = _Bow_Critical();
	Fin.Bow_HitRate		= _Bow_HiteRate();

	Fin.Bow_AttackRange	= _Bow_AttackRange();

	Fin.Throw_DMG			= _Throw_DMG();
	Fin.Throw_CriticalHit	= _Throw_CriticalHit();
	Fin.Throw_ATKSpeed		= _Throw_ATKSpeed();
	Fin.Throw_HitRate		= _Throw_HitRate();
	Fin.Throw_AttackRange	= _Throw_AttackRange();

    for( int i = 0 ; i < EM_MagicResist_MAXCOUNT ; i++ )
    {
		Fin.Resist._ArrList[i] =	Mid.Body[ EM_WearEqType_AllResist ] 
		+	Mid.Body[ EM_WearEqType_Resist_Earth + i ] 
		+	Bas.Resist._ArrList[i];
    }

	for( int i = 0 ; i < EM_MagicResist_MAXCOUNT ; i++ )
	{
		Fin.ResistPer._ArrList[i] =	Mid.BodyRate[ EM_WearEqType_AllResist_Per ] * Mid.BodyRate[ EM_WearEqType_Resist_Earth_Per + i ];
	}

	//計算SkillValue
	_SkillValueCal();

	_CalElementPower();

	Effect._Value[0] &= (Bas.Effect._Value[0]);
	//Bas.Effect._Value[1] 已經改說-1才對的說....先強制改
	if( Bas.Effect._Value[1] == 0) Bas.Effect._Value[1] = -1;
	Effect._Value[1] &= (Bas.Effect._Value[1]);
}

//////////////////////////////////////////////////////////////////////////
float	RoleValueData::BaseEQSTR()
{
	float Value = ( Ability->STR + Bas.BaseStr + BaseEQ.Body[ EM_WearEqType_STR ] + BaseEQ.Body[ EM_WearEqType_AllState ] ) * (  BaseEQ.BodyRate[ EM_WearEqType_STR_Rate ] * BaseEQ.BodyRate[ EM_WearEqType_AllState_Rate ] );
	return __max( Value , 0 );
}
float	RoleValueData::BaseEQSTA()
{
	float Value = ( Ability->STA + Bas.BaseSta + BaseEQ.Body[ EM_WearEqType_STA ] + BaseEQ.Body[ EM_WearEqType_AllState ] ) * ( BaseEQ.BodyRate[ EM_WearEqType_STA_Rate ] * BaseEQ.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::BaseEQINT()
{
	FLOAT Value = ( Ability->INT + Bas.BaseInt + BaseEQ.Body[ EM_WearEqType_INT ] + BaseEQ.Body[ EM_WearEqType_AllState ] ) * ( BaseEQ.BodyRate[ EM_WearEqType_INT_Rate ] * BaseEQ.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::BaseEQMND()
{
	float Value = ( Ability->MND + Bas.BaseMnd + BaseEQ.Body[ EM_WearEqType_MND ] + BaseEQ.Body[ EM_WearEqType_AllState ] ) * ( BaseEQ.BodyRate[ EM_WearEqType_MND_Rate ] * BaseEQ.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::BaseEQAGI()
{
	float Value = ( Ability->AGI + Bas.BaseAgi + BaseEQ.Body[ EM_WearEqType_AGI ] + BaseEQ.Body[ EM_WearEqType_AllState ] ) * ( BaseEQ.BodyRate[ EM_WearEqType_AGI_Rate ] * BaseEQ.BodyRate[ EM_WearEqType_AllState_Rate ] );
	return __max( Value , 0 );
}
//----------------------------------------------------------------------	
//各項數值簡易算式
//----------------------------------------------------------------------	
float	RoleValueData::_STR()
{
	float Value = ( Ability->STR + Bas.BaseStr + Mid.Body[ EM_WearEqType_STR ] + Mid.Body[ EM_WearEqType_AllState ] ) * (  Mid.BodyRate[ EM_WearEqType_STR_Rate ] * Mid.BodyRate[ EM_WearEqType_AllState_Rate ] );
	return __max( Value , 0 );
}
float	RoleValueData::_STA()
{
	float Value = ( Ability->STA + Bas.BaseSta + Mid.Body[ EM_WearEqType_STA ] + Mid.Body[ EM_WearEqType_AllState ] ) * ( Mid.BodyRate[ EM_WearEqType_STA_Rate ] * Mid.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::_INT()
{
	FLOAT Value = ( Ability->INT + Bas.BaseInt + Mid.Body[ EM_WearEqType_INT ] + Mid.Body[ EM_WearEqType_AllState ] ) * ( Mid.BodyRate[ EM_WearEqType_INT_Rate ] * Mid.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::_MND()
{
	float Value = ( Ability->MND + Bas.BaseMnd + Mid.Body[ EM_WearEqType_MND ] + Mid.Body[ EM_WearEqType_AllState ] ) * ( Mid.BodyRate[ EM_WearEqType_MND_Rate ] * Mid.BodyRate[ EM_WearEqType_AllState_Rate ] );

	return __max( Value , 0 );
}
float	RoleValueData::_AGI()
{
	float Value = ( Ability->AGI + Bas.BaseAgi + Mid.Body[ EM_WearEqType_AGI ] + Mid.Body[ EM_WearEqType_AllState ] ) * ( Mid.BodyRate[ EM_WearEqType_AGI_Rate ] * Mid.BodyRate[ EM_WearEqType_AllState_Rate ] );
	return __max( Value , 0 );
}
float	RoleValueData::_LUK()
{
    return 0;
}
float	RoleValueData::_MaxHP( )
{
	  float Value = ( ExAddHP + Bas.BaseHP + Fin.STR * Arg.HpStrArg+ Fin.STA * Arg.HpStaArg + Mid.Body[ EM_WearEqType_MaxHP ] ) * ( Mid.BodyRate[ EM_WearEqType_MaxHP_Rate ] );
	  return __max( Value , 1 );
}
float	RoleValueData::_MaxMP( )
{
	float Value = ( Bas.BaseMP + Fin.INT * Arg.MPIntArg + Fin.MND * Arg.MpMndArg + Mid.Body[ EM_WearEqType_MaxMP ] ) * ( Mid.BodyRate[ EM_WearEqType_MaxMP_Rate ] );
	return __max( Value , 0 );
}
float	RoleValueData::_MaxSP( )
{
    return Arg.MaxSP;
}
float	RoleValueData::_MaxSP_Sub( )
{
	return Arg_Sub.MaxSP;
}


float	RoleValueData::_ATK( )
{
    float RetAtk = Fin.STR* Arg.AtkStrArg + Fin.INT * Arg.AtkIntArg + Fin.AGI * Arg.AtkAgiArg;
	RetAtk = ( RetAtk + Mid.Body[ EM_WearEqType_ATK ] ) * ( Mid.BodyRate[ EM_WearEqType_ATK_Per ] );

    return __max( 1 , RetAtk );
}

float	RoleValueData::_DEF( )
{
	float AddDef = 0;

	AddDef =  BaseEQ.Def[ EM_Armor_HeavyArmed  ] * ( Mid.BodyRate[ EM_WearEqType_DEF_HeavyArmed ] )
			+ BaseEQ.Def[ EM_Armor_LightArmed	] * ( Mid.BodyRate[ EM_WearEqType_DEF_LightArmed ] )
			+ BaseEQ.Def[ EM_Armor_Leather		] * ( Mid.BodyRate[ EM_WearEqType_DEF_Leather	 ] )
			+ BaseEQ.Def[ EM_Armor_Clothes		] * ( Mid.BodyRate[ EM_WearEqType_DEF_Clothes	 ] )
			+ BaseEQ.Def[ EM_Armor_Robe		] * ( Mid.BodyRate[ EM_WearEqType_DEF_Robe		 ] )
			+ BaseEQ.Def[ EM_Armor_Shield		] * ( Mid.BodyRate[ EM_WearEqType_DEF_Shield	 ] )
			+ BaseEQ.Def[ EM_Armor_Implement	] 
			+ BaseEQ.Def[ EM_Armor_Ornament	] 
			;


    float RetValue =  (Fin.STA * Arg.DefArg + Mid.Body[ EM_WearEqType_DEF ] + AddDef )*( Mid.BodyRate[ EM_WearEqType_DEF_Per ]  )  ;
	return __max( 1 , RetValue );
}

float	RoleValueData::_MDEF( )
{
	float RetValue = ( Fin.MND * Arg.MDefArg + Mid.Body[ EM_WearEqType_MDEF ] ) * ( Mid.BodyRate[ EM_WearEqType_MDEF_Rate ]  );
    return __max( 1 , RetValue );
}
float	RoleValueData::_MATK( )
{
	float RetValue = ( Fin.INT * Arg.MAtkArg + Mid.Body[ EM_WearEqType_MATK ] ) * ( Mid.BodyRate[ EM_WearEqType_MATK_Rate ]  );
    return  __max( 1 , RetValue );
}

float	RoleValueData::_HitRate( )
{
	return Mid.Body[ EM_WearEqType_HitPoint ] + FixArg().PhyHit_AgiArg * Fin.AGI ;
}
float	RoleValueData::_DodgeRate( )
{
	return Mid.Body[ EM_WearEqType_DodgePoint ] + FixArg().PhyAvoid_AgiArg * Fin.AGI ;
}
float	RoleValueData::_MagHitRate( )
{
	return Mid.Body[ EM_WearEqType_MagicHitPoint ] + FixArg().MagHit_MndArg * Fin.MND ;
}
float	RoleValueData::_MagDodgeRate( )
{
	return Mid.Body[ EM_WearEqType_MagicDodgePoint ] + FixArg().MagAvoid_MndArg * Fin.MND + FixArg().MagAvoid_AgiArg * Fin.AGI ;
}


float	RoleValueData::_CriticalHit( )
{
    return __max( 1 , Mid.Body[ EM_WearEqType_CritRate ] + FixArg().BaseCritHit );
}

float	RoleValueData::_CriticalHitPower( )
{
	return __max( 0.5 , Mid.Body[ EM_WearEqType_CritPower ]/100 + FixArg().BaseCritPower );
}

float	RoleValueData::_MagicCriticalHit( )
{
	return __max( 0.5 , Mid.Body[ EM_WearEqType_MagicCritRate ] + FixArg().BaseMagicCritHit );
}

float	RoleValueData::_MagicCriticalHitPower( )
{
	return __max( 1 , Mid.Body[ EM_WearEqType_MagicCritPower ]/100 + FixArg().BaseMagicCritPower );
}


float	RoleValueData::_Main_CriticalHit( )
{
    return __max( 1 , /*Mid.Body[ EM_WearEqType_CritRate ] +*/ BaseEQ.Main_CriticalHit + Fin.CriticalHit );
}

float	RoleValueData::_Sec_CriticalHit( )
{
    return __max( 1 , /*Mid.Body[ EM_WearEqType_CritRate ]*/ + BaseEQ.Sec_CriticalHit + Fin.CriticalHit );
}

float	RoleValueData::_ParryRate( )
{
    return __max( 0 , Mid.Body[ EM_WearEqType_ParryRate ] );
}

float	RoleValueData::_ShieldBlockRate( )
{
    return __max( 0 , Mid.Body[ EM_WearEqType_ShieldBlockRate ] );
}


float	RoleValueData::_ReHP( )
{
    return __max( 0 , Arg.BaseReHP + Fin.STA * Arg.ReHpArg + Mid.Body[ EM_WearEqType_ReHP ] ); 
}
float	RoleValueData::_ReMP( )
{
    return __max( 0 , Arg.BaseReMP + Fin.MND * Arg.ReMpArg + Mid.Body[ EM_WearEqType_ReMP ] );
}
float 	RoleValueData::_Main_ATKSpeed( )
{
	if( MainWeaponType == EM_Weapon_None )
		return _BASE_ATTACK_SPEED_;

	
	float AtkSpeed_Per = Mid.BodyRate[ EM_WearEqType_AtkSpeed ] * BaseEQ.Main_ATKSpeed_Per* Mid.BodyRate[ EM_WearEqType_AttackSpeed_AllWeapon ];

	switch( MainWeaponType )
	{
	case EM_Weapon_Unarmed:	

		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Unarmed ];
		break;
    case EM_Weapon_Blade:        
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Blade ];
		break;
    case EM_Weapon_Dagger:       
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Dagger ];
		break;
    case EM_Weapon_Wand:         
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Wand ];
		break;
    case EM_Weapon_Axe:          
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Axe ];
		break;
    case EM_Weapon_Bludgeon:     
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Bludgeon ];
		break;
    case EM_Weapon_Claymore:     
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Claymore ];
		break;
    case EM_Weapon_Staff:        
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Staff ];
		break;
    case EM_Weapon_2H_Axe:       
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_2H_Axe ];
		break;
    case EM_Weapon_2H_Hammer:    
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_2H_Hammer ];
		break;
	case EM_Weapon_Polearm:		
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Polearm ];
		break;

	}

    return __max( 5 , ( ( AtkSpeed_Per ) * MainWeaponAttackSpeed ) );
}

float 	RoleValueData::_Sec_ATKSpeed( )
{
	if( SecWeaponType == EM_Weapon_None )
		return _BASE_ATTACK_SPEED_;

	float AtkSpeed_Per = Mid.BodyRate[ EM_WearEqType_AtkSpeed ] * BaseEQ.Sec_ATKSpeed_Per * Mid.BodyRate[ EM_WearEqType_AttackSpeed_AllWeapon ];

	switch( SecWeaponType )
	{
	case EM_Weapon_Unarmed:	
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Unarmed ];
		break;
	case EM_Weapon_Blade:        
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Blade ];
		break;
	case EM_Weapon_Dagger:       
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Dagger ];
		break;
	case EM_Weapon_Wand:         
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Wand ];
		break;
	case EM_Weapon_Axe:          
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Axe ];
		break;
	case EM_Weapon_Bludgeon:     
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Bludgeon ];
		break;
	case EM_Weapon_Claymore:     
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Claymore ];
		break;
	case EM_Weapon_Staff:        
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Staff ];
		break;
	case EM_Weapon_2H_Axe:       
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_2H_Axe ];
		break;
	case EM_Weapon_2H_Hammer:    
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_2H_Hammer ];
		break;
	case EM_Weapon_Polearm:		
		AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Polearm ];
		break;
	}

	return __max( 5 , ( ( AtkSpeed_Per ) * SecWeaponAttackSpeed ) );
}


float RoleValueData::_MoveSpeed( )
{
	float Speed;
	if( Effect.Ride != false )
		Speed = __max( 5 , _BASE_MOVE_SPEED_ *  Mid.BodyRate[ EM_WearEqType_RideSpeed ] * Bas.MoveSpeed_Per / 100 );
	else
	    Speed = __max( 5 , _BASE_MOVE_SPEED_ *  Mid.BodyRate[ EM_WearEqType_MoveSpeed ] * Bas.MoveSpeed_Per / 100 );

	if( Speed >= LastMaxMoveSpeed )
		LastMaxMoveSpeed = Speed;

	return Speed;
}

float   RoleValueData::_DMG( )
{
	float Rate = 0;
	if( FixArg().DmgAtkArg != 0 )
		Rate = 1/FixArg().DmgAtkArg;

	float Dmg = ( Fin.ATK * Rate + Mid.Body[ EM_WearEqType_DMG ])  * Arg.DmgRate * Mid.BodyRate[ EM_WearEqType_DMG_Per ];
    return __max( 0 , Dmg );
}

float   RoleValueData::_MDMG( )
{
	float Rate = 0;
	if( FixArg().MDmgMAtkArg != 0 )
		Rate = 1/FixArg().MDmgMAtkArg;

	float MDmg = ( Fin.MATK * Rate + Mid.Body[ EM_WearEqType_MDMG ]) * Mid.BodyRate[ EM_WearEqType_MDMG_Per ];;
	return __max( 0 , MDmg );
}


float   RoleValueData::_MPow()           //魔法增強率
{
	return __max( 0 , Mid.BodyRate[ EM_WearEqType_MagicPow_AllMagic ]  );
}
float   RoleValueData::_MAbr()           //魔法防禦吸收率
{
	return  Mid.BodyRate[ EM_WearEqType_MAbsorbRate ] -1;

}
float   RoleValueData::_Abr()            //防禦吸收率
{
	return Mid.BodyRate[ EM_WearEqType_AbsorbRate ] -1 ;
}
float   RoleValueData::_AB()             //防禦吸收點數
{
	return __max( Mid.Body[ EM_WearEqType_Absorb ] , 0 );
}

float	RoleValueData::ManaDecrease()
{
	if( Mid.Body[ EM_WearEqType_ManaDecrease ] > 50 )
		return 50;

	return Mid.Body[ EM_WearEqType_ManaDecrease ];
}
float	RoleValueData::SPWarriorDecrease()
{
	if( Mid.Body[ EM_WearEqType_SP_Warrior_Consume ] > 50 )
		return 50;

	return Mid.Body[ EM_WearEqType_SP_Warrior_Consume ];
}
float	RoleValueData::SPRogueDecrease()
{
	if( Mid.Body[ EM_WearEqType_SP_Rogue_Consume ] > 50 )
		return 50;

	return Mid.Body[ EM_WearEqType_SP_Rogue_Consume ];
}
float	RoleValueData::SPRangerDecrease()
{
	if( Mid.Body[ EM_WearEqType_SP_Ranger_Consume ] > 50 )
		return 50;

	return Mid.Body[ EM_WearEqType_SP_Ranger_Consume ];
}

float   RoleValueData::_MainDMG()
{
	float DmgRate = BaseEQ.Main_DMG_Per * Mid.BodyRate[ EM_WearEqType_DMG_AllWeapon ]* Mid.BodyRate[ EM_WearEqType_DMG_Per ];
	switch( MainWeaponType )
	{
	case EM_Weapon_Unarmed:	
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Unarmed ];
		break;
	case EM_Weapon_Blade:        
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Blade ];
		break;
	case EM_Weapon_Dagger:       
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Dagger ];
		break;
	case EM_Weapon_Wand:         
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Wand ];
		break;
	case EM_Weapon_Axe:          
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Axe ];
		break;
	case EM_Weapon_Bludgeon:     
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Bludgeon ];
		break;
	case EM_Weapon_Claymore:     
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Claymore ];
		break;
	case EM_Weapon_Staff:        
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Staff ];
		break;
	case EM_Weapon_2H_Axe:       
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_2H_Axe ];
		break;
	case EM_Weapon_2H_Hammer:    
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_2H_Hammer ];
		break;
	case EM_Weapon_Polearm:		
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Polearm ];
		break;
	}
//	float Ret = 0;

	if( BaseEQ.Main_DMG == 0 )
		BaseEQ.Main_DMG = Level * 2;

	float Ret = ( ( Fin.DMG + BaseEQ.Main_DMG )* ( DmgRate ) );

//	if( Ret <= 0 )
//		return Level * 2;

	if( Ret > 1 )
		return Ret;
	return 1;
}
float   RoleValueData::_SecDMG()
{
	float DmgRate = BaseEQ.Sec_DMG_Per *  Mid.BodyRate[ EM_WearEqType_SecHand_DMG_Per ] * Mid.BodyRate[ EM_WearEqType_DMG_AllWeapon ]* Mid.BodyRate[ EM_WearEqType_DMG_Per ];
	switch( SecWeaponType )
	{
	case EM_Weapon_Unarmed:	
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Unarmed ];
		break;
	case EM_Weapon_Blade:        
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Blade ];
		break;
	case EM_Weapon_Dagger:       
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Dagger ];
		break;
	case EM_Weapon_Wand:         
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Wand ];
		break;
	case EM_Weapon_Axe:          
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Axe ];
		break;
	case EM_Weapon_Bludgeon:     
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Bludgeon ];
		break;
	case EM_Weapon_Claymore:     
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Claymore ];
		break;
	case EM_Weapon_Staff:        
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Staff ];
		break;
	case EM_Weapon_2H_Axe:       
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_2H_Axe ];
		break;
	case EM_Weapon_2H_Hammer:    
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_2H_Hammer ];
		break;
	case EM_Weapon_Polearm:		
		DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Polearm ];
		break;
	}

	float Ret = ( ( Fin.DMG + BaseEQ.Sec_DMG ) * ( DmgRate ) ) * FixArg().Dmg_SecHand;
	if( Ret > 0 )
		return Ret;
	return 0;
}

float	RoleValueData::_Main_HitRate()
{
	float Rate = Fin.HitRate + BaseEQ.Main_HitRate;
	return Rate;
}
float	RoleValueData::_Sec_HitRate()
{
	float Rate = Fin.HitRate + BaseEQ.Sec_HitRate  + Mid.Body[ EM_WearEqType_SecHand_HitRate ];
	Rate *= FixArg().Miss_SecHand;
	return Rate;
}
EqWearSkillStruct RoleValueData::_EqWearSkill()
{
	EqWearSkillStruct Ret = JobWearSkill[ Voc ];

	for( int i = EM_WearEqType_WearEqAbility_Unarmed ; i <= EM_WearEqType_WearEqAbility_SecondHand ; i++ )
	{
		if( Mid.Body[i] > 0  )
		{
			int Pos = i - EM_WearEqType_WearEqAbility_Unarmed;
			Ret._Skill |= (1<<(Pos));
		}
	}
	return Ret;
}


//----------------------------------------------------------------------
//	全域資料
//----------------------------------------------------------------------
bool	RoleValueData::InitTable( char* Path )
{
    return true;
}
void RoleValueData::CalBaseTB( )
{
/*
#ifndef _CLIENT
    int R , V , S , L , T;
	float Arg;
	float ArgBase;
    for ( R = 0 ; R < _MAX_RACE_COUNT_ ; R++ )
	{
        for( V = 0 ; V < _MAX_VOCATION_COUNT_ ; V++ )
		{
            for( S = 0 ; S < _MAX_SEX_COUNT_; S++ )
            {
				for( T = 0 ; T < 2 ; T++ )
				{
					BaseStrTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BStrLv1 + VocArg[V][T].BStrLv1 + SexArg[S].BStrLv1;
					Arg		= RaceArg[R].StrArg + VocArg[V][T].StrArg + SexArg[S].StrArg;
					ArgBase = RaceArg[R].BStrArg + VocArg[V][T].BStrArg + SexArg[S].BStrArg;

					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseStrTB[ R ][ V ][ S ][ L ][ T ] = BaseStrTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}


					BaseStaTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BStaLv1 + VocArg[V][T].BStaLv1 + SexArg[S].BStaLv1;
					Arg		= RaceArg[R].StaArg + VocArg[V][T].StaArg + SexArg[S].StaArg;
					ArgBase = RaceArg[R].BStaArg + VocArg[V][T].BStaArg + SexArg[S].BStaArg;
				

					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseStaTB[ R ][ V ][ S ][ L ][ T ] = BaseStaTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}

					BaseIntTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BIntLv1 + VocArg[V][T].BIntLv1 + SexArg[S].BIntLv1;
					Arg		= RaceArg[R].IntArg + VocArg[V][T].IntArg + SexArg[S].IntArg;
					ArgBase = RaceArg[R].BIntArg + VocArg[V][T].BIntArg + SexArg[S].BIntArg;


					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseIntTB[ R ][ V ][ S ][ L ][ T ] = BaseIntTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}

					BaseMndTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BMndLv1 + VocArg[V][T].BMndLv1 + SexArg[S].BMndLv1;
					Arg		= RaceArg[R].MndArg + VocArg[V][T].MndArg + SexArg[S].MndArg;
					ArgBase = RaceArg[R].BMndArg + VocArg[V][T].BMndArg + SexArg[S].BMndArg;


					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseMndTB[ R ][ V ][ S ][ L ][ T ] = BaseMndTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}

					BaseAgiTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BAgiLv1 + VocArg[V][T].BAgiLv1 + SexArg[S].BAgiLv1;
					Arg		= RaceArg[R].AgiArg + VocArg[V][T].AgiArg + SexArg[S].AgiArg;
					ArgBase = RaceArg[R].BAgiArg + VocArg[V][T].BAgiArg + SexArg[S].BAgiArg;


					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseAgiTB[ R ][ V ][ S ][ L ][ T ] = BaseAgiTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}

					BaseHPTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BHpLv1 + VocArg[V][T].BHpLv1 + SexArg[S].BHpLv1;
					Arg		= RaceArg[R].HPArg + VocArg[V][T].HPArg + SexArg[S].HPArg;
					ArgBase = RaceArg[R].BHpArg + VocArg[V][T].BHpArg + SexArg[S].BHpArg;


					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseHPTB[ R ][ V ][ S ][ L ][ T ] = BaseHPTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}

					BaseMPTB[ R ][ V ][ S ][ 1 ][ T ] = RaceArg[R].BMpLv1 + VocArg[V][T].BMpLv1 + SexArg[S].BMpLv1;
					Arg		= RaceArg[R].MPArg + VocArg[V][T].MPArg + SexArg[S].MPArg;
					ArgBase = RaceArg[R].BMpArg + VocArg[V][T].BMpArg + SexArg[S].BMpArg;


					for( L = 2 ; L <= _MAX_LEVEL_ ; L ++ ) 
					{
						BaseMPTB[ R ][ V ][ S ][ L ][ T ] = BaseMPTB[ R ][ V ][ S ][ L -1 ][ T ] * ( 1 + Arg  )  + ArgBase; 
					}
				
				}
			}
		}
	}

#endif
*/
}

//計算物理傷害　被防禦修正
float	RoleValueData::CalWeaponDMG( float Power )
{
	if( Power >= 0 )
		return Power;
	float Value = ( Power + Fin.AB ) * ( 1 - Fin.Abr );
	return __min( -1 , int(Value) );
}


//計算法術傷害　被魔防修正
float	RoleValueData::CalMagicDMG( float Power )
{
	if( Power >= 0 )
		return Power;

	float Value = ( Power ) * ( 1 - Fin.MAbr );
	return __min( -1 , int(Value) );
}

float	RoleValueData::MainAtkDamage( ATTACK_DMGTYPE_ENUM DmgType )
{
	//計算亂數	
	float Dmg = Fin.Main_DMG * float( rand() % (WeaponBaseRand[MainWeaponType] *2+1) - WeaponBaseRand[MainWeaponType] + 100 )/100;

    float Value = ( Dmg - Target->Fin.AB ) * ( 1 - Target->Fin.Abr );

	float OAtk = ( Fin.ATK + 100 );
	float TDef = Target->Fin.DEF + 200;
	float PowerRate = 1.0f;

    switch( DmgType )
    {
	case EM_ATTACK_DMGTYPE_HALF:		    //被隔檔
		PowerRate = 0.5f;
		break;
	case EM_ATTACK_DMGTYPE_NORMAL:			//一般
	case EM_ATTACK_DMGTYPE_HITBACK:         //反擊
		break;
	case EM_ATTACK_DMGTYPE_DOUBLE:			//會心一擊
		{
			PowerRate = Fin.CriticalHitPower;
		}
		break;
	default:
		return 0;
    }

	float AttackRate = 1 + ( OAtk - TDef )/ __max( OAtk , TDef );

	if( AttackRate < 0.3f )
		AttackRate = 0.3f;

	Value = Value * AttackRate * PowerRate;

	return __max( 1 , Value ) ;


}

float	RoleValueData::SecAtkDamage( ATTACK_DMGTYPE_ENUM DmgType )
{

	//計算亂數
	float DMG = Fin.Sec_DMG  * float( rand() % (WeaponBaseRand[SecWeaponType] *2+1) - WeaponBaseRand[SecWeaponType] + 100 )/100;

    float Value = ( DMG - Target->Fin.AB ) * ( 1 - Target->Fin.Abr );

	float  OAtk = ( Fin.ATK + 100 );
	float  TDef = Target->Fin.DEF + 200;
	float PowerRate = 1.0f;

	switch( DmgType )
	{
	case EM_ATTACK_DMGTYPE_HALF:		    //被隔檔
		PowerRate = 0.5f;
		break;
	case EM_ATTACK_DMGTYPE_NORMAL:			//一般
	case EM_ATTACK_DMGTYPE_HITBACK:         //反擊
		break;
	case EM_ATTACK_DMGTYPE_DOUBLE:			//會心一擊
		{
			PowerRate = Fin.CriticalHitPower;
		}
		break;
	default:
		return 0;
	}

	float AttackRate = 1 + ( OAtk - TDef )/ __max( OAtk , TDef );

	if( AttackRate < 0.3f )
		AttackRate = 0.3f;

	Value = Value * AttackRate * PowerRate;

	return __max( 1 , Value ) ;

}

void	RoleValueData::_SkillValueCal()
{
	for( int i = 0 ; i < EM_SkillValueType_MaxCount ; i++ )
	{
		Fin.SkillValue.Skill[i] = __min( SkillValue->Skill[i] , MaxSkillValue.Skill[i] );
	}
	Fin.SkillValue.Skill[ EM_SkillValueType_Unarmed		] += Mid.Body[ EM_WearEqType_SkillValue_Unarmed	 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Blade     	] += Mid.Body[ EM_WearEqType_SkillValue_Blade    	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Dagger    	] += Mid.Body[ EM_WearEqType_SkillValue_Dagger   	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Wand      	] += Mid.Body[ EM_WearEqType_SkillValue_Wand     	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Axe       	] += Mid.Body[ EM_WearEqType_SkillValue_Axe      	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Bludgeon  	] += Mid.Body[ EM_WearEqType_SkillValue_Bludgeon 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Claymore  	] += Mid.Body[ EM_WearEqType_SkillValue_Claymore 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Staff     	] += Mid.Body[ EM_WearEqType_SkillValue_Staff    	];
	Fin.SkillValue.Skill[ EM_SkillValueType_2H_Axe    	] += Mid.Body[ EM_WearEqType_SkillValue_2H_Axe   	];
	Fin.SkillValue.Skill[ EM_SkillValueType_2H_Hammer 	] += Mid.Body[ EM_WearEqType_SkillValue_2H_Hammer	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Polearm		] += Mid.Body[ EM_WearEqType_SkillValue_Polearm	 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Bow			] += Mid.Body[ EM_WearEqType_SkillValue_Bow		 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_CossBow		] += Mid.Body[ EM_WearEqType_SkillValue_CossBow	 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Gun			] += Mid.Body[ EM_WearEqType_SkillValue_Gun		 	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Define		] += Mid.Body[ EM_WearEqType_SkillValue_Define		];
	Fin.SkillValue.Skill[ EM_SkillValueType_BlackSmith	] += Mid.Body[ EM_WearEqType_SkillValue_BlackSmith	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Carpenter	] += Mid.Body[ EM_WearEqType_SkillValue_Carpenter	];
	Fin.SkillValue.Skill[ EM_SkillValueType_MakeArmor	] += Mid.Body[ EM_WearEqType_SkillValue_MakeArmor	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Tailor		] += Mid.Body[ EM_WearEqType_SkillValue_Tailor		];
	Fin.SkillValue.Skill[ EM_SkillValueType_Cook		] += Mid.Body[ EM_WearEqType_SkillValue_Cook		];
	Fin.SkillValue.Skill[ EM_SkillValueType_Alchemy		] += Mid.Body[ EM_WearEqType_SkillValue_Alchemy		];
	Fin.SkillValue.Skill[ EM_SkillValueType_Mining		] += Mid.Body[ EM_WearEqType_SkillValue_Mining		];
	Fin.SkillValue.Skill[ EM_SkillValueType_Lumbering	] += Mid.Body[ EM_WearEqType_SkillValue_Lumbering	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Herblism	] += Mid.Body[ EM_WearEqType_SkillValue_Herbalism	];
	Fin.SkillValue.Skill[ EM_SkillValueType_Fishing		] += Mid.Body[ EM_WearEqType_SkillValue_Fishing		];
//	Fin.SkillValue.Skill[ EM_SkillValueType_Plant		] += Mid.Body[ EM_SkillValueType_Plant		];
//	Fin.SkillValue.Skill[ EM_SkillValueType_CatchPet	] += Mid.Body[ EM_SkillValueType_CatchPet		];
}

//某系魔法威力
float	RoleValueData::MagicPow( MagicResistENUM Type )
{
	switch( Type )
	{
	case EM_MagicResist_Earth:   
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Earth];
	case EM_MagicResist_Water:   
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Water];
	case EM_MagicResist_Fire:    
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Fire];
	case EM_MagicResist_Wind:    
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Wind];
	case EM_MagicResist_Light:   
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Light];
	case EM_MagicResist_Darkness:
		return Fin.MPow * Mid.BodyRate[EM_WearEqType_MagicPow_Darkness];
	}
	return Fin.MPow;		
}

//某系魔法施法速度
float	RoleValueData::MagicSpellSpeed( )
{
	return Mid.BodyRate[EM_WearEqType_SpellSpeed_AllMagic ];
}

float   RoleValueData::_Bow_ATKSpeed()
{
	if( BowWeaponType == EM_Weapon_None )
		return _BASE_ATTACK_SPEED_;

	float AtkSpeed_Per = Mid.BodyRate[ EM_WearEqType_AtkSpeed ] * BaseEQ.Bow_ATKSpeed_Per * Mid.BodyRate[ EM_WearEqType_AttackSpeed_AllRange ];

	switch( BowWeaponType )
	{
		case EM_Weapon_Bow:			
			AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Bow ];
			break;
		case EM_Weapon_CossBow:		
			AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Cossbow ];
			break;
		case EM_Weapon_Gun:			
			AtkSpeed_Per *= Mid.BodyRate[ EM_WearEqType_AttackSpeed_Gun ];
			break;
	}

	return ( AtkSpeed_Per * BoweAttackSpeed );
}
float   RoleValueData::_Bow_DMG()
{
	float DmgRate = BaseEQ.Bow_DMG_Per * Mid.BodyRate[ EM_WearEqType_DMG_AllRange ]  * Mid.BodyRate[ EM_WearEqType_DMG_Per ] ;
	switch( BowWeaponType )
	{
		case EM_Weapon_Bow:			
			DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Bow ];
			break;
		case EM_Weapon_CossBow:		
			DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Cossbow ];
			break;
		case EM_Weapon_Gun:			
			DmgRate *= Mid.BodyRate[ EM_WearEqType_DMG_Gun ];
			break;
	}
	float Ret = ( Fin.DMG + BaseEQ.Bow_DMG * ( DmgRate ) );
	if( Ret <=0 )
		Ret = 0;

	return Ret;
}
float	RoleValueData::_Bow_Critical()
{
	return Mid.Body[ EM_WearEqType_CritRate ] + BaseEQ.Bow_CriticalHit;
}
float	RoleValueData::_Bow_HiteRate()
{
	return Mid.Body[ EM_WearEqType_HitPoint ] + BaseEQ.Bow_HitRate;
}

float	RoleValueData::_MainJobSPRate()
{
	float Ret = 0;
	switch( Voc )
	{
	case EM_Vocation_Warrior:			// 戰士
	case EM_Vocation_Psyron:
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Warrior] );
		break;
	case EM_Vocation_Ranger:			// 遊俠
	case EM_Vocation_Harpsyn:			// 遊俠
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Ranger] );
		break;
	case EM_Vocation_Rogue:				// 盜賊
	case EM_Vocation_Duelist:
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Rogue] );
		break;
	}
	if( Ret < 0 )
		Ret = 0;
	return Ret;
}
float	RoleValueData::_SubJobSPRate()
{
	float Ret = 0;
	switch( Voc_Sub )
	{
	case EM_Vocation_Warrior:			// 戰士
	case EM_Vocation_Psyron:
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Warrior] ) ;
	case EM_Vocation_Ranger:			// 遊俠
	case EM_Vocation_Harpsyn:			// 遊俠
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Ranger] );
	case EM_Vocation_Rogue:				// 盜賊
	case EM_Vocation_Duelist:			// 鬥棋士
		Ret = ( Mid.BodyRate[EM_WearEqType_ReSP_Per_Rogue] );
	}
	if( Ret < 0 )
		Ret = 0;
	return Ret;
}

float	RoleValueData::_Bow_AttackRange()
{
	return Mid.Body[ EM_WearEqType_RangeAttackRange ] + BaseEQ.Bow_AttackRange;
}

float	RoleValueData::_Throw_DMG()
{
	float DmgRate = BaseEQ.Throw_DMG_Per * Mid.BodyRate[ EM_WearEqType_DMG_AllRange ] * Mid.BodyRate[ EM_WearEqType_DMG_Per ];
	float Ret = ( ( Fin.DMG + BaseEQ.Throw_DMG) * ( DmgRate ) );
	if( Ret <= 0 )
		Ret = 0;
	return Ret;
}
float	RoleValueData::_Throw_CriticalHit()
{
	return Mid.Body[ EM_WearEqType_CritRate ] + BaseEQ.Throw_CriticalHit;
}
float	RoleValueData::_Throw_ATKSpeed()
{
	if( BowWeaponType != EM_Weapon_None )
		return _BASE_ATTACK_SPEED_;

	float AtkSpeed_Per = Mid.BodyRate[ EM_WearEqType_AtkSpeed ] * BaseEQ.Throw_ATKSpeed_Per * Mid.BodyRate[ EM_WearEqType_AttackSpeed_AllRange ];

	return ( ( AtkSpeed_Per ) * ThrowAttackSpeed );
}
float	RoleValueData::_Throw_HitRate()
{
	return Mid.Body[ EM_WearEqType_HitPoint ] + BaseEQ.Throw_HitRate;
}
float	RoleValueData::_Throw_AttackRange()
{
	return Mid.Body[ EM_WearEqType_RangeAttackRange ] + BaseEQ.Throw_AttackRange;
}

void	RoleValueData::AddAbility_Buff( GameObjectWearEqStruct* Ability , float Power )
{
	int Type;
	float Value;

	for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
	{
		if( unsigned( Ability->EqType[ i ] ) >= unsigned( EM_WearEqType_MaxCount ) )
			Ability->EqType[ i ] = EM_WearEqType_None;
	}

	if(		Mid.OnAttackMagicRank <= Ability->OnAttackMagicRank 
		&&  Ability->OnAttackMagicID != 0 )
	{
		Mid.OnAttackMagicRank = Ability->OnAttackMagicRank;
		Mid.OnAttackMagicRate = Ability->OnAttackMagicRate;
		Mid.OnAttackMagicID   = Ability->OnAttackMagicID;
	}
	/*
	if(		BaseEQ.Main_OnAttackMagicRank <= Ability->OnAttackMagicRank 
		&&  Ability->OnAttackMagicID != 0 )
	{
		BaseEQ.Main_OnAttackMagicRank = Ability->OnAttackMagicRank;
		BaseEQ.Main_OnAttackMagicRate = Ability->OnAttackMagicRate;
		BaseEQ.Main_OnAttackMagicID   = Ability->OnAttackMagicID;
	}

	if(		BaseEQ.Sec_OnAttackMagicRank <= Ability->OnAttackMagicRank 
		&&  Ability->OnAttackMagicID != 0 )
	{
		BaseEQ.Sec_OnAttackMagicRank = Ability->OnAttackMagicRank;
		BaseEQ.Sec_OnAttackMagicRate = Ability->OnAttackMagicRate;
		BaseEQ.Sec_OnAttackMagicID   = Ability->OnAttackMagicID;
	}*/

	for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
	{
		Type	= Ability->EqType[ i ];
		Value	= Ability->EqTypeValue[i];
		Value	= Value * Power;
		Mid.Body[ Type ] += Value;
		Mid.BodyRate[ Type ] = _CalRate( Mid.BodyRate[Type ] , Value );
	}

}

//增加能力
void	RoleValueData::AddAbility( GameObjectWearEqStruct* Ability , GameObjectArmorENUM ArmorType , int Pos , float Power   )
{
	int Type;
	float Value;
	
	for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
	{
		if( unsigned( Ability->EqType[ i ] ) >= unsigned( EM_WearEqType_MaxCount ) )
			Ability->EqType[ i ] = EM_WearEqType_None;
	}

	switch( Pos )
	{
	case EM_EQWearPos_MainHand:
		{
			if(		BaseEQ.Main_OnAttackMagicRank <= Ability->OnAttackMagicRank 
				&&  Ability->OnAttackMagicID != 0 )
			{
				BaseEQ.Main_OnAttackMagicRank = Ability->OnAttackMagicRank;
				BaseEQ.Main_OnAttackMagicRate = Ability->OnAttackMagicRate;
				BaseEQ.Main_OnAttackMagicID   = Ability->OnAttackMagicID;
			}

			for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
			{
				Type	= Ability->EqType[ i ];
				Value	= Ability->EqTypeValue[i];
				//Value	= ToRoundOff( Value * Power );
				Value	= Value * Power;

				if( (unsigned)Type >= EM_WearEqType_MaxCount )
					continue;

				switch( Type )
				{
				case EM_WearEqType_HitPoint	    		:	//命中率
					BaseEQ.Main_HitRate += Value;
					break;
				case EM_WearEqType_CritRate	    		:   //致命一擊率
					BaseEQ.Main_CriticalHit += Value;
					break;
				case EM_WearEqType_AtkSpeed	    		:   //攻擊速度
					 BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_DMG           		:   //武器威力 所有近戰或遠程 ( DMG )
					BaseEQ.Main_DMG += Value;
					break;
					//尚未實作
				case EM_WearEqType_DMG_AllWeapon		:	//近戰武器威力 所有
					BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Unarmed			:	//近戰武器威力 空手
					if( SecWeaponType == EM_Weapon_Unarmed )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Blade     		:	//近戰武器威力 劍
					if( SecWeaponType == EM_Weapon_Blade )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Dagger    		:	//近戰武器威力 匕首
					if( SecWeaponType == EM_Weapon_Dagger )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Wand      		:	//近戰武器威力 權杖
					if( SecWeaponType == EM_Weapon_Wand )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Axe       		:	//近戰武器威力 斧
					if( SecWeaponType == EM_Weapon_Axe )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Bludgeon  		:	//近戰武器威力 鎚棍棒
					if( SecWeaponType == EM_Weapon_Bludgeon )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Claymore  		:	//近戰武器威力 雙手劍
					if( SecWeaponType == EM_Weapon_Claymore )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Staff     		:	//近戰武器威力 杖
					if( SecWeaponType == EM_Weapon_Staff )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_2H_Axe    		:	//近戰武器威力 雙手斧
					if( SecWeaponType == EM_Weapon_2H_Axe )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_2H_Hammer 		:	//近戰武器威力 雙手鎚
					if( SecWeaponType == EM_Weapon_2H_Hammer )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Polearm			:	//近戰武器威力 槍(長矛)
					if( SecWeaponType == EM_Weapon_Polearm )
						BaseEQ.Main_DMG_Per = _CalRate( BaseEQ.Main_DMG_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_AllWeapon:	//近戰武器速度 所有				
					BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Unarmed	:	//近戰武器速度 空手
					if( SecWeaponType == EM_Weapon_Unarmed )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Blade    :	//近戰武器速度 劍
					if( SecWeaponType == EM_Weapon_Blade )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Dagger   :	//近戰武器速度 匕首
					if( SecWeaponType == EM_Weapon_Dagger )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Wand     :	//近戰武器速度 權杖
					if( SecWeaponType == EM_Weapon_Wand )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Axe      :	//近戰武器速度 斧
					if( SecWeaponType == EM_Weapon_Axe )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Bludgeon :	//近戰武器速度 鎚棍棒
					if( SecWeaponType == EM_Weapon_Bludgeon )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Claymore :	//近戰武器速度 雙手劍
					if( SecWeaponType == EM_Weapon_Claymore )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Staff    :	//近戰武器速度 杖
					if( SecWeaponType == EM_Weapon_Staff )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_2H_Axe   :	//近戰武器速度 雙手斧
					if( SecWeaponType == EM_Weapon_2H_Axe )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_2H_Hammer:	//近戰武器速度 雙手鎚
					if( SecWeaponType == EM_Weapon_2H_Hammer )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Polearm	:	//近戰武器速度 槍(長矛)
					if( SecWeaponType == EM_Weapon_Polearm )
						BaseEQ.Main_ATKSpeed_Per = _CalRate( BaseEQ.Main_ATKSpeed_Per , Value );
					break;					
				case EM_WearEqType_Magic_EarthPower:	// "地屬性攻擊" ,
				case EM_WearEqType_Magic_WaterhPower:	// "水屬性攻擊" ,
				case EM_WearEqType_Magic_FirePower:		// "火屬性攻擊" ,
				case EM_WearEqType_Magic_WindhPower:	// "風屬性攻擊" ,
				case EM_WearEqType_Magic_LightPower:	// "光屬性攻擊" ,
				case EM_WearEqType_Magic_DarkPower:		// "暗屬性攻擊" ,
					BaseEQ.Main_MagicAtk[ Type - EM_WearEqType_Magic_EarthPower ] += Value;
					break;
					/*
				case EM_WearEqType_SpellSpeed_AllMagic:
				case EM_WearEqType_MoveSpeed:
				case EM_WearEqType_RideSpeed:
				case EM_WearEqType_Gravity:
				case EM_WearEqType_JumpRate:
					BaseEQ.Body[Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
					break;*/
				default:
					{
						BaseEQ.Body[Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[ Type ] , Value );
					}
					break;
				}				

			}	
		}
		break;
	case EM_EQWearPos_SecondHand:
		{	
			if(		BaseEQ.Sec_OnAttackMagicRank <= Ability->OnAttackMagicRank 
				&&  Ability->OnAttackMagicID != 0 )
			{
				BaseEQ.Sec_OnAttackMagicRank = Ability->OnAttackMagicRank;
				BaseEQ.Sec_OnAttackMagicRate = Ability->OnAttackMagicRate;
				BaseEQ.Sec_OnAttackMagicID   = Ability->OnAttackMagicID;
			}

			for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
			{
				Type	= Ability->EqType[ i ];
				Value	= Ability->EqTypeValue[i];
				Value	= Value * Power;

				if( (unsigned)Type >= EM_WearEqType_MaxCount )
					continue;

				switch( Type )
				{

				case EM_WearEqType_HitPoint	    		:	//命中率
					BaseEQ.Sec_HitRate += Value;
					break;
				case EM_WearEqType_CritRate	    		:   //致命一擊率
					BaseEQ.Sec_CriticalHit += Value;
					break;
				case EM_WearEqType_AtkSpeed	    		:   //攻擊速度
					BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_DMG           		:   //武器威力 所有近戰或遠程 ( DMG )
					BaseEQ.Sec_DMG += Value;
					break;
					//尚未實作
				case EM_WearEqType_DMG_AllWeapon		:	//近戰武器威力 所有
					BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Unarmed			:	//近戰武器威力 空手
					if( SecWeaponType == EM_Weapon_Unarmed )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Blade     		:	//近戰武器威力 劍
					if( SecWeaponType == EM_Weapon_Blade )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Dagger    		:	//近戰武器威力 匕首
					if( SecWeaponType == EM_Weapon_Dagger )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Wand      		:	//近戰武器威力 權杖
					if( SecWeaponType == EM_Weapon_Wand )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Axe       		:	//近戰武器威力 斧
					if( SecWeaponType == EM_Weapon_Axe )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Bludgeon  		:	//近戰武器威力 鎚棍棒
					if( SecWeaponType == EM_Weapon_Bludgeon )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Claymore  		:	//近戰武器威力 雙手劍
					if( SecWeaponType == EM_Weapon_Claymore )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Staff     		:	//近戰武器威力 杖
					if( SecWeaponType == EM_Weapon_Staff )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_2H_Axe    		:	//近戰武器威力 雙手斧
					if( SecWeaponType == EM_Weapon_2H_Axe )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_2H_Hammer 		:	//近戰武器威力 雙手鎚
					if( SecWeaponType == EM_Weapon_2H_Hammer )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_DMG_Polearm			:	//近戰武器威力 槍(長矛)
					if( SecWeaponType == EM_Weapon_Polearm )
						BaseEQ.Sec_DMG_Per = _CalRate( BaseEQ.Sec_DMG_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_AllWeapon:	//近戰武器速度 所有				
					BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Unarmed	:	//近戰武器速度 空手
					if( SecWeaponType == EM_Weapon_Unarmed )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Blade    :	//近戰武器速度 劍
					if( SecWeaponType == EM_Weapon_Blade )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Dagger   :	//近戰武器速度 匕首
					if( SecWeaponType == EM_Weapon_Dagger )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Wand     :	//近戰武器速度 權杖
					if( SecWeaponType == EM_Weapon_Wand )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Axe      :	//近戰武器速度 斧
					if( SecWeaponType == EM_Weapon_Axe )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Bludgeon :	//近戰武器速度 鎚棍棒
					if( SecWeaponType == EM_Weapon_Bludgeon )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Claymore :	//近戰武器速度 雙手劍
					if( SecWeaponType == EM_Weapon_Claymore )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Staff    :	//近戰武器速度 杖
					if( SecWeaponType == EM_Weapon_Staff )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_2H_Axe   :	//近戰武器速度 雙手斧
					if( SecWeaponType == EM_Weapon_2H_Axe )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_2H_Hammer:	//近戰武器速度 雙手鎚
					if( SecWeaponType == EM_Weapon_2H_Hammer )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_AttackSpeed_Polearm	:	//近戰武器速度 槍(長矛)
					if( SecWeaponType == EM_Weapon_Polearm )
						BaseEQ.Sec_ATKSpeed_Per = _CalRate( BaseEQ.Sec_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_Magic_EarthPower:	// "地屬性攻擊" ,
				case EM_WearEqType_Magic_WaterhPower:	// "水屬性攻擊" ,
				case EM_WearEqType_Magic_FirePower:		// "火屬性攻擊" ,
				case EM_WearEqType_Magic_WindhPower:	// "風屬性攻擊" ,
				case EM_WearEqType_Magic_LightPower:	// "光屬性攻擊" ,
				case EM_WearEqType_Magic_DarkPower:		// "暗屬性攻擊" ,
					BaseEQ.Main_MagicAtk[ Type - EM_WearEqType_Magic_EarthPower ] += Value;
/*
				case EM_WearEqType_SpellSpeed_AllMagic:
				case EM_WearEqType_MoveSpeed:
				case EM_WearEqType_RideSpeed:
				case EM_WearEqType_Gravity:
				case EM_WearEqType_JumpRate:
					BaseEQ.Body[Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
					break;
					*/
				default:
					{
						BaseEQ.Body[Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[Type ] , Value );
					}
					break;

				}					 
			}	 
		}
		break;
	case EM_EQWearPos_Bow:
		{
			for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
			{
				Type	= Ability->EqType[ i ];
				Value	= Ability->EqTypeValue[i];
				Value	= Value * Power;

				if( (unsigned)Type >= EM_WearEqType_MaxCount )
					continue;

				switch( Type )
				{

				case EM_WearEqType_HitPoint	    		:	//命中率
					BaseEQ.Bow_HitRate += Value;
					break;
				case EM_WearEqType_CritRate	    		:   //致命一擊率
					BaseEQ.Bow_CriticalHit += Value;
					break;
				case EM_WearEqType_AtkSpeed	    		:   //攻擊速度
					BaseEQ.Bow_ATKSpeed_Per = _CalRate( BaseEQ.Bow_ATKSpeed_Per , Value );
					break;
				case EM_WearEqType_DMG           		:   //武器威力 所有近戰或遠程 ( DMG )
					BaseEQ.Bow_DMG += Value;
					break;
				case EM_WearEqType_RangeAttackRange:
					BaseEQ.Bow_AttackRange += Value;
					break;
				case EM_WearEqType_AttackRange:
					/*
				case EM_WearEqType_SpellSpeed_AllMagic:
				case EM_WearEqType_MoveSpeed:
				case EM_WearEqType_RideSpeed:
				case EM_WearEqType_Gravity:
				case EM_WearEqType_JumpRate:
					BaseEQ.Body[Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
					break;
*/
				default:
					{
						BaseEQ.Body[Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[Type ] , Value );
					}
					break;
				}		

			}	
		}
		break;
	case EM_EQWearPos_Ammo:
		{
			for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
			{
				Type	= Ability->EqType[ i ];
				Value	= Ability->EqTypeValue[i];
				Value	= Value * Power;

				if( (unsigned)Type >= EM_WearEqType_MaxCount )
					continue;

				switch( Type )
				{
				case EM_WearEqType_HitPoint	    		:	//命中率
					BaseEQ.Throw_HitRate += Value;
					break;
				case EM_WearEqType_CritRate	    		:   //致命一擊率
					BaseEQ.Throw_CriticalHit += Value;
					break;
				case EM_WearEqType_AttackSpeed_AllRange	:   //攻擊速度
					BaseEQ.Throw_ATKSpeed_Per = _CalRate( BaseEQ.Throw_ATKSpeed_Per  , Value );
					break;
				case EM_WearEqType_DMG           		:   //武器威力 所有近戰或遠程 ( DMG )
					BaseEQ.Throw_DMG += Value;
					BaseEQ.Bow_DMG += Value;
					break;
				case EM_WearEqType_RangeAttackRange:
					BaseEQ.Throw_AttackRange += Value;
					break;
					/*
				case EM_WearEqType_SpellSpeed_AllMagic:
				case EM_WearEqType_MoveSpeed:
				case EM_WearEqType_RideSpeed:
				case EM_WearEqType_Gravity:
				case EM_WearEqType_JumpRate:
					BaseEQ.Body[Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
					break;
*/

				default:
					{
						BaseEQ.Body[Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[Type ] , Value );
					}
					break;
				}					 
			}	
		}
		break;
	default:
		{
			if(		BaseEQ.Main_OnAttackMagicRank <= Ability->OnAttackMagicRank 
				&&  Ability->OnAttackMagicID != 0 )
			{
				BaseEQ.Main_OnAttackMagicRank = Ability->OnAttackMagicRank;
				BaseEQ.Main_OnAttackMagicRate = Ability->OnAttackMagicRate;
				BaseEQ.Main_OnAttackMagicID   = Ability->OnAttackMagicID;
			}

			if(		BaseEQ.Sec_OnAttackMagicRank <= Ability->OnAttackMagicRank 
				&&  Ability->OnAttackMagicID != 0 )
			{
				BaseEQ.Sec_OnAttackMagicRank = Ability->OnAttackMagicRank;
				BaseEQ.Sec_OnAttackMagicRate = Ability->OnAttackMagicRate;
				BaseEQ.Sec_OnAttackMagicID   = Ability->OnAttackMagicID;
			}

			//額外計算各類裝備的防禦值
			//if( OrgDB->IsArmor() )
			if( ArmorType != EM_Armor_None )
			{
				for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
				{
					Type	= Ability->EqType[ i ];
					Value	= Ability->EqTypeValue[i];
					Value	= Value * Power;

					if( (unsigned)Type >= EM_WearEqType_MaxCount )
						continue;

					switch( Type )
					{
					case EM_WearEqType_DEF:
						BaseEQ.Def[ ArmorType ] +=  Value;
						break;
						/*
					case EM_WearEqType_AtkSpeed:			
					case EM_WearEqType_MoveSpeed:
					case EM_WearEqType_SpellSpeed_AllMagic:
					case EM_WearEqType_AttackSpeed_AllRange:
					case EM_WearEqType_AttackSpeed_Bow:
					case EM_WearEqType_AttackSpeed_Cossbow:
					case EM_WearEqType_AttackSpeed_Gun:
					case EM_WearEqType_AttackSpeed_AllWeapon:
					case EM_WearEqType_AttackSpeed_Unarmed:
					case EM_WearEqType_AttackSpeed_Blade:
					case EM_WearEqType_AttackSpeed_Dagger:
					case EM_WearEqType_AttackSpeed_Wand:
					case EM_WearEqType_AttackSpeed_Axe:
					case EM_WearEqType_AttackSpeed_Bludgeon:
					case EM_WearEqType_AttackSpeed_Claymore:
					case EM_WearEqType_AttackSpeed_Staff:
					case EM_WearEqType_AttackSpeed_2H_Axe:
					case EM_WearEqType_AttackSpeed_2H_Hammer:
					case EM_WearEqType_AttackSpeed_Polearm:
					case EM_WearEqType_RideSpeed:
					case EM_WearEqType_Gravity:
					case EM_WearEqType_JumpRate:
						BaseEQ.Body[ Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
						break;
						*/
					default:
						BaseEQ.Body[ Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[Type ] , Value );
						break;
					}
				}
			}
			else
			{
				for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
				{
					Type	= Ability->EqType[ i ];
					Value	= Ability->EqTypeValue[i];
					Value	= Value * Power;

					if( (unsigned)Type >= EM_WearEqType_MaxCount )
						continue;

					//switch( Type )
					{
						/*
					case EM_WearEqType_AtkSpeed:			
					case EM_WearEqType_MoveSpeed:
					case EM_WearEqType_SpellSpeed_AllMagic:
					case EM_WearEqType_AttackSpeed_AllRange:
					case EM_WearEqType_AttackSpeed_Bow:
					case EM_WearEqType_AttackSpeed_Cossbow:
					case EM_WearEqType_AttackSpeed_Gun:
					case EM_WearEqType_AttackSpeed_AllWeapon:
					case EM_WearEqType_AttackSpeed_Unarmed:
					case EM_WearEqType_AttackSpeed_Blade:
					case EM_WearEqType_AttackSpeed_Dagger:
					case EM_WearEqType_AttackSpeed_Wand:
					case EM_WearEqType_AttackSpeed_Axe:
					case EM_WearEqType_AttackSpeed_Bludgeon:
					case EM_WearEqType_AttackSpeed_Claymore:
					case EM_WearEqType_AttackSpeed_Staff:
					case EM_WearEqType_AttackSpeed_2H_Axe:
					case EM_WearEqType_AttackSpeed_2H_Hammer:
					case EM_WearEqType_AttackSpeed_Polearm:
					case EM_WearEqType_RideSpeed:
					case EM_WearEqType_Gravity:
					case EM_WearEqType_JumpRate:
						BaseEQ.Body[ Type ] = _CalRate( BaseEQ.Body[Type ] , Value );
						break;
						*/
					//default:
						BaseEQ.Body[ Type ] += Value;
						BaseEQ.BodyRate[ Type ] = _CalRate( BaseEQ.BodyRate[Type ] , Value );
						//break;
					}
				}
				
			}
		}
		break;
	}
}

float	RoleValueData::_CalRate( float OrgSpeed , float AddSpeed )
{
	return ( OrgSpeed ) * ( AddSpeed / 100 + 1 ) ;
}

float		RoleValueData::_CalBaseStr( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BStrLv1 + VocArg[Voc][FixArgTableID].BStrLv1 + SexArg[Sex].BStrLv1;
	float Arg		= RaceArg[Race].StrArg + VocArg[Voc][FixArgTableID].StrArg + SexArg[Sex].StrArg;
	float ArgBase	= RaceArg[Race].BStrArg + VocArg[Voc][FixArgTableID].BStrArg + SexArg[Sex].BStrArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseSta( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BStaLv1 + VocArg[Voc][FixArgTableID].BStaLv1 + SexArg[Sex].BStaLv1;
	float Arg		= RaceArg[Race].StaArg + VocArg[Voc][FixArgTableID].StaArg + SexArg[Sex].StaArg;
	float ArgBase	= RaceArg[Race].BStaArg + VocArg[Voc][FixArgTableID].BStaArg + SexArg[Sex].BStaArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseInt( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BIntLv1 + VocArg[Voc][FixArgTableID].BIntLv1 + SexArg[Sex].BIntLv1;
	float Arg		= RaceArg[Race].IntArg + VocArg[Voc][FixArgTableID].IntArg + SexArg[Sex].IntArg;
	float ArgBase	= RaceArg[Race].BIntArg + VocArg[Voc][FixArgTableID].BIntArg + SexArg[Sex].BIntArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseMnd( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BMndLv1 + VocArg[Voc][FixArgTableID].BMndLv1 + SexArg[Sex].BMndLv1;
	float Arg		= RaceArg[Race].MndArg + VocArg[Voc][FixArgTableID].MndArg + SexArg[Sex].MndArg;
	float ArgBase	= RaceArg[Race].BMndArg + VocArg[Voc][FixArgTableID].BMndArg + SexArg[Sex].BMndArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseAgi( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BAgiLv1 + VocArg[Voc][FixArgTableID].BAgiLv1 + SexArg[Sex].BAgiLv1;
	float Arg		= RaceArg[Race].AgiArg + VocArg[Voc][FixArgTableID].AgiArg + SexArg[Sex].AgiArg;
	float ArgBase	= RaceArg[Race].BAgiArg + VocArg[Voc][FixArgTableID].BAgiArg + SexArg[Sex].BAgiArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseHP ( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BHpLv1 + VocArg[Voc][FixArgTableID].BHpLv1 + SexArg[Sex].BHpLv1;
	float Arg		= RaceArg[Race].HPArg + VocArg[Voc][FixArgTableID].HPArg + SexArg[Sex].HPArg;
	float ArgBase	= RaceArg[Race].BHpArg + VocArg[Voc][FixArgTableID].BHpArg + SexArg[Sex].BHpArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}
float		RoleValueData::_CalBaseMP ( int Race , int Voc , int Sex , int Lv )
{
	float Value		= RaceArg[Race].BMpLv1 + VocArg[Voc][FixArgTableID].BMpLv1 + SexArg[Sex].BMpLv1;
	float Arg		= RaceArg[Race].MPArg + VocArg[Voc][FixArgTableID].MPArg + SexArg[Sex].MPArg;
	float ArgBase	= RaceArg[Race].BMpArg + VocArg[Voc][FixArgTableID].BMpArg + SexArg[Sex].BMpArg;

	for( int L = 2 ; L <= Level  ; L ++ ) 
		Value = Value* ( 1 + Arg  )  + ArgBase; 

	return Value;
}

float	RoleValueData::ToRoundOff( float X )
{
	float Ret = X; 
	if( X > 0 )
	{
		Ret = float( int ( X+0.5f ) ); 
	}
	else if( X < 0 )
	{
		Ret = float( int ( X-0.5f ) ); 
	}
	return Ret;
}

void RoleValueData::_CalElementPower()
{
	for( int i = 0 ; i < EM_MagicResist_MAXCOUNT ; i++ )
	{
		Fin.Main_MagicAtk[i] = BaseEQ.Main_MagicAtk[i]+Mid.Body[ i+EM_WearEqType_Magic_EarthPower ];
		Fin.Sec_MagicAtk[i] = BaseEQ.Sec_MagicAtk[i]+Mid.Body[ i+EM_WearEqType_Magic_EarthPower ];
	}
}

FixFightArgumentStruct&   RoleValueData::FixArg()     //固定參數表
{
	return FixArgTable[ FixArgTableID ];
}
float RoleValueData::_ResistParryRate()
{
	return	Mid.Body[ EM_WearEqType_ResistParry ];
}
float RoleValueData::_ResistBlockRate()
{
	return	Mid.Body[ EM_WearEqType_ResistShieldBlock ];
}
float RoleValueData::_ResistCriticalHit()
{
	return	Mid.Body[ EM_WearEqType_ResistCritRate ];
}
float RoleValueData::_ResistMagicCriticalHit()
{
	return	Mid.Body[ EM_WearEqType_ResistMagicCritRate ];
}

float	RoleValueData::CalShieldBlockRate	( int TargetLv , float TargetResistRate )
{
	float OAtk = (Fin.ShieldBlockRate + FixArg().BaseRateArg + Level*FixArg().DLvRateArg );
	float TDef = (TargetResistRate + FixArg().BaseResistArg + TargetLv*FixArg().DLvResistArg );
	if ( __max(OAtk , TDef ) == 0.0f )
		return 0.0f;
	float PowerRate = ( 1 + ( OAtk - TDef )/ __max(OAtk , TDef ) ) * 0.5f;
	return PowerRate;
}
float	RoleValueData::CalParryRate		( int TargetLv , float TargetResistRate )
{
	float OAtk = (Fin.ParryRate + FixArg().BaseRateArg + Level*FixArg().DLvRateArg );
	float TDef = (TargetResistRate + FixArg().BaseResistArg + TargetLv*FixArg().DLvResistArg );
	if ( __max(OAtk , TDef ) == 0.0f )
		return 0.0f;
	float PowerRate = ( 1 + ( OAtk - TDef )/ __max(OAtk , TDef ) ) * 0.5f;
	PowerRate += ( Mid.BodyRate[EM_WearEqType_ParryRate_Per] - 1 );

	return PowerRate;
}
float	RoleValueData::CalCritialRate		( float CritialRate , int TargetLv , float TargetResistRate )
{
	float OAtk = (CritialRate + FixArg().BaseRateArg + Level*FixArg().DLvRateArg );
	float TDef = (TargetResistRate + FixArg().BaseResistArg + TargetLv*FixArg().DLvResistArg );
	if ( __max(OAtk , TDef ) == 0.0f )
		return 0.0f;
	float PowerRate = ( 1 + ( OAtk - TDef )/ __max(OAtk , TDef ) ) * 0.5f;

	if( Effect.Critial ) 
		return 100;

	return PowerRate;
}
float	RoleValueData::CalMagCritialRate	( float MagCritialRate , int TargetLv , float TargetResistRate )
{
	float OAtk = (MagCritialRate + FixArg().BaseRateArg + Level*FixArg().DLvRateArg );
	float TDef = (TargetResistRate + FixArg().BaseResistArg + TargetLv*FixArg().DLvResistArg );
	if ( __max(OAtk , TDef ) == 0.0f )
		return 0.0f;
	float PowerRate = ( 1 + ( OAtk - TDef )/ __max(OAtk , TDef ) ) * 0.5f;

	if( Effect.Critial ) 
		return 100;

	return PowerRate;
}