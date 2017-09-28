#include "stdafx.h"
#include "ThreadEntry.h"
#include "Thread.h"

namespace NetworkCommunication
{
	CThreadEntry::CThreadEntry()
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

	void CThreadEntry::OnThreadRun()
	{

	}

	void CThreadEntry::Run()
	{
		m_pThread->Run();
	}
}