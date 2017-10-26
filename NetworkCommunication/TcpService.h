#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"
#include "TcpEvt.h"

namespace NetworkCommunication
{
	///tcp服务
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		SOCKET m_socket;//socket,服务端(客户端)socket
		TCHAR m_strServerIP[20];//socket关联的服务端IP
		int m_nServerPort;//socket关联的服务端端口
		LPTcpEventCallback m_lpCallback;//tcp事件回调函数指针

	protected:
		friend class CTcpEvtMgr;
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(CTcpEvt* pEvent);

		//************************************
		// Method:    向对端发送数据
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 是否异步,默认异步发送
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

	public:
		CTcpService();
		~CTcpService();

		//************************************
		// Method:    获取服务关联的socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    获取服务端IP
		//************************************
		TCHAR* GetServerIP();

		//************************************
		// Method:    获取服务端端口
		//************************************
		int GetServerPort();

		//************************************
		// Method:    注册tcp事件回调函数
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}