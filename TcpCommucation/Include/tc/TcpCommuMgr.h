#pragma once
#include "../../SelectThread.h"
#include "../../RecvThread.h"
#include "../../SendThread.h"
#include "../../SelectSingalThread.h"
#include "../../TcpEvtThread.h"
#include "../../LogThread.h"

#include "../../Select.h"
#include "../../SelectSingal.h"

#include "../../TcpConnectionMgr.h"
#include "../../TcpServiceMgr.h"
#include "../../TcpEvtMgr.h"
#include "../../LogMgr.h"
#include "../../SocketDataMgr.h"

namespace tc
{
	//����ͨ�Ź������
	class CTcpCommuMgr
	{
	private:
		static volatile bool m_bExited;				// �Ƿ���Ҫ�˳���

		static SelectThread selectThread;			// select�̶߳���
		static RecvThread recvThread;				// �������̶߳���
		static SendThread sendThread;				// �������̶߳���
		static SelectSingalThread selectSingalThread;// select�źŴ����̶߳���
		static TcpEvtThread tcpEvtThread;			// tcp�¼��߳�

		static Select select;						// select����
		static SelectSingal selectSingal;			// select�źŴ������
		
		static SocketDataMgr socketDataMgr;			// socket���ݹ������
		static TcpConnectionMgr m_tcpConnMgr;		// tcp���ӹ������
		static TcpServiceMgr m_tcpServiceMgr;		// tcp����������
		static TcpEvtMgr m_tcpEvtMgr;				// tcp�¼��������
		static LogMgr logMgr;						// ��־�������

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
		static void Init(LPTcpLogCallback lpfnCallback = NULL, void* pParam1 = NULL, void* pParam2 = NULL);

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
		static SelectThread* GetSelectThread();

		//************************************
		// Method:    ��ȡ�������̶߳���
		//************************************
		static RecvThread* GetRecvThread();

		//************************************
		// Method:    ��ȡ�������̶߳���
		//************************************
		static SendThread* GetSendThread();

		//************************************
		// Method:    ��ȡselect�źŴ����̶߳���
		//************************************
		static SelectSingalThread* GetSelectSingalThread();

		//************************************
		// Method:    ��ȡtcp�¼��̶߳���
		//************************************
		static TcpEvtThread* GetTcpEvtThread();

		//************************************
		// Method:    ��ȡselect����
		//************************************
		static Select* GetSelect();

		//************************************
		// Method:    ��ȡselect�źŴ������
		//************************************
		static SelectSingal* GetSelectSingal();

		//************************************
		// Method:    ��ȡTcpConnectionMgr����
		//************************************
		static TcpConnectionMgr* GetTcpConnectionMgr();

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

		//************************************
		// Method:    ��ȡsocket���ݹ������
		//************************************
		static SocketDataMgr* GetSocketDataMgr();
	};
}