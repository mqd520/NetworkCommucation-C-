#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Tcp.h"
#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpServerMgr.h"

namespace NetworkCommunication
{
	//网络通信管理对象
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//线程管理对象
		static CSelect* m_Select;//select对象
		static CTcp* m_tcp;//tcp对象
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp连接管理对象
		static CTcpServiceMgr* m_tcpServiceMgr;//tcp服务管理对象
		static CTcpServerMgr* m_tcpServerMgr;//tcp server管理对象

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
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    获取tcp服务管理对象
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    获取tcp server管理对象
		//************************************
		static CTcpServerMgr* GetTcpServerMgr();
	};
}