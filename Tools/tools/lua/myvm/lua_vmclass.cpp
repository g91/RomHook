// LUA_VMClass.cpp: implementation of the LUA_VMClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma	warning (disable:4786)
#pragma warning (disable:4949)
#include <stdio.h>
#include <io.h>
#include "LUA_VMClass.h"
#include "../LuaWrapper/LuaWrap.h"
#include "basefunction/BaseFunction.h"
#include "lua/ldo.h"
#include "../debugger/LuaDebugger.h"

#pragma unmanaged

#define		_Max_Thread_Count_		40
//--------------------------------------------------------------------------------
//PlotRunTimeEvent 靜態資料
//--------------------------------------------------------------------------------
vector<PlotRunTimeEvent*>	PlotRunTimeEvent::_ItemList;
vector<int>					PlotRunTimeEvent::_UnUsed;
bool						PlotRunTimeEvent::_DestroyEvent	= false;	//是否有物件要刪除

#ifdef _LUA_HOOK_ENABLE_
void callhook( lua_State * L, lua_Debug * ar )
{
	printf( "call-hook, event: %d\r\n", ar->event );
	//lua_sethook(pLuaState, rethook, LUA_MASKCALL, 0);
}

void linehook( lua_State * L, lua_Debug * ar )
{
	printf( "line-hook, line: %d\r\n", ar->currentline );
}

void rethook( lua_State * L, lua_Debug * ar )
{
	char buff[255];
	sprintf( buff,"ret-hook, event: %d, line: %d\r\n", ar->event,ar->currentline );
	OutputDebugString(buff);
}

#endif
//lua_sethook(L, NULL, 0, 0); //turn off hooks
//--------------------------------------------------------------------------------
//PlotRunTimeEvent	資料
//--------------------------------------------------------------------------------
PlotRunTimeEvent::PlotRunTimeEvent()
{
	
	if( _UnUsed.size() == 0 )
	{
		_UnUsed.push_back( (int)_ItemList.size() );
		_ItemList.push_back( NULL );
	}
	_ID = _UnUsed.back();
	_UnUsed.pop_back();
	_ItemList[ _ID ]  = this;
	_Destroy = false;
}
PlotRunTimeEvent::~PlotRunTimeEvent()
{
	_ItemList[ _ID ] = NULL;
	_UnUsed.push_back( _ID );
}

