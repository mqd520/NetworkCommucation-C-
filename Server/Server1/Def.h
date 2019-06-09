#pragma once

#include <string>

using namespace std;

// 日志类型
enum ELogType
{
	Info,	// 信息
	Debug,	// 调试
	Error,	// 错误
	Fatal,	// 严重错误

	None	// 无
};

// 客户端连接信息
typedef struct tagClientConnInfo
{
	string ip;			// ip
	int port;			// 端口
	int socket;			// 
}ClientConnInfo;

