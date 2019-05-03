#include "stdafx.h"
#include "Include/tc/NCTool.h"

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