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

//���� sprintf �u�O�N�r��^�ǥX��
//��K��X �B�~�T��
//�r����׭���MAX_PATH
//�`�N�^�Ǫ��r�ꥲ�����W�ϥΤ��i�O�d
char* Com_FormatString( LPCSTR szFormat , ... ) ;


/************************************************************************/
/* ���N�r��                                                             */
// inString		��l�r��
// keyString	�j�M�����r��
// valueString	�����s�r��
/************************************************************************/
string ReplaceKeyString(string inString, const string& keyString, const string& valueString);

string ReplaceKeyString(string inString, const string& keyString, int number);





