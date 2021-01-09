//------------------------------------------------------------------------------------------------------
//          ÀRºA²£¥Íªº Vector
//------------------------------------------------------------------------------------------------------
#pragma once
#include "MyTypeDef.h"
#include <algorithm>

template < class T , int S >
class StaticVector
{
protected:
    T          _Arr[ S ];    
    unsigned int     _Size;

public:

    StaticVector( );

    T&          Back();
    T&          Front();
    bool        IsEmpty() const;
    void        Clear();
    T*          Begin() ;
    T*          End() ;

	int		Find( const T& );
    bool    Push_Back( const T& );
    bool    Pop_Back( );
    bool    Pop_Front( );
        
    int     Size() const;
	int		MaxSize() const;
    bool    Insert( const unsigned int ID , const T& );
    bool    Erase( const unsigned int ID );
    bool    Swap( const unsigned int AID , const unsigned int BID );

    T&      operator[] ( const unsigned int Pos );
	T&		operator() ( const T&  );
};


template < class T , int S >
StaticVector< T , S >::StaticVector(void)
{
    _Size    = 0;
};


template < class T , int S >
T&      StaticVector< T , S >::Back() 
{
    return _Arr[ _Size -1 ];
};

template < class T , int S >
T&      StaticVector< T , S >::Front()
{
    return _Arr[ 0 ];
};

template < class T , int S >
bool    StaticVector< T , S >::IsEmpty() const
{
    return _Size == 0;
};

template < class T , int S >
void    StaticVector< T , S >::Clear()
{
    _Size = 0;
};

template < class T , int S >
T*      StaticVector< T , S >::Begin() 
{
    return &_Arr[0];
};

template < class T , int S >
T*      StaticVector< T , S >::End() 
{
    return &_Arr[ _Size ];
};


template < class T , int S >
bool      StaticVector< T , S >::Push_Back( const T&  Value )
{
    if( _Size >= S )
        return false;

    _Arr[ _Size ] = Value;
    _Size++;
    return true;
};

template < class T , int S >
int      StaticVector< T , S >::Find( const T&  Value )
{
	for( unsigned int i = 0 ; i < _Size ; i++ )
	{
		if( _Arr[ i ] == Value )
			return i;
	}

	return -1;
};

template < class T , int S >
bool      StaticVector< T , S >::Pop_Back( )
{
    if( _Size == 0 )
        return false;

    _Size--;
    return true;
};

template < class T , int S >
bool      StaticVector< T , S >::Pop_Front( )
{
    return Erase( 0 );
};

template < class T , int S >
int     StaticVector< T , S >::Size() const
{
    return _Size;
};

template < class T , int S >
int     StaticVector< T , S >::MaxSize() const
{
	return S;
};

template < class T , int S >
bool     StaticVector< T , S >::Insert( const unsigned int ID , const T& Value )
{
    if( ID > _Size )
        return false;

    if( _Size >= S )
        return false;

    memmove( &_Arr[ ID + 1 ]  , &_Arr[ ID ] , (_Size-ID)*sizeof( T ) );

    _Size++;
    _Arr[ID] = Value;
    return true;
};
template < class T , int S >
bool     StaticVector< T , S >::Erase( const unsigned int ID )
{

    if( ID >= _Size )
        return false;

    memmove( &_Arr[ ID  ]  , &_Arr[ ID + 1  ] , (_Size-ID-1)*sizeof( T ) );
    _Size--;
    return true;
};
template < class T , int S >
bool     StaticVector< T , S >::Swap( const unsigned int AID , const unsigned int BID )
{
    if(     AID >= _Size 
        ||  BID >= _Size )
        return false;

    std::swap( _Arr[AID] , _Arr[BID] );
    return true;
};

template < class T , int S >
T&      StaticVector< T , S >::operator[] ( const unsigned int Pos )
{
    return _Arr[Pos];
};
template < class T , int S >
T&      StaticVector< T , S >::operator() ( const T&  Value  )
{
	for( int i = 0 ; i < _Arr[Pos] )
	return _Arr[Pos];
};