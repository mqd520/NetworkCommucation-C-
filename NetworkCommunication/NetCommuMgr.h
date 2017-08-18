#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Tcp.h"
#include "ServerSocketMgr.h"
#include "ServerClientSocketMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//线程管理对象
		static CSelect* m_Select;//select对象
		static CTcp* m_tcp;//tcp对象
		static CServerSocketMgr* m_serverSocketMgr;//服务端socket数据管理对象
		static CServerClientSocketMgr* m_serverCLientSocketMgr;//对端socket数据管理对象
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp连接管理对象
		static CTcpServiceMgr* m_tcpSrvMgr;//tcp服务管理对象

	private:
		CNetworkCommuMgr();

	public:
		~CNetworkCommuMgr();

		//************************************
		// Method:    初始化
		//************************************
		static void Init();

		//************************************
		// Method:    退出
		//************************************
		static void Exit();

		//************************************
		// Method:    获取线程管理对象
		//************************************
		static CThreadMgr* GetThreadMgr();

		//************************************
		// Method:    获取select对象
		//************************************
		static CSelect* GetSelect();

		//************************************
		// Method:    获取tcp对象
		//************************************
		static CTcp* GetTcp();

		//************************************
		// Method:    获取服务端socket数据管理对象
		//************************************
		static CServerSocketMgr* GetServerSocketMgr();

		//************************************
		// Method:    获取服务客户端socket管理对象
		//************************************
		static CServerClientSocketMgr* GetServerClientSocketMgr();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    获取tcp服务管理对象
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();
	};
}