#include "stdafx.h"
#include "Include/tc/TcpEvtThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpEvtMgr.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpEvtThread::TcpEvtThread()
	{

	}

	TcpEvtThread::~TcpEvtThread()
	{

	}

	void TcpEvtThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			TcpLog::WriteLine(ETcpLogType::Debug, "tcp evt thread run.");
		}
	}

	void TcpEvtThread::OnThreadExecute()
	{
		if (TcpCommu::GetTcpEvtMgr()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			TcpCommu::GetTcpEvtMgr()->ProcessTcpEvt();
		}
	}
}