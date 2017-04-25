#include "stdafx.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer()
	{

	}

	CTcpServer::~CTcpServer()
	{

	}

	void CTcpServer::InitSocket()
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			//SendTcpEvt(TcpEvtType::error, _T("Socket≥ı ºªØ ß∞‹!\n"));
		}
	}
}