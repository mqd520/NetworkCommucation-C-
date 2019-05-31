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
		m_nAsyncSendStatus(EAsyncSendStatus::SendCmp),
		m_bCanAsyncSend(true)
	{
		CTcpCommuMgr::GetSelect()->AddSocket(sendrecv, ESocketType::SendRecvData);	// 加入select队列
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

		m_nAsyncSendStatus = EAsyncSendStatus::PreSend;
	}

	void CTcpConnection::AsyncSendData()
	{
		if (m_nAsyncSendStatus == EAsyncSendStatus::PreSend && m_pAsyncSendBuf && m_nAsyncSendLen > 0)
		{
			int len = 0;
			m_nAsyncSendStatus = EAsyncSendStatus::Sending;
			bool result = SocketTool::Send(m_sendrecvSocket, m_pAsyncSendBuf, m_nAsyncSendLen, &len);

			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new SendDataResultEvt(m_pTcpSrv, result, m_nAsyncSendLen, len));

			delete m_pAsyncSendBuf;
			m_pAsyncSendBuf = NULL;
			m_nAsyncSendLen = 0;

			m_nAsyncSendStatus = EAsyncSendStatus::SendCmp;

			ProcessSendResult(result);
		}
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

			if (len == 0) // 没有接收到任何数据
			{

			}

			if (len < 0)	// 发生异常了
			{
				OnConnDisconnect();
			}
		}
	}

	void CTcpConnection::OnConnDisconnect()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//移除select队列中socket
		CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//移除tcp连接对象
	}

	void CTcpConnection::OnNetError()
	{
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//移除指定发送(接收)数据的socket关联的tcp连接
	}

	void CTcpConnection::Close()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);	// 移除select队列中socket
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);	// 移除tcp连接对象
	}
}