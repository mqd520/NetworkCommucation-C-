#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "SendThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	SendThread::SendThread()
	{

	}

	SendThread::~SendThread()
	{

	}

	void SendThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Debug, "send thread run.");
		}
	}

	void SendThread::OnThreadExecute()
	{
		if (TcpCommu::GetSendHandler()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			TcpCommu::GetSendHandler()->ProcessSocketEvt();
		}
	}
}