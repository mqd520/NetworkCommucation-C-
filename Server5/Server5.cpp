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
	CNetworkCommuMgr::Init();//网络通信初始化

	CTcpServer server;
	server.Init("192.168.0.68", 8040);
	server.AddAllowIP("192.168.0.68");
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
			BYTE* buf = WriteMultiByteStr("Leon520汉字~!@#$%^&*()-=_+[]{};'\\:\"|,./<>?", &len);
			int socket = ::atoi(input);
			bool result = server.SendData((SOCKET)socket, buf, len);//同步发送
			//server.AsyncSendData((SOCKET)socket, buf, len);//异步发送
		}
	}

	CNetworkCommuMgr::Exit();
	return 0;
}