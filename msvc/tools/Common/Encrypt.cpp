
#include "Encrypt.h"

#define DF_CIPHERMAX 256

DWORD CEncrypt::m_dwCipher[DF_CIPHERMAX] =
{
	0x5B5624FB , 0x2A75E7E3 , 0xC67B92C1 , 0x800AAF52 , 
	0xEEFBB098 , 0xCC69B7B7 , 0x16B2CE28 , 0x3F6961B9 , 
	0x9D762F6B , 0x1BE40D43 , 0xB513230A , 0xC094FD3D , 
	0xDF5F0CEE , 0xAF506231 , 0x3C1529CF , 0xEA02CC36 , 
	0x3D1EDC97 , 0xE1535DF7 , 0x1232560F , 0xF53C655C , 
	0x2E3A09F0 , 0x6756461E , 0xC0F03422 , 0x899A4007 , 
	0x3A3C2A8F , 0x9CD1C5FE , 0xCDD83BCF , 0x0FC4F6BE , 
	0xD99DB7CC , 0x055C432F , 0xA152E15F , 0x0E32FE0A , 
	0x94D21931 , 0x3C5F5729 , 0xE4F6B05A , 0xFF6BB063 , 
	0xE286F765 , 0x98516A83 , 0xFF3C3F38 , 0x69D9B551 , 
	0x6C00BABF , 0xB2DB02A6 , 0x69ABD791 , 0xC402935C , 
	0x68E7E8C8 , 0x0055A92A , 0xBAAC2FEC , 0xA88FA5EB , 
	0x80B4FBF8 , 0x1D57E767 , 0x4BD79FA3 , 0x8EB79088 , 
	0x4CDF6BE7 , 0x5E691205 , 0xC394BF6C , 0xDD24CEB9 , 
	0x12E0DEFC , 0x5DE2D46B , 0x9A8B0880 , 0x2D6CB6F6 , 
	0x8C5EAEC0 , 0x916BA423 , 0x4913F197 , 0xE7D8F0C9 , 
	0x119352CC , 0x827CFBB3 , 0x47B51318 , 0xA21005B9 , 
	0x3A457375 , 0xA97D5094 , 0x2C09D49D , 0xD68C5C2D , 
	0x6EDD8856 , 0x8D064B4D , 0x5177CE7C , 0x0CC47EBE , 
	0x35C2F9E6 , 0xA69F3548 , 0x6C87595E , 0xBB3FD1C4 , 
	0x289E4EAC , 0x7C9FA41B , 0xC8B11B9A , 0x5B760FF7 , 
	0xADC71011 , 0x88AF2230 , 0x0A8C8EDA , 0x75F17FAE , 
	0x4FD7B6BD , 0x5237372C , 0xAC711985 , 0x8038BA73 , 
	0x7344D908 , 0x50CF4A6A , 0x15084512 , 0x14B347DC , 
	0xC397DF8A , 0x0CDEE381 , 0xEDC9B92A , 0x99F99E42 , 
	0xB64733CA , 0xFDEE8AE8 , 0x8D1BBD25 , 0x9874284D , 
	0xB4EE8A22 , 0xAC75B819 , 0x8C88FA9A , 0x88BA9C44 , 
	0x46D24E48 , 0x8F0CF4AA , 0x53A6D7F3 , 0xF23432F1 , 
	0xF3BCE685 , 0x201BB6F3 , 0x88DEDCC6 , 0x6C89B2AA , 
	0x43E4FA80 , 0xF73987AE , 0x95B8818C , 0x410375E8 , 
	0xAF02E2A3 , 0x8BC0DE22 , 0xF2AB6FBD , 0x2648F233 , 
	0xAE7D4784 , 0x545633E6 , 0x2541EDE1 , 0x75D1C113 , 
	0xC8DF819C , 0xDA741F83 , 0xB8008370 , 0xC5166B1F , 
	0x769E3653 , 0x96920871 , 0x2261EAF1 , 0x8EAF4791 , 
	0x3F33D041 , 0x0F287938 , 0xFCDC69FD , 0x49E4FE2F , 
	0x9B36D6EE , 0xADCDF74F , 0x8DF988DC , 0x8C7CE652 , 
	0x121EC1B1 , 0x18EA0C2F , 0x8D3FD036 , 0xB2C0A981 , 
	0x2D551833 , 0xB9F71F51 , 0x5418C872 , 0x5058AE56 , 
	0x537153EC , 0x089CB95B , 0x7B2AE83A , 0x00AC7E37 , 
	0x1DFBFA44 , 0x9B3150B5 , 0x89CEB9E4 , 0x193490AE , 
	0xF25B86D3 , 0xEC5E8ED9 , 0xD78CA209 , 0x34877C11 , 
	0x7A197E20 , 0x627ABB4D , 0x1BEB4B11 , 0xC81F9B28 , 
	0x0DCC5A95 , 0x961E7D9B , 0x9F740C94 , 0x4D62944D , 
	0x24CDA3C8 , 0x1EB23E29 , 0x0B907E09 , 0x4BF9CFF7 , 
	0x76B4D012 , 0x34EE8690 , 0xC5E518EA , 0x4B4BD4BD , 
	0x4BF9792A , 0xA00AEB47 , 0x57CC53BD , 0xB4E22C18 , 
	0x4C24F75A , 0xC9ADC7D8 , 0x49DCB6FB , 0x2E343E70 , 
	0xC0ADE148 , 0x1750B2B9 , 0x117FC92B , 0x02CA936C , 
	0x7F1BCF6D , 0x227B2263 , 0x394B04C7 , 0xE72CC166 , 
	0xB1E70931 , 0x73A6A15E , 0x38B9E065 , 0x35B23204 , 
	0x0F99283C , 0x7149B622 , 0x8741F46E , 0x85147EAF , 
	0xF1A9B4E6 , 0xB4FCCA46 , 0xBD7BB86A , 0x5EB9FBEF , 
	0x0D9F33C6 , 0xA4265434 , 0x32CE95C1 , 0x181A432C , 
	0xADE21F55 , 0xDA40FC72 , 0x9FB3122B , 0x4CAFDE0E , 
	0x681BEF1B , 0xBDF22A99 , 0x5AC3C7FF , 0x710032FC , 
	0xB6A21B80 , 0xD6A457F1 , 0xED732DA7 , 0x2FA5E96F , 
	0x201F3C2C , 0xBCDD1A21 , 0xD04EABD9 , 0xDE055AFF , 
	0x3DEAC986 , 0xC707DBB3 , 0x9ACBD9FD , 0xE7AA0E14 , 
	0x56AA3B07 , 0x9FB8230D , 0xB3512F8D , 0x010A9C46 , 
	0x01B90848 , 0x9D7989A8 , 0xA3992600 , 0x95BE5C0C , 
	0xE8BDCAAE , 0x58A2652C , 0xF3EB45FD , 0x291DF6DF , 
	0x430FF8C4 , 0x49DA50F0 , 0x2AEF25DD , 0x27B1D337 , 
	0xD8460B01 , 0xF68BC18E , 0xA0FD1D28 , 0x17207ABC , 
	0xE1DC8A0C , 0xE94B407C , 0xFEBCB576 , 0x90C364B6 
};

