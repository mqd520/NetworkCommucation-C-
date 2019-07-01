#include "stdafx.h"
#include "Include/tc/TcpLogMgr.h"

namespace tc
{
	Fun1	TcpLogMgr::fun;
	void*	TcpLogMgr::pParam1 = NULL;
	void*	TcpLogMgr::pParam2 = NULL;

	TcpLogMgr::TcpLogMgr()
	{

	}

	void TcpLogMgr::SetCallbackFn(Fun1 fun, void* pParam1, void* pParam2)
	{
		TcpLogMgr::fun = fun;
		TcpLogMgr::pParam1 = pParam1;
		TcpLogMgr::pParam2 = pParam2;
	}

	void TcpLogMgr::OnLog(ETcpLogType type, string log)
	{
		if (!fun._Empty())
		{
			fun(type, log, pParam1, pParam2);
		}
	}
}