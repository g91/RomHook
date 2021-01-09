/********************************************************************
	Created:	21/3/2004, 21:38
	File name: 	D:\Projects\Exile\MD5\MD5.cpp
	File path:	D:\Projects\Exile\MD5
	File base:	MD5
	File ext:	cpp
	Author:		Gogolev Anton
*********************************************************************/

// MD5.cpp : Defines the entry point for the DLL
//

#include "MD5.h"
#include <stdlib.h>
#include <math.h>
#include <map>

// Context map
typedef std::map<HMD5CONTEXT, MD5CONTEXT> MD5CONTEXTMAP;

MD5CONTEXTMAP mMd5Ctx;

// Summands used in rounds
//MD5_WORD *g_pwSummands = 0;

// Chaining constants
static const MD5_WORD g_wChainA = 0x67452301;
static const MD5_WORD g_wChainB = 0xEFCDAB89;
static const MD5_WORD g_wChainC = 0x98BADCFE;
static const MD5_WORD g_wChainD = 0x10325476;

// Padding buffer
static const MD5_BYTE g_aPadding[64] =
	{ 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//////////////////////////////////////////////////////////////////////////
// MD5 Nonlinear functions

inline MD5_WORD F(MD5_WORD wX, MD5_WORD wY, MD5_WORD wZ)
{	
	return ((wX & wY) | (~wX & wZ));
}

inline MD5_WORD G(MD5_WORD wX, MD5_WORD wY, MD5_WORD wZ)
{
	return ((wX & wZ) | (wY & ~wZ));
}

inline MD5_WORD H(MD5_WORD wX, MD5_WORD wY, MD5_WORD wZ)
{
	return (wX ^ wY ^ wZ);
}

inline MD5_WORD I(MD5_WORD wX, MD5_WORD wY, MD5_WORD wZ)
{
	return (wY ^ (wX | ~wZ));
}

//////////////////////////////////////////////////////////////////////////
// MD5 Transformation Functions

inline void FF(MD5_WORD &wA, MD5_WORD wB, MD5_WORD wC, MD5_WORD wD, MD5_WORD wM, int nS, MD5_WORD wT)
{	
	wA += F(wB, wC, wD) + wM + wT;
	wA = _lrotl(wA, nS);
	wA += wB;
}

inline void GG(MD5_WORD &wA, MD5_WORD wB, MD5_WORD wC, MD5_WORD wD, MD5_WORD wM, int nS, MD5_WORD wT)
{	
	wA += G(wB, wC, wD) + wM + wT;
	wA = _lrotl(wA, nS);
	wA += wB;
}

inline void HH(MD5_WORD &wA, MD5_WORD wB, MD5_WORD wC, MD5_WORD wD, MD5_WORD wM, int nS, MD5_WORD wT)
{	
	wA += H(wB, wC, wD) + wM + wT;
	wA = _lrotl(wA, nS);
	wA += wB;
}

inline void II(MD5_WORD &wA, MD5_WORD wB, MD5_WORD wC, MD5_WORD wD, MD5_WORD wM, int nS, MD5_WORD wT)
{	
	wA += I(wB, wC, wD) + wM + wT;
	wA = _lrotl(wA, nS);
	wA += wB;
}

//////////////////////////////////////////////////////////////////////////
// MD5 Main

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason) 
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	} // switch

    return TRUE;
}

MD5_API BOOL Md5Initialize()
{
	/*
	if(g_pwSummands) 
	{
		// Already initialized
		return FALSE;		
	} // if

	g_pwSummands = new MD5_WORD[64];

	for(int n = 0; n < 64; ++n)
	{
		double dVal = pow(2.0, 32.0) * fabs(sin((double)n + 1.0));
		g_pwSummands[n] = MD5_WORD(dVal);
	} // for
	*/

	return TRUE;
}

