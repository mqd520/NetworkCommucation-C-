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
		//************************************
		// Method:    ���캯��
		// Parameter: ���նԶ����ݵ�socket
		//************************************
		CPeerCloseAction(SOCKET recv);
		~CPeerCloseAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();
	};
}