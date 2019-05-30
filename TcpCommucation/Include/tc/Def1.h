#pragma once

#include "Include/tc/TcpEvt.h"

// tcp事件回调函数指针
// pEvent	tcp事件对象
// pEvent	事件附加参数
typedef void(*LPTcpEventCallback)(TcpEvt* pEvt, void* pParam);

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