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

	//Socket�ͻ�����
	class CSocketClient
	{
	private:
		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//���
			DWORD nThreadID;//ID
		}ThreadInfo, *LPThreadInfo;

		//����Socket��������Ϣ
		typedef struct tagCatchSocketBufInfo
		{
			int adress;//ָ���ַ
			int len;//����������
		}CatchSocketBufInfo, *LPCatchSocketBufInfo;

	protected:
		const TCHAR* m_strServerIP;//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bIsCleaned;//�Ƿ�������
		bool m_bIsConnected;//�Ƿ��Ѿ������Ϸ����
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

	protected:
		//************************************
		// Method:    ��ʼ���ͻ���socket
		// FullName:  TCPCommunication::CSocketClient::InitSocket
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool InitSocket();

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
		virtual void Init(const TCHAR* ip, int port, LPOnRecvNotifyEvt lpfnOnRecvNotifyEvt = NULL, int socketBufLen = 1024);

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
		// Method:    ���ӷ����(����)
		// FullName:  TCPCommunication::CSocketClient::Connect
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool Connect();

		//************************************
		// Method:    ���ӷ����(������)
		// FullName:  TCPCommunication::CSocketClient::ConnectUnasync
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool ConnectUnasync();

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