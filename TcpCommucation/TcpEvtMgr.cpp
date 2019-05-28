#include "stdafx.h"
#include "TcpEvtMgr.h"
#include "TcpService.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	CTcpEvtMgr::CTcpEvtMgr()
	{

	}

	CTcpEvtMgr::~CTcpEvtMgr()
	{
		while (m_queueEvent.size() > 0)
		{
			TcpEvt* pEvent = m_queueEvent.front();
			m_queueEvent.pop();

			delete pEvent;
		}
	}

	bool CTcpEvtMgr::IsEmpty()
	{
		return m_queueEvent.size() == 0;
	}

	void CTcpEvtMgr::PushTcpEvent(TcpEvt* pEvent)
	{
		m_queueEvent.push(pEvent);
	}

	void CTcpEvtMgr::ProcessTcpEvt()
	{
		while (m_queueEvent.size() > 0)
		{
			if (CTcpCommuMgr::IsExited())//指示需要退出了
			{
				break;
			}

			TcpEvt* pEvent = m_queueEvent.front();
			m_queueEvent.pop();

			TcpService* pSrv = pEvent->GetTcpSrv();
			if (pSrv)
			{
				pSrv->OnRecvTcpEvent(pEvent);
			}

			delete pEvent;
		}
	}
}