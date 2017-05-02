#include "stdafx.h"
#include "Test.h"
#include "MemoryTool.h"

MyClass::MyClass()
{

}

MyClass::~MyClass()
{

}

bool MyClass::OnRecvData(BYTE buf[], int len)
{
	string str = ReadMultiByteStr(buf, len);
#ifdef _UNICODE
	wstring wstr = MultiByteToUTF8(str.c_str());
	_tprintf(wstr.c_str());
#else
	_tprintf(str.c_str());
#endif // _UN
	return false;
}

void MyClass::OnRecvEvt(TcpEvtType type, TCHAR* msg)
{
	_tprintf(msg);
}

void MyClass::Init(TCHAR* ip, int port)
{
	m_tcp.Init(ip, port);
	m_tcp.SetCallbackT(this, &MyClass::OnRecvData, &MyClass::OnRecvEvt);
}

void MyClass::Connect()
{
	m_tcp.Connect();
}

bool MyClass::SendData(BYTE* buf, int len)
{
	return m_tcp.SendData(buf, len);
}