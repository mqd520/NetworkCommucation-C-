#include "stdafx.h"
#include "TcpServiceMgr.h"
#include "NetCommuMgr.h"
#include "RecvNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	void OnTcpEventThreadStart();

	CTcpServiceMgr::CTcpServiceMgr()
	{
		m_thread = new CThread(this);
	}

	CTcpServiceMgr::~CTcpServiceMgr()
	{

	}

	void OnTcpEventThreadStart()
	{
		CNetworkCommuMgr::GetTcpServiceMgr()->Run();
	}

	void CTcpServiceMgr::Run()
	{
		if (true)
		{
			m_thread->Run();
			PrintfInfo(_T("Tcp event thread started"));
		}
	}

	void CTcpServiceMgr::OnThreadRun()
	{
		if (m_queueEvent.size() > 0)
		{
			ProcessTcpEvent();
		}
		else
		{
			Sleep(5);
		}
	}

	void CTcpServiceMgr::ProcessTcpEvent()
	{
		while (m_queueEvent.size() > 0)
		{
			CTcpSrvEvt* pEvent = m_queueEvent.front();
			m_queueEvent.pop();

			//switch (pEvent->GetEvtType())
			//{
			//case ETcpSrvEvent::RecvNewConnection:
			//	for (int i = 0; i < (int)m_vecTcpService.size(); i++)
			//	{
			//		if (m_vecTcpService[i]->GetSrvType() == ETcpServiceType::Server)//只有服务端对象才能处理的事件
			//		{
			//			//m_vecTcpService[i]->OnRecvTcpEvent(pEvent);
			//		}
			//	}
			//	break;
			//case  ETcpSrvEvent::PeerCloseConn:
			//case  ETcpSrvEvent::AsyncSendDataResult:
			//case  ETcpSrvEvent::RecvPeerData:
			//	for (int i = 0; i < (int)m_vecTcpService.size(); i++)
			//	{
			//		//m_vecTcpService[i]->OnRecvTcpEvent(pEvent);//所有tcp服务对象都可以处理的事件
			//	}
			//	break;
			//}

			CTcpService* pSrv = pEvent->GetTcpSrv();
			pSrv->OnRecvTcpEvent(pEvent);

			delete pEvent;
		}
	}

	void CTcpServiceMgr::PushTcpService(CTcpService* srv)
	{
		m_vecTcpService.push_back(srv);
	}

	void CTcpServiceMgr::PushTcpEvent(CTcpSrvEvt* pEvent)
	{
		m_queueEvent.push(pEvent);
	}

	CTcpService* CTcpServiceMgr::GetTcpSrvBySocket(SOCKET socket)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			if (m_vecTcpService[i]->GetSocket() == socket)
			{
				return m_vecTcpService[i];
			}
		}
		return NULL;
	}
}