#include "stdafx.h"
#include "RecvThread.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include <tchar.h>

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
			PrintfInfo(_T("Recv thread run"));
			__super::Run();
		}
	}

	void CRecvThread::OnThreadExecute()
	{
		if (CNetworkCommuMgr::GetRecvDataSingal()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CNetworkCommuMgr::GetRecvDataSingal()->ProcessSocketSingal();
		}
	}
}