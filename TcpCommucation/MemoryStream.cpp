#include "stdafx.h"
#include "Include/tc/MemoryStream.h"
#include "MemoryTool.h"

using namespace tc;

MemoryStream::MemoryStream(int len) :
nBufLen(len),
pBuf(new BYTE[len]),
nReadIndex(0)
{
	memset(pBuf, 0, len);
}

MemoryStream::~MemoryStream()
{
	if (pBuf)
	{
		delete pBuf;
		pBuf = NULL;
	}
}

void MemoryStream::ReAssignBuf(int len)
{
	if (len > nBufLen)
	{
		BYTE* pTmp = new BYTE[len];
		memset(pTmp, 0, len);
		memcpy(pTmp + nReadIndex, pBuf + nReadIndex, AvaliableWriteLen());
		delete pBuf;
		pBuf = pTmp;
		nBufLen = len;
	}
}

void MemoryStream::LeftPan(int index, int len, int size)
{
	BYTE* pTmp = new BYTE[len];
	memcpy(pTmp, pBuf + index, len);
	memcpy(pBuf, pTmp, len);
	delete pTmp;
}

int MemoryStream::GetTotalLen()
{
	return nBufLen;
}

int MemoryStream::AvaliableReadLen()
{
	return nBufLen - nReadIndex;
}

int MemoryStream::AvaliableWriteLen()
{
	return nBufLen - nReadIndex;
}

bool MemoryStream::Copy(BYTE buf[], int len)
{
	if (len <= AvaliableReadLen())
	{
		memcpy(buf, pBuf + nReadIndex, len);

		return true;
	}

	return false;
}

bool MemoryStream::Read(BYTE buf[], int len)
{
	if (len <= AvaliableReadLen())
	{
		memcpy(buf, pBuf + nReadIndex, len);
		nReadIndex += len;
		
		return true;
	}

	return false;
}

void MemoryStream::Write(BYTE buf[], int len)
{
	int len1 = AvaliableWriteLen();	// 原可写长度

	if (len > nBufLen)
	{
		ReAssignBuf(len);	// 重新分配缓冲区
	}

	if (nReadIndex > 0)
	{
		LeftPan(nReadIndex, len1, nReadIndex);
		nReadIndex = 0;
	}

	memcpy(pBuf + len1, buf, len);
}

void MemoryStream::Clear()
{
	memset(pBuf, 0, nBufLen);
	nReadIndex = 0;
}