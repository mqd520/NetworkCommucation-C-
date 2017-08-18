#include "stdafx.h"
#include "TcpServiceMgr.h"
#include "NetCommuMgr.h"
#include "RecvNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	CTcpServiceMgr::CTcpServiceMgr()
	{

	}

	CTcpServiceMgr::~CTcpServiceMgr()
	{

	}

	void CTcpServiceMgr::PushTcpService(CTcpService* srv)
	{
		m_vecTcpService.push_back(srv);
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

	void CTcpServiceMgr::OnRecvNewConnection(CRecvNewConnAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			//找到对应的tcp服务端对象,只有tcp服务端对象才能处理此动作
			if (srv->GetSrvType() == ETcpServiceType::Server && srv->GetLocalSocket() == pAction->GetServerSocket())
			{
				ServerSocket sData = srv->GetServerSocketData();//获取服务端socket数据
				//获取服务端客户端socket数据
				ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(pAction->GetServerClientSocket());
				PrintfDebug("[%s:%d] recv a new connection [%s:%d], socket: %d,%d", sData.ip, sData.port, scData.ip, scData.port, sData.socket, scData.client);
				srv->OnRecvNewConnection(sData, scData);//通知tcp服务端对象处理动作
			}
		}
	}

	//void CTcpServiceMgr::OnRecvPeerData(CRecvPeerDataAction* pAction)
	//{
	//	for (int i = 0; i < (int)m_vecTcpService.size(); i++)
	//	{
	//		CTcpService* srv = m_vecTcpService[i];
	//		if (srv->GetLocalSocket() == pAction->GetLocalSocket())//找到对应的tcp服务对象
	//		{
	//			srv->OnRecvPeerData(pAction->GetPeerData());//通知tcp服务对象处理动作
	//			break;
	//		}
	//	}
	//}

	void CTcpServiceMgr::OnPeerClose(CPeerCloseAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//找到对应的tcp服务对象
			{
				//ServerClientSocket data = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(pAction->GetMapSocket());
				//srv->OnPeerCloseSocket(data);//通知tcp服务对象处理动作
				break;
			}
		}
	}

	void CTcpServiceMgr::OnSendPeerDataCompleted(CSendPeerDataResultAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//找到对应的tcp服务对象
			{
				SendPeerDataResult result = pAction->GetResult();//获取结果
				srv->OnSendPeerDataCompleted(result);//通知tcp服务对象处理动作
				break;
			}
		}
	}
}