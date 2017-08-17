#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�յ��Զ����ݶ���
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		SocketRecvData m_recvData;

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ���յ��ĶԶ�����
		// Parameter: ����socket
		//************************************
		CRecvPeerDataAction(SocketRecvData data, SOCKET local);
		~CRecvPeerDataAction();

		//��ȡtcp��������
		int GetActionType();

		//��ȡ��������
		SocketRecvData GetRecvData();
	};
}