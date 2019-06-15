#pragma once
#include "TcpConnection.h"
#include "Include/tc/TcpServer.h"

namespace tc
{
	// 服务端tcp连接对象
	class CServerTcpConnection : public CTcpConnection
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务对象
		// Parameter: 收发数据关联的socket
		//************************************
		CServerTcpConnection(TcpServer* pTcpSrv, SOCKET sendrecv);
		~CServerTcpConnection();

	public:
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