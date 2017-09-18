#include "stdafx.h"
#include "TcpSessionDataMgr.h"

CTcpDataSessionDataMgr::CTcpDataSessionDataMgr()
{

}

CTcpDataSessionDataMgr::~CTcpDataSessionDataMgr()
{

}

int CTcpDataSessionDataMgr::Push(TcpSessionData data)
{
	m_vec.push_back(data);
	int index = m_vec.size() - 1;
	if (index < 0)
	{
		index = 0;
	}
	return index;
}

TcpSessionData CTcpDataSessionDataMgr::GetDataByIndex(int index)
{
	return m_vec[index];
}

int CTcpDataSessionDataMgr::RemoveByClientSocket(SOCKET client)
{
	int index = -1;
	int i = 0;
	for (vector<TcpSessionData>::iterator it = m_vec.begin(); it < m_vec.end(); it++)
	{
		if (it->client == client)
		{
			m_vec.erase(it);
			index = i;
			break;
		}
		i++;
	}
	return index;
}