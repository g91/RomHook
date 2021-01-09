#pragma once
#include <string.h>
#include "staticVector.h"

template < int S >
class StaticString 
{
	char    _Arr[S];
	void    _SetString( const char* Str ) ;
public:
	StaticString( const char* Str );
	StaticString( ){ Clear(); };

	const char* SafeStr();
	const char* Begin() const;
	const int   Size() const;
	void    Clear();

	const char* operator = ( const char* Str );
	const char* operator = ( char* Str );

	template < class T >  
	bool operator == ( const T& Src2 );

	template < class T >  
	bool operator != ( const T& Src2 );

	template < class T >  
	char* operator = ( const T& SrcStr  );

	operator const char* () const { return Begin(); }

	void MakeLower( );
	void MakeUpper( );

	template < class T > 
	int  Compare( const T& SrcStr ) const;

	template < class T >
	int  CompareNoCase( const T& SrcStr  ) const; 

	int  Compare( const char* SrcStr ) const;  
	int  CompareNoCase( const char* SrcStr  ) const; 

	void StrArrange( );

};

template < int S >
void StaticString<S>::StrArrange( )
{
	for( int i = Size()+1 ; i < S ; i++ )
		_Arr[i] = 0;
}

template < int S >
StaticString<S>::StaticString( const char* Str )
{
	_SetString( Str );
};

template < int S >
const char* StaticString<S>::operator = ( const char* Str )
{
	_SetString( Str );
	return _Arr;
};

template < int S >
const char* StaticString<S>::operator = ( char* Str )
{
	_SetString( Str );
	return _Arr;
};

template < int S >
template < class T >
char* StaticString<S>::operator = ( const T& SrcStr  )
{
	_SetString( SrcStr.Begin() );
	return _Arr;
};


template < int S >
void    StaticString<S>::_SetString( const char* Str )
{
	if(Str == NULL)
	{
		if(S > 4)
			strcpy_s(_Arr, "null");
		else
			_Arr[0] = 0;
		return;
	}

	int Size = (int)strlen( Str )+1;
	if( Size >= S )
	{
		Size = S-1;
//		_Arr[ Size ] = 0;
	}

	memset( _Arr , 0 , S );
	memcpy( _Arr , Str , Size ); 

};

template < int S >
void StaticString<S>::MakeLower( )
{
	_strlwr( _Arr );
}

template < int S >
void StaticString<S>::MakeUpper( )
{
	_strupr( _Arr );
}

template < int S >
template < class T >
int  StaticString<S>::Compare( const T& SrcStr ) const
{
	return strcmp( _Arr , SrcStr.Begin() );
}

template < int S >
template < class T >
int  StaticString<S>::CompareNoCase( const T& SrcStr  ) const
{
	return stricmp( _Arr , SrcStr.Begin() );
}

template < int S >
int  StaticString<S>::Compare( const char* SrcStr ) const
{
	if(SrcStr == NULL)
		return 1;

	return strcmp( _Arr , SrcStr );
}

template < int S >
int  StaticString<S>::CompareNoCase( const char* SrcStr  ) const 
{
	if(SrcStr == NULL)
		return 1;

	return stricmp( _Arr , SrcStr );
}

template < int S >
template < class T >  
bool StaticString<S>::operator == ( const T& Src2 )
{
	return ( Compare( Src2 ) == 0 );
}

template < int S >
template < class T >  
bool StaticString<S>::operator != ( const T& Src2 )
{
	return ( Compare( Src2 ) != 0 );
}

template < int S >
const char* StaticString<S>::Begin() const
{
	return (const char*)_Arr;
}
template < int S >
const char* StaticString<S>::SafeStr()
{
	_Arr[ S -1] = 0;
	return (const char*)_Arr;
}

template < int S >
const int   StaticString<S>::Size() const
{
	return int( strnlen( _Arr, S ) );
}
template < int S >
void    StaticString<S>::Clear()
{
	_Arr[0] = 0;
}

