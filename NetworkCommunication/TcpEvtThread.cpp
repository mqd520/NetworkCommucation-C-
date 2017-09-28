#include "stdafx.h"
#include "TcpEvtThread.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "TcpEvtMgr.h"
#include <tchar.h>

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
		PrintfInfo(_T("Tcp event thread run"));

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