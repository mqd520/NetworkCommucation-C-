#include "stdafx.h"
#include "Include/tc/Def.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	RecvNewConnEvt::RecvNewConnEvt(TcpService* pSrv, SOCKET client) :
		TcpEvt(pSrv, client),
		bIsAllow(false)
	{
		evtType = ETcpEvtType::RecvNewConn;
	}

	bool RecvNewConnEvt::IsAllow()
	{
		return bIsAllow;
	}

	void RecvNewConnEvt::Allow()
	{
		TcpCommu::GetSocketDataMgr()->EnableSocket(socket, true);
	}
}