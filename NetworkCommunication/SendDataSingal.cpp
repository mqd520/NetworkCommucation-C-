#include "stdafx.h"
#include "SendDataSingal.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CSendDataSingal::CSendDataSingal()
	{

	}

	CSendDataSingal::~CSendDataSingal()
	{

	}

	void CSendDataSingal::ProcessWriteSingal(SOCKET socket, int type)
	{
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->AsyncSendData();
		}
		else
		{
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);//ÒÆ³ıselectÖĞÖ¸¶¨socket
		}
	}
}