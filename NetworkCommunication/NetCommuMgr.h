#pragma once
#include "SelectThread.h"
#include "RecvThread.h"
#include "SendThread.h"
#include "CommonThread.h"
#include "TcpEvtThread.h"

#include "Select.h"
#include "SocketSingal.h"

#include "TcpConnectionMgr.h"
#include "TcpServiceMgr.h"
#include "TcpEvtMgr.h"

namespace NetworkCommunication
{
	//����ͨ�Ź������
	class CNetworkCommuMgr
	{
	private:
		static volatile bool m_bExited;//�Ƿ���Ҫ�˳���

		static CSelectThread m_selectThread;//select�̶߳���
		static CRecvThread m_recvThread;//�������̶߳���
		static CSendThread m_sendThread;//�������̶߳���
		static CCommonThread m_commonThread;//ͨ���źŴ����̶߳���
		static CTcpEvtThread m_tcpEvtThread;//tcp�¼��߳�

		static CSelect m_Select;//select����
		static CSocketSingal m_recvSingal;//�������źŴ������
		static CSocketSingal m_sendSingal;//�������źŴ������
		static CSocketSingal m_otherSingal;//�����źŴ������
		
		static CTcpConnectionMgr m_tcpConnMgr;//tcp���ӹ������
		static CTcpServiceMgr m_tcpServiceMgr;//tcp����������
		static CTcpEvtMgr m_tcpEvtMgr;//tcp�¼��������

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
		// Method:    �ͷ���Դ
		//************************************
		//static void Release();

		//************************************
		// Method:    �Ƿ���Ҫ�˳�
		//************************************
		static bool IsExited();

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
		static CSocketSingal* GetRecvDataSingal();

		//************************************
		// Method:    ��ȡ�������źŴ������
		//************************************
		static CSocketSingal* GetSendDataSingal();

		//************************************
		// Method:    ��ȡ�����źŴ������
		//************************************
		static CSocketSingal* GetOtherSingal();

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