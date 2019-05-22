#include "stdafx.h"
#include "SendThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"
#include <tchar.h>

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
			PrintfInfo(_T("Send thread run"));
			__super::Run();
		}
	}

	void CSendThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetSendDataSingal()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CTcpCommuMgr::GetSendDataSingal()->ProcessSocketSingal();
		}
	}
}