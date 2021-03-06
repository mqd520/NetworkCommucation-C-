#include "stdafx.h"
#include "Include/tc/RecvThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/Log.h"

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
			TcpLog::WriteLine(ETcpLogType::Debug, true, "recv thread run.");
		}
	}

	void RecvThread::OnThreadExecute()
	{
		if (TcpCommu::GetRecvHandler()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			TcpCommu::GetRecvHandler()->ProcessSocketEvt();
		}
	}
}