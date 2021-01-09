#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include "FunctionSchedular.h"
#pragma warning (disable:4949)
#pragma unmanaged
//***************************************************************************************
//�R�A��Ʃw�q
//***************************************************************************************
/*
MyP_Queue1	<		SchedularInfo*
,	vector<SchedularInfo*>
,	SICompGreat	>			FunctionSchedularClass::_PQueue;

vector< SchedularInfo* >						FunctionSchedularClass::_FunList;
vector< int >									FunctionSchedularClass::_NousedGUIDList;
*/
//template <> FunctionSchedularClass*  Singleton<FunctionSchedularClass>::_Singleton = 0;
//***************************************************************************************
//	SchedularInfo ���禡�갵
//***************************************************************************************
FunctionSchedularClass g_Schedular;
//----------------------------------------------------------------------------------
//�غc�禡 ��ƪ�l��
//----------------------------------------------------------------------------------
SchedularInfo::SchedularInfo( )
{
	_Next		= NULL;							//�U�ӫ��O
	_Front		= NULL;							//�W�ӫ��O
	//----------------------------------------------------------------------------------
	//	����w�q
	//----------------------------------------------------------------------------------
	_GUID		= -1;							//���󸹽X
	_ProcessTime= 0;					//���j�ɶ�
	_Func		= NULL;
	_Enable		= true;						//������O�_�P��
}
//----------------------------------------------------------------------------------
FunctionSchedularClass::~FunctionSchedularClass( )
{
	Clear();
}
//----------------------------------------------------------------------------------
//�B�z�ɶ� (��ɳB�z)
//----------------------------------------------------------------------------------
int			SchedularInfo::ProcessTime	( )
{
	return _ProcessTime;
}
//----------------------------------------------------------------------------------
//��ƬO�_����
//----------------------------------------------------------------------------------
bool		SchedularInfo::Enable( )
{
	return _Enable;
}
//----------------------------------------------------------------------------------
//Ū���Ѽ�(�Ʀr)
//----------------------------------------------------------------------------------
char*		SchedularInfo::GetString( string Name )
{
	map<string,string>::iterator Iter;

	Iter = _Arg.find( Name );
	if( Iter == _Arg.end() )
		return NULL;		

	return (char*)Iter->second.c_str();
}
//----------------------------------------------------------------------------------
//Ū���Ѽ�(�r��)
//----------------------------------------------------------------------------------
int			SchedularInfo::GetNumber( string Name )
{
	map<string,string>::iterator Iter;

	Iter = _Arg.find( Name );
	if( Iter == _Arg.end() )
		return 0;		

	return atol( Iter->second.c_str() );
}
//----------------------------------------------------------------------------------
//��Ƴ]�w
//----------------------------------------------------------------------------------
void		SchedularInfo::PushValue( string Name , string Value )
{
	_Arg[ Name ] = Value;
}
//----------------------------------------------------------------------------------
//�[�J�@��CallBack�禡
//----------------------------------------------------------------------------------
void		SchedularInfo::Add( SchedularInfo* Next )
{
	SchedularInfo*	Temp;
	for( Temp = this ; Temp->_Next != NULL ; Temp = Temp->_Next );

	Temp->_Next  = Next;
	Next->_Front = Temp->_Next;
}

//***************************************************************************************
//FunctionSchedularClass
//***************************************************************************************
//----------------------------------------------------------------------------------
//�Ҧ���ƲM��
//----------------------------------------------------------------------------------
void	FunctionSchedularClass::Clear( )
{
	int i;
	//�M���Ұt�m���O����
	for( i = 0 ; i < (int)_FunList.size() ; i++ )
	{
		if( _FunList[ i ] != NULL )
			delete _FunList[ i ];
	}

	_FunList.clear();
	_NousedGUIDList.clear();
	_PQueue.clear();
}
//----------------------------------------------------------------------------------
//�t�m�@��ID
//----------------------------------------------------------------------------------
int		FunctionSchedularClass::_GetGUID( )
{
	int Ret;

	if( _NousedGUIDList.size() != 0 )
	{
		Ret = _NousedGUIDList.back();
		_NousedGUIDList.pop_back();
		return Ret;
	}

	Ret = (int)_FunList.size();
	_FunList.push_back( NULL );
	return Ret;
}
//----------------------------------------------------------------------------------
//����t�mID
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::_ReleaseGUID( int id )
{
	if( _FunList.size() <= (unsigned)id )
		return false;

	_FunList[id] = NULL;
	_NousedGUIDList.push_back( id );
	return true;
}
//----------------------------------------------------------------------------------
//���o�Y�@��ID���禡�n�J���
//----------------------------------------------------------------------------------
SchedularInfo*	FunctionSchedularClass::_GetSchedularInfo( int guid )
{
	if( (unsigned)guid >= _FunList.size() )
		return NULL;

	return _FunList[ guid ];
}
//----------------------------------------------------------------------------------
//�]�w�Y�@��guid ���禡�n�J���
//----------------------------------------------------------------------------------
bool FunctionSchedularClass::_SetSchedularInfo( int guid , SchedularInfo* Info)
{
	if( (unsigned)guid >= _FunList.size() )
		return false;

	_FunList[ guid ] = Info;
	return true;
}
//----------------------------------------------------------------------------------
//�]�w�h�[�H�����Y�Ӧ^�I�禡
//�^�ǵn�JGUID �A �ΨӲ����Ƶ{�����ƥ��
//�̫�@�ӺU�Ƥ@�w�n�ONULL
//�d��:Push( Fun, ProcTime ,InuptClass , name1 , EM_ValueType_float  , 10000.0
//						   , name2 , EM_ValueType_string , "Value2"
//						   , name3 , EM_ValueType_int    ,  100		,NULL )
//Func		= �n�^�I�s���禡
//ProcTime	= �h�[�@��n����(�d�����@�����)
//type		= EM_ValueType_float , EM_ValueType_int , EM_ValueType_string , EM_ValueType_void
//----------------------------------------------------------------------------------
int		FunctionSchedularClass::Push( SchedularFunctionBase Func , int  ProcTime , void* _UserObjPoint , ... )
{


	FuncSchedularValueTypeENUM	type;
	char			Buf[64];

	char*			name;	
	char*			value;
	SchedularInfo*	Info = NEW( SchedularInfo );
	va_list			marker;

	va_start( marker , _UserObjPoint );
	while( 1 )
	{
		name = va_arg( marker , char* );
		if( name == NULL )
			break;
		type = ( FuncSchedularValueTypeENUM )va_arg( marker , int );
		switch( type )
		{
		case EM_ValueType_double:
			sprintf( Buf , "%f" , va_arg( marker , double ) );
			value = Buf;
			break;
		case EM_ValueType_int:
			sprintf( Buf , "%d" , va_arg( marker , int ) );
			value = Buf;
			break;
		case EM_ValueType_string:
			value = va_arg( marker , char* );
			break;
		}
		Info->PushValue( name , value );
	}

	va_end( marker );

	//���@��ID
	Info->_GUID			= _GetGUID( );
	Info->_ProcessTime	= ProcTime + clock();
	Info->_Func			= Func;
	Info->_UserObjPoint = _UserObjPoint;
	//��Ƶn�J�޲z
	_SetSchedularInfo( Info->_GUID , Info );
	//���B�z�Ƶ{
	_PQueue.push( Info );

	return Info->_GUID;
}

