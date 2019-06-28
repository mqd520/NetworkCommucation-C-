#pragma once
#include "Def.h"
#include "Include/Lib1/Def1.h"
#include "tc/PacketBase.h"

using namespace tc;

namespace lib1
{
	// ��������
	class PacketTool
	{
	public:
		PacketTool();
		~PacketTool();

		//************************************
		// Method:    �Ƿ����ڰ�����
		// Parameter: int cmd
		//************************************
		static bool IsPacketCmd(int cmd);

		//************************************
		// Method:    ����һ����������
		// Parameter: pck:	��
		// Parameter: pBuf: ������
		// Parameter: len:	����������
		//************************************
		static int BuildBuf(PacketBase& pck, BYTE* pBuf, int len = LIB1_MAXSENDBULEN);
	};
}