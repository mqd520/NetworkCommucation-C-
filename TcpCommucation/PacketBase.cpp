#include "stdafx.h"
#include "PacketBase.h"

namespace tc
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

	void PacketBase::Release()
	{

	}
}