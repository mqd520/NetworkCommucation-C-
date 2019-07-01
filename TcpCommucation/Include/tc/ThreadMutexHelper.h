#pragma once
#include "ThreadMutex.h"

namespace tc
{
	class CThreadMutexHelper
	{
	public:
		CThreadMutexHelper(CThreadMutex& mutex);
		~CThreadMutexHelper();

		CThreadMutex& m_Mutex;
	};
}