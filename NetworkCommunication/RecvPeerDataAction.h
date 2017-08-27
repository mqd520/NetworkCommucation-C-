#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�յ��Զ����ݶ���
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		PeerData* m_pRecvData;//���յ��ĶԶ�����

	public:
		CRecvPeerDataAction(PeerData* pData);
		~CRecvPeerDataAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ���յ��ĶԶ�����
		//************************************
		PeerData* GetPeerData();
	};
}