#pragma once

#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include <queue>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<CTcpConnection*> m_vecTcpConnection;//tcp连接集合
		CThread* m_threadRW;//读写线程
		queue<SocketRecvData> m_quSocketRecvData;//socket接收数据队列

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		void PushTcpConn(CTcpConnection* session);

		void RemoveByPeer(SOCKET peer);

		//************************************
		// Method:    socket有数据可读
		// Parameter: SOCKET socket
		//************************************
		void OnSocketCanRead(SOCKET socket);

		void ThreadEntry();

		void Run();

		//************************************
		// Method:    通过对端socket获取tcp连接对象
		// Parameter: 对端socket
		// Return:	  tcp连接对象
		//************************************
		CTcpConnection* GetTcpConnByPeerSocket(SOCKET peer);

		// 删除指定对端seocket的tcp连接
		void RemoveTcpConnByPeerSocket(SOCKET peer);
	};
}