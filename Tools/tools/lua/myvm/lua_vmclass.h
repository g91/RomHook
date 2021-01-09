//======================================================================================
/**
 * @file lua_vmclass.h lua_vmclass.cpp
 * 主要用來處理劇情的物件,可以同時跑多個劇情\n
 * 可用系統VM跑劇情\n
 * 也可以定義屬於自己的VM，處理屬於自己的劇情\n
 * Data : 2003.8.29
 * @author jacklo@softstar.com.tw
 */
//======================================================================================
#pragma     once
#pragma	warning (disable:4786)
#pragma warning (disable:4949)

#include "MyBaseInc.h"

#pragma unmanaged

extern "C"{
	#include "../lua.h"
	#include "../lauxlib.h"
	#include "../lualib.h"
	#include "../llex.h"
	#include "../lfunc.h"
	#include "../ldo.h"
	#include "../lmem.h"
	#include "../lobject.h"
	#include "../lopcodes.h"
	#include "../lstring.h"
	#include "../lundump.h"
};

typedef void					 (*OutputDebugFunction)     ( int OwnerID, int TargetID, const char* FunName , const char* Msg );
//--------------------------------------------------------------------------
//		資料定義
//--------------------------------------------------------------------------
///定義最多可以有多少個Virtual Machine
//#ifndef _MAX_LUA_VIRTUAL_MACHINE_
//	#define		_MAX_LUA_VIRTUAL_MACHINE_		3000
//#endif

///迴圈一次最多處理多少個劇情指令，如果超過則作"等待10輪迴"的動作等一段時間再處理
#define		_MAX_LUA_PROCESS_COUNT			10000									

//定義LUA_FuntionName 最大的字串長度
//#define		_MAX_LUA_FUNTIONNAMESIZE_		32
//--------------------------------------------------------------------------
/// 義一個Marco 給每個劇情指令作檢查的動作
/// 主要是用來查詢劇情，一次處理過的指令
/// 如果處理過多的指令則 Waitting 10 回合，並輸出資料到螢幕

#define		_P1_( L )	{	    									\
			PlotRegStruct* T = LUA_VMClass::ProcReg();				\
			if(T != NULL /*&& T->Type != PlotPCall*/)					\
			{														\
				if(LUA_VMClass::ProcTimes++ > _MAX_LUA_PROCESS_COUNT)	\
				{														\
                    lua_Debug ar;                                       \
                    lua_getstack(L, 0, &ar);                            \
                    lua_getinfo(L, "n", &ar);                           \
                    if (ar.name == NULL)                                \
                        ar.name = "?";                                  \
					char szbuff[1024];									\
					sprintf( szbuff, "Plot Error : Loop??\nFunc = %s , Cmd = %s",T->FuncName,ar.name);  \
					LUA_VMClass::ProcReg()->ExecuteTime	+= 10;		\
					OutputDebugString("Loop?");						\
					LUA_VMClass::OutputError( T->OwnerID,T->TargetID,T->FuncName,szbuff );	\
					return lua_yield(L,lua_gettop(L));				\
				}													\
			}														\
		}
#define _P_  _P1_( L )

//--------------------------------------------------------------------------
//		注意事項
//	1 是否每個函式都要有對應的執行物件 
//--------------------------------------------------------------------------
using		namespace std;
//---------------------------------------------------------------------------
enum MyVMValueTypeENUM
{
	MyVMValueType_Nil		,
	MyVMValueType_Number	,
	MyVMValueType_String	,
	MyVMValueType_Boolean	,
};

struct MyVMValueStruct
{
	MyVMValueTypeENUM	Type;

	double	Number;
	int		Number_Int;
	string	Str;
	bool	Flag;
};
//--------------------------------------------------------------------------
//劇情執行期事件
class	PlotRunTimeEvent
{
protected:
	//--------------------------------------------------------------------------
	//管理部份
	//--------------------------------------------------------------------------
	static vector<PlotRunTimeEvent*>	_ItemList;
	static vector<int>					_UnUsed;
	static bool							_DestroyEvent;	//是否有物件要刪除
public:
	static void OnTimeProc();							//定時處理函式

