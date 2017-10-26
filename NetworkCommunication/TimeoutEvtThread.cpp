#include "stdafx.h"
#include "TimeoutEvtThread.h"
#include "TimeoutMgr.h"
#include "TimeoutListMgr.h"

namespace NetworkCommunication
{
	CTimeoutEvtThread::CTimeoutEvtThread()
	{

	}

	CTimeoutEvtThread::~CTimeoutEvtThread()
	{

	}

	void CTimeoutEvtThread::OnThreadExecute()
	{
		CTimeoutMgr::m_timeoutEvtProcess.ProcessTimeoutEvt();
	}
}