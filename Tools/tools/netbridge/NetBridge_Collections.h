#ifndef _NETBRIDGE_COLLECTIONS_H_
#define _NETBRIDGE_COLLECTIONS_H_

// ************************************************************************************************************************************************************

template <class DataType>
class CNetArrayList
{
protected:
	DataType*					m_data;
	int							m_numEntries;
	int							m_numEntriesAllocated;
	int							m_lastIndex;

public:
								CNetArrayList(int allocationSize = 128);
								CNetArrayList(const CNetArrayList<DataType> &srcList);
								~CNetArrayList();

	void						Release();

	bool						SetArraySize(int arraySize);
	bool						SetNumEntries(int numEntries);

	bool						Add(const DataType &entry);
	bool						Insert(int index, DataType entry);
	bool						ReplaceAt(int index, DataType entry);
	void						Remove(const DataType &entryData);
	void						RemoveAt(int entry);
	DataType&					Get(int entry);
	inline int					Count() const { return m_numEntries; }
	bool						Contains(const DataType &entryData) const;

	int							GetIndex(const DataType &entryData) const;
	int							IndexOf(const DataType &entryData) const;

	inline void					Clear() { m_numEntries = 0; }
	inline DataType*			GetArray() { return m_data; }
	inline const DataType*		GetArray() const { return m_data; }
	void						CloneFrom(const CNetArrayList<DataType> &srcList);

	inline DataType&			operator[](int index);
	inline const DataType&		operator[](int index) const;
};

// ************************************************************************************************************************************************************

template <class DataType>
class CNetQueue
{
private:
	DataType*				m_queue;								// Queue
	int						m_queueSize;							// Actual size of the allocated queue
	int						m_itemCount;							// Number of entries on the queue
	int						m_queueHead;							// Index of the first item on the queue
	int						m_queueTail;							// Index of the last item on the queue

public:
							CNetQueue(int initialQueueSize = 128);
							~CNetQueue();

	// Queue operations
	bool					Queue(DataType entry);
	DataType				Dequeue();								// Dequeues the head, treating the queue as a FIFO queue
	DataType				DequeueTail();							// Dequeues the tail, treating the queue as a LIFO queue
	bool					RequeueHead();							// Re-queues the head of the queue to the tail

	DataType				Front();

	BOOL					MergeAtEnd(CNetQueue<DataType> &queue);	// Merges the specified queue into this one at the end

	inline bool				IsEmpty() const { return (m_itemCount == 0) ? TRUE : FALSE; }
	
	inline int				Count() const { return m_itemCount; }
	inline int				size()	const { return m_itemCount; }	

	void					Clear();
	void					clear() { Clear(); }

private:
	void					ResizeQueue(INT32 newQueueSize = 0);
};

// ************************************************************************************************************************************************************

/*
--------------------------------------------------------------------
CNetArrayList

Beginning of function definition for templatized CNetArrayList

--------------------------------------------------------------------
*/

template <class DataType>
CNetArrayList<DataType>::CNetArrayList(int allocationSize)
{
	if(allocationSize == 0)
		m_data = NULL;
	else
		m_data = new DataType [allocationSize];
	m_numEntries = 0;
	m_numEntriesAllocated = allocationSize;
	m_lastIndex = m_numEntriesAllocated - 1;
}

template <class DataType>
CNetArrayList<DataType>::CNetArrayList(const CNetArrayList<DataType> &srcList)
{
	m_data = NULL;
	m_numEntries = 0;
	m_numEntriesAllocated = 0;
	m_lastIndex = -1;

	CloneFrom(srcList);
}

template <class DataType>
CNetArrayList<DataType>::~CNetArrayList()
{
	if(m_data != NULL)
		delete[] m_data;
}

template <class DataType>
void CNetArrayList<DataType>::Release()
{
	if(m_data != NULL)
		delete[] m_data;
	m_data = NULL;
	m_numEntries = 0;
	m_numEntriesAllocated = 0;
}

template <class DataType>
bool CNetArrayList<DataType>::SetArraySize(int arraySize)
{
	// If array size is zero, force delete of the data array
	if(arraySize == 0)
	{
		delete[] m_data;

		m_data = NULL;
		m_numEntries = 0;
		m_numEntriesAllocated = 0;
		m_lastIndex = -1;

		return TRUE;
	}

	// If array size is smaller than or equal to the number of entries, abort
	if(arraySize <= m_numEntries)
	{
		return FALSE;
	}

	DataType *dataNew;
	dataNew = new DataType [arraySize];

	if(dataNew == NULL)
		return FALSE;

	if(m_data != NULL)
	{
		memcpy(dataNew, m_data, m_numEntries * sizeof(DataType));
		delete[] m_data;
	}

	m_data = dataNew;
	m_numEntriesAllocated = arraySize;
	m_lastIndex = m_numEntriesAllocated - 1;

	return TRUE;
}

