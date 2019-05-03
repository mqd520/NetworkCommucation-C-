#include "stdafx.h"
#include "PacketHeadBase.h"

namespace tc
{
	PacketHeadBase::PacketHeadBase()
	{

	}

	PacketHeadBase::~PacketHeadBase()
	{

	}

	int PacketHeadBase::GetHeadLen()
	{
		return 0;
	}

	int PacketHeadBase::GetPacketLen()
	{
		return 0;
	}

	int PacketHeadBase::GetTotalLen()
	{
		return GetHeadLen() + GetPacketLen();
	}

	int PacketHeadBase::GetCmd()
	{
		return 0;
	}

	bool PacketHeadBase::IsValid()
	{
		return false;
	}

	BYTE* PacketHeadBase::Read(int cmd, int len)
	{
		return NULL;
	}

	void PacketHeadBase::Write(BYTE* buf, int len)
	{

	}
}