#pragma once
#include <vector>
#include "SocketAPI.h"

using namespace std;

#ifndef MAXCLIENTCOUNT
#define MAXCLIENTCOUNT	65535	//最大客户端连接数
#endif 

#ifndef TCPBUFFERSIZE
#define TCPBUFFERSIZE	2048	//tcp缓冲区大小
#endif 

//socket接收数据
typedef struct tagSocketRecvData
{
	SOCKET peer;//对端socket
	BYTE* pBuf;//接收到的数据
	int len;//接收到的数据长度
}SocketRecvData;

//服务端socket关联数据
typedef struct tagServerSocketRelationData
{
	SOCKET socket;//服务端socket
	char ip[20];//监听的IP
	int port;//监听的端口
	SOCKADDR_IN addr;//服务端地址
	vector<TCHAR*> vecAllowIP;//允许指定IP连接服务端
	void* tcpServer;
}ServerSocketData;

//tcp连接两端socket数据
typedef struct tagSocketPair
{
	SOCKET local;//本地socket
	SOCKET peer;//对端socket
}SocketPair;

typedef struct tagPeerSocketData
{
	SOCKET peer;//对端socket
	char ip[20];//对端IP
	int	port;//对端端口
	SOCKET local;//关联的本地socket
}PeerSocketData;

//tcp服务类型
class ETcpServiceType
{
public:
	enum
	{
		Client,	//客户端
		Server	//服务端
	};
};

//tcp动作类型
class ETcpActionType
{
public:
	enum
	{
		AcceptNewConnection,//接收到新的客户端连接
		PeerClose,//对端主动关闭
		RecvPeerData,//收到对端socket数据
		SendData//向对端发送数据
	};
};

//select队列socket类型
class ESelectSocketType
{
public:
	enum
	{
		Server,//服务端socket
		Peer//对端socket
	};
};

typedef struct tagSelectSocketData
{
	SOCKET	socket;//socket
	int		type;  //select监听socket类型
}SelectSocketData;