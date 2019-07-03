#include "stdafx.h"
#include "Include/pck/IGPacketHead.h"
#include "Include/pck/Def.h"
#include "Include/pck/PacketTool.h"

/*
	第1、2字节:	mask
	第3、4字节:	cmd
	第5、6字节:	len(包总长)
	第7字节:	code(加密码)
	*/

namespace pck
{
	IGPacketHead::IGPacketHead(int cmd /*= 0*/, int len /*= 0*/) :
		PacketHead(cmd, len),
		nMask(PCR_PacketHeadMask),
		nCode(0)
	{
		this->nHeadLen = PCR_PacketHeadLen;
		this->nTotalLen = this->nHeadLen + this->nLen;
	}

	void IGPacketHead::Read(NetworkStreamRead& ns)
	{
		this->nMask = ns.ReadInt16();
		this->nCmd = ns.ReadInt16();
		this->nTotalLen = ns.ReadInt16();
		this->nCode = ns.ReadByte();

		this->nLen = this->nTotalLen - PacketHead::nHeadLen;
	}

	void IGPacketHead::Write(NetworkStreamWrite& ns)
	{
		ns.WriteInt16(this->nMask);
		ns.WriteInt16(this->nCmd);
		ns.WriteInt16(this->nTotalLen);
		ns.WriteByte(this->nCode);
	}

	bool IGPacketHead::IsValid()
	{
		if (PacketTool::IsCmdValid((EPacketCmd)this->nCmd) &&
			this->nTotalLen <= PCR_MaxPacketLen &&
			this->nCode >= 0 && this->nCode <= 256 &&
			this->nMask == PCR_PacketHeadMask)
		{
			return true;
		}

		return false;
	}

	int IGPacketHead::GetCode()
	{
		return nCode;
	}

	int IGPacketHead::GetMask()
	{
		return nMask;
	}
}