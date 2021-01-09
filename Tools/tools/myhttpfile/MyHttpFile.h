#pragma once
#pragma warning (disable:4949)

#pragma unmanaged
//////////////////////////////////////////////////////////////////////////
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <String>
#include <windows.h>
#include <vector>
//////////////////////////////////////////////////////////////////////////
using namespace std;

enum	MyHttpFileProcessTypeENUM
{
	EM_MyHttpFileProcessType_None		,
	EM_MyHttpFileProcessType_Download	,	//更い
	EM_MyHttpFileProcessType_OK			,	//更Θ
	EM_MyHttpFileProcessType_Failed		,	//更ア
	EM_MyHttpFileProcessType_Interrupt	,	//璶―い耞
};

class MyHttpFile
{
	double	_totalSize;		//郎
	double	_dlSize;		//更Size

	string	_url;			
	int		_port;

	string	_url_proxy;		
	int		_port_proxy;

	string	_destFolder;
	string	_remoteFile;	//更郎嘿
	string  _localFile;		//纗郎嘿
	string	_userpwd;		//眀腹盞絏
	
	bool	_isRunThread;

	MyHttpFileProcessTypeENUM	_state;		//ヘ玡矪瞶篈

	HANDLE	_hThread;
	DWORD	_threadId;

	vector<CURLcode>	_curlErrCode;

public:
	MyHttpFile( );
	~MyHttpFile( );
	
	static void Init();
	static void Release();

	//更
	void	SetDownloadUrl( const char* url );
	void	SetDownloadPort( int port );

	void	SetProxyUrl( const char* url );
	void	SetProxyPort( int port );
	
	void	SetUserPwd( string	UserPwd );

	bool	Download( string destFolder , string remoteFile ,string localFile );
	bool	Download_NoThread( string destFolder , string remoteFile , string localFile , int tryTimes );
	bool	Download_NoThread( string destFolder , string remoteFile , string localFile );
	/*
	bool	Download( const char* url , const char* destFolder , const char* remoteFile , char* localFile );

	bool	Download_NoThread( const char* url , const char* destFolder , const char* remoteFile , char* localFile );

	bool	Download_NoThread( const char* url , const char* destFolder , const char* remoteFile , char* localFile , int TryTimes );
*/
	vector<CURLcode>*	GetCurlErrCode(){ return& _curlErrCode; };

	//璶―い耞更
	bool	Interrupt( );

	//睲埃
	bool	Clear();

	//琌临禲 Thread  (更い)
	bool	IsRunThread();

	MyHttpFileProcessTypeENUM State();

	double	TotalSize();
	double	DownloadSize();

	const char* Url( );
	const char* DestFolder( );
	const char* RemoteFileName( );
	const char* LocalFileName( );
	int m_Got_Nothing;
	float m_dlKbs;
	int m_sTime;

protected:
	static DWORD WINAPI _St_DownloadThread( void* This ){ return ((MyHttpFile*)This)->_DownloadThread() ; };
	int    _DownloadThread( );

	int  m_bInterrupt;
	static int CurlProgressCallback(void *clientp,double dltotal,double dlnow,double ultotal,double ulnow );
	static size_t WriteFunctionCallback( void *ptr, size_t size, size_t nmemb, void *stream );

};






//////////////////////////////////////////////////////////////////////////
#pragma managed
