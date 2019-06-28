#include "stdafx.h"
#include "Def.h"
#include "Include/Lib1/Packet.h"
#include "Include/Lib1/PacketCmd.h"

namespace lib1
{
	KeepAlivePck::KeepAlivePck(BYTE* pBuf /*= NULL*/, int len /*= 0*/, bool bigEndian /*= true*/) :
		PacketBase((int)EPacketCmd::KeepAlive)
	{
		if (pBuf && len > 0)
		{
			this->Read1(pBuf, len, bigEndian);
		}
	}

	KeepAlivePck::~KeepAlivePck()
	{

	}

	int KeepAlivePck::GetLen()
	{
		int len = 0;
		len += sizeof(BYTE);
		return len;
	}

	void KeepAlivePck::Read(CNetworkStreamRead& ns)
	{
		cbKeepAlive = ns.ReadByte();
	}

	void KeepAlivePck::Write(CNetworkStreamWrite& ns)
	{
		ns.WriteByte(cbKeepAlive);
	}




	LoginSrRequestPck::LoginSrRequestPck(BYTE* pBuf /*= NULL*/, int len /*= 0*/, bool bigEndian /*= true*/) :
		PacketBase((int)EPacketCmd::LoginSrvRequest)
	{
		if (pBuf && len > 0)
		{
			this->Read1(pBuf, len, bigEndian);
		}
	}

	LoginSrRequestPck::~LoginSrRequestPck()
	{

	}

	int LoginSrRequestPck::GetLen()
	{
		int len = 0;
		len += sizeof(BYTE);
		len += sizeof(BYTE);
		len += sizeof(BYTE);
		len += sizeof(INT32);
		len += sizeof(INT32) + strGuid.size() + 1;
		return len;
	}

	void LoginSrRequestPck::Read(CNetworkStreamRead& ns)
	{
		cbCurrentServerType = ns.ReadByte();
		cbRequestServerID = ns.ReadByte();
		cbRequestServerID = ns.ReadByte();
		nVersion = ns.ReadInt32();
		strGuid = ns.ReadGB2312Str1();
	}

	void LoginSrRequestPck::Write(CNetworkStreamWrite& ns)
	{
		ns.WriteByte(cbCurrentServerType);
		ns.WriteByte(cbRequestServerID);
		ns.WriteByte(cbKeepAlive);
		ns.WriteInt32(nVersion);
		ns.WriteGB2312Str(strGuid, sizeof(INT32), true);
	}



	LoginSrResultPck::LoginSrResultPck(BYTE* pBuf /*= NULL*/, int len /*= 0*/, bool bigEndian /*= true*/) :
		PacketBase((int)EPacketCmd::LoginSrvResult)
	{
		if (pBuf && len > 0)
		{
			this->Read1(pBuf, len, bigEndian);
		}
	}

	LoginSrResultPck::~LoginSrResultPck()
	{

	}

	int LoginSrResultPck::GetLen()
	{
		int len = 0;
		len += sizeof(BYTE);
		len += sizeof(INT32);
		return len;
	}

	void LoginSrResultPck::Read(CNetworkStreamRead& ns)
	{
		cbVerifyCode = ns.ReadByte();
		nServerID = ns.ReadInt32();
	}

	void LoginSrResultPck::Write(CNetworkStreamWrite& ns)
	{
		ns.WriteByte(cbVerifyCode);
		ns.WriteInt32(nServerID);
	}
}