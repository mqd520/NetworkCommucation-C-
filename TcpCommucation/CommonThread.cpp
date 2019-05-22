#include "stdafx.h"
#include "CommonThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"
#include <tchar.h>

namespace tc
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
		if (CTcpCommuMgr::GetOtherSingal()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CTcpCommuMgr::GetOtherSingal()->ProcessSocketSingal();
		}
	}
}