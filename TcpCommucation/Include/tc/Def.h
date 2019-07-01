#pragma once
#include <vector>
#include <WinSock2.h>
#include <functional>
using namespace std;
using namespace std::placeholders;

#define	TC_MAXCLIENTCOUNT			65535	// 最大tcp连接数
#define TC_TCPRECVBUFFERSIZE		4096	// tcp接收缓冲区默认大小
#define TC_RECONNECTTIME			3000	// 自动重连间隔时间

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
		SendPeerData,		// 发送对端数据
		ConnectCpl,			// 连接服务端完成

		None				// 无
	};

	// tcp srv 类型
	enum class ETcpSrvType : int
	{
		Server,		// 服务端
		Client,		// 客户端

		None		// 无
	};

	// tcp事件类型
	enum class ETcpEvtType : int
	{
		RecvNewConn,		// 收到新连接
		RecvData,			// 收到对端数据
		ConnDisconnect,		// 连接断开
		SendDataResult,		// 发送数据结果
		RecvConnResult,		// 接收客户端连接的结果
		ConnectSrvResult,	// 连接服务端的结果

		None				// 无
	};

	// 日志类型
	enum class ETcpLogType : int
	{
		Info,		// 消息
		Warn,		// 警告
		Debug,		// 调试
		Error,		// 错误
		Fatal,		// 严重错误
		Exception,	// 系统异常

		None	// 无
	};

	// 连接断开原因
	enum class EDisconnReason
	{
		Peer,			// 对方关闭
		Local,			// 本地关闭
		Error,			// 发生socket错误

		Other			// 其它原因
	};

	// 包数据
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// 包体缓冲区
		int nLen;		// 包体缓冲区长度
		int cmd;		// 包命令
		int clientId;	// client id(适用于服务端)
	}PacketData;

	class TcpEvt;
	// tcp事件回调函数指针
	typedef std::function<void(TcpEvt*, void*, void*)> Fun2;

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

