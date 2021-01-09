/*************************************************************************************\
Class: VivoxClient

Usage: store necessary data for vivox SDK using;

Setup: Copy Vivox SDK(vivox-sdk-3.0.0006.7545-Release-win32) into related path
		.\Client\Ispania\tools\Vivox\VivoxLib\core

LOG:
	GKy 091202 start

	GKy 091211 Channel Name Format Definition:

	1. Team Channle

		CHANNELNAME_WN_teamID
		type	world	sys_id

	2. Customize CH

		GROUP_1_1
		RUNEWAKER_1_0

	GKy 091229 Channel Name Format please see code. sample
		Format: Territory.SecureCode_ChannelType_WorldID_SysID

    slime 2010/10/21 - start refactoring all :
    * remove all static, change to singleton pattern.
    * remove some macro, change to function.
    * remove all MFC CString object.
    * remove useless include.
    * remove useless code.
    * remove some debug code.
    * remove meaningless comment.
    * fix bug.
    * rename.
    * change some get/set function to inline
    * add real VOD effect.

    slime 2010/11/11 - start update vivox lib - ver.3.2.2.9361
    * change some command.

\*************************************************************************************/

#pragma once

#define VIVOX_USE_SINGLETON 0                       // 是否使用 static referance singleton (預設不使用)
#define VIVOX_CHECK_SINGLETON_COUNT 1               // 是否檢查 singleton 總數 (建議開啟)

#define VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_01 0    // 追蹤 g_pInterface->SendWorldEvent()
#define VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_02 0    // 將 Core Command 印到 Chat Frame 上.
#define VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_03 0    // 將一般訊息印到 Chat Frame 上.
#define VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_04 0    // 將錯誤訊息印到 Chat Frame 上.

#define VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME 0    // 追蹤函式呼叫順序 (for debug)
#define VIVOX_CLIENT_DEBUG_PRINT_COMMAND_EXEC 1     // 是否印出 Core Command (for debug)
#define VIVOX_CLIENT_DEBUG_PRINT_OUTPUT_INFO 0      // 是否印出一般訊息 (包含 command echo)
#define VIVOX_CLIENT_DEBUG_PRINT_ERROR_INFO 1       // 是否印出錯誤訊息 (for debug)

#pragma comment(lib, "vivoxsdk.lib") 
#pragma comment(lib, "vivoxplatform.lib") 

#include <fstream> // std::ifstream

#include "VivoxLib/SDKSampleApp.h"
#include "VivoxLib/ParticipantState.h"

#define VVX_DEBUG 0
#define VVX_CORE_OFF 0
#define VVX_PATH_LOG ".\\VivoxLogs\\VivoxClient\\VivoxClient.log"

#define VVX_WORLD_EVT_PART_UPDATE   "Voice_Chat_World_Event_Part_Update"
#define VVX_WORLD_EVT_PART_SILENT   "Voice_Chat_World_Event_Part_Silent"
#define VVX_WORLD_EVT_PART_MUTE_ON  "Voice_Chat_World_Event_Part_Mute_On"
#define VVX_WORLD_EVT_PART_MUTE_OFF "Voice_Chat_World_Event_Part_Mute_Off"
#define VVX_WORLD_EVT_CH_JOIN       "Voice_Chat_World_Event_Ch_Join"
#define VVX_WORLD_EVT_CH_EXIT       "Voice_Chat_World_Event_Ch_Exit"
#define VVX_WORLD_EVT_CH_JOIN_PART  "Voice_Chat_World_Event_Ch_Join_Partner"
#define VVX_WORLD_EVT_CH_EXIT_PART  "Voice_Chat_World_Event_Ch_Exit_Partner"
#define VVX_WORLD_EVT_ENABLE_OK     "Voice_Chat_World_Event_Enable_OK"
#define VVX_WORLD_EVT_DISABLE_OK    "Voice_Chat_World_Event_Disable_OK"

