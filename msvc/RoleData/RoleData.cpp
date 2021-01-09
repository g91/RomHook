#include "RoleData.h"
//-------------------------------------------------------------------------------------
PlayerSelfRoleData RoleData::gPlayerSelfData;
//PlayerBaseRoleData RoleData::gPlayerBaseData;
PlayerTempRoleData RoleData::gPlayerTempData;
//-------------------------------------------------------------------------------------
//		SelfData
//-------------------------------------------------------------------------------------
void	SelfRoleData::Init()
{
	memset( this , 0 , sizeof(*this) );
	LiveTime = -1;
}
//-------------------------------------------------------------------------------------
//		BaseData
//-------------------------------------------------------------------------------------
void	BaseRoleData::Init()
{
	memset( this , 0 , sizeof(*this) );
}
//-------------------------------------------------------------------------------------
//		TempData
//-------------------------------------------------------------------------------------
void	TempRoleData::Init()
{
	memset( this , 0 , sizeof(*this) );

    Sys.Init();

	AI.LTargetID	= -1;
	AI.TargetID		= -1;

	Attr.AllZoneState.FindParty = false;

	BoundRadiusX			= 1;
	BoundRadiusY			= 1;
	IdleMotionID			= 0; // ruFUSION_ACTORSTATE_NORMAL;
	CursorType				= 0;

	CrystalID				= 0;
	iWorldID				= 0;

	iLockGUID				= 0;
	iLockTime				= 0;		
	ModelRate				= 1.0f;
//	CastData.Clear();
}
//-------------------------------------------------------------------------------------
RoleData::RoleData()	
{ 
	PlayerSelfData = &gPlayerSelfData;
//	PlayerBaseData = &gPlayerBaseData;
	PlayerTempData = &gPlayerTempData;
    Init(); 
} 
RoleData::~RoleData( )
{

}
//-------------------------------------------------------------------------------------
void	RoleData::Init()
{

    Base.Type			= EM_ObjectClass_None;
    Base.DBID			= -1;							//資料庫ID
    Base.Account_ID.Clear();							//帳號名稱

    SelfData.Init();
	BaseData.Init();
	TempData.Init();
	DynamicData.Init();

	TempData.Attr.SkillValue	= &TempData.Attr.MaxSkillValue;		//技能資料
	TempData.CliActionID		= 1;

}
//-------------------------------------------------------------------------------------
void RoleData::GlobalInit()
{
	gPlayerSelfData.Init();
//	gPlayerBaseData.Init();
	gPlayerTempData.Init();
}
//-------------------------------------------------------------------------------------

template< class T >
int MakeSerialCode( T& data )
{
	int ret = 0;
	//裝備
	int* ptr = (int*)&data;
	for( int i = 0 ; i < sizeof( T )/4 ; i++ )
	{
		ret = ret ^ ptr[i];
	}
	return ret;
}

int PlayerRoleData::SerialCode( )
{
	if( PlayerBaseData.Body.Money == 0 )
		return 0;
	Base.CreateTime.StrArrange();
	return MakeSerialCode( Base.CreateTime ) ^ 0x6396 ^ PlayerBaseData.Body.Money;
}

int PlayerRoleData::SerialCode1( )
{
	if( PlayerBaseData.Body.Money == 0 )
		return 0;
	Base.Account_ID.StrArrange();
	return MakeSerialCode( Base.Account_ID ) ^ 0x6396 ^ PlayerBaseData.Body.Money;
}


int PlayerRoleData::SerialCode_All( )
{
	int ret = 0x6396;

	ret ^= MakeSerialCode( PlayerBaseData.Body.Item );
	ret ^= MakeSerialCode( PlayerBaseData.Bank.Item );
	ret ^= MakeSerialCode( PlayerBaseData.AbilityList );
	ret ^= MakeSerialCode( PlayerBaseData.Card );
	ret ^= MakeSerialCode( BaseData.EQ );
	ret ^= MakeSerialCode( BaseData.KeyItem );

	return ret;
}
int PlayerRoleData::AccountSerialCode( )
{
	int ret = 0x6396;

	if(		PlayerBaseData.Money_Bonus == 0
		&&	PlayerBaseData.Body.Money_Account == 0 )
		return 0;

	ret ^= MakeSerialCode( Base.Account_ID );
	ret ^= PlayerBaseData.Money_Bonus;
	ret ^= PlayerBaseData.Body.Money_Account;
	return ret;
}
