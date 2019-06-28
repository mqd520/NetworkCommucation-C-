#include "stdafx.h"
#include "Include/Lib1/LibServer.h"
#include "Include/Lib1/Packet.h"

#include "tc/NetworkStreamWrite.h"
#include "tc/ConnDisconnectEvt.h"
#include "tc/ConnectSrvResultEvt.h"
#include "tc/RecvDataEvt.h"
#include "tc/RecvNewConnEvt.h"

namespace lib1
{
	LibServer::LibServer(EServiceType type /*= EServiceType::None*/, bool bNeedVertify /*= true*/, string ip /*= ""*/, int port /*= 0*/) :
		TcpServer(ip, port),
		LibSrv1(type, this, ELibSrvType::Server),
		nClientId(0),
		bNeedVertify(bNeedVertify)
	{

	}

	LibServer::~LibServer()
	{

	}

	void LibServer::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		nClientId = pEvt->GetSendRecvSocketId();

		TcpServer::OnRecvTcpEvent(pEvt);
		LibSrv1::OnRecvTcpEvent(pEvt);
	}

	void LibServer::OnRecvConnection(TcpEvt* pEvt)
	{
		PacketServerClient* pClient = clientMgr.CreateClient(nClientId, this, bNeedVertify);
		if (pClient)
		{
			pClient->OnCreate();
		}
	}

	void LibServer::OnConnDiconnect(TcpEvt* pEvt)
	{
		PacketServerClient* pClient = clientMgr.GetClient(nClientId);
		if (pClient)
		{
			pClient->OnClose();
		}

		clientMgr.Remove(nClientId);
	}

	void LibServer::OnRecvPeerData(TcpEvt* pEvt)
	{
		RecvDataEvt* pEvt1 = static_cast<RecvDataEvt*>(pEvt);
		BYTE* pBuf = pEvt1->GetRecvBuf();
		int len = pEvt1->GetBufLen();

		PacketServerClient* pClient = clientMgr.GetClient(nClientId);
		bool vertified = true;
		if (pClient)
		{
			vertified = pClient->IsVertified();
		}

		if (vertified)
		{
			LibSrv1::ProcessRecvBuf(pBuf, len, nClientId);	// 处理包缓冲区
		}
		else
		{
			if (pClient)
			{
				pClient->OnVertifyPwd(pBuf, len);	// 验证密码
			}
		}
	}

	void LibServer::OnLoginSrvRequest(PacketData& data)
	{
		PacketServerClient* pClient = clientMgr.GetClient(nClientId);
		if (pClient)
		{
			pClient->OnLoginSrvRequest(data);
		}
	}

	void LibServer::OnKeepAlive(PacketData& data)
	{
		PacketServerClient* pClient = clientMgr.GetClient(nClientId);
		if (pClient)
		{
			pClient->OnKeepAlive(data);
		}
	}

	void LibServer::SendPck(PacketBase& pck, int clientId)
	{
		LibSrv1::SendPck1(pck, clientId);
	}

	void LibServer::CloseClient(int clientId, bool b /*= true*/)
	{
		PacketServerClient* pClient = clientMgr.GetClient(nClientId);
		if (pClient)
		{
			pClient->OnClose();
		}
		clientMgr.Remove(nClientId);

		TcpServer::CloseClient(clientId, b);
	}

	void LibServer::Exit()
	{
		TcpServer::Exit();

		clientMgr.CloseAll();
	}

	void LibServer::OnMissKeepAlive(int clientId, int count)
	{
		LibSrv1::WriteLog(ETcpLogType::Warn, "miss KeepAlive from %s:%d, count: %d", "192.168.0.111", 56763, count);
	}
}
