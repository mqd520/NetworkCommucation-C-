#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "CommonThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

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
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ETcpLogType::Debug, "common thread run.");
		}
	}

	void CCommonThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetOtherSingal()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetOtherSingal()->ProcessSocketSingal();
		}
	}
}