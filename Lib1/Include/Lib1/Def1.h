#pragma once

namespace lib1
{
	// 服务类型
	enum class EServiceType : int
	{
		PlazaSrv = 3,			// 大厅服务
		CenterSrv = 5,			// 中心服务

		None = -1				// None
	};

	// 包数据
	typedef struct tagPacketData
	{
		BYTE* pBuf;		// 包体缓冲区
		int nLen;		// 包体缓冲区长度
		int cmd;		// 包命令
		int clientId;	// client id(适用于服务端)
	}PacketData;
}