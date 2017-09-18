#include "stdafx.h"
#include "TcpServerMgr.h"

namespace NetworkCommunication
{
	CTcpServerMgr::CTcpServerMgr()
	{
		
	}

	CTcpServerMgr::~CTcpServerMgr()
	{

	}

	void CTcpServerMgr::Push(CTcpServer* tcpserver)
	{
		m_vecTcpServer.push_back(tcpserver);
	}

	CTcpServer* CTcpServerMgr::GetTcpServerByServerSocket(SOCKET server)
	{
		for (int i = 0; i < (int)m_vecTcpServer.size(); i++)
		{
			if (m_vecTcpServer[i]->GetSocket() == server)
			{
				return m_vecTcpServer[i];
			}
		}
		return NULL;
	}
}