	static  PlotRunTimeEvent* GetObj(int Id);
	//--------------------------------------------------------------------------
	//使用者部份
	//--------------------------------------------------------------------------
protected:
	int		_ID;	
	bool	_Destroy;

public:
	PlotRunTimeEvent();
	~PlotRunTimeEvent();

	void	Destroy();							//刪除此物件
	
	virtual void OnBegin()	{};
	virtual void OnEnd()	{};
	virtual void OnError()	{};
};
//--------------------------------------------------------------------------
///目前劇情執行狀態的列舉資料
enum PlotRegType
{
	PlotEnd			= 0	,
	PlotRun			= 1 ,
	PlotMultiRun	= 2 , 
	PlotPCall		= 3 ,	//始用直接執行模式
	PlotBeginCall	= 4 ,	//使用 CallPlot, 第一次執行
	PlotPause		= 5 ,

};

//typedef bool (CALLBACK *CB_LuaUnlockTest)	( int VMID , void* context);

//typedef void (CALLBACK *CB_OutputError) (const char* error);

#define		_LOCK_LUA_SCRIPT(_L,_fu,_in)	{						\
			PlotRegStruct* _T = LUA_VMClass::ProcReg();				\
			if(_T != NULL)											\
			{														\
				_T->SetUnlockTest(_fu,_in);							\
				_T->ExecuteTime++;									\
				return lua_yield(_L,0);								\
			} else return 0;										\
		}

///儲存劇情執行時的狀態資料的結構
struct PlotRegStruct
{
	///呼叫的函式名稱
	char				FuncName[64];
	///執行時間
	unsigned int		ExecuteTime;
	//暫停時還差多少時間處理
	unsigned int		Pause_DTime;
	///劇情執行狀態
	PlotRegType			Type;
    //LUA ID
    int					ID;
	///執行所屬物件
	int					OwnerID;				
	///目標所屬物件
	int					TargetID;				
	///lua virtual machine id 哪個VM在處理
	int					L_StateID;

	ArgTransferStruct	Arg;
	//使用者設定的事件
	PlotRunTimeEvent	*Event;


    PlotRegStruct( )
	{
		Init();
	}

	void	Init()
    {
		FuncName[0] = 0;
		ExecuteTime = 0;	
		Type		= PlotEnd;
		ID			= 0;
		OwnerID		= 0;
		TargetID	= 0;
		L_StateID	= 0;

		Arg.Clear();
		Event		= NULL;
    }

    bool operator < ( const PlotRegStruct* B) const
    {
        return ExecuteTime < B->ExecuteTime ;
    }

    bool operator > ( const PlotRegStruct* B) const
    {
        return ExecuteTime > B->ExecuteTime ;
    }    
    bool operator ( ) (  const PlotRegStruct* A , const PlotRegStruct* B) const
    {
        return A->ExecuteTime > B->ExecuteTime ;
    }    
};
//--------------------------------------------------------------------------
//
struct LuaVarInfoStruct
{
	std::string Key;
	std::string Value;
	int			Type;
	int			Size;

	LuaVarInfoStruct()
	{
		Key = "";
		Value = "";
		Type = LUA_TNONE;
		Size = 0;
	}
};

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
/**
 *	@brief 管理執行劇情的 Virtual Machine
 *	靜態部分主要是控管所有VM的行為模式，
 *	動態部分是配置屬於自己的VM
 *	劇情的時間計算由 Process()一次為一個單位時間
 *	每個VM擁有屬於自己的劇情管理物件，互相不會影響
 */

class LUA_VMClass  
{
protected:

    struct StaticData
    {
		int						MaxVMCount;
        ///劇情的目前時間
		unsigned int            VMTime;
        //是否為PCall   不能始用Sleep
        bool                    IsPCall;
		bool					IsRunning;
		bool					IsAllowDebugger;
		bool					IsLogPCall;		 //是否記錄PCall的執行時的函式

        //把在Wait狀態的劇情丟入Queue內
        MyP_Queue<	PlotRegStruct*  , vector<PlotRegStruct*> , PlotRegStruct >     ExePlot;

