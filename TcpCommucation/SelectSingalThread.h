#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// select �źŴ����߳�
	class SelectSingalThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		SelectSingalThread();
		~SelectSingalThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}