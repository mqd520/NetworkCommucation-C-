#include "stdafx.h"
#include "Include/tc/NCTool.h"
#include <time.h>

using namespace tc;

union MyUnion
{
	int n;
	char ch;
};

NCTool::NCTool()
{

}

NCTool::~NCTool()
{

}

EByteOrder NCTool::GetHostByteOrder()
{
	MyUnion u1;
	u1.n = 1;

	if (u1.ch == 1)
	{
		return EByteOrder::litte;
	}

	return EByteOrder::big;
}

void NCTool::ReverseBuf(BYTE* pBuf, int len)
{
	for (int i = 0; i < len / 2; i++)
	{
		BYTE tmp = pBuf[len - 1 - i];
		pBuf[len - 1 - i] = pBuf[i];
		pBuf[i] = tmp;
	}
}

int NCTool::CreateRand(unsigned int min /*= 0*/, unsigned int max /*= 0*/)
{
	int result = 0;
	srand((int)time(NULL));
	if (max > 0 && max > min)
	{
		int mod = max - min + 1;
		result = rand() % mod + min;
	}
	else
	{
		result = rand() + min;
	}
	return result;
}