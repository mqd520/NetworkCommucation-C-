#pragma once

#include <string>

using namespace std;

namespace tc
{
	// tcp事件类型
	enum class ETcpEvt : int
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
		Err,	// 错误
		Fatal,	// 严重错误

		None	// 无
	};

	class TcpEvt;
	// tcp事件回调函数指针
	// pEvent	tcp事件对象
	// pParam1	附加参数1
	// pParam2	附加参数2
	typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam1, void* pParam2);

	// 日志回调函数指针
	// type		日志类型: ETcpLogType
	// log		日志内容
	// pParam1	附加参数1
	// pParam1	附加参数2
	typedef void(*LPTcpLogCallback)(ETcpLogType type, string log, void* pParam1, void* pParam2);
}

