#include "stdafx.h"
#include "SocketExceptAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CSocketExcept::CSocketExcept(SOCKET socket, int type) :
		CTcpAction(NULL, socket)
	{

	}

	CSocketExcept::~CSocketExcept()
	{

	}

	int CSocketExcept::GetActionType()
	{
		return ETcpActionType::SocketExcept;
	}

	int CSocketExcept::GetExceptSocketType()
	{
		return m_nSocketType;
	}
}