template <class DataType>
bool CNetArrayList<DataType>::SetNumEntries(int numEntries)
{
	if(m_numEntriesAllocated < numEntries && SetArraySize(numEntries) == FALSE)
	{
		return FALSE;
	}

	m_numEntries = numEntries;

	return TRUE;
}

template <class DataType>
bool CNetArrayList<DataType>::Add(const DataType &entry)
{
	if(m_data == NULL || m_numEntries >= m_lastIndex)
	{
		DataType *dataNew;
		int numEntriesAllocatedNew;
		if(m_numEntriesAllocated == 0)
			numEntriesAllocatedNew = 16;
		else
			numEntriesAllocatedNew = m_numEntriesAllocated * 2;
		dataNew = new DataType [numEntriesAllocatedNew];
		if(dataNew == NULL)
			return FALSE;
		if(m_data != NULL)
		{
			memcpy(dataNew, m_data, m_numEntries * sizeof(DataType));
			delete[] m_data;
		}
		m_data = dataNew;
		m_numEntriesAllocated = numEntriesAllocatedNew;
		m_lastIndex = m_numEntriesAllocated - 1;
	}

	m_data[m_numEntries] = entry;
	++m_numEntries;

	return TRUE;
}

template <class DataType>
bool CNetArrayList<DataType>::Insert(int index, DataType entry)
{
	if(m_data == NULL || m_numEntries + 1 > m_numEntriesAllocated)
	{
		DataType *dataNew;
		int numEntriesAllocatedNew;
		if(m_numEntriesAllocated == 0)
			numEntriesAllocatedNew = 16;
		else
			numEntriesAllocatedNew = m_numEntriesAllocated * 2;
		dataNew = new DataType [numEntriesAllocatedNew];
		if(dataNew == NULL)
			return FALSE;
		if(m_data != NULL)
		{
			memcpy(dataNew, m_data, m_numEntries * sizeof(DataType));
			delete[] m_data;
		}
		m_data = dataNew;
		m_numEntriesAllocated = numEntriesAllocatedNew;
	}

	if(index > m_numEntries)
		index = m_numEntries;

	int entriesToMove = m_numEntries - index;
	if(entriesToMove > 0)
		memmove(&m_data[index + 1], &m_data[index], entriesToMove * sizeof(DataType));

	m_data[index] = entry;
	m_numEntries++;

	return TRUE;
}

template <class DataType>
bool CNetArrayList<DataType>::ReplaceAt(int index, DataType entry)
{
	if(index < 0 || index >= m_numEntries)
		return FALSE;

	m_data[index] = entry;

	return TRUE;
}

template <class DataType>
void CNetArrayList<DataType>::Remove(const DataType &entryData)
{
	for(int index = 0; index < m_numEntries; index++)
	{
		if(m_data[index] == entryData)
		{
			RemoveAt(index);
			return;
		}
	}
}

template <class DataType>
void CNetArrayList<DataType>::RemoveAt(int entry)
{
	// Decrement count
	m_numEntries--;

	// Collapse the array
	if(m_numEntries - entry > 0)
	{
		memmove(&m_data[entry], &m_data[entry + 1], (m_numEntries - entry) * sizeof(DataType));
	}
}

template <class DataType>
DataType &CNetArrayList<DataType>::Get(int entry)
{
	return m_data[entry];
}

template <class DataType>
bool CNetArrayList<DataType>::Contains(const DataType &entryData) const
{
	for(int entry = 0; entry < m_numEntries; entry++)
	{
		if(m_data[entry] == entryData)
			return TRUE;
	}

	return FALSE;
}

template <class DataType>
int CNetArrayList<DataType>::GetIndex(const DataType &entryData) const
{
	for(int entry = 0; entry < m_numEntries; entry++)
	{
		if(m_data[entry] == entryData)
			return entry;
	}

	return 0xFFFFFFFF;
}

