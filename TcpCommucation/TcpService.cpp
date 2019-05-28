#include "stdafx.h"
#include "TcpService.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "ServerTcpConnection.h"
#include "Include/tc/RecvNewConnEvt.h"

namespace tc
{
	TcpService::TcpService() :
		socket(INVALID_SOCKET),
		nSelfPort(0),
		lpCallback(NULL)
	{
		CTcpCommuMgr::GetTcpServiceMgr()->PushTcpService(this);
		strSelfIP = "";
	}

	TcpService::~TcpService()
	{

	}

	SOCKET TcpService::GetSocket()
	{
		return socket;
	}

	string TcpService::GetSelfIP()
	{
		return strSelfIP;
	}

	int TcpService::GetSelfPort()
	{
		return nSelfPort;
	}

	void TcpService::RegTcpEventCallback(LPTcpEventCallback lpCallback, void* param)
	{
		lpCallback = lpCallback;
		pParam = param;
	}

	bool TcpService::SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs, int* actualLen)
	{
		//获取指定socket的tcp连接对象
		CTcpConnection* pConn = CTcpCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);

		if (pConn)
		{
			if (asyncs)//异步发送
			{
				pConn->SetAsyncSendData(pBuf, len, actualLen);
				return true;
			}
			else//同步发送
			{
				pConn->SendData(pBuf, len, actualLen);
			}
		}

		return false;
	}

	void TcpService::OnRecvTcpEvent(TcpEvt* pEvent)
	{
		DispatchTcpEvt(pEvent);
	}

	void TcpService::DispatchTcpEvt(TcpEvt* pEvent)
	{
		if (lpCallback)
		{
			lpCallback(pEvent, pParam);	//通知事件注册方
		}
	}
}