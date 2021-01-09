
#include "CommandHandler.h"
#include "Vxc.h"
#include "VxcRequests.h"
#include "VxcResponses.h"
#include "ResponseManager.h"
#include "RequestManager.h"
#include "StateManager.h"
#include <fstream>
#if defined (__linux__)
#include <stdlib.h>
#endif

#ifndef _WIN32
#ifdef SN_TARGET_PS3
#include <sys/timer.h>
#define Sleep(k) sys_timer_usleep(k*1000);
#else
#define Sleep(k) usleep(k * 1000)
#endif
#endif
static std::ofstream g_callbackLogFile;

using namespace std;



static bool ReadWholeFile(const std::string &filename, string &output)
{
    char * buffer;
    size_t size;
    ifstream file (filename.c_str(), ios::in|ios::binary|ios::ate);
    if(!file.is_open()) return false;
    size = (size_t)file.tellg();
    file.seekg (0, ios::beg);
    buffer = new char [size];
    file.read (buffer, size);
    file.close();
    std::string tmp(buffer, size);
    delete[] buffer;
    output = tmp;
    return true;
}

static void WriteToCallBackFile(const char* msg)
{
    g_callbackLogFile << ResponseManager::CreateTimeStamp() << ": " << msg << std::endl << std::endl;
    g_callbackLogFile.flush();
	// GKy 100114, GKy 100115 keep as OLD.
    //if (debuglevel >= 1){
	//if (VivoxClient::m_bOutDebugMsg >= 1){
    
		g_callbackLogFile << ResponseManager::CreateTimeStamp() << ": " << msg << std::endl << std::endl;
		g_callbackLogFile.flush();
	//}//if

}

static void OnLogMessage(const char* source, const char* level, const char* message)
{
    std::stringstream ss;
    ss << source << " " << level << message;
    WriteToCallBackFile(ss.str().c_str());
}

static void InitializeLogging(vx_log_type log_type, int log_level)
{
    std::string folder;
#ifdef _WIN32
    //folder = vx_strdup("C:\\VivoxLogs\\");
    folder = vx_strdup(".\\VivoxLogs\\");
#else
    folder = vx_strdup("./VivoxLogs/");
#endif

    vx_register_logging_initialization(log_type, folder.c_str(), vx_strdup("vx"), vx_strdup(".txt"), log_level, OnLogMessage);
	// GKy 100106 hide
    vx_register_logging_initialization(log_type, folder.c_str(), vx_strdup("vxIsp"), vx_strdup(".txt"), log_level, OnLogMessage);
	// GKy 100114
	//vx_register_logging_initialization(log_to_file, folder.c_str(), vx_strdup("vxIsp"), vx_strdup(".txt"), 0, OnLogMessage); 
	// GKy 100115 improve..seems no need? not sure if init will call here..check..
	//vx_register_logging_initialization(log_to_file, folder.c_str(), vx_strdup("vxIsp"), vx_strdup(".txt"), 0, OnLogMessage); 

	////DECLARE_COMMAND(initlogging,"logtype (file=0, callback=1, file and callback=2), loglevel (no logging=0, error=1, warning=2, info=3, debug=4, trace=5)");

}

CommandHandler::~CommandHandler()
{

}

bool CommandHandler::validateInt(const std::string &command, const std::string &param, int &val) const
{
    if (sscanf(param.c_str(),"%d",&val) != 1)
    {
        printUsage(command);
        return false;
    }
    else
    {
        return true;
    }
}

bool CommandHandler::validateDouble(const std::string &command, const std::string &param, double &val) const
{
    if (sscanf(param.c_str(),"%lf",&val) != 1)
    {
        printUsage(command);
        return false;
    }
    else
    {
        return true;
    }
}

