#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//���������߳�
	class CSendThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

	public:
		CSendThread();
		~CSendThread();
	};
}