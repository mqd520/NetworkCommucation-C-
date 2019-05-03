#include "stdafx.h"
#include "ThreadMutex.h"

namespace tc
{
	CThreadMutex::CThreadMutex(BOOL bInitialOwner, LPCTSTR lpName)
	{
		m_hMutex = ::CreateMutex(
			NULL,              // default security attributes
			bInitialOwner,     // initially not owned
			lpName);           // named mutex
	}

	CThreadMutex::~CThreadMutex(void)
	{
		::CloseHandle(m_hMutex);
	}

	HANDLE CThreadMutex::GetHandle() const
	{
		return m_hMutex;
	}

	void CThreadMutex::RetrieveOwner() const
	{
		Wait(INFINITE);
	}

	bool CThreadMutex::Wait(DWORD timeoutMillis) const
	{
		bool ok = true;
		DWORD result = ::WaitForSingleObject(m_hMutex, timeoutMillis);
		if (result == WAIT_TIMEOUT)
		{
			ok = false;
		}
		else if (result == WAIT_OBJECT_0)
		{
			ok = true;
		}
		return ok;
	}

	void CThreadMutex::Release()
	{
		::ReleaseMutex(m_hMutex);
	}
}