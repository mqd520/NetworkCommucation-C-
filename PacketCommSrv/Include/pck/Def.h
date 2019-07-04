#pragma once

#define		PCR_PacketHeadLen					(7)						// 包头长度
#define		PCR_PacketHeadMask					(32616)					// 包头mask
#define		PCR_MaxPacketLen					(2048)					// 最大包总长度
#define		PCR_Version							(0x0007)				// 版本
#define		PCR_Connect_Timeout					(2 * 1000)				// 验证客户端密码和登录服务端请求超时时间
#define		PCR_KeepAlive_Timespan				(3 * 1000)				// 默认心跳包发送间隔时间
#define		PCR_KeepAlive_Timeout				(10 * 1000)				// 默认心跳包超时时间
#define		PCR_KeepAlive_MaxMissCount			(2)						// 默认允许丢失心跳包最大次数
#define		PCR_KeepAlive_RecvTimespan			(1 * 1000)				// 服务端接收客户端心跳包的间隔时间

namespace pck
{
	// 服务器类型
	enum class EServerType : int
	{
		Plaza = 3,				// 大厅服务
		Center = 5,				// 中心服务

		None = -1				// None
	};

	// 服务器ID
	enum class EServerId : int
	{
		Plaza		= 1,		// 大厅服务

		None					// 无
	};
}