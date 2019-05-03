#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace tc
{
	//socket����
	class CSocketAPI
	{
	protected:
		bool m_bErr;//�Ƿ��������
		TCHAR* m_strMsg;//������Ϣ

	protected:
		//���������Ϣ
		void SaveErr(TCHAR* msg);

	public:
		CSocketAPI();
		~CSocketAPI();

		//�Ƿ�����˴���
		bool IsErr();

		//��ȡ���һ�δ�����Ϣ
		TCHAR* GetLastErr();

		//��ʼ��socket����
		static bool Init();

		//�ͷ���Դ
		static void Release();

		//����һ��socket(tcp)
		SOCKET CreateTcpSocket();

		SOCKADDR_IN GetSocketAddr(TCHAR* ip, int port);

		bool Connect1(SOCKET socket, TCHAR* ip, int port);

		int Recv(SOCKET socket, BYTE* buf, int len);

		bool CloseSocket(SOCKET socket);

		bool Bind(SOCKET socket, TCHAR* ip, int port);

		bool Listen(SOCKET socket, int max = SOMAXCONN);

		void SetNonBlock(SOCKET socket);

		SOCKET Accept(SOCKET socket, TCHAR* ip, int port);

		SOCKET Accept(SOCKET socket, SOCKADDR_IN addr);

		void GetPeerIpAndPort(SOCKET socket, TCHAR* ip, int* port);

		int Select(int nfds, fd_set* readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);

		bool Send(SOCKET s, BYTE buf[], int len, int* actualLen = NULL);
	};
}