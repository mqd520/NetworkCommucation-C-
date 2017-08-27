#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//�ܾ��ͻ������Ӷ���
	class CRefuseNewConnAction :public CTcpAction
	{
	private:
		char m_strIP[20];//�Զ�IP
		int m_nPort;//�Զ˶˿�

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: �����socket
		// Parameter: ����˵Ŀͻ���socket
		//************************************
		CRefuseNewConnAction(SOCKET server, SOCKET scSocket, char* ip, int port);
		~CRefuseNewConnAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ�Զ�IP
		//************************************
		char* GetPeerIP();

		//************************************
		// Method:    ��ȡ�Զ˶˿�
		//************************************
		int GetPeerPort();
	};
}