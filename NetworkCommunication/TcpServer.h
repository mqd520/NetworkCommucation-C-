#pragma once

#include "SocketMgr.h"
#include "TcpSessionMgr.h"

namespace NetworkCommunication
{
	//tcp服务端
	class CTcpServer
	{
	protected:
		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//线程句柄
			DWORD dwThreadID;//线程ID
			bool bPause;//是否暂停
		}ThreadInfo, *LPThreadInfo;

	protected:
		CSocketMgr m_socketMgr;//socket管理对象
		TCHAR m_strServerIP[20];//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bInited;//是否已初始化
		SOCKET m_serverSocket;
		bool m_bListening;//是否正在监听
		ThreadInfo m_tiAccept;//接受客户端连接线程信息
		CTcpSessionMgr m_sessionMgr;//tcp会话管理
		int m_nMaxConnectionCount;//允许最大客户端连接计数,0:无限制
		int m_nConnectedCount;//已连接客户端计数
		ThreadInfo m_tiSelect;//
		FD_SET m_fdRead;//

	protected:
		void CleanThread();

	public:
		CTcpServer();
		~CTcpServer();

		void Init(TCHAR* ip, int port, int maxConn = 0);
		void Listen();

		//不需要调用
		void StartAccept();
		void StartSelect();
	};
}