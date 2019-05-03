#include "stdafx.h"
#include "ThreadEvent.h"

namespace tc
{
	CThreadEvent::CThreadEvent(bool bManualReset /*= true*/, bool bInitialState /*= false*/)
	{
		m_hEvent = ::CreateEvent(NULL, bManualReset, bInitialState, NULL);
	}

	CThreadEvent::~CThreadEvent()
	{
		::CloseHandle(m_hEvent);
	}

	HANDLE CThreadEvent::GetEvent() const
	{
		return m_hEvent;
	}

	void CThreadEvent::Wait() const
	{
		Wait(INFINITE);
	}

	bool CThreadEvent::Wait(DWORD timeoutMillis) const
	{
		bool ok = true;
		DWORD result = ::WaitForSingleObject(m_hEvent, timeoutMillis);
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

	void CThreadEvent::Active()
	{
		::SetEvent(m_hEvent);
	}

	void CThreadEvent::Inactive()
	{
		::ResetEvent(m_hEvent);
	}
}