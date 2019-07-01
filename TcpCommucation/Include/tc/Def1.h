#pragma once

#include <string>

using namespace std;

namespace tc
{
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
		Info,	// 消息
		Warn,	// 警告
		Debug,	// 调试
		Error,	// 错误
		Fatal,	// 严重错误

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

	class TcpEvt;
	// tcp事件回调函数指针
	// pEvent	tcp事件对象
	// pParam1	附加参数1
	// pParam2	附加参数2
	using LPTcpEventCallback = void(*)(TcpEvt* pEvt, void* pParam1, void* pParam2);

	// 日志回调函数指针
	// type		日志类型: ETcpLogType
	// log		日志内容
	// pParam1	附加参数1
	// pParam1	附加参数2
	using LPTcpLogCallback = void(*)(ETcpLogType type, string log, void* pParam1, void* pParam2);

	// 包数据
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// 包体缓冲区
		int nLen;		// 包体缓冲区长度
		int cmd;		// 包命令
		int clientId;	// client id(适用于服务端)
	}PacketData;
}

