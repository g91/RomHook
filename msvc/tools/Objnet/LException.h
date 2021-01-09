#if !defined(_L_EXCEPTION_H_)
#define _L_EXCEPTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>

class LThrowable
{
private:
	int m_id;
	const char* m_msg;
public:

	LThrowable(void) :m_id(0), m_msg(NULL) {}
	LThrowable(int id) :m_id(id), m_msg(NULL) {}
	LThrowable(int id,const char* msg):m_id(id), m_msg(msg) {}

	const char*	GetMessage(void) const { return m_msg; }
	int		GetID(void){ return m_id; }
};
class LError: public LThrowable
{};

class LException: public LThrowable
{
public:
	LException(int id) :LThrowable(id) {}
	LException(int id, const char* msg) :LThrowable(id,msg) {}
};

class LMemError: public LError
{};


#endif // _L_EXCEPTION_H_