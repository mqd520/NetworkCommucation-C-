#include "stdafx.h"
#include "TcpEvtThread.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "TcpEvtMgr.h"

namespace NetworkCommunication
{
	CTcpEvtThread::CTcpEvtThread()
	{

	}

	CTcpEvtThread::~CTcpEvtThread()
	{

	}

	void CTcpEvtThread::OnThreadRun()
	{
		//PrintfInfo(_T(""));

		if (CNetworkCommuMgr::GetTcpEvtMgr()->IsEmpty())
		{
			Sleep(10);
		}
		else
		{
			CNetworkCommuMgr::GetTcpEvtMgr()->ProcessTcpEvt();
		}
	}
}