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
		CPeerCloseAction(SOCKET local);
		~CPeerCloseAction();

		//获取tcp动作类型
		int GetActionType();
	};
}