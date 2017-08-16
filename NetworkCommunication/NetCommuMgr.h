#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Accept.h"
#include "ServerSocketMgr.h"
#include "TcpConnectionMgr.h"
#include "Tcp.h"
#include "TcpServiceMgr.h"
#include "PeerSocketDataMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//线程管理对象
		static CSelect* m_Select;//select对象
		static CAccept* m_accept;//接收socket对象
		static CServerSocketDataMgr* m_serverSocketDataMgr;//服务端socket数据管理对象
		static CPeerSocketDataMgr* m_peerSocketDataMgr;//对端socket数据管理对象
		static int m_srvType;//服务类型
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp连接管理对象
		static CTcp* m_tcp;//tcp对象
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
		// Method:    获取accept对象
		//************************************
		static CAccept* GetAccept();

		//************************************
		// Method:    获取服务端socket数据管理对象
		//************************************
		static CServerSocketDataMgr* GetServerSocketMgr();

		//************************************
		// Method:    获取对端socket数据管理对象
		//************************************
		static CPeerSocketDataMgr* GetPeerSocketDataMgr();

		//************************************
		// Method:    获取服务类型
		//************************************
		static int GetSrvType();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    获取tcp对象
		//************************************
		static CTcp* GetTcp();

		//************************************
		// Method:    获取tcp服务管理对象
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();
	};
}