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
		queueTime.push(millsecond);
	}

	void TimeMgr::Clear()
	{
		while (!queueTime.empty())
		{
			queueTime.pop();
		}
	}

	void TimeMgr::ProcessTime()
	{
		while ((int)queueTime.size() > 0)
		{
			int millsecond = queueTime.front();
			queueTime.pop();

			TimerMoudleMgr::GetTimerMgr()->OnTimer(millsecond);
		}
	}
}