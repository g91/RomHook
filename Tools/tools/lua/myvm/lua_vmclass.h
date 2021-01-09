//======================================================================================
/**
 * @file lua_vmclass.h lua_vmclass.cpp
 * �D�n�ΨӳB�z�@��������,�i�H�P�ɶ]�h�Ӽ@��\n
 * �i�Ψt��VM�]�@��\n
 * �]�i�H�w�q�ݩ�ۤv��VM�A�B�z�ݩ�ۤv���@��\n
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
//		��Ʃw�q
//--------------------------------------------------------------------------
///�w�q�̦h�i�H���h�֭�Virtual Machine
//#ifndef _MAX_LUA_VIRTUAL_MACHINE_
//	#define		_MAX_LUA_VIRTUAL_MACHINE_		3000
//#endif

///�j��@���̦h�B�z�h�֭Ӽ@�����O�A�p�G�W�L�h�@"����10���j"���ʧ@���@�q�ɶ��A�B�z
#define		_MAX_LUA_PROCESS_COUNT			10000									

//�w�qLUA_FuntionName �̤j���r�����
//#define		_MAX_LUA_FUNTIONNAMESIZE_		32
//--------------------------------------------------------------------------
/// �q�@��Marco ���C�Ӽ@�����O�@�ˬd���ʧ@
/// �D�n�O�ΨӬd�߼@���A�@���B�z�L�����O
/// �p�G�B�z�L�h�����O�h Waitting 10 �^�X�A�ÿ�X��ƨ�ù�

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
//		�`�N�ƶ�
//	1 �O�_�C�Ө禡���n�����������檫�� 
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
//�@��������ƥ�
class	PlotRunTimeEvent
{
protected:
	//--------------------------------------------------------------------------
	//�޲z����
	//--------------------------------------------------------------------------
	static vector<PlotRunTimeEvent*>	_ItemList;
	static vector<int>					_UnUsed;
	static bool							_DestroyEvent;	//�O�_������n�R��
public:
	static void OnTimeProc();							//�w�ɳB�z�禡

	static  PlotRunTimeEvent* GetObj(int Id);
	//--------------------------------------------------------------------------
	//�ϥΪ̳���
	//--------------------------------------------------------------------------
protected:
	int		_ID;	
	bool	_Destroy;

public:
	PlotRunTimeEvent();
	~PlotRunTimeEvent();

	void	Destroy();							//�R��������
	
	virtual void OnBegin()	{};
	virtual void OnEnd()	{};
	virtual void OnError()	{};
};
//--------------------------------------------------------------------------
///�ثe�@�����檬�A���C�|���
enum PlotRegType
{
	PlotEnd			= 0	,
	PlotRun			= 1 ,
	PlotMultiRun	= 2 , 
	PlotPCall		= 3 ,	//�l�Ϊ�������Ҧ�
	PlotBeginCall	= 4 ,	//�ϥ� CallPlot, �Ĥ@������
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

///�x�s�@������ɪ����A��ƪ����c
struct PlotRegStruct
{
	///�I�s���禡�W��
	char				FuncName[64];
	///����ɶ�
	unsigned int		ExecuteTime;
	//�Ȱ����ٮt�h�֮ɶ��B�z
	unsigned int		Pause_DTime;
	///�@�����檬�A
	PlotRegType			Type;
    //LUA ID
    int					ID;
	///������ݪ���
	int					OwnerID;				
	///�ؼЩ��ݪ���
	int					TargetID;				
	///lua virtual machine id ����VM�b�B�z
	int					L_StateID;

	ArgTransferStruct	Arg;
	//�ϥΪ̳]�w���ƥ�
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
 *	@brief �޲z����@���� Virtual Machine
 *	�R�A�����D�n�O���ީҦ�VM���欰�Ҧ��A
 *	�ʺA�����O�t�m�ݩ�ۤv��VM
 *	�@�����ɶ��p��� Process()�@�����@�ӳ��ɶ�
 *	�C��VM�֦��ݩ�ۤv���@���޲z����A���ۤ��|�v�T
 */

class LUA_VMClass  
{
protected:

    struct StaticData
    {
		int						MaxVMCount;
        ///�@�����ثe�ɶ�
		unsigned int            VMTime;
        //�O�_��PCall   ����l��Sleep
        bool                    IsPCall;
		bool					IsRunning;
		bool					IsAllowDebugger;
		bool					IsLogPCall;		 //�O�_�O��PCall������ɪ��禡

