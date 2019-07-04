#include "stdafx.h"
#include "Include/tc/TcpServer.h"
#include "Include/tc/TcpConnectionMgr.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpServer::TcpServer(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port, ETcpSrvType::Server),
		bListening(false)
	{

	}

	TcpServer::~TcpServer()
	{

	}

	void TcpServer::SetListenInfo(string ip, int port)
	{
		if (!bListening)
		{
			strIP = ip;
			nPort = port;
		}
	}

	bool TcpServer::Listen()
	{
		if (!bListening)
		{
			socket = SocketTool::CreateTcpSocket();
			if (socket != INVALID_SOCKET)
			{
				bool b1 = SocketTool::Bind(socket, strIP.c_str(), nPort);
				if (b1)
				{
					SocketTool::SetNonBlock(socket);
					bool b2 = SocketTool::Listen(socket, strIP, nPort);
					if (b2)
					{
						TcpCommu::GetSocketDataMgr()->Add(socket, ESocketType::Accept);
						TcpCommu::GetTcpServiceMgr()->PushTcpService(this);
						bListening = true;
					}
				}
			}
		}

		if (bListening)
		{
			TcpLog::WriteLine(ETcpLogType::Info, "listen success: %s:%d", strIP.c_str(), nPort);
		}
		else
		{
			TcpLog::WriteLine(ETcpLogType::Error, "listen fail: %s:%d", strIP.c_str(), nPort);
		}

		return bListening;
	}

	void TcpServer::Send(int clientId, BYTE* pBuf, int len)
	{
		SocketInfoData data = TcpCommu::GetSocketDataMgr()->GetSocketData(clientId);
		if (data.socket > 0)
		{
			__super::SendData(data.socket, pBuf, len);
		}
	}

	void TcpServer::CloseClient(int clientId, bool b /*= true*/)
	{
		SocketInfoData data = TcpCommu::GetSocketDataMgr()->GetSocketData(clientId);
		if (data.socket > 0)
		{
			__super::CloseConnection(data.socket, b);
		}
	}

	string TcpServer::GetPeerIp(int clientId)
	{
		return TcpCommu::GetSocketDataMgr()->GetSocketData(clientId).peerIp;
	}

	int TcpServer::GetPeerPort(int clientId)
	{
		return TcpCommu::GetSocketDataMgr()->GetSocketData(clientId).peerPort;
	}

	void TcpServer::AddAllowIP(string ip)
	{
		bool exist = false;

		for (int i = 0; i < (int)vecAllowIP.size(); i++)
		{
			if (vecAllowIP[i] == ip)
			{
				exist = true;
				break;
			}
		}

		if (!exist)
		{
			vecAllowIP.push_back(ip);
		}
	}

	void TcpServer::RemoveAllowIP(string ip)
	{
		for (vector<string>::iterator it = vecAllowIP.begin(); it < vecAllowIP.end(); it++)
		{
			if (*it == ip)
			{
				vecAllowIP.erase(it);
				break;
			}
		}
	}

	void TcpServer::ClearAllowIP()
	{
		vecAllowIP.clear();
	}

	bool TcpServer::IsAllow(string ip)
	{
		bool result = true;
		int count = (int)vecAllowIP.size();
		if (count > 0)
		{
			result = false;
			for (int i = 0; i < count; i++)
			{
				if (vecAllowIP[i] == ip)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}
}