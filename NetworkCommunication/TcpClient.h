#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//tcp¿Í»§¶Ë
	class CTcpClient : public CTcpService
	{
	public:
		CTcpClient();
		~CTcpClient();
	};
}