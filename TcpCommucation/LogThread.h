#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// ��־�߳���
	class LogThread : public CThreadEntry
	{
	public:
		LogThread();
		~LogThread();

	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		void Run();
	};
}