#include "stdafx.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	bool TimerMoudleMgr::bInited = false;

	int TimerMoudleMgr::nTimeUnit = 200;
	TimeThread2 TimerMoudleMgr::timeThread1;
	TimeThread1 TimerMoudleMgr::timeThread2;
	TimerMgr TimerMoudleMgr::timerMgr;
	TimeMgr TimerMoudleMgr::timeMgr;

	TimerMoudleMgr::TimerMoudleMgr()
	{

	}

	TimerMoudleMgr::~TimerMoudleMgr()
	{

	}

	void TimerMoudleMgr::Init()
	{
		if (!bInited)
		{
			bInited = true;
			timeThread2.Run();
			timeThread1.Run();
		}
	}

	void TimerMoudleMgr::Exit()
	{
		timeThread2.Exit();
		timeThread1.Exit();
	}

	int TimerMoudleMgr::GetTimeUnit()
	{
		return nTimeUnit;
	}

	void TimerMoudleMgr::SetTimeUnit(int millsecond)
	{
		nTimeUnit = millsecond;
	}

	TimerMgr* TimerMoudleMgr::GetTimerMgr()
	{
		return &timerMgr;
	}

	TimeMgr* TimerMoudleMgr::GetTimeMgr()
	{
		return &timeMgr;
	}
}