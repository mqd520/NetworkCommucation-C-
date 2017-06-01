// Server4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

string UTF8ToMultiByte(const wchar_t* str);
void GetIpAndPort(SOCKET socket, TCHAR* ip, int* port);
wstring MultiByteToUTF8(const char* str);
void Dispose();

vector<SOCKET> list;

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR strServerIP[20] = { 0 };
	int nServerPort = 8010;
	int nConnectCount = 1;//连接总数
	_tprintf(_T("Please enter server IP: "));
	_tscanf(_T("%s"), strServerIP);
	_tprintf(_T("Please enter server port: "));
	_tscanf(_T("%d"), &nServerPort);
	_tprintf(_T("Please enter connect count: "));
	_tscanf(_T("%d"), &nConnectCount);


	int nIndex = 0;
	int nCreateSocketFailCount = 0;
	int nConnectSrvFailCount = 0;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
	{
		SOCKADDR_IN addrSrv;
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(nServerPort);
#ifdef _UNICODE
		string strTmp = UTF8ToMultiByte(strServerIP);
		addrSrv.sin_addr.S_un.S_addr = inet_addr(strTmp.c_str());
#else
		addrSrv.sin_addr.S_un.S_addr = inet_addr(strServerIP);
#endif
		_tprintf(_T("Start to connect server: %s:%d \n"), strServerIP, nServerPort);
		DWORD tStart = GetTickCount();
		DWORD tEnd;

		while (true)
		{
			_tprintf(_T("Index: %d \n"), nIndex + 1);

			_tprintf(_T("	    Start to create client socket \n"));
			SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			nIndex++;
			if (socket != INVALID_SOCKET)
			{
				list.push_back(socket);
				_tprintf(_T("	    Successed to create client socket,connecting to server \n"));
				int result = ::connect(socket, (SOCKADDR*)&addrSrv, sizeof(addrSrv));
				if (result != SOCKET_ERROR)
				{
					TCHAR ip[20];
					int port = 0;
					GetIpAndPort(socket, ip, &port);
					_tprintf(_T("	    [%s:%d] Successed to connect server! \n"), ip, port);
				}
				else
				{
					nConnectSrvFailCount++;
					_tprintf(_T("	    Failed to connect server! \n"));
				}
			}
			else
			{
				nCreateSocketFailCount++;
				_tprintf(_T("	    Failed to create client socket \n"));
			}

			if (nIndex == nConnectCount)
			{
				tEnd = GetTickCount();
				break;
			}
		}

		_tprintf(_T("\nConnect Complete! \n"));
		_tprintf(_T("Total: %d \n"), nConnectCount);
		_tprintf(_T("Duration(ms): %d \n"), tEnd - tStart);
		_tprintf(_T("Successed to Create Socket: %d \n"), nConnectCount - nCreateSocketFailCount);
		_tprintf(_T("Failed to Create Socket: %d \n"), nCreateSocketFailCount);
		_tprintf(_T("Successed to connect server:  %d \n"), nConnectCount - nCreateSocketFailCount - nConnectSrvFailCount);
		_tprintf(_T("Failed to connect server:  %d \n"), nConnectSrvFailCount);
	}
	else
	{
		_tprintf(_T("WSAStartup failed! \n"));
	}

	Dispose();

	::system("pause");
	return 0;
}

void Dispose()
{
	for (vector<SOCKET>::iterator it = list.begin(); it < list.end(); it++)
	{
		::closesocket(*it);
	}

	::WSACleanup();
}

string UTF8ToMultiByte(const wchar_t* str)
{
	int nlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* strMultiByte = new char[nlen];
	WideCharToMultiByte(CP_ACP, 0, str, -1, strMultiByte, nlen, NULL, NULL);
	string result = strMultiByte;
	delete strMultiByte;
	return result;
}

void GetIpAndPort(SOCKET socket, TCHAR* ip, int* port)
{
	SOCKADDR_IN addr;
	int len = sizeof(addr);
	int result = ::getsockname(socket, (SOCKADDR*)&addr, &len);
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


