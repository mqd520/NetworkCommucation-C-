#pragma once
#include "SocketAPI.h"
#include <queue>
#include "Thread.h"
#include "Def.h"
#include "TcpAction.h"
#include "RecvNewConnAction.h"
#include "RecvPeerDataAction.h"

using namespace std;

namespace NetworkCommunication
{
	//处理tcp动作
	class CTcp
	{
	private:
		queue<CTcpAction*> m_quTcpAction;//tcp动作队列
		CThread* m_threadAccept;//处理新socket连接的线程
		CSocketAPI m_socketAPI;//socket api
		BYTE* m_pBuf;//接收缓冲区指针
		int m_nBufLen;//接收缓冲区字节最大长度

	private:
		//************************************
		// Method:    处理tcp动作队列
		//************************************
		void ProcessQueue();

		//************************************
		// Method:    处理接收新连接动作
		// Parameter: 新连接动作
		//************************************
		void ProcessAcceptNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    处理收到对端数据动作
		// Parameter: 收到对端数据动作
		//************************************
		void ProcessRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    过滤指定客户端连接
		// Returns:   是否继续
		//************************************
		bool FilterClientSocket(SOCKET server, SOCKET client);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    运行处理新连接线程
		//************************************
		void Run();

		//************************************
		// Method:    accept线程入口点
		//************************************
		void ThreadEntry();

		//************************************
		// Method:    服务端socket有数据可读事件处理
		// Parameter: 服务端socket
		//************************************
		void OnServerSocketCanRead(SOCKET server);

		//************************************
		// Method:    读写socket有数据可读事件处理
		// Parameter: 读写socket
		//************************************
		void OnReadWriteSocketCanRead(SOCKET server);
	};
}
