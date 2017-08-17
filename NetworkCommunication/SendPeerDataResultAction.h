#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//���ͶԶ����ݽ������
	class CSendPeerDataResultAction : public CTcpAction
	{
	private:
		SendPeerDataResult m_result;//���ͽ��

	public:
		CSendPeerDataResultAction(SendPeerDataResult data, SOCKET local);
		~CSendPeerDataResultAction();

		//��ȡtcp��������
		int GetActionType();

		//��ȡ�������
		SendPeerDataResult GetResult();
	};
}