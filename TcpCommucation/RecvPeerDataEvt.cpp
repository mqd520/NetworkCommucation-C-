#include "stdafx.h"
#include "Include/tc/RecvPeerDataEvt.h"
#include "Include/tc/Def.h"

namespace tc
{
	RecvPeerDataEvt::RecvPeerDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len) :
		TcpEvt(pSrv, recv),
		pBuf(pBuf),
		nLen(len)
	{
		evtType = ETcpEvtType::RecvPeerData;
	}

	RecvPeerDataEvt::~RecvPeerDataEvt()
	{
		if (pBuf && nLen > 0)
		{
			delete pBuf;
		}
	}

	BYTE* RecvPeerDataEvt::GetRecvBuf()
	{
		return pBuf;
	}

	int RecvPeerDataEvt::GetBufLen()
	{
		return nLen;
	}

	int RecvPeerDataEvt::Read(BYTE* buf, int len)
	{
		int len1 = len > nLen ? nLen : len;	// 实际读取长度
		memcpy(buf, pBuf, len1);

		int len2 = nLen - len1;		// 剩余长度
		if (len2 > 0)
		{
			BYTE* pBufTmp = new BYTE[len2];
			memcpy(pBufTmp, pBuf + len1, len2);

			delete pBuf;
			pBuf = pBufTmp;		// 指向剩余缓冲区
			nLen = len2;
		}
		else
		{
			delete pBuf;
			pBuf = NULL;
			nLen = 0;
		}

		return len1;
	}
}