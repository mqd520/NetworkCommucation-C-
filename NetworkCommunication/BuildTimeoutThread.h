#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//���ɳ�ʱ�����߳�
	class CBuildTimeoutThread : public CThreadEntry
	{
	private:
		int m_nTimespan;//���ʱ��

	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CBuildTimeoutThread();
		~CBuildTimeoutThread();
	};
}