#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//select�߳�
	class CSelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CSelectThread();
		~CSelectThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}