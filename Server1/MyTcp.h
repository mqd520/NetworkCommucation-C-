#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <vector>

using namespace std;

//��ʼTCP����
void StartListen(TCHAR* ip, int port);
//��������
bool SendData(SOCKET socket, TCHAR* data);
//����
void CleanSocket();

