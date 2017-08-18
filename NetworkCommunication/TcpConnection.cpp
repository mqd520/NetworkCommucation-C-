#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "RecvPeerDataAction.h"
#include "NetCommuMgr.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv)
	{
		CNetworkCommuMgr::GetSelect()->AddSocket(sendrecv, ESelectSocketType::ReadWriteData);//����select����
	}

	CTcpConnection::~CTcpConnection()
	{

	}

	SOCKET CTcpConnection::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	CTcpService* CTcpConnection::GetTcpService()
	{
		return m_pTcpSrv;
	}

	bool CTcpConnection::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool result = m_socketAPI.Send(GetSendRecvSocket(), buf, len, actualLen);

		//�����������ݽ������
		SendPeerDataResult data;
		data.success = result;
		data.len = len;
		data.peer = m_sendrecvSocket;
		ServerClientSocket peerData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(m_sendrecvSocket);//��ȡ�Զ�socket����
		strcpy(data.ip, peerData.ip);
		data.port = peerData.port;
		CSendPeerDataResultAction* pAction = new CSendPeerDataResultAction(data, m_sendrecvSocket);

		if (!result)//����ʧ��
		{
			if (m_pTcpSrv != NULL && m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)//ָʾtcp����˶���
			{
				CNetworkCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//��select���Ƴ��Զ�socket
			}
			else
			{

			}
		}
		return result;
	}

	void CTcpConnection::OnRecvPeerData(PeerData* data)
	{
		if (m_pTcpSrv)
		{
			if (m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)
			{
				ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(data->socket);
				ServerSocket sData = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(scData.server);
				PrintfDebug("[%s:%d] recv [%s:%d] data, size: %d, socket: %d,%d", sData.ip, sData.port, scData.ip, scData.port, sData.socket, scData.client);
			}

			m_pTcpSrv->OnRecvPeerData(data);
		}
	}

	void CTcpConnection::OnPeerCloseSocket(SOCKET peer)
	{
		////����tcp����: �Զ������ر�
		//CPeerCloseAction* pAction = new CPeerCloseAction(m_localSocket, peer);
		//CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		//CNetworkCommuMgr::GetTcpConnectionMgr()->OnPeerClose(peer);//֪ͨtcp���ӹ���,�Զ������ر�
	}
}