#include "stdafx.h"
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "ServerTcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	RecvNewConnEvt::RecvNewConnEvt(CTcpService* pSrv, SOCKET client, TCHAR* ip, int port) :
		TcpEvt(pSrv, client),
		nClientPort(port),
		bRecvConn(true)
	{
		evt = ETcpEvt::RecvConnResult;
		_tcscpy(strClientIP, ip);
	}

	RecvNewConnEvt::~RecvNewConnEvt()
	{
		if (bRecvConn)
		{
			CServerTcpConnection* conn = new CServerTcpConnection(pTcpSrv, socket, pTcpSrv->GetSocket());
			CTcpCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);
		}
	}

	void RecvNewConnEvt::Refuse()
	{
		bRecvConn = false;
	}

	bool RecvNewConnEvt::IsRecv()
	{
		return bRecvConn;
	}

	string RecvNewConnEvt::GetClientIP()
	{
		return "";
	}

	int RecvNewConnEvt::GetClientPort()
	{
		return nClientPort;
	}
}