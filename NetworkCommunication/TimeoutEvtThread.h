#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	class CTimeoutEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CTimeoutEvtThread();
		~CTimeoutEvtThread();
	};
}