#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Accept.h"
#include "ServerSocketMgr.h"
#include "TcpConnectionMgr.h"
#include "Tcp.h"
#include "TcpServiceMgr.h"
#include "PeerSocketDataMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//�̹߳������
		static CSelect* m_Select;//select����
		static CAccept* m_accept;//����socket����
		static CServerSocketDataMgr* m_serverSocketDataMgr;//�����socket���ݹ������
		static CPeerSocketDataMgr* m_peerSocketDataMgr;//�Զ�socket���ݹ������
		static int m_srvType;//��������
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp���ӹ������
		static CTcp* m_tcp;//tcp����
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
		// Method:    ��ȡaccept����
		//************************************
		static CAccept* GetAccept();

		//************************************
		// Method:    ��ȡ�����socket���ݹ������
		//************************************
		static CServerSocketDataMgr* GetServerSocketMgr();

		//************************************
		// Method:    ��ȡ�Զ�socket���ݹ������
		//************************************
		static CPeerSocketDataMgr* GetPeerSocketDataMgr();

		//************************************
		// Method:    ��ȡ��������
		//************************************
		static int GetSrvType();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    ��ȡtcp����
		//************************************
		static CTcp* GetTcp();

		//************************************
		// Method:    ��ȡtcp����������
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();
	};
}