#include "stdafx.h"
#include "Timer.h"
#include <time.h>

namespace NetworkCommunication
{
	//��ʱ�߳����
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
		int timeout = m_nTimeout;//����ʱ��
		while (true)
		{
			::Sleep(timeout);//sleepָ������ʱ�����ܱ�����,�ȵ��ٻָ���,����ʱ����ܵ���timeout
			time_t actual = time(NULL) - m_nStartTime;//ʵ�����ߵ�ʱ��
			time_t remain = timeout - actual * 1000;//��Ҫ���ߵ�ʣ��ʱ��
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
				//������ʱ
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
