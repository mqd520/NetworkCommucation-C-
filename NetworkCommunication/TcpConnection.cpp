#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "RecvPeerDataAction.h"
#include "NetCommuMgr.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(SOCKET localSocket, SOCKET peerSocket/* = NULL*/, CTcpService* pSrv/* = NULL*/) :
		m_peerSocket(peerSocket),
		m_localSocket(localSocket),
		m_pTcpSrv(pSrv)
	{

	}

	CTcpConnection::~CTcpConnection()
	{

	}

	SOCKET CTcpConnection::GetSendSocket()
	{
		if (m_peerSocket == NULL)//��ʾ��ǰ��������tcp�ͻ�������
		{
			return m_localSocket;
		}
		else//��ʾ��ǰ��������tcp���������
		{
			return m_peerSocket;
		}
	}

	bool CTcpConnection::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool result = m_socketAPI.Send(GetSendSocket(), buf, len, actualLen);

		//�����������ݽ������
		SendPeerDataResult data;
		data.success = result;
		data.len = len;
		data.peer = m_peerSocket;
		if (m_peerSocket == NULL)//��ʾ��ǰ��������tcp�ͻ�������
		{

		}
		else
		{
			PeerSocketData peerData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(m_peerSocket);//��ȡ�Զ�socket����
			strcpy(data.ip, peerData.ip);
			data.port = peerData.port;
		}
		CSendPeerDataResultAction* pAction = new CSendPeerDataResultAction(data, m_localSocket);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		if (!result)//����ʧ��
		{
			if (m_pTcpSrv != NULL && m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)//ָʾtcp����˶���
			{
				CNetworkCommuMgr::GetSelect()->RemoveSocket(m_peerSocket);//��select���Ƴ��Զ�socket
			}
			else
			{

			}
		}
		return result;
	}

	void CTcpConnection::OnRecvPeerData(SocketRecvData data)
	{
		//����
		CRecvPeerDataAction* pAction = new CRecvPeerDataAction(data, m_localSocket);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);
	}

	void CTcpConnection::OnPeerClose(SOCKET peer)
	{
		//����tcp����: �Զ������ر�
		CPeerCloseAction* pAction = new CPeerCloseAction(m_localSocket, peer);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		CNetworkCommuMgr::GetTcpConnectionMgr()->OnPeerClose(peer);//֪ͨtcp���ӹ���,�Զ������ر�
	}

	SOCKET CTcpConnection::GetLocalSocket()
	{
		return m_localSocket;
	}

	SOCKET CTcpConnection::GetPeerSocket()
	{
		return m_peerSocket;
	}
}