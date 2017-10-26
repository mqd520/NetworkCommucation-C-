#include "stdafx.h"
#include <stdio.h>
#include <string>
#include "SocketAPI.h"
#include "MemoryTool.h"

using namespace std;

namespace NetworkCommunication
{
	CSocketAPI::CSocketAPI() :
		m_strMsg(NULL), m_bErr(false)
	{
		m_strMsg = new TCHAR[100];
		memset(m_strMsg, 0, sizeof(TCHAR));
	}

	CSocketAPI::~CSocketAPI()
	{
		if (m_strMsg)
		{
			delete m_strMsg;
		}
	}

	bool CSocketAPI::Init()
	{
		WSADATA wsaData;
		if (::WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			return false;
		}
		return true;
	}

	void CSocketAPI::Release()
	{
		::WSACleanup();
	}

	void CSocketAPI::SaveErr(TCHAR* msg)
	{
		::memcpy(m_strMsg, msg, 100);
	}

	bool CSocketAPI::IsErr()
	{
		return m_bErr;
	}

	TCHAR* CSocketAPI::GetLastErr()
	{
		return m_strMsg;
	}

	SOCKET CSocketAPI::CreateTcpSocket()
	{
		SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socket == INVALID_SOCKET)
		{

		}
		return socket;
	}

	SOCKADDR_IN CSocketAPI::GetSocketAddr(TCHAR* ip, int port)
	{
		m_bErr = false;
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
#ifdef _UNICODE
		string str = UTF8ToMultiByte(ip);
		addr.sin_addr.S_un.S_addr = inet_addr(str.c_str());
#else
		addr.sin_addr.S_un.S_addr = inet_addr(ip);
#endif // _UNICODE
		return addr;
	}

	bool CSocketAPI::Connect1(SOCKET socket, TCHAR* ip, int port)
	{
		m_bErr = false;
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int result = ::connect(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == SOCKET_ERROR)
		{
			m_bErr = true;
		}
		return !m_bErr;
	}

	bool CSocketAPI::CloseSocket(SOCKET socket)
	{
		int result = ::closesocket(socket);
		return true;
	}

	int CSocketAPI::Recv(SOCKET socket, BYTE* buf, int len)
	{
		m_bErr = false;
		int len1 = ::recv(socket, (char*)buf, len, 0);
		if (len1 == SOCKET_ERROR)
		{
			m_bErr = true;

		}
		return len1;
	}

	bool CSocketAPI::Bind(SOCKET socket, TCHAR* ip, int port)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int result = bind(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == 0)
		{
			return true;
		}
		else
		{
			//错误处理
			return false;
		}
	}

	bool CSocketAPI::Listen(SOCKET socket, int max)
	{
		int result = ::listen(socket, max);
		if (result == 0)
		{
			return true;
		}
		else
		{
			//错误处理
			return false;
		}
	}

	void CSocketAPI::SetNonBlock(SOCKET socket)
	{
		u_long mode = 1;//打开异步
		ioctlsocket(socket, FIONBIO, &mode);
	}

	SOCKET CSocketAPI::Accept(SOCKET socket, TCHAR* ip, int port)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		return Accept(socket, addr);
	}

	SOCKET CSocketAPI::Accept(SOCKET socket, SOCKADDR_IN addr)
	{
		SOCKET client = ::accept(socket, (SOCKADDR*)&addr, NULL);
		if (client == INVALID_SOCKET)
		{
			//错误处理
			return 0;
		}
		else
		{
			return client;
		}
	}

	void CSocketAPI::GetPeerIpAndPort(SOCKET socket, TCHAR* ip, int* port)
	{
		SOCKADDR_IN addr;
		int len = sizeof(addr);
		int result = ::getpeername(socket, (SOCKADDR*)&addr, &len);
		if (result != SOCKET_ERROR)
		{
			if (ip != NULL)
			{
				char* ipTmp = ::inet_ntoa(addr.sin_addr);
#ifdef _UNICODE
				wstring str = MultiByteToUTF8(ipTmp);
				wcscpy(ip, str.c_str());
#else
				strcpy(ip, ipTmp);
#endif // _UNICODE
			}
			if (port != NULL)
			{
				*port = ntohs(addr.sin_port);
			}
		}
	}

	int CSocketAPI::Select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval* timeout)
	{
		int result = ::select(nfds, readfds, writefds, exceptfds, timeout);
		return result;
	}

	bool CSocketAPI::Send(SOCKET s, BYTE buf[], int len, int* actualLen)
	{
		bool result = false;
		int sended = 0;
		while (true)
		{
			int actualLen = ::send(s, (const char*)(buf + sended), len - sended, 0);
			if (actualLen > 0)
			{
				sended += actualLen;

				if (sended == len)
				{
					result = true;
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
		if (actualLen != NULL)
		{
			*actualLen = sended;
		}
		return result;
	}
}