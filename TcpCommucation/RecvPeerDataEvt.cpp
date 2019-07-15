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
		int len1 = len > nLen ? nLen : len;	// Actual read length
		memcpy(buf, pBuf, len1);

		int len2 = nLen - len1;		// left length
		if (len2 > 0)
		{
			BYTE* pBufTmp = new BYTE[len2];
			memcpy(pBufTmp, pBuf + len1, len2);

			delete pBuf;
			pBuf = pBufTmp;		// point to left buf
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

	void RecvPeerDataEvt::Write(BYTE* buf, int len)
	{
		BYTE* pTmpBuf = new BYTE[nLen + len];
		if (pBuf && nLen > 0)
		{
			memcpy(pTmpBuf, pBuf, nLen);
		}
		memcpy(pTmpBuf + nLen, buf, len);
	}

	void RecvPeerDataEvt::ResetBuf(BYTE* buf, int len)
	{
		if (pBuf)
		{
			delete pBuf;
			pBuf = NULL;
			nLen = 0;
		}

		pBuf = buf;
		nLen = len;
	}
}