#include "stdafx.h"
#include "Include/pck/LoginSrvRequestPacket.h"

namespace pck
{
	LoginSrvRequestPacket::LoginSrvRequestPacket() :
		Packet((int)EPacketCmd::LoginSrvRequest),
		cbCurrentServerType(0),
		cbRequestServerID(0),
		cbKeepAlive(0),
		nVersion(0),
		strGuid("")
	{

	}

	int LoginSrvRequestPacket::GetLen()
	{
		int len = 0;

		len += sizeof(BYTE);
		len += sizeof(BYTE);
		len += sizeof(BYTE);
		len += sizeof(INT32);
		len += sizeof(INT32) + strGuid.size() + 1;

		return len;
	}

	void LoginSrvRequestPacket::Read(NetworkStreamRead& ns)
	{
		cbCurrentServerType = ns.ReadByte();
		cbRequestServerID = ns.ReadByte();
		cbKeepAlive = ns.ReadByte();
		nVersion = ns.ReadInt32();
		strGuid = ns.ReadGB2312Str1();
	}

	void LoginSrvRequestPacket::Write(NetworkStreamWrite& ns)
	{
		ns.WriteByte(cbCurrentServerType);
		ns.WriteByte(cbRequestServerID);
		ns.WriteByte(cbKeepAlive);
		ns.WriteInt32(nVersion);
		ns.WriteGB2312Str(strGuid);
	}
}