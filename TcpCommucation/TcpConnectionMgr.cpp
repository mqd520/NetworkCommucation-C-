#include "stdafx.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace tc
{
	CTcpConnectionMgr::CTcpConnectionMgr()
	{

	}

	CTcpConnectionMgr::~CTcpConnectionMgr()
	{
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it != m_vecTcpConnection.end();)
		{
			CTcpConnection* pConn = *it;
			it = m_vecTcpConnection.erase(it);
			if (pConn)
			{
				delete pConn;
			}
		}
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
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it != m_vecTcpConnection.end(); it++)
		{
			CTcpConnection* pConn = *it;
			if (pConn->GetSendRecvSocket() == socket)
			{
				m_vecTcpConnection.erase(it);
				delete pConn;
				break;
			}
		}
	}

	int CTcpConnectionMgr::Count()
	{
		return (int)m_vecTcpConnection.size();
	}
}