#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "SendThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	CSendThread::CSendThread()
	{

	}

	CSendThread::~CSendThread()
	{

	}

	void CSendThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ELogType::Debug, "send thread run.");
		}
	}

	void CSendThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetSendDataSingal()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetSendDataSingal()->ProcessSocketSingal();
		}
	}
}