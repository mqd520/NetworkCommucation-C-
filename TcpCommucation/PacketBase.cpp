#include "stdafx.h"
#include "Include/tc/PacketBase.h"

namespace tc
{
	PacketBase::PacketBase(int cmd) :
		pckCmd(cmd)
	{

	}

	PacketBase::~PacketBase()
	{

	}

	int PacketBase::GetLen()
	{
		return 0;
	}

	int PacketBase::GetCmd()
	{
		return pckCmd;
	}

	void PacketBase::Read(CNetworkStreamRead& ns)
	{

	}

	void PacketBase::Read1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		CNetworkStreamRead ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Read(ns);
	}

	void PacketBase::Write(CNetworkStreamWrite& ns)
	{

	}

	void PacketBase::Write1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		CNetworkStreamWrite ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Write(ns);
	}
}