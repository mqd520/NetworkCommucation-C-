#pragma once
#include "TcpAction.h"

namespace NetworkCommunication
{
	//网络错误动作
	class CNetErrorAction : public CTcpAction
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: 发送(接收)数据的socket
		//************************************
		CNetErrorAction(SOCKET sendrecv);
		~CNetErrorAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();
	};
}