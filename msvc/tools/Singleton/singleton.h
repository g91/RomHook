#pragma once
// --------------------------------------------------------------------------------------
//#include <assert.h>
//#include "Malloc/MyAlloc.h"
#include "MyBaseInc.h"
// --------------------------------------------------------------------------------------
#pragma warning (disable : 4311)
#pragma warning (disable : 4312)
// --------------------------------------------------------------------------------------
template <typename T> class Singleton
{
protected:
	static T*   _Singleton;
    int         _Count;
public:
	Singleton( void )
	{
    	assert( !_Singleton );
    	_Singleton = static_cast< T* >( this );
        _Count = 1;
	}

	~Singleton( void )
	{  
		assert( _Singleton );
		_Singleton = 0;
	}

	static T& getSingleton( void )
	{
		assert( _Singleton );

		return ( *_Singleton );
	}
        
	static T* getSingletonPtr( void )
	{
		return ( _Singleton );  
	}

    static T* New( void )
    {
        if( _Singleton == 0 ) 
        {
            _Singleton = NEW( T );	
        }
        else
        {
            _Singleton->_Count ++;
        }
        return _Singleton ;
    }

    static void Del( void )
    {
		if( _Singleton == NULL )
			return;
        assert( _Singleton );
        assert( _Singleton->_Count > 0 );
        if( _Singleton->_Count > 1 )
            _Singleton->_Count--;
        else
        {
            delete _Singleton;
        }
      
    }


};

