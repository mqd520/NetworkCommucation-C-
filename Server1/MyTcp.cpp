#pragma once


#include "stdafx.h"
#include "MyTcp.h"

#ifdef _DEBUG
#define new new(__FILE__, __LINE__)
#endif

#define ClientCount 2

//线程句柄
HANDLE hThread = 0;
//线程ID
DWORD threadID = 0;
SOCKET socketListen;
SOCKADDR_IN addrClientList[ClientCount];
SOCKET socClientList[ClientCount];

DWORD WINAPI WaitConnect(LPVOID lpParam);

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
		closesocket(socClientList[i]);
	}
	_tprintf(_T("已关闭客户端所有Socket\n"));
	closesocket(socketListen);
	_tprintf(_T("已关闭服务端Socket\n"));
	WSACleanup();
}


DWORD WINAPI WaitConnect(LPVOID lpParam)
{
	int i = 0;
	int len = sizeof(SOCKADDR);
	while (true)
	{
		//客户端连接已满,不接受新客户端连接
		if (i == ClientCount - 1)
		{
			continue;
		}

		//等待客户端连接
		SOCKET socClient = accept(socketListen, (SOCKADDR *)&addrClientList[i], &len);
		_tprintf(_T("收到新客户端连接: %s:%d\n"), inet_ntoa(addrClientList[i].sin_addr), (int)addrClientList[i].sin_port);
		socClientList[i] = socClient;
		if (i == ClientCount - 1)
		{
			_tprintf(_T("服务端已满%d个客户端连接!,不再接受新客户端连接!\n"), ClientCount);
			break;
		}
		i++;
	}
	CleanSocket();
	return 0;
}

