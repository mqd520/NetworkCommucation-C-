#pragma once

#include "TcpEvt.h"

using namespace tc;

// tcp事件
enum ETcpEvt
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
enum ELogType
{
	Info,	// 消息
	Debug,	// 调试
	Err,	// 错误

	None1	// 其它
};


// tcp事件回调函数指针
// pEvent	tcp事件对象
// pEvent	事件附加参数
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam);

// 日志回调函数指针
// type		日志类型: ELogType
// log		日志内容
// pParam1	附加参数1
// pParam1	附加参数2
typedef void(*LPLogCallback)(int type, string log, void* pParam1, void* pParam2);