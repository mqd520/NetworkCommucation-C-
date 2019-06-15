#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "SelectSingalThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	SelectSingalThread::SelectSingalThread()
	{

	}

	SelectSingalThread::~SelectSingalThread()
	{

	}

	void SelectSingalThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Debug, "common thread run.");
		}
	}

	void SelectSingalThread::OnThreadExecute()
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