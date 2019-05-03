#include "stdafx.h"
#include "BuildTimeoutThread.h"
#include "TimerAppMgr.h"

namespace tc
{
	CBuildTimeoutThread::CBuildTimeoutThread()
	{
		m_nTimespan = CTimerAppMgr::GetTimeoutUnit();
		SetSleepTime(m_nTimespan);
	}

	CBuildTimeoutThread::~CBuildTimeoutThread()
	{

	}

	void CBuildTimeoutThread::OnThreadExecute()
	{
		CTimerAppMgr::GetTimeoutMgr()->Add(m_nTimespan);
	}
}