        ///lua 的 vm
        lua_State*			    L_State;
        //-----------------------------------------------------------------------
        //	vm 資料管理
        //-----------------------------------------------------------------------
        ///目前尚未使用的VM
        vector<int>			    UnUsed_VM;
        //全部的資料
        vector<lua_State*>	    Host_VM;
        vector<lua_State*>	    Total_VM;
        //目前使用的對應表 TURE 使用中 FALSE 沒使用
        vector<bool>		    Total_VMState;
		//Lua thread跟VM User的對應
		map<lua_State*, LUA_VMClass*> VM_UserMapping;
        //-----------------------------------------------------------------------
        //預先配置PlotReg的記憶體 資料管理
        //-----------------------------------------------------------------------
        RecycleBin<PlotRegStruct>*	UnUsedPlotReg;
        //-----------------------------------------------------------------------
        //目前跑劇情處理的Reg
        PlotRegStruct*		    ProcReg;
        //-----------------------------------------------------------------------
        //系統VM
        //-----------------------------------------------------------------------
        LUA_VMClass*		    SysVM;

        vector<string>          FuncNameList;

        vector<int>			    UnusedID;

        //所有個人的資料
        vector<LUA_VMClass*>	All_VMUser;
            
        OutputDebugFunction     OutputErrorFunc;

        StaticData( int MaxVMCount );
        ~StaticData();
    };

    static StaticData*         _St;

    ///產生一個VM
    static	int					_NewVM(LUA_VMClass* VMUser);
    ///釋放一個VM
    static	bool				_FreeVM(int ID);
    ///取得某個VM 的lua 資料結構
    static  lua_State*			_GetLua_State(int ID);
    ///取得某目錄下的所有子目錄
    static  vector<string>*		_AllPathList( string FilePath );

    static	PlotRegStruct*		_NewPlotReg();
    static	void				_FreePlotReg(PlotRegStruct*);
	
	//目前執行的劇情
	static  string				_RunningPlotStr;
public:
	//此輪迴指令處理多少次，用來檢測是否有不合理的迴圈
	static	unsigned int ProcTimes;

	///@brief 初始化
	///初始化VM的所有能 
	///在使用所有VM 指令或能前一定要先執行過初始化
	static	bool	Init( int MaxVMCount = 3000 );

	///@brief 把配置資料清除
	static	void	Release();


	/// @brief 取得系統VM
	/// 主要是取得系統 VM 的指標，系統 VM 主要處理一般系統需要的劇情
	/// 或不屬於任何一個專屬 VM 的劇情
	/// @return 回傳系統VM的指標	
	static	LUA_VMClass*	SysVM()	{return _St->SysVM;};

	///取得某一個VM使用者
	static	LUA_VMClass*	GetVMUser(int ID);
	static	LUA_VMClass*	GetVMUser(lua_State* L);

	//for luadebugger
	static  int				GetOwnerID(lua_State* L);

	// 將所有VM執行工作終止掉, 包括系統VM
	// (!) 2004.06.08 Add by Luky
	static  void	StopAllVM();

	///Load 某一個目錄下 *.lua 的劇情資料到 VM
	static	void	LoadAllFile(string FilePath);

	///遞迴載入某目錄與其子目錄的檔案
	static	void	RecursiveLoadAllFile( string FilePath );

	///Load 某一個檔案 的劇情資料到 VM
	static	void	LoadFile(string FileName);


	///登入劇情指令 ， 設定劇情可使用得函式能
	static	void	RegFunction(string	FuncName,lua_CFunction FuncPoint);
		
	///劇情處理
	static	void	Process(int TimePass = 1);

    ///內定的劇情指令讓劇情暫停一段時間
	static	int Sleep(lua_State *L)
	{
		int T = (int)lua_tonumber(L,1);
		//當尚未初始化前則不處理此指令
		if( _St->ProcReg == NULL || _St->IsPCall != false )
			return 0;

		int iNum = lua_gettop (L);

		_St->ProcReg->ExecuteTime	+= T;
		return lua_yield(L,0);		
	}
	//---------------------------------------------------------------
    static int Hex( lua_State* L)
    {
        const char* T = lua_tostring(L,1);
//        char *stopstring;

        //int Value = strtol( T , NULL , 16 );
		int Value = (int)HexStrToUInt( T );

        lua_pushnumber( L , Value );
        return 1;
        
    }
	//---------------------------------------------------------------

	//---------------------------------------------------------------

	///取得執行中的暫存器
	static PlotRegStruct* ProcReg() {return _St->ProcReg ;};

