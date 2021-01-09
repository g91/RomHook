//不可以使用於多執行序
//在多執行續內使用會造成不可預期的當機

#pragma once
#pragma warning (disable:4200)
#pragma warning (disable:4949)
#pragma unmanaged

#ifndef _MY_MEM_NEW_
#define NEW new 
#define MyAllocMemoryReport( )
#define MyAllocRelease( )    
#define MyAllocMemoryCheck( )    
#else
#define NEW new(__FILE__,__LINE__)
#define MyAllocMemoryReport _MyAllocMemoryReport
#define MyAllocRelease _MyAllocRelease    
#define MyAllocMemoryCheck _MyAllocMemoryCheck    

void    _MyAllocMemoryCheck( );
//列印記憶體
bool    _MyAllocMemoryReport( );
bool    _MyAllocMemoryReportAll( );
//清除記憶體
void    _MyAllocRelease( );        

void*   operator new( size_t size );
void*   operator new( size_t size , const char* File , const int Line );
void*   operator new[]( size_t size );
void*   operator new[]( size_t size , const char* File , const int Line );


void    operator delete( void *buf );
void    operator delete[]( void *buf );
void    operator delete( void *buf , const char* File , const int Line );
void    operator delete[]( void *buf , const char* File , const int Line );

#endif

#pragma managed


