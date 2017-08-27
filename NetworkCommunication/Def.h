#pragma once
#include <vector>
#include "SocketAPI.h"
#include "TcpAction.h"

using namespace std;
using namespace NetworkCommunication;

#ifndef MAXCLIENTCOUNT
#define MAXCLIENTCOUNT	65535	//最大客户端连接数
#endif 

#ifndef TCPRECVBUFFERSIZE
#define TCPRECVBUFFERSIZE	2048	//tcp接收缓冲区大小
#endif 

//socket发送接收类型
class ESocketSendRecvType
{
public:
	enum
	{
		Recv,	//接收数据
		Send	//发送数据
	};
};

//对端接收数据
typedef struct tagPeerData
{
	SOCKET socket;//接收数据的socket
	BYTE* pBuf;//接收到的数据
	int len;//接收到的数据长度
	char ip[20];//对端IP
	int port;//对端端口
}PeerData;

//服务端socket数据
typedef struct tagServerSocket
{
	SOCKET socket;//服务端socket
	char ip[20];//监听的IP
	int port;//监听的端口
	SOCKADDR_IN addr;//服务端地址
	vector<TCHAR*> vecAllowIP;//允许指定IP连接服务端
	void* tcpServer;//关联的tcp服务对象
}ServerSocket;

//服务端关联的客户端socket数据结构
typedef struct tagServerClientSocket
{
	SOCKET scClient;//服务客户端socket
	char ip[20];//客户端IP
	int	port;//客户端端口
	SOCKET server;//关联的服务端socket
}ServerClientSocket;

//客户端socket数据结构
typedef struct tagClientSocket
{
	SOCKET client;//客户端socket
	char clientIP[20];//客户端IP
	int clientPort;//客户端端口
	char serverIP[20];//服务端IP
	int serverPort;//服务端端口
}ClientSocket;

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
		RecvNewConnection,//收到新连接
		RecvPeerData,//收到对端数据
		PeerCloseConn,//对端主动关闭连接
		AsyncSendData,//异步发送数据
		SendDataResult,//发送数据结果
		NetError,//发生了网络错误
		RefuseNewConn//拒绝客户端连接
	};
};

//select队列socket类型
class ESelectSocketType
{
public:
	enum
	{
		RecvConn,//指示用于接收新连接的socket
		ReadWriteData//指示用于读写数据的socket
	};
};

//select队列socket数据结构
typedef struct tagSelectSocketData
{
	SOCKET	socket;//socket
	int		type;  //select监听socket类型
}SelectSocketData;

//向对端发送数据结果
typedef struct tagSendPeerDataResult
{
	char ip[20];//对端IP
	int port;//对端端口
	bool success;//是否成功
	int len;//发送数据字节长度
	int actualLen;//实际发送字节长度
}SendPeerDataResult;

//异步发送对端数据
typedef struct tagAsyncSendPeerData
{
	int len;//发送数据字节长度
	BYTE* pBuf;//缓冲区指针
	SOCKET send;//发送数据的socket
}AsyncSendPeerData;

//tcp事件回调函数指针
typedef void(*LPTcpEventCallback)(CTcpAction* action);