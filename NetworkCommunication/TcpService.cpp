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

	ServerSocket CTcpService::GetServerSocketData()
	{
		return{ 0 };
	}

	SOCKET CTcpService::GetLocalSocket()
	{
		return m_localSocket;
	}

	void CTcpService::OnRecvNewConnection(ServerSocket server, ServerClientSocket client)
	{
		PrintfInfo("recv a new connection: [%s:%d]", client.ip, client.port);
	}

	void CTcpService::OnPeerCloseSocket(ServerClientSocket data)
	{
		//Printf1("[%s:%d] close the socket", data.ip, data.port);
		PrintfInfo("[%s:%d] close the socket: %d", data.ip, data.port, data.client);
	}

	bool CTcpService::OnRecvPeerData(PeerData* data)
	{
		//Printf1("Recv from [%s:%d] data, size: %d", data.ip, data.port, len);
		//Printf1("Recv [%s:%d] data, size: %d, socket: %d", data.ip, data.port, len, data.client);
		return true;
	}

	void CTcpService::OnSendPeerDataCompleted(SendPeerDataResult result)
	{
		if (result.success)
		{
			PrintfInfo("Send data to [%s:%d] success, size: %d", result.ip, result.port, result.len);
		}
		else
		{
			PrintfInfo("Send data to [%s:%d] failed", result.ip, result.port);
			if (m_nSrvType == ETcpServiceType::Server)//ָʾtcp����˶���
			{
				CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(result.peer);
				m_socketAPI.CloseSocket(result.peer);//�ر�socket
			}
			else//tcp�ͻ��˶���
			{

			}
		}
	}

	bool CTcpService::SendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		CTcpConnection* conn = NULL;
		if (m_nSrvType == ETcpServiceType::Server)//ָʾtcp����˶���
		{
			conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);//��ȡָ���Զ�socket��tcp���Ӷ���
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

	void CTcpService::AsyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		//CNetworkCommuMgr::GetTcpConnectionMgr()->AsyncSend(socket, buf, len, actualLen);
	}
}