#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <queue>
#include "Timer.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp�¼�����
	enum TcpEvtType
	{
		error,//����
		connfailed,//����ʧ��
		connectsuccess,//���ӳɹ�,
		disconnect,//�������Ͽ�����,
		Net,//�������,
		TcpInfo//��Ϣ
	};

	//tcp���ݽ��շ�ʽ
	enum TcpDataRecvType
	{
		que,//����
		single,//���߳�(�����߳�)
		multi//���߳�
	};

	//��������Ϣ
	typedef struct tagBufInfo
	{
		BYTE* buf;//������
		int len;//����������
	}BufInfo, *LPBufInfo;

	//************************************
	// Method:    �յ�tcp���ݺ���ָ��
	// FullName:  NetworkCommunication::LPOnRecvTcpData
	// Access:    public 
	// Returns:   ָʾ�������Ƿ����ͷŻ�����
	// Qualifier: ������
	// Parameter: ����������
	//************************************
	typedef bool(*LPOnRecvTcpData)(BYTE buf[], int len);

	//************************************
	// Method:    �յ�tcp�¼�����ָ��
	// FullName:  NetworkCommunication::LPOnRecvTcpEvt
	// Access:    public 
	// Returns:   void
	// Qualifier: �¼�����
	// Parameter: ��Ϣ
	//************************************
	typedef void(*LPOnRecvTcpEvt)(TcpEvtType type, TCHAR* msg);

	//tcp�ͻ���
	class CTcpClient
	{
	private:
		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//�߳̾��
			DWORD dwThreadID;//�߳�ID
			bool bPause;//�Ƿ���ͣ
		}ThreadInfo, *LPThreadInfo;

	protected:
		//const TCHAR* m_strServerIP;//�����IP
		TCHAR m_strServerIP[20];//�����IP
		int m_nServerPort;//����˶˿�
		SOCKADDR_IN m_addrSrv;//����˵�ַ
		SOCKET m_socket;//�ͻ���Socket
		bool m_bInited;//�Ƿ��ʼ��
		LPOnRecvTcpData m_lpfnOnRecvTcpData;//����tcp���ݻص�����
		int m_nRecvTcpBufLen;//����tcp�������ܳ���
		char* m_pRecvTcpBuf;//����tcp������
		LPOnRecvTcpEvt m_lpfnOnRecvTcpEvt;//����tcp�¼��ص�����
		bool m_bHaslpfnRecvTcpData;//�Ƿ����н���tcp���ݻص�����
		int m_nReconnectTimeSpan;//����ʧ�ܺ��ٴ����Ӽ��ʱ��(����)
		int m_nAllowReconnectCount;//������������(-1:����������,0:������,>0:�������)
		int m_nReconnectCount;//����������(���ӳɹ�����������0)
		int m_nConnectTimeout;//���ӳ�ʱʱ��(0:�����Ƶȴ�,>0:����ָ��ʱ��)
		bool m_bAllowReconnect;//���ӶϿ����Ƿ�������������
		ThreadInfo m_tiConnect;//�����߳���Ϣ
		ThreadInfo m_tiReadTcpData;//��ȡtcp�����߳���Ϣ
		CTimerT<CTcpClient>* m_timer;//���ӳ�ʱ����
		TcpDataRecvType m_sendType;//tcp���ݷ��ͷ�ʽ
		queue<BufInfo> m_queue;//���ж���
		ThreadInfo m_tiQueue;//�����߳���Ϣ
		bool m_bSocketAvaliabled;//socket�Ƿ����

	protected:
		//��ʼ��socket����
		void InitSocket();

		//��ʼ������˵�ַ��Ϣ
		void InitServerAddr();

		//����socket
		void CreateSocket();

		//************************************
		// Method:    ����tcp�¼�
		// Parameter: �¼�����
		// Parameter: ��Ϣ
		//************************************
		virtual void SendTcpEvt(TcpEvtType type, TCHAR* msg);

		//���ӳɹ��¼�����
		void OnConnectSuccess();

		//************************************
		// Method:    ���ӳ�ʱ�¼�����
		// Returns:   �Ƿ������ʱ
		//************************************
		bool OnConnectTimeout();

		//************************************
		// Method:    ��ͣ(�ָ�)ָ���߳�
		// Parameter: �߳���Ϣָ��
		// Parameter: ��ͣ���
		//************************************
		void PauseThread(ThreadInfo* ti, bool b);

		//�����߳�
		void CleanThread();

		//�ر�socket
		void CloseSocket();

		//************************************
		// Method:    �յ�tcp�����¼�����
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void OnRecvTcpData(BYTE buf[], int len);

		//************************************
		// Method:    ���ͽ��յ���tcp����
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void SendTcpData(BYTE buf[], int len);

		//************************************
		// Method:    ���̴߳�����յ�������
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void OnSingle(BYTE buf[], int len);

		//************************************
		// Method:    ���д�����յ�������
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void OnQueue(BYTE buf[], int len);

		//************************************
		// Method:    ���̴߳�����յ�������
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void OnMulti(BYTE buf[], int len);

		//���ӶϿ�����������
		void Reconnect();

	public:
		CTcpClient();
		~CTcpClient();

		//************************************
		// Method:    ��ʼ��
		// Parameter: �����IP
		// Parameter: ����˶˿�
		// Parameter: ���ͽ��յ���tcp���ݷ�ʽ
		// Parameter: ���ջ���������
		// Parameter: ������������(-1:����������,0:������,>0:�������)
		// Parameter: �������
		// Parameter: ���ӳ�ʱʱ��
		// Parameter: �Ͽ����Ƿ���������
		//************************************
		void Init(TCHAR* ip, int port, TcpDataRecvType type = TcpDataRecvType::single, int socketBufLen = 1024, int allowReconnectCount = 0,
			int reconnectTimeSpan = 2000, int connectTimeout = 2000, bool allowReconnect = true);

		//************************************
		// Method:    ���ûص�����
		// FullName:  NetworkCommunication::CTcpClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ����tcp���ݻص�����
		// Parameter: ����tcp�¼��ص�����
		//************************************
		void SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData, LPOnRecvTcpEvt lpfnOnRecvTcpEvt = NULL);

		//��ʼ����
		void Connect();

		//�ر�����
		void CloseConnect();

		//************************************
		// Method:    ��������
		// Returns:   �Ƿ��ͳɹ�
		// Parameter: �ֽ�����
		// Parameter: �ֽ����鳤��
		// Parameter: ʵ�ʷ��ͳ���
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    ģ��һ�η���˷���
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void SimulateServerData(BYTE* buf, int len);

		//��ȡ�����߳����(�������)
		void ReadQueue();

		//���ӷ�����߳����(�������)
		void ConnectServer();

		//��ȡtcp�����߳����(�������)
		void ReadTcpData();

		//************************************
		// Method:    ���̴߳�����յ�tcp�����߳����(�������)
		// Parameter: ������
		// Parameter: ����������
		//************************************
		void MultiSendTcpData(BYTE buf[], int len);
	};
}