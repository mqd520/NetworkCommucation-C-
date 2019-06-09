#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "RecvThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	CRecvThread::CRecvThread()
	{

	}

	CRecvThread::~CRecvThread()
	{

	}

	void CRecvThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ETcpLogType::Debug, "recv thread run.");
		}
	}

	void CRecvThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetRecvDataSingal()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetRecvDataSingal()->ProcessSocketSingal();
		}
	}
}