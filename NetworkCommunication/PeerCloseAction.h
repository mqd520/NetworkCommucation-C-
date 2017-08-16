#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�Զ������ر�
	class CPeerCloseAction : public CTcpAction
	{
	private:
		CSocketAPI m_socketAPI;//

	public:
		CPeerCloseAction(SOCKET peer);
		~CPeerCloseAction();

		//��ȡtcp��������
		int GetActionType();
	};
}