#pragma once
#include "SocketAPI.h"

//tcp�Ự����
typedef struct tagTcpSessionData
{
	SOCKET server;//�����socket
	SOCKET client;//�ͻ���socket
	TCHAR ip[20];//�ͻ���IP
	int port;//�ͻ��˶˿�
}TcpSessionData;

#define WM_RECVNEWCONNECTION	(WM_USER + 1)	//�յ��¿ͻ���������Ϣ	