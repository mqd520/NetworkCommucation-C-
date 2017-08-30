#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//�ܾ��ͻ������Ӷ���
	class CRefuseNewConnAction :public CTcpAction
	{
	private:
		TCHAR m_strIP[20];//�Զ�IP
		int m_nPort;//�Զ˶˿�

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: �����socket
		// Parameter: ����˵Ŀͻ���socket
		//************************************
		CRefuseNewConnAction(SOCKET server, SOCKET scSocket, TCHAR* ip, int port);
		~CRefuseNewConnAction();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetActionType();

		//************************************
		// Method:    ��ȡ�Զ�IP
		//************************************
		TCHAR* GetPeerIP();

		//************************************
		// Method:    ��ȡ�Զ˶˿�
		//************************************
		int GetPeerPort();
	};
}