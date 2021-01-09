
#include "Com_Function.h"


#include <stdio.h>

#define DF_StringArrayCount 10 

LPSTR Com_GetStaticString()
{
	static char  strArray[DF_StringArrayCount][512] ;
	static DWORD dwNum = 0 ; //�ثe�Ψ���@�Ӧr��

	if( dwNum >= DF_StringArrayCount )
		dwNum = 0 ;

	return strArray[dwNum++] ;
}

//���� sprintf �u�O�N�r��^�ǥX��
//��K��X �B�~�T��

char* Com_FormatString( LPCSTR szFormat , ... )
{
	va_list argList;
	va_start( argList , szFormat );

	int nLength = _vscprintf( szFormat, argList );
	if( nLength >= MAX_PATH ) 
		return NULL;

	LPSTR pString = Com_GetStaticString() ;

	vsprintf( pString , szFormat , argList );
	va_end( argList );

	return pString;
}

string ReplaceKeyString(string inString, const string& keyString, const string& valueString)
{
	size_t begin;
	while ( (begin = inString.find(keyString)) != string::npos )
		inString.replace(begin, keyString.size(), valueString);
	return inString;
}


string ReplaceKeyString(string inString, const string& keyString, int number)
{
	return ReplaceKeyString( inString, keyString, Com_FormatString( "%d" , number ) );
}












