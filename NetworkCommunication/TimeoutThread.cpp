#include "stdafx.h"
#include "TimeoutThread.h"
#include "TimeoutMgr.h"

namespace NetworkCommunication
{
	CTimeoutThread::CTimeoutThread()
	{
		m_nTimeout = CTimeoutMgr::GetUnitMillSecond();
		SetSleepTime(m_nTimeout);
	}

	CTimeoutThread::~CTimeoutThread()
	{

	}

	void CTimeoutThread::OnThreadExecute()
	{
		CTimeoutMgr::m_timeoutEvtProcess.AddTimeoutEvt(m_nTimeout);
	}
}