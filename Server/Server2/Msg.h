#pragma once

#define WM_USER_LOGINFO					(WM_USER + 10001)		// ��־, wParam: string(��־��Ϣ), lParam: NULL
#define WM_USER_CONNECTRESULT			(WM_USER + 10002)		// ���ӷ���˽��, wParam: bool(�Ƿ����ӳɹ�), lParam: void*(TcpClient��ַ)