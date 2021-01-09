#pragma once 
#include <vector>
#include <string>
#include "ObjectStructEx.h"
#include "RoleBaseDef.h"

class CampStatuteClass
{
	vector< string >	_CampName;
	GameCampTypeENUM	_CampStatute[ _MAX_CAMP_COUNT_ ][ _MAX_CAMP_COUNT_ ];

public:
	void Init( GameObjDbStructEx*	ObjDB );
	
	vector< string >*	CampName();
	
	//�]�w������Y
	void	CampStatute( int CampA , int CampB , GameCampTypeENUM Type );

	//���������t
	GameCampTypeENUM	CampStatute( int CampA , int CampB );

	bool	IsEnemy( int CampA , int CampB );
	bool	IsCanAttack( int CampA , int CampB );
	bool	IsCanHelp( int CampA , int CampB );
	bool	IsCanAttck( int CampA , int CampB );
	bool	IsFriend( int CampA , int CampB );

	//���o�}�窺���X
	CampID_ENUM		GetCampID( const char* CampName );
};