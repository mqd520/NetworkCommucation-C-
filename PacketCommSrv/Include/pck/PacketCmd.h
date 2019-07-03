#pragma once

namespace pck
{
	// packet cmd
	enum class EPacketCmd : int
	{
		KeepAlive = 1,					// 心跳包
		LoginSrvRequest = 8,			// 登录服务端请求包
		LoginSrvResult = 9,				// 登录服务端结果包


		None
	};
}