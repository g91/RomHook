// Buffer.h: interface for the cNetBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFER_H__B74B0B41_E9D9_11D3_94F4_003043001255__INCLUDED_)
#define AFX_BUFFER_H__B74B0B41_E9D9_11D3_94F4_003043001255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LU32Array.h"

typedef unsigned int HBUFFER;
#define INVALID_BUFFERHANDLE INVALID_UINT32

class cBufferMan {
	UINT32Array	m_arrayReference;
	UINT32Array m_arrayBufferPointer;

public:
	cBufferMan(void) throw();
	~cBufferMan() throw();

	// for read
	HBUFFER CreateBuffer( int nSize ) throw();
	void GetBuffer( HBUFFER hBuffer, int& nSize, void*& vpData ) throw();
	
	// for write
	HBUFFER AddBuffer( int nSize, void* vpData ) throw();
	void GetPureBuffer( HBUFFER hBuffer, int& nSize, void*& vpData ) throw();

	void AddRef ( HBUFFER ) throw();
	void Release( HBUFFER ) throw();
	void AddRef ( HBUFFER, int nAddRef ) throw();
	void Release( HBUFFER, int nRelRef ) throw();
};

extern cBufferMan g_BufferMan;


#endif // !defined(AFX_BUFFER_H__B74B0B41_E9D9_11D3_94F4_003043001255__INCLUDED_)
