#include "stdafx.h"
#include "Common.h"

//多字节转UTF-8
wstring MultiByteToUTF8(const char* str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wchar_t* strUTF = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strUTF, nlen);
	wstring result = strUTF;
	delete  strUTF;
	return result;
}

//UTF-8转多字节
string UTF8ToMultiByte(const wchar_t* str)
{
	int nlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* strMultiByte = new char[nlen];
	WideCharToMultiByte(CP_ACP, 0, str, -1, strMultiByte, nlen, NULL, NULL);
	string result = strMultiByte;
	delete strMultiByte;
	return result;
}

//获取本地IP
bool GetLocalIP(TCHAR* ip)
{
	//1.初始化wsa  
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return false;
	}
	//2.获取主机名  
	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	//3.获取主机ip  
	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return false;
	}

#ifndef _UNICODE

	strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
#else
	char tmp[20] = { '\0' };
	strcpy(tmp, inet_ntoa(*(in_addr*)*host->h_addr_list));
	wstring ip1 = MultiByteToUTF8(tmp);
	wmemcpy(ip, ip1.c_str(), 20);
#endif // _UNICODE

	return true;
}