        //��bWait���A���@����JQueue��
        MyP_Queue<	PlotRegStruct*  , vector<PlotRegStruct*> , PlotRegStruct >     ExePlot;

        ///lua �� vm
        lua_State*			    L_State;
        //-----------------------------------------------------------------------
        //	vm ��ƺ޲z
        //-----------------------------------------------------------------------
        ///�ثe�|���ϥΪ�VM
        vector<int>			    UnUsed_VM;
        //���������
        vector<lua_State*>	    Host_VM;
        vector<lua_State*>	    Total_VM;
        //�ثe�ϥΪ������� TURE �ϥΤ� FALSE �S�ϥ�
        vector<bool>		    Total_VMState;
		//Lua thread��VM User������
		map<lua_State*, LUA_VMClass*> VM_UserMapping;
        //-----------------------------------------------------------------------
        //�w���t�mPlotReg���O���� ��ƺ޲z
        //-----------------------------------------------------------------------
        RecycleBin<PlotRegStruct>*	UnUsedPlotReg;
        //-----------------------------------------------------------------------
        //�ثe�]�@���B�z��Reg
        PlotRegStruct*		    ProcReg;
        //-----------------------------------------------------------------------
        //�t��VM
        //-----------------------------------------------------------------------
        LUA_VMClass*		    SysVM;

        vector<string>          FuncNameList;

        vector<int>			    UnusedID;

        //�Ҧ��ӤH�����
        vector<LUA_VMClass*>	All_VMUser;
            
        OutputDebugFunction     OutputErrorFunc;

        StaticData( int MaxVMCount );
        ~StaticData();
    };

    static StaticData*         _St;

    ///���ͤ@��VM
    static	int					_NewVM(LUA_VMClass* VMUser);
    ///����@��VM
    static	bool				_FreeVM(int ID);
    ///���o�Y��VM ��lua ��Ƶ��c
    static  lua_State*			_GetLua_State(int ID);
    ///���o�Y�ؿ��U���Ҧ��l�ؿ�
    static  vector<string>*		_AllPathList( string FilePath );

    static	PlotRegStruct*		_NewPlotReg();
    static	void				_FreePlotReg(PlotRegStruct*);
	
	//�ثe���檺�@��
	static  string				_RunningPlotStr;
public:
	//�����j���O�B�z�h�֦��A�Ψ��˴��O�_�����X�z���j��
	static	unsigned int ProcTimes;

	///@brief ��l��
	///��l��VM���Ҧ��� 
	///�b�ϥΩҦ�VM ���O�ί�e�@�w�n������L��l��
	static	bool	Init( int MaxVMCount = 3000 );

	///@brief ��t�m��ƲM��
	static	void	Release();


	/// @brief ���o�t��VM
	/// �D�n�O���o�t�� VM �����СA�t�� VM �D�n�B�z�@��t�λݭn���@��
	/// �Τ��ݩ����@�ӱM�� VM ���@��
	/// @return �^�Ǩt��VM������	
	static	LUA_VMClass*	SysVM()	{return _St->SysVM;};

	///���o�Y�@��VM�ϥΪ�
	static	LUA_VMClass*	GetVMUser(int ID);
	static	LUA_VMClass*	GetVMUser(lua_State* L);

	//for luadebugger
	static  int				GetOwnerID(lua_State* L);

	// �N�Ҧ�VM����u�@�פ, �]�A�t��VM
	// (!) 2004.06.08 Add by Luky
	static  void	StopAllVM();

	///Load �Y�@�ӥؿ��U *.lua ���@����ƨ� VM
	static	void	LoadAllFile(string FilePath);

	///���j���J�Y�ؿ��P��l�ؿ����ɮ�
	static	void	RecursiveLoadAllFile( string FilePath );

	///Load �Y�@���ɮ� ���@����ƨ� VM
	static	void	LoadFile(string FileName);


	///�n�J�@�����O �A �]�w�@���i�ϥαo�禡��
	static	void	RegFunction(string	FuncName,lua_CFunction FuncPoint);
		
	///�@���B�z
	static	void	Process(int TimePass = 1);

