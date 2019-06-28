#include "stdafx.h"
#include "LibSrv1.h"
#include "Include/Lib1/PacketCmd.h"
#include "PacketTool.h"
#include "PacketHead.h"
#include "Include/Lib1/Packet.h"
#include "EncryptHelper.h"

#include "tc/NetworkStreamRead.h"
#include "tc/NetworkStreamWrite.h"
#include "tc/RecvDataEvt.h"

namespace lib1
{
	LibSrv1::LibSrv1(EServiceType type /*= EServiceType::None*/, void* pObj /*= NULL*/, ELibSrvType type1 /*= ELibSrvType::Client*/) :
		srvType(type),
		pObj(pObj),
		libSrvType(type1)
	{

	}

	LibSrv1::~LibSrv1()
	{

	}

	string LibSrv1::GetIp1()
	{
		if (libSrvType == ELibSrvType::Client)
		{
			return ((TcpClient*)pObj)->GetIP();
		}
		else
		{
			return ((TcpServer*)pObj)->GetIP();
		}
	}

	int LibSrv1::GetPort1()
	{
		if (libSrvType == ELibSrvType::Client)
		{
			return ((TcpClient*)pObj)->GetPort();
		}
		else
		{
			return ((TcpServer*)pObj)->GetPort();
		}
	}

	void LibSrv1::WriteLog(ETcpLogType type, string format, ...)
	{
		char log[1024] = { 0 };
		va_list  argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, 1024 - 1, format.c_str(), argPtr);
		va_end(argPtr);

		OnLog(type, log);
	}

	void LibSrv1::OnLog(ETcpLogType type, string log)
	{
		// ...
	}

	void LibSrv1::OnRecvTcpEvent(TcpEvt* pEvt)
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

	void LibSrv1::ProcessRecvBuf(BYTE* pBuf, int len, int clientId /*= 0*/)
	{
		ms.Write(pBuf, len);
		vector<PacketData> vec = ParsePacketBuf();
		for (vector<PacketData>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			it->clientId = clientId;
			OnProcessPck(*it);

			delete it->pBuf;
		}
	}

	vector<PacketData> LibSrv1::ParsePacketBuf()
	{
		vector<PacketData> vec;

		while (ms.AvaliableReadLen() > Lib1_PacketHeadLen)
		{
			BYTE buf[Lib1_PacketHeadLen] = { 0 };
			ms.Copy(buf, Lib1_PacketHeadLen);
			CNetworkStreamRead ns(buf, Lib1_PacketHeadLen, EByteOrder::litte);
			PacketHead header;
			header.Read(ns);
			if (header.IsValid())
			{
				int cmd = header.GetCmd();
				int len = header.GetPacketLen();
				int totalLen = header.GetTotalLen();
				if (totalLen <= ms.AvaliableReadLen())
				{
					BYTE buf2[Lib1_PacketHeadLen] = { 0 };
					ms.Read(buf2, Lib1_PacketHeadLen);

					BYTE* pBuf = new BYTE[len];
					ms.Read(pBuf, len);

					bool b1 = EncryptHelper::Decrypt((char*)pBuf, len, header.GetCode());
					if (b1)
					{
						PacketData data = { pBuf, len, header.GetCmd() };
						vec.push_back(data);
					}
					else
					{
						LibSrv1::WriteLog(ETcpLogType::Warn, "parse pck error, decryption incorrect, addr: %s:%d, cmd: %d, len: ",
							GetIp1().c_str(), GetPort1(), cmd, len);
					}
				}
			}
			else
			{
				ms.Clear();
				LibSrv1::WriteLog(ETcpLogType::Warn, "parse pck error, header incorrect, addr: %s:%d, cmd: %d, len: ",
					GetIp1().c_str(), GetPort1(), header.GetCmd(), header.GetPacketLen());
			}
		}

		return vec;
	}

	void LibSrv1::OnConnectCpl(TcpEvt* pEvt)
	{

	}

	void LibSrv1::OnConnDiconnect(TcpEvt* pEvt)
	{

	}

	void LibSrv1::OnRecvConnection(TcpEvt* pEvt)
	{

	}

	void LibSrv1::OnRecvPeerData(TcpEvt* pEvt)
	{

	}

	void LibSrv1::OnProcessPck(PacketData& data)
	{
		if (data.cmd == (int)EPacketCmd::KeepAlive)
		{
			OnKeepAlive(data);
		}
		else if (data.cmd == (int)EPacketCmd::LoginSrvRequest)
		{
			OnLoginSrvRequest(data);
		}
		else if (data.cmd == (int)EPacketCmd::LoginSrvResult)
		{
			OnLoginSrvResult(data);
		}
		else
		{
			OnProcessBusinessPck(data);
		}
	}

	void LibSrv1::OnProcessBusinessPck(PacketData& data)
	{

	}

	void LibSrv1::OnKeepAlive(PacketData& data)
	{

	}

	void LibSrv1::OnLoginSrvRequest(PacketData& data)
	{

	}

	void LibSrv1::OnLoginSrvResult(PacketData& data)
	{

	}

	void LibSrv1::SendPck1(PacketBase& pck, int clientId /*= 0*/)
	{
		BYTE buf[LIB1_MAXSENDBULEN] = { 0 };
		int len = PacketTool::BuildBuf(pck, buf);

		if (clientId == 0)
		{
			((TcpClient*)pObj)->Send(buf, len);
		}
		else
		{
			((TcpServer*)pObj)->Send(clientId, buf, len);
		}
	}

	EServiceType LibSrv1::GetSrvType()
	{
		return srvType;
	}
}