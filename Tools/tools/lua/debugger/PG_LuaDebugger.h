#pragma once
#ifndef	__PG_LUA_DEBUGGER_H__
#define __PG_LUA_DEBUGGER_H__
#include <memory.h>

#define LD_MAX_PATH				260
#define MAX_LD_NAME_WHAT_LENGTH	32
#define MAX_LD_WHAT_LENGTH		32
#define MAX_LD_NAME_LENGTH		64
#define MAX_LD_VAL_NAME_LENGTH	128

#define safe_strcopy(dest, src) {strncpy(dest, src, sizeof(dest)); dest[sizeof(dest) - 1] = 0;}

enum LuaDebuggerPacketType
{
	EM_LD_PG_BASE									= 0,			//default packet

	EM_LD_PG_DCtoDA_INIT_INFO						= 1000,	

	EM_LD_PG_DCtoDA_LOCK							= 1100,	
	EM_LD_PG_DCtoDA_UNLOCK							,

	EM_LD_PG_DCtoDA_ADD_BP							= 1200,
	EM_LD_PG_DCtoDA_REMOVE_BP						,
	EM_LD_PG_DCtoDA_ENABLE_BP						,
	EM_LD_PG_DCtoDA_DISABLE_BP						,
	EM_LD_PG_DCtoDA_SET_BP_FILTER_GUID				,
	EM_LD_PG_DCtoDA_SET_BP_FILTER_ORGOBJID			,

	EM_LD_PG_DCtoDA_START_DEBUGGING					= 1300,
	EM_LD_PG_DCtoDA_STOP_DEBUGGING					,
	EM_LD_PG_DCtoDA_RUN								,
	EM_LD_PG_DCtoDA_SETP_INTO						,
	EM_LD_PG_DCtoDA_SETP_OVER						,

	EM_LD_PG_DCtoDA_GET_GLOBAL_VALUE				= 1400,
	EM_LD_PG_DCtoDA_REQUEST_LUA_FILE				,

	EM_LD_PG_DCtoDA_REQUEST_ZONE_INFO				= 1500,

	EM_LD_PG_DAtoLD_LOCK							= 2000,	
	EM_LD_PG_DAtoLD_UNLOCK							,

	EM_LD_PG_DAtoLD_ADD_BP							= 2100,
	EM_LD_PG_DAtoLD_REMOVE_BP						,
	EM_LD_PG_DAtoLD_ENABLE_BP						,
	EM_LD_PG_DAtoLD_DISABLE_BP						,
	EM_LD_PG_DAtoLD_SET_BP_FILTER_GUID				,
	EM_LD_PG_DAtoLD_SET_BP_FILTER_ORGOBJID			,

	EM_LD_PG_DAtoLD_START_DEBUGGING					= 2200,
	EM_LD_PG_DAtoLD_STOP_DEBUGGING					,
	EM_LD_PG_DAtoLD_RUN								,
	EM_LD_PG_DAtoLD_SETP_INTO						,
	EM_LD_PG_DAtoLD_SETP_OVER						,

	EM_LD_PG_DAtoLD_GET_GLOBAL_VALUE				= 2300,
	EM_LD_PG_DAtoLD_REQUEST_LUA_FILE				,

	EM_LD_PG_LDtoDA_INIT_INFO						= 3000,

	EM_LD_PG_LDtoDA_LOCK_RESULT						= 3100,
	EM_LD_PG_LDtoDA_UNLOCK_RESULT					,

	EM_LD_PG_LDtoDA_ADD_BP_RESULT					= 3200,
	EM_LD_PG_LDtoDA_REMOVE_BP_RESULT				,
	EM_LD_PG_LDtoDA_ENABLE_BP_RESULT				,
	EM_LD_PG_LDtoDA_DISABLE_BP_RESULT				,
	EM_LD_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT		,
	EM_LD_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT	,

	EM_LD_PG_LDtoDA_START_DEBUGGING_RESULT			= 3300,
	EM_LD_PG_LDtoDA_STOP_DEBUGGING_RESULT			,
	EM_LD_PG_LDtoDA_RUN_RESULT						,
	EM_LD_PG_LDtoDA_SETP_INTO_RESULT				,
	EM_LD_PG_LDtoDA_SETP_OVER_RESULT				,

