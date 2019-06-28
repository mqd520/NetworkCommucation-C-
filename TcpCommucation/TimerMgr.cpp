#include "stdafx.h"
#include "TimerMgr.h"

namespace tc
{
	TimerMgr::TimerMgr()
	{

	}

	TimerMgr::~TimerMgr()
	{

	}

	void TimerMgr::Add(Timer* pTimer)
	{
		vecTimer.push_back(pTimer);
	}

	void TimerMgr::Remove(Timer* pTimer)
	{
		for (vector<Timer*>::iterator it = vecTimer.begin(); it != vecTimer.end(); it++)
		{
			if (*it == pTimer)
			{
				vecTimer.erase(it);
				break;
			}
		}
	}

	void TimerMgr::Clear()
	{
		vecTimer.clear();
	}

	int TimerMgr::Count()
	{
		return (int)vecTimer.size();
	}

	void TimerMgr::OnTimer(int millsecond)
	{
		for (vector<Timer*>::iterator it = vecTimer.begin(); it != vecTimer.end(); it++)
		{
			(*it)->OnTimer(millsecond);
			if (vecTimer.empty())
			{
				break;
			}
		}
	}
}