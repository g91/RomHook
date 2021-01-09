//-----------------------------------------------------------------------------------
// Attention: This class only can be used in one thread read, one thread write ........
// 可更動定義說明：
//		FIFO_NUM_PER_BLOCK: 定義每一個 dynamic 的 alloc block 的大小，越小每次
//-----------------------------------------------------------------------------------
#ifndef _THREADFREEFIFO_H
#define _THREADFREEFIFO_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "LTestValid.h"

#ifndef FIFO_NUM_PER_BLOCK
	#define FIFO_NUM_PER_BLOCK 10
#endif

const int NUM_PER_BLOCK = FIFO_NUM_PER_BLOCK;

template <class T >
class ThreadFreeFIFO : TEST_VALID
{
private:
	
	int m_uEleCount;
	
	struct ElementBlock{
		T Element[NUM_PER_BLOCK];
		ElementBlock* pNext;
	};
	
	struct {
		int uIndex;
		ElementBlock* pBlock;
	} currRead, currWrite;
	
public:
		
		ThreadFreeFIFO()
		{
			m_uEleCount = 0;
			currRead.uIndex = 0;
			currRead.pBlock = new ElementBlock;
			ASSERT( currRead.pBlock );
			currRead.pBlock->pNext = NULL;
			currWrite.uIndex = 0;
			currWrite.pBlock = currRead.pBlock;
			
		}
		
		~ThreadFreeFIFO()
		{
			ASSERT_VALID( this );
			// error occured if app forget to release them
			// bcz element shouldn't be left there
			ASSERT( m_uEleCount == 0 );
			
			delete currRead.pBlock;
		}

		void Write( T Element )
		{
			ASSERT_VALID( this );
			// store app message
			currWrite.pBlock->Element[currWrite.uIndex] = Element;
			
			// if exceed the boundary, allocate a new block.........
			if( ++currWrite.uIndex >= NUM_PER_BLOCK) {
				currWrite.pBlock->pNext = new ElementBlock;
				ASSERT( currWrite.pBlock->pNext );
				
				currWrite.pBlock = currWrite.pBlock->pNext;
				currWrite.pBlock->pNext = NULL;
				currWrite.uIndex = 0;
			}
			
			m_uEleCount++;
		}
		
		bool IsEmpty(void)
		{
			ASSERT_VALID( this );
			return (m_uEleCount <= 0);
		}
		int Size(void) {

			ASSERT_VALID( this );
			return m_uEleCount;
		}

		bool Read(T& Element)
		{
			ASSERT_VALID( this );
			// no message
			if( m_uEleCount <= 0 ) return false;
			
			// set return value
			Element = currRead.pBlock->Element[currRead.uIndex];
			
			// if read till the end of block, free it
			if( ++currRead.uIndex >= NUM_PER_BLOCK ) {
				// bcz write at least have one block, so we can ignore it
				ElementBlock* temp;
				
				temp = currRead.pBlock->pNext;
				ASSERT( temp != NULL );
				delete currRead.pBlock;
				
				currRead.pBlock = temp;
				currRead.uIndex = 0;
			}
			
			m_uEleCount--;
			return true;
		}

#ifdef _DEBUG
	virtual bool IsValid(void)
	{
		return (
			TestValid::IsValid() &&
			this != NULL &&
			currRead.pBlock != NULL &&
			currWrite.pBlock != NULL
			);
	}
#endif

};

#endif //_THREADFREEFIFO_H