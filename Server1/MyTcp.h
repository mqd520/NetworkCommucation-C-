#pragma once

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

//��ʼTCP����
void StartListen(TCHAR* ip, int port);

//����Socket
void CleanSocket();