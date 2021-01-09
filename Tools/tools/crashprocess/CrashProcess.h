#pragma once

#ifndef	__CRASHPROCESS_H__
#define __CRASHPROCESS_H__

#include <windows.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

#pragma unmanaged

#define CrashProcessFunction  boost::function< void ( ) >

class CrashProcess
{
private:
	static HANDLE					m_MainThreadHandle;
	static DWORD					m_dwCheckTick;
	static LPVOID					m_LPV;				//Crashrpt instance pointer
	static bool						m_bRunning;
	static CrashProcessFunction		m_OnCheck;
	static CrashProcessFunction		m_OnExit;

public:
	static bool						Init(HANDLE hMainThread, LPVOID lpV);
	static bool						Start();
	static void						Check();
	static bool						Stop();

	static void						SetOnCheck ( CrashProcessFunction Func ){ m_OnCheck = Func;}
	static void						SetOnExit  ( CrashProcessFunction Func ){ m_OnExit  = Func;}

	static LPVOID					GetLPV (){ return m_LPV;}

protected:
	static bool						IsNormal();
	static DWORD WINAPI				ServiceLoop( void* );
};

#endif