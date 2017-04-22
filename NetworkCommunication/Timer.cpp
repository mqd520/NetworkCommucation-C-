#include "stdafx.h"
#include "Timer.h"
#include <time.h>

namespace NetworkCommunication
{
	//超时线程入口
	DWORD WINAPI Timeout(LPVOID lpParam);

	CTimer::CTimer(int timeout) :
		m_nTimeout(timeout),
		m_hThread(0),
		m_nStartTime(0),
		m_bRunning(false),
		m_lpfnOnTimeout(NULL),
		m_bTimeout(false)
	{
		m_hThread = ::CreateThread(NULL, 0, NetworkCommunication::Timeout, this, CREATE_SUSPENDED, NULL);
	}

	CTimer::~CTimer()
	{
		::TerminateThread(m_hThread, 0);
		::CloseHandle(m_hThread);
	}

	DWORD WINAPI Timeout(LPVOID lpParam)
	{
		CTimer* p = (CTimer*)lpParam;
		p->Timeout();
		return 0;
	}

	void CTimer::Timeout()
	{
		int timeout = m_nTimeout;//休眠时间
		while (true)
		{
			::Sleep(timeout);//sleep指定休眠时间后可能被挂起,等到再恢复后,休眠时间可能低于timeout
			time_t actual = time(NULL) - m_nStartTime;//实际休眠的时间
			time_t remain = timeout - actual * 1000;//需要休眠的剩余时间
			if (remain > 0)
			{
				timeout = (int)remain;
			}
			else
			{
				timeout = m_nTimeout;
				OnTimeout();
			}
		}
	}

	void CTimer::Start()
	{
		if (!m_bRunning)
		{
			m_bTimeout = false;
			m_nStartTime = time(NULL);
			m_bRunning = true;
			::ResumeThread(m_hThread);
		}
	}

	void CTimer::SetCallback(LPOnTimeout lpfnOnTimeout)
	{
		m_lpfnOnTimeout = lpfnOnTimeout;
	}

	void CTimer::OnTimeout()
	{
		m_bTimeout = true;
		m_bRunning = false;
		if (m_lpfnOnTimeout != NULL)
		{
			if (m_lpfnOnTimeout())
			{
				//继续计时
				Start();
			}
			else
			{
				::SuspendThread(m_hThread);
			}
		}
		else
		{
			::SuspendThread(m_hThread);
		}
	}

	void CTimer::Stop()
	{
		m_bTimeout = false;
		m_bRunning = false;
		::SuspendThread(m_hThread);
	}

	bool CTimer::IsTimeoutCmp()
	{
		return m_bTimeout;
	}
}
