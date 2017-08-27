#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�첽�������ݶ���
	class CAsyncSendDataAction :public CTcpAction
	{
	private:
		AsyncSendPeerData* m_pData;//��������

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ���͵�����
		//************************************
		CAsyncSendDataAction(AsyncSendPeerData* pData);
		~CAsyncSendDataAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ��������
		//************************************
		AsyncSendPeerData* GetSendData();
	};
}