#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	///tcp服务
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		int m_nSrvType;//服务类型
		SOCKET m_socket;//socket,服务端(客户端)socket
		char m_strLocalIP[20];//socket关联的本地IP
		int m_nLocalPort;//socket关联的本地端口
		LPTcpEventCallback m_lpCallback;//tcp事件回调函数指针

	public:
		CTcpService(int srvType);
		~CTcpService();

		//************************************
		// Method:    获取tcp服务类型
		//************************************
		int GetSrvType();

		//************************************
		// Method:    获取服务端socket数据
		//************************************
		virtual ServerSocket GetServerSocketData();

		//************************************
		// Method:    获取socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    获取本地IP
		//************************************
		char* GetLocalIP();

		//************************************
		// Method:    获取本地端口
		//************************************
		int GetLocalPort();

		//************************************
		// Method:    向对端发送数据(同步)
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    向对端发送数据(异步)
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		virtual void AsyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    注册tcp事件回调函数
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);

		//************************************
		// Method:    收到新的客户端连接事件处理
		// Parameter: 对端IP
		// Parameter: 对端端口
		// Parameter: 服务端客户端socket
		//************************************
		virtual void OnRecvNewConnection(char* ip, int port, SOCKET scSocket);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: 对端数据
		//************************************
		virtual bool OnRecvPeerData(PeerData* data);

		//************************************
		// Method:    对端主动关闭连接事件处理
		// Parameter: 对端IP
		// Parameter: 对端端口
		//************************************
		virtual void OnPeerCloseConn(char* ip, int port);

		//************************************
		// Method:    发送对端数据完成事件处理
		// Parameter: 发送数据结果
		//************************************
		virtual void OnSendPeerDataCompleted(SendPeerDataResult* result);

		//************************************
		// Method:    网络错误事件处理
		// Parameter: 对端IP
		// Parameter: 对端端口
		//************************************
		virtual void OnNetError(char* ip, int port);

		//************************************
		// Method:    拒绝新客户端连接事件处理
		// Parameter: 对端IP
		// Parameter: 对端端口
		//************************************
		virtual void OnRefuseNewConn(char* ip, int port);
	};
}