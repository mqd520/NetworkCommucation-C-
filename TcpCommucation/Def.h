#pragma once
#include <vector>
#include <WinSock2.h>

using namespace std;

#define	TC_MAXCLIENTCOUNT			65535	//最大tcp连接数
#define TC_TCPRECVBUFFERSIZE		1024	//tcp接收缓冲区默认大小
#define TC_TCPSENDBUFFERSIZE		1024	//tcp异步发送缓冲区默认大小
#define TC_MAXIPSTRELN				20		//ip字符串最大长度

namespace tc
{
	// socket类型
	enum class ESocketType : int
	{
		Accept,			// 用于接收新连接(服务端的socket)
		SendRecvData,	// 用于收(发)数据的socket
		Connect			// 用于连接服务端的socket(客户端的socket)
	};

	// 异步发送状态
	enum class EAsyncSendStatus : int
	{
		PreSend,	// 准备发送
		Sending,	// 正在发送
		SendCmp		// 发送完成
	};

	// socket信号类型
	enum class ESocketSingalType : int
	{
		Read,	// 可读
		Write,	// 可写
		Except	// 异常
	};

	// socket事件类型
	enum class ESocketEvtType : int
	{
		RecvNewConn,		// 收到新连接
		RecvPeerData,		// 收到对端数据
		ConnDisconnect,		// 连接被断开
		
		None				// 无
	};

	// 网络地址
	typedef struct tagNetAddress
	{
		string ip;	// ip
		int port;	// 端口
	}NetAddress;

	// select队列socket数据结构
	typedef struct tagSelectSocketData
	{
		SOCKET	socket;		// socket
		ESocketType type;	// socket类型: ESocketType
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

	// socket信号数据
	typedef struct tagSocketSingalData
	{
		SOCKET socket;					// 有信号的socket
		ESocketSingalType singaltype;	// socket信号类型: ESocketSingalType
		ESocketType sockettype;			// socket类型:	ESocketType
	}SocketSingalData;

	// 正在处理的socket数据
	typedef	struct tagProcessingSocketData
	{
		SOCKET socket;			// 正在处理的socket
		ESocketSingalType type;	// 信号类型: ESocketType
	}ProcessingSocketData;

	// socket信息数据
	typedef struct tagSocketInfoData
	{
		SOCKET socket;		// 关联的socket
		ESocketType type;	// socket type
		string peerIp;		// 对端ip
		int peerPort;		// 对端端口
		string localIP;		// 关联的本地ip
		int localPort;		// 关联的本地端口
		int socketId;		// socket id, 关联一个socket
	}SocketInfoData;
}

