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
		void OnThreadExecute();

	public:
		CSendThread();
		~CSendThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}