	///記憶體檢查是否有異常
	static bool	CheckMemory( ){ return _St->UnUsedPlotReg->CheckAllMem(); };

    ///不能使用 Sleep 指令
    static void DoString( char* Str );
	static void DoBuffer( const char* Str , int Size, const char* Name = NULL );

    ///取得涵式名稱
    static vector<string>* GetFuncNameList( ){ return &_St->FuncNameList;};
    
    static lua_State*		L_State() { return _St->L_State; };
    static vector<string>*  FuncNameList() { return &_St->FuncNameList; };

    static void SetOutputErrorFunc( OutputDebugFunction Func );
	static void	OutputError( int OwnerID, int TargetID, const char* FunName , const char* pszMsg );

    //錯誤輸出
    static void DisplayError(lua_State * L,int errorcode,char* pInfo);

    //直接執行某 LUA 
    static bool PCall( string _Plot , int OwnerID , int TargetID , vector<MyVMValueStruct>* ArgList = NULL , vector<MyVMValueStruct>* RetList = NULL , int RetCount = 5 );
	//直接執行某 LUA  例: PlotCmd = Test( "ABC" , 109 )
	static bool PCallByStrArg( string PlotCmd , int OwnerID , int TargetID , vector<MyVMValueStruct>* RetList = NULL , int RetCount = 5 );

	static bool CheckFunc( string luaFunc );

	static void GetProcFuncName( char* pszFuncName );
	static int	GetProcFuncExecuteTime();

	//允許使用Lua Debugger
	static void AllowDebugger() {_St->IsAllowDebugger = true;}

	//將來源Lua Thread上指定位置的table複製一份到目標Lua Thread (目標Lua Thread不能同等於來源Thread )
	static void	CopyLuaTable( lua_State* src_thread, int src_idx, lua_State* dest_thread );

	//將Lua thread上指定位置的變數輸出成字串
	static std::string LuaVartoString(lua_State* L, int idx);

	//列出所有的Lua全域變數
	static void ListGlobalVariables(std::vector<LuaVarInfoStruct>& output, int filter);

	//取得Lua變數佔記憶體大小
	static int GetLuaDataSize(lua_State* L, int idx, std::set<std::string>* tableset);

	//取得Lua全域變數佔的記憶體大小
	static int GetLuaMemoryUsage();

	//取得LuaTable內容
	static bool GetLuaTableInfo(const char* tablename, std::vector<LuaVarInfoStruct>& info);

	//設定是否記錄PCall資訊
	static void SetIsLogPCall(bool value) {_St->IsLogPCall = value;}

//--------------------------------------------------------------------------
// 管理個人劇情的資料
//--------------------------------------------------------------------------
protected:

	//登入的劇情
    map<string,PlotRegStruct*>	_PlotProc;
	//此劇情的擁有者
    int         _OwnerID;

	int			_ID;

	//是否初始化成 
	bool		_Ready;

public:

	LUA_VMClass( int OwnerID  );
	~LUA_VMClass();

	///取得目前執行劇情的Map
    map<string,PlotRegStruct*>*	    PlotProc(){return &_PlotProc;};

	///檢查某一個lua 的劇情是否已在執行中
	bool	CheckLuaFunc(string FuncName);

	int					CallPlot			( lua_State *L, int iObjID, string sFuncName, int iNumArg );

	///劇情呼叫
	ArgTransferStruct*	CallLuaFunc			(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );
	///結束某一個劇情
	bool	EndLuaFunc(string FuncName);
	///結束所有執行的劇情
	bool	EndAllLuaFunc( );
	//暫停所有執行的劇情
	bool	PauseAllLuaFunc( );
	//把所有暫停的劇情繼續執行
	bool	StartAllLuaFunc( );
	///強制重新執行某一個劇情
	ArgTransferStruct*	ReCallLuaFunc(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );
	///同時可執行多個的行程(不能中斷)
	ArgTransferStruct*	MultiCallLuaFunc(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );

	//==========================================================================
	//			資料取得
	//==========================================================================	
	///擁有者ID
	int	GetOwner()	{return _OwnerID;};
	///是否致能
	bool GetReady()	{return _Ready;};


	// debug
	//------------------------------------------------------------
	void		SetLuaDebug();
	static void	LuaHookRoutine(lua_State *L, lua_Debug *ar);


};
#pragma managed

