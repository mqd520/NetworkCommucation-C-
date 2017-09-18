#include "stdafx.h"
#include "TcpClient.h"


namespace NetworkCommunication
{
	CTcpClient::CTcpClient() :
		CTcpService(ETcpServiceType::Client)
	{

	}

	CTcpClient::~CTcpClient()
	{

	}
}