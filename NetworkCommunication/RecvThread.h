#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//���������߳�
	class CRecvThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

	public:
		CRecvThread();
		~CRecvThread();
	};
}