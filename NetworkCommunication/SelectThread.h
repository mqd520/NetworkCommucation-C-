#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
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