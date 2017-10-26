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
		if (type == ESelectSocketType::RecvConn)//指示socket用于接收新连接
		{
			OnRecvNewConn(socket);
		}
	}

	void CCommonSingal::ProcessWriteSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//指示socket用于连接服务端,表示连接已建立
		{
			//获取服务端socket关联的tcp服务对象
			CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
			if (pSrv)
			{
				//连接成功后,不再需要监听是否已连接上服务端
				CNetworkCommuMgr::GetSelect()->RemoveSocket(socket, false);

				//创建连接完成事件
				CConnectCmpEvt* pEvent = new CConnectCmpEvt(pSrv, true);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);

				//建立tcp连接
				CClientTcpConnection* pConn = new CClientTcpConnection(pSrv, socket);
				CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(pConn);

				//客户端socket立刻转变为收发数据的socket
				CNetworkCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::ReadWriteData);
			}
		}
	}

	void CCommonSingal::ProcessExceptSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::Connect)//指示socket用于连接服务端,表示连接失败了
		{
			//获取服务端socket关联的tcp服务对象
			CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
			if (pSrv)
			{
				//创建连接完成事件
				CConnectCmpEvt* pEvent = new CConnectCmpEvt(pSrv, false);
				CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
			}
		}
	}

	void CCommonSingal::OnRecvNewConn(SOCKET socket)
	{
		//获取服务端socket关联的tcp服务对象
		CTcpService* pSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(socket);
		if (pSrv)
		{
			CTcpServer* pServer = (CTcpServer*)pSrv;
			SOCKET client = m_socketAPI.Accept(socket, pServer->GetServerSocketAddr());

			//获取客户端IP
			TCHAR ip[NETCOMM_MAXIPSTRELN];
			int port = 0;
			m_socketAPI.GetPeerIpAndPort(client, ip, &port);

			//判断客户端IP是否被服务端允许
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