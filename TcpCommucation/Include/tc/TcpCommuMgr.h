#pragma once
#include "SelectThread.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "TcpEvtThread.h"

#include "Select.h"
#include "RecvDataHandler.h"
#include "SendDataHandler.h"

#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpEvtMgr.h"
#include "SocketDataMgr.h"

#include "Timer.h"


namespace tc
{
	// tcp comm
	class TcpCommu
	{
	private:
		TcpCommu();

	private:
		static SelectThread selectThread;			// select线程对象
		static RecvThread recvThread;				// 收数据线程对象
		static SendThread sendThread;				// 发数据线程对象
		static TcpEvtThread tcpEvtThread;			// tcp事件线程

		static Select select;						// select对象
		static RecvDataHandler recvHandler;			// 收数据处理对象
		static SendDataHandler sendHandler;			// 发数据处理对象
		
		static SocketDataMgr socketDataMgr;			// socket数据管理对象
		static TcpConnectionMgr tcpConnMgr;			// tcp连接管理对象
		static TcpServiceMgr tcpServiceMgr;			// tcp服务管理对象
		static TcpEvtMgr tcpEvtMgr;					// tcp事件管理对象

		static Timer t;								// timer for close socket

	public:
		~TcpCommu();

		//************************************
		// Method:    初始化
		//************************************
		static void Init();

		//************************************
		// Method:    退出
		//************************************
		static void Exit();

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
		// Method:    获取tcp事件线程对象
		//************************************
		static TcpEvtThread* GetTcpEvtThread();

		//************************************
		// Method:    获取select对象
		//************************************
		static Select* GetSelect();

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
		// Method:    获取socket数据管理对象
		//************************************
		static SocketDataMgr* GetSocketDataMgr();

		//************************************
		// Method:    获取收数据处理对象
		//************************************
		static RecvDataHandler* GetRecvHandler();

		//************************************
		// Method:    获取发数据处理对象
		//************************************
		static SendDataHandler* GetSendHandler();
	};
}