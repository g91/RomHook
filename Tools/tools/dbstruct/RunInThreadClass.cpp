#include "RunInThreadClass.h"

RunInThreadClass::RunInThreadClass(void)
{
}

RunInThreadClass::~RunInThreadClass(void)
{
}

DWORD WINAPI RunInThreadClass::_ThreadFuction( void* _this )
{ 
	RunInThreadClass* This = (RunInThreadClass*)_this;
	This->_exeFunc( This->_userData );
	This->_IsEnd = false;
	return 0;
};

bool RunInThreadClass::RunInThread( ExeInThreadFunc func , void *userData , int timeOut )
{
	_IsEnd = true;
	_exeFunc  = func;
	_userData = userData;

	_hThread = CreateThread( NULL , 0 , _ThreadFuction , (LPVOID) this , 0 , NULL );

	for( int i = 0 ; i < timeOut*50 ; i++ )
	{
		Sleep( 20 );
		if( _IsEnd == false )
			return true;
	}

	TerminateThread( _hThread , 0 );

	return false;
}