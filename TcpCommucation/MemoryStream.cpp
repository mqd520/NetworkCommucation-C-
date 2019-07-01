#include "stdafx.h"
#include "Include/tc/MemoryStream.h"

using namespace tc;

MemoryStream::MemoryStream(int len) :
nBufLen(len),
pBuf(new BYTE[len]),
nDataStartIndex(0),
nDataEndIndex(-1)
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
		int len1 = AvaliableReadLen();
		if (len1 > 0)
		{
			memcpy(pTmp + nDataStartIndex, pBuf + nDataStartIndex, len1);
		}
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

BYTE* MemoryStream::GetBuf()
{
	return pBuf;
}

int MemoryStream::GetTotalLen()
{
	return nBufLen;
}

int MemoryStream::AvaliableReadLen()
{
	if (nDataEndIndex >= nDataStartIndex)
	{
		return nDataEndIndex - nDataStartIndex + 1;
	}

	return 0;
}

int MemoryStream::AvaliableWriteLen()
{
	return nBufLen - AvaliableReadLen();
}

bool MemoryStream::Copy(BYTE buf[], int len)
{
	if (len <= AvaliableReadLen())
	{
		memcpy(buf, pBuf + nDataStartIndex, len);

		return true;
	}

	return false;
}

bool MemoryStream::Read(BYTE buf[], int len)
{
	if (len <= AvaliableReadLen())
	{
		memcpy(buf, pBuf + nDataStartIndex, len);
		nDataStartIndex += len;

		return true;
	}

	return false;
}

void MemoryStream::Write(BYTE buf[], int len)
{
	int len1 = AvaliableWriteLen();
	int len2 = AvaliableReadLen();

	if (len > len1)
	{
		ReAssignBuf(len);	// 重新分配缓冲区
	}

	if (len2 > 0 && nDataStartIndex > 0)
	{
		LeftPan(nDataStartIndex, len2, nDataStartIndex);
		nDataStartIndex = 0;
		nDataEndIndex = len2 - 1;
	}

	if (nDataEndIndex + 1 <= nBufLen - 1)
	{
		memcpy(pBuf + nDataEndIndex + 1, buf, len);
		nDataEndIndex += len;
	}
}

void MemoryStream::Clear()
{
	memset(pBuf, 0, nBufLen);
	nDataStartIndex = 0;
	nDataEndIndex = 0;
}