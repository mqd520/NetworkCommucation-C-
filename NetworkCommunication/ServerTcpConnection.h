#pragma once
#include "TcpConnection.h"

namespace NetworkCommunication
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
		CServerTcpConnection(CTcpService* pTcpSrv, SOCKET client, SOCKET server);
		~CServerTcpConnection();

		//获取服务端socket
		SOCKET GetServerSocket();

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    tcp连接断开事件处理
		//************************************
		void OnTcpDisconnect(int reason);

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