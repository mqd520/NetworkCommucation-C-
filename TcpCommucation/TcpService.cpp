#include "stdafx.h"
#include "Include/tc/TcpService.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpService::TcpService(string ip /*= ""*/, int port /*= 0*/, ETcpSrvType type /*= ETcpSrvType::None*/) :
		socket(INVALID_SOCKET),
		strIP(ip),
		nPort(port),
		pParam1(NULL),
		pParam2(NULL),
		tcpSrvType(type),
		pSessionMgr(NULL)
	{
		pSessionMgr = new SessionMgr();
	}

	TcpService::~TcpService()
	{
		if (this->pSessionMgr)
		{
			delete this->pSessionMgr;
			this->pSessionMgr = NULL;
		}
	}

	void TcpService::OnTcpEvt(TcpEvt* pEvt)
	{
		ETcpEvtType type = pEvt->GetEvtType();
		if (type == ETcpEvtType::RecvNewConn)
		{
			OnRecvNewConnection((RecvNewConnEvt*)pEvt);
		}
		else if (type == ETcpEvtType::ConnDisconnect)
		{
			OnConnDisconnect((ConnDisconnectEvt*)pEvt);
		}
		else if (type == ETcpEvtType::RecvPeerData)
		{
			OnRecvPeerData((RecvPeerDataEvt*)pEvt);
		}
		else if (type == ETcpEvtType::ConnectSrvCpl)
		{
			OnConnectSrvCpl((ConnectSrvCplEvt*)pEvt);
		}

		DispatchTcpEvt(pEvt);
	}

	void TcpService::OnRecvNewConnection(RecvNewConnEvt* pEvt)
	{
		pSessionMgr->Add(pEvt->GetPeerIp(), pEvt->GetPeerPort(), pEvt->GetSendRecvSocketId());

		TcpLog::WriteLine(ETcpLogType::Debug, "recv new connection: %s:%d",
			pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort());
	}

	void TcpService::OnConnDisconnect(ConnDisconnectEvt* pEvt)
	{
		pSessionMgr->Remove(pEvt->GetSendRecvSocketId());

		TcpLog::WriteLine(ETcpLogType::Error, "lose connection from %s:%d",
			pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort());
	}

	void TcpService::OnRecvPeerData(RecvPeerDataEvt* pEvt)
	{
		//TcpLog::WriteLine(ETcpLogType::Debug, "recv data from %s:%d, len: %d",
		//	pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort(), pEvt->GetBufLen());
	}

	void TcpService::OnConnectSrvCpl(ConnectSrvCplEvt* pEvt)
	{
		bool b = pEvt->GetConnectResult();

		if (b)
		{
			pSessionMgr->Add(pEvt->GetPeerIp(), pEvt->GetPeerPort(), pEvt->GetSendRecvSocketId());
		}

		TcpLog::WriteLine(b ? ETcpLogType::Info : ETcpLogType::Error, "connect to %s:%d %s",
			pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort(), b ? "success" : "fail");
	}

	void TcpService::DispatchTcpEvt(TcpEvt* pEvt)
	{
		if (!fun._Empty())
		{
			__try
			{
				fun(pEvt, pParam1, pParam2);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				//TcpLog::WriteLine(ETcpLogType::Exception, "TcpEvt: %d, client: %s:%d",
				//	pEvt->GetEvtType(), pEvt->GetPeerIp().c_str(), pEvt->GetPeerPort());
			}
		}
	}

	void TcpService::CloseConnection(SOCKET socket, bool b /*= true*/)
	{
		if (this->socket != INVALID_SOCKET)
		{
			TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(this->socket);
			if (pConn)
			{
				pConn->Close(b);
			}
		}
	}

	void TcpService::SetSessionMgr(SessionMgr* pSessionMgr)
	{
		if (this->pSessionMgr)
		{
			delete this->pSessionMgr;
		}

		this->pSessionMgr = pSessionMgr;
	}

	ETcpSrvType TcpService::GetTcpSrvType()
	{
		return tcpSrvType;
	}

	SOCKET TcpService::GetSocket()
	{
		return socket;
	}

	string TcpService::GetIP()
	{
		return strIP;
	}

	int TcpService::GetPort()
	{
		return nPort;
	}

	void TcpService::RegTcpEventCallback(Fun2 fun, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		this->fun = fun;
		this->pParam1 = pParam1;
		this->pParam2 = pParam2;
	}

	void TcpService::SendData(SOCKET socket, BYTE* pBuf, int len)
	{
		if (socket != INVALID_SOCKET)
		{
			TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
			if (pConn)
			{
				pConn->SendData(pBuf, len);
			}
		}
		else
		{
			TcpLog::WriteLine(ETcpLogType::Warn, "send data error, socket invalid: %d", socket);
		}
	}

	void TcpService::Init()
	{

	}

	void TcpService::Exit()
	{

	}

	SessionMgr* TcpService::GetSessionMgr()
	{
		return pSessionMgr;
	}
}