/********************************************************************
	Created:	21/3/2004, 21:39
	File name: 	D:\Projects\Exile\MD5\MD5.h
	File path:	D:\Projects\Exile\MD5
	File base:	MD5
	File ext:	h
	Author:		Gogolev Anton
*********************************************************************/

#pragma once
#include <Windows.h>
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MD5_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MD5_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef MD5_DLL_EXPORT

#ifdef MD5_EXPORTS
#define MD5_API extern "C" __declspec(dllexport)
#else
#define MD5_API extern "C" __declspec(dllimport)
#endif
#else
#define MD5_API
#endif


BOOL WINAPI DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);

//////////////////////////////////////////////////////////////////////////
// MD5 Types

// MD5 Word
typedef unsigned long int MD5_WORD;

// MD5 Byte
typedef unsigned char MD5_BYTE;

// MD5 Hashing Context
typedef unsigned long int HMD5CONTEXT;

// MD5 Hash
typedef struct tagMD5HASH {
	MD5_WORD wA;
	MD5_WORD wB;
	MD5_WORD wC;
	MD5_WORD wD;
} MD5HASH, *LPMD5HASH;

// MD5 Digest
typedef unsigned char MD5DIGEST[16];

// MD5 Hashing Context
typedef struct tagMD5CONTEXT {
	MD5HASH hsState;
	MD5_BYTE *pBuffer; // To buffer data which is still to be hashed
	MD5_WORD wSize[2]; // Total size of data hashed (in bytes)
} MD5CONTEXT, *LPMD5CONTEXT;

// Initializes MD5 internal structures
MD5_API BOOL Md5Initialize();

// Uninitializes and performs cleanup
MD5_API BOOL Md5Uninitialize();

// Acquire initialized MD5 Hashing context.
MD5_API BOOL Md5AcquireContext(HMD5CONTEXT &hMd5);

// Release MD5 Hashing context
MD5_API BOOL Md5ReleaseContext(HMD5CONTEXT &hMd5);

// Resets a hashing context so new data block can be hashed
MD5_API BOOL Md5ResetContext(HMD5CONTEXT hMd5);

// Determine if given context is a valid one
MD5_API BOOL Md5ValidContext(HMD5CONTEXT hMd5);

// Hashes a buffer (pBuffer) of a given size (sBuffer) and
// awaits either for a next part of a message, or for
// a call to Md5FinalHash()
MD5_API BOOL Md5UpdateHash(HMD5CONTEXT hMd5, const MD5_BYTE *pBuffer, size_t sBuffer);

// Hashes buffered data (if any), produces a final hash
// and automatically resets hashing context.
MD5_API BOOL Md5FinalHash(HMD5CONTEXT hMd5, MD5DIGEST &dMd5);

// Transforms 64-byte buffer pointed by pData.
// Not exported from library.
BOOL Md5Transform(const MD5_BYTE *pData, MD5HASH &hMd5);

// Tests if two hashes are equal
MD5_API BOOL Md5EqualHashes(const MD5DIGEST& hsMd5A, const MD5DIGEST& hsMd5B);

// Encodes dwords in pwData into LSB bytes. Assumes sLength is
// a multiple of 4
MD5_API BOOL Md5EncodeBytes(MD5_BYTE *pBuffer, const MD5_WORD *pwData, size_t sLength);

// Decodes bytes in pBuffer into pwData. Assumes sLength is
// a multiple of 4
MD5_API BOOL Md5DecodeBytes(MD5_WORD *pwData, const MD5_BYTE *pBuffer, size_t sLength);

//#endif //__MD5_H__