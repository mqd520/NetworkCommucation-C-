#include "stdafx.h"
#include "TcpService.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "AsyncSendDataAction.h"

namespace NetworkCommunication
{

	CTcpService::CTcpService(int srvType) :
		m_nSrvType(srvType),
		m_socket(0),
		m_nLocalPort(0),
		m_lpCallback(NULL)
	{
		memset(m_strLocalIP, 0, 20 * sizeof(TCHAR));
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

	void CTcpService::OnRecvNewConnection(TCHAR* ip, int port, SOCKET scSocket)
	{
		PrintfInfo(_T("recved a new connection: [%s:%d]"), ip, port);
		if (m_lpCallback)
		{
			CRecvNewConnAction* pAction = new CRecvNewConnAction(m_socket, scSocket);
			m_lpCallback(pAction);
			delete pAction;
		}
	}

	bool CTcpService::OnRecvPeerData(PeerData* pData)
	{
		PrintfInfo(_T("recved from [%s:%d] data, size: %d"), pData->ip, pData->port, pData->len);
		return true;
	}

	void CTcpService::OnPeerCloseConn(TCHAR* ip, int port)
	{
		PrintfInfo(_T("client [%s:%d] closed the connection"), ip, port);
	}

	void CTcpService::OnSendPeerDataCompleted(SendPeerDataResult* result)
	{
		if (result->success)
		{
			PrintfInfo(_T("Send data to [%s:%d] successed, size: %d"), result->ip, result->port, result->len);
		}
		else
		{
			PrintfInfo(_T("Send data to [%s:%d] failed, size: %d, actual size: %d"), result->ip, result->port, result->len, result->actualLen);
		}
	}

	void CTcpService::OnNetError(TCHAR* ip, int port)
	{
		PrintfError(_T("Net error, %s:%d"), ip, port);
	}

	void CTcpService::OnRefuseNewConn(TCHAR* ip, int port)
	{
		PrintfWarning(_T("server refuse a connection: %s:%d"), ip, port);
	}
}