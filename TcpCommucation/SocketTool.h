#pragma once
#include <WinSock2.h>
#include <string>

using namespace std;

namespace tc
{
	class SocketTool
	{
	public:
		SocketTool();
		~SocketTool();

	public:
		static string GetPeerIpAndPort(SOCKET socket, int* port);
	};
}