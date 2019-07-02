#include "stdafx.h"
#include "Include/tc/TcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvPeerDataEvt.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/SendPeerDataSocEvt.h"
#include "Include/tc/TcpLog.h"

namespace tc
{
	TcpConnection::TcpConnection(TcpService* pSrv, SOCKET sendrecv) :
		pTcpSrv(pSrv),
		sendrecvSocket(sendrecv)
	{
		SocketTool::SetNonBlock(sendrecv);
		TcpCommu::GetSocketDataMgr()->Add(sendrecv, ESocketType::SendRecvData);
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
		SocketInfoData data = TcpCommu::GetSocketDataMgr()->Remove(sendrecvSocket);
		TcpLog::WriteLine(ETcpLogType::Warn, "connection disconnect: %s:%d, reason: %d", data.peerIp.c_str(), data.peerPort, (int)reason);

		if (b)
		{
			TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(pTcpSrv, sendrecvSocket));
		}
		SocketTool::ShutDown(sendrecvSocket, false);
		SocketTool::CloseSocket(sendrecvSocket, false);

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