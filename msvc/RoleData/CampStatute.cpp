#include "CampStatute.h"
#include "ObjectStructEx.h"
#include <string.h>

void CampStatuteClass::Init( GameObjDbStructEx*	ObjDB )
{
	memset( &_CampStatute , 0 , sizeof( _CampStatute ) );
	_CampName.clear();

	for( int i = 0 ; i < _MAX_CAMP_COUNT_ ; i++ )
	{
		if( strlen( ObjDB->Camp.CampName[i] ) <= 1 )
			break;

		_CampName.push_back( ObjDB->Camp.CampName[i] );
	}

	for( int i = 0 ; i < (int)_CampName.size() ; i++ )
		for( int j = 0 ; j < (int)_CampName.size() ; j++ )
		{
			_CampStatute[i][j] = (GameCampTypeENUM)ObjDB->Camp.CampInfo[i][j];
		}
}

vector< string >*	CampStatuteClass::CampName()
{ 
	return &_CampName; 
};

//設定兩者關係
void	CampStatuteClass::CampStatute( int CampA , int CampB , GameCampTypeENUM Type )
{
	_CampStatute[ CampA ][ CampB ] = Type;
}

//比較兩者關系
GameCampTypeENUM	CampStatuteClass::CampStatute( int CampA , int CampB )
{
	return _CampStatute[ CampA ][ CampB ];
}

bool	CampStatuteClass::IsCanAttack( int CampA , int CampB )
{
	GameCampTypeENUM Type = CampStatute( CampA , CampB );

	if(		EM_GameCampType_Enemy == Type 
		||	EM_GameCampType_Neutrality == Type )
		return true;

	return false;
}

bool	CampStatuteClass::IsEnemy( int CampA , int CampB )
{
	GameCampTypeENUM Type = CampStatute( CampA , CampB );

	if( EM_GameCampType_Enemy == Type )
		return true;

	return false;
}

bool	CampStatuteClass::IsFriend( int CampA , int CampB )
{
	GameCampTypeENUM Type = CampStatute( CampA , CampB );

	if(		EM_GameCampType_Friend == Type 
		||  EM_GameCampType_Alliance == Type )
		return true;

	return false;
}

bool	CampStatuteClass::IsCanHelp( int CampA , int CampB )
{
	GameCampTypeENUM Type = CampStatute( CampA , CampB );

	if(		EM_GameCampType_Enemy == Type 
		||	EM_GameCampType_Neutrality == Type  )
		return false;

	return true;
}

bool	CampStatuteClass::IsCanAttck( int CampA , int CampB )
{
	GameCampTypeENUM Type = CampStatute( CampA , CampB );

	if(		EM_GameCampType_Alliance == Type )
		return false;

	return true;
}

CampID_ENUM		CampStatuteClass::GetCampID( const char* CampName )
{
	for( int i = 0 ; i < (int)_CampName.size() ; i++ )
	{
		if( stricmp( CampName , _CampName[i].c_str() ) == 0 )
			return (CampID_ENUM)i;
	}

	return EM_CampID_Unknow;
}