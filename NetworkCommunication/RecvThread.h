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
		void OnThreadExecute();

	public:
		CRecvThread();
		~CRecvThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}