template <class DataType>
int CNetArrayList<DataType>::IndexOf(const DataType &entryData) const
{
	for(int entry = 0; entry < m_numEntries; entry++)
	{
		if(m_data[entry] == entryData)
			return entry;
	}

	return 0xFFFFFFFF;
}

template <class DataType>
void CNetArrayList<DataType>::CloneFrom(const CNetArrayList<DataType> &srcList)
{
	if(m_numEntriesAllocated >= srcList.m_numEntriesAllocated)
	{
		m_numEntries = srcList.m_numEntries;
		memcpy(m_data, srcList.m_data, sizeof(DataType) * srcList.m_numEntries);
	}
	else
	{
		Release();
		m_data = new DataType [srcList.m_numEntries];
		m_numEntries = srcList.m_numEntries;
		m_numEntriesAllocated = srcList.m_numEntries;
		memcpy(m_data, srcList.m_data, sizeof(DataType) * srcList.m_numEntries);
	}
}

template <class DataType>
DataType &CNetArrayList<DataType>::operator[](int index)
{
	return m_data[index];
}

template <class DataType>
const DataType &CNetArrayList<DataType>::operator[](int index) const
{
	return m_data[index];
}

// ************************************************************************************************************************************************************

/*
--------------------------------------------------------------------
CNetQueue

Beginning of function definition for templatized CNetQueue

--------------------------------------------------------------------
*/

template <class DataType>
CNetQueue<DataType>::CNetQueue(int initialQueueSize)
: m_queue(NULL), m_queueSize(initialQueueSize), m_itemCount(0), m_queueHead(0), m_queueTail(0)
{
	// Prevent idiotic usages
	if(m_queueSize <= 1)
		m_queueSize = 2;

	//m_queue = new DataType [m_queueSize];
	m_queue = new DataType [m_queueSize];
}

template <class DataType>
CNetQueue<DataType>::~CNetQueue()
{
	delete[] m_queue;
}

template <class DataType>
bool CNetQueue<DataType>::Queue(DataType entry)
{
	if(m_itemCount == m_queueSize)
		ResizeQueue();

	// Insert item at tail
	m_queue[m_queueTail] = entry;
	m_itemCount++;

	// Advance tail
	m_queueTail++;
	if(m_queueTail == m_queueSize)
		m_queueTail = 0;

	return TRUE;
}

template <class DataType>
DataType CNetQueue<DataType>::Front()
{
	DataType &dequeuedEntry = m_queue[m_queueHead];
	return dequeuedEntry;
}


template <class DataType>
DataType CNetQueue<DataType>::Dequeue()
{
	DataType &dequeuedEntry = m_queue[m_queueHead];
	m_itemCount--;
	m_queueHead++;
	if(m_queueHead == m_queueSize)
		m_queueHead = 0;

	return dequeuedEntry;
}

template <class DataType>
DataType CNetQueue<DataType>::DequeueTail()
{
	// Determine the index to dequeue (subtract 1 from the queue tail, wrap around if necessary)
	int dequeuedIndex = m_queueTail - 1;
	if(dequeuedIndex < 0)
		dequeuedIndex = m_queueSize - 1;

	DataType &dequeuedEntry = m_queue[dequeuedIndex];
	m_itemCount--;

	m_queueTail = dequeuedIndex;

	return dequeuedEntry;
}

template <class DataType>
bool CNetQueue<DataType>::RequeueHead()
{
	if(m_itemCount > 1)
	{
		DataType &dequeuedEntry = m_queue[m_queueHead];

		// Advance queue head
		m_queueHead++;
		if(m_queueHead == m_queueSize)
			m_queueHead = 0;

		// Insert item at tail
		m_queue[m_queueTail] = dequeuedEntry;

		// Advance queue tail
		m_queueTail++;
		if(m_queueTail == m_queueSize)
			m_queueTail = 0;

		return TRUE;
	}

	return FALSE;
}

