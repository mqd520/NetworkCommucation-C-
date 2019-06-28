#pragma once
#include "tc/TcpEvt.h"

using namespace tc;

namespace lib1
{
	// °üÊÂ¼þ
	class PacketEvt : public TcpEvt
	{
	public:
		PacketEvt();
		~PacketEvt();

	};
}