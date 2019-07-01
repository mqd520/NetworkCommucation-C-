#include "stdafx.h"
#include "Include/tc/ThreadSemaphore.h"

namespace tc
{
	CThreadSemaphore::CThreadSemaphore(LONG lInitialCount, LONG lMaximumCount /*= 4096*/, LPCTSTR lpName /*= NULL*/)
	{
		m_hSemaphore = ::CreateSemaphore(NULL, lInitialCount, lMaximumCount, lpName);
	}

	CThreadSemaphore::~CThreadSemaphore()
	{
		if (m_hSemaphore)
		{
			::CloseHandle(m_hSemaphore);
		}
	}

	void CThreadSemaphore::Down() const
	{
		::WaitForSingleObject(m_hSemaphore, INFINITE);
	}

	void CThreadSemaphore::Up() const
	{
		::ReleaseSemaphore(m_hSemaphore, 1, NULL);
	}
}