#include "stdafx.h"
#include "SocketTool.h"

namespace tc
{
	SocketTool::SocketTool()
	{

	}

	SocketTool::~SocketTool()
	{

	}

	string SocketTool::GetPeerIpAndPort(SOCKET socket, int* port)
	{
		string strIP = "";

		SOCKADDR_IN addr;
		int len = sizeof(addr);
		int result = ::getpeername(socket, (SOCKADDR*)&addr, &len);
		if (result != SOCKET_ERROR)
		{
			char* ipTmp = ::inet_ntoa(addr.sin_addr);
			strIP = ipTmp;

			if (port != NULL)
			{
				*port = ntohs(addr.sin_port);
			}
		}

		return strIP;
	}
}