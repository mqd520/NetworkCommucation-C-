#include "stdafx.h"
#include "TcpEvtMgr.h"
#include "TcpService.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	TcpEvtMgr::TcpEvtMgr()
	{

	}

	TcpEvtMgr::~TcpEvtMgr()
	{
		while (queueEvent.size() > 0)
		{
			TcpEvt* pEvent = queueEvent.front();
			queueEvent.pop();

			delete pEvent;
		}
	}

	bool TcpEvtMgr::IsEmpty()
	{
		return queueEvent.size() == 0;
	}

	void TcpEvtMgr::PushTcpEvent(TcpEvt* pEvent)
	{
		queueEvent.push(pEvent);
	}

	void TcpEvtMgr::ProcessTcpEvt()
	{
		while (queueEvent.size() > 0)
		{
			if (CTcpCommuMgr::IsExited())//指示需要退出了
			{
				break;
			}

			TcpEvt* pEvent = queueEvent.front();
			queueEvent.pop();

			TcpService* pSrv = pEvent->GetTcpSrv();
			if (pSrv)
			{
				pSrv->OnRecvTcpEvent(pEvent);
			}

			delete pEvent;
		}
	}
}