#include "stdafx.h"
#include "SocketDataMgr.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	SocketDataMgr::SocketDataMgr()
	{

	}

	SocketDataMgr::~SocketDataMgr()
	{

	}

	int SocketDataMgr::CreateSocketId(SOCKET socket)
	{
		return ((int)(socket << 16)) | socket;
	}

	void SocketDataMgr::Add(SOCKET socket, ESocketType type)
	{
		lock1.Lock();

		bool b = false;
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			int socketId = CreateSocketId(socket);
			int peerPort = 0;
			string peerIp = SocketTool::GetPeerIpAndPort(socket, &peerPort);

			vecSocketData.push_back({ socket, type, peerIp, peerPort, "", 0, socketId });
		}

		lock1.Unlock();
	}

	void SocketDataMgr::Remove(SOCKET socket)
	{
		lock1.Lock();

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket)
			{
				vecSocketData.erase(it);
				break;
			}
		}

		lock1.Unlock();
	}

	void SocketDataMgr::Remove(SOCKET socket, ESocketType type)
	{
		lock1.Lock();

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
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

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			SocketTool::ShutDown(it->socket, false);
			SocketTool::CloseSocket(it->socket, false);
		}
		vecSocketData.clear();

		lock1.Unlock();
	}

	vector<SOCKET> SocketDataMgr::GetSocketData(ESocketType type)
	{
		lock1.Lock();

		vector<SOCKET> vec;
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->type == type)
			{
				vec.push_back(it->socket);
			}
		}

		lock1.Unlock();

		return vec;
	}

	vector<SocketInfoData> SocketDataMgr::GetSocketData()
	{
		lock1.Lock();

		vector<SocketInfoData> vec;
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			vec.push_back(*it);
		}

		lock1.Unlock();

		return vec;
	}

	SocketInfoData SocketDataMgr::GetSocketData(SOCKET socket)
	{
		lock1.Lock();

		SocketInfoData data = { 0 };
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket)
			{
				data = *it;
				break;
			}
		}

		lock1.Unlock();

		return data;
	}

	SocketInfoData SocketDataMgr::GetSocketData(int socketId)
	{
		lock1.Lock();

		SocketInfoData data = { 0 };
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socketId == socketId)
			{
				data = *it;
				break;
			}
		}

		lock1.Unlock();

		return data;
	}

	ESocketType SocketDataMgr::GetSocketType(SOCKET socket)
	{
		lock1.Lock();

		ESocketType type = ESocketType::Accept;
		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
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