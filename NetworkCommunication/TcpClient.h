#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//tcp�ͻ���
	class CTcpClient : public CTcpService
	{
	public:
		CTcpClient();
		~CTcpClient();
	};
}