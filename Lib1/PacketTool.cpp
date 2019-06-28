#include "stdafx.h"
#include "PacketTool.h"
#include "EncryptHelper.h"
#include "PacketHead.h"

#include "tc/NetworkStreamWrite.h"
#include "tc/NetworkStreamRead.h"
#include "tc/MemoryStream.h"
#include "tc/NCTool.h"

namespace lib1
{
	PacketTool::PacketTool()
	{

	}

	PacketTool::~PacketTool()
	{

	}

	bool PacketTool::IsPacketCmd(int cmd)
	{
		return true;
	}

	int PacketTool::BuildBuf(PacketBase& pck, BYTE* pBuf, int len /*= LIB1_MAXSENDBULEN*/)
	{
		// 创建包体缓冲区
		BYTE buf1[LIB1_MAXSENDBULEN] = { 0 };
		CNetworkStreamWrite ns1(buf1, LIB1_MAXSENDBULEN, EByteOrder::litte);
		pck.Write(ns1);
		int len1 = ns1.WritedCount();
		int code = EncryptHelper::Encrypt((char*)buf1, len1);

		// 创建包头缓冲区
		BYTE buf2[Lib1_PacketHeadLen] = { 0 };
		CNetworkStreamWrite ns2(buf2, Lib1_PacketHeadLen, EByteOrder::litte);
		PacketHead header(pck.GetCmd(), len1, code);
		header.Write(ns2);

		// 合并包头包体缓冲区
		memcpy(pBuf, buf2, Lib1_PacketHeadLen);
		memcpy(pBuf + Lib1_PacketHeadLen, buf1, len1);

		return Lib1_PacketHeadLen + len1;
	}
}