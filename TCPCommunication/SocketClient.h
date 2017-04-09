#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

namespace TCPCommunication
{
	//����ָ��:�յ�tcp����
	typedef void(*LPOnRecvSocketData)(BYTE buf[], int len);

	//TcpClient�ͻ�����
	class CSocketClient
	{
	private:
		//�߳���Ϣ
		typedef struct tagThreadInfo
		{
			HANDLE hThread;
			DWORD nThreadID;
		}ThreadInfo;

	protected:
		const TCHAR* m_strServerIP;//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bIsCleaned;//�Ƿ�������
		bool m_bIsConnected;//�Ƿ��Ѿ������Ϸ����
		TCHAR* m_strLastError;//���һ�δ�����Ϣ
		SOCKADDR_IN m_addrSrv;//����˵�ַ
		SOCKET m_socket;//�ͻ���Socket
		ThreadInfo m_readThreadInfo;//���ݶ�ȡ�߳���Ϣ
		bool m_bInited;//��ʼ��
		LPOnRecvSocketData m_lpOnRecvData;//���ݻص�ָ��
		TCHAR* m_strClientIP;//�ͻ���IP
		int m_nClientPort;//�ͻ��˶˿�
		int m_nSocketBufLen;//���ջ�������С
		char* m_pRecvBuf;//���ջ�����

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
		// Method:    д��һ����־
		// FullName:  TCPCommunication::CSocketClient::WriteLine
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		// Parameter: string log
		//************************************
		virtual void WriteLine(string log);

		//************************************
		// Method:    �����߳�
		// FullName:  TCPCommunication::CSocketClient::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CleanThread();

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
		// Parameter: �ص�����ָ��
		//************************************
		virtual void Init(const TCHAR* ip, int port, LPOnRecvSocketData lpfn, int socketBufLen = 1024);

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
		// Method:    ��ʼ���ӷ����
		// FullName:  TCPCommunication::CSocketClient::StartConnect
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool StartConnect();

		//************************************
		// Method:    �ر�����������
		// FullName:  TCPCommunication::CSocketClient::CloseConnect
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    ��ȡ���һ�δ�����Ϣ
		// FullName:  TCPCommunication::CSocketClient::GetLastError
		// Access:    public 
		// Returns:   TCHAR*
		// Qualifier:
		//************************************
		virtual TCHAR* GetLastError();

		//************************************
		// Method:    ��ȡ�����Socket
		// FullName:  TCPCommunication::CSocketClient::GetServerSocket
		// Access:    public 
		// Returns:   SOCKET
		// Qualifier:
		//************************************
		virtual SOCKET GetServerSocket();

		//************************************
		// Method:    socket���ݽ��մ���
		// FullName:  TCPCommunication::CSocketClient::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: �ֽ�����
		// Parameter: �ֽ����鳤��
		//************************************
		virtual void OnRecvData(BYTE buf[], int len);

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
		// Method:    �Ƿ��ѳ�ʼ��
		// FullName:  TCPCommunication::CSocketClient::IsInited
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool IsInited();

		//************************************
		// Method:    ��ȡ���ջ�����
		// FullName:  TCPCommunication::CSocketClient::GetRecvBuf
		// Access:    virtual public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ��������С(���)
		//************************************
		virtual char* GetRecvBuf(int *len);
	};
}