//========================================================================
//¥[±K
//========================================================================
CEncrypt::CEncrypt(void)
{

}

CEncrypt::~CEncrypt(void)
{

}

//¥[¸Ñ±K
void CEncrypt::Encrypt( LPVOID pDestination , LPCVOID pSource , DWORD dwSize , DWORD dwCipher )
{
	//A( 0 == dwSize % 4 );
	//A( 0 == dwOffset % 4 );

 	//dwSize = dwSize / 4;														   
	//dwOffset = dwOffset / 4;

	UINT nQuo = dwSize / 4; 
	UINT nRem = dwSize % 4;

	DWORD* pdwSource = (DWORD*)pSource;
	DWORD* pdwDestination = (DWORD*)pDestination;

	LPBYTE pBYTE = (LPBYTE)&dwCipher;
 	DWORD index = (DWORD)( pBYTE[0] ^ pBYTE[1] ^ pBYTE[2] ^ pBYTE[3] );

	UINT i;
	for( i = 0 ; i < nQuo ; ++i )
	{
		pdwDestination[i] = pdwSource[i] ^ m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] ^ dwCipher; //XOR
	}


	if( nRem == 1 )
	{
		( (LPBYTE)&pdwDestination[i] )[0] = ( (LPBYTE)&pdwSource[i] )[0] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[0];
	}
	else if( nRem == 2 )
	{
		( (LPBYTE)&pdwDestination[i] )[0] = ( (LPBYTE)&pdwSource[i] )[0] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[0];
		( (LPBYTE)&pdwDestination[i] )[1] = ( (LPBYTE)&pdwSource[i] )[1] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[1];
	}
	else if( nRem == 3 )
	{
		( (LPBYTE)&pdwDestination[i] )[0] = ( (LPBYTE)&pdwSource[i] )[0] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[0];
		( (LPBYTE)&pdwDestination[i] )[1] = ( (LPBYTE)&pdwSource[i] )[1] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[1];
		( (LPBYTE)&pdwDestination[i] )[2] = ( (LPBYTE)&pdwSource[i] )[2] ^ ( (LPBYTE)&m_dwCipher[ ( i + index ) % DF_CIPHERMAX ] )[2];
	}

}

DWORD* CEncrypt::GetCipher()
{
	return m_dwCipher;
}




//========================================================================
//CEncryptData
//========================================================================
CEncryptData::CEncryptData( LONG nOffset )
{
	if( nOffset < 0 )
		nOffset = rand();

	m_nOffset = nOffset % DF_CIPHERMAX; 
}
CEncryptData::~CEncryptData(void)
{

}


//========================================================================
//CEncryptLONG
//========================================================================
CEncryptLONG::CEncryptLONG( LONG lData , LONG nOffset ) : 
CEncryptData( nOffset ) 
{
	*this = lData;
}
CEncryptLONG::~CEncryptLONG(void)
{

}

//========================================================================
//CEncryptFLOAT
//========================================================================
CEncryptFLOAT::CEncryptFLOAT( FLOAT fData , LONG nOffset ) :
CEncryptData( nOffset )
{
	*this = fData;
}

CEncryptFLOAT::~CEncryptFLOAT(void)
{

}

//========================================================================
//CEncryptDouble
//========================================================================
CEncryptDouble::CEncryptDouble( double Val , LONG nOffset ) :
CEncryptData( nOffset )
{
	*this = Val;
}

CEncryptDouble::~CEncryptDouble(void)
{

}

