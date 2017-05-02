// Client6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test.h"
#include "OtherTool.h"
#include "MemoryTool.h"

MyClass test;

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR ip[20] = { 0 };
	if (GetLocalIP(ip))
	{
		test.Init(ip, 8080);
		test.Connect();
	}

	while (true)
	{
		char str[100] = { 0 };
		gets(str);
		printf(str);
		printf("\n");
		int len = 0;
		BYTE* buf = WriteMultiByteStr(str, &len);
		bool b = test.SendData(buf, len);
		delete buf;
		printf("%d\n", b);
	}

	return 0;
}

