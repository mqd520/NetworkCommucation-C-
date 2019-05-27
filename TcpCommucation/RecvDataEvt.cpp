#include "stdafx.h"
#include "Include/tc/RecvDataEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	RecvDataEvt::RecvDataEvt(CTcpService* pSrv, SOCKET recv, BYTE* pBuf, int len) :
		TcpEvt(pSrv, recv),
		pBuf(pBuf),
		nLen(len)
	{
		evt = ETcpEvt::RecvData;
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
}