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
			//�ҵ���Ӧ��tcp����˶���,ֻ��tcp����˶�����ܴ���˶���
			if (srv->GetSrvType() == ETcpServiceType::Server && srv->GetLocalSocket() == pAction->GetServerSocket())
			{
				ServerSocket sData = srv->GetServerSocketData();//��ȡ�����socket����
				//��ȡ����˿ͻ���socket����
				ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(pAction->GetServerClientSocket());
				PrintfDebug("[%s:%d] recv a new connection [%s:%d], socket: %d,%d", sData.ip, sData.port, scData.ip, scData.port, sData.socket, scData.client);
				srv->OnRecvNewConnection(sData, scData);//֪ͨtcp����˶�������
			}
		}
	}

	//void CTcpServiceMgr::OnRecvPeerData(CRecvPeerDataAction* pAction)
	//{
	//	for (int i = 0; i < (int)m_vecTcpService.size(); i++)
	//	{
	//		CTcpService* srv = m_vecTcpService[i];
	//		if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
	//		{
	//			srv->OnRecvPeerData(pAction->GetPeerData());//֪ͨtcp�����������
	//			break;
	//		}
	//	}
	//}

	void CTcpServiceMgr::OnPeerClose(CPeerCloseAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
			{
				//ServerClientSocket data = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(pAction->GetMapSocket());
				//srv->OnPeerCloseSocket(data);//֪ͨtcp�����������
				break;
			}
		}
	}

	void CTcpServiceMgr::OnSendPeerDataCompleted(CSendPeerDataResultAction* pAction)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			CTcpService* srv = m_vecTcpService[i];
			if (srv->GetLocalSocket() == pAction->GetLocalSocket())//�ҵ���Ӧ��tcp�������
			{
				SendPeerDataResult result = pAction->GetResult();//��ȡ���
				srv->OnSendPeerDataCompleted(result);//֪ͨtcp�����������
				break;
			}
		}
	}
}