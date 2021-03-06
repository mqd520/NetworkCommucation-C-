#include "stdafx.h"
#include "Include/tc/TcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvPeerDataEvt.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/SendPeerDataSocEvt.h"
#include "Include/tc/Log.h"

namespace tc
{
	TcpConnection::TcpConnection(TcpService* pSrv, SOCKET sendrecv, bool bEnable /*= true*/) :
		pTcpSrv(pSrv),
		sendrecvSocket(sendrecv)
	{
		SocketTool::SetNonBlock(sendrecv);
		TcpCommu::GetSocketDataMgr()->Add(sendrecv, ESocketType::SendRecvData, bEnable);
	}

	TcpConnection::~TcpConnection()
	{

	}

	SOCKET TcpConnection::GetSendRecvSocket()
	{
		return sendrecvSocket;
	}

	TcpService* TcpConnection::GetTcpService()
	{
		return pTcpSrv;
	}

	void TcpConnection::SendData(BYTE* pBuf, int len)
	{
		TcpCommu::GetSendHandler()->PushSocketEvt(new SendPeerDataSocEvt(sendrecvSocket, pBuf, len));
	}

	void TcpConnection::OnRecvPeerData(BYTE* pBuf, int len)
	{
		TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new RecvPeerDataEvt(pTcpSrv, sendrecvSocket, pBuf, len));
	}

	void TcpConnection::OnConnDisconnect(EDisconnReason reason, bool b /*= true*/)
	{
		if (b)
		{
			TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(pTcpSrv, sendrecvSocket, reason));
		}
		TcpCommu::GetSocketDataMgr()->Remove(sendrecvSocket);

		TcpCommu::GetTcpConnectionMgr()->RemoveBySendRecvSocket(sendrecvSocket);
	}

	void TcpConnection::OnNetError()
	{
		OnConnDisconnect(EDisconnReason::Error);
	}

	void TcpConnection::Close(bool b /*= false*/)
	{
		OnConnDisconnect(EDisconnReason::Local, b);
	}
}