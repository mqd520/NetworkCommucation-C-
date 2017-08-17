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
		CSocketAPI m_socketAPI;
		vector<CTcpConnection*> m_vecTcpConnection;//tcp���Ӽ���
		CThread* m_threadRW;//��д�߳�
		queue<SocketRecvData> m_quSocketSendRecvData;//socket���ͽ������ݶ���

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		//�߳����
		void ThreadEntry();

		//�����߳�
		void Run();

		//����һ��tcp����
		void PushTcpConn(CTcpConnection* session);

		//************************************
		// Method:    �Ƴ�ָ���Զ�socket��tcp���Ӷ���
		// Parameter: �Զ�socket
		//************************************
		void RemoveTcpConnByPeerSocket(SOCKET peer);

		//************************************
		// Method:    �Զ�socket�����ݿɶ��¼�����
		// Parameter: �Զ�socket
		//************************************
		void OnPeerSocketCanRead(SOCKET peer);

		//************************************
		// Method:    ͨ���Զ�socket��ȡtcp���Ӷ���
		// Parameter: �Զ�socket
		// Return:	  tcp���Ӷ���
		//************************************
		CTcpConnection* GetTcpConnByPeerSocket(SOCKET peer);

		//�Զ������ر��¼�����
		void OnPeerClose(SOCKET peer);

		void UnAsyncSend(SOCKET socket, BYTE buf[], int len, int* actualLen);
	};
}