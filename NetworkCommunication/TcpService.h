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
		CSocketAPI m_socketAPI;
		int m_nSrvType;//服务类型
		SOCKET m_localSocket;//本地socket
		char m_strLocalIP[20];//本地socket关联IP
		int m_nLocalPort;//本地socket关联的端口

	private:
		void OnRecvNewConnection();

	public:
		~CTcpService();
		CTcpService(int srvType);

		// 获取tcp服务类型
		int GetSrvType();

		//************************************
		// Method:    获取服务端socket数据
		//************************************
		virtual ServerSocket GetServerSocketData();

		//************************************
		// Method:    获取本地socket
		//************************************
		SOCKET GetLocalSocket();

		//************************************
		// Method:    接收到新的客户端连接事件处理
		// Parameter: 服务端socket	
		// Parameter: 对端socket数据
		//************************************
		virtual void OnRecvNewConnection(ServerSocket server, ServerClientSocket client);

		//************************************
		// Method:    对端主动关闭事件处理
		// Parameter: 服务端socket	
		// Parameter: 对端socket数据
		//************************************
		virtual void OnPeerCloseSocket(ServerClientSocket data);

		virtual bool OnRecvPeerData(PeerData* data);

		//************************************
		// Method:    发送对端数据完成事件处理
		// Parameter: 发送结果
		//************************************
		virtual void OnSendPeerDataCompleted(SendPeerDataResult result);

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
		void AsyncSendData(SOCKET client, BYTE buf[], int len, int* actualLen = NULL);
	};
}