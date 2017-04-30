#include "stdafx.h"
#include "DemoPacket.h"
#include "NetworkStream.h"
#include "MemoryTool.h"

namespace DemoProtocolMgr
{
	//////////////////////////////////包头////////////////////////////////////////
	DemoPacketHead::DemoPacketHead()
	{

	}

	DemoPacketHead::~DemoPacketHead()
	{

	}

	int DemoPacketHead::GetHeadLen()
	{
		return DemoPacketHead_Len;
	}

	int DemoPacketHead::GetPacketLen()
	{
		return nLen - GetHeadLen();
	}

	int DemoPacketHead::GetTotalLen()
	{
		return nLen;
	}

	int DemoPacketHead::GetCmd()
	{
		return nCmd;
	}

	bool DemoPacketHead::IsValid()
	{
		if (nMask == DemoPacketHead_Mask)
		{
			return true;
		}
		return false;
	}

	BYTE* DemoPacketHead::Read(int cmd, int len)
	{
		CNetworkStream s;
		s.WriteShort((short)DemoPacketHead_Mask);
		s.WriteShort((short)cmd);
		s.WriteShort((short)len + (short)GetHeadLen());
		s.WriteByte(0);
		BYTE* buf = new BYTE[GetHeadLen()];
		s.Read(buf, GetHeadLen());
		return buf;
	}

	void DemoPacketHead::Write(BYTE* buf, int len)
	{
		if (len == GetHeadLen())
		{
			CNetworkStream s;
			s.Write(buf, len);
			nMask = s.ReadShort();
			nCmd = s.ReadShort();
			nLen = s.ReadShort();
			cbCode = s.ReadByte();
		}
	}

#define Packet_Implement_Constructor(classname)\
	classname::classname(){}

#define Packet_Implement_Unconstructor(classname)\
	classname::~classname(){}

#define Packet_Implement_GetCmd(classname,cmd)\
	int classname::GetCmd(){return cmd;}

#define Packet_Implement_Release(classname)\
	void classname::Release(){}

	//////////////////////////////////心跳包////////////////////////////////////////
	Packet_Implement_Constructor(KeepAlivePack)
		Packet_Implement_Unconstructor(KeepAlivePack)
		Packet_Implement_GetCmd(KeepAlivePack, DemoPacketCmd::KeepAlive)
		Packet_Implement_Release(KeepAlivePack)
		BYTE* KeepAlivePack::Read(int* len)
	{
		BYTE* buf = new BYTE[1];
		buf[0] = n;
		if (len != NULL)
		{
			*len = 1;
		}
		return buf;
	}
	void KeepAlivePack::Write(BYTE* buf, int len)
	{
		n = buf[0];
	}

	//////////////////////////////////服务登陆包////////////////////////////////////////
	Packet_Implement_Constructor(ServiceLoginPack)
		Packet_Implement_GetCmd(ServiceLoginPack, DemoPacketCmd::ServiceLogin)
		Packet_Implement_Unconstructor(ServiceLoginPack)
		void ServiceLoginPack::Release()
	{
		if (strGuid)
		{
			delete strGuid;
		}
	}
	BYTE* ServiceLoginPack::Read(int* len)
	{
		CNetworkStream s;
		s.WriteByte(cbCurrentServerType);
		s.WriteByte(cbRequestServerID);
		s.WriteByte(cbKeepAlive);
		s.WriteInt32(nVersion);
		int nByte = GetAStrByteCount(strGuid);
		s.WriteInt32(nByte);
		s.WriteMultiStr(strGuid);
		int nlen = s.AvaliableRead();
		BYTE* buf = new BYTE[nlen];
		s.Read(buf, nlen);
		if (len != NULL)
		{
			*len = nlen;
		}
		return buf;
	}
	void ServiceLoginPack::Write(BYTE* buf, int len)
	{
		CNetworkStream s;
		s.Write(buf, len);
		cbCurrentServerType = s.ReadByte();
		cbRequestServerID = s.ReadByte();
		cbKeepAlive = s.ReadByte();
		nVersion = s.ReadInt32();
		int nlen = s.ReadInt32();
		strGuid = s.ReadMultiStr(nlen);
	}

	//////////////////////////////////服务登陆应答包////////////////////////////////////////
	Packet_Implement_Constructor(ServiceLoginReplyPack)
		Packet_Implement_GetCmd(ServiceLoginReplyPack, DemoPacketCmd::ServiceLoginReply)
		Packet_Implement_Unconstructor(ServiceLoginReplyPack)
		Packet_Implement_Release(ServiceLoginReplyPack)
		BYTE* ServiceLoginReplyPack::Read(int* len)
	{
		CNetworkStream s;
		s.WriteByte(cbVerifyCode);
		s.WriteInt32(nServerID);
		int nlen = s.AvaliableRead();
		BYTE* buf = new BYTE[nlen];
		s.Read(buf, nlen);
		if (len != NULL)
		{
			*len = nlen;
		}
		return buf;
	}
	void ServiceLoginReplyPack::Write(BYTE* buf, int len)
	{
		CNetworkStream s;
		s.Write(buf, len);
		cbVerifyCode = s.ReadByte();
		nServerID = s.ReadInt32();
	}

	//////////////////////////////////荷官登陆包////////////////////////////////////////
	Packet_Implement_Constructor(DealerLoginPack)
		Packet_Implement_GetCmd(DealerLoginPack, DemoPacketCmd::DealerLogin)
		Packet_Implement_Unconstructor(DealerLoginPack)
		Packet_Implement_Release(DealerLoginPack)
		BYTE* DealerLoginPack::Read(int* len)
	{
		CNetworkStream s;
		int nStrNameLen = GetWStrByteCount(strName);//用户名字符串字节长度
		s.WriteInt32(nStrNameLen);
		s.WriteUTF8Str(strName);
		int nStrPwdLen = GetWStrByteCount(strPwd);//密码字符串字节长度
		s.WriteInt32(nStrPwdLen);
		s.WriteUTF8Str(strPwd);
		s.WriteInt32(nTableID);
		s.WriteInt32((int)vecMac.size());
		for (vector<wchar_t*>::iterator it = vecMac.begin(); it < vecMac.end(); it++)
		{
			int strlen = GetWStrByteCount(*it);//字符串字节长度
			s.WriteInt32(strlen);
			s.WriteUTF8Str(*it);
		}
		s.WriteInt64(DealerSSID);
		int nlen = s.AvaliableRead();
		BYTE* buf = new BYTE[nlen];
		s.Read(buf, nlen);
		if (len != NULL)
		{
			*len = nlen;
		}
		return buf;
	}
	void DealerLoginPack::Write(BYTE* buf, int len)
	{

	}

	//////////////////////////////////荷官登陆结果包////////////////////////////////////////
	Packet_Implement_Constructor(DealerLoginResultPack)
		Packet_Implement_GetCmd(DealerLoginResultPack, DemoPacketCmd::DealerLoginResult)
		Packet_Implement_Unconstructor(DealerLoginResultPack)
		Packet_Implement_Release(DealerLoginResultPack)
		BYTE* DealerLoginResultPack::Read(int* len)
	{
		return NULL;
	}
	void DealerLoginResultPack::Write(BYTE* buf, int len)
	{
		CNetworkStream s;
		s.Write(buf, len);
		nTableID = s.ReadInt32();
		nResult = s.ReadInt32();
		nReloginCode = s.ReadInt32();
	}
}