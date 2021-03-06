#include "stdafx.h"
#include "Include/tc/ThreadMutexHelper.h"

namespace tc
{
	CThreadMutexHelper::CThreadMutexHelper(CThreadMutex& mutex) :m_Mutex(mutex)
	{
		m_Mutex.RetrieveOwner();
	}

	CThreadMutexHelper::~CThreadMutexHelper()
	{
		m_Mutex.Release();
	}
}