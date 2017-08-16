#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"

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
		if (m_peerSocket == NULL)//��ʾ��ǰ�Ự���ڿͻ���
		{
			return m_localSocket;
		}
		else//��ʾ��ǰ�Ự���ڷ����
		{
			return m_peerSocket;
		}
	}

	bool CTcpConnection::SendData(BYTE buf[], int len)
	{
		return m_mgr.Send(m_peerSocket, buf, len);
	}

	void CTcpConnection::OnRecvData(SocketRecvData data)
	{
		delete data.pBuf;
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