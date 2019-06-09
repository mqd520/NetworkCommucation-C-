#pragma once
#include "../../SelectThread.h"
#include "../../RecvThread.h"
#include "../../SendThread.h"
#include "../../CommonThread.h"
#include "../../TcpEvtThread.h"
#include "../../LogThread.h"

#include "../../Select.h"
#include "../../SocketSingal.h"

#include "../../TcpConnectionMgr.h"
#include "../../TcpServiceMgr.h"
#include "../../TcpEvtMgr.h"
#include "../../LogMgr.h"

namespace tc
{
	//����ͨ�Ź������
	class CTcpCommuMgr
	{
	private:
		static volatile bool m_bExited;//�Ƿ���Ҫ�˳���

		static CSelectThread m_selectThread;//select�̶߳���
		static CRecvThread m_recvThread;//�������̶߳���
		static CSendThread m_sendThread;//�������̶߳���
		static CCommonThread m_commonThread;//ͨ���źŴ����̶߳���
		static CTcpEvtThread m_tcpEvtThread;//tcp�¼��߳�

		static CSelect m_Select;//select����
		static SocketSingalProcess m_recvSingal;//�������źŴ������
		static SocketSingalProcess m_sendSingal;//�������źŴ������
		static SocketSingalProcess m_otherSingal;//�����źŴ������
		
		static CTcpConnectionMgr m_tcpConnMgr;//tcp���ӹ������
		static TcpServiceMgr m_tcpServiceMgr;//tcp����������
		static TcpEvtMgr m_tcpEvtMgr;//tcp�¼��������
		static LogMgr logMgr;	// ��־�������

	private:
		CTcpCommuMgr();

	public:
		~CTcpCommuMgr();

		//************************************
		// Method:    ��ʼ��
		// Parameter: lpfnCallback:	��־�ص�����ָ��(�ο�: LPLogCallback)
		// Parameter: pParam1:	���Ӳ���1
		// Parameter: pParam2:	���Ӳ���2
		//************************************
		static void Init(LPLogCallback lpfnCallback = NULL, void* pParam1 = NULL, void* pParam2 = NULL);

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
		static SocketSingalProcess* GetRecvDataSingal();

		//************************************
		// Method:    ��ȡ�������źŴ������
		//************************************
		static SocketSingalProcess* GetSendDataSingal();

		//************************************
		// Method:    ��ȡ�����źŴ������
		//************************************
		static SocketSingalProcess* GetOtherSingal();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static CTcpConnectionMgr* GetTcpConnectionMgr();

		//************************************
		// Method:    ��ȡtcp����������
		//************************************
		static TcpServiceMgr* GetTcpServiceMgr();

		//************************************
		// Method:    ��ȡtcp�¼��������
		//************************************
		static TcpEvtMgr* GetTcpEvtMgr();

		//************************************
		// Method:    ��ȡ��־�������
		//************************************
		static LogMgr* GetLogMgr();
	};
}