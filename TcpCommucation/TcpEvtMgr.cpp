#include "stdafx.h"
#include "Include/tc/TcpEvtMgr.h"
#include "Include/tc/TcpService.h"
#include "Include/tc/TcpCommuMgr.h"
#include <assert.h>

namespace tc
{
	TcpEvtMgr::TcpEvtMgr()
	{

	}

	TcpEvtMgr::~TcpEvtMgr()
	{
		Clear();
	}

	bool TcpEvtMgr::IsEmpty()
	{
		return queueEvent.size() == 0;
	}

	void TcpEvtMgr::PushTcpEvent(TcpEvt* pEvent)
	{
		queueEvent.push(pEvent);
	}

	void TcpEvtMgr::Clear()
	{
		while ((int)queueEvent.size() > 0)
		{
			TcpEvt* pEvent = queueEvent.front();
			queueEvent.pop();
			delete pEvent;
		}
	}

	void TcpEvtMgr::ProcessTcpEvt()
	{
		while ((int)queueEvent.size() > 0)
		{
			TcpEvt* pEvent = queueEvent.front();
			assert(!queueEvent.empty());
			queueEvent.pop();

			TcpService* pSrv = pEvent->GetTcpSrv();
			if (pSrv)
			{
				pSrv->OnTcpEvt(pEvent);
			}

			delete pEvent;
		}
	}
}