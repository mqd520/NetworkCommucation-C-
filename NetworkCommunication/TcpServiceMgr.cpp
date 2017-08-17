#include "stdafx.h"
#include "TcpServiceMgr.h"
#include "NetCommuMgr.h"
#include "AcceptNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnTcpActionThreadStart();//tcp�����߳����

	CTcpServiceMgr::CTcpServiceMgr() :
		m_thread(NULL)
	{

	}

	CTcpServiceMgr::~CTcpServiceMgr()
	{

	}

	void CTcpServiceMgr::PushTcpService(CTcpService* srv)
	{
		m_vecTcpService.push_back(srv);
		if (srv->GetSrvType() == ETcpServiceType::Server)
		{
			CNetworkCommuMgr::GetAccept()->Run();//ֻ������һ��
		}
	}

	void CTcpServiceMgr::PushTcpAction(CTcpAction* pAction)
	{
		m_tcpAction.push(pAction);
	}

	void CTcpServiceMgr::Run()
	{
		if (m_thread == NULL)
		{
			m_thread = new CThread();
			m_thread->SetCallback(OnTcpActionThreadStart);
			m_thread->Start();
		}
	}

	void OnTcpActionThreadStart()
	{
		Printf1("Tcp action thread started");
		CNetworkCommuMgr::GetTcpServiceMgr()->ThreadEntry();
	}

	void CTcpServiceMgr::ThreadEntry()
	{
		while (true)
		{
			if (m_tcpAction.size() > 0 && m_vecTcpService.size())
			{
				ProcessTcpAction();
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CTcpServiceMgr::ProcessTcpAction()
	{
		while (m_tcpAction.size() > 0)
		{
			CTcpAction* pAction = m_tcpAction.front();//ȡ��tcp����
			m_tcpAction.pop();

			switch (pAction->GetActionType())//�ж�tcp��������
			{
			case ETcpActionType::AcceptNewConnection://���յ��¿ͻ�������
				ProcessAcceptNewConnAction((CAcceptNewConnAction*)pAction);
				break;
			case ETcpActionType::PeerClose://�Զ������ر�
				ProcessPeerCloseAction((CPeerCloseAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://�յ��Զ�socket����
				ProcessRecvPeerDataAction((CRecvPeerDataAction*)pAction);
				break;
			case ETcpActionType::SendPeerDataResult://�յ��Զ�socket����
				ProcessSendPeerDataResultAction((CSendPeerDataResultAction*)pAction);
				break;
			}

			delete pAction;
		}
	}

	void CTcpServiceMgr::ProcessAcceptNewConnAction(CAcceptNewConnAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetSrvType() == ETcpServiceType::Server && srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp����˶���,ֻ��tcp����˶�����ܴ����˶���
			{
				ServerSocketData serverSocketData = srv->GetServerSocketData();//��ȡ�����socket����
				PeerSocketData clientSocketData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());//��ȡ�Զ�socket����
				srv->OnRecvNewConnection(serverSocketData, clientSocketData);//֪ͨtcp����˶���������
			}
		}
	}

	void CTcpServiceMgr::ProcessPeerCloseAction(CPeerCloseAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
			{
				PeerSocketData data = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());
				srv->OnPeerCloseSocket(data);//֪ͨtcp�������������
				break;
			}
		}
	}

	void CTcpServiceMgr::ProcessRecvPeerDataAction(CRecvPeerDataAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
			{
				PeerSocketData peerSocketData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());//��ȡ�Զ�socket����
				SocketRecvData recvData = pAction->GetRecvData();//��ȡ��������
				srv->OnRecvPeerData(recvData.pBuf, recvData.len, peerSocketData);//֪ͨtcp�������������
				break;
			}
		}
	}

	void CTcpServiceMgr::ProcessSendPeerDataResultAction(CSendPeerDataResultAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
			{
				SendPeerDataResult result = pAction->GetResult();//��ȡ���
				srv->OnSendPeerDataCompleted(result);//֪ͨtcp�������������
				break;
			}
		}
	}

	CTcpService* CTcpServiceMgr::GetTcpSrvByLocalSocket(SOCKET local)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			if (m_vecTcpService[i]->GetLocalSocket() == local)
			{
				return m_vecTcpService[i];
			}
		}
		return NULL;
	}
}