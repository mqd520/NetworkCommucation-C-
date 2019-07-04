#include "stdafx.h"
#include "Include/tc/keepAliveServer.h"

namespace tc
{
	KeepAliveServer::KeepAliveServer(
		int clientId /*= 0*/, int nRecvTimespan /*= TC_KeepAlive_RecvTimespan*/,
		int nTimeout /*= TC_KeepAlive_Timeout*/, int nMaxCount /*= TC_KeepAlive_MaxMissCount*/,
		void* pObj1 /*= NULL*/, void* pObj2 /*= NULL*/) :

		KeepAliveSrv(clientId, nTimeout, nMaxCount, pObj1, pObj2),
		nRecvTimespan(nRecvTimespan),
		dwLastRecv(0)
	{

	}

	KeepAliveServer::~KeepAliveServer()
	{

	}

	void KeepAliveServer::OnKeepAlive()
	{
		__super::OnKeepAlive();

		int n1 = dwLastRecv;
		int n2 = GetTickCount();
		dwLastRecv = n2;

		int span = n2 - n1;
		if (span >= nRecvTimespan)
		{
			SendKeepAlive(nClientId);
		}
	}
}