// Server5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpServer.h"
#include "MemoryTool.h"
#include "Common.h"

#include <stdio.h>

using namespace NetworkCommunication;

int _tmain(int argc, _TCHAR* argv[])
{
	CNetworkCommuMgr::Init();
	CTcpServer server;
	CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpService((CTcpService*)&server);
	server.Init("192.168.0.68", 8040);
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
			int len = 0;
			//BYTE* buf = WriteUTF8Str(L"Leon520汉字汉字", &len);
			BYTE* buf = WriteMultiByteStr("Leon520汉字汉字", &len);
			int socket = ::atoi(input);
			server.SendData((SOCKET)socket, buf, len);
		}
	}

	CNetworkCommuMgr::Exit();
	return 0;
}

