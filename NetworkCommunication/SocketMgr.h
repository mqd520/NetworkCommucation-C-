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

		//初始化socket环境
		bool Init();

		//释放资源
		void Release();

		//是否产生了错误
		bool IsErr();

		//获取最后一次错误信息
		TCHAR* GetLastErr();

		//创建一个socket(tcp)
		SOCKET CreateTcpSocket();

		//************************************
		// Method:    创建socket地址信息
		// FullName:  NetworkCommunication::CSocketMgr::CreateSocketAddr
		// Access:    public 
		// Returns:   地址信息
		// Qualifier:
		// Parameter: IP
		// Parameter: 端口
		//************************************
		SOCKADDR_IN CreateSocketAddr(TCHAR* ip, int port);

		//************************************
		// Method:    同步连接
		// FullName:  NetworkCommunication::CSocketMgr::Connect
		// Access:    public 
		// Returns:   是否成功
		// Qualifier:
		// Parameter: socket
		// Parameter: 服务端地址
		//************************************
		bool Connect(SOCKET socket, SOCKADDR_IN* addr);

		int Read(SOCKET socket, char* buf, int len);

		//关闭socket
		void CloseSocket(SOCKET socket);
	};
}