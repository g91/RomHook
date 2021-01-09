#ifndef _L_U32ARRAY_H_
#define _L_U32ARRAY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( push )
#pragma		warning (disable:4267)
#pragma		warning (disable:4018)

#include "MyDebug.h"
#include "LBaseType.h"
#include <windows.h>
#include <vector>


#define UINT32ArrayList_foreach( _list, _do_something ) {\
	for( int i=0; i< _list._pArray.size(); i++ ) {\
		UINT32 u32Value = _list._pArray[i];\
		if(  u32Value != INVALID_UINT32 ) {\
			{_do_something}\
		}\
	}\
}


#define LU32ARRAY_CALL __stdcall

typedef int(LU32ARRAY_CALL *UINT32Array_EnumFunc)(UINT32,void*);
class UINT32Array {
private:
public:
	std::vector<UINT32> _pArray;
	std::vector<UINT32> _UnUseArray;

	UINT32Array (){};
	~UINT32Array (){};
	int Size(void) { return _pArray.size() - _UnUseArray.size() ; };
	int Add(UINT32);
	void Remove( int nIndex );
	UINT32 ValueAt( int nIndex );

	void SetValue( int nIndex, UINT32 u32Value );
	int IncreaseValueAt( int nIndex );
	int DecreaseValueAt( int nIndex );
	int IncreaseValueAt( int nIndex, int nHowMany );
	int DecreaseValueAt( int nIndex, int nHowMany );

	bool IsValidAt( int nIndex );
	int foreach( UINT32Array_EnumFunc, void* pContext);
	void Clear(void);
};


inline	int		UINT32Array::Add(UINT32 value)
{
	
	if(value == INVALID_UINT32)
		return -1;

	int Ret;
	if(_UnUseArray.size() == 0)
	{
		Ret = _pArray.size();
		_pArray.push_back(INVALID_UINT32);
	}
	else
	{
		Ret = _UnUseArray[_UnUseArray.size()-1];
		_UnUseArray.pop_back();

	}

	_pArray[Ret] = value;

	return Ret;
}

inline	void	UINT32Array::Remove( int nIndex )
{
	if((unsigned)nIndex >= _pArray.size())
	{
		return;
	}

	if(_pArray[nIndex] == INVALID_UINT32)
	{
		return;
	}

	_pArray[nIndex] = INVALID_UINT32 ;

	_UnUseArray.push_back(nIndex);

}

inline	UINT32	UINT32Array::ValueAt( int nIndex )
{
	if(nIndex >= _pArray.size() )
		return INVALID_UINT32;

	return _pArray[nIndex];

}


inline	void	UINT32Array::SetValue( int nIndex, UINT32 u32Value )
{
	if(nIndex >= _pArray.size() )
		return ;

	_pArray[nIndex] = u32Value;

}


inline	int		UINT32Array::IncreaseValueAt( int nIndex )
{
	if(nIndex >= _pArray.size() )
		return INVALID_UINT32;

    if(_pArray[nIndex] == INVALID_UINT32 )	
		return INVALID_UINT32;

	return ++_pArray[nIndex];
}

inline	int		UINT32Array::DecreaseValueAt( int nIndex )
{
	if(nIndex >= _pArray.size() )
		return INVALID_UINT32;

    if(_pArray[nIndex] == INVALID_UINT32 )	
		return INVALID_UINT32;

	return --_pArray[nIndex];

}
inline	int		UINT32Array::IncreaseValueAt( int nIndex, int nHowMany )
{
	if(nIndex >= _pArray.size() )
		return INVALID_UINT32;

    if(_pArray[nIndex] == INVALID_UINT32 )	
		return INVALID_UINT32;

	_pArray[nIndex] += nHowMany;

	return _pArray[nIndex];

}
inline	int		UINT32Array::DecreaseValueAt( int nIndex, int nHowMany )
{
	if(nIndex >= _pArray.size() )
		return INVALID_UINT32;

    if(_pArray[nIndex] == INVALID_UINT32 )	
		return INVALID_UINT32;

	_pArray[nIndex] -= nHowMany;

	return _pArray[nIndex];
}


inline	bool	UINT32Array::IsValidAt( int nIndex )
{
	if(		nIndex >= _pArray.size() 
		||	_pArray[nIndex] == INVALID_UINT32 )
		return false;
	return true;
}

inline	void	UINT32Array::Clear(void)
{
	_pArray.clear();
	_UnUseArray.clear();
}

#pragma		warning (pop)
#endif //_L_U32ARRAY_H_
