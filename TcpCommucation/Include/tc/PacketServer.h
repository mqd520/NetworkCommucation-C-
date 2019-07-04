#pragma once
#include "TcpServer.h"

namespace tc
{
	// packet server
	class PacketServer : public TcpServer
	{
	public:
		PacketServer();
		virtual ~PacketServer();

	};
}