#include "stdafx.h"
#include "ServerSocketMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CServerSocketDataMgr::CServerSocketDataMgr()
	{

	}

	CServerSocketDataMgr::~CServerSocketDataMgr()
	{

	}

	ServerSocketData CServerSocketDataMgr::Create(char* ip, int port, SOCKET socket, void* server)
	{
		CSocketAPI api;
		ServerSocketData data = { 0 };
		strcpy(data.ip, ip);
		data.port = port;
		data.addr = api.GetSocketAddr(data.ip, data.port);
		data.tcpServer = server;
		data.socket = socket;
		CNetworkCommuMgr::GetServerSocketMgr()->PushServerSocketData(data);
		return data;
	}

	void CServerSocketDataMgr::PushServerSocketData(ServerSocketData data)
	{
		m_vecData.push_back(data);
	}

	ServerSocketData CServerSocketDataMgr::GetDataBySocket(SOCKET socket)
	{
		ServerSocketData result = { 0 };
		for (int i = 0; i < (int)m_vecData.size(); i++)
		{
			if (m_vecData[i].socket == socket)
			{
				result = m_vecData[i];
				break;
			}
		}
		return result;
	}

	ServerSocketData CServerSocketDataMgr::GetDataByServer(void* server)
	{
		ServerSocketData result = { 0 };
		for (int i = 0; i < (int)m_vecData.size(); i++)
		{
			if (m_vecData[i].tcpServer == server)
			{
				result = m_vecData[i];
				break;
			}
		}
		return result;
	}
}