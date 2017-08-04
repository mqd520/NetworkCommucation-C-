#pragma once
#include "ThreadMutex.h"

namespace NetworkCommunication
{
	class CThreadMutexHelper
	{
	public:
		CThreadMutexHelper(CThreadMutex& mutex);
		~CThreadMutexHelper();

		CThreadMutex& m_Mutex;
	};
}