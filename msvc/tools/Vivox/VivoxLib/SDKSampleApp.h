#pragma once
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
#include <vector>
#include <sstream>
#include "vxplatform/vxcplatform.h"

class RequestManager;
class ResponseManager;
class CommandHandler;
class StateManager;

#include <boost/function.hpp> // boost::func
//typedef void (* pf_console_output_t)(void *handle, const char *);
typedef boost::function<void (void*, const char*)> VivoxConsoleOutputCallback;

class SDKSampleApp
{
public:
    SDKSampleApp(VivoxConsoleOutputCallback stdcout, VivoxConsoleOutputCallback stdcerr, void *handle, int argc, char *argv[]);
    ~SDKSampleApp();
    bool ProcessCommand(const std::vector<std::string> &cmd);
    void Shutdown();

    //////////////////////////////////////////////////////////////////////////

	inline StateManager*    GetStateManager() { return stateMgr; }
	inline RequestManager*  GetRequestManager() { return reqMgr; }
	inline ResponseManager* GetResponseManager() { return respMgr; }

protected:

private:
    static vxplatform::os_error_t ListenerThread(void *arg);        //For catching Reponses and Events
    void ListenerThread();

    vxplatform::os_thread_handle    m_hListenerThread;

    vxplatform::os_event_handle listenerThreadTerminatedEvent;
    StateManager * stateMgr;                //Keeps track of state for requests/reponses/objects
    RequestManager * reqMgr;                //Handles all out-going Requests
    ResponseManager * respMgr;                //Handles all incoming Responses and Events
    CommandHandler *cmdHandler;
    bool quickTestMode;        //for "quicktest" only
    std::string quickTestUserName;  //for "quicktest" only
    std::string quickTestUserPW;    //for "quicktest" only
    std::string quickTestURI;       //for "quicktest" only
    std::stringstream cout;
    std::stringstream cerr;
    std::stringstream responseCout;
    std::stringstream responseCerr;
    void *m_ioHandle;

    VivoxConsoleOutputCallback  m_writeCout;
    VivoxConsoleOutputCallback  m_writeCerr;

    int             m_iVVXstate;
};
