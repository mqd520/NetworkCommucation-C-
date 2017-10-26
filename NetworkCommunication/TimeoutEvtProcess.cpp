#include "stdafx.h"
#include "TimeoutEvtProcess.h"
#include "TimeoutMgr.h"

namespace NetworkCommunication
{
	CTimeoutEvtProcess::CTimeoutEvtProcess()
	{

	}

	CTimeoutEvtProcess::~CTimeoutEvtProcess()
	{

	}

	void CTimeoutEvtProcess::AddTimeoutEvt(int millsecond)
	{
		m_lock1.Lock();
		m_quTimeout.push(millsecond);
		m_lock1.Unlock();
	}

	void CTimeoutEvtProcess::ProcessTimeoutEvt()
	{
		while (m_quTimeout.size() > 0)
		{
			int millsecond = m_quTimeout.front();

			m_lock1.Lock();
			m_quTimeout.pop();
			m_lock1.Unlock();

			CTimeoutMgr::m_timeoutListMgr.OnTimeout(millsecond);
		}
	}
}