#include "stdafx.h"
#include "Include/pck/IGPacketSrv.h"
#include "Include/pck/IGPacketHead.h"
#include "Include/pck/EncryptHelper.h"
#include "Include/pck/PacketTool.h"

namespace pck
{
	IGPacketSrv::IGPacketSrv(EServerType localType /*= EServerType::None*/, EServerType peerType /*= EServerType::None*/) :
		PacketSrv(NULL, false),
		localType(localType),
		peerType(peerType)
	{

	}

	IGPacketSrv::~IGPacketSrv()
	{

	}

	PacketHead* IGPacketSrv::GetPacketHead(int cmd, int len)
	{
		return new IGPacketHead(cmd, len);
	}

	int IGPacketSrv::GetPacketHeadLen()
	{
		return PCR_PacketHeadLen;
	}

	BYTE* IGPacketSrv::ParsePacketBody(PacketHead* pHead, BYTE* pBuf, int len, int* len1)
	{
		IGPacketHead* pHead1 = (IGPacketHead*)pHead;
		int code = pHead1->GetCode();
		bool b = EncryptHelper::Decrypt(pBuf, len, code);
		if (b)
		{
			return __super::ParsePacketBody(pHead, pBuf, len, len1);
		}
		else
		{
			*len1 = -1;
			return pBuf;
		}
	}

	Packet* IGPacketSrv::BufToPacket(int cmd, BYTE* pBuf, int len)
	{
		Packet* pPck = PacketTool::GetPacket((EPacketCmd)cmd);
		if (pPck)
		{
			pPck->Read1(pBuf, len, __super::IsBigByteOrder());
		}

		return pPck;
	}

	int IGPacketSrv::BuildPacketBodyBuf(Packet& pck, BYTE* pBuf, int len, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		int n = __super::BuildPacketBodyBuf(pck, pBuf, len, pParam1, pParam2);
		BYTE code = EncryptHelper::Encrypt(pBuf, n);
		if (pParam1)
		{
			memcpy(pParam1, &code, sizeof(BYTE));
		}

		return n;
	}

	void IGPacketSrv::SendPacket(Packet& pck, int clientId /*= 0*/)
	{
		int code = 0;
		BYTE buf[TC_MaxSendBufLen] = { 0 };
		int len = __super::BuildPacketBuf(pck, buf, TC_MaxSendBufLen, &code, NULL, NULL, NULL);
		buf[PCR_PacketHeadLen - 1] = code;

		SendPacketBuf(buf, len, clientId);
	}

	EServerType IGPacketSrv::GetLocalServerType()
	{
		return localType;
	}

	EServerType IGPacketSrv::GetPeerServerType()
	{
		return peerType;
	}
}