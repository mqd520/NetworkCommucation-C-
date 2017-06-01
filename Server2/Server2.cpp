// Server2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpServer.h"

using namespace NetworkCommunication;

class MyClass
{
public:
	BYTE* m_p;
	CTcpServer* m_p1;
	MyClass(int n1, int n2){
		m_p = new BYTE[1024];
		m_p1 = new CTcpServer();
	};
	~MyClass(){
		if (m_p)
		{
			//delete m_p;
			_tprintf(_T("~MyClass \n"));
		}
	};
};

void fun1()
{
	MyClass my(1, 1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	fun1();

	//CTcpServer server;
	//server.Init(_T("192.168.1.100"), 8080, 1);
	//server.Listen();

	while (true)
	{
		int n = getchar();
		if (n == 48)
		{
			break;
		}
	}

	return 0;
}

