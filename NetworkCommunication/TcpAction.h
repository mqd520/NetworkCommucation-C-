#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp����
	class CTcpAction
	{
	private:
		SOCKET m_local;//����socket
		SOCKET m_peer;//�Զ�socket

	public:
		CTcpAction(SOCKET local = NULL, SOCKET peer = NULL);
		~CTcpAction();

		//��ȡ����socket
		SOCKET GetLocalSocket();

		//��ȡ�Զ�socket
		SOCKET GetPeerSocket();

		//��ȡtcp��������
		virtual int GetActionType();
	};
}