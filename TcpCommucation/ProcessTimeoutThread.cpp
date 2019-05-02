#include "stdafx.h"
#include "ProcessTimeoutThread.h"
#include "TimerAppMgr.h"

namespace NetworkCommunication
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