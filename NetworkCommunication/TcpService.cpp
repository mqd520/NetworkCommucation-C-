#include "stdafx.h"
#include "TcpService.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace NetworkCommunication
{

	CTcpService::CTcpService(int srvType) :
		m_nSrvType(srvType),
		m_localSocket(0),
		m_nLocalPort(0)
	{
		memset(m_strLocalIP, 0, 20 * sizeof(char));
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

	SOCKET CTcpService::GetLocalSocket()
	{
		return m_localSocket;
	}

	void CTcpService::OnRecvNewConnection(ServerSocketData server, PeerSocketData client)
	{
		//Printf1("[%s:%d] recv a new connection: [%s:%d]", server.ip, server.port, client.ip, client.port);
		Printf1("[%s:%d:%d] recv a new connection: [%s:%d:%d]", server.ip, server.port, server.socket, client.ip, client.port, client.peer);
	}

	void CTcpService::OnPeerCloseSocket(PeerSocketData data)
	{
		//Printf1("[%s:%d] close the socket", data.ip, data.port);
		Printf1("[%s:%d] close the socket: %d", data.ip, data.port, data.peer);
	}

	bool CTcpService::OnRecvPeerData(BYTE buf[], int len, PeerSocketData data)
	{
		//Printf1("Recv from [%s:%d] data, size: %d", data.ip, data.port, len);
		Printf1("Recv [%s:%d] data, size: %d, socket: %d", data.ip, data.port, len, data.peer);
		return true;
	}

	void CTcpService::OnSendPeerDataCompleted(SendPeerDataResult result)
	{
		if (result.success)
		{
			Printf1("Send data to [%s:%d] success, size: %d", result.ip, result.port, result.len);
		}
		else
		{
			Printf1("Send data to [%s:%d] failed", result.ip, result.port);
			if (m_nSrvType == ETcpServiceType::Server)//指示tcp服务端对象
			{
				CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveTcpConnByPeerSocket(result.peer);
				m_socketAPI.CloseSocket(result.peer);//关闭socket
			}
			else//tcp客户端对象
			{

			}
		}
	}

	bool CTcpService::SendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		CTcpConnection* conn = NULL;
		if (m_nSrvType == ETcpServiceType::Server)//指示tcp服务端对象
		{
			conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetTcpConnByPeerSocket(socket);//获取指定对端socket的tcp连接对象
		}
		else
		{

		}

		if (conn)
		{
			return conn->SendData(buf, len, actualLen);
		}
		return false;
	}

	void CTcpService::UnasyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		CNetworkCommuMgr::GetTcpConnectionMgr()->UnAsyncSend(socket, buf, len, actualLen);
	}
}