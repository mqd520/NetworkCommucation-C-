#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	class CAcceptNewConnAction : public CTcpAction
	{
	public:
		CAcceptNewConnAction(SOCKET server, SOCKET client);
		~CAcceptNewConnAction();

		//��ȡtcp��������
		int GetActionType();
	};
}