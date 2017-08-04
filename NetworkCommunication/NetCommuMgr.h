#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Accept.h"
#include "ServerSocketMgr.h"
#include "TcpConnectionMgr.h"

namespace NetworkCommunication
{
	class CNetworkCommuMgr
	{
	public:
		//��������
		enum EServiceType
		{
			Client,//�ͻ���
			Server,//�����
			Both//����ͬʱ�߱�
		};

	private:
		CNetworkCommuMgr();
		static CThreadMgr* m_threadMgr;
		static CSelect* m_Select;
		static CAccept* m_accept;
		static CServerSocketMgr* m_serverSockerMgr;
		static EServiceType m_srvType;
		static CTcpConnectionMgr* m_tcpConnMgr;

	public:
		~CNetworkCommuMgr();

		//************************************
		// Method:    ��ʼ��
		//************************************
		static void Init(EServiceType type);

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
		// Method:    ��ȡsocket���ݹ������
		//************************************
		static CServerSocketMgr* GetServerSocketMgr();

		//************************************
		// Method:    ��ȡ��������
		//************************************
		static EServiceType GetSrvType();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();
	};
}