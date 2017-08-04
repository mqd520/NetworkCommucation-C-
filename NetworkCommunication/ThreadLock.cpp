#include "stdafx.h"
#include "ThreadLock.h"

namespace NetworkCommunication
{
	CThreadLock::CThreadLock()
	{
		InitializeCriticalSection(&m_crSection);
	}

	CThreadLock::~CThreadLock()
	{
		DeleteCriticalSection(&m_crSection);
	}

	void CThreadLock::Lock()
	{
		EnterCriticalSection(&m_crSection);
	}

	void CThreadLock::Unlock()
	{
		LeaveCriticalSection(&m_crSection);
	}
}