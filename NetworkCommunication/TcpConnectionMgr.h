#pragma once
#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include "Def.h"
#include <queue>

using namespace std;

namespace NetworkCommunication
{
	//tcp连接管理对象
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<CTcpConnection*> m_vecTcpConnection;//tcp连接集合
		CThread* m_threadRW;//读写线程
		queue<SocketRecvData> m_quSocketSendRecvData;//socket发送接收数据队列

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		//线程入口
		void ThreadEntry();

		//启动线程
		void Run();

		//增加一个tcp连接
		void PushTcpConn(CTcpConnection* session);

		//************************************
		// Method:    移除指定对端socket的tcp连接对象
		// Parameter: 对端socket
		//************************************
		void RemoveTcpConnByPeerSocket(SOCKET peer);

		//************************************
		// Method:    对端socket有数据可读事件处理
		// Parameter: 对端socket
		//************************************
		void OnPeerSocketCanRead(SOCKET peer);

		//************************************
		// Method:    通过对端socket获取tcp连接对象
		// Parameter: 对端socket
		// Return:	  tcp连接对象
		//************************************
		CTcpConnection* GetTcpConnByPeerSocket(SOCKET peer);

		//对端主动关闭事件处理
		void OnPeerClose(SOCKET peer);

		void UnAsyncSend(SOCKET socket, BYTE buf[], int len, int* actualLen);
	};
}