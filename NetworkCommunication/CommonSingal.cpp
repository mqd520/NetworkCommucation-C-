#include "stdafx.h"
#include "CommonSingal.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"
#include "ConnectCmpEvt.h"
#include "TcpServer.h"
#include "TcpConnectionMgr.h"
#include "ClientTcpConnection.h"

namespace NetworkCommunication
{
	CCommonSingal::CCommonSingal()
	{

	}

	CCommonSingal::~CCommonSingal()
	{

	}

	void CCommonSingal::ProcessReadSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::RecvConn)//ָʾsocket���ڽ���������
		{
			OnRecvNewConn(socket);
		}
	}

	void CCommonSingal::ProcessWriteSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//ָʾsocket�������ӷ����,��ʾ�����ѽ���
		{
			//��ȡ�����socket������tcp�������
			CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
			if (pSrv)
			{
				//���ӳɹ���,������Ҫ�����Ƿ��������Ϸ����
				CNetworkCommuMgr::GetSelect()->RemoveSocket(socket, false);

				//������������¼�
				CConnectCmpEvt* pEvent = new CConnectCmpEvt(pSrv, true);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

				//����tcp����
				CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
				CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

				//�ͻ���socket����ת��Ϊ�շ����ݵ�socket
				CNetworkCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::ReadWriteData);
			}
		}
	}

	void CCommonSingal::ProcessExceptSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//ָʾsocket�������ӷ����,��ʾ����ʧ����
		{
			//��ȡ�����socket������tcp�������
			CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
			if (pSrv)
			{
				//������������¼�
				CConnectCmpEvt* pEvent = new CConnectCmpEvt(pSrv, false);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
			}
		}
	}

	void CCommonSingal::OnRecvNewConn(SOCKET socket)
	{
		//��ȡ�����socket������tcp�������
		CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			CTcpServer* pServer = (CTcpServer*)pSrv;
			SOCKET client = m_socketAPI.Accept(socket, pServer->GetServerSocketAddr());

			//��ȡ�ͻ���IP
			TCHAR ip[NETCOMM_MAXIPSTRELN];
			int port = 0;
			m_socketAPI.GetPeerIpAndPort(client, ip, &port);

			//�жϿͻ���IP�Ƿ񱻷��������
			if (!pServer->IsAllow(ip))
			{
				m_socketAPI.CloseSocket(client);

				PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
					pSrv->GetServerIP(), pSrv->GetServerPort(), pSrv->GetSocket(), ip, port, client);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRefuseNewConnEvt(pSrv, client, ip, port));
			}
			else
			{
				PrintfInfo(_T("[%s:%d][socket: %d] recv a new connection [%s:%d][socket: %d]"),
					pSrv->GetServerIP(), pSrv->GetServerPort(), pSrv->GetSocket(), ip, port, client);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRecvNewConnEvt(pSrv, client));
			}
		}
	}
}