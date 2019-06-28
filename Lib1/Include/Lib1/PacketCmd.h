#pragma once

namespace lib1
{
	// 包命令
	enum class EPacketCmd : int
	{
		KeepAlive = 1,					// 心跳包
		LoginSrvRequest = 8,			// 登录服务端请求包
		LoginSrvResult = 9,				// 登录服务端结果包


		PlayerRequestLogin,				// 玩家请求登陆包
		PlayerLoginResult,				// 玩家登陆结果包


		None							// None
	};
}