#ifndef	__ROLEDATAEX_H_
#define __ROLEDATAEX_H_
#include "Roledata.h"
#include "ReaderClass/ReaderClass.h"
#include <boost/function.hpp>
#include <boost/function_equal.hpp> 
#include "CampStatute.h"

using namespace boost;


enum   RoleDataResultENUM
{
	EM_RoleData_OKEx_SpecialEq	= -1	,
    EM_RoleData_OK				= 0		,	
    EM_RoleData_PosErr			,
    EM_RoleData_BufferEmpty		,
    EM_RoleData_DataInfoErr		,
    EM_RoleData_ApartSizeErr	,
    EM_RoleData_OrgObjIDErr		,
    EM_RoleData_EQWearPosErr	,
    EM_RoleData_CountErr		,
	EM_RoleData_IsEmpty			,
	EM_RoleData_Err_ItemUnique	,	

};


class RoleDataEx : public RoleData
{
public:
    static	int				G_ZoneID;									//�ϰ�id(�R�A����)
    static	int				G_Clock;									//�ɯ�
    static	myUInt32		G_SysTime;									//��timeGetTime() - G_SysTime_Base ���o����
    static	myUInt32		G_SysTime_Base;								//�ε{���}�Ү� timeGetTime() ���o����
    static	PKTypeENUM		G_PKType;
	static  int				G_TimeZone;									//Server�ɰ�
	static  int				G_MaxVocCount;								//�̦h¾�~�ƶq

    static  StaticString< _MAX_CREATETIME_SIZE_> G_NowStr;  			//�ثe�ɶ��r��
	static  myUInt32		G_Now;
	static	float			G_Now_Float;
	static	int				G_Day;

    //�رڤ����
    static  int				HateTable[_MAX_RACE_COUNT_][_MAX_RACE_COUNT_];

	static float			ArmorArg[3][EM_ArmorPos_MaxCount][EM_Armor_MaxCount];		//�˳Ư�O�Ѽ�
	static int				BaseMagicList[ EM_BaseMagic_MaxCount ];									   

	static vector<string>	ZoneChannel;

	static int				AddLv_byRare[ 10 ];

//	static vector<EqRefinePowerStruct> EqRefineTable; 

	static CampStatuteClass	Camp;						//�}��

	static vector<int>		RefineExpTable;				//�һs���g��Ȫ�
	static vector<int>		JobExpTable;				//�g��Ȫ�
	static vector<int>		SkillExpTable;				//�ޯ�g��Ȫ�
	static vector<int>		GatherExpTable;				//�Ķ��g��Ȫ�
	static vector<int>		PlantExpTable;				//�شӸg��Ȫ�
	static vector<float>	PlantEffectPointTable;		//�شӪήƿ@�׮t�v�T���d
	static vector<int>		PlotExpTable;				//�@���i��o�g���
	static vector<int>		PlotMoneyTable;				//�@���i��o����
	static vector<float>	JobExp_LvGrowRateTable;		//�g�禨���v
	static vector<int>		JobSkillExpTable;			//¾�~�g��Ȫ�
	static vector<int>		StandardCostTable;			//
	static vector<int>		HouseExpArgTable;			//
	static vector<float>	MPCostPowerRate;			//�C��PowerLv�һݭnMP
	static vector<int>		PetExpTable;
//	static vector<int>		PetLearnMagicCostTable;
	static vector<int>		PetLifeSkillTable;

	static vector< LvDissolutionTable > DissolutionTable;
	static vector< ComboTable> ComboInfo;
	static vector< int >	LifeSkillLearnKey[ EM_SkillValueType_MaxCount ];
	static map< int , vector< ItemCombineStruct > >		ItemCombineList;
	static int				ItemCombineListExGroupID;
	static map< int , map< int , vector< ItemCombineStruct > > > ItemCombineListEx;

	static bool				G_IsPvE;					//pk �Ҧ�
	//-----------------------------------------------------------------------------------------
	//�Ҧ�¾�~ �P �ر�
	//----------------------------------------------------------------------------------------
	static char*			RaceShortStr[32];
	static char*			RaceStr[32];
	static char*			VocShortStr[32];
	static char*			VocStr[32];
	static int				SysDTime;		//�t�ήɶ��t
	//-----------------------------------------------------------------------------------------
	//���ϳ]�w
	//----------------------------------------------------------------------------------------
	static GlobalServerDBInfoStruct	GlobalSetting;
	static bool				IsDisablePVPRule;
	static bool				IsDisablePVPRule_Temp;
	static bool				IsDisableMagicRebound;			//
	//----------------------------------------------------------------------------------------
	//�ϰ�������Ӹ�T
	//----------------------------------------------------------------------------------------
	static int				MoneyIn;
	static int				MoneyOut;
	static int				AccountMoneyIn;
	static int				AccountMoneyOut;
	//----------------------------------------------------------------------------------------
	//�׸� �������
	//----------------------------------------------------------------------------------------
	static float			FixArmorRate[ EM_Armor_MaxCount ];
	
	//�̫�@���B�z���Ѫ��T��
	static RoleErrorMsgENUM		LastProcErr;

	static int					LastLockMoneySpentPlayerDBID;
	static int					LastLockMoneySpent;
    static OnAttackInfoStruct	LastAttackInfo;

	static vector<WeekZoneStruct>	WeekInstances;	
	static int						WeekInstancesDay;

	static map< int,PhantomRankTableStruct >		   PhantomRank;
	static map< int,map < int,PhantomLvTableStruct > > PhantomLv;
	static map< INT64,int >							   PhantomSkill;	//key = �jid + �pid * 0x100000000
	static map< int,float >							   PhantomAbiArg;

    #include "RD_NetFunction.inl"

	#include "RD_Check.inl"
	#include "RD_ItemProc.inl"
	#include "RD_Normal.inl"
	#include "RD_Save.inl"
	#include "RD_Search.inl"
	#include "RD_STFunc.inl"
	#include "RD_ValueCal.inl"
	#include "RD_Setting.inl"
	#include "RD_Event.inl"
	#include "RD_Script.inl"
	#include "RD_Utility.inl"
    
};

#endif