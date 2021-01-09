#ifndef _L_Mutex_H_
#define _L_Mutex_H_

#ifdef _WIN32
#include <winbase.h>
#else // Linux
#include <pthread.h>
#endif

#include "LException.h"
//#include "Config.h"

#ifdef _LWZ_MT

class LMutex
{
private:
#ifdef _WIN32
	HANDLE	m_hMutex;
#else // Linux
	pthread_mutex_t m_mutex;
#endif
public:
	LMutex(void);
	~LMutex();
	void Lock(void);
	void TryLock(void);
	void Unlock(void);
};

#ifdef WIN32
inline LMutex::LMutex(void)
:	m_hMutex( NULL )
{
	m_hMutex = CreateMutex( NULL , FALSE, NULL );
	if( !m_hMutex )
		throw LException(1, "LMutex: construct failed" );
}
inline LMutex::~LMutex()
{
	if( m_hMutex )
		CloseHandle( m_hMutex );
}
inline void LMutex::Lock(void)
{
	if( WaitForSingleObject( m_hMutex, INFINITE ) != WAIT_OBJECT_0 )
		throw LException(GetLastError(), "LMutex: Lock failed" );
}
inline void LMutex::TryLock(void)
{
	if( WaitForSingleObject( m_hMutex, 0 ) != WAIT_OBJECT_0 )
		throw LException(GetLastError(), "LMutex: TryLock failed" );
}
inline void LMutex::Unlock(void)
{
	if(! ReleaseMutex( m_hMutex ) )
		throw LException(GetLastError(), "LMutex: Unlock failed" );
}


#else // Linux
inline LMutex::LMutex(void)
{
}
inline LMutex::~LMutex()
{
}
inline void LMutex::Lock(void)
{
}
inline void LMutex::TryLock(void)
{
}
inline void LMutex::Unlock(void)
{
}
#endif

#else // _LWZ_MT

class LMutex {
public:
	void Lock(void) {};
	void TryLock(void){};
	void Unlock(void){};
};

#endif // _LWZ_MT


#endif //#ifndef _L_Mutex_H_

