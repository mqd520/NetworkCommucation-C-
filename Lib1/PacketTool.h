#pragma once
#include "Def.h"
#include "Include/Lib1/Def1.h"
#include "tc/PacketBase.h"

using namespace tc;

namespace lib1
{
	// 包工具类
	class PacketTool
	{
	public:
		PacketTool();
		~PacketTool();

		//************************************
		// Method:    是否属于包命令
		// Parameter: int cmd
		//************************************
		static bool IsPacketCmd(int cmd);

		//************************************
		// Method:    生成一个包缓冲区
		// Parameter: pck:	包
		// Parameter: pBuf: 缓冲区
		// Parameter: len:	缓冲区长度
		//************************************
		static int BuildBuf(PacketBase& pck, BYTE* pBuf, int len = LIB1_MAXSENDBULEN);
	};
}