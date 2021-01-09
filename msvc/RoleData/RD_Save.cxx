#include "RoleDataEx.h"
void RoleDataEx::SaveDB_Item( )
{

}
void RoleDataEx::SaveDB_Body( )
{

}
void RoleDataEx::SaveDB_Bank( )
{

}
void RoleDataEx::SaveDB_All( )
{
	if( IsPlayer() == false )
		return;
    Net_SavePlayer( 0 , sizeof( PlayerRoleData ) , 60 * 1000 * 30 );
}

void    RoleDataEx::SaveDB_All_Now( )
{
	if( IsPlayer() == false )
		return;
	Net_SavePlayer( 0 , sizeof( PlayerRoleData ) , 0 );
}

void	RoleDataEx::SaveDB_Test( )
{
	if( IsPlayer() == false )
		return;
	Net_SavePlayer( 0 , 0 ,  60 * 1000 * 30 );
}

void RoleDataEx::SaveDB_Pos( )
{

}

void RoleDataEx::SaveDB_DelTime()   //把時間減掉
{
	if( SelfData.LiveTime != -1 )
	{
		SelfData.LiveTime -= G_SysTime;		
		if( SelfData.LiveTime < 0 ) 
			SelfData.LiveTime = 0;
	}

/*
    for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
    {
        PlayerBaseData->Body.Item[i].Coldown -= G_SysTime;
        if( PlayerBaseData->Body.Item[i].Coldown < 0 )
            PlayerBaseData->Body.Item[i].Coldown = 0;
    }

    for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )
    {
        PlayerBaseData->Bank.Item[i].Coldown -= G_SysTime;
        if( PlayerBaseData->Bank.Item[i].Coldown < 0 )
            PlayerBaseData->Bank.Item[i].Coldown = 0;
    }

    for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
    {
        BaseData.EQ.Item[i].Coldown -= G_SysTime;
        if( BaseData.EQ.Item[i].Coldown < 0 )
            BaseData.EQ.Item[i].Coldown = 0;
    }    

    for( int i = 0 ; i < _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ ; i++ )
    {
        PlayerBaseData->Skill.AllMagic[i].Coldown -= G_SysTime;
        if( PlayerBaseData->Skill.AllMagic[i].Coldown < 0 )
            PlayerBaseData->Skill.AllMagic[i].Coldown = 0;
    }

	for( int i = 0 ; i < _MAX_SHARE_COLDWON_COUNT_ ; i++ )
	{
		PlayerBaseData->ShareColdown[i] -= G_SysTime;
		if( PlayerBaseData->ShareColdown[i] <0 )
			PlayerBaseData->ShareColdown[i] = 0;
	}
	*/
}
void RoleDataEx::SaveDB_AddTime()   //把時間加回
{

	if( SelfData.LiveTime != -1 )
	{
		SelfData.LiveTime += G_SysTime;		
	}	
/*
    for( int i = 0 ; i < PlayerBaseData->Body.Count ; i++ )
    {
        PlayerBaseData->Body.Item[i].Coldown += G_SysTime;
    }

    for( int i = 0 ; i < PlayerBaseData->Bank.Count ; i++ )
    {
        PlayerBaseData->Bank.Item[i].Coldown +=G_SysTime;
    }

    for( int i = 0 ; i < EM_EQWearPos_MaxCount ; i++ )
    {
        BaseData.EQ.Item[i].Coldown += G_SysTime;
    }    

    for( int i = 0 ; i < _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ ; i++ )
    {
        PlayerBaseData->Skill.AllMagic[i].Coldown += G_SysTime;
    }

	for( int i = 0 ; i < _MAX_SHARE_COLDWON_COUNT_ ; i++ )
	{
		PlayerBaseData->ShareColdown[i] += G_SysTime;
	}
	*/
}