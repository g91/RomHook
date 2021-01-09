
#include "ParticipantState.h"

//////////////////////////////////////////////

ParticipantGroup::ParticipantGroup()
{
}

ParticipantGroup::~ParticipantGroup()
{
	ClearAll();
}

void ParticipantGroup::ClearAll()
{
	m_mapURI2Obj.clear();
	m_mapDBid2URI.clear(); // for zS
}

unsigned int ParticipantGroup::GetSize()
{
	return m_mapURI2Obj.size();
}

// GKy 091222, from VxSession::partInsert
void ParticipantGroup::InsertState(ParticipantState& p)
{
	m_mapURI2Obj[ p.uri ] = p;
	m_mapDBid2URI[ atoi(p.display_name.c_str()) ] = p.uri; // for zS
}

int ParticipantGroup::RemoveStateByUri(const char* uri)
{
	std::string str_temp = uri;

	std::map<std::string, ParticipantState>::iterator iterObj = m_mapURI2Obj.find(str_temp);
	if (iterObj != m_mapURI2Obj.end())
    {
		// for zS, Need clear another map
		int DBid = atoi(iterObj->second.display_name.c_str());
		std::map<int, std::string>::iterator iterUri = m_mapDBid2URI.find(DBid);
		if (iterUri != m_mapDBid2URI.end())
        {
			m_mapDBid2URI.erase(iterUri);
		}
		m_mapURI2Obj.erase(iterObj);
	}

	return 1;
}

ParticipantState ParticipantGroup::GetStateByUri(const char* uri)
{
	std::string str_temp;

	std::map<std::string, ParticipantState>::iterator iterObj;
	ParticipantState p;
	p.uri = "";

	str_temp = uri;
	iterObj = m_mapURI2Obj.find(str_temp);
	if (iterObj != m_mapURI2Obj.end())
    {
		p = iterObj->second;
		return p;
	}

	return p;
}

int ParticipantGroup::SetState(ParticipantState& p)
{
	InsertState(p);
	return 0;
}

std::string ParticipantGroup::GetUriByDBID(int DBid)
{
	std::map<int, std::string>::iterator iter = m_mapDBid2URI.find(DBid);
	if (iter != m_mapDBid2URI.end())
    {
		return (iter->second);
	}
    return ""; 
}

bool ParticipantGroup::CheckUriExistByDBID( int DBid )
{
    std::map<int, std::string>::iterator iter = m_mapDBid2URI.find(DBid);
	if (iter != m_mapDBid2URI.end())
    {
		return true;
	}
	return false;
}

int ParticipantGroup::CheckMuteByDBID(int DBid)
{
	int ret = 0;

    std::map<int, std::string>::iterator iterUri = m_mapDBid2URI.find(DBid);
	if (iterUri != m_mapDBid2URI.end())
    {
		// Need hash again to get Real Partner data
		std::map<std::string, ParticipantState>::iterator iterObj;
		iterObj = m_mapURI2Obj.find(iterUri->second);
		if (iterObj != m_mapURI2Obj.end())
        {
			//return it->second.is_audio_muted_for_me;
			ret = iterObj->second.audio_muted_for_me;
		}
	}

	return ret;
}

int ParticipantGroup::CheckSpeakingByDBID(int DBid)
{
	int ret = 0;

	std::map<int, std::string>::iterator iterUri = m_mapDBid2URI.find(DBid);
	if (iterUri != m_mapDBid2URI.end())
    {
		// Need hash again to get Real Partner data
		std::map<std::string, ParticipantState>::iterator iterObj;
		iterObj = m_mapURI2Obj.find(iterUri->second);
		if (iterObj != m_mapURI2Obj.end())
        {
			ret = iterObj->second.speaking;
		}
	}

	return ret;
}
