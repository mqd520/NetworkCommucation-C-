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
		void OnThreadRun();

	public:
		CCommonThread();
		~CCommonThread();
	};
}