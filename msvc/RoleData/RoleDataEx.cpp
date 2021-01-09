#include "RoleDataEx.h"
//------------------------------------------------------------------------------------------------------------------------
int			                           	RoleDataEx::G_ZoneID		= 0;	//�ϰ�id(�R�A����)
int			                           	RoleDataEx::G_Clock			= 0;			
myUInt32		                       	RoleDataEx::G_SysTime		= 0;				
myUInt32		                       	RoleDataEx::G_SysTime_Base	= 0;		
PKTypeENUM         	                   	RoleDataEx::G_PKType		= EM_PK_Normal;
StaticString< _MAX_CREATETIME_SIZE_>   	RoleDataEx::G_NowStr;
myUInt32								RoleDataEx::G_Now;
float									RoleDataEx::G_Now_Float;
int										RoleDataEx::G_Day;
bool									RoleDataEx::G_IsPvE			= false;
int										RoleDataEx::G_TimeZone		= 0;	//Server�ɰ�
int										RoleDataEx::G_MaxVocCount	= 16;
//------------------------------------------------------------------------------------------------------------------------
//�رڤ����
int		RoleDataEx::HateTable[_MAX_RACE_COUNT_][_MAX_RACE_COUNT_];
//int     RoleDataEx::RoleExp[ _MAX_LEVEL_ ][ _MAX_VOCATION_COUNT_ ];
//float	RoleDataEx::SkillValueExp[ _MAX_LEVEL_ ];						//�C���ŨC�@�I�ҥ[�� �ޯ�ƭ�
int		RoleDataEx::BaseMagicList[ EM_BaseMagic_MaxCount ];

float	RoleDataEx::ArmorArg[3][EM_ArmorPos_MaxCount][EM_Armor_MaxCount];	//�˳Ư�O�Ѽ�
int		RoleDataEx::AddLv_byRare[ 10 ] = { 0 , 2 , 5 , 9 , 12 , 15 , 20 , 24 , 28 , 35 };

CampStatuteClass	RoleDataEx::Camp;							//�}��

//vector<EqRefinePowerStruct> RoleDataEx::EqRefineTable; 
//int		RoleDataEx::RefineExpTable[_MAX_SKILL_LEVE_];			//�һs���g��Ȫ�
vector< int >	RoleDataEx::LifeSkillLearnKey[ EM_SkillValueType_MaxCount ];
//------------------------------------------------------------------------------------------------------------------------
char*	RoleDataEx::RaceShortStr[32] = { "�H��" , "���F" , "�ڤ�" ,"����" , "�ͪ�" , "����" , "�ȤH" , "���" , "����" , "����" , "�]�~" , "�s��" , "�c�]" , "����" };
char*	RoleDataEx::RaceStr[32]		 = { "�H��" , "���F" , "�ڤ�" ,"����" , "�ͪ�" , "����" , "�ȤH" , "���" , "����" , "����" , "�]�~" , "�s��" , "�c�]" , "����" };
char*	RoleDataEx::VocShortStr[32]  = { "GM" , "�Ԥh","�C�L","�s��","�k�v","���q","�M�h","���F��","�w�|��","�t�M�h","�u�C�v�H","�s�M�h", "�𰫤h","��ù�k�v","���F�k�v","���~��","��{","�C�]�k�v","�]�k��"};
char*	RoleDataEx::VocStr[32]		 = { "GM" , "�Ԥh","�C�L","�s��","�k�v","���q","�M�h","���F��","�w�|��","�t�M�h","�u�C�v�H","�s�M�h", "�𰫤h","��ù�k�v","���F�k�v","���~��","��{","�C�]�k�v","�]�k��"};
//------------------------------------------------------------------------------------------------------------------------
vector<string>	RoleDataEx::ZoneChannel;
vector<int>		RoleDataEx::RefineExpTable;				//�һs���g��Ȫ�
vector<int>		RoleDataEx::JobExpTable;				//�g��Ȫ�
vector<int>		RoleDataEx::SkillExpTable;				//�ޯ�g��Ȫ�
vector<int>		RoleDataEx::GatherExpTable;				//�Ķ��g��Ȫ�
vector<int>		RoleDataEx::PlantExpTable;				//�شӸg��Ȫ�
vector<float>	RoleDataEx::PlantEffectPointTable;		//�شӸg��Ȫ�
vector<int>		RoleDataEx::PlotExpTable;				//�@���i��o�g���
vector<int>		RoleDataEx::PlotMoneyTable;				//�@���i��o����
vector<float>	RoleDataEx::JobExp_LvGrowRateTable;		//�g�禨���v
vector<int>		RoleDataEx::JobSkillExpTable;
vector<int>		RoleDataEx::StandardCostTable;
vector<int>		RoleDataEx::HouseExpArgTable;			//
vector<float>	RoleDataEx::MPCostPowerRate;			//�C��PowerLv�һݭnMP
vector<int>		RoleDataEx::PetExpTable;
//vector<int>		RoleDataEx::PetLearnMagicCostTable;
vector<int>		RoleDataEx::PetLifeSkillTable;
vector< LvDissolutionTable >				RoleDataEx::DissolutionTable;
vector< ComboTable>							RoleDataEx::ComboInfo;
map< int , vector< ItemCombineStruct > >	RoleDataEx::ItemCombineList;
map< int , map< int , vector< ItemCombineStruct > > > RoleDataEx::ItemCombineListEx;
int				RoleDataEx::ItemCombineListExGroupID = -1;
int				RoleDataEx::SysDTime = 0;				//�t�ήɶ��t

GlobalServerDBInfoStruct	RoleDataEx::GlobalSetting;
bool						RoleDataEx::IsDisablePVPRule		= false;
bool						RoleDataEx::IsDisablePVPRule_Temp	= false;
bool						RoleDataEx::IsDisableMagicRebound	= false;			//
//----------------------------------------------------------------------------------------
//�ϰ�������Ӹ�T
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