#include "stdafx.h"
#include "TcpEvtMgr.h"
#include "TcpService.h"
#include "NetCommuMgr.h"

namespace tc
{
	CTcpEvtMgr::CTcpEvtMgr()
	{

	}

	CTcpEvtMgr::~CTcpEvtMgr()
	{
		while (m_queueEvent.size() > 0)
		{
			CTcpEvt* pEvent = m_queueEvent.front();
			m_queueEvent.pop();

			delete pEvent;
		}
	}

	bool CTcpEvtMgr::IsEmpty()
	{
		return m_queueEvent.size() == 0;
	}

	void CTcpEvtMgr::PushTcpEvent(CTcpEvt* pEvent)
	{
		m_queueEvent.push(pEvent);
	}

	void CTcpEvtMgr::ProcessTcpEvt()
	{
		while (m_queueEvent.size() > 0)
		{
			if (CNetworkCommuMgr::IsExited())//指示需要退出了
			{
				break;
			}

			CTcpEvt* pEvent = m_queueEvent.front();
			m_queueEvent.pop();

			CTcpService* pSrv = pEvent->GetTcpSrv();
			if (pSrv)
			{
				pSrv->OnRecvTcpEvent(pEvent);
			}

			delete pEvent;
		}
	}
}