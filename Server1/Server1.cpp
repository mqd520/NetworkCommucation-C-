// Server1.cpp : 定义控制台应用程序的入口点。
//
#pragma once

#include "stdafx.h"
#include "MyTcp.h"

#define ListenPort	8011

int _tmain(int argc, _TCHAR* argv[])
{
	StartListen(NULL, ListenPort);

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
	Clean();
	return 0;
}



