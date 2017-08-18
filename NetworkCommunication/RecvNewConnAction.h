#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"
#include "Def.h"

namespace NetworkCommunication
{
	//�յ������Ӷ���
	class CRecvNewConnAction : public CTcpAction
	{
	public:
		CRecvNewConnAction(SOCKET server, SOCKET sendrecv);
		~CRecvNewConnAction();

		//��ȡtcp��������
		int GetActionType();

		//��ȡ�����socket
		SOCKET GetServerSocket();

		//��ȡ����˿ͻ���socket
		SOCKET GetServerClientSocket();
	};
}