MD5_API BOOL Md5Uninitialize()
{
	/*
	if(g_pwSummands)
	{
		delete [] g_pwSummands;
		g_pwSummands = 0;
	
		return TRUE;
	} // if

	// Not yet initialized
	return FALSE;	
	*/

	return TRUE;
}

MD5_API BOOL Md5AcquireContext(HMD5CONTEXT &hMd5)
{
	hMd5 = (HMD5CONTEXT)&hMd5;

	// Check for duplicates
	if(mMd5Ctx.end() != mMd5Ctx.find(hMd5)) 
	{
		hMd5 = (HMD5CONTEXT)0;
		return FALSE;
	} // if

	MD5CONTEXT cMd5;

	cMd5.hsState.wA = g_wChainA;
	cMd5.hsState.wB = g_wChainB;
	cMd5.hsState.wC = g_wChainC;
	cMd5.hsState.wD = g_wChainD;
	cMd5.pBuffer = new MD5_BYTE[64];
	memset(cMd5.pBuffer, 0, sizeof(MD5_BYTE) * 64);
	cMd5.wSize[0] = cMd5.wSize[1] = 0;	

	mMd5Ctx[hMd5] = cMd5;

	return TRUE;
}

MD5_API BOOL Md5ReleaseContext(HMD5CONTEXT &hMd5)
{
	// This is an error
	if(0 == hMd5) 
	{
		return FALSE;
	} // if

	MD5CONTEXTMAP::iterator mMd5i = mMd5Ctx.find(hMd5);
	if(mMd5Ctx.end() != mMd5i)
	{
		// Cleaning up
		memset(mMd5i->second.pBuffer, 0, sizeof(MD5_BYTE) * 64);
		delete [] mMd5i->second.pBuffer;

		hMd5 = (HMD5CONTEXT)0;
		mMd5Ctx.erase(mMd5i);

		return TRUE;
	} // if

	return FALSE;
}

MD5_API BOOL Md5ResetContext(HMD5CONTEXT hMd5)
{
	if(0 == hMd5) 
	{
		return FALSE;
	} // if

	// Reset state variables and stuff...
	MD5CONTEXTMAP::iterator mMd5i = mMd5Ctx.find(hMd5);
	if(mMd5Ctx.end() != mMd5i)
	{
		mMd5i->second.hsState.wA = g_wChainA;
		mMd5i->second.hsState.wB = g_wChainB;
		mMd5i->second.hsState.wC = g_wChainC;
		mMd5i->second.hsState.wD = g_wChainD;
		memset(mMd5i->second.pBuffer, 0, sizeof(MD5_BYTE) * 64);		
		mMd5i->second.wSize[0] = mMd5i->second.wSize[1] = 0;

		return TRUE;
	} // if
	
	return FALSE;
}

MD5_API BOOL Md5ValidContext(HMD5CONTEXT hMd5)
{
	// Zero context id indicates error
	if(0 == hMd5) 
	{
		return FALSE;
	} // if

	if(mMd5Ctx.end() != mMd5Ctx.find(hMd5)) 
	{
		return TRUE;
	} // if
	
	return FALSE;
}

