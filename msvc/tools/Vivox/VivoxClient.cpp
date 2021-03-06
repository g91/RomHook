
#include "VivoxClient.h"

#include <sstream> // std::ostringstream
#include <boost/bind.hpp> // boost::bind

// Vivox Main
#include "vxplatform/vxcplatformmain.h"

// Vivox Sample Managers
#include "VivoxLib/StateManager.h"
#include "VivoxLib/RequestManager.h"
#include "VivoxLib/ResponseManager.h"

// some static function call need those includes.
#include "../../Interface/WorldFrames/ChatFrame.h" // g_pChatFrame
#include "../../netwaker_member/net_login/NetCli_Login.h"
#include "../../netwaker_member/net_channel/NetCli_ChannelChild.h"
#include "../../netwaker_member/Net_Other/NetCli_OtherChild.h"

//////////////////////////////////////////////////////////////////////////

#if VIVOX_USE_SINGLETON
#else
VivoxClient* VivoxClient::sm_pkInstance = NULL;

#if VIVOX_CHECK_SINGLETON_COUNT
unsigned int VivoxClient::sm_uiInstanceCount = 0;
#endif

VivoxClient* VivoxClient::GetInstance()
{
#if VIVOX_CHECK_SINGLETON_COUNT
    if (sm_uiInstanceCount > 1)
    {
        assert(!(sm_uiInstanceCount > 1) && "GetInstance() After DeleteInstance()");
        return NULL;
    }
    if (sm_pkInstance == NULL)
    {
        sm_pkInstance = new VivoxClient();
        sm_uiInstanceCount += 1;
    }
#else
    if (sm_pkInstance == NULL)
    {
        sm_pkInstance = new VivoxClient();
    }
#endif
    return sm_pkInstance;
}

void VivoxClient::DeleteInstance()
{
#if VIVOX_CHECK_SINGLETON_COUNT
    if (sm_pkInstance != NULL)
    {
        delete sm_pkInstance;
        sm_pkInstance = NULL;
        sm_uiInstanceCount += 1; // please do not change to (-= 1)
    }
#else
    if (sm_pkInstance != NULL)
    {
        delete sm_pkInstance;
        sm_pkInstance = NULL;
    }
#endif
}
#endif

//////////////////////////////////////////////////////////////////////////

VivoxClient::VivoxClient()
: s_w_iolock(NULL),
  s_e_iolock(NULL),
  s_o_iolock(NULL),
  s_p_iolock(NULL),
  m_pkVivoxApp(NULL),
  m_iPartnerDBidLast(0),
  m_iLoginRetry(0),
  m_iLoginMode(VVX_LOGIN_MODE_INIT),
  m_eVivoxState(VVX_STATE_IDLE),
  m_eVivoxCase(VVX_CASE_IDLE),
  m_iInputMode(VVX_INPUT_MODE_NULL),
  m_iState(VVX_STATE_IDLE),
  m_iCase(VVX_CASE_IDLE),
  m_iCasePrevious(VVX_CASE_IDLE),
  m_iStateUpdate(0),
  m_bEnable(false),
  m_iInputVolumn(0),
  m_iHangOver(1),
  m_iSensitivity(0),
  m_iOutputDebugMessage(0),
  m_strAccount(VVX_CLN_ACC),
  m_strPassword(VVX_CLN_PWD),
  m_iInputDeviceIndex(0),
  m_iOutputDeviceIndex(0),
  m_bSysEnableVoiceChat(false),
  m_bSysInputMute(false),
  m_iSysInputMode(0),
  m_iSysInputDeviceIndex(0),
  m_iSysInputVolumn(0),
  m_iSysInputSensitivity(0),
  m_iSysOutputDeviceIndex(0),
  m_iSysOutputVolumn(0)
{
    Initial();
}

VivoxClient::~VivoxClient()
{
    Release();
}

void VivoxClient::Initial()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::Initial()\n"));
#endif

#if VVX_DEBUG //////////////////////////////////////////////////////////////
    m_iLoginMode = VVX_LOGIN_MODE_INIT; // GKy 100129
#else
    m_iLoginMode = VVX_LOGIN_MODE_NA; // 
#endif //////////////////////////////////////////////////////////////

    m_ParticipantState.energy = 0.0;

    //Release(); why release before init ?
    ////////////////////////////////////

    vx_initialize();

    // GKy 091202 add Vivox Initialization
    s_w_iolock = new vxplatform::Lock();
    s_e_iolock = new vxplatform::Lock();
    s_o_iolock = new vxplatform::Lock();
    s_p_iolock = new vxplatform::Lock();

    InitialApp(
        boost::bind(&VivoxClient::VivoxOutputPrint, this, _1, _2),
        boost::bind(&VivoxClient::VivoxErrorPrint, this, _1, _2)
        );

    LoadSystemSettings();
}

void VivoxClient::InitialApp(VivoxConsoleOutputCallback stdcout, VivoxConsoleOutputCallback stdcerr,
                             void* handle, int argc, char** argv)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::InitialApp()\n"));
#endif

#if VVX_CORE_OFF ////////////////////////////////////////////
    //##############################
    return; // GKy 100309 #test
    //##############################
#endif // #if VVX_CORE_OFF ////////////////////////////////////////////

    // 注意 : SDKSampleApp 中有內含一個 Event Callback Thread
    m_pkVivoxApp = new SDKSampleApp(stdcout, stdcerr, NULL, 0, NULL);
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("SDKSampleApp::Initial()\n"));
#endif

    if (m_pkVivoxApp == NULL)
    {
        assert(!(m_pkVivoxApp == NULL) && "SDKSampleApp ctor failed !");
    }

    // set vivox log level by runedev.ini
    TCHAR szReadBuffer[512];
    TCHAR szIniFilename[256];
    TCHAR szWorkDirectory[256];
    memset(szReadBuffer, 0, sizeof(szReadBuffer));
    memset(szIniFilename, 0, sizeof(szIniFilename));
    memset(szWorkDirectory, 0, sizeof(szWorkDirectory));
    GetCurrentDirectory(sizeof(szWorkDirectory), szWorkDirectory);
    _stprintf(szIniFilename, _T("%s\\runedev.ini"), szWorkDirectory);
    if ( GetPrivateProfileString(_T("Debug"), _T("VivoxLogLevel"), 0, szReadBuffer, sizeof(szReadBuffer), szIniFilename) )
    {
        int iVivoxLogLevel = _ttoi(szReadBuffer);
        if (iVivoxLogLevel < 0)
            iVivoxLogLevel = 0;
        if (iVivoxLogLevel > 2) // do not let user set 3 or 4
            iVivoxLogLevel = 2;
        m_pkVivoxApp->GetRequestManager()->SetLogLevel(iVivoxLogLevel);
    }
    else // no define in file
    {
        m_pkVivoxApp->GetRequestManager()->SetLogLevel(0); // 0 by default
    }
}

void VivoxClient::Release()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::Release() - Start\n"));
#endif

    SaveSystemSettings();

    if (m_pkVivoxApp)
    {
        m_pkVivoxApp->Shutdown();
        delete m_pkVivoxApp;
        m_pkVivoxApp = NULL;
    }

    vx_uninitialize();

    if (s_w_iolock)
    {
        delete s_w_iolock;
        s_w_iolock = NULL;
    }
    if (s_e_iolock)
    {
        delete s_e_iolock;
        s_e_iolock = NULL;
    }
    if (s_o_iolock)
    {
        delete s_o_iolock;
        s_o_iolock = NULL;
    }
    if (s_p_iolock)
    {
        delete s_p_iolock;
        s_p_iolock = NULL;
    }

#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::Release() - End\n"));
#endif
}

void VivoxClient::LoadSystemSettings()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::LoadSystemSettings()\n"));
#endif

    RuPropertyType propertyValue;

    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_ENABLE, propertyValue))
    {
        m_bSysEnableVoiceChat = (boost::get<BOOL>(propertyValue) == FALSE) ? false : true;
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_MUTE, propertyValue))
    {
        m_bSysInputMute = (boost::get<BOOL>(propertyValue) == FALSE) ? false : true;
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_MODE, propertyValue))
    {
        m_iSysInputMode = boost::get<INT32>(propertyValue);
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_DEV_IDX, propertyValue))
    {
        m_iSysInputDeviceIndex = boost::get<INT32>(propertyValue);
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_VOL, propertyValue))
    {
        m_iSysInputVolumn = boost::get<INT32>(propertyValue);
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_SEN, propertyValue))
    {
        m_iSysInputSensitivity = boost::get<INT32>(propertyValue);
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_OUTPUT_DEV_IDX, propertyValue))
    {
        m_iSysOutputDeviceIndex = boost::get<INT32>(propertyValue);
    }
    if (g_ruEngineSettings->GetSetting(ENGINE_SETTINGS_VOICE_CHAT_OUTPUT_VOL, propertyValue))
    {
        m_iSysOutputVolumn = boost::get<INT32>(propertyValue);
    }
}

void VivoxClient::InitialSystemSetting()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::InitialSystemSetting()\n"));
#endif

    //m_iSysInputSensitivity = 100 - m_iSysInputSensitivity; // reverse for ui

    if (m_bSysEnableVoiceChat)
    {
        Enable_With_CheckAccount();
    }
    else
    {
        Disable_With_CheckEnable();
    }
    SetInputMute(m_bSysInputMute);
    SetInputMode(m_iSysInputMode);
    SetInputDeviceIndex(m_iSysInputDeviceIndex);
    SetInputVolumn(m_iSysInputVolumn);
    SetInputSensitivity(m_iSysInputSensitivity);    // will reverse at set
    SetOutputDeviceIndex(m_iSysOutputDeviceIndex);
    SetOutputVolumn(m_iSysOutputVolumn);
}

