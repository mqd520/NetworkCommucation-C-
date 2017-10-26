#pragma once
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace NetworkCommunication
{
	//超时事件处理
	class CTimeoutEvtProcess
	{
	private:
		queue<int> m_quTimeout;//超时队列
		CThreadLock m_lock1;//线程锁,针对m_vecTimeout变量

	public:
		CTimeoutEvtProcess();
		~CTimeoutEvtProcess();

		void AddTimeoutEvt(int millsecond);

		void ProcessTimeoutEvt();
	};
}