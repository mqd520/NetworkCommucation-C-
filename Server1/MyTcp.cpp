#pragma once


#include "stdafx.h"
#include "MyTcp.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

#define ClientCount 2

struct SocketInfo
{
	SOCKET socket;
	bool connected;
	SOCKADDR_IN addr;
};

//线程句柄
HANDLE hThread = 0;
//线程ID
DWORD threadID = 0;
SOCKET socketListen;
vector<SocketInfo> socClientList;
DWORD WINAPI WaitConnect(LPVOID lpParam);
DWORD WINAPI ListenClientSocketStatus(LPVOID lpParam);
bool SendData(SOCKET socket, TCHAR* data);


void StartListen(TCHAR* ip, int port)
{
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) == 0)
	{
		//创建socket
		socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//创建监听地址
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		TCHAR* showIP;//显示IP
		if (ip == NULL)
		{
			addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//绑定本地任意IP地址
			showIP = _T("127.0.0.1");
		}
		else
		{
			addr.sin_addr.S_un.S_addr = inet_addr(ip);//绑定指定IP地址
			showIP = ip;
		}

		//绑定socket和监听地址
		int rec = bind(socketListen, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("绑定Socket成功\n"));

			//开始监听
			int rec1 = listen(socketListen, 0);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("监听成功\n"), showIP, port);
				hThread = ::CreateThread(NULL, 0, WaitConnect, NULL, NULL, &threadID);
				::CreateThread(NULL, 0, ListenClientSocketStatus, NULL, NULL, &threadID);
			}
			else
			{
				closesocket(socketListen);
				WSACleanup();
				_tprintf(_T("监听失败(%d): %s:%d\n"), WSAGetLastError(), showIP, port);
			}
		}
		else
		{
			closesocket(socketListen);
			WSACleanup();
			_tprintf(_T("绑定Socket失败(%d): %d\n"), WSAGetLastError(), rec);
		}
	}
	else
	{
		_tprintf(_T("Socket模块启动失败!\n"));
	}
}

void CleanSocket()
{
	for (int i = 0; i < ClientCount; i++)
	{
		closesocket(socClientList[i].socket);
	}
	_tprintf(_T("已关闭客户端所有Socket\n"));
	closesocket(socketListen);
	_tprintf(_T("已关闭服务端Socket\n"));
	WSACleanup();
}

//监听客户端连接线程
DWORD WINAPI WaitConnect(LPVOID lpParam)
{
	int len = sizeof(SOCKADDR);
	while (true)
	{
		int socketLen = socClientList.size();
		//客户端连接已满,不接受新客户端连接
		if (socketLen == ClientCount)
		{
			continue;
		}

		SocketInfo info = {};

		//等待客户端连接
		SOCKET socClient = accept(socketListen, (SOCKADDR *)&info.addr, &len);
		_tprintf(_T("收到新客户端连接: %s:%d\n"), inet_ntoa(info.addr.sin_addr), (int)info.addr.sin_port);

		info.connected = true;
		info.socket = socClient;
		socClientList.push_back(info);

		if (socketLen == ClientCount - 1)
		{
			_tprintf(_T("服务端已满%d个客户端连接!,不再接受新客户端连接!\n"), ClientCount);
		}
	}
	return 0;
}

//监听客户端Socket状态
DWORD WINAPI ListenClientSocketStatus(LPVOID lpParam)
{
	while (true)
	{
		Sleep(3 * 1000);
		for (vector<SocketInfo>::iterator it = socClientList.begin(); it != socClientList.end(); ++it)
		{
			if (it->connected)
			{
				if (!SendData(it->socket, _T("OK")))
				{
					closesocket(it->socket);
					socClientList.erase(it);
					_tprintf(_T("失去一个客户端连接\n"));
				}
			}
		}
	}
}

bool SendData(SOCKET socket, TCHAR* data)
{
	int len = sizeof(data);
	int val = send(socket, data, len, 0);
	if (val == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

