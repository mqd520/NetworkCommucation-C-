#include "stdafx.h"
#include "ProcessTimeoutThread.h"
#include "TimerAppMgr.h"

namespace tc
{
	CProcessTimeoutThread::CProcessTimeoutThread()
	{

	}

	CProcessTimeoutThread::~CProcessTimeoutThread()
	{

	}

	void CProcessTimeoutThread::OnThreadExecute()
	{
		CTimerAppMgr::GetTimeoutMgr()->ProcessTimeout();
	}
}