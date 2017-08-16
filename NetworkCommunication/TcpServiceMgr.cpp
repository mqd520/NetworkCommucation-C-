#include "stdafx.h"
#include "TcpServiceMgr.h"
#include "NetCommuMgr.h"
#include "AcceptNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnTcpActionThreadStart();//tcp动作线程入口

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
			CNetworkCommuMgr::GetAccept()->Run();//只会启动一次
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
			CTcpAction* pAction = m_tcpAction.front();//取出tcp动作
			m_tcpAction.pop();

			switch (pAction->GetActionType())//判断tcp动作类型
			{
			case ETcpActionType::AcceptNewConnection://接收到新客户端连接
				ProcessAcceptNewConnAction((CAcceptNewConnAction*)pAction);
				break;
			case ETcpActionType::PeerClose://对端主动关闭
				ProcessPeerCloseAction((CPeerCloseAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://收到对端socket数据
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
			if (srv->GetSrvType() == ETcpServiceType::Server)//服务端对象才能处理此动作
			{
				ServerSocketData serverSocketData = srv->GetServerSocketData();//获取服务端socket数据
				if (serverSocketData.socket == pAction->GetLocalSocket())//找到对应的tcp服务端对象
				{
					PeerSocketData clientSocketData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(pAction->GetPeerSocket());//获取对端socket数据
					srv->OnRecvNewConnection(serverSocketData, clientSocketData);//通知tcp服务端对象处理动作
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