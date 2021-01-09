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

#ifndef __SESSIONSTATE_H
#define __SESSIONSTATE_H

#include <map>
#include <set>
#include <string>
#include "Vxc.h"

#include "ParticipantState.h" // GKy 091209

class VxSession
{
private:
    std::string sessionHandle;
    std::string sessionUri;
    vx_session_media_state mediaState;
    vx_session_text_state textState;
    bool incoming;
    bool isTransmitting;
    bool isFocused;
    int volume;
    bool isMuted;
    bool isTextMuted;
    int fontID;

    //stores participants handles and corresponding states
    std::map<std::string, ParticipantState> m_mapParticipantStates; // <uri, obj>

public:
    VxSession(const std::string &session_handle, const std::string &uri);
    ~VxSession();
    const std::string &GetSessionHandle() const;
    const std::string &GetSessionURI() const;
    vx_session_media_state GetMediaState() const;
    void SetMediaState(vx_session_media_state state);
    vx_session_text_state GetTextState() const;
    void SetTextState(vx_session_text_state state);
    bool GetIsIncoming() const;
    void SetIsIncoming(bool state);
    bool GetIsTransmitting() const;
    void SetIsTransmitting(bool state);
    void SetIsFocused(bool state);
    bool GetIsFocused() const;
    void SetVolume(int vol);
    int GetVolume() const;
    void SetIsMuted(bool muted);
    bool GetIsMuted() const;
    void SetIsTextMuted(bool textmuted);
    bool GetIsTextMuted() const;
    void SetFontID(int font_id);
    int GetFontID() const;

	void InsertState(ParticipantState& p);
	int RemoveState(const char* uri);
};

#endif
