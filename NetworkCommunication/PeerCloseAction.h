#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//对端主动关闭动作
	class CPeerCloseAction : public CTcpAction
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: 接收对端数据的socket
		//************************************
		CPeerCloseAction(SOCKET recv);
		~CPeerCloseAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();
	};
}