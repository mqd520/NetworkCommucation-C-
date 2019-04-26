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

//�Զ�����
typedef	struct tagPeerData
{
	TCHAR ip[20];//�Զ�IP
	int port;//�Զ˶˿�
	BYTE* buf;//���ݻ�����ָ��
	int len;//���ݳ���
}PeerData;


#define	KEY_SIZE 50
#define	VALUE_SIZE 100
// 
typedef struct tagKeyValueDataW
{
	wchar_t key[KEY_SIZE];  // ����
	wchar_t value[VALUE_SIZE]; // ��ֵ
} KeyValueDataW;

// 
typedef struct tagKeyValueDataA
{
	char key[KEY_SIZE];  // ����
	char value[VALUE_SIZE]; // ��ֵ
} KeyValueDataA;

#define WM_RECVNEWCONNECTION	(WM_USER + 1)	//�յ��¿ͻ�������	
#define WM_RECVPEERDATA			(WM_USER + 2)	//�յ��Զ�����
#define WM_PEERCLOSE			(WM_USER + 3)	//�Զ˹ر�����
#define WM_SENDPEERDATARESULT	(WM_USER + 4)	//�첽�������ݽ��
#define	WM_REFUSENEWCONNECTION	(WM_USER + 5)	//�ܾ��¿ͻ�������