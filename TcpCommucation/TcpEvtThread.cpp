#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "TcpEvtThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"
#include "TcpEvtMgr.h"

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
			CTcpCommuMgr::GetLogMgr()->AddLog(ETcpLogType::Debug, "tcp evt thread run.");
		}
	}

	void TcpEvtThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetTcpEvtMgr()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetTcpEvtMgr()->ProcessTcpEvt();
		}
	}
}