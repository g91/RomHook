#ifndef _L_DEBUG_H_
#define _L_DEBUG_H_

#ifdef __BORLANDC__
#pragma warn -sig
#endif
#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifdef _DEBUG

	#if defined(_MSC_VER)
		//#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
		#include <malloc.h>
		#include <stdlib.h>
		//#include <malloc_dbg.h>
		//#include <stdlib_dbg.h>
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#else
		#include <malloc.h>
		#include <stdlib.h>
       #ifndef __BORLANDC__
			#define OutputDebugString(a) {cout<<a;}
       #endif
	#endif

	#include <assert.h>
	#define VERIFY(a)		assert( a )
	#define ASSERT(a)		assert( a )
#ifndef _ASSERTE
	#define ASSERTE(a)		assert( a )
#else
	#define ASSERTE(a)		_ASSERTE( a )
#endif

	#define TRACE0(a)		OutputDebugString(a)
	#define TRACE1(a,b)		{ char  szTemp[256];wsprintf( szTemp, a, b );		OutputDebugString( szTemp ); }
	#define TRACE2(a,b,c)	{ char  szTemp[256];wsprintf( szTemp, a, b , c);		OutputDebugString( szTemp ); }
	#define TRACE3(a,b,c,d)	{ char  szTemp[256];wsprintf( szTemp, a, b , c, d);	OutputDebugString( szTemp ); }
	#define TRACE4(a,b,c,d,e){char  szTemp[256];wsprintf( szTemp, a, b , c, d,e);OutputDebugString( szTemp ); }
	#define TRACE5(a,b,c,d,e,f){char  szTemp[256];wsprintf( szTemp, a, b , c, d,e,f);OutputDebugString( szTemp ); }
	#define TRACEHR( a,hr ) {char* szTemp=(char*)_alloca(strlen(a)+20);wsprintf( szTemp, "%s, hr = %lx\n",a,hr );OutputDebugString( szTemp ); }
	#define CheckFail( hRet, szError )	if( FAILED(hRet) ){\
		TRACEHR( szError, hRet);\
		return hRet;\
	}

#else
	#define VERIFY(a) a
	#define ASSERT(a)
	#define ASSERTE(a)
	#define TRACE0(a)		
	#define TRACE1(a,b)	
	#define TRACE2(a,b,c)
	#define TRACE3(a,b,c,d)
	#define TRACE4(a,b,c,d,e)
	#define TRACE5(a,b,c,d,e,f)
	#define TRACEHR( a,hr )
	#define CheckFail( hRet, szError )  if( FAILED(hRet) ){\
		return hRet;\
	}

#endif // _DEBUG


#endif // _L_DEBUG_H_