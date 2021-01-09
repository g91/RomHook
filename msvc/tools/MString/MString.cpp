
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <memory.h>
#include <string.h>
//#include <tchar.h>

#include "MString.h"

inline int IsCharAlphabetA(const unsigned char *ch)
{
	switch(ch[0])
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		return 1;

	case 0xE3:
		switch(ch[1])
		{
		case 0x80:
		case 0x81:
		case 0x82:
		case 0x83:
		case 0x84:
		case 0x85:
		case 0x86:
		case 0x87:
		case 0x88:
		case 0x89:
		case 0x8A:
		case 0x8B:
		case 0x8C:
		case 0x8D:
		case 0x8E:
		case 0x8F:
		case 0x90:
		case 0x91:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		case 0x96:
		
		case 0x98:
		case 0x99:
		case 0x9A:
		case 0x9B:
		case 0x9C:
		case 0x9D:
		case 0x9E:
		case 0x9F:
		case 0xA0:
		case 0xA1:
		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		case 0xA8:
		case 0xA9:
		case 0xAA:
		case 0xAB:
		case 0xAC:
		case 0xAD:
		case 0xAE:
		case 0xAF:
		case 0xB0:
		case 0xB1:
		case 0xB2:
		case 0xB3:
		case 0xB4:
		case 0xB5:
		case 0xB6:
		
		case 0xB8:
		case 0xB9:
		case 0xBA:
		case 0xBB:
		case 0xBC:
		case 0xBD:
		case 0xBE:
		case 0xBF:
			return 2;
		}

	case 0xE5:
		if (ch[1] == 0xB8)
			return 2;
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: CharAlphabetA()
// Desc: 取得歐美單字長度
// Arg : const char* inString 來源字串
//		 int iLength 來源字串長度
// return : 回傳字串長度
//-----------------------------------------------------------------------------
int SeparateStringA(const unsigned char* inString, int iLength)
{
	int iLen = 0;
	if ( inString == NULL || iLength <= 0 )
		return iLen;
	
	int chLen;
	if ( (chLen = IsCharAlphabetA(inString + iLen)) > 0 )
	{
		iLen += chLen;
		while ( iLen < iLength )
		{
			if ( (chLen = IsCharAlphabetA(inString + iLen)) > 0 )
				iLen += chLen;
			else
				break;
		}
	}
	else
	{
		iLen++;
		while ( iLen < iLength )
		{
			if ( IsCharAlphabetA(inString + iLen) == 0 )
				iLen++;
			else
				break;
		}
	}
	
	return (iLen == 0) ? 1 : iLen;
}

//-----------------------------------------------------------------------------
// Name: IntToStr()
// Desc: 數值轉換成字串並會考慮字串所要產生位置
// Arg : char *pDest 儲存轉換後字串資料
//		 int iValue 欲轉換的數值
//		 int iPosi 類似 printf("%2d")中2d的效果,設定此參數會在轉換後比對字串長
//		 度是否小於iPosi設定值,若小於則補上空格
// return : 回傳經轉換後目的字串新的指標位置
//-----------------------------------------------------------------------------
char* IntToStrA( char *pDest ,int iValue, int iPosi )
{
	char* pTemp = pDest;
	if ( iValue < 0 )
	{
		*pDest++ = '-';
		iValue = -iValue;
	}
	for ( int i=1; i<=1000000000; i*=10 )
		if ( iValue/(i*10) == 0 )
		{
			for ( int j=i; j>0 ; j/=10 )
			{
				*pDest++ = 48+iValue/j;
				iValue %= j;
			}

			if ( iPosi == 0 )
				return pDest;
			else if ( iPosi < 0 )
			{
				int iLen = pDest-pTemp;
				iPosi = -iPosi;	
				for ( ; iLen<iPosi; iLen++ )
					*pDest++ = ' ';
				return pDest;
			}
			else
			{
				int iLen = pDest-pTemp;
				if ( iLen < iPosi )
				{
					pDest += iPosi-iLen;
					memmove( pTemp+iPosi-iLen, pTemp, iLen );
					for ( ;iLen<iPosi ; iLen++ )
						*pTemp++ = ' ';					
				}
				return pDest;
			}
		}

	return pDest;
}


//-----------------------------------------------------------------------------
// Name: CommandAnalytic()
// Desc: 檢查字串是否為轉換控制碼
// Arg : const char* string 來源字串
//		 int* piLen 字串前進距離,控制碼所佔字元個數
// return : 回傳控制碼類型
//-----------------------------------------------------------------------------
int CommandAnalyticA( const char* string, int* piLen )
{
	int iSrc = 0;
	*piLen = 0;
	if ( string[iSrc++] == '%' )
	{
		// 如果下一個為%符號
		if ( string[iSrc] == '%' )
		{
			*piLen = iSrc;
			return 0;
		}

		while(1)
		{
			// 字元若為數字、小數點或負號
			if ( (string[iSrc]>='0' && string[iSrc]<='9') || string[iSrc]=='.' || string[iSrc]=='-' )
				iSrc++;
			else if ( string[iSrc] == 0 )
				return 0;
			else
			{
				switch (string[iSrc])
				{
				// 字元
				case 'c':
				case 'C':
					*piLen = iSrc+1;
					return 1;
				// 數字
				case 'd':
				case 'D':
					*piLen = iSrc+1;
					return 2;
				// 浮點數
				case 'f':
				case 'F':
					*piLen = iSrc+1;
					return 3;
				// 字串
				case 's':
				case 'S':
					*piLen = iSrc+1;
					return 4;
				// 數字16進位
				case 'x':
				case 'X':
					*piLen = iSrc+1;
					return 5;
				default:
					return 0;
				}
			}
		}
	}
	return 0;
}


//-----------------------------------------------------------------------------
// Name: ChangeString()
// Desc: 轉換字串中的特殊控制碼字元
// Arg : char* dest 目的字串
//		 const char* format_string 來源字串
//		 ... 不定參數個數
// return : 0
//-----------------------------------------------------------------------------
void SwapStringA( char* dest, const char* format_string, ... )
{
	va_list argp;	
	va_start( argp, format_string );
	SwapStringExA( dest, format_string, argp );
	va_end( argp );
}

//-----------------------------------------------------------------------------
// Name: ChangeString()
// Desc: 轉換字串中的特殊控制碼字元
// Arg : char* dest 目的字串
//		 const char* format_string 來源字串
//		 ... 不定參數個數
// return : 0
//-----------------------------------------------------------------------------
void SwapStringExA( char* dest, const char* format_string, va_list argp )
{
	char	bTemp[32];
	char	szOperation[32];
	int		iSrc=0;
	int		iNext,iLen;
	int		iArg;
	double	dArg;
	char*	pArg;
	char	bArg;
	
	while ( format_string[iSrc] != 0 )
	{
		switch( CommandAnalyticA( &format_string[iSrc], &iNext ) )
		{
			// Non
			case 0:				
				*dest++ = format_string[iSrc+iNext];
				iNext++;
				break;
			// char 
			case 1:
				bArg = va_arg( argp, char );
				*dest++ = bArg;
				break;
			// int
			case 2:				
				iArg = va_arg( argp, int );
				memcpy( szOperation, &format_string[iSrc+1], iNext-1 );
				szOperation[iNext-1] = 0;
				dest = IntToStrA( dest, iArg, atoi(szOperation) );
				break;
			// float
			case 3:
				dArg = va_arg( argp, double);
				memcpy( szOperation, &format_string[iSrc], iNext );
				szOperation[iNext] = 0;
				sprintf( bTemp, szOperation, dArg );
				iLen = strlen(bTemp);
				memcpy( dest, bTemp, iLen );
				dest += iLen;
				break;
			// string
			case 4:
				pArg = va_arg( argp, char* );				
				if ( (int)pArg > 0xFFFF ) 
				{
					//iLen = strlen(pArg);
					iLen = 0;
					while (iLen < 1024 && pArg[iLen]) iLen++;
					memcpy( dest, pArg, iLen );
					dest += iLen;
				}
				break;
			// int 16HEX
			case 5:
				iArg = va_arg( argp, int );
				memcpy( szOperation, &format_string[iSrc], iNext );
				szOperation[iNext] = 0;
				sprintf( bTemp, szOperation, iArg );
				iLen = strlen(bTemp);
				memcpy( dest, bTemp, iLen );
				dest += iLen;
				break;
		}

		iSrc += iNext;
	}
	*dest = '\0';
}

//-----------------------------------------------------------------------------
// Name: CharDouble()
// Desc: 判斷是否為雙字元組
// Arg : const char* dest 判斷字元
// return : 0否 1是
//-----------------------------------------------------------------------------
int CharDouble(const char* dest)
{
	if (dest)
		return *dest&0x80;
	return 0;
}

//-----------------------------------------------------------------------------
// Name: _m_show_char()
// Desc: 是否為可見字元(32 ~ 127)
// Arg : unsigned char ch 判斷字元
// return : 0否 1是
//-----------------------------------------------------------------------------
int _m_show_char(char ch)
{
	return (ch>=32 && ch<=127);
}


//-----------------------------------------------------------------------------
// Name: CopyString()
// Desc: 複製字串
// Arg : const char* src 來源字串
//		 char* des 目的字串
//		 iLimit 指定複製到目的字串的長度
//		 pChar 字元比對函式,用以判斷該字元是要算一個字元數量,比如有些程式可能會
//		 使用一些小於0x20的數值為控制碼,當在複製字串時可能會希望控制碼不算在字
//		 串長度內.
// return : 來源字串實際複製字元數
//-----------------------------------------------------------------------------
int CopyString(char* des, const char* src, int iLimit, pFCompareChar pfChar)
{	
	return _m_strncpy(des, src, iLimit, pfChar);	
}

//-----------------------------------------------------------------------------
// Name: _m_strncpy()
// Desc: 複製指定長度字串到目的字串內,並可指定是否忽略計算某些字元
// Arg : char* des 目的字串指標
//		 const char* src 來源字串
//		 iLimit 限制複製字元數(BYTE)
//		 pfChar 字元比對函式,若傳回false則該字元會加入目的字串內,但不計算該字元
//				長度,主要用以將一些控制碼複製到目的字串內,但只計算可顯示的字元
//				長度
// return : 來源字串實際複製字元數
//-----------------------------------------------------------------------------
int _m_strncpy(char* des, const char* src, int iLimit, pFCompareChar pfChar)
{
	int iNow = 0;
	int iLen = 0;
	int iWord;
	int iHave;
	if ( src==NULL || des==NULL || iLimit<=0 )
		return NULL;

	while(*src)
	{
		// 判斷是否為雙字組
		if (*src & 0x80)
			iWord = 2;
		else
			iWord = 1;

		if (iLen+iWord > iLimit)
			break;
		else
		{
			if (iWord==2)
			{
				*des++ = *src++;
				*des++ = *src++;
				iLen += 2;
				iNow += 2;
			}
			else
			{
				iHave = 1;
				if (pfChar)
					iHave = pfChar(*src);
				if (iHave)
					iLen++;
				*des++ = *src++;
				iNow++;

				if (*(src-1) == '\n')
					break;
			}
		}
	}
	*des = 0;
	return iNow;
}


// ----------------------------------------------------------------------------
// 將字串依指定大小(Byte),中間加入指定符號
int SizeAddChar(char* des, char* src, int iLimit, char ch, pFCompareChar pChar)
{
	int iSrc = 0;
	int iDes = 0;
	int iLine = 0;
	int iLen;
	
	while(src[iSrc])
	{
		iLen = CopyString(des+iDes, src+iSrc, iLimit, pChar);
		iSrc += iLen;
		iDes += iLen;
		iLine++;
		if (src[iSrc])
			des[iDes++] = ch;
	}
	des[iDes] = 0;
	return iLine;
}

// ----------------------------------------------------------------------------
// 裁切顯示字串為指定大小
int ClipText(char* des, char* src, int iLimit)
{
	int iSrc = 0;
	int iDes = 0;
	int iLine = 0;
	int iMax = 0;
	int iLen;	
	
	while(src[iSrc])
	{
		iLen = CopyString(des+iDes, src+iSrc, iLimit, _m_show_char);
		iSrc += iLen;
		iDes += iLen;
		iLine++;
		if (src[iSrc] && des[iDes-1]!='\n')
		{
			des[iDes++] = '\n';
			if (src[iSrc] == '\n')
				iSrc++;
		}
	}
	des[iDes] = 0;
	return iLine;
}


// ----------------------------------------------------------------------------
// 傳回可顯示的最大字串長度,若不能顯示字元不算在內,當有換行字元時,重新計算
int _m_show_strlen(char* src)
{	
	int iMax = 0;
	int iLen = 0;

	if (src)
	{
		while(*src)
		{	
			if (*src & 0x80)
			{
				src++;
				iLen += 2;
			}
			else if (*src == '\n')
			{
				if (iLen>iMax)
				{
					iMax = iLen;
					iLen = 0;
				}
			}
			else if (*src >= 32)
				iLen++;
			src++;
		}

		if (iLen>iMax)
			iMax = iLen;
	}
	return iMax;
}


// ----------------------------------------------------------------------------
// 取得顯示字串最大寬度字元數
int ShowTextWidth(char* src)
{
	return _m_show_strlen(src);
}


// ----------------------------------------------------------------------------
// 計算字串顯示時寬高大小
void _m_Show_Text_Dimension(char* pSrc, int* piWidth, int* piHeight)
{
	int iMax = 0;
	int iLen = 0;
	int iY = 1;

	if (pSrc)
	{
		while(*pSrc)
		{	
			if (*pSrc & 0x80)
			{
				pSrc++;
				iLen += 2;
			}
			else if (*pSrc == '\n')
			{
				iY++;
				if (iLen>iMax)
				{
					iMax = iLen;
					iLen = 0;
				}				
			}
			else if (*pSrc >= 32)
				iLen++;
			pSrc++;
		}

		if (iLen>iMax)
			iMax = iLen;
	}

	if (piWidth)
		*piWidth = iMax;
	if (piHeight)
		*piHeight = iY;
}


// ----------------------------------------------------------------------------
// 取代字串中指定字元為另一字元
void _m_Replace_Text_Char(char* pText, char cDes, char cSrc)
{
	if (pText)
	{
		int iLen = 0;
		while(pText[iLen])
		{
			if (pText[iLen]&0x80)
				iLen += 2;
			else
			{
				if (pText[iLen] == cDes)
					pText[iLen] = cSrc;
				iLen++;
			}
		}
	}
}


// ----------------------------------------------------------------------------
// 搜尋字元最後出現在字串的位置
int _m_Search_Last_Char(const char* pSrc, char ch)
{
	int iLast = -1;
	int iCount = 0;
	if (pSrc)
	{
		while(pSrc[iCount])
		{
			if (pSrc[iCount] & 0x80)
				iCount += 2;
			else
			{
				if (pSrc[iCount] == ch)
					iLast = iCount;
				iCount++;
			}		
		}
	}
	return iLast;
}