
#pragma once

#include "luastack.h"

void    Empty_SendLuaErrorInfo( int, int, const char*  , const char*  ) {}

LuaOutputDebugFunction g_pfunLuaDebugOut = Empty_SendLuaErrorInfo;
//###############################################################################################################
//加入檢查型別
//###############################################################################################################
//LuaStackOutputDebugFunction	g_pfunLuaErrorOut = NULL;
bool CheckLuaArg_Num( lua_State* L , int Index )
{
    if( lua_isnumber( L , Index ) )
        return true;

//	printf("%s\n",lua_tostring(L,-1));

    lua_Debug trouble_info;
    memset(&trouble_info, 0 , sizeof(lua_Debug));
    int debug_StackNum = lua_gettop (L);
    if(lua_getstack(L,0,&trouble_info) || lua_getstack(L,1,&trouble_info))
        lua_getinfo(L,"Snl",&trouble_info);

	char szMsg[ 8192 ];

    if( lua_isnil( L , Index ) )
    {
        sprintf( szMsg, "Lua function(%s), %d arg is null" , trouble_info.name , Index );
		g_pfunLuaDebugOut( 0,0,trouble_info.name , szMsg );
    }
    else if( lua_isstring( L , Index ) )
    {
        sprintf( szMsg, "Lua function(%s) %d arg type error('%s') it's not number" , trouble_info.name , Index, lua_tostring( L , Index ) );
		g_pfunLuaDebugOut( 0,0,trouble_info.name,szMsg );
    }
    else
    {
        sprintf( szMsg, "Lua function(%s), %d arg type error", trouble_info.name , Index );
		g_pfunLuaDebugOut( 0,0, trouble_info.name,szMsg );
    }


	
    sprintf( szMsg, "name:(%s) namewhat:(%s) what:(%s) source:(%s) short:(%s) linedefined:(%d) currentline:(%d)\n",
        trouble_info.name,
        trouble_info.namewhat,
        trouble_info.what,
        trouble_info.source,
        trouble_info.short_src,
        trouble_info.linedefined,
        trouble_info.currentline
        );

	sprintf( szMsg, "CallStack:\n" );


	// Print callstack
	lua_Debug ar;
	int iStackLevel = 0; 
	while (lua_getstack(L, iStackLevel, &ar))
	{
		lua_getinfo(L, "Sln", &ar);
		sprintf( szMsg, "Source = %s, Line = %d", ar.source, ar.currentline );
		iStackLevel++;
	}


	if( g_pfunLuaDebugOut )
	{
		g_pfunLuaDebugOut( 0,0, trouble_info.name,szMsg );
	}
 

    return false; 
}

__int64	StrToInt64( const char* str )
{
	__int64 ret = 0;
	for( int i = 0 ; str[i] != 0 ; i++ )
	{
		ret *= 16;
		if( str[i] <= '9' )
			ret += str[i] - '0';
		else if( str[i] <= 'F' )
			ret += (str[i] - 'A' + 10);
		else if( str[i] <= 'f' )
			ret += (str[i] - 'a' + 10);
	}

	return ret;

}

bool CheckLuaArg_Str( lua_State* L , int Index )
{
    if( lua_isstring( L , Index ) )
        return true;

	char szMsg[ 1024 ];

    lua_Debug trouble_info;
    memset(&trouble_info, 0 , sizeof(lua_Debug));
    int debug_StackNum = lua_gettop (L);
    if(lua_getstack(L,0,&trouble_info) || lua_getstack(L,1,&trouble_info))
        lua_getinfo(L,"Snl",&trouble_info);

    if( lua_isnil( L , Index ) )
    {
        sprintf( szMsg, "Lua func(%s) 第%d arg dosent exist" , trouble_info.name , Index );
		g_pfunLuaDebugOut( 0,0,trouble_info.name,szMsg );
    }
    else
    {
        sprintf(szMsg, "Lua func(%s) 第%d arg type error", trouble_info.name , Index );
		g_pfunLuaDebugOut( 0,0,trouble_info.name,szMsg );
    }

    sprintf( szMsg, "name:(%s) namewhat:(%s) what:(%s) source:(%s) short:(%s) linedefined:(%d) currentline:(%d)\n",
        trouble_info.name,
        trouble_info.namewhat,
        trouble_info.what,
        trouble_info.source,
        trouble_info.short_src,
        trouble_info.linedefined,
        trouble_info.currentline
        );

	if( g_pfunLuaDebugOut )
	{
		g_pfunLuaDebugOut( 0,0,trouble_info.name,szMsg );
	}

    return false; 
}


void	SetLuaDebugOutput( LuaOutputDebugFunction pfun )
{ 
	g_pfunLuaDebugOut = pfun; 
}