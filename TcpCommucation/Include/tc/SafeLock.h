#pragma once
#include "ThreadLock.h"

namespace tc
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