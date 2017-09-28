#pragma once
#include "ThreadEvent.h"
#include <process.h>
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//œﬂ≥Ã¿‡
	class CThread
	{
	private:
		//CThreadEvent m_evtReady;
		//CThreadEvent m_evtGiven;
		CThreadEntry* m_pEntry;

	private:
		static unsigned WINAPI  Run(LPVOID lParam);

	public:
		CThread(CThreadEntry* pEntry);
		~CThread();

		bool Run();

		void Wait(int millsecond = 0);

		int Execute();

		void Free();
	};
}