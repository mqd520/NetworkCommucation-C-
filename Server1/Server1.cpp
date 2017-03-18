// Server1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define ListenPort	8011
#define ListenIP	_T("127.0.0.1")
#define MaxListenNum	1000


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
		//addr.sin_addr.S_un.S_addr = htonl(inet_addr(ListenIP));//绑定指定IP地址

		//绑定socket和监听地址
		int rec = bind(soc, (SOCKADDR *)&addr, sizeof(SOCKADDR_IN));
		if (rec != SOCKET_ERROR)
		{
			_tprintf(_T("绑定Socket成功\n"));

			//开始监听
			int rec1 = listen(soc, MaxListenNum);
			if (rec != SOCKET_ERROR)
			{
				_tprintf(_T("监听成功: %s:%d\n"), ListenIP, ListenPort);

				SOCKADDR_IN addrClient;
				int len = sizeof(SOCKADDR);
				while (true)
				{
					//等待客户端连接
					SOCKET socClient = accept(soc, (SOCKADDR *)&addrClient, &len);
					_tprintf(_T("收到客户端连接: %s:%d\n"), inet_ntoa(addrClient.sin_addr), (int)addrClient.sin_port);
					
					Sleep(2 * 1000);
					_tprintf(_T("断开客户端Socket\n"));
					closesocket(socClient);
				}
				closesocket(soc);
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
	return 0;
}

