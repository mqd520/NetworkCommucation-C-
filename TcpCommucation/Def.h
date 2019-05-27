#pragma once
#include <vector>
#include "SocketAPI.h"

using namespace std;
using namespace tc;

#define	TC_MAXCLIENTCOUNT			65535	//最大tcp连接数
#define TC_TCPRECVBUFFERSIZE		1024	//tcp接收缓冲区默认大小
#define TC_TCPSENDBUFFERSIZE		1024	//tcp异步发送缓冲区默认大小
#define TC_MAXIPSTRELN				20		//ip字符串最大长度

// 网络地址
typedef struct tagNetAddress
{
	TCHAR ip[TC_MAXIPSTRELN];	// ip
	int port;					// 端口
}NetAddress;

// select队列socket类型
class ESelectSocketType
{
public:
	enum
	{
		Accept,			// 接收新连接的服务端socket
		ReadWriteData,	// 读写数据的socket
		Connect			// 连接服务端的客户端socket
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

// select队列socket数据结构
typedef struct tagSelectSocketData
{
	SOCKET	socket;	// socket
	int type;		// socket类型: ESelectSocketType
}SelectSocketData;

// 向对端发送数据结果
typedef struct tagSendPeerDataResult
{
	TCHAR ip[20];	//对端IP
	int port;		//对端端口
	bool success;	//是否成功
	int len;		//发送数据字节长度
	int actualLen;	//实际发送字节长度
}SendPeerDataResult;

// socket信号类型
class ESocketSingalType
{
public:
	enum
	{
		Read,	// 可读
		Write,	// 可写
		Except	// 异常
	};
};

// socket信号数据
typedef struct tagSocketSingalData
{
	SOCKET socket;	// 有信号的socket
	int singaltype;	// socket信号类型: ESocketSingalType
	int sockettype;	// socket类型:	ESelectSocketType
}SocketSingalData;

// 正在处理的socket数据
typedef	struct tagProcessingSocketData
{
	SOCKET socket;	// 正在处理的socket
	int type;		// 信号类型: ESelectSocketType
}ProcessingSocketData;