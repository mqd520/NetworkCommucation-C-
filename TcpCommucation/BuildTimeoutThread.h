#pragma once
#include "ThreadEntry.h"

namespace tc
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