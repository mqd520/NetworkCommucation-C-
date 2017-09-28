#include "stdafx.h"
#include "TcpEvtMgr.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	CTcpEvtMgr::CTcpEvtMgr()
	{

	}

	CTcpEvtMgr::~CTcpEvtMgr()
	{

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