#include "stdafx.h"
#include "Include/tc/Def1.h"
#include "Include/tc/SelectThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpLog.h"

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
			TcpLog::WriteLine(ETcpLogType::Debug, "select thread run.");
		}
	}

	void SelectThread::OnThreadExecute()
	{
		vector<SocketInfoData> vec = TcpCommu::GetSocketDataMgr()->GetSocketData();
		if (vec.empty())
		{
			SetSleepTime();
		}
		else
		{
			TcpCommu::GetSelect()->QuerySingal(vec);
		}
	}
}