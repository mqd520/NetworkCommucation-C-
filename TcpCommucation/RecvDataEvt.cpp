#include "stdafx.h"
#include "Include/tc/RecvDataEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	RecvDataEvt::RecvDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len) :
		TcpEvt(pSrv, recv),
		pBuf(pBuf),
		nLen(len)
	{
		evtType = ETcpEvtType::RecvData;
		strIp = SocketTool::GetPeerIpAndPort(recv, &nPort);
	}

	RecvDataEvt::~RecvDataEvt()
	{
		if (pBuf)
		{
			delete pBuf;
		}
	}

	BYTE* RecvDataEvt::GetRecvBuf()
	{
		return pBuf;
	}

	int RecvDataEvt::GetBufLen()
	{
		return nLen;
	}

	string RecvDataEvt::GetPeerIp()
	{
		return strIp;
	}

	int RecvDataEvt::GetPeerPort()
	{
		return nPort;
	}
}