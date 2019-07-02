#include "stdafx.h"
#include "Include/tc/TcpService.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpService::TcpService(string ip /*= ""*/, int port /*= 0*/) :
		socket(INVALID_SOCKET),
		strIP(ip),
		nPort(port),
		pParam1(NULL),
		pParam2(NULL),
		tcpSrvType(ETcpSrvType::None)
	{

	}

	TcpService::~TcpService()
	{

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
		TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->SendData(pBuf, len);
		}
	}

	void TcpService::OnTcpEvt(TcpEvt* pEvt)
	{
		ETcpEvtType type = ETcpEvtType::None;
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
			OnRecvPeerData((RecvPeerDataEvt*)pEvt);
		}

		DispatchTcpEvt(pEvt);
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

	void TcpService::Exit()
	{

	}
}