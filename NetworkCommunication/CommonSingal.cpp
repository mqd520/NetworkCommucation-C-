#include "stdafx.h"
#include "CommonSingal.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"
#include "TcpServer.h"

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
					pSrv->GetLocalIP(), pSrv->GetLocalPort(), pSrv->GetSocket(), ip, port, client);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRefuseNewConnEvt(pSrv, client, ip, port));
			}
			else
			{
				PrintfInfo(_T("[%s:%d][socket: %d] recv a new connection [%s:%d][socket: %d]"),
					pSrv->GetLocalIP(), pSrv->GetLocalPort(), pSrv->GetSocket(), ip, port, client);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CRecvNewConnEvt(pSrv, client));
			}
		}
	}
}