template <class DataType>
BOOL CNetQueue<DataType>::MergeAtEnd(CNetQueue<DataType> &srcQueue)
{
	INT32 mergedQueueSize = m_itemCount + srcQueue.Count();

	if(mergedQueueSize >= m_queueSize)
		ResizeQueue(mergedQueueSize * 2);

	if(srcQueue.m_itemCount > 0)
	{
		INT32 copyCount = 0;

		INT32 dstBlock0Head = m_queueTail;
		INT32 dstBlock0Size = (m_queueTail > m_queueHead || m_itemCount == 0) ? m_queueSize - m_queueTail : m_queueHead - m_queueTail;
		INT32 dstBlock1Head = 0;
		INT32 dstBlock1Size = (m_queueTail > m_queueHead || m_itemCount == 0) ? m_queueHead : 0;

		INT32 srcBlock0Head = srcQueue.m_queueHead;
		INT32 srcBlock0Size = (srcQueue.m_queueTail > srcQueue.m_queueHead || srcQueue.m_itemCount == 0) ? (srcQueue.m_queueTail - srcQueue.m_queueHead) : (srcQueue.m_queueSize - srcQueue.m_queueHead);
		INT32 srcBlock1Head = 0;
		INT32 srcBlock1Size = (srcQueue.m_queueTail > srcQueue.m_queueHead || srcQueue.m_itemCount == 0) ? 0 : srcQueue.m_queueTail;

		// Copy as much of source block 0 into destination block 0 as possible
		copyCount = min(dstBlock0Size, srcBlock0Size);
		memcpy(&m_queue[dstBlock0Head], &srcQueue.m_queue[srcBlock0Head], sizeof(DataType) * copyCount);

		dstBlock0Head += copyCount;
		dstBlock0Size -= copyCount;

		srcBlock0Head += copyCount;
		srcBlock0Size -= copyCount;

		// More of source block 0 remain -- destination block 1 must be able to fit all of the remaining data
		if(srcBlock0Size > 0)
		{
			// Copy remainder of source block 0 into destination block 1
			copyCount = srcBlock0Size;
			memcpy(&m_queue[dstBlock1Head], &srcQueue.m_queue[srcBlock0Head], sizeof(DataType) * copyCount);

			dstBlock1Head += copyCount;
			dstBlock1Size -= copyCount;

			srcBlock0Head += copyCount;
			srcBlock0Size -= copyCount;

			// Copy all of source block 1 into destination block 1
			memcpy(&m_queue[dstBlock1Head], &srcQueue.m_queue[srcBlock1Head], sizeof(DataType) * srcBlock1Size);
		}
		// No more of source block 0 remain
		else
		{
			// Copy as much of source block 1 into destination block 0 as possible
			copyCount = min(dstBlock0Size, srcBlock1Size);
			memcpy(&m_queue[dstBlock0Head], &srcQueue.m_queue[srcBlock1Head], sizeof(DataType) * copyCount);

			dstBlock0Head += copyCount;
			dstBlock0Size -= copyCount;

			srcBlock1Head += copyCount;
			srcBlock1Size -= copyCount;

			if(srcBlock1Size > 0)
			{
				// Copy remainder of source block 1 into destination block 1
				memcpy(&m_queue[dstBlock1Head], &srcQueue.m_queue[srcBlock1Head], sizeof(DataType) * srcBlock1Size);
			}
		}

		// Store new item count
		m_itemCount = mergedQueueSize;

		// Update queue tail
		m_queueTail = (m_queueTail + srcQueue.Count()) % m_queueSize;
	}

	return TRUE;
}

template <class DataType>
void CNetQueue<DataType>::Clear()
{
	m_itemCount = 0;
	m_queueHead = 0;
	m_queueTail = 0;
}

template <class DataType>
void CNetQueue<DataType>::ResizeQueue(INT32 newQueueSize)
{
	// If specified queue size is zero, simply double the current queue size
	newQueueSize = (newQueueSize <= 0) ? m_queueSize * 2 : newQueueSize;

	// Allocate new array for the queue
	DataType *newQueue = new DataType [newQueueSize];

	// Copy old data over to the new array
	if(m_itemCount > 0)
	{
		if(m_queueHead < m_queueTail)
		{
			// Queue is in one segment, so perform a copy directly
			memcpy(newQueue, &m_queue[m_queueHead], sizeof(DataType) * m_itemCount);
		}
		else
		{
			// Copy from queue head to end of queue array
			memcpy(newQueue, &m_queue[m_queueHead], sizeof(DataType) * (m_queueSize - m_queueHead));

			// Copy from beginning of queue array to queue tail - 1
			if(m_queueTail > 0)
				memcpy(&newQueue[m_queueSize - m_queueHead], m_queue, sizeof(DataType) * m_queueTail);
		}

		m_queueHead = 0;
		m_queueTail = m_itemCount;
	}

	// Delete old queue array and assign new queue array to it
	delete[] m_queue;
	m_queue = newQueue;
	m_queueSize = newQueueSize;
}

// ************************************************************************************************************************************************************

#endif
