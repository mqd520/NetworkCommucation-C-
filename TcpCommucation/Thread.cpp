#include "stdafx.h"
#include "Thread.h"

namespace NetworkCommunication
{
	CThread::CThread(CThreadEntry* pEntry) :
		m_pEntry(pEntry),
		m_hThread(0)
	{

	}

	CThread::~CThread()
	{

	}

	unsigned WINAPI  CThread::Run(LPVOID lParam)
	{
		CThread* pThread = (CThread*)lParam;

		pThread->Execute();
		pThread->ExecuteCmp();

		return 0;
	}

	void CThread::Run()
	{
		if (m_hThread == 0)
		{
			m_hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, NULL);
		}
	}

	void CThread::Wait(int millsecond)
	{
		if (millsecond == 0)
		{
			m_evtReady.Wait();
		}
		else
		{
			Sleep(millsecond);
		}
	}

	void CThread::Execute()
	{
		if (m_pEntry)
		{
			while (m_pEntry->IsCanExit() == false)
			{
				//执行具体业务
				m_pEntry->OnThreadExecute();

				//休眠一段时间
				m_pEntry->Sleep();
			}

			int n = 0;
			n++;
		}
	}

	void CThread::ExecuteCmp()
	{
		::CloseHandle(m_hThread);
		if (m_pEntry)
		{
			m_pEntry->OnThreadCmp();
		}
	}
}