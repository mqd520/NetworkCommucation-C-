#pragma once

#define WM_USER_RECVNEWCLIENT		(WM_USER + 10001)		// 收到新客户端, wParam: 客户端连接信息Id
#define WM_USER_CLIENTDISCONN		(WM_USER + 10002)		// 客户端断开