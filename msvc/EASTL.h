#include <EASTL/string.h>

#ifndef EASTL_EXT
#define EASTL_EXT

namespace eastl
{
	class ansi_string : public basic_string< char >
	{
	public:

		__forceinline ansi_string( char *CharArray ) : basic_string< char >::basic_string( CharArray, strlen( CharArray ) ){}

		__forceinline ansi_string( std::string s ) : basic_string< char >::basic_string( const_cast< char* >( s.c_str() ), s.length() ){}

		__forceinline std::string c_str()
		{
			std::string ret;

			for( size_t l = 0; l < length(); l++ )
			{
				ret += at( l );
			}

			return ret;
		}
	};

	class unicode_string : public basic_string< wchar_t >
	{
	public:
		__forceinline unicode_string( wchar_t *CharArray ) : basic_string< wchar_t >::basic_string( CharArray, wcslen( CharArray ) ){}

		__forceinline unicode_string( std::wstring s ) : basic_string< wchar_t >::basic_string( const_cast< wchar_t* >( s.c_str() ), s.length() ){}

		__forceinline std::wstring c_str()
		{
			std::wstring ret;

			for( size_t l = 0; l < length(); l++ )
			{
				ret += at( l );
			}

			return ret;
		}
	};
}

#endif