#pragma once

#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include <queue>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<CTcpConnection*> m_vecTcpConnection;//tcp���Ӽ���
		CThread* m_threadRW;//��д�߳�
		queue<SocketRecvData> m_quSocketRecvData;//socket�������ݶ���

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		void PushTcpConn(CTcpConnection* session);

		void RemoveByPeer(SOCKET peer);

		//************************************
		// Method:    socket�����ݿɶ�
		// Parameter: SOCKET socket
		//************************************
		void OnSocketCanRead(SOCKET socket);

		void ThreadEntry();

		void Run();

		//************************************
		// Method:    ͨ���Զ�socket��ȡtcp���Ӷ���
		// Parameter: �Զ�socket
		// Return:	  tcp���Ӷ���
		//************************************
		CTcpConnection* GetTcpConnByPeerSocket(SOCKET peer);

		// ɾ��ָ���Զ�seocket��tcp����
		void RemoveTcpConnByPeerSocket(SOCKET peer);
	};
}