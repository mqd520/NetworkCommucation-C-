#include "stdafx.h"
#include "CommonThread.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include <tchar.h>

namespace NetworkCommunication
{
	CCommonThread::CCommonThread()
	{

	}

	CCommonThread::~CCommonThread()
	{

	}

	void CCommonThread::Run()
	{
		if (!m_bRun)
		{
			PrintfInfo(_T("Common thread run"));
			__super::Run();
		}
	}

	void CCommonThread::OnThreadExecute()
	{
		if (CNetworkCommuMgr::GetOtherSingal()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CNetworkCommuMgr::GetOtherSingal()->ProcessSocketSingal();
		}
	}
}