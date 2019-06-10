#include "stdafx.h"
#include "SocketDataMgr.h"

namespace tc
{
	SocketDataMgr::SocketDataMgr()
	{

	}

	SocketDataMgr::~SocketDataMgr()
	{

	}

	void SocketDataMgr::Add(SOCKET socket, ESocketType type)
	{
		lock1.Lock();

		bool b = false;
		for (vector<SelectSocketData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			vecSocketData.push_back({ socket, type });
		}

		lock1.Unlock();
	}

	void SocketDataMgr::Remove(SOCKET socket)
	{
		lock1.Lock();

		for (vector<SelectSocketData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket)
			{
				vecSocketData.erase(it);
				break;
			}
		}

		lock1.Unlock();
	}

	void SocketDataMgr::Clear()
	{
		lock1.Lock();

		vecSocketData.clear();

		lock1.Unlock();
	}

	vector<SOCKET> SocketDataMgr::GetSocket(ESocketType type)
	{
		lock1.Lock();

		vector<SOCKET> vec;
		for (vector<SelectSocketData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->type == type)
			{
				vec.push_back(it->socket);
			}
		}

		lock1.Unlock();

		return vec;
	}

	vector<SelectSocketData> SocketDataMgr::GetSocket()
	{
		lock1.Lock();

		vector<SelectSocketData> vec;
		for (vector<SelectSocketData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			vec.push_back(*it);
		}

		lock1.Unlock();

		return vec;
	}

	ESocketType SocketDataMgr::GetSocketType(SOCKET socket)
	{
		lock1.Lock();

		ESocketType type = ESocketType::Accept;
		for (vector<SelectSocketData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket)
			{
				type = it->type;
				break;
			}
		}

		lock1.Unlock();

		return type;
	}
}