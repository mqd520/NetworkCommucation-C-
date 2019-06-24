#include "stdafx.h"
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	RecvNewConnEvt::RecvNewConnEvt(TcpService* pSrv, SOCKET client) :
		TcpEvt(pSrv, client)
	{
		evtType = ETcpEvtType::RecvNewConn;
		strClientIP = SocketTool::GetPeerIpAndPort(client, &nClientPort);
	}

	RecvNewConnEvt::~RecvNewConnEvt()
	{

	}

	string RecvNewConnEvt::GetClientIP()
	{
		return strClientIP;
	}

	int RecvNewConnEvt::GetClientPort()
	{
		return nClientPort;
	}
}