#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace TCPCommunication
{
	//************************************
	// Method:    �յ�socket����
	// FullName:  TCPCommunication::LPOnRecvSocketData
	// Access:    public 
	// Returns:   ָʾ�����Ƿ����ͷŻ�����
	// Qualifier: ������
	// Parameter: ����������
	//************************************
	typedef bool(*LPOnRecvSocketData)(BYTE buf[], int len);

	//�¼�����
	enum SocketClientEvtType
	{
		Info,//��Ϣ
		error,//����
		disconnected,//ʧȥ���������
		connected,//�����Ϸ����
		Debug//����
	};

	//��Ϣ֪ͨ�ṹ��
	typedef struct tagNotifyEvt
	{
		bool haveMsg;//�Ƿ����¼�
		SocketClientEvtType type;//�¼�����
		TCHAR* msg;//��Ϣ
	}NotifyEvt, *LPNotifyEvt;

	//************************************
	// Method:    �յ�socket�ͻ����¼�����ָ��
	// FullName:  TCPCommunication::LPOnRecvNotifyEvt
	// Access:    public 
	// Returns:   �Ƿ��Ѵ���
	// Qualifier: �¼�����
	// Parameter: ��Ϣ
	//************************************
	typedef bool(*LPOnRecvNotifyEvt)(SocketClientEvtType type, TCHAR* msg);

	//�߳�ѭ����Ϣ
	typedef struct tagThreadWhileInfo
	{
		bool bReadSocketData;
		bool bConnectServer;
		bool bReadCatchSocketData;
		bool bReadNotifyEvt;
	}ThreadWhileInfo, *LPThreadWhileInfo;

	//Socket�ͻ�����
	class CSocketClient
	{
	private:
		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//���
			DWORD nThreadID;//ID
			bool bPause;//�Ƿ�����ͣ
		}ThreadInfo, *LPThreadInfo;

		//����Socket��������Ϣ
		typedef struct tagCatchSocketBufInfo
		{
			int adress;//ָ���ַ
			int len;//����������
		}CatchSocketBufInfo, *LPCatchSocketBufInfo;

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
		ThreadInfo m_tiReadSocketData;//��ȡsocket�����߳���Ϣ
		bool m_bInited;//�Ƿ��ʼ��
		LPOnRecvSocketData m_lpfnOnRecvSocketData;//����socket���ݻص�����
		TCHAR* m_strClientIP;//�ͻ���IP
		int m_nClientPort;//�ͻ��˶˿�
		int m_nRecvSocketBufLen;//����Socket�������ܳ���
		char* m_pRecvSocketBuf;//����Socket������
		NotifyEvt m_evt;//�¼�
		ThreadInfo m_tiReadNotifyEvt;//��ȡ֪ͨ��Ϣ�߳���Ϣ
		LPOnRecvNotifyEvt m_lpfnOnRecvNotifyEvt;//����֪ͨ��Ϣ�ص�����
		const int m_msgbufsize = 1024;//֪ͨ��Ϣ��������С
		vector<CatchSocketBufInfo> m_vecCatchRecvSocketBuf;//������ջ���������
		ThreadInfo m_tiReadCatchSocketData;//��ȡ����socket�����߳���Ϣ
		bool m_bHaslpfnRecvSocketData;//�Ƿ����н���socket���ݻص�����
		ThreadInfo m_tiConnectServer;//���ӷ�����߳���Ϣ
		bool m_bConnected;//�Ƿ��������Ϸ����
		int m_nReconnectTimeSpan;//����ʧ�ܺ���ʱ��(����)
		int m_nReconnectTimes;//������������(0:һֱ����)(Ĭ��1)
		int m_nReconnected;//�Ͽ�������������
		bool m_bReconnecting;//������������
		bool m_bAutoReconnect;//���ߺ��Ƿ��Զ���������
		ThreadWhileInfo m_whileinfo;//�߳�ѭ����Ϣ

	protected:
		//************************************
		// Method:    ��ʼ��socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitSocket();

		//************************************
		// Method:    ��ʼ���ͻ���socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void CreateClientSocket();

		//************************************
		// Method:    �������ӷ����
		// FullName:  TCPCommunication::CSocketClient::ReconnectServer
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReconnectServer();

		//************************************
		// Method:    ����Socket
		// FullName:  TCPCommunication::CSocketClient::CleanSocket
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanSocket();

		//************************************
		// Method:    �����߳�
		// FullName:  TCPCommunication::CSocketClient::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanThread();

		//************************************
		// Method:    ����֪ͨ�¼�
		// FullName:  TCPCommunication::CSocketClient::SaveNotifyEvt
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ����
		// Parameter: ��Ϣ
		//************************************
		virtual void SaveNotifyEvt(SocketClientEvtType type, TCHAR* msg);

		//************************************
		// Method:    ���ÿͻ���IP�Ͷ˿�
		// FullName:  CSocketClient::SetAddressBySocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: SOCKET socket
		//************************************
		virtual bool SetAddressBySocket(SOCKET socket);

		//************************************
		// Method:    ��ӡ��Ϣ
		// FullName:  TCPCommunication::CSocketClient::Printf
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ��Ϣ
		//************************************
		virtual void Printf(TCHAR* msg);

		//************************************
		// Method:    ���ͽ��յ���socket���ݵ�������
		// FullName:  TCPCommunication::CSocketClient::SendRecvData
		// Access:    virtual protected 
		// Returns:   ָʾ�����Ƿ����ͷŻ�����
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual bool SendRecvData(BYTE buf[], int len);

		//************************************
		// Method:    ������̨�߳�
		// FullName:  TCPCommunication::CSocketClient::CreateThread
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CreateThread();

		//************************************
		// Method:    ʧȥ���������
		// FullName:  TCPCommunication::CSocketClient::OnLoseConnect
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: ԭ��
		//************************************
		virtual void OnLoseConnect(LoseConnectReason reason);

		//************************************
		// Method:    ��ͣ(�ָ�)�߳�
		// FullName:  TCPCommunication::CSocketClient::PauseThread
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: �Ƿ���ͣ
		// Parameter: �߳���Ϣ
		//************************************
		virtual void PauseThread(bool pause, LPThreadInfo ti);

		//************************************
		// Method:    �������Ϸ����
		// FullName:  TCPCommunication::CSocketClient::OnConnected
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnected();

	public:
		CSocketClient();
		~CSocketClient();

		//************************************
		// Method:    ��ʼ��
		// FullName:  TCPCommunication::CSocketClient::Init
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
		// FullName:  TCPCommunication::CSocketClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ����socket���ݻص�����
		//************************************
		virtual void SetCallback(LPOnRecvSocketData lpfnOnRecvSocketData);

		//************************************
		// Method:    ���ӷ����
		// FullName:  TCPCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    ǿ���������ӷ����
		// FullName:  TCPCommunication::CSocketClient::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Reconnect();

		//************************************
		// Method:    ���ӷ����
		// FullName:  TCPCommunication::CSocketClient::ConnectServer
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual void ConnectServer();

		//************************************
		// Method:    �ر�����������
		// FullName:  TCPCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    ��ȡ�����Socket
		// FullName:  TCPCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetClientSocket();

		//************************************
		// Method:    ��ȡSocket����
		// FullName:  TCPCommunication::CSocketClient::OnRecvSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void ReadSocketData();

		//************************************
		// Method:    ��ȡ�߳�ѭ����Ϣ
		// FullName:  TCPCommunication::CSocketClient::GetWhileInfo
		// Access:    virtual public 
		// Returns:   TCPCommunication::CSocketClient::ThreadWhileInfo
		// Qualifier:
		//************************************
		virtual ThreadWhileInfo GetWhileInfo();

		//************************************
		// Method:    �����ͷ���Դ
		// FullName:  TCPCommunication::CSocketClient::Dispose
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Dispose();

		//************************************
		// Method:    ��������
		// FullName:  TCPCommunication::CSocketClient::SendData
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: �ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		virtual bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    ��ȡ֪ͨ��Ϣ�����͸�������
		// FullName:  TCPCommunication::CSocketClient::NotifyMsg
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReadNotifyEvt();

		//************************************
		// Method:    ��ȡ����Socket���ݲ����͸�������
		// FullName:  TCPCommunication::CSocketClient::SendSocketData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void ReadCatchSocketData();

		//************************************
		// Method:    ��ȡ����״̬
		// FullName:  TCPCommunication::CSocketClient::GetConnectStatus
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool GetConnectStatus();

		//************************************
		// Method:    ģ��һ�η���˷���
		// FullName:  TCPCommunication::CSocketClient::SimularServerData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		virtual void SimulateServerData(BYTE* buf, int len);
	};
}