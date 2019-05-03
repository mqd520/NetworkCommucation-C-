#pragma once
#include "ThreadEvent.h"
#include <process.h>
#include "ThreadEntry.h"

namespace tc
{
	//线程类
	class CThread
	{
	private:
		HANDLE m_hThread;//线程句柄

		CThreadEvent m_evtReady;
		CThreadEvent m_evtGiven;
		CThreadEntry* m_pEntry;

	private:
		//************************************
		// Method:    线程入口
		//************************************
		static unsigned WINAPI  Run(LPVOID lParam);

	public:
		CThread(CThreadEntry* pEntry);
		~CThread();

		//************************************
		// Method:    运行线程
		//************************************
		void Run();

		void Wait(int millsecond = 0);

		//************************************
		// Method:    线程执行
		//************************************
		void Execute();

		//************************************
		// Method:    线程执行完毕
		//************************************
		void ExecuteCmp();
	};
}