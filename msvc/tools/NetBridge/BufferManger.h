#ifndef __CBUFFERMANGER_H__
#define __CBUFFERMANGER_H__

#include "NetBridge_Struct.h"
#include <Windows.h>
#include < map >

using namespace std;

#define BUFFERMANAGER_PREFIX_SIZE		16
#define BUFFERMANAGER_BASE_SIZE			512
#define BUFFERMANAGER_BASE_POOLCOUNT	12

class CBufferManger
{
public:
	CBufferManger(void)
	{
		// Initialize metrics
		m_iCountDelete = 0;
		m_iCountApply = 0;
		m_lastFlushTime = 0;

		// Initialize buffer pools
		m_bufferPoolCount = BUFFERMANAGER_BASE_POOLCOUNT;
		m_bufferPoolAllocSize = new int [m_bufferPoolCount];
		m_bufferPool = new CNetQueue<BYTE *> [m_bufferPoolCount];
		for(int i = 0, allocSize = BUFFERMANAGER_BASE_SIZE; i < m_bufferPoolCount; ++i, allocSize = allocSize << 1)
		{
			m_bufferPoolAllocSize[i] = allocSize;
		}
	}

	~CBufferManger(void)
	{
		// Release all buffer pools
		// TODO: Keep track of allocated buffers? And destroy them all here? Or just accept the memory leak to be safe?
		for(int i = 0; i < m_bufferPoolCount; ++i)
		{
			while(!m_bufferPool[i].IsEmpty())
			{
				delete[] m_bufferPool[i].Dequeue();
			}
		}

		delete[] m_bufferPoolAllocSize;
		delete[] m_bufferPool;
	}

	BYTE*	Apply	( DWORD dwSize	)
	{
		// Increment apply metric
		m_iCountApply++;

		DWORD sizeWithPrefix = dwSize + BUFFERMANAGER_PREFIX_SIZE;

		BYTE *pChunk = NULL;

		m_csBuffer.Enter( "CBufferManger::Apply" );
		{

			for(int i = 0; i < m_bufferPoolCount; ++i)
			{
				if(static_cast<DWORD>(m_bufferPoolAllocSize[i]) >= sizeWithPrefix)
				{
					if(m_bufferPool[i].IsEmpty())
					{
						//@ Memory leak
						// Allocate raw chunk with the pool's allocation size
						pChunk = new BYTE [m_bufferPoolAllocSize[i]];

						// Store pool index
						pChunk[0] = i;

						// Offset chunk address so it can be returned to caller
						pChunk = pChunk + BUFFERMANAGER_PREFIX_SIZE;
					}
					else
					{
						// Dequeue and offset chunk address so it can be returned to caller
						pChunk = m_bufferPool[i].Dequeue() + BUFFERMANAGER_PREFIX_SIZE;
					}

					break;
				}
			}


			/*
			int i = sizeWithPrefix / BUFFERMANAGER_BASE_SIZE;

			if(m_bufferPool[i].IsEmpty())
			{
			// Allocate raw chunk with the pool's allocation size
			pChunk = new BYTE [m_bufferPoolAllocSize[i]];

			// Store pool index
			pChunk[0] = i;

			// Offset chunk address so it can be returned to caller
			pChunk = pChunk + BUFFERMANAGER_PREFIX_SIZE;
			}
			else
			{
			// Dequeue and offset chunk address so it can be returned to caller
			pChunk = m_bufferPool[i].Dequeue() + BUFFERMANAGER_PREFIX_SIZE;
			}
			*/

		}
		m_csBuffer.Leave( "CBufferManger::Apply" );

		return pChunk;
	}

	void	Delete	( BYTE* pAddress )
	{
		// Increment delete metric
		m_iCountDelete++;

		// Offset chunk address so we can get the buffer prefix
		pAddress = pAddress - BUFFERMANAGER_PREFIX_SIZE;
		int poolIdx = pAddress[0];

		m_csBuffer.Enter( "CBufferManger::Delete" );
		{
			// Push chunk into buffer pool for later reuse
			m_bufferPool[poolIdx].Queue(pAddress);
		}
		m_csBuffer.Leave( "CBufferManger::Delete" );
	}

	void	Flush()
	{
		DWORD timeSinceLastFlush = GetTickCount() - m_lastFlushTime;

		if(timeSinceLastFlush > 5000)
		{
			m_csBuffer.Enter( "CBufferManger::Flush" );
			{
				m_lastFlushTime = GetTickCount();

				for(int i = 0; i < m_bufferPoolCount; ++i)
				{
					int targetPoolSize = max(m_bufferPool[i].Count() * 8 / 10, 16);

					while(m_bufferPool[i].Count() > targetPoolSize)
					{
						delete[] m_bufferPool[i].Dequeue();
					}
				}
			}
			m_csBuffer.Leave( "CBufferManger::Flush" );
		}
	}

protected:
	int							m_iCountDelete;
	int							m_iCountApply;
	DWORD						m_lastFlushTime;
	CCritcalsection				m_csBuffer;

	int							m_bufferPoolCount;
	int*						m_bufferPoolAllocSize;
	CNetQueue<BYTE *>*			m_bufferPool;
};

#endif
