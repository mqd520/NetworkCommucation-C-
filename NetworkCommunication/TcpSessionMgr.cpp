#include "stdafx.h"
#include "TcpSessionMgr.h"

namespace NetworkCommunication
{
	CTcpSessionMgr::CTcpSessionMgr()
	{

	}

	CTcpSessionMgr::~CTcpSessionMgr()
	{

	}

	void CTcpSessionMgr::Push(CTcpSession session)
	{
		m_vecSessionList.push_back(session);
	}
}