#pragma once
#include "ThreadMgr.h"
#include "Select.h"
#include "Tcp.h"
#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpServerMgr.h"

namespace NetworkCommunication
{
	//����ͨ�Ź������
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//�̹߳������
		static CSelect* m_Select;//select����
		static CTcp* m_tcp;//tcp����
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp���ӹ������
		static CTcpServiceMgr* m_tcpServiceMgr;//tcp����������
		static CTcpServerMgr* m_tcpServerMgr;//tcp server�������

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
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    ��ȡtcp����������
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    ��ȡtcp server�������
		//************************************
		static CTcpServerMgr* GetTcpServerMgr();
	};
}