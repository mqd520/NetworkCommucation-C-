#pragma once

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS

//开始TCP监听
void StartListen(TCHAR* ip, int port);

//清理Socket
void CleanSocket();