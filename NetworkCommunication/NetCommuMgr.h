#pragma once
#include "ThreadMgr.h"
#include "SelectThread.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "CommonThread.h"
#include "TcpEvtThread.h"

#include "Select.h"
#include "CommonSingal.h"
#include "RecvDataSingal.h"
#include "SendDataSingal.h"

#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpEvtMgr.h"

namespace NetworkCommunication
{
	//网络通信管理对象
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//线程管理对象
		static CSelectThread* m_selectThread;//select线程对象
		static CRecvThread* m_recvThread;//收数据线程对象
		static CSendThread* m_sendThread;//发数据线程对象
		static CCommonThread* m_commonThread;//通用信号处理线程对象
		static CTcpEvtThread* m_tcpEvtThread;//tcp事件线程

		static CSelect* m_Select;//select对象
		static CRecvDataSingal* m_recvSingal;//收数据信号处理对象
		static CSendDataSingal* m_sendSingal;//发数据信号处理对象
		static CCommonSingal* m_commonSingal;//通用信号处理对象
		
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp连接管理对象
		static CTcpServiceMgr* m_tcpServiceMgr;//tcp服务管理对象
		static CTcpEvtMgr* m_tcpEvtMgr;//tcp事件管理对象

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
		// Method:    获取select线程对象
		//************************************
		static CSelectThread* GetSelectThread();

		//************************************
		// Method:    获取收数据线程对象
		//************************************
		static CRecvThread* GetRecvThread();

		//************************************
		// Method:    获取发数据线程对象
		//************************************
		static CSendThread* GetSendThread();

		//************************************
		// Method:    获取通用信号处理线程对象
		//************************************
		static CCommonThread* GetCommonThread();

		//************************************
		// Method:    获取tcp事件线程对象
		//************************************
		static CTcpEvtThread* GetTcpEvtThread();

		//************************************
		// Method:    获取select对象
		//************************************
		static CSelect* GetSelect();

		//************************************
		// Method:    获取收数据信号处理对象
		//************************************
		static CRecvDataSingal* GetRecvDataSingal();

		//************************************
		// Method:    获取发数据信号处理对象
		//************************************
		static CSendDataSingal* GetSendDataSingal();

		//************************************
		// Method:    获取通用信号处理对象
		//************************************
		static CCommonSingal* GetCommonSingal();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    获取tcp服务管理对象
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    获取tcp事件管理对象
		//************************************
		static CTcpEvtMgr* GetTcpEvtMgr();
	};
}