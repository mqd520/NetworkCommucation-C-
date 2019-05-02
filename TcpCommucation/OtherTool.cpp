#include "stdafx.h"
#include "OtherTool.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	void Printf(TCHAR* msg)
	{
#ifdef _DEBUG
#ifdef _CONSOLE_APP
		_tprintf(msg);
#endif
#ifdef _WINDOWS_
		OutputDebugString(msg);
#endif
#endif // _DEBUG
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

	void PauseThread(ThreadInfo* info, bool pause)
	{
		if (info->hThread != 0)
		{
			if (pause)
			{
				if (!info->bPause)
				{
					::SuspendThread(info->hThread);
				}
			}
			else
			{
				if (info->bPause)
				{
					::ResumeThread(info->hThread);
				}
			}
		}
	}
}