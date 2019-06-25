#include "stdafx.h"
#include "TimeMgr.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	TimeMgr::TimeMgr()
	{

	}

	TimeMgr::~TimeMgr()
	{

	}

	void TimeMgr::Add(int millsecond)
	{
		lock1.Lock();
		queueTime.push(millsecond);
		lock1.Unlock();
	}

	void TimeMgr::ProcessTime()
	{
		lock1.Lock();

		while (queueTime.size() > 0)
		{
			int millsecond = queueTime.front();
			queueTime.pop();

			TimerMoudleMgr::GetTimerMgr()->OnTimer(millsecond);
		}

		lock1.Unlock();
	}
}