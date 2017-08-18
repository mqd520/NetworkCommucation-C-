#pragma once
#include "SocketAPI.h"
#include <queue>
#include "Thread.h"
#include "Def.h"
#include "TcpAction.h"
#include "RecvNewConnAction.h"
#include "RecvPeerDataAction.h"

using namespace std;

namespace NetworkCommunication
{
	//����tcp����
	class CTcp
	{
	private:
		queue<CTcpAction*> m_quTcpAction;//tcp��������
		CThread* m_threadAccept;//������socket���ӵ��߳�
		CSocketAPI m_socketAPI;//socket api
		BYTE* m_pBuf;//���ջ�����ָ��
		int m_nBufLen;//���ջ������ֽ���󳤶�

	private:
		//************************************
		// Method:    ����tcp��������
		//************************************
		void ProcessQueue();

		//************************************
		// Method:    ������������Ӷ���
		// Parameter: �����Ӷ���
		//************************************
		void ProcessAcceptNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    �����յ��Զ����ݶ���
		// Parameter: �յ��Զ����ݶ���
		//************************************
		void ProcessRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    ����ָ���ͻ�������
		// Returns:   �Ƿ����
		//************************************
		bool FilterClientSocket(SOCKET server, SOCKET client);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    ���д����������߳�
		//************************************
		void Run();

		//************************************
		// Method:    accept�߳���ڵ�
		//************************************
		void ThreadEntry();

		//************************************
		// Method:    �����socket�����ݿɶ��¼�����
		// Parameter: �����socket
		//************************************
		void OnServerSocketCanRead(SOCKET server);

		//************************************
		// Method:    ��дsocket�����ݿɶ��¼�����
		// Parameter: ��дsocket
		//************************************
		void OnReadWriteSocketCanRead(SOCKET server);
	};
}
