#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace NetworkCommunication
{
	//tcp服务端
	class CTcpServer
	{
	protected:
		//初始化socket环境
		void InitSocket();

	public:
		CTcpServer();
		~CTcpServer();
	};
}