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
		CRecvPeerDataAction(SocketRecvData data);
		~CRecvPeerDataAction();

		//��ȡtcp��������
		int GetActionType();

		BYTE* GetBuf();
	};
}