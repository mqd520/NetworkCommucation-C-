#include "stdafx.h"
#include "Include/tc/SocketTool.h"

#define	_WINSOCK_DEPRECATED_NO_WARNINGS

#pragma warning(disable:4996)

namespace tc
{
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

			for (vector<SocketCallbackInfo>::iterator it; it != vecFNs.end(); it++)
			{
				it->lpfn(ch, it->lpParam);
			}
		}
	}

	void SocketTool::RegErrorCallback(LPErrorCallback lpfn, void* lpParam)
	{
		bool b = false;
		for (vector<SocketCallbackInfo>::iterator it; it != vecFNs.end(); it++)
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
		for (vector<SocketCallbackInfo>::iterator it; it != vecFNs.end(); it++)
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
			ProcessErrorInfo("WSAStartup", WSAGetLastError(), "", b);
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
			ProcessErrorInfo("::socket", WSAGetLastError(), "create socket fail", b);
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
			char ch[50] = { 0 };
			sprintf_s(ch, "bind fail, ip: %s, port: %d", ip.c_str(), port);
			ProcessErrorInfo("::bind", WSAGetLastError(), ch, b);
			return false;
		}
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