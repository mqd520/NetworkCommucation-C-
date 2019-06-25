#pragma once
#include "SocketTool.h"
#include "../../TcpService.h"
#include "timer.h"

namespace tc
{
	class TimerCallback;

	// tcp客户端类
	class TcpClient : public TcpService
	{
	public:
		TcpClient(string ip = "", int port = 0);
		virtual ~TcpClient();

	private:
		bool bInited;			// 是否已初始化
		bool bIsConnecting;		// 是否正在进行连接
		bool bIsConnected;		// 是否已连接上
		bool bIsReconnect;		// 是否需要自动重新连接
		int nTimeSpan;			// 自动重连间隔时间
		Timer t;				// 定时器

	private:
		friend class TimerCallback;

		void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    初始化
		//************************************
		void Init();

		//************************************
		// Method:    连接服务端
		//************************************
		void ConnectServer();

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		void Exit();

		//************************************
		// Method:    设置自动重新信息
		// Parameter: 是否自动重连
		// Parameter: 间隔时间(ms)
		//************************************
		void SetAutoReconnect(bool b = true, int time = TC_RECONNECTTIME);

		//************************************
		// Method:    连接服务端
		//************************************
		void Connect();

		//************************************
		// Method:    关闭连接
		// Parameter: b:	是否产生连接关闭事件
		//************************************
		void Close(bool b = true);

		//************************************
		// Method:    设置连接信息
		// Parameter: ip:	服务端IP
		// Parameter: port:	服务端端口
		//************************************
		void SetConnectInfo(string ip, int port);

		//************************************
		// Method:    向对端发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		//************************************
		void Send(BYTE* pBuf, int len);
	};

	class TimerCallback
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}