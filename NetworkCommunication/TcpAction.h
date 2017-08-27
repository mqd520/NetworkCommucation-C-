#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp����
	class CTcpAction
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		SOCKET m_sendrecvSocket;//���ط���(����)���ݵ�socket
		SOCKET m_attachmentSocket;//����socket,�������������������

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ����(����)���ݵ�socket
		// Parameter: ����socket,�������������������
		//************************************
		CTcpAction(SOCKET sendrecv = NULL, SOCKET attachment = NULL);
		~CTcpAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		virtual int GetActionType();

		//************************************
		// Method:    ��ȡ����(����)���ݵ�socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    ��ȡ����socket,�������������������
		//************************************
		SOCKET GetAttachmentSocket();
	};
}