MD5_API BOOL Md5UpdateHash(HMD5CONTEXT hMd5, const MD5_BYTE *pBuffer, size_t sBuffer)
{
	/*if(!sBuffer)
	{
		return TRUE;
	} // if*/

	if(0 == hMd5) 
	{
		return FALSE;
	} // if

	MD5CONTEXTMAP::iterator mMd5i = mMd5Ctx.find(hMd5);
	if(mMd5Ctx.end() == mMd5i) 
	{
		return FALSE;
	} // if

	unsigned int i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (unsigned int)((mMd5i->second.wSize[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((mMd5i->second.wSize[0] += ((MD5_WORD)sBuffer << 3))
			< ((MD5_WORD)sBuffer << 3))
			mMd5i->second.wSize[1]++;
		mMd5i->second.wSize[1] += ((MD5_WORD)sBuffer >> 29);

		partLen = 64 - index;

		/* Transform as many times as possible.
		*/
		if (sBuffer >= partLen) {
			memcpy
				((MD5_BYTE *)&mMd5i->second.pBuffer[index], (MD5_BYTE *)pBuffer, partLen);
			Md5Transform (mMd5i->second.pBuffer, mMd5i->second.hsState);

			for (i = partLen; i + 63 < sBuffer; i += 64)
				Md5Transform (&pBuffer[i], mMd5i->second.hsState);

			index = 0;
		}
		else
			i = 0;

		/* Buffer remaining pBuffer */
		memcpy
			((MD5_BYTE *)&mMd5i->second.pBuffer[index], (MD5_BYTE *)&pBuffer[i],
			sBuffer-i);


	/*MD5_WORD wI, wIndex, wPart;

	wIndex = (MD5_WORD)((mMd5i->second.wSize[0] >> 3) & 0x3F);
	mMd5i->second.wSize[0] += (MD5_WORD)(sBuffer << 3);

	if(mMd5i->second.wSize[0] < (MD5_WORD)(sBuffer << 3))
	{
		++(mMd5i->second.wSize[1]);
	} // if

	mMd5i->second.wSize[1] += (MD5_WORD)(sBuffer >> 29);

	wPart = 64 - wIndex;

	if(sBuffer >= wPart)
	{
		memcpy(mMd5i->second.pBuffer + wIndex, pBuffer, wPart);
		Md5Transform(mMd5i->second.pBuffer, mMd5i->second.hsState);

		for(wI = wPart; (wI + 63) < sBuffer; wI += 64)
		{
			Md5Transform(pBuffer + wI, mMd5i->second.hsState);		
		} // for

		wIndex = 0;
	}
	else
	{
		wI = 0;
	} // else

	memcpy(mMd5i->second.pBuffer + wIndex, pBuffer + wI, sBuffer - wI);*/

	return TRUE;
}

MD5_API BOOL Md5FinalHash(HMD5CONTEXT hMd5, MD5DIGEST &dMd5)
{
	if(0 == hMd5) 
	{
		return FALSE;
	} // if

	MD5CONTEXTMAP::iterator mMd5i = mMd5Ctx.find(hMd5);
	if(mMd5Ctx.end() == mMd5i) 
	{
		return FALSE;
	} // if

/*	unsigned char bits[8];
	unsigned int index, padLen;

	// Save number of bits
	Md5EncodeBytes(bits, context->count, 8);

	// Pad out to 56 mod 64.
	
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (context, PADDING, padLen);

	// Append length (before padding) 
	MD5Update (context, bits, 8);

		// Store state in digest 
		Encode (digest, context->state, 16);*/


	MD5_BYTE aBits[8];
	MD5_WORD wIndex, wPad;

	Md5EncodeBytes((MD5_BYTE *)aBits, (MD5_WORD*)(mMd5i->second.wSize), 8);
	
	wIndex = (MD5_WORD)((mMd5i->second.wSize[0] >> 3) & 0x3F);
	wPad = (wIndex < 56) ? (56 - wIndex) : (120 - wIndex);
	Md5UpdateHash(hMd5, g_aPadding, wPad);
	
	Md5UpdateHash(hMd5, aBits, 8);
	
	Md5EncodeBytes((MD5_BYTE *)&dMd5, (MD5_WORD *)&(mMd5i->second.hsState), 16);

	/*MD5_WORD wLast, wPadn;
	MD5_WORD wHigh, wLow;
	MD5_BYTE aBits[8];

	wHigh = (mMd5i->second.wSize[0] >> 29) | (mMd5i->second.wSize[1] << 3);
	wLow = (mMd5i->second.wSize[0] << 3);

	Md5EncodeBytes(aBits, &wLow, sizeof(MD5_WORD));
	Md5EncodeBytes(aBits + 4, &wHigh, sizeof(MD5_WORD));

	wLast = mMd5i->second.wSize[0] & 0x3F;
	wPadn = (wLast < 56) ? (56 - wLast) : (120 - wLast);

	Md5UpdateHash(hMd5, (MD5_BYTE *)g_aPadding, wPadn);
	Md5UpdateHash(hMd5, (MD5_BYTE *)aBits, 8);
	
	Md5EncodeBytes((MD5_BYTE *)&hsMd5.wA, &(mMd5i->second.hsState.wA), sizeof(MD5_WORD));
	Md5EncodeBytes((MD5_BYTE *)&hsMd5.wB, &(mMd5i->second.hsState.wB), sizeof(MD5_WORD));
	Md5EncodeBytes((MD5_BYTE *)&hsMd5.wC, &(mMd5i->second.hsState.wC), sizeof(MD5_WORD));
	Md5EncodeBytes((MD5_BYTE *)&hsMd5.wD, &(mMd5i->second.hsState.wD), sizeof(MD5_WORD));	

	Md5ResetContext(hMd5);*/

	return TRUE;
}

BOOL Md5Transform(const MD5_BYTE *pData, MD5HASH &hMd5)
{
	//if(!g_pwSummands)
	//	return FALSE;

	MD5_WORD wA, wB, wC, wD;
	MD5_WORD awBuffer[16];

	Md5DecodeBytes(awBuffer, pData, 64);
	
	// Here we go
	wA = hMd5.wA;
	wB = hMd5.wB;
	wC = hMd5.wC;
	wD = hMd5.wD;

	// Stage 1
	FF(wA, wB, wC, wD, awBuffer[0], 7, 0xd76aa478);
	FF(wD, wA, wB, wC, awBuffer[1], 12, 0xe8c7b756);
	FF(wC, wD, wA, wB, awBuffer[2], 17, 0x242070db);
	FF(wB, wC, wD, wA, awBuffer[3], 22, 0xc1bdceee);
	FF(wA, wB, wC, wD, awBuffer[4], 7, 0xf57c0faf);
	FF(wD, wA, wB, wC, awBuffer[5], 12, 0x4787c62a);
	FF(wC, wD, wA, wB, awBuffer[6], 17, 0xa8304613);
	FF(wB, wC, wD, wA, awBuffer[7], 22, 0xfd469501);
	FF(wA, wB, wC, wD, awBuffer[8], 7, 0x698098d8);
	FF(wD, wA, wB, wC, awBuffer[9], 12, 0x8b44f7af);
	FF(wC, wD, wA, wB, awBuffer[10], 17, 0xffff5bb1);
	FF(wB, wC, wD, wA, awBuffer[11], 22, 0x895cd7be);
	FF(wA, wB, wC, wD, awBuffer[12], 7, 0x6b901122);
	FF(wD, wA, wB, wC, awBuffer[13], 12, 0xfd987193);
	FF(wC, wD, wA, wB, awBuffer[14], 17, 0xa679438e);
	FF(wB, wC, wD, wA, awBuffer[15], 22, 0x49b40821);
	/*
	FF(wA, wB, wC, wD, awBuffer[0], 7, g_pwSummands[0]);
	FF(wD, wA, wB, wC, awBuffer[1], 12, g_pwSummands[1]);
	FF(wC, wD, wA, wB, awBuffer[2], 17, g_pwSummands[2]);
	FF(wB, wC, wD, wA, awBuffer[3], 22, g_pwSummands[3]);

	FF(wA, wB, wC, wD, awBuffer[4], 7, g_pwSummands[4]);
	FF(wD, wA, wB, wC, awBuffer[5], 12, g_pwSummands[5]);
	FF(wC, wD, wA, wB, awBuffer[6], 17, g_pwSummands[6]);
	FF(wB, wC, wD, wA, awBuffer[7], 22, g_pwSummands[7]);

	FF(wA, wB, wC, wD, awBuffer[8], 7, g_pwSummands[8]);
	FF(wD, wA, wB, wC, awBuffer[9], 12, g_pwSummands[9]);
	FF(wC, wD, wA, wB, awBuffer[10], 17, g_pwSummands[10]);
	FF(wB, wC, wD, wA, awBuffer[11], 22, g_pwSummands[11]);

	FF(wA, wB, wC, wD, awBuffer[12], 7, g_pwSummands[12]);
	FF(wD, wA, wB, wC, awBuffer[13], 12, g_pwSummands[13]);
	FF(wC, wD, wA, wB, awBuffer[14], 17, g_pwSummands[14]);
	FF(wB, wC, wD, wA, awBuffer[15], 22, g_pwSummands[15]);*/

	// Stage 2
	GG(wA, wB, wC, wD, awBuffer[1], 5, 0xf61e2562);
	GG(wD, wA, wB, wC, awBuffer[6], 9, 0xc040b340);
	GG(wC, wD, wA, wB, awBuffer[11], 14, 0x265e5a51);
	GG(wB, wC, wD, wA, awBuffer[0], 20, 0xe9b6c7aa);
	GG(wA, wB, wC, wD, awBuffer[5], 5, 0xd62f105d);
	GG(wD, wA, wB, wC, awBuffer[10], 9,  0x2441453);
	GG(wC, wD, wA, wB, awBuffer[15], 14, 0xd8a1e681);
	GG(wB, wC, wD, wA, awBuffer[4], 20, 0xe7d3fbc8);
	GG(wA, wB, wC, wD, awBuffer[9], 5, 0x21e1cde6);
	GG(wD, wA, wB, wC, awBuffer[14], 9, 0xc33707d6);
	GG(wC, wD, wA, wB, awBuffer[3], 14, 0xf4d50d87);
	GG(wB, wC, wD, wA, awBuffer[8], 20, 0x455a14ed);
	GG(wA, wB, wC, wD, awBuffer[13], 5, 0xa9e3e905);
	GG(wD, wA, wB, wC, awBuffer[2], 9, 0xfcefa3f8);
	GG(wC, wD, wA, wB, awBuffer[7], 14, 0x676f02d9);
	GG(wB, wC, wD, wA, awBuffer[12], 20, 0x8d2a4c8a);
	
	/*GG(wA, wB, wC, wD, awBuffer[1], 5, g_pwSummands[16]);
	GG(wD, wA, wB, wC, awBuffer[6], 9, g_pwSummands[17]);
	GG(wC, wD, wA, wB, awBuffer[11], 14, g_pwSummands[18]);
	GG(wB, wC, wD, wA, awBuffer[0], 20, g_pwSummands[19]);

	GG(wA, wB, wC, wD, awBuffer[5], 5, g_pwSummands[20]);
	GG(wD, wA, wB, wC, awBuffer[10], 9, g_pwSummands[21]);
	GG(wC, wD, wA, wB, awBuffer[15], 14, g_pwSummands[22]);
	GG(wB, wC, wD, wA, awBuffer[4], 20, g_pwSummands[23]);

	GG(wA, wB, wC, wD, awBuffer[9], 5, g_pwSummands[24]);
	GG(wD, wA, wB, wC, awBuffer[14], 9, g_pwSummands[25]);
	GG(wC, wD, wA, wB, awBuffer[3], 14, g_pwSummands[26]);
	GG(wB, wC, wD, wA, awBuffer[8], 20, g_pwSummands[27]);

	GG(wA, wB, wC, wD, awBuffer[13], 5, g_pwSummands[28]);
	GG(wD, wA, wB, wC, awBuffer[2], 9, g_pwSummands[29]);
	GG(wC, wD, wA, wB, awBuffer[7], 14, g_pwSummands[30]);
	GG(wB, wC, wD, wA, awBuffer[12], 20, g_pwSummands[31]);*/

	// Stage 3
	HH(wA, wB, wC, wD, awBuffer[5], 4, 0xfffa3942);
	HH(wD, wA, wB, wC, awBuffer[8], 11, 0x8771f681);
	HH(wC, wD, wA, wB, awBuffer[11], 16, 0x6d9d6122);
	HH(wB, wC, wD, wA, awBuffer[14], 23, 0xfde5380c);
	HH(wA, wB, wC, wD, awBuffer[1], 4, 0xa4beea44);
	HH(wD, wA, wB, wC, awBuffer[4], 11, 0x4bdecfa9);
	HH(wC, wD, wA, wB, awBuffer[7], 16, 0xf6bb4b60);
	HH(wB, wC, wD, wA, awBuffer[10], 23, 0xbebfbc70);
	HH(wA, wB, wC, wD, awBuffer[13], 4, 0x289b7ec6);
	HH(wD, wA, wB, wC, awBuffer[0], 11, 0xeaa127fa);
	HH(wC, wD, wA, wB, awBuffer[3], 16, 0xd4ef3085);
	HH(wB, wC, wD, wA, awBuffer[6], 23,  0x4881d05);
	HH(wA, wB, wC, wD, awBuffer[9], 4, 0xd9d4d039);
	HH(wD, wA, wB, wC, awBuffer[12], 11, 0xe6db99e5);
	HH(wC, wD, wA, wB, awBuffer[15], 16, 0x1fa27cf8);
	HH(wB, wC, wD, wA, awBuffer[2], 23, 0xc4ac5665);

	/*HH(wA, wB, wC, wD, awBuffer[5], 4, g_pwSummands[32]);
	HH(wD, wA, wB, wC, awBuffer[8], 11, g_pwSummands[33]);
	HH(wC, wD, wA, wB, awBuffer[11], 16, g_pwSummands[34]);
	HH(wB, wC, wD, wA, awBuffer[14], 23, g_pwSummands[35]);

	HH(wA, wB, wC, wD, awBuffer[1], 4, g_pwSummands[36]);
	HH(wD, wA, wB, wC, awBuffer[4], 11, g_pwSummands[37]);
	HH(wC, wD, wA, wB, awBuffer[7], 16, g_pwSummands[38]);
	HH(wB, wC, wD, wA, awBuffer[10], 23, g_pwSummands[39]);

	HH(wA, wB, wC, wD, awBuffer[13], 4, g_pwSummands[40]);
	HH(wD, wA, wB, wC, awBuffer[0], 11, g_pwSummands[41]);
	HH(wC, wD, wA, wB, awBuffer[3], 16, g_pwSummands[42]);
	HH(wB, wC, wD, wA, awBuffer[6], 23, g_pwSummands[43]);

	HH(wA, wB, wC, wD, awBuffer[8], 4, g_pwSummands[44]);
	HH(wD, wA, wB, wC, awBuffer[12], 11, g_pwSummands[45]);
	HH(wC, wD, wA, wB, awBuffer[15], 16, g_pwSummands[46]);
	HH(wB, wC, wD, wA, awBuffer[2], 23, g_pwSummands[47]);*/

	// Stage 4
	II(wA, wB, wC, wD, awBuffer[0], 6, 0xf4292244);
	II(wD, wA, wB, wC, awBuffer[7], 10, 0x432aff97);
	II(wC, wD, wA, wB, awBuffer[14], 15, 0xab9423a7);
	II(wB, wC, wD, wA, awBuffer[5], 21, 0xfc93a039);
	II(wA, wB, wC, wD, awBuffer[12], 6, 0x655b59c3);
	II(wD, wA, wB, wC, awBuffer[3], 10, 0x8f0ccc92);
	II(wC, wD, wA, wB, awBuffer[10], 15, 0xffeff47d);
	II(wB, wC, wD, wA, awBuffer[1], 21, 0x85845dd1);
	II(wA, wB, wC, wD, awBuffer[8], 6, 0x6fa87e4f);
	II(wD, wA, wB, wC, awBuffer[15], 10, 0xfe2ce6e0);
	II(wC, wD, wA, wB, awBuffer[6], 15, 0xa3014314);
	II(wB, wC, wD, wA, awBuffer[13], 21, 0x4e0811a1);
	II(wA, wB, wC, wD, awBuffer[4], 6, 0xf7537e82);
	II(wD, wA, wB, wC, awBuffer[11], 10, 0xbd3af235);
	II(wC, wD, wA, wB, awBuffer[2], 15, 0x2ad7d2bb);
	II(wB, wC, wD, wA, awBuffer[9], 21, 0xeb86d391);

	/*II(wA, wB, wC, wD, awBuffer[0], 6, g_pwSummands[48]);
	II(wD, wA, wB, wC, awBuffer[7], 10, g_pwSummands[49]);
	II(wC, wD, wA, wB, awBuffer[14], 15, g_pwSummands[50]);
	II(wB, wC, wD, wA, awBuffer[5], 21, g_pwSummands[51]);

	II(wA, wB, wC, wD, awBuffer[12], 6, g_pwSummands[52]);
	II(wD, wA, wB, wC, awBuffer[3], 10, g_pwSummands[53]);
	II(wC, wD, wA, wB, awBuffer[10], 15, g_pwSummands[54]);
	II(wB, wC, wD, wA, awBuffer[1], 21, g_pwSummands[55]);

	II(wA, wB, wC, wD, awBuffer[8], 6, g_pwSummands[56]);
	II(wD, wA, wB, wC, awBuffer[15], 10, g_pwSummands[57]);
	II(wC, wD, wA, wB, awBuffer[6], 15, g_pwSummands[58]);
	II(wB, wC, wD, wA, awBuffer[13], 21, g_pwSummands[59]);

	II(wA, wB, wC, wD, awBuffer[4], 6, g_pwSummands[60]);
	II(wD, wA, wB, wC, awBuffer[11], 10, g_pwSummands[61]);
	II(wC, wD, wA, wB, awBuffer[2], 15, g_pwSummands[62]);
	II(wB, wC, wD, wA, awBuffer[9], 21, g_pwSummands[63]);*/

	// Now we add resulting values to the MD5 hash structure
	hMd5.wA += wA;
	hMd5.wB += wB;
	hMd5.wC += wC;
	hMd5.wD += wD;

	// Deleting sensitive information
	memset(awBuffer, 0, sizeof(MD5_WORD) * 16);

	return TRUE;
}

MD5_API BOOL Md5EqualHashes(const MD5DIGEST& dMd5A, const MD5DIGEST& dMd5B)
{
	return (0 == memcmp(&dMd5A, &dMd5B, sizeof(MD5DIGEST)));
	/*return ((hsMd5A.wA == hsMd5B.wA) &&
		(hsMd5A.wB == hsMd5B.wB) &&
		(hsMd5A.wC == hsMd5B.wC) &&
		(hsMd5A.wD == hsMd5B.wD));*/
}

MD5_API BOOL Md5EncodeBytes(MD5_BYTE *pBuffer, const MD5_WORD *pwData, size_t sLength)
{
	for(size_t i = 0, j = 0; j < sLength; ++i, j += 4)
	{
		pBuffer[j] = (MD5_BYTE)(pwData[i] & 0xFF);
		pBuffer[j + 1] = (MD5_BYTE)((pwData[i] >> 8) & 0xFF);
		pBuffer[j + 2] = (MD5_BYTE)((pwData[i] >> 16) & 0xFF);
		pBuffer[j + 3] = (MD5_BYTE)((pwData[i] >> 24) & 0xFF);
	} // for

	return TRUE;
}

MD5_API BOOL Md5DecodeBytes(MD5_WORD *pwData, const MD5_BYTE *pBuffer, size_t sLength)
{
	for(size_t i = 0, j = 0; j < sLength; ++i, j += 4)
	{
		pwData[i] = ((MD5_WORD)pBuffer[j]) | (((MD5_WORD)pBuffer[j + 1]) << 8) |
			(((MD5_WORD)pBuffer[j + 2]) << 16) | (((MD5_WORD)pBuffer[j + 3]) << 24);
	} // for

	return TRUE;
}