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

//服务端关联的客户端socket数据结构
typedef struct tagServerClientSocket
{
	SOCKET scClient;//服务客户端socket
	SOCKET server;//关联的服务端socket
	TCHAR ip[NETCOMM_MAXIPSTRELN];//客户端IP
	int	port;//客户端端口
}ClientSocketData;

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
		SocketExcept,//socket发生了异常
		NetError//发生了网络错误
	};
};

//tcp服务事件
class ETcpSrvEvent
{
public:
	enum
	{
		None,//无
		RecvNewConnection,//收到新连接
		RefuseNewConnection,//拒绝新连接
		RecvPeerData,//收到对端数据
		ConnDisconnect,//连接断开
		AsyncSendDataResult//异步发送数据结果
	};
};

//tcp连接断开原因
class ETcpDisconnectReason
{
public:
	enum
	{
		Peer,//对端主动断开
		Local,//本地主动断开
		Except//socket异常
	};
};

//select队列socket类型
class ESelectSocketType
{
public:
	enum
	{
		None,//无
		RecvConn,//指示用于接收新连接的socket
		ReadWriteData//指示用于读写数据的socket
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

//异步发送对端数据
typedef struct tagAsyncSendPeerData
{
	int len;//发送数据字节长度
	BYTE* pBuf;//缓冲区指针
	SOCKET send;//发送数据的socket
}AsyncSendPeerData;

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