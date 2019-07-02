#include "stdafx.h"
#include "Include/tc/PacketCommuSrv.h"
#include "Include/tc/Def.h"
#include "Include/tc/NetworkStreamRead.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	PacketCommuSrv::PacketCommuSrv(const int nHeadLen, PacketHeadBase header) :
		nHeadLen(nHeadLen),
		header(header)
	{

	}

	void PacketCommuSrv::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		ETcpEvtType type = pEvt->GetEvtType();
		if (type == ETcpEvtType::ConnDisconnect)
		{
			OnConnDiconnect(pEvt);
		}
		else if (type == ETcpEvtType::ConnectSrvCpl)
		{
			OnConnectCpl(pEvt);
		}
		else if (type == ETcpEvtType::RecvPeerData)
		{
			OnRecvPeerData(pEvt);
		}
		else if (type == ETcpEvtType::RecvNewConn)
		{
			OnRecvConnection(pEvt);
		}
	}

	void PacketCommuSrv::OnConnectCpl(TcpEvt* pEvt)
	{

	}

	void PacketCommuSrv::OnConnDiconnect(TcpEvt* pEvt)
	{

	}

	void PacketCommuSrv::OnRecvConnection(TcpEvt* pEvt)
	{

	}

	void PacketCommuSrv::OnRecvPeerData(TcpEvt* pEvt)
	{

	}

	void PacketCommuSrv::ProcessRecvBuf(BYTE* pBuf, int len, int clientId /*= 0*/)
	{
		ms.Write(pBuf, len);

		vector<PacketData> vec;
		ParsePacketBuf(vec);
		for (vector<PacketData>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			it->clientId = clientId;
			//OnProcessPck(*it);

			delete it->pBuf;
		}
	}

	void PacketCommuSrv::ParsePacketBuf(vector<PacketData>& vec)
	{
		while (ms.AvaliableReadLen() > nHeadLen)
		{
			BYTE buf[7] = { 0 };
			ms.Copy(buf, nHeadLen);
			CNetworkStreamRead ns(buf, nHeadLen, EByteOrder::litte);
			PacketHeadBase header1 = header;
			header.Read(ns);
			if (header.IsValid())
			{
				int cmd = header.GetCmd();
				int len = header.GetPacketLen();
				int totalLen = header.GetTotalLen();
				if (totalLen <= ms.AvaliableReadLen())
				{
					BYTE buf2[7] = { 0 };
					ms.Read(buf2, nHeadLen);

					BYTE* pBuf = new BYTE[len];
					ms.Read(pBuf, len);

					bool b2 = ProcessOriginPckBuf(header1, pBuf, len);
					if (b2)
					{
						PacketData data = { pBuf, len, header.GetCmd() };
						vec.push_back(data);
					}
					else
					{
						TcpLog::WriteLine(ETcpLogType::Warn, "parse pck error: pck incorrect, addr: %s:%d, cmd: %d, len: ",
							"", 12345, cmd, len);
					}
				}
			}
			else
			{
				ms.Clear();

				TcpLog::WriteLine(ETcpLogType::Warn, "parse pck error: header incorrect, addr: %s:%d, cmd: %d, len: ",
					"", 12345, header.GetCmd(), header.GetTotalLen());
			}
		}
	}

	bool PacketCommuSrv::ProcessOriginPckBuf(PacketHeadBase& header, BYTE* pBuf, int len)
	{
		throw new exception;
	}

	void PacketCommuSrv::PreProcessPck(PacketData& data)
	{
		OnProcessPck(data);
	}

	void PacketCommuSrv::OnProcessPck(PacketData& data)
	{

	}
}