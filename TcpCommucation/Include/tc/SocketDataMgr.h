#pragma once

#include <WinSock2.h>
#include <vector>
#include <queue>
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// socket数据管理类
	class SocketDataMgr
	{
	public:
		SocketDataMgr();
		~SocketDataMgr();

	private:
		vector<SocketInfoData> vecSocketData;	// socket数据集合
		CThreadLock lock1;						// 线程锁, 针对: vecSocketData

		queue<SOCKET> quRemovedSockets;			// removed sockets

	private:
		//************************************
		// Method:    创建一个socket id
		//************************************
		int CreateSocketId(SOCKET socket);

	public:
		//************************************
		// Method:    添加一个socket
		// Parameter: SOCKET socket:	socket
		// Parameter: ESocketType type:	socket类型
		// Parameter: bEnable: 是否立即启用
		//************************************
		void Add(SOCKET socket, ESocketType type, bool bEnable = true);

		//************************************
		// Method:    移除一个socket
		// Parameter: SOCKET socket:	socket
		//************************************
		SocketInfoData Remove(SOCKET socket);

		//************************************
		// Method:    移除一个socket
		// Parameter: SOCKET socket:	socket
		// Parameter: ESocketType type:	socket type
		//************************************
		SocketInfoData Remove(SOCKET socket, ESocketType type);

		//************************************
		// Method:    清除所有socket
		//************************************
		void Clear();

		//************************************
		// Method:    获取指定类型的socket数据集合
		// Parameter: ESocketType type:	socket类型
		//************************************
		vector<SOCKET> GetSocketData(ESocketType type);

		//************************************
		// Method:    获取所有socket数据
		//************************************
		vector<SocketInfoData> GetSocketData();

		//************************************
		// Method:    获取socket data
		//************************************
		SocketInfoData GetSocketData(SOCKET socket);

		//************************************
		// Method:    获取socket data
		//************************************
		SocketInfoData GetSocketData(int socketId);

		//************************************
		// Method:    获取指定socket的类型
		// Parameter: SOCKET socket:	socket
		//************************************
		ESocketType GetSocketType(SOCKET socket);

		//************************************
		// Method:    Enable Socket
		// Parameter: SOCKET socket
		// Parameter: bool bEnable
		//************************************
		void EnableSocket(SOCKET socket, bool bEnable = true);

		void ProcessRemovedSocket();
	};
}