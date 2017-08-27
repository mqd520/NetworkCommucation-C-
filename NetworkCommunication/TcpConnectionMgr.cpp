#include "stdafx.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	CTcpConnectionMgr::CTcpConnectionMgr()
	{

	}

	CTcpConnectionMgr::~CTcpConnectionMgr()
	{

	}

	void CTcpConnectionMgr::PushTcpConn(CTcpConnection* conn)
	{
		m_vecTcpConnection.push_back(conn);
	}

	CTcpConnection* CTcpConnectionMgr::GetBySendRecvSocket(SOCKET sendrecv)
	{
		for (int i = 0; i < (int)m_vecTcpConnection.size(); i++)
		{
			if (m_vecTcpConnection[i]->GetSendRecvSocket() == sendrecv)
			{
				return m_vecTcpConnection[i];
			}
		}
		return NULL;
	}

	void CTcpConnectionMgr::RemoveBySendRecvSocket(SOCKET socket)
	{
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it < m_vecTcpConnection.end(); it++)
		{
			if ((*it)->GetSendRecvSocket() == socket)
			{
				m_vecTcpConnection.erase(it);
				break;
			}
		}
	}
}