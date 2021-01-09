// Buffer.cpp: implementation of the cNetBuffer class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning( push )
#pragma		warning (disable:4311)
#pragma		warning (disable:4312)
#pragma		warning (disable:4018)

#include "LBuffer.h"
#include <memory.h> 

cBufferMan g_BufferMan;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cBufferMan::cBufferMan(void) throw(){
}

cBufferMan::~cBufferMan() throw(){

	UINT32ArrayList_foreach( m_arrayBufferPointer, {
		free( (void*) u32Value );
		m_arrayBufferPointer._pArray[i] = INVALID_UINT32;
	}
	)
}


HBUFFER cBufferMan::CreateBuffer( int nSize ) throw(){
	ASSERTE( nSize < 65535 && nSize > 0 /* 封包必須小於 65535 */ );

	// +8 因為 recv 時 data align 的問題會超寫 +1為檢查碼
	void* p = malloc( nSize + sizeof(WORD) +8);
	*(WORD*)p = nSize;
//	memcpy( ((BYTE*)p)+2, vpData, nSize );

	int n,m;
	n = m_arrayBufferPointer.Add( UINT32(p) );
	m = m_arrayReference.Add( 1 );
	ASSERT( n == m );
	//TRACE3( "CreateBuffer slot %d size %d %x\n", n, nSize, p );

	return n;
}
void cBufferMan::GetBuffer( HBUFFER hBuffer, int& nSize, void*& vpData ) throw(){
	ASSERTE( m_arrayReference.IsValidAt( hBuffer ) );

	void* p = (void*) m_arrayBufferPointer.ValueAt( hBuffer );
	nSize = *(WORD*) p;
	vpData = (WORD*) p + 1;
}


HBUFFER cBufferMan::AddBuffer( int nSize, void* vpData ) throw(){
	ASSERTE( nSize < 65535 && nSize > 0 /* 封包必須小於 65535 */ );
	nSize ++;
	void* p = malloc( nSize + sizeof(WORD) );
	*(WORD*)p = nSize;
	memcpy( ((BYTE*)p)+2, vpData, nSize );

	int n,m;
	n = m_arrayBufferPointer.Add( UINT32(p) );
	m = m_arrayReference.Add( 1 );
	ASSERT( n == m );
	//TRACE3( "AddBuffer slot %d size %d %x\n", n, nSize, p );

	return n;
}

void cBufferMan::GetPureBuffer( HBUFFER hBuffer, int& nSize, void*& vpData ) throw(){
	ASSERTE( m_arrayReference.IsValidAt( hBuffer ) );

	void* p = (void*) m_arrayBufferPointer.ValueAt( hBuffer );
	nSize = *(WORD*) p;
	vpData = p;
}


void cBufferMan::AddRef ( HBUFFER hBuffer, int nAddRef ) throw(){
	ASSERTE( m_arrayReference.IsValidAt( hBuffer ) );

	//TRACE1( "AddRef %d\n", hBuffer );
	m_arrayReference.IncreaseValueAt( hBuffer, nAddRef );
}
void cBufferMan::Release( HBUFFER hBuffer, int nRelRef ) throw(){
	m_arrayReference.DecreaseValueAt( hBuffer, nRelRef );
}

void cBufferMan::AddRef ( HBUFFER hBuffer ) throw(){
	ASSERTE( m_arrayReference.IsValidAt( hBuffer ) );

	//TRACE1( "AddRef %d\n", hBuffer );
	m_arrayReference.IncreaseValueAt( hBuffer );
}
void cBufferMan::Release( HBUFFER hBuffer ) throw(){
	//ASSERTE( m_arrayReference.IsValidAt( hBuffer ) );

	//TRACE1( "Release %d \n", hBuffer );
	if( m_arrayReference.DecreaseValueAt( hBuffer ) != 0 )
		return;

	// free buffer
	void* pBuffer = (void *) m_arrayBufferPointer.ValueAt( hBuffer );
	//TRACE2( "Free %d %x\n", hBuffer, pBuffer);
	free( pBuffer );

	m_arrayReference.Remove( hBuffer );
	m_arrayBufferPointer.Remove( hBuffer );
}

#pragma		warning (pop)