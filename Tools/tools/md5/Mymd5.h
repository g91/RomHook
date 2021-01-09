#pragma  once
#include "md5.h"
#include <string>
using namespace std;
/////////////////////////////////////DataBase_GlobalDataBase_Global/////////////////////////////////////
//Â²¤ÆMD5³B²z
//////////////////////////////////////////////////////////////////////////
class MyMD5Class
{
	char		_MD5Str[33];
	const char*	_ComputeStringHash( const char* Str , const char* XorStr );
	const char*	_ComputeFileHash( const char* FileName );

public:
	MyMD5Class() { m_pwSummands = NULL; }

	void		Init();
	void		Release();

	const char*	ComputeStringHash( const char* Str , const char* XorStr = NULL );
	const char*	ComputeFileHash( const char* FileName );
	const char*	GetMd5Str(){ return _MD5Str; };

	MD5_WORD *m_pwSummands;
};
//////////////////////////////////////////////////////////////////////////