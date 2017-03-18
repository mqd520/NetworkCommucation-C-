// Server1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define ListenPort	80
#define ListenIP	_T("127.0.0.1")
#define ClientCount	3


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) == 0)
	{
		//创建socket
		SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//创建监听地址
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(ListenPort);
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//绑定本地任意IP地址
		//addr.sin_addr.S_un.S_addr = inet_addr(ListenIP);//绑定指定IP地址

		//绑定socket和监听地址
		int rec = bind(soc, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("绑定Socket成功\n"));

			//开始监听
			int rec1 = listen(soc, 0);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("监听成功: %s:%d\n"), ListenIP, ListenPort);
				_tprintf(_T("客户端连接满%d个,服务端将自动关闭Socket\n"), ClientCount);

				SOCKADDR_IN addrClientList[ClientCount];
				SOCKET socClientList[ClientCount];
				int i = 0;
				int len = sizeof(SOCKADDR);
				while (true)
				{
					//等待客户端连接
					SOCKET socClient = accept(soc, (SOCKADDR *)&addrClientList[i], &len);
					_tprintf(_T("收到新客户端连接: %s:%d\n"), inet_ntoa(addrClientList[i].sin_addr), (int)addrClientList[i].sin_port);
					socClientList[i] = socClient;

					if (i == ClientCount - 1)
					{
						_tprintf(_T("服务端已满%d个客户端连接!\n"), ClientCount);
						break;
					}
					i++;
				}
				for (int i = 0; i < ClientCount; i++)
				{
					closesocket(socClientList[i]);
				}
				_tprintf(_T("已关闭客户端所有Socket\n"));
				closesocket(soc);
				_tprintf(_T("已关闭服务端Socket\n"));
				WSACleanup();
			}
			else
			{
				closesocket(soc);
				WSACleanup();
				_tprintf(_T("监听失败(%d): %s:%d\n"), WSAGetLastError(), ListenIP, ListenPort);
			}
		}
		else
		{
			closesocket(soc);
			WSACleanup();
			_tprintf(_T("绑定Socket失败(%d): %d\n"), WSAGetLastError(), rec);
		}
	}
	else
	{
		_tprintf(_T("Socket模块启动失败!\n"));
	}

	system("pause");
	return 0;
}

