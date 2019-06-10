#pragma once

#include <WinSock2.h>
#include <vector>
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
		vector<SelectSocketData> vecSocketData;	// socket数据集合
		CThreadLock lock1;	// 线程锁, 针对: vecSocketData

	public:
		//************************************
		// Method:    添加一个socket
		// Parameter: SOCKET socket:	socket
		// Parameter: ESocketType type:	socket类型
		//************************************
		void Add(SOCKET socket, ESocketType type);

		//************************************
		// Method:    移除一个socket
		// Parameter: SOCKET socket:	socket
		//************************************
		void Remove(SOCKET socket);

		//************************************
		// Method:    清除所有socket
		//************************************
		void Clear();

		//************************************
		// Method:    获取指定类型的socket数据集合
		// Parameter: ESocketType type:	socket类型
		//************************************
		vector<SOCKET> GetSocket(ESocketType type);

		//************************************
		// Method:    获取所有socket数据
		//************************************
		vector<SelectSocketData> GetSocket();

		//************************************
		// Method:    获取指定socket的类型
		// Parameter: SOCKET socket:	socket
		//************************************
		ESocketType GetSocketType(SOCKET socket);
	};
}