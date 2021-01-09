
#if !defined(_L_TEST_VALID_H_)
#define _L_TEST_VALID_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// inherit 時方便使用
#define TEST_VALID public TestValid



#ifdef _DEBUG
#include "MyDebug.h"
#endif

class TestValid  
{

// 因為非 debug 模式不需要這些東西，只要 inherit 空白的 class
#ifdef _DEBUG
	DWORD dwPointerCheck1;
	DWORD dwPointerCheck2;
public:
	virtual bool IsValid(void)
	{
		return ( (dwPointerCheck1 == 0x786403e4) && (dwPointerCheck2 == 0xa3cd4ffc));
	}
	TestValid() : dwPointerCheck1(0x786403e4),dwPointerCheck2(0xa3cd4ffc){}
	~TestValid() { dwPointerCheck1 = 0xcdcdcdcd; dwPointerCheck2 = 0xcdcdcdcd;}
#endif

};

#ifndef _DEBUG

	#define ASSERT_VALID( p ) NULL

#else

	#define ASSERT_VALID( p ) \
	{\
	ASSERT( (p) != NULL );\
	ASSERT( (p)->IsValid() );\
	}

#endif

#endif // !_L_TEST_VALID_H_
