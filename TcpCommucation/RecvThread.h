#pragma once
#include "Include/tc/ThreadEntry.h"

namespace tc
{
	//���������߳�
	class RecvThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		RecvThread();
		~RecvThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}