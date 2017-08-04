// Server5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpServer.h"

using namespace NetworkCommunication;

int _tmain(int argc, _TCHAR* argv[])
{
	CNetworkCommuMgr::Init(CNetworkCommuMgr::Server);
	CTcpServer server;
	server.Init(_T("192.168.0.68"), 8040);
	server.Listen();

	_tprintf(_T("输入exit退出程序!\n"));
	char input[5];
	while (true)
	{
		scanf("%4s", input, 5);
		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else
		{
			_tprintf(_T("无法识别命令!\n"));
		}
	}

	CNetworkCommuMgr::Exit();
	return 0;
}

