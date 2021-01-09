/* Copyright (c) 2007 by Vivox Inc.
 *
 * Permission to use, copy, modify or distribute this software in binary or source form 
 * for any purpose is allowed only under explicit prior consent in writing from Vivox Inc.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND VIVOX DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL VIVOX
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "ResponseManager.h"
#include "StateManager.h"
#include "RequestManager.h"
#include "ParticipantState.h" // GKy 091230

#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>

#include "../../../mainproc/GameMain.h" // GKy 091222 for g_pGameMain and g_pInterface

//#include "../../../mainproc/RuneDev.h"
#include "../VivoxClient.h" // GKy 091215


#ifdef WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

using namespace std;

#ifdef _WIN32
//const std::string logPath = "c:\\VivoxLogs\\SampleApp\\";
const std::string logPath = ".\\VivoxLogsRespMgr\\App\\";
#else
const std::string logPath = "./VivoxLogs/SampleApp/";
#endif

std::string toString(vx_buddy_presence_state state)
{
    std::string presence;
    switch(state)
    {
    // !FIX make unknown = offline for now    
    //case buddy_presence_unknown: presence = "Unknown"; break;
    case buddy_presence_pending: presence = "Pending"; break;
    case buddy_presence_online: presence = "Online"; break;
    case buddy_presence_busy: presence = "Busy"; break;
    case buddy_presence_brb: presence = "BeRightBack"; break;
    case buddy_presence_away: presence = "Away"; break;
    case buddy_presence_onthephone: presence = "OnThePhone"; break;
    case buddy_presence_outtolunch: presence = "OutToLunch"; break;
    //case buddy_presence_closed: presence = "Closed"; break;
    case buddy_presence_offline: presence = "Offline"; break;
    case buddy_presence_online_slc: presence = "Online-slc"; break;
    default:
        presence="Unknown";
    };
    return presence;
}

std::string toString(vx_session_media_state value)
{
    switch(value) {
        case session_media_none: return "session_media_none";
        case session_media_disconnected:return "session_media_disconnected";
        case session_media_connected:return "session_media_connected";
        case session_media_connecting:return "session_media_connecting";
        case session_media_ringing:return "session_media_ringing";
        case session_media_hold:return "session_media_hold";
        case session_media_refer:return "session_media_refer";
        case session_media_disconnecting: return "session_media_disconnecting";
        default:
            return "unknown";
    };
}

std::string toString(vx_session_text_state value)
{
    switch(value) {
        case session_text_disconnected: return "session_text_disconnected";
        case session_text_connected: return "session_text_connected";
        case session_text_connecting: return "session_text_connecting";
        case session_text_disconnecting: return "session_text_disconnecting";
        default: return "unknown";
    }
}

std::string toString(vx_media_completion_type value)
{
    switch(value) {
        case media_completion_type_none: return "media_completion_type_none";
        case aux_buffer_audio_capture: return "aux_buffer_audio_capture";
        case aux_buffer_audio_render: return "aux_buffer_audio_render";
        case sessiongroup_audio_injection: return "sessiongroup_audio_injection";
        default:
        return "unknown vx_media_completion_type";
    }
}

ResponseManager::ResponseManager(std::ostream &stdcout, std::ostream &stdcerr, StateManager *sMgr, RequestManager *reqMgr) :
    cout(stdcout),
    cerr(stdcerr)
{
    debuglevel = 0;
    stateMgr = sMgr;
    stopOnShutdownResponse = false;
    stopNow = false;
    m_reqMgr = reqMgr;
    quickTestMode = false;
   
}

ResponseManager::~ResponseManager()
{
    if (debuglevel >= 1)
    {
        logFile.close();
        callbackLogFile.close();
    }
}

std::string ResponseManager::CreateTimeStamp(bool bShowSecond, bool bShowMin, bool bShowHour,
                                             bool bShowDay, bool bShowMonth, bool bShowYear)
{
    time_t curr;
    tm local;
    time(&curr);
    local=*(localtime(&curr));
    std::stringstream timestamp;
    if (bShowYear)
        timestamp << (local.tm_year + 1900);
    if (bShowMonth)
        timestamp << "." << (local.tm_mon + 1);
    if (bShowDay)
        timestamp << "." << local.tm_mday;
    if (bShowHour)
        timestamp << "-" << local.tm_hour;
    if (bShowMin)
        timestamp << "." << local.tm_min;
    if (bShowSecond)
		timestamp << "." << local.tm_sec;

    return timestamp.str();
}

void ResponseManager::CreateFolder(std::string path)
{
    std::vector<std::string> ss;
    size_t lastpos = 0;
    for(;;)
    {
#ifdef _WIN32
        size_t pos = path.find("\\", lastpos);
#else
        size_t pos = path.find("/", lastpos);
#endif
        if(pos == std::string::npos)
        {
            if(lastpos < path.size())
            {
                ss.push_back(path.substr(lastpos, path.size() - lastpos));
            }
            break;
        }
        else
        {
            ss.push_back(path.substr(lastpos, pos - lastpos));
        }
        lastpos = pos + 1;
        if(lastpos >= path.size())
            break;
    }

    std::stringstream st;
#ifdef _WIN32
    st << ss[0] << "\\";
#else
    st << ss[0] << "/";
#endif
    for (size_t i=1;i<ss.size();i++)
    {
#ifdef WIN32        
        st << ss[i] << "\\";
        mkdir(st.str().c_str());
#else
        st << ss[i] << "/";
        mkdir(st.str().c_str(), 0777 );
#endif        
    }
}

void ResponseManager::WriteResponseToFile(vx_resp_base_t* respObj)
{
    char* thexml = NULL;
    vx_response_to_xml(respObj, &thexml);
    std::string xmlstr(thexml);
    xmlstr = FormatXml(xmlstr);
    std::stringstream ss; 
    ss << "On Handle " << respObj->message.sdk_handle << endl << xmlstr;
    WriteToFile(ss.str().c_str());
    vx_free(thexml);
}

void ResponseManager::WriteEventToFile(vx_evt_base_t* evtObj)
{
    char* thexml = NULL;
    vx_event_to_xml(evtObj, &thexml);
    std::string xmlstr(thexml);
    xmlstr = FormatXml(xmlstr);
    std::stringstream ss; 
    ss << "On Handle " << evtObj->message.sdk_handle << endl << xmlstr;
    WriteToFile(ss.str().c_str());
    vx_free(thexml);
}

void ResponseManager::WriteLogCallbackToFile(const char* message)
{
    WriteToCallBackFile(message);
}

std::string ResponseManager::FormatXml(const std::string &thexml)
{
    std::stringstream res;
    int offset = 0;
    int d1 = 0;
    int d2 = 0;
    d1 = thexml.find("<",offset);
    d2 = thexml.find(">",offset);
    res << thexml.substr(0,d2 - d1 + 1);
    int current_indent = 0;
    res << endl;
    bool prevend = false;
    while (d2 > 0)
    {
        offset = d2 + 1;
        if (offset < (int)thexml.length())
        {
            d1 = thexml.find("<",offset);
            d2 = thexml.find(">",offset);

            //determine indent
            bool indent = true;
            if (thexml.substr(d1+1,1) == "/" && d1 == offset)
            {
                current_indent--;
                prevend = true;
            }
            else
            {
                if (thexml.substr(d2-1,1) != "/" && thexml.substr(d1+1,1) != "/") 
                {
                    if (prevend == false)
                    {
                        current_indent++;
                    }
                    prevend = false;
                }
                else
                {
                    prevend = true;
                }
            }

            //write content
            if (d1 > offset)
            {
                indent = false;
                res << thexml.substr(offset,d1 - offset);
            }

            //write indent
            if (indent) { for (int i=0;i<current_indent;i++) res << "   "; }

            //write tag
            res << thexml.substr(d1,d2 - d1 + 1);  

            //write line break
            if (thexml.substr(d2+1,1) == "<") { res << endl;}
        }
        else
        {
            d2 = 0;
        }
    }
    return res.str();
}

void ResponseManager::WriteToFile(const char* msg)
{
    if (debuglevel >= 3)
    {
        cout << msg << endl << endl;
    }
    if (debuglevel >= 1)
    {
        logFile << this->CreateTimeStamp() << ": ";
        logFile << msg << std::endl << std::endl;
        logFile.flush();
    }
}

void ResponseManager::WriteToCallBackFile(const char* msg)
{
    callbackLogFile << this->CreateTimeStamp() << ": ";
    callbackLogFile << msg << std::endl << std::endl;
    callbackLogFile.flush();
}

void ResponseManager::SetDebug(int debugval)
{
    debuglevel = debugval;
    if (logFile.is_open())
    {
        logFile.close();
    }
    if (debuglevel >= 1)
    {
        this->CreateFolder(logPath);
        std::string path = logPath;
#ifdef _WIN32
        if (path.substr(path.length()-1,1) != "\\")
        {
            path.append("\\");
        }
#else
        if (path.substr(path.length()-1,1) != "/")
        {
            path.append("/");
        }
#endif
        std::string filename = path + "vivox";
        filename.append(this->CreateTimeStamp());
        filename.append(".txt");
        logFile.open(filename.c_str());
    }
}

void ResponseManager::OpenCallBackFile()
{
    if(callbackLogFile.is_open())
    {
        callbackLogFile.close();
    }
    this->CreateFolder(logPath);
    std::string path = logPath;
    if (path.substr(path.length()-1,1) != "\\")
    {
        path.append("\\");
    }
    std::string callbackFileName = path + "vivoxCallBack";
    callbackFileName.append(this->CreateTimeStamp());
    callbackFileName.append(".txt");
    callbackLogFile.open(callbackFileName.c_str());
}

void ResponseManager::resp_ConnectorCreate(vx_resp_connector_create_t* respObj)
{
    std::string connectorHandle = respObj->connector_handle;        //retrieve the object ID from the response
    std::string ver(respObj->version_id);
    stateMgr->SetConnectorInitialized(connectorHandle,ver);
    if (debuglevel >= 2)
    {
        cout << "Connector Handle: " << connectorHandle << endl << endl;
    }

	/////
	// GKy 091217
	stateMgr->txConnectorCreateOK();


}

void ResponseManager::resp_ConnectorShutdown(vx_resp_connector_initiate_shutdown_t* respObj)
{
    stateMgr->SetConnectorUninitialized();

    if(stopOnShutdownResponse) {
        stopNow = true;
    }

	// GKy 091217 add
	stateMgr->txShutDownOK();

}

void ResponseManager::resp_ChannelCreate(vx_resp_account_channel_create_t* respObj)
{
    if (debuglevel >= 2)
        cout << endl << "Channel URI: " << respObj->channel_uri << endl;


	stateMgr->txChannelCreateOK( (const char*)respObj->channel_uri ); // GKy 091211

}

void ResponseManager::resp_ChannelFavSet(vx_resp_account_channel_favorite_set_t* respObj)
{
    if (debuglevel >= 2)
        cout << endl << "Fav ID: " << respObj->channel_favorite_id << endl;
}

void ResponseManager::resp_ChannelFavGroupSet(vx_resp_account_channel_favorite_group_set_t* respObj)
{
    if (debuglevel >= 2)
        cout << endl << "Fav Group ID: " << respObj->group_id << endl;
}

void ResponseManager::resp_CaptureAudioStop(vx_resp_aux_capture_audio_stop_t *respObj)
{
    if (respObj->audioBufferPtr != NULL)
    {
        // First, copy the passed in audio buffer
        void* audioBufferPtrCopy = vx_copy_audioBuffer(respObj->audioBufferPtr);

        if (audioBufferPtrCopy == NULL)
        {
            return;
        }

        // Now, free up the audioBufferPtr from the response object
        vx_free_audioBuffer(&(respObj->audioBufferPtr));

        // Finally, add this audio buffer to the internal map
        std::string audioBufferId = stateMgr->AddAudioBuffer(audioBufferPtrCopy);

        cout << endl << "Added a new audioBuffer, Id="<< audioBufferId << endl;
    }
}

void ResponseManager::resp_ListRenderDevices(vx_resp_aux_get_render_devices_t* respObj)
{
    if (respObj->count > 0)
    {
        cout << endl << endl << "Render Device List: " << endl;

		VivoxClient::GetInstance()->ClearOutputDevices(); // GKy

        //for (int i=0; i < respObj->count; i++)
        for (int j=0,i=(respObj->count)-1; 0 <= i; i--,j++) 
        {
            //cout << " " << i << ": " << respObj->render_devices[i]->device << endl;
            cout << " " << j << ": " << respObj->render_devices[i]->device << endl;

			std::string str = respObj->render_devices[i]->device;
			VivoxClient::GetInstance()->OutputDeviceNameStringByIndex(j) = str; // GKy 091215 make a backup.

			// GKy 091215 Get Index of Current Device
			if (str == respObj->current_render_device->device &&
                VivoxClient::GetInstance()->GetVivoxCase() == VVX_CASE_OUT_DEV_GET)
            {
				VivoxClient::GetInstance()->SetOutputDeviceIndex(j);
			}
        }
        cout << endl;
    }

    if (respObj->current_render_device && respObj->current_render_device->device)
    {
        cout << "Current Render Device: " << respObj->current_render_device->device << endl << endl;
    }
    if (respObj->effective_render_device && respObj->effective_render_device->device)
    {
        cout << "Effective Render Device: " << respObj->effective_render_device->device << endl << endl;
    }

	// GKy 091214, GKy 091216 cont.
	stateMgr->txListDevs();
}

void ResponseManager::resp_ListCaptureDevices(vx_resp_aux_get_capture_devices_t* respObj)
{
    if (respObj->count > 0)
    {
        cout << endl << endl << "Capture Device List: " << endl;

		VivoxClient::GetInstance()->ClearInputDevices(); // GKy

        for (int j = 0, i = (respObj->count) - 1; i >= 0; --i, ++j)
        {

            //cout << " " << i << ": " << respObj->capture_devices[i]->device << endl;
            cout << " " << j << ": " << respObj->capture_devices[i]->device << endl;

			std::string str = respObj->capture_devices[i]->device;
			VivoxClient::GetInstance()->InputDeviceNameStringByIndex(j) = str; // GKy 091214 make a backup.

			// GKy 091215 Get Index of Current Device..have mirage?..
			if (str == respObj->current_capture_device->device &&
                VivoxClient::GetInstance()->GetVivoxCase() == VVX_CASE_IN_DEV_GET)
            {
				//VivoxClient::m_iVivoxInDevIdx = j+1;
				VivoxClient::GetInstance()->SetInputDeviceIndex(j);

			}//if
        }
        cout << endl;
    }

    if (respObj->current_capture_device && respObj->current_capture_device->device)
    {
        cout << "Current Capture Device: " << respObj->current_capture_device->device << endl << endl;
		// GKy 091214 need set to config?. but..mu..seems still need some switch case..
    }

    if (respObj->effective_capture_device && respObj->effective_capture_device->device)
    {
        cout << "Effective Capture Device: " << respObj->effective_capture_device->device << endl << endl;
    }

	////////////////////////////
	// GKy 091214, GKy 091216 cont.
	stateMgr->txListDevs();
}

void ResponseManager::resp_GetSessionFonts(vx_resp_account_get_session_fonts_t* respObj)
{
    if (debuglevel >= 2 && respObj->session_font_count > 0)
    {
        cout << endl << "Session Fonts:" <<endl;
        for (int i=0;i<respObj->session_font_count;i++)
        {
            vx_voice_font_t* vf = (vx_voice_font_t*)respObj->session_fonts[i];
            cout << "ID: " << vf->id << "   Type: " << vf->type << "   Name: " << vf->name << endl;
        }
        cout << endl;
    }
}

void ResponseManager::resp_GetTemplateFonts(vx_resp_account_get_template_fonts_t* respObj)
{
    if (debuglevel >= 2 && respObj->template_font_count > 0)
    {
        cout << endl << "Template Fonts:" <<endl;
        for (int i=0;i<respObj->template_font_count;i++)
        {
            vx_voice_font_t* vf = (vx_voice_font_t*)respObj->template_fonts[i];
            cout << "ID: " << vf->id << "   Type: " << vf->type << "   Name: " << vf->name << endl;
        }
        cout << endl;
    }
}

void ResponseManager::resp_GetVadProperties(vx_resp_aux_get_vad_properties_t* respObj)
{
    if (debuglevel >= 2)
    {
        cout << endl << "Vad properties:" <<endl;
        cout << "VadHangover(s): "<< respObj->vad_hangover << " (Valid values are 1 - 60 s)" <<endl;
        cout << "VadSensitivity: "<< respObj->vad_sensitivity <<" (Valid values are 0 - 100)"<< endl;
        cout << endl;
    }
}

/*void ResponseManager::resp_AddUserFont(vx_resp_account_add_user_font_t* respObj)
{
    if (debuglevel >= 2)
        cout << endl << "User Font ID: " << respObj->user_font_id << endl << endl;
}*/

