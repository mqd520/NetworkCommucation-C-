#include "stdafx.h"
#include "SendThread.h"
#include "NetCommuMgr.h"
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
		if (CNetworkCommuMgr::GetSendDataSingal()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CNetworkCommuMgr::GetSendDataSingal()->ProcessSocketSingal();
		}
	}
}