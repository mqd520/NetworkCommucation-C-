// Server1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyTcp.h"

#define ListenPort	8080

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 67305985;
	BYTE p[4];
	memcpy(p, &n, 4);

	StartListen(_T("121.196.201.36"), ListenPort);

	_tprintf(_T("输入exit退出程序!\n"));
	TCHAR input[5];
	while (true)
	{
		_tscanf(_T("%4s"), input, 5);
		if (strcmp(input, _T("exit")) == 0)
		{
			break;
		}
		else
		{
			_tprintf(_T("无法识别命令!\n"));
		}
	}
	return 0;
}


