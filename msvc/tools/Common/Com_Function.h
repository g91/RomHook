/*
----------------------------------------------------------------------
	filename: 	Com_Function.h
    created:	2007/9/17
	author:		Xun
	
	purpose:	?


----------------------------------------------------------------------
*/



#pragma once

#include <windows.h>
#include <string>

using namespace std;

//類似 sprintf 只是將字串回傳出來
//方便輸出 額外訊息
//字串長度限制MAX_PATH
//注意回傳的字串必須馬上使用不可保留
char* Com_FormatString( LPCSTR szFormat , ... ) ;


/************************************************************************/
/* 替代字串                                                             */
// inString		原始字串
// keyString	搜尋替換字串
// valueString	替換新字串
/************************************************************************/
string ReplaceKeyString(string inString, const string& keyString, const string& valueString);

string ReplaceKeyString(string inString, const string& keyString, int number);





