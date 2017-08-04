#include "stdafx.h"
#include "ServerSocketMgr.h"

namespace NetworkCommunication
{
	CServerSocketMgr::CServerSocketMgr()
	{

	}

	CServerSocketMgr::~CServerSocketMgr()
	{

	}

	void CServerSocketMgr::Push(ServerSocketData data)
	{
		m_vecData.push_back(data);
	}

	ServerSocketData CServerSocketMgr::GetDataBySocket(SOCKET socket)
	{
		ServerSocketData result = { 0 };
		for (int i = 0; i < m_vecData.size();i++)
		{
			if (m_vecData[i].socket == socket)
			{
				result = m_vecData[i];
				break;
			}
		}
		return result;
	}
}