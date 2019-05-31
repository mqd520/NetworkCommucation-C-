#include "stdafx.h"
#include "Include/tc/Def1.h"
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

	void LogThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ELogType::Debug, "log thread run.");
		}
	}

	void LogThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetLogMgr()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetLogMgr()->ProcessLog();
		}
	}
}