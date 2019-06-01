#pragma once

#include <string>

using namespace std;

// 客户端连接信息
typedef struct tagClientConnInfo
{
	string ip;			// ip
	int port;			// 端口
	int socket;			// 
}ClientConnInfo;