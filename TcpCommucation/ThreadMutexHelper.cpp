#include "stdafx.h"
#include "ThreadMutexHelper.h"

namespace NetworkCommunication
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