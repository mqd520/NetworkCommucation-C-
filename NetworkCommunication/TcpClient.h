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
	enum SocketClientEvtType
	{
		Info,//��Ϣ
		error,//����
		disconnected,//ʧȥ���������
		connected,//�����Ϸ����
		Debug//����
	};

	//************************************
	// Method:    �յ�socket����
	// FullName:  NetworkCommunication::LPOnRecvSocketData
	// Access:    public 
	// Returns:   ָʾ�����Ƿ����ͷŻ�����
	// Qualifier: ������
	// Parameter: ����������
	//************************************
	typedef bool(*LPOnRecvSocketData)(BYTE buf[], int len);

	//************************************
	// Method:    �յ�socket�ͻ����¼�����ָ��
	// FullName:  NetworkCommunication::LPOnRecvNotifyEvt
	// Access:    public 
	// Returns:   �Ƿ��Ѵ���
	// Qualifier: �¼�����
	// Parameter: ��Ϣ
	//************************************
	typedef bool(*LPOnRecvNotifyEvt)(SocketClientEvtType type, TCHAR* msg);

	//tcp�ͻ���
	class CTcpClient
	{
		//ʧȥ���������ԭ��ö��
		enum LoseConnectReason
		{
			Server,//����������Ͽ�
			Client,//�ͻ��������Ͽ�
			Net//�������
		};

	protected:
		const TCHAR* m_strServerIP;//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bIsCleaned;//�Ƿ�������
		SOCKADDR_IN m_addrSrv;//����˵�ַ
		SOCKET m_socket;//�ͻ���Socket
		bool m_bInited;//�Ƿ��ʼ��
		LPOnRecvSocketData m_lpfnOnRecvSocketData;//����socket���ݻص�����
		int m_nRecvSocketBufLen;//����Socket�������ܳ���
		char* m_pRecvSocketBuf;//����Socket������
		LPOnRecvNotifyEvt m_lpfnOnRecvNotifyEvt;//����֪ͨ�¼��ص�����
		bool m_bHaslpfnRecvSocketData;//�Ƿ����н���socket���ݻص�����
		bool m_bConnected;//�Ƿ��������Ϸ����
		int m_nReconnectTimeSpan;//����ʧ�ܺ���ʱ��(����)
		int m_nReconnectTimes;//������������(0:һֱ����)(Ĭ��1)
		int m_nReconnected;//�Ͽ�������������
		bool m_bReconnecting;//������������
		bool m_bAutoReconnect;//���ߺ��Ƿ��Զ���������
		bool m_bExitThread;//ָʾ�߳�Ӧ���˳�(ֻ���������������òŸ�ֵ"true")

	protected:
		//************************************
		// Method:    ��ʼ��socket
		// FullName:  NetworkCommunication::CSocketClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    ��ʼ���ͻ���socket
		// FullName:  NetworkCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    �������ӷ����
		// FullName:  NetworkCommunication::CSocketClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    ����Socket
		// FullName:  NetworkCommunication::CSocketClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    ����֪ͨ�¼�
		// FullName:  NetworkCommunication::CSocketClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ����
		// Parameter: ��Ϣ
		//************************************
		virtual void SendNotifyEvt(SocketClientEvtType type, TCHAR* msg);

		//************************************
		// Method:    ��ӡ��Ϣ
		// FullName:  NetworkCommunication::CSocketClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ��Ϣ
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    ʧȥ���������
		// FullName:  NetworkCommunication::CSocketClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ԭ��
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    �������Ϸ����
		// FullName:  NetworkCommunication::CSocketClient::OnConnected
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
		// FullName:  NetworkCommunication::CSocketClient::Init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: �����IP
		// Parameter: ����˶˿�
		// Parameter: ������Ϣ�ص�����
		// Parameter: �ص�����ָ��
		//************************************
		virtual void Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt = NULL, int socketBufLen = 1024,
			bool autoReconnect = true, int reconnectTimes = 3, int reconnectTimeSpan = 1500);

		//************************************
		// Method:    ���ý���socket���ݻص�����
		// FullName:  NetworkCommunication::CSocketClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ����socket���ݻص�����
		//************************************
		virtual void SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData);

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    ǿ���������ӷ����
		// FullName:  NetworkCommunication::CSocketClient::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Reconnect();

		//************************************
		// Method:    ���ӷ����
		// FullName:  NetworkCommunication::CSocketClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   �Ƿ�Ӧ���˳��߳�
		// Qualifier:
		//************************************
		virtual bool ConnectServer();

		//************************************
		// Method:    �ر�����������
		// FullName:  NetworkCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    ��ȡ�����Socket
		// FullName:  NetworkCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    ��ȡSocket����
		// FullName:  NetworkCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   �Ƿ���˳��߳�
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool ReadSocketData();

		//************************************
		// Method:    ��������
		// FullName:  NetworkCommunication::CSocketClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: �ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		virtual bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ����״̬
		// FullName:  NetworkCommunication::CSocketClient::GetConnectStatus
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool GetConnectStatus();

		//************************************
		// Method:    �յ�socket����
		// FullName:  NetworkCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: BYTE buf[]
		// Parameter: int len
		//************************************
		virtual void OnRecvSocketData(BYTE buf[], int len);

		//************************************
		// Method:    ģ��һ�η���˷���
		// FullName:  NetworkCommunication::CSocketClient::SimularServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}