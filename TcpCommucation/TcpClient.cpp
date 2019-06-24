#include "stdafx.h"
#include "Include/tc/TcpClient.h"
#include "Include/tc/Def1.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpEvt.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "LogMgr.h"

namespace tc
{
	TcpClient::TcpClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port),
		bIsConnecting(false),
		bIsConnected(false)
	{
		this->tcpSrvType = ETcpSrvType::Client;
	}

	TcpClient::~TcpClient()
	{

	}

	void TcpClient::Init()
	{

	}

	void TcpClient::ConnectServer()
	{
		if (!bIsConnecting && !bIsConnected)
		{
			bIsConnecting = true;
			this->socket = SocketTool::CreateTcpSocket();
			if (this->socket != INVALID_SOCKET)
			{
				bool b1 = SocketTool::Bind(this->socket, this->strIP, this->nPort);
				if (b1)
				{
					SocketTool::SetNonBlock(this->socket);
					TcpCommu::GetSocketDataMgr()->Add(this->socket, ESocketType::Connect);
					TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Info, "connecting to %s:%d", this->strIP, this->nPort);
					SocketTool::Connect(this->socket, this->strIP, this->nPort, false);
				}
			}
		}
	}

	void TcpClient::Connect()
	{
		Close(false);
		ConnectServer();
	}

	void TcpClient::Close(bool b /*= true*/)
	{
		if (this->socket != INVALID_SOCKET)
		{
			if (bIsConnected)
			{
				TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(this->socket);
				if (pConn)
				{
					pConn->Close(b);
				}
			}
			else
			{
				TcpCommu::GetSocketDataMgr()->Remove(this->socket);
			}
		}

		bIsConnecting = false;
		bIsConnected = false;
	}

	void TcpClient::SetConnectInfo(string ip, int port)
	{
		this->strIP = ip;
		this->nPort = port;
	}

	void TcpClient::Send(BYTE* pBuf, int len)
	{
		return __super::SendData(socket, pBuf, len);
	}

	void TcpClient::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		if (pEvt->GetEvtType() == ETcpEvtType::ConnectSrvResult)
		{
			bIsConnecting = false;
			ConnectSrvResultEvt* pEvt1 = (ConnectSrvResultEvt*)pEvt;
			bIsConnected = pEvt1->GetConnectResult();

			if (bIsConnected)
			{
				TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Info, "connect to %s:%d success", this->strIP, this->nPort);
			}
			else
			{
				TcpCommu::GetLogMgr()->AddLog(ETcpLogType::Err, "connect to %s:%d fail", this->strIP, this->nPort);
			}
		}

		__super::OnRecvTcpEvent(pEvt);
	}
}