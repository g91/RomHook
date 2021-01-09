#include <fstream>
#include "mymd5.h"
#include "smallobj/SmallObj.h"

#define BUFFER_SIZE 256

const char*	MyMD5Class::ComputeStringHash( const char* Str , const char* XorStr )
{
	g_CritSect()->Enter();
	const char*	RetStr = _ComputeStringHash( Str , XorStr );
	g_CritSect()->Leave();
	return RetStr;
}
const char*	MyMD5Class::ComputeFileHash( const char* FileName )
{
	g_CritSect()->Enter();
	const char*	RetStr = _ComputeFileHash( FileName );
	g_CritSect()->Leave();
	return RetStr;
}

const char*	MyMD5Class::_ComputeStringHash( const char* Str , const char* XorStr )
{
	::Md5Initialize();

	MD5DIGEST dMd5;
	HMD5CONTEXT hMd5;

	if(!::Md5AcquireContext(hMd5))
	{
		return NULL;
	} // if

	
	int nLength = int( strlen( Str ) );

	// Allocating required buffer
	MD5_BYTE* pBuffer = NEW MD5_BYTE[nLength];
	//memcpy( pBuffer , Str , nLength );

	int XorStrLen;
	if( XorStr != NULL )
		XorStrLen = int( strlen(XorStr) );
	else
		XorStrLen = 0;
	if( XorStrLen != 0 )
	{
		for( int i = 0 ; i < nLength ; i++ )
		{
			pBuffer[i] = Str[i] ^ XorStr[ i % XorStrLen ];
		}
	}
	else
	{
		memcpy( pBuffer , Str , nLength );
	}

	// Hashing
	::Md5UpdateHash(hMd5, pBuffer, nLength );
	::Md5FinalHash(hMd5, dMd5);
	delete pBuffer;

	for(int n = 0; n < 16; ++n)
	{
		sprintf( _MD5Str+n*2 , "%02X", dMd5[n] );
	} // for

	::Md5ReleaseContext(hMd5);

	::Md5Uninitialize();

	return _MD5Str;
}

const char*	MyMD5Class::_ComputeFileHash( const char* FileName )
{
	::Md5Initialize();

	MD5DIGEST dMd5;
	HMD5CONTEXT hMd5;

	if(!::Md5AcquireContext(hMd5))
	{		
		return NULL;
	} // if

	// If we're hashing a file
	fstream file;

	file.open( FileName , ios::in | ios::binary );	

	if( file.is_open() == false )
	{
		return NULL;
	}

	MD5_BYTE *pBuffer = NEW MD5_BYTE[BUFFER_SIZE]; // IO buffer
	UINT unSize = sizeof(BYTE) * BUFFER_SIZE;
//	UINT unBytes = file.read((char *)pBuffer, unSize);		

	//while(unBytes)
	while( 1 )
	{
		file.read((char *)pBuffer, unSize);		
		if( file.gcount() == 0 )
			break;

		if(!::Md5UpdateHash(hMd5, pBuffer, file.gcount() )) 
		{
			delete [] pBuffer;
			return NULL;
		} // if

	} // while

	delete [] pBuffer;

	::Md5FinalHash(hMd5, dMd5);
	::Md5ReleaseContext(hMd5);
	
	for(int n = 0; n < 16; ++n)
	{
		sprintf( _MD5Str+n*2 , "%02X", dMd5[n] );
	} // for

	::Md5ReleaseContext(hMd5);

	::Md5Uninitialize();

	return _MD5Str;
}