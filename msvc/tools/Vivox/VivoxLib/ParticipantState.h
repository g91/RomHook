/*************************************************************************************\
Class: ParticipantState

Usage: store temporary data for vivox SDK using;

LOG:
	GKy 091209 start

\*************************************************************************************/

#pragma once

#ifndef __PARTICIPANTSTATE_H
#define __PARTICIPANTSTATE_H

#include <map>
//#include <set>
#include <string>
#include <Vxc.h>

//class ParticipantState;
//class ParticipantGroup;

//typedef std::map<int, std::string>  VVXtypeDBid2URI;

// One Partner state in a Voice Channel
//class ParticipantState
struct ParticipantState
{
    vx_participant_type vx_type;
	std::string     uri;              // viovx sys ID
	std::string     display_name;     // for store Our Game ID
    int             anonymous_login;
	int             audio_muted_for_me; // for zS check if this user LocalMute
	int             speaking;
	double          energy;

    ParticipantState()
    : vx_type(static_cast<vx_participant_type>(0)),
      uri(""),
      display_name(""),
      anonymous_login(0),
      audio_muted_for_me(0),
      speaking(0),
      energy(0.0)
    {
    }
};

//typedef std::map<std::string, ParticipantState> VVXtypePartner;

// A class to manage ALL ParticipantState in one Voice Channel
class ParticipantGroup
{
public:
	ParticipantGroup();
	~ParticipantGroup();

	void            ClearAll();
	unsigned int    GetSize();

	void            InsertState( ParticipantState& p );
	int             RemoveStateByUri( const char* uri );

	//ParticipantState  partGet( int DBid );
	ParticipantState    GetStateByUri( const char* uri );
	int             SetState( ParticipantState& p ); // GKy 100104, now share to partInsert..

	std::string     GetUriByDBID(int DBid);

    bool            CheckUriExistByDBID(int DBid);  // for zS
	int             CheckMuteByDBID(int DBid);      // for zS
	int             CheckSpeakingByDBID(int DBid);  // for zS

protected:

private:
    std::map<int, std::string> m_mapDBid2URI;               // <DBid, uri> for zS
    std::map<std::string, ParticipantState> m_mapURI2Obj;   // <uri, obj>

};

#endif // __PARTICIPANTSTATE_H