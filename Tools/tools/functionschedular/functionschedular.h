//=====================================================================================
/**
 * @file functionschedular.h functionSchedular.cpp 
 * �禡�Ƶ{�t�Ϊ���A�N���ߧY�B�z���禡���Ƶ{������ݳB�z�ɦA�I�s\n
 * Last UpDate:2003.8.29
 * @author jacklo@softstar.com.tw
 */
//=====================================================================================
#pragma once
#pragma warning (disable:4786)
#pragma warning (disable:4949)

#include <map>
#include <queue>
#include <vector>
#include <string>
#include "Singleton/singleton.h"
#include <boost/function.hpp>
#include <functional>
#pragma unmanaged
using namespace	std;

class	SchedularInfo;
class	FunctionSchedularClass;
//=====================================================================================
//�禡���Щw�q
//=====================================================================================
///�w�q�^�G�禡���榡 Ret �U�@�ӫ��O�B�z���ɶ�  Ret = -1 �N����
//typedef	int		(*SchedularFunctionBase)(SchedularInfo*	Obj,void*	InputClass);
#define SchedularFunctionBase boost::function<int ( SchedularInfo*	Obj,void*	InputClass ) >
//=====================================================================================
//�禡�Ƶ{�������
//=====================================================================================
class	SchedularInfo 
{
	friend class	FunctionSchedularClass;
protected:
	SchedularInfo*			_Next;							//�U�ӫ��O
	SchedularInfo*			_Front;							//�W�ӫ��O
	//----------------------------------------------------------------------------------
	//	����w�q
	//----------------------------------------------------------------------------------
	long					_GUID;							//���󸹽X
	long					_ProcessTime;					//���j�ɶ�
	SchedularFunctionBase	_Func;
	map<string,string>		_Arg;							//�ѼơA�P��	
	bool					_Enable;						//������O�_�P��
	void*					_UserObjPoint;					//���a�]�w���
public:
	SchedularInfo( );
	int			ProcessTime	( );							//�B�z�ɶ�
	bool		Enable		( );							//��ƬO�_����
	int			GetNumber	( string Name );				//Ū���Ѽ�(�Ʀr)
	char*		GetString	( string Name );				//Ū���Ѽ�(�r��)
	void		PushValue	( string Name , string Value );	//��Ƴ]�w
	void		Add			( SchedularInfo* Next );		//�[�J�@��CallBack�禡
	long		GUID		(){return _GUID;};				//�^�� GUID
};

//=====================================================================================

//=====================================================================================
///��Priority Queue �ƧǥΪ��������
struct	SICompGreat{
	bool operator() ( SchedularInfo* A , SchedularInfo* B ) 
		{ return A->ProcessTime() > B->ProcessTime(); }
};

//=====================================================================================

//=====================================================================================
//�@���Ѽƫ��A�w�q
enum	FuncSchedularValueTypeENUM
{
	EM_ValueType_double	    = 1 ,
	EM_ValueType_int		= 2 ,
	EM_ValueType_string	    = 3 ,
    EM_FuncSchedularValueType_FORCE_DWORD   = 0x7fffffff, 
};
//=====================================================================================

//=====================================================================================
//�ק�᪺priority_queue
template<class T,class Container,class Compare>
class MyP_Queue1 : public priority_queue<T,Container,Compare>
{
public:
    void clear(){c.clear();};

};
//=====================================================================================
//
//=====================================================================================
///�B�z�禡�^�I������A��禡�����|���g�L�]�w�o�ɶ���~����
class	FunctionSchedularClass //: public Singleton< FunctionSchedularClass >
{
	
protected:
	MyP_Queue1	<		SchedularInfo*
						,	vector<SchedularInfo*>
						,	SICompGreat	>			_PQueue;

	vector< SchedularInfo* >						_FunList;
	vector< int >   								_NousedGUIDList;

	//�t�m�@��ID
	int		_GetGUID( );

	//����t�mID
	bool		_ReleaseGUID( int guid );

	//���o�Y�@��ID�����
	SchedularInfo*	_GetSchedularInfo( int guid );

	//�]�w�Y�@��guid ���n�J��� 
	bool		_SetSchedularInfo( int guid , SchedularInfo* );

	//�M���Y�@�� SchedularInfo ���Ҧ��������
	bool		_EraseSchedularInfo( SchedularInfo* );
public:
	~FunctionSchedularClass();

	///�Ҧ���ƲM��
	void	Clear();

	///�]�w�h�[�H�����Y�Ӧ^�I�禡											\n
	///�^�ǵn�JGUID �A �ΨӲ����Ƶ{�����ƥ��								\n
	///�̫�@�ӺU�Ƥ@�w�n�ONULL												\n
	///�d��:Push( Fun, ProcTime , NULL										\n
	///	 		    , name1 , EM_ValueType_float  , 10000.0				\n
	///				, name2 , EM_ValueType_string , "Value2"				\n
	///				, name3 , EM_ValueType_int    ,  100		,NULL )		\n
	///@param Func		= �n�^�I�s���禡									\n
	///@param ProcTime	= �h�[�@��n����(�d�����@�����)					\n
	///@param UserObjPoint = �ϥΪ̪��������								\n
	///@param ... �� �禡�W�� ���O  �� .... �̫�NULL 
	int		Push( SchedularFunctionBase Func , int  ProcTime , void* UserObjPoint , ... );



	///�]�w��YGUID���^�I�禡������A�h�[�H��A����Y�Ӧ^�I�禡				\n
	///�^�ǵn�����P�_														\n
	///�̫�@�ӺU�Ƥ@�w�n�ONULL												\n
	///�d��:AddPush( guid , Fun , NULL										\n
	///					 , name1 , EM_ValueType_float  , 10000.0			\n
	///					 , name2 , EM_ValueType_string , "Value2"			\n
	///					 , name3 , EM_ValueType_int    ,  100		,NULL )	\n
	///@param GUID		= �n�[�J���Ө禡�᭱								\n
	///@param Func		= �n�^�I�s���禡(�d�����@�����)					\n
	///@param UserObjPoint = �ϥΪ̪��������								\n
	///@param ... �� �禡�W�� ���O  �� .... �̫�NULL 						\n
	bool		AddPush( int GUID , SchedularFunctionBase Func , void* UserObjPoint , ... );

	
	///��Y�w�Өƥ󭫱Ƶ{���R��
	bool		Erase( int GUID );


	///�w�ɨ禡�B�z
	void		Process();

};

extern FunctionSchedularClass g_Schedular;
//=====================================================================================
#pragma managed
