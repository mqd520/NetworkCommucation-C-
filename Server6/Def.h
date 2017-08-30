#pragma once
#include "SocketAPI.h"

//tcp会话数据
typedef struct tagTcpSessionData
{
	SOCKET server;//服务端socket
	SOCKET client;//客户端socket
	TCHAR ip[20];//客户端IP
	int port;//客户端端口
}TcpSessionData;

#define WM_RECVNEWCONNECTION	(WM_USER + 1)	//收到新客户端连接消息	