#pragma once
#include "ThreadEntry.h"

namespace tc
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