    ///���w���@�����O���@���Ȱ��@�q�ɶ�
	static	int Sleep(lua_State *L)
	{
		int T = (int)lua_tonumber(L,1);
		//��|����l�ƫe�h���B�z�����O
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

	///���o���椤���Ȧs��
	static PlotRegStruct* ProcReg() {return _St->ProcReg ;};

	///�O�����ˬd�O�_�����`
	static bool	CheckMemory( ){ return _St->UnUsedPlotReg->CheckAllMem(); };

    ///����ϥ� Sleep ���O
    static void DoString( char* Str );
	static void DoBuffer( const char* Str , int Size, const char* Name = NULL );

    ///���o�[���W��
    static vector<string>* GetFuncNameList( ){ return &_St->FuncNameList;};
    
    static lua_State*		L_State() { return _St->L_State; };
    static vector<string>*  FuncNameList() { return &_St->FuncNameList; };

    static void SetOutputErrorFunc( OutputDebugFunction Func );
	static void	OutputError( int OwnerID, int TargetID, const char* FunName , const char* pszMsg );

    //���~��X
    static void DisplayError(lua_State * L,int errorcode,char* pInfo);

    //��������Y LUA 
    static bool PCall( string _Plot , int OwnerID , int TargetID , vector<MyVMValueStruct>* ArgList = NULL , vector<MyVMValueStruct>* RetList = NULL , int RetCount = 5 );
	//��������Y LUA  ��: PlotCmd = Test( "ABC" , 109 )
	static bool PCallByStrArg( string PlotCmd , int OwnerID , int TargetID , vector<MyVMValueStruct>* RetList = NULL , int RetCount = 5 );

	static bool CheckFunc( string luaFunc );

	static void GetProcFuncName( char* pszFuncName );
	static int	GetProcFuncExecuteTime();

	//���\�ϥ�Lua Debugger
	static void AllowDebugger() {_St->IsAllowDebugger = true;}

	//�N�ӷ�Lua Thread�W���w��m��table�ƻs�@����ؼ�Lua Thread (�ؼ�Lua Thread����P����ӷ�Thread )
	static void	CopyLuaTable( lua_State* src_thread, int src_idx, lua_State* dest_thread );

	//�NLua thread�W���w��m���ܼƿ�X���r��
	static std::string LuaVartoString(lua_State* L, int idx);

	//�C�X�Ҧ���Lua�����ܼ�
	static void ListGlobalVariables(std::vector<LuaVarInfoStruct>& output, int filter);

	//���oLua�ܼƦ��O����j�p
	static int GetLuaDataSize(lua_State* L, int idx, std::set<std::string>* tableset);

	//���oLua�����ܼƦ����O����j�p
	static int GetLuaMemoryUsage();

	//���oLuaTable���e
	static bool GetLuaTableInfo(const char* tablename, std::vector<LuaVarInfoStruct>& info);

	//�]�w�O�_�O��PCall��T
	static void SetIsLogPCall(bool value) {_St->IsLogPCall = value;}

//--------------------------------------------------------------------------
// �޲z�ӤH�@�������
//--------------------------------------------------------------------------
protected:

	//�n�J���@��
    map<string,PlotRegStruct*>	_PlotProc;
	//���@�����֦���
    int         _OwnerID;

	int			_ID;

	//�O�_��l�Ʀ� 
	bool		_Ready;

public:

	LUA_VMClass( int OwnerID  );
	~LUA_VMClass();

	///���o�ثe����@����Map
    map<string,PlotRegStruct*>*	    PlotProc(){return &_PlotProc;};

	///�ˬd�Y�@��lua ���@���O�_�w�b���椤
	bool	CheckLuaFunc(string FuncName);

	int					CallPlot			( lua_State *L, int iObjID, string sFuncName, int iNumArg );

	///�@���I�s
	ArgTransferStruct*	CallLuaFunc			(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );
	///�����Y�@�Ӽ@��
	bool	EndLuaFunc(string FuncName);
	///�����Ҧ����檺�@��
	bool	EndAllLuaFunc( );
	//�Ȱ��Ҧ����檺�@��
	bool	PauseAllLuaFunc( );
	//��Ҧ��Ȱ����@���~�����
	bool	StartAllLuaFunc( );
	///�j��s����Y�@�Ӽ@��
	ArgTransferStruct*	ReCallLuaFunc(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );
	///�P�ɥi����h�Ӫ���{(���त�_)
	ArgTransferStruct*	MultiCallLuaFunc(string FuncName,int Target,unsigned int ExeTime = 0 , PlotRunTimeEvent* Listen = NULL );

	//==========================================================================
	//			��ƨ��o
	//==========================================================================	
	///�֦���ID
	int	GetOwner()	{return _OwnerID;};
	///�O�_�P��
	bool GetReady()	{return _Ready;};


	// debug
	//------------------------------------------------------------
	void		SetLuaDebug();
	static void	LuaHookRoutine(lua_State *L, lua_Debug *ar);


};
#pragma managed

