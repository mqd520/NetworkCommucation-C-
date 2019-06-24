#include "stdafx.h"
#include "SendDataHandler.h"
#include "Include/tc/SocketTool.h"
#include "SendPeerDataSocEvt.h"
#include "TcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	SendDataHandler::SendDataHandler()
	{

	}

	SendDataHandler::~SendDataHandler()
	{

	}

	void SendDataHandler::OnSocketEvtProcess(SocketEvt* pEvt)
	{
		ESocketEvtType type = pEvt->GetEvtType();
		if (type == ESocketEvtType::SendPeerData)
		{
			OnSendPeerData(pEvt);
		}
	}

	void SendDataHandler::OnSendPeerData(SocketEvt* pEvt)
	{
		SendPeerDataSocEvt* pEvt1 = static_cast<SendPeerDataSocEvt*>(pEvt);
		SOCKET socket = pEvt1->GetSocket();
		BYTE* pBuf = pEvt1->GetBuf();
		int len = pEvt1->GetLen();
		int nLen = 0;
		bool b = SocketTool::Send(socket, pBuf, len, &nLen);
		if (!b)
		{
			TcpConnection* pConn = TcpCommu::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);
			if (pConn)
			{
				pConn->OnConnDisconnect(EDisconnReason::Error);
			}
		}
	}
}