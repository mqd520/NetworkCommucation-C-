#include "stdafx.h"
#include "Include/tc/TimeThread2.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	TimeThread2::TimeThread2()
	{

	}

	TimeThread2::~TimeThread2()
	{

	}

	void TimeThread2::OnThreadExecute()
	{
		TimerMoudleMgr::GetTimeMgr()->ProcessTime();
	}
}