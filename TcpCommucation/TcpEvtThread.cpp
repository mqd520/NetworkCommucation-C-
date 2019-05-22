#include "stdafx.h"
#include "TcpEvtThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"
#include "TcpEvtMgr.h"
#include <tchar.h>

namespace tc
{
	CTcpEvtThread::CTcpEvtThread()
	{

	}

	CTcpEvtThread::~CTcpEvtThread()
	{

	}

	void CTcpEvtThread::Run()
	{
		if (!m_bRun)
		{
			PrintfInfo(_T("Tcp event thread run"));
			__super::Run();
		}
	}

	void CTcpEvtThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetTcpEvtMgr()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CTcpCommuMgr::GetTcpEvtMgr()->ProcessTcpEvt();
		}
	}
}