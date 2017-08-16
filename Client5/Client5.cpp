// Client5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpClient.h"
#include "OtherTool.h"
#include "MemoryTool.h"
#include "SocketAPI.h"

using namespace NetworkCommunication;

CSocketMgr mgr;

bool OnRecvData(BYTE buf[], int len);
void OnRecvEvt(TcpEvtType type, TCHAR* msg);

CTcpClient m_tcp;

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR ip[20] = { 0 };
	if (GetLocalIP(ip))
	{
		//m_tcp.Init(_T("192.168.0.10"), 8080);
		m_tcp.Init(ip, 8080);
		m_tcp.SetCallback(OnRecvData, OnRecvEvt);
		m_tcp.Connect();
	}

	while (true)
	{
		char str[100] = { 0 };
		gets(str);
		printf(str);
		printf("\n");
		int len = 0;
		BYTE* buf = WriteMultiByteStr(str, &len);
		bool b = m_tcp.SendData(buf, len);
		delete buf;
		printf("%d\n", b);
	}

	return 0;
}

bool OnRecvData(BYTE buf[], int len)
{
	string str = ReadMultiByteStr(buf, len);
#ifdef _UNICODE
	wstring wstr = MultiByteToUTF8(str.c_str());
	_tprintf(wstr.c_str());
#else
	_tprintf(str.c_str());
#endif // _UN

	_tprintf(_T("\n"));

	return false;
}

void OnRecvEvt(TcpEvtType type, TCHAR* msg)
{
	_tprintf(msg);
}
