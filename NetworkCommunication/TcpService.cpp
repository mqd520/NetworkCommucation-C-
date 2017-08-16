#include "stdafx.h"
#include "TcpService.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace NetworkCommunication
{

	CTcpService::CTcpService(int srvType) :
		m_nSrvType(srvType)
	{

	}

	CTcpService::~CTcpService()
	{

	}

	int CTcpService::GetSrvType()
	{
		return m_nSrvType;
	}

	ServerSocketData CTcpService::GetServerSocketData()
	{
		return{ 0 };
	}

	void CTcpService::OnRecvNewConnection(ServerSocketData server, PeerSocketData client)
	{
		Printf1("[%s:%d] recv a new connection: [%s:%d]", server.ip, server.port, client.ip, client.port);
	}

	void CTcpService::OnPeerCloseSocket(PeerSocketData data)
	{
		Printf1("[%s:%d] close the socket", data.ip, data.port);
	}
}