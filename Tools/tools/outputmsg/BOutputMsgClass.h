// OutputMsgClass.h: interface for the OutputMsgClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_)
#define AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_
//===========================================================================================
//	��Class OutputMsgClass 
//*�ت� 
//		���F����T��Log��X��K�A�g�@�Ӱ򥻪�����B�z 
// 
//*�ݨD 
//  	�޲zLog��X�ɮסA�ù��A�P�O�_��X 
//
//*���ƨϥ� 
//		���Ӧ�����ݭnLog ��X�����n�ϥΦ�����A���~�Ӧ����� 
//
//*�D�n�� 
//
//��X�Φ� (type)<�ù���X�A�ɮ׿�X�A�ù��P�ɮ׿�X�A�@���T�w�q�g�X> 
//�T�w�q�g�X��Buf�j�p  (Size) 
//�}�� (filename) 
//���� () 
//�j���g�� () �]�w�h�[�j���x�s 
//�T����X (���e)  
//
//===========================================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
#include <stdio.h>
#include "IOutputMsg.h"

class BOutputMsgClass: public IOutputMsg
{
	FILE*	_File;

	char    _FileName[128];								//�ɮ�
	char    _TimePath[128];								//���|
	char    _FieldName[128];							//��X�ؿ�

	char	_Buf[2048];									//��ƼȦs��
	int		_OutputLevel;								//��X����
	int		_NextClostTime;								//�U���n�����ɮת��ɶ�

	bool _Open		(void);								//�}�ҭn�g�X���ɮ�
	bool _Close		(void);								//�����ɮ�

public:
	BOutputMsgClass();
	virtual ~BOutputMsgClass();

	void  FileName	(char *file);						//�]�w��X�ɮצW��
	char* FileName	(void);								//Ū����X�ɮצW��

	void  FiledName	(char* Path);						//�]�w��X�ؿ�

	void  OutputLV	(int LV);							//�]�w��X����(�]�w�h�֯ťH�W���~��X)

	bool Print		(int Lv,const char *format,...);	//��ܦb�ù��W
	bool Write		(int Lv,const char *format,...);	//�g�ɮ�
	void Flush		(void);								//�j��g�J�ɮ�

	void MakePath	(void);								//�]�w�ؿ�
	

};

#endif // !defined(AFX_OUTPUTMSGCLASS_H__541313E2_F65E_4E68_A08F_A80E9C054B6B__INCLUDED_)
