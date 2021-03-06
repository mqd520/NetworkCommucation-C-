#include "stdafx.h"
#include "Include/tc/TcpSession.h"

namespace tc
{
	TcpSession::TcpSession(string peerIp /*= ""*/, int peerPort /*= 0*/, int clientId /*= 0*/, string localIp /*= ""*/, int localPort /*= 0*/) :
		strPeerIp(peerIp),
		nPeerPort(peerPort),
		nClientId(clientId),
		strLocalIp(localIp),
		nLocalPort(localPort)
	{

	}

	TcpSession::~TcpSession()
	{

	}
}