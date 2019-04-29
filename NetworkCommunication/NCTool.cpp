#include "stdafx.h"
#include "Include/nc/NCTool.h"

using namespace NetworkCommunication;

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