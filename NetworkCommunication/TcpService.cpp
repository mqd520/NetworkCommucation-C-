#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"

namespace NetworkCommunication
{
	CTcpService::CTcpService() :
		m_socket(INVALID_SOCKET),
		m_nServerPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strServerIP, 0, NETCOMM_MAXIPSTRELN * sizeof(TCHAR));
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpService(this);
	}

	CTcpService::~CTcpService()
	{

	}

	SOCKET CTcpService::GetSocket()
	{
		return m_socket;
	}

	TCHAR* CTcpService::GetServerIP()
	{
		return m_strServerIP;
	}

	int CTcpService::GetServerPort()
	{
		return m_nServerPort;
	}

	void CTcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback)
	{
		m_lpCallback = lpCallback;
	}

	bool CTcpService::SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		//获取指定socket的tcp连接对象
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);

		if (pConn)
		{
			if (asyncs)//异步发送
			{
				pConn->SetAsyncSendData(pBuf, len, actualLen);
				return true;
			}
			else//同步发送
			{
				pConn->SendData(pBuf, len, actualLen);
			}
		}

		return false;
	}

	void CTcpService::OnRecvTcpEvent(CTcpEvt* pEvent)
	{
		if (m_lpCallback)
		{
			m_lpCallback(pEvent);//通知事件注册方

			if (pEvent->GetEvtType() == ETcpEvent::RecvNewConnection)
			{
				CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;
				if (pRecvEvent->m_bRefuse)//用户拒绝了新连接
				{
					SOCKET clientSocket = pRecvEvent->GetSendRecvSocket();//获取客户端socket
					TCHAR ip[NETCOMM_MAXIPSTRELN];
					int port = 0;
					m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

					m_socketAPI.CloseSocket(pRecvEvent->GetSendRecvSocket());//关闭客户端socket

					PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
						this->GetServerIP(), this->GetServerPort(), this->GetSocket(), ip, port, clientSocket);
					CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRefuseNewConnEvt(this, clientSocket, ip, port));
				}
				else//用户允许了新连接
				{
					//创建tcp连接对象
					CServerTcpConnection* conn = new CServerTcpConnection(this, pRecvEvent->GetSendRecvSocket(), m_socket);
					CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//加入tcp连接对象
				}
			}
		}
	}
}