void VivoxClient::SaveSystemSettings()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::SaveSystemSettings()\n"));
#endif

    // copy member value to system value for save file. // TODO: 或許需要合併某些變數.
    //m_bSysEnableVoiceChat = m_bEnable;
    m_iSysInputMode = static_cast<int>(m_iInputMode);
    m_iSysInputDeviceIndex = m_iInputDeviceIndex;
    //m_iSysInputVolumn = m_iInputVolumn;
    m_iSysInputSensitivity = 100 - m_iSensitivity; // reverse for ui
    m_iSysOutputDeviceIndex = m_iOutputDeviceIndex;

    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_ENABLE, m_bSysEnableVoiceChat);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_MUTE, m_bSysInputMute);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_MODE, m_iSysInputMode);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_DEV_IDX, m_iSysInputDeviceIndex);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_VOL, m_iSysInputVolumn);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_INPUT_SEN, m_iSysInputSensitivity);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_OUTPUT_DEV_IDX, m_iSysOutputDeviceIndex);
    g_ruEngineSettings->SetSetting(ENGINE_SETTINGS_VOICE_CHAT_OUTPUT_VOL, m_iSysOutputVolumn);
}

//----------------------------------------------------------------------------
// GKy 100111 for old use
std::vector<std::string> VivoxClient::splitCmdLine(const std::string &s)
{
	return splitCmdLine(s, ' ');
}

std::vector<std::string> VivoxClient::splitCmdLine(const std::string &s, char cut_char)
{
    std::vector<std::string> items;
    std::string currentString;
    char lastc = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s.at(i);
        //if(c == ' ') { // org+++
        if (c == cut_char)
        {
            if (currentString.empty())
            {
                continue;
            }
            if (lastc == '\\')
            {
                currentString.push_back(c);
                continue;
            }

            items.push_back(currentString);
            currentString.clear();
            lastc = 0;
        }
        else if (c == '\\')
        {
            if (lastc == '\\')
            {
                currentString.push_back(c);
                lastc = 0;
            }
            else
            {
                lastc = c;
            }
        }
        else
        {
            currentString.push_back(c);
            lastc = c;
        }
    }

    if (!currentString.empty())
    {
        items.push_back(currentString);
    }

    return items;
}

void VivoxClient::PrintToChatFrame(const char* theMessage)
{
    if (g_pChatFrame)
    {
        //g_pChatFrame->SendChatMessage(CHAT_MSG_SYSTEM, NULL, theMessage); // cannot use NULL
        g_pChatFrame->SendChatMessage(CHAT_MSG_SYSTEM, "", theMessage);
    }
}

// GKy 091216 make sure only g_fVVXout use this to void critical sections? OR..
void VivoxClient::VivoxOutputPrintWithLog(const char* str_message)
{
	if (m_iOutputDebugMessage <= 0)
    {
        return;
    }

	FlushLog(str_message); // GKy 100105 #test

	AppendMessage(str_message);
}

// GKy 091202 Viovx std I/O for test
// GKy 091211 treat as Vivox SDK main response handler.
// GKy 091216 So,,this fnc have Critical Section ability..
void VivoxClient::VivoxOutputPrint(void* h, const char* s)
{
#if VIVOX_CLIENT_DEBUG_PRINT_OUTPUT_INFO
    std::ostringstream oss_out;
    oss_out << "Vivox> Output> " << s << std::endl
            << "//////////////////////////////////////////////////////////////////////////" << std::endl;
    OutputDebugString(oss_out.str().c_str());
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_03
    PrintToChatFrame(oss_out.str().c_str());
#endif
#endif

	if (m_iOutputDebugMessage <= 0)
    {
        return;
    }

    if (s != 0)
    {
        s_w_iolock->Take();
		//////////////////////////////////////

		VivoxOutputPrintWithLog(s);

		////////////////////////
        s_w_iolock->Release();
    }
}

void VivoxClient::VivoxErrorPrint(void* h, const char* s)
{
#if VIVOX_CLIENT_DEBUG_PRINT_ERROR_INFO
    std::ostringstream oss_err;
    oss_err << "Vivox> Error> " << s << std::endl
            << "//////////////////////////////////////////////////////////////////////////" << std::endl;
    OutputDebugString(oss_err.str().c_str());
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_04
    PrintToChatFrame(oss_err.str().c_str());
#endif
#endif
}

//----------------------------------------------------------------------------
void VivoxClient::InitialCaseEnum(VVX_CASE case_new)
{
    m_iCasePrevious = case_new;
    m_iCase = case_new;
}

void VivoxClient::SetCaseEnum(VVX_CASE case_new)
{
	if (m_iCase != case_new)
    {
		m_iCasePrevious = m_iCase;
		m_iCase = case_new;
	}
}

bool VivoxClient::IsCaseEnumChanged()
{
	if (m_iCase != m_iCasePrevious)
    {
		return true;
	}
    else
    {
		return false;
	}
}

/*
	GKy 100118 not real get the g_VVXstate,

	BUT map to VvxCore internal state

	GKy 100201 reName function.
*/
//VVX_STATE  VivoxClient::STATEget()
VVX_STATE VivoxClient::DetectState()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::DetectState()\n"));
#endif

	// 1. if init/connect
	if (IsConnect())
    {
		// 2. if Login
		if (IsLogin())
        {
			// 3. if sg create
			if (IsCreate())
            {
				return VVX_STATE_SG_CREATE;
			}
            else
            {
				return VVX_STATE_LOGIN;
			}
		}
        else
        {
			return VVX_STATE_INIT;
		}
	}
    else
    {
		return VVX_STATE_SHUTDOWN;
	}
}

// GKy 100201 really get internal state
//VVX_STATE VivoxClient::GetState()
//{
//	return g_iVVXstate;
//}

std::string VivoxClient::GetModeName(int mode_enum)
{
    std::ostringstream r;

    if (mode_enum == VVX_INPUT_MODE_MAX)
    {
        mode_enum = m_iInputMode;
    }

    switch (mode_enum)
    {
        VIVOX_CASE_ENUM_NAME(VVX_INPUT_MODE_NULL, "未設定")
        VIVOX_CASE_ENUM_NAME(VVX_INPUT_MODE_DETECT, "自動偵測")
        VIVOX_CASE_ENUM_NAME(VVX_INPUT_MODE_PTT, "按鍵")
        VIVOX_CASE_ENUM_NAME(VVX_INPUT_MODE_MAX, "??????")
    default:
        r << static_cast<int>(mode_enum);
        break;
    }// switch

    r << '\0';
    return r.str();
}

std::string VivoxClient::GetCaseEnumName(VVX_CASE case_enum)
{
    std::ostringstream r;

    if (case_enum == VVX_CASE_MAX)
    {
        case_enum = m_iCase;
    }

    switch (case_enum)
    {
        VIVOX_CASE_ENUM_NAME(VVX_CASE_IDLE, "發呆")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_DISABLE, "失效")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_CH_JOIN_INIT, "加入-初始化")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_CH_JOIN_CREATE, "加入-產生")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_ACC_CHECK, "檢查帳號")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_CH_JOIN_ADD, "加入-新增")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_CH_EXIT_INIT, "離開-初始化")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_TEST_INIT, "測試-初始化")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_TEST_END_INIT, "測試-結束初始化")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_in_TEAM, "")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_in_TEST, "測試中")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_IN_DEV_SET, "設定輸入裝置")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_IN_DEV_GET, "取得輸入裝置")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_OUT_DEV_SET, "設定輸出裝置")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_OUT_DEV_GET, "取得輸出裝置")
        VIVOX_CASE_ENUM_NAME(VVX_CASE_MAX, "??????")
        default:
            r << static_cast<int>(case_enum);
            break;
    }// switch

    r << '\0';
    return r.str();
}

std::string VivoxClient::GetStateName(VVX_STATE state_enum)
{
	std::ostringstream r;

	if (state_enum == VVX_STATE_MAX)
    {
		state_enum = m_eVivoxState;
	}

	switch (state_enum)
    {
        VIVOX_CASE_ENUM_NAME(VVX_STATE_IDLE, "發呆")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_INIT, "初始化")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_INIT_OK, "初始化OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SHUTDOWN, "關閉")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SHUTDOWN_OK, "關閉OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGIN, "登入")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGIN_OK, "登入OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGIN_ANY, "匿名登入")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGIN_ANY_OK, "匿名登入OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGOUT, "登出")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_LOGOUT_OK, "登出OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ACC_UPDATE, "更新帳號")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ACC_UPDATE_OK, "更新帳號OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SG_CREATE, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SG_CREATE_OK, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SG_DEL, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SG_DEL_OK, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SS_ADD, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SS_ADD_OK, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SS_REMOVE, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SS_REMOVE_OK, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SM_DISCONNECTING, "正在斷線") 
        VIVOX_CASE_ENUM_NAME(VVX_STATE_SM_DISCONNECTED, "已經斷線")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_PART_MUTE, "靜音")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_PART_MUTE_OK, "靜音OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_CH_CREATE_ECHO, "產生回音頻道")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_CH_CREATE, "產生頻道")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_CH_CREATE_OK, "產生頻道OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_CH_DEL, "刪除頻道")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_CH_DEL_OK, "刪除頻道OK")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ADJUST, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ADJUST_OK, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ADJUST_IN_DEV, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_ADJUST_OUT_DEV, "")
        VIVOX_CASE_ENUM_NAME(VVX_STATE_MAX, "??????")
		default:
			r << static_cast<int>(state_enum);
            break;
	}// switch

    r << '\0';
	return r.str();
}

//----------------------------------------------------------------------------

