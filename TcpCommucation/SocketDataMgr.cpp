#include "stdafx.h"
#include "Include/tc/SocketDataMgr.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/TcpService.h"
#include "Include/tc/TcpCommuMgr.h"
#include <assert.h>

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
			string peerIp = "";

			if (type == ESocketType::SendRecvData)
			{
				peerIp = SocketTool::GetPeerIpAndPort(socket, &peerPort);
			}

			vecSocketData.push_back({ socket, type, peerIp, peerPort, "", 0, socketId });
		}

		lock1.Unlock();
	}

	SocketInfoData SocketDataMgr::Remove(SOCKET socket)
	{
		SocketInfoData data = { 0 };

		lock1.Lock();

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket)
			{
				data = *it;
				vecSocketData.erase(it);
				break;
			}
		}

		lock1.Unlock();

		quRemovedSockets.push(data.socket);

		return data;
	}

	SocketInfoData SocketDataMgr::Remove(SOCKET socket, ESocketType type)
	{
		SocketInfoData data = { 0 };

		lock1.Lock();

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				data = *it;
				vecSocketData.erase(it);
				break;
			}
		}

		lock1.Unlock();

		quRemovedSockets.push(data.socket);

		return data;
	}

	void SocketDataMgr::Clear()
	{
		lock1.Lock();

		for (vector<SocketInfoData>::iterator it = vecSocketData.begin(); it != vecSocketData.end(); it++)
		{
			quRemovedSockets.push(it->socket);
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

	void SocketDataMgr::ProcessRemovedSocket()
	{
		while (!quRemovedSockets.empty())
		{
			SOCKET el = quRemovedSockets.front();

			assert(!quRemovedSockets.empty());
			quRemovedSockets.pop();

			SocketTool::ShutDown(el, 2, false);
			SocketTool::CloseSocket(el, false);
		}
	}
}