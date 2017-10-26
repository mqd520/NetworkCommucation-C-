#include "stdafx.h"
#include "Timeout.h"
#include "TimeoutMgr.h"

namespace NetworkCommunication
{
	CTimeout::CTimeout(int millsecond, LPTimeoutCallback lpfn, int count/* = 0*/)
		:m_nTimeout(millsecond),
		m_lpfn(lpfn),
		m_nCount(count),
		m_bRunning(false),
		m_nTimeouted(0),
		m_nCounted(0)
	{
		CTimeoutMgr::m_timeoutListMgr.Add(this);
	}

	CTimeout::~CTimeout()
	{

	}

	void CTimeout::Run(bool clear)
	{
		m_bRunning = true;
		if (clear)
		{
			m_nTimeouted = 0;
		}
	}

	void CTimeout::Pause()
	{
		m_bRunning = false;
	}

	bool CTimeout::IsRun()
	{
		return m_bRunning;
	}

	void CTimeout::OnTimeout(int millsecond)
	{
		if (m_bRunning && (m_nCount == 0 || m_nCounted < m_nCount))
		{
			m_nTimeouted += millsecond;

			m_nTimeouted = m_nTimeouted > m_nTimeout ? m_nTimeout : m_nTimeouted;

			if (m_nTimeouted == m_nTimeout)
			{
				m_nCounted++;
				m_nTimeouted = 0;
				m_lpfn(this, m_nCounted);
			}
		}
	}

	int CTimeout::Count()
	{
		return m_nCounted;
	}
}