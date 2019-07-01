#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "Include/tc/SendThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpLog.h"

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
			TcpLog::WriteLine(ETcpLogType::Debug, "send thread run.");
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