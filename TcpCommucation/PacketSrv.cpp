#include "stdafx.h"
#include "Include/tc/PacketSrv.h"
#include "Include/tc/Def.h"
#include "Include/tc/NetworkStreamRead.h"
#include "Include/tc/TcpLog.h"
#include "Include/tc/TcpClient.h"
#include "Include/tc/TcpServer.h"

namespace tc
{
	PacketSrv::PacketSrv(void* pObj /*= NULL*/, bool bBigByteOrder /*= true*/) :
		pObjPS(pObj),
		bBigByteOrder(bBigByteOrder)
	{

	}

	PacketSrv::~PacketSrv()
	{

	}

	string PacketSrv::GetPeerIp(int clientId /*= 0*/)
	{
		if (clientId == 0)
		{
			return ((TcpClient*)pObjPS)->GetIP();
		}
		else
		{
			return ((TcpServer*)pObjPS)->GetPeerIp(clientId);
		}
	}

	int PacketSrv::GetPeerPort(int clientId /*= 0*/)
	{
		if (clientId == 0)
		{
			return ((TcpClient*)pObjPS)->GetPort();
		}
		else
		{
			return ((TcpServer*)pObjPS)->GetPeerPort(clientId);
		}
	}

	void PacketSrv::AttachTcpServiceObj(void* pObj)
	{
		this->pObjPS = pObj;
	}

	PacketHead* PacketSrv::GetPacketHead(int cmd, int len)
	{
		return new PacketHead(cmd, len);
	}

	int PacketSrv::GetPacketHeadLen()
	{
		throw new exception;
	}

	void PacketSrv::ProcessRecvBuf(BYTE* pBuf, int len, int clientId /*= 0*/)
	{
		ms.Write(pBuf, len);

		vector<PacketData> vec;
		ParsePacket(vec);

		for (vector<PacketData>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			(*it).clientId = clientId;
			(*it).peerIp = GetPeerIp(clientId);
			(*it).peerPort = GetPeerPort(clientId);
			PreProcessPck(*it);

			delete it->pPck;
		}
	}

	void PacketSrv::ParsePacket(vector<PacketData>& vec)
	{
		int headLen = GetPacketHeadLen();
		BYTE buf[TC_MaxPacketHeadLen] = { 0 };

		while (ms.AvaliableReadLen() > headLen)
		{
			memset(buf, 0, TC_MaxPacketHeadLen);

			ms.Copy(buf, headLen);
			PacketHead* pHead = ParsePacketHead(buf, headLen);

			if (pHead->IsValid())
			{
				int cmd = pHead->GetCmd();
				int len = pHead->GetPacketLen();
				int totalLen = pHead->GetTotalLen();

				if (totalLen <= ms.AvaliableReadLen())
				{
					ms.Read(buf, headLen);

					BYTE* pBuf3 = new BYTE[len];
					ms.Read(pBuf3, len);

					int len2 = -1;
					BYTE* pBuf4 = ParsePacketBody(pHead, pBuf3, len, &len2);
					if (len2 >= 0)
					{
						Packet* pPck = BufToPacket(cmd, pBuf4, len2);
						PacketData pd = { pPck, cmd, 0 };
						vec.push_back(pd);
					}
					else
					{
						TcpLog::WriteLine(ETcpLogType::Warn, "parse pck error, cmd: %d, len: %d, addr: %s:%d ",
							cmd, len, GetPeerIp().c_str(), GetPeerPort());
					}

					if (pBuf3 == pBuf4)
					{
						delete pBuf3;
					}
					else
					{
						delete pBuf3;
						delete pBuf4;
					}
				}
			}
			else
			{
				ms.Clear();

				TcpLog::WriteLine(ETcpLogType::Warn, "parse header error, cmd: %d, len: %d, addr: %s:%d ",
					pHead->GetCmd(), pHead->GetTotalLen(), GetPeerIp().c_str(), GetPeerPort());
			}

			delete pHead;
		}
	}

	PacketHead* PacketSrv::ParsePacketHead(BYTE* pBuf, int len)
	{
		NetworkStreamRead ns(pBuf, len, bBigByteOrder ? EByteOrder::big : EByteOrder::litte);
		PacketHead* pHead = GetPacketHead(0, 0);
		pHead->Read(ns);

		return pHead;
	}

	BYTE* PacketSrv::ParsePacketBody(PacketHead* pHead, BYTE* pBuf, int len, int* len1)
	{
		*len1 = len;

		return pBuf;
	}

	Packet* PacketSrv::BufToPacket(int cmd, BYTE* pBuf, int len)
	{
		throw new exception;
	}

	void PacketSrv::PreProcessPck(PacketData& pd)
	{
		OnProcessPck(pd);
	}

	void PacketSrv::OnProcessPck(PacketData& pd)
	{
		TcpLog::WriteLine(ETcpLogType::Warn, "OnProcessPck, cmd: %d, len: %d, addr: %s:%d",
			pd.pPck->GetCmd(), pd.pPck->GetLen(), GetPeerIp().c_str(), GetPeerPort());
	}

	int PacketSrv::BuildPacketBuf(Packet& pck, BYTE* pBuf, int len,
		void* pHeadParam1 /*= NULL*/, void* pHeadParam2 /*= NULL*/, void* pPacketParam1 /*= NULL*/, void* pPacketParam2 /*= NULL*/)
	{
		BYTE buf1[TC_MaxPacketLen] = { 0 };
		int n1 = BuildPacketBodyBuf(pck, buf1, TC_MaxPacketLen, pHeadParam1, pHeadParam2);

		BYTE buf2[TC_MaxPacketHeadLen] = { 0 };
		int n2 = BuildPacketHeadBuf(pck.GetCmd(), pck.GetLen(), buf2, TC_MaxPacketHeadLen, pPacketParam1, pPacketParam2);

		memcpy(pBuf, buf2, n2);
		memcpy(pBuf + n2, buf1, n1);

		return n1 + n2;
	}

	int PacketSrv::BuildPacketHeadBuf(int cmd, int len, BYTE* pBuf, int nLen, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		PacketHead* pHead = GetPacketHead(cmd, len);
		NetworkStreamWrite ns(pBuf, nLen, bBigByteOrder ? EByteOrder::big : EByteOrder::litte);
		pHead->Write(ns);
		int n = pHead->GetHeadLen();
		delete pHead;

		return n;
	}

	int PacketSrv::BuildPacketBodyBuf(Packet& pck, BYTE* pBuf, int len, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		NetworkStreamWrite ns(pBuf, len, bBigByteOrder ? EByteOrder::big : EByteOrder::litte);
		pck.Write(ns);

		return pck.GetLen();
	}

	void PacketSrv::SendPacket(Packet& pck, int clientId /*= 0*/)
	{
		BYTE buf[TC_MaxSendBufLen] = { 0 };
		int len = BuildPacketBuf(pck, buf, TC_MaxSendBufLen, NULL, NULL, NULL, NULL);
		SendPacketBuf(buf, len, clientId);
	}

	void PacketSrv::SendPacketBuf(BYTE* pBuf, int len, int clientId /*= 0*/)
	{
		if (clientId == 0)
		{
			((TcpClient*)pObjPS)->Send(pBuf, len);
		}
		else
		{
			((TcpServer*)pObjPS)->Send(clientId, pBuf, len);
		}
	}

	bool PacketSrv::IsBigByteOrder() const
	{
		return bBigByteOrder;
	}

	void PacketSrv::Exit()
	{

	}
}