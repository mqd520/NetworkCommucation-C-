#include "stdafx.h"
#include "Include/pck/IGPacketSrvServer.h"
#include "Include/pck/PacketCmd.h"
#include "Include/pck/LoginSrvRequestPacket.h"
#include "Include/pck/LoginSrvResultPacket.h"
#include "Include/pck/CommonTool.h"
#include "Include/pck/ServerSession.h"
#include "Include/pck/KeepAlivePacket.h"

#include "tc/TcpLog.h"

namespace pck
{
	IGPacketSrvServer::IGPacketSrvServer(
		string ip /*= ""*/, int port /*= 0*/,
		EServerType localType /*= EServerType::None*/,
		bool bRecvPwd /*= true*/) :

		TcpServer(ip, port),
		IGPacketSrv(localType),
		bRecvPwd(bRecvPwd),
		nCurClientId(0)
	{
		AttachTcpServiceObj(this);
	}

	IGPacketSrvServer::~IGPacketSrvServer()
	{

	}

	void IGPacketSrvServer::OnRecvNewConnection(RecvNewConnEvt* pEvt)
	{
		nCurClientId = pEvt->GetSendRecvSocketId();
		sessionMgr.CreateSession(nCurClientId, this, bRecvPwd);
	}

	void IGPacketSrvServer::OnRecvPeerData(RecvPeerDataEvt* pEvt)
	{
		nCurClientId = pEvt->GetSendRecvSocketId();
		__super::OnRecvPeerData(pEvt);

		ServerSession* pSession = sessionMgr.GetSession(nCurClientId);
		if (pSession)
		{
			if (pSession->OnRecvPeerData(pEvt))
			{
				IGPacketSrv::ProcessRecvBuf(pEvt->GetRecvBuf(), pEvt->GetBufLen(), nCurClientId);
			}
		}
		else
		{
			TcpLog::WriteLine(ETcpLogType::Warn, "lose session: %s:%d", pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort());
			CloseClient(nCurClientId);
		}
	}

	void IGPacketSrvServer::OnConnDisconnect(ConnDisconnectEvt* pEvt)
	{
		nCurClientId = pEvt->GetSendRecvSocketId();
		__super::OnConnDisconnect(pEvt);
		sessionMgr.CloseSession(nCurClientId);
	}

	void IGPacketSrvServer::PreProcessPck(PacketData& data)
	{
		if (data.cmd == (int)EPacketCmd::LoginSrvRequest)
		{
			OnLoginSrvRequest(data);
		}
		else if (data.cmd == (int)EPacketCmd::KeepAlive)
		{
			ServerSession* pSession = sessionMgr.GetSession(nCurClientId);
			if (pSession)
			{
				pSession->OnRecvKeepAlive();
			}
		}
		else
		{
			__super::PreProcessPck(data);
		}
	}

	void IGPacketSrvServer::OnLoginSrvRequest(PacketData& data)
	{
		LoginSrvRequestPacket* pPck = (LoginSrvRequestPacket*)data.pPck;
		if (pPck)
		{
			ServerSession* pSession = sessionMgr.GetSession(nCurClientId);
			if (pSession)
			{
				pSession->OnLoginSrvRequest(data, true);
			}

			string ip = TcpServer::GetPeerIp(data.clientId);
			int port = TcpServer::GetPeerPort(data.clientId);
			TcpLog::WriteLine(ETcpLogType::Info, "recv client login request, login success, addr: %s:%d, type: %s",
				ip.c_str(), port, CommonTool::GetServerName((EServerType)pPck->cbCurrentServerType).c_str());

			SendLoginSrvResultPck(data.clientId);
		}
	}

	void IGPacketSrvServer::SendLoginSrvResultPck(int clientId)
	{
		LoginSrvResultPacket pck;
		pck.cbVerifyCode = 1;
		pck.nServerID = 32656;

		SendPck(pck, clientId);
	}

	void IGPacketSrvServer::OnSessionClose(int clientId)
	{
		sessionMgr.CloseSession(clientId);
		CloseClient(clientId);
	}

	void IGPacketSrvServer::SendKeepAlive(int clientId /*= 0*/)
	{
		KeepAlivePacket pck;
		pck.cbKeepAlive = 1;

		SendPck(pck, clientId);


	}

	void IGPacketSrvServer::OnMissKeepAlive(int clientId, int count, bool b /*= true*/)
	{
		if (b)
		{
			CloseClient(clientId, true);
		}
	}

	void IGPacketSrvServer::SendPck(Packet& pck, int clientId)
	{
		SendPacket(pck, clientId);
	}

	void IGPacketSrvServer::Exit()
	{
		sessionMgr.CloseSession();
		TcpServer::Exit();
		IGPacketSrv::Exit();
	}
}