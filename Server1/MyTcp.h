#pragma once

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS

//��ʼTCP����
void StartListen(TCHAR* ip, int port);

//����Socket
void CleanSocket();