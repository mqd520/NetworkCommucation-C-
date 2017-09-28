#pragma once
#include "ThreadMgr.h"
#include "SelectThread.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "CommonThread.h"
#include "TcpEvtThread.h"

#include "Select.h"
#include "CommonSingal.h"
#include "RecvDataSingal.h"
#include "SendDataSingal.h"

#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpEvtMgr.h"

namespace NetworkCommunication
{
	//����ͨ�Ź������
	class CNetworkCommuMgr
	{
	private:
		static CThreadMgr* m_threadMgr;//�̹߳������
		static CSelectThread* m_selectThread;//select�̶߳���
		static CRecvThread* m_recvThread;//�������̶߳���
		static CSendThread* m_sendThread;//�������̶߳���
		static CCommonThread* m_commonThread;//ͨ���źŴ����̶߳���
		static CTcpEvtThread* m_tcpEvtThread;//tcp�¼��߳�

		static CSelect* m_Select;//select����
		static CRecvDataSingal* m_recvSingal;//�������źŴ������
		static CSendDataSingal* m_sendSingal;//�������źŴ������
		static CCommonSingal* m_commonSingal;//ͨ���źŴ������
		
		static CTcpConnectionMgr* m_tcpConnMgr;//tcp���ӹ������
		static CTcpServiceMgr* m_tcpServiceMgr;//tcp����������
		static CTcpEvtMgr* m_tcpEvtMgr;//tcp�¼��������

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
		// Method:    ��ȡselect�̶߳���
		//************************************
		static CSelectThread* GetSelectThread();

		//************************************
		// Method:    ��ȡ�������̶߳���
		//************************************
		static CRecvThread* GetRecvThread();

		//************************************
		// Method:    ��ȡ�������̶߳���
		//************************************
		static CSendThread* GetSendThread();

		//************************************
		// Method:    ��ȡͨ���źŴ����̶߳���
		//************************************
		static CCommonThread* GetCommonThread();

		//************************************
		// Method:    ��ȡtcp�¼��̶߳���
		//************************************
		static CTcpEvtThread* GetTcpEvtThread();

		//************************************
		// Method:    ��ȡselect����
		//************************************
		static CSelect* GetSelect();

		//************************************
		// Method:    ��ȡ�������źŴ������
		//************************************
		static CRecvDataSingal* GetRecvDataSingal();

		//************************************
		// Method:    ��ȡ�������źŴ������
		//************************************
		static CSendDataSingal* GetSendDataSingal();

		//************************************
		// Method:    ��ȡͨ���źŴ������
		//************************************
		static CCommonSingal* GetCommonSingal();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    ��ȡtcp����������
		//************************************
		static CTcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    ��ȡtcp�¼��������
		//************************************
		static CTcpEvtMgr* GetTcpEvtMgr();
	};
}