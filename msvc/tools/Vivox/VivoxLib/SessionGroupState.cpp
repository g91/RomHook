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

#include "SessionGroupState.h"

using namespace std;

VxSessionGroup::VxSessionGroup(string session_group_handle)
{
    sessionGroupHandle = session_group_handle;
}

VxSessionGroup::~VxSessionGroup()
{
    map<string,VxSession*>::const_iterator itr;
    for (itr = sessions.begin(); itr != sessions.end(); ++itr)
    {
        VxSession* tmpSession = itr->second;
        delete tmpSession;
    }
    sessions.clear();
}

void VxSessionGroup::AddSession(string session_handle, string uri, int incoming)
{
    VxSession* s = new VxSession(session_handle, uri);
    s->SetIsIncoming(incoming ? true : false);
    this->sessions.insert(make_pair(session_handle,s));
}

void VxSessionGroup::RemoveSession(string session_handle)
{
    map<string,VxSession*>::const_iterator itr;
    itr = sessions.find(session_handle);
    if (itr != sessions.end())
    {
        VxSession* tmpSession = itr->second;
        sessions.erase(session_handle);
        delete tmpSession;
    }
}

void VxSessionGroup::UpdateSession(string session_handle, int tx, int focus, int muted, int textmuted, int font_id, int vol)
{
    map<string,VxSession*>::const_iterator itr;
    itr = sessions.find(session_handle);
    if (itr != sessions.end())
    {
        VxSession* sess = itr->second;
        sess->SetIsTransmitting(tx == 1 ? true : false);
        sess->SetIsFocused(focus == 1 ? true : false);
        sess->SetIsMuted(muted == 1 ? true : false);
        sess->SetIsTextMuted(textmuted == 1 ? true : false);
        sess->SetFontID(font_id);
        sess->SetVolume(vol);
    }
}

void VxSessionGroup::UpdateMediaState(string session_handle, vx_session_media_state state)
{
    map<string,VxSession*>::const_iterator itr;
    itr = sessions.find(session_handle);
    if (itr != sessions.end())
    {
        VxSession* sess = (VxSession*)itr->second;
        sess->SetMediaState(state);
    }
}

void VxSessionGroup::UpdateTextState(string session_handle, vx_session_text_state state)
{
    map<string,VxSession*>::const_iterator itr;
    itr = sessions.find(session_handle);
    if (itr != sessions.end())
    {
        VxSession* sess = (VxSession*)itr->second;
        sess->SetTextState(state);
    }
}

set<string> VxSessionGroup::GetSessionHandles()
{
    set<string> handles;
    map<string,VxSession*>::const_iterator itr;
    for (itr = sessions.begin(); itr != sessions.end(); ++itr)
    {
        handles.insert(itr->first);
    }
    return handles;
}

VxSession* VxSessionGroup::GetSession(string session_handle)
{
    map<string,VxSession*>::const_iterator itr;
    itr = sessions.find(session_handle);
    if (itr != sessions.end())
        return itr->second;
    else
        return NULL;
}

string VxSessionGroup::GetSessionGroupHandle()
{
    return sessionGroupHandle;
}

int VxSessionGroup::GetNumberOfSessions()
{
    return this->sessions.size();
}
