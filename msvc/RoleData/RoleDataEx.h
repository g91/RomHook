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
    static	int				G_ZoneID;									//區域id(靜態全域)
    static	int				G_Clock;									//時脈
    static	myUInt32		G_SysTime;									//用timeGetTime() - G_SysTime_Base 取得的值
    static	myUInt32		G_SysTime_Base;								//用程式開啟時 timeGetTime() 取得的值
    static	PKTypeENUM		G_PKType;
	static  int				G_TimeZone;									//Server時區
	static  int				G_MaxVocCount;								//最多職業數量

    static  StaticString< _MAX_CREATETIME_SIZE_> G_NowStr;  			//目前時間字串
	static  myUInt32		G_Now;
	static	float			G_Now_Float;
	static	int				G_Day;

    //種族仇恨表
    static  int				HateTable[_MAX_RACE_COUNT_][_MAX_RACE_COUNT_];

	static float			ArmorArg[3][EM_ArmorPos_MaxCount][EM_Armor_MaxCount];		//裝備能力參數
	static int				BaseMagicList[ EM_BaseMagic_MaxCount ];									   

	static vector<string>	ZoneChannel;

	static int				AddLv_byRare[ 10 ];

//	static vector<EqRefinePowerStruct> EqRefineTable; 

	static CampStatuteClass	Camp;						//陣營

	static vector<int>		RefineExpTable;				//煉製的經驗值表
	static vector<int>		JobExpTable;				//經驗值表
	static vector<int>		SkillExpTable;				//技能經驗值表
	static vector<int>		GatherExpTable;				//採集經驗值表
	static vector<int>		PlantExpTable;				//種植經驗值表
	static vector<float>	PlantEffectPointTable;		//種植肥料濃度差影響健康
	static vector<int>		PlotExpTable;				//劇情可獲得經驗值
	static vector<int>		PlotMoneyTable;				//劇情可獲得金錢
	static vector<float>	JobExp_LvGrowRateTable;		//經驗成長率
	static vector<int>		JobSkillExpTable;			//職業經驗值表
	static vector<int>		StandardCostTable;			//
	static vector<int>		HouseExpArgTable;			//
	static vector<float>	MPCostPowerRate;			//每個PowerLv所需要MP
	static vector<int>		PetExpTable;
//	static vector<int>		PetLearnMagicCostTable;
	static vector<int>		PetLifeSkillTable;

	static vector< LvDissolutionTable > DissolutionTable;
	static vector< ComboTable> ComboInfo;
	static vector< int >	LifeSkillLearnKey[ EM_SkillValueType_MaxCount ];
	static map< int , vector< ItemCombineStruct > >		ItemCombineList;
	static int				ItemCombineListExGroupID;
	static map< int , map< int , vector< ItemCombineStruct > > > ItemCombineListEx;

	static bool				G_IsPvE;					//pk 模式
	//-----------------------------------------------------------------------------------------
	//所有職業 與 種族
	//----------------------------------------------------------------------------------------
	static char*			RaceShortStr[32];
	static char*			RaceStr[32];
	static char*			VocShortStr[32];
	static char*			VocStr[32];
	static int				SysDTime;		//系統時間差
	//-----------------------------------------------------------------------------------------
	//全區設定
	//----------------------------------------------------------------------------------------
	static GlobalServerDBInfoStruct	GlobalSetting;
	static bool				IsDisablePVPRule;
	static bool				IsDisablePVPRule_Temp;
	static bool				IsDisableMagicRebound;			//
	//----------------------------------------------------------------------------------------
	//區域金錢消耗資訊
	//----------------------------------------------------------------------------------------
	static int				MoneyIn;
	static int				MoneyOut;
	static int				AccountMoneyIn;
	static int				AccountMoneyOut;
	//----------------------------------------------------------------------------------------
	//修裝 價錢比例
	//----------------------------------------------------------------------------------------
	static float			FixArmorRate[ EM_Armor_MaxCount ];
	
	//最後一次處理失敗的訊息
	static RoleErrorMsgENUM		LastProcErr;

	static int					LastLockMoneySpentPlayerDBID;
	static int					LastLockMoneySpent;
    static OnAttackInfoStruct	LastAttackInfo;

	static vector<WeekZoneStruct>	WeekInstances;	
	static int						WeekInstancesDay;

	static map< int,PhantomRankTableStruct >		   PhantomRank;
	static map< int,map < int,PhantomLvTableStruct > > PhantomLv;
	static map< INT64,int >							   PhantomSkill;	//key = 大id + 小id * 0x100000000
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