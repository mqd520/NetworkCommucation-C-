#include "stdafx.h"
#include "Timer.h"
#include "TimerAppMgr.h"

namespace NetworkCommunication
{
	CTimer::CTimer(int millsecond, LPTimeoutCallback lpfn, int count/* = 0*/)
		:m_nTimeout(millsecond),
		m_lpfn(lpfn),
		m_nCount(count),
		m_bRunning(false),
		m_nTimeouted(0),
		m_nCounted(0)
	{
		CTimerAppMgr::GetTimerMgr()->Add(this);
	}

	CTimer::~CTimer()
	{

	}

	void CTimer::Run(bool clear)
	{
		m_bRunning = true;
		if (clear)
		{
			m_nTimeouted = 0;
		}
	}

	void CTimer::Pause()
	{
		m_bRunning = false;
	}

	bool CTimer::IsRun()
	{
		return m_bRunning;
	}

	void CTimer::OnTimeout(int millsecond)
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

	int CTimer::Count()
	{
		return m_nCounted;
	}
}