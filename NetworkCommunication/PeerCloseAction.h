#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�Զ������رն���
	class CPeerCloseAction : public CTcpAction
	{
	public:
		CPeerCloseAction(SOCKET local);
		~CPeerCloseAction();

		//��ȡtcp��������
		int GetActionType();
	};
}