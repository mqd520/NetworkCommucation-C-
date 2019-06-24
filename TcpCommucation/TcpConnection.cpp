#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/RecvDataEvt.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Include/tc/SendDataResultEvt.h"
#include "Include/tc/SocketTool.h"

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

	void TcpConnection::SendData(BYTE* pBuf, int len, int* actualLen)
	{
		int len1 = 0;//实际发送长度
		bool result = SocketTool::Send(sendrecvSocket, pBuf, len, &len1);

		if (actualLen != NULL)
		{
			*actualLen = len1;
		}
	}

	void TcpConnection::OnRecvPeerData(BYTE* pBuf, int len)
	{
		TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new RecvDataEvt(pTcpSrv, sendrecvSocket, pBuf, len));
	}

	void TcpConnection::OnConnDisconnect(EDisconnReason reason, bool b /*= true*/)
	{
		if (b)
		{
			TcpCommu::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(pTcpSrv, sendrecvSocket));
		}
		TcpCommu::GetSocketDataMgr()->Remove(sendrecvSocket);
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