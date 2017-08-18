#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Tcp.h"
#include "ServerSocketMgr.h"
#include "ServerClientSocketMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//�̹߳������
		static CSelect* m_Select;//select����
		static CTcp* m_tcp;//tcp����
		static CServerSocketMgr* m_serverSocketMgr;//�����socket���ݹ������
		static CServerClientSocketMgr* m_serverCLientSocketMgr;//�Զ�socket���ݹ������
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp���ӹ������
		static CTcpServiceMgr* m_tcpSrvMgr;//tcp����������

	private:
		CNetworkCommuMgr();

	public:
		~CNetworkCommuMgr();

		//************************************
		// Method:    ��ʼ��
		//************************************
		static void Init();

		//************************************
		// Method:    �˳�
		//************************************
		static void Exit();

		//************************************
		// Method:    ��ȡ�̹߳������
		//************************************
		static CThreadMgr* GetThreadMgr();

		//************************************
		// Method:    ��ȡselect����
		//************************************
		static CSelect* GetSelect();

		//************************************
		// Method:    ��ȡtcp����
		//************************************
		static CTcp* GetTcp();

		//************************************
		// Method:    ��ȡ�����socket���ݹ������
		//************************************
		static CServerSocketMgr* GetServerSocketMgr();

		//************************************
		// Method:    ��ȡ����ͻ���socket�������
		//************************************
		static CServerClientSocketMgr* GetServerClientSocketMgr();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    ��ȡtcp����������
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();
	};
}