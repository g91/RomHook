#pragma managed(push, off)
#include "NetBridgeFileTransfer.h"
#include <algorithm>
#include <locale>
#include <errno.h>
#include "smallobj/SmallObj.h"

// ************************************************************************************************************************************************************
// Table of CRC-32's of all single-byte values (made by make_crc_table)
const unsigned long MyCrcFile::m_CrcTable[256] = {
	0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
	0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
	0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
	0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
	0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
	0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
	0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
	0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
	0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
	0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
	0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
	0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
	0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
	0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
	0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
	0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
	0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
	0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
	0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
	0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
	0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
	0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
	0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
	0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
	0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
	0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
	0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
	0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
	0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
	0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
	0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
	0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
	0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
	0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
	0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
	0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
	0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
	0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
	0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
	0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
	0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
	0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
	0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
	0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
	0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
	0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
	0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
	0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
	0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
	0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
	0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
	0x2d02ef8dL
};

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int	GenerateGUID()
{
	std::string szGUID = "";
	//--COM
	CoInitialize(NULL);

	char buf[64] = {0};

	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf)
			, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);

		szGUID = buf;
	}

	locale loc;
	const collate<char>& coll = use_facet<collate<char> >(loc);

	return coll.hash(szGUID.data(),szGUID.data() + szGUID.length());
}

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
MyCrcFile::MyCrcFile(MyCrcFileModeENUM Mode)
{
	m_Mode		= Mode;
	m_CRC		= 0xFFFFFFFF;
	m_FileName	= L"";
	m_Offset	= 0;
	m_FileSize	= 0;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
MyCrcFile::~MyCrcFile()
{
	Close();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool MyCrcFile::MakeDir(const wchar_t* lpszPath)
{
	bool Result = false;
	size_t found;
	std::wstring wszTokens = L"\\/";
	std::wstring wszDir = L"";
	std::wstring wszPath = lpszPath;

	found = wszPath.find_last_of(wszTokens);
	if (found < wszPath.length())
	{
		wszPath = wszPath + L"\\";
	}

	found = wszPath.find_first_of(wszTokens);

	while(found != wstring::npos)
	{
		wszDir = wszPath.substr(0, found);
		_wmkdir(wszDir.c_str());
		found = wszPath.find_first_of(wszTokens, found + 1);
	}

	int iRetCode = _wmkdir(wszPath.c_str());

	if (iRetCode == 0)
	{
		Result = true;
	}
	else if (iRetCode == -1)
	{
		int iErrCode = 0;
		_get_errno(&iErrCode);

		if (iErrCode == EEXIST)
		{
			Result = true;
		}
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
std::wstring MyCrcFile::GetFilePath(const wchar_t* lpszFilePath)
{
	std::wstring Result = lpszFilePath;

	int iPos1 = (int)Result.find_last_of(L'\\');
	int iPos2 = (int)Result.find_last_of(L'/');

	Result = Result.substr(0, max(iPos1, iPos2) + 1);

	return Result.c_str();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void MyCrcFile::CalCRC(void* pData, unsigned long size)
{
	PBYTE pChunk = (PBYTE)pData;

	for(unsigned long i = 0; i < size; i++)
	{
		m_CRC = m_CrcTable[(m_CRC ^ (*pChunk)) & 0xFF] ^ (m_CRC >> 8);
		pChunk++;
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool MyCrcFile::Open(const wchar_t* lpszFileName)
{
	bool Result = false;

	Close();

	switch (m_Mode)
	{
	case EM_CrcFileMode_Read:
		{
			m_FileName = lpszFileName;

			m_Stream.open(m_FileName.c_str(), ios::in | ios::binary);//開啟檔案，準備讀取

			if (m_Stream.is_open())
			{
				m_Stream.seekg(0, ios::end);
				m_FileSize = m_Stream.tellg();
				m_Stream.seekg(0, ios::beg);

				Result = true;
			}
		}
		break;
	case EM_CrcFileMode_Write:
		{
			m_FileName = lpszFileName;

			//make sure path is existed
			std::wstring wszPath = GetFilePath(m_FileName.c_str());
			MakeDir(wszPath.c_str());

			m_Stream.open(m_FileName.c_str(), ios::in |ios::out | ios::binary | ios::trunc);//開啟檔案 準備寫入

			if (m_Stream.is_open())
			{
				Result = true;
			}
		}
		break;
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int MyCrcFile::Read(unsigned long size, unsigned long dwBufferSize, void* pBuffer)
{
	int Result = 0;

	if (m_Mode == EM_CrcFileMode_Read)
	{
		if (dwBufferSize >= size)
		{
			if (!m_Stream.eof())
			{
				m_Offset = m_Stream.tellg();

				if (m_FileSize >= m_Offset)
				{
					int iRemaining = m_FileSize - m_Offset;

					Result = size;

					if (Result > iRemaining)
					{
						Result = iRemaining;
					}

					if (Result > 0)
					{
						m_Stream.read((char*)pBuffer, Result);					
					}

					CalCRC(pBuffer, Result);
				}
			}
		}
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool MyCrcFile::Write(unsigned long dwOffset, void* pData, unsigned long size)
{
	bool Result = false;

	if (m_Mode == EM_CrcFileMode_Write)
	{
		if(m_Stream.is_open())
		{
			m_Stream.seekg(dwOffset, ios::beg);
			m_Stream.write((char*)pData, size);

			CalCRC(pData, size);

			Result = true;
		}
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void MyCrcFile::Close()
{
	if(m_Stream.is_open())
	{
		m_Stream.close();

		m_CRC		= 0xFFFFFFFF;
		m_FileName	= L"";
		m_Offset	= 0;
		m_FileSize	= 0;
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void MyCrcFile::GetFileTime(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime)
{
	HANDLE hFile = CreateFileW(m_FileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		::GetFileTime(hFile, pftCreateTime, NULL, pftLastWriteTime);
		CloseHandle(hFile);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void MyCrcFile::UpdateFileTime(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime)
{
	HANDLE hFile = CreateFileW(m_FileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::SetFileTime(hFile, pftCreateTime, NULL, pftLastWriteTime);
		CloseHandle(hFile);
	}
}

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileTransfer::NetBridgeFileTransfer(NetBridgeFileTransferManager* manager)
{
	m_Manager		= manager;
	m_File			= NULL;
	m_GUID			= 0;
	m_PeerGUID		= 0;
	m_PeerNetID		= 0xFFFFFFFF;
	m_Status		= 0;
	m_TaskID		= 1;
	m_Buffer		= NULL;
	m_BufferSize	= 0;
	m_UserData		= NULL;
	m_UserDataSize	= 0;
	m_CrcError		= false;
	m_OnCompleted	= NULL;
	m_OnBeginFile	= NULL;
	m_OnProgress	= NULL;
	m_OnEndFile		= NULL;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileTransfer::~NetBridgeFileTransfer()
{
	if (m_Buffer != NULL)
	{
		delete m_Buffer;
	}

	if (m_UserData != NULL)
	{
		delete m_UserData;
	}

	if (m_File != NULL)
	{
		delete m_File;
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void* NetBridgeFileTransfer::GetBuffer(unsigned long size)
{
	if (size > m_BufferSize)
	{
		if (m_Buffer != NULL)
		{
			delete m_Buffer;
		}

		m_BufferSize = ((size / 4) + 1) * 4;

		m_Buffer = new BYTE[m_BufferSize];
	}

	memset(m_Buffer, 0, m_BufferSize);

	return m_Buffer;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransfer::AddFile(const wchar_t* localfilename, const wchar_t* peerfilename, int guid)
{
	TransferTask Task;

	Task.GUID		   = m_TaskID++;
	Task.LocalFileName = localfilename;
	Task.PeerFileName  = peerfilename;

	m_Tasks.push_back(Task);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransfer::Complete()
{
	if (m_OnCompleted != NULL)
	{
		m_OnCompleted(this);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
unsigned long NetBridgeFileTransfer::GetFileSize()
{
	unsigned long Result = 0;

	if (m_File != NULL)
	{
		Result = m_File->FileSize;
	}

	return Result;
}

// ************************************************************************************************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileSender::NetBridgeFileSender(NetBridgeFileTransferManager* pManager)
: NetBridgeFileTransfer(pManager)
{
	m_File = new MyCrcFile(EM_CrcFileMode_Read);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::Transfer()
{
	if (m_Status == EM_FT_StatusStandBy)
	{
		m_Status = EM_FT_StatusTransfer;
	}	
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::Process()
{
	switch (m_Status)
	{
	case EM_FT_StatusStandBy:
		break;
	case EM_FT_StatusTransfer:
		{
			//send 1MB data per process
			for (int i = 0; i < 32; ++i)
			{
				void* pBuffer = GetBuffer(DEFAULT_DATA_LENGTH);
				int ByteRead = m_File->Read(DEFAULT_DATA_LENGTH, DEFAULT_DATA_LENGTH, pBuffer);

				if (ByteRead >= 0)
				{
					if (ByteRead > 0)
					{
						HandleFile(m_File->Offset, m_File->CRC, ByteRead, pBuffer);
					}

					if (ByteRead < DEFAULT_DATA_LENGTH)
					{
						//read end
						EndFile(NULL, NULL);
						Status = EM_FT_StatusStandBy;
						break;
					}
				}
				else
				{
					//read error
					Status = EM_FT_StatusError;
					break;
				}
			}
		}
		break;
	case EM_FT_StatusError:
		break;
	case EM_FT_StatusCompleted:
		break;
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::Complete()
{
	Status = EM_FT_StatusCompleted;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::Abort()
{
	Status = EM_FT_StatusCompleted;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool NetBridgeFileSender::BeginFile()
{
	bool Result = false;

	if (!m_Tasks.empty())
	{
		m_CurrentTask = m_Tasks.front();
		m_Tasks.pop_front();

		Result = m_File->Open(m_CurrentTask.LocalFileName.c_str());

		if (Result == true)
		{
			if (m_OnBeginFile != NULL)
			{
				m_OnBeginFile(this, m_CurrentTask.GUID,  m_CurrentTask.LocalFileName.c_str(), FileSize, m_CompletedTasks.size(), (m_Tasks.size() + m_CompletedTasks.size() + 1));
			}
		}
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool NetBridgeFileSender::HandleFile(unsigned long offset, unsigned long crc, unsigned long datasize, void* data)
{
	m_Manager->S_PG_TXtoRX_FILE_DATA(m_PeerNetID, m_PeerGUID, offset, crc, datasize, data);

	if (m_OnProgress != NULL)
	{
		m_OnProgress(this, m_CurrentTask.GUID, (offset + datasize));
	}

	return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::EndFile(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime)
{
	FILETIME ftCreate;
	FILETIME ftLastWrite;
	m_File->GetFileTime(&ftCreate, &ftLastWrite);
	m_Manager->S_PG_TXtoRX_END_FILE(m_PeerNetID, m_PeerGUID, &ftCreate, &ftLastWrite);

	m_CompletedTasks.push_back(m_CurrentTask);

	if (m_OnEndFile != NULL)
	{
		m_OnEndFile(this, m_CurrentTask.GUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileSender::SetStatus(int value)
{
	if (m_Status == value)
		return;

	m_Status = value;

	switch (m_Status)
	{
	case EM_FT_StatusStandBy:
	case EM_FT_StatusTransfer:
		break;
	case EM_FT_StatusError:
		{
			m_File->Close();
			m_Tasks.clear();
			m_CompletedTasks.clear();
			m_CurrentTask.Init();
		}
		break;
	case EM_FT_StatusCompleted:
		{
			m_File->Close();
			m_Tasks.clear();
			m_CompletedTasks.clear();
			m_CurrentTask.Init();

			if (m_OnCompleted != NULL)
			{
				m_OnCompleted(this);
			}
		}
		break;
	}
}

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileReceiver::NetBridgeFileReceiver(NetBridgeFileTransferManager* pManager)
: NetBridgeFileTransfer(pManager)
{
	m_File = new MyCrcFile(EM_CrcFileMode_Write);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileReceiver::Abort()
{
	m_File->Close();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool NetBridgeFileReceiver::BeginFile()
{
	m_CurrentTask = m_Tasks.front();
	m_Tasks.pop_front();

	return m_File->Open(m_CurrentTask.LocalFileName.c_str());
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool NetBridgeFileReceiver::HandleFile(unsigned long dwOffset, unsigned long dwCRC, unsigned long dwDataSize, void* pData)
{
	bool Result = false;

	Result = m_File->Write(dwOffset, pData, dwDataSize);

	if (dwCRC != m_File->CRC)
	{
		m_CrcError = true;
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileReceiver::EndFile(FILETIME* pftCreateTime, FILETIME* pftLastWriteTime)
{
	std::wstring wszFileName = m_File->FileName;
	m_File->Close();

	if (pftCreateTime != NULL && pftLastWriteTime != NULL)
	{
		m_File->FileName = wszFileName.c_str();
		m_File->UpdateFileTime(pftCreateTime, pftLastWriteTime);
		m_File->FileName = L"";
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileReceiver::SetFileSize(unsigned long value)
{
	if (m_File != NULL)
	{
		m_File->FileSize = value;
	}
}

// ************************************************************************************************************************************************************
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileTransferManager::NetBridgeFileTransferManager(CNetBridge* netbridge, int pgid)
{
	m_NetBridge  = netbridge;
	m_PGID		 = pgid;
	m_Buffer	 = NULL;
	m_BufferSize = 0;

	InitPG();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileTransferManager::~NetBridgeFileTransferManager()
{
	m_RecycleBin.clear();

	//--------------------------------------------------
	std::map<int, NetBridgeFileTransfer*>::iterator it;

	for (it = m_FileTransfers.begin(); it != m_FileTransfers.end(); it++)
	{
		NetBridgeFileTransfer* pFT = it->second;
		if (pFT != NULL)
		{
			delete pFT;
		}
	}
	m_FileTransfers.clear();
	//--------------------------------------------------

	if (m_Buffer != NULL)
	{
		delete m_Buffer;
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::InitPG()
{
	m_PGCallBack[EM_FTM_PG_TXtoRX_NOTIFY]		= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_NOTIFY, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_RXtoTX_READY]		= boost::bind<void>(&NetBridgeFileTransferManager::_PG_RXtoTX_READY, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_TXtoRX_BEGIN_FILE]	= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_BEGIN_FILE, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_RXtoTX_BEGIN_FILE]	= boost::bind<void>(&NetBridgeFileTransferManager::_PG_RXtoTX_BEGIN_FILE, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_TXtoRX_FILE_DATA]	= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_FILE_DATA, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_RXtoTX_CRC_ERROR]	= boost::bind<void>(&NetBridgeFileTransferManager::_PG_RXtoTX_CRC_ERROR, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_TXtoRX_END_FILE]		= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_END_FILE, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_RXtoTX_END_FILE]		= boost::bind<void>(&NetBridgeFileTransferManager::_PG_RXtoTX_END_FILE, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_TXtoRX_COMPLETED]	= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_COMPLETED, this, _1, _2, _3);
	m_PGCallBack[EM_FTM_PG_TXtoRX_ABORT]		= boost::bind<void>(&NetBridgeFileTransferManager::_PG_TXtoRX_ABORT, this, _1, _2, _3);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::Process()
{
	//--------------------------------------------------
	for each (int GUID in m_RecycleBin)
	{
		RemoveFileTransfer(GUID);
	}
	m_RecycleBin.clear();
	//--------------------------------------------------

	//--------------------------------------------------
	std::map<int, NetBridgeFileTransfer*>::iterator it;

	for (it = m_FileTransfers.begin(); it != m_FileTransfers.end(); it++)
	{
		NetBridgeFileTransfer* pFT = it->second;
		if (pFT != NULL)
		{
			pFT->Process();
		}
	}
	//--------------------------------------------------
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileSender* NetBridgeFileTransferManager::CreateSender()
{
	NetBridgeFileSender* Result = new NetBridgeFileSender(this);
	Result->GUID = GenerateGUID();
	m_FileTransfers[Result->GUID] = Result;

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::LaunchSender(int guid)
{
	NetBridgeFileSender* pTx = GetSender(guid);

	if (pTx)
	{
		S_PG_TXtoRX_NOTIFY(pTx->PeerNetID, guid);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileReceiver* NetBridgeFileTransferManager::CreateReceiver()
{
	NetBridgeFileReceiver* Result = new NetBridgeFileReceiver(this);
	Result->GUID = GenerateGUID();
	m_FileTransfers[Result->GUID] = Result;
	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileSender* NetBridgeFileTransferManager::GetSender(int guid)
{
	NetBridgeFileSender* Result = NULL;

	std::map<int, NetBridgeFileTransfer*>::iterator it = m_FileTransfers.find(guid);

	if (it != m_FileTransfers.end())
	{
		Result = (NetBridgeFileSender*)it->second;
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
NetBridgeFileReceiver* NetBridgeFileTransferManager::GetReceiver(int guid)
{
	NetBridgeFileReceiver* Result = NULL;

	std::map<int, NetBridgeFileTransfer*>::iterator it = m_FileTransfers.find(guid);

	if (it != m_FileTransfers.end())
	{
		Result = (NetBridgeFileReceiver*)it->second;
	}

	return Result;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::RemoveFileTransfer(int guid)
{
	std::map<int, NetBridgeFileTransfer*>::iterator it = m_FileTransfers.find(guid);

	if (it != m_FileTransfers.end())
	{
		NetBridgeFileTransfer* pFT = it->second;

		if (pFT != NULL)
		{
			delete pFT;
		}

		m_FileTransfers.erase(it);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::RecycleFileTransfer(int guid)
{
	m_RecycleBin.push_back(guid);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void* NetBridgeFileTransferManager::GetBuffer(unsigned long size)
{
	if (size > m_BufferSize)
	{
		if (m_Buffer != NULL)
		{
			delete m_Buffer;
		}

		m_BufferSize = ((size / 4) + 1) * 4;

		m_Buffer = new BYTE[m_BufferSize];
	}

	memset(m_Buffer, 0, m_BufferSize);

	return m_Buffer;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_NOTIFY(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_NOTIFY);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_NOTIFY* pHeader = (PG_TXtoRX_NOTIFY*)pTraveler;
	pHeader->Type = EM_FTM_PG_TXtoRX_NOTIFY;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_RXtoTX_READY(unsigned long netid, int guid, int peerguid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_RXtoTX_READY);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_RXtoTX_READY* pHeader = (PG_RXtoTX_READY*)pTraveler;
	pHeader->Type	  = EM_FTM_PG_RXtoTX_READY;
	pHeader->GUID	  = guid;
	pHeader->PeerGUID = peerguid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_BEGIN_FILE(unsigned long netid, int guid, int fileguid, const wchar_t* localfilename, const wchar_t* peerfilename, unsigned long filesize)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_BEGIN_FILE);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_BEGIN_FILE* pHeader = (PG_TXtoRX_BEGIN_FILE*)pTraveler;
	pHeader->Type			= EM_FTM_PG_TXtoRX_BEGIN_FILE;
	pHeader->GUID			= guid;
	pHeader->FileGUID		= fileguid;
	pHeader->LocalFileName	= localfilename;
	pHeader->PeerFileName	= peerfilename;
	pHeader->FileSize		= filesize;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_RXtoTX_BEGIN_FILE(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_RXtoTX_BEGIN_FILE);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_RXtoTX_BEGIN_FILE* pHeader = (PG_RXtoTX_BEGIN_FILE*)pTraveler;
	pHeader->Type = EM_FTM_PG_RXtoTX_BEGIN_FILE;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_FILE_DATA(unsigned long netid, int guid, unsigned long offset, unsigned long crc, unsigned long datasize, void* data)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_FILE_DATA) + datasize;

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_FILE_DATA* pHeader = (PG_TXtoRX_FILE_DATA*)pTraveler;
	pHeader->Type	  = EM_FTM_PG_TXtoRX_FILE_DATA;
	pHeader->GUID	  = guid;
	pHeader->Offset	  = offset;
	pHeader->CRC	  = crc;
	pHeader->DataSize = datasize;

	pTraveler += sizeof(PG_TXtoRX_FILE_DATA);
	memcpy(pTraveler, data, datasize);

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_RXtoTX_CRC_ERROR(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_RXtoTX_CRC_ERROR);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_RXtoTX_CRC_ERROR* pHeader = (PG_RXtoTX_CRC_ERROR*)pTraveler;
	pHeader->Type = EM_FTM_PG_RXtoTX_CRC_ERROR;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_END_FILE(unsigned long netid, int guid, FILETIME* createtime, FILETIME* lastwritetime)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_END_FILE);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_END_FILE* pHeader = (PG_TXtoRX_END_FILE*)pTraveler;
	pHeader->Type		   = EM_FTM_PG_TXtoRX_END_FILE;
	pHeader->GUID		   = guid;
	pHeader->CreateTime	   = (*createtime);
	pHeader->LastWriteTime = (*lastwritetime);

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_RXtoTX_END_FILE(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_RXtoTX_END_FILE);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_RXtoTX_END_FILE* pHeader = (PG_RXtoTX_END_FILE*)pTraveler;
	pHeader->Type = EM_FTM_PG_RXtoTX_END_FILE;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_COMPLETED(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_COMPLETED);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_COMPLETED* pHeader = (PG_TXtoRX_COMPLETED*)pTraveler;
	pHeader->Type = EM_FTM_PG_TXtoRX_COMPLETED;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::S_PG_TXtoRX_ABORT(unsigned long netid, int guid)
{
	unsigned long dwPacketSize = GetHeaderSize() + sizeof(PG_TXtoRX_ABORT);

	void* pPacket = GetBuffer(dwPacketSize);
	PBYTE pTraveler = (PBYTE)pPacket;

	pTraveler += GetHeaderSize();

	PG_TXtoRX_ABORT* pHeader = (PG_TXtoRX_ABORT*)pTraveler;
	pHeader->Type = EM_FTM_PG_TXtoRX_ABORT;
	pHeader->GUID = guid;

	Send(netid, dwPacketSize, pPacket);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_NOTIFY(unsigned long netid, int guid)
{
	NetBridgeFileReceiver* pRx = CreateReceiver();
	pRx->PeerGUID  = guid;
	pRx->PeerNetID = netid;

	S_PG_RXtoTX_READY(netid, guid, pRx->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_RXtoTX_READY(unsigned long netid, int guid, int peerguid)
{
	NetBridgeFileSender* pTx = GetSender(guid);

	if (pTx == NULL)
		return;

	pTx->PeerGUID  = peerguid;
	pTx->PeerNetID = netid;

	if (pTx->BeginFile())
	{
		S_PG_TXtoRX_BEGIN_FILE(netid, peerguid, pTx->CurrentTask.GUID, pTx->CurrentTask.LocalFileName.c_str(), pTx->CurrentTask.PeerFileName.c_str(), pTx->FileSize);
	}
	else
	{
		S_PG_TXtoRX_COMPLETED(netid, peerguid);

		pTx->Complete();

		RecycleFileTransfer(pTx->GUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_BEGIN_FILE(unsigned long netid, int guid, int fileguid, const wchar_t* localfilename, const wchar_t* peerfilename, unsigned long filesize)
{
	NetBridgeFileReceiver* pRx = GetReceiver(guid);

	if (pRx == NULL)
		return;

	pRx->AddFile(peerfilename, localfilename, fileguid);

	if (pRx->BeginFile())
	{
		pRx->FileSize = filesize;

		S_PG_RXtoTX_BEGIN_FILE(netid, pRx->PeerGUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_RXtoTX_BEGIN_FILE(unsigned long netid, int guid)
{
	NetBridgeFileSender* pTx = GetSender(guid);

	if (pTx == NULL)
		return;

	pTx->Transfer();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_FILE_DATA(unsigned long netid, int guid, unsigned long offset, unsigned long crc, unsigned long datasize, void* data)
{
	NetBridgeFileReceiver* pRx = GetReceiver(guid);

	if (pRx == NULL)
		return;

	pRx->HandleFile(offset, crc, datasize, data);

	if (pRx->CrcError)
	{
		S_PG_RXtoTX_CRC_ERROR(netid, pRx->PeerGUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_RXtoTX_CRC_ERROR(unsigned long netid, int guid)
{
	NetBridgeFileSender* pTx = GetSender(guid);

	if (pTx == NULL)
		return;

	if (pTx->Status != EM_FT_StatusCompleted)
	{
		S_PG_TXtoRX_ABORT(netid, pTx->PeerGUID);
		pTx->Abort();

		RecycleFileTransfer(pTx->GUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_END_FILE(unsigned long netid, int guid, FILETIME* pftCreateTime, FILETIME* pftLastWriteTime)
{
	NetBridgeFileReceiver* pRx = GetReceiver(guid);

	if (pRx == NULL)
		return;

	pRx->EndFile(pftCreateTime, pftLastWriteTime);
	S_PG_RXtoTX_END_FILE(netid, pRx->PeerGUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_RXtoTX_END_FILE(unsigned long netid, int guid)
{
	NetBridgeFileSender* pTx = GetSender(guid);

	if (pTx == NULL)
		return;

	if (pTx->BeginFile())
	{
		S_PG_TXtoRX_BEGIN_FILE(netid, pTx->PeerGUID, pTx->CurrentTask.GUID, pTx->CurrentTask.LocalFileName.c_str(), pTx->CurrentTask.PeerFileName.c_str(), pTx->FileSize);
	}
	else
	{
		pTx->Complete();

		S_PG_TXtoRX_COMPLETED(netid, pTx->PeerGUID);

		RecycleFileTransfer(pTx->GUID);
	}
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_COMPLETED(unsigned long netid, int guid)
{
	NetBridgeFileReceiver* pRx = GetReceiver(guid);

	if (pRx == NULL)
		return;

	pRx->Complete();

	RecycleFileTransfer(pRx->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::On_PG_TXtoRX_ABORT(unsigned long netid, int guid)
{
	NetBridgeFileReceiver* pRx = GetReceiver(guid);

	if (pRx == NULL)
		return;

	pRx->Abort();

	RecycleFileTransfer(pRx->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_NOTIFY(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_NOTIFY* pPacket = (PG_TXtoRX_NOTIFY*)pg;
	On_PG_TXtoRX_NOTIFY(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_RXtoTX_READY(unsigned long netid, unsigned long size, void* pg)
{
	PG_RXtoTX_READY* pPacket = (PG_RXtoTX_READY*)pg;
	On_PG_RXtoTX_READY(netid, pPacket->GUID, pPacket->PeerGUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_BEGIN_FILE(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_BEGIN_FILE* pPacket = (PG_TXtoRX_BEGIN_FILE*)pg;
	On_PG_TXtoRX_BEGIN_FILE(netid, pPacket->GUID, pPacket->FileGUID, pPacket->LocalFileName.Begin(), pPacket->PeerFileName.Begin(), pPacket->FileSize);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_RXtoTX_BEGIN_FILE(unsigned long netid, unsigned long size, void* pg)
{
	PG_RXtoTX_BEGIN_FILE* pPacket = (PG_RXtoTX_BEGIN_FILE*)pg;
	On_PG_RXtoTX_BEGIN_FILE(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_FILE_DATA(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_FILE_DATA* pPacket = (PG_TXtoRX_FILE_DATA*)pg;
	PBYTE pTraveler = (PBYTE)pg;
	pTraveler += sizeof(PG_TXtoRX_FILE_DATA);
	On_PG_TXtoRX_FILE_DATA(netid, pPacket->GUID, pPacket->Offset, pPacket->CRC, pPacket->DataSize, pTraveler);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_RXtoTX_CRC_ERROR(unsigned long netid, unsigned long size, void* pg)
{
	PG_RXtoTX_CRC_ERROR* pPacket = (PG_RXtoTX_CRC_ERROR*)pg;
	On_PG_RXtoTX_CRC_ERROR(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_END_FILE(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_END_FILE* pPacket = (PG_TXtoRX_END_FILE*)pg;
	On_PG_TXtoRX_END_FILE(netid, pPacket->GUID, &(pPacket->CreateTime), &(pPacket->LastWriteTime));
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_RXtoTX_END_FILE(unsigned long netid, unsigned long size, void* pg)
{
	PG_RXtoTX_END_FILE* pPacket = (PG_RXtoTX_END_FILE*)pg;
	On_PG_RXtoTX_END_FILE(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_COMPLETED(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_COMPLETED* pPacket = (PG_TXtoRX_COMPLETED*)pg;
	On_PG_TXtoRX_COMPLETED(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void NetBridgeFileTransferManager::_PG_TXtoRX_ABORT(unsigned long netid, unsigned long size, void* pg)
{
	PG_TXtoRX_ABORT* pPacket = (PG_TXtoRX_ABORT*)pg;
	On_PG_TXtoRX_ABORT(netid, pPacket->GUID);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool NetBridgeFileTransferManager::Recv(unsigned long netid, unsigned long size, void* pg)
{
	bool Result = false;

	if (pg != NULL)
	{
		FTM_PG_BASE *pPkt = reinterpret_cast<FTM_PG_BASE *>(pg);

		PFUNC_FTM_PG pFunc = m_PGCallBack[pPkt->Type];

		if (pFunc != NULL)
		{
			pFunc(netid, size, pg);
			Result = true;
		}
	}

	return Result;
}

#pragma managed(pop)