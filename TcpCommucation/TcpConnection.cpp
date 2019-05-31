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
		CTcpCommuMgr::GetSelect()->AddSocket(sendrecv, ESocketType::SendRecvData);	// ����select����
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
		int len1 = 0;//ʵ�ʷ��ͳ���
		bool result = SocketTool::Send(m_sendrecvSocket, pBuf, len, &len1);

		if (actualLen != NULL)
		{
			*actualLen = len1;
		}

		ProcessSendResult(result);//���������ݽ��

		return result;
	}

	void CTcpConnection::SetAsyncSendData(BYTE* pBuf, int len, int* actualLen)
	{
		//�ȴ��������ڽ��еķ������ݶ���

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
		if (b)	// �������ݳɹ�
		{
			RecvDataEvt* pEvent = new RecvDataEvt(m_pTcpSrv, m_sendrecvSocket, pRecvBuf, len);
			CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(pEvent);
		}
		else   // ��������ʧ��
		{
			delete pRecvBuf;

			if (len == 0) // û�н��յ��κ�����
			{

			}

			if (len < 0)	// �����쳣��
			{
				OnConnDisconnect();
			}
		}
	}

	void CTcpConnection::OnConnDisconnect()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//�Ƴ�select������socket
		CTcpCommuMgr::GetTcpEvtMgr()->PushTcpEvent(new ConnDisconnectEvt(m_pTcpSrv, m_sendrecvSocket));
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�tcp���Ӷ���
	}

	void CTcpConnection::OnNetError()
	{
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);//�Ƴ�ָ������(����)���ݵ�socket������tcp����
	}

	void CTcpConnection::Close()
	{
		CTcpCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);	// �Ƴ�select������socket
		CTcpCommuMgr::GetTcpConnectionMgr()->RemoveBySendRecvSocket(m_sendrecvSocket);	// �Ƴ�tcp���Ӷ���
	}
}