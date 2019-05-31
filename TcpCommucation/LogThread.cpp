#include "stdafx.h"
#include "LogThread.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	LogThread::LogThread()
	{

	}

	LogThread::~LogThread()
	{

	}

	void LogThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetLogMgr()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CTcpCommuMgr::GetLogMgr()->ProcessLog();
		}
	}

	void LogThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
		}
	}
}