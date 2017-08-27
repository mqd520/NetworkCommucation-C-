#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		CTcpService(ETcpServiceType::Server),
		m_bListening(false),
		m_socketData({ 0 })
	{

	}

	CTcpServer::~CTcpServer()
	{

	}

	void CTcpServer::Init(char* ip, int port)
	{
		strcpy(m_strLocalIP, ip);
		m_nLocalPort = port;
	}

	void CTcpServer::AddAllowIP(char* ip)
	{
		bool exist = false;
		for (int i = 0; i < (int)m_vecAllowIP.size(); i++)
		{
			if (strcmp(m_vecAllowIP[i], ip) == 0)
			{
				exist = true;
				break;
			}
		}
		if (!exist)
		{
			char* strIP = new char[20];
			strcpy(strIP, ip);
			m_vecAllowIP.push_back(strIP);
		}
	}

	void CTcpServer::RemoveAllowIP(char* ip)
	{
		for (vector<char*>::iterator it = m_vecAllowIP.begin(); it < m_vecAllowIP.end(); it++)
		{
			if (strcmp(*it, ip) == 0)
			{
				m_vecAllowIP.erase(it);
				break;
			}
		}
	}

	void CTcpServer::ClearAllowIP()
	{
		m_vecAllowIP.clear();
	}

	bool CTcpServer::IsAllow(char* ip)
	{
		bool result = true;
		int count = (int)m_vecAllowIP.size();
		if (count > 0)
		{
			result = false;
			for (int i = 0; i < count; i++)
			{
				if (strcmp(m_vecAllowIP[i], ip) == 0)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}

	bool CTcpServer::Listen()
	{
		if (!m_bListening)
		{
			//初始化服务端socket
			m_bListening = true;
			m_socket = m_socketAPI.CreateTcpSocket();
			m_socketAPI.SetNonBlock(m_socket);
			m_socketAPI.Bind(m_socket, m_strLocalIP, m_nLocalPort);
			m_socketAPI.Listen(m_socket);
			PrintfDebug("listen success: %s:%d, socket: %d", m_strLocalIP, m_nLocalPort, m_socket);
			PrintfInfo("listen success: %s:%d", m_strLocalIP, m_nLocalPort);

			//创建并增加一个服务端socket数据
			m_socketData = CServerSocketMgr::Create(m_strLocalIP, m_nLocalPort, m_socket, this);

			//加入select队列
			CNetworkCommuMgr::GetSelect()->AddSocket(m_socket, ESelectSocketType::RecvConn);

			return true;
		}
		return true;
	}

	ServerSocket CTcpServer::GetServerSocketData()
	{
		return m_socketData;
	}
}