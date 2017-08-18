#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//收到新连接动作
	class CRecvNewConnAction : public CTcpAction
	{
	public:
		CRecvNewConnAction(SOCKET server, SOCKET sendrecv);
		~CRecvNewConnAction();

		//获取tcp动作类型
		int GetActionType();

		//获取服务端socket
		SOCKET GetServerSocket();

		//获取服务端客户端socket
		SOCKET GetServerClientSocket();
	};
}