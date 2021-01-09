#ifndef __NB_EVENTOBJ_H__
#define __NB_EVENTOBJ_H__

//#include <Windows.h>

class CEventObj
{
public:
	CEventObj(){};
	~CEventObj(){};

	virtual bool		OnRecv			( unsigned long dwNetID, unsigned long dwPackSize, void* pPacketData ) =0;
	//  ����ʥ]
	//		dwID
	//			�ʥ]�N��
	//		dwPackSize
	//			�ʥ]�j�p
	//		pPacketData
	//			���, ��񱼦��@�T����, �t�αN�ۤv�R���ӫʥ], �����i�H�N����ƫ��Яd�U

	virtual void		OnConnectFailed	( unsigned long dwNetID, unsigned long dwFailedCode ) =0;
	//  �s�u����
	//		dwFailedCode
	//			���ѥN�X

	virtual void		OnConnect		( unsigned long dwNetID ) =0;
	//  �s�u���\
	//		dwNetID			
	//			������Client, ���\�P�ؼЫإ߳s�u, ���� NetID ����� Connect �ɩҶǦ^�� NetID


	virtual	void		OnDisconnect	( unsigned long dwNetID ) =0;
	// �_�u
	//		dwNetID			�_�u��H NetID

	virtual CEventObj*	OnAccept		( unsigned long dwNetID ) { return 0; };
	// �@�ӷs���s�u�s�J
	//		dwNetID
	//			�ӳs�u�� NetID
	//	�Ǧ^��
	//			�]�w�ӳs�u�s�� Event

};

#endif