void VivoxClient::ProcessCoreCommand(const char* cmd_input)
{
	VivoxOutputPrint(NULL, cmd_input);

#if VIVOX_CLIENT_DEBUG_PRINT_COMMAND_EXEC
    {
        char debug_core_cmd[256];
        debug_core_cmd[255] = '\0';
        _snprintf(debug_core_cmd, 255, "Vivox> %s \n", cmd_input);
        OutputDebugString(debug_core_cmd);
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_02
        PrintToChatFrame(debug_core_cmd);
#endif
    }
#endif

	std::string tmpLine = cmd_input;

    // Get the user input and determine the desired action
    std::vector<std::string> cmd = splitCmdLine(tmpLine);

	if (cmd.empty())
    {
        return;
    }

	if (strcasecmp(cmd[0].c_str(), "file") == 0)
    {
		std::string inputfilename;
		if (cmd.size() < 2)
        {
			VivoxOutputPrint(NULL, "Error opening input file, no file name given");
            return;
		}
#ifdef SN_TARGET_PS3
		inputfilename = SYS_APP_HOME + cmd[1];
#else
		inputfilename = cmd[1];
#endif
		if (m_oVivoxFin.is_open())
        {
            m_oVivoxFin.close();  // close any open file, breaks nesting
        }

		m_oVivoxFin.clear();
		m_oVivoxFin.open(inputfilename.c_str()); 
		if (!m_oVivoxFin.is_open())
        {
			std::string temp;
			temp = "Error opening input file: ";
			temp += inputfilename.c_str();
			VivoxOutputPrint(NULL, temp.c_str());
		}
        return;
	}
    else if (cmd[0] == "sleep") //for diagnostic purposes only
    {
		if (cmd.size() == 2)
		{
			VivoxOutputPrint(NULL, "Sleeping...");
#ifdef _WIN32
			DWORD slp = 0;
			slp = atoi(cmd[1].c_str()) * 1000;
			Sleep(slp);
#else
#ifndef SN_TARGET_PS3
			int slp = 0;
			slp = atoi(cmd[1].c_str());
			sleep(slp);
#else
			int slp = 0;
			slp = atoi(cmd[1].c_str());
			sys_timer_usleep(slp * 1000000);
#endif
#endif
		}
        else
        {
			VivoxOutputPrint(NULL, "usage: sleep <number of seconds to sleep");
            return;
		}
	}
    else if (cmd[0] == "echo" || cmd[0] == "pause")       //for diagnostic purposes only
	{
		if (cmd.size() > 1)
		{
			std::ostringstream oss;
			for (unsigned int i = 1; i < cmd.size(); ++i)
			{
				oss << cmd[i] << " ";
			}
			VivoxOutputPrint(NULL, oss.str().c_str());
		}
		if (cmd[0] == "pause")
        {
			// wait for a return
			//std::getline(std::cin, tmpLine); // don't know why use std::cin here. marked by slime.
            return;
		}
	}

	if (!m_pkVivoxApp->ProcessCommand(cmd))
    {
#if VIVOX_CLIENT_DEBUG_PRINT_ERROR_INFO
        char szDebug[256];
        szDebug[255] = '\0';
        _snprintf(szDebug, 255, "m_pkVivoxApp->ProcessCommand(%s) failed ! \n", cmd);
        OutputDebugString(szDebug);
#endif
    }
}

