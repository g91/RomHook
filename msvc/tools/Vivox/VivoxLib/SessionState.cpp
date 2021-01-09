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

#include "SessionState.h"

using namespace std;

VxSession::VxSession(const string &session_handle, const string &uri)
{
    sessionHandle = session_handle;
    sessionUri = uri;
    incoming = false;
    mediaState = session_media_none; //session_media_disconnected; // note : do not change this value. (by slime)
    textState = session_text_disconnected;
    isTransmitting = false;
    isFocused = false;
    volume = 50;
    isMuted = false;
    isTextMuted = false;
    fontID = 0;
}

VxSession::~VxSession()
{
}

const string &VxSession::GetSessionHandle() const
{
    return sessionHandle;
}

const string &VxSession::GetSessionURI() const
{
    return sessionUri;
}

vx_session_media_state VxSession::GetMediaState() const
{
    return mediaState;
}

void VxSession::SetMediaState(vx_session_media_state state)
{
    mediaState = state;
}

vx_session_text_state VxSession::GetTextState() const
{
    return textState;
}

void VxSession::SetTextState(vx_session_text_state state)
{
    textState = state;
}

bool VxSession::GetIsIncoming() const
{
    return incoming;
}

void VxSession::SetIsIncoming(bool state)
{
    incoming = state;
}

bool VxSession::GetIsTransmitting() const
{
    return isTransmitting;
}

void VxSession::SetIsTransmitting(bool state)
{
    isTransmitting = state;
}

bool VxSession::GetIsFocused() const
{
    return isFocused;
}

void VxSession::SetIsFocused(bool state)
{
    isFocused = state;
}

int VxSession::GetVolume() const
{
    return volume;
}

void VxSession::SetVolume(int vol)
{
    volume = vol;
}

bool VxSession::GetIsMuted() const
{
    return isMuted;
}

void VxSession::SetIsMuted(bool muted)
{
    isMuted = muted;
}

bool VxSession::GetIsTextMuted() const
{
    return isTextMuted;
}

void VxSession::SetIsTextMuted(bool textmuted)
{
    isTextMuted = textmuted;
}

int VxSession::GetFontID() const
{
    return fontID;
}

void VxSession::SetFontID(int font_id)
{
    fontID = font_id;
}

void VxSession::InsertState(ParticipantState& p)
{
	m_mapParticipantStates[ p.uri ] = p;
}

int VxSession::RemoveState(const char* uri)
{
	std::string str_temp = uri;
	std::map<std::string, ParticipantState>::iterator iter = m_mapParticipantStates.find(str_temp);
	if (iter != m_mapParticipantStates.end())
    {
		m_mapParticipantStates.erase(iter);
	}
	return 1;
}
