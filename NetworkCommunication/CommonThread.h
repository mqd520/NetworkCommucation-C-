#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//ͨ���źŴ����߳�
	class CCommonThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CCommonThread();
		~CCommonThread();

		//************************************
		// Method:    ��ʼ�����߳�
		//************************************
		void Run();
	};
}