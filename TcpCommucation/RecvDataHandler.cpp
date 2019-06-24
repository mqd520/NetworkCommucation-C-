#include "stdafx.h"
#include "RecvDataHandler.h"
#include "RecvNewConnSocEvt.h"
#include "ConnDisconnSocEvt.h"
#include "RecvPeerDataSocEvt.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"

namespace tc
{
	RecvDataHandler::RecvDataHandler()
	{

	}

	RecvDataHandler::~RecvDataHandler()
	{
		Clear();
	}

	void RecvDataHandler::PushSocketEvt(SocketEvt* pEvt)
	{
		quSocketEvts.push(pEvt);
	}

	bool RecvDataHandler::IsEmpty()
	{
		return quSocketEvts.empty();
	}

	void RecvDataHandler::Clear()
	{
		while (!quSocketEvts.empty())
		{
			SocketEvt* pEvt = quSocketEvts.front();
			quSocketEvts.pop();
			delete pEvt;
		}
	}

	void RecvDataHandler::ProcessSocketEvt()
	{
		while (!quSocketEvts.empty())
		{
			SocketEvt* pEvt = quSocketEvts.front();
			quSocketEvts.pop();

			ESocketEvtType type = pEvt->GetEvtType();
			if (type == ESocketEvtType::RecvNewConn)	// 收到新连接
			{
				OnRecvNewConn(pEvt);
			}
			else if (type == ESocketEvtType::RecvPeerData)	// 收到对端数据
			{
				OnRecvPeerData(pEvt);
			}
			else if (type == ESocketEvtType::ConnDisconnect) // 连接断开
			{
				OnConnDisconnect(pEvt);
			}

			delete pEvt;
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
				TcpCommu::GetTcpConnectionMgr()->CreateTcpConnection(*it, pEvt1->GetServerSocket());

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
}