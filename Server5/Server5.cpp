// Server5.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TcpServer.h"
#include "MemoryTool.h"
#include "Common.h"

#include <stdio.h>

using namespace NetworkCommunication;

int _tmain(int argc, _TCHAR* argv[])
{
	CNetworkCommuMgr::Init();//����ͨ�ų�ʼ��

	CTcpServer server;
	server.Init("192.168.0.68", 8040);
	server.AddAllowIP("192.168.0.68");
	server.Listen();

	_tprintf(_T("����exit�˳�����!\n"));
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
			BYTE* buf = WriteMultiByteStr("Leon520����~!@#$%^&*()-=_+[]{};'\\:\"|,./<>?", &len);
			int socket = ::atoi(input);
			bool result = server.SendData((SOCKET)socket, buf, len);//ͬ������
			//server.AsyncSendData((SOCKET)socket, buf, len);//�첽����
		}
	}

	CNetworkCommuMgr::Exit();
	return 0;
}