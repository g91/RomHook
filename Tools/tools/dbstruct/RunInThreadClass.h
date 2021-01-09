#pragma once
#include <Windows.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>


#define ExeInThreadFunc         boost::function<void ( void* UserData ) >

class RunInThreadClass
{
	HANDLE			_hThread;
	ExeInThreadFunc	_exeFunc;
	void*			_userData;
	bool			_IsEnd;			//������O�_�w����

	static DWORD WINAPI _ThreadFuction( void* _this );
public:
	RunInThreadClass(void);
	~RunInThreadClass(void);

	bool RunInThread( ExeInThreadFunc func , void *userData , int timeOut );
};
