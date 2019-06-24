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
		pParam2(NULL)
	{

	}

	TcpService::~TcpService()
	{

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

	void TcpService::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		DispatchTcpEvt(pEvent);
	}

	void TcpService::DispatchTcpEvt(TcpEvt* pEvent)
	{
		if (lpCallback)
		{
			lpCallback(pEvent, pParam1, pParam2);	// 通知事件注册方
		}
	}
}