#include "stdafx.h"
#include "Include/tc/SocketTool.h"

#define	_WINSOCK_DEPRECATED_NO_WARNINGS

#pragma warning(disable:4996)

namespace tc
{
	vector<SocketCallbackInfo> SocketTool::vecFNs;

	SocketTool::SocketTool()
	{

	}

	SocketTool::~SocketTool()
	{

	}

	void SocketTool::ProcessErrorInfo(string fn, int code, string remark /*= ""*/, bool b /*= true*/)
	{
		if (b)
		{
			char ch[256] = { 0 };
			sprintf_s(ch, "socket error, fn: %s, code: %d, remark: %s", fn.c_str(), code, remark.c_str());

			for (vector<SocketCallbackInfo>::iterator it = vecFNs.begin(); it != vecFNs.end(); it++)
			{
				it->lpfn(ch, it->lpParam);
			}
		}
	}

	void SocketTool::RegErrorCallback(LPErrorCallback lpfn, void* lpParam)
	{
		bool b = false;
		for (vector<SocketCallbackInfo>::iterator it = vecFNs.begin(); it != vecFNs.end(); it++)
		{
			if (it->lpfn == lpfn)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			SocketCallbackInfo info;
			info.lpfn = lpfn;
			info.lpParam = lpParam;
			vecFNs.push_back(info);
		}
	}

	void SocketTool::RemoveErrorCallback(LPErrorCallback lpfn)
	{
		for (vector<SocketCallbackInfo>::iterator it = vecFNs.begin(); it != vecFNs.end(); it++)
		{
			if (it->lpfn == lpfn)
			{
				vecFNs.erase(it);
				break;
			}
		}
	}

	bool SocketTool::Init(bool b /*= true*/)
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			if (b)
			{
				ProcessErrorInfo("WSAStartup", WSAGetLastError(), "", b);
			}

			return false;
		}
		return true;
	}

	void SocketTool::Release()
	{
		WSACleanup();
	}

	SOCKET SocketTool::CreateTcpSocket(bool b /*= true*/)
	{
		SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			if (b)
			{
				ProcessErrorInfo("socket", WSAGetLastError(), "create socket fail", b);
			}
		}

		return s;
	}

	SOCKADDR_IN SocketTool::GetSocketAddr(string ip, int port)
	{
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (ip == "")
		{
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
		}
		else
		{
			addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		}
		return addr;
	}

	bool SocketTool::Bind(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int result = bind(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == 0)
		{
			return true;
		}
		else
		{
			if (b)
			{
				char ch[50] = { 0 };
				sprintf_s(ch, "bind fail, ip: %s, port: %d", ip.c_str(), port);
				ProcessErrorInfo("bind", WSAGetLastError(), ch, b);
			}

			return false;
		}
	}

	bool SocketTool::Listen(SOCKET socket, string ip, int port, int backlog /*= SOMAXCONN*/, bool b /*= true*/)
	{
		int ret = listen(socket, backlog);
		if (ret == 0)
		{
			return true;
		}
		else
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "listen fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("listen", WSAGetLastError(), ch, b);
			}

			return false;
		}
	}

	SOCKET SocketTool::Accept(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		SOCKET client = ::accept(socket, (SOCKADDR*)&addr, NULL);
		if (client == INVALID_SOCKET)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "accept fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("accept", WSAGetLastError(), ch, b);
			}
		}

		return client;
	}

	bool SocketTool::Recv(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b /*= true*/)
	{
		int ret = ::recv(socket, (char*)pBuf, len, 0);

		if (actuallyLen != NULL)
		{
			*actuallyLen = ret;
		}

		if (ret > 0)
		{
			return true;
		}
		else
		{
			if (ret == SOCKET_ERROR)
			{
				if (b)
				{
					char ch[100] = { 0 };
					sprintf_s(ch, "recv fail, socket: %d", socket);
					ProcessErrorInfo("recv", WSAGetLastError(), ch, b);
				}
			}

			return false;
		}
	}

	bool SocketTool::Send(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b /*= true*/)
	{
		int ret = ::send(socket, (const char*)pBuf, len, 0);

		if (actuallyLen != NULL)
		{
			*actuallyLen = ret;
		}

		if (ret > 0)
		{
			return true;
		}
		else
		{
			if (ret == SOCKET_ERROR)
			{
				if (b)
				{
					char ch[100] = { 0 };
					sprintf_s(ch, "send fail, socket: %d", socket);
					ProcessErrorInfo("send", WSAGetLastError(), ch, b);
				}
			}

			return false;
		}
	}

	bool SocketTool::Connect(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int ret = ::connect(socket, (SOCKADDR*)&addr, sizeof(addr));

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "connect fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("connect", WSAGetLastError(), ch, b);
			}

			return false;
		}

		return true;
	}

	int SocketTool::Select(int nfds, fd_set* readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout, bool b /*= true*/)
	{
		int ret = ::select(nfds, readfds, writefds, exceptfds, timeout);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				ProcessErrorInfo("select", WSAGetLastError(), "select fail", b);
			}
		}
		return ret;
	}


	void SocketTool::ShutDown(SOCKET socket, int how /*= SD_BOTH*/, bool b /*= true*/)
	{
		int ret = ::shutdown(socket, how);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "shutdown fail, socket: %d", socket);
				ProcessErrorInfo("shutdown", WSAGetLastError(), ch, b);
			}
		}
	}

	bool SocketTool::CloseSocket(SOCKET socket, bool b /*= true*/)
	{
		int ret = ::closesocket(socket);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "closesocket fail, socket: %d", socket);
				ProcessErrorInfo("closesocket", WSAGetLastError(), ch, b);
			}
			return false;
		}

		return true;
	}

	void SocketTool::SetNonBlock(SOCKET socket, bool nonblock /*= true*/)
	{
		u_long mode = nonblock ? 1 : 0;
		ioctlsocket(socket, FIONBIO, &mode);
	}

	string SocketTool::GetPeerIpAndPort(SOCKET socket, int* port)
	{
		string strIP = "";

		SOCKADDR_IN addr;
		int len = sizeof(addr);
		int result = ::getpeername(socket, (SOCKADDR*)&addr, &len);
		if (result != SOCKET_ERROR)
		{
			char* ipTmp = inet_ntoa(addr.sin_addr);
			strIP = ipTmp;

			if (port != NULL)
			{
				*port = ntohs(addr.sin_port);
			}
		}

		return strIP;
	}

	string SocketTool::GetLocalIP()
	{
		string ip = "";

		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret == 0)
		{
			char hostname[256];
			ret = gethostname(hostname, sizeof(hostname));
			if (ret != SOCKET_ERROR)
			{
				HOSTENT* host = gethostbyname(hostname);
				if (host != NULL)
				{
					char ch[20] = { 0 };
					strcpy(ch, inet_ntoa(*(in_addr*)*host->h_addr_list));
					ip = ch;
				}
			}
		}

		return ip;
	}
}