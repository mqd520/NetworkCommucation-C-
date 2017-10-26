#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	class CTimeoutThread : public CThreadEntry
	{
	private:
		int m_nTimeout;//超时时间

	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CTimeoutThread();
		~CTimeoutThread();
	};
}