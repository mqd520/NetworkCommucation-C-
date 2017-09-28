#include "stdafx.h"
#include "RecvDataSingal.h"
#include "NetCommuMgr.h"
#include "TcpConnection.h"

namespace NetworkCommunication
{
	CRecvDataSingal::CRecvDataSingal()
	{

	}

	CRecvDataSingal::~CRecvDataSingal()
	{

	}

	void CRecvDataSingal::ProcessReadSingal(SOCKET socket, int type)
	{
		if (type == ESelectSocketType::ReadWriteData)
		{
			//��ȡtcp���Ӷ���
			CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
			if (pConn)
			{
				pConn->OnRecvPeerData();
			}
			else
			{
				CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);
			}
		}
	}
}