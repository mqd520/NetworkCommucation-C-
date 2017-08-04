#pragma once

#include "ThreadEvent.h"
#include <process.h>

typedef void (*LPThreadStart)();

namespace NetworkCommunication
{
	class CThread
	{
	private:
		CThreadEvent m_evtReady;
		CThreadEvent m_evtGiven;
		LPThreadStart m_lpfnThreadStart;
		//T* m_pInstance;//回调函数指针所属成员对象
		//ThreadStart m_lpfnThreadStart;//回调函数指针

	private:
		static unsigned WINAPI  Run(LPVOID lParam)
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

	public:
		CThread(){};
		~CThread(){};

		void SetCallback(LPThreadStart lpfn)
		{
			m_lpfnThreadStart = lpfn;
		}

		//void SetCallback(ThreadStart start, T* instance)
		//{
		//	m_lpfnThreadStart = start;
		//	m_pInstance = instance;
		//}

		bool Start()
		{
			HANDLE hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, NULL);
			if (hThread)
			{
				::CloseHandle(hThread);
			}
			return (hThread != 0);
		}

		void Wait()
		{
			m_evtReady.Wait();
		}

		int Execute()
		{
			//m_evtReady.Active();
			//m_evtGiven.Wait();
			if (m_lpfnThreadStart)
			{
				m_lpfnThreadStart();
			}
			return 0;
		}

		void Free()
		{
			//CNetworkCommuMgr::GetThreadMgr()->AddRecycleThread(this);
		}
	};

	//template<typename T>
	//void CThread::SetCallback(ThreadStart start, T* instance)
	//{
	//	m_lpfnThreadStart = start;
	//	m_pInstance = instance;
	//}

	//template<typename T>
	//bool CThread::Start()
	//{
	//	HANDLE hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, NULL);
	//	if (hThread)
	//	{
	//		::CloseHandle(hThread);
	//	}
	//	return (hThread != 0);
	//}

	//template<typename T>
	//unsigned WINAPI CThread::Run(LPVOID lParam)
	//{
	//	CThread* pThread = (CThread*)lParam;
	//	if (pThread == NULL)
	//	{
	//		return 0;
	//	}
	//	pThread->Execute();
	//	pThread->Free();
	//	_endthreadex(0);
	//	return 0;
	//}

	//template<typename T>
	//void CThread::Free()
	//{
	//	CNetworkCommuMgr::GetThreadMgr()->AddRecycleThread(this);
	//}

	//template<typename T>
	//void CThread::Wait()
	//{
	//	m_evtReady.Wait();
	//}

	//template<typename T>
	//int CThread::Execute()
	//{
	//	m_evtReady.Active();
	//	m_evtGiven.Wait();
	//	if (m_lpfnThreadStart)
	//	{
	//		(m_pInstance->*m_lpfnThreadStart)();
	//	}
	//	return 0;
	//}
}