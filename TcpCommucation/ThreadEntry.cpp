#include "stdafx.h"
#include "ThreadEntry.h"
#include "Thread.h"

namespace tc
{
	CThreadEntry::CThreadEntry() :
		m_bExist(false),
		m_bRun(false),
		m_nSleepMillSecond(0)
	{
		m_pThread = new CThread(this);
	}

	CThreadEntry::~CThreadEntry()
	{
		if (m_pThread)
		{
			delete m_pThread;
		}
	}

	void CThreadEntry::OnThreadExecute()
	{

	}

	void CThreadEntry::OnThreadCmp()
	{

	}

	bool CThreadEntry::IsCanExit()
	{
		return m_bExist;
	}

	void CThreadEntry::Sleep()
	{
		if (m_nSleepMillSecond > 0)
		{
			::Sleep(m_nSleepMillSecond);
		}
	}

	void CThreadEntry::SetSleepTime(int millsecond)
	{
		m_nSleepMillSecond = millsecond;
	}

	void CThreadEntry::Run()
	{
		if (!m_bRun)
		{
			m_pThread->Run();
		}
	}

	void CThreadEntry::Exit()
	{
		m_bExist = true;
	}
}