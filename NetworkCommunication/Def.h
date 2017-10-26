#pragma once
#include <vector>
#include "SocketAPI.h"
#include "TcpEvt.h"

using namespace std;
using namespace NetworkCommunication;

#define	NETCOMM_MAXCLIENTCOUNT			65535	//最大tcp连接数
#define NETCOMM_TCPRECVBUFFERSIZE		1024	//tcp接收缓冲区默认大小
#define NETCOMM_TCPSENDBUFFERSIZE		1024	//tcp异步发送缓冲区默认大小
#define NETCOMM_MAXIPSTRELN				20		//ip字符串最大长度

//网络地址
typedef struct tagNetAddress
{
	TCHAR ip[NETCOMM_MAXIPSTRELN];//ip
	int port;//端口
}NetAddress;

//tcp事件
class ETcpEvent
{
public:
	enum
	{
		RecvNewConnection,//收到新连接
		RefuseNewConnection,//拒绝新连接
		RecvPeerData,//收到对端数据
		ConnDisconnect,//连接断开
		AsyncSendDataResult,//异步发送数据结果
		ConnectCmp//连接完成
	};
};

//select队列socket类型
class ESelectSocketType
{
public:
	enum
	{
		RecvConn,//指示用于接收新连接的服务端socket
		ReadWriteData,//指示用于读写数据的socket
		Connect//指示用于连接服务端的客户端socket
	};
};

//异步发送状态
class EAsyncSendStatus
{
public:
	enum
	{
		PreSend,//准备发送
		Sending,//正在发送
		SendCmp//发送完成
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
	TCHAR ip[20];//对端IP
	int port;//对端端口
	bool success;//是否成功
	int len;//发送数据字节长度
	int actualLen;//实际发送字节长度
}SendPeerDataResult;

//tcp事件回调函数指针
//pEvent	tcp服务事件
typedef void(*LPTcpEventCallback)(CTcpEvt* pEvent);

//socket信号类型
class SocketSingalType
{
public:
	enum
	{
		Read,//可读
		Write,//可写
		Except//异常
	};
};

//socket信号数据
typedef struct tagSocketSingalData
{
	SOCKET socket;//有信号的socket
	int singaltype;//socket信号类型
	int sockettype;//socket类型
}SocketSingalData;

//正在处理的socket数据
typedef	struct tagProcessingSocketData
{
	SOCKET socket;//正在处理的socket
	int type;//信号类型
}ProcessingSocketData;