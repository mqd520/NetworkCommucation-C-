#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//�¼�����
	enum TcpClientEvtType
	{
		Info,//��Ϣ
		error,//����
		disconnected,//ʧȥ���������
		connected,//�����Ϸ����
		Debug//����
	};

	//************************************
	// Method:    �յ�tcp����
	// FullName:  NetworkCommunication::LPOnRecvTcpData
	// Access:    public 
	// Returns:   ָʾ�������Ƿ����ͷŻ�����
	// Qualifier: ������
	// Parameter: ����������
	//************************************
	typedef bool(*LPOnRecvTcpData)(BYTE buf[], int len);

	//************************************
	// Method:    �յ�tcp�ͻ����¼�����ָ��
	// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
	// Access:    public 
	// Returns:   �Ƿ��Ѵ���
	// Qualifier: �¼�����
	// Parameter: ��Ϣ
	//************************************
	typedef bool(*LPOnRecvNotifyEvt)(TcpClientEvtType type, TCHAR* msg);

	//tcp�ͻ���
	class CTcpClient
	{
	private:
		//ʧȥ���������ԭ��ö��
		enum LoseConnectReason
		{
			Server,//����������Ͽ�
			Client,//�ͻ��������Ͽ�
			Net//�������
		};

		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//�߳̾��
			DWORD dwThreadID;//�߳�ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		const TCHAR* m_strServerIP;//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bIsCleaned;//�Ƿ�������
		SOCKADDR_IN m_addrSrv;//����˵�ַ
		SOCKET m_socket;//�ͻ���Socket
		bool m_bInited;//�Ƿ��ʼ��::CTcpClient::
		LPOnRecvTcpData m_lpfnOnRecvTcpData;//����tcp���ݻص�����
		int m_nRecvTcpBufLen;//����tcp�������ܳ���
		char* m_pRecvTcpBuf;//����tcp������
		LPOnRecvNotifyEvt m_lpfnOnRecvNotifyEvt;//����֪ͨ�¼��ص�����
		bool m_bHaslpfnRecvTcpData;//�Ƿ����н���tcp���ݻص�����
		bool m_bConnected;//�Ƿ��������Ϸ����
		int m_nReconnectTimeSpan;//����ʧ�ܺ���ʱ��(����)
		int m_nReconnectTimes;//������������(0:һֱ����)(Ĭ��1)
		int m_nReconnected;//�Ͽ�������������
		bool m_bReconnecting;//������������
		bool m_bAutoReconnect;//���ߺ��Ƿ��Զ���������
		bool m_bExitThread;//ָʾ�߳�Ӧ���˳�(ֻ���������������òŸ�ֵ"true")
		int m_nConnectTimeout;//���ӳ�ʱʱ��(0:�����Ƶȴ�)
		ThreadInfo m_tiConnect;//�����߳���Ϣ
		ThreadInfo m_tiConnectTimeout;//���ӳ�ʱ�߳���Ϣ
		bool m_bConnectedTimeout;//ָʾ�����Ƿ�ʱ

	protected:
		//************************************
		// Method:    ��ʼ��socket
		// FullName:  NetworkCommunication::CTcpClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    ��ʼ���ͻ���socket
		// FullName:  NetworkCommunication::CTcpClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    �������ӷ����
		// FullName:  NetworkCommunication::CTcpClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    ����Socket
		// FullName:  NetworkCommunication::CTcpClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    ����֪ͨ�¼�
		// FullName:  NetworkCommunication::CTcpClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ����
		// Parameter: ��Ϣ
		//************************************
		virtual void SendNotifyEvt(TcpClientEvtType type, TCHAR* msg);

		//************************************
		// Method:    ��ӡ��Ϣ
		// FullName:  NetworkCommunication::CTcpClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ��Ϣ
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    ʧȥ���������
		// FullName:  NetworkCommunication::CTcpClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ԭ��
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    �������Ϸ����
		// FullName:  NetworkCommunication::CTcpClient::OnConnected
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnected();

	public:
		CTcpClient();
		~CTcpClient();

		//************************************
		// Method:    ��ʼ��
		// FullName:  NetworkCommunication::CTcpClient::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: �����IP
		// Parameter: ����˶˿�
		// Parameter: ������Ϣ�ص�����
		// Parameter: �ص�����ָ��
		//************************************
		virtual void Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt = NULL, int socketBufLen = 1024,
			bool autoReconnect = true, int reconnectTimes = 3, int reconnectTimeSpan = 1500, int connectTimeout = 2000);

		//************************************
		// Method:    ���ý���tcp���ݻص�����
		// FullName:  NetworkCommunication::CTcpClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ����socket���ݻص�����
		//************************************
		virtual void SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData);

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CTcpClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    ǿ���������ӷ����
		// FullName:  NetworkCommunication::CTcpClient::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Reconnect();

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CTcpClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   �Ƿ�Ӧ���˳��߳�
		// Qualifier:
		//************************************
		virtual bool ConnectServer();

		//************************************
		// Method:    �ر�����������
		// FullName:  NetworkCommunication::CTcpClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    ��ȡ�����Socket
		// FullName:  NetworkCommunication::CTcpClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    ��ȡtcp����
		// FullName:  NetworkCommunication::CTcpClient::ReadTcpData
		// Access:    virtual public 
		// Returns:   �Ƿ���˳��߳�
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool ReadTcpData();

		//************************************
		// Method:    ��������
		// FullName:  NetworkCommunication::CTcpClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: �ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		virtual bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ����״̬
		// FullName:  NetworkCommunication::CTcpClient::GetConnectStatus
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool GetConnectStatus();

		//************************************
		// Method:    �յ�tcp����
		// FullName:  NetworkCommunication::CTcpClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void OnRecvTcpData(BYTE buf[], int len);

		//************************************
		// Method:    ���ӳ�ʱ
		// FullName:  NetworkCommunication::CTcpClient::OnConnectTimeout
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectTimeout();

		//************************************
		// Method:    ģ��һ�η���˷���
		// FullName:  NetworkCommunication::CTcpClient::SimulateServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}