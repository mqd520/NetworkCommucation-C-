#include "stdafx.h"
#include "TimeThread1.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	TimeThread1::TimeThread1()
	{
		nTime = TimerMoudleMgr::GetTimeUnit();
		SetSleepTime(nTime);
	}

	TimeThread1::~TimeThread1()
	{

	}

	void TimeThread1::OnThreadExecute()
	{
		TimerMoudleMgr::GetTimeMgr()->Add(nTime);
	}
}