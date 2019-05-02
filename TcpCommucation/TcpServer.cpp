#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"
#include "RecvNewConnEvt.h"
#include "ServerTcpConnection.h"
#include "RecvConnResultEvt.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		m_bListening(false)
	{

	}

	CTcpServer::~CTcpServer()
	{

	}

	bool CTcpServer::Listen(TCHAR* ip, int port)
	{
		if (!m_bListening)
		{
			_tcscpy(m_strServerIP, ip);
			m_nServerPort = port;

			//初始化服务端socket
			m_bListening = true;
			m_socket = m_socketAPI.CreateTcpSocket();
			m_socketAPI.SetNonBlock(m_socket);
			m_socketAPI.Bind(m_socket, m_strServerIP, m_nServerPort);
			m_socketAPI.Listen(m_socket);
			m_socketAddr = m_socketAPI.GetSocketAddr(m_strServerIP, m_nServerPort);

			PrintfInfo(_T("Listen success: %s:%d"), m_strServerIP, m_nServerPort);
			PrintfDebug(_T("Listen success: %s:%d, socket: %d"), m_strServerIP, m_nServerPort, m_socket);

			//加入select队列
			CNetworkCommuMgr::GetSelect()->AddSocket(m_socket, ESelectSocketType::RecvConn);

			return true;
		}
		return true;
	}

	void CTcpServer::OnRecvTcpEvent(CTcpEvt* pEvent)
	{
		if (pEvent->GetEvtType() == ETcpEvent::RecvNewConnection)//收到新连接
		{
			SOCKET clientSocket = pEvent->GetSendRecvSocket();//获取客户端socket
			TCHAR ip[NETCOMM_MAXIPSTRELN];
			int port = 0;
			m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

			bool result = false;//接收连接结果
			if (IsAllow(ip))
			{
				DispatchTcpEvt(pEvent);

				CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;
				if (pRecvEvent->m_bRefuse)//用户拒绝了新连接
				{
					m_socketAPI.CloseSocket(pRecvEvent->GetSendRecvSocket());//关闭客户端socket

					PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
						this->GetServerIP(), this->GetServerPort(), this->GetSocket(), ip, port, clientSocket);
				}
				else//用户允许了新连接
				{
					//创建tcp连接对象
					CServerTcpConnection* conn = new CServerTcpConnection(this, pRecvEvent->GetSendRecvSocket(), m_socket);
					CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//加入tcp连接对象
					result = true;
				}
			}
			else
			{
				//...
			}

			CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRecvConnResultEvt(this, result, clientSocket, ip, port));

			return;
		}

		__super::OnRecvTcpEvent(pEvent);
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
			TCHAR* strIP = new TCHAR[NETCOMM_MAXIPSTRELN]{0};
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

	bool CTcpServer::Send(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		return __super::SendData(socket, pBuf, len, asyncs, actualLen);
	}

	void CTcpServer::CloseClient(SOCKET client)
	{
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(client);
		if (pConn)
		{
			pConn->Close();
		}
	}
}