// Server1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyTcp.h"

#define ListenPort	7080

int _tmain(int argc, _TCHAR* argv[])
{
	StartListen(_T("192.168.0.17"), ListenPort);

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


