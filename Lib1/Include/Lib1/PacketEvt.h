#pragma once
#include "tc/TcpEvt.h"

using namespace tc;

namespace lib1
{
	// ���¼�
	class PacketEvt : public TcpEvt
	{
	public:
		PacketEvt();
		~PacketEvt();

	};
}