//WCharª©¥»
template < int S >
class StaticWCharString 
{
	wchar_t _Arr[S];
	void	_SetString( const wchar_t* Str ) ;
public:
	StaticWCharString( const wchar_t* Str );
	StaticWCharString( ){ Clear(); };

	const wchar_t* SafeStr();
	const wchar_t* Begin() const;
	const int   Size() const;
	void    Clear();

	const wchar_t* operator = ( const wchar_t* Str );
	const wchar_t* operator = ( wchar_t* Str );

	template < class T >  
	bool operator == ( const T& Src2 );

	template < class T >  
	bool operator != ( const T& Src2 );

	template < class T >  
	wchar_t* operator = ( const T& SrcStr  );

	operator const wchar_t* () const { return Begin(); }

	void MakeLower( );
	void MakeUpper( );

	template < class T > 
	int  Compare( const T& SrcStr ) const;

	template < class T >
	int  CompareNoCase( const T& SrcStr  ) const; 

	int  Compare( const wchar_t* SrcStr ) const;  
	int  CompareNoCase( const wchar_t* SrcStr  ) const; 

};


template < int S >
StaticWCharString<S>::StaticWCharString( const wchar_t* Str )
{
	_SetString( Str );
};

template < int S >
const wchar_t* StaticWCharString<S>::operator = ( const wchar_t* Str )
{
	_SetString( Str );
	return _Arr;
};

template < int S >
const wchar_t* StaticWCharString<S>::operator = ( wchar_t* Str )
{
	_SetString( Str );
	return _Arr;
};

template < int S >
template < class T >
wchar_t* StaticWCharString<S>::operator = ( const T& SrcStr  )
{
	_SetString( SrcStr.Begin() );
	return _Arr;
};


template < int S >
void    StaticWCharString<S>::_SetString( const wchar_t* Str )
{
	if(Str == NULL)
	{
		if(S > 4)
			wcscpy(_Arr, L"null");
		else
			_Arr[0] = 0;
		return;
	}

	int Size = (int)wcslen( Str )+1;
	if( Size >= S )
	{
		Size = S-1;
		_Arr[ Size ] = 0;
	}

	memcpy( _Arr , Str , Size ); 

};

template < int S >
void StaticWCharString<S>::MakeLower( )
{
	_wcslwr( _Arr );
}

template < int S >
void StaticWCharString<S>::MakeUpper( )
{
	_wcsupr( _Arr );
}

template < int S >
template < class T >
int  StaticWCharString<S>::Compare( const T& SrcStr ) const
{
	return wcscmp( _Arr , SrcStr.Begin() );
}

template < int S >
template < class T >
int  StaticWCharString<S>::CompareNoCase( const T& SrcStr  ) const
{
	return wcsicmp( _Arr , SrcStr.Begin() );
}

template < int S >
int  StaticWCharString<S>::Compare( const wchar_t* SrcStr ) const
{
	if(SrcStr == NULL)
		return 1;

	return wcscmp( _Arr , SrcStr );
}

template < int S >
int  StaticWCharString<S>::CompareNoCase( const wchar_t* SrcStr  ) const 
{
	if(SrcStr == NULL)
		return 1;

	return wcsicmp( _Arr , SrcStr );
}

template < int S >
template < class T >  
bool StaticWCharString<S>::operator == ( const T& Src2 )
{
	return ( Compare( Src2 ) == 0 );
}

template < int S >
template < class T >  
bool StaticWCharString<S>::operator != ( const T& Src2 )
{
	return ( Compare( Src2 ) != 0 );
}

template < int S >
const wchar_t* StaticWCharString<S>::Begin() const
{
	return (const wchar_t*)_Arr;
}
template < int S >
const wchar_t* StaticWCharString<S>::SafeStr()
{
	_Arr[S-1] = 0;
	return (const wchar_t*)_Arr;
}


template < int S >
const int   StaticWCharString<S>::Size() const
{
	return int( wcslen( _Arr ) );
}
template < int S >
void    StaticWCharString<S>::Clear()
{
	_Arr[0] = 0;
}