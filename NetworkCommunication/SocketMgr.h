#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace NetworkCommunication
{
	//socket管理
	class CSocketMgr
	{
	protected:
		bool m_bErr;//是否产生错误
		TCHAR* m_strMsg;//错误信息

	protected:
		//保存错误信息
		void SaveErr(TCHAR* msg);

	public:
		CSocketMgr();
		~CSocketMgr();

		//是否产生了错误
		bool IsErr();

		//获取最后一次错误信息
		TCHAR* GetLastErr();

		//初始化socket环境
		bool Init();

		//释放资源
		void Release();

		//创建一个socket(tcp)
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