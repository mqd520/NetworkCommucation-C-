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
			}
		}
	}

	void CTcpServiceMgr::ProcessAcceptNewConnAction(CAcceptNewConnAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetSrvType() == ETcpServiceType::Server)//����˶�����ܴ���˶���
			{
				ServerSocketData serverSocketData = srv->GetServerSocketData();//��ȡ�����socket����
				if (serverSocketData.socket == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp����˶���
				{
					PeerSocketData clientSocketData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());//��ȡ�Զ�socket����
					srv->OnRecvNewConnection(serverSocketData, clientSocketData);//֪ͨtcp����˶�������
				}
			}
		}
	}

	void CTcpServiceMgr::ProcessPeerCloseAction(CPeerCloseAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			PeerSocketData data = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());
			srv->OnPeerCloseSocket(data);
		}
	}

	void CTcpServiceMgr::ProcessRecvPeerDataAction(CRecvPeerDataAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			PeerSocketData data = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());
		}
	}

	bool CTcpServiceMgr::IsHasServer()
	{
		bool flag = false;
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			if (m_vecTcpService[i]->GetSrvType() == ETcpServiceType::Server)
			{
				flag = true;
				break;
			}
		}
		return flag;
	}
}