// IOutputMsg.h: interface for the IOutputMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_)
#define AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_

//-----------------------------------------------------------------------------------------
//	��Log ��X��Interface 
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
//-----------------------------------------------------------------------------------------

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IOutputMsg  
{
public:
	virtual ~IOutputMsg(){};

	virtual void  FileName	(char *file) = 0;					//�]�w��X�ɮצW��
	virtual char* FileName	(void)		 = 0;					//Ū����X�ɮצW��

	virtual void  OutputLV	(int LV) = 0;						//�]�w��X����

	virtual bool  Print		(int,const char *format,...) = 0;	//��ܦb�ù��W
	virtual bool  Write		(int,const char *format,...) = 0;	//�g�ɮ�
	virtual void  Flush		(void) = 0;							//�j��g�J�ɮ�

};

#endif // !defined(AFX_IOUTPUTMSG_H__464D4CEF_AF23_46C3_9D0E_8FBFE69E58BB__INCLUDED_)
