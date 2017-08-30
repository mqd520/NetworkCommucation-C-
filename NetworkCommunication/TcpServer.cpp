#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		CTcpService(ETcpServiceType::Server),
		m_bListening(false)
	{
		CNetworkCommuMgr::GetTcpServerMgr()->Push(this);
	}

	CTcpServer::~CTcpServer()
	{

	}

	bool CTcpServer::Listen(TCHAR* ip, int port)
	{
		if (!m_bListening)
		{
			_tcscpy(m_strLocalIP, ip);
			m_nLocalPort = port;

			//初始化服务端socket
			m_bListening = true;
			m_socket = m_socketAPI.CreateTcpSocket();
			m_socketAPI.SetNonBlock(m_socket);
			m_socketAPI.Bind(m_socket, m_strLocalIP, m_nLocalPort);
			m_socketAPI.Listen(m_socket);
			m_socketAddr = m_socketAPI.GetSocketAddr(m_strLocalIP, m_nLocalPort);

			PrintfDebug(_T("listen success: %s:%d, socket: %d"), m_strLocalIP, m_nLocalPort, m_socket);
			PrintfInfo(_T("listen success: %s:%d"), m_strLocalIP, m_nLocalPort);

			//加入select队列
			CNetworkCommuMgr::GetSelect()->AddSocket(m_socket, ESelectSocketType::RecvConn);

			return true;
		}
		return true;
	}

	SOCKADDR_IN CTcpServer::GetServerSocketAddr()
	{
		return m_socketAddr;
	}

	void CTcpServer::AddAllowIP(TCHAR* ip)
	{
		bool exist = false;
		for (int i = 0; i < (int)m_vecAllowIP.size(); i++)
		{
			if (_tcscmp(m_vecAllowIP[i], ip) == 0)
			{
				exist = true;
				break;
			}
		}
		if (!exist)
		{
			TCHAR* strIP = new TCHAR[20]{0};
			_tcscpy(strIP, ip);
			m_vecAllowIP.push_back(strIP);
		}
	}

	void CTcpServer::RemoveAllowIP(TCHAR* ip)
	{
		for (vector<TCHAR*>::iterator it = m_vecAllowIP.begin(); it < m_vecAllowIP.end(); it++)
		{
			if (_tcscmp(*it, ip) == 0)
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

	bool CTcpServer::IsAllow(TCHAR* ip)
	{
		bool result = true;
		int count = (int)m_vecAllowIP.size();
		if (count > 0)
		{
			result = false;
			for (int i = 0; i < count; i++)
			{
				if (_tcscmp(m_vecAllowIP[i], ip) == 0)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}
}