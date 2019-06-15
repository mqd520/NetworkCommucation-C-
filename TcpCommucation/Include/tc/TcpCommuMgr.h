#pragma once
#include "../../SelectThread.h"
#include "../../RecvThread.h"
#include "../../SendThread.h"
#include "../../SelectSingalThread.h"
#include "../../TcpEvtThread.h"
#include "../../LogThread.h"

#include "../../Select.h"
#include "../../SelectSingal.h"

#include "../../TcpConnectionMgr.h"
#include "../../TcpServiceMgr.h"
#include "../../TcpEvtMgr.h"
#include "../../LogMgr.h"
#include "../../SocketDataMgr.h"

namespace tc
{
	//网络通信管理对象
	class CTcpCommuMgr
	{
	private:
		static volatile bool m_bExited;				// 是否需要退出了

		static SelectThread selectThread;			// select线程对象
		static RecvThread recvThread;				// 收数据线程对象
		static SendThread sendThread;				// 发数据线程对象
		static SelectSingalThread selectSingalThread;// select信号处理线程对象
		static TcpEvtThread tcpEvtThread;			// tcp事件线程

		static Select select;						// select对象
		static SelectSingal selectSingal;			// select信号处理对象
		
		static SocketDataMgr socketDataMgr;			// socket数据管理对象
		static TcpConnectionMgr m_tcpConnMgr;		// tcp连接管理对象
		static TcpServiceMgr m_tcpServiceMgr;		// tcp服务管理对象
		static TcpEvtMgr m_tcpEvtMgr;				// tcp事件管理对象
		static LogMgr logMgr;						// 日志管理对象

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
		static void Init(LPTcpLogCallback lpfnCallback = NULL, void* pParam1 = NULL, void* pParam2 = NULL);

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
		static SelectThread* GetSelectThread();

		//************************************
		// Method:    获取收数据线程对象
		//************************************
		static RecvThread* GetRecvThread();

		//************************************
		// Method:    获取发数据线程对象
		//************************************
		static SendThread* GetSendThread();

		//************************************
		// Method:    获取select信号处理线程对象
		//************************************
		static SelectSingalThread* GetSelectSingalThread();

		//************************************
		// Method:    获取tcp事件线程对象
		//************************************
		static TcpEvtThread* GetTcpEvtThread();

		//************************************
		// Method:    获取select对象
		//************************************
		static Select* GetSelect();

		//************************************
		// Method:    获取select信号处理对象
		//************************************
		static SelectSingal* GetSelectSingal();

		//************************************
		// Method:    获取TcpConnectionMgr对象
		//************************************
		static TcpConnectionMgr* GetTcpConnectionMgr();

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

		//************************************
		// Method:    获取socket数据管理对象
		//************************************
		static SocketDataMgr* GetSocketDataMgr();
	};
}