#include "stdafx.h"
#include "Include/pck/KeepAlivePacket.h"

namespace pck
{
	KeepAlivePacket::KeepAlivePacket() :
		Packet((int)EPacketCmd::KeepAlive),
		cbKeepAlive(0)
	{

	}

	int KeepAlivePacket::GetLen()
	{
		return sizeof(BYTE);
	}

	void KeepAlivePacket::Read(NetworkStreamRead& ns)
	{
		cbKeepAlive = ns.ReadByte();
	}

	void KeepAlivePacket::Write(NetworkStreamWrite& ns)
	{
		ns.WriteByte(cbKeepAlive);
	}
}