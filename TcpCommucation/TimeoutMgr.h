#pragma once
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	//超时事件管理
	class CTimeoutMgr
	{
	private:
		queue<int> m_quTimeout;//超时队列
		CThreadLock m_lock1;//线程锁,针对m_vecTimeout变量

	public:
		CTimeoutMgr();
		~CTimeoutMgr();

		//************************************
		// Method:    添加一个超时数据
		// Parameter: 超时时间
		//************************************
		void Add(int millsecond);

		//************************************
		// Method:    处理超时数据
		//************************************
		void ProcessTimeout();
	};
}