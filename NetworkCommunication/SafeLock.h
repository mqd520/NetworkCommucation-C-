#pragma once
#include "ThreadLock.h"

namespace NetworkCommunication
{
	class CSafeLock
	{
	private:
		CThreadLock* m_pLock;

	public:
		CSafeLock(CThreadLock* pLock);

		~CSafeLock();
	};
}