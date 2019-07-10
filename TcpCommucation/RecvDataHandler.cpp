#include "stdafx.h"
#include "Include/tc/RecvDataHandler.h"
#include "Include/tc/RecvNewConnSocEvt.h"
#include "Include/tc/ConnDisconnSocEvt.h"
#include "Include/tc/RecvPeerDataSocEvt.h"
#include "Include/tc/ConnectCplSocEvt.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/ConnectSrvCplEvt.h"

namespace tc
{
	RecvDataHandler::RecvDataHandler()
	{

	}

	RecvDataHandler::~RecvDataHandler()
	{

	}

	void RecvDataHandler::OnSocketEvtProcess(SocketEvt* pEvt)
	{
		ESocketEvtType type = pEvt->GetEvtType();
		if (type == ESocketEvtType::RecvNewConn)
		{
			OnRecvNewConn(pEvt);
		}
		else if (type == ESocketEvtType::ConnDisconnect)
		{
			OnConnDisconnect(pEvt);
		}
		else if (type == ESocketEvtType::RecvPeerData)
		{
			OnRecvPeerData(pEvt);
		}
		else if (type == ESocketEvtType::ConnectCpl)
		{
			OnConnectCpl(pEvt);
		}
	}

	void RecvDataHandler::OnRecvNewConn(SocketEvt* evt)
	{
		RecvNewConnSocEvt* pEvt1 = static_cast<RecvNewConnSocEvt*>(evt);
		vector<SOCKET> clients = pEvt1->GetClients();
		TcpService* pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(pEvt1->GetServerSocket());
		if (pSrv)
		{
			for (vector<SOCKET>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				RecvNewConnEvt* pEvt2 = new RecvNewConnEvt(pSrv, *it);
				TcpCommu::GetTcpEvtMgr()->PushTcpEvent(pEvt2);
			}
		}
		else
		{
			for (vector<SOCKET>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				SocketTool::ShutDown(*it);
				SocketTool::CloseSocket(*it);
			}
		}
	}

	void RecvDataHandler::OnRecvPeerData(SocketEvt* pEvt)
	{
		RecvPeerDataSocEvt* pEvt1 = static_cast<RecvPeerDataSocEvt*>(pEvt);
		TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(pEvt1->GetSocket());
		if (pConn)
		{
			pConn->OnRecvPeerData(pEvt1->GetBuf(), pEvt1->GetLen());
		}
	}

	void RecvDataHandler::OnConnDisconnect(SocketEvt* pEvt)
	{
		ConnDisconnSocEvt* pEvt1 = static_cast<ConnDisconnSocEvt*>(pEvt);
		TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(pEvt1->GetSocket());
		if (pConn)
		{
			pConn->OnConnDisconnect(EDisconnReason::Peer);
		}
	}

	void RecvDataHandler::OnConnectCpl(SocketEvt* pEvt)
	{
		ConnectCplSocEvt* pEvt1 = static_cast<ConnectCplSocEvt*>(pEvt);
		if (pEvt1->GetResult())
		{
			TcpCommu::GetTcpConnectionMgr()->CreateTcpConnection(pEvt1->GetSocket(), NULL);
		}

		TcpService* pTcpSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(pEvt1->GetSocket());
		if (pTcpSrv)
		{
			ConnectSrvCplEvt* pEvt2 = new ConnectSrvCplEvt(pTcpSrv, pEvt1->GetSocket(), pEvt1->GetResult());
			TcpCommu::GetTcpEvtMgr()->PushTcpEvent(pEvt2);
		}
	}
}