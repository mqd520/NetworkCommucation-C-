#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�Զ������ر�
	class CPeerCloseAction : public CTcpAction
	{
	public:
		CPeerCloseAction(SOCKET peer);
		~CPeerCloseAction();

		//��ȡtcp��������
		int GetActionType();
	};
}