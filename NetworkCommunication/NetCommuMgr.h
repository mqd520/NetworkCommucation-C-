#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Accept.h"
#include "ServerSocketMgr.h"
#include "TcpConnectionMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	public:
		//服务类型
		enum EServiceType
		{
			Client,//客户端
			Server,//服务端
			Both//二者同时具备
		};

	private:
		CNetworkCommuMgr();
		static CThreadMgr* m_threadMgr;
		static CSelect* m_Select;
		static CAccept* m_accept;
		static CServerSocketMgr* m_serverSockerMgr;
		static EServiceType m_srvType;
		static CTcpConnectionMgr* m_tcpConnMgr;

	public:
		~CNetworkCommuMgr();

		//************************************
		// Method:    初始化
		//************************************
		static void Init(EServiceType type);

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
		// Method:    获取socket数据管理对象
		//************************************
		static CServerSocketMgr* GetServerSocketMgr();

		//************************************
		// Method:    获取服务类型
		//************************************
		static EServiceType GetSrvType();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();
	};
}