#include "stdafx.h"
#include "TimeoutMgr.h"
#include "TimerAppMgr.h"

namespace NetworkCommunication
{
	CTimeoutMgr::CTimeoutMgr()
	{

	}

	CTimeoutMgr::~CTimeoutMgr()
	{

	}

	void CTimeoutMgr::Add(int millsecond)
	{
		m_lock1.Lock();
		m_quTimeout.push(millsecond);
		m_lock1.Unlock();
	}

	void CTimeoutMgr::ProcessTimeout()
	{
		while (CTimerAppMgr::CanExit() == false && m_quTimeout.size() > 0)
		{
			int millsecond = m_quTimeout.front();

			m_lock1.Lock();
			m_quTimeout.pop();
			m_lock1.Unlock();

			CTimerAppMgr::GetTimerMgr()->OnTimeout(millsecond);
		}
	}
}