	EM_LD_PG_LDtoDA_BREAK_AT						= 3400,

	EM_LD_PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE			= 3500,
	EM_LD_PG_LDtoDA_LOCAL_VALUE						,
	EM_LD_PG_LDtoDA_END_SEND_LOCAL_VALUE			,
	EM_LD_PG_LDtoDA_BEGIN_SEND_UP_VALUE				,
	EM_LD_PG_LDtoDA_UP_VALUE						,
	EM_LD_PG_LDtoDA_END_SEND_UP_VALUE				,
	EM_LD_PG_LDtoDA_GLOBAL_VALUE					,
	EM_LD_PG_LDtoDA_BEGIN_SEND_LUA_FILE				,
	EM_LD_PG_LDtoDA_END_SEND_LUA_FILE				,
	EM_LD_PG_LDtoDA_BEGIN_RELOAD_PLOT				,
	EM_LD_PG_LDtoDA_END_RELOAD_PLOT					,
	EM_LD_PG_LDtoDA_BEGIN_SEND_CALL_STACK			,
	EM_LD_PG_LDtoDA_CALL_STACK						,
	EM_LD_PG_LDtoDA_END_SEND_CALL_STACK				,

	EM_LD_PG_DAtoDC_LOCK_RESULT						= 4000,
	EM_LD_PG_DAtoDC_UNLOCK_RESULT					,

	EM_LD_PG_DAtoDC_ADD_BP_RESULT					= 4100,
	EM_LD_PG_DAtoDC_REMOVE_BP_RESULT				,
	EM_LD_PG_DAtoDC_ENABLE_BP_RESULT				,
	EM_LD_PG_DAtoDC_DISABLE_BP_RESULT				,
	EM_LD_PG_DAtoDC_SET_BP_FILTER_GUID_RESULT		,
	EM_LD_PG_DAtoDC_SET_BP_FILTER_ORGOBJID_RESULT	,

	EM_LD_PG_DAtoDC_START_DEBUGGING_RESULT			= 4200,
	EM_LD_PG_DAtoDC_STOP_DEBUGGING_RESULT			,
	EM_LD_PG_DAtoDC_RUN_RESULT						,
	EM_LD_PG_DAtoDC_SETP_INTO_RESULT				,
	EM_LD_PG_DAtoDC_SETP_OVER_RESULT				,

	EM_LD_PG_DAtoDC_BREAK_AT						= 4300,

	EM_LD_PG_DAtoDC_BEGIN_SEND_LOCAL_VALUE			= 4400,
	EM_LD_PG_DAtoDC_LOCAL_VALUE						,
	EM_LD_PG_DAtoDC_END_SEND_LOCAL_VALUE			,
	EM_LD_PG_DAtoDC_BEGIN_SEND_UP_VALUE				,
	EM_LD_PG_DAtoDC_UP_VALUE						,
	EM_LD_PG_DAtoDC_END_SEND_UP_VALUE				,
	EM_LD_PG_DAtoDC_GLOBAL_VALUE					,
	EM_LD_PG_DAtoDC_BEGIN_SEND_LUA_FILE				,
	EM_LD_PG_DAtoDC_END_SEND_LUA_FILE				,
	EM_LD_PG_DAtoDC_BEGIN_RELOAD_PLOT				,
	EM_LD_PG_DAtoDC_END_RELOAD_PLOT					,
	EM_LD_PG_DAtoDC_BEGIN_SEND_CALL_STACK			,
	EM_LD_PG_DAtoDC_CALL_STACK						,
	EM_LD_PG_DAtoDC_END_SEND_CALL_STACK				,

	EM_LD_PG_DAtoDC_BEGIN_SEND_ZONE_INFO			= 4500,
	EM_LD_PG_DAtoDC_ZONE_INFO						,
	EM_LD_PG_DAtoDC_END_SEND_ZONE_INFO				,

	EM_LD_PG_LD_DC_FILE_TRANSFER					= 5000,

	EM_LD_PG_FORCE_DWORD							= 0x7FFFFFFF
};

