#include "stdafx.h"
#include "Include/pck/LoginSrvResultPacket.h"

namespace pck
{
	LoginSrvResultPacket::LoginSrvResultPacket() :
		Packet((int)EPacketCmd::LoginSrvResult),
		cbVerifyCode(0),
		nServerID(0)
	{

	}

	int LoginSrvResultPacket::GetLen()
	{
		int len = 0;

		len += sizeof(BYTE);
		len += sizeof(INT32);

		return len;
	}

	void LoginSrvResultPacket::Read(NetworkStreamRead& ns)
	{
		cbVerifyCode = ns.ReadByte();
		nServerID = ns.ReadInt32();
	}

	void LoginSrvResultPacket::Write(NetworkStreamWrite& ns)
	{
		ns.WriteByte(cbVerifyCode);
		ns.WriteInt32(nServerID);
	}
}