// Server1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#pragma once

#include "stdafx.h"
#include "MyTcp.h"

#define ListenPort	8011

int _tmain(int argc, _TCHAR* argv[])
{
	StartListen(NULL, ListenPort);

	_tprintf(_T("����exit�˳�����!\n"));
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
			_tprintf(_T("�޷�ʶ������!\n"));
		}
	}
	Clean();
	return 0;
}



