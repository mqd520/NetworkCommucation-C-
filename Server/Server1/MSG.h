#pragma once

#define WM_USER_RECVNEWCLIENT		(WM_USER + 10001)		// �յ��¿ͻ���, wParam: �ͻ���������ϢId, lParam: NULL
#define WM_USER_CLIENTDISCONN		(WM_USER + 10002)		// �ͻ��˶Ͽ�,	wParam: NULL, lParam: NULL
#define WM_USER_LOGINFO				(WM_USER + 10003)		// ��־��Ϣ, wParam: string(��־��Ϣ), lParam: NULL