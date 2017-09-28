#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "RecvPeerDataEvt.h"
#include "TcpDisconnectEvt.h"
#include "SendDataResultEvt.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv),
		m_pAsyncSendBuf(NULL),
		m_nAsyncSendLen(0),
		m_nAsyncSendStatus(EAsyncSendStatus::SendCmp),
		m_bCanAsyncSend(true)
	{
		CNetworkCommuMgr::GetSelect()->AddSocket(sendrecv, ESelectSocketType::ReadWriteData);//加入select队列
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

	CTcpService* CTcpConnection::GetTcpService()
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
			PrintfError(_T("Send data to %s:%d failed"), m_peerAddress.ip, m_peerAddress.port);
			OnConnDisconnect();
		}
	}

	bool CTcpConnection::SendData(BYTE* pBuf, int len, int* actualLen)
	{
		int len1 = 0;//实际发送长度
		bool result = m_socketAPI.Send(m_sendrecvSocket, pBuf, len, &len1);

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
			bool result = m_socketAPI.Send(m_sendrecvSocket, m_pAsyncSendBuf, m_nAsyncSendLen, &len);

			CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CSendDataResultEvt(m_pTcpSrv, result, m_nAsyncSendLen, len));

			delete m_pAsyncSendBuf;
			m_pAsyncSendBuf = NULL;
			m_nAsyncSendLen = 0;

			m_nAsyncSendStatus = EAsyncSendStatus::SendCmp;

			ProcessSendResult(result);
		}
	}

	void CTcpConnection::OnRecvPeerData()
	{
		BYTE* pRecvBuf = new BYTE[NETCOMM_TCPRECVBUFFERSIZE];
		int len = m_socketAPI.Recv(m_sendrecvSocket, pRecvBuf, NETCOMM_TCPRECVBUFFERSIZE);
		if (len == SOCKET_ERROR)
		{
			OnConnDisconnect();
		}
		else if (len == 0)//客户端断开了连接
		{
			OnConnDisconnect();
		}
		else
		{
			PrintfDebug(_T("[%s:%d][socket: %d] recved [%s:%d][socket: %d] data, size: %d"),
				m_localAddress.ip, m_localAddress.port, m_pTcpSrv->GetSocket(), m_peerAddress.ip, m_peerAddress.port, m_sendrecvSocket, len);

			CRecvPeerDataEvt* pEvent = new CRecvPeerDataEvt(m_pTcpSrv, m_sendrecvSocket, pRecvBuf, len);
			CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
		}
	}

	void CTcpConnection::OnConnDisconnect()
	{
		CNetworkCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//移除select队列中socket
		CNetworkCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new CTcpDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
		CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//移除tcp连接对象
	}

	void CTcpConnection::OnNetError()
	{
		CNetworkCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//移除指定发送(接收)数据的socket关联的tcp连接
	}
}