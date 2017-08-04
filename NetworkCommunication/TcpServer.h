#pragma once

#include "SocketMgr.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	//tcp服务端
	class CTcpServer
	{
	protected:
		CSocketMgr m_socketMgr;//socket管理对象
		TCHAR m_strServerIP[20];//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bInited;//是否已初始化
		SOCKET m_serverSocket;
		bool m_bListening;//是否正在监听
		CTcpConnectionMgr m_sessionMgr;//tcp会话管理
		int m_nMaxConnectionCount;//允许最大客户端连接计数,0:无限制
		int m_nConnectedCount;//已连接客户端计数
		FD_SET m_fdRead;//

	public:
		CTcpServer();
		~CTcpServer();

		void Init(TCHAR* ip, int port, int maxConn = 0);
		bool Listen();
	};
}