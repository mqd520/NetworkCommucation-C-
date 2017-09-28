#include "stdafx.h"
#include "Thread.h"

namespace NetworkCommunication
{
	CThread::CThread(CThreadEntry* pEntry) :
		m_pEntry(pEntry)
	{
		
	}

	CThread::~CThread()
	{

	}

	unsigned WINAPI  CThread::Run(LPVOID lParam)
	{
		CThread* pThread = (CThread*)lParam;
		if (pThread == NULL)
		{
			return 0;
		}
		pThread->Execute();
		pThread->Free();
		::_endthreadex(0);
		return 0;
	}

	bool CThread::Run()
	{
		HANDLE hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, NULL);
		if (hThread)
		{
			::CloseHandle(hThread);
		}
		return (hThread != 0);
	}

	void CThread::Wait(int millsecond)
	{
		if (millsecond == 0)
		{
			//m_evtReady.Wait();
		}
		else
		{
			Sleep(millsecond);
		}
	}

	int CThread::Execute()
	{
		//m_evtReady.Active();
		//m_evtGiven.Wait();
		while (true)
		{
			m_pEntry->OnThreadRun();
		}
		return 0;
	}

	void CThread::Free()
	{
		//CNetworkCommuMgr::GetThreadMgr()->AddRecycleThread(this);
	}
}