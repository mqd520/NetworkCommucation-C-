#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"
#include "AsyncSendDataAction.h"


namespace NetworkCommunication
{
	CTcpService::CTcpService(int srvType) :
		m_nSrvType(srvType),
		m_socket(0),
		m_nLocalPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strLocalIP, 0, MAXIPSTRELN * sizeof(TCHAR));
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

	bool CTcpService::SendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		CTcpConnection* conn = NULL;
		if (m_nSrvType == ETcpServiceType::Server)//ָʾtcp����˶���
		{
			conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);//��ȡָ��socket��tcp���Ӷ���
		}
		else//ָʾtcp�ͻ��˶���
		{
			conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(m_socket);//��ȡָ��socket��tcp���Ӷ���
		}

		if (conn)
		{
			return conn->SendData(buf, len, actualLen);
		}
		return false;
	}

	void CTcpService::AsyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		AsyncSendPeerData* pData = new AsyncSendPeerData();
		if (m_nSrvType == ETcpServiceType::Server)//ָʾtcp����˶���
		{
			pData->send = socket;
		}
		else//ָʾtcp�ͻ��˶���
		{
			pData->send = m_socket;
		}
		pData->pBuf = buf;
		pData->len = len;
		CAsyncSendDataAction* pAction = new CAsyncSendDataAction(pData);
		CNetworkCommuMgr::GetTcp()->PushTcpAction(pAction);
	}

	void CTcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback)
	{
		m_lpCallback = lpCallback;
	}

	void CTcpService::OnRecvTcpEvent(CTcpSrvEvt* pEvent)
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
					TCHAR ip[MAXIPSTRELN];
					int port = 0;
					m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

					m_socketAPI.CloseSocket(pRecvEvent->GetSendRecvSocket());//�رտͻ���socket

					PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
						this->GetLocalIP(), this->GetLocalPort(), this->GetSocket(), ip, port, clientSocket);
					CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(new CRefuseNewConnEvt(this, clientSocket, ip, port));
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

	//void CTcpService::OnRecvNewConnection(CTcpAction* pEvent)
	//{
	//	if (m_lpCallback)
	//	{
	//		m_lpCallback(pEvent);
	//	}
	//}

	//bool CTcpService::OnRecvPeerData(PeerData* pData)
	//{
	//	PrintfInfo(_T("recved from [%s:%d] data, size: %d"), pData->ip, pData->port, pData->len);
	//	return true;
	//}

	//void CTcpService::OnPeerCloseConn(TCHAR* ip, int port)
	//{
	//	PrintfInfo(_T("client [%s:%d] closed the connection"), ip, port);
	//}

	//void CTcpService::OnSendPeerDataCompleted(SendPeerDataResult* result)
	//{
	//	if (result->success)
	//	{
	//		PrintfInfo(_T("Send data to [%s:%d] successed, size: %d"), result->ip, result->port, result->len);
	//	}
	//	else
	//	{
	//		PrintfInfo(_T("Send data to [%s:%d] failed, size: %d, actual size: %d"), result->ip, result->port, result->len, result->actualLen);
	//	}
	//}

	//void CTcpService::OnNetError(TCHAR* ip, int port)
	//{
	//	PrintfError(_T("Net error, %s:%d"), ip, port);
	//}

	//void CTcpService::OnRefuseNewConn(TCHAR* ip, int port)
	//{
	//	PrintfWarning(_T("server refuse a connection: %s:%d"), ip, port);
	//}
}