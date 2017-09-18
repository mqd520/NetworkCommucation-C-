#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�յ��Զ����ݶ���
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		BYTE* m_pBuf;//���յ������ݻ�����ָ��
		int m_nLen;//���ݳ���

	public:
		CRecvPeerDataAction(SOCKET recv, BYTE buf[], int len);
		~CRecvPeerDataAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ���ݳ���
		//************************************
		int GetLen();

		//************************************
		// Method:    ��ȡ���ݻ�����ָ��
		//************************************
		BYTE* GetBuf();
	};
}