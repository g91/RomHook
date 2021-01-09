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
	EM_MyHttpFileProcessType_Download	,	//下載中
	EM_MyHttpFileProcessType_OK			,	//下載成功
	EM_MyHttpFileProcessType_Failed		,	//下載失敗
	EM_MyHttpFileProcessType_Interrupt	,	//要求中斷
};

class MyHttpFile
{
	double	_totalSize;		//檔案大小
	double	_dlSize;		//已下載Size

	string	_url;			
	int		_port;

	string	_url_proxy;		
	int		_port_proxy;

	string	_destFolder;
	string	_remoteFile;	//下載的檔案名稱
	string  _localFile;		//儲存的檔案名稱
	string	_userpwd;		//帳號密碼
	
	bool	_isRunThread;

	MyHttpFileProcessTypeENUM	_state;		//目前處理狀態

	HANDLE	_hThread;
	DWORD	_threadId;

	vector<CURLcode>	_curlErrCode;

public:
	MyHttpFile( );
	~MyHttpFile( );
	
	static void Init();
	static void Release();

	//下載
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

	//要求中斷下載
	bool	Interrupt( );

	//清除
	bool	Clear();

	//是否還在跑 Thread  (下載中)
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
