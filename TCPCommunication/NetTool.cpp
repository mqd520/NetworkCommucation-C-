#include "stdafx.h"
#include "NetTool.h"
#include "StringHandle.h"

namespace TCPCommunication
{
	string ReadMultiByteStr(BYTE buf[], int len)
	{
		char* str = new char[len + 1];
		memcpy(str, buf, len);
		str[len] = 0;
		string result = str;
		delete str;
		return result;
	}

	wstring ReadUTF8Str(BYTE buf[], int len)
	{
		int size = len / 2;
		wchar_t* strUTF8 = new wchar_t[size + 1];
		memcpy(strUTF8, buf, len);
		strUTF8[size] = 0;
		wstring result = strUTF8;
		delete strUTF8;
		return result;
	}

	BYTE* WriteMultiByteStr(char* str, int* size)
	{
		*size = strlen(str) + 1;
		BYTE* buf = new BYTE[*size];
		memcpy(buf, str, *size);
		return buf;
	}

	BYTE* WriteUTF8Str(wchar_t* str, int* size)
	{
		*size = GetWStrByteCount(str);
		BYTE* buf = new BYTE[*size];
		memcpy(buf, str, *size);
		return buf;
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
}