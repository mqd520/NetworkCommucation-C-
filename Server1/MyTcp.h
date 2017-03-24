#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <vector>

using namespace std;

//开始TCP监听
void StartListen(TCHAR* ip, int port);
//发送数据
bool SendData(SOCKET socket, TCHAR* data);
//清理
void CleanSocket();

