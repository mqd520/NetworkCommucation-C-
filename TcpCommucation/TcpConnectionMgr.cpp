#include "stdafx.h"
#include "TcpConnectionMgr.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"

namespace tc
{
	TcpConnectionMgr::TcpConnectionMgr()
	{

	}

	TcpConnectionMgr::~TcpConnectionMgr()
	{
		Clear();
	}

	void TcpConnectionMgr::PushTcpConn(CTcpConnection* conn)
	{
		vecTcpConn.push_back(conn);
	}

	CTcpConnection* TcpConnectionMgr::GetBySendRecvSocket(SOCKET sendrecv)
	{
		for (int i = 0; i < (int)vecTcpConn.size(); i++)
		{
			if (vecTcpConn[i]->GetSendRecvSocket() == sendrecv)
			{
				return vecTcpConn[i];
			}
		}

		return NULL;
	}

	void TcpConnectionMgr::RemoveBySendRecvSocket(SOCKET socket)
	{
		for (vector<CTcpConnection*>::iterator it = vecTcpConn.begin(); it != vecTcpConn.end(); it++)
		{
			CTcpConnection* pConn = *it;
			if (pConn->GetSendRecvSocket() == socket)
			{
				vecTcpConn.erase(it);
				delete pConn;
				break;
			}
		}
	}

	void TcpConnectionMgr::Clear()
	{
		for (vector<CTcpConnection*>::iterator it = vecTcpConn.begin(); it != vecTcpConn.end();)
		{
			CTcpConnection* pConn = *it;
			it = vecTcpConn.erase(it);
			if (pConn)
			{
				delete pConn;
			}
		}
	}

	int TcpConnectionMgr::Count()
	{
		return (int)vecTcpConn.size();
	}
}