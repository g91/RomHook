#pragma once

#ifndef __NB_FILE_TRANSFER_H__
#define __NB_FILE_TRANSFER_H__

#pragma managed(push, off)
#include <Windows.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <deque>

#include "../netbridge/NetBridge.h"
#include "../smallobj/StaticString.h"

#define MAX_FTM_PG_NUM		7
#define MAX_FTM_FUNC_RECV	10
#define DEFAULT_DATA_LENGTH	1024*32 //64K
#define MAX_CRC_TABLE_SIZE	256

enum FileTransferManagerPacketType
{
	EM_FTM_PG_BASE				= 0,
	EM_FTM_PG_TXtoRX_NOTIFY		,
	EM_FTM_PG_RXtoTX_READY		,
	EM_FTM_PG_TXtoRX_BEGIN_FILE	,
	EM_FTM_PG_RXtoTX_BEGIN_FILE	,
	EM_FTM_PG_TXtoRX_FILE_DATA	,
	EM_FTM_PG_RXtoTX_CRC_ERROR	,
	EM_FTM_PG_TXtoRX_END_FILE	,
	EM_FTM_PG_RXtoTX_END_FILE	,
	EM_FTM_PG_TXtoRX_COMPLETED	,
	EM_FTM_PG_TXtoRX_ABORT		,

	EM_FTM_PG_FORCE_DWORD		= 0x7FFFFFFF
};

enum FileTranferStatusENUM
{
	EM_FT_StatusStandBy		,
	EM_FT_StatusTransfer	,
	EM_FT_StatusError		,
	EM_FT_StatusCompleted
};