enum LuaDebuggerCommonResult
{
	EM_LD_COMMON_RET_OK				= 1000,
	EM_LD_COMMON_RET_ZONE_LOCKED	,
	EM_LD_COMMON_RET_NO_SUCH_ZONE
};

enum LuaDebuggerStepIntoResult
{
	EM_LD_STEP_INTO_RET_NONE_BLOCKED
};

enum LuaDebuggerStepOverResult
{
	EM_LD_STEP_OVER_RET_NONE_BLOCKED
};

enum LuaDebuggerDataType
{
	EM_LD_TNONE				= -1,
	EM_LD_TNIL				= 0,
	EM_LD_TBOOLEAN			= 1,
	EM_LD_TLIGHTUSERDATA	= 2,
	EM_LD_TNUMBER			= 3,
	EM_LD_TSTRING			= 4,
	EM_LD_TTABLE			= 5,
	EM_LD_TFUNCTION			= 6,
	EM_LD_TUSERDATA			= 7,
	EM_LD_TTHREAD			= 8
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LD_VALUE
{
	int			  iType;
	unsigned long dwDataSize;
	char		  szName[MAX_LD_VAL_NAME_LENGTH];

	union
	{
		int		Boolean;
		double	Number;
		void*	Thread;
		void*	UserData;
		void*	Function;
		int		KVCount;	//for lua table
		char	String[1];
	}Data;

	PG_LD_VALUE()
	{
		memset(this, 0, sizeof(*this));
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LD_STACK_INFO
{
	int	 iStackLevel;
	int	 iLine;
	char szNamewhat[MAX_LD_NAME_WHAT_LENGTH];
	char szWhat[MAX_LD_WHAT_LENGTH];
	char szSource[LD_MAX_PATH];

	PG_LD_STACK_INFO()
	{
		memset(this, 0, sizeof(*this));
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct LD_PG_BASE
{
	int iType;
	LD_PG_BASE()
	{
		iType = EM_LD_PG_BASE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_INIT_INFO : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_DCtoDA_INIT_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_INIT_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_LOCK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_LOCK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_LOCK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_UNLOCK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_UNLOCK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_UNLOCK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_ADD_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;
	int  iZoneID;	

	PG_DCtoDA_ADD_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_ADD_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_REMOVE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];	
	int	 iLine;
	int  iZoneID;

	PG_DCtoDA_REMOVE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_REMOVE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_ENABLE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];	
	int	 iLine;
	int  iZoneID;

	PG_DCtoDA_ENABLE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_ENABLE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_DISABLE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];	
	int	 iLine;
	int  iZoneID;

	PG_DCtoDA_DISABLE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_DISABLE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_SET_BP_FILTER_GUID : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];	
	int	 iLine;
	int  iGUID;
	int  iZoneID;

	PG_DCtoDA_SET_BP_FILTER_GUID()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_SET_BP_FILTER_GUID;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_SET_BP_FILTER_ORGOBJID : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];	
	int	 iLine;
	int  iOrgObjID;
	int  iZoneID;

	PG_DCtoDA_SET_BP_FILTER_ORGOBJID()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_SET_BP_FILTER_ORGOBJID;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_START_DEBUGGING : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_START_DEBUGGING()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_START_DEBUGGING;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_STOP_DEBUGGING : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_STOP_DEBUGGING()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_STOP_DEBUGGING;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_RUN : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_RUN()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_RUN;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_SETP_INTO : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_SETP_INTO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_SETP_INTO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_SETP_OVER : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_SETP_OVER()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_SETP_OVER;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_GET_GLOBAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szVarName[MAX_LD_VAL_NAME_LENGTH];
	int  iZoneID;

	PG_DCtoDA_GET_GLOBAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_GET_GLOBAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_REQUEST_LUA_FILE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLuaPath[LD_MAX_PATH];
	int  iZoneID;

	PG_DCtoDA_REQUEST_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_REQUEST_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DCtoDA_REQUEST_ZONE_INFO : public LD_PG_BASE
{
	PG_DCtoDA_REQUEST_ZONE_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DCtoDA_REQUEST_ZONE_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_LOCK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_LOCK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_LOCK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_UNLOCK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_UNLOCK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_UNLOCK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_ADD_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;

	PG_DAtoLD_ADD_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_ADD_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_REMOVE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;

	PG_DAtoLD_REMOVE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_REMOVE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_ENABLE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;

	PG_DAtoLD_ENABLE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_ENABLE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_DISABLE_BP : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;

	PG_DAtoLD_DISABLE_BP()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_DISABLE_BP;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_SET_BP_FILTER_GUID : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;
	int  iGUID;

	PG_DAtoLD_SET_BP_FILTER_GUID()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_SET_BP_FILTER_GUID;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_SET_BP_FILTER_ORGOBJID : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;
	int  iOrgObjID;

	PG_DAtoLD_SET_BP_FILTER_ORGOBJID()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_SET_BP_FILTER_ORGOBJID;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_START_DEBUGGING : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_START_DEBUGGING()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_START_DEBUGGING;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_STOP_DEBUGGING : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_STOP_DEBUGGING()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_STOP_DEBUGGING;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_RUN : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_RUN()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_RUN;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_SETP_INTO : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_SETP_INTO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_SETP_INTO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_SETP_OVER : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_DAtoLD_SETP_OVER()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_SETP_OVER;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_GET_GLOBAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szVarName[MAX_LD_VAL_NAME_LENGTH];

	PG_DAtoLD_GET_GLOBAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_GET_GLOBAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoLD_REQUEST_LUA_FILE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLuaPath[LD_MAX_PATH];

	PG_DAtoLD_REQUEST_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoLD_REQUEST_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_INIT_INFO : public LD_PG_BASE
{
	int iZoneID;

	PG_LDtoDA_INIT_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_INIT_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_LOCK_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int  iResult;
	bool bLoadFdbLuaScript;
	bool bLoadTxtLuaScript;

	PG_LDtoDA_LOCK_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_LOCK_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_UNLOCK_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_UNLOCK_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_UNLOCK_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_ADD_BP_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_ADD_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_ADD_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_REMOVE_BP_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_REMOVE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_REMOVE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_ENABLE_BP_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_ENABLE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_ENABLE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_DISABLE_BP_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_DISABLE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_DISABLE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_SET_BP_FILTER_GUID_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_SET_BP_FILTER_GUID_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_SET_BP_FILTER_GUID_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_SET_BP_FILTER_ORGOBJID_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_START_DEBUGGING_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_START_DEBUGGING_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_START_DEBUGGING_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_STOP_DEBUGGING_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_STOP_DEBUGGING_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_STOP_DEBUGGING_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_RUN_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_RUN_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_RUN_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_SETP_INTO_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_SETP_INTO_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_SETP_INTO_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_SETP_OVER_RESULT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;

	PG_LDtoDA_SETP_OVER_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_SETP_OVER_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BREAK_AT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	char szFileName[LD_MAX_PATH];
	int	 iLine;

	PG_LDtoDA_BREAK_AT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BREAK_AT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BEGIN_SEND_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_LOCAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_END_SEND_LOCAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_END_SEND_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_END_SEND_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BEGIN_SEND_UP_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_BEGIN_SEND_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BEGIN_SEND_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_UP_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_END_SEND_UP_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_END_SEND_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_END_SEND_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_GLOBAL_VALUE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];

	PG_LDtoDA_GLOBAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_GLOBAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BEGIN_SEND_LUA_FILE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_BEGIN_SEND_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BEGIN_SEND_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_END_SEND_LUA_FILE : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_END_SEND_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_END_SEND_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BEGIN_RELOAD_PLOT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_BEGIN_RELOAD_PLOT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BEGIN_RELOAD_PLOT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_END_RELOAD_PLOT : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_END_RELOAD_PLOT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_END_RELOAD_PLOT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_BEGIN_SEND_CALL_STACK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_BEGIN_SEND_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_BEGIN_SEND_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_CALL_STACK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LD_STACK_INFO Info;

	PG_LDtoDA_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LDtoDA_END_SEND_CALL_STACK : public LD_PG_BASE
{
	char szWho[MAX_LD_NAME_LENGTH];
	PG_LDtoDA_END_SEND_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LDtoDA_END_SEND_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_LOCK_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int  iResult;
	int  iZoneID;
	bool bLoadFdbLuaScript;
	bool bLoadTxtLuaScript;

	PG_DAtoDC_LOCK_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_LOCK_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_UNLOCK_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_UNLOCK_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_UNLOCK_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_ADD_BP_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_ADD_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_ADD_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_REMOVE_BP_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_REMOVE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_REMOVE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_ENABLE_BP_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_ENABLE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_ENABLE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_DISABLE_BP_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_DISABLE_BP_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_DISABLE_BP_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_SET_BP_FILTER_GUID_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_SET_BP_FILTER_GUID_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_SET_BP_FILTER_GUID_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_SET_BP_FILTER_ORGOBJID_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_SET_BP_FILTER_ORGOBJID_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_SET_BP_FILTER_ORGOBJID_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_START_DEBUGGING_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_START_DEBUGGING_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_START_DEBUGGING_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_STOP_DEBUGGING_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_STOP_DEBUGGING_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_STOP_DEBUGGING_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_RUN_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_RUN_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_RUN_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_SETP_INTO_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_SETP_INTO_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_SETP_INTO_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_SETP_OVER_RESULT : public LD_PG_BASE
{
	char szLocker[MAX_LD_NAME_LENGTH];
	int iResult;
	int iZoneID;

	PG_DAtoDC_SETP_OVER_RESULT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_SETP_OVER_RESULT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BREAK_AT : public LD_PG_BASE
{
	char szFileName[LD_MAX_PATH];
	int iLine;
	int iZoneID;

	PG_DAtoDC_BREAK_AT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BREAK_AT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_SEND_LOCAL_VALUE : public LD_PG_BASE
{
	int iZoneID;
	PG_DAtoDC_BEGIN_SEND_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_SEND_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_LOCAL_VALUE : public LD_PG_BASE
{	
	int iZoneID;

	PG_DAtoDC_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_SEND_LOCAL_VALUE : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_END_SEND_LOCAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_SEND_LOCAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_SEND_UP_VALUE : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_BEGIN_SEND_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_SEND_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_UP_VALUE : public LD_PG_BASE
{	
	int iZoneID;
	
	PG_DAtoDC_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_SEND_UP_VALUE : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_END_SEND_UP_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_SEND_UP_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_GLOBAL_VALUE : public LD_PG_BASE
{	
	int iZoneID;

	PG_DAtoDC_GLOBAL_VALUE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_GLOBAL_VALUE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_SEND_LUA_FILE : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_BEGIN_SEND_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_SEND_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_SEND_LUA_FILE : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_END_SEND_LUA_FILE()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_SEND_LUA_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_RELOAD_PLOT : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_BEGIN_RELOAD_PLOT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_RELOAD_PLOT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_RELOAD_PLOT : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_END_RELOAD_PLOT()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_RELOAD_PLOT;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_SEND_CALL_STACK : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_BEGIN_SEND_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_SEND_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_CALL_STACK : public LD_PG_BASE
{
	int				 iZoneID;
	PG_LD_STACK_INFO Info;

	PG_DAtoDC_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_SEND_CALL_STACK : public LD_PG_BASE
{
	int iZoneID;

	PG_DAtoDC_END_SEND_CALL_STACK()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_SEND_CALL_STACK;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_BEGIN_SEND_ZONE_INFO : public LD_PG_BASE
{
	PG_DAtoDC_BEGIN_SEND_ZONE_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_BEGIN_SEND_ZONE_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_ZONE_INFO : public LD_PG_BASE
{
	int  iZoneID;
	char szLocker[MAX_LD_NAME_LENGTH];

	PG_DAtoDC_ZONE_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_ZONE_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_DAtoDC_END_SEND_ZONE_INFO : public LD_PG_BASE
{
	PG_DAtoDC_END_SEND_ZONE_INFO()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_DAtoDC_END_SEND_ZONE_INFO;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_LD_DC_FILE_TRANSFER : public LD_PG_BASE
{
	unsigned long dwDataSize;

	PG_LD_DC_FILE_TRANSFER()
	{
		memset(this, 0, sizeof(*this));
		iType = EM_LD_PG_LD_DC_FILE_TRANSFER;
	}
};


#endif //__PG_H__