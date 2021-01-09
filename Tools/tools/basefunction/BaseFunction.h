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
//�ɮשҦb���|�P�ɦW���X
char* CombineFilePath( const char* Path , const char* File );
//���W���ɮ׸��|
void  FilePathnormalize( char* FilePath , char* OutPath );
//-------------------------------------------------------------------------------------
//²�d��ƬO�_����
bool CheckFloatAvlid( float X );
//-------------------------------------------------------------------------------------
//����ഫ
string   FloatToStr( float Value );
string   IntToStr( int Value );
int		 StrToNum( const char* Str, int Size );
//--------------------------------------------------------------------- ----------------
unsigned int MytimeGetTime( );
//-------------------------------------------------------------------------------------
//���o�Y�ؿ��U�Ҧ��l�ؿ�
vector<string>*	AllPathList( string Path );
vector<string>*	AllPathList_Pure( string Path );
//���o�Y�ؿ��U�Ҧ��l�ؿ� �P�ɮ�
vector<string>*	AllFileList( string Path , string Sub );
//���o�Y�ؿ��U�Ҧ��l�ؿ� �P�ɮ�(�۹�ؿ�)
vector<string>*	AllFileList_Sub( string Path , string Sub );

//-------------------------------------------------------------------------------------
//��ߥH�Y�ؿ��U�Ҧ��l�ؿ�
bool	CreateAllPath( string Path , vector<string>& PathList );
//-------------------------------------------------------------------------------------
bool	FloatEQU ( float X , float Y );
//-------------------------------------------------------------------------------------

//��r���নSql�G�i����
string   StringToSqlX( const char* Str , int Size , bool IsNullEnd = true );
string   WStringToSqlX( const wchar_t* Str , int Size );
string   StringToSqlStr( const char* Str , int Size , bool IsNullEnd = true );
//Sql�r���ˬd�O�_�� ��޸�
bool	CheckSqlStr( const char* Str );
string	SqlStr_AddSingleQuotationMark( const char* Str );
//-------------------------------------------------------------------------------------
//���ü�
int     Random( int );
int     Random( int Min , int Max );
//-------------------------------------------------------------------------------------
//�]�w�ƭȽd��
int		RangeValue( int MinValue , int MaxValue , int Value );
//-------------------------------------------------------------------------------------
//�K�X²��s�X
char* 	EncodePassword( const char* Password , const char* Key );
char* 	DecodePassword( const char* Password , const char* Key );

//-------------------------------------------------------------------------------------
int		ExceptionFilter( unsigned int code, struct _EXCEPTION_POINTERS *ep);
//-------------------------------------------------------------------------------------
//�զX�ƶq
int		MathCombination( int TotalCount , int SelectCount );
//-------------------------------------------------------------------------------------
//�ˬd�O�_�����r��
bool	CheckDoubleChar( const char* Str );
//-------------------------------------------------------------------------------------
//�r���ഫ
int		WCharToUTF8(const wchar_t *ws , char* StrOut , int BufSize );
//²���ഫ
//char*	UTF8ToChar( char* utf8InStr );
//-------------------------------------------------------------------------------------
//�ɶ��ഫ�A�B�I(SQL) �P int(C) ����
float	TimeExchangeIntToFloat( int Time );
int		TimeExchangeFloatToInt( float Time );
//-------------------------------------------------------------------------------------
//�|�ˤ��J�����
float	ToRoundOff( float );
//-------------------------------------------------------------------------------------
//16�i��r����Ʀr
int		MAtoi	(char* Str);
//�r����Ʀr,�H","����ĴX��
int		GetNum	(char *Str,int index);
//�r����r��,�H","����ĴX��
char*	GetStr	(char *Str,int index);
//-------------------------------------------------------------------------------------
//�إߥؿ�
bool Com_CreatePath( const char* szPathName );
//-------------------------------------------------------------------------------------
void	MyStrcpy( char* strDest , const char* StrSrc , int DestBufSize );
//-------------------------------------------------------------------------------------
//���ovector<int>�����F��
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
//���o�O����ϥζq
int	GetMemoryUsage( int ProcessID );
//-------------------------------------------------------------------------------------
unsigned long GetHashCode(const void *vk, int length);


//��u�_�O�_�����I
bool	CheckTwoLineIntersect( float x1 , float y1 , float x2 , float y2 , float x3 , float y3 , float x4 , float y4 );


#pragma managed
#endif