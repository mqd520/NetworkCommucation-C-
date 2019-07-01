#include "stdafx.h"
#include "Include/tc/Timer.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	Timer::Timer(int timeout /*= 1000*/, int count /*= 0*/) :
		nTimeout(timeout),
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

	void Timer::SetCallback(Fun3 fun, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		this->fun = fun;
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

				if (!fun._Empty())
				{
					fun(this, nCounted, pParam1, pParam2);
				}
			}
		}
	}

	int Timer::Count()
	{
		return nCounted;
	}
}