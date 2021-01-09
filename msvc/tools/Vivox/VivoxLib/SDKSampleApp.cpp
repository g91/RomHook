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

#ifndef _WIN32
#ifdef SN_TARGET_PS3
#include <sys/timer.h>
#define Sleep(k) sys_timer_usleep(k*1000);
#else
#define Sleep(k) usleep(k * 1000)
#endif
#endif

#include "SDKSampleApp.h"
#include <stdio.h>
#if defined (__linux__)
#include <stdlib.h>
#endif
#include <vector>
#include <deque>
#include <iostream>

#include "usage.h"
#include "StateManager.h"
#include "RequestManager.h"
#include "ResponseManager.h"
#include "vxplatform/vxcplatform.h"
#include "CommandHandler.h"

using namespace std;
using namespace vxplatform;

#include "../VivoxClient.h"

SDKSampleApp::SDKSampleApp(VivoxConsoleOutputCallback writeCout, VivoxConsoleOutputCallback writeCerr, void *ioHandle, int argc, char *argv[])
: m_writeCout(writeCout),
  m_writeCerr(writeCerr),
  m_hListenerThread(NULL)
{
    quickTestMode = false;
    m_ioHandle = ioHandle;

	m_iVVXstate = VVX_STATE_IDLE; // GKy 091228

    /* Debug modes:
    0 - None (default)
    1 - Logs only
    2 - Handles on stdout, Logs
    3 - Handles on stdout, Logs, Responses and Events on stdout */
    int debugval = 0; //2; // GKy 091225
    if (argc >= 2)
    {
        debugval = atoi(argv[1]);
    }

    stateMgr = new StateManager();
    reqMgr = new RequestManager(cout, cerr, stateMgr);    
    respMgr = new ResponseManager(responseCout, responseCerr, stateMgr, reqMgr);
    cmdHandler = new CommandHandler(cout, cerr, reqMgr, respMgr, stateMgr);

    reqMgr->SetDebug(debugval);
    respMgr->SetDebug(debugval);

    if (argc >= 3)      //This block is for "quicktest" only
    {
        string flag(argv[2]);
        if (flag == "quicktest")
        {
            quickTestMode = true;
            stringstream ss;
            ss << argv[4];
            quickTestUserName = ss.str();
            ss.str("");
            ss << argv[5];
            quickTestUserPW = ss.str();
            ss.str("");
            ss << argv[6];
            quickTestURI = ss.str();
            reqMgr->req_ConnectorCreate(argv[3],0,0);
        }
    }

    //os_thread_handle listenerThread;

    vxplatform::os_error_t error_code = vxplatform::create_event(&listenerThreadTerminatedEvent);
#ifdef SN_TARGET_PS3
    error_code = vxplatform::create_thread(&SDKSampleApp::ListenerThread, this, &m_hListenerThread, 0, 1001);
#else
    error_code = vxplatform::create_thread(&SDKSampleApp::ListenerThread, this, &m_hListenerThread);
#endif

    std::ostringstream oss;
    if (m_hListenerThread == NULL)
    {
        oss << "Unable to spawn listener thread." << endl;
    }

    oss << "SDKSampleApp          COPYRIGHT 2007-2009 VIVOX INC." << endl << endl;
    oss << "Type 'help' for a full list of available commands." << endl << endl;
    //(* writeCout)(ioHandle, ss.str().c_str());
    writeCout(ioHandle, oss.str().c_str());
}

SDKSampleApp::~SDKSampleApp()
{
    if (m_hListenerThread != NULL)
    {
        vxplatform::os_error_t error_code = vxplatform::delete_thread(m_hListenerThread); // cannot delete after close.
        //error_code = vxplatform::close_thread_handle(m_hListenerThread); // cannot close after delete.
        m_hListenerThread = NULL;
    }

    delete stateMgr;
    delete reqMgr;
    delete respMgr;
    delete cmdHandler;
}

extern "C" {
    void VIVOXSDK_DLLEXPORT vx_on_application_exit();
}
        
void SDKSampleApp::Shutdown()
{
    OutputDebugString(_T("SDKSampleApp::Shutdown()\n"));

    bool shutdown = false;
    if (stateMgr->GetIsConnectorInitialized())
    {
        shutdown = true;
        reqMgr->req_ConnectorShutdown(stateMgr->GetConnectorHandle());
        stateMgr->SetConnectorUninitialized();
    }

    respMgr->Stop(shutdown);

    cout << "Quitting.\n";

    if(wait_event(listenerThreadTerminatedEvent, 30000)) {
        cout << "Timed out waiting for listener thread to terminate." << endl;
    } else {
        os_error_t error_code = delete_event(listenerThreadTerminatedEvent); // try to delete when shutdown
        vx_on_application_exit();
    }
}

bool SDKSampleApp::ProcessCommand(const std::vector<std::string> &cmd)
{
    if(cmd.at(0) == "q") {
        Shutdown();
        return false;
    }
    if (cmd.at(0).find("//") == 0 ) {
        return true;
    }
    std::vector<std::vector<std::string> > cmds;
    std::vector<std::string> c;
    for(std::vector<std::string>::const_iterator i = cmd.begin();i!=cmd.end();++i)
    {
        if(*i == ";") {
            if(!c.empty())
                cmds.push_back(c);
            c.clear();
        } else {
            c.push_back(*i);
        }
    }
    if(!c.empty())
        cmds.push_back(c);

    bool quit = true;
    for(std::vector<std::vector<std::string> >::const_iterator i = cmds.begin();i!=cmds.end();++i) {
        cout.str("");
        cerr.str("");
        if(!i->empty() && i->at(0) == "q") {
           Shutdown();
           quit &= false;
        }
        Disposition disposition = cmdHandler->Execute(*i);
        if(!cout.str().empty())
            m_writeCout(m_ioHandle, cout.str().c_str());
        if(!cerr.str().empty())
            m_writeCerr(m_ioHandle, cerr.str().c_str());
        if(disposition == DispositionQuit)
            quit &= false;
    }
    return quit;
}

static void OnMessage(void *callbackData)
{
    os_event_handle responseHandle = reinterpret_cast<os_event_handle>(callbackData);
    set_event(responseHandle);
}

// Pulls a message from the queue.  If no message found, waits until notified, then tries again.
// Type of the message, and then type of the Event or Response is discovered, and the
// appropriate call is made to process that message type.
os_error_t SDKSampleApp::ListenerThread(void *arg)
{
    SDKSampleApp *pThis = reinterpret_cast<SDKSampleApp *>(arg);
    pThis->ListenerThread();
    return 0;
}

void SDKSampleApp::ListenerThread()
{
    os_event_handle responseHandle;
    create_event(&responseHandle);
    vx_register_message_notification_handler(OnMessage, responseHandle);
    for (;!respMgr->IsStopped();) {
        vx_message_base_t* basemsg = NULL;
        int ret = vx_get_message(&basemsg);            //Pull a message from the queue
        if(ret == 0) {
            responseCout.str("");
            responseCerr.str("");
            respMgr->ProcessMessage(basemsg);
            if(!responseCout.str().empty())
                m_writeCout(m_ioHandle, responseCout.str().c_str());
            if(!responseCerr.str().empty())
                m_writeCerr(m_ioHandle, responseCerr.str().c_str());

            continue;
        } else {
            wait_event(responseHandle, 200);
        }
    }
    vxplatform::set_event(listenerThreadTerminatedEvent);
    vx_unregister_message_notification_handler(OnMessage, NULL);
}