enum MyCrcFileModeENUM
{
	EM_CrcFileMode_Read	,
	EM_CrcFileMode_Write,
};

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct FTM_PG_BASE
{
	int Type;
	int GUID;

	FTM_PG_BASE()
	{
		Type = EM_FTM_PG_BASE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_NOTIFY : public FTM_PG_BASE
{
	PG_TXtoRX_NOTIFY()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_NOTIFY;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_RXtoTX_READY : public FTM_PG_BASE
{
	int PeerGUID;

	PG_RXtoTX_READY()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_RXtoTX_READY;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_BEGIN_FILE : public FTM_PG_BASE
{
	int							FileGUID;
	StaticWCharString<MAX_PATH> LocalFileName;
	StaticWCharString<MAX_PATH> PeerFileName;
	unsigned long				FileSize;

	PG_TXtoRX_BEGIN_FILE()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_BEGIN_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_RXtoTX_BEGIN_FILE : public FTM_PG_BASE
{
	PG_RXtoTX_BEGIN_FILE()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_RXtoTX_BEGIN_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_FILE_DATA : public FTM_PG_BASE
{
	unsigned long Offset;
	unsigned long DataSize;
	unsigned long CRC;

	PG_TXtoRX_FILE_DATA()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_FILE_DATA;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_RXtoTX_CRC_ERROR : public FTM_PG_BASE
{
	PG_RXtoTX_CRC_ERROR()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_RXtoTX_CRC_ERROR;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_END_FILE : public FTM_PG_BASE
{
	FILETIME CreateTime;
	FILETIME LastWriteTime;

	PG_TXtoRX_END_FILE()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_END_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_RXtoTX_END_FILE : public FTM_PG_BASE
{
	PG_RXtoTX_END_FILE()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_RXtoTX_END_FILE;
	}
};

//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_COMPLETED : public FTM_PG_BASE
{
	PG_TXtoRX_COMPLETED()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_COMPLETED;
	}
};


//---------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------
struct PG_TXtoRX_ABORT : public FTM_PG_BASE
{
	PG_TXtoRX_ABORT()
	{
		memset(this, 0, sizeof(*this));
		Type = EM_FTM_PG_TXtoRX_ABORT;
	}
};

// ************************************************************************************************************************************************************
class NetBridgeFileTransfer;
class NetBridgeFileSender;
class NetBridgeFileReceiver;
class NetBridgeFileTransferManager;

// ************************************************************************************************************************************************************
#define PFUNC_FTM_PG		boost::function<void (unsigned long, unsigned long, void*)>
#define PFUNC_FT_COMPLETED	boost::function<void (NetBridgeFileTransfer*)>
#define PFUNC_FT_BEGIN_FILE boost::function<void (NetBridgeFileTransfer*, int, const wchar_t*, unsigned long, int, int)>	//(ft, fileid, filename, filesize, completedcount, totalcount)
#define PFUNC_FT_PROGRESS	boost::function<void (NetBridgeFileTransfer*, int, unsigned long)>								//(ft, fileid, offset)
#define PFUNC_FT_END_FILE	boost::function<void (NetBridgeFileTransfer*, int)>												//(ft, fileid)
// ************************************************************************************************************************************************************
class MyCrcFile
{
protected:
	static const unsigned long m_CrcTable[MAX_CRC_TABLE_SIZE];

protected:
	MyCrcFileModeENUM m_Mode;
	std::wstring	  m_FileName;
	std::fstream	  m_Stream;
	unsigned long	  m_CRC;
	unsigned long	  m_Offset;
	unsigned long	  m_FileSize;

public:
	MyCrcFile(MyCrcFileModeENUM Mode);
	virtual ~MyCrcFile();

protected:
	bool		 MakeDir	(const wchar_t* lpszPath);
	std::wstring GetFilePath(const wchar_t* lpszFilePath);
	void		 CalCRC		(void* pData, unsigned long size);	

public:
	bool Open (const wchar_t* lpszFileName);
	int	 Read (unsigned long size, unsigned long dwBufferSize, void* pBuffer);
	bool Write(unsigned long dwOffset, void* pData, unsigned long size);
	void Close();

public:
	void GetFileTime	(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime);
	void UpdateFileTime	(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime);

public:
	const wchar_t*	GetFileName()						{return m_FileName.c_str();}
	void 			SetFileName(const wchar_t* value)	{m_FileName = value;}
	unsigned long	GetCRC()							{return m_CRC;}
	unsigned long	GetOffset()							{return m_Offset;}
	unsigned long	GetFileSize()						{return m_FileSize;}
	void			SetFileSize(unsigned long value)	{m_FileSize = value;}

public:
	__declspec(property(get = GetFileName, put = SetFileName	)) const wchar_t*	FileName;
	__declspec(property(get = GetCRC							)) unsigned long	CRC;
	__declspec(property(get = GetOffset							)) unsigned long	Offset;
	__declspec(property(get = GetFileSize, put = SetFileSize	)) unsigned long	FileSize;
};

// ************************************************************************************************************************************************************
class NetBridgeFileTransfer
{
protected:
	friend class NetBridgeFileTransferManager;

protected:
	struct TransferTask
	{
		int			 GUID;
		std::wstring LocalFileName;
		std::wstring PeerFileName;

		TransferTask()
		{
			Init();
		}

		void Init()
		{
			GUID		  = 0;
			LocalFileName = L"";
			PeerFileName  = L"";
		}
	};

protected:
	NetBridgeFileTransferManager*	m_Manager;
	MyCrcFile*						m_File;
	int								m_GUID;	
	int								m_PeerGUID;
	unsigned long					m_PeerNetID;
	int								m_Status;
	int								m_TaskID;
	std::deque<TransferTask>		m_Tasks;
	std::deque<TransferTask>		m_CompletedTasks;
	TransferTask					m_CurrentTask;

	void*							m_Buffer;
	unsigned long					m_BufferSize;

	void*							m_UserData;
	unsigned long					m_UserDataSize;

	bool							m_CrcError;

	PFUNC_FT_COMPLETED				m_OnCompleted;
	PFUNC_FT_BEGIN_FILE				m_OnBeginFile;
	PFUNC_FT_PROGRESS				m_OnProgress;
	PFUNC_FT_END_FILE				m_OnEndFile;

public:
	NetBridgeFileTransfer(NetBridgeFileTransferManager* manager);
	virtual ~NetBridgeFileTransfer();

protected:
	void* GetBuffer(unsigned long size);

public:
	virtual void Process(){}
	virtual void Complete();

public:
	virtual	void AddFile	(const wchar_t* localfilename, const wchar_t* peerfilename, int guid = 0);
	virtual	bool BeginFile	(){return true;}
	virtual bool HandleFile	(unsigned long offset, unsigned long crc, unsigned long datasize, void* data){return true;}
	virtual void EndFile	(FILETIME* createtime, FILETIME* lastwritetime){}
	virtual	void Abort		(){}

public:
	virtual int				GetGUID()								{return m_GUID;}
	virtual void			SetGUID(int value)						{m_GUID = value;}
	virtual int				GetPeerGUID()							{return m_PeerGUID;}
	virtual void			SetPeerGUID(int value)					{m_PeerGUID = value;}
	virtual unsigned long	GetPeerNetID()							{return m_PeerNetID;}
	virtual void			SetPeerNetID(unsigned long value)		{m_PeerNetID = value;}
	virtual int				GetStatus()								{return m_Status;}
	virtual void			SetStatus(int value)					{m_Status = value;}
	virtual TransferTask&	GetCurrentTask()						{return m_CurrentTask;}
	virtual unsigned long	GetFileSize();
	virtual void			SetFileSize(unsigned long value)		{}
	virtual void*			GetUserData()							{return m_UserData;}
	virtual void			SetUserData(void* value)				{m_UserData = value;}
	virtual unsigned long	GetUserDataSize()						{return m_UserDataSize;}
	virtual void			SetUserDataSize(unsigned long value)	{m_UserDataSize = value;}
	virtual bool			GetCrcError()							{return m_CrcError;}
	virtual void			SetCrcError(bool value)					{m_CrcError = value;}

	virtual PFUNC_FT_COMPLETED	GetOnCompleted()							{return m_OnCompleted;}
	virtual void				SetOnCompleted(PFUNC_FT_COMPLETED value)	{m_OnCompleted = value;}
	virtual PFUNC_FT_BEGIN_FILE	GetOnBeginFile()							{return m_OnBeginFile;}
	virtual void				SetOnBeginFile(PFUNC_FT_BEGIN_FILE value)	{m_OnBeginFile = value;}
	virtual PFUNC_FT_PROGRESS	GetOnProgress()								{return m_OnProgress;}
	virtual void				SetOnProgress(PFUNC_FT_PROGRESS value)		{m_OnProgress = value;}
	virtual PFUNC_FT_END_FILE	GetOnEndFile()								{return m_OnEndFile;}
	virtual void				SetOnEndFile(PFUNC_FT_END_FILE value)		{m_OnEndFile = value;}

public:
	__declspec(property(get = GetGUID			, put = SetGUID			)) int					GUID;	
	__declspec(property(get = GetPeerGUID		, put = SetPeerGUID		)) int					PeerGUID;
	__declspec(property(get = GetPeerNetID		, put = SetPeerNetID	)) unsigned long		PeerNetID;
	__declspec(property(get = GetStatus			, put = SetStatus		)) int					Status;
	__declspec(property(get = GetCurrentTask							)) TransferTask&		CurrentTask;
	__declspec(property(get = GetFileSize		, put = SetFileSize		)) unsigned long		FileSize;
	__declspec(property(get = GetUserData		, put = SetUserData		)) void*				UserData;
	__declspec(property(get = GetUserDataSize	, put = SetUserDataSize	)) unsigned long		UserDataSize;
	__declspec(property(get = GetCrcError		, put = SetCrcError		)) bool					CrcError;
	__declspec(property(get = GetOnCompleted	, put = SetOnCompleted	)) PFUNC_FT_COMPLETED	OnCompleted;
	__declspec(property(get = GetOnBeginFile	, put = SetOnBeginFile	)) PFUNC_FT_BEGIN_FILE	OnBeginFile;
	__declspec(property(get = GetOnProgress		, put = SetOnProgress	)) PFUNC_FT_PROGRESS	OnProgress;
	__declspec(property(get = GetOnEndFile		, put = SetOnEndFile	)) PFUNC_FT_END_FILE	OnEndFile;
};

// ************************************************************************************************************************************************************
class NetBridgeFileSender : public NetBridgeFileTransfer
{
protected:
	friend class NetBridgeFileTransferManager;

public:
	NetBridgeFileSender(NetBridgeFileTransferManager* pManager);

public:
	void Transfer();

public:
	virtual void Process ();
	virtual void Complete();
	virtual	void Abort	 ();

public:	
	virtual	bool BeginFile	();
	virtual bool HandleFile	(unsigned long dwOffset, unsigned long dwCRC, unsigned long dwDataSize, void* pData);
	virtual void EndFile	(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime);

public:
	virtual void SetStatus(int value);
};

// ************************************************************************************************************************************************************
class NetBridgeFileReceiver : public NetBridgeFileTransfer
{
public:
	NetBridgeFileReceiver(NetBridgeFileTransferManager* pManager);

public:
	virtual	void Abort();

public:
	virtual	bool BeginFile	();
	virtual bool HandleFile	(unsigned long dwOffset, unsigned long dwCRC, unsigned long dwDataSize, void* pData);
	virtual void EndFile	(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime);

public:
	virtual void SetFileSize(unsigned long value);
};


// ************************************************************************************************************************************************************
class NetBridgeFileTransferManager
{
protected:
	friend class NetBridgeFileTransfer;
	friend class NetBridgeFileSender;
	friend class NetBridgeFileReceiver;

protected:
	CNetBridge*								m_NetBridge;
	int										m_PGID;
	std::map<int, PFUNC_FTM_PG>				m_PGCallBack;
	std::vector<int>						m_RecycleBin;
	std::map<int, NetBridgeFileTransfer*>	m_FileTransfers;
	void*									m_Buffer;
	unsigned long							m_BufferSize;

public:
	NetBridgeFileTransferManager(CNetBridge* netbridge, int pgid);
	virtual ~NetBridgeFileTransferManager();

protected:
	void InitPG();

public:
	void Process();

public:
	NetBridgeFileSender*	CreateSender();
	void					LaunchSender(int guid);

protected:	
	NetBridgeFileReceiver*	CreateReceiver		();
	NetBridgeFileSender*	GetSender			(int guid);	
	NetBridgeFileReceiver*	GetReceiver			(int guid);
	void					RemoveFileTransfer	(int guid);
	void					RecycleFileTransfer	(int guid);

protected:
	void* GetBuffer(unsigned long size);

protected:
	virtual int	GetHeaderSize() = 0;
	virtual void Send(unsigned long netid, unsigned long size, void* pg) = 0;

protected:
	void S_PG_TXtoRX_NOTIFY		(unsigned long netid, int guid);
	void S_PG_RXtoTX_READY		(unsigned long netid, int guid, int peerguid);
	void S_PG_TXtoRX_BEGIN_FILE	(unsigned long netid, int guid, int fileguid, const wchar_t* localfilename, const wchar_t* peerfilename, unsigned long filesize);
	void S_PG_RXtoTX_BEGIN_FILE	(unsigned long netid, int guid);
	void S_PG_TXtoRX_FILE_DATA	(unsigned long netid, int guid, unsigned long offset, unsigned long crc, unsigned long datasize, void* data);
	void S_PG_RXtoTX_CRC_ERROR	(unsigned long netid, int guid);
	void S_PG_TXtoRX_END_FILE	(unsigned long netid, int guid, FILETIME* createtime, FILETIME* lastwritetime);
	void S_PG_RXtoTX_END_FILE	(unsigned long netid, int guid);
	void S_PG_TXtoRX_COMPLETED	(unsigned long netid, int guid);
	void S_PG_TXtoRX_ABORT		(unsigned long netid, int guid);

protected:
	void On_PG_TXtoRX_NOTIFY	(unsigned long netid, int guid);
	void On_PG_RXtoTX_READY		(unsigned long netid, int guid, int peerguid);
	void On_PG_TXtoRX_BEGIN_FILE(unsigned long netid, int guid, int fileguid, const wchar_t* localfilename, const wchar_t* peerfilename, unsigned long filesize);
	void On_PG_RXtoTX_BEGIN_FILE(unsigned long netid, int guid);
	void On_PG_TXtoRX_FILE_DATA	(unsigned long netid, int guid, unsigned long offset, unsigned long crc, unsigned long datasize, void* data);
	void On_PG_RXtoTX_CRC_ERROR	(unsigned long netid, int guid);
	void On_PG_TXtoRX_END_FILE	(unsigned long netid, int guid, FILETIME* createtime, FILETIME* lastwritetime);
	void On_PG_RXtoTX_END_FILE	(unsigned long netid, int guid);
	void On_PG_TXtoRX_COMPLETED	(unsigned long netid, int guid);
	void On_PG_TXtoRX_ABORT		(unsigned long netid, int guid);

protected:
	void _PG_TXtoRX_NOTIFY		(unsigned long netid, unsigned long size, void* pg);
	void _PG_RXtoTX_READY		(unsigned long netid, unsigned long size, void* pg);
	void _PG_TXtoRX_BEGIN_FILE	(unsigned long netid, unsigned long size, void* pg);
	void _PG_RXtoTX_BEGIN_FILE	(unsigned long netid, unsigned long size, void* pg);
	void _PG_TXtoRX_FILE_DATA	(unsigned long netid, unsigned long size, void* pg);
	void _PG_RXtoTX_CRC_ERROR	(unsigned long netid, unsigned long size, void* pg);
	void _PG_TXtoRX_END_FILE	(unsigned long netid, unsigned long size, void* pg);
	void _PG_RXtoTX_END_FILE	(unsigned long netid, unsigned long size, void* pg);
	void _PG_TXtoRX_COMPLETED	(unsigned long netid, unsigned long size, void* pg);
	void _PG_TXtoRX_ABORT		(unsigned long netid, unsigned long size, void* pg);

public:
	bool Recv					(unsigned long netid, unsigned long size, void* pg);
};
#pragma managed(pop)
#endif