Disposition CommandHandler::initlogging(const std::vector<std::string> &cmd)
{
    vx_log_type log_type; 
    int log_level;

    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    if (atoi(cmd.at(1).c_str()) == 0)
        log_type = log_to_file;
    else if (atoi(cmd.at(1).c_str()) == 1)
        log_type = log_to_callback;
    else if (atoi(cmd.at(1).c_str()) == 2)
        log_type = log_to_file_and_callback;
    else
    {
        cout << "Invalid Log type..." << std::endl;
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    log_level = atoi(cmd.at(2).c_str());

    cout << "Initializing SDK Logging..." << std::endl;

    if ((log_type == log_to_callback || log_type == log_to_file_and_callback) && log_level > 0)
    {
        m_respMgr->OpenCallBackFile();
    }
    InitializeLogging(log_type, log_level);
    return DispositionSubmitted;
}

Disposition CommandHandler::init(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
        return printUsage(cmd.at(0));
    std::string server;
    int minPort = 0;
    int maxPort = 0;

    server = cmd.at(1);        //pull from user input
    if (cmd.size() >= 3)
    {
        if (!validateInt(cmd.at(0),cmd.at(2),minPort)) return DispositionNotSubmitted;
    }
    if (cmd.size() >= 4)
    {
        if (!validateInt(cmd.at(0),cmd.at(3),maxPort)) return DispositionNotSubmitted;
    }

    cout << "Initializing Connector:\n";

    m_reqMgr->req_ConnectorCreate(server.c_str(), minPort, maxPort);
    return DispositionSubmitted;
}

Disposition CommandHandler::shutdown(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    if (m_stateMgr->GetConnectorHandle() != cmd.at(1))
    {
        cout << std::endl << "Connector handle " << cmd.at(1) << " not found." << std::endl << std::endl;
        return DispositionNotSubmitted;
    }

    cout << "Shutting Down Connector..." << std::endl;

    m_reqMgr->req_ConnectorShutdown(cmd.at(1));
    return DispositionSubmitted;
}

Disposition CommandHandler::login(const std::vector<std::string> &cmd)
{
    std::string username;
    std::string password;
    int participantPropertyFrequency = 100;     // default to on state change
    int buddyManagementMode = 0;                // default to AutoAccept
    int autoanswer = 0;                         // default to false
    int pres = 1;
    int text = 1;
    int sendChannelNotify = 0;

    if (cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    username = cmd.at(2);
    password = cmd.at(3);
    if (cmd.size() >= 5)  pres = atoi(cmd.at(4).c_str());
    if (cmd.size() >= 6)  autoanswer = atoi(cmd.at(5).c_str());
    if (cmd.size() >= 7)  text = atoi(cmd.at(6).c_str());
    if (cmd.size() >= 8)  participantPropertyFrequency = atoi(cmd.at(7).c_str());
    if (cmd.size() >= 9)  buddyManagementMode = atoi(cmd.at(8).c_str());
    cout << "Logging in to Connector:\n";

    m_reqMgr->req_AccountLogin(cmd.at(1), username, password, pres, autoanswer, text, participantPropertyFrequency, vx_buddy_management_mode(buddyManagementMode));

    return DispositionSubmitted;
}

Disposition CommandHandler::authtokenlogin(const std::vector<std::string> &cmd)
{
    std::string authToken;
    int participantPropertyFrequency = 100;     // default to on state change
    int buddyManagementMode = 0;                // default to AutoAccept
    int autoanswer = 0;                         // default to false
    int pres = 1;
    int text = 1;
    int sendChannelNotify = 0;

    if (cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    authToken = cmd.at(2);
    if (cmd.size() >= 4)  pres = atoi(cmd.at(3).c_str());
    if (cmd.size() >= 5)  autoanswer = atoi(cmd.at(4).c_str());
    if (cmd.size() >= 6)  text = atoi(cmd.at(5).c_str());
    if (cmd.size() >= 7)  participantPropertyFrequency = atoi(cmd.at(6).c_str());
    if (cmd.size() >= 8)  buddyManagementMode = atoi(cmd.at(7).c_str());
    cout << "Logging in to Connector:\n";

    m_reqMgr->req_AccountAuthTokenLogin(cmd.at(1), authToken, pres, autoanswer, text, participantPropertyFrequency, vx_buddy_management_mode(buddyManagementMode));

    return DispositionSubmitted;
}

Disposition CommandHandler::anonymouslogin(const std::vector<std::string> &cmd)
{
    std::string displayname;
    int participantPropertyFrequency = 100;     // default to on state change
    int buddyManagementMode = 0;                // default to AutoAccept
    int pres = 0;
    int sendChannelNotify = 0;

    if (cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    if (cmd.size() >= 3)  displayname = cmd.at(2);
    if (cmd.size() >= 4)  pres = atoi(cmd.at(3).c_str());
    if (cmd.size() >= 5)  participantPropertyFrequency = atoi(cmd.at(4).c_str());
    if (cmd.size() >= 6)  buddyManagementMode = atoi(cmd.at(5).c_str());
    cout << "Annonymously Logging in to Connector:\n";

    m_reqMgr->req_AccountAnonymousLogin(cmd.at(1), displayname, pres, participantPropertyFrequency, vx_buddy_management_mode(buddyManagementMode));

    return DispositionSubmitted;
}

Disposition CommandHandler::logout(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Logging out of Connector..." << std::endl;

    m_reqMgr->req_AccountLogout(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::loginprops(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int autoanswer;
    if (!validateInt(cmd.at(0),cmd.at(2),autoanswer)) return DispositionNotSubmitted;
    int ppfreq;
    if (!validateInt(cmd.at(0),cmd.at(3),ppfreq)) return DispositionNotSubmitted;
    int enable_send_chan_notifs;
    if (!validateInt(cmd.at(0),cmd[4],enable_send_chan_notifs)) return DispositionNotSubmitted;
    cout << "Setting Login Properties..." << std::endl;


    m_reqMgr->req_SetLoginProperties(cmd.at(1),autoanswer,ppfreq,enable_send_chan_notifs);

    return DispositionSubmitted;
}

Disposition CommandHandler::sgcreate(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int playback = 0;
    if(cmd.size() == 3)
    {
        if (!validateInt(cmd.at(0),cmd.at(2),playback)) return DispositionNotSubmitted;
    }

    cout << "Creating SessionGroup..." << std::endl;

    m_reqMgr->req_SessionGroupCreate(cmd.at(1),playback);

    return DispositionSubmitted;
}

Disposition CommandHandler::sgterminate(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Terminating SessionGroup..." << std::endl;


    m_reqMgr->req_SessionGroupTerminate(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgaddsession(const std::vector<std::string> &cmd)
{
    std::string pw;
    if(cmd.size() < 5 || cmd.size() > 8)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int connectAudio;
    if (!validateInt(cmd.at(0),cmd.at(3),connectAudio)) return DispositionNotSubmitted;

    int connectText;
    if (!validateInt(cmd.at(0),cmd[4],connectText)) return DispositionNotSubmitted;

    int sessionFontID = 0;
    if (cmd.size() > 5)
    {
        if (!validateInt(cmd.at(0),cmd[5],sessionFontID)) return DispositionNotSubmitted;
    }

    if(cmd.size() > 6)
    {
        pw = cmd[6];    //send password if supplied, otherwise send empty string
    }

    int jitter_compensation = 0;
    if (cmd.size() > 7)
    {
        if (!validateInt(cmd.at(0),cmd[7],jitter_compensation)) return DispositionNotSubmitted;
    }

    cout << "Adding Session to SessionGroup..." << std::endl;


    m_reqMgr->req_SessionGroupAddSession(cmd.at(1), cmd.at(2), connectAudio, connectText, sessionFontID, pw, jitter_compensation);

    return DispositionSubmitted;
}


Disposition CommandHandler::sgremovesession(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Removing Session from SessionGroup..." << std::endl;


    m_reqMgr->req_SessionGroupRemoveSession(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgsetfocus(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Setting Focus..." << std::endl;


    m_reqMgr->req_SessionGroupSetFocus(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgunsetfocus(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Unsetting Focus..." << std::endl;


    m_reqMgr->req_SessionGroupUnsetFocus(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgresetfocus(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Resetting Focus..." << std::endl;


    m_reqMgr->req_SessionGroupResetFocus(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgsettx(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Setting Transmit Session..." << std::endl;


    m_reqMgr->req_SessionGroupSetTx(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgsettxall(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Setting Transmit to all Sessions..." << std::endl;


    m_reqMgr->req_SessionGroupSetTxAll(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::sgsettxnone(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Setting transmit to no session..." << std::endl;


    m_reqMgr->req_SessionGroupSetTxNone(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::createsession(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int connectAudio;
    if (!validateInt(cmd.at(0),cmd.at(3),connectAudio)) return DispositionNotSubmitted;

    int connectText;
    if (!validateInt(cmd.at(0),cmd[4],connectText)) return DispositionNotSubmitted;

    int sessionFontId = 0;
    if(cmd.size() > 5)
    {
        if (!validateInt(cmd.at(0),cmd[5],sessionFontId)) return DispositionNotSubmitted;
    }

    std::string channelName;
    if(cmd.size() > 6)
    {
        channelName = cmd[6];    //send channel name if supplied, otherwise send empty string
    }
    std::string pw;
    if(cmd.size() > 7)
    {
        pw = cmd[7];    //send password if supplied, otherwise send empty string
    }

    int useHash = 0;
    if(cmd.size() > 8)
    {
        if (!validateInt(cmd.at(0),cmd[8],useHash)) return DispositionNotSubmitted;
    }

    int jitter_compensation =0;
    if (cmd.size() > 9)
    {
        if (!validateInt(cmd.at(0), cmd[9], jitter_compensation)) return DispositionNotSubmitted;
    }

    cout << "Creating session..." << std::endl;

    m_reqMgr->req_SessionCreate(cmd.at(1), cmd.at(2), sessionFontId, channelName, pw, connectAudio, connectText, useHash, jitter_compensation);

    return DispositionSubmitted;
}

Disposition CommandHandler::mediaconnect(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int sessionFontID = 0;
    if(cmd.size() > 2)
    {
        if (!validateInt(cmd.at(0),cmd.at(2),sessionFontID)) return DispositionNotSubmitted;
    }

    int jitter_compensation = 0;
    if (cmd.size() > 3)
    {
        if (!validateInt(cmd.at(0),cmd.at(3),jitter_compensation)) return DispositionNotSubmitted;
    }

    cout << "Connecting media..." << std::endl;

    m_reqMgr->req_MediaConnect(cmd.at(1),sessionFontID, jitter_compensation);

    return DispositionSubmitted;
}

Disposition CommandHandler::mediadisconnect(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Disconnecting media..." << std::endl;

    m_reqMgr->req_MediaDisconnect(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::textconnect(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Connecting text..." << std::endl;

    m_reqMgr->req_TextConnect(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::textdisconnect(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Disconnecting text..." << std::endl;

    m_reqMgr->req_TextDisconnect(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::terminatesession(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Terminating session..." << std::endl;


    m_reqMgr->req_SessionTerminate(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::sessionmute(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(2),mute)) return DispositionNotSubmitted;
    if (mute > 0)
        cout << "Muting Session..." << std::endl;
    else
        cout << "Unmuting Session..." << std::endl;

    vx_mute_scope mutescope = mute_scope_all;
    if (cmd.size() == 4)
    {
        int scope;
        if (!validateInt(cmd.at(0),cmd.at(3),scope)) return DispositionNotSubmitted;
        if (scope == 1)
            mutescope = mute_scope_audio;
        else if (scope == 2)
            mutescope = mute_scope_text;
    }



    m_reqMgr->req_SessionMuteLocalSpeaker(cmd.at(1),mute,mutescope);

    return DispositionSubmitted;
}

Disposition CommandHandler::sessionvol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(2),vol)) return DispositionNotSubmitted;

    cout << "Setting Session Speaker Volume ..." << std::endl;


    m_reqMgr->req_SessionSetLocalSpeakerVolume(cmd.at(1),vol);

    return DispositionSubmitted;
}

Disposition CommandHandler::getsessionfonts(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting Session Fonts..." << std::endl;

    m_reqMgr->req_GetSessionFonts(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::gettemplatefonts(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting Template Fonts..." << std::endl;


    m_reqMgr->req_GetTemplateFonts(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::setvoicefont(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Setting Voice Font..." << std::endl;



    m_reqMgr->req_SessionSetVoiceFont(cmd.at(1),atoi(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::call(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    std::string channelName;
    if(cmd.size() > 3)
    {
        channelName = cmd.at(3);    //send channel name if supplied, otherwise send empty string
    }
    std::string pw;
    if(cmd.size() > 4)
    {
        pw = cmd[4];    //send password if supplied, otherwise send empty string
    }
    cout << "Calling " << cmd.at(2) << "..." << std::endl;


    m_reqMgr->req_SessionCreate(cmd.at(1), cmd.at(2).c_str(), 0, channelName, pw, 1, 0, 0, 0);

    return DispositionSubmitted;
}

Disposition CommandHandler::answer(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int sessionFontID = 0;
    if(cmd.size() > 2)
    {
        if (!validateInt(cmd.at(0),cmd.at(2),sessionFontID)) return DispositionNotSubmitted;
    }

    int jitter_compensation = 0;
    if (cmd.size() > 3)
    {
        if (!validateInt(cmd.at(0),cmd.at(3),jitter_compensation)) return DispositionNotSubmitted;
    }

    cout << "Answering call..." << std::endl;


    m_reqMgr->req_MediaConnect(cmd.at(1),sessionFontID, jitter_compensation);

    return DispositionSubmitted;
}

Disposition CommandHandler::hangup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Hanging up..." << std::endl;


    m_reqMgr->req_MediaDisconnect(cmd.at(1));

    return DispositionSubmitted;
}

static vx_channel_mode ChannelModeFromString(const std::string &value)
{
    int mode = atoi(value.c_str());
    if (mode == 1)
        return  channel_mode_presentation;
    else if (mode == 2)
        return  channel_mode_lecture;
    else if (mode == 3)
        return  channel_mode_open;
    else if (mode == 4)
        return  channel_mode_auditorium;
    else
        return  channel_mode_normal;
}

static vx_channel_type ChannelTypeFromString(const std::string &value)
{
    int type = atoi(value.c_str());
    if (type == 0)
        return channel_type_normal;
    else
        return channel_type_positional;
}

Disposition CommandHandler::createchannel(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int maxp = 50;
    int persistent = 1;
    vx_channel_mode channel_mode  = channel_mode_normal;
    int maxrange = -1;
    int clamping = -1;
    double rolloff = -1;
    double maxgain = -1;
    int distmodel = -1;
    int encrypt=0;
    std::string pw;
    vx_channel_type channel_type = channel_type_normal;
    int pers = 0;

    size_t cmdIdx = 1;
    string accountHandle = cmd.at(cmdIdx++);
    string channelName = cmd.at(cmdIdx++);
    string channelDesc;
    
    if(cmdIdx < cmd.size())
        channelDesc = cmd.at(cmdIdx++);
    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd[cmdIdx++],maxp)) return DispositionNotSubmitted;
    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd[cmdIdx++],pers)) return DispositionNotSubmitted;
    
    if(cmdIdx < cmd.size())
        channel_mode = ChannelModeFromString(cmd.at(cmdIdx++));
    if(cmdIdx < cmd.size())
        channel_type = ChannelTypeFromString(cmd.at(cmdIdx++));
    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd.at(cmdIdx++),encrypt)) return DispositionNotSubmitted;

    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd.at(cmdIdx++),maxrange)) return DispositionNotSubmitted;

    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd.at(cmdIdx++),clamping)) return DispositionNotSubmitted;
    if(cmdIdx < cmd.size())
        if (!validateDouble(cmd.at(0),cmd.at(cmdIdx++),rolloff)) return DispositionNotSubmitted;
    if(cmdIdx < cmd.size())
        if (!validateDouble(cmd.at(0),cmd.at(cmdIdx++),maxgain)) return DispositionNotSubmitted;
    if(cmdIdx < cmd.size())
        if (!validateInt(cmd.at(0),cmd.at(cmdIdx++),distmodel)) return DispositionNotSubmitted;
    if(cmdIdx < cmd.size())
        pw = cmd.at(cmdIdx++);

    cout << "Creating Channel..." << std::endl;


    m_reqMgr->req_CreateChannel(accountHandle,channelName,channelDesc,channel_type, maxp,pers,channel_mode,maxrange,clamping,rolloff,maxgain,distmodel,pw,encrypt);

    return DispositionSubmitted;
}

Disposition CommandHandler::updatechannel(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 7)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int maxrange = -1;
    int clamping = -1;
    double rolloff = -1;
    double maxgain = -1;
    int distmodel = -1;

    int maxp;
    if (!validateInt(cmd.at(0),cmd[5],maxp)) return DispositionNotSubmitted;
    int pers;
    if (!validateInt(cmd.at(0),cmd[6],pers)) return DispositionNotSubmitted;
    int is_protected = -1;    
    if(cmd.size() > 7) {
        if (!validateInt(cmd.at(0),cmd[7],is_protected)) return DispositionNotSubmitted;
    }

    vx_channel_mode channel_mode;
    channel_mode = channel_mode_none;
    if (cmd.size() > 8)
    {
        int mode = atoi(cmd[8].c_str());
        if (mode == 0)
            channel_mode = channel_mode_normal;
        else if (mode == 1)
            channel_mode = channel_mode_presentation;
        else if (mode == 2)
            channel_mode = channel_mode_lecture;
        else if (mode == 3)
            channel_mode = channel_mode_open;
        else if (mode == 4)
            channel_mode = channel_mode_auditorium;
        else
            channel_mode = channel_mode_none;
    }

    std::string pw;
    int encrypt=0;
    if (cmd.size() > 9)
    {
        if (!validateInt(cmd.at(0),cmd[9],encrypt)) return DispositionNotSubmitted;
        if (encrypt == 1)
            encrypt=1; 
    }
    if (cmd.size() > 14)
    {
        if (!validateInt(cmd.at(0),cmd[10],maxrange)) return DispositionNotSubmitted;
        if (!validateInt(cmd.at(0),cmd[11],clamping)) return DispositionNotSubmitted;
        if (!validateDouble(cmd.at(0),cmd[12],rolloff)) return DispositionNotSubmitted;
        if (!validateDouble(cmd.at(0),cmd[13],maxgain)) return DispositionNotSubmitted;
        if (!validateInt(cmd.at(0),cmd[14],distmodel)) return DispositionNotSubmitted;
    }
    if (is_protected == 1)
    {
        if (cmd.size() == 16)
        {
            pw = cmd[15];
        }
        else
        {
            cout << "Password is missing." << std::endl;
            printUsage(cmd.at(0));
            return DispositionNotSubmitted;
        }
    }

    cout << "Updating Channel..." << std::endl;


    m_reqMgr->req_UpdateChannel(cmd.at(1),cmd.at(2),cmd.at(3),cmd[4],maxp,pers,is_protected,channel_mode,maxrange,clamping,rolloff,maxgain,distmodel,pw, encrypt);

    return DispositionSubmitted;
}

Disposition CommandHandler::deletechannel(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Deleting Channel..." << std::endl;


    m_reqMgr->req_DeleteChannel(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::getfavs(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting Favorites..." << std::endl;


    m_reqMgr->req_GetFavs(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::setfav(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 6)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int group;
    if (!validateInt(cmd.at(0),cmd[5],group)) return DispositionNotSubmitted;

    int fav_id = 0;
    if (cmd.at(2) != "''")
    {
        if (!validateInt(cmd.at(0),cmd.at(2),fav_id)) return DispositionNotSubmitted;
    }

    string label;
    if (cmd.size() == 7)
        label = cmd[6];

    cout << "Setting Favorite..." << std::endl;


    m_reqMgr->req_SetFav(cmd.at(1),fav_id,cmd.at(3),cmd[4],group,label);

    return DispositionSubmitted;
}

Disposition CommandHandler::deletefav(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int fav;
    if (!validateInt(cmd.at(0),cmd.at(2),fav)) return DispositionNotSubmitted;

    cout << "Deleting Favorite..." << std::endl;


    m_reqMgr->req_DeleteFav(cmd.at(1),fav);

    return DispositionSubmitted;
}

Disposition CommandHandler::setfavgroup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Setting Favorite Group..." << std::endl;

    int fav_group_id = 0;
    if (cmd.at(2) != "''")
    {
        if (!validateInt(cmd.at(0),cmd.at(2),fav_group_id)) return DispositionNotSubmitted;
    }



    m_reqMgr->req_SetFavGroup(cmd.at(1),fav_group_id,cmd.at(3),cmd[4]);
    return DispositionSubmitted;
}

Disposition CommandHandler::deletefavgroup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int group;
    if (!validateInt(cmd.at(0),cmd.at(2),group)) return DispositionNotSubmitted;

    cout << "Deleting Favorite Group..." << std::endl;


    m_reqMgr->req_DeleteFavGroup(cmd.at(1),group);

    return DispositionSubmitted;
}

Disposition CommandHandler::getchannelinfo(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting Channel Info..." << std::endl;


    m_reqMgr->req_GetChannelInfo(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::searchchannels(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 6)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int pgNum;
    if (!validateInt(cmd.at(0),cmd.at(2),pgNum)) return DispositionNotSubmitted;
    int pgSize;
    if (!validateInt(cmd.at(0),cmd.at(3),pgSize)) return DispositionNotSubmitted;

    cout << "Searching Channels..." << std::endl;
    int active = 0;
    if (cmd.size() == 7)
    {
        if (!validateInt(cmd.at(0),cmd[6],active)) return DispositionNotSubmitted;
    }
    vx_channel_moderation_type modsearch = channel_moderation_type_all;
    if (cmd.size() == 8)
    {
        int mod;
        if (!validateInt(cmd.at(0),cmd[7],mod)) return DispositionNotSubmitted;
        if (mod == 1) modsearch = channel_moderation_type_current_user;
    }


    m_reqMgr->req_SearchChannels(cmd.at(1),pgNum,pgSize,cmd[4],cmd[5],active,modsearch);

    return DispositionSubmitted;
}

Disposition CommandHandler::searchaccounts(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 9)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int pgNum;
    if (!validateInt(cmd.at(0),cmd.at(2),pgNum)) return DispositionNotSubmitted;
    int pgSize;
    if (!validateInt(cmd.at(0),cmd.at(3),pgSize)) return DispositionNotSubmitted;

    cout << "Searching Buddies..." << std::endl;


    m_reqMgr->req_SearchAccounts(cmd.at(1),pgNum,pgSize,cmd[4],cmd[5],cmd[6],cmd[7],cmd[8]);

    return DispositionSubmitted;
}

Disposition CommandHandler::modmuteall(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    vx_mute_scope mutescope = mute_scope_all;
    if (cmd.size() == 5)
    {
        int scope;
        if (!validateInt(cmd.at(0),cmd[4],scope)) return DispositionNotSubmitted;
        if (scope == 1)
            mutescope = mute_scope_audio;
        else if (scope == 2)
            mutescope = mute_scope_text;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(2),mute)) return DispositionNotSubmitted;

    if (mute > 0)
        cout << "Muting all users..." << std::endl;
    else
        cout << "Unmuting all users..." << std::endl;


    m_reqMgr->req_MuteAllUsers(cmd.at(1),mute,cmd.at(3),mutescope);

    return DispositionSubmitted;
}

Disposition CommandHandler::modmute(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    vx_mute_scope mutescope = mute_scope_all;
    if (cmd.size() == 6)
    {
        int scope;
        if (!validateInt(cmd.at(0),cmd[5],scope)) return DispositionNotSubmitted;
        if (scope == 1)
            mutescope = mute_scope_audio;
        else if (scope == 2)
            mutescope = mute_scope_text;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(2),mute)) return DispositionNotSubmitted;

    if (mute > 0)
        cout << "Muting user..." << std::endl;
    else
        cout << "Unmuting user..." << std::endl;


    m_reqMgr->req_MuteUser(cmd.at(1),mute,cmd.at(3),cmd[4],mutescope);

    return DispositionSubmitted;
}

Disposition CommandHandler::ban(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int ban;
    if (!validateInt(cmd.at(0),cmd.at(2),ban)) return DispositionNotSubmitted;

    if (ban > 0)
        cout << "Banning user..." << std::endl;
    else
        cout << "Unbanning user..." << std::endl;



    m_reqMgr->req_BanUser(cmd.at(1),ban,cmd.at(3),cmd[4]);

    return DispositionSubmitted;
}

Disposition CommandHandler::getbannedlist(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting banned users..." << std::endl;


    m_reqMgr->req_GetBannedUsers(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::kick(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Kicking user..." << std::endl;


    m_reqMgr->req_KickUser(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::lock(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Locking channel..." << std::endl;


    m_reqMgr->req_SetLockMode(cmd.at(1),cmd.at(2),channel_lock);

    return DispositionSubmitted;
}

Disposition CommandHandler::unlock(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Unlocking channel..." << std::endl;


    m_reqMgr->req_SetLockMode(cmd.at(1),cmd.at(2),channel_unlock);

    return DispositionSubmitted;
}

Disposition CommandHandler::localusermute(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(2),mute)) return DispositionNotSubmitted;

    vx_mute_scope mutescope = mute_scope_all;
    if (cmd.size() == 5)
    {
        int scope;
        if (!validateInt(cmd.at(0),cmd[4],scope)) return DispositionNotSubmitted;
        if (scope == 1)
            mutescope = mute_scope_audio;
        else if (scope == 2)
            mutescope = mute_scope_text;
    }

    if (mute > 0)
        cout << "Muting user locally..." << std::endl;
    else
        cout << "Unmuting user locally..." << std::endl;


    m_reqMgr->req_LocalUserMute(cmd.at(1),mute,cmd.at(3),mutescope);

    return DispositionSubmitted;
}

Disposition CommandHandler::localuservolume(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(2),vol)) return DispositionNotSubmitted;

    cout << "Setting user's volume locally..." << std::endl;


    m_reqMgr->req_LocalUserVolume(cmd.at(1),vol,cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::addmoderator(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Adding Moderator..." << std::endl;


    m_reqMgr->req_ModeratorAdd(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::removemoderator(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Removing Moderator..." << std::endl;


    m_reqMgr->req_ModeratorRemove(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::getmoderators(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Retrieving Moderators..." << std::endl;


    m_reqMgr->req_ModeratorGet(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::addacl(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Adding ACL..." << std::endl;


    m_reqMgr->req_ACLAdd(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::removeacl(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Removing ACL..." << std::endl;


    m_reqMgr->req_ACLRemove(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::getacl(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Retrieving ACL..." << std::endl;


    m_reqMgr->req_ACLGet(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::changechannelowner(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Changing Channel Owner..." << std::endl;


    m_reqMgr->req_ChangeChannelOwner(cmd.at(1),cmd.at(2),cmd.at(3));

    return DispositionSubmitted;
}

Disposition CommandHandler::senddata(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    std::string content_type = "text/xml";
    if (cmd.size() == 5)
        content_type = cmd[4];
    cout << "Sending Data..." << std::endl;

    m_reqMgr->req_SendUserAppData(cmd.at(1),cmd.at(2),cmd.at(3),content_type);

    return DispositionSubmitted;
}

Disposition CommandHandler::getparts(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int pgNum;
    if (!validateInt(cmd.at(0),cmd.at(3),pgNum)) return DispositionNotSubmitted;
    int pgSize;
    if (!validateInt(cmd.at(0),cmd[4],pgSize)) return DispositionNotSubmitted;

    cout << "Getting Channel Participants..." << std::endl;


    m_reqMgr->req_GetParts(cmd.at(1),cmd.at(2),pgNum,pgSize);

    return DispositionSubmitted;
}

Disposition CommandHandler::audioinfo(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 1)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting audio info..." << std::endl;


    m_reqMgr->req_AudioInfo();

    return DispositionSubmitted;
}

Disposition CommandHandler::speakervol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(1),vol)) return DispositionNotSubmitted;

    cout << "Setting Local Speaker Volume..." << std::endl;


    m_reqMgr->req_SpeakerVol(vol);

    return DispositionSubmitted;
}

Disposition CommandHandler::speakermute(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(1),mute)) return DispositionNotSubmitted;

    if (mute > 0)
        cout << "Muting Local Speaker..." << std::endl;
    else
        cout << "Unmuting Local Speaker..." << std::endl;


    m_reqMgr->req_SpeakerMute(mute);

    return DispositionSubmitted;
}

Disposition CommandHandler::micvol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(1),vol)) return DispositionNotSubmitted;

    cout << "Setting Local Mic Volume..." << std::endl;


    m_reqMgr->req_MicVol(vol);

    return DispositionSubmitted;
}

Disposition CommandHandler::micmute(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int mute;
    if (!validateInt(cmd.at(0),cmd.at(1),mute)) return DispositionNotSubmitted;

    if (mute > 0)
        cout << "Muting Local Mic..." << std::endl;
    else
        cout << "Unmuting Local Mic..." << std::endl;


    m_reqMgr->req_MicMute(mute);

    return DispositionSubmitted;
}


Disposition CommandHandler::movetoorigin(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position to the origin" << std::endl;


    m_reqMgr->req_moveToOrigin(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::dance(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int count = atoi(cmd.at(2).c_str());
    int delay = atoi(cmd.at(3).c_str());
    cout << "Moving around the origin " << count << " times with a delay of " << delay << std::endl;
    cout.flush();

    for(int i=0;i<count;++i) {
        m_reqMgr->req_moveToOrigin(cmd.at(1));
        Sleep(delay);
        m_reqMgr->req_moveLeft(cmd.at(1), 1);
        Sleep(delay);
        m_reqMgr->req_moveRight(cmd.at(1), 1);
        Sleep(delay);
        m_reqMgr->req_moveBack(cmd.at(1), 1);
        Sleep(delay);
        m_reqMgr->req_moveRight(cmd.at(1), 1);
        Sleep(delay);
    }

    return DispositionSubmitted;
}

Disposition CommandHandler::enablevvs(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2 && cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    string host = cmd.at(1).c_str();
    int port = 44125;
    if(cmd.size() == 3) {
        port = atoi(cmd.at(2).c_str());
    }
    int status = m_reqMgr->req_enableVVS(host, port);
    if(status != 0)
        cout << "enablevvs failed - error " << status << endl;
    else
        cout << "SDK Handle is " << m_stateMgr->get_SdkHandle() << endl;
    return DispositionSubmitted;
}

Disposition CommandHandler::disablevvs(const std::vector<std::string> &cmd)
{
    int status = m_reqMgr->req_disableVVS();
    if(status != 0)
        cout << "disablevvs failed - error " << status << endl;
    else 
        cout << "vvs disabled" << endl;
    return DispositionSubmitted;
}

Disposition CommandHandler::state(const std::vector<std::string> &cmd)
{

    m_reqMgr->req_StateDump();
    return DispositionSubmitted;
}
Disposition CommandHandler::moveleft(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Left by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveLeft(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::moveright(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Right by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveRight(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::moveforward(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Forward by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveForward(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::moveback(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Back by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveBack(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::moveup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Up by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveUp(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::movedown(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Moving Listener Position Down by " << cmd.at(2) << std::endl;


    m_reqMgr->req_moveDown(cmd.at(1),atof(cmd.at(2).c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::turnleft45(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Turning Listener Left (Anti-Clockwise) by 45 degrees" << std::endl;


    m_reqMgr->req_turnLeft45(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::turnright45(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Turning Listener Right (Clockwise) by 45 degrees" << std::endl;


    m_reqMgr->req_turnRight45(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::sessionpos(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int angle;
    if (!validateInt(cmd.at(0),cmd.at(3),angle)) return DispositionNotSubmitted;
    if (angle < 0 || angle > 180)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int dist;
    if (!validateInt(cmd.at(0),cmd[4],dist)) return DispositionNotSubmitted;

    cout << "Setting session 3D position" << std::endl;


    m_reqMgr->req_sessionPos(cmd.at(1),cmd.at(2),angle,dist);

    return DispositionSubmitted;
}

Disposition CommandHandler::setbuddy(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 6)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int group;
    if (!validateInt(cmd.at(0),cmd[5],group)) return DispositionNotSubmitted;

    std::string msg;
    //if(cmd.size() == 7)
    //{
    //    msg = cmd[6];    //send msg if supplied, otherwise send empty string
    //}

    cout << "Setting Buddy..." << std::endl;


    m_reqMgr->req_BuddySet(cmd.at(1),cmd.at(2),cmd.at(3), cmd[4], group, msg);

    return DispositionSubmitted;
}

Disposition CommandHandler::deletebuddy(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Deleting Buddy..." << std::endl;

    m_reqMgr->req_BuddyDelete(cmd.at(1), cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::setbuddygroup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 5)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int group;
    if (!validateInt(cmd.at(0),cmd.at(2),group)) return DispositionNotSubmitted;

    cout << "Setting BuddyGroup..." << std::endl;


    m_reqMgr->req_BuddyGroupSet(cmd.at(1),group,cmd.at(3),cmd[4]);

    return DispositionSubmitted;
}

Disposition CommandHandler::deletebuddygroup(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int group;
    if (!validateInt(cmd.at(0),cmd.at(2),group)) return DispositionNotSubmitted;

    cout << "Deleting BuddyGroup..." << std::endl;


    m_reqMgr->req_BuddyGroupDelete(cmd.at(1),group);

    return DispositionSubmitted;
}

Disposition CommandHandler::createblockrule(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int pres;
    if (!validateInt(cmd.at(0),cmd.at(3),pres)) return DispositionNotSubmitted;

    cout << "Creating Block Rule..." << std::endl;

    m_reqMgr->req_CreateBlockRule(cmd.at(1),cmd.at(2),pres);

    return DispositionSubmitted;
}

Disposition CommandHandler::deleteblockrule(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Deleting Block Rule..." << std::endl;

    m_reqMgr->req_DeleteBlockRule(cmd.at(1).c_str(),cmd.at(2).c_str());

    return DispositionSubmitted;
}

Disposition CommandHandler::listblockrules(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Listing Block Rules..." << std::endl;

    m_reqMgr->req_ListBlockRules(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::createautoacceptrule(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int autoadd;
    if (!validateInt(cmd.at(0),cmd.at(3),autoadd)) return DispositionNotSubmitted;
    std::string nickname;
    if (cmd.size() == 5)
    {
        nickname = cmd[4];
    }
    cout << "Creating Auto Accept Rule..." << std::endl;

    m_reqMgr->req_CreateAutoAcceptRule(cmd.at(1),cmd.at(2),autoadd,nickname);

    return DispositionSubmitted;
}

Disposition CommandHandler::deleteautoacceptrule(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Deleting Auto Accept Rule..." << std::endl;

    m_reqMgr->req_DeleteAutoAcceptRule(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::listautoacceptrules(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Listing Auto Accept Rules..." << std::endl;

    m_reqMgr->req_ListAutoAcceptRules(cmd.at(1));

    return DispositionSubmitted;
}

Disposition CommandHandler::subscriptionreply(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 6)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Sending Subscription reply..." << std::endl;

    m_reqMgr->req_SubscriptionReply(cmd.at(1), cmd.at(2), cmd.at(3), vx_rule_type(atoi(cmd[4].c_str())), atoi(cmd[5].c_str()));

    return DispositionSubmitted;
}

Disposition CommandHandler::sendmsg(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Sending Message..." << std::endl;
    std::stringstream ss;
    for (size_t i=2; i<cmd.size(); i++)
    {
        ss << cmd[i];
        if (i<cmd.size() - 1) ss << " ";
    }

    m_reqMgr->req_SendMessage(cmd.at(1),ss.str().c_str());

    return DispositionSubmitted;
}

Disposition CommandHandler::setpresence(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 4) {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    } else {

        m_reqMgr->req_SetPresence(cmd.at(1), cmd.at(2), cmd.at(3));

        return DispositionSubmitted;
    }
}

Disposition CommandHandler::senddtmf(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    if (cmd.at(2).length() > 1)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }


    int retcode = m_reqMgr->req_SendDTMF(cmd.at(1),cmd.at(2));
    if (retcode == -1)
        cout << "Invalid DTMF value entered.  Please use 0-9,A,B,C,D,*,#" << std::endl;

    return DispositionSubmitted;
}

Disposition CommandHandler::sendnotification(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int state;
    if (!validateInt(cmd.at(0),cmd.at(2),state)) return DispositionNotSubmitted;


    m_reqMgr->req_SendNotification(cmd.at(1),state);

    return DispositionSubmitted;
}

Disposition CommandHandler::networktest(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2 && cmd.size() != 6)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    bool use_server = false;
    if (cmd.size() == 2)
    {
        use_server = true;
    }

    cout << "Testing Network..." << std::endl;

    if (use_server)
        m_reqMgr->req_NetworkTest(cmd.at(1));
    else
    {
        int echoport;
        if (!validateInt(cmd.at(0),cmd[4],echoport)) return DispositionNotSubmitted;
        int timeout;
        if (!validateInt(cmd.at(0),cmd[5],timeout)) return DispositionNotSubmitted;
        m_reqMgr->req_NetworkTest(cmd.at(1),cmd.at(2),cmd.at(3),echoport,timeout);
    }


    return DispositionSubmitted;
}

Disposition CommandHandler::recstart(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int deltas_per_control;
    if (!validateInt(cmd.at(0),cmd.at(2),deltas_per_control)) return DispositionNotSubmitted;

    int events = 0;
    int loop_duration = 0;
    string filename;
    if(cmd.size() >= 4)
        if (!validateInt(cmd.at(0),cmd.at(3),events)) return DispositionNotSubmitted;
    if(cmd.size() >= 5)
        if (!validateInt(cmd.at(0),cmd[4],loop_duration)) return DispositionNotSubmitted;
    if(cmd.size() >= 6)
        filename = cmd[5];

    cout << "Starting Client-Side Recording" << std::endl;


    m_reqMgr->req_CSControlRecording(cmd.at(1),VX_SESSIONGROUP_RECORDING_CONTROL_START,deltas_per_control,filename,events,loop_duration);

    return DispositionSubmitted;
}

Disposition CommandHandler::recstop(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Stopping Client-Side Recording" << std::endl;


    m_reqMgr->req_CSControlRecording(cmd.at(1),VX_SESSIONGROUP_RECORDING_CONTROL_STOP,0,"",0,0);

    return DispositionSubmitted;
}

Disposition CommandHandler::listrenderdevs(const std::vector<std::string> &cmd)
{
    cout << "Listing Available Audio Render Devices" << std::endl;


    m_reqMgr->req_ListRenderDevices();

    return DispositionSubmitted;

}

Disposition CommandHandler::listcapturedevs(const std::vector<std::string> &cmd)
{
    cout << "Listing Available Audio Capture Devices" << std::endl;


    m_reqMgr->req_ListCaptureDevices();

    return DispositionSubmitted;
}

Disposition CommandHandler::setrenderdev(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    std::string renderDevString;
    for (size_t i=1; i < cmd.size(); i++) {
        if (i > 1) {
            renderDevString += " ";
        }
        renderDevString += cmd[i];
    }
    cout << "Setting Render Device to '" << renderDevString << "' "<< std::endl;

    m_reqMgr->req_SetRenderDevice(renderDevString);

    return DispositionSubmitted;
}

Disposition CommandHandler::setcapturedev(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    std::string captureDevString;
    for (size_t i=1; i < cmd.size(); i++) {
        if (i > 1) {
            captureDevString += " ";
        }
        captureDevString += cmd[i];
    }

    cout << "Setting Capture Device to '" << captureDevString << "' "<< std::endl;

    m_reqMgr->req_SetCaptureDevice(captureDevString);

    return DispositionSubmitted;
}

Disposition CommandHandler::setdefaultrenderdev(const std::vector<std::string> &cmd)
{
    cout << "Setting Default Render Device "<< std::endl;

    m_reqMgr->req_SetDefaultRenderDevice();

    return DispositionSubmitted;
}

Disposition CommandHandler::setdefaultcapturedev(const std::vector<std::string> &cmd)
{
    cout << "Setting Default Capture Device "<< std::endl;

    m_reqMgr->req_SetDefaultCaptureDevice();

    return DispositionSubmitted;
}

Disposition CommandHandler::renderaudiostart(const std::vector<std::string> &cmd)
{
    int loop = 0;
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    if (cmd.size() == 3) 
    {
        if (atoi(cmd.at(2).c_str()) != 1) {
            printUsage(cmd.at(0));
            return DispositionNotSubmitted;
        }
        else 
        {
            loop = 1;
        }
    }

    cout << "Rendering audio from wav file '" << cmd.at(1) << "' "<< std::endl;
    if (loop == 1)
    {
        cout << "Loop mode is on " << std::endl << std::endl;
    }

    m_reqMgr->req_RenderAudioStart(cmd.at(1), loop);

    return DispositionSubmitted;
}

Disposition CommandHandler::renderaudiofrombufferstart(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 1 || cmd.size() > 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    std::string ahandle;
    if (cmd.size() > 1)
        ahandle = cmd.at(1).c_str();
    int template_font_id = -1;
    if (cmd.size() > 2)
    {
        if (!validateInt(cmd.at(0),cmd.at(2),template_font_id)) return DispositionNotSubmitted;
    }
    std::string deltaFile;
    if (cmd.size() > 3)
        deltaFile = cmd.at(3).c_str();

    std::string deltacontents;
    if(!deltaFile.empty())
    {
        if(!ReadWholeFile(deltaFile, deltacontents))
        {
            cout << std::endl << "Unable to open Delta file '" << deltaFile << "'." << std::endl << std::endl;
            return DispositionNotSubmitted;
        }
    }

    cout << "Rendering audio from internal buffer"<< std::endl;

    m_reqMgr->req_RenderAudioFromBufferStart(ahandle,template_font_id,deltacontents);

    return DispositionSubmitted;
}

Disposition CommandHandler::renderaudiostop(const std::vector<std::string> &cmd)
{
    cout << "Stopping render audio playback" << std::endl;

    m_reqMgr->req_RenderAudioStop();

    return DispositionSubmitted;
}

Disposition CommandHandler::settuningspeakervol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(1),vol)) return DispositionNotSubmitted;

    cout << "Setting Master Local Speaker Volume to " << cmd.at(1) << std::endl;


    m_reqMgr->req_MasterSpeakerSetVol(vol);

    return DispositionSubmitted;
}

Disposition CommandHandler::settuningmicvol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int vol;
    if (!validateInt(cmd.at(0),cmd.at(1),vol)) return DispositionNotSubmitted;

    cout << "Setting Master Local Mic Volume to " << cmd.at(1) << std::endl;


    m_reqMgr->req_MasterMicSetVol(vol);

    return DispositionSubmitted;
}

Disposition CommandHandler::gettuningspeakervol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 1)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Getting Master Local Speaker Volume." << std::endl;


    m_reqMgr->req_MasterSpeakerGetVol();

    return DispositionSubmitted;
}

Disposition CommandHandler::gettuningmicvol(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 1)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    cout << "Getting Master Local Mic Volume." << std::endl;


    m_reqMgr->req_MasterMicGetVol();

    return DispositionSubmitted;
}

Disposition CommandHandler::captureaudiostart(const std::vector<std::string> &cmd)
{
    cout << "Starting audio capture "<< std::endl;

    m_reqMgr->req_CaptureAudioStart();

    return DispositionSubmitted;
}

Disposition CommandHandler::captureaudiotobufferstart(const std::vector<std::string> &cmd)
{
    cout << "Starting audio capture to internalbuffer"<< std::endl;

    m_reqMgr->req_CaptureAudioToBufferStart();

    return DispositionSubmitted;
}

Disposition CommandHandler::captureaudiostop(const std::vector<std::string> &cmd)
{
    cout << "Stopping audio capture "<< std::endl;

    m_reqMgr->req_CaptureAudioStop();

    return DispositionSubmitted;
}

Disposition CommandHandler::updateaccount(const std::vector<std::string> &cmd)
{
    //not setting phone and carrier will cause the fields to be blanked out.
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Updating Account..." << std::endl;
    std::stringstream displayname;
    for (size_t i=2; i<cmd.size(); i++)
    {
        displayname << cmd[i];
        if (i<cmd.size() - 1) displayname << " ";
    }

    m_reqMgr->req_UpdateAccount(cmd.at(1),displayname.str());

    return DispositionSubmitted;
}

Disposition CommandHandler::getaccount(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Getting Account..." << std::endl;

    m_reqMgr->req_GetAccount(cmd.at(1),cmd.at(2));

    return DispositionSubmitted;
}

Disposition CommandHandler::sendsms(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Sending SMS..." << std::endl;
    std::stringstream ss;
    for (size_t i=3; i<cmd.size(); i++)
    {
        ss << cmd[i];
        if (i<cmd.size() - 1) ss << " ";
    }

    m_reqMgr->req_SendSMS(cmd.at(1),cmd.at(2),ss.str());

    return DispositionSubmitted;
}

Disposition CommandHandler::setidletimeout(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int timeout;
    if (!validateInt(cmd.at(0),cmd.at(1),timeout)) return DispositionNotSubmitted;


    m_reqMgr->req_SetIdleTimeout(timeout);

    return DispositionSubmitted;
}

Disposition CommandHandler::bindkey(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    std::set<int> codes;
    for(size_t i=2;i<cmd.size();++i) {
        codes.insert(atoi(cmd.at(i).c_str()));
    }

    m_reqMgr->req_BindKey(cmd.at(1), codes);

    return DispositionSubmitted;                
}

Disposition CommandHandler::resetpw(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 4) {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    } else {

        m_reqMgr->req_ResetPassword(cmd.at(1), cmd.at(2), cmd.at(3));

        return DispositionSubmitted;        
    }
}

Disposition CommandHandler::createaccount1(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 6) {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    } else {

        m_reqMgr->req_CreateAccount(cmd.at(1), cmd.at(2), "", cmd.at(3), cmd.at(4), cmd.at(5));

        return DispositionSubmitted;        
    }
}

Disposition CommandHandler::createaccount2(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 5) {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    } else {
        char buf[0x8000];
#ifdef WIN32
        FILE *fp = fopen(cmd.at(1).c_str(), "rb");
#else
        FILE *fp = fopen(cmd.at(1).c_str(), "r");
#endif
        if (fp == NULL) {
            cerr << "Unable to open grant document file '" << cmd.at(1) << std::endl;
            return DispositionNotSubmitted;
        }
        int nread = fread(buf, 1, 0x8000, fp);
        if(nread >= 0)
            buf[nread] = 0;
        fclose(fp);


        m_reqMgr->req_CreateAccount("", "", buf, cmd.at(2), cmd.at(3), cmd.at(4));

        return DispositionSubmitted;        
    }
}

Disposition CommandHandler::setvadproperties(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }

    int vad_hangover = atoi(cmd.at(1).c_str());

    int vad_sensitivity = atoi(cmd.at(2).c_str());

    cout << "Changing connector vad hangover to "<< vad_hangover << " (seconds), and sensitivity to "<< vad_sensitivity << std::endl;

    m_reqMgr->req_SetVadProperties(vad_hangover, vad_sensitivity);

    return DispositionSubmitted;
}

Disposition CommandHandler::getvadproperties(const std::vector<std::string> &cmd)
{

    cout << "Getting vad properties "<< std::endl;

    m_reqMgr->req_GetVadProperties();

    return DispositionSubmitted;
}

Disposition CommandHandler::injectaudiostart(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    string filename;
    filename = cmd.at(2);

    cout << "Starting Audio Injection" << std::endl;


    m_reqMgr->req_ControlAudioInjection(cmd.at(1),VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_START,filename);

    return DispositionSubmitted;
}

Disposition CommandHandler::injectaudiorestart(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    string filename;
    filename = cmd.at(2);

    cout << "Restarting Audio Injection" << std::endl;


    m_reqMgr->req_ControlAudioInjection(cmd.at(1),VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_RESTART,filename);

    return DispositionSubmitted;
}

Disposition CommandHandler::injectaudiostop(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    cout << "Stopping Audio Injection" << std::endl;


    m_reqMgr->req_ControlAudioInjection(cmd.at(1),VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_STOP,"");

    return DispositionSubmitted;
}

Disposition CommandHandler::listaudiobuffers(const std::vector<std::string> &cmd)
{
    m_stateMgr->ListAudioBuffers(&cout);

    return DispositionSubmitted;
}

Disposition CommandHandler::removeaudiobuffer(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    string audioBufferId;
    audioBufferId = cmd.at(1);

    cout << "Removing audio buffer... " << audioBufferId;


    m_stateMgr->RemoveAudioBuffer(audioBufferId);

    cout << "done" << std::endl;

    return DispositionSubmitted;
}

Disposition CommandHandler::exportaudiobuffer(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    string audioBufferId = cmd.at(1);
    string filePath = cmd.at(2);

    cout << "Exporting audio buffer " << audioBufferId << " to file " << filePath << "...";

    m_stateMgr->ExportAudioBufferToWav(audioBufferId, filePath);

    cout << "done" << std::endl;

    return DispositionSubmitted;
}
Disposition CommandHandler::dump(const std::vector<std::string> &cmd)
{
    cout << "Dumping State..." << endl;
    if(cmd.size() == 1)
    {
        m_stateMgr->DumpStateToFile(&cout);
        cout << endl;
    }
    else
    {
        ofstream dumpFile;
        string filename = cmd.at(1);
        filename.append(StateManager::GetTime());
        filename.append(".txt");
        dumpFile.open(filename.c_str());
        m_stateMgr->DumpStateToFile(&dumpFile);
        dumpFile.close();
    }
    return DispositionSubmitted;
}


Disposition CommandHandler::debuglevel(const std::vector<std::string> &cmd)
{
    if(cmd.size() != 2)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    int debug;
    if (!validateInt(cmd.at(0),cmd.at(1),debug)) return DispositionNotSubmitted;

    m_reqMgr->SetDebug(debug);
    m_respMgr->SetDebug(debug);
    return DispositionSubmitted;
}
Disposition CommandHandler::webcall(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 3)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    string accountHandle = cmd.at(1);
    string relativePath = cmd.at(2);
    std::vector<std::string> parameters;
    for(size_t i=3;i<cmd.size();++i) {
        parameters.push_back(cmd[i]);
    }
    m_reqMgr->req_WebCall(accountHandle, relativePath, parameters);
    return DispositionSubmitted;
}
Disposition CommandHandler::renderaudiomodify(const std::vector<std::string> &cmd)
{
    if(cmd.size() < 1)
    {
        printUsage(cmd.at(0));
        return DispositionNotSubmitted;
    }
    std::string font;
    font.reserve(0x8000);
    if(cmd.size() == 2) 
    {
        FILE *fp = fopen(cmd.at(1).c_str(), "rb");
        if(!fp) {
            fprintf(stderr, "unable to open font file '%s'\n", cmd.at(1).c_str());
            return DispositionNotSubmitted;
        }
        int c;
        do {
            c = fgetc(fp);
            if(c >= 0)
                font += (char)c;
        } while(c >= 0);
        fclose(fp);
    }
    m_reqMgr->req_RenderAudioModify(font);
    return DispositionSubmitted;
}

Disposition CommandHandler::printUsage(const std::string &key) const
{
    CommandMap::const_iterator itr;
    itr = m_commands.find(key);
    if(itr != m_commands.end()) {
        cout << "usage: " << itr->first << " " << itr->second.GetUsage() << endl << endl;
    } else {
        cout << "usage not defined for " << itr->first << endl << endl;;
    }
    return DispositionNotSubmitted;
}

#ifndef _WIN32
#define mem_fun1 mem_fun
#endif

#define DECLARE_COMMAND(x, y) m_commands.insert(std::make_pair(#x, Command(#x, std::mem_fun1(&CommandHandler::x), y)))

CommandHandler::CommandHandler(std::ostream &stdcout, std::ostream &stdcerr,RequestManager *reqMgr, 
                               ResponseManager *respMgr, StateManager *stateMgr) :
cout(stdcout),
cerr(stdcerr)
{
    m_reqMgr = reqMgr;
    m_respMgr = respMgr;
    m_stateMgr = stateMgr;

    DECLARE_COMMAND(initlogging,"logtype (file=0, callback=1, file and callback=2), loglevel (no logging=0, error=1, warning=2, info=3, debug=4, trace=5)");
    DECLARE_COMMAND(init,"account_management_server [minimum_port] [maximum_port]");
    DECLARE_COMMAND(shutdown,"connector_handle");
    DECLARE_COMMAND(login,"connector_handle username password [presence (0 or 1)] [auto-answer (0 or 1)] [enable-text (0 or 1)] [speaking_notif_freq] [buddy_management_mode (0=AutoAccept, 1=AutoAdd, 2=Block, 3=Hide, 4=Application)] [send_channel_notification (0 or 1)]");
    DECLARE_COMMAND(authtokenlogin,"connector_handle authtoken [presence (0 or 1)] [auto-answer (0 or 1)] [enable-text (0 or 1)] [speaking_notif_freq] [buddy_management_mode (0=AutoAccept, 1=AutoAdd, 2=Block, 3=Hide, 4=Application)] [send_channel_notification (0 or 1)]");
    DECLARE_COMMAND(anonymouslogin,"connector_handle [displayname] [presence (0 or 1)] [speaking_notif_freq] [buddy_management_mode (0=AutoAccept, 1=AutoAdd, 2=Block, 3=Hide, 4=Application)] [send_channel_notification (0 or 1)]");
    DECLARE_COMMAND(logout,"acct_handle");
    DECLARE_COMMAND(loginprops,"acct_handle auto-answer(0 or 1) speaking_notif_freq enable_send_channel_notifs");
    DECLARE_COMMAND(sgcreate,"acct_handle [playback(0 or 1)]");
    DECLARE_COMMAND(sgterminate,"group_handle");
    DECLARE_COMMAND(sgaddsession,"group_handle uri connect_audio (0 or 1) connect_text (0 or 1) [fontID] [password] [jitter_compensation]");
    DECLARE_COMMAND(sgremovesession,"group_handle session_handle");
    DECLARE_COMMAND(sgsetfocus,"group_handle session_handle");
    DECLARE_COMMAND(sgunsetfocus,"group_handle session_handle");
    DECLARE_COMMAND(sgresetfocus,"group_handle");
    DECLARE_COMMAND(sgsettx,"group_handle session_handle");
    DECLARE_COMMAND(sgsettxall,"group_handle");
    DECLARE_COMMAND(sgsettxnone,"group_handle");
    DECLARE_COMMAND(createsession,"acct_handle dest_uri connect_audio(0 or 1) connect_text(0 or 1) [fontID]  [channelName] [password] [passwordhashed (0 or 1)] [jitter_compensation]");
    DECLARE_COMMAND(mediaconnect,"session_handle [fontID] [jitter_compensation]");
    DECLARE_COMMAND(mediadisconnect,"session_handle");
    DECLARE_COMMAND(textconnect,"session_handle");
    DECLARE_COMMAND(textdisconnect,"session_handle");
    DECLARE_COMMAND(terminatesession,"session_handle");
    DECLARE_COMMAND(sessionmute,"session_handle mute(0 or 1) [scope(0=all,1=audio,2=text)]");
    DECLARE_COMMAND(sessionvol,"session_handle volume");
    DECLARE_COMMAND(getsessionfonts,"account_handle");
    DECLARE_COMMAND(gettemplatefonts,"account_handle");
    DECLARE_COMMAND(setvoicefont,"session_handle voice_font_id");
    DECLARE_COMMAND(call,"acct_handle dest_uri [channelName] [password]");        //starts audio only
    DECLARE_COMMAND(answer,"session_handle [fontID]");                            //answers audio only
    DECLARE_COMMAND(hangup,"session_handle");                                     //disconnects audio only
    DECLARE_COMMAND(createchannel,"acct_handle name [desc] [max_partips] [persist(0 or 1)] [mode (0=normal, 1=pres, 2=lec, 3=open, 4=aud)] [channel_type (static = 0, positional = 1)] [encrypt (1=encrypt, 0=default)] [maxrange] [clampingdist] [rolloff] [maxgain] [distmodel] [pw]");
    DECLARE_COMMAND(updatechannel,"acct_handle uri name desc max_partips persist(0 or 1) protect(0 or 1) [mode (0=normal, 1=pres, 2=lec, 3=open, 4=aud)][encrypt (1=encrypt, 0=default)] [maxrange] [clampingdist] [rolloff] [maxgain] [distmodel] [pw]");
    DECLARE_COMMAND(deletechannel,"acct_handle uri");
    DECLARE_COMMAND(getfavs,"acct_handle");
    DECLARE_COMMAND(setfav,"acct_handle fav_id channel_uri data group_id [label] (use '' for fav_id when creating new fav)");
    DECLARE_COMMAND(deletefav,"acct_handle fav_id");
    DECLARE_COMMAND(setfavgroup,"acct_handle group_id name data (use '' for group_id when creating new group)");
    DECLARE_COMMAND(deletefavgroup,"acct_handle group_id");
    DECLARE_COMMAND(getchannelinfo,"acct_handle uri");
    DECLARE_COMMAND(searchchannels,"acct_handle page_num page_size name desc [isactive] [moderate(0 or 1)] (use '' for any empty search criteria)");
    DECLARE_COMMAND(searchaccounts,"acct_handle page_num page_size first_name last_name user_name email displayname (use '' for empty search criteria)");
    DECLARE_COMMAND(modmuteall,"acct_handle yesno(1 or 0) chanuri [scope(0=all,1=audio,2=text)]");
    DECLARE_COMMAND(modmute,"acct_handle yesno(1 or 0) chanuri uri [scope(0=all,1=audio,2=text)]");
    DECLARE_COMMAND(ban,"acct_handle yesno(1 or 0) chanuri uri");
    DECLARE_COMMAND(getbannedlist,"acct_handle chanuri");
    DECLARE_COMMAND(kick,"acct_handle chanuri uri");
    DECLARE_COMMAND(lock,"acct_handle chanuri");
    DECLARE_COMMAND(unlock,"acct_handle chanuri");
    DECLARE_COMMAND(localusermute,"session_handle yesno(1 or 0) user_uri [scope(0=all,1=audio,2=text)]");
    DECLARE_COMMAND(localuservolume,"session_handle vol[0 - 100] user_uri");
    DECLARE_COMMAND(addmoderator,"acct_handle chanuri uri");
    DECLARE_COMMAND(removemoderator,"acct_handle chanuri uri");
    DECLARE_COMMAND(getmoderators,"acct_handle chanuri");
    DECLARE_COMMAND(addacl,"acct_handle chanuri uri");
    DECLARE_COMMAND(removeacl,"acct_handle chanuri uri");
    DECLARE_COMMAND(getacl,"acct_handle chanuri");
    DECLARE_COMMAND(changechannelowner,"acct_handle chan_uri new_owner_uri");
    DECLARE_COMMAND(senddata,"acct_handle to_uri content [content_type]");
    DECLARE_COMMAND(getparts,"acct_handle channel_uri page_num page_size");
    DECLARE_COMMAND(audioinfo,"connector_handle");
    DECLARE_COMMAND(speakervol,"volume(int)");
    DECLARE_COMMAND(speakermute,"mute(1 or 0)");
    DECLARE_COMMAND(micvol,"volume(int)");
    DECLARE_COMMAND(micmute,"mute(1 or 0)");
    DECLARE_COMMAND(movetoorigin,"session_handle");
    DECLARE_COMMAND(moveleft,"session_handle delta(float)");
    DECLARE_COMMAND(moveright,"session_handle delta(float)");
    DECLARE_COMMAND(moveforward,"session_handle delta(float)");
    DECLARE_COMMAND(moveback,"session_handle delta(float)");
    DECLARE_COMMAND(moveup,"session_handle delta(float)");
    DECLARE_COMMAND(movedown,"session_handle delta(float)");
    DECLARE_COMMAND(turnleft45,"session_handle");
    DECLARE_COMMAND(turnright45,"session_handle");
    DECLARE_COMMAND(sessionpos,"session_group_handle session_handle angle(0-180) dist)");
    DECLARE_COMMAND(setbuddy,"acct_handle accountbuddy_uri display_name buddy_data group_id");
    DECLARE_COMMAND(deletebuddy,"acct_handle buddy_uri");
    DECLARE_COMMAND(setbuddygroup,"acct_handle group_id group_name group_data");
    DECLARE_COMMAND(deletebuddygroup,"acct_handle group_id");
    DECLARE_COMMAND(createblockrule,"acct_handle mask presence_only(1 or 0)");
    DECLARE_COMMAND(deleteblockrule,"acct_handle mask");
    DECLARE_COMMAND(listblockrules,"acct_handle");
    DECLARE_COMMAND(createautoacceptrule,"acct_handle mask auto_add_as_buddy(1 or 0) [nickname]");
    DECLARE_COMMAND(deleteautoacceptrule,"acct_handle mask");
    DECLARE_COMMAND(listautoacceptrules,"acct_handle");
    DECLARE_COMMAND(subscriptionreply,"acct_handle subscription_handle uri rule_type(1=allow, 2=block, 3=hide) add_as_buddy(1 or 0)");
    DECLARE_COMMAND(sendmsg,"session_handle msg");
    DECLARE_COMMAND(setpresence,"acct_handle online|busy|lunch|phone|brb|away message");
    DECLARE_COMMAND(senddtmf,"session_handle dtmf (0-9,#,*)");
    DECLARE_COMMAND(sendnotification,"session_handle state (0 = Stopped Typing, 1 = Started Typing, 2 = Hand Lowered, 3 = Hand Raised)");
    DECLARE_COMMAND(networktest,"[well_known_ip stun_server echo_server echo_port timeout] or [acct_mgmt_server]");
    DECLARE_COMMAND(recstart,"session_group_handle delta_frames_per_control_frame [events(1 or 0) loop_duration_seconds filename]");
    DECLARE_COMMAND(recstop,"session_group_handle");
    DECLARE_COMMAND(listrenderdevs,"");
    DECLARE_COMMAND(listcapturedevs,"");
    DECLARE_COMMAND(setrenderdev,"render_device_name");
    DECLARE_COMMAND(setcapturedev,"capture_device_name");
    DECLARE_COMMAND(setdefaultrenderdev,"");
    DECLARE_COMMAND(setdefaultcapturedev,"");
    DECLARE_COMMAND(renderaudiostart,"wav_file_path [1 (loop mode - Default is play once)]");
    DECLARE_COMMAND(renderaudiofrombufferstart,"[acct handle] [template font id] [path to delta xml file]");
    DECLARE_COMMAND(renderaudiostop,"");
    DECLARE_COMMAND(settuningspeakervol,"[0 - 100]");
    DECLARE_COMMAND(settuningmicvol,"[0 - 100]");
    DECLARE_COMMAND(gettuningspeakervol,"");
    DECLARE_COMMAND(gettuningmicvol,"");
    DECLARE_COMMAND(captureaudiostart,"");
    DECLARE_COMMAND(captureaudiotobufferstart,"");
    DECLARE_COMMAND(captureaudiostop,"");
    DECLARE_COMMAND(updateaccount,"acct_handle displayname");
    DECLARE_COMMAND(getaccount,"acct_handle uri");
    DECLARE_COMMAND(sendsms,"acct_handle recipient_uri content");
    DECLARE_COMMAND(setidletimeout,"seconds (0 to disable idle timeouts");
    DECLARE_COMMAND(bindkey,"binding_name vkcode1 [vkcode2] [vkcode3] ... (4 is middle mouse, 32 is space, 160 is left shift)");
    DECLARE_COMMAND(resetpw,"server_url uri email");
    DECLARE_COMMAND(createaccount1,"admin_username admin_password username password server_url");
    DECLARE_COMMAND(createaccount2,"grant_document_filename username password server_url");
    DECLARE_COMMAND(setvadproperties,"hangover time in seconds (1 - 60) sensitivity (0 - 100)");
    DECLARE_COMMAND(getvadproperties,"");
    DECLARE_COMMAND(injectaudiostart,"session_group_handle wav_file_path");
    DECLARE_COMMAND(injectaudiorestart,"session_group_handle wav_file_path");
    DECLARE_COMMAND(injectaudiostop,"session_group_handle");
    DECLARE_COMMAND(listaudiobuffers,"");
    DECLARE_COMMAND(removeaudiobuffer,"audioBufferId");
    DECLARE_COMMAND(exportaudiobuffer,"audioBufferId wav_file_path");
    DECLARE_COMMAND(webcall,"account_handle relative_path [name1=value1] [name2=value2]...");
    DECLARE_COMMAND(renderaudiomodify, "[font filename]");
    DECLARE_COMMAND(debuglevel,"0-3");
    DECLARE_COMMAND(dump,"[filename]");
    DECLARE_COMMAND(dance,"session_handle iterations delay");
    DECLARE_COMMAND(enablevvs, "address [port]");
    DECLARE_COMMAND(disablevvs, "");
    DECLARE_COMMAND(state,"");
    m_commands.insert(std::make_pair("/?", Command("/?", std::mem_fun1(&CommandHandler::usage), "[match string]")));
    m_commands.insert(std::make_pair("?", Command("?", std::mem_fun1(&CommandHandler::usage), "[match string]")));
    m_commands.insert(std::make_pair("help", Command("help", std::mem_fun1(&CommandHandler::usage), "[match string]")));

}

Disposition CommandHandler::Execute(const std::vector<std::string> &cmd)
{
    if(cmd.empty())
        return DispositionNotSubmitted;
    CommandMap::const_iterator i = m_commands.find(cmd.at(0));
    if(i == m_commands.end()) {
        cout << "'" << cmd.at(0) << "' is not a valid command. Type ? for a list of valid commands." << endl;
        return DispositionNotSubmitted;
    } else {
        return (i->second.GetExecuteFunction())(this, cmd);
    }
}

Disposition CommandHandler::usage(const std::vector<std::string> &cmd)
{
    CommandMap::const_iterator itr;
    string match;
    if (cmd.size() > 1)
    {
        match = cmd[1];
        cout << endl << "Commands matching '" << match << "'" << endl << endl;
    } else 
    {
        cout << endl << "All Commands" << endl << endl;
    }
    int i=1;
    for (itr = m_commands.begin(); itr != m_commands.end(); ++itr) {
        if(match.empty() || itr->first.find(match) != std::string::npos) {
            cout << itr->first << " " << itr->second.GetUsage() << endl;
            i++;
        }
    }
    cout << endl;
    return DispositionNotSubmitted;
}
