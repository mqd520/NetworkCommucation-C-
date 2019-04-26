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

//对端数据
typedef	struct tagPeerData
{
	TCHAR ip[20];//对端IP
	int port;//对端端口
	BYTE* buf;//数据缓冲区指针
	int len;//数据长度
}PeerData;


#define	KEY_SIZE 50
#define	VALUE_SIZE 100
// 
typedef struct tagKeyValueDataW
{
	wchar_t key[KEY_SIZE];  // 键名
	wchar_t value[VALUE_SIZE]; // 键值
} KeyValueDataW;

// 
typedef struct tagKeyValueDataA
{
	char key[KEY_SIZE];  // 键名
	char value[VALUE_SIZE]; // 键值
} KeyValueDataA;

#define WM_RECVNEWCONNECTION	(WM_USER + 1)	//收到新客户端连接	
#define WM_RECVPEERDATA			(WM_USER + 2)	//收到对端数据
#define WM_PEERCLOSE			(WM_USER + 3)	//对端关闭连接
#define WM_SENDPEERDATARESULT	(WM_USER + 4)	//异步发送数据结果
#define	WM_REFUSENEWCONNECTION	(WM_USER + 5)	//拒绝新客户端连接