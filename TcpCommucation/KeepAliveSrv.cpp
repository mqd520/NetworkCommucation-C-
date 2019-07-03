#include "stdafx.h"
#include "Include/tc/KeepAliveSrv.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	KeepAliveSrv::KeepAliveSrv(
		int nTimeout /*= TC_KeepAlive_Timeout*/, int nMaxCount /*= TC_KeepAlive_MaxMissCount*/,
		void* pObj1 /*= NULL*/, void* pObj2 /*= NULL*/) :
		nTimeout(nTimeout),
		nMaxCount(nMaxCount),
		pObj1(pObj1),
		pObj2(pObj2),
		nMissCount(0)
	{
		tTimeout.SetTimeout(nTimeout);
		auto fun = std::bind(&KeepAliveSrv::OnTimer, this, _1, _2, _3, _4);
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

	//Packet* KeepAliveAliveSrv::BuildKeepAlive()
	//{
	//	throw new exception;
	//}

	void KeepAliveSrv::SendKeepAlive(int clientId /*= 0*/)
	{
		TcpLog::WriteLine(ETcpLogType::Info, "send keepAlive to %s:%d", "192.168.0.111", 12345);
	}

	void KeepAliveSrv::OnKeepAlive()
	{
		tTimeout.Reset();
		nMissCount = 0;

		TcpLog::WriteLine(ETcpLogType::Info, "recv keepAlive from %s:%d", "192.168.0.111", 12345);
	}

	void KeepAliveSrv::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		nMissCount++;
		if (nMissCount >= nMaxCount)
		{
			tTimeout.Stop();
		}

		OnMissKeepAlive(nMissCount, nMissCount >= nMaxCount);
	}

	void KeepAliveSrv::OnMissKeepAlive(int count, bool b /*= true*/)
	{
		TcpLog::WriteLine(ETcpLogType::Warn, "lose keepAlive from %s:%d, count: %d", "192.168.0.111", 12345, count);
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
}