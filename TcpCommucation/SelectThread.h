#pragma once
#include "Include/tc/ThreadEntry.h"

namespace tc
{
	//select�߳�
	class SelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		SelectThread();
		~SelectThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}