void PlotRunTimeEvent::Destroy()
{
	_Destroy		= true;		
	_DestroyEvent	= true;
}
//--------------------------------------------------------------------------------
//定時處理函式
void PlotRunTimeEvent::OnTimeProc()					
{
	if( _DestroyEvent == false )
		return;
	_DestroyEvent = false;


	int					 i;
	PlotRunTimeEvent	*T;
	for( i=0 ; i< (int)_ItemList.size() ; i++ )
	{
		T = _ItemList[i];
		if(		( T == NULL) 
			||  ( T->_Destroy == false ) )
			continue;
		
		delete T;
		_ItemList[i] = NULL;
	}
}
//--------------------------------------------------------------------------------
PlotRunTimeEvent* PlotRunTimeEvent::GetObj( int Id )
{
	if( _ItemList.size() <= (unsigned)Id )
		return NULL;

	return _ItemList[Id];
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
LUA_VMClass::StaticData*        LUA_VMClass::_St = NULL;
unsigned int				    LUA_VMClass::ProcTimes;
//--------------------------------------------------------------------------------
LUA_VMClass::StaticData::StaticData( int _MaxVMCount )
{
	MaxVMCount		= _MaxVMCount;
    VMTime          = 0;
    L_State         = lua_open();    
    ProcReg         = NULL;
    OutputErrorFunc = NULL;
	IsPCall         = false;
	IsRunning		= false;
	IsAllowDebugger = false;
	IsLogPCall		= false;
    UnUsedPlotReg   = NEW RecycleBin<PlotRegStruct>(MaxVMCount);
}

LUA_VMClass::StaticData::~StaticData()
{
    //釋放劇情暫存資料
    if( UnUsedPlotReg != NULL)
    {
        delete UnUsedPlotReg;
        UnUsedPlotReg = NULL;
    }

    //關閉LUA
    if( L_State != NULL)
    {
        //luaL_setgcthreshold( L_State , 0);  //(!)Luky collected garbage
        lua_close( L_State );
        L_State = NULL;
    }

    ExePlot.clear();
    VMTime = 0;
    UnUsed_VM.clear();
    Total_VM.clear();
    Host_VM.clear();
    Total_VMState.clear();

    ProcReg = NULL;		
    All_VMUser.clear();			    
}
//--------------------------------------------------------------------------------
// Lua錯誤回報
//--------------------------------------------------------------------------------
//static void DisplayError(lua_State * L,int errorcode,char* pInfo=NULL);

static char* ErrorCodeToString(int errorcode)
{
    switch(errorcode)
    {
    case LUA_ERRRUN:
        return "LUA_ERRRUN";
    case LUA_ERRFILE:
        return "LUA_ERRFILE";
    case LUA_ERRSYNTAX:
        return "LUA_ERRSYNTAX";
    case LUA_ERRMEM:
        return "LUA_ERRMEM";
    case LUA_ERRERR:
        return "LUA_ERRERR";
    }
    return "Unknown Error";
}

void LUA_VMClass::DisplayError(lua_State * L,int errorcode,char* pInfo)
{
    TCHAR buff[4096];
	PlotRegStruct* T = LUA_VMClass::ProcReg();
	if( T != NULL )
	{
		sprintf( buff, "\r\nerror runing function %s " , T->FuncName );
	}

	sprintf(buff,"%s\r\n%s",buff,lua_tostring(L,-1));
    
	lua_Debug trouble_info;
	ZeroMemory(&trouble_info,sizeof(lua_Debug));
	int debug_StackNum = lua_gettop (L);

	if(lua_getstack(L,0,&trouble_info) || lua_getstack(L,1,&trouble_info))
    //if(lua_getstack(L,0,&trouble_info) )
	{
		lua_getinfo(L,"Snl",&trouble_info);
		sprintf(buff,"%s\nname:(%s) namewhat:(%s) what:(%s) \n short:(%s) \nlinedefined:(%d) currentline:(%d)\n",
			buff,
			trouble_info.name,
			trouble_info.namewhat,
			trouble_info.what,
			//			trouble_info.source,
			trouble_info.short_src,
			trouble_info.linedefined,
			trouble_info.currentline
			);
        
	}
	else
	{
		if(pInfo)
			sprintf(buff,"%s:('%s')",buff,pInfo);

	}

	OutputDebugString( buff );
    printf( buff );
	if( _St->OutputErrorFunc != NULL )
	{
		if( T != NULL )
			_St->OutputErrorFunc( T->OwnerID, T->TargetID, T->FuncName,buff );
		else
			_St->OutputErrorFunc( 0, 0, "",buff);
	}
}

//--------------------------------------------------------------------------------
// VM 記憶體配置處理
//--------------------------------------------------------------------------------
//vm 記憶體配置
int		LUA_VMClass::_NewVM(LUA_VMClass* VMUser)
{
	int MaxThreadCount = 10000;

	if( _St->MaxVMCount < MaxThreadCount )
		MaxThreadCount = _St->MaxVMCount;

	int		i;
 	if(_St->UnUsed_VM.size() == 0)
	{
		if(_St->Total_VMState.size() != 0)
			return -1;

		lua_State* LastVM = _St->L_State; 

		for(i = 0 ;i <= MaxThreadCount /_Max_Thread_Count_ ;i++)
		{
			LastVM = lua_newthread(LastVM);
			_St->Host_VM.push_back(LastVM);
		}

		for(i = 0 ;i < MaxThreadCount ;i++)
		{
			LastVM = lua_newthread(_St->Host_VM[i/_Max_Thread_Count_]);
			_St->Total_VM.push_back(LastVM);
			_St->Total_VMState.push_back(false);
			_St->UnUsed_VM.push_back(i);
		}
	}
	
	{
		int NewID = _St->UnUsed_VM.back();
		_St->UnUsed_VM.pop_back();
		_St->Total_VMState[NewID] = true;

		lua_State* L = _St->Total_VM[NewID];
		_St->VM_UserMapping[L] = VMUser;

		if (_St->IsAllowDebugger == true)
		{
			LuaDebugger::HookLuaThread(L);
		}

		return NewID;
	}

}

//vm 記憶體歸還
bool	LUA_VMClass::_FreeVM(int ID)
{
	//
	if(unsigned(ID) >= _St->Total_VM.size())
		return false;

	if(_St->Total_VMState[ID] != true)
		return false;

	_St->Total_VMState[ID] = false;
	_St->UnUsed_VM.push_back(ID);

	//********************************************************************
	//把lua_state 初始化
	lua_State* L = _St->Total_VM[ID];
	lua_resetstate( L );
	//********************************************************************
	_St->VM_UserMapping[L] = NULL;

	return true;
}

//取得正 lua_State
lua_State*			LUA_VMClass::_GetLua_State(int ID)
{
	if(unsigned(ID) >= _St->Total_VM.size())
		return NULL;

	if(_St->Total_VMState[ID] != true)
		return NULL;

	return _St->Total_VM[ID];
}
//-----------------------------------------------------------------------
//預先配置PlotReg的記憶體 資料管理
//-----------------------------------------------------------------------
//配置空的PlotReg
PlotRegStruct*		LUA_VMClass::_NewPlotReg()
{
	PlotRegStruct* pRegStruct = _St->UnUsedPlotReg->NewObj();
	if( pRegStruct == NULL )
		return NULL;

	pRegStruct->Init();
//	pRegStruct->ClearUnlockTest(); //(!)Luky
	return pRegStruct;
}
//歸還PlotReg
void				LUA_VMClass::_FreePlotReg(PlotRegStruct* Reg)
{
	if( Reg->Event != NULL )
		Reg->Event->OnEnd();

	Reg->Event = NULL;

	Reg->Type = PlotEnd;
	_St->UnUsedPlotReg->DeleteObj(Reg);
}
//-----------------------------------------------------------------------

//--------------------------------------------------------------------------------
//	其他一般處理
//--------------------------------------------------------------------------------
bool	LUA_VMClass::Init( int MaxVMCount )
{

    if( _St != NULL )
        return false;

    _St = NEW StaticData( MaxVMCount );
    
	//(!)Try to load lualib.
	luaopen_base(_St->L_State);
	luaopen_table(_St->L_State);
//	luaopen_io(_St->L_State);
	luaopen_string(_St->L_State);
	luaopen_math(_St->L_State);
	luaopen_debug(_St->L_State);

#ifdef _LUA_HOOK_ENABLE_
	lua_sethook(_St->L_State, callhook, LUA_MASKCALL, 0);
	lua_sethook(_St->L_State, linehook, LUA_MASKLINE, 0);
	lua_sethook(_St->L_State, rethook, LUA_MASKRET, 0);
#endif


    RegFunction("Sleep",Sleep);
    RegFunction("Hex",Hex);
	//RegFunction("CallPlot",CallPlot);

    _St->SysVM = NEW LUA_VMClass( -1 );		

    return true;
}

//資源釋放
void	LUA_VMClass::Release()
{	
    //清除系統資源
    if( _St->SysVM != NULL )
    {
        delete _St->SysVM;
        _St->SysVM	= NULL;
    }

    if( _St != NULL )
    {
        delete _St;
        _St = NULL;
    }

}

//設定劇情可使用得函式能
void	LUA_VMClass::RegFunction(	string			FuncName
								 ,	lua_CFunction	FuncPoint)
{
	//_strlwr( (char*)FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );
    ///lua 的掛函式的輔助工具 

	lua_register(_St->L_State, FuncName.c_str() ,FuncPoint);
    _St->FuncNameList.push_back( FuncName );
}


//劇情資料載入
void	LUA_VMClass::LoadFile(string FileName)
{
    static char buff[80]={0};
    int res;


	//char szWorkFolder[256];

	//GetCurrentDirectory( sizeof(szWorkFolder), szWorkFolder );

    if(res = luaL_loadfile(_St->L_State,FileName.c_str()))
    {
        //lua_error(_St->L_State);
//#ifdef _DEBUG
//        const char* err = lua_tostring(_St->L_State, -1);


        sprintf(buff,"luaL_loadfile( %s )",FileName.c_str());
		DisplayError(_St->L_State,res,buff);
#ifdef _RA_DEBUG
        MessageBox(NULL,lua_tostring(_St->L_State, 1),buff,MB_OK|MB_ICONWARNING);
#endif
//#else
//        lua_error(_St->L_State); //let it crash ?
//#endif
    }
    else
    if(res = lua_pcall(_St->L_State, 0, LUA_MULTRET, 0))
    {
        //lua_error(_St->L_State);
//#ifdef _DEBUG
        sprintf(buff,"lua_pcall( %s )",FileName.c_str());
        DisplayError(_St->L_State,res,buff);
        //MessageBox(NULL,lua_tostring(_St->L_State, 1),buff,MB_OK|MB_ICONWARNING);
//#else
//        lua_error(_St->L_State); //let it crash ?
//#endif
    }
}


//劇情處理
void	LUA_VMClass::Process(int TimePass )
{
	int		ret;
	_St->VMTime	+= TimePass;
	_St->IsRunning		= true;

	//定時檢查看是否有物件要刪除
	PlotRunTimeEvent::OnTimeProc();

	string		LastProcFunc;
	unsigned	LastProcTime = GetTickCount();
	char		Buf[512];
	

	while(1)
	{
		if(_St->ExePlot.size() == 0)
			break;

		_St->ProcReg = _St->ExePlot.top();

		if(_St->ProcReg->ExecuteTime > _St->VMTime)
			break;

		_St->ExePlot.pop();

		//////////////////////////////////////////////////////////////////////////
		unsigned NowProcTime = GetTickCount();

		if( NowProcTime - LastProcTime > 100 )
		{
			sprintf( Buf , "Proc Time = %d  Lua Delay.." , NowProcTime - LastProcTime );
			if( _St->OutputErrorFunc )
			{
				if( _St->ProcReg == NULL )
					_St->OutputErrorFunc( 0, 0, LastProcFunc.c_str() , Buf );
				else
					_St->OutputErrorFunc( _St->ProcReg->OwnerID, _St->ProcReg->TargetID, LastProcFunc.c_str() , Buf );
			}
		}
		LastProcTime = NowProcTime;
		LastProcFunc = _St->ProcReg->FuncName;
		//////////////////////////////////////////////////////////////////////////

		//重設處理次數
		ProcTimes			= 0 ;

		if( GetVMUser( _St->ProcReg->ID ) == NULL )
		{
			_St->ProcReg->Type = PlotEnd;
		}

		switch(_St->ProcReg->Type )
		{
		case PlotEnd:
			{
				printf("L_StateID = %d 終斷\n",_St->ProcReg->L_StateID);
				_FreeVM(_St->ProcReg->L_StateID);
				_FreePlotReg(_St->ProcReg);						
			}break;
		case PlotBeginCall:
			{				
				lua_State * L			= _GetLua_State(_St->ProcReg->L_StateID);
				int			iStatck		= lua_gettop (L);
				int			iNumArg		= iStatck - 1;

				if( iNumArg < 0 )
					iNumArg = 0;
				
				ret = lua_resume(L,iNumArg);

				_St->ProcReg->Type = PlotRun;		// 接下來接回正常流程, 

				if(ret != 0 ) 
				{
					if(ret != 0)
					{
						if( _St->ProcReg->Event != NULL )
							_St->ProcReg->Event->OnError();
						DisplayError(L,ret,_St->ProcReg->FuncName);
					}

					printf("L_StateID = %d 結束\n",_St->ProcReg->L_StateID);

					//把此劇情移出
					LUA_VMClass*	OwnerVM = GetVMUser(_St->ProcReg->ID);

					//檢查資料是否有效
					if( OwnerVM != NULL )
					{
						OwnerVM->_PlotProc.erase(_St->ProcReg->FuncName);
					}

					_FreeVM(_St->ProcReg->L_StateID);
					_FreePlotReg(_St->ProcReg);		
					break;
				}
				else
				{
					_St->ExePlot.push(_St->ProcReg);
				}

			}break;
		case PlotRun:
			{
                lua_State * L = _GetLua_State(_St->ProcReg->L_StateID);

				int			iStatck		= lua_gettop (L);
				int			iNumArg		= iStatck - 1;

				if( iNumArg < 0 )
					iNumArg = 0;

				ret = lua_resume(L,iNumArg);

				//如果執行有問題 or 結束
                //Modified.04/01/12 by Luky :加入自然結束判斷
				if( ret == LUA_YIELD && L->status == LUA_YIELD )
				{
					_St->ExePlot.push(_St->ProcReg);
				}
				else
				{
                    if(ret != 0)
					{
						if( _St->ProcReg->Event != NULL )
							_St->ProcReg->Event->OnError();
                        DisplayError(L,ret,_St->ProcReg->FuncName);
					}

					{
						printf("L_StateID = %d 結束\n",_St->ProcReg->L_StateID);				

						//把此劇情移出
						LUA_VMClass*	OwnerVM = GetVMUser(_St->ProcReg->ID);

						//檢查資料是否有效
						if( OwnerVM != NULL )
						{
							OwnerVM->_PlotProc.erase(_St->ProcReg->FuncName);
							//break;
						}

						_FreeVM(_St->ProcReg->L_StateID);
						_FreePlotReg(_St->ProcReg);		
					}

					break;
				}
				
			}break;
		case PlotMultiRun:
			{
				lua_State * L = _GetLua_State(_St->ProcReg->L_StateID);
				ret = lua_resume(L,0);			
				
                //Modified.04/01/12 by Luky :加入自然結束判斷
				//if(ret != 0 /*|| L->ci->state == 1*/) 
				if( ret == LUA_YIELD && L->status == LUA_YIELD )
				{
					_St->ExePlot.push(_St->ProcReg);
				}
				else
				{
                    if(ret != 0)
					{
						if( _St->ProcReg->Event != NULL )
							_St->ProcReg->Event->OnError();
                        DisplayError(L,ret,NULL);
					}
					printf("L_StateID = %d Mutli結束\n",_St->ProcReg->L_StateID);

					_FreeVM(_St->ProcReg->L_StateID);
					_FreePlotReg(_St->ProcReg);		
					break;
				}
			
			}break;
		case PlotPause:
			{
				_St->ProcReg->ExecuteTime += 10;
				_St->ExePlot.push(_St->ProcReg);
			}
			break;
		}
		
	}
    _St->ProcReg = NULL;
	_St->IsRunning		= false;
}

LUA_VMClass::LUA_VMClass( int OwnerID )	
{
    _Ready = false;

    if( (int)_St->All_VMUser.size() > _St->MaxVMCount )
        return;

    if( _St->UnusedID.empty() )
        _St->UnusedID.push_back( (int)_St->All_VMUser.size() );

    _ID = _St->UnusedID.back();
    _St->UnusedID.pop_back();


	while( (int)_St->All_VMUser.size() <= _ID)
		_St->All_VMUser.push_back(NULL);

	if(_St->All_VMUser[_ID] != NULL)
		return;

	_St->All_VMUser[_ID] = this;

    _OwnerID = OwnerID;

	_Ready = true;
}

LUA_VMClass::~LUA_VMClass()
{
	if(_Ready == false)
		return;

	if( _St == NULL )
		return;

	EndAllLuaFunc();

	_St->UnusedID.push_back( _ID );
	//this->EndAllLuaFunc();

	_St->All_VMUser[_ID] = NULL;
//	_St->Total_VMState[_OwnerID] = false;

}

LUA_VMClass*	LUA_VMClass::GetVMUser(int ID)
{
	if(unsigned(ID) >= _St->All_VMUser.size())
		return NULL;

	return _St->All_VMUser[ID];
}

LUA_VMClass*	LUA_VMClass::GetVMUser(lua_State* L)
{
	map<lua_State*, LUA_VMClass*>::iterator it = _St->VM_UserMapping.find(L);

	if (it != _St->VM_UserMapping.end())
	{
		return it->second;
	}

	return NULL;
}

int	LUA_VMClass::GetOwnerID(lua_State* L)
{
	LUA_VMClass* VMUser = GetVMUser(L);

	if (VMUser != NULL)
	{
		return VMUser->GetOwner();
	}

	return -1;
}

static void StopVM(LUA_VMClass* pVM)
{
	if(pVM)
		pVM->EndAllLuaFunc();
}
// 將所有VM執行工作終止掉, 包括系統VM
void LUA_VMClass::StopAllVM()
{
	std::for_each( _St->All_VMUser.begin() , _St->All_VMUser.end(), StopVM);
}

//檢查某一個lua 的劇情是否已在執行中
bool	LUA_VMClass::CheckLuaFunc(string FuncName)
{
//	_strlwr( (char*)FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );

	char szName[256];
	strcpy( szName , FuncName.c_str() );

//	map<string,PlotRegStruct *,StringCmp>::iterator it;
    map<string,PlotRegStruct *>::iterator it;
	it = _PlotProc.find(FuncName);

	if(it == _PlotProc.end())
		return false;

	return true;
}

int	LUA_VMClass::CallPlot( lua_State *L, int iTargetObjID, string FuncName, int iNumArg )
{
	if( FuncName.length() == 0 || FuncName[0] == ' ' )
		return NULL;

	//_strlwr((char*) FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );

	
	if(CheckLuaFunc(FuncName) != false)
	{
		char szBuff[1024];
		sprintf( szBuff, "\n Plot [ %s ] [ %d ] already running!", FuncName.c_str() , _OwnerID );
		OutputDebugString(szBuff);

		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc( iTargetObjID, iTargetObjID, FuncName.c_str() , szBuff);

		return NULL;
	}

	PlotRegStruct *Reg = _NewPlotReg();
	if(Reg == NULL)
	{
		OutputDebugString("\nPlot Reg Alloc Error!!");

		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc( iTargetObjID, iTargetObjID, FuncName.c_str(),"\nPlot Reg Alloc Error!!");

		return NULL;
	}

	// 設定 -----------------------
	//memcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	MyStrcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	Reg->ExecuteTime = _St->VMTime;
	Reg->L_StateID   = _NewVM(this);
	Reg->OwnerID	 = _OwnerID;
	Reg->ID          = _ID;
	Reg->TargetID	 = iTargetObjID;
	Reg->Type		 = PlotRun;
	Reg->Event		 = NULL;


	if(Reg->L_StateID == -1)
	{
		OutputDebugString("\nVirtual Machine Alloc Error!!");
		_FreePlotReg(Reg);
		return NULL;
	}

	lua_State*	L_ThreadState = _GetLua_State(Reg->L_StateID);
//	lua_resetstate( L_ThreadState );
	//如果堆疊還有資料要清除
	int PopCount = lua_gettop(L_ThreadState);
	lua_pop(L_ThreadState,PopCount  );

	lua_getglobal(L_ThreadState,FuncName.c_str());

	int iNum = lua_gettop ( L );
	for( int i = 1; i<= iNum; i++ )
	{
		if( i >= 3 )
		{
			int t = lua_type(L, i);
			switch (t)
			{
			case LUA_TSTRING: /* strings */
				{
					const char* pString = lua_tostring( L, i );
					lua_pushstring( L_ThreadState , pString );
				} break;
			case LUA_TBOOLEAN: /* booleans */
				{
					bool bFlag = lua_toboolean( L, i ) ? true : false;
					lua_pushboolean ( L_ThreadState , bFlag );
				} break;
			case LUA_TNUMBER: /* numbers */				
				{
					int iVal = (int)lua_tonumber( L, i );
					lua_pushnumber( L_ThreadState , iVal );
				} break;
			case LUA_TTABLE:
				{
					CopyLuaTable(L, i, L_ThreadState);
				} break;
			default: /* other values */
				lua_pushnil( L_ThreadState );
				break;
			}
		}
	}
	
	_St->ExePlot.push(Reg);
	_PlotProc[FuncName] = Reg;
	
	return 0;
}


//劇情呼叫
ArgTransferStruct*	LUA_VMClass::CallLuaFunc(string FuncName, int Target,unsigned int ExeTime , PlotRunTimeEvent* Listen )
{
	if( FuncName.length() == 0 || FuncName[0] == ' ' )
		return NULL;

	//_strlwr((char*) FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );

	if(CheckLuaFunc(FuncName) != false)
	{
		char szBuff[1024];
		sprintf( szBuff, "\n Plot [ %s ] [ %d ] already running!", FuncName.c_str() , _OwnerID );
		OutputDebugString(szBuff);

		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc( _OwnerID, Target, FuncName.c_str(),szBuff);

		return NULL;
	}

	PlotRegStruct *Reg = _NewPlotReg();
	if(Reg == NULL)
	{
		OutputDebugString("\nPlot Reg Alloc Error!!");

		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc( _OwnerID, Target, FuncName.c_str(),"\nPlot Reg Alloc Error!!");

		return NULL;
	}

	// 設定 -----------------------
	//memcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	MyStrcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	Reg->ExecuteTime = _St->VMTime + ExeTime;
	Reg->L_StateID   = _NewVM(this);
	Reg->OwnerID	 = _OwnerID;
    Reg->ID          = _ID;
	Reg->TargetID	 = Target;
	Reg->Type		 = PlotRun;
	Reg->Event		 = Listen;

	//劇情開始
	if( Listen != NULL )
		Listen->OnBegin();

	if(Reg->L_StateID == -1)
	{
		OutputDebugString("\nVirtual Machine Alloc Error!!");
		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc( _OwnerID, Target, FuncName.c_str(),"\nVirtual Machine Alloc Error!!");
		if( Listen != NULL )
			Listen->OnError();
		_FreePlotReg(Reg);
		return NULL;
	}
	
	lua_State*	L_ThreadState = _GetLua_State(Reg->L_StateID);
//	lua_resetstate( L_ThreadState );
	//如果堆疊還有資料要清除
	int PopCount = lua_gettop(L_ThreadState);
	lua_pop(L_ThreadState,PopCount  );
	lua_getglobal(L_ThreadState,FuncName.c_str());

	_St->ExePlot.push(Reg);
	_PlotProc[FuncName] = Reg;

	return &Reg->Arg;
}

bool	LUA_VMClass::EndLuaFunc(string FuncName)
{
	//_strlwr( (char*)FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );

//	map<string,PlotRegStruct *,StringCmp>::iterator it;
    map<string,PlotRegStruct *>::iterator it;
	it = _PlotProc.find(FuncName);

	if(it == _PlotProc.end())
		return false;

	PlotRegStruct *Reg = it->second;
	if(Reg->Type != PlotRun)
		return false;

	Reg->Type = PlotEnd;

	//把此劇情移出
	LUA_VMClass*	OwnerVM = GetVMUser(Reg->ID);
	OwnerVM->_PlotProc.erase(FuncName);

	return true;
}

bool	LUA_VMClass::EndAllLuaFunc( )
{
    map<string,PlotRegStruct *>::iterator it;
	PlotRegStruct *Reg;

	//queue<PlotRegStruct*> tempQue;
	//endit = _PlotProc.end();
	for ( it = _PlotProc.begin() ; it != _PlotProc.end() ; it++ )
	{
		//string funname = (*it).first;
		Reg = (*it).second;
		Reg->Type = PlotEnd;

		//tempQue.push(Reg);
		
	}
	_PlotProc.clear();

	/*
	while(!tempQue.empty())
	{
		Reg = tempQue.front();
		tempQue.pop();

		if(		Reg->Type != PlotRun
			&&	Reg->Type != PlotPause )
			continue;

		Reg->Type = PlotEnd;
	}
	*/
	return true;
}

//暫停所有執行的劇情
bool	LUA_VMClass::PauseAllLuaFunc( )
{
	map<string,PlotRegStruct *>::iterator it,endit;
	PlotRegStruct *Reg;

	queue<PlotRegStruct*> tempQue;
	endit = _PlotProc.end();
	for ( it = _PlotProc.begin() ; it != endit ; it++ )
	{
		string funname = (*it).first;
		Reg = (*it).second;

		tempQue.push(Reg);

	}
//	_PlotProc.clear();

	while(!tempQue.empty())
	{
		Reg = tempQue.front();
		tempQue.pop();

		if(Reg->Type != PlotRun)
			continue;

		Reg->Type = PlotPause;
		Reg->Pause_DTime = Reg->ExecuteTime - _St->VMTime;
	}
	return true;
}

bool	LUA_VMClass::StartAllLuaFunc( )
{
	map<string,PlotRegStruct *>::iterator it,endit;
	PlotRegStruct *Reg;

	queue<PlotRegStruct*> tempQue;
	endit = _PlotProc.end();
	for ( it = _PlotProc.begin() ; it != endit ; it++ )
	{
		string funname = (*it).first;
		Reg = (*it).second;

		tempQue.push(Reg);

	}
//	_PlotProc.clear();

	while(!tempQue.empty())
	{
		Reg = tempQue.front();
		tempQue.pop();

		if(Reg->Type != PlotPause)
			continue;

		Reg->Type = PlotRun;
		Reg->ExecuteTime = _St->VMTime + Reg->Pause_DTime;
	}
	return true;
}

ArgTransferStruct*	LUA_VMClass::ReCallLuaFunc(string FuncName,int Target,unsigned int ExeTime,PlotRunTimeEvent* Listen)
{
	if( FuncName.length() == 0 || FuncName[0] == ' ' )
		return NULL;

	EndLuaFunc(FuncName);
	return CallLuaFunc(FuncName,Target,ExeTime,Listen);
}

	//同時可執行多個的行程(不能中斷)
ArgTransferStruct*	LUA_VMClass::MultiCallLuaFunc(string FuncName,int Target,unsigned int ExeTime,PlotRunTimeEvent* Listen)
{
	if( FuncName.length() == 0 || FuncName[0] == ' ' )
		return NULL;

	//_strlwr( (char*)FuncName.c_str() );	
	std::transform( FuncName.begin(), FuncName.end(), FuncName.begin(), ::tolower );

	PlotRegStruct *Reg = _NewPlotReg();
	if(Reg == NULL)
	{
		OutputDebugString("\nPlot Reg Alloc Error!!");
		return NULL;
	}

	// 設定 -----------------------
	//memcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	MyStrcpy(Reg->FuncName,FuncName.c_str(),sizeof(Reg->FuncName));
	Reg->ExecuteTime = _St->VMTime + ExeTime;
	Reg->L_StateID   = _NewVM(this);
	Reg->OwnerID	 = _OwnerID;
	Reg->TargetID	 = Target;
	Reg->Type		 = PlotMultiRun;
	Reg->Event		 = Listen;
	
	//劇情開始
	if( Listen != NULL )
		Listen->OnBegin();

	if(Reg->L_StateID == -1)
	{
		OutputDebugString("\nVirtual Machine Alloc Error!!");
		if( Listen != NULL )
			Listen->OnError();
		_FreePlotReg(Reg);
		return NULL;
	}
	
	lua_State*	L_ThreadState = _GetLua_State(Reg->L_StateID);

	//如果堆疊還有資料要清除
	int PopCount = lua_gettop(L_ThreadState);
	if(PopCount != 0)
		lua_pop(L_ThreadState,PopCount);

	lua_getglobal(L_ThreadState,FuncName.c_str());

	_St->ExePlot.push(Reg);
	
	return &Reg->Arg;
}

//把資料放入Map裡面
void	LUA_VMClass::LoadAllFile(string FilePath)
{
	string FullPath;
	if(		FilePath.c_str()[ FilePath.length() - 1 ] != '\\' 
		&&	FilePath.c_str()[ FilePath.length() - 1 ] != '/'	)
		FilePath += "\\";

	FullPath = FilePath ;
	FullPath += "*.lua";

	WIN32_FIND_DATA  file_data;
	HANDLE	hfile = FindFirstFile(FullPath.c_str(), &file_data);
	if(hfile == INVALID_HANDLE_VALUE)
		return;

	FullPath = FilePath;
	FullPath += file_data.cFileName;
	LoadFile( FullPath );

	while(FindNextFile(hfile, &file_data))
	{
		FullPath =  FilePath;
		FullPath +=	file_data.cFileName;
		LoadFile( FullPath );
	}

}

//取得某目錄下的所有子目錄
vector<string>*	LUA_VMClass::_AllPathList( string Path )
{
	static vector<string> AllPath;

	vector<string> OpenPath;
	struct _finddata_t c_file;
	long	hFile;
	string	Findmask;
	string	TempPath;


	AllPath.clear();
	OpenPath.clear();

	const char *P = Path.c_str();
	if( P[ Path.length() - 1] != '\\' && Path.length() != 0 )
		Path += "\\";


	OpenPath.push_back( Path );


	while( OpenPath.size() )
	{
		Path = OpenPath.back();
		AllPath.push_back( Path );

		OpenPath.pop_back();
		Findmask = Path + "*.";

		if( (hFile = (long)_findfirst( (char*)Findmask.c_str() , &c_file )) != -1L )
		{

			do
			{
				if( !(c_file.attrib & _A_SUBDIR) )
					continue;
				
				if( c_file.name[0] == '.' )
					continue;

				TempPath = Path + c_file.name + "\\";
				OpenPath.push_back( TempPath );
				

			}while( _findnext( hFile, &c_file ) == 0 );


			_findclose( hFile );
		}
	}

	return &AllPath;
}


//遞迴載入某目錄與其子目錄的檔案
void	LUA_VMClass::RecursiveLoadAllFile( string FilePath )
{
	int		i;
	vector<string>*	PathList = _AllPathList( FilePath );

	for( i = 0 ; i < (int)PathList->size() ; i++ )
	{
		LoadAllFile( (*PathList)[i] );
	}

}


void LUA_VMClass::DoBuffer( const char* Str , int Size, const char* Name )
{
	_St->IsPCall		= true;
	_St->IsRunning		= true;
	int        LState_ID = _NewVM(_St->SysVM);
	lua_State* LState    = _GetLua_State( LState_ID );

	if (Name == NULL)
	{
		luaL_dobuffer( LState , Str , Size , Str );
	}
	else
	{
		luaL_dobuffer( LState , Str , Size , Name );
	}

	_FreeVM( LState_ID );
	_St->IsPCall		= false;
	_St->IsRunning		= false;
}

void    LUA_VMClass::DoString( char* Str )
{
    _St->IsPCall = true;
	_St->IsRunning		= true;
    int        LState_ID = _NewVM(_St->SysVM);
    lua_State* LState    = _GetLua_State( LState_ID );

    luaL_dostring( LState , Str );
    
    _FreeVM( LState_ID );
    _St->IsPCall = false;
	_St->IsRunning		= false;
}

bool LUA_VMClass::PCall( string _Plot , int OwnerID , int TargetID , vector<MyVMValueStruct>* ArgList , vector<MyVMValueStruct>* RetList , int RetCount )
{
	char Buf[512];

	unsigned ProcTime = GetTickCount();

	bool Ret = true;
	char* Plot = (char*)_Plot.c_str();
	_strlwr( (char*)Plot );	
	_St->IsPCall = true;
	_St->IsRunning		= true;

	int        LState_ID = _NewVM(_St->SysVM);
	lua_State* LState    = _GetLua_State( LState_ID );

	ProcTimes			= 0;

	PlotRegStruct Proc;

	Proc.OwnerID    = OwnerID;
	Proc.TargetID   = TargetID;
	Proc.Type		= PlotPCall;

	MyStrcpy( Proc.FuncName , _Plot.c_str() , sizeof( Proc.FuncName ) );
	PlotRegStruct* ProcRegBK = _St->ProcReg;
	_St->ProcReg	= &Proc;

	int PopCount = lua_gettop( LState );
	lua_pop( LState,PopCount  );
	lua_settop( LState , 0 );

	int ArgCount = 0;
	lua_getglobal( LState , Plot );
	if( ArgList != NULL )
	{
		ArgCount = (int)ArgList->size();
		for( int i = 0 ; i < (int)ArgList->size() ; i++ )
		{
			MyVMValueStruct& Temp = ((*ArgList)[i]);
			switch( Temp.Type )
			{
			case MyVMValueType_Nil:
				lua_pushnil(LState );
				break;
			case MyVMValueType_Number:
				lua_pushnumber( LState , Temp.Number );
				break;
			case MyVMValueType_String:
				lua_pushstring( LState , Temp.Str.c_str() );
				break;
			case MyVMValueType_Boolean:
				lua_pushboolean ( LState , Temp.Flag );
				break;
			}
		}
	}

	int GC_Size1 = 0;
	int GC_Size2 = 0;

	//記錄PCall執行前, GC的使用量
	if (_St->IsLogPCall == true)
	{
		GC_Size1 = lua_gc(LState, LUA_GCCOUNT, 0);
	}

	int PcallRet = lua_pcall( LState , ArgCount , RetCount , NULL );
	if( PcallRet != 0 )
	{
		sprintf(Buf,"lua_pcall( %s )",_Plot.c_str() );
		DisplayError( LState , PcallRet , Buf );
		/*
		char szBuff[1024];
		char szDebugBuff[1024];

		//sprintf( szBuff, "error runing function %s " , lua_tostring( LState , - 1 ) );
		sprintf( szBuff, "error runing function %s " , _Plot.c_str() );

		printf( szBuff );
		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc(_Plot.c_str() ,szBuff);

		lua_Debug trouble_info;
		ZeroMemory(&trouble_info,sizeof(lua_Debug));
		//int debug_StackNum = lua_gettop (L);

		if(lua_getstack(LState,0,&trouble_info) || lua_getstack(LState,1,&trouble_info))
			//if(lua_getstack(L,0,&trouble_info) )
		{
			lua_getinfo(LState,"Snl",&trouble_info);
			sprintf(szDebugBuff,"%s\n %s\nname:(%s) namewhat:(%s) what:(%s) \nsource:(%s) short:(%s) \nlinedefined:(%d) currentline:(%d)\n",
				szBuff,
				lua_tostring( LState , - 1 ),
				trouble_info.name,
				trouble_info.namewhat,
				trouble_info.what,
				trouble_info.source,
				trouble_info.short_src,
				trouble_info.linedefined,
				trouble_info.currentline
				);

		}
		else
		{
			sprintf(szDebugBuff,"%s",	szBuff );
		}


		if( _St->OutputErrorFunc )
			_St->OutputErrorFunc(_Plot.c_str() , szDebugBuff );
*/
		Ret = false;
	}
	else if( RetList != NULL )
	{
		vector<MyVMValueStruct> TempList;
		RetList->clear();
		bool  PassNil = true;
		for( int i = 0 ; i < RetCount ; i++ )
		{
			MyVMValueStruct Data;
			//Data.Str	= lua_tostring( LState , -1 );

			int iType = lua_type(LState, -1);

			if( lua_isnumber( LState , -1 ) )
			{
				Data.Number = (double)lua_tonumber( LState , -1 );
				Data.Str	= lua_tostring( LState , -1 );
				Data.Type	= MyVMValueType_Number;
				Data.Flag	= ( TRUE == lua_toboolean( LState , -1 ) );
				Data.Number_Int = (int)lua_tonumber( LState , -1 );
				PassNil		= false;
			}
			else if( lua_isstring( LState , -1 ) )
			{
				Data.Number = 0;
				Data.Str	= lua_tostring( LState , -1 );
				Data.Type	= MyVMValueType_String;
				Data.Flag	= ( TRUE == lua_toboolean( LState , -1 ) );
				PassNil		= false;
			}
			else if( lua_isboolean( LState , -1  ) )
			{
				Data.Number = 0;
				Data.Flag	= ( TRUE == lua_toboolean( LState , -1 ) );
				Data.Str	= "";
				Data.Type	= MyVMValueType_Boolean;
				PassNil		= false;
			}
			else
			{
				Data.Number = 0;
				Data.Type = MyVMValueType_Nil;
				
				if( PassNil )
				{
					lua_pop( LState , 1 );
					continue;
				}
			}			

			TempList.push_back( Data );
			lua_pop( LState , 1 );
		}
		while( TempList.size() )
		{
			RetList->push_back( TempList.back() );
			TempList.pop_back();
		}
	}

	//Log PCall的執行資訊
	if (_St->IsLogPCall == true)
	{
		GC_Size2 = lua_gc(LState, LUA_GCCOUNT, 0);

		std::string Func = _Plot;
		Func.append("(");

		if(ArgList != NULL)
		{
			for(int i = 0; i < (int)ArgList->size(); ++i)
			{
				MyVMValueStruct& Arg = ((*ArgList)[i]);
				switch(Arg.Type)
				{
				case MyVMValueType_Nil:
					Func.append("nil");
					break;
				case MyVMValueType_Number:
					{
						sprintf(Buf, "%f", Arg.Number);
						Func.append(Buf);
					}
					break;
				case MyVMValueType_String:
					Func.append(Arg.Str);
					break;
				case MyVMValueType_Boolean:
					{
						if (Arg.Flag == true)
						{
							Func.append("true");
						}
						else
						{
							Func.append("false");
						}
					}
					break;
				}

				if ((i == (ArgList->size() - 1)) == false)
				{
					Func.append(", ");
				}
			}
		}

		Func.append(")");

		Print(LV5, "PCall", "function=%s, OwnerID=%d, TargetID=%d, GC size before = %d KB, GC size after = %dKB", Func.c_str(), OwnerID, TargetID, GC_Size1, GC_Size2);
	}

	_FreeVM( LState_ID );
	_St->IsPCall = false;
	_St->IsRunning	= false;
	_St->ProcReg = ProcRegBK;

	ProcTime = GetTickCount() - ProcTime;
	if( ProcTime > 200 )
	{
		sprintf( Buf , "Proc Time = %d  Lua Delay.." , ProcTime );
		if( _St->OutputErrorFunc )
		{
			if( _St->ProcReg == NULL )
				_St->OutputErrorFunc( 0, 0, Proc.FuncName , Buf );
			else
				_St->OutputErrorFunc( _St->ProcReg->OwnerID, _St->ProcReg->TargetID, Proc.FuncName , Buf );			
		}
	}

	return Ret;
}

//直接執行某 LUA 
bool LUA_VMClass::PCallByStrArg( string PlotArgCmd , int OwnerID , int TargetID , vector<MyVMValueStruct>* RetList , int RetCount )
{
	char Buf[1024];

    char	seps[] = " ,\t\n()";
	char*	Next_token;
	//參數分析	
	if( PlotArgCmd.size() == 0 )
		return false;

	strcpy( Buf , PlotArgCmd.c_str() );

//	char* ArgListStr = strstr( Buf , "(" );
	char* Plot = strtok_s( Buf , seps , &Next_token );

	if( Plot == NULL )
		return false;

	//轉成小寫
	_strlwr( Plot );

	vector<MyVMValueStruct> ArgList;
	MyVMValueStruct VMArg;
	char* Arg;
	
	bool CheckStr;
	//取數值
	for( int i = 0 ; ; i++ )
	{
		CheckStr = false;
		for( int j = 0 ; ; j++  )
		{
			if( Next_token[j] == 0 )
				break;
			if( Next_token[j] == '\"' )
			{
				CheckStr = true;
				break;
			}
			if(		Next_token[j] != ' '
				&&  Next_token[j] != ',')
			{				
				break;
			}
		}
		
		if( CheckStr == false )
			Arg = strtok_s( NULL , seps , &Next_token );
		else
			Arg = strtok_s( NULL , "," , &Next_token );

		if( Arg== NULL ) 
			break;

		while( 1 )
		{
			if( Arg[0] == 0 )
				break;
			if( Arg[0] != ' ')
				break;
			Arg++;
		}

		if( Arg[0] == '\"' )
		{
			string Str = Arg;
			while( 1 )
			{
				if( Str.size() == 0 )
					break;
				if(		Str[ Str.size() - 1 ] == ' ' 
					||	Str[ Str.size() - 1 ] == ')' )
				{
					Str.erase( Str.end()-1 );
				}
				else
					break;
			}

			if( Str[ Str.size() - 1 ] != '\"' )
			{
				return false;
			}
			Str.erase( Str.end()-1 );
			VMArg.Number = 0;
			VMArg.Type = MyVMValueType_String;
			VMArg.Str = ( Str.c_str()+sizeof( char ) );
		}
		else
		{
			//檢查是否為true false
			if( stricmp( "true" , Arg ) == 0 )
			{
				VMArg.Number = 0;
				VMArg.Type = MyVMValueType_Boolean;
				VMArg.Flag = true;
			}
			else if( stricmp( "false" , Arg ) == 0  )
			{
				VMArg.Number = 0;
				VMArg.Type = MyVMValueType_Boolean;
				VMArg.Flag = false;
			}
			else
			{
				VMArg.Number = (double)atof( Arg );
				VMArg.Type = MyVMValueType_Number;
				VMArg.Str = "";
			}
		}
		ArgList.push_back( VMArg );
	}
	return PCall( Plot , OwnerID , TargetID , &ArgList , RetList , RetCount );
}
//---------------------------------------------
bool LUA_VMClass::CheckFunc( string luaFunc )
{
	return true;
}

void LUA_VMClass::SetOutputErrorFunc( OutputDebugFunction Func )
{ 
	_St->OutputErrorFunc = Func; 
	//g_pfunLuaErrorOut = Func; 
	SetLuaDebugOutput( Func );
}

void LUA_VMClass::GetProcFuncName( char* pszFuncName )
{
	if( pszFuncName != NULL )
	{
		pszFuncName[0] = 0;
		if( LUA_VMClass::_St->ProcReg != NULL )
			strcpy( pszFuncName, LUA_VMClass::_St->ProcReg->FuncName );

		//strcpy( pszFuncName, (*((*(LUA_VMClass::_St)).ProcReg)).FuncName );
	}
}

int LUA_VMClass::GetProcFuncExecuteTime()
{
	if( LUA_VMClass::_St->ProcReg != NULL )
		return LUA_VMClass::_St->ProcReg->ExecuteTime;

	return 0;

//	return (*((*(LUA_VMClass::_St)).ProcReg)).ExecuteTime;
}

//將來源Lua Thread上指定位置的table複製一份到目標Lua Thread (目標Lua Thread不能同等於來源Thread )
void LUA_VMClass::CopyLuaTable( lua_State* src_thread, int src_idx, lua_State* dest_thread )
{
	if (dest_thread == src_thread)
		return;

	if (src_idx == 0)
		return;

	if (src_idx < 0)
	{
		src_idx = lua_gettop(src_thread) + src_idx + 1;
	}

	if (lua_type(src_thread, src_idx) == LUA_TTABLE)
	{
		//create a new table onto dest thread's stack top
		lua_newtable(dest_thread);
		int dest_idx = lua_gettop(dest_thread);

		//begin travel table, push a 'nil' onto stack top as first key
		lua_pushnil(src_thread);

		//lua_next() will pop top of stack as iterator key and push key and value onto stack
		while (lua_next(src_thread, src_idx) != 0)
		{
			int iVal = 0;
			double fVal = 0;
			const char* pString = NULL;

			//copy key (at index -2)
			int idx = lua_gettop(src_thread) - 1;
			int t   = lua_type(src_thread, idx);

			switch (t)
			{
			case LUA_TBOOLEAN:
				iVal = lua_toboolean(src_thread, idx);
				lua_pushboolean(dest_thread, iVal);
				break;
			case LUA_TNUMBER:
				fVal = lua_tonumber(src_thread, idx);
				lua_pushnumber(dest_thread, fVal);
				break;
			case LUA_TSTRING:
				pString = lua_tostring(src_thread, idx);
				lua_pushstring(dest_thread, pString);
				break;
			case LUA_TTABLE:
				CopyLuaTable(src_thread, idx, dest_thread);
				break;
			default:
				lua_pushnil( dest_thread );
				break;
			}

			//copy value (at index -1)
			idx = lua_gettop(src_thread);
			t	= lua_type(src_thread, idx);

			switch (t)
			{
			case LUA_TBOOLEAN:
				iVal = lua_toboolean(src_thread, idx);
				lua_pushboolean(dest_thread, iVal);
				break;
			case LUA_TNUMBER:
				fVal = lua_tonumber(src_thread, idx);
				lua_pushnumber(dest_thread, fVal);
				break;
			case LUA_TSTRING:
				pString = lua_tostring(src_thread, idx);
				lua_pushstring(dest_thread, pString);
				break;
			case LUA_TTABLE:
				CopyLuaTable(src_thread, idx, dest_thread);
				break;
			default:
				lua_pushnil( dest_thread );
				break;
			}

			//set key-value pair to dest table
			lua_settable(dest_thread, dest_idx);

			/* removes 'value'; keeps 'key' for next iteration */
			lua_pop(src_thread, 1);
		}
	}
}

//將Lua thread上指定位置的變數輸出成字串
std::string LUA_VMClass::LuaVartoString(lua_State* L, int idx)
{
	std::string Result = "";

	if (idx != 0)
	{
		if (idx < 0)
		{
			idx = lua_gettop(L) + idx + 1;
		}

		//get tostring function pointer
		lua_getglobal(L, "tostring");

		//push a copy onto stack
		lua_pushvalue(L, idx);   

		//call tostring function
		lua_call(L, 1, 1);

		const char* s = lua_tostring(L, -1);  /* get result */

		if (s != NULL)
			Result = s;

		lua_pop(L, 1);  /* pop result */
	}

	return Result;
}

//列出所有的Lua全域變數
void LUA_VMClass::ListGlobalVariables(std::vector<LuaVarInfoStruct>& output, int filter)
{
	output.clear();
	std::set<std::string> TableSet;

	int        LState_ID = _NewVM(_St->SysVM);
	lua_State* L		 = _GetLua_State( LState_ID );

	//find _G table and push onto stack
	lua_getglobal(L, "_G");

	int idx = lua_gettop(L);

	//begin travel table, push a 'nil' onto stack top as first key
	lua_pushnil(L);

	//lua_next() will pop top of stack as iterator key and push key and value onto stack
	while (lua_next(L, idx) != 0)
	{
		int varidx = lua_gettop(L);  //(index -1)
		int keyidx = varidx - 1;	 //(index -2)

		std::string KeyStr = LuaVartoString(L, keyidx);
		strlwr((char*)KeyStr.c_str());

		//get value string and data size (at index -1)
		int	VarType = lua_type(L, varidx);

		if (VarType == LUA_TTABLE)
		{
			TableSet.clear();
			TableSet.insert("_g");
			TableSet.insert(KeyStr.c_str());
		}

		int			VarSize = GetLuaDataSize(L, varidx, &TableSet);
		std::string VarStr  = LuaVartoString(L, varidx);

		bool bOutput = true;

		if (filter > 0)
		{	
			if (VarType != filter)
				bOutput = false;
		}

		if (bOutput == true)
		{
			LuaVarInfoStruct Info;
			Info.Key = KeyStr.c_str();
			Info.Value = VarStr.c_str();
			Info.Type = VarType;
			Info.Size = VarSize;

			output.push_back(Info);
		}

		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}

	//pop _G
	lua_pop(L, 1);

	_FreeVM(LState_ID);
}

//取得Lua變數佔記憶體大小
int LUA_VMClass::GetLuaDataSize(lua_State* L, int idx, std::set<std::string>* tableset)
{
	int Result = 0;

	if (idx != 0)
	{
		if (idx < 0)
		{
			idx = lua_gettop(L) + idx + 1;
		}

		int datatype = lua_type(L, idx);

		switch(datatype)
		{
		case LUA_TNONE:
			break;
		case LUA_TNIL:
			break;
		case LUA_TBOOLEAN:
			Result = sizeof(int);
			break;
		case LUA_TLIGHTUSERDATA:
			Result = 4;
			break;
		case LUA_TNUMBER:
			Result = sizeof(double);
			break;
		case LUA_TSTRING:
			{
				const char* s = lua_tostring(L, idx);
				if (s != NULL)
				{
					Result = strlen(s);
				}
			}
			break;
		case LUA_TTABLE:
			{
				//begin travel table, push a 'nil' onto stack top as first key
				lua_pushnil(L);

				//lua_next() will pop top of stack as iterator key and push key and value onto stack
				while (lua_next(L, idx) != 0)
				{
					int varidx = lua_gettop(L);
					int keyidx = varidx-1;

					std::string KeyStr = LuaVartoString(L, keyidx);
					strlwr((char*)KeyStr.c_str());

					int	VarType = lua_type(L, varidx);

					bool CountValue = true;

					if (VarType == LUA_TTABLE)
					{
						if (!KeyStr.empty())
						{
							std::set<std::string>::iterator it = tableset->find(KeyStr.c_str());
							if (it != tableset->end())
							{
								CountValue = false;
							}
							else
							{
								tableset->insert(KeyStr.c_str());
							}
						}
					}

					if (CountValue == true)
					{
						//get value size (at index -1)
						Result += GetLuaDataSize(L, varidx, tableset);
					}

					//get key size (at index -2)
					Result += GetLuaDataSize(L, keyidx, tableset);

					/* removes 'value'; keeps 'key' for next iteration */
					lua_pop(L, 1);
				}
			}
			break;
		case LUA_TFUNCTION:
			Result = 4;
			break;
		case LUA_TUSERDATA:
			Result = 4;
			break;
		case LUA_TTHREAD:
			Result = 4;
			break;
		}
	}

	return Result;
}

//取得Lua全域變數佔的記憶體大小
int LUA_VMClass::GetLuaMemoryUsage()
{
	int Result = lua_gc(_St->L_State, LUA_GCCOUNT, 0);
	return Result;
}

//取得LuaTable的內容資訊
bool LUA_VMClass::GetLuaTableInfo(const char* tablename, std::vector<LuaVarInfoStruct>& info)
{
	bool Result = false;

	int        LState_ID = _NewVM(_St->SysVM);
	lua_State* L		 = _GetLua_State( LState_ID );

	std::set<std::string> TableSet;	

	//find table and push onto stack
	lua_getglobal(L, tablename);

	int idx = lua_gettop(L);

	int	VarType = lua_type(L, idx);

	if (VarType == LUA_TTABLE)
	{
		//begin travel table, push a 'nil' onto stack top as first key
		lua_pushnil(L);

		//lua_next() will pop top of stack as iterator key and push key and value onto stack
		while (lua_next(L, idx) != 0)
		{
			TableSet.clear();
			TableSet.insert(tablename);

			int varidx = lua_gettop(L);
			int keyidx = varidx-1;

			LuaVarInfoStruct Info;
			Info.Key   = LuaVartoString(L, keyidx);
			Info.Value = LuaVartoString(L, varidx);
			Info.Type  = lua_type(L, varidx);
			Info.Size  = GetLuaDataSize(L, varidx, &TableSet);

			info.push_back(Info);

			/* removes 'value'; keeps 'key' for next iteration */
			lua_pop(L, 1);
		}

		Result = true;
	}

	//pop table
	lua_pop(L, 1);

	_FreeVM(LState_ID);

	return Result;
}

void LUA_VMClass::OutputError( int OwnerID, int TargetID, const char* FunName ,  const char* pszMsg )
{
	if( _St->OutputErrorFunc )
	{
		_St->OutputErrorFunc( OwnerID, TargetID, FunName , pszMsg );
	}
}


void LUA_VMClass::SetLuaDebug()
{
	lua_sethook( _St->L_State, LuaHookRoutine, LUA_MASKLINE, 0);
}

void LUA_VMClass::LuaHookRoutine(lua_State *L, lua_Debug *ar)
{
	char buff[255];
	sprintf( buff,"ret-hook, event: %d, line: %d\r\n", ar->event,ar->currentline );
}

#pragma managed
