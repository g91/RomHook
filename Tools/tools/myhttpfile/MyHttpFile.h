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
	EM_MyHttpFileProcessType_Download	,	//�U����
	EM_MyHttpFileProcessType_OK			,	//�U����
	EM_MyHttpFileProcessType_Failed		,	//�U����
	EM_MyHttpFileProcessType_Interrupt	,	//�n�D���_
};

class MyHttpFile
{
	double	_totalSize;		//�ɮפj�p
	double	_dlSize;		//�w�U��Size

	string	_url;			
	int		_port;

	string	_url_proxy;		
	int		_port_proxy;

	string	_destFolder;
	string	_remoteFile;	//�U�����ɮצW��
	string  _localFile;		//�x�s���ɮצW��
	string	_userpwd;		//�b���K�X
	
	bool	_isRunThread;

	MyHttpFileProcessTypeENUM	_state;		//�ثe�B�z���A

	HANDLE	_hThread;
	DWORD	_threadId;

	vector<CURLcode>	_curlErrCode;

public:
	MyHttpFile( );
	~MyHttpFile( );
	
	static void Init();
	static void Release();

	//�U��
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

	//�n�D���_�U��
	bool	Interrupt( );

	//�M��
	bool	Clear();

	//�O�_�٦b�] Thread  (�U����)
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
