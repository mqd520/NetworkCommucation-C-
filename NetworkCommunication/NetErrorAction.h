#pragma once
#include "TcpAction.h"

namespace NetworkCommunication
{
	//���������
	class CNetErrorAction : public CTcpAction
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ����(����)���ݵ�socket
		//************************************
		CNetErrorAction(SOCKET sendrecv);
		~CNetErrorAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();
	};
}