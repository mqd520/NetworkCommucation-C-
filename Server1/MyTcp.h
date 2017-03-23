#pragma once

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

//开始TCP监听
void StartListen(TCHAR* ip, int port);

//清理Socket
void CleanSocket();