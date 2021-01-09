#include "RoleDataEx.h"
//------------------------------------------------------------------------------------------------------------------------
int			                           	RoleDataEx::G_ZoneID		= 0;	//區域id(靜態全域)
int			                           	RoleDataEx::G_Clock			= 0;			
myUInt32		                       	RoleDataEx::G_SysTime		= 0;				
myUInt32		                       	RoleDataEx::G_SysTime_Base	= 0;		
PKTypeENUM         	                   	RoleDataEx::G_PKType		= EM_PK_Normal;
StaticString< _MAX_CREATETIME_SIZE_>   	RoleDataEx::G_NowStr;
myUInt32								RoleDataEx::G_Now;
float									RoleDataEx::G_Now_Float;
int										RoleDataEx::G_Day;
bool									RoleDataEx::G_IsPvE			= false;
int										RoleDataEx::G_TimeZone		= 0;	//Server時區
int										RoleDataEx::G_MaxVocCount	= 16;
//------------------------------------------------------------------------------------------------------------------------
//種族仇恨表
int		RoleDataEx::HateTable[_MAX_RACE_COUNT_][_MAX_RACE_COUNT_];
//int     RoleDataEx::RoleExp[ _MAX_LEVEL_ ][ _MAX_VOCATION_COUNT_ ];
//float	RoleDataEx::SkillValueExp[ _MAX_LEVEL_ ];						//每等級每一點所加的 技能數值
int		RoleDataEx::BaseMagicList[ EM_BaseMagic_MaxCount ];

float	RoleDataEx::ArmorArg[3][EM_ArmorPos_MaxCount][EM_Armor_MaxCount];	//裝備能力參數
int		RoleDataEx::AddLv_byRare[ 10 ] = { 0 , 2 , 5 , 9 , 12 , 15 , 20 , 24 , 28 , 35 };

CampStatuteClass	RoleDataEx::Camp;							//陣營

//vector<EqRefinePowerStruct> RoleDataEx::EqRefineTable; 
//int		RoleDataEx::RefineExpTable[_MAX_SKILL_LEVE_];			//煉製的經驗值表
vector< int >	RoleDataEx::LifeSkillLearnKey[ EM_SkillValueType_MaxCount ];
//------------------------------------------------------------------------------------------------------------------------
char*	RoleDataEx::RaceShortStr[32] = { "人類" , "精靈" , "歐比" ,"雪米" , "生物" , "不死" , "亞人" , "精怪" , "元素" , "機關" , "魔獸" , "龍族" , "惡魔" , "神祇" };
char*	RoleDataEx::RaceStr[32]		 = { "人類" , "精靈" , "歐比" ,"雪米" , "生物" , "不死" , "亞人" , "精怪" , "元素" , "機關" , "魔獸" , "龍族" , "惡魔" , "神祇" };
char*	RoleDataEx::VocShortStr[32]  = { "GM" , "戰士","遊俠","盜賊","法師","祭司","騎士","言靈使","德魯依","暗騎士","吟遊師人","龍騎士", "氣鬥士","塔羅法師","死靈法師","馴獸使","賭徒","青魔法師","魔法使"};
char*	RoleDataEx::VocStr[32]		 = { "GM" , "戰士","遊俠","盜賊","法師","祭司","騎士","言靈使","德魯依","暗騎士","吟遊師人","龍騎士", "氣鬥士","塔羅法師","死靈法師","馴獸使","賭徒","青魔法師","魔法使"};
//------------------------------------------------------------------------------------------------------------------------
vector<string>	RoleDataEx::ZoneChannel;
vector<int>		RoleDataEx::RefineExpTable;				//煉製的經驗值表
vector<int>		RoleDataEx::JobExpTable;				//經驗值表
vector<int>		RoleDataEx::SkillExpTable;				//技能經驗值表
vector<int>		RoleDataEx::GatherExpTable;				//採集經驗值表
vector<int>		RoleDataEx::PlantExpTable;				//種植經驗值表
vector<float>	RoleDataEx::PlantEffectPointTable;		//種植經驗值表
vector<int>		RoleDataEx::PlotExpTable;				//劇情可獲得經驗值
vector<int>		RoleDataEx::PlotMoneyTable;				//劇情可獲得金錢
vector<float>	RoleDataEx::JobExp_LvGrowRateTable;		//經驗成長率
vector<int>		RoleDataEx::JobSkillExpTable;
vector<int>		RoleDataEx::StandardCostTable;
vector<int>		RoleDataEx::HouseExpArgTable;			//
vector<float>	RoleDataEx::MPCostPowerRate;			//每個PowerLv所需要MP
vector<int>		RoleDataEx::PetExpTable;
//vector<int>		RoleDataEx::PetLearnMagicCostTable;
vector<int>		RoleDataEx::PetLifeSkillTable;
vector< LvDissolutionTable >				RoleDataEx::DissolutionTable;
vector< ComboTable>							RoleDataEx::ComboInfo;
map< int , vector< ItemCombineStruct > >	RoleDataEx::ItemCombineList;
map< int , map< int , vector< ItemCombineStruct > > > RoleDataEx::ItemCombineListEx;
int				RoleDataEx::ItemCombineListExGroupID = -1;
int				RoleDataEx::SysDTime = 0;				//系統時間差

GlobalServerDBInfoStruct	RoleDataEx::GlobalSetting;
bool						RoleDataEx::IsDisablePVPRule		= false;
bool						RoleDataEx::IsDisablePVPRule_Temp	= false;
bool						RoleDataEx::IsDisableMagicRebound	= false;			//
//----------------------------------------------------------------------------------------
//區域金錢消耗資訊
//----------------------------------------------------------------------------------------
int				RoleDataEx::MoneyIn			= 0;
int				RoleDataEx::MoneyOut		= 0;
int				RoleDataEx::AccountMoneyIn	= 0;
int				RoleDataEx::AccountMoneyOut	= 0;

float			RoleDataEx::FixArmorRate[ EM_Armor_MaxCount ];

RoleErrorMsgENUM	RoleDataEx::LastProcErr;

int					RoleDataEx::LastLockMoneySpentPlayerDBID = 0;
int					RoleDataEx::LastLockMoneySpent = 0;
OnAttackInfoStruct	RoleDataEx::LastAttackInfo;
vector<WeekZoneStruct>	RoleDataEx::WeekInstances;	

map< int,PhantomRankTableStruct >			RoleDataEx::PhantomRank;
map< int,map < int,PhantomLvTableStruct > > RoleDataEx::PhantomLv;
map< INT64,int >							RoleDataEx::PhantomSkill;
map< int,float >							RoleDataEx::PhantomAbiArg;	