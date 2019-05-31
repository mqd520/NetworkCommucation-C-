#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "SelectThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	CSelectThread::CSelectThread()
	{

	}

	CSelectThread::~CSelectThread()
	{
		int n = 0;
	}

	void CSelectThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ELogType::Debug, "select thread run.");
		}
	}

	void CSelectThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetSelect()->IsEmpty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetSelect()->Select();
		}
	}
}