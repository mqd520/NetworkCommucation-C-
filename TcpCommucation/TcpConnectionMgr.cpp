#include "stdafx.h"
#include "Include/tc/TcpConnectionMgr.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpConnection.h"

namespace tc
{
	TcpConnectionMgr::TcpConnectionMgr()
	{

	}

	TcpConnectionMgr::~TcpConnectionMgr()
	{
		Clear();
	}

	void TcpConnectionMgr::PushTcpConn(TcpConnection* conn)
	{
		vecTcpConn.push_back(conn);
	}

	TcpConnection* TcpConnectionMgr::GetBySendRecvSocket(SOCKET sendrecv)
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

	vector<TcpConnection*> TcpConnectionMgr::GetByTcpService(TcpService* pTcpService)
	{
		vector<TcpConnection*> vec;

		for (vector<TcpConnection*>::iterator it = vecTcpConn.begin(); it != vecTcpConn.end(); it++)
		{
			if ((*it)->GetTcpService() == pTcpService)
			{
				vec.push_back(*it);
				break;
			}
		}

		return vec;
	}

	void TcpConnectionMgr::RemoveBySendRecvSocket(SOCKET socket)
	{
		for (vector<TcpConnection*>::iterator it = vecTcpConn.begin(); it != vecTcpConn.end(); it++)
		{
			TcpConnection* pConn = *it;
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
		for (vector<TcpConnection*>::iterator it = vecTcpConn.begin(); it != vecTcpConn.end();)
		{
			TcpConnection* pConn = *it;
			it = vecTcpConn.erase(it);
			if (pConn)
			{
				delete pConn;
			}
		}
	}

	void TcpConnectionMgr::CreateTcpConnection(SOCKET sendrecv, SOCKET accept /*= NULL*/, bool bEnable /*= true*/)
	{
		TcpService* pSrv = NULL;
		if (accept != NULL)
		{
			pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(accept);
		}
		else
		{
			pSrv = TcpCommu::GetTcpServiceMgr()->GetTcpSrvBySocket(sendrecv);
		}

		if (pSrv)
		{
			TcpConnection* pConn = new TcpConnection(pSrv, sendrecv, bEnable);
			vecTcpConn.push_back(pConn);
		}
	}

	int TcpConnectionMgr::Count()
	{
		return (int)vecTcpConn.size();
	}
}