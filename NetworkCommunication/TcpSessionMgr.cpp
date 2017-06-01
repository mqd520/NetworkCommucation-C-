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

	void CTcpSessionMgr::OnSelectReturn()
	{
		//for (vector<CTcpSession>::iterator it = m_vecSessionList.begin(); it < m_vecSessionList.end(); it++)
		//{
		//	if (FD_ISSET())
		//	{
		//	}
		//}
	}
}