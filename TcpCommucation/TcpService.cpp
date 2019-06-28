#include "stdafx.h"
#include "TcpService.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvNewConnEvt.h"

namespace tc
{
	TcpService::TcpService(string ip /*= ""*/, int port /*= 0*/) :
		socket(INVALID_SOCKET),
		strIP(ip),
		nPort(port),
		lpCallback(NULL),
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

	void TcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
	{
		TcpService::lpCallback = lpCallback;
		TcpService::pParam1 = pParam1;
		TcpService::pParam2 = pParam2;
	}

	void TcpService::SendData(SOCKET socket, BYTE* pBuf, int len)
	{
		TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
		if (pConn)
		{
			pConn->SendData(pBuf, len);
		}
	}

	void TcpService::OnRecvTcpEvent(TcpEvt* pEvt)
	{
		DispatchTcpEvt(pEvt);
	}

	void TcpService::DispatchTcpEvt(TcpEvt* pEvt)
	{
		if (lpCallback)
		{
			__try
			{
				lpCallback(pEvt, pParam1, pParam2);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				int n = 0;
				n++;
			}
		}
	}

	void TcpService::Exit()
	{

	}
}