// Internal Event
#define VVX_SELF_EVT_ACC_CREATE_RETRY   "Voice_Chat_Self_Event_Acc_Create_Retry" 
#define VVX_SELF_EVT_SM_DISCONNECTED    "Voice_Chat_Self_Event_SessionMedia_Disconnected" 
#define VVX_SELF_EVT_CH_JOIN_START      "Voice_Chat_Self_Event_Ch_Join_Start"
#define VVX_SELF_EVT_CH_JOIN_OK         "Voice_Chat_Self_Event_Ch_Join_OK"
#define VVX_SELF_EVT_CH_EXIT_OK         "Voice_Chat_Self_Event_Ch_Exit_OK"

#if VVX_DEBUG ///////////////////////////////////
#define VVX_SELF_EVT_DEBUG_RM_VVX_ACC_RE "Voice_Chat_Self_Event_Debug_RM_VVX_ACC_Re" // GKy 100206 add for deBug
#endif // #if VVX_DEBUG ///////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

// GKy 100128 now deisgn, VVX_SVR_URL, VVX_CLN_ACC, VVX_CLN_PWD all set up by Game Server
//#define VVX_SVR_URL     "DefaultServerURL" // Server URL GKy 100122 default can`t as empty, need trigger txErr handle
#define VVX_SVR_URL_EMPTY "EmptyServerURL" // Server URL GKy 100129 for get Null string handle

//#define VVX_CLN_ACC   "DefaultAccount" // Default Client Account
#define VVX_CLN_ACC   "_?DefaultAccount" // Default Client Account // GKy 100208 for distinguish to normal acc
//#define VVX_CLN_ACC   "_DefaultVivoxAccount" // GKy 100211 redefine for Log also worked. BUT seems not so good
#define VVX_CLN_PWD   "_?DefaultPassword" // Default Client Password

#if VVX_DEBUG ////////////////////////////////// GKy 100208 add for deBug
#define VVX_CLN_ACC_DEBUG_S  "test38rw"
#define VVX_CLN_ACC_DEBUG  "test41rw" // "test40rw"
#define VVX_CLN_PWD_DEBUG  "C58A2A78" // "23410D90"
#endif // #if VVX_DEBUG ////////////////////////////////// GKy 100208 add for deBug

// GKy 100120 have bug, like if SVR domain changed, try fix.
// GKy 100128 real ECHO channel URI will update at Account Check process.
//#define VVX_ECHO_CHL_URI   "sip:confctl-2@rwp.vivox.com" // Channel ID : Echo, for test

// Special String
#define VVX_CH_NAME_TEST "VvxTestCh" // GKy 100112 only for Internal use.

// +++ Channel Name Rule +++
//#define VVX_CH_NAME_FORMAT001 "iSpAniA8401_%d_%d_%d" // GKy 091218
// Format: SecretCode_ChType_WorldID_SysID
//#define VVX_CH_NAME_FORMAT002 "%s.iSpAniA8511_%d_%d_%d" // GKy 091221
//#define VVX_CH_NAME_FORMAT002 "%s.iSpAniA7551_%d_%d_%s" // GKy 091228
// Format: Territory.SecureCode_ChannelType_WorldID_SysID

//#define VVX_STATE_UPDATE_MAX 100 // GKy 091215
//#define VVX_STATE_UPDATE_MAX 0 // GKy 091215 -- GKy 100108 obsolete
//#define VVX_MAX_PARTNER 5000 // GKy 100108

// 不知道為何預設 Partner 需要用到 5000, 所以降低為 100 (一百人同時使用也很扯了)

/////////////////////////////////////////////////////////////////////////////////////////

