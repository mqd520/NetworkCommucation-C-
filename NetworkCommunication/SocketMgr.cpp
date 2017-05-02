#include "stdafx.h"
#include <stdio.h>
#include <string>
#include "SocketMgr.h"
#include "MemoryTool.h"

using namespace std;

namespace NetworkCommunication
{
	CSocketMgr::CSocketMgr() :
		m_strMsg(NULL), m_bErr(false)
	{
		m_strMsg = new TCHAR[100];
	}

	CSocketMgr::~CSocketMgr()
	{
		if (m_strMsg)
		{
			delete m_strMsg;
		}
	}

	bool CSocketMgr::Init()
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			return false;
		}
		return true;
	}

	void CSocketMgr::Release()
	{
		WSACleanup();
	}

	void CSocketMgr::SaveErr(TCHAR* msg)
	{
		::memcpy(m_strMsg, msg, 100);
	}

	bool CSocketMgr::IsErr()
	{
		return m_bErr;
	}

	TCHAR* CSocketMgr::GetLastErr()
	{
		return m_strMsg;
	}

	SOCKET CSocketMgr::CreateTcpSocket()
	{
		SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socket == INVALID_SOCKET)
		{

		}
		return socket;
	}

	SOCKADDR_IN CSocketMgr::CreateSocketAddr(TCHAR* ip, int port)
	{
		m_bErr = false;
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
#ifdef _UNICODE
		string strTmp = UTF8ToMultiByte(ip);
		addr.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
		addr.sin_addr.S_un.S_addr = inet_addr(ip);
#endif
		return addr;
	}

	bool CSocketMgr::Connect(SOCKET socket, TCHAR* ip, int port)
	{
		m_bErr = false;
		SOCKADDR_IN addr = GetSockAddr(ip, port);
		int result = ::connect(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == SOCKET_ERROR)
		{
			m_bErr = true;
		}
		return !m_bErr;
	}

	void CSocketMgr::CloseSocket(SOCKET socket)
	{
		::closesocket(socket);
	}

	int CSocketMgr::Read(SOCKET socket, char* buf, int len)
	{
		m_bErr = false;
		int len1 = ::recv(socket, buf, len, 0);
		if (len1 == SOCKET_ERROR)
		{
			m_bErr = true;

		}
		return 0;
	}

	bool CSocketMgr::Bind(SOCKET socket, TCHAR* ip, int port)
	{
		SOCKADDR_IN addr = GetSockAddr(ip, port);
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

	bool CSocketMgr::Listen(SOCKET socket)
	{
		int result = ::listen(socket, SOMAXCONN);
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

	void CSocketMgr::SetNonBlock(SOCKET socket)
	{
		u_long mode = 1;//打开异步
		ioctlsocket(socket, FIONBIO, &mode);
	}

	SOCKET CSocketMgr::Accept(SOCKET socket, TCHAR* ip, int port)
	{
		SOCKADDR_IN addr = GetSockAddr(ip, port);
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

	SOCKADDR_IN CSocketMgr::GetSockAddr(TCHAR* ip, int port)
	{
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (ip == NULL)
		{
			addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//绑定本地任意IP地址
		}
		else
		{
#ifdef _UNICODE
			string str = UTF8ToMultiByte((wchar_t*)ip);
			addr.sin_addr.S_un.S_addr = inet_addr(str.c_str());//绑定指定IP地址
#else
			addr.sin_addr.S_un.S_addr = inet_addr((char*)ip);//绑定指定IP地址
#endif // _UNICODE
		}
		return addr;
	}

	void CSocketMgr::GetIpAndPort(SOCKET socket, TCHAR* ip, int* port)
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
				wstring wstr = MultiByteToUTF8(ipTmp);
				wcscpy(ip, wstr.c_str());
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
}