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

#ifndef __STATEMANAGER_H
#define __STATEMANAGER_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <sstream>
#include "SessionState.h"
#include "SessionGroupState.h"
#include "Vxc.h"
#include "VxcResponses.h"
#include "VxcEvents.h"
#include "math.h"

#include "../VivoxClient.h" // GKy 091211
#include "../../../mainproc/GameMain.h" // GKy 091223 for g_pGameMain and g_pInterface

//#define PI 3.1415926535897932384626433832795 // PI redefined - marked by slime 2010/08/02

#define STATE_UPDATE_MAX 10

class StateManager
{
		int stateUpdate; // GKy 091215 for poll state

        int guid;
        bool isConnectorInitialized;
        bool isAccountLoggedIn;
        std::string connectorHandle;
        std::string accountHandle;
		std::map<std::string,VxSessionGroup*> sessionGroups;        //stores session handles and corresponding states
        std::map<std::string,std::string> requests;                 //stores requestIDs and corresponding types
        int audioBufferGuid;
        std::map<std::string,void *> audioBuffers;                  //stores currently recorded 

        //positional info
        double listenerHeadingDegrees; // Listener's heading in degrees (North (Negative Z axis) is 0 deg, East (Positive X axis) is +90 deg etc)
        double listenerPosition[3];
        double listenerOrientation[6]; 

        //version info
        std::string version;

        // active handle for talking out of proc
        VX_SDK_HANDLE m_sdkHandle;
  public:
        StateManager();
        std::string GenerateID();
        
        static std::string GetTime();

        // Audio buffers managemement
        std::string GenerateAudioBufferId();
        std::string AddAudioBuffer(void *audioBufferPtr);
        void ListAudioBuffers(std::ostream *) const;
        void RemoveAudioBuffer(std::string audioBufferId);
        bool ExportAudioBufferToWav(std::string audioBufferId, std::string filePath);

        //Application state methods
        bool SetConnectorInitialized(std::string, std::string);
        void SetConnectorUninitialized();

        bool SetStateAccountLoggedIn(std::string account_handle);
        void SetStateAccountLoggedOut();

        bool AddSessionGroup(std::string session_group_handle);
        void RemoveSessionGroup(std::string session_group_handle);
        VxSessionGroup* GetSessionGroup(std::string session_group_handle);
        void ClearSessionGroups();

        bool AddSession(std::string session_group_handle, std::string session_handle, std::string uri, int incoming);
        void RemoveSession(std::string session_group_handle, std::string session_handle);
        void UpdateSession(std::string session_group_handle, std::string session_handle, int tx, int focus, int muted, int textmuted, int font_id, int vol);

        void UpdateMediaStreamState(std::string session_group_handle, std::string session_handle, vx_session_media_state state);
        void UpdateTextStreamState(std::string session_group_handle, std::string session_handle, vx_session_text_state state);

        //State info
        bool GetIsConnectorInitialized();
        bool GetIsAccountLoggedIn();
        std::string GetConnectorHandle();
        std::string GetAccountHandle();

        bool GetSessionGroupExists(std::string); // GKy 091211 improve
//      std::set<std::string> GetAllSessionGroupHandles();
        std::set<std::string> GetAllSessionGroupHandles(void); // GKy 091203 try implement
//      std::set<std::string> GetAllSessionHandles();
        std::set<std::string> GetAllSessionHandles(const char* sg_id_); // GKy 091204 try implement

        std::set<std::string> GetAllSessionPartnersURI(const char* sg_id_, const char* ss_id_); // GKy 091204 try 

        int GetMediaSessionState(std::string);
        int GetTextSessionState(std::string);

        //State info dump
		void DumpStateToFile(std::ostream*);
		void DumpState(std::ostream*); // GKy 091215

		//request map methods
        void InsertCommandReqID(std::string, std::string);
		void DeleteCommandReqID(std::string);
		int  GetNumOutStandingRequests();  // return the number of requests waiting on a response

        //positional info methods
        void GetListenerPosition(double *);
        void GetListenerOrientation(double *);
        void SetListenerPosition(double *);
        void SetListenerOrientation(double *);
        void GetListenerHeadingDegrees(double *);
        void SetListenerHeadingDegrees(double);

        VX_SDK_HANDLE get_SdkHandle() const { return m_sdkHandle; }
        void set_SdkHandle(VX_SDK_HANDLE value) { m_sdkHandle = value; }

		// GKy 091211 add for Transaction+++++++++++++++++++++++++++++++
		void txErr(int status_code, const char* status_string ); // GKy 091231

		//void txALL(VVX_STATE state_, const char* ChURI = NULL);
		void txALL(const char* ChURI = NULL);

		// GKy 100120 indeed below fnc seems meaningless?..
		//
		void txConnectorCreateOK(); //++
		void txShutDownOK(); //++

		void txChannelCreateOK( const char* ChURI ); //++

		void txSessionGroupAdded(); //++
		//void txSessionGroupUpdated();
		void txSessionConnected(); //++ ensure Session Add OK
		void txSessionConnectedHandle(); // GKy 100121 add

		void txSessionDisconnected(); // GKy 100106

		// RemoveOK, no handle!?..
		void txSessionRemoveOK(); // main for reJoin Handle. //-+
		void txSessionRemovedHandle(); // GKy 100128 add

		void txSessionMediaUpdate(); // Pool >state XXX, ---

		void txLoginOK(); // GKy 091217  //++
		//void txLoginAnyOK(); // GKy 091217  //
		void txLogOutOK(); // GKy 091216 //++

		/////////////////////////////////////////////////////////////////////
		//void txListCaptureDevs(); // indeed seems not need so comlex?..
		void txListDevs(); // indeed seems not need so comlex?..

};

#endif
