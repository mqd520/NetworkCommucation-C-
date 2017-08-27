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
		//************************************
		// Method:    构造函数
		// Parameter: 服务端server
		// Parameter: 发送(接收)数据的socket
		//************************************
		CRecvNewConnAction(SOCKET server, SOCKET sendrecv);
		~CRecvNewConnAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();
	};
}