#pragma once
#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include "Def.h"
#include <queue>

using namespace std;

namespace NetworkCommunication
{
	//tcp���ӹ������
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<CTcpConnection*> m_vecTcpConnection;//tcp���Ӽ���

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		//����һ��tcp����
		void PushTcpConn(CTcpConnection* conn);

		//************************************
		// Method:    �Ƴ�ָ���շ����ݵ�socket������tcp���Ӷ���
		// Parameter: �շ����ݵ�socket
		//************************************
		void RemoveBySendRecvSocket(SOCKET socket);

		//************************************
		// Method:    ��ȡָ���շ����ݵ�socket������tcp���Ӷ���
		// Parameter: �շ����ݵ�socket
		// Return:	  tcp���Ӷ���
		//************************************
		CTcpConnection* GetBySendRecvSocket(SOCKET socket);

		//void AsyncSend(SOCKET socket, BYTE buf[], int len, int* actualLen);

		//************************************
		// Method:    ���յ��Զ������¼�����
		// Parameter: �Զ�����
		//************************************
		void OnRecvPeerData(PeerData* data);

		//�Զ������ر��¼�����
		void OnPeerClose(SOCKET peer);
	};
}