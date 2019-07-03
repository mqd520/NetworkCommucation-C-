#include "stdafx.h"
#include "Include/tc/Packet.h"

namespace tc
{
	Packet::Packet(int cmd) :
		pckCmd(cmd)
	{

	}

	int Packet::GetLen()
	{
		return 0;
	}

	int Packet::GetCmd()
	{
		return pckCmd;
	}

	void Packet::Read(NetworkStreamRead& ns)
	{

	}

	void Packet::Read1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		NetworkStreamRead ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Read(ns);
	}

	void Packet::Write(NetworkStreamWrite& ns)
	{

	}

	void Packet::Write1(BYTE* pBuf, int len, bool bigEndian /*= true*/)
	{
		NetworkStreamWrite ns(pBuf, len, bigEndian ? EByteOrder::big : EByteOrder::litte);
		this->Write(ns);
	}
}