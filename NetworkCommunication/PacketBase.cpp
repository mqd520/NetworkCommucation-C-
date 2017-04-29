#include "stdafx.h"
#include "PacketBase.h"

namespace NetworkCommunication
{
	PacketBase::PacketBase()
	{

	}

	PacketBase::~PacketBase()
	{

	}

	int PacketBase::GetCmd()
	{
		return 0;
	}

	BYTE* PacketBase::Read(int* len)
	{
		return NULL;
	}

	void PacketBase::Write(BYTE* buf, int len)
	{

	}
}