void ResponseManager::resp_NetworkTest(vx_resp_aux_connectivity_info_t* respObj)
{
    if (respObj->count > 0 && respObj->test_results)
    {
        cout << endl<< endl;
        for (int i = 0; i < respObj->count; ++i)
        {
            vx_connectivity_test_result_t* r = respObj->test_results[i];
               cout << "Test type: ";

            switch (r->test_type)
            {
                case ND_TEST_LOCATE_INTERFACE:
                    cout << "ND_TEST_LOCATE_INTERFACE"; break;
                case ND_TEST_PING_GATEWAY:
                    cout << "ND_TEST_PING_GATEWAY"; break;
                case ND_TEST_DNS:
                    cout << "ND_TEST_DNS"; break;
                case ND_TEST_STUN:
                    cout << "ND_TEST_STUN"; break;
                case ND_TEST_ECHO:
                    cout << "ND_TEST_ECHO"; break;
                case ND_TEST_ECHO_SIP_FIRST_PORT:
                    cout << "ND_TEST_ECHO_SIP_FIRST_PORT"; break;
                case ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_REQUEST:
                    cout << "ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_REQUEST"; break;
                case ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_RESPONSE:
                    cout << "ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_RESPONSE"; break;
                case ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_REQUEST:
                    cout << "ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_REQUEST"; break;
                case ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_RESPONSE:
                    cout << "ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_RESPONSE"; break;
                case ND_TEST_ECHO_SIP_SECOND_PORT:
                    cout << "ND_TEST_ECHO_SIP_SECOND_PORT"; break;
                case ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_REQUEST:
                    cout << "ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_REQUEST"; break;
                case ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_RESPONSE:
                    cout << "ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_RESPONSE"; break;
                case ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_REQUEST:
                    cout << "ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_REQUEST"; break;
                case ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_RESPONSE:
                    cout << "ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_RESPONSE"; break;
                case ND_TEST_ECHO_MEDIA:
                    cout << "ND_TEST_ECHO_MEDIA"; break;
                case ND_TEST_ECHO_MEDIA_LARGE_PACKET:
                    cout << "ND_TEST_ECHO_MEDIA_LARGE_PACKET"; break;
            }
            cout << endl;
            cout << "    Error Code: ";
            switch (r->test_error_code)
            {
                case ND_E_NO_ERROR:
                    cout << "ND_E_NO_ERROR"; break;
                case ND_E_TEST_NOT_RUN:
                    cout << "ND_E_TEST_NOT_RUN"; break;
                case ND_E_NO_INTERFACE:
                    cout << "ND_E_NO_INTERFACE"; break;
                case ND_E_NO_INTERFACE_WITH_GATEWAY:
                    cout << "ND_E_NO_INTERFACE_WITH_GATEWAY"; break;
                case ND_E_NO_INTERFACE_WITH_ROUTE:
                    cout << "ND_E_NO_INTERFACE_WITH_ROUTE"; break;
                case ND_E_TIMEOUT:
                    cout << "ND_E_TIMEOUT"; break;
                case ND_E_CANT_ICMP:
                    cout << "ND_E_CANT_ICMP"; break;
                case ND_E_CANT_RESOLVE_VIVOX_UDP_SERVER:
                    cout << "ND_E_CANT_RESOLVE_VIVOX_UDP_SERVER"; break;
                case ND_E_CANT_RESOLVE_ROOT_DNS_SERVER:
                    cout << "ND_E_CANT_RESOLVE_ROOT_DNS_SERVER"; break;
                case ND_E_CANT_CONVERT_LOCAL_IP_ADDRESS:
                    cout << "ND_E_CANT_CONVERT_LOCAL_IP_ADDRESS"; break;
                case ND_E_CANT_CONTACT_STUN_SERVER_ON_UDP_PORT_3478:
                    cout << "ND_E_CANT_CONTACT_STUN_SERVER_ON_UDP_PORT_3478"; break;
                case ND_E_CANT_CREATE_TCP_SOCKET:
                    cout << "ND_E_CANT_CREATE_TCP_SOCKET"; break;
                case ND_E_CANT_LOAD_ICMP_LIBRARY:
                    cout << "ND_E_CANT_LOAD_ICMP_LIBRARY"; break;
                case ND_E_CANT_FIND_SENDECHO2_PROCADDR:
                    cout << "ND_E_CANT_FIND_SENDECHO2_PROCADDR"; break;
                case ND_E_CANT_CONNECT_TO_ECHO_SERVER:
                    cout << "ND_E_CANT_CONNECT_TO_ECHO_SERVER"; break;
                case ND_E_ECHO_SERVER_LOGIN_SEND_FAILED:
                    cout << "ND_E_ECHO_SERVER_LOGIN_SEND_FAILED"; break;
                case ND_E_ECHO_SERVER_LOGIN_RECV_FAILED:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RECV_FAILED"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_STATUS:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_STATUS"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_FAILED_STATUS:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_FAILED_STATUS"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SESSIONID:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SESSIONID"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SIPPORT:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SIPPORT"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTP:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTP"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTCP:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTCP"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTP:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTP"; break;
                case ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTCP:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTCP"; break;
                case ND_E_ECHO_SERVER_CANT_ALLOCATE_SIP_SOCKET:
                    cout << "ND_E_ECHO_SERVER_CANT_ALLOCATE_SIP_SOCKET"; break;
                case ND_E_ECHO_SERVER_CANT_ALLOCATE_MEDIA_SOCKET:
                    cout << "ND_E_ECHO_SERVER_CANT_ALLOCATE_MEDIA_SOCKET"; break;
                case ND_E_ECHO_SERVER_SIP_UDP_SEND_FAILED:
                    cout << "ND_E_ECHO_SERVER_SIP_UDP_SEND_FAILED"; break;
                case ND_E_ECHO_SERVER_SIP_UDP_RECV_FAILED:
                    cout << "ND_E_ECHO_SERVER_SIP_UDP_RECV_FAILED"; break;
                case ND_E_ECHO_SERVER_SIP_TCP_SEND_FAILED:
                    cout << "ND_E_ECHO_SERVER_SIP_TCP_SEND_FAILED"; break;
                case ND_E_ECHO_SERVER_SIP_TCP_RECV_FAILED:
                    cout << "ND_E_ECHO_SERVER_SIP_TCP_RECV_FAILED"; break;
                case ND_E_ECHO_SERVER_SIP_NO_UDP_OR_TCP:
                    cout << "ND_E_ECHO_SERVER_SIP_NO_UDP_OR_TCP"; break;
                case ND_E_ECHO_SERVER_SIP_NO_UDP:
                    cout << "ND_E_ECHO_SERVER_SIP_NO_UDP"; break;
                case ND_E_ECHO_SERVER_SIP_NO_TCP:
                    cout << "ND_E_ECHO_SERVER_SIP_NO_TCP"; break;
                case ND_E_ECHO_SERVER_SIP_MALFORMED_TCP_PACKET:
                    cout << "ND_E_ECHO_SERVER_SIP_MALFORMED_TCP_PACKET"; break;
                case ND_E_ECHO_SERVER_SIP_UDP_DIFFERENT_LENGTH:
                    cout << "ND_E_ECHO_SERVER_SIP_UDP_DIFFERENT_LENGTH"; break;
                case ND_E_ECHO_SERVER_SIP_UDP_DATA_DIFFERENT:
                    cout << "ND_E_ECHO_SERVER_SIP_UDP_DATA_DIFFERENT"; break;
                case ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT:
                    cout << "ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT"; break;
                case ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT_SIZE:
                    cout << "ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT_SIZE"; break;
                case ND_E_ECHO_SERVER_LOGIN_RECV_FAILED_TIMEOUT:
                    cout << "ND_E_ECHO_SERVER_LOGIN_RECV_FAILED_TIMEOUT"; break;
                case ND_E_ECHO_SERVER_TCP_SET_ASYNC_FAILED:
                    cout << "ND_E_ECHO_SERVER_TCP_SET_ASYNC_FAILED"; break;
                case ND_E_ECHO_SERVER_UDP_SET_ASYNC_FAILED:
                    cout << "ND_E_ECHO_SERVER_UDP_SET_ASYNC_FAILED"; break;
                case ND_E_ECHO_SERVER_CANT_RESOLVE_NAME:
                    cout << "ND_E_ECHO_SERVER_CANT_RESOLVE_NAME"; break;
            }
            cout << endl;
            cout << "    Additional Info: ";
            cout << r->test_additional_info;
            cout << endl<< endl;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// Events ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ResponseManager::evt_Generic(vx_evt_base_t* evtObj)
{
}

void ResponseManager::evt_AccountLoginStateChange(vx_evt_account_login_state_change_t* evtObj)
{
    int state = evtObj->state;

    switch (state)
    {
    case login_state_logged_in:
        stateMgr->SetStateAccountLoggedIn(evtObj->account_handle);
        if (debuglevel >= 2)
        {
            cout << "Account Handle: " << evtObj->account_handle << endl << endl;
        }

		// GKy 091217
		stateMgr->txLoginOK();

        break;
    case login_state_logged_out:
        stateMgr->SetStateAccountLoggedOut();
        break;
    }
}

void ResponseManager::evt_SessionGroupAdded(vx_evt_sessiongroup_added_t* evtObj)
{
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    cout << "SessionGroup " << sessionGroupHandle << " Added." << std::endl;
    stateMgr->AddSessionGroup(sessionGroupHandle);

	////////////////////////////////////////////

	// GKy 091211
	stateMgr->txSessionGroupAdded();



}

void ResponseManager::evt_SessionGroupRemoved(vx_evt_sessiongroup_removed_t* evtObj)
{
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    cout << "SessionGroup " << sessionGroupHandle << " Terminated." << std::endl;
    stateMgr->RemoveSessionGroup(sessionGroupHandle);
}

void ResponseManager::evt_SessionGroupUpdated(vx_evt_sessiongroup_updated_t* evtObj)
{
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    cout << "SessionGroup " << sessionGroupHandle << " Updated." << std::endl;

	// GKy 091211
	//stateMgr->txSessionGroupUpdated();
	//
}

void ResponseManager::evt_SessionAdded(vx_evt_session_added_t* evtObj)
{
    std::string sessionHandle(evtObj->session_handle);
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
	std::string uri(evtObj->uri); // GKy 

	std::stringstream ossOut; 

#if VVX_DEBUG /////////////////////////////////////////////////////////////
    cout << "Session " << sessionHandle << " Added.  Incoming = " << evtObj->incoming << std::endl;
    cout << "  Displayname= " << ( evtObj->displayname != NULL ? evtObj->displayname : "none")<< endl ;
	// So..displayname really may as NULL!? ..
    strOut << "Session " << sessionHandle << " Added.  Incoming = " << evtObj->incoming << std::endl;
    strOut << "  Displayname= " << ( evtObj->displayname != NULL ? evtObj->displayname : "NULL")<< endl ;
#endif /////////////////////////////////////////////////////////////////////

    stateMgr->AddSession(sessionGroupHandle, sessionHandle, uri, evtObj->incoming); //+++

	VivoxClient::GetInstance()->FlushLog(ossOut.str().c_str()); // #test #LOG


	//// Origin Code, indeed strange
 //   std::string sessionHandle(evtObj->session_handle);
 //   std::string sessionGroupHandle(evtObj->sessiongroup_handle);
 //   cout << "Session " << sessionHandle << " Added.  Incoming = " << evtObj->incoming << std::endl;
 //   cout << "  Displayname= " << ( evtObj->displayname != NULL ? evtObj->displayname : "none")<< endl ;
 //   string uri(evtObj->uri);
 //   stateMgr->AddSession(sessionGroupHandle, sessionHandle, uri, evtObj->incoming);
	////
}

void ResponseManager::evt_SessionRemoved(vx_evt_session_removed_t* evtObj)
{
    //std::string sessionHandle(evtObj->session_handle);
    //std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    //cout << "Session " << sessionHandle << " Terminated." << std::endl;
    //stateMgr->RemoveSession(sessionGroupHandle, sessionHandle);


    std::string sessionHandle(evtObj->session_handle);
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);

	std::string sURI(evtObj->uri);

	std::ostringstream ossOut; 

#if VVX_DEBUG /////////////////////////////////////////////////////////////
    cout << "Session " << sessionHandle << " Terminated." << std::endl;
    strOut << "Session " << sessionHandle << " Terminated. uri = " << sURI.c_str() << std::endl;
#endif ////////////////////////////////////////////////////////////////////


    //strOut << cout;

    stateMgr->RemoveSession(sessionGroupHandle, sessionHandle);

	stateMgr->txSessionRemoveOK(); // GKy 091217

	//VivoxClient::flushLog(strOut); // #test #LOG
	VivoxClient::GetInstance()->FlushLog(ossOut.str().c_str()); // #test #LOG

}

void ResponseManager::evt_SessionUpdated(vx_evt_session_updated_t* evtObj)
{
    std::string sessionHandle(evtObj->session_handle);
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    cout << "Session " << sessionHandle << " Updated." << std::endl;
    stateMgr->UpdateSession(sessionGroupHandle,sessionHandle,evtObj->transmit_enabled, evtObj->is_focused, evtObj->is_muted, evtObj->is_text_muted, evtObj->session_font_id, evtObj->volume);
}

void ResponseManager::evt_MediaStreamUpdated(vx_evt_media_stream_updated_t* evtObj)
{
    std::string sessionHandle(evtObj->session_handle);
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
	//std::string sState = toString(evtObj->state);

    //cout << "Media Stream Updated for Session " << sessionHandle << ", State = " << sState << std::endl;
    cout << "Media Stream Updated for Session " << sessionHandle << ", State = " << toString(evtObj->state) << std::endl;
    stateMgr->UpdateMediaStreamState(sessionGroupHandle,sessionHandle,evtObj->state);

	//////////////////////////////////////////////////////////////////////////
	// GKy 091215 add handle.

	
	//evtObj->session_handle //X?
	stateMgr->txSessionMediaUpdate(); // 




    switch(evtObj->state) {
        case session_media_none: 

        case session_media_disconnected: // GKy 100106 need handle some case..Like Channel Full
			stateMgr->txSessionDisconnected(); // 
			break;

        case session_media_connected:
			// GKy 091215 need handle here for ensure Session is connected OK:
			stateMgr->txSessionConnected(); // 
			break;

        case session_media_connecting:
        case session_media_ringing:
        case session_media_hold:
        case session_media_refer:
        case session_media_disconnecting: 
        default:
			break;
    };

}

void ResponseManager::evt_TextStreamUpdated(vx_evt_text_stream_updated_t* evtObj)
{
    std::string sessionHandle(evtObj->session_handle);
    std::string sessionGroupHandle(evtObj->sessiongroup_handle);
    cout << "Text Stream Updated for Session " << sessionHandle << ", State = " << toString(evtObj->state) << std::endl;
    stateMgr->UpdateTextStreamState(sessionGroupHandle,sessionHandle,evtObj->state);
}

void ResponseManager::evt_MediaCompleted(vx_evt_media_completion_t* evtObj)
{
    cout << "Media Completed " << toString(evtObj->completion_type) << endl;
}

void ResponseManager::evt_Message(vx_evt_message_t* evtObj)
{
    cout << endl << endl << "IM received from " << evtObj->participant_uri << " on session " << evtObj->session_handle << ": " << endl << evtObj->message_body << "" << endl << endl;
    cout << endl << "From displayname : " << (evtObj->participant_displayname != NULL ? evtObj->participant_displayname : "none") << endl ;
}

void ResponseManager::evt_NetworkMessage(vx_evt_network_message_t*evtObj)
{
    cout << endl << endl << "Offline IM received from " << evtObj->sender_uri << " " << evtObj->sender_display_name << ": " << endl;
    cout << "Content-Type: " << evtObj->content_type << endl;
    cout << "Content: " << evtObj->content << endl << endl;
    cout << "Sender Display Name : " << (evtObj->sender_display_name != NULL ? evtObj->sender_display_name : "none") << endl ;
}


void ResponseManager::evt_BuddyPresenceChange(vx_evt_buddy_presence_t* evtObj)
{
    cout << std::endl << "Buddy Presence Change: uri=" << evtObj->buddy_uri << ", state=" << toString(evtObj->presence) << ", note='" << 
        evtObj->custom_message << "'" << std::endl;
    cout << "  Displayname= " << ( evtObj->displayname != NULL ? evtObj->displayname : "none")<< endl ;
}

std::string safestring(const char *s)
{
    if(s == NULL) return "";
    return s;
}

void ResponseManager::evt_BuddyChanged(vx_evt_buddy_changed_t *evtObj)
{
    if(evtObj->change_type == change_type_set) {
        cout << std::endl << "Buddy Set: uri=" << evtObj->buddy_uri << ", displayName=" << safestring(evtObj->display_name) << endl;
    } else if(evtObj->change_type == change_type_delete) {
        cout << std::endl << "Buddy Deleted: uri=" << evtObj->buddy_uri << endl;
    }
}

void ResponseManager::evt_BuddyGroupChanged(vx_evt_buddy_group_changed_t *evtObj)
{
    if(evtObj->change_type == change_type_set) {
        cout << std::endl << "Buddy Group Set: id=" << evtObj->group_id << ", displayName=" << safestring(evtObj->group_name) << endl;
    } else if(evtObj->change_type == change_type_delete) {
        cout << std::endl << "Buddy Group Deleted: id=" << evtObj->group_id << endl;
    }
}

void ResponseManager::evt_Subscription(vx_evt_subscription_t *evtObj)
{
    cout << std::endl << "Subscription Event: Account Handle=" << safestring(evtObj->account_handle) 
        << ", URI=" << safestring(evtObj->buddy_uri) << ", Subscription Handle=" << safestring(evtObj->subscription_handle) << endl;
    cout << endl << "From displayname : " << (evtObj->displayname != NULL ? evtObj->displayname : "none") << endl ;

}

void ResponseManager::evt_AuxAudioProperties(vx_evt_aux_audio_properties_t* evtObj)
{
	VivoxClient::GetInstance()->GetPartiStateRef().energy = evtObj->mic_energy;
}

// TODO: 或許需要將這些東西移出 Response Manager ... by slime
void ResponseManager::evt_ParticipantUpdated(vx_evt_participant_updated_t* evtObj)
{
	std::string str_temp;

	int UpdateDataOnly = 1; // 0:false(also send World Evt) 1:true

	//std::map<std::string,ParticipantState>::iterator  it;
	std::ostringstream ossOut; // #test for output deBug.

	//# test ############################################################################
#if VVX_DEBUG /////////////////////////////////////////////////////////////
	strOut << endl;
	strOut << "\n---evt_ParticipantUpdated---";
	strOut << "\n  evtObj->sg_handle=" << evtObj->sessiongroup_handle << "+";
	strOut << "\n  evtObj->ss_handle=" << evtObj->session_handle << "+";

	strOut << "\n    evtObj->participant_uri=" << evtObj->participant_uri << "+";
	strOut << "\n    evtObj->is_speaking=" << evtObj->is_speaking << "+";
	strOut << "\n    evtObj->type=" << evtObj->type << "+";
	strOut << "\n    evtObj->energy=" << evtObj->energy << "+";
	strOut << "\n    evtObj->volume=" << evtObj->volume << "+";

	strOut << "\n    evtObj->is_muted_for_me=" << evtObj->is_muted_for_me << "+"; // GKy 100106
#endif /////////////////////////////////////////////////////////////////////////////////////

	//// GKy 091222 need get Session Obj, or try more simple way?..try simpler 1st
	//// GKy 091222 due to now into Test still not set displayName, need distinguish as two case? 
	////     091222 try do in add Evt;
	//// GKy 091224 Fix ////////////////////////////////////////////
	if (evtObj->participant_uri != NULL)
    {
		// 0. Update to general data(m_mParts)
		////// GKy 091224 Get Partner Obj
		ParticipantState p;
		p = VivoxClient::GetInstance()->GetPartiGroupRef().GetStateByUri( (const char*) evtObj->participant_uri );

		if (p.uri != "")
        {
		    // partner found
			if (VivoxClient::GetInstance()->GetPartiStateRef().uri == evtObj->participant_uri)
            {
			    // 1. Update self.energy

#if VVX_DEBUG /////////////////////////////////////////////////////////////
				strOut << "\n  sTalk energy=" << evtObj->energy;
#endif ////////////////////////////////////////////////////////////////////

				VivoxClient::GetInstance()->GetPartiStateRef().energy = evtObj->energy;   //+++ 091222 try for TEST and NOR case

				// GKy 100106 if self is_speaking change, then send Evt.
				if (VivoxClient::GetInstance()->GetPartiStateRef().speaking != evtObj->is_speaking)
                {
					VivoxClient::GetInstance()->GetPartiStateRef().speaking = evtObj->is_speaking;
					UpdateDataOnly = 0;
				}

				// GKy 100115 try here.............
				switch (VivoxClient::GetInstance()->GetInputMode())
                {
					case VVX_INPUT_MODE_DETECT:
						//VivoxClient::GetInstance()->SetInputSensSwitch(evtObj->energy); // marked by slime
						break;

					case VVX_INPUT_MODE_PTT:
					default:
						break;

				}//switch
			}
            else
            {
				// GKy 091222 catch Last talker ///////////////////////////////////////
				// GKy 100104 as Lua Task? mu.. BUT..if same partner cont?..OLD seems still keep.
				if (evtObj->is_speaking)
                {

#if VVX_DEBUG /////////////////////////////////////////////////////////////
					strOut << "\n  P is speaking=" << evtObj->energy;
					strOut << "  evt:disName=" << p.m_str_display_name.c_str();
					strOut << "  VC::m_sPartDisNameLast=" << VivoxClient::m_iPartnerDBidLast;
#endif ////////////////////////////////////////////////////////////////////

					// if different ppl speaking 
					if (VivoxClient::GetInstance()->GetPartnerDBidLast() != atoi(p.display_name.c_str()))
					{
						VivoxClient::GetInstance()->SetPartnerDBidLast( atoi(p.display_name.c_str()) );

						//strOut << VivoxClient::messageStoreEvt( VVX_WORLD_EVT_PART_UPDATE, evtObj->participant_uri ).c_str();
						UpdateDataOnly = 0;
					}
                    else
                    {
						// Sure is not me and is the same partner chat
					}
				}
                else
                {
                    // Other Partner Not Speaking+++++++++++++++++++++++++++++++++++
					// Need Send WorldEvt to Cancel UI LastDisName
					// 1+ GKy 100104 merge as one Evt.
					//strOut << VivoxClient::messageStoreEvt( VVX_WORLD_EVT_PART_SILENT, evtObj->participant_uri ).c_str();
					UpdateDataOnly = 0;

					///////////////////////////////////////

					// 2. kS Evt +++++++++++++++++++
					// Same Last partner who is in talking
					if (VivoxClient::GetInstance()->GetPartnerDBidLast() == atoi(p.display_name.c_str()))
					{
						// Reset
						VivoxClient::GetInstance()->SetPartnerDBidLast(0);
					}
				}
			}

			///////////////////////////////////////////////////////////////////////

			/*///////// GKy 100104 Update to data
			p.energy      = evtObj->energy;
			p.is_speaking = evtObj->is_speaking;
			VivoxClient::m_oParts.partSet( p );
			/*///////// GKy 100105 move to msgDump parts. BTW, if so, each Evt need keep..mu..

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// Format: "EVT URI energy is_speaking UpdateDataOnly is_muted_for_me"

			std::ostringstream oss;
			oss << " " << evtObj->participant_uri
                << " " << evtObj->energy
                << " " << evtObj->is_speaking
                << " " << UpdateDataOnly
                << " " << evtObj->is_muted_for_me;

			// Just found..if is_speaking also as a para, Evt para in here seems not so necessary..?
			// BUT seems still with Evt para is better.
			if (evtObj->is_speaking)
            {
				ossOut << VivoxClient::GetInstance()->AppendMessageEvent( VVX_WORLD_EVT_PART_UPDATE, oss.str().c_str() ).c_str();
			}
            else
            {
				ossOut << VivoxClient::GetInstance()->AppendMessageEvent( VVX_WORLD_EVT_PART_SILENT, oss.str().c_str() ).c_str();
			}
		}
	}
    else
    {
	}

	//////////////////////////////////////////////////////////////////////////

	if (VivoxClient::GetInstance()->GetOutputDebugMessage() >= 2)
    {
		VivoxClient::GetInstance()->AppendMessage(ossOut.str().c_str()); //#test
    }

	//// #test #LOG
	VivoxClient::GetInstance()->FlushLog(ossOut.str().c_str());

 ///////////////////////////////////////////////////////////
 //s_p_iolock->Release();
}

void ResponseManager::evt_ParticipantAdded(vx_evt_participant_added_t *evtObj)
{
	// seems have problem..about deBugOutput
	std::ostringstream oss;
	std::string strT;

#if VVX_DEBUG /////////////////////////////////////////////////////////////
	// GKy 091221 Add
    strOut << endl;

	strOut << "---evt_ParticipantAdded---++++++++++++++++++++";

	strOut << "\n  evtObj->sessiongroup_handle=" << evtObj->sessiongroup_handle;
	strOut << "\n  evtObj->session_handle=" << evtObj->session_handle;

	//////////////// GKy 091222 try simpler way ///////////////////

			strOut << "\n  Add partner: uri = " << (const char*)evtObj->participant_uri << "+";

			//strT = evtObj->displayname; // Seems OK for receive NULL? No..

			// May Get NULL
			if( NULL == evtObj->displayname ){ //X, deprecated!!?? AND CAUSE CRASH
				strOut << "\n   evtObj->displayname = NULL "; 
			}else{
				strOut << "\n   evtObj->displayname = " << (const char*)evtObj->displayname << "+"; 
			}//if

			if( NULL == evtObj->display_name ){ //X, deprecated???? BUT have value.
				strOut << "\n   evtObj->display_name = NULL";
			}else{
				strOut << "\n   evtObj->display_name = " << evtObj->display_name; 
			}//if
#endif //////////////////////////////////////////////////////////////////////////////

    ParticipantState partS;
    partS.uri = evtObj->participant_uri;
    partS.display_name = evtObj->display_name;

    VivoxClient::GetInstance()->GetPartiGroupRef().InsertState(partS);
    // GKy 100106 also move into msgDump? BUT..here need more para..

    oss << VivoxClient::GetInstance()->AppendMessageEvent( VVX_WORLD_EVT_CH_JOIN_PART, evtObj->participant_uri).c_str();

    // GKy 091222 Need Setup self data +++++++++++++++++++++++++++++
    //std::string sDBid = itoa(g_pGameMain->GetDBID(),10); // try get Self DBid
    int iDBid = g_pGameMain->GetDBID(); // try get Self DBid

#if VVX_DEBUG /////////////////////////////////////////////////////////////
				strOut << "\n  Get DBid = " << iDBid;
#endif //////////////////////////////////////////////////////////////////

    //if( iDBid == atoi((const char*)evtObj->displayname) ){
    if (VivoxClient::GetInstance()->IsInTest() ||
        iDBid == atoi((const char*)evtObj->display_name))
    {
#if VVX_DEBUG /////////////////////////////////////////////////////////////
				strOut << "; Get Self DBid = " << iDBid;
#endif  ///////////////////////////////////////////////////////////////////
        VivoxClient::GetInstance()->GetPartiStateRef().uri = evtObj->participant_uri;
        VivoxClient::GetInstance()->GetPartiStateRef().display_name = evtObj->display_name;
    }
#if VVX_DEBUG /////////////////////////////////////////////////////////////
	if (VivoxClient::GetOutputDebugMessage() >= 1)
    {
		VivoxClient::AppendMessage( strOut.str().c_str() );
    }
	VivoxClient::FlushLog(strOut.str().c_str()); //#test #LOG
#endif /////////////////////////////////////////////////////////////////////
}

//--------------------------------------------------------------------------------
void ResponseManager::evt_ParticipantRemoved(vx_evt_participant_removed_t *evtObj)
{
	std::ostringstream oss;
	std::string strT;

	VxSession*		pVxS  = NULL;
	VxSessionGroup* pVxSG = NULL;

#if VVX_DEBUG /////////////////////////////////////////////////////////////
    strOut << endl;

	strOut << "---evt_ParticipantRemoved--------------------------------";

	strOut << "\n  evtObj->sessiongroup_handle=" << evtObj->sessiongroup_handle;
	strOut << "\n  evtObj->session_handle=" << evtObj->session_handle;

	/////////////////////////////////

	strOut << "\n     try remove=" << evtObj->participant_uri;
#endif ///////////////////////////////////////////////////////////////////////////

	// need done after below Evt.
	oss << VivoxClient::GetInstance()->AppendMessageEvent(VVX_WORLD_EVT_CH_EXIT_PART, evtObj->participant_uri).c_str();

#if VVX_DEBUG /////////////////////////////////////////////////////////////
	if (VivoxClient::GetOutputDebugMessage() >= 1)
    {
		VivoxClient::AppendMessage( strOut.str().c_str() );
    }
	VivoxClient::FlushLog(strOut.str().c_str()); //#test #LOG
#endif /////////////////////////////////////////////////////////////////////
}

void ResponseManager::Stop(bool waitForShutdown)
{
    this->stopOnShutdownResponse = waitForShutdown;
    this->stopNow = !waitForShutdown;
}

bool ResponseManager::IsStopped() const
{
    return stopNow;
}

void ResponseManager::resp_ListAutoAcceptRules(vx_resp_account_list_auto_accept_rules_t *respObj)
{
    cout << endl;
    if(respObj->rule_count == 0) {
        cout << "There are no autoaccept rules for this account." << endl;
    } else {
        cout << setw(40) << left << "Mask" << " " << "Auto Add As Buddy" << endl;
        for(int i = 0;i<respObj->rule_count;++i) {
            cout << setw(40) << left << respObj->auto_accept_rules[i]->auto_accept_mask << " " << (respObj->auto_accept_rules[i]->auto_add_as_buddy ? "true" : "false") << endl;
        }
    }
    cout << endl;
}

void ResponseManager::resp_ListBlockRules(vx_resp_account_list_block_rules_t *respObj)
{
    cout << endl;
    if(respObj->rule_count == 0) {
        cout << "There are no block rules for this account." << endl;
    } else {
        cout << setw(40) << left << "Mask" << " " << "Block Presence Only" << endl;
        for(int i = 0;i<respObj->rule_count;++i) {
            cout << setw(40) << left << respObj->block_rules[i]->block_mask << " " << (respObj->block_rules[i]->presence_only ? "true" : "false") << endl;
        }
    }
    cout << endl;
}

void ResponseManager::resp_ChannelGetParticipants(vx_resp_account_channel_get_participants *respObj)
{
    cout << endl;
    if(respObj->participant_count == 0) {
        cout << "There are no participants in this channel." << endl;
    } else {
        cout << setw(4) << "idx" << setw(30) << "uri" << setw(20) << "username" << setw(20) << "displayname" << setw(3) << "m" << setw(3) << "o" << setw(3) << "am" << setw(3) << "tm" << setw(10) << "accountid" << endl;
        for(int i=respObj->from;i<(respObj->participant_count+respObj->from);++i) {
            vx_participant *p = respObj->participants[i];
            cout << setw(4) << i << setw(30) << p->uri << setw(20) << p->username << setw(20) << p->display_name << setw(3) << p->is_moderator << setw(3) << p->is_owner 
                << setw(3) << p->is_moderator_muted << setw(3) << p->is_moderator_text_muted << setw(10) << p->account_id << endl;
        }
    }
}

void ResponseManager::resp_AudioInfo(vx_resp_connector_get_local_audio_info_t *respObj)
{
    cout << endl;
    cout << "speaker_volume=" << respObj->speaker_volume << endl;
    cout << "is_speaker_muted=" << respObj->is_speaker_muted << endl;
    cout << "mic_volume=" << respObj->mic_volume << endl;
    cout << "is_mic_muted=" << respObj->is_mic_muted << endl;
    cout << endl;
}

void ResponseManager::resp_State(vx_resp_aux_diagnostic_state_dump_t *respObj)
{
	std::string strT;

	VxSession*		pVxS  = NULL; // GKy 091209 add
	VxSessionGroup* pVxSG = NULL;

	// GKy 091217 Add
    cout << endl;
	cout << " Vvx::case=" << VivoxClient::GetInstance()->GetCaseEnum();
	cout << " Vvx::state=" << VivoxClient::GetInstance()->GetVivoxState() << endl;

	cout << " VvxCnt::m_sVivoxChannelName="    << VivoxClient::GetInstance()->ChannelNameString() << endl;
	cout << " VvxCnt::m_sVivoxChannelNamePre=" << VivoxClient::GetInstance()->ChannelNamePreviousString() << endl;
	cout << " VvxCnt::m_sVivoxChannelURI="  << VivoxClient::GetInstance()->ChannelURIString() << endl;

	cout << " VvxCnt::m_sAcc=" << VivoxClient::GetInstance()->GetAccount().c_str() << "";
	cout << " VvxCnt::m_sPwd="  << VivoxClient::GetInstance()->GetPassword().c_str() << endl;

	cout << " VvxCnt::m_oSelf.uri="  << VivoxClient::GetInstance()->GetPartiStateRef().uri << endl;
	cout << " VvxCnt::m_oSelf.display_name="  << VivoxClient::GetInstance()->GetPartiStateRef().display_name;

	//cout << " VvxCnt::m_mParts.size="  << VivoxClient::m_mParts.size();
	cout << " VvxCnt::m_oParts.size="  << VivoxClient::GetInstance()->GetPartiGroupRef().GetSize();
	cout << " VvxCnt::LoginModeGet()="  << VivoxClient::GetInstance()->GetLoginMode();

	////////////////////////////////////////////////////////////////////

    cout << endl;

    cout << "Current SDK Internal State" << endl;

    if (respObj->current_render_device && respObj->current_render_device->device)
    {
        cout << "Current Render Device: " << respObj->current_render_device->device << endl << endl;
    }
    if (respObj->effective_render_device && respObj->effective_render_device->device)
    {
        cout << "Effective Render Device: " << respObj->effective_render_device->device << endl << endl;
    }

    if (respObj->current_capture_device && respObj->current_capture_device->device) {
        cout << "Current Capture Device: " << respObj->current_capture_device->device << endl << endl;
    }
    if (respObj->effective_capture_device && respObj->effective_capture_device->device) {
        cout << "Effective Capture Device: " << respObj->effective_capture_device->device << endl << endl;
    }

    if(respObj->state_connector_count == 0) {
        cout << "The SDK has no internal connectors created." << endl;
        return;
    }

    for (int i = 0; i < respObj->state_connector_count; ++i)
    {
        vx_state_connector_t* c = respObj->state_connectors[i];
        cout << "connector[" << i << "].connector_handle=" << c->connector_handle << endl;
        for (int j = 0; j < c->state_accounts_count; ++j)
        {
            vx_state_account* a = c->state_accounts[j];
            cout << " " << "account[" << j << "].account_handle=" << a->account_handle << endl;
            cout << " " << "account[" << j << "].account_uri=" << a->account_uri << endl;

			VivoxClient::GetInstance()->GetPartiStateRef().uri = a->account_uri; // GKy 091215 Set Self URI

            for (int k = 0; k < a->state_sessiongroups_count; ++k)
            {
                vx_state_sessiongroup* sg = a->state_sessiongroups[k];
                cout << "  " << "sessiongroup[" << k << "].sessiongroup_handle=" << sg->sessiongroup_handle << endl;

				// GKy 091209
				strT = sg->sessiongroup_handle;
				pVxSG = stateMgr->GetSessionGroup(strT);

                for (int m = 0; m < sg->state_sessions_count; ++m)
                {
                    vx_state_session* s = sg->state_sessions[m];

					// GKy 091209
					strT = s->session_handle;
					pVxS = pVxSG->GetSession(strT);

                    cout << "   " << "session[" << m << "].session_handle=" << s->session_handle << endl;
                    cout << "   " << "session[" << m << "].uri=" << s->uri << endl;
                    cout << "   " << "session[" << m << "].has_audio=" << s->has_audio << endl;
                    cout << "   " << "session[" << m << "].has_text=" << s->has_text << endl;
                    cout << "   " << "session[" << m << "].is_audio_muted_for_me=" << s->is_audio_muted_for_me << endl;
                    cout << "   " << "session[" << m << "].is_connected=" << s->is_connected << endl;
                    cout << "   " << "session[" << m << "].is_focused=" << s->is_focused << endl;
                    cout << "   " << "session[" << m << "].is_incoming=" << s->is_incoming << endl;
                    cout << "   " << "session[" << m << "].is_positional=" << s->is_positional << endl;
                    cout << "   " << "session[" << m << "].is_text_muted_for_me=" << s->is_text_muted_for_me << endl;
                    cout << "   " << "session[" << m << "].is_transmitting=" << s->is_transmitting << endl;
                    cout << "   " << "session[" << m << "].name=" << s->name << endl;
                    cout << "   " << "session[" << m << "].session_font_id=" << s->session_font_id << endl;
                    cout << "   " << "session[" << m << "].volume=" << s->volume << endl;
                    for (int n = 0; n < s->state_participant_count; ++n)
                    {
                        vx_state_participant* p = s->state_participants[n];

                        cout << "    " << "part[" << n << "].uri=" << p->uri << endl;
                        cout << "    " << "part[" << n << "].display_name=" << p->display_name << endl;
                        cout << "    " << "part[" << n << "].energy=" << p->energy << endl;
                        cout << "    " << "part[" << n << "].is_audio_enabled=" << p->is_audio_enabled << endl;
                        cout << "    " << "part[" << n << "].is_audio_moderator_muted=" << p->is_audio_moderator_muted << endl;
                        cout << "    " << "part[" << n << "].is_audio_muted_for_me=" << p->is_audio_muted_for_me << endl;
                        cout << "    " << "part[" << n << "].is_hand_raised=" << p->is_hand_raised << endl;
                        cout << "    " << "part[" << n << "].is_speaking=" << p->is_speaking << endl;
                        cout << "    " << "part[" << n << "].is_text_enabled=" << p->is_text_enabled << endl;
                        cout << "    " << "part[" << n << "].is_text_moderator_muted=" << p->is_text_moderator_muted << endl;
                        cout << "    " << "part[" << n << "].is_text_muted_for_me=" << p->is_text_muted_for_me << endl;
                        cout << "    " << "part[" << n << "].is_typing=" << p->is_typing << endl;
                        cout << "    " << "part[" << n << "].type=" << p->type << endl;
                        cout << "    " << "part[" << n << "].volume=" << p->volume << endl;

						// GKy 091209 try copy a duplication in StateManager for further using.
						ParticipantState partS;
						partS.uri = p->uri;
						partS.speaking = p->is_speaking;
						partS.vx_type = p->type;

						pVxS->InsertState(partS);

						// GKy 091215 try update self energy, etc
						if (partS.uri == VivoxClient::GetInstance()->GetPartiStateRef().uri)
                        {
							VivoxClient::GetInstance()->GetPartiStateRef().energy = p->energy;

							cout << endl;
							cout << "    " << "part[" << n << "].uri=" << p->uri << endl;
							cout << "    " << "part[" << n << "].energy=" << p->energy << endl;
						}
                    }
                }
            }
        }
    }
    cout << endl;
}

void ResponseManager::resp_LocalUserMute(vx_resp_session_set_participant_mute_for_me_t *respObj)
{
	// GKy 100105 : respObj seems carry no important data..
	/*
		Detail see: VxcResponses.h
		typedef struct vx_resp_session_set_participant_mute_for_me {
			vx_resp_base_t base;
		} vx_resp_session_set_participant_mute_for_me_t;
	*/
	// GKy 100105 here main for void Critical Section

	std::ostringstream oss;

#if VVX_DEBUG /////////////////////////////////////////////////////////////
	strOut << "---resp_LocalUserMute---" << endl;
	strOut << "  return code = " << respObj->base.return_code << endl;
	strOut << "  status code = " << respObj->base.status_code << endl;
	//strOut << "  " << endl;
#endif ///////////////////////////////////////////////////////////////////


	//strOut.str().c_str()
	//VivoxClient::flushLog(strOut.str().c_str());
	VivoxClient::GetInstance()->VivoxOutputPrint(NULL, oss.str().c_str() );
}

// GKy 100114
void ResponseManager::resp_GetMicLevel(vx_resp_aux_get_mic_level_t *respObj)
{
    cout << endl;
	cout << "GKy 100114 mic_Level=" << respObj->level << endl;
    cout << endl;
}

void ResponseManager::ProcessMessage(vx_message_base_t *basemsg)
{
    vx_message_type messageType;
    //mutex2.Take();
    messageType = basemsg->type;        //Get the type of the message (Response or Event)
    switch (messageType)
    {
        case msg_event:
        {
            vx_evt_base_t* theEvent;
            theEvent = (vx_evt_base_t*)basemsg;
            vx_event_type eventType;
            eventType = theEvent->type;

            //These are events that we want to perform state mgmt or special reporting for .
            switch (eventType)        //Find the specific Event type, process the Event
            {
                case evt_account_login_state_change:
                    evt_AccountLoginStateChange((vx_evt_account_login_state_change_t*)theEvent);
                    if (quickTestMode)  //for "quicktest" only
                    {
                        vx_evt_account_login_state_change_t* evt = (vx_evt_account_login_state_change_t*)theEvent;
                        m_reqMgr->req_SessionCreate(evt->account_handle, quickTestURI, 0, "", "", 1, 1, 0, 0);
                    }
                    break;
                case evt_media_stream_updated:
                    evt_MediaStreamUpdated((vx_evt_media_stream_updated_t*)theEvent);
                    break;
                case evt_text_stream_updated:
                    evt_TextStreamUpdated((vx_evt_text_stream_updated_t*)theEvent);
                    break;
                case evt_sessiongroup_added:
                    evt_SessionGroupAdded((vx_evt_sessiongroup_added_t*)theEvent);
                    break;
                case evt_sessiongroup_removed:
                    evt_SessionGroupRemoved((vx_evt_sessiongroup_removed_t*)theEvent);
                    break;
                case evt_sessiongroup_updated:
                    evt_SessionGroupUpdated((vx_evt_sessiongroup_updated_t*)theEvent);
                    break;
                case evt_session_added:
                    evt_SessionAdded((vx_evt_session_added_t*)theEvent);
                    break;
                case evt_session_removed:
                    evt_SessionRemoved((vx_evt_session_removed_t*)theEvent);
                    break;
                case evt_session_updated:
                    evt_SessionUpdated((vx_evt_session_updated_t*)theEvent);
                    break;
                case evt_message:
                    evt_Message((vx_evt_message_t*)theEvent);
                    break;
                case evt_network_message:
                    evt_NetworkMessage((vx_evt_network_message_t *)theEvent);
                    break;
                case evt_buddy_presence:
                    evt_BuddyPresenceChange((vx_evt_buddy_presence_t*)theEvent);
                    break;
                case evt_buddy_changed:
                    evt_BuddyChanged((vx_evt_buddy_changed_t *)theEvent);
                    break;
                case evt_buddy_group_changed:
                    evt_BuddyGroupChanged((vx_evt_buddy_group_changed_t *)theEvent);
                    break;
                case evt_subscription:
                    evt_Subscription((vx_evt_subscription_t *)theEvent);
                    break;
                case evt_aux_audio_properties:
                    evt_AuxAudioProperties((vx_evt_aux_audio_properties_t*)theEvent); //+++++++ not work?
                    break;
                case evt_participant_updated: // GKy 091215 try this
					evt_ParticipantUpdated((vx_evt_participant_updated_t*)theEvent);
                    break;
                case evt_participant_added: // GKy 091221 
					evt_ParticipantAdded((vx_evt_participant_added_t*)theEvent);
                    break;
                case evt_participant_removed: // GKy 091221
					evt_ParticipantRemoved((vx_evt_participant_removed_t*)theEvent);
                    break;
                case evt_media_completion:
                    evt_MediaCompleted((vx_evt_media_completion_t*)theEvent);
                    break;
                default:
                    //evt_Generic(theEvent);
                    break;
            }
            if (theEvent->type != evt_aux_audio_properties)     //suppress these beacuse they are too numerous
            {
                WriteEventToFile(theEvent);
            }
            destroy_evt(theEvent);
            break;
        }
        case msg_response:
        {
            vx_resp_base_t* theResponse;
            theResponse = (vx_resp_base_t*)basemsg;
            vx_response_type responseType;
            responseType = theResponse->type;

            if (theResponse->return_code != 0)
            {
                cout << endl << endl << "ERROR in response.  Status Code: " << theResponse->status_code << endl << "Status String: " << theResponse->status_string << endl << endl;
				// GKy 091231 Add Error Handle:
				//switch()
				stateMgr->txErr( theResponse->status_code, (const char*)theResponse->status_string );
            }
            else
            {
                //These are responses that we want to perform state mgmt or special reporting for .
                switch (responseType)        //Find the specific Response type, process the Response
                {
                    case resp_connector_create:
                        resp_ConnectorCreate((vx_resp_connector_create_t*)theResponse);
                        if (quickTestMode)  //for "quicktest" only
                        {
                            vx_resp_connector_create_t* resp = (vx_resp_connector_create_t*)theResponse;
                            m_reqMgr->req_AccountLogin(resp->connector_handle, quickTestUserName, quickTestUserPW, 0, 0, 0, 0, mode_auto_accept);
                        }
                        break;
                    case resp_connector_initiate_shutdown:
                        resp_ConnectorShutdown((vx_resp_connector_initiate_shutdown_t*)theResponse);
                        break;
                    case resp_account_channel_create:
                        resp_ChannelCreate((vx_resp_account_channel_create_t*)theResponse);
                        break;
                    case resp_account_channel_favorite_set:
                        resp_ChannelFavSet((vx_resp_account_channel_favorite_set_t*)theResponse);
                        break;
                    case resp_account_channel_favorite_group_set:
                        resp_ChannelFavGroupSet((vx_resp_account_channel_favorite_group_set_t*)theResponse);
                        break;
                    case resp_aux_capture_audio_stop:
                        resp_CaptureAudioStop((vx_resp_aux_capture_audio_stop_t *)theResponse);
                        break;
                    case resp_aux_connectivity_info:
                        resp_NetworkTest((vx_resp_aux_connectivity_info_t*)theResponse);
                        break;
                    case resp_aux_get_render_devices:
                        resp_ListRenderDevices((vx_resp_aux_get_render_devices_t*)theResponse);
                        break;
                    case resp_aux_get_capture_devices:
                        resp_ListCaptureDevices((vx_resp_aux_get_capture_devices_t*)theResponse);
                        break;
                    case resp_account_get_session_fonts:
                        resp_GetSessionFonts((vx_resp_account_get_session_fonts_t *)theResponse);
                        break;
                    case resp_account_get_template_fonts:
                        resp_GetTemplateFonts((vx_resp_account_get_template_fonts_t *)theResponse);
                        break;
                    case resp_aux_get_vad_properties:
                        resp_GetVadProperties((vx_resp_aux_get_vad_properties_t *)theResponse);
                        break;
                    case resp_account_list_auto_accept_rules:
                        resp_ListAutoAcceptRules((vx_resp_account_list_auto_accept_rules_t *)theResponse);
                        break;
                    case resp_account_list_block_rules:
                        resp_ListBlockRules((vx_resp_account_list_block_rules_t *)theResponse);
                        break;
                    case resp_aux_diagnostic_state_dump:
                        resp_State((vx_resp_aux_diagnostic_state_dump_t *)theResponse);
                        break;
                    case resp_connector_get_local_audio_info:
                        resp_AudioInfo((vx_resp_connector_get_local_audio_info_t *)theResponse);
                        break;
                    case resp_account_channel_get_participants:
                        resp_ChannelGetParticipants((vx_resp_account_channel_get_participants *)theResponse);
                        break;
                    case resp_none:
                    case resp_account_login:
                    case resp_account_logout:
                    case resp_account_set_login_properties:
                    case resp_sessiongroup_create:
                    case resp_sessiongroup_terminate:
                    case resp_sessiongroup_add_session:
                    case resp_sessiongroup_remove_session:
                    case resp_sessiongroup_set_focus:
                    case resp_sessiongroup_unset_focus:
                    case resp_sessiongroup_reset_focus:
                    case resp_sessiongroup_set_tx_session:
                    case resp_sessiongroup_set_tx_all_sessions:
                    case resp_sessiongroup_set_tx_no_session:
                    case resp_session_create:
                    case resp_session_media_connect:
                    case resp_session_media_disconnect:
                    case resp_session_terminate:
						break;

                    case resp_session_mute_local_speaker: // GKy 100105
						break;

                    case resp_session_set_local_speaker_volume:
                    case resp_session_channel_invite_user:
                    case resp_session_set_participant_volume_for_me:
						break;

                    case resp_session_set_participant_mute_for_me: // GKy 100105 ++++
                        resp_LocalUserMute((vx_resp_session_set_participant_mute_for_me_t *)theResponse);
						break;

                    case resp_session_set_3d_position:
                    case resp_session_set_voice_font:
                    case resp_account_channel_update:
                    case resp_account_channel_delete:
                    case resp_account_channel_favorites_get_list:
                    case resp_account_channel_favorite_delete:
                    case resp_account_channel_favorite_group_delete:
                    case resp_account_channel_get_info:
                    case resp_account_channel_search:
                    case resp_account_buddy_search:
                    case resp_account_channel_add_moderator:
                    case resp_account_channel_remove_moderator:
                    case resp_account_channel_get_moderators:
                    case resp_account_channel_add_acl:
                    case resp_account_channel_remove_acl:
                    case resp_account_channel_get_acl:
                    case resp_channel_mute_user:
                    case resp_channel_ban_user:
                    case resp_channel_get_banned_users:
                    case resp_channel_kick_user:
                    case resp_channel_mute_all_users:
                    case resp_connector_mute_local_mic:
                    case resp_connector_mute_local_speaker:
                    case resp_connector_set_local_mic_volume:
                    case resp_connector_set_local_speaker_volume:
                    case resp_account_buddy_set:
                    case resp_account_buddy_delete:
                    case resp_account_buddygroup_set:
                    case resp_account_buddygroup_delete:
                    case resp_account_list_buddies_and_groups:
                    case resp_session_send_message:
                    case resp_account_set_presence:
                    case resp_account_send_subscription_reply:
                    case resp_session_send_notification:
                    case resp_account_create_block_rule:
                    case resp_account_delete_block_rule:
                    case resp_account_create_auto_accept_rule:
                    case resp_account_delete_auto_accept_rule:
						break;

					// GKy 091231 
                    case resp_account_update_account:
						VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_ACC_UPDATE_OK);
						stateMgr->txALL();
						break;

                    case resp_account_get_account:
                    case resp_account_send_sms:
                    case resp_aux_set_render_device:
                    case resp_aux_set_capture_device:
						break;

					// GKy 100114
					case resp_aux_get_mic_level: //Check..not sure why sameple not complete this part,
					// may be still under construction
						//vx_resp_aux_get_mic_level
						resp_GetMicLevel((vx_resp_aux_get_mic_level_t *)theResponse);
						break;

                    case resp_aux_get_speaker_level:
                    case resp_aux_set_mic_level:
                    case resp_aux_set_speaker_level:
                    case resp_aux_render_audio_start:
                    case resp_aux_render_audio_stop:
                    case resp_aux_capture_audio_start:
                    case resp_aux_global_monitor_keyboard_mouse:
                    case resp_aux_set_idle_timeout:
                    case resp_aux_create_account:
                    case resp_aux_reactivate_account:
                    case resp_aux_deactivate_account:
                    case resp_account_post_crash_dump:
                    case resp_aux_reset_password:
                    case resp_sessiongroup_set_session_3d_position:
                    case resp_aux_start_buffer_capture:
                    case resp_aux_play_audio_buffer:
                    case resp_sessiongroup_control_recording:
                    case resp_sessiongroup_control_playback:
                    case resp_sessiongroup_set_playback_options:
                    case resp_session_text_connect:
                    case resp_session_text_disconnect:
                    case resp_channel_set_lock_mode:
                    case resp_aux_render_audio_modify:
                    case resp_session_send_dtmf:
                    case resp_aux_set_vad_properties:
                    case resp_sessiongroup_control_audio_injection:
                    case resp_account_channel_change_owner:
                    case resp_account_send_user_app_data:
                    case req_max:
                        break;


                }
            }
            WriteResponseToFile(theResponse);
            std::string reqID(theResponse->request->cookie ? theResponse->request->cookie : "");
            stateMgr->DeleteCommandReqID(reqID);
            destroy_resp(theResponse);
            break;
        }
        default:
            break;
    }
    //mutex2.Release();
}
