#pragma once
#include <vector>
#include <queue>
#include "Def.h"
#include "TcpConnection.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// tcp连接管理类
	class TcpConnectionMgr
	{
	public:
		TcpConnectionMgr();
		~TcpConnectionMgr();

	private:
		vector<CTcpConnection*> vecTcpConn;//tcp连接集合
		CThreadLock m_lock;

	public:
		//************************************
		// Method:    增加一个tcp连接
		//************************************
		void PushTcpConn(CTcpConnection* conn);

		//************************************
		// Method:    移除指定收发数据的socket关联的tcp连接对象
		// Parameter: 收发数据的socket
		//************************************
		void RemoveBySendRecvSocket(SOCKET socket);

		//************************************
		// Method:    获取指定收(发)数据的socket关联的tcp连接对象
		// Parameter: 收(发)数据的socket
		// Return:	  tcp连接对象
		//************************************
		CTcpConnection* GetBySendRecvSocket(SOCKET sendrecv);

		//************************************
		// Method:    清除所有连接对象
		//************************************
		void Clear();

		//************************************
		// Method:    获取连接总数
		//************************************
		int Count();
	};
}