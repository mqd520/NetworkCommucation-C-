#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp����
	class CTcpAction
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		SOCKET m_localSocket;//����socket,�����socket���߿ͻ���socket
		SOCKET m_socket;//������socket,�������������������

	public:
		CTcpAction(SOCKET local = NULL, SOCKET socket = NULL);
		~CTcpAction();

		//��ȡtcp��������
		virtual int GetActionType();

		//��ȡ����socket
		SOCKET GetLocalSocket();
	};
}