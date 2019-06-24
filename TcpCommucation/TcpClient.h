#pragma once
#include "Include/tc/SocketTool.h"
#include "TcpService.h"

namespace tc
{
	// tcp客户端类
	class TcpClient : public TcpService
	{
	public:
		TcpClient(string ip = "", int port = 0);
		virtual ~TcpClient();

	private:
		bool bIsConnecting;		// 是否正在进行连接
		bool bIsConnected;		// 是否已连接上
		bool bIsReconnect;		// 是否需要自动重新连接

	private:
		//************************************
		// Method:    初始化
		//************************************
		void Init();

		//************************************
		// Method:    设置连接信息
		// Parameter: ip:	服务端IP
		// Parameter: port:	服务端端口
		//************************************
		void SetConnectInfo(string ip, int port);

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
		// Method:    向对端发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		//************************************
		void Send(BYTE* pBuf, int len);
	};
}