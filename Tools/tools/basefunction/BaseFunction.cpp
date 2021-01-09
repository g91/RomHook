#pragma warning (disable:4949)
#pragma warning(disable : 4996)

#include "BaseFunction.h"
#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include <assert.h>
#include <psapi.h>

#pragma unmanaged

#define _1900_1970_DAY_COUNT_ 25567
//-------------------------------------------------------------------------------------
//檔案所在路徑與檔名結合
//-------------------------------------------------------------------------------------
char* CombineFilePath( const char* _Path , const char* File )
{
	static char Buf[512];
    char*   Path =( char* )_Path;
	for( int i= int(strlen(Path)-1) ; i >=0 ; i-- )
	{
		if( Path[i] != ' ' && Path[i] != '\t')
			break;

		Path[i] = '\0';
	}

	if(		Path[strlen(Path)-1] == '\\' 
		|| 	Path[strlen(Path)-1] == '/')
		sprintf( Buf , "%s%s",Path ,File );
	else
		sprintf( Buf , "%s\\%s",Path ,File );

	return Buf;
}

#define _SMATH_EPSILON			1.0e-4f						//1E-6f

bool FloatEQU ( float X , float Y )
{
    return (((X - _SMATH_EPSILON) < Y) && (Y < ( X + _SMATH_EPSILON)));
}

bool CheckFloatAvlid( float X )
{
    struct 
    {
        union
        {
            float Value;
            struct
            {
                unsigned int     Fraction : 23;
                unsigned int     Exponent : 8;
                unsigned int     Sign :1;
            };
        };
    }Float;

    Float.Value = X;
    if( Float.Exponent == 0 && Float.Fraction != 0 )
        return false;
    if( Float.Exponent == 255 )
        return false;
    return true;
}

string FloatToStr( float Value )
{
	char Buf[64];
	sprintf( Buf , "%f" , Value );
	return Buf;
}
//資料轉換
string  IntToStr( int Value )
{
    char Buf[32];
    sprintf( Buf , "%d" , Value );
    return Buf;
}

int		 StrToNum( const char* Str, int Size )
{
	char	Buf[32];
	memset( Buf , 0 , sizeof(Buf) );
	memcpy( Buf , Str , Size );
	return atol( Buf );
}

unsigned int MytimeGetTime( )
{
    static unsigned int  BeginTime = timeGetTime();
    return timeGetTime() - BeginTime;
}
//-------------------------------------------------------------------------------------
vector<string>*	AllPathList( string SrcPath )
{
    static vector<string> AllPath;
    string Path;
    vector<string> OpenPath;
    struct _finddata_t c_file;
    long	hFile;

    char Findmask[512];
    char Buf[512];

    AllPath.clear();
    OpenPath.clear();

    const char *P = SrcPath.c_str();
    if( P[ SrcPath.length() - 1] != '\\' && SrcPath.length() != 0 )
        SrcPath += "\\";


    OpenPath.push_back( "" );


    while( OpenPath.size() )
    {
        Path = OpenPath.back();

        AllPath.push_back( Path );

        OpenPath.pop_back();
        sprintf( Findmask , "%s%s*." , SrcPath.c_str() , Path.c_str() );

        if( (hFile = (long)_findfirst( (char*)Findmask , &c_file )) != -1L )
        {

            do
            {
                if( !(c_file.attrib & _A_SUBDIR) )
                    continue;

                if( c_file.name[0] == '.' )
                    continue;

                //TempPath = Path + c_file.name + "\\";
                sprintf( Buf , "%s%s\\", Path.c_str() , c_file.name );
                OpenPath.push_back( Buf );


            }while( _findnext( hFile, &c_file ) == 0 );


            _findclose( hFile );
        }
    }

    return &AllPath;
}
vector<string>*	AllPathList_Pure( string Path )
{
    vector<string>*	Ret;
    char CurPath[ _MAX_PATH ];

    if( _getcwd( CurPath, _MAX_PATH ) == NULL )
        return NULL;

    _chdir( Path.c_str() );

    Ret = AllPathList( "" );

    _chdir( CurPath );

    return Ret;
}

vector<string>*	AllFileList_Sub( string Path , string Sub )
{
    vector<string>*	Ret;
    char CurPath[ _MAX_PATH ];

    if( _getcwd( CurPath, _MAX_PATH ) == NULL )
        return NULL;

    _chdir( Path.c_str() );

    Ret = AllFileList( "" , Sub );

    _chdir( CurPath );

    return Ret;
}
//-------------------------------------------------------------------------------------
bool	CreateAllPath( string Path , vector<string>& PathList )
{
    char CurPath[ _MAX_PATH ];

    if( _getcwd( CurPath, _MAX_PATH ) == NULL )
        return false;

    _mkdir( Path.c_str() );
    _chdir( Path.c_str() );
    for( int i = 0 ; i < (int)PathList.size() ; i++ )
    {
        _mkdir( PathList[i].c_str() );
    }

    _chdir( CurPath );

    return true;

}
//-------------------------------------------------------------------------------------

vector<string>*	AllFileList( string Path , string Sub )
{
    static vector<string> AllFilePath;
    vector<string>* AllPath = AllPathList( Path );

    if(		Path.c_str()[ Path.length() - 1 ] != '\\' 
        &&	Path.c_str()[ Path.length() - 1 ] != '/'	)
        Path += "\\";

    AllFilePath.clear();
    string Temp;
    for( int i = 0 ; i < (int)AllPath->size() ; i++ )
    {
        Path = (*AllPath)[i] + Sub;

        WIN32_FIND_DATA  file_data;
        HANDLE	hfile = FindFirstFile(Path.c_str(), &file_data);
        if(hfile == INVALID_HANDLE_VALUE)
            continue;
            //return &AllFilePath;

		if( (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			AllFilePath.push_back( (*AllPath)[i] + file_data.cFileName );


        while(FindNextFile(hfile, &file_data))
        {
			if( (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				AllFilePath.push_back( (*AllPath)[i] + file_data.cFileName );
        }

    }

    return &AllFilePath;

}
string  StringToSqlX( const char* Str , int Size , bool IsNullEnd )
{    
    //bool    NullEnd = false;
    int     i;
    if( Str == NULL )
        return "0x00";
    if( Size == 0)
    {
        Size = 0x10000 / 2 -2;
//        NullEnd = true;
    }

	assert( Size*2+2 <= 0x10000 );
    //static char Ret[ 2 ] = { '0' , 'x' };
    char OutStr[0x10000 ] = { '0' , 'x' };
    
    for( i = 0 ; i < Size ; i++ )
    {
        if( Str[i] == 0 && IsNullEnd != false )
            break;

        sprintf( OutStr+i*2+2 , "%02x" , (unsigned char)Str[i] );

    }
    if( i == 0  )
    {
        sprintf( OutStr+i*2+2 , "0000" );
    }
	else
	{
		OutStr[ i*2+2 ] = 0;
	}
    return OutStr;
}

string  WStringToSqlX( const wchar_t* Str , int Size  )
{    
	//bool    NullEnd = false;
	int     i;
	if( Str == NULL )
		return "0x0000";
	if( Size == 0)
	{
		Size = 0x10000 / 2 -2;
	}

	assert( Size*2+2 <= 0x10000 );
	//static char Ret[ 2 ] = { '0' , 'x' };
	char OutStr[0x10000 ] = { '0' , 'x' };

	for( i = 0 ; i < Size ; i++ )
	{
		if( Str[i] == 0  )
			break;
		unsigned char* p = (unsigned char*)(Str+i);

		sprintf( OutStr+i*4+2 , "%02x%02x" , p[0] , p[1] );

	}
	if( i == 0  )
	{
		sprintf( OutStr+i*4+4 , "0000" );
	}
	else
	{
		OutStr[ i*4+2 ] = 0;
		OutStr[ i*4+3 ] = 0;
	}
	return OutStr;
}


string   StringToSqlStr( const char* Str , int Size , bool IsNullEnd )
{

	int     i;
	if( Str == NULL )
		return "";

	assert( Size <= 0x10000 );
	
	char OutStr[ 0x10000 ];
	if( Size == 0 )
		Size = 0x10000 -1;

	int idx = 0;
	for( i = 0 ; i < Size ; i++ )
	{
		if( Str[i] == 0 && IsNullEnd != false )
			break;

		if( Str[i] == '\'' )
		{
			OutStr[idx++] = '\'';
			OutStr[idx++] = '\'';
		}
		else
			OutStr[idx++] = Str[i];
	}
	OutStr[ idx ] = 0;

	return OutStr;
}

//-------------------------------------------------------------------------------------
//正規化檔案路徑
void  FilePathnormalize( char* FilePath , char* OutPath )
{
    char Buf[ 512 ];
    strncpy( Buf , FilePath , sizeof(Buf) );

    _strlwr( Buf );

    int i , j;

    //1 把多的空白去除
    for( i = (int)strlen( Buf ) - 1 ; i >= 0 ; i-- )
    {
        if( Buf[i] != ' ' )
            break;

        Buf[i] = 0;
    }

    //去除前面多的斜線與空白
    for( i = 0 ; Buf[i] != 0; i++ )
    {
        if( Buf[i] != ' ' )
            break;
    }

    if( Buf[i] == '\\' )
    {
        if( Buf[i+1] == '\\' )
        {
        }
        else
            i++;
    }
    else if( Buf[i] == '/')
    {
        i++;
    }

//    int StartPoint = i;

    //2 把斜線轉成相同  
    for( j = 0 ; Buf[i] ; i++ )
    {
        if( Buf[i] == '/' || Buf[i] == '\\')
        {
            OutPath[j++] = '/';
            for( ; Buf[i+1] != ' ' ; i++ )
                break;
        }
        else
        {
            OutPath[j++] = Buf[i];
        }
    }
    OutPath[ j ] = 0;
}

int     Random( int Range )
{
	if( Range <= 1 )
		return 0;

	if( Range >= 0x8000 )
	{
		unsigned RandValue = unsigned( rand() * 0x8000 + rand() ) % Range;
		return RandValue;
	}

	return rand() % Range;
	/*
    if( Value <= 1 )
        return 0;

    if( Value < 65536 )
    {
        return rand()%Value;
    }
    
    int R = rand() + rand()* 0x10000 ;

    return R % Value;
	*/
}

int     Random( int Min , int Max )
{
	int Range = Max - Min;
	if( Range == 0  )
	{
		return Min;
	}
	else if( Range > 0 )
	{
		return Min + Random( Range+1 );
	}
	else
	{
		return Max + Random( Range * -1 +1 );
	}
}

//設定數值範圍
int		RangeValue( int MinValue , int MaxValue , int Value )
{
	if( Value < MinValue )
		return MinValue;
	if( Value > MaxValue )
		return MaxValue;
	return Value;
}

unsigned HexStrToUInt( const char *valueStr )
{
	unsigned int value = 0;
	if ( valueStr ) 
	{
		if(		valueStr[0] != '0' 
			||  ( valueStr[1] != 'x' && valueStr[1] != 'X' ) )
		{
			return 0;
		}
		int len = (int)strlen( valueStr );
		if ( len > 10 ) len = 10;
		for ( int i = 2 ; i < len ; i++ ) 
		{
			value = value * 16;
			if ( valueStr[i] >= '0' && valueStr[i] <= '9' ) 
			{
				value += (valueStr[i] - '0') ;
			} 
			else if ( valueStr[i] >= 'A' && valueStr[i] <= 'F' ) 
			{
				value += (valueStr[i] - 'A' + 10);
			} 
			else if ( valueStr[i] >= 'a' && valueStr[i] <= 'f' ) 
			{
				value += (valueStr[i] - 'a' + 10);
			} 
			else 
			{
				return 0;
			}
		}
	}
	return value;
}


string	SqlStr_AddSingleQuotationMark( const char* Str )
{
	string RetStr;

	for( int i = 0 ; Str[i] != 0 ; i++ )
	{
		if( Str[i] == '\'' )
			RetStr.push_back( '\'');
		RetStr.push_back( Str[i] );
	}
	return RetStr;
}


//Sql字串檢查是否有 單引號
bool	CheckSqlStr( const char* Str )
{
	int i= 0;
	while( 1 )
	{
		if( Str[i] == '\'' )
			return false;
		if( Str[i] == 0 )
			break;
		i++;
	}
	/*
	//檢查是否有不玩全的中文字
	//char	Buf[1024];
	//strcpy( Buf , Str )
	int LastCharSize = 1;
	const char *pNextchar = Str;
	const char *pLNextchar = Str;
	char Temp[3];
	
	while( 1 )
	{
		pNextchar = CharNextA( pNextchar );
		if( pNextchar == pLNextchar )
			break;

		Temp[0] = *pLNextchar;

		LastCharSize = pNextchar - pLNextchar; 
		pLNextchar = pNextchar;
		
	}

	if( LastCharSize == 1 )
	{
		pNextchar = Temp;
		pLNextchar = Temp;
		Temp[1] = '\'';
		Temp[2] = 0;
		pNextchar = CharNextA( pNextchar );
		LastCharSize = pNextchar - pLNextchar; 
		if( LastCharSize == 2 )
			return false;
	}
*/
	return true;
}


//密碼簡單編碼
char* EncodePassword( const char* Password , const char* Key )
{
	static char	Buf[256];
	int		KeyLen	= int( strlen( Key ) );
	int		PwdLen  = int( strlen( Password) );

	if( KeyLen <= 2 || PwdLen <=2  )
		return "";
	
	for( int i = 0 ; i < PwdLen ; i++ )
	{
		char Value = Password[i] ^ Key[ (i+1)%KeyLen ];
		sprintf( Buf+i*2 , "%02x" , Value );
	}
	return Buf;
}

char	GetHexValue( const char Key[2] )
{
	char K[2];

	char RetValue = 0;
	for( int i = 0 ; i < 2 ; i++ )
	{
		if( Key[i] >='0' && Key[i] <= '9' )
			K[i] = Key[i]-'0';
		else if( Key[i] >='a' && Key[i] <= 'f' ) 
			K[i] = Key[i]-'a' + 10;
		else if( Key[i] >='A' && Key[i] <= 'F' ) 
			K[i] = Key[i]-'A' + 10;			
	}

	return K[0]*16 + K[1] ;
}


char* 	DecodePassword( const char* Password , const char* Key )
{
	static char	Buf[256];
	int		KeyLen	= int( strlen( Key ) );
	int		PwdLen  = int( strlen( Password)/2 );

	for( int i = 0 ; i < PwdLen ; i++ )
	{
		char Value = GetHexValue( Password + i*2 );
		Buf[i] = Value ^ Key[ (i+1)%KeyLen ];		
	}
	Buf[ PwdLen ] = 0;
	return Buf;
}
	
int ExceptionFilter( unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
	if (code == EXCEPTION_ACCESS_VIOLATION) 
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else 
	{
		return EXCEPTION_CONTINUE_SEARCH;
	};
}

//組合數量
int		MathCombination( int TotalCount , int SelectCount )
{
	int HightNum = 1;
	int LowNum = 1;
	for( int i = 0 ; i < SelectCount ; i++ , TotalCount-- )
	{
		HightNum = HightNum * TotalCount;
		LowNum	 = LowNum * i;
	}
	return HightNum / LowNum;
}
//-------------------------------------------------------------------------------------
//檢查是否有雙字元
bool	CheckDoubleChar( const char* Str )
{
	int Strlen = (int)strlen( Str );
	char* TempPoint;

	for( int i = 0 ;i < Strlen ; i++ )
	{
		TempPoint = CharNextA( Str+i );
		if( (TempPoint - Str - i)  >= 2 )
			return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------
//字串轉換

int	WCharToUTF8( const wchar_t *wStr , char* outUtf8Str , int buffSize )
{
	/*
	buffSize--;
	int len = WideCharToMultiByte(CP_UTF8, 0, wStr , -1, outUtf8Str, buffSize, NULL, NULL);
	outUtf8Str[buffSize] = 0;

	return len;
*/
	int utf8Len = 0;
	buffSize--;

	for( int i = 0 ; ; i++ )
	{
		if( *wStr == 0 )
			break;

		int len =  WideCharToMultiByte(CP_UTF8, 0, wStr , 1 ,  outUtf8Str , buffSize - utf8Len  , NULL, NULL);
		if( len == 0 )
			break;
		utf8Len+=len;
		outUtf8Str+=len;
		wStr++;
	}
	outUtf8Str[0] = 0;
	return utf8Len + 1;
	
}

//-------------------------------------------------------------------------------------
/*
char* UTF8ToChar( char* utf8Str  )
{
	wchar_t	wTempStr[0x100];

}
*/
//-------------------------------------------------------------------------------------
//時間轉換，浮點(SQL) 與 int(C) 互轉
float	TimeExchangeIntToFloat( int Time )
{
	float Ret = float( Time )/(24*60*60) + _1900_1970_DAY_COUNT_;
	return Ret;
}
int		TimeExchangeFloatToInt( float Time )
{
	if( Time < _1900_1970_DAY_COUNT_ )
		return 0;

	int Ret =  int( ( Time- _1900_1970_DAY_COUNT_ )*(24*60*60) );
	return Ret;
}

//四捨五入取整數
float	ToRoundOff( float X )
{
	if( X > 0 )
		return float( int ( X+0.5f ) ); 
	else
		return float( int ( X-0.5f ) ); 
}

//////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
int MAtoi(char* Str)
{
	long	Ret;

	if(atoi(Str) == 0)
	{
		Ret = strtol(Str,NULL,16);
		return Ret;
	}

	return atoi(Str);
}
//-----------------------------------------------------------------------------
//分析字串
int GetNum(char *Str,int index)
{
	char Num[1024];
	int i,j,k;
	if(Str[0] == 0 || Str == NULL)
		return -1;
	for(i=0,j=0,k=0;  ;j++,k++)
	{
		if((Str[j] == ',' || Str[j] == 0 || Str[j] == '\t' ) && i == index)
		{
			Num[k]=0;
			break;
		}
		if( Str[j] == 0)
			return -1;
		if(Str[j] == ',' || Str[j] == '\t' )
		{
			k=-1;
			i++;
		}
		else
			Num[k] = Str[j];
	}

	return MAtoi(Num);
}
//-----------------------------------------------------------------------------
char* GetStr(char *Str,int index)
{
	static char Num[1024];
	int i,j,k;
	for(i=0,j=0,k=0;  ;j++,k++)
	{
		if( (Str[j] == ',' || Str[j] == '\t' || Str[j] == 0 ) && i == index)
		{
			Num[k]=0;
			break;
		}
		if( Str[j] == 0)
			return NULL;

		if(Str[j] == ',' || Str[j] == '\t' )
		{
			k=-1;
			i++;
		}
		else
			Num[k] = Str[j];
	}
	return Num;

}
//////////////////////////////////////////////////////////////////////////
//建立目錄
bool Com_CreatePath( const char* szPathName ) 
{
	if( false == CreateDirectory( szPathName , NULL ) )
	{
		DWORD dwLastError = GetLastError();
		if( 183 == dwLastError ) //當檔案已存在時，無法建立該檔案。
		{
			return true;
		}
		else if( dwLastError == ERROR_PATH_NOT_FOUND ) //沒有路徑嘗試建立上一個路徑
		{
			if( strlen( szPathName ) >= 256 )
			{
				return false;
			}

			char temp[256];
			strcpy( temp, szPathName );

			bool bFind = false;
			int i = (INT)strlen( temp ) - 1;
			while( i >= 0 )
			{
				if( temp[i] == '\\' || 
					temp[i] == '/'  )
				{
					temp[i] = '\0';
					bFind = true;
					break ;
				}
				--i;
			}

			if( !bFind )
			{
				return false;	
			}

			Com_CreatePath( temp );

			if( FALSE == CreateDirectory( szPathName , NULL ) )
			{
				dwLastError = GetLastError();
				if( 183 == dwLastError ) //當檔案已存在時，無法建立該檔案。
					return true;
				return false;
			}
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
void	MyStrcpy( char* strDest , const char* StrSrc , int DestBufSize )
{
	strncpy( strDest , StrSrc , DestBufSize );
	strDest[ DestBufSize -1 ] = 0;
}
//////////////////////////////////////////////////////////////////////////
float RandFloat() 
{
	return float( rand() ) / RAND_MAX ; 
}
//////////////////////////////////////////////////////////////////////////
/*
bool LessCharStr( const char* LeftStr , const char* RightStr )
{
	return ( strcmp( LeftStr , RightStr ) < 0 )
}
*/
//取得記憶體使用量
int	GetMemoryUsage( int processID )
{
	PROCESS_MEMORY_COUNTERS pmc={0};
	HANDLE hProcess= OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS));
	pmc.cb=sizeof(PROCESS_MEMORY_COUNTERS);
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(PROCESS_MEMORY_COUNTERS));
	CloseHandle(hProcess);
	return (int)pmc.WorkingSetSize;
}
//////////////////////////////////////////////////////////////////////////
#define _HashGenerator_MIX(a, b, c)	\
{									\
	a -= b; a -= c; a ^= (c >> 13);	\
	b -= c; b -= a; b ^= (a << 8);	\
	c -= a; c -= b; c ^= (b >> 13);	\
	a -= b; a -= c; a ^= (c >> 12);	\
	b -= c; b -= a; b ^= (a << 16);	\
	c -= a; c -= b; c ^= (b >> 5);	\
	a -= b; a -= c; a ^= (c >> 3);	\
	b -= c; b -= a; b ^= (a << 10);	\
	c -= a; c -= b; c ^= (b >> 15);	\
}

DWORD GetHashCode(const void *vk, int length)
{
	const BYTE *k = (const BYTE *)vk;
	DWORD a, b, c, len;

	// Set up the internal state
	len = length;
	a = b = 0x9e3779b9;		// The golden ratio; an arbitrary value
	c = 0;			// The previous hash value

	// Handle most of the key
	while (len >= 12)
	{
		a += (k[0] +((DWORD) k[1] << 8) + ((DWORD) k[2] << 16) + ((DWORD) k[3] << 24));
		b += (k[4] +((DWORD) k[5] << 8) + ((DWORD) k[6] << 16) + ((DWORD) k[7] << 24));
		c += (k[8] +((DWORD) k[9] << 8) + ((DWORD) k[10] << 16)+ ((DWORD) k[11] << 24));
		_HashGenerator_MIX(a, b, c);
		k += 12; len -= 12;
	}

	// Handle the last 11 bytes
	c += length;
	switch(len)				// All the case statements fall through
	{
	case 11:
		c += ((DWORD) k[10] << 24);
	case 10:
		c += ((DWORD) k[9] << 16);
	case 9:
		c += ((DWORD) k[8] << 8);
		// The first byte of c is reserved for the length
	case 8:
		b += ((DWORD) k[7] << 24);
	case 7:
		b += ((DWORD) k[6] << 16);
	case 6:
		b += ((DWORD) k[5] << 8);
	case 5:
		b += k[4];
	case 4:
		a += ((DWORD) k[3] << 24);
	case 3:
		a += ((DWORD) k[2] << 16);
	case 2:
		a += ((DWORD) k[1] << 8);
	case 1:
		a += k[0];
		// case 0: nothing left to add
	}

	_HashGenerator_MIX(a, b, c);

	// Return the result
	return c;
}
//////////////////////////////////////////////////////////////////////////
//兩線斷是否有交點
bool	CheckTwoLineIntersect( float x1 , float y1 , float x2 , float y2 , float x3 , float y3 , float x4 , float y4 )
{
	/*
	給定(x1,y1),(x2,y2)兩點, 令dx1=x2-x1,dy1=y2-y1, 其線的公式為:

	y = (x-x1)*dy1/dx1 + y1

	若再給兩點(x3,y3),(x4,y4)的另一線為 (dx2=x4-x3,dy2=y4-y3):

	y = (x-x3)*dy2/dx2 + y3

	解此聯立方程式得:

	x = (y3*dx2*dx1-y1*dx2*dx1+x1*dy1*dx2-x3*dy2*dx1)/(dy1*dx2-dy2*dx1)

	將x代入前述任何一個公式即可求得y. 注意dy1*dx2-dy2*dx1不能為0, 否則為2平行線.

	前述求的點是直線相交的狀況, 你必須確認相交點是否都在兩線段以內:

	if ((x >= min(x1,x2)) && (x <= max(x1,x2)) && (y >= min(y1,y2) && (y <= max(y1,y2))) 在第一線段內
	*/
	float dx1= x2-x1;
	float dy1= y2-y1;

	float dx2= x4-x3;
	float dy2= y4-y3;
	
	if( (dy1*dx2-dy2*dx1) == 0 || dx2 == 0 )
		return false;

	float x = (y3*dx2*dx1-y1*dx2*dx1+x1*dy1*dx2-x3*dy2*dx1)/(dy1*dx2-dy2*dx1);
	float y = (x-x3)*dy2/dx2 + y3;

	//線斷檢查
	if (x < __min(x1,x2) || x > __max(x1,x2) || y < __min(y1,y2) || y > __max(y1,y2) )
		return false;
	if (x < __min(x3,x4) || x > __max(x3,x4) || y < __min(y3,y4) || y > __max(y3,y4) )
		return false;

	return true;
}

#pragma managed