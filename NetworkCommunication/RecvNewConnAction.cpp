#include "stdafx.h"
#include "RecvNewConnAction.h"

namespace NetworkCommunication
{
	CRecvNewConnAction::CRecvNewConnAction(SOCKET server, SOCKET sendrecv) :
		CTcpAction(server, sendrecv)
	{

	}

	CRecvNewConnAction::~CRecvNewConnAction()
	{

	}

	int CRecvNewConnAction::GetActionType()
	{
		return ETcpActionType::AcceptNewConnection;
	}

	SOCKET CRecvNewConnAction::GetServerSocket()
	{
		return m_localSocket;
	}

	SOCKET CRecvNewConnAction::GetServerClientSocket()
	{
		return m_socket;
	}
}