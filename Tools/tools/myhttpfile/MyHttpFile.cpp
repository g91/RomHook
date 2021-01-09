#include "MyHttpFile.h"
#include <stdio.h>
#include <assert.h>
#include "basefunction/BaseFunction.h"
#include <algorithm>

//int  MyHttpFile::;
//////////////////////////////////////////////////////////////////////////
MyHttpFile::MyHttpFile( )
{
	m_bInterrupt=0;
	_totalSize		= 0;		//郎
	_dlSize			= 0;		//更Size
	_isRunThread	= false;
	_state			=	 EM_MyHttpFileProcessType_None;		//ヘ玡矪瞶篈
	m_dlKbs=0;
	_port			= 0;
	_port_proxy		= 0;
	m_Got_Nothing=0;

}
MyHttpFile::~MyHttpFile( )
{
	Clear();
}

void	MyHttpFile::SetDownloadUrl( const char* url )
{
	_url = url;
}
void	MyHttpFile::SetDownloadPort( int port )
{
	_port = port;
}

void	MyHttpFile::SetProxyUrl( const char* url )
{
	_url_proxy = url;
}
void	MyHttpFile::SetProxyPort( int port )
{
	_port_proxy = port;
}

void	MyHttpFile::SetUserPwd( string	UserPwd )
{
	_userpwd = UserPwd;
}

//睲埃
bool	MyHttpFile::Clear()
{
	int		i;
	if( _isRunThread != false ) 
	{
		_state = EM_MyHttpFileProcessType_Interrupt;

	//	m_bInterrupt=1;
		//单ミ
		for( i = 0 ; i < 1000 ; i++ )
		{
			
			if( _isRunThread == false )
				break;
			Sleep( 10);
		}
		assert( i != 1000 );
	}
	
	_totalSize	= 0;		//郎
	_dlSize		= 0;		//更Size
	_state		= EM_MyHttpFileProcessType_None; 		//ヘ玡矪瞶篈
	_hThread	= NULL;
	_threadId	= 0;
	m_dlKbs=0;
	_url.clear();			
	_destFolder.clear();
	_remoteFile.clear();
	_localFile.clear();

	return true;
}
//////////////////////////////////////////////////////////////////////////
//更
bool	MyHttpFile::Download( string destFolder , string remoteFile ,string localFile )
{
	if( _isRunThread != false )
		return false;

//	_url		= url;			
	_destFolder	= destFolder;
	_remoteFile = remoteFile;
	_localFile  = localFile;
//	_port		= port;

	if( _url.size() > 1 && *_url.rbegin() != '\\' &&  *_url.rbegin() != '/' )
		_url = _url + '/';

	if( destFolder.length() != 0 )
	{
		if( *(_destFolder.rbegin()) != '\\' && *(_destFolder.rbegin()) != '/' )
			_destFolder = _destFolder + '/';
	}

	if( _isRunThread != false )
		return false;

	_isRunThread = true;
	_state = EM_MyHttpFileProcessType_Download;

	_hThread = CreateThread( NULL , 0 , _St_DownloadThread , (LPVOID) this , 0 , &_threadId );

	return true;
}

bool	MyHttpFile::Download_NoThread( string destFolder , string remoteFile , string localFile , int TryTimes )
{
	for( int i = 0 ; i < TryTimes ; i++ )
	{
		if(	State() == EM_MyHttpFileProcessType_Interrupt )
			return false;
		if(	m_bInterrupt  )
			return false;

		if( Download_NoThread( destFolder , remoteFile , localFile ) != false )
			return true;
		if(	State() == EM_MyHttpFileProcessType_Interrupt )
			return false;
		if(	m_bInterrupt  )
			return false;

		if (m_Got_Nothing)
			break;
		Sleep( 1000 );
	}
	return false;
}

