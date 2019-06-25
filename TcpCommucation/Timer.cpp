#include "stdafx.h"
#include "Include/tc/Timer.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	Timer::Timer(int timeout /*= 1000*/, LPTimeoutCallback lpfn /*= NULL*/, int count /*= 0*/) :
		nTimeout(timeout),
		lpfn(lpfn),
		nCount(0),
		bRunning(false),
		nTimeouted(0),
		nCounted(0),
		pParam1(NULL),
		pParam2(NULL),
		bInited(false)
	{

	}

	Timer::~Timer()
	{

	}

	void Timer::Init()
	{
		if (!bInited)
		{
			bInited = true;
			TimerMoudleMgr::GetTimerMgr()->Add(this);
		}
	}

	void Timer::SetTimeout(int millsecond)
	{
		nTimeout = millsecond;
	}

	void Timer::SetCallback(LPTimeoutCallback lpfn, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		this->lpfn = lpfn;
		this->pParam1 = pParam1;
		this->pParam2 = pParam2;
	}

	void Timer::Run()
	{
		Init();
		bRunning = true;
	}

	void Timer::Stop()
	{
		bRunning = false;
		nTimeouted = 0;
		nCounted = 0;
	}

	void Timer::Pause()
	{
		bRunning = false;
	}

	void Timer::Resume()
	{
		bRunning = true;
	}

	void Timer::Reset()
	{
		nTimeouted = 0;
	}

	bool Timer::IsRun()
	{
		return bRunning;
	}

	void Timer::OnTimer(int millsecond)
	{
		if (bRunning && (nCount == 0 || nCounted < nCount))
		{
			nTimeouted += millsecond;

			nTimeouted = nTimeouted > nTimeout ? nTimeout : nTimeouted;

			if (nTimeouted == nTimeout)
			{
				nCounted++;
				nTimeouted = 0;
				lpfn(this, nCounted, this->pParam1, this->pParam2);
			}
		}
	}

	int Timer::Count()
	{
		return nCounted;
	}
}