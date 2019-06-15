#include "stdafx.h"
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "ServerTcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	RecvNewConnEvt::RecvNewConnEvt(TcpService* pSrv, SOCKET client) :
		TcpEvt(pSrv, client),
		bRecvConn(true)
	{
		evt = ETcpEvt::RecvNewConn;
		strClientIP = SocketTool::GetPeerIpAndPort(client, &nClientPort);
	}

	RecvNewConnEvt::~RecvNewConnEvt()
	{
		if (bRecvConn)
		{
			CServerTcpConnection* conn = new CServerTcpConnection(static_cast<TcpServer*>(pTcpSrv), socket);
			TcpCommu::GetTcpConnectionMgr()->PushTcpConn(conn);
		}
		else
		{
			SocketTool::ShutDown(socket);
			SocketTool::CloseSocket(socket);
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
		return strClientIP;
	}

	int RecvNewConnEvt::GetClientPort()
	{
		return nClientPort;
	}
}