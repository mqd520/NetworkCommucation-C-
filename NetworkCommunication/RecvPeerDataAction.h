#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�յ��Զ����ݶ���
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		PeerData* m_recvData;

	public:
		CRecvPeerDataAction(PeerData* pData);
		~CRecvPeerDataAction();

		//��ȡtcp��������
		int GetActionType();

		//��ȡ���նԶ�����
		PeerData* GetPeerData();
	};
}