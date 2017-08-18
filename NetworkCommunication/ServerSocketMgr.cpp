#include "stdafx.h"
#include "ServerSocketMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CServerSocketMgr::CServerSocketMgr()
	{

	}

	CServerSocketMgr::~CServerSocketMgr()
	{

	}

	ServerSocket CServerSocketMgr::Create(char* ip, int port, SOCKET socket, void* server)
	{
		CSocketAPI api;
		ServerSocket data = { 0 };
		strcpy(data.ip, ip);
		data.port = port;
		data.addr = api.GetSocketAddr(data.ip, data.port);
		data.tcpServer = server;
		data.socket = socket;
		CNetworkCommuMgr::GetServerSocketMgr()->PushServerSocketData(data);
		return data;
	}

	void CServerSocketMgr::PushServerSocketData(ServerSocket data)
	{
		m_vecData.push_back(data);
	}

	ServerSocket CServerSocketMgr::GetDataBySocket(SOCKET socket)
	{
		ServerSocket result = { 0 };
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

	ServerSocket CServerSocketMgr::GetDataByServer(void* server)
	{
		ServerSocket result = { 0 };
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