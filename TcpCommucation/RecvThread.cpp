#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "RecvThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	RecvThread::RecvThread()
	{

	}

	RecvThread::~RecvThread()
	{

	}

	void RecvThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Debug, "recv thread run.");
		}
	}

	void RecvThread::OnThreadExecute()
	{
		if (TcpCommu::GetSelectSingal()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			TcpCommu::GetSelectSingal()->ProcessSocketSingal();
		}
	}
}