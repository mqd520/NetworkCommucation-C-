#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	class CTimeoutEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CTimeoutEvtThread();
		~CTimeoutEvtThread();
	};
}