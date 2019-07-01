#include "stdafx.h"
#include "Include/tc/TcpClient.h"
#include "Include/tc/Def1.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/TcpEvt.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "Include/tc/TimerMoudleMgr.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	void OnTimer1(Timer* pTimer, int count, void* pParam1, void* pParam2);	// timer»Øµ÷º¯Êý

	TcpClient::TcpClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port),
		bInited(false),
		bIsConnecting(false),
		bIsConnected(false),
		bIsReconnect(true),
		nTimeSpan(TC_RECONNECTTIME)
	{
		this->tcpSrvType = ETcpSrvType::Client;

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
		ETcpEvtType type = pEvt->GetEvtType();
		if (type == ETcpEvtType::ConnectSrvResult)
		{
			bIsConnecting = false;
			ConnectSrvResultEvt* pEvt1 = (ConnectSrvResultEvt*)pEvt;
			bIsConnected = pEvt1->GetConnectResult();

			if (bIsConnected)
			{
				TcpLog::WriteLine(ETcpLogType::Info, "connect to %s:%d success", this->strIP.c_str(), this->nPort);
				t.Stop();
			}
			else
			{
				TcpLog::WriteLine(ETcpLogType::Error, "connect to %s:%d fail", this->strIP.c_str(), this->nPort);
				if (bIsReconnect)
				{
					t.Run();
				}
			}
		}
		else if (type == ETcpEvtType::ConnDisconnect)
		{
			bIsConnecting = false;
			bIsConnected = false;
			if (bIsReconnect)
			{
				t.Run();
			}
		}

		__super::OnRecvTcpEvent(pEvt);
	}

	void TcpClient::OnTimer(Timer* pTimer, int count, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		ConnectServer();
	}
}