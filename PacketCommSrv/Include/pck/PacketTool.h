#pragma once
#include "PacketCmd.h"

#include "tc/Packet.h"
using namespace tc;

namespace pck
{
	// packet tool
	class PacketTool final
	{
	private:
		PacketTool();

	public:
		//************************************
		// Method:    cmd是否可用
		//************************************
		static bool IsCmdValid(EPacketCmd cmd);

		//************************************
		// Method:    解析包
		// Parameter: cmd:	包命令
		//************************************
		static Packet* GetPacket(EPacketCmd cmd);
	};
}