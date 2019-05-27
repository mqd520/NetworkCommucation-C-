#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

namespace tc
{
	//tcp客户端
	class CTcpClient : public CTcpService
	{
	public:
		CTcpClient(TCHAR* strServerIP, int nServerPort);
		~CTcpClient();

	private:
		CSocketAPI m_socketAPI;//
		bool m_bIsConnecting;//是否正在进行连接
		bool m_bIsConnected;//是否已连接上

	private:
		//************************************
		// Method:    初始化
		//************************************
		void Init();

		//************************************
		// Method:    重连
		//************************************
		void Reconnect();

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
		// Method:    向对端发送数据
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 是否异步,默认异步发送
		// Parameter: 实际发送字节长度
		//************************************
		bool Send(BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);
	};
}