#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"

namespace NetworkCommunication
{
	CTcpService::CTcpService(int srvType) :
		m_nSrvType(srvType),
		m_socket(0),
		m_nLocalPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strLocalIP, 0, NETCOMM_MAXIPSTRELN * sizeof(TCHAR));
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpService(this);
	}

	CTcpService::~CTcpService()
	{

	}

	int CTcpService::GetSrvType()
	{
		return m_nSrvType;
	}

	SOCKET CTcpService::GetSocket()
	{
		return m_socket;
	}

	TCHAR* CTcpService::GetLocalIP()
	{
		return m_strLocalIP;
	}

	int CTcpService::GetLocalPort()
	{
		return m_nLocalPort;
	}

	void CTcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback)
	{
		m_lpCallback = lpCallback;
	}

	void CTcpService::OnRecvTcpEvent(CTcpEvt* pEvent)
	{
		if (m_lpCallback && pEvent && pEvent->GetEvtType() != ETcpSrvEvent::None)
		{
			m_lpCallback(pEvent);//֪ͨ�¼�ע�᷽

			if (pEvent->GetEvtType() == ETcpSrvEvent::RecvNewConnection)
			{
				CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;
				if (pRecvEvent->m_bRefuse)//�û��ܾ���������
				{
					SOCKET clientSocket = pRecvEvent->GetSendRecvSocket();//��ȡ�ͻ���socket
					TCHAR ip[NETCOMM_MAXIPSTRELN];
					int port = 0;
					m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

					m_socketAPI.CloseSocket(pRecvEvent->GetSendRecvSocket());//�رտͻ���socket

					PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
						this->GetLocalIP(), this->GetLocalPort(), this->GetSocket(), ip, port, clientSocket);
					CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRefuseNewConnEvt(this, clientSocket, ip, port));
				}
				else//�û�������������
				{
					//����tcp���Ӷ���
					CServerTcpConnection* conn = new CServerTcpConnection(this, pRecvEvent->GetSendRecvSocket(), m_socket);
					CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//����tcp���Ӷ���
				}
			}
		}
	}
}