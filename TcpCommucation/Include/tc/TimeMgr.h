#pragma once
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// 时间管理
	class TimeMgr
	{
	public:
		TimeMgr();
		~TimeMgr();

	private:
		queue<int> queueTime;	// 时间队列
		CThreadLock lock1;		// 线程锁, 针对queueTime变量

	public:
		//************************************
		// Method:    添加一个时间数据
		//************************************
		void Add(int millsecond);

		//************************************
		// Method:    清除时间数据
		//************************************
		void Clear();

		//************************************
		// Method:    处理时间数据
		//************************************
		void ProcessTime();
	};
}