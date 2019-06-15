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
	CTcpConnection::CTcpConnection(TcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv),
		m_pAsyncSendBuf(NULL),
		m_nAsyncSendLen(0),
		//m_nAsyncSendStatus(EAsyncSendStatus::SendCmp),
		m_bCanAsyncSend(true)
	{
		SocketTool::SetNonBlock(sendrecv);
		CTcpCommuMgr::GetSocketDataMgr()->Add(sendrecv, ESocketType::SendRecvData);
	}

	CTcpConnection::~CTcpConnection()
	{
		if (m_pAsyncSendBuf)
		{
			delete m_pAsyncSendBuf;
		}
	}

	SOCKET CTcpConnection::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	TcpService* CTcpConnection::GetTcpService()
	{
		return m_pTcpSrv;
	}

	NetAddress CTcpConnection::GetLocalAddress()
	{
		return m_localAddress;
	}

	NetAddress CTcpConnection::GetPeerAddress()
	{
		return m_peerAddress;
	}

	void CTcpConnection::ProcessSendResult(bool success)
	{
		if (!success)
		{
			OnConnDisconnect();
		}
	}

	bool CTcpConnection::SendData(BYTE* pBuf, int len, int* actualLen)
	{
		int len1 = 0;//实际发送长度
		bool result = SocketTool::Send(m_sendrecvSocket, pBuf, len, &len1);

		if (actualLen != NULL)
		{
			*actualLen = len1;
		}

		ProcessSendResult(result);//处理发送数据结果

		return result;
	}

	void CTcpConnection::SetAsyncSendData(BYTE* pBuf, int len, int* actualLen)
	{
		//等待可能正在进行的发送数据动作

		m_pAsyncSendBuf = new BYTE[len];
		memcpy(m_pAsyncSendBuf, pBuf, len);
		m_nAsyncSendLen = len;

		//m_nAsyncSendStatus = EAsyncSendStatus::PreSend;
	}

	void CTcpConnection::AsyncSendData()
	{
		//if (m_nAsyncSendStatus == EAsyncSendStatus::PreSend && m_pAsyncSendBuf && m_nAsyncSendLen > 0)
		//{
		//	int len = 0;
		//	m_nAsyncSendStatus = EAsyncSendStatus::Sending;
		//	bool result = SocketTool::Send(m_sendrecvSocket, m_pAsyncSendBuf, m_nAsyncSendLen, &len);

		//	CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new SendDataResultEvt(m_pTcpSrv, result, m_nAsyncSendLen, len));

		//	delete m_pAsyncSendBuf;
		//	m_pAsyncSendBuf = NULL;
		//	m_nAsyncSendLen = 0;

		//	m_nAsyncSendStatus = EAsyncSendStatus::SendCmp;

		//	ProcessSendResult(result);
		//}
	}

	void CTcpConnection::OnRecvPeerData()
	{
		BYTE* pRecvBuf = new BYTE[TC_TCPRECVBUFFERSIZE];
		int len = 0;
		bool b = SocketTool::Recv(m_sendrecvSocket, pRecvBuf, TC_TCPRECVBUFFERSIZE, &len);
		if (b)	// 接收数据成功
		{
			RecvDataEvt* pEvent = new RecvDataEvt(m_pTcpSrv, m_sendrecvSocket, pRecvBuf, len);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
		}
		else   // 接收数据失败
		{
			delete pRecvBuf;

			OnConnDisconnect();	// 连接断开了
		}
	}

	void CTcpConnection::OnConnDisconnect()
	{
		CTcpCommuMgr::GetSocketDataMgr()->Remove(m_sendrecvSocket);
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);
		
		SocketTool::ShutDown(m_sendrecvSocket, false);
		SocketTool::CloseSocket(m_sendrecvSocket, false);

		CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
	}

	void CTcpConnection::OnNetError()
	{
		CTcpCommuMgr::GetSocketDataMgr()->Remove(m_sendrecvSocket);

		SocketTool::ShutDown(m_sendrecvSocket, false);
		SocketTool::CloseSocket(m_sendrecvSocket, false);

		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);
	}

	void CTcpConnection::Close(bool b /*= false*/)
	{
		if (b)
		{
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
		}
		CTcpCommuMgr::GetSocketDataMgr()->Remove(m_sendrecvSocket);

		SocketTool::ShutDown(m_sendrecvSocket, false);
		SocketTool::CloseSocket(m_sendrecvSocket, false);
		
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);
	}
}