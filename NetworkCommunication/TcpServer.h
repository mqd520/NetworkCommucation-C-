#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>

namespace NetworkCommunication
{
	//tcp�����
	class CTcpServer
	{
	protected:
		//��ʼ��socket����
		void InitSocket();

	public:
		CTcpServer();
		~CTcpServer();
	};
}