#define VVX_SYS_MSG(DB_ID)\
	g_ObjectData->GetString(#DB_ID)

#define VIVOX_CASE_ENUM_NAME(e, d)\
{\
    case e:\
        r << #e << " " << d;\
        break;\
}

//#define VIVOX_CLIENT_WAIT_RESPONSE_TIME_DEFAULT 250 // 預設回應等待時間(數字越大等待越久)

///////////////////////////////////////////////////

enum VVX_CH_TYPE
{
    VVX_CH_TYPE_NULL = 0,
    VVX_CH_TYPE_TEAM = 1,   // bind to Team/Raid
    VVX_CH_TYPE_USER = 2,   // bind to user create channel
    VVX_CH_TYPE_GUILD = 3,  // bind to Guild

    VVX_CH_TYPE_MAX
};

enum VVX_STATE
{
    VVX_STATE_IDLE = 0,         // default, no connect to Vivox server
    VVX_STATE_INIT,             // connect to Vivox server
    VVX_STATE_INIT_OK,
    VVX_STATE_SHUTDOWN,         // disconnect to Vivox server
    VVX_STATE_SHUTDOWN_OK,
    VVX_STATE_LOGIN,            // Normal Login
    VVX_STATE_LOGIN_OK,
    VVX_STATE_LOGIN_ANY,        // anonymous Login
    VVX_STATE_LOGIN_ANY_OK,     // no need this state? GKy 091217 still need..? BUT..
    VVX_STATE_LOGOUT,           // Normal Logout
    VVX_STATE_LOGOUT_OK,
    VVX_STATE_ACC_UPDATE,       // >updateaccount
    VVX_STATE_ACC_UPDATE_OK,
    VVX_STATE_SG_CREATE,        // session group operation state
    VVX_STATE_SG_CREATE_OK,
    VVX_STATE_SG_DEL,
    VVX_STATE_SG_DEL_OK,
    VVX_STATE_SS_ADD,           // channel(session) operation state
    VVX_STATE_SS_ADD_OK,
    VVX_STATE_SS_REMOVE,
    VVX_STATE_SS_REMOVE_OK,
    // session_media state change
    VVX_STATE_SM_DISCONNECTING,
    VVX_STATE_SM_DISCONNECTED,
    // GKy 100104 Only as para, Seems no resp?..
    VVX_STATE_PART_MUTE,        // >localusermute
    VVX_STATE_PART_MUTE_OK,
    VVX_STATE_CH_CREATE_ECHO,   // GKy 100120 for get Echo Channel URI.
    VVX_STATE_CH_CREATE,        // channel management operation
    VVX_STATE_CH_CREATE_OK,
    VVX_STATE_CH_DEL,           //
    VVX_STATE_CH_DEL_OK,
    VVX_STATE_ADJUST,           // Generic Adjust Transaction
    VVX_STATE_ADJUST_OK,        // GKy 100201 seems less to use? ..
    VVX_STATE_ADJUST_IN_DEV,    // >setcapturedev
    VVX_STATE_ADJUST_OUT_DEV,   // >setrenderdev

    VVX_STATE_MAX
};

enum VVX_CASE
{
    VVX_CASE_IDLE = 0,          // default
    //VVX_CASE_ENABLE,          // may be exH, due to no need this tX anymore.
    VVX_CASE_DISABLE,
    //VVX_CASE_LOGIN,
    //VVX_CASE_LOGIN_ANY,
    VVX_CASE_CH_JOIN_INIT,
    VVX_CASE_CH_JOIN_CREATE,
    VVX_CASE_ACC_CHECK,
    VVX_CASE_CH_JOIN_ADD,
    //VVX_CASE_CH_JOIN_ADD_OK,  // GKy 091215, 091216 obsolete, use VVX_CASE_IDLE; instead
    //VVX_CASE_CH_EXIT_INIT_TEST,   //+++ GKy 100112 add for TestEnd case, other same to VVX_CASE_CH_EXIT_INIT but..
    VVX_CASE_CH_EXIT_INIT,
    //VVX_CASE_CH_EXIT_LAST,    // Last one exit
    //VVX_CASE_CH_EXIT_NOR,     // Normal exit
    //VVX_CASE_CH_EXIT_REJOIN,  //+++ GKy 100118 add for reJoin handle. GKy 100121 seems obsolete?
    // Case Test +++
    VVX_CASE_TEST_INIT,         // GKy 091215, seems can as internal or Just an init case..
    // +++in other words, this case never assign to VivoxClient::m_iVVXcase
    //VVX_CASE_TEST_ADD,        // GKy 091217, seems no need, we need ensure para(ChName) always can be set
    VVX_CASE_TEST_END_INIT,     // GKy 091217, merge to VVX_CASE_CH_EXIT_INIT, GKy 091223 only as ChExit in para.
    // +++never assign to VivoxClient::m_iVVXcase
    //VVX_CASE_TEST_END_NOR,
    // Persistance Case +++++++++++++++++++++++
    VVX_CASE_in_TEAM, // in a specific channel
    VVX_CASE_in_TEST, // in test echo channel
    // Case Adjust ++++++++++++++++++++++++++++
    VVX_CASE_IN_DEV_SET,
    VVX_CASE_IN_DEV_GET,
    VVX_CASE_OUT_DEV_SET,
    VVX_CASE_OUT_DEV_GET,
    //VVX_CASE_VOL_MIC_SET,     // set process need get List at first.
    //VVX_CASE_VOL_MIC_GET,
    //VVX_CASE_VOL_SPK,

    VVX_CASE_MAX
};

enum VVX_INPUT_MODE
{
    VVX_INPUT_MODE_NULL = 0,
    VVX_INPUT_MODE_DETECT = 1,
    VVX_INPUT_MODE_PTT = 2,

    VVX_INPUT_MODE_MAX
};

enum VVX_LOGIN_MODE
{
    VVX_LOGIN_MODE_INIT = 0, // Follow Default Set.
    VVX_LOGIN_MODE_NA, // Not Available (Can try enable voice BUT can`t join voice Ch)
    VVX_LOGIN_MODE_ANY, // anonymous Login
    VVX_LOGIN_MODE_NOR, // With Normal Account
    /************* TEST MODE ******************/
    VVX_LOGIN_MODE_TEST_SVR_ERR, // #test Server No Send Msg
    VVX_LOGIN_MODE_TEST_NEW_ERR, // #test When Client demand Create new Acc, no response
    VVX_LOGIN_MODE_TEST_ACC_ERR, // #test Acc Check Login Err, like wrong password etc.

    VVX_LOGIN_MODE_MAX
};

class VivoxClient
{
#if VIVOX_USE_SINGLETON
private:
    VivoxClient();                              // ctor is hidden

    VivoxClient(VivoxClient const&);            // copy ctor is hidden
    VivoxClient& operator=(VivoxClient const&); // assign op is hidden

public:
    ~VivoxClient();

    static VivoxClient& GetInstance()
    {
        static VivoxClient s_instance;
        return s_instance;
    }
#else
private:
    VivoxClient();                              // ctor is hidden

    VivoxClient(VivoxClient const&);            // copy ctor is hidden
    VivoxClient& operator=(VivoxClient const&); // assign op is hidden

#if VIVOX_CHECK_SINGLETON_COUNT
    static unsigned int sm_uiInstanceCount;
#endif

public:
    static VivoxClient* sm_pkInstance;
    static VivoxClient* GetInstance();
    static void DeleteInstance();

    ~VivoxClient();
#endif

    //////////////////////////////////////////////////////////////////////////

    void            Initial();
    void            InitialApp(VivoxConsoleOutputCallback stdcout, VivoxConsoleOutputCallback stdcerr,
                                void* handle = NULL, int argc = 0, char** argv = NULL);
    void            Release();
    void            LoadSystemSettings();
    void            InitialSystemSetting();
    void            SaveSystemSettings();

    //////////////////////////////////////////////////////////////////////////

    std::vector<std::string> splitCmdLine(const std::string &s);
    std::vector<std::string> splitCmdLine(const std::string &s, char cut_char);

    void            PrintToChatFrame(const char* theMessage);
    void            VivoxOutputPrintWithLog(const char* str_message);
    void            VivoxOutputPrint(void* h, const char* s);
    void            VivoxErrorPrint(void* h, const char* s);

    //////////////////////////////////////////////////////////////////////////

    void            InitialCaseEnum(VVX_CASE case_new);
    void            SetCaseEnum(VVX_CASE case_new);
    bool            IsCaseEnumChanged();

    inline VVX_CASE GetCaseEnum() { return m_iCase; }
    inline VVX_CASE GetCaseEnumPrevious() { return m_iCasePrevious; }

    // GKy 100118, for transaction init use
    // GKy 100201, change name: STATEget => STATEdetect; origin STATEget real for get the VVXstate value
    VVX_STATE		DetectState(); 

    std::string     GetModeName(int mode_enum = VVX_INPUT_MODE_MAX);
    std::string     GetCaseEnumName(VVX_CASE case_enum = VVX_CASE_MAX);
    std::string		GetStateName(VVX_STATE state_enum = VVX_STATE_MAX);

    //////////////////////////////////////////////////////////////////////////

	void            ProcessCoreCommand(const char* cmd_input); // Command to Core

    // CC = CoreCommand
    void            CC_Initial();
    void            CC_Shutdown();
    void            CC_Login();
    void            CC_AnonymousLogin();
    void            CC_Logout();
    void            CC_CreateSessionGroup();
    void            CC_TerminateSessionGroup(const char* group_name);
    void            CC_AddSessionIntoSessionGroup(const char* group_name);
    void            CC_RemoveSessionFromSessionGroup(); // TODO:
    void            CC_CreateEchoChannel();
    void            CC_CreateChannel();
    void            CC_SetupInputDevice();
    void            CC_SetupOutputDevice();
    void            CC_UpdateAccount();
    void            CC_LocalUserMute(); // TODO:

    void            CC_SetupInputMute(bool isMute);
    void            CC_SetupInputVolumn(int nValue);
    void            CC_SetupInputSensitivity(int nValue, int nHangoverTime = 1); // (HangoverTime 單位:秒)
    void            CC_SetupOutputVolumn(int nValue);

    void            CC_ListInputDevice();
    void            CC_ListOutputDevice();

	int             ProcessByState(VVX_STATE state_enum, const char* cmd_param); // Integration of Steps
    int             ProcessByUpdateState(VVX_STATE state_enum);
	int             ProcessGeneric();

	/////////////////////////////////////////////////////////////
	// Generic Operations ///////////////////////////////////////

	//bool is_connect(); // try #Macro instead

    inline bool     IsEnable() { return m_bEnable; }
	bool            IsInTest(); 
	bool            IsInChannel();
	int             IsBusy();

    bool            IsConnect();
    bool            IsLogin();
    bool            IsCreate();

	// Partner State Check Operations.
	bool            IsPlayerInVoiceChannel(int DBid);
	int             IsPlayerMute(int DBid);
	int             IsPlayerSpeaking(int DBid);

	/************************************************
		iAccCheckRetry : -1 //   No Account Checking
		iAccCheckRetry : 0  // Only Account Checking, no   try make new Account
		iAccCheckRetry : N  //      Account Checking, also try make new Account
	************************************************/
    // default (iAccCheckRetry = -1, bCheckEnable = 1)
	int             Enable(int iAccountCheckRetry, int bCheckEnable);

    // default (bCheckEnable = 1)
	int             Disable(int bCheckEnable);
	int             DisableWithInitialCase();

	void            UpdateState();

	void            CheckAccount();

	// Operations for Channel
	std::string     GetChannelName(VVX_CH_TYPE channel_type, int world_id, int sys_id); // for create unique name
	std::string     GetChannelName(VVX_CH_TYPE channel_type, int world_id, const char* sys_id);

	std::string     GetChannelNamePrevious(bool bMustGet = false);
	void            SetChannelNamePrevious(const char* str);

    //////////////////////////////////////////////////////////////////////////

	int             JoinChannel(const char* channel_name, int user_id, VVX_CASE case_enum = VVX_CASE_CH_JOIN_INIT);
	int             JoinChannelWithInitialCase(VVX_CASE case_enum);

	int             ExitChannel(const char* channel_name = NULL, VVX_CASE case_enum = VVX_CASE_CH_EXIT_INIT);
	int             ExitChannelWithInitialCase();

    int             Disconnected();

    //////////////////////////////////////////////////////////////////////////

	//void close(void); // GKy 100107 for set LoginModeNA using. may be..
    // default (bIfSendWorldEvt = 1)
	void            Close(int bIfSendWorldEvt);

	// GKy 100104 for zS
	void            PartnerMute(int iDBid, bool bYes);

    int             GetDBID();
    void            SetDBID(int iDBid);

	// Operations for Options ////////////////
	void            SetAllVolumn();
	void            SetAllVolumn(int micVol, int spkVol, int micSen);

	inline int      GetInputMode() { return static_cast<int>(m_iInputMode); }
	void            SetInputMode(int iMode);
	void            SetInputMute(bool isMute);
	void            SetInputVolumn(int vol);
	void            SetInputSensitivity(int vol);
	void            SetInputSensSwitch(double dEnergy); // GKy 100114 for Sensitivity, internal using
    void            SetOutputVolumn(int vol);
    double          GetSelfEnergy();

    //////////////////////////////////////////////////////////////////////////

    void            ConstrainVolumn(int& nValue);

    void            WaitDeviceResponse(int WaitTime);
    void            WaitResponse(int WaitTime);

    int             GetInputDeviceIndex();
	void            SetInputDeviceIndex(int Index);
    int             GetOutputDeviceIndex();
    void            SetOutputDeviceIndex(int Index);

    //////////////////////////////////////////////////////////////////////////

	void            TestStart(); /// //+
	void            TestEnd(); // //+

	void            DumpMessage(); // for GameMain.cpp dump str to ChatFrame
	void            AppendMessage(const char* str_message); // GKy 091218 push message into a queue
	std::string     AppendMessageEvent(const char* str_type, const char* str_id);

	// GKy 100211 add for some reset, like player select another character
	void            LeaveWorld(); // --may be obsolete, keep for other usage
	void            OnRevServerList(); // ++try this

	void            FlushLog(const char* str_log);

#if VVX_DEBUG
	void            debug_CNetCli_Login_Child__RM_VivoxAccount(const char* pszAccout, const char* pszPassword, bool bCreateResult);
#endif // VVX_DEBUG

    void            CheckInputDeviceIndexRange();

    //////////////////////////////////////////////////////////////////////////

    inline void Enable_With_CheckAccount() { Enable(-1, 1); }
    inline void Enable_Without_CheckAccount() { Enable(0, 1); }
    inline void Enable_And_SkipAllCheck() { Enable(0, 0); }

    inline void Disable_Without_CheckEnable() { Disable(0); }
    inline void Disable_With_CheckEnable() { Disable(1); }

    inline void Close_Without_Message() { Close(0); }
    inline void Close_With_AppendMessage() { Close(1); }

    //////////////////////////////////////////////////////////////////////////

    inline VVX_LOGIN_MODE   GetLoginMode(void) { return m_iLoginMode; }
    inline void         SetLoginMode(VVX_LOGIN_MODE mod_enum) { m_iLoginMode = mod_enum; }

    inline int          GetLoginRetry(void) { return m_iLoginRetry; }
    inline void         SetLoginRetry(int v) { m_iLoginRetry = v; }

    inline std::string  GetAccount() { return m_strAccount; }
    inline void         SetAccount(const char* Acc) { m_strAccount = Acc; }

    inline std::string  GetPassword() { return m_strPassword; }
    inline void         SetPassword(const char* Pwd) { m_strPassword = Pwd; }

    //inline void             ServerURLset(const char* str) { m_sVivoxServerURL = str; }
    inline std::string  GetServerURL() { return m_strServerURL; }
    void                SetServerURL(const char* str);

    inline std::string  GetEchoURI() { return m_strEchoChannelURI; }
    inline void         SetEchoURI(const char* str) { m_strEchoChannelURI = str; }

    inline std::string  GetCurrentChannelName(void) { return m_strChannelName; }
    inline void         SetCurrentChannelName(const char* str) { m_strChannelName = str; }

    //////////////////////////////////////////////////////////////////////////

    inline ParticipantGroup&    GetPartiGroupRef() { return m_ParticipantGroup; }
    inline ParticipantState&    GetPartiStateRef() { return m_ParticipantState; }

    inline int          GetPartnerDBidLast() { return m_iPartnerDBidLast; }
    inline void         SetPartnerDBidLast(int nValue) { m_iPartnerDBidLast = nValue; }

    inline VVX_STATE    GetVivoxState() { return m_eVivoxState; }
    inline void         SetVivoxState(VVX_STATE state_enum) { m_eVivoxState = state_enum; }
    inline VVX_CASE     GetVivoxCase() { return m_eVivoxCase; }
    inline void         SetVivoxCase(VVX_CASE case_enum) { m_eVivoxCase = case_enum; }

    inline int          GetOutputDebugMessage() { return m_iOutputDebugMessage; }
    inline void         SetOutputDebugMessage(int nValue) { m_iOutputDebugMessage = nValue; }

    //inline std::string& AccountString() { return m_strAccount; }
    //inline std::string& PasswordString() { return m_strPassword; }
    inline std::string& ServerURLString() { return m_strServerURL; }
    //inline std::string& EchoChannelURIString() { return m_strEchoChannelURI; }
    inline std::string& ChannelURIString() { return m_strChannelURI; }
    inline std::string& ChannelNameString() { return m_strChannelName; }
    inline std::string& ChannelNamePrefixString() { return m_strChannelNamePrefix; }
    inline std::string& ChannelNamePreviousString() { return m_strChannelNamePrevious; }

    inline size_t       GetInputDevicesTotalSize() { return m_mapInputDevices.size(); }
    inline std::string& InputDeviceNameString() { return m_mapInputDevices[m_iInputDeviceIndex]; }
    inline std::string& InputDeviceNameStringByIndex(unsigned int Index) { return m_mapInputDevices[Index]; }
    inline void         ClearInputDevices() { m_mapInputDevices.clear(); }

    inline size_t       GetOutputDevicesTotalSize() { return m_mapOutputDevices.size(); }
    inline std::string& OutputDeviceNameString() { return m_mapOutputDevices[m_iOutputDeviceIndex]; }
    inline std::string& OutputDeviceNameStringByIndex(unsigned int Index) { return m_mapOutputDevices[Index]; }
    inline void         ClearOutputDevices() { m_mapOutputDevices.clear(); }

    //////////////////////////////////////////////////////////////////////////

    inline bool         GetSysEnable()              { return m_bSysEnableVoiceChat; }
    inline bool         GetSysInputMute()           { return m_bSysInputMute; }
    inline int          GetSysInputMode()           { return m_iSysInputMode; }
    inline int          GetSysInputDeviceIndex()    { return m_iSysInputDeviceIndex; }
    inline int          GetSysInputVolumn()         { return m_iSysInputVolumn; }
    inline int          GetSysInputSensitivity()    { return m_iSysInputSensitivity; }
    inline int          GetSysOutputDeviceIndex()   { return m_iSysOutputDeviceIndex; }
    inline int          GetSysOutputVolumn()        { return m_iSysOutputVolumn; }

    inline void         SetSysEnable(bool bFlag)            { m_bSysEnableVoiceChat = bFlag; }
    inline void         SetSysInputMute(bool bFlag)         { m_bSysInputMute = bFlag; }
    inline void         SetSysInputMode(int nValue)         { m_iSysInputMode = nValue; }
    inline void         SetSysInputDeviceIndex(int nValue)  { m_iSysInputDeviceIndex = nValue; }
    inline void         SetSysInputVolumn(int nValue)       { m_iSysInputVolumn = nValue; }
    inline void         SetSysInputSensitivity(int nValue)  { m_iSysInputSensitivity = nValue; }
    inline void         SetSysOutputDeviceIndex(int nValue) { m_iSysOutputDeviceIndex = nValue; }
    inline void         SetSysOutputVolumn(int nValue)      { m_iSysOutputVolumn = nValue; }

    //////////////////////////////////////////////////////////////////////////

#if 0 // do not publish this when release.
    inline SDKSampleApp* GetInnerApp() { return m_pkVivoxApp; }
#endif

protected:

private:
    static const int c_DefaultWaitResponseTime = 250;//250  // 預設回應等待時間(數字越大等待越久)
    static const int c_DefaultMaxPartips = 5000;//5000      // 預設最大??????數.

    //////////////////////////////////////////////////////////////////////////

    // Vovix 用鎖定物件(範本內只有兩個)
    vxplatform::Lock* s_w_iolock;
    vxplatform::Lock* s_e_iolock;
    vxplatform::Lock* s_o_iolock;
    vxplatform::Lock* s_p_iolock;

    SDKSampleApp*   m_pkVivoxApp;       // 主要執行類別.

    ParticipantGroup    m_ParticipantGroup;
    ParticipantState    m_ParticipantState;
    int             m_iPartnerDBidLast; // GKy 091229 using this replace up for solving Critical Section problem

    int             m_iLoginRetry;      // 登入重試.
    VVX_LOGIN_MODE  m_iLoginMode;       // 登入模式.

    // update by slime - 2010/10/25
    VVX_STATE       m_eVivoxState;      // renamed g_iVVXstate
    VVX_CASE        m_eVivoxCase;       // renamed g_iVVXcaseDev
    // p.s. 似乎只有 ResponseManager.cpp 與 StateManager.cpp 使用到.
    //      這兩個變數與下方的 m_iState, m_iCase 有相似之處.
    //      無法理解原作者之設計意涵, 故暫時先保留變數之獨立性.
    //      理論上 VivoxLib 內的檔案應該不需要更動其內容.
    //      這部分的依賴性還有待解決 ... by slime

    VVX_INPUT_MODE  m_iInputMode;       // 輸入模式.
    VVX_STATE       m_iState;           // 狀態.
    VVX_CASE        m_iCase;            // 
    VVX_CASE        m_iCasePrevious;    // 上一個.

    int             m_iStateUpdate;
    bool            m_bEnable;

    int             m_iInputVolumn;     // 語音輸入音量.
    int             m_iHangOver;        // 語音自動停止時間(秒)
    int             m_iSensitivity;     // 語音偵測感度.

	/*
		0: off
		1: default and dump some data to Log files
		2: some extra infor (Like dump evt_part_update)
	*/
	int             m_iOutputDebugMessage; // GKy 091223 try as Int enable deBug Level.

    std::string     m_strAccount;               // 帳號.
    std::string     m_strPassword;              // 密碼.
	std::string     m_strServerURL;             // 語音伺服器位置.
	std::string     m_strEchoChannelURI;        // 回音頻道 URI
	std::string     m_strChannelURI;            // 目前頻道 URI
	std::string     m_strChannelName;           // 目前頻道名稱.
	std::string     m_strChannelNamePrefix;     // 目前頻道前綴詞(國碼/區碼)
	std::string     m_strChannelNamePrevious;   // 前一個頻道名稱.

	std::ifstream   m_oVivoxFin; // GKy 091202 Vivox used to read from a file.

    std::vector<std::string>    m_vecMessage;
	std::map<int, std::string>  m_mapInputDevices;  // 輸入裝置名稱列表.
	std::map<int, std::string>  m_mapOutputDevices; // 輸出裝置名稱列表.
    unsigned int    m_iInputDeviceIndex;            // 目前輸入裝置索引.
    unsigned int    m_iOutputDeviceIndex;           // 目前輸出裝置索引.

    // 系統設定值(會自動載入與回存至INI檔案)
    bool            m_bSysEnableVoiceChat;      // 是否開啟語音.
    bool            m_bSysInputMute;            // 是否靜音.
    int             m_iSysInputMode;            // 輸入模式.
    int             m_iSysInputDeviceIndex;     // 輸入驅動選擇.
    int             m_iSysInputVolumn;          // 輸入音量.
    int             m_iSysInputSensitivity;     // 輸入自動偵測感度.
    int             m_iSysOutputDeviceIndex;    // 輸出驅動選擇.
    int             m_iSysOutputVolumn;         // 輸出音量.

};
