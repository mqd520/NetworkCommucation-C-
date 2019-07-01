#include "stdafx.h"
#include "Include/tc/PacketCommuSrv.h"
#include "Include/tc/Def1.h"
#include "Include/tc/NetworkStreamRead.h"

namespace tc
{
	PacketCommuSrv::PacketCommuSrv(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port)
	{

	}

	void PacketCommuSrv::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		ETcpEvtType type = pEvt->GetEvtType();
		if (type == ETcpEvtType::ConnDisconnect)
		{
			OnConnDiconnect(pEvt);
		}
		else if (type == ETcpEvtType::ConnectSrvResult)
		{
			OnConnectCpl(pEvt);
		}
		else if (type == ETcpEvtType::RecvData)
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
		//while (ms.AvaliableReadLen() > Lib1_PacketHeadLen)
		//{
		//	BYTE buf[Lib1_PacketHeadLen] = { 0 };
		//	ms.Copy(buf, Lib1_PacketHeadLen);
		//	CNetworkStreamRead ns(buf, Lib1_PacketHeadLen, EByteOrder::litte);
		//	PacketHead header;
		//	header.Read(ns);
		//	if (header.IsValid())
		//	{
		//		int cmd = header.GetCmd();
		//		int len = header.GetPacketLen();
		//		int totalLen = header.GetTotalLen();
		//		if (totalLen <= ms.AvaliableReadLen())
		//		{
		//			BYTE buf2[Lib1_PacketHeadLen] = { 0 };
		//			ms.Read(buf2, Lib1_PacketHeadLen);

		//			BYTE* pBuf = new BYTE[len];
		//			ms.Read(pBuf, len);

		//			bool b1 = EncryptHelper::Decrypt((char*)pBuf, len, header.GetCode());
		//			if (b1)
		//			{
		//				PacketData data = { pBuf, len, header.GetCmd() };
		//				vec.push_back(data);
		//			}
		//			else
		//			{
		//				LibSrv1::WriteLog(ETcpLogType::Warn, "parse pck error, decryption incorrect, addr: %s:%d, cmd: %d, len: ",
		//					GetIp1().c_str(), GetPort1(), cmd, len);


		//			}
		//		}
		//	}
		//	else
		//	{
		//		ms.Clear();
		//		LibSrv1::WriteLog(ETcpLogType::Warn, "parse pck error, header incorrect, addr: %s:%d, cmd: %d, len: ",
		//			GetIp1().c_str(), GetPort1(), header.GetCmd(), header.GetPacketLen());
		//	}
		//}
	}
}