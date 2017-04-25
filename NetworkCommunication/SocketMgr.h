#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace NetworkCommunication
{
	//socket����
	class CSocketMgr
	{
	protected:
		bool m_bErr;//�Ƿ��������
		TCHAR* m_strMsg;//������Ϣ

	protected:
		//���������Ϣ
		void SaveErr(TCHAR* msg);

	public:
		CSocketMgr();
		~CSocketMgr();

		//��ʼ��socket����
		bool Init();

		//�ͷ���Դ
		void Release();

		//�Ƿ�����˴���
		bool IsErr();

		//��ȡ���һ�δ�����Ϣ
		TCHAR* GetLastErr();

		//����һ��socket(tcp)
		SOCKET CreateTcpSocket();

		//************************************
		// Method:    ����socket��ַ��Ϣ
		// FullName:  NetworkCommunication::CSocketMgr::CreateSocketAddr
		// Access:    public 
		// Returns:   ��ַ��Ϣ
		// Qualifier:
		// Parameter: IP
		// Parameter: �˿�
		//************************************
		SOCKADDR_IN CreateSocketAddr(TCHAR* ip, int port);

		//************************************
		// Method:    ͬ������
		// FullName:  NetworkCommunication::CSocketMgr::Connect
		// Access:    public 
		// Returns:   �Ƿ�ɹ�
		// Qualifier:
		// Parameter: socket
		// Parameter: ����˵�ַ
		//************************************
		bool Connect(SOCKET socket, SOCKADDR_IN* addr);

		int Read(SOCKET socket, char* buf, int len);

		//�ر�socket
		void CloseSocket(SOCKET socket);
	};
}