bool	MyHttpFile::Download_NoThread( string destFolder , string remoteFile , string localFile )
{

	if( Download( destFolder , remoteFile , localFile ) == false )
		return false;

	while(1)
	{
		Sleep( 1 );
		switch( State() )
		{
		case EM_MyHttpFileProcessType_Download:		//更い
			break;
		case EM_MyHttpFileProcessType_OK:			//更Θ
			{
				return true;
			}
			break;
		case EM_MyHttpFileProcessType_None:
		case EM_MyHttpFileProcessType_Failed:		//更ア
		case EM_MyHttpFileProcessType_Interrupt:	//璶―い耞
			{
				return false;
			}
			break;
		}
		if(	m_Got_Nothing  )
			return false;
	}
}
//////////////////////////////////////////////////////////////////////////
//矪瞶更磅︽
int    MyHttpFile::_DownloadThread( )
{
	// 022708 эみ 谨/в岸

	MyHttpFileProcessTypeENUM nextState = _state;
	__try
	{
		if( EM_MyHttpFileProcessType_Interrupt == _state ) 
		{
			nextState=EM_MyHttpFileProcessType_Interrupt;
			//	_isRunThread=false;
			return 0;
		}

		//	if (m_bInterrupt)
		//	{
		//	_isRunThread=false;
		//		return 0;
		//	}
		static CURL *curl = NULL;
		CURLcode res;

		if( curl == NULL )
		{
			curl = curl_easy_init();
		}

		if( curl == NULL )  
		{
			//if(	m_bInterrupt  )
			//return false;

			if( EM_MyHttpFileProcessType_Interrupt != _state )
				_state = EM_MyHttpFileProcessType_Failed;
			return 0;
		}

		char	UrlFile[ 512 ];
		char	OutputFile[ 512 ];
		sprintf( UrlFile , "%s%s", _url.c_str() , _remoteFile.c_str() );
		sprintf( OutputFile , "%s%s", _destFolder.c_str() , _localFile.c_str() );


		SetFileAttributes( OutputFile , FILE_ATTRIBUTE_NORMAL );

		FILE*	file = fopen( OutputFile , "wb" );
		if( file == NULL )
		{
			if( EM_MyHttpFileProcessType_Interrupt != _state )
				_state = EM_MyHttpFileProcessType_Failed;

			//curl_easy_cleanup(curl);
			return 0;
		}


		curl_easy_setopt( curl, CURLOPT_URL , UrlFile );
		if( _port != 0 )
			curl_easy_setopt( curl, CURLOPT_PORT  , _port  );

		if( _url_proxy.length() != 0 )
		{
			curl_easy_setopt( curl, CURLOPT_PROXY   , _url_proxy.c_str()  );
			if( _port_proxy != 0 )
				curl_easy_setopt( curl, CURLOPT_PROXYPORT   , _port_proxy  );
		}

		curl_easy_setopt( curl, CURLOPT_NOPROGRESS , FALSE );

		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteFunctionCallback );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, file );

		curl_easy_setopt( curl, CURLOPT_PROGRESSFUNCTION , CurlProgressCallback );
		curl_easy_setopt( curl, CURLOPT_PROGRESSDATA , this );

		curl_easy_setopt( curl,  CURLOPT_CONNECTTIMEOUT, 20 );
		//curl_easy_setopt( curl,  CURLOPT_LOW_SPEED_LIMIT, 300 );
		//curl_easy_setopt( curl,  CURLOPT_LOW_SPEED_TIME, 5 );
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE);


		m_sTime=timeGetTime();
		m_Got_Nothing=0;
		if( _userpwd.size() != 0 )
			curl_easy_setopt( curl , CURLOPT_USERPWD , _userpwd.c_str() );

		for( int i = 0 ; ; i++ )
		{
			res = curl_easy_perform( curl );
			if (CURLE_GOT_NOTHING==res)
			{
				m_Got_Nothing=1;
				return 0;
			}

			if( res != 0 )
			{
				_curlErrCode.push_back( res );
				/*
				MessageBox( NULL, "FAILED", "FAILED", MB_OK );
				//				_dlSize	  = 0;		//更Size

				curl_easy_cleanup(curl);
				curl = curl_easy_init();


				curl_easy_setopt( curl, CURLOPT_URL , UrlFile );
				if( _port != 0 )
				curl_easy_setopt( curl, CURLOPT_PORT  , _port  );

				if( _url_proxy.length() != 0 )
				{
				curl_easy_setopt( curl, CURLOPT_PROXY   , _url_proxy.c_str()  );
				if( _port_proxy != 0 )
				curl_easy_setopt( curl, CURLOPT_PROXYPORT   , _port_proxy  );
				}

				curl_easy_setopt( curl, CURLOPT_NOPROGRESS , FALSE );

				curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteFunctionCallback );
				curl_easy_setopt( curl, CURLOPT_WRITEDATA, file );

				curl_easy_setopt( curl, CURLOPT_PROGRESSFUNCTION , CurlProgressCallback );
				curl_easy_setopt( curl, CURLOPT_PROGRESSDATA , this );

				curl_easy_setopt( curl , CURLOPT_USERPWD , _userpwd.c_str() );
				*/				



				curl_easy_setopt( curl , CURLOPT_RESUME_FROM  , ftell(file) );

				Sleep( 1000 );


				if( EM_MyHttpFileProcessType_Interrupt == _state )
				{
					nextState = EM_MyHttpFileProcessType_Interrupt;
					break;
				}

				if( i >= 10 )
				{
					nextState = EM_MyHttpFileProcessType_Failed;
					break;
				}
			}
			else
			{
				res = curl_easy_getinfo( curl , CURLINFO_SIZE_DOWNLOAD , &_totalSize );

				//curl_easy_cleanup(curl);

				_dlSize	  = _totalSize;		//更Size

				nextState = EM_MyHttpFileProcessType_OK;
				break;
			}
			if (m_bInterrupt)
			{
				nextState=EM_MyHttpFileProcessType_Interrupt;
				//	_isRunThread=false;
				break ;
			}

		}
		fclose( file );
		//curl_easy_cleanup(curl);

		_state = nextState;

		return 0;
	}

	__finally
	{
		_isRunThread = false;
	}
}

