#pragma once

#define WM_USER_LOGINFO					(WM_USER + 10001)		// 日志, wParam: string(日志信息), lParam: NULL
#define WM_USER_CONNECTRESULT			(WM_USER + 10002)		// 连接服务端结果, wParam: bool(是否连接成功), lParam: void*(TcpClient地址)