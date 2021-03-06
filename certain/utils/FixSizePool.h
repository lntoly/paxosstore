#ifndef CERTAIN_UTILS_FIXSIZEPOLL_H_
#define CERTAIN_UTILS_FIXSIZEPOLL_H_

#include "utils/Logger.h"

namespace Certain
{

class clsFixSizePool
{
	public:
		clsFixSizePool(int iItemCnt, int iItemSize);
		~clsFixSizePool();
		char * Alloc(int iItemSize, bool bLock);
		void Free(char * pItem, bool bLock);

		int GetAllocCnt(){return m_iAllocCnt;}
		int GetItemCnt(){ return m_iItemCnt;}

		//for test
		char * GetBegin(){return  m_pItem;}
		char * GetEnd(){return  m_pItem + (unsigned long long)m_iItemSize * m_iItemCnt;}

		void PrintStat();

		void StartPrintStatWorker();
		static void * PrintStatWork(void * args);

	private:

		int * GetNext(int iIndex)
		{
			return (int*)(m_pItem + iIndex * (unsigned long long)m_iItemSize); 
		}

	private:
		struct PoolStat
		{
			int item_cnt;
			int item_size;
			uint64_t pool_alloc_cnt;
			uint64_t pool_alloc_size;
			uint64_t os_alloc_cnt;
			uint64_t os_alloc_size;
		};
		
	private:
		PoolStat _stat;
		int m_iItemCnt;
		int m_iItemSize;
		char * m_pItem;
		volatile int m_iHead;
		volatile int m_iAllocCnt;
		pthread_mutex_t m_tMutex;
};

}

#endif
