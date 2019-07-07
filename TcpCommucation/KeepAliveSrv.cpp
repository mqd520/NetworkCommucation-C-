#include "stdafx.h"
#include "Include/tc/KeepAliveSrv.h"
#include "Include/tc/TcpLog.h"
#include "Include/tc/TimerMoudleMgr.h"
#include "Include/tc/TcpClient.h"
#include "Include/tc/TcpServer.h"

namespace tc
{
	KeepAliveSrv::KeepAliveSrv(
		int clientId /*= 0*/, int nTimeout /*= TC_KeepAlive_Timeout*/, int nMaxCount /*= TC_KeepAlive_MaxMissCount*/,
		void* pObj1 /*= NULL*/, void* pObj2 /*= NULL*/) :
		nClientId(clientId),
		nTimeout(nTimeout),
		nMaxCount(nMaxCount),
		pObj1(pObj1),
		pObj2(pObj2),
		nMissCount(0)
	{
		tTimeout.SetTimeout(nTimeout);
		auto fun = std::bind(&KeepAliveSrv::OnTimerTimeout, this, _1, _2, _3, _4);
		tTimeout.SetCallback(fun, NULL, NULL);
	}

	KeepAliveSrv::~KeepAliveSrv()
	{

	}

	void KeepAliveSrv::AttachObj(void* pObj1, void* pObj2)
	{
		this->pObj1 = pObj1;
		this->pObj2 = pObj2;
	}

	string KeepAliveSrv::GetPeerIp()
	{
		if (strPeerIp.empty())
		{
			if (pObj1)
			{
				if (nClientId == 0)
				{
					strPeerIp = ((TcpClient*)pObj1)->GetIP();
				}
				else
				{
					strPeerIp = ((TcpServer*)pObj1)->GetPeerIp(nClientId);
				}
			}
		}

		return strPeerIp;
	}

	int KeepAliveSrv::GetPeerPort()
	{
		if (nPort == 0)
		{
			if (pObj1)
			{
				if (nClientId == 0)
				{
					nPort = ((TcpClient*)pObj1)->GetPort();
				}
				else
				{
					nPort = ((TcpServer*)pObj1)->GetPeerPort(nClientId);
				}
			}
		}

		return nPort;
	}

	void KeepAliveSrv::SendKeepAlive(int clientId /*= 0*/)
	{
		//TcpLog::WriteLine(ETcpLogType::Debug, "send keepAlive to %s:%d", GetPeerIp().c_str(), GetPeerPort());
	}

	void KeepAliveSrv::OnKeepAlive()
	{
		tTimeout.Reset();
		nMissCount = 0;

		//TcpLog::WriteLine(ETcpLogType::Debug, "recv keepAlive from %s:%d", GetPeerIp().c_str(), GetPeerPort());
	}

	void KeepAliveSrv::OnTimerTimeout(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		nMissCount++;
		if (nMissCount >= nMaxCount)
		{
			CloseKeepAlive();
		}

		OnMissKeepAlive(nMissCount, nMissCount >= nMaxCount);
	}

	void KeepAliveSrv::OnMissKeepAlive(int count, bool b /*= true*/)
	{
		TcpLog::WriteLine(ETcpLogType::Warn, "lose keepAlive from %s:%d, count: %d", GetPeerIp().c_str(), GetPeerPort(), count);
	}

	void KeepAliveSrv::StartKeepAlive()
	{
		tTimeout.Run();
	}

	void KeepAliveSrv::CloseKeepAlive()
	{
		tTimeout.Stop();
		nMissCount = 0;
	}

	void KeepAliveSrv::Exit()
	{
		CloseKeepAlive();
		TimerMoudleMgr::GetTimerMgr()->Remove(&tTimeout);
	}
}