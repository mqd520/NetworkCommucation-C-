#pragma once
#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include "Def.h"
#include <queue>
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	//tcp���ӹ������
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<CTcpConnection*> m_vecTcpConnection;//tcp���Ӽ���
		CThreadLock m_lock;

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
		// Method:    ��ȡָ����(��)���ݵ�socket������tcp���Ӷ���
		// Parameter: ��(��)���ݵ�socket
		// Return:	  tcp���Ӷ���
		//************************************
		CTcpConnection* GetBySendRecvSocket(SOCKET sendrecv);

		//************************************
		// Method:    ��ȡ��������
		//************************************
		int Count();
	};
}