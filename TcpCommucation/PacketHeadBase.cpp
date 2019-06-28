#include "stdafx.h"
#include "Include/tc/PacketHeadBase.h"

namespace tc
{
	PacketHeadBase::PacketHeadBase(int cmd, int len) :
		nCmd(cmd),
		nLen(len),
		nHeadLen(0)
	{

	}

	PacketHeadBase::~PacketHeadBase()
	{

	}

	int PacketHeadBase::GetHeadLen()
	{
		return nHeadLen;
	}

	int PacketHeadBase::GetPacketLen()
	{
		return nLen;
	}

	int PacketHeadBase::GetTotalLen()
	{
		return nTotalLen;
	}

	int PacketHeadBase::GetCmd()
	{
		return nCmd;
	}

	bool PacketHeadBase::IsValid()
	{
		return false;
	}

	void PacketHeadBase::Read(CNetworkStreamRead& ns)
	{

	}

	void PacketHeadBase::Read1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		CNetworkStreamRead ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Read(ns);
	}

	void PacketHeadBase::Write(CNetworkStreamWrite& ns)
	{

	}

	void PacketHeadBase::Write1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		CNetworkStreamWrite ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Write(ns);
	}
}