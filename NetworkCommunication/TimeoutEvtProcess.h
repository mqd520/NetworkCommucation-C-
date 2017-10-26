#pragma once
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace NetworkCommunication
{
	//��ʱ�¼�����
	class CTimeoutEvtProcess
	{
	private:
		queue<int> m_quTimeout;//��ʱ����
		CThreadLock m_lock1;//�߳���,���m_vecTimeout����

	public:
		CTimeoutEvtProcess();
		~CTimeoutEvtProcess();

		void AddTimeoutEvt(int millsecond);

		void ProcessTimeoutEvt();
	};
}