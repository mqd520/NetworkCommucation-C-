#pragma once

#define Lib1_PacketMask						(32616)					// 包头mask
#define Lib1_PacketHeadLen					(7)						// 包头长度
#define Lib1_ConnectPwd						("abcdefg")				// 服务连接密码
#define LIB1_MAXSENDBULEN					(1024)					// 默认最大发送缓冲区长度
#define Lib1_Version						(0x0007)				// 版本
#define Lib1_keepAlive						(0x0001)				// keepalive
#define Lib1_ServerId						(0x0001)				// serverId
#define Lib1_MaxPacketLen					(0x8096)				// 包体缓冲区字节最大长度
#define Lib1_KeepAliveTimespan1				(10 * 1000)				// 丢失心跳包时间间隔
#define Lib1_KeepAliveTimespan2				(2 * 1000)				// 发送心跳包时间间隔
#define Lib1_VertifyCode					(66)					// 验证码
#define Lib1_MaxMissCount					(3)						// 最大允许丢失心跳包的次数(超过后将关闭连接)
#define Lib1_PwdTimeout						(3 * 1000)				// 服务端接受密码的超时时间
#define Lib1_LoginRequestTimeout			(3 * 1000)				// 服务端接受登录服务请求的超时时间


namespace lib1
{
	// 服务类型
	enum class ELibSrvType : int
	{
		Client,
		Server
	};
}