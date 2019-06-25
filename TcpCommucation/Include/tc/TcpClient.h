#pragma once
#include "SocketTool.h"
#include "../../TcpService.h"
#include "timer.h"

namespace tc
{
	class TimerCallback;

	// tcp�ͻ�����
	class TcpClient : public TcpService
	{
	public:
		TcpClient(string ip = "", int port = 0);
		virtual ~TcpClient();

	private:
		bool bInited;			// �Ƿ��ѳ�ʼ��
		bool bIsConnecting;		// �Ƿ����ڽ�������
		bool bIsConnected;		// �Ƿ���������
		bool bIsReconnect;		// �Ƿ���Ҫ�Զ���������
		int nTimeSpan;			// �Զ��������ʱ��
		Timer t;				// ��ʱ��

	private:
		friend class TimerCallback;

		void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    ��ʼ��
		//************************************
		void Init();

		//************************************
		// Method:    ���ӷ����
		//************************************
		void ConnectServer();

	protected:
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		void Exit();

		//************************************
		// Method:    �����Զ�������Ϣ
		// Parameter: �Ƿ��Զ�����
		// Parameter: ���ʱ��(ms)
		//************************************
		void SetAutoReconnect(bool b = true, int time = TC_RECONNECTTIME);

		//************************************
		// Method:    ���ӷ����
		//************************************
		void Connect();

		//************************************
		// Method:    �ر�����
		// Parameter: b:	�Ƿ�������ӹر��¼�
		//************************************
		void Close(bool b = true);

		//************************************
		// Method:    ����������Ϣ
		// Parameter: ip:	�����IP
		// Parameter: port:	����˶˿�
		//************************************
		void SetConnectInfo(string ip, int port);

		//************************************
		// Method:    ��Զ˷�������
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		//************************************
		void Send(BYTE* pBuf, int len);
	};

	class TimerCallback
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}