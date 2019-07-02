#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Include/tc/Def.h"
#include "Include/tc/SocketDataMgr.h"

namespace tc
{
	ConnDisconnectEvt::ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv, EDisconnReason reason)
		:TcpEvt(pSrv, sendrecv),
		reason(reason)
	{
		evtType = ETcpEvtType::ConnDisconnect;
	}

	EDisconnReason ConnDisconnectEvt::GetReason()
	{
		return reason;
	}

	//string ConnDisconnectEvt::GetPeerIp()
	//{
	//	return strIP;
	//}

	//int ConnDisconnectEvt::GetPeerPort()
	//{
	//	return nPort;
	//}
}
