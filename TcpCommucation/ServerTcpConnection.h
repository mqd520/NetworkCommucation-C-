#pragma once
#include "TcpConnection.h"

namespace tc
{
	//服务端tcp连接对象
	class CServerTcpConnection : public CTcpConnection
	{
	private:
		SOCKET m_serverSocket;//服务端socket

	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务对象
		// Parameter: 客户端socket
		// Parameter: 服务端socket
		//************************************
		CServerTcpConnection(TcpService* pTcpSrv, SOCKET client, SOCKET server);
		~CServerTcpConnection();

		//获取服务端socket
		SOCKET GetServerSocket();

		//************************************
		// Method:    收到对端数据事件处理
		//************************************
		void OnRecvPeerData();

		//************************************
		// Method:    连接断开事件处理
		//************************************
		void OnConnDisconnect();

		//************************************
		// Method:    发送对端数据完成事件处理
		// Parameter: 发送对端数据结果
		//************************************
		void OnSendDataCompleted(SendPeerDataResult* pResult);

		//************************************
		// Method:    网络错误事件处理
		//************************************
		void OnNetError();
	};
}