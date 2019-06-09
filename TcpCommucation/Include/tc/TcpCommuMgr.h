#pragma once
#include "../../SelectThread.h"
#include "../../RecvThread.h"
#include "../../SendThread.h"
#include "../../CommonThread.h"
#include "../../TcpEvtThread.h"
#include "../../LogThread.h"

#include "../../Select.h"
#include "../../SocketSingal.h"

#include "../../TcpConnectionMgr.h"
#include "../../TcpServiceMgr.h"
#include "../../TcpEvtMgr.h"
#include "../../LogMgr.h"

namespace tc
{
	//网络通信管理对象
	class CTcpCommuMgr
	{
	private:
		static volatile bool m_bExited;//是否需要退出了

		static CSelectThread m_selectThread;//select线程对象
		static CRecvThread m_recvThread;//收数据线程对象
		static CSendThread m_sendThread;//发数据线程对象
		static CCommonThread m_commonThread;//通用信号处理线程对象
		static CTcpEvtThread m_tcpEvtThread;//tcp事件线程

		static CSelect m_Select;//select对象
		static SocketSingalProcess m_recvSingal;//收数据信号处理对象
		static SocketSingalProcess m_sendSingal;//发数据信号处理对象
		static SocketSingalProcess m_otherSingal;//其它信号处理对象
		
		static CTcpConnectionMgr m_tcpConnMgr;//tcp连接管理对象
		static TcpServiceMgr m_tcpServiceMgr;//tcp服务管理对象
		static TcpEvtMgr m_tcpEvtMgr;//tcp事件管理对象
		static LogMgr logMgr;	// 日志管理对象

	private:
		CTcpCommuMgr();

	public:
		~CTcpCommuMgr();

		//************************************
		// Method:    初始化
		// Parameter: lpfnCallback:	日志回调函数指针(参看: LPLogCallback)
		// Parameter: pParam1:	附加参数1
		// Parameter: pParam2:	附加参数2
		//************************************
		static void Init(LPLogCallback lpfnCallback = NULL, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    退出
		//************************************
		static void Exit();

		//************************************
		// Method:    释放资源
		//************************************
		//static void Release();

		//************************************
		// Method:    是否需要退出
		//************************************
		static bool IsExited();

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
		static SocketSingalProcess* GetRecvDataSingal();

		//************************************
		// Method:    获取发数据信号处理对象
		//************************************
		static SocketSingalProcess* GetSendDataSingal();

		//************************************
		// Method:    获取其它信号处理对象
		//************************************
		static SocketSingalProcess* GetOtherSingal();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    获取tcp服务管理对象
		//************************************
		static TcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    获取tcp事件管理对象
		//************************************
		static TcpEvtMgr* GetTcpEvtMgr();

		//************************************
		// Method:    获取日志管理对象
		//************************************
		static LogMgr* GetLogMgr();
	};
}