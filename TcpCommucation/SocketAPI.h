#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace tc
{
	//socket管理
	class CSocketAPI
	{
	protected:
		bool m_bErr;//是否产生错误
		TCHAR* m_strMsg;//错误信息

	protected:
		//保存错误信息
		void SaveErr(TCHAR* msg);

	public:
		CSocketAPI();
		~CSocketAPI();

		//是否产生了错误
		bool IsErr();

		//获取最后一次错误信息
		TCHAR* GetLastErr();

		//初始化socket环境
		static bool Init();

		//释放资源
		static void Release();

		//创建一个socket(tcp)
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