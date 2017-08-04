#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(SOCKET localSocket, SOCKET peerSocket) :
		m_peerSocket(peerSocket),
		m_localSocket(localSocket),
		m_nRecvBufLen(1024)
	{
		m_pRecvBuf = new BYTE[m_nRecvBufLen];
	}

	CTcpConnection::~CTcpConnection()
	{
		if (m_pRecvBuf)
		{
			delete m_pRecvBuf;
		}
	}

	SOCKET CTcpConnection::GetRecvSocket()
	{
		if (m_peerSocket == NULL)//表示当前会话属于客户端
		{
			return m_localSocket;
		}
		else//表示当前会话属于服务端
		{
			return m_peerSocket;
		}
	}

	bool CTcpConnection::SendData(BYTE buf[], int len)
	{
		return true;
	}

	bool CTcpConnection::SendPacket(PacketBase* pack)
	{
		return true;
	}

	bool CTcpConnection::BatchSendPacket(vector<PacketBase*> packs)
	{
		return true;
	}

	void CTcpConnection::OnReadData()
	{
		int result = m_mgr.Recv(GetPeerSocket(), m_pRecvBuf, m_nRecvBufLen);
		if (result > 0)
		{
			_tprintf(_T("Recv data from %d, size: %d \n"), GetPeerSocket(), result);
		}
		else
		{

		}
	}

	SOCKET CTcpConnection::GetLocalSocket()
	{
		return m_localSocket;
	}

	SOCKET CTcpConnection::GetPeerSocket()
	{
		return m_peerSocket;
	}
}