#include "stdafx.h"
#include "Include/tc/KeepAliveClient.h"
#include "Include/tc/TimerMoudleMgr.h"

namespace tc
{
	KeepAliveClient::KeepAliveClient(
		int nTimespan /*= TC_KeepAlive_Timespan*/,
		int nTimeout /*= TC_KeepAlive_Timeout*/, int nMaxCount /*= TC_KeepAlive_MaxMissCount*/, void* pObj1 /*= NULL*/, void* pObj2 /*= NULL*/) :
		KeepAliveSrv(0, nTimeout, nMaxCount, pObj1, pObj2),
		nTimespan(nTimespan)
	{
		tTimespan.SetTimeout(nTimespan);
		auto fun = std::bind(&KeepAliveClient::OnTimerClient, this, _1, _2, _3, _4);
		tTimespan.SetCallback(fun, NULL, NULL);
	}

	KeepAliveClient::~KeepAliveClient()
	{

	}

	void KeepAliveClient::OnTimerClient(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		SendKeepAlive(nClientId);
	}

	void KeepAliveClient::OnKeepAlive()
	{
		tTimespan.Reset();

		__super::OnKeepAlive();
	}

	void KeepAliveClient::OnMissKeepAlive(int count, bool b /*= true*/)
	{
		__super::OnMissKeepAlive(count);

		if (b)
		{
			tTimespan.Stop();
		}
	}

	void KeepAliveClient::StartKeepAlive()
	{
		__super::StartKeepAlive();

		SendKeepAlive(nClientId);
		tTimespan.Run();
	}

	void KeepAliveClient::CloseKeepAlive()
	{
		__super::CloseKeepAlive();

		tTimespan.Stop();
	}

	void KeepAliveClient::Exit()
	{
		__super::Exit();
		TimerMoudleMgr::GetTimerMgr()->Remove(&tTimespan);
	}
}