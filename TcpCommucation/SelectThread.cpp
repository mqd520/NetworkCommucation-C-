#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "SelectThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	SelectThread::SelectThread()
	{

	}

	SelectThread::~SelectThread()
	{
		int n = 0;
	}

	void SelectThread::Run()
	{
		if (!m_bRun)
		{
			__super::Run();
			CTcpCommuMgr::GetLogMgr()->AddLog(ETcpLogType::Debug, "select thread run.");
		}
	}

	void SelectThread::OnThreadExecute()
	{
		vector<SelectSocketData> vec = CTcpCommuMgr::GetSocketDataMgr()->GetSocket();
		if (vec.empty())
		{
			SetSleepTime();
		}
		else
		{
			CTcpCommuMgr::GetSelect()->QuerySingal(vec);
		}
	}
}