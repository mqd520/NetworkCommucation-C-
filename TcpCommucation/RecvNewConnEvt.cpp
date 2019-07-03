#include "stdafx.h"
#include "Include/tc/Def.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	RecvNewConnEvt::RecvNewConnEvt(TcpService* pSrv, SOCKET client) :
		TcpEvt(pSrv, client)
	{
		evtType = ETcpEvtType::RecvNewConn;
	}
}