#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	class CTimeoutThread : public CThreadEntry
	{
	private:
		int m_nTimeout;//��ʱʱ��

	protected:
		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadExecute();

	public:
		CTimeoutThread();
		~CTimeoutThread();
	};
}