//----------------------------------------------------------------------------------
//�]�w��YGUID���^�I�禡������A�h�[�H��A����Y�Ӧ^�I�禡
//�^�ǵn�����\�P�_
//�̫�@�ӺU�Ƥ@�w�n�ONULL
//�d��:AddPush( guid , Fun, ProcTime 
//						   , name1 , EM_ValueType_float  , 10000.0
//						   , name2 , EM_ValueType_string , "Value2"
//						   , name3 , EM_ValueType_int    ,  100		,NULL )
//GUID		= �n�[�J���Ө禡�᭱
//Func		= �n�^�I�s���禡
//ProcTime	= �h�[�@��n����
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::AddPush( int GUID , SchedularFunctionBase Func , void* _UserObjPoint , ... )
{

	FuncSchedularValueTypeENUM	type;
	SchedularInfo*	PrvInfo = _GetSchedularInfo( GUID );

	if( PrvInfo == NULL ) 
		return false;

	char*			name;	
	char*			value;
	SchedularInfo*	Info = NEW( SchedularInfo );
	va_list			marker;
	char			Buf[64];

	va_start( marker , _UserObjPoint );

	while( 1 )
	{
		name = va_arg( marker , char* );
		if( name == NULL )
			break;
		type = ( FuncSchedularValueTypeENUM )va_arg( marker , int );
		switch( type )
		{
		case EM_ValueType_double:
			sprintf( Buf , "%f" , va_arg( marker , double ) );
			value = Buf;
			break;
		case EM_ValueType_int:
			sprintf( Buf , "%d" , va_arg( marker , int ) );
			value = Buf;
			break;
		case EM_ValueType_string:
			value = va_arg( marker , char* );
			break;
		}
		Info->PushValue( name , value );
	}

	va_end( marker );

	Info->_UserObjPoint = _UserObjPoint;
	Info->_Func			= Func;
	PrvInfo->Add( Info );

	return true;
}

//----------------------------------------------------------------------------------
//��Y�w�Өƥ󭫱Ƶ{���R��
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::Erase( int GUID )
{
	SchedularInfo*	PrvInfo = _GetSchedularInfo( GUID );
	if( PrvInfo == NULL )
		return false;

	PrvInfo->_Enable = false;
	return true;
}
//----------------------------------------------------------------------------------
//�M���Y�@�� SchedularInfo ���Ҧ��������
//----------------------------------------------------------------------------------
bool	FunctionSchedularClass::_EraseSchedularInfo( SchedularInfo* Info )
{

	for( ; Info->_Front != NULL ; Info = Info->_Front );

	_ReleaseGUID( Info->_GUID );

	for( ; Info->_Next != NULL ; Info = Info->_Next )
		delete Info->_Front;


	delete Info;

	return true;
}
//----------------------------------------------------------------------------------
//�w�ɨ禡�B�z
//----------------------------------------------------------------------------------
void	FunctionSchedularClass::Process( )
{

	int				IntervalTime;
	SchedularInfo*	Info;
	while(1)
	{
		if( _PQueue.size() == 0 )
			return;

		Info = _PQueue.top();

		//�ɶ��٨S��
		if( Info->_ProcessTime - clock() > 0)
			return;

		_PQueue.pop();

		if( !Info->Enable() )
		{
			_EraseSchedularInfo( Info );
			continue;
		}

		if( Info->_Func != NULL)
		{
			IntervalTime = Info->_Func( Info , Info->_UserObjPoint );

			if( IntervalTime == -1 || Info->_Next == NULL )
			{
				_EraseSchedularInfo( Info );
			}
			else 
			{
				Info->_Next->_ProcessTime = clock() + IntervalTime;
				_PQueue.push( Info->_Next );
			}
		}
	}
}
//***************************************************************************************
#pragma managed