// CC = CoreCommand
void VivoxClient::CC_Initial()
{
    // usage : init account_management_server [minimum_port] [maximum_port]
    std::ostringstream oss_cmd;
    oss_cmd << "init " << m_strServerURL;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_Shutdown()
{
    // usage : shutdown connector_handle
    std::ostringstream oss_cmd;
    oss_cmd << "shutdown " << m_pkVivoxApp->GetStateManager()->GetConnectorHandle();
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_Login()
{
    // usage : login connector_handle username password [presence] [auto-answer] [enable-text] [speaking_notif_freq] [buddy_management_mode]                                   [send_channel_notification]
    //                                                  (0 or 1)   (0 or 1)      (0 or 1)      (0 or 1)              (0=AutoAccept, 1=AutoAdd, 2=Block, 3=Hide, 4=Application) (0 or 1)
    std::ostringstream oss_cmd;
    oss_cmd << "login " << m_pkVivoxApp->GetStateManager()->GetConnectorHandle()
            << " " << m_strAccount
            << " " << m_strPassword;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_AnonymousLogin()
{
    // usage : anonymouslogin connector_handle [displayname] [presence] [speaking_notif_freq] [buddy_management_mode]                                   [send_channel_notification]
    //                                                       (0 or 1)                         (0=AutoAccept, 1=AutoAdd, 2=Block, 3=Hide, 4=Application) (0 or 1)
    std::ostringstream oss_cmd;
    oss_cmd << "anonymouslogin " << m_pkVivoxApp->GetStateManager()->GetConnectorHandle()
            << " " << m_ParticipantState.display_name;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_Logout()
{
    // usage : logout acct_handle
    std::ostringstream oss_cmd;
    oss_cmd << "logout " << m_pkVivoxApp->GetStateManager()->GetAccountHandle();
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_CreateSessionGroup()
{
    // usage : sgcreate acct_handle [playback]
    //                              (0 or 1)
    std::ostringstream oss_cmd;
    oss_cmd << "sgcreate " << m_pkVivoxApp->GetStateManager()->GetAccountHandle();
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_TerminateSessionGroup(const char* group_name)
{
    // usage : sgterminate group_handle
    std::ostringstream oss_cmd;
    oss_cmd << "sgterminate " << group_name;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_AddSessionIntoSessionGroup(const char* group_name)
{
    // usage : sgaddsession uri connect_audio connect_text [fontID] [password] [jitter_compensation]
    //                          (0 or 1)      (0 or 1)
    std::ostringstream oss_cmd;
    oss_cmd << "sgaddsession " << group_name
            << " " << m_strChannelURI
            << " 1 0";
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_RemoveSessionFromSessionGroup()
{
    // TODO:
}

void VivoxClient::CC_CreateEchoChannel()
{
    // usage : createchannel acct_handle name [desc] [max_partips] [persist] [mode]                                   [channel_type]                           [encrypt] [maxrange] [clampingdist] [rolloff] [maxgain] [distmodel] [pw]
    //                                                             (0 or 1)  (0=normal, 1=pres, 2=lec, 3=open, 4=aud) (0=normal, 1=pres, 2=lec, 3=open, 4=aud) (1=encrypt, 0=default)
    std::ostringstream oss_cmd;
    oss_cmd << "createchannel " << m_pkVivoxApp->GetStateManager()->GetAccountHandle()
            << " Echo";
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_CreateChannel()
{
    std::ostringstream oss_cmd;
    // usage : createchannel acct_handle name [desc] [max_partips] [persist] [mode]                                   [channel_type]                           [encrypt] [maxrange] [clampingdist] [rolloff] [maxgain] [distmodel] [pw]
    //                                                             (0 or 1)  (0=normal, 1=pres, 2=lec, 3=open, 4=aud) (0=normal, 1=pres, 2=lec, 3=open, 4=aud) (1=encrypt, 0=default)
    oss_cmd << "createchannel " << m_pkVivoxApp->GetStateManager()->GetAccountHandle()
            << " " << m_strChannelName
            << " Ispania"
            << " " << c_DefaultMaxPartips;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_SetupInputDevice()
{
    // usage : setcapturedev capture_device_name
    std::ostringstream oss_cmd;
    oss_cmd << "setcapturedev " << m_mapInputDevices[m_iInputDeviceIndex];
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_SetupOutputDevice()
{
    // usage : setrenderdev render_device_name
    std::ostringstream oss_cmd;
    oss_cmd << "setrenderdev " << m_mapOutputDevices[m_iOutputDeviceIndex];
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_UpdateAccount()
{
    // usage : updateaccount acct_handle displayname
    std::ostringstream oss_cmd;
    oss_cmd << "updateaccount " << m_pkVivoxApp->GetStateManager()->GetAccountHandle()
            << " " << GetDBID();
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_LocalUserMute()
{
    // TODO:
}

void VivoxClient::CC_SetupInputMute(bool isMute)
{
    // usage : micmute mute
    //                 (0 or 1)
    std::ostringstream oss_cmd;
    oss_cmd << "micmute " << isMute ? 1 : 0;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_SetupInputVolumn(int nValue)
{
    if (nValue < 0)
        nValue = 0;
    if (nValue > 100)
        nValue = 100;

    // usage : settuningmicvol [0 - 100]
    std::ostringstream oss_cmd;
    oss_cmd << "settuningmicvol " << nValue;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_SetupInputSensitivity(int nValue, int nHangoverTime)
{
    if (nHangoverTime < 1)
        nHangoverTime = 1;
    if (nHangoverTime > 60)
        nHangoverTime = 60;
    if (nValue < 0)
        nValue = 0;
    if (nValue > 100)
        nValue = 100;

    // usage : setvadproperties hangover_time_in_seconds sensitivity
    std::ostringstream oss_cmd;
    oss_cmd << "setvadproperties " << nHangoverTime
            << " " << nValue;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_SetupOutputVolumn(int nValue)
{
    if (nValue < 0)
        nValue = 0;
    if (nValue > 100)
        nValue = 100;

    // usage : settuningspeakervol [0 - 100]
    std::ostringstream oss_cmd;
    oss_cmd << "settuningspeakervol " << nValue;
    ProcessCoreCommand(oss_cmd.str().c_str());
}

void VivoxClient::CC_ListInputDevice()
{
    ProcessCoreCommand("listcapturedevs");
}

void VivoxClient::CC_ListOutputDevice()
{
    ProcessCoreCommand("listrenderdevs");
}

int VivoxClient::ProcessByState(VVX_STATE state_enum , const char* cmd_param)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::ProcessByState(%s, %s)\n", GetStateName(state_enum).c_str(), cmd_param);
    OutputDebugString(szDebug);
#endif

	switch (state_enum)
    {
		case VVX_STATE_IDLE:
			break;

		case VVX_STATE_INIT: 
			// 1. Connect to Server
			if (!IsConnect())
            {
                CC_Initial();
				//GKy 091202 Need find a way to wait previous step complete..
            }
			break;

		case VVX_STATE_SHUTDOWN: 
			if (IsConnect())
            {
                CC_Shutdown();
			}
            break;

		case VVX_STATE_LOGIN: // try Login (after init OK)
			// 2. Login
            if (IsConnect())
            {
                CC_Login();
            }
            else
            {
                return 0;
            }
            break;

		case VVX_STATE_LOGIN_ANY:
            if (IsConnect())
            {
                CC_AnonymousLogin();
            }
            else
            {
                return 0;
            }
            break;

		case VVX_STATE_LOGOUT:
			if (IsLogin())
            {
                CC_Logout();
			}
            break;

		case VVX_STATE_SG_CREATE: // try Session Group Create after init OK
			// 3. Create Session Group
			if (IsLogin())
            {
                CC_CreateSessionGroup();
			}
            else
            {
                return 0; // S_OK
            }
            break;

		case VVX_STATE_SG_DEL:
        {   // note : 只會取第一個 ... ?
            std::set<std::string> setSesstionGroupStrings = m_pkVivoxApp->GetStateManager()->GetAllSessionGroupHandles();
            if (setSesstionGroupStrings.size() > 0)
            {
                std::set<std::string>::iterator iter = setSesstionGroupStrings.begin();
                if (iter != setSesstionGroupStrings.end())
                {
                    CC_TerminateSessionGroup( (*iter).c_str() );
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }   break;

		case VVX_STATE_SS_ADD:
        {   // note : 只會取第一個 ... ?
            std::set<std::string> setSesstionGroupStrings = m_pkVivoxApp->GetStateManager()->GetAllSessionGroupHandles();
            if (setSesstionGroupStrings.size() > 0)
            {
                std::set<std::string>::iterator iter = setSesstionGroupStrings.begin();
                if (iter != setSesstionGroupStrings.end())
                {
                    CC_AddSessionIntoSessionGroup( (*iter).c_str() );
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }   break;

		case VVX_STATE_SS_REMOVE:
		{
            // TODO: 此段落語意混淆不清, 可能有錯誤, 待查 ...
            //CC_RemoveSessionFromSessionGroup();

			// 0. try get SG handle
            std::set<std::string> setSesstionGroupStrings = m_pkVivoxApp->GetStateManager()->GetAllSessionGroupHandles();
            std::set<std::string>::iterator iter = setSesstionGroupStrings.begin();
			if (iter != setSesstionGroupStrings.end())
            {
                std::string strSessionGroupID = (*iter);
				std::set<std::string> setSesstionStringsByID = m_pkVivoxApp->GetStateManager()->GetAllSessionHandles(strSessionGroupID.c_str());
                std::set<std::string>::iterator iterByID = setSesstionStringsByID.begin();
				if (iterByID != setSesstionStringsByID.end())
                {
                    // usage : sgremovesession group_handle session_handle
                    std::ostringstream oss_cmd;
                    oss_cmd << "sgremovesession " << strSessionGroupID
                            << " " << (*iterByID);
                    ProcessCoreCommand(oss_cmd.str().c_str());
				}
                else
                {
					// GKy 100118 for ChSwitch repaidly reClick handle?
					// OR try using return value. check
					return 0;
				}
			}
            else
            {
				return 0;
			}
		}	break; // VVX_STATE_SG_REMOVE

		case VVX_STATE_CH_CREATE_ECHO:
			if (IsLogin())
            {
                CC_CreateEchoChannel();
			}
            else
            {
                return 0;
            }
			break;

		case VVX_STATE_CH_CREATE:
			if (IsLogin())
            {
                CC_CreateChannel();
			}
            else
            {
                return 0;
            }
            break;

		case VVX_STATE_ADJUST_IN_DEV:
            {
                CC_SetupInputDevice();
                break;
            }

		case VVX_STATE_ADJUST_OUT_DEV:
            {
                CC_SetupOutputDevice();
                break;
            }
	
		case VVX_STATE_ACC_UPDATE:
		{
			int iDBid = -1;
			if (g_pGameMain != NULL)
            {
				iDBid = g_pGameMain->GetDBID();
				if (iDBid != -1)
                {
					SetDBID(iDBid);
				}
			}
            else
            {
				// Exception Case Handle
			}

            CC_UpdateAccount();
        }   break;

		case VVX_STATE_PART_MUTE:
		{
            //CC_LocalUserMute(); // TODO:

			// 0. try get SG handle
			std::set<std::string> setSessionGroupStrings = m_pkVivoxApp->GetStateManager()->GetAllSessionGroupHandles();
			std::set<std::string>::iterator iter = setSessionGroupStrings.begin();
			if (iter != setSessionGroupStrings.end())
            {
				std::string strSessionGroupID = (*iter);
				std::set<std::string> setSessionGroupStringsByID = m_pkVivoxApp->GetStateManager()->GetAllSessionHandles(strSessionGroupID.c_str());
				std::set<std::string>::iterator iterByID = setSessionGroupStringsByID.begin();
				if (iterByID != setSessionGroupStringsByID.end())
                {
					if (cmd_param)
                    {
                        // usage : localusermute yesno user_uri [scope]
                        //                       (0 or 1)       (0=all,1=audio,2=text)
                        std::ostringstream oss_cmd;
                        oss_cmd << "localusermute " << (*iterByID)
                                << " " << cmd_param;
                        ProcessCoreCommand(oss_cmd.str().c_str());
					}
                    else
                    {
                        return 0;
                    }
				}
                else
                {
                    return 0;
                }
			}
		}	break; // VVX_STATE_PART_MUTE

        default:
            break;
	} // switch (state_enum)

	return 1;
}

int VivoxClient::ProcessByUpdateState(VVX_STATE state_enum)
{
    m_eVivoxState = state_enum;
    return ProcessByState(state_enum, NULL);
}

int VivoxClient::ProcessGeneric()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::ProcessGeneric()\n"));
#endif

    switch (DetectState())
    {
        case VVX_STATE_SHUTDOWN:
            ProcessByUpdateState(VVX_STATE_INIT);
            break;

        case VVX_STATE_INIT:
            ProcessByUpdateState(VVX_STATE_LOGIN);
            break;

        case VVX_STATE_LOGIN:
            ProcessByUpdateState(VVX_STATE_SG_CREATE);
            break;

        case VVX_STATE_SG_CREATE: // mu..!?
            ProcessByUpdateState(VVX_STATE_SG_DEL);
            break;

        default:
            break;
    } // switch (DetectState())

    return 0;
}

//////////////////////////////////////////////////////

bool VivoxClient::IsInTest()
{
	if (m_strChannelURI != m_strEchoChannelURI)
    {
		return false;
	}
    else
    {
		return true;
	}
}

bool VivoxClient::IsInChannel()
{
	if (m_strChannelName != "")
    {
		return true;
	}
    else
    {
		return false;
	}
}

/*
	0: idle
	1: busy
*/
int VivoxClient::IsBusy()
{
	switch (m_iCase)
    {
		case VVX_CASE_IDLE:
		case VVX_CASE_in_TEAM:
		case VVX_CASE_in_TEST: // not sure if need, due to Test UI not use this
			return 0;
			break;

		default:
			return 1;
			break;
	}
}

bool VivoxClient::IsConnect()
{
    return m_pkVivoxApp->GetStateManager()->GetIsConnectorInitialized();
}

bool VivoxClient::IsLogin()
{
    return m_pkVivoxApp->GetStateManager()->GetIsAccountLoggedIn();
}

bool VivoxClient::IsCreate()
{
    //return m_pkVivoxApp->GetStateManager()->GetSessionGroupExists("");
    return m_pkVivoxApp ? m_pkVivoxApp->GetStateManager()->GetSessionGroupExists("") : false;
}

bool VivoxClient::IsPlayerInVoiceChannel(int DBid)
{
    return m_ParticipantGroup.CheckUriExistByDBID(DBid);
}

int VivoxClient::IsPlayerMute(int DBid)
{
    return m_ParticipantGroup.CheckMuteByDBID(DBid);
}

int VivoxClient::IsPlayerSpeaking(int DBid)
{
    return m_ParticipantGroup.CheckSpeakingByDBID(DBid);
}

int VivoxClient::Enable(int iAccountCheckRetry, int bCheckEnable)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::Enable(%d, %d)\n", iAccountCheckRetry, bCheckEnable);
    OutputDebugString(szDebug);
#endif

	if (bCheckEnable)
    {
        if (m_bEnable)
        {
            return 0; // GKy 100128 removed..<==============================
        }
    }

	m_bEnable = true;

	int ret = 0;

	//// reJoin HANDLE
	// Need check if need reJoin back to Origin Channel
	//if(VivoxClient::m_sVivoxChannelName == "" ){
	if (!IsInChannel())
    {
	    // ensure we are free to any Team channel.
    }
    else
    {
	    // We are in some Ch, need reJoin
	    // GKy 100114 feel not so necessary with new style.
		SetCurrentChannelName("");
	}

	switch (m_iCase)
    {
		// Busy wait ////////////////////////////////////////////////////
		case VVX_CASE_DISABLE:
		case VVX_CASE_ACC_CHECK:
			ret = 0;
			break;
		// Do ////////////////////////////////////////////////////
		default:
			ret = 1;
			if (iAccountCheckRetry != -1)
            {
				SetLoginRetry(iAccountCheckRetry);
				CheckAccount();
			}
			break;
	} // switch (m_iCase)

	return ret;
}

//-------------------------------------------------------------
int VivoxClient::Disable(int bCheckEnable)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::Disable(%d)\n", bCheckEnable);
    OutputDebugString(szDebug);
#endif

	if (bCheckEnable)
    {
	    if (!m_bEnable)
        {
            return 0; // GKy 100128 hide for txALL End recall.
        }
    }

	m_bEnable = false;

	int ret = 0;

	// GKy 100114 no need auto reJoin when re-enable, try.
	// GKy 100128 BUT..if call to ChExit? mu..disable seems no call to ChExit..
	// GKy 100128 may be need called when Disable end? mu..BUT if no Ch, call ChExit will show S_MSG_EXIT..
	SetCurrentChannelName("");
	m_strChannelURI = "";

	//////////////////////////////////////

	switch (m_iCase)
    {
		// Busy, Wait..or?.. May be ShutDown no need wait?..
		// GKy 100108 ensure here must Do
		// GKy 100128 BUT still have some risk?
		//////////////////////////////////////////////////////
		case VVX_CASE_DISABLE:
		case VVX_CASE_ACC_CHECK: // GKy 100128 add, for during enable call disable
			ret = 0;

		//case VVX_CASE_CH_JOIN_INIT:
		//case VVX_CASE_CH_JOIN_CREATE:
		//case VVX_CASE_CH_JOIN_ADD:
		//case VVX_CASE_CH_EXIT_INIT:
		//case VVX_CASE_TEST_INIT:

			////VivoxClient::m_iVVXcase  = VVX_CASE_DISABLE;
			//VivoxClient::CASEset( VVX_CASE_DISABLE );

			break; // GKy 100128 try resume? BUT..

		// Do
		default:
			ret = 1;
			DisableWithInitialCase();
			break;
	} // switch (m_iCase)

	return ret;
}

int VivoxClient::DisableWithInitialCase()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::DisableWithInitialCase()\n"));
#endif

	if (IsConnect())
    {
		InitialCaseEnum(VVX_CASE_DISABLE);
		m_eVivoxState = VVX_STATE_SHUTDOWN;
		ProcessByState(m_eVivoxState, NULL);
	}
    else
    {
		StateManager* pkStateManager = m_pkVivoxApp->GetStateManager();
		if (pkStateManager)
        {
			InitialCaseEnum(VVX_CASE_DISABLE);
			m_eVivoxState = VVX_STATE_SHUTDOWN_OK;
			pkStateManager->txALL();
		}
        else
        {
			InitialCaseEnum(VVX_CASE_IDLE);
			return 0;
		}
	}

	return 1;
}

void VivoxClient::UpdateState()
{
    RequestManager* pkRequestManager;

    pkRequestManager = m_pkVivoxApp->GetRequestManager();
    pkRequestManager->req_StateDump();
}

void VivoxClient::CheckAccount()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::CheckAccount()\n");
#endif

    // GKy 100122 need send some S_MSG, or move to enable part?
    // GKy 100127 reset LoginMode, void some other interference, like ChJoin..
    SetLoginMode(VVX_LOGIN_MODE_NA);

    InitialCaseEnum(VVX_CASE_ACC_CHECK);
    if (IsConnect())
    {
        m_eVivoxState = VVX_STATE_SHUTDOWN;
    }
    else
    {
        m_eVivoxState = VVX_STATE_INIT;
    }
    ProcessByState(m_eVivoxState, NULL);
}

std::string VivoxClient::GetChannelName(VVX_CH_TYPE channel_type, int world_id, int sys_id)
{
	char partyID[256];
    partyID[255] = '\0';
	//sprintf_s(worldID, "%d", g_pAccountLogin->GetWorldID());
	_snprintf(partyID, 255, "%d", sys_id);

	return GetChannelName(channel_type, world_id, (const char*)partyID);
}

std::string VivoxClient::GetChannelName(VVX_CH_TYPE channel_type, int world_id, const char* sys_id)
{
    std::ostringstream oss;

    // "%s.iSpAniA7551_%d_%d_%s"
    oss << m_strChannelNamePrefix
        << ".iSpAniA7551_" << channel_type
        << "_" << world_id
        << "_" << sys_id;
       
	return oss.str();
}

std::string VivoxClient::GetChannelNamePrevious(bool bMustGet)
{
    if (bMustGet)
    {
        if (m_strChannelNamePrevious != "")
        {
            return m_strChannelNamePrevious; 
        }
        else
        {
            return m_strChannelName;
        }
    }
    else
    {
        return m_strChannelNamePrevious; 
    }
}

void VivoxClient::SetChannelNamePrevious(const char* str)
{
	if (IsInTest())
    {
        m_strChannelNamePrevious = VVX_CH_NAME_TEST;
	}
    else
    {
		// GKy 100112 main for VVX_SYS_MSG(S_VOICE_CHAT_CH_JOIN_OK) using
		// Indeed, not so match the name Logic..
		if (m_strChannelNamePrevious != str)
        {
			m_strChannelNamePrevious = str;
		}
	}
}

//const char* VivoxClient::ChannelNameGet( VVX_CH_TYPE channel_type, int world_id, int sys_id){
/*
	Indeed, this fnc often be called in strange phase..
	GKy 100112 this fnc seems can`t be recalled? but..
*/
int VivoxClient::JoinChannelWithInitialCase(VVX_CASE case_enum)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::JoinChannelWithInitialCase(%s)\n", GetCaseEnumName(case_enum).c_str());
    OutputDebugString(szDebug);
#endif

    // void inTest, then disAble will reJoin
    if (!m_bEnable)
    {
		SetCaseEnum(VVX_CASE_IDLE);
		return 0;
	}

	if (m_iCase == VVX_CASE_in_TEST)
    {
		return 0;
	}

	////////////////////////////////////////////////////////////////////////////

#if 1
	std::ostringstream oss;
	oss << VVX_SELF_EVT_CH_JOIN_START;

	switch (case_enum)
    {
		default:
		case VVX_CASE_CH_JOIN_CREATE: // Nor Ch
			oss << " " << m_strChannelName;
			break;

		case VVX_CASE_CH_JOIN_ADD: // Into Test
			//ss << " " << "TEST";
			oss << " " << VVX_CH_NAME_TEST;
			break;
	}

	AppendMessage(oss.str().c_str());
#endif

	InitialCaseEnum(case_enum);

	switch (DetectState())
    {
		case VVX_STATE_SHUTDOWN:
			m_eVivoxState = VVX_STATE_SHUTDOWN_OK;
			break;

		case VVX_STATE_INIT:
			m_eVivoxState = VVX_STATE_INIT_OK;
			break;

		case VVX_STATE_LOGIN:
			m_eVivoxState = VVX_STATE_LOGIN_OK;
			break;

		case VVX_STATE_SG_CREATE: // mu..!?
			//g_iVVXstate = VVX_STATE_SG_DEL;
			m_eVivoxState = VVX_STATE_LOGIN_OK; // GKy 100118, SG_CREATE pass by txALL check.
			break;

		default:
			m_eVivoxState = VVX_STATE_SHUTDOWN;
			if (ProcessByState(m_eVivoxState, NULL))
            {
				return 0;
			}
            else
            {
				m_eVivoxState = VVX_STATE_SHUTDOWN_OK;
			}
			break;

	} // switch (DetectState())

	StateManager* pkStateManager = m_pkVivoxApp->GetStateManager();
	if (pkStateManager)
    {
		pkStateManager->txALL();
        return 1;
	}
    else
    {
		InitialCaseEnum( VVX_CASE_IDLE );
		return 0;
	}
}

int VivoxClient::JoinChannel(const char* channel_name, int user_id, VVX_CASE case_enum)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::JoinChannel(%s, %d, %s)\n", channel_name, user_id, GetCaseEnumName(case_enum).c_str());
    OutputDebugString(szDebug);
#endif

	//// GKy 100121, put here will crash...try again...
	switch (m_iLoginMode)
    {
		case VVX_LOGIN_MODE_INIT: // GKy 100129 improve
			m_iLoginMode = VVX_LOGIN_MODE_NA;

		case VVX_LOGIN_MODE_NA:
			return 0;
			break;

		default:
			break;

	} // switch (m_iLoginMode)

	// SET NEEDED DATA
	VVX_CASE case_temp = VVX_CASE_CH_JOIN_CREATE;

	//VivoxClient::m_iVVXcase  = VVX_CASE_CH_JOIN_INIT; // need set Later void effect other on going process.
    // For distinguish different Join Ch Type
	switch (case_enum)
    {
		default:
			break;

		//case VVX_CASE_CH_JOIN_CREATE: // Already onGoing, do nothings.
		//case VVX_CASE_CH_JOIN_ADD:
		//	break;

		case VVX_CASE_CH_JOIN_INIT:
			//m_sVivoxChannelNamePre = m_sVivoxChannelName; // GKy 100111
			// GKy 100112 here done, afraid of rapid;y reCLick effect. mu..
			// GKy 100112 try done as ensure Join parts.
			m_strChannelName = channel_name;

			//strT.Format("%d",user_id);
			//m_oSelf.display_name = strT;
			SetDBID(user_id);

			case_temp = VVX_CASE_CH_JOIN_CREATE;
			break;

		//case VVX_CASE_TEST_ADD: // Already onGoing, do nothings. TBC.
		//	break;

		case VVX_CASE_TEST_INIT:
			m_strChannelURI = GetEchoURI();
			case_temp = VVX_CASE_CH_JOIN_ADD;
			break;

	} // switch (case_enum)

	///////////////////////////////////////////////////
    // Check if Enable, before here need keep some data
	if (!m_bEnable)
    { 
		return 0;
	}
	///////////////////////////////////////////////////

	// Check if VivoxClient::m_iVVXcase is valid

	switch (m_iCase)
    {
	//switch(VivoxClient::m_iVVXcase){

		// Busy, Wait +++++++++++++++++++++++++++++++++++++++++
		case VVX_CASE_DISABLE:
		//case VVX_CASE_CH_JOIN_INIT:
		case VVX_CASE_CH_EXIT_INIT:
		//case VVX_CASE_TEST_INIT:
			SetCaseEnum(case_temp);
			break;

		// GKy 100114 improve for ChSwitch case ++++++++++++++++
		case VVX_CASE_CH_JOIN_CREATE:
		case VVX_CASE_CH_JOIN_ADD:
			//ChannelNamePreviousSet(channel_name); // for S_MSG display
			// Have mirage, will effect 1st Leave =w=;

			ExitChannelWithInitialCase();
			break;

		// GKy 100127 void VvxCnt::enable then call to ChJoin too quickly
		case VVX_CASE_ACC_CHECK: 
			break;
		
		// Do, BUT need handle previous existed Ch, GKy 100107 TBC ++++++++++++++++++
		case VVX_CASE_in_TEAM:
			//ChannelExitInit( ); // GKy 100107 OLD, have mirage:
            // GKy 100108 need more Test:
            switch (case_enum)
            {
				default:
					break;

				case VVX_CASE_CH_JOIN_INIT: // Into Another VoiceCh
					ExitChannelWithInitialCase( );
					break;

				case VVX_CASE_TEST_INIT: // Into TestCh
					ExitChannelWithInitialCase( );
					break;
			} // switch (case_enum)
			break;

		case VVX_CASE_in_TEST: //+++++++++++++++++++++++++++++++++++++++++++++++++
			//ChannelExitInit( ); // GKy 100107 OLD, have mirage:
            // GKy 100108 need more Test:
			switch (case_enum)
            {
				default:
					break;

				case VVX_CASE_CH_JOIN_INIT: 
					//ChannelExitInit();
					// Just Set para, really join will be done when TestEnd
					// GKy 100112 TestEnd is call to here. mu..Have mirage =w=;
					// GKy 100113 TestEnd now call to ChExit
					break;

				case VVX_CASE_TEST_INIT: // Still Into Test, do nothing.
					break;
			} // switch (case_enum)
			break;

		// Do +++++++++++++++++++++++++++++++++++++++++++
		default:
			JoinChannelWithInitialCase(case_temp);
			break;
	} // switch (m_iCase)

	return 1;
}

int VivoxClient::ExitChannelWithInitialCase()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::ExitChannelWithInitialCase()\n");
#endif
    
    InitialCaseEnum(VVX_CASE_CH_EXIT_INIT);

	switch (DetectState())
    {
		case VVX_STATE_SHUTDOWN:
			//g_iVVXstate = VVX_STATE_SS_REMOVE; //VVX_STATE_SHUTDOWN_OK; //X
			m_eVivoxState = VVX_STATE_SS_REMOVE_OK;
			break;
		//case VVX_STATE_INIT:
		//	g_iVVXstate = VVX_STATE_INIT_OK;
		//	break;
		//case VVX_STATE_LOGIN:
		//	g_iVVXstate = VVX_STATE_LOGIN_OK;
		//	break;

		case VVX_STATE_SG_CREATE:
			//g_iVVXstate = VVX_STATE_SG_DEL;
			m_eVivoxState = VVX_STATE_SS_REMOVE;
			if (ProcessByState(m_eVivoxState, NULL))
            {
				return 0;
			}
            else
            {
				// May be no session can be deleted
				m_eVivoxState = VVX_STATE_SS_REMOVE_OK;
			}
			break;

		default:
			m_eVivoxState = VVX_STATE_SS_REMOVE_OK;
			break;
	} // switch (DetectState())

	StateManager* pkStateManager = m_pkVivoxApp->GetStateManager();
	if (pkStateManager)
    {
		pkStateManager->txALL();
	}
    else
    {
		InitialCaseEnum(VVX_CASE_IDLE);
		return 0;
	}

	return 1;
}

int VivoxClient::ExitChannel(const char *channel_name, VVX_CASE case_enum)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::ExitChannel()\n");
#endif

	// RESET VAR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// GKy 091223 add extra input value to detect different exit case:
    // Only for distinguish different ExitCh Type, no used further more.
	switch (case_enum)
    {
		default:
			break;

		case VVX_CASE_CH_EXIT_INIT:
			if (!IsInTest())        // Not in test
            { 
				m_strChannelURI = ""; // GKy 100112 may be need move this to other place..
				m_strChannelName = "";
			}
            else                    // In test
            {
				//m_sVivoxChannelURI = ""; // keep URI for other case identify inTest
				m_strChannelName = "";
				return 0;
			}
			break;

		case VVX_CASE_TEST_END_INIT:
			if (IsInChannel())      // In some Team Voice Ch
            {
				if (!IsInTest())    // Not in test
                { 
					m_strChannelURI = "";
					m_strChannelName = "";
				}
                else
                {
					m_strChannelURI = "";
				}
			}
            else                    // Not in a Team Voice Ch
            {
				if (!IsInTest())    // In test
                { 
					m_strChannelURI = "";
					m_strChannelName = "";
				}
                else
                {
					m_strChannelURI = "";
					m_strChannelName = "";
				}
			} // if (IsInChannel())
			break;
	} // switch (case_enum)

	// GKy 091217 indeed, Exit should have the ablity to interupt..so set here?
	// BUT we still need switch case to detect..=w=; ...Seems I am too tired..
	
	//switch(VivoxClient::m_iVVXcase){
	switch (m_iCase)
    {
		// Busy, Wait
		case VVX_CASE_DISABLE:
		//case VVX_CASE_CH_JOIN_INIT:
		case VVX_CASE_CH_JOIN_CREATE:
		case VVX_CASE_CH_JOIN_ADD:
		case VVX_CASE_CH_EXIT_INIT:
		//case VVX_CASE_TEST_INIT:
			//VivoxClient::m_iVVXcase  = VVX_CASE_CH_EXIT_INIT;
			SetCaseEnum( VVX_CASE_CH_EXIT_INIT );
			break;

		//case VVX_CASE_in_TEAM:
		//case VVX_CASE_in_TEST:
		//	VivoxClient::CASEini( VVX_CASE_IDLE ); // 
		//	break;

		// Do
		default:
			ExitChannelWithInitialCase();
			break;
	} // switch (m_iCase)

	return 1;
}

int VivoxClient::Disconnected()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::Disconnected()\n");
#endif

	// Reset, BUT due to zS fnc already call to ChExit, so may be no need? mu..
	// GKy 100126 seems have some crisis?
	m_ParticipantGroup.ClearAll();
	m_iPartnerDBidLast = 0;

	// Send World Evt
	//VivoxClient::messageStore( VVX_WORLD_EVT_CH_EXIT ); 
	// Ch to call zS fnc
    //CChatFrame::ExitVoiceChannel();
	AppendMessage( VVX_SELF_EVT_SM_DISCONNECTED ); 

	return 1;
}

//-------------------------------------------------------------
void VivoxClient::Close(int bIfSendWorldEvt)
{
    SetLoginMode(VVX_LOGIN_MODE_NA);

    InitialCaseEnum(VVX_CASE_IDLE);

    m_bSysEnableVoiceChat = false;
    SaveSystemSettings();

    if (bIfSendWorldEvt && m_bEnable)
    {
        AppendMessage(VVX_WORLD_EVT_DISABLE_OK);
    }

    Disable_With_CheckEnable();

#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::Close(%d)\n", bIfSendWorldEvt);
    OutputDebugString(szDebug);
#endif
}

void VivoxClient::PartnerMute(int iDBid, bool bYes)
{
    s_p_iolock->Take();
    //////////////////////////////////////////////////////////////////////////

    std::ostringstream oss;
    std::string URI = m_ParticipantGroup.GetUriByDBID(iDBid);
    int mute = (bYes ? 1 : 0);

	// 1. Internal data modify and send a World Evt. ---------------

	ParticipantState p;
	p = m_ParticipantGroup.GetStateByUri( (const char*) URI.c_str() );

	if (p.uri == "")
    {
        s_p_iolock->Release();
        return;
	}

	///////////////////////////////////////////////////////////////////////

	if (bYes)
    {
		AppendMessageEvent(VVX_WORLD_EVT_PART_MUTE_ON,  URI.c_str());
	}
    else
    {
		AppendMessageEvent(VVX_WORLD_EVT_PART_MUTE_OFF, URI.c_str());
	}

	// 2. Send command to VVX core ---------------------------------
	// localusermute session_handle yesno(1 or 0) user_uri
	oss << " " << mute << " " << URI.c_str() << ""; // yesno(1 or 0) user_uri

	m_eVivoxState = VVX_STATE_PART_MUTE;
	ProcessByState(m_eVivoxState, oss.str().c_str());

    //////////////////////////////////////////////////////////////////////////
    s_p_iolock->Release();
}

int VivoxClient::GetDBID()
{
	return atoi(m_ParticipantState.display_name.c_str()); // using display name save DBID
}

void VivoxClient::SetDBID(int iDBid)
{
	//m_oSelf.display_name = DBid; // using display name save DBID
	std::ostringstream oss;
	oss << iDBid;
	m_ParticipantState.display_name = oss.str().c_str();
}

void VivoxClient::SetInputMode(int iMode)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    char szDebug[256];
    szDebug[255] = '\0';
    _snprintf(szDebug, 255, "VivoxClient::SetInputMode(%d)\n", iMode);
    OutputDebugString(szDebug);
#endif

	switch (iMode)
    {
		case VVX_INPUT_MODE_PTT:
			SetInputMute(true); // this mode need mute mic at first
			m_iInputMode = VVX_INPUT_MODE_PTT;
			break;

		case VVX_INPUT_MODE_DETECT:
		default:
            SetInputMute(m_bSysInputMute); // Reset mic by mic if enable flag;
			m_iInputMode = VVX_INPUT_MODE_DETECT;
			break;
	} // switch (iMode)
}

void VivoxClient::SetInputMute(bool isMute)
{
    CC_SetupInputMute(isMute);
}

void VivoxClient::SetAllVolumn( void )
{
	int micVol = -1;
	int spkVol = -1;
	int micSen = -1;

    micVol = m_iSysInputVolumn;
    spkVol = m_iSysOutputVolumn;
    micSen = m_iSysInputSensitivity;

	SetAllVolumn(micVol, spkVol, micSen);
}

void VivoxClient::SetAllVolumn(int micVol, int spkVol, int micSen)
{
	if (micVol != -1)
    {
        SetInputVolumn(micVol);
    }
	if (spkVol != -1)
    {
        SetOutputVolumn(spkVol);
    }
	if (micSen != -1)
    {
        SetInputSensitivity(micSen);
    }
}

void VivoxClient::SetInputVolumn(int vol)
{
    if (vol > 100)
        vol = 100;
    if (vol < 0)
        vol = 0;

	// GKy 091221: Need transform Value range from 0~100 to resonable range 40~75
	ConstrainVolumn(vol);
    m_iInputVolumn = vol;

    CC_SetupInputVolumn(m_iInputVolumn);
}

void VivoxClient::SetInputSensitivity(int vol)
{
	if (vol > 100)
        vol = 100;
    if (vol < 0)
        vol = 0;

	// GKy 100519 due to UI design mismatch, need convert the vol value
    //vol = vol - 100;
    //if (vol < 0)
    //    vol = -vol;

	m_iSensitivity = 100 - vol;
    m_iHangOver = 2; // auto stop in 2 sec.

    CC_SetupInputSensitivity(m_iSensitivity, m_iHangOver);
}

void VivoxClient::SetInputSensSwitch(double dEnergy)
{
	int vol = m_iInputVolumn;
	int volT = 50;
	int iEnergy = static_cast<int>(dEnergy * 100);

    // note : don't know why do this ... by slime
	if (iEnergy > m_iSensitivity)
    {
	}
    else
    {
		vol = 1;
		volT = 1;
	}

	// TuningVol --------------------------
    CC_SetupInputVolumn(vol);
}

void VivoxClient::SetOutputVolumn(int vol)
{
    if (vol > 100)
        vol = 100;
    if (vol < 0)
        vol = 0;

    // GKy 091221: Need transform Value range from 0~100 to resonable range 40~75
    ConstrainVolumn(vol);

    CC_SetupOutputVolumn(vol);
}

double VivoxClient::GetSelfEnergy()
{
	// call to >state to update the value? mu..do outsides.
	return m_ParticipantState.energy; // range seems from 0~0.5?
}

//////////////////////////////////////////////////////////////////////////

void VivoxClient::ConstrainVolumn(int& nValue)
{
    double volumn_temp = static_cast<double>(nValue) * 0.35;
    volumn_temp += 40;
    nValue = static_cast<int>(volumn_temp);
}

void VivoxClient::WaitDeviceResponse(int WaitTime)
{
    for (int i = 0; i < WaitTime; ++i)
    {
        if (m_eVivoxCase == VVX_CASE_IDLE)
        {
            break;
        }
        Sleep(10);
    }
}

void VivoxClient::WaitResponse(int WaitTime)
{
    for (int i = 0; i < WaitTime; ++i)
    {
        if (m_iCase == VVX_CASE_IDLE)
        {
            break;
        }
        Sleep(10);
    }
}

int VivoxClient::GetInputDeviceIndex()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::GetInputDeviceIndex()\n");
#endif

	//WaitDeviceResponse(c_DefaultWaitResponseTime);

	m_eVivoxCase = VVX_CASE_IN_DEV_GET;

    CC_ListInputDevice();

    //WaitDeviceResponse(c_DefaultWaitResponseTime);

    return m_iInputDeviceIndex;
}

void VivoxClient::SetInputDeviceIndex(int Index)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::SetInputDeviceIndex()\n");
#endif

	//WaitDeviceResponse(c_DefaultWaitResponseTime);

	m_eVivoxCase = VVX_CASE_IN_DEV_SET; // used this afraid of effect others..=w=;

	m_iInputDeviceIndex = Index;

    CC_ListInputDevice();
}

int VivoxClient::GetOutputDeviceIndex()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::GetOutputDeviceIndex()\n");
#endif

	//WaitDeviceResponse(c_DefaultWaitResponseTime);

	m_eVivoxCase = VVX_CASE_OUT_DEV_GET;

    CC_ListOutputDevice();

    //WaitDeviceResponse(c_DefaultWaitResponseTime);

	return m_iOutputDeviceIndex;
}

void VivoxClient::SetOutputDeviceIndex(int Index)
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString("VivoxClient::SetOutputDeviceIndex()\n");
#endif

	//WaitDeviceResponse(c_DefaultWaitResponseTime);

	m_eVivoxCase = VVX_CASE_OUT_DEV_SET; // 

	m_iOutputDeviceIndex = Index; //

    CC_ListOutputDevice();
}

//////////////////////////////////////////////////////////////////////////

void VivoxClient::TestStart()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::TestStart()\n"));
#endif

	if (!m_bEnable)
    {
        return;
    }

	JoinChannel("", 0, VVX_CASE_TEST_INIT);
}

void VivoxClient::TestEnd()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::TestEnd()\n"));
#endif

	// Need check if need reJoin back to Origin Channel
	if (!IsInChannel())
    {
        // ensure we are free to any Team channel.
		// ensure we are in test Channel
		if (IsInTest())
        { 
            ExitChannel(NULL, VVX_CASE_TEST_END_INIT);
		}
        else
        {
		}
	}
    else
    {
        // We are in some Ch
		// ensure we are in test Channel, and want Exit, need reJoin back to origin Ch.
		// GKy 091217 try do in ResponseMgr, ss_remove_ok?..still old way stable.

		if (IsInTest())
        { 
			//VivoxClient::CASEini( VVX_CASE_IDLE );
			// GKy 100112 this also need hide..
			//// GKy 100113 ma be also call to this? BUT..
			//// GKy 100113 here seems keep as OLD is better..BUT..
			//// GKy 100113 may be both can take a test..Indeed both way seems ALL OK? if want..
			//// GKy 100127 ensure this way is better ----------------------------------------
			ExitChannel(NULL, VVX_CASE_TEST_END_INIT);
			/*/// org ------------------------------------------------------------------------
			VivoxClient::ChannelJoin(VivoxClient::m_sVivoxChannelName.c_str(), atoi(VivoxClient::m_oSelf.display_name.c_str()) ); //+++
			//*//////////////////////////////// -----------------------------------------------
		}
        else
        {
		}
	}
}

//---------------------------------------------------------------

void VivoxClient::DumpMessage()
{
	std::ostringstream ossMsg;
	std::vector<std::string> vecMsg;

    s_o_iolock->Take();     // for Critical Sections; seems have bug?
    //////////////////////////////////////////////////////////////////////////
    vecMsg = m_vecMessage;  // make a copy
	m_vecMessage.clear();   // clear generic queue, then reLease it void deadLock
    //////////////////////////////////////////////////////////////////////////
    s_o_iolock->Release();  // for Critical Sections

  	// Dump Message
	for (std::vector<std::string>::iterator iter = vecMsg.begin(); iter != vecMsg.end(); ++iter)
	{
		std::vector<std::string> cmd = splitCmdLine((*iter));

		if (cmd.empty())
        {
            continue;
        }

		if (cmd[0] == VVX_SELF_EVT_ACC_CREATE_RETRY)
		{
			CNetCli_Login::SM_CreateVivoxAccount( m_strAccount.c_str() ); // Request Server Create this Acc again
		}
		else if (cmd[0] == VVX_SELF_EVT_SM_DISCONNECTED)
		{
			InitialCaseEnum( VVX_CASE_IDLE );

			if (g_pChatFrame)
            {
				g_pChatFrame->ExitVoiceChannel();
			}
		}
		else if (cmd[0] == VVX_SELF_EVT_CH_JOIN_OK ||
                 cmd[0] == VVX_SELF_EVT_CH_JOIN_START ||
                 cmd[0] == VVX_SELF_EVT_CH_EXIT_OK)
		{
            // "EVT ChName"
			if (g_pChatFrame)
            {
				if (cmd.size() > 1)
                {
					// 1. Parse Actual ChName, need refer to ChName Rules
					std::string sChName = cmd[1];
					//int iChID = -1;
					std::vector<std::string> vChName = splitCmdLine( sChName, '_' );
					//#define VVX_CH_NAME_FORMAT002 "%s.iSpAniA7551_%d_%d_%s" // GKy 091228
					//// Format: Territory.SecureCode_ChannelType_WorldID_SysID

					if (vChName.size() == 4)
                    {
						// NorCh
						switch ( atoi(vChName[1].c_str()) )
                        {
							case VVX_CH_TYPE_TEAM:
							case VVX_CH_TYPE_GUILD:
								sChName = g_ObjectData->GetString("S_VOICE_CHAT_CH_NAME_TEAM");
								break;

							case VVX_CH_TYPE_USER:
							{
								const char* channelName = NetCli_ChannelChild::GetChannelNameByID( atoi(vChName[3].c_str()) );
								if ( channelName != NULL )
                                {
									sChName = channelName;
								}
                                else
                                {
									sChName = "";
								}
							}	break;

                            default:
								sChName = "";
								break;
						}
					}
                    else
                    {
						// TestCh
						sChName = g_ObjectData->GetString("S_VOICE_CHAT_CH_NAME_TEST");
					}

					// 2. Send Message
					std::ostringstream oss;
					if (cmd[0] == VVX_SELF_EVT_CH_JOIN_OK)
                    {
						oss << VVX_SYS_MSG(S_VOICE_CHAT_CH_JOIN_OK_NAME) << "";
					}
                    else if (cmd[0] == VVX_SELF_EVT_CH_JOIN_START)
                    {
						oss << VVX_SYS_MSG(S_VOICE_CHAT_CH_JOIN_START_NAME) << "";
					}
                    else if (cmd[0] == VVX_SELF_EVT_CH_EXIT_OK)
                    {
						oss << VVX_SYS_MSG(S_VOICE_CHAT_CH_EXIT_OK_NAME) << "";
					}

					g_pChatFrame->SendChatMessageEx(CHAT_MSG_SYSTEM, "", oss.str().c_str(), sChName.c_str() );
				}
			}
		}
		else if (cmd[0] == VVX_WORLD_EVT_CH_JOIN ||
                 cmd[0] == VVX_WORLD_EVT_CH_EXIT ||
                 cmd[0] == VVX_WORLD_EVT_ENABLE_OK ||
                 cmd[0] == VVX_WORLD_EVT_DISABLE_OK)
		{
			if (g_pInterface)
            {
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_01
                char szDebug[256];
                szDebug[255] = '\0';
                _snprintf(szDebug, 255, "g_pInterface->SendWorldEvent(%s)\n", cmd[0].c_str());
                OutputDebugString(szDebug);
#endif
				g_pInterface->SendWorldEvent( cmd[0].c_str() );
            }
		}
        else if (cmd[0] == VVX_WORLD_EVT_CH_JOIN_PART ||
                 cmd[0] == VVX_WORLD_EVT_CH_EXIT_PART ||
                 cmd[0] == VVX_WORLD_EVT_PART_MUTE_ON ||
                 cmd[0] == VVX_WORLD_EVT_PART_MUTE_OFF)
		{
            // "EVT URI"
			if (g_pInterface)
            {
				// Get Participant Obj ------------------------
				ParticipantState p;
				std::string CharName = "";

                if (cmd.size() > 1)
                {
					p = m_ParticipantGroup.GetStateByUri(cmd[1].c_str());

					if (p.uri != "")
                    {
                        // find partner
						CharName = NetCli_OtherChild::GetRoleName( atoi(p.display_name.c_str()) );

						// GKy 100105 Add Mute Handle:
						if (cmd[0] == VVX_WORLD_EVT_PART_MUTE_ON)
                        {
							p.audio_muted_for_me = 1;
							m_ParticipantGroup.SetState(p);
						}
						else if (cmd[0] == VVX_WORLD_EVT_PART_MUTE_OFF)
                        {
							p.audio_muted_for_me = 0;
							m_ParticipantGroup.SetState(p);
						}
						else if (cmd[0] == VVX_WORLD_EVT_CH_EXIT_PART)
                        {
							if (m_ParticipantState.uri == p.uri)
                            {
                                // is Self Leave the Ch
								m_ParticipantGroup.ClearAll();
							}
                            else
                            {
								m_ParticipantGroup.RemoveStateByUri(p.uri.c_str());
							}
						}
					}
				}

				// Prepare Return Data ------------------------
				if (CharName != "")
                {
					lua_State* L = g_pInterface->GetLuaState();

					lua_pushstring( L, CharName.c_str() );
					lua_setglobal( L, "arg1" );

					//lua_pushnumber( L, energy );
					//lua_setglobal( L, "arg2" );
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_01
                    char szDebug[256];
                    szDebug[255] = '\0';
                    _snprintf(szDebug, 255, "g_pInterface->SendWorldEvent(%s)\n", cmd[0].c_str());
                    OutputDebugString(szDebug);
#endif
					g_pInterface->SendWorldEvent( cmd[0].c_str() );
				}
			}
		}
		else if (cmd[0] == VVX_WORLD_EVT_PART_UPDATE ||
                 cmd[0] == VVX_WORLD_EVT_PART_SILENT)
		{
            // "EVT URI energy is_speaking UpdateDataOnly is_muted_for_me" +++++++++++++
			if (g_pInterface)
            {
				if (cmd.size() > 5)
                {
					// Get Participant Obj ------------------------
					ParticipantState p;
					std::string CharName = "";
					//int UpdateDataOnly = 0;

					//UpdateDataOnly = atoi(cmd[4].c_str());

					p = m_ParticipantGroup.GetStateByUri(cmd[1].c_str());
					if (p.uri != "")
                    {
                        // find partner
						CharName = NetCli_OtherChild::GetRoleName( atoi(p.display_name.c_str()) );

						// update to partner
						p.energy = atof(cmd[2].c_str());
						p.speaking = atoi(cmd[3].c_str());
						p.audio_muted_for_me = atoi(cmd[5].c_str());

						m_ParticipantGroup.SetState(p);

						// Prepare Return Data ------------------------
						if (CharName != "" && cmd[4] == "0")
                        { //UpdateDataOnly = atoi(cmd[4].c_str());
							lua_State* L = g_pInterface->GetLuaState();

							lua_pushstring( L, CharName.c_str() );
							lua_setglobal( L, "arg1" );

							//lua_pushnumber( L, energy );
							//lua_setglobal( L, "arg2" );
#if VIVOX_CLIENT_DEBUG_PRINT_TRACE_INFO_01
                            char szDebug[256];
                            szDebug[255] = '\0';
                            _snprintf(szDebug, 255, "g_pInterface->SendWorldEvent(%s)\n", cmd[0].c_str());
                            OutputDebugString(szDebug);
#endif
							g_pInterface->SendWorldEvent( cmd[0].c_str() );
						}
					}
				}
			}
		}
		else
		{
            PrintToChatFrame(iter->c_str());
		}
	}

	FlushLog( ossMsg.str().c_str() ); // GKy 100105 #deBug

	//m_vMsg.clear(); // GKy 100127 move up
	vecMsg.clear(); // may be no need

}

void VivoxClient::AppendMessage(const char* str_message)
{
    s_o_iolock->Take();     // for Critical Sections
    //////////////////////////////////////////////////////////////////////////

	std::string str_temp = str_message;
	m_vecMessage.push_back(str_temp);

    //////////////////////////////////////////////////////////////////////////
    s_o_iolock->Release();  // for Critical Sections
}

std::string VivoxClient::AppendMessageEvent(const char* str_type, const char* str_id)
{
    std::string str_temp;
    str_temp.append(str_type);
    str_temp.append(" ");
    str_temp.append(str_id);

    AppendMessage(str_temp.c_str());

    return str_temp;
}

void VivoxClient::LeaveWorld()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::LeaveWorld()\n"));
#endif
	//VivoxClient::AccountSet(VVX_CLN_ACC);
	//VivoxClient::PasswordSet(VVX_CLN_PWD);
	//VivoxClient::LoginModeSet(VVX_LOGIN_MODE_NA);
}

void VivoxClient::OnRevServerList()
{
#if VIVOX_CLIENT_DEBUG_PRINT_FUNCTION_NAME
    OutputDebugString(_T("VivoxClient::OnRevServerList()\n"));
#endif
	// Reset some data
	SetAccount(VVX_CLN_ACC);
	SetPassword(VVX_CLN_PWD);
	SetLoginMode(VVX_LOGIN_MODE_NA);
}

void VivoxClient::FlushLog(const char* str_log)
{
	std::ostringstream ossFilePath;
	std::string strName = "_";

	// If input is empty, return.
	if (str_log == NULL)
    {
        return;
    }

	std::string str_temp = str_log;
	if (str_temp == "")
    {
        return;
    }

	if (m_iOutputDebugMessage < 1)
    {
        return;
    }

    ///////////////////////////////////////////////////

	if (g_pGameMain == NULL)
    {
        return;
    }

	int iDBid = g_pGameMain->GetDBID();

	CRoleSprite* pkRoleSprite = g_pGameMain->FindSpriteByDBID(iDBid);
	if (pkRoleSprite == NULL)
    {
		strName = m_strAccount;
	}
    else
    {
		strName = pkRoleSprite->GetName();
		if (strName == "")
        {
			strName = m_strAccount;
		}
	}

	if (strName == VVX_CLN_ACC)
    {
		strName = "_DefaultAcc";
	}

	//////////////////////////////////////////////////////////////////////////

	ResponseManager* pkResponseManager = m_pkVivoxApp->GetResponseManager();
	if (pkResponseManager == NULL)
    {
        return;
    }

	////////////////////////////////////////////////////////////////////////////////////////

	ossFilePath << VVX_PATH_LOG << "_" << strName.c_str() << "_" << pkResponseManager->CreateTimeStamp(false).c_str();

	std::string FilePath;
			//	FilePath = m_sRootPath + PCK_PATH_;
			//	FilePath = FilePath + PCK_FILE_ERRORLOG;
			//	FilePath = VVX_PATH_LOG;
				FilePath = ossFilePath.str().c_str();

	std::fstream oFileResult;
    oFileResult.open(FilePath.c_str(), std::ios::out | std::ios::app);
	if (oFileResult.is_open())
	{
		//Get Time
		time_t t;
		time( &t ); // fill now with the current time

		std::string strTime;
	    strTime = ctime(&t);
	    strTime.erase(24); // del '\n'
	    strTime += ""; // Add Null

		oFileResult << strTime.c_str() << ":" << endl << str_log << "\n";

		oFileResult.close();
	}
#if VIVOX_CLIENT_DEBUG_PRINT_ERROR_INFO
    else
    {
        std::ostringstream oss;
        oss << std::endl
            << "Unable to open Log file: " << FilePath << std::endl;
        OutputDebugString(oss.str().c_str());
		//std::cout << "\n Unable to open Log file:" << FilePath;
	}
#endif
}

// GKy 100206 add for debug
#if VVX_DEBUG
//-------------------------------------------------------------------
void VivoxClient::debug_CNetCli_Login_Child__RM_VivoxAccount(const char* pszAccout, const char* pszPassword, bool bCreateResult)
{
	std::stringstream ss; ss.str("");
	ss << "debug CNetCli_Login_Child::RM_VivoxAccount( " << pszAccout << "," << pszPassword <<","<< bCreateResult << ")"
       << "+++ VivoxClient::LoginModeGet() = " << VivoxClient::GetLoginMode();
	VivoxOutputPrint( NULL, ss.str().c_str() );

	switch( VivoxClient::GetLoginMode() ){

		default:
			break;

	}//switch

	////////////////////////////////////////////////

	static bool init = true; // GKy 100104 may obsolete

	//if( init ){
	if( false ){

		//SM_CreateVivoxAccount( pszAccout ); // Request Server Create this Acc again

		init = false;

	}else{

		// 1st bCreateResult == false;
		if( bCreateResult ){
			VivoxClient::SetLoginRetry( 0 );
		}else{
			VivoxClient::SetLoginRetry( 1 );
		}

		VivoxClient::SetAccount( pszAccout );
		VivoxClient::SetPassword( pszPassword );

		VivoxClient::CheckAccount();
		
		// 1. Response need handle in other place.

	}//if

}
#endif // #if VVX_DEBUG

void VivoxClient::CheckInputDeviceIndexRange()
{
    if (m_iInputDeviceIndex < 1)
    {
        m_iInputDeviceIndex = 1;
    }
    if (m_iInputDeviceIndex > m_mapInputDevices.size())
    {
        m_iInputDeviceIndex = m_mapInputDevices.size();
    }
}

void VivoxClient::SetServerURL(const char* str)
{
	std::string url = str;
	if (url != "")
    {
		if (m_strChannelNamePrefix != "")
        {
			m_strServerURL = str; 
		}
        else
        {
			m_strServerURL = VVX_SVR_URL_EMPTY; //
		}
	}
    else
    {
		m_strServerURL = VVX_SVR_URL_EMPTY; //VVX_SVR_URL; 
	}
}

//////////////////////////////////////////////////////////////////////////
