#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	class CAcceptNewConnAction : public CTcpAction
	{
	private:
		CSocketAPI m_socketAPI;

	public:
		CAcceptNewConnAction(SOCKET server, SOCKET client);
		~CAcceptNewConnAction();

		//获取tcp动作类型
		int GetActionType();
	};
}