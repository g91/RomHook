#include "ObjNet.h"
#include "SockMan.h"
#include "LBuffer.h"

//IObjNet* LSAPI  CreateObjNet( bool bIsCompress ) throw() {
IObjNet* LSAPI  CreateObjNet( void ) throw() {
	InitSock();
	cSockMan* p = new cSockMan;
	//p->Init(bIsCompress);
	p->Init(false);
	return p;
}
void LSAPI  DestroyObjNet( IObjNet* p ) throw() {
	delete p;
	UninitSock();
}



void	LSAPI ObjNetBufferAddRef( HBUFFER hBuffer ) {
	TRACE1("ObjNetBufferAddRef %d\n", hBuffer );
	::g_BufferMan.AddRef( hBuffer );
}
void	LSAPI ObjNetBufferRelease( HBUFFER hBuffer ) {
	TRACE1("ObjNetBufferRelease %d\n", hBuffer );
	::g_BufferMan.Release( hBuffer );
}
void	LSAPI ObjNetGetBuffer( HBUFFER hBuffer, int& nSize, void*& vpData ) {
//	if(hBuffer != 0)
//	{
//		TRACE1("ObjNetGetBuffer %d\n", hBuffer );
//	}
	::g_BufferMan.GetBuffer( hBuffer, nSize, vpData );
}
