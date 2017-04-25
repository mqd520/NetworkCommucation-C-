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
		m_bErr = false;
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			m_bErr = true;
			m_strMsg = _T("create socket failed! \n");
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
		m_bErr = false;
		SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socket == INVALID_SOCKET)
		{
			m_bErr = true;
			m_strMsg = _T("´´½¨SocketÊ§°Ü!\n");
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

	bool CSocketMgr::Connect(SOCKET socket, SOCKADDR_IN* addr)
	{
		m_bErr = false;
		int result = ::connect(socket, (SOCKADDR*)addr, sizeof(addr));
		if (result == SOCKET_ERROR)
		{
			m_bErr = true;
			TCHAR str[100];
			char*  ip = ::inet_ntoa(addr->sin_addr);
#ifdef _UNICODE
			wstring str1 = MultiByteToUTF8(ip);
			wsprintf(str, _T("failed to connect kserver: %s:%d\n"), str1.c_str(), addr->sin_port);
#else
			wsprintf(str, _T("failed to connect server: %s:%d\n"), ip, 8070);
#endif
			SaveErr(str);
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
}