int MyHttpFile::CurlProgressCallback( void *clientp , double dltotal , double dlnow , double ultotal , double ulnow )
{
	MyHttpFile* This = (MyHttpFile*)clientp;
	This->_totalSize = dltotal;		//郎
	This->_dlSize	 = dlnow;		//更Size

	float time= float( timeGetTime()-This->m_sTime );
	time=time+1;
	time=time/1000.0f;

	This->m_dlKbs=(float )dlnow/time/1000.0f;

	//if( EM_MyHttpFileProcessType_Download != This->_state )
	//	return 1;

	return 0;
}

size_t  MyHttpFile::WriteFunctionCallback( void *ptr, size_t size, size_t nmemb, void *stream )
{	
	FILE* out=(FILE*)stream;

	int	Tell = ftell(out);

	return fwrite( ptr, size, nmemb, out );
}

//////////////////////////////////////////////////////////////////////////
//璶―い耞更
bool	MyHttpFile::Interrupt( )
{
	if(_isRunThread ==true )
	{
		m_bInterrupt=1;
		int		i;
		_state = EM_MyHttpFileProcessType_Interrupt;

		//单ミ
		for( i = 0 ; i < 10 ; i++ )
		{
			if( _isRunThread == false )
				break;
			Sleep( 10 );
		}
		//assert( i != 1000 );
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
#pragma region test

MyHttpFileProcessTypeENUM MyHttpFile::State()
{
	return _state;
}

double	MyHttpFile::TotalSize()
{
	return _totalSize;
}

double	MyHttpFile::DownloadSize()
{
	return _dlSize;
}

const char* MyHttpFile::Url( )
{
	return _url.c_str();
}

const char* MyHttpFile::DestFolder( )
{
	return _destFolder.c_str();
}

const char* MyHttpFile::RemoteFileName( )
{
	return _remoteFile.c_str();
}

const char* MyHttpFile::LocalFileName( )
{
	return _remoteFile.c_str();
}

bool	MyHttpFile::IsRunThread()
{
	return _isRunThread;
}
#pragma endregion	//弄戈
//////////////////////////////////////////////////////////////////////////
#pragma region test
void MyHttpFile::Init()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

void MyHttpFile::Release()
{
	curl_global_cleanup();
}
#pragma endregion //办砞﹚
//////////////////////////////////////////////////////////////////////////