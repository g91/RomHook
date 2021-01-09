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

#include <string>
#include <ostream>
#include <fstream>
#include <VxcRequests.h>
#include <VxcResponses.h>
#include <VxcEvents.h>

class StateManager;
class RequestManager;
class ResponseManager
{
public:
    static std::string CreateTimeStamp( bool bShowSecond = true, bool bShowMin = true, bool bShowHour = true,
                                        bool bShowDay = true, bool bShowMonth = true, bool bShowYear = true);
    static void CreateFolder(std::string);

    ResponseManager(std::ostream &stdcout, std::ostream &stdcerr, StateManager *stateMgr, RequestManager *reqMgr);
    ~ResponseManager();
    void ProcessMessage(vx_message_base_t *msg);
   
public:
    void WriteResponseToFile(vx_resp_base_t*);
    void WriteEventToFile(vx_evt_base_t*);
    void WriteLogCallbackToFile(const char*);
    void SetDebug(int);
    void OpenCallBackFile();

    // Response methods.  These are called to handle the appropriate Response.
    void resp_ConnectorCreate(vx_resp_connector_create_t*);                 //required for state mgmt
    void resp_ConnectorShutdown(vx_resp_connector_initiate_shutdown_t*);    //required for state mgmt
    void resp_ChannelCreate(vx_resp_account_channel_create_t*);
    void resp_ChannelFavSet(vx_resp_account_channel_favorite_set_t*);
    void resp_ChannelFavGroupSet(vx_resp_account_channel_favorite_group_set_t*);
    void resp_NetworkTest(vx_resp_aux_connectivity_info_t*);
    void resp_ListRenderDevices(vx_resp_aux_get_render_devices_t* respObj);
    void resp_ListCaptureDevices(vx_resp_aux_get_capture_devices_t* respObj);
    void resp_GetSessionFonts(vx_resp_account_get_session_fonts_t* respObj);
    void resp_GetTemplateFonts(vx_resp_account_get_template_fonts_t* respObj);
    void resp_GetVadProperties(vx_resp_aux_get_vad_properties_t* respObj);
    //void resp_AddUserFont(vx_resp_account_add_user_font_t* respObj);
    void resp_ListAutoAcceptRules(vx_resp_account_list_auto_accept_rules_t *respObj);
    void resp_ListBlockRules(vx_resp_account_list_block_rules_t *respObj);
    void resp_CaptureAudioStop(vx_resp_aux_capture_audio_stop_t *respObj);
    void resp_State(vx_resp_aux_diagnostic_state_dump_t *respObj);
    void resp_AudioInfo(vx_resp_connector_get_local_audio_info_t *respObj);
    void resp_ChannelGetParticipants(vx_resp_account_channel_get_participants *respObj);

	void resp_LocalUserMute(vx_resp_session_set_participant_mute_for_me_t *respObj); // GKy 100105

	void resp_GetMicLevel(vx_resp_aux_get_mic_level_t *respObj); // GKy 100114

    // Events
    void evt_Generic(vx_evt_base_t*);
    void evt_AccountLoginStateChange(vx_evt_account_login_state_change_t*);
    void evt_SessionGroupAdded(vx_evt_sessiongroup_added_t*);
    void evt_SessionGroupRemoved(vx_evt_sessiongroup_removed_t*);
    void evt_SessionGroupUpdated(vx_evt_sessiongroup_updated_t*);
    void evt_SessionAdded(vx_evt_session_added_t*);
    void evt_SessionRemoved(vx_evt_session_removed_t*);
    void evt_SessionUpdated(vx_evt_session_updated_t*);
    void evt_MediaStreamUpdated(vx_evt_media_stream_updated_t*);
    void evt_TextStreamUpdated(vx_evt_text_stream_updated_t*);
    void evt_MediaCompleted(vx_evt_media_completion_t*);

    void evt_Message(vx_evt_message_t*);
    void evt_NetworkMessage(vx_evt_network_message_t*);
    void evt_BuddyPresenceChange(vx_evt_buddy_presence_t* evtObj);
    void evt_BuddyChanged(vx_evt_buddy_changed_t *evtObj);
    void evt_BuddyGroupChanged(vx_evt_buddy_group_changed_t *evtObj);
    void evt_AuxAudioProperties(vx_evt_aux_audio_properties_t* evtObj);
	void evt_ParticipantUpdated(vx_evt_participant_updated_t* evtObj); // GKy 091216
	void evt_ParticipantAdded(  vx_evt_participant_added_t*   evtObj); // GKy 091221
	void evt_ParticipantRemoved(vx_evt_participant_removed_t* evtObj); // GKy 091221

    void evt_Subscription(vx_evt_subscription_t *evtObj);

    void Stop(bool waitForShutdown);
    bool IsStopped() const;
    static std::string FormatXml(const std::string &);
    void WriteToFile(const char*);
    void WriteToCallBackFile(const char* msg);

private:
    int debuglevel;
    bool stopOnShutdownResponse;
    bool stopNow;
    bool quickTestMode;
    std::string quickTestUserName;  //for "quicktest" only
    std::string quickTestUserPW;    //for "quicktest" only
    std::string quickTestURI;       //for "quicktest" only

    StateManager * stateMgr;
    RequestManager *m_reqMgr;
    std::ostream &cout;
    std::ostream &cerr;
    std::ofstream logFile;
    std::ofstream callbackLogFile;
};
