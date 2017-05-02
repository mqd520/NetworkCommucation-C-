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

		//�Ƿ�����˴���
		bool IsErr();

		//��ȡ���һ�δ�����Ϣ
		TCHAR* GetLastErr();

		//��ʼ��socket����
		bool Init();

		//�ͷ���Դ
		void Release();

		//����һ��socket(tcp)
		SOCKET CreateTcpSocket();

		SOCKADDR_IN GetSockAddr(TCHAR* ip, int port);

		SOCKADDR_IN CreateSocketAddr(TCHAR* ip, int port);

		bool Connect(SOCKET socket, TCHAR* ip, int port);

		int Read(SOCKET socket, char* buf, int len);

		void CloseSocket(SOCKET socket);

		bool Bind(SOCKET socket, TCHAR* ip, int port);

		bool Listen(SOCKET socket);

		void SetNonBlock(SOCKET socket);

		SOCKET Accept(SOCKET socket, TCHAR* ip, int port);

		void GetIpAndPort(SOCKET socket, TCHAR* ip, int* port);
	};
}