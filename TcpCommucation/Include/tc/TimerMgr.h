#pragma once
#include <vector>
#include "ThreadLock.h"
#include "Timer.h"

using namespace std;

namespace tc
{
	//定时器管理
	class TimerMgr
	{
	public:
		TimerMgr();
		~TimerMgr();

	private:
		vector<Timer*> vecTimer;	// 定时器集合
		CThreadLock lock1;			// 线程锁, 针对 vecTimer

	public:
		//************************************
		// Method:    添加一个定时器
		// Parameter: 定时器
		//************************************
		void Add(Timer* pTimer);

		//************************************
		// Method:    移除一个定时器
		// Parameter: 定时器
		//************************************
		void Remove(Timer* pTimer);

		//************************************
		// Method:    清除所有定时器
		//************************************
		void Clear();

		//************************************
		// Method:    获取定时器数目
		//************************************
		int Count();

		//************************************
		// Method:    时间事件处理
		// Parameter: 超时时间
		//************************************
		void OnTimer(int millsecond);
	};
}