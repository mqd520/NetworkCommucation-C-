#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//����ʱ�����߳�
	class CProcessTimeoutThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CProcessTimeoutThread();
		~CProcessTimeoutThread();
	};
}