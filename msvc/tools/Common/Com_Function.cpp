
#include "Com_Function.h"


#include <stdio.h>

#define DF_StringArrayCount 10 

LPSTR Com_GetStaticString()
{
	static char  strArray[DF_StringArrayCount][512] ;
	static DWORD dwNum = 0 ; //目前用到哪一個字串

	if( dwNum >= DF_StringArrayCount )
		dwNum = 0 ;

	return strArray[dwNum++] ;
}

//類似 sprintf 只是將字串回傳出來
//方便輸出 額外訊息

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












