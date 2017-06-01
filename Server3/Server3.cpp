// Server3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void GetIpAndPort(SOCKET socket, TCHAR* ip, int* port);
wstring MultiByteToUTF8(const char* str);

int _tmain(int argc, _TCHAR* argv[])
{
	int nPort = 0;
	_tprintf(_T("Please enter listen port: "), nPort);
	_tscanf(_T("%d"), &nPort);

	int nRecved = 0;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
	{
		SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(nPort);
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		int result = bind(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == 0)
		{
			::listen(socket, SOMAXCONN);
			_tprintf(_T("Listen success! \n"), nPort);
			_tprintf(_T("Start accept client connection. \n"));
			while (true)
			{
				SOCKET s = ::accept(socket, (SOCKADDR*)&addr, NULL);
				nRecved++;
				TCHAR ip[20];
				int port = 0;
				GetIpAndPort(s, ip, &port);
				_tprintf(_T("[Index: %d] Recv a new client connection: %s:%d \n"), nRecved, ip, port);
			}

			::closesocket(socket);
			::WSACleanup();
		}
		else
		{
			_tprintf(_T("Bind failed! \n"));
		}
	}
	else
	{
		_tprintf(_T("WSAStartup failed! \n"));
	}
	::system("pause");
	return 0;
}

void GetIpAndPort(SOCKET socket, TCHAR* ip, int* port)
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

wstring MultiByteToUTF8(const char* str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wchar_t* strUTF = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strUTF, nlen);
	wstring result = strUTF;
	delete  strUTF;
	return result;
}

