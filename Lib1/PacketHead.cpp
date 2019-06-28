#include "stdafx.h"
#include "Def.h"
#include "PacketHead.h"
#include "PacketTool.h"

namespace lib1
{
	PacketHead::PacketHead(int cmd /*= 0*/, int len /*= 0*/, int code /*= 0*/) :
		PacketHeadBase(cmd, len),
		nMask(Lib1_PacketMask),
		nCode(code)
	{
		PacketHeadBase::nHeadLen = Lib1_PacketHeadLen;
		PacketHeadBase::nTotalLen = nHeadLen + nLen;
	}

	PacketHead::~PacketHead()
	{

	}

	void PacketHead::Read(CNetworkStreamRead& ns)
	{
		nMask = ns.ReadInt16();
		nCmd = ns.ReadInt16();
		nTotalLen = ns.ReadInt16();
		nCode = ns.ReadByte();
		nLen = nTotalLen - nHeadLen;
	}

	void PacketHead::Write(CNetworkStreamWrite& ns)
	{
		ns.WriteInt16(nMask);
		ns.WriteInt16(nCmd);
		ns.WriteInt16(nTotalLen);
		ns.WriteByte(nCode);
	}

	bool PacketHead::IsValid()
	{
		if (nMask == Lib1_PacketMask && PacketTool::IsPacketCmd(nCmd) && nLen >= 0)
		{
			return true;
		}

		return false;
	}

	BYTE PacketHead::GetCode()
	{
		return nCode;
	}
}