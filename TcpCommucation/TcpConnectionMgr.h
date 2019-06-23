#pragma once
#include <vector>
#include <queue>
#include "Def.h"
#include "TcpConnection.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// tcp���ӹ�����
	class TcpConnectionMgr
	{
	public:
		TcpConnectionMgr();
		~TcpConnectionMgr();

	private:
		vector<CTcpConnection*> vecTcpConn;//tcp���Ӽ���
		CThreadLock m_lock;

	public:
		//************************************
		// Method:    ����һ��tcp����
		//************************************
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
		// Method:    ����������Ӷ���
		//************************************
		void Clear();

		//************************************
		// Method:    ��ȡ��������
		//************************************
		int Count();
	};
}