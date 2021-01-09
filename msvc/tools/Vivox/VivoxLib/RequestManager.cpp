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

#include "RequestManager.h"
#include "StateManager.h"
#include <stdio.h>

using namespace std;

RequestManager::RequestManager(std::ostream &stdcout, std::ostream &stdcerr, StateManager* sMgr) :
    cout(stdcout),
    cerr(stdcerr)
{
    debuglevel = 0;
    loglevel = 0; // turn off log by default
    stateMgr = sMgr;
}

void RequestManager::SetDebug(int debugval)
{
    debuglevel = debugval;
}

void RequestManager::SetLogLevel(int logval)
{
    loglevel = logval;
}

int RequestManager::req_ConnectorCreate(std::string acctmgmtserver, int minimumPort, int maximumPort)
{
    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_create_t");

    vx_req_connector_create_t* reqStruct = NULL;
    vx_req_connector_create_create(&reqStruct);
    reqStruct->mode = connector_mode_normal;
    reqStruct->acct_mgmt_server = vx_strdup(acctmgmtserver.c_str());
    reqStruct->minimum_port = minimumPort;
    reqStruct->maximum_port = maximumPort;
    reqStruct->client_name = vx_strdup("TestApp");
    reqStruct->log_filename_prefix = vx_strdup("vx");
    reqStruct->log_filename_suffix = vx_strdup(".txt");
#ifdef _WIN32
    //reqStruct->log_folder = vx_strdup("C:\\VivoxLogs\\");
    reqStruct->log_folder = vx_strdup(".\\VivoxLogsReqMgr\\");
#else
    reqStruct->log_folder = vx_strdup("./VivoxLogs/");
#endif
    reqStruct->log_level = loglevel;
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle_type = session_handle_type_legacy;
    reqStruct->application = vx_strdup("VivoxSDKSampleApp.1");

    int ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_AccountLogin(std::string chandle, std::string username, std::string password, int pres, int autoanswer, int text, int participantPropertyFrequnecy, vx_buddy_management_mode buddyManagementMode)
{
    int ret = -1;
    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_login_t");

    vx_req_account_login_t* reqStruct = NULL;
    vx_req_account_login_create(&reqStruct);
    reqStruct->acct_name = vx_strdup(username.c_str());
    reqStruct->acct_password = vx_strdup(password.c_str());
    if (autoanswer == 0)
    {
        reqStruct->answer_mode = mode_verify_answer;
    }
    else
    {
        reqStruct->answer_mode = mode_auto_answer;
    }
    reqStruct->participant_property_frequency = participantPropertyFrequnecy;
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->connector_handle = vx_strdup(chandle.c_str());
    if (pres > 0)
    {
        reqStruct->enable_buddies_and_presence = 1;
    }
    if (text > 0)
    {
        reqStruct->enable_text = text_mode_enabled;
    }
    else
    {
        reqStruct->enable_text = text_mode_disabled;
    }

    reqStruct->buddy_management_mode = buddyManagementMode;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_AccountAuthTokenLogin(std::string chandle, std::string authtoken, int pres, int autoanswer, int text, int participantPropertyFrequnecy, vx_buddy_management_mode buddyManagementMode)
{
    int ret = -1;
    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_authtoken_login_t");

    vx_req_account_authtoken_login_t* reqStruct = NULL;
    vx_req_account_authtoken_login_create(&reqStruct);
    reqStruct->authtoken = vx_strdup(authtoken.c_str());
    reqStruct->participant_property_frequency = participantPropertyFrequnecy;
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->connector_handle = vx_strdup(chandle.c_str());
    if (pres > 0)
    {
        reqStruct->enable_buddies_and_presence = 1;
    }
    if (text > 0)
    {
        reqStruct->enable_text = text_mode_enabled;
    }
    else
    {
        reqStruct->enable_text = text_mode_disabled;
    }

    reqStruct->buddy_management_mode = buddyManagementMode;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_AccountAnonymousLogin(std::string chandle, std::string displayname, int pres, int participantPropertyFrequnecy, vx_buddy_management_mode buddyManagementMode)
{
    int ret = -1;
    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_anonymous_login_t");

    vx_req_account_anonymous_login_t* reqStruct = NULL;
    vx_req_account_anonymous_login_create(&reqStruct);
    reqStruct->displayname = vx_strdup(displayname.c_str());
    reqStruct->participant_property_frequency = participantPropertyFrequnecy;
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->connector_handle = vx_strdup(chandle.c_str());
    if (pres > 0)
    {
        reqStruct->enable_buddies_and_presence = 1;
    }
    reqStruct->buddy_management_mode = buddyManagementMode;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupCreate(std::string ahandle, int isPlayback)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_sessiongroup_create_t* reqStruct;
        vx_req_sessiongroup_create_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        if (isPlayback == 1)
        {
            reqStruct->type = sessiongroup_type_playback;
        }
        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());

        stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_create_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SessionGroupTerminate(std::string sghandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_terminate_t* reqStruct = NULL;
    vx_req_sessiongroup_terminate_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_terminate_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupAddSession(std::string sghandle, std::string uri, int connect_audio, int connect_text, int session_font_id, std::string pw, int jitter_compensation)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_add_session_t* reqStruct = NULL;
    vx_req_sessiongroup_add_session_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->uri = vx_strdup(uri.c_str());
    reqStruct->connect_audio = connect_audio;
    reqStruct->connect_text = connect_text;
    reqStruct->password = vx_strdup(pw.c_str());
    reqStruct->session_font_id = session_font_id;

    if (jitter_compensation > 0)
    {
        reqStruct->jitter_compensation = jitter_compensation;
    }

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_add_session_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupRemoveSession(std::string sghandle, std::string shandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_remove_session_t* reqStruct = NULL;
    vx_req_sessiongroup_remove_session_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_remove_session_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}   

int RequestManager::req_SessionGroupSetFocus(std::string sghandle, std::string shandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_set_focus_t* reqStruct = NULL;
    vx_req_sessiongroup_set_focus_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_set_focus_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupUnsetFocus(std::string sghandle, std::string shandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_unset_focus_t* reqStruct = NULL;
    vx_req_sessiongroup_unset_focus_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_unset_focus_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupResetFocus(std::string sghandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_reset_focus_t* reqStruct = NULL;
    vx_req_sessiongroup_reset_focus_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_reset_focus_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupSetTx(std::string sghandle, std::string shandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_set_tx_session_t* reqStruct = NULL;
    vx_req_sessiongroup_set_tx_session_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_set_tx_session_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupSetTxAll(std::string sghandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_set_tx_all_sessions_t* reqStruct = NULL;
    vx_req_sessiongroup_set_tx_all_sessions_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_set_tx_all_sessions_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionGroupSetTxNone(std::string sghandle)
{
    int ret = -1;
    if (!stateMgr->GetSessionGroupExists(sghandle))
    {
        cout << "SessionGroup handle " << sghandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_set_tx_no_session_t* reqStruct = NULL;
    vx_req_sessiongroup_set_tx_no_session_create(&reqStruct);

    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_set_tx_no_session_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionCreate(std::string ahandle, std::string desturi, int session_font_id, std::string channelName, std::string pw, int connectAudio, int connectText, int passwordHashed, int jitter_compensation)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_session_create_t");

        vx_req_session_create_t* reqStruct = NULL;
        vx_req_session_create_create(&reqStruct);
        if (connectAudio == 0)
        {
            reqStruct->connect_audio = 0;
        }
        else
        {
            reqStruct->connect_audio = 1;
        }

        if (connectText == 0)
        {
            reqStruct->connect_text = 0;
        }
        else
        {
            reqStruct->connect_text = 1;
        }

        reqStruct->name = vx_strdup("");
        reqStruct->uri = vx_strdup(desturi.c_str());
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->session_font_id = session_font_id;
        if (channelName.size() > 0)
        {
            reqStruct->name = vx_strdup(channelName.c_str());
        }
        if (pw.size() > 0)
        {
            reqStruct->password = vx_strdup(pw.c_str());
        }

        if(passwordHashed == 0)
            reqStruct->password_hash_algorithm = password_hash_algorithm_cleartext;
        else if (passwordHashed == 1)
            reqStruct->password_hash_algorithm = password_hash_algorithm_sha1_username_hash;
        else
            reqStruct->password_hash_algorithm = password_hash_algorithm_cleartext;

        /*reqStruct->join_audio = hasAudio;
        reqStruct->join_text = hasText;*/

        if (jitter_compensation > 0)
        {
            reqStruct->jitter_compensation = jitter_compensation;
        }
 
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}
int RequestManager::req_MediaConnect(std::string shandle, int session_font_id, int jitter_compensation)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_media_connect_t");

    vx_req_session_media_connect_t* reqStruct = NULL;
    vx_req_session_media_connect_create(&reqStruct);
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->media = media_type_audio;
    reqStruct->session_font_id = session_font_id;
    if (jitter_compensation > 0)
    {
        reqStruct->jitter_compensation = jitter_compensation;
    }
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MediaDisconnect(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_media_disconnect_t");

    vx_req_session_media_disconnect_t* reqStruct = NULL;
    vx_req_session_media_disconnect_create(&reqStruct);
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->media = media_type_audio;
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_TextConnect(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_text_connect_t");

    vx_req_session_text_connect_t* reqStruct = NULL;
    vx_req_session_text_connect_create(&reqStruct);
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_TextDisconnect(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_text_disconnect_t");

    vx_req_session_text_disconnect_t* reqStruct = NULL;
    vx_req_session_text_disconnect_create(&reqStruct);
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionTerminate(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    std::string newReqID = stateMgr->GenerateID();
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_terminate_t");

    vx_req_session_terminate_t* reqStruct = NULL;
    vx_req_session_terminate_create(&reqStruct);
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionMuteLocalSpeaker(std::string shandle, int mute, vx_mute_scope scope)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    vx_req_session_mute_local_speaker_t* reqStruct = NULL;
    vx_req_session_mute_local_speaker_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->mute_level = mute;
    reqStruct->scope = scope;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_mute_local_speaker_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SessionSetLocalSpeakerVolume(std::string shandle, int vol)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    vx_req_session_set_local_speaker_volume_t* reqStruct = NULL;
    vx_req_session_set_local_speaker_volume_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->volume = vol;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_local_speaker_volume_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_GetSessionFonts(std::string ahandle)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }

    vx_req_account_get_session_fonts_t* reqStruct = NULL;
    vx_req_account_get_session_fonts_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_get_session_fonts_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_GetTemplateFonts(std::string ahandle)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }

    vx_req_account_get_template_fonts_t* reqStruct = NULL;
    vx_req_account_get_template_fonts_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_get_template_fonts_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

/*int RequestManager::req_AddUserFont(std::string ahandle, int parent_id, std::string name, std::string desc, std::string delta)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }

    vx_req_account_add_user_font_t* reqStruct = NULL;
    vx_req_account_add_user_font_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());
    reqStruct->parent_font_id = parent_id;
    reqStruct->name = vx_strdup(name.c_str());
    reqStruct->description = vx_strdup(desc.c_str());
    reqStruct->font_delta = vx_strdup(delta.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_add_user_font_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_UpdateUserFont(std::string ahandle, int id, std::string name, std::string desc, std::string delta, int active)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }

    vx_req_account_update_user_font_t* reqStruct = NULL;
    vx_req_account_update_user_font_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());
    reqStruct->user_font_id = id;
    reqStruct->name = vx_strdup(name.c_str());
    reqStruct->description = vx_strdup(desc.c_str());
    reqStruct->font_delta = vx_strdup(delta.c_str());
    reqStruct->active = active;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_update_user_font_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}*/

int RequestManager::req_SessionSetVoiceFont(std::string shandle, int voice_font_id)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    vx_req_session_set_voice_font_t* reqStruct = NULL;
    vx_req_session_set_voice_font_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->session_font_id = voice_font_id;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_voice_font_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_AccountLogout(std::string ahandle)
{
    int ret = -1;
    //if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    //{
        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_logout_t");

        vx_req_account_logout_t* reqStruct = NULL;
        vx_req_account_logout_create(&reqStruct);
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        reqStruct->account_handle = vx_strdup(ahandle.c_str());

        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    //}
    //else
    //{
    //    cout << "Account handle " << ahandle << " not found." << endl;
    //}
    return ret;
}

int RequestManager::req_SetLoginProperties(std::string ahandle, int autoanswer, int participantPropertyFrequnecy, int enableSendChanNotifs)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_set_login_properties_t");

        vx_req_account_set_login_properties_t* reqStruct = NULL;
        vx_req_account_set_login_properties_create(&reqStruct);
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->participant_property_frequency = participantPropertyFrequnecy;
        if (autoanswer == 0)
        {
            reqStruct->answer_mode = mode_verify_answer;
        }
        else if (autoanswer == 1)
        {
            reqStruct->answer_mode = mode_auto_answer;
        }

        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ConnectorShutdown(std::string chandle)
{
    int ret = -1;
    if (stateMgr->GetIsConnectorInitialized() && stateMgr->GetConnectorHandle() == chandle)
    {
        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_initiate_shutdown_t");

        vx_req_connector_initiate_shutdown_t* reqStruct = NULL;
        vx_req_connector_initiate_shutdown_create(&reqStruct);
        reqStruct->client_name = vx_strdup("");
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        reqStruct->connector_handle = vx_strdup(chandle.c_str());

        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Connector handle " << chandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_CreateChannel(const std::string &ahandle, const std::string &chan_name, const std::string &chan_desc, 
                                      vx_channel_type channel_type, int chan_maxparts, int chan_ispersistent, 
                                      vx_channel_mode mode, int maxrange, int clampingdist, double rolloff, 
                                      double maxgain, int distmodel, const std::string &chan_password, int chan_encrypt)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_create_t* reqStruct;
        vx_req_account_channel_create_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_name = vx_strdup(chan_name.c_str());
        reqStruct->channel_desc = vx_strdup(chan_desc.c_str());
        reqStruct->channel_type = channel_type;
        reqStruct->channel_mode = mode;
        reqStruct->max_participants = chan_maxparts;
        reqStruct->set_persistent = chan_ispersistent;
        reqStruct->max_range = maxrange;
        reqStruct->clamping_dist = clampingdist;
        reqStruct->roll_off = rolloff;
        reqStruct->max_gain = maxgain;
        reqStruct->dist_model = distmodel;
        reqStruct->encrypt_audio = chan_encrypt;

        if (chan_password.length() > 0)
        {
            reqStruct->set_protected = 1;
            reqStruct->protected_password = vx_strdup(chan_password.c_str());
        }
        else
        {
            reqStruct->set_protected = 0;
        }

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_create_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_UpdateChannel(std::string ahandle, std::string chan_uri, std::string chan_name, std::string chan_desc, int chan_maxparts, int chan_ispersistent, int chan_isprotected, vx_channel_mode mode, int maxrange, int clampingdist, double rolloff, double maxgain, int distmodel, std::string chan_password, int chan_encrypt)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_update_t* reqStruct;
        vx_req_account_channel_update_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->channel_name = vx_strdup(chan_name.c_str());
        reqStruct->channel_desc = vx_strdup(chan_desc.c_str());
        reqStruct->channel_mode = mode;
        reqStruct->max_participants = chan_maxparts;
        reqStruct->set_persistent = chan_ispersistent;
        reqStruct->max_range = maxrange;
        reqStruct->clamping_dist = clampingdist;
        reqStruct->roll_off = rolloff;
        reqStruct->max_gain = maxgain;
        reqStruct->dist_model = distmodel;
        reqStruct->encrypt_audio = chan_encrypt;

        if (chan_isprotected == 1)
        {
            reqStruct->set_protected = 1;
            reqStruct->protected_password = vx_strdup(chan_password.c_str());
        }
        else if (chan_isprotected == 0)
        {
            reqStruct->set_protected = 0;
        }

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_update_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_DeleteChannel(std::string ahandle, std::string chan_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_delete_t* reqStruct;
        vx_req_account_channel_delete_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_delete_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
        return ret;
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}


int RequestManager::req_GetFavs(std::string ahandle)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_favorites_get_list_t* reqStruct;
        vx_req_account_channel_favorites_get_list_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_favorites_get_list_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SetFav(std::string ahandle, int favID, std::string chanUri, std::string chanData, int groupID, std::string label)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_favorite_set_t* reqStruct;
        vx_req_account_channel_favorite_set_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_favorite_id = favID;
        if (chanUri.length() > 0)
            reqStruct->channel_favorite_uri = vx_strdup(chanUri.c_str());
        reqStruct->channel_favorite_group_id = groupID;
        if (chanData.length() > 0)
            reqStruct->channel_favorite_data = vx_strdup(chanData.c_str());
        if (label.length() > 0)
            reqStruct->channel_favorite_label = vx_strdup(label.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_favorite_set_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_DeleteFav(std::string ahandle, int favID)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_favorite_delete_t* reqStruct;
        vx_req_account_channel_favorite_delete_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_favorite_id = favID;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_favorite_delete_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SetFavGroup(std::string ahandle, int groupID, std::string name, std::string data)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_favorite_group_set_t* reqStruct;
        vx_req_account_channel_favorite_group_set_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_favorite_group_id = groupID;
        reqStruct->channel_favorite_group_name = vx_strdup(name.c_str());
        reqStruct->channel_favorite_group_data = vx_strdup(data.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_favorite_group_set_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_DeleteFavGroup(std::string ahandle, int groupID)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_favorite_group_delete_t* reqStruct;
        vx_req_account_channel_favorite_group_delete_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_favorite_group_id = groupID;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_favorite_group_delete_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_GetChannelInfo(std::string ahandle, std::string chanUri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_get_info_t* reqStruct;
        vx_req_account_channel_get_info_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chanUri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_get_info_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SearchChannels(std::string ahandle, int pgNum, int pgSize, std::string name, std::string desc, int active, vx_channel_moderation_type mod)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_search_t* reqStruct;
        vx_req_account_channel_search_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->page_number = pgNum;
        reqStruct->page_size = pgSize;
        if (name != "''")
            reqStruct->channel_name = vx_strdup(name.c_str());
        if (desc != "''")
            reqStruct->channel_description = vx_strdup(desc.c_str());
        if (active == 1)
            reqStruct->channel_active = 1;
        reqStruct->moderation_type = mod;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_search_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SearchAccounts(std::string ahandle, int pgNum, int pgSize, std::string first, std::string last, std::string user, std::string email, const std::string &displayName)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_buddy_search_t* reqStruct;
        vx_req_account_buddy_search_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->page_number = pgNum;
        reqStruct->page_size = pgSize;
        if (first != "''")
            reqStruct->buddy_first_name = vx_strdup(first.c_str());
        if (last != "''")
            reqStruct->buddy_last_name = vx_strdup(last.c_str());
        if (user != "''")
            reqStruct->buddy_user_name = vx_strdup(user.c_str());
        if (email != "''")
            reqStruct->buddy_email = vx_strdup(email.c_str());
        if (displayName != "''")
            reqStruct->buddy_display_name = vx_strdup(displayName.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_buddy_search_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ModeratorAdd(std::string ahandle, std::string chan_uri, std::string mod_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_add_moderator_t* reqStruct;
        vx_req_account_channel_add_moderator_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->moderator_uri = vx_strdup(mod_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_add_moderator_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ModeratorRemove(std::string ahandle, std::string chan_uri, std::string mod_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_remove_moderator_t* reqStruct;
        vx_req_account_channel_remove_moderator_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->moderator_uri = vx_strdup(mod_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_remove_moderator_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ModeratorGet(std::string ahandle, std::string chan_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_get_moderators_t* reqStruct;
        vx_req_account_channel_get_moderators_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_get_moderators_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ACLGet(std::string ahandle, std::string chan_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_get_acl_t* reqStruct;
        vx_req_account_channel_get_acl_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_get_acl_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ACLAdd(std::string ahandle, std::string chan_uri, std::string acl_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_add_acl_t* reqStruct;
        vx_req_account_channel_add_acl_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->acl_uri = vx_strdup(acl_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_add_acl_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ACLRemove(std::string ahandle, std::string chan_uri, std::string acl_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_channel_remove_acl_t* reqStruct;
        vx_req_account_channel_remove_acl_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->acl_uri = vx_strdup(acl_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_remove_acl_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_MuteUser(std::string ahandle, int setMute, std::string chan_uri, std::string user_uri, vx_mute_scope scope)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_mute_user_t* reqStruct;
        vx_req_channel_mute_user_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->set_muted = setMute;
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->participant_uri = vx_strdup(user_uri.c_str());
        reqStruct->scope = scope;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_mute_user_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_MuteAllUsers(std::string ahandle, int setMuteAll, std::string chan_uri, vx_mute_scope scope)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_mute_all_users_t* reqStruct;
        vx_req_channel_mute_all_users_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->set_muted = setMuteAll;
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->scope = scope;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_mute_all_users_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_BanUser(std::string ahandle, int setBan, std::string chan_uri, std::string user_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_ban_user_t* reqStruct;
        vx_req_channel_ban_user_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->set_banned = setBan;
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->participant_uri = vx_strdup(user_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_ban_user_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_GetBannedUsers(std::string ahandle, std::string chan_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_get_banned_users_t* reqStruct;
        vx_req_channel_get_banned_users_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_get_banned_users_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_KickUser(std::string ahandle, std::string chan_uri, std::string user_uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_kick_user_t* reqStruct;
        vx_req_channel_kick_user_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
        reqStruct->participant_uri = vx_strdup(user_uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_kick_user_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SetLockMode(std::string ahandle, std::string channel_uri, vx_channel_lock_mode lock_mode)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_channel_set_lock_mode_t* reqStruct;
        vx_req_channel_set_lock_mode_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->channel_uri = vx_strdup(channel_uri.c_str());
        reqStruct->lock_mode = lock_mode;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_channel_set_lock_status_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_InviteUser(std::string shandle, std::string user_uri)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    vx_req_session_channel_invite_user_t* reqStruct;
    vx_req_session_channel_invite_user_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->participant_uri = vx_strdup(user_uri.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_channel_invite_user_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_LocalUserMute(std::string shandle, int mute, std::string user_uri, vx_mute_scope scope)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    vx_req_session_set_participant_mute_for_me_t* reqStruct;
    vx_req_session_set_participant_mute_for_me_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->participant_uri = vx_strdup(user_uri.c_str());
    reqStruct->mute = mute;
    reqStruct->scope = scope;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_participant_mute_for_me_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_LocalUserVolume(std::string shandle, int vol, std::string user_uri)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    vx_req_session_set_participant_volume_for_me_t* reqStruct;
    vx_req_session_set_participant_volume_for_me_create(&reqStruct);

    reqStruct->session_handle = vx_strdup(shandle.c_str());
    reqStruct->participant_uri = vx_strdup(user_uri.c_str());
    reqStruct->volume = vol;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_participant_volume_for_me_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_GetParts(std::string ahandle, std::string chan_uri, int pgNum, int pgSize)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }

    vx_req_account_channel_get_participants_t* reqStruct;
    vx_req_account_channel_get_participants_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());    
    reqStruct->channel_uri = vx_strdup(chan_uri.c_str());    
    reqStruct->page_number = pgNum;
    reqStruct->page_size = pgSize;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_channel_get_participants_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;    
}

int RequestManager::req_ChangeChannelOwner(std::string ahandle, std::string chan_uri, std::string new_owner_uri)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }
    vx_req_account_channel_change_owner_t* reqStruct;
    vx_req_account_channel_change_owner_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());
    reqStruct->channel_uri = vx_strdup(chan_uri.c_str());
    reqStruct->new_owner_uri = vx_strdup(new_owner_uri.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_channel_change_owner_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SendUserAppData(std::string ahandle, std::string to_uri, std::string content, std::string content_type)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != ahandle)
    {
        cout << "Account handle " << ahandle << " not found." << endl;
        return ret;
    }
    vx_req_account_send_user_app_data_t* reqStruct;
    vx_req_account_send_user_app_data_create(&reqStruct);

    reqStruct->account_handle = vx_strdup(ahandle.c_str());
    reqStruct->to_uri = vx_strdup(to_uri.c_str());
    reqStruct->content_type = vx_strdup(content_type.c_str());
    reqStruct->content = vx_strdup(content.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_send_user_app_data_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_AudioInfo()
{
    int ret = -1;
    vx_req_connector_get_local_audio_info_t* reqStruct;
    vx_req_connector_get_local_audio_info_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_get_local_audio_info_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_ListRenderDevices(void)
{
    int ret = -1;

    vx_req_aux_get_render_devices_t* reqStruct = NULL;
    vx_req_aux_get_render_devices_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_get_render_devices_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetRenderDevice(std::string renderDeviceString)
{
    int ret = -1;

    vx_req_aux_set_render_device_t* reqStruct = NULL;
    vx_req_aux_set_render_device_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_render_device_t");
    reqStruct->render_device_specifier = vx_strdup(renderDeviceString.c_str());
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetDefaultRenderDevice(void)
{
    int ret = -1;

    vx_req_aux_set_render_device_t* reqStruct = NULL;
    vx_req_aux_set_render_device_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_render_device_t");
    reqStruct->render_device_specifier = NULL; 
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MasterSpeakerSetVol(int vol)
{
    int ret = -1;

    vx_req_aux_set_speaker_level_t* reqStruct = NULL;
    vx_req_aux_set_speaker_level_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_speaker_level_t");
    reqStruct->level = vol;
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MasterSpeakerGetVol(void)
{
    int ret = -1;

    vx_req_aux_get_speaker_level_t* reqStruct = NULL;
    vx_req_aux_get_speaker_level_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_get_speaker_level_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_ListCaptureDevices(void)
{
    int ret = -1;

    vx_req_aux_get_capture_devices_t* reqStruct = NULL;
    vx_req_aux_get_capture_devices_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_get_capture_devices_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetCaptureDevice(std::string captureDeviceString)
{
    int ret = -1;

    vx_req_aux_set_capture_device_t* reqStruct = NULL;
    vx_req_aux_set_capture_device_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_capture_device_t");
    reqStruct->capture_device_specifier = vx_strdup(captureDeviceString.c_str());
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetDefaultCaptureDevice(void)
{
    int ret = -1;

    vx_req_aux_set_capture_device_t* reqStruct = NULL;
    vx_req_aux_set_capture_device_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_capture_device_t");
    reqStruct->capture_device_specifier = NULL;
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MasterMicSetVol(int vol)
{
    int ret = -1;

    vx_req_aux_set_mic_level_t* reqStruct = NULL;
    vx_req_aux_set_mic_level_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_mic_level_t");
    reqStruct->level = vol;
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MasterMicGetVol(void)
{
    int ret = -1;

    vx_req_aux_get_mic_level_t* reqStruct = NULL;
    vx_req_aux_get_mic_level_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_get_mic_level_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_RenderAudioStart(std::string wavFilePath, int loop)
{
    int ret = -1;

    vx_req_aux_render_audio_start_t* reqStruct = NULL;
    vx_req_aux_render_audio_start_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_render_audio_start_create");

    reqStruct->sound_file_path = vx_strdup(wavFilePath.c_str());
    reqStruct->loop = loop;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_GetVadProperties(void)
{
    int ret = -1;

    vx_req_aux_get_vad_properties_t* reqStruct = NULL;
    vx_req_aux_get_vad_properties_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_get_vad_properties_create");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetVadProperties(int vad_hangover, int vad_sensitivity)
{
    int ret = -1;

    vx_req_aux_set_vad_properties_t* reqStruct = NULL;
    vx_req_aux_set_vad_properties_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_set_vad_properties_create");

    reqStruct->vad_hangover = vad_hangover;
    reqStruct->vad_sensitivity = vad_sensitivity;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_RenderAudioFromBufferStart(std::string ahandle, int template_font_id, std::string delta)
{
    int ret = -1;

    vx_req_aux_play_audio_buffer_t* reqStruct = NULL;
    vx_req_aux_play_audio_buffer_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());

    if (ahandle.length() > 0)
    {
        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        if (template_font_id > -1)
        {
            reqStruct->template_font_id = template_font_id;
            if (delta.length() > 0)
            {
                reqStruct->font_delta = vx_strdup(delta.c_str());
            }
        }
    }

    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_play_audio_buffer_t");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_RenderAudioStop(void)
{
    int ret = -1;

    vx_req_aux_render_audio_stop_t* reqStruct = NULL;
    vx_req_aux_render_audio_stop_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_render_audio_stop_t");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_CaptureAudioStart(void)
{
    int ret = -1;

    vx_req_aux_capture_audio_start_t* reqStruct = NULL;
    vx_req_aux_capture_audio_start_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_capture_audio_start_t");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_CaptureAudioToBufferStart(void)
{
    int ret = -1;

    vx_req_aux_start_buffer_capture_t* reqStruct = NULL;
    vx_req_aux_start_buffer_capture_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_start_buffer_capture_t");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_CaptureAudioStop(void)
{
    int ret = -1;

    vx_req_aux_capture_audio_stop_t* reqStruct = NULL;
    vx_req_aux_capture_audio_stop_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_capture_audio_stop_t");

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SpeakerVol(int vol)
{
    int ret = -1;
    vx_req_connector_set_local_speaker_volume_t* reqStruct;
    vx_req_connector_set_local_speaker_volume_create(&reqStruct);

    reqStruct->volume = vol;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_set_local_speaker_volume_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SpeakerMute(int mute)
{
    int ret = -1;
    vx_req_connector_mute_local_speaker_t* reqStruct;
    vx_req_connector_mute_local_speaker_create(&reqStruct);

    reqStruct->mute_level = mute;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_mute_local_speaker_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MicVol(int vol)
{
    int ret = -1;
    vx_req_connector_set_local_mic_volume_t* reqStruct;
    vx_req_connector_set_local_mic_volume_create(&reqStruct);

    reqStruct->volume = vol;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_set_local_mic_volume_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_MicMute(int mute)
{
    vx_req_connector_mute_local_mic_t* reqStruct;
    vx_req_connector_mute_local_mic_create(&reqStruct);

    reqStruct->mute_level = mute;

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_connector_mute_local_mic_t");
    int ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveToOrigin(std::string shandle)
{
    int ret = -1;
    //int state = stateMgr->GetMediaSessionState(shandle);
    //if (state < 0)
    //{
    //    cout << "Session handle " << shandle << " not found." << endl;
    //    return ret;
    //}
 //   if (state != session_media_connected)
    //{
    //    cout << shandle << " is not connected to audio." << endl;
 //       return ret;
    //}

    double listenerOrientation[6];
    double listenerPosition[3];

    listenerPosition[0] = 0.0;
    listenerPosition[1] = 0.0;
    listenerPosition[2] = 0.0;

    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2]; 

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerPosition(reqStruct->listener_position);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveLeft(std::string shandle, double delta)
{
    int ret = -1;
    //int state = stateMgr->GetMediaSessionState(shandle);
    //if (state < 0)
    //{
    //    cout << "Session handle " << shandle << " not found." << endl;
    //    return ret;
    //}
    //if (state != session_media_connected)
    //{
    //    cout << shandle << " is not connected to audio." << endl;
    //    return ret;
    //}

    double listenerPosition[3];
    double listenerOrientation[6];
    double delta_x = 0.0;
    double delta_z = 0.0;

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    delta_x = delta * listenerOrientation[2];
    delta_z = -1.0 * delta * listenerOrientation[0];

    listenerPosition[0] += delta_x;

    listenerPosition[2] += delta_z;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];



    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveRight(std::string shandle, double delta)
{
    int ret = -1;
    //int state = stateMgr->GetMediaSessionState(shandle);
    //if (state < 0)
    //{
    //    cout << "Session handle " << shandle << " not found." << endl;
    //    return ret;
    //}
    //if (state != session_media_connected)
    //{
    //    cout << shandle << " is not connected to audio." << endl;
    //    return ret;
    //}

    double listenerPosition[3];
    double listenerOrientation[6];
    double delta_x = 0.0;
    double delta_z = 0.0;

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    delta_x = -1.0 * delta * listenerOrientation[2];
    delta_z = delta * listenerOrientation[0];

    listenerPosition[0] += delta_x;

    listenerPosition[2] += delta_z;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];


    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveForward(std::string shandle, double delta)
{
    int ret = -1;
    //int state = stateMgr->GetMediaSessionState(shandle);
    //if (state < 0)
    //{
    //    cout << "Session handle " << shandle << " not found." << endl;
    //    return ret;
    //}
    //if (state != session_media_connected)
    //{
    //    cout << shandle << " is not connected to audio." << endl;
    //    return ret;
    //}

    double listenerPosition[3];
    double listenerOrientation[6];
    double delta_x = 0.0;
    double delta_z = 0.0;

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    delta_x = delta * listenerOrientation[0];
    delta_z = delta * listenerOrientation[2];

    listenerPosition[0] += delta_x;

    listenerPosition[2] += delta_z;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveBack(std::string shandle, double delta)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    double listenerPosition[3];
    double listenerOrientation[6];
    double delta_x = 0.0;
    double delta_z = 0.0;

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    delta_x = -1.0 * delta * listenerOrientation[0];
    delta_z = -1.0 * delta * listenerOrientation[2];

    listenerPosition[0] += delta_x;

    listenerPosition[2] += delta_z;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveUp(std::string shandle, double delta)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    double listenerPosition[3];
    double listenerOrientation[6];

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    listenerPosition[1] += delta;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_moveDown(std::string shandle, double delta)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    double listenerPosition[3];
    double listenerOrientation[6];

    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    listenerPosition[1] -= delta;

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerPosition(listenerPosition);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_turnLeft45(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    double listenerHeadingDegrees;
    double listenerPosition[3];
    double listenerOrientation[6];

    stateMgr->GetListenerHeadingDegrees(&listenerHeadingDegrees);
    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position_t* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    listenerHeadingDegrees -= 45.0;
    if (listenerHeadingDegrees < 0.0) {
        listenerHeadingDegrees += 360.0;
    }

    listenerOrientation[0] = 1.0 * sin(2 * PI *(listenerHeadingDegrees/360.0));
    listenerOrientation[2] = -1.0 * cos(2 * PI * (listenerHeadingDegrees/360.0));

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];


    stateMgr->SetListenerHeadingDegrees(listenerHeadingDegrees);
    stateMgr->SetListenerOrientation(listenerOrientation);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_turnRight45(std::string shandle)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }
    if (state != session_media_connected)
    {
        cout << shandle << " is not connected to audio." << endl;
        return ret;
    }

    double listenerHeadingDegrees;
    double listenerPosition[3];
    double listenerOrientation[6];

    stateMgr->GetListenerHeadingDegrees(&listenerHeadingDegrees);
    stateMgr->GetListenerPosition(listenerPosition);
    stateMgr->GetListenerOrientation(listenerOrientation);

    vx_req_session_set_3d_position_t* reqStruct;
    vx_req_session_set_3d_position_create(&reqStruct);
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    listenerHeadingDegrees += 45.0;
    if (listenerHeadingDegrees >= 360.0) {
        listenerHeadingDegrees -= 360.0;
    }

    listenerOrientation[0] = 1.0 * sin(2 * PI *(listenerHeadingDegrees/360.0));
    listenerOrientation[2] = -1.0 * cos(2 * PI * (listenerHeadingDegrees/360.0));

    reqStruct->listener_position[0] = listenerPosition[0];
    reqStruct->listener_position[1] = listenerPosition[1];
    reqStruct->listener_position[2] = listenerPosition[2];

    reqStruct->listener_at_orientation[0] = listenerOrientation[0];
    reqStruct->listener_at_orientation[1] = listenerOrientation[1];
    reqStruct->listener_at_orientation[2] = listenerOrientation[2];

    reqStruct->listener_up_orientation[0] = listenerOrientation[3];
    reqStruct->listener_up_orientation[1] = listenerOrientation[4];
    reqStruct->listener_up_orientation[2] = listenerOrientation[5];

    reqStruct->speaker_position[0] = listenerPosition[0];
    reqStruct->speaker_position[1] = listenerPosition[1];
    reqStruct->speaker_position[2] = listenerPosition[2]; 

    reqStruct->speaker_at_orientation[0] = listenerOrientation[0];
    reqStruct->speaker_at_orientation[1] = listenerOrientation[1];
    reqStruct->speaker_at_orientation[2] = listenerOrientation[2];

    reqStruct->speaker_up_orientation[0] = listenerOrientation[3];
    reqStruct->speaker_up_orientation[1] = listenerOrientation[4];
    reqStruct->speaker_up_orientation[2] = listenerOrientation[5];

    stateMgr->SetListenerHeadingDegrees(listenerHeadingDegrees);
    stateMgr->SetListenerOrientation(listenerOrientation);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

#define SDK_SAMPLE_APP_PI 3.1415926535897932384626433832795

int RequestManager::req_sessionPos(std::string sghandle, std::string shandle, int angle, int dist)
{
    int ret = -1;
    int state = stateMgr->GetMediaSessionState(shandle);
    if (state < 0)
    {
        cout << "Session handle " << shandle << " not found." << endl;
        return ret;
    }

    vx_req_sessiongroup_set_session_3d_position_t* reqStruct;
    vx_req_sessiongroup_set_session_3d_position_create(&reqStruct);
    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->session_handle = vx_strdup(shandle.c_str());

    reqStruct->speaker_at_orientation[0] = 0.0;
    reqStruct->speaker_at_orientation[1] = 0.0;
    reqStruct->speaker_at_orientation[2] = -1.0;

    reqStruct->speaker_position[0] = (double)dist * cos(((double)angle/180.0) * (SDK_SAMPLE_APP_PI));
    reqStruct->speaker_position[1] = 0.0;
    reqStruct->speaker_position[2] = (double)dist * sin(((double)angle/180.0) * (SDK_SAMPLE_APP_PI));

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_session_set_3d_position");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);

    return ret;
}

int RequestManager::req_BuddySet(const std::string &acct_handle, std::string buddy_uri, std::string buddy_display_name, std::string buddy_data, int group_id, std::string msg)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != acct_handle)
    {
        cout << "Account handle " << acct_handle << " not found." << endl;
    }

    vx_req_account_buddy_set_t* reqStruct;
    vx_req_account_buddy_set_create(&reqStruct);

    reqStruct->buddy_uri = vx_strdup(buddy_uri.c_str());
    reqStruct->display_name = vx_strdup(buddy_display_name.c_str());
    reqStruct->buddy_data = vx_strdup(buddy_data.c_str());
    reqStruct->account_handle = vx_strdup(acct_handle.c_str());
    reqStruct->group_id = group_id;
    if (msg.size() > 0)
    {
        reqStruct->message = vx_strdup(msg.c_str());
    }

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_buddy_set_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_BuddyDelete(const std::string &acct_handle, std::string buddy_uri)
{
    int ret = -1;
    if (!stateMgr->GetIsAccountLoggedIn() || stateMgr->GetAccountHandle() != acct_handle)
    {
        cout << "Account handle " << acct_handle << " not found." << endl;
    }
    vx_req_account_buddy_delete_t* reqStruct;
    vx_req_account_buddy_delete_create(&reqStruct);

    reqStruct->buddy_uri = vx_strdup(buddy_uri.c_str());
    reqStruct->account_handle = vx_strdup(acct_handle.c_str());

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_buddy_delete_t");
    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_BuddyGroupSet(std::string ahandle, int group_id, std::string group_name, std::string group_data)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_buddygroup_set_t* reqStruct;
        vx_req_account_buddygroup_set_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->group_id = group_id;
        reqStruct->group_name = vx_strdup(group_name.c_str());
        reqStruct->group_data = vx_strdup(group_data.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_buddygroup_set_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_BuddyGroupDelete(std::string ahandle, int group_id)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_buddygroup_delete_t* reqStruct;
        vx_req_account_buddygroup_delete_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->group_id = group_id;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_buddygroup_delete_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_CreateBlockRule(std::string ahandle, std::string mask, int presence_only)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_create_block_rule_t* reqStruct;
        vx_req_account_create_block_rule_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->block_mask = vx_strdup(mask.c_str());
        reqStruct->presence_only = presence_only;

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_create_block_rule_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_DeleteBlockRule(std::string ahandle, std::string mask)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_delete_block_rule_t* reqStruct;
        vx_req_account_delete_block_rule_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->block_mask = vx_strdup(mask.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_delete_block_rule_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ListBlockRules(std::string ahandle)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_list_block_rules_t* reqStruct;
        vx_req_account_list_block_rules_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_list_block_rules_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_CreateAutoAcceptRule(std::string ahandle, std::string mask, int auto_add, std::string nickname)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_create_auto_accept_rule_t* reqStruct;
        vx_req_account_create_auto_accept_rule_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->auto_accept_mask = vx_strdup(mask.c_str());
        reqStruct->auto_add_as_buddy = auto_add;
        if (!nickname.empty())
        {
            reqStruct->auto_accept_nickname = vx_strdup(nickname.c_str());
        }

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_create_auto_accept_rule_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_DeleteAutoAcceptRule(std::string ahandle, std::string mask)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_delete_auto_accept_rule_t* reqStruct;
        vx_req_account_delete_auto_accept_rule_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->auto_accept_mask = vx_strdup(mask.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_delete_auto_accept_rule_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_ListAutoAcceptRules(std::string ahandle)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_list_auto_accept_rules_t* reqStruct;
        vx_req_account_list_auto_accept_rules_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_list_auto_accept_rules_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SubscriptionReply(std::string ahandle, std::string subscriptionHandle, std::string uri, vx_rule_type ruleType, int addAsBuddy)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_send_subscription_reply_t* reqStruct;
        vx_req_account_send_subscription_reply_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->subscription_handle = vx_strdup(subscriptionHandle.c_str());
        reqStruct->buddy_uri = vx_strdup(uri.c_str());
        reqStruct->rule_type = ruleType;
        reqStruct->auto_accept = addAsBuddy;
        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_send_subscription_reply_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SendMessage(std::string shandle, std::string msg)
{
    int ret = -1;
    if (stateMgr->GetTextSessionState(shandle) >= 0)
    {
        vx_req_session_send_message_t* reqStruct;
        vx_req_session_send_message_create(&reqStruct);

        reqStruct->session_handle = vx_strdup(shandle.c_str());
        reqStruct->message_body = vx_strdup(msg.c_str());
        reqStruct->message_header = vx_strdup("");
        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_session_send_message_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Session handle " << shandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_NetworkTest(std::string wellknownip, std::string stunserver, std::string echoserver, int echoPort, int timeout)
{
    int ret = -1;
    vx_req_aux_connectivity_info_t* reqStruct;
    vx_req_aux_connectivity_info_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_connectivity_info_t");
    reqStruct->well_known_ip = vx_strdup(wellknownip.c_str());
    reqStruct->stun_server = vx_strdup(stunserver.c_str());
    reqStruct->echo_server = vx_strdup(echoserver.c_str());
    reqStruct->echo_port = echoPort;
    reqStruct->timeout = timeout;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_NetworkTest(std::string acct_mgmt_server)
{
    int ret = -1;
    vx_req_aux_connectivity_info_t* reqStruct;
    vx_req_aux_connectivity_info_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_aux_connectivity_info_t");
    reqStruct->acct_mgmt_server = vx_strdup(acct_mgmt_server.c_str());

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_CSControlRecording(std::string sghandle, vx_sessiongroup_recording_control_type type, int deltas_per_control, string filename, int throw_events, int loop_duration)
{
    int ret = -1;
    vx_req_sessiongroup_control_recording_t* reqStruct;
    vx_req_sessiongroup_control_recording_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_control_recording_t");
    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->recording_control_type = type;
    reqStruct->delta_frames_per_control_frame = deltas_per_control;
    if (filename.length() > 0)
    {
        reqStruct->filename = vx_strdup(filename.c_str());
    }
    reqStruct->enable_audio_recording_events = throw_events;
    reqStruct->loop_mode_duration_seconds = loop_duration;

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_ControlAudioInjection(std::string sghandle, vx_sessiongroup_audio_injection_control_type type, std::string filename)
{
    int ret = -1;
    vx_req_sessiongroup_control_audio_injection_t* reqStruct;
    vx_req_sessiongroup_control_audio_injection_create(&reqStruct);

    std::string newReqID = stateMgr->GenerateID();
    reqStruct->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_sessiongroup_control_audio_injection_t");
    reqStruct->sessiongroup_handle = vx_strdup(sghandle.c_str());
    reqStruct->audio_injection_control_type = type;
    if (filename.length() > 0)
    {
        reqStruct->filename = vx_strdup(filename.c_str());
    }

    ret = vx_issue_request((vx_req_base_t*)reqStruct);
    return ret;
}

int RequestManager::req_SetPresence(const std::string &acct_handle, const std::string &state, const std::string &message) {
    //int ret = -1;
    vx_req_account_set_presence_t *pRequest;
    vx_req_account_set_presence_create(&pRequest);
    pRequest->account_handle = vx_strdup(acct_handle.c_str());
    vx_buddy_presence_state presence = buddy_presence_online;
    if(state == "online") {
        presence = buddy_presence_online;
    } else if(state == "away") {
        presence = buddy_presence_away;
    } else if(state == "busy") { 
        presence = buddy_presence_busy;
    } else if(state == "phone") {
        presence = buddy_presence_onthephone;
    } else if(state == "lunch") {
        presence = buddy_presence_outtolunch;
    } else if(state == "brb") {
        presence = buddy_presence_brb;
    } else if(state == "online-slc") {
        presence = buddy_presence_online_slc;
    } 
    pRequest->presence = presence;
    pRequest->custom_message = vx_strdup(message.c_str());

    std::string newReqID = stateMgr->GenerateID();
      pRequest->base.cookie = vx_strdup(newReqID.c_str());
    stateMgr->InsertCommandReqID(newReqID, "vx_req_account_set_presence_t");

    return vx_issue_request(&pRequest->base);
}

int RequestManager::req_SendDTMF(std::string shandle, std::string dtmf)
{
    int ret = -1;
    if (stateMgr->GetTextSessionState(shandle) > 0 || stateMgr->GetMediaSessionState(shandle) > 0)
    {
        vx_dtmf_type dtmf_val;
        if (dtmf.substr(0,1) == "0")
             dtmf_val = dtmf_0;
        else if (dtmf.substr(0,1) == "1")
            dtmf_val = dtmf_1;
        else if (dtmf.substr(0,1) == "2")
            dtmf_val = dtmf_2;
        else if (dtmf.substr(0,1) == "3")
            dtmf_val = dtmf_3;
        else if (dtmf.substr(0,1) == "4")
            dtmf_val = dtmf_4;
        else if (dtmf.substr(0,1) == "5")
            dtmf_val = dtmf_5;
        else if (dtmf.substr(0,1) == "6")
            dtmf_val = dtmf_6;
        else if (dtmf.substr(0,1) == "7")
            dtmf_val = dtmf_7;
        else if (dtmf.substr(0,1) == "8")
            dtmf_val = dtmf_8;
        else if (dtmf.substr(0,1) == "9")
            dtmf_val = dtmf_9;
        else if (dtmf.substr(0,1) == "#")
            dtmf_val = dtmf_pound;
        else if (dtmf.substr(0,1) == "*")
            dtmf_val = dtmf_star;
        else if (dtmf.substr(0,1) == "A")
            dtmf_val = dtmf_A;
        else if (dtmf.substr(0,1) == "B")
            dtmf_val = dtmf_B;
        else if (dtmf.substr(0,1) == "C")
            dtmf_val = dtmf_C;
        else if (dtmf.substr(0,1) == "D")
            dtmf_val = dtmf_D;
        else
            return -1;

        vx_req_session_send_dtmf_t* reqStruct;
        vx_req_session_send_dtmf_create(&reqStruct);
        reqStruct->session_handle = vx_strdup(shandle.c_str());
        reqStruct->dtmf_type = dtmf_val;
        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_session_send_dtmf_t");
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Session handle " << shandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SendNotification(std::string shandle, int state)
{
    int ret = -1;
    if (stateMgr->GetTextSessionState(shandle) > 0 || stateMgr->GetMediaSessionState(shandle) > 0)
    {
        vx_req_session_send_notification_t* reqStruct;
        vx_req_session_send_notification_create(&reqStruct);

        reqStruct->session_handle = vx_strdup(shandle.c_str());
        switch(state) {
            case 0:
                reqStruct->notification_type = notification_not_typing; break;
            case 1:
                reqStruct->notification_type = notification_typing; break;
            case 2:
                reqStruct->notification_type = notification_hand_lowered; break;
            case 3:
                reqStruct->notification_type = notification_hand_raised; break;
            default:
                cout << "State " << state << " is not valid." << endl;
                return ret;
        }

        std::string newReqID = stateMgr->GenerateID();
        stateMgr->InsertCommandReqID(newReqID, "vx_req_session_send_notification_t");
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Session handle " << shandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_UpdateAccount(std::string ahandle, std::string displayname)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_update_account_t* reqStruct;
        vx_req_account_update_account_create(&reqStruct);
        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        if (displayname.length() > 0)
        {
            reqStruct->displayname = vx_strdup(displayname.c_str());
        }

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_update_account_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_GetAccount(std::string ahandle, std::string uri)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_get_account_t* reqStruct;
        vx_req_account_get_account_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        //reqStruct->uri = vx_strdup(uri.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_get_account_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SendSMS(std::string ahandle, std::string recipient_uri, std::string content)
{
    int ret = -1;
    if (stateMgr->GetIsAccountLoggedIn() && stateMgr->GetAccountHandle() == ahandle)
    {
        vx_req_account_send_sms_t* reqStruct;
        vx_req_account_send_sms_create(&reqStruct);

        reqStruct->account_handle = vx_strdup(ahandle.c_str());
        reqStruct->recipient_uri = vx_strdup(recipient_uri.c_str());
        reqStruct->content = vx_strdup(content.c_str());

        std::string newReqID = stateMgr->GenerateID();
        reqStruct->base.cookie = vx_strdup(newReqID.c_str());
        stateMgr->InsertCommandReqID(newReqID, "vx_req_account_send_sms_t");
        ret = vx_issue_request((vx_req_base_t*)reqStruct);
    }
    else
    {
        cout << "Account handle " << ahandle << " not found." << endl;
    }
    return ret;
}

int RequestManager::req_SetIdleTimeout(int seconds)
{
    //int ret = -1;
    vx_req_aux_set_idle_timeout_t *req = NULL;
    vx_req_aux_set_idle_timeout_create(&req);
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    req->seconds = seconds;
    return vx_issue_request((vx_req_base_t *)req);
}

int RequestManager::req_BindKey(const std::string &handle, const std::set<int> &codes)
{
    //int ret = -1;
    vx_req_aux_global_monitor_keyboard_mouse_t *req = NULL;
    vx_req_aux_global_monitor_keyboard_mouse_create(&req);
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    req->name = vx_strdup(handle.c_str());
    int k = 0;
    for(std::set<int>::const_iterator i = codes.begin();i!=codes.end();++i, ++k) {
        req->codes[k] = *i;
    }
    req->code_count = codes.size();
    return vx_issue_request((vx_req_base_t *)req);
}

int RequestManager::req_ResetPassword(const std::string server, const std::string uri, const std::string email)
{
    //int ret = -1;
    vx_req_aux_reset_password_t *req = NULL;
    vx_req_aux_reset_password_create(&req);
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    req->user_uri = vx_strdup(uri.c_str());
    req->user_email = vx_strdup(email.c_str());
    req->server_url = vx_strdup(server.c_str());
    return vx_issue_request((vx_req_base_t *)req);
}

int RequestManager::req_CreateAccount(const std::string &adminAcct, const std::string &adminPassword, const std::string &grantDocument, 
                                      const std::string &username, const std::string &password, const std::string &serverUrl)
{
    //int ret = -1;
    vx_req_aux_create_account_t *req = NULL;
    vx_req_aux_create_account_create(&req);
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    if(!adminAcct.empty()) {
        req->credentials.admin_username = vx_strdup(adminAcct.c_str());
        req->credentials.admin_password = vx_strdup(adminPassword.c_str());
    } else {
        req->credentials.grant_document = vx_strdup(grantDocument.c_str());
    }
    req->credentials.server_url = vx_strdup(serverUrl.c_str());
    req->user_name = vx_strdup(username.c_str());
    req->password = vx_strdup(password.c_str());
    return vx_issue_request((vx_req_base_t *)req);
}
int RequestManager::req_StateDump()
{
    vx_req_aux_diagnostic_state_dump_t *req = NULL;
    vx_req_aux_diagnostic_state_dump_create(&req);
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    return vx_issue_request((vx_req_base_t *)req);
}

int RequestManager::req_WebCall(const std::string &accountHandle, const std::string &relativePath, const std::vector<std::string> &parameters)
{
    vx_req_account_web_call_t *req = NULL;
    vx_req_account_web_call_create(&req);
    req->account_handle = vx_strdup(accountHandle.c_str());
    req->relative_path = vx_strdup(relativePath.c_str());
    req->parameter_count = parameters.size();
    vx_name_value_pairs_create(req->parameter_count, &req->parameters);
    for(int i=0;i<req->parameter_count;++i) {
        vx_name_value_pair_create(&req->parameters[i]);
        std::string name;
        std::string value;
        size_t pos = parameters.at(i).find("=");
        if(pos == string::npos) {
            name = parameters.at(i);
        } else {
            name = parameters.at(i).substr(0, pos);
            value = parameters.at(i).substr(pos+1);
        }
        req->parameters[i]->name = vx_strdup(name.c_str());
        req->parameters[i]->value = vx_strdup(value.c_str());
    }

    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    return vx_issue_request((vx_req_base_t *)req);

}

int RequestManager::req_RenderAudioModify(const std::string &fontstr)
{
    vx_req_aux_render_audio_modify * req = NULL;
    vx_req_aux_render_audio_modify_create(&req);
    req->font_str = vx_strdup(fontstr.c_str());
    req->base.cookie = vx_strdup(stateMgr->GenerateID().c_str());
    return vx_issue_request((vx_req_base_t *)req);
}

int RequestManager::req_enableVVS(const std::string &host, int port)
{
    VX_SDK_HANDLE h;
    int status = vx_alloc_sdk_handle(host.c_str(), port, &h);
    if(!status)
        stateMgr->set_SdkHandle(h);
    return status;
}

int RequestManager::req_disableVVS()
{
    int status = vx_free_sdk_handle(stateMgr->get_SdkHandle());
    if(!status)
        stateMgr->set_SdkHandle(0);
    return status;
}

int RequestManager::vx_issue_request(vx_req_base_t *r)
{
    r->message.sdk_handle = stateMgr->get_SdkHandle();
    return ::vx_issue_request(r);
}

