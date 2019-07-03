#include "stdafx.h"
#include "Include/tc/TcpClient.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpEvt.h"
#include "Include/tc/ConnectSrvCplEvt.h"
#include "Include/tc/TimerMoudleMgr.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpClient::TcpClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port, ETcpSrvType::Client),
		bInited(false),
		bIsConnecting(false),
		bIsConnected(false),
		bIsReconnect(true),
		nTimeSpan(TC_ReconnectTime)
	{
		t.SetTimeout(nTimeSpan);
		Fun3 fun = std::bind(&TcpClient::OnTimer, this, _1, _2, _3, _4);
		t.SetCallback(fun, NULL, NULL);
	}

	TcpClient::~TcpClient()
	{
	
	}

	void TcpClient::Exit()
	{
		TimerMoudleMgr::GetTimerMgr()->Remove(&t);
		__super::Exit();
	}

	void TcpClient::Init()
	{
		if (!bInited)
		{
			bInited = true;
			TcpCommu::GetTcpServiceMgr()->PushTcpService(this);
		}
	}

	void TcpClient::ConnectServer()
	{
		if (!bIsConnecting && !bIsConnected)
		{
			bIsConnecting = true;
			this->socket = SocketTool::CreateTcpSocket();
			if (this->socket != INVALID_SOCKET)
			{
				SocketTool::SetNonBlock(this->socket);
				TcpCommu::GetSocketDataMgr()->Add(this->socket, ESocketType::Connect);
				TcpLog::WriteLine(ETcpLogType::Info, "connecting to %s:%d", this->strIP.c_str(), this->nPort);
				SocketTool::Connect(this->socket, this->strIP, this->nPort, false);
			}
		}
	}

	void TcpClient::OnConnectSrvCpl(ConnectSrvCplEvt* pEvt)
	{
		bIsConnecting = false;
		bIsConnected = pEvt->GetConnectResult();

		if (bIsConnected)
		{
			t.Stop();
		}
		else
		{
			if (bIsReconnect)
			{
				t.Run();
			}
		}

		__super::OnConnectSrvCpl(pEvt);
	}

	void TcpClient::OnConnDisconnect(ConnDisconnectEvt* pEvt)
	{
		bIsConnecting = false;
		bIsConnected = false;
		if (bIsReconnect)
		{
			t.Run();
		}

		__super::OnConnDisconnect(pEvt);
	}

	void TcpClient::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		ConnectServer();
	}

	void TcpClient::SetAutoReconnect(bool b /*= true*/, int time /*= TC_RECONNECTTIME*/)
	{
		bIsReconnect = b;
		nTimeSpan = time;
		t.SetTimeout(nTimeSpan);
		t.Stop();
	}

	void TcpClient::Connect()
	{
		Init();
		if (!bIsConnecting && !bIsConnected)
		{
			ConnectServer();
		}
	}

	void TcpClient::Close(bool b /*= true*/)
	{
		t.Stop();

		if (bIsConnected)
		{
			__super::CloseConnection(socket, b);
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
		if (bIsConnected)
		{
			__super::SendData(socket, pBuf, len);
		}
	}
}