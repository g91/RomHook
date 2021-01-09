#ifndef _BASEFUNCTION_H_2003_09_22
#define _BASEFUNCTION_H_2003_09_22
#pragma warning (disable:4949)
#pragma unmanaged

#include <string>
#include <vector>
#include <excpt.h>

using namespace std;

//-------------------------------------------------------------------------------------
#define SetBit(x,b)		((x) |= (1<<(b)))
#define TestBit(x,b)	(((x) & (1<<(b))) != 0 ) 
//-------------------------------------------------------------------------------------
unsigned HexStrToUInt( const char *valueStr );
//-------------------------------------------------------------------------------------
//檔案所在路徑與檔名結合
char* CombineFilePath( const char* Path , const char* File );
//正規化檔案路徑
void  FilePathnormalize( char* FilePath , char* OutPath );
//-------------------------------------------------------------------------------------
//簡查資料是否有效
bool CheckFloatAvlid( float X );
//-------------------------------------------------------------------------------------
//資料轉換
string   FloatToStr( float Value );
string   IntToStr( int Value );
int		 StrToNum( const char* Str, int Size );
//--------------------------------------------------------------------- ----------------
unsigned int MytimeGetTime( );
//-------------------------------------------------------------------------------------
//取得某目錄下所有子目錄
vector<string>*	AllPathList( string Path );
vector<string>*	AllPathList_Pure( string Path );
//取得某目錄下所有子目錄 與檔案
vector<string>*	AllFileList( string Path , string Sub );
//取得某目錄下所有子目錄 與檔案(相對目錄)
vector<string>*	AllFileList_Sub( string Path , string Sub );

//-------------------------------------------------------------------------------------
//件立以某目錄下所有子目錄
bool	CreateAllPath( string Path , vector<string>& PathList );
//-------------------------------------------------------------------------------------
bool	FloatEQU ( float X , float Y );
//-------------------------------------------------------------------------------------

//把字串轉成Sql二進位表示
string   StringToSqlX( const char* Str , int Size , bool IsNullEnd = true );
string   WStringToSqlX( const wchar_t* Str , int Size );
string   StringToSqlStr( const char* Str , int Size , bool IsNullEnd = true );
//Sql字串檢查是否有 單引號
bool	CheckSqlStr( const char* Str );
string	SqlStr_AddSingleQuotationMark( const char* Str );
//-------------------------------------------------------------------------------------
//取亂數
int     Random( int );
int     Random( int Min , int Max );
//-------------------------------------------------------------------------------------
//設定數值範圍
int		RangeValue( int MinValue , int MaxValue , int Value );
//-------------------------------------------------------------------------------------
//密碼簡單編碼
char* 	EncodePassword( const char* Password , const char* Key );
char* 	DecodePassword( const char* Password , const char* Key );

//-------------------------------------------------------------------------------------
int		ExceptionFilter( unsigned int code, struct _EXCEPTION_POINTERS *ep);
//-------------------------------------------------------------------------------------
//組合數量
int		MathCombination( int TotalCount , int SelectCount );
//-------------------------------------------------------------------------------------
//檢查是否有雙字元
bool	CheckDoubleChar( const char* Str );
//-------------------------------------------------------------------------------------
//字串轉換
int		WCharToUTF8(const wchar_t *ws , char* StrOut , int BufSize );
//簡易轉換
//char*	UTF8ToChar( char* utf8InStr );
//-------------------------------------------------------------------------------------
//時間轉換，浮點(SQL) 與 int(C) 互轉
float	TimeExchangeIntToFloat( int Time );
int		TimeExchangeFloatToInt( float Time );
//-------------------------------------------------------------------------------------
//四捨五入取整數
float	ToRoundOff( float );
//-------------------------------------------------------------------------------------
//16進位字串轉數字
int		MAtoi	(char* Str);
//字串取數字,以","分格第幾個
int		GetNum	(char *Str,int index);
//字串取字串,以","分格第幾個
char*	GetStr	(char *Str,int index);
//-------------------------------------------------------------------------------------
//建立目錄
bool Com_CreatePath( const char* szPathName );
//-------------------------------------------------------------------------------------
void	MyStrcpy( char* strDest , const char* StrSrc , int DestBufSize );
//-------------------------------------------------------------------------------------
//取得vector<int>內的東西
template< class T > 
T	GetVectorPos( vector<T>& v , int Pos , T ErrorRet )
{
	if( unsigned(Pos) >= v.size() )
		return ErrorRet;
	return v[Pos];
};

template< class T > 
T*	GetVectorPosPoint( vector<T>& v , int Pos )
{
	if( unsigned(Pos) >= v.size() )
		return NULL;
	return& v[Pos];
};
//-------------------------------------------------------------------------------------
float RandFloat();
//-------------------------------------------------------------------------------------
//bool LessCharStr( const char* LeftStr , const char* RightStr );
//取得記憶體使用量
int	GetMemoryUsage( int ProcessID );
//-------------------------------------------------------------------------------------
unsigned long GetHashCode(const void *vk, int length);


//兩線斷是否有交點
bool	CheckTwoLineIntersect( float x1 , float y1 , float x2 , float y2 , float x3 , float y3 , float x4 , float y4 );


#pragma managed
#endif