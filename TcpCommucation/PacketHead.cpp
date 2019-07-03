#include "stdafx.h"
#include "Include/tc/PacketHead.h"

namespace tc
{
	PacketHead::PacketHead(int cmd, int len) :
		nCmd(cmd),
		nLen(len)
	{
		nHeadLen = GetHeadLen();
		nHeadLen = nLen + nHeadLen;
	}

	int PacketHead::GetHeadLen()
	{
		return nHeadLen;
	}

	int PacketHead::GetPacketLen()
	{
		return nLen;
	}

	int PacketHead::GetTotalLen()
	{
		return nTotalLen;
	}

	int PacketHead::GetCmd()
	{
		return nCmd;
	}

	bool PacketHead::IsValid()
	{
		return false;
	}

	void PacketHead::Read(NetworkStreamRead& ns)
	{

	}

	void PacketHead::Read1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		NetworkStreamRead ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Read(ns);
	}

	void PacketHead::Write(NetworkStreamWrite& ns)
	{

	}

	void PacketHead::Write1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		